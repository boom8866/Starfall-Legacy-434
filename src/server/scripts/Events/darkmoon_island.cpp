
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

class spell_df_heal_injured_carnie : public SpellScriptLoader
{
public:
    spell_df_heal_injured_carnie() : SpellScriptLoader("spell_df_heal_injured_carnie")
    {
    }

    enum npcId
    {
        NPC_INJURED_CARNIE     = 54518
    };

    class spell_df_heal_injured_carnie_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_df_heal_injured_carnie_SpellScript);

        SpellCastResult CheckCast()
        {
            if (Unit* caster = GetCaster())
            {
                if (Unit* target = GetExplTargetUnit())
                {
                    if (target->ToCreature())
                    {
                        if (target->GetEntry() == NPC_INJURED_CARNIE && target->HasFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP))
                            return SPELL_CAST_OK;
                    }
                }
            }
            return SPELL_FAILED_BAD_TARGETS;
        }

        void HandleAfterHeal(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
            {
                if (Unit* target = GetHitUnit())
                {
                    target->RemoveFlag(UNIT_FIELD_BYTES_1, 8);
                    target->SetFacingToObject(caster);
                    if (target->ToCreature())
                    {
                        target->ToCreature()->AI()->TalkWithDelay(1500, 0, caster->GetGUID());
                        target->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                        target->ToCreature()->DespawnOrUnsummon(6000);
                    }
                    target->SetHealth(target->GetMaxHealth());
                    caster->ToPlayer()->KilledMonsterCredit(NPC_INJURED_CARNIE);
                }
            }
        }

        void Register()
        {
            OnCheckCast += SpellCheckCastFn(spell_df_heal_injured_carnie_SpellScript::CheckCast);
            OnEffectHitTarget += SpellEffectFn(spell_df_heal_injured_carnie_SpellScript::HandleAfterHeal, EFFECT_0, SPELL_EFFECT_HEAL_PCT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_df_heal_injured_carnie_SpellScript();
    }
};

class npc_df_injured_carnie : public CreatureScript
{
public:
    npc_df_injured_carnie() : CreatureScript("npc_df_injured_carnie")
    {
    }


    struct npc_df_injured_carnieAI : public ScriptedAI
    {
        npc_df_injured_carnieAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        void InitializeAI()
        {
            me->SetHealth(me->GetMaxHealth() / urand(3, 4));
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_df_injured_carnieAI(creature);
    }
};

class spell_df_put_up_darkmoon_banner : public SpellScriptLoader
{
public:
    spell_df_put_up_darkmoon_banner() : SpellScriptLoader("spell_df_put_up_darkmoon_banner")
    {
    }

    enum npcId
    {
        NPC_LOOSE_STONES = 54545
    };

    enum spellId
    {
        SPELL_SUMMON_BANNER = 102006
    };

    enum goId
    {
        GO_DARKMOON_BANNER = 179965
    };

    class spell_df_put_up_darkmoon_banner_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_df_put_up_darkmoon_banner_SpellScript);

        void HandleBanner()
        {
            if (Unit* caster = GetCaster())
            {
                if (Creature* looseStones = caster->FindNearestCreature(NPC_LOOSE_STONES, 5.0f))
                {
                    GameObject* banner = caster->FindNearestGameObject(GO_DARKMOON_BANNER, 8.0f);
                    if (!banner)
                    {
                        looseStones->CastSpell(looseStones, SPELL_SUMMON_BANNER, true);
                        if (caster->GetTypeId() == TYPEID_PLAYER)
                            caster->ToPlayer()->KilledMonsterCredit(NPC_LOOSE_STONES);
                    }
                }
            }
        }

        void Register()
        {
            AfterCast += SpellCastFn(spell_df_put_up_darkmoon_banner_SpellScript::HandleBanner);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_df_put_up_darkmoon_banner_SpellScript();
    }
};

class spell_repair_damaged_tonk : public SpellScriptLoader
{
public:
    spell_repair_damaged_tonk() : SpellScriptLoader("spell_repair_damaged_tonk")
    {
    }

    enum npcId
    {
        NPC_DAMAGED_TONK    = 54504
    };

    class spell_repair_damaged_tonk_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_repair_damaged_tonk_SpellScript);

        SpellCastResult CheckCast()
        {
            if (Unit* caster = GetCaster())
            {
                if (Unit* target = GetExplTargetUnit())
                {
                    if (target->ToCreature())
                    {
                        if (target->GetEntry() == NPC_DAMAGED_TONK && target->HasFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH))
                            return SPELL_CAST_OK;
                    }
                }
            }
            return SPELL_FAILED_BAD_TARGETS;
        }

        void HandleAfterHeal(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
            {
                if (Unit* target = GetHitUnit())
                {
                    target->RemoveFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
                    target->RemoveFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_DEAD);
                    target->RemoveFlag(UNIT_FIELD_FLAGS, 537133056);
                    if (target->ToCreature())
                    {
                        target->RemoveFlag(UNIT_NPC_FLAGS, UNIT_FLAG2_FEIGN_DEATH);
                        target->ToCreature()->DespawnOrUnsummon(10000);
                        target->SetWalk(true);
                        target->GetMotionMaster()->MovePoint(0, target->GetPositionX()+urand(1,3), target->GetPositionY()+urand(1,3), target->GetPositionZ());
                    }
                    target->SetHealth(target->GetMaxHealth());
                    caster->ToPlayer()->KilledMonsterCredit(NPC_DAMAGED_TONK);
                }
            }
        }

        void Register()
        {
            OnCheckCast += SpellCheckCastFn(spell_repair_damaged_tonk_SpellScript::CheckCast);
            OnEffectHitTarget += SpellEffectFn(spell_repair_damaged_tonk_SpellScript::HandleAfterHeal, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_repair_damaged_tonk_SpellScript();
    }
};

void AddSC_darkmoon_island()
{
    new npc_df_fire_juggler();
    new at_whack_a_gnoll();
    new spell_darkmoon_deathmatch();
    new spell_df_heal_injured_carnie();
    new npc_df_injured_carnie();
    new spell_df_put_up_darkmoon_banner();
    new spell_repair_damaged_tonk();
}
