#include "ScriptPCH.h"
#include "grim_batol.h"
#include "Vehicle.h"

enum Spells
{
    // Drahga
   SPELL_BURNING_SHADOWBOLT         = 75245,
   SPELL_BURNING_SHADOWBOLT_DUMMY   = 75246,
};

enum Texts
{
    // Drahga
    SAY_INTRO                           = 0,
    SAY_AGGRO                           = 1,
    SAY_ANNOUNCE_INVOCATION_OF_FLAME    = 2,
    SAY_INVOCATION_OF_FLAME             = 3,
    SAY_VALIONA_INTRO                   = 4,
    SAY_SLAY                            = 5,
    SAY_DEATH                           = 6,

    // Valiona
    SAY_VALIONA_AGGRO                   = 0,
    SAY_ANNOUNCE_DEVOURING_FLAMES       = 1,
    SAY_VALIONA_FLEE                    = 2,
};

enum Events
{
    EVENT_BURNING_SHADOWBOLT = 1,
};

enum Actions
{
};

enum Points
{
};

class boss_drahga_shadowburner : public CreatureScript
{
public:
    boss_drahga_shadowburner() : CreatureScript("boss_drahga_shadowburner") { }

    struct boss_drahga_shadowburnerAI : public BossAI
    {
        boss_drahga_shadowburnerAI(Creature* creature) : BossAI(creature, DATA_DRAHGA_SHADOWBURNER)
        {
            _introDone = false;
        }

        Creature* valiona;
        bool _introDone;

        void Reset()
        {
            _Reset();
            _introDone = false;
        }

        void EnterCombat(Unit* /*who*/)
        {
            _EnterCombat();
            Talk(SAY_AGGRO);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            events.ScheduleEvent(EVENT_BURNING_SHADOWBOLT, 3000);
        }

        void JustDied(Unit* /*victim*/)
        {
            _JustDied();
            Talk(SAY_DEATH);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            summons.DespawnAll();
            events.Reset();
            _DespawnAtEvade();
        }

        void KilledUnit(Unit* killed)
        {
            if (killed->GetTypeId() == TYPEID_PLAYER)
                Talk(SAY_SLAY);
        }

        void MovementInform(uint32 type, uint32 id)
        {
            if (type == POINT_MOTION_TYPE)
            {
                switch (id)
                {
                    case 0:
                        break;
                    default:
                        break;
                }
            }
        }

        void DoAction(int32 action)
        {
            switch(action)
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
                    case EVENT_BURNING_SHADOWBOLT:
                        DoCast(SPELL_BURNING_SHADOWBOLT);
                        events.ScheduleEvent(EVENT_BURNING_SHADOWBOLT, 2500);
                        break;
                    default:
                        break;
                }
            }
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_drahga_shadowburnerAI (creature);
    }
};

class npc_gb_valiona : public CreatureScript
{
public:
    npc_gb_valiona() : CreatureScript("npc_gb_valiona") { }

    struct npc_gb_valionaAI : public ScriptedAI
    {
        npc_gb_valionaAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        Unit* dragah;

        void Reset()
        {
        }

        void JustSummoned(Creature* summon)
        {
        }

        void IsSummonedBy(Unit* summoner)
        {
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
                }
            }

            DoMeleeAttackIfReady();
        }

        void DoAction(int32 action)
        {
            switch(action)
            {
                case 0:
                    break;
                default:
                    break;
            }
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_gb_valionaAI (creature);
    }
};

class spell_gb_burning_shadowbolt : public SpellScriptLoader
{
public:
    spell_gb_burning_shadowbolt() : SpellScriptLoader("spell_gb_burning_shadowbolt") { }

    class spell_gb_burning_shadowbolt_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_gb_burning_shadowbolt_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            Trinity::Containers::RandomResizeList(targets, 1);
            if (Unit* target = Trinity::Containers::SelectRandomContainerElement(targets)->ToUnit()) // A bit cheaty but ok for now
                GetCaster()->CastSpell(target, SPELL_BURNING_SHADOWBOLT_DUMMY, true);
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_gb_burning_shadowbolt_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_gb_burning_shadowbolt_SpellScript();
    }
};

void AddSC_boss_drahga_shadowburner()
{
    new boss_drahga_shadowburner();
    new npc_gb_valiona();
    new spell_gb_burning_shadowbolt();
}