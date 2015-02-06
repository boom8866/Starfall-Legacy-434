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
    // Isiset
    SPELL_SUPERNOVA                     = 74136,
    SPELL_ASTRAL_RAIN                   = 74134,

    // Mirror Images System
    SPELL_MIRROR_IMAGE_1                = 69936,
    SPELL_MIRROR_IMAGE_2                = 69939,
    SPELL_MIRROR_IMAGE_VISUAL           = 69940,
    SPELL_MIRROR_IMAGE_SCRIPT           = 69941,
    SPELL_ASTRAL_SHIFT                  = 74312,
    SPELL_ASTRAL_SHIFT_EXPLOSION        = 74333,
    SPELL_MIRROR_IMAGE_N                = 74263, // Celestial Call
    SPELL_MIRROR_IMAGE_E                = 74262, // Astral Rain
    SPELL_MIRROR_IMAGE_W                = 74261, // Veil of Sky
    SPELL_MIRROR_IMAGE_SCRIPT_2         = 74264,

    SPELL_ASTRAL_SHIFT_EXPLOSION_VISUAL = 74331,
};

enum Events
{
    EVENT_SUPERNOVA = 1,
};

enum Actions
{
    ACTION_SUMMON_MIRROR_IMAGES = 1,
    ACTION_ASTRAL_RAIN_KILLED,
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
        uint8 _shiftCount;

        void Reset()
        {
            _astralRain = true;
            _celestialCall = true;
            _veilOfSky = true;
            _shiftCount = 0;
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
            me->RemoveFlag(UNIT_FIELD_FLAGS, 34375744);
            instance->SetBossState(DATA_ISISET, FAIL);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            _astralRain = true;
            _celestialCall = true;
            _veilOfSky = true;
            _shiftCount = 0;
            events.Reset();
            summons.DespawnAll();
        }

        void JustSummoned(Creature* summon)
        {
            switch(summon->GetEntry())
            {
                case NPC_ASTRAL_SHIFT_DUMMY:
                    summon->AI()->DoCast(SPELL_ASTRAL_SHIFT_EXPLOSION_VISUAL);
                    summons.Summon(summon);
                    break;
                case NPC_CELESTIAL_CALL:
                case NPC_VEIL_OF_SKY:
                case NPC_ASTRAL_RAIN:
                    summon->AI()->DoZoneInCombat();
                    break;
                default:
                    summons.Summon(summon);
                    break;
            }
        }

        void DamageTaken(Unit* /*attacker*/, uint32& damage)
        {
            if (me->HealthBelowPct(66) && _shiftCount == 0)
            {
                DoAction(ACTION_SUMMON_MIRROR_IMAGES);
                _shiftCount++;
            }
            else if (me->HealthBelowPct(33) && _shiftCount == 1)
            {
                DoAction(ACTION_SUMMON_MIRROR_IMAGES);
                _shiftCount++;
            }
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_SUMMON_MIRROR_IMAGES:
                    instance->SendEncounterUnit(ENCOUNTER_FRAME_UPDATE_PRIORITY, me, 1);
                    me->SetFlag(UNIT_FIELD_FLAGS, 34375744);
                    events.Reset();
                    DoCast(SPELL_MIRROR_IMAGE_1);
                    DoCast(SPELL_MIRROR_IMAGE_2);
                    DoCast(SPELL_MIRROR_IMAGE_VISUAL);
                    DoCast(SPELL_MIRROR_IMAGE_SCRIPT);
                    DoCast(SPELL_ASTRAL_SHIFT_EXPLOSION);
                    DoCast(SPELL_ASTRAL_SHIFT);
                    if (_astralRain)
                        DoCast(SPELL_MIRROR_IMAGE_E);
                    if (_celestialCall)
                        DoCast(SPELL_MIRROR_IMAGE_N);
                    if (_veilOfSky)
                        DoCast(SPELL_MIRROR_IMAGE_W);
                    break;
                default:
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim() || !CheckInRoom())
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
