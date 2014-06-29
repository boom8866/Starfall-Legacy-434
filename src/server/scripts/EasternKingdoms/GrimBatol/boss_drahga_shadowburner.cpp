#include "ScriptPCH.h"
#include "grim_batol.h"
#include "Vehicle.h"

enum Spells
{
    // Drahgas Spells
    SPELL_BURNING_SHADOWBOLT    = 75245,
    SPELL_BURNING_SHADOWBOLT_H  = 90915,

    SPELL_INVOCATION_OF_FLAME   = 75218,

    SPELL_TWILIGHT_PROTECTION   = 76303,

    // Valionas Spells
    SPELL_VALIONAS_FLAME        = 75321,
    SPELL_SHREDDING_SWIPE       = 75271,
    SPELL_SEEPING_TWILIGHT      = 75318,
    SPELL_SEEPING_TWILIGHT_DMG  = 75274,
    SPELL_DEVOURING_FLAMES_H    = 90950,

    SPELL_TWILIGHT_SHIFT        = 75328,

    // Invoked Flame Spirits Spells
    SPELL_FLAMING_FIXATE        = 82850,
    SPELL_SUPERNOVA             = 75238,
    SPELL_SUPERNOVA_H           = 90972,
};

enum Events
{
    EVENT_BURNING_SHADOWBOLT = 1,
    EVENT_SUMMON_INVOKED_FLAME_SPIRIT,

    EVENT_VALIONAS_FLAME,
    EVENT_SHREDDING_SWIPE,
    EVENT_SEEPING_TWILIGHT,
    EVENT_DEVOURING_FLAMES,

    EVENT_DRAGAH_ENTER_VEHICLE,
    EVENT_VALIONA_ENTER_GROUNDPHASE,
};

enum Actions
{
    ACTION_DRAGAH_CALLS_VALIONA_FOR_HELP = 1,
    ACTION_VALIONA_SHOULD_FLY_AWAY,
    ACTION_DRAGAH_IS_ON_THE_GROUND,
};

enum Points
{
    POINT_VALIONA_FLY_IN_THE_AIR = 1,
    POINT_VALIONA_LAND,
    POINT_VALIONA_FLY_AWAY,
    POINT_VALIONA_IS_AWAY,

    POINT_DRAHGA_GO_TO_THE_LAVA,
};

enum DrahgaYells
{
    SAY_AGGRO,
    SAY_WARNING,
    SAY_SPIRIT,
    SAY_VALIONA,
    SAY_SLAY,
    SAY_INTRO,
    SAY_DEATH,
};

enum ValionaYells
{
    SAY_HELP,
    SAY_FLEE,
    SAY_FLAMEBREATH,
};

class boss_drahga_shadowburner : public CreatureScript
{
public:
    boss_drahga_shadowburner() : CreatureScript("boss_drahga_shadowburner") { }

    struct boss_drahga_shadowburnerAI : public BossAI
    {
        boss_drahga_shadowburnerAI(Creature* creature) : BossAI(creature, DATA_DRAHGA_SHADOWBURNER)
        {
        }

        Creature* valiona;
        bool introDone;

        void Reset()
        {
            _Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            _EnterCombat();
            Talk(SAY_AGGRO);
        }

        void JustDied(Unit* /*victim*/)
        {
            Talk(SAY_DEATH);
            _JustDied();
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
                    case 0:
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

void AddSC_boss_drahga_shadowburner()
{
    new boss_drahga_shadowburner();
    new npc_gb_valiona();
}