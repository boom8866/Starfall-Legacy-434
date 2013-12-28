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
    SPELL_FRENZY                = 74853,
    SPELL_SUMMON_SIEGE_DUMMY    = 74640,
    SPELL_GROUND_SIEGE          = 74634,
    SPELL_SUMMON_BLITZ_DUMMY    = 74668,
    SPELL_BLITZ                 = 74670,
    SPELL_BLEEDING_WOUND        = 74846,
    SPELL_SUMMON_SKARDYN        = 74859,
};

enum Events
{
    EVENT_GROUND_SIEGE = 1,
    EVENT_BLITZ,
    EVENT_BLEEDING_WOUND,
    EVENT_SUMMON_TROGGS,
};

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
        }

        bool _frenzied;

        void Reset()
        {
            _Reset();
            _frenzied = false;
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
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            me->GetMotionMaster()->MoveTargetedHome();
            _frenzied = false;
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

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                    case EVENT_GROUND_SIEGE:
                        Talk(SAY_SIEGE_WARNING);
                        DoCastAOE(SPELL_SUMMON_SIEGE_DUMMY);
                        events.ScheduleEvent(EVENT_GROUND_SIEGE, 23000);
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

                        std::vector<Position> positions;
                        for(uint8 i = 0; i < 4; ++i)
                            positions.push_back(spawnLocations[i]);

                        for(uint8 i = 0; i < 4; ++i)
                        {
                            if(positions.empty())
                                break;

                            std::vector<Position>::iterator pos = positions.begin();
                            std::advance(pos, urand(0, positions.size()-1));

                            if(Creature* trogg = me->SummonCreature((!i) ? NPC_TROGG_MAL : NPC_TROGG_HAB, *pos, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3000))
                                trogg->SetInCombatWithZone();

                            positions.erase(pos);
                        }

                        events.ScheduleEvent(EVENT_SUMMON_TROGGS, 60000);
                        break;
                    }
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
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            _JustDied();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_general_umbrissAI(creature);
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
                }
        }

        void Register()
        {
            OnEffectLaunch += SpellEffectFn(spell_gb_blitz_summon_SpellScript::HandleLaunch, EFFECT_0, SPELL_EFFECT_SUMMON);
        }
    };

    SpellScript *GetSpellScript() const
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

        void HandleScriptEffect(SpellEffIndex /*effIndex*/)
        {
            if (Unit* target = GetHitUnit())
                if (Unit* caster = GetCaster())
                    if (caster->GetTypeId() == TYPEID_UNIT)
                        caster->ToCreature()->AI()->Talk(SAY_BLITZ_WARNING, target->GetGUID());
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_gb_blitz_SpellScript::HandleScriptEffect, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
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

        void HandleLaunch(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
                if (Creature* umbriss = caster->FindNearestCreature(BOSS_GENERAL_UMBRISS, 200.0f, true))
                {
                    umbriss->SetFacingToObject(caster);
                    umbriss->AI()->DoCastAOE(SPELL_GROUND_SIEGE);
                }
        }

        void Register()
        {
            OnEffectLaunch += SpellEffectFn(spell_gb_siege_summon_SpellScript::HandleLaunch, EFFECT_0, SPELL_EFFECT_SUMMON);
        }
    };

    SpellScript *GetSpellScript() const
    {
        return new spell_gb_siege_summon_SpellScript();
    }
};

void AddSC_boss_general_umbriss() 
{
    new boss_general_umbriss();
    new spell_gb_blitz_summon();
    new spell_gb_blitz();
    new spell_gb_siege_summon();
}
