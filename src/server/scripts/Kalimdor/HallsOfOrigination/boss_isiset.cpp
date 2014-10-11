/*
    Copyright 2014 - Northstrider
*/

#include "halls_of_origination.h"

enum Texts
{
    SAY_AGGRO               = 0,
    SAY_SLAY                = 1,
    SAY_SUPERNOVA           = 2,
    SAY_ANNOUNCE_SUPERNOVA  = 3,
    SAY_DEATH               = 4,
};

enum Spells
{
    SPELL_SUPERNOVA     = 74136,
    SPELL_ASTRAL_RAIN   = 74134,
};

enum Events
{
    EVENT_SUPERNOVA = 1,
};

enum Actions
{
    ACTION_ASTRAL_RAIN_KILLED = 1,
    ACTION_CELESTIAL_CALL,
    ACTION_VEIL_OF_SKY,
};

class boss_isiset : public CreatureScript
{
public:
    boss_isiset() : CreatureScript("boss_isiset") { }

    struct boss_isisetAI : public BossAI
    {
        boss_isisetAI(Creature* creature) : BossAI(creature, DATA_ISISET)
        {
        }

        bool _astralRain;
        bool _celestialCall;
        bool _veilOfSky;

        void Reset()
        {
            _astralRain = true;
            _celestialCall = true;
            _veilOfSky = true;
        }

        void EnterCombat(Unit* /*who*/)
        {
            _EnterCombat();
            Talk(SAY_AGGRO);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            events.ScheduleEvent(EVENT_SUPERNOVA, 15500);
        }

        void JustDied(Unit* /*who*/)
        {
            Talk(SAY_DEATH);
            _JustDied();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            summons.DespawnAll();
        }

        void KilledUnit(Unit* killed)
        {
            if (killed->GetTypeId() == TYPEID_PLAYER)
                Talk(SAY_SLAY);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            me->GetMotionMaster()->MoveTargetedHome();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            _astralRain = true;
            _celestialCall = true;
            _veilOfSky = true;
            events.Reset();
            summons.DespawnAll();
        }

        void JustSummoned(Creature* summon)
        {
            switch(summon->GetEntry())
            {
                case 0:
                    break;
                default:
                    break;
            }
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
            if (!UpdateVictim())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SUPERNOVA:
                        Talk(SAY_SUPERNOVA);
                        Talk(SAY_ANNOUNCE_SUPERNOVA);
                        DoCast(me, SPELL_SUPERNOVA);
                        break;
                    default:
                        break;
                }
            }
            DoMeleeAttackIfReady();
        }

        uint8 GetDeadMirrorImages()
        {
            uint8 images = 0;
            if (!_celestialCall)
                images++;
            if (!_astralRain)
                images++;
            if (!_veilOfSky)
                images++;

            return images;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_isisetAI(creature);
    }
};

class spell_hoo_supernova : public SpellScriptLoader
{
public:
    spell_hoo_supernova() : SpellScriptLoader("spell_hoo_supernova") { }

    class spell_hoo_supernova_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hoo_supernova_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            std::list<WorldObject*>::iterator it = targets.begin();

            while (it != targets.end())
            {
                if (Unit* caster = GetCaster())
                {
                    WorldObject* unit = *it;

                    if (!unit)
                        continue;

                    if (!unit->isInFront(caster))
                        it = targets.erase(it);
                    else
                        it++;
                }
            }
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_hoo_supernova_SpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_SRC_AREA_ENEMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_hoo_supernova_SpellScript();
    }
};

void AddSC_boss_isiset()
{
    new boss_isiset();
    new spell_hoo_supernova();
}
