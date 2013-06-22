
#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "PassiveAI.h"
#include "SpellScript.h"
#include "MoveSplineInit.h"
#include "Cell.h"
#include "CellImpl.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "firelands.h"

enum Texts
{
    // Shannox
    SAY_INTRO           = 0,
    SAY_AGGRO           = 1,
    SAY_SLAY            = 2,
    SAY_HURL_SPEAR      = 3,

    // Shannox Controller
    SAY_HORN_1          = 0,
    SAY_HORN_2          = 1,
};

enum Spells
{
    // Shannox
    SPELL_THROW_CRYSTAL_TRAP    = 99836,
    SPELL_THROW_IMMOLATION_TRAP = 99839,
    SPELL_ARCING_SLASH          = 99931,
    SPELL_HURL_SPEAR_SUMMON     = 99978,
    SPELL_HURL_SPEAR_DUMMY      = 100031,
    SPELL_HURL_SPEAR_THROW      = 100002,
    SPELL_MAGMA_FLARE           = 100495,
    SPELL_MAGMA_RUPTURE         = 99841,

    // Shannox Spear
    SPELL_SPEAR_TARGET          = 99988,
    SPELL_SPEAR_VISUAL          = 100005,

    // Riplimb
    SPELL_WARY                  = 100167,

    // Crystal Prison Trap
    SPELL_PRISON_EFFECT         = 99837,

    // Immolation Trap
    SPELL_IMMOLATION_EFFECT     = 99838,
};

enum Events
{
    EVENT_TALK_INTRO = 1,
    EVENT_THROW_CRYSTAL_TRAP,
    EVENT_THROW_IMMOLATION_TRAP,
    EVENT_ARCING_SLASH,
    EVENT_HURL_SPEAR,
};

enum Actions
{
    ACTION_TRASH_KILLED     = 1,
};

enum Phases
{
    PHASE_INTRO     = 1,
    PHASE_COMBAT    = 2,
};

enum Points
{
    POINT_INTRO     = 1,
};

Position const ShannoxSpawnPos = {14.40601f, -64.01636f, 55.22266f, 4.469716f};
Position const RagefaceSpawnPos = {29.51563f, -54.70139f, 54.58546f, 4.469716f};
Position const RiplimpSpawnPos = {29.15799f,-73.91146f, 54.78453f, 4.469716f};

Position const ShannoxMovePos = {-55.36111f, -58.91667f, 57.69878f};

class boss_shannox : public CreatureScript
{
public:
    boss_shannox() : CreatureScript("boss_shannox") { }

    struct boss_shannoxAI : public BossAI
    {
        boss_shannoxAI(Creature* creature) : BossAI(creature, DATA_SHANNOX)
        {
            _riplimbSlain = false;
        }

        Creature* riplimb;  // Define them as public creature to have a full controll everywherre
        Creature* rageface;

        bool _riplimbSlain; // needed later for heroic encounter

        void IsSummonedBy(Unit* /*summoner*/)
        {
            events.SetPhase(PHASE_INTRO);

            if (riplimb = me->SummonCreature(NPC_RIPLIMB, RiplimpSpawnPos, TEMPSUMMON_MANUAL_DESPAWN))
            {
                riplimb->GetMotionMaster()->MoveFollow(me, 5.0f, 90.0f);
                riplimb->SetReactState(REACT_PASSIVE);
            }
            if (rageface = me->SummonCreature(NPC_RAGEFACE, RagefaceSpawnPos, TEMPSUMMON_MANUAL_DESPAWN))
            {
                rageface->GetMotionMaster()->MoveFollow(me, 5.0f, 270.0f);
                rageface->SetReactState(REACT_PASSIVE);
            }

            if (GameObject* door = me->FindNearestGameObject(GO_BALEROC_DOOR, 200.0f))
                door->SetGoState(GO_STATE_ACTIVE);

            me->GetMotionMaster()->MovePoint(POINT_INTRO, ShannoxMovePos.GetPositionX(), ShannoxMovePos.GetPositionY(), ShannoxMovePos.GetPositionZ(), false);
        }

        void JustSummoned(Creature* summon)
        {
            switch (summon->GetEntry())
            {
                case NPC_HURL_SPEAR_TARGET:
                    DoCast(summon, SPELL_HURL_SPEAR_THROW);
                    summon->AddAura(SPELL_SPEAR_TARGET, summon);
                    break;
                default:
                    break;
            }
        }

        void Reset()
        {
            events.Reset();
            instance->SetBossState(DATA_SHANNOX, NOT_STARTED);
        }

        void EnterCombat(Unit* /*who*/)
        {
            _EnterCombat();
            Talk(SAY_AGGRO);
            if (Unit* victim = me->getVictim())
            {
                riplimb->Attack(victim, true);
                rageface->Attack(victim, true);
                riplimb->GetMotionMaster()->MoveChase(victim);
                rageface->GetMotionMaster()->MoveChase(victim);
            }
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, riplimb);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, rageface);
            events.SetPhase(PHASE_COMBAT);
            events.ScheduleEvent(EVENT_THROW_CRYSTAL_TRAP, 9950, 0, PHASE_COMBAT);
            events.ScheduleEvent(EVENT_THROW_IMMOLATION_TRAP, 16500, 0, PHASE_COMBAT);
            events.ScheduleEvent(EVENT_ARCING_SLASH, 6900, 0, PHASE_COMBAT);
            events.ScheduleEvent(EVENT_HURL_SPEAR, 23500, 0, PHASE_COMBAT);
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_INTRO:
                    events.ScheduleEvent(EVENT_TALK_INTRO, 100, 0, PHASE_INTRO);
                    break;
                default:
                    break;
            }
        }

        void KilledUnit(Unit* killed) 
        {
            if (killed->GetTypeId() == TYPEID_PLAYER)
                Talk(SAY_SLAY);
        }

        void JustDied(Unit* /*Killer*/)
        {
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, riplimb);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, rageface);
            _JustDied();
        }

        void EnterEvadeMode()
        {
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, riplimb);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, rageface);
            Reset();
        }

        void UpdateAI(uint32 diff)
        {
            if (!(events.IsInPhase(PHASE_INTRO)))
                if (!UpdateVictim())
                    return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_TALK_INTRO:
                        TalkToFar(SAY_INTRO, TEXT_RANGE_MAP);
                        if (GameObject* door = me->FindNearestGameObject(GO_BALEROC_DOOR, 200.0f))
                            door->SetGoState(GO_STATE_READY);
                        break;
                    case EVENT_THROW_CRYSTAL_TRAP:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true))
                            DoCast(target, SPELL_THROW_CRYSTAL_TRAP);
                        events.ScheduleEvent(EVENT_THROW_CRYSTAL_TRAP, 26500, 0, PHASE_COMBAT);
                        break;
                    case EVENT_THROW_IMMOLATION_TRAP:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true))
                            DoCast(target, SPELL_THROW_IMMOLATION_TRAP);
                        events.ScheduleEvent(EVENT_THROW_IMMOLATION_TRAP, 9700, 0, PHASE_COMBAT);
                        break;
                    case EVENT_ARCING_SLASH:
                        DoCastVictim(SPELL_ARCING_SLASH);
                        events.ScheduleEvent(EVENT_ARCING_SLASH, 12000, 0, PHASE_COMBAT);
                        break;
                    case EVENT_HURL_SPEAR:
                        DoCast(riplimb, SPELL_HURL_SPEAR_SUMMON);
                        DoCastAOE(SPELL_HURL_SPEAR_DUMMY);
                        Talk(SAY_HURL_SPEAR);
                        events.ScheduleEvent(EVENT_HURL_SPEAR, 53000, 0, PHASE_COMBAT);
                        break;
                    default:
                        break;
                }
            }
            DoMeleeAttackIfReady();
        }
    };
    CreatureAI* GetAI(Creature* Creature) const
    {
        return new boss_shannoxAI (Creature);
    }
};

class npc_fl_shannox_controller : public CreatureScript
{
    public:
        npc_fl_shannox_controller() :  CreatureScript("npc_fl_shannox_controller") { }

        struct npc_fl_shannox_controllerAI : public ScriptedAI
        {
            npc_fl_shannox_controllerAI(Creature* creature) : ScriptedAI(creature)
            {
                instance = me->GetInstanceScript();
                _shannoxSummoned = false;
                _trashKilled = 0;
                me->setActive(true);
            }

            InstanceScript* instance;
            bool _shannoxSummoned;
            uint8 _trashKilled;

            void Reset()
            {
                me->setActive(true);
            }

            void UpdateAI(uint32 diff)
            {
            }

            void DoAction(int32 action)
            {
                switch (action)
                {
                    case ACTION_TRASH_KILLED:
                        _trashKilled++;
                        if (_trashKilled == 5)
                            TalkToFar(SAY_HORN_1, TEXT_RANGE_MAP);
                        else if (_trashKilled == 10)
                            TalkToFar(SAY_HORN_2, TEXT_RANGE_MAP);
                        else if (_trashKilled == 15 && !_shannoxSummoned)
                            if (Creature* shannox = me->SummonCreature(BOSS_SHANNOX, ShannoxSpawnPos, TEMPSUMMON_MANUAL_DESPAWN))
                                _shannoxSummoned = true;
                        break;
                    default:
                        break;
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_fl_shannox_controllerAI(creature);
        }
};

class spell_fl_hurl_spear : public SpellScriptLoader
{
public:
    spell_fl_hurl_spear() : SpellScriptLoader("spell_fl_hurl_spear") { }

    class spell_fl_hurl_spear_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_fl_hurl_spear_SpellScript);

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            if (Unit* target = GetHitUnit())
            {
                target->CastSpell(target, SPELL_MAGMA_FLARE);
			    for (float r = 0; r <= 30; r = r + 10)
                {
				    for (float x = 0; x <= r * 2; x = x + 2)
				    {
					    target->CastSpell(target->GetPositionX()+ cos(x)*r, target->GetPositionY()+ sin(x)*r, target->GetPositionZ(), SPELL_MAGMA_RUPTURE, true);
					    target->CastSpell(target->GetPositionX()-cos(x)*r, target->GetPositionY()-sin(x)*r, target->GetPositionZ(), SPELL_MAGMA_RUPTURE, true);
				    }
                }
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_fl_hurl_spear_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_fl_hurl_spear_SpellScript();
    }
};

void AddSC_boss_shannox()
{
    new npc_fl_shannox_controller();
    new boss_shannox();
    new spell_fl_hurl_spear();
}