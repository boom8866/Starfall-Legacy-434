
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

// Fire Jugglers
enum JugglerDefines
{
    SPELL_JUGGLE_TORCHES    = 102905,

    EVENT_START_JUGGLE      = 1,
    EVENT_STOP_JUGGLE       = 2,
};

class npc_df_fire_juggler : public CreatureScript
{
public:
    npc_df_fire_juggler() : CreatureScript("npc_df_fire_juggler") { }

    struct npc_df_fire_jugglerAI : public ScriptedAI
    {
        npc_df_fire_jugglerAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void Reset()
        {
            events.ScheduleEvent(EVENT_START_JUGGLE, 1);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_START_JUGGLE:
                        DoCastAOE(SPELL_JUGGLE_TORCHES);
                        events.ScheduleEvent(EVENT_STOP_JUGGLE, 30000);
                        break;
                    case EVENT_STOP_JUGGLE:
                        me->RemoveAllAuras();
                        events.ScheduleEvent(EVENT_START_JUGGLE, 30000);
                        break;
                }
            }           
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_df_fire_jugglerAI(creature);
    }
};

enum GnollSpells
{
    SPELL_WHACK_A_GNOLL_UI      = 101612,
    SPELL_WHACK_A_GNOLL_COUNTER = 110230,
    SPELL_GNOLL_SUMMON          = 102036,
    SPELL_BABY_SUMMON           = 102043,
    SPELL_HOGGER_SUMMON         = 102044,
    SPELL_GNOLL_HIT_AURA        = 101996,
    SPELL_WHACK_A_GNOLL_CREDIT  = 101835,
    SPELL_WHACK                 = 102022,
    SPELL_GNOLL_SPAWN_EFFECT    = 102136,
    SPELL_STAY_OUT_GNOLL        = 110966,
};

enum GnollCreatures
{
    NPC_GNOLL_HOLDER    = 54547,
    NPC_GNOLL_BONUS     = 54549,
    NPC_GNOLL           = 54444,
    NPC_GNOLL_BABY      = 54466,
};

enum GnollQuest
{
    QUEST_ITS_HAMMER_TIME   = 29463,
};

class at_whack_a_gnoll : public AreaTriggerScript
{
    public:
        at_whack_a_gnoll() : AreaTriggerScript("at_whack_a_gnoll") { }

        bool OnTrigger(Player* player, AreaTriggerEntry const* /*areaTrigger*/)
        {
            if (!player->HasAura(101612))
                player->CastSpell(player, SPELL_STAY_OUT_GNOLL);
            return true;
        }
};

// 7344 trigger
class spell_darkmoon_deathmatch : public SpellScriptLoader
{
public:
    spell_darkmoon_deathmatch() : SpellScriptLoader("spell_darkmoon_deathmatch") { }

    class spell_darkmoon_deathmatch_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_darkmoon_deathmatch_SpellScript);

        void HandleScriptEffect(SpellEffIndex /*effIndex*/)
        {
            if (Unit* player = GetHitUnit())
                if (player->GetAreaId() != 5877)
                    player->CastSpell(player, 108919);
                else
                    player->CastSpell(player, 108923);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_darkmoon_deathmatch_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_darkmoon_deathmatch_SpellScript();
    }
};

void AddSC_darkmoon_island()
{
    new npc_df_fire_juggler();
    new at_whack_a_gnoll();
    new spell_darkmoon_deathmatch();
}
