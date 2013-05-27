/* 2011- Dreadii Developement (c)
* Base by TrueBlood
*Script complete : 50%
*Todo:
*
*- add weapon to umbriss
*- find correct death sound ( if there's one :D)
*/

#include "ScriptPCH.h"
#include "grim_batol.h"

enum Yells
{
    SAY_AGGRO,
    SAY_BLITZ,
    SAY_SUMMON,
    SAY_BOMB,
    SAY_SLAY,
    SAY_DEATH,
    SAY_BLITZ_WARNING,
    SAY_SIEGE_WARNING,
};

enum Spells
{
    SPELL_FRENZY            = 74853,
    SPELL_GROUND_SIEGE      = 74634,
    SPELL_BLITZ             = 74670,
    SPELL_BLEEDING_WOUND    = 74846
};

enum Events
{
    EVENT_GROUND_SIEGE      = 1,
    EVENT_BLITZ             = 2,
    EVENT_WOUND             = 3,
    EVENT_SUMMON            = 4,
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
    boss_general_umbriss() : CreatureScript("boss_general_umbriss") {}

    struct boss_general_umbrissAI : public BossAI
    {
        boss_general_umbrissAI(Creature* creature) : BossAI(creature, DATA_GENERAL_UMBRISS)
        {
        }

        void Reset()
        {
            me->RemoveAurasDueToSpell(SPELL_FRENZY);
            _Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {                
            Talk(SAY_AGGRO);

            events.ScheduleEvent(EVENT_GROUND_SIEGE, urand(30000, 35000));
            events.ScheduleEvent(EVENT_BLITZ, urand(22000, 27000));
            events.ScheduleEvent(EVENT_WOUND, urand(15000, 23000));
            events.ScheduleEvent(EVENT_SUMMON, 60000);

            _EnterCombat();
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if(!HealthAbovePct(30) && !me->HasAura(SPELL_FRENZY))
                DoCast(me, SPELL_FRENZY);

            events.Update(diff);
            // _DoAggroPulse(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                case EVENT_GROUND_SIEGE:
                    {
                        Talk(SAY_SIEGE_WARNING);
                        DoCast(SPELL_GROUND_SIEGE);
                        events.ScheduleEvent(EVENT_GROUND_SIEGE, urand(30000, 35000));
                        break;
                    }
                case EVENT_BLITZ:
                    {
                        Talk(SAY_BLITZ);
                        DoCast(SPELL_BLITZ);
                        events.ScheduleEvent(EVENT_BLITZ, urand(22000, 27000));
                        break;
                    }
                case EVENT_WOUND:
                    {
                        DoCastVictim(SPELL_BLEEDING_WOUND);
                        events.ScheduleEvent(EVENT_WOUND, urand(15000, 23000));
                        break;
                    }
                case EVENT_SUMMON:
                    {
                        Talk(SAY_SUMMON);

                        std::vector<Position> positions;
                        for(uint8 i = 0; i < 4; ++i)
                            positions.push_back(spawnLocations[i]);

                        for(uint8 i = 0; i < 4; ++i)
                        {
                            if(positions.empty())
                                break;

                            std::vector<Position>::iterator pos = positions.begin();
                            std::advance(pos, urand(0, positions.size()-1));

                            if(Creature* trogg = me->SummonCreature((!i) ? NPC_TROGG_MAL : NPC_TROGG_HAB, *pos, TEMPSUMMON_CORPSE_DESPAWN))
                                trogg->SetInCombatWithZone();

                            positions.erase(pos);
                        }

                        events.ScheduleEvent(EVENT_SUMMON, 60000);
                        break;
                    }
                }
            }
            DoMeleeAttackIfReady();
        }

        void KilledUnit(Unit* /*victim*/)
        {
            Talk(SAY_SLAY);
        }

        void JustDied(Unit* /*killer*/)
        {
            Talk(SAY_DEATH);
            _JustDied();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_general_umbrissAI(creature);
    }
};

class spell_blitz : public SpellScriptLoader
{
public:
    spell_blitz() : SpellScriptLoader("spell_blitz") { }

    class spell_blitzSpellScript : public SpellScript
    {
        PrepareSpellScript(spell_blitzSpellScript);

        void HandleLaunchTarget(SpellEffIndex /*effIndex*/)
        {
            if(Unit* caster = GetCaster())
                if(Creature* me = caster->ToCreature())
                    if(Player* target = GetHitPlayer())
                        me->AI()->Talk(SAY_BLITZ_WARNING, target->GetGUID());
        }

        void Register()
        {
            OnEffectLaunchTarget += SpellEffectFn(spell_blitzSpellScript::HandleLaunchTarget, EFFECT_0, SPELL_EFFECT_CHARGE_DEST);
        }
    };

    SpellScript *GetSpellScript() const
    {
        return new spell_blitzSpellScript();
    }
};

void AddSC_boss_general_umbriss() 
{
    new boss_general_umbriss();
    new spell_blitz();
}
