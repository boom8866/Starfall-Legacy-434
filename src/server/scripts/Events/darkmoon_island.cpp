
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
#include "AchievementMgr.h"

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
            if (!player->HasAura(101612) && !player->isGameMaster())
                player->CastSpell(player, SPELL_STAY_OUT_GNOLL, true);
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

class spell_df_summon_gnoll_aura : public SpellScriptLoader
{
public:
    spell_df_summon_gnoll_aura() : SpellScriptLoader("spell_df_summon_gnoll_aura")
    {
    }

    enum npcId
    {
        NPC_GNOLL_BARREL    = 54546,
        NPC_GNOLL_FIRST     = 54444,
        NPC_GNOLL_SECOND    = 54466,
        NPC_GNOLL_THIRD     = 54549
    };

    class spell_df_summon_gnoll_aura_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_df_summon_gnoll_aura_AuraScript);

        void OnTick(AuraEffect const* aurEff)
        {
            if (Unit* caster = GetCaster())
            {
                std::list<Creature*> creatures;
                GetCreatureListWithEntryInGrid(creatures, caster, NPC_GNOLL_BARREL, 80.0f);
                if (!creatures.empty())
                {
                    for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                    {
                        Creature* first = (*iter)->FindNearestCreature(NPC_GNOLL_FIRST, 5.0f, true);
                        Creature* second = (*iter)->FindNearestCreature(NPC_GNOLL_SECOND, 5.0f, true);
                        Creature* third = (*iter)->FindNearestCreature(NPC_GNOLL_THIRD, 5.0f, true);
                        if (!first && !second && !third)
                        {
                            if (roll_chance_f(8.0f))
                            {
                                caster->CastSpell((*iter), SPELL_GNOLL_SUMMON, true);
                                (*iter)->CastSpell((*iter), SPELL_GNOLL_SPAWN_EFFECT, true);
                            }
                            if (roll_chance_f(8.0f))
                            {
                                caster->CastSpell((*iter), SPELL_BABY_SUMMON, true);
                                (*iter)->CastSpell((*iter), SPELL_GNOLL_SPAWN_EFFECT, true);
                            }
                            if (roll_chance_f(8.0f))
                            {
                                caster->CastSpell((*iter), SPELL_HOGGER_SUMMON, true);
                                (*iter)->CastSpell((*iter), SPELL_GNOLL_SPAWN_EFFECT, true);
                            }
                        }
                    }
                }
            }
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_df_summon_gnoll_aura_AuraScript::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_df_summon_gnoll_aura_AuraScript();
    }
};

class spell_df_whack_gnoll : public SpellScriptLoader
{
public:
    spell_df_whack_gnoll() : SpellScriptLoader("spell_df_whack_gnoll")
    {
    }

    enum npcId
    {
        NPC_GNOLL_FIRST     = 54444,
        NPC_GNOLL_SECOND    = 54466,
        NPC_GNOLL_THIRD     = 54549
    };

    enum creditID
    {
        QUEST_CREDIT_GNOLL  = 54505
    };

    class spell_df_whack_gnoll_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_df_whack_gnoll_SpellScript);

        void KillGnoll()
        {
            if (Unit* caster = GetCaster())
            {
                if (caster->GetTypeId() != TYPEID_PLAYER)
                    return;

                Creature* first = caster->FindNearestCreature(NPC_GNOLL_FIRST, 2.0f, true);
                Creature* second = caster->FindNearestCreature(NPC_GNOLL_SECOND, 2.0f, true);
                Creature* third = caster->FindNearestCreature(NPC_GNOLL_THIRD, 2.0f, true);
                if (first)
                {
                    caster->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_GNOLL);
                    caster->Kill(first, false);
                    caster->EnergizeBySpell(caster, GetSpellInfo()->Id, 1, POWER_ALTERNATE_POWER);
                }
                if (second)
                {
                    caster->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_GNOLL);
                    caster->Kill(second, false);
                    caster->EnergizeBySpell(caster, GetSpellInfo()->Id, 1, POWER_ALTERNATE_POWER);
                }
                if (third)
                {
                    caster->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_GNOLL);
                    caster->Kill(third, false);
                    caster->EnergizeBySpell(caster, GetSpellInfo()->Id, 1, POWER_ALTERNATE_POWER);
                }
            }
        }

        void Register()
        {
            AfterCast += SpellCastFn(spell_df_whack_gnoll_SpellScript::KillGnoll);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_df_whack_gnoll_SpellScript();
    }
};

class spell_df_cannon_preparation : public SpellScriptLoader
{
public:
    spell_df_cannon_preparation() : SpellScriptLoader("spell_df_cannon_preparation")
    {
    }

    enum spellId
    {
        SPELL_CANNON_TELEPORT   = 102113,
        SPELL_FIRE_CANNON       = 102115,
        SPELL_MAGIC_WINGS       = 102116,
        SPELL_CANNON_BLAST      = 102121
    };

    class spell_df_cannon_preparation_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_df_cannon_preparation_AuraScript);

        void OnApplyEffect(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* target = GetTarget())
            {
                if (target->GetTypeId() == TYPEID_PLAYER)
                {
                    target->Dismount();
                    target->AddUnitMovementFlag(MOVEMENTFLAG_FLYING);
                    target->SetControlled(true, UNIT_STATE_ROOT);
                    target->CastSpell(target, SPELL_CANNON_TELEPORT, true);
                    target->CastSpell(target, SPELL_CANNON_BLAST, true);
                }
            }
        }

        void OnRemoveEffect(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* target = GetTarget())
            {
                if (target->GetTypeId() == TYPEID_PLAYER)
                {
                    target->RemoveUnitMovementFlag(MOVEMENTFLAG_FLYING);
                    target->CastSpell(target, SPELL_FIRE_CANNON, true);
                    target->CastSpell(target, SPELL_MAGIC_WINGS, true);
                    target->SetControlled(false, UNIT_STATE_ROOT);
                    target->GetMotionMaster()->MovementExpired(false);
                    target->GetMotionMaster()->MoveJump(-4479.46f, 6221.82f, 0.0f, 75.0f, 35.0f, 0);
                }
            }
        }

        void Register()
        {
            OnEffectApply += AuraEffectApplyFn(spell_df_cannon_preparation_AuraScript::OnApplyEffect, EFFECT_2, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
            OnEffectRemove += AuraEffectRemoveFn(spell_df_cannon_preparation_AuraScript::OnRemoveEffect, EFFECT_2, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_df_cannon_preparation_AuraScript();
    }
};

class spell_df_magic_wings : public SpellScriptLoader
{
public:
    spell_df_magic_wings() : SpellScriptLoader("spell_df_magic_wings")
    {
    }

    enum creditId
    {
        QUEST_CREDIT_ACCRUED    = 54224
    };

    enum npcId
    {
        NPC_CANNON_TARGET   = 33068
    };

    enum achieId
    {
        ACHIE_BULLSEYE  = 6021
    };

    class eventCreditQuest : public BasicEvent
    {
    public:
        explicit eventCreditQuest(Player* player) : player(player)
        {
        }

        bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
        {
            if (player && player->IsInWorld())
            {
                if (Creature* cannonTarget = player->FindNearestCreature(NPC_CANNON_TARGET, 15.0f, true))
                {
                    for (int i = 0; i < 5; i++)
                        player->KilledMonsterCredit(QUEST_CREDIT_ACCRUED);

                    if (AchievementEntry const* bullseye = sAchievementMgr->GetAchievement(ACHIE_BULLSEYE))
                        player->CompletedAchievement(bullseye);
                }
            }
            return true;
        }

    private:
        Player* player;
    };

    class spell_df_magic_wings_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_df_magic_wings_AuraScript);

        void OnRemoveEffect(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* target = GetTarget())
            {
                if (target->GetTypeId() == TYPEID_PLAYER)
                {
                    target->GetMotionMaster()->MovementExpired(false);
                    target->ToPlayer()->m_Events.AddEvent(new eventCreditQuest(target->ToPlayer()), (target->ToPlayer())->m_Events.CalculateTime(1500));
                }
            }
        }

        void Register()
        {
            OnEffectRemove += AuraEffectRemoveFn(spell_df_magic_wings_AuraScript::OnRemoveEffect, EFFECT_1, SPELL_AURA_FEATHER_FALL, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_df_magic_wings_AuraScript();
    }
};

class npc_df_shoot_target_controller : public CreatureScript
{
public:
    npc_df_shoot_target_controller() : CreatureScript("npc_df_shoot_target_controller")
    {
    }

    enum eventId
    {
        EVENT_ADD_TARGETING     = 1
    };

    enum spellId
    {
        SPELL_DARKMOON_TARGET   = 43313
    };

    enum npcId
    {
        NPC_TARGET_BUNNY    = 24171
    };

    enum targetGUID
    {
        TARGET_FIRST    = 8891,
        TARGET_SECOND   = 8892,
        TARGET_THIRD    = 8889
    };

    struct npc_df_shoot_target_controllerAI : public ScriptedAI
    {
        npc_df_shoot_target_controllerAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void Reset()
        {
            events.ScheduleEvent(EVENT_ADD_TARGETING, 1);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_ADD_TARGETING:
                    {
                        targetSelected = urand(1, 3);

                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_TARGET_BUNNY, 20.0f);
                        if (!creatures.empty())
                        {
                            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                            {
                                switch (targetSelected)
                                {
                                    case 1:
                                    {
                                        if ((*iter)->GetGUIDLow() == TARGET_FIRST)
                                        {
                                            (*iter)->CastSpell((*iter), SPELL_DARKMOON_TARGET, true);
                                            events.RescheduleEvent(EVENT_ADD_TARGETING, 6000);
                                        }
                                        break;
                                    }
                                    case 2:
                                    {
                                        if ((*iter)->GetGUIDLow() == TARGET_SECOND)
                                        {
                                            (*iter)->CastSpell((*iter), SPELL_DARKMOON_TARGET, true);
                                            events.RescheduleEvent(EVENT_ADD_TARGETING, 6000);
                                        }
                                        break;
                                    }
                                    case 3:
                                    {
                                        if ((*iter)->GetGUIDLow() == TARGET_THIRD)
                                        {
                                            (*iter)->CastSpell((*iter), SPELL_DARKMOON_TARGET, true);
                                            events.RescheduleEvent(EVENT_ADD_TARGETING, 6000);
                                        }
                                        break;
                                    }
                                    default:
                                        break;
                                }
                            }
                        }
                        break;
                    }
                    default:
                        break;
                }
            }
        }

        uint8 targetSelected;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_df_shoot_target_controllerAI(creature);
    }
};

class npc_df_darkmoon_target_bunny : public CreatureScript
{
public:
    npc_df_darkmoon_target_bunny() : CreatureScript("npc_df_darkmoon_target_bunny")
    {
    }

    enum spellId
    {
        SPELL_DARKMOON_SHOOT    = 101872,
        SPELL_DARKMOON_TARGET   = 43313,
        SPELL_DARKMOON_HIT      = 43300,
        SPELL_QUICKSHOT         = 101010
    };

    enum achievementId
    {
        ACHIEVEMENT_QUICK_SHOT  = 6022
    };

    struct npc_df_darkmoon_target_bunnyAI : public ScriptedAI
    {
        npc_df_darkmoon_target_bunnyAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            switch (spell->Id)
            {
                case SPELL_DARKMOON_SHOOT:
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        if (me->HasAura(SPELL_DARKMOON_TARGET))
                            caster->CastSpell(caster, SPELL_DARKMOON_HIT, true);

                        // Bonus shot + achievement
                        if (me->HasAura(SPELL_QUICKSHOT))
                        {
                            Talk(0, caster->GetGUID());
                            if (AchievementEntry const* quickShot = sAchievementMgr->GetAchievement(ACHIEVEMENT_QUICK_SHOT))
                                caster->ToPlayer()->CompletedAchievement(quickShot);
                            caster->CastSpell(caster, SPELL_DARKMOON_HIT, true);
                        }
                    }
                    break;
                }
                default:
                    break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_df_darkmoon_target_bunnyAI(creature);
    }
};

class spell_df_ring_toss : public SpellScriptLoader
{
public:
    spell_df_ring_toss() : SpellScriptLoader("spell_df_ring_toss")
    {
    }

    enum npcId
    {
        NPC_DUBENKO         = 54490,
        NPC_JESSICA_ROGERS  = 54485
    };

    enum spellId
    {
        SPELL_RINGS_LANDED  = 101807,
        SPELL_RING_FIRST    = 101734,
        SPELL_RING_SECOND   = 101736,
        SPELL_RING_THIRD    = 101738,
        SPELL_RING_TOSSED   = 101697
    };

    class spell_df_ring_toss_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_df_ring_toss_SpellScript);

        SpellCastResult CheckCast()
        {
            if (Unit* caster = GetCaster())
            {
                if (Creature* jessicaRogers = caster->FindNearestCreature(NPC_JESSICA_ROGERS, 1.5f, true))
                    return SPELL_CAST_OK;
            }
            return SPELL_FAILED_NOT_HERE;
        }

        void HandleLaunch(SpellEffIndex /*effIndex*/)
        {
            if (Unit* caster = GetCaster())
            {
                if (caster->GetTypeId() == TYPEID_PLAYER)
                {
                    if (WorldLocation const* const position = GetExplTargetDest())
                    {
                        if (!caster->ToPlayer()->HasSpellCooldown(SPELL_RING_TOSSED))
                        {
                            caster->CastSpell(position->GetPositionX(), position->GetPositionY(), position->GetPositionZ(), SPELL_RING_TOSSED, false);
                            caster->ToPlayer()->AddSpellCooldown(SPELL_RING_TOSSED, 0, time(NULL) + 1);
                        }
                        return;
                    }
                }
            }
        }

        void Register()
        {
            OnCheckCast += SpellCheckCastFn(spell_df_ring_toss_SpellScript::CheckCast);
            OnEffectHitTarget += SpellEffectFn(spell_df_ring_toss_SpellScript::HandleLaunch, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_df_ring_toss_SpellScript();
    }
};

class spell_df_ring_powerbar : public SpellScriptLoader
{
public:
    spell_df_ring_powerbar() : SpellScriptLoader("spell_df_ring_powerbar")
    {
    }

    class spell_df_ring_powerbar_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_df_ring_powerbar_AuraScript);

        void OnApplyEffect(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* target = GetTarget())
            {
                if (target->GetTypeId() == TYPEID_PLAYER)
                {
                    target->SetMaxPower(POWER_ALTERNATE_POWER, 10);
                    target->SetPower(POWER_ALTERNATE_POWER, 10);
                }
            }
        }

        void OnRemoveEffect(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* target = GetTarget())
            {
                if (target->GetTypeId() == TYPEID_PLAYER)
                {
                    target->SetMaxPower(POWER_ALTERNATE_POWER, 0);
                    target->SetPower(POWER_ALTERNATE_POWER, 0);
                }
            }
        }

        void Register()
        {
            OnEffectApply += AuraEffectApplyFn(spell_df_ring_powerbar_AuraScript::OnApplyEffect, EFFECT_1, SPELL_AURA_ENABLE_ALT_POWER, AURA_EFFECT_HANDLE_REAL);
            OnEffectRemove += AuraEffectRemoveFn(spell_df_ring_powerbar_AuraScript::OnRemoveEffect, EFFECT_1, SPELL_AURA_ENABLE_ALT_POWER, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_df_ring_powerbar_AuraScript();
    }
};

class npc_df_dubenko : public CreatureScript
{
public:
    npc_df_dubenko() : CreatureScript("npc_df_dubenko")
    {
    }

    struct npc_df_dubenkoAI : public ScriptedAI
    {
        npc_df_dubenkoAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        enum spellId
        {
            SPELL_RINGS_LANDED          = 101807,
            SPELL_RING_FIRST            = 101734,
            SPELL_RING_SECOND           = 101736,
            SPELL_RING_THIRD            = 101738,
            SPELL_RING_TOSSED           = 101697,
            SPELL_RING_TOSSED_GROUND    = 101700
        };

        enum eventId
        {
            EVENT_CHECK_RING    = 1
        };

        enum goId
        {
            GO_RING_TOSSED  = 209269
        };

        void Reset()
        {
            events.ScheduleEvent(EVENT_CHECK_RING, 1);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CHECK_RING:
                    {
                        if (GameObject* ring = me->FindNearestGameObject(GO_RING_TOSSED, 1.0f))
                        {
                            if (Unit* owner = ring->GetOwner())
                            {
                                owner->CastSpell(owner, SPELL_RINGS_LANDED, true);
                                if (!me->HasAura(SPELL_RING_FIRST) && !me->HasAura(SPELL_RING_SECOND) && !me->HasAura(SPELL_RING_THIRD))
                                {
                                    me->CastSpell(me, SPELL_RING_FIRST, true);
                                    events.RescheduleEvent(EVENT_CHECK_RING, 500);
                                    ring->Delete();
                                    break;
                                }
                                if (me->HasAura(SPELL_RING_FIRST) && !me->HasAura(SPELL_RING_SECOND))
                                {
                                    me->CastSpell(me, SPELL_RING_SECOND, true);
                                    events.RescheduleEvent(EVENT_CHECK_RING, 500);
                                    ring->Delete();
                                    break;
                                }
                                if (me->HasAura(SPELL_RING_SECOND) && !me->HasAura(SPELL_RING_THIRD))
                                {
                                    me->CastSpell(me, SPELL_RING_THIRD, true);
                                    events.RescheduleEvent(EVENT_CHECK_RING, 500);
                                    ring->Delete();
                                    break;
                                }
                            }
                        }
                        events.RescheduleEvent(EVENT_CHECK_RING, 500);
                        break;
                    }
                    default:
                        break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_df_dubenkoAI(creature);
    }
};

class at_target_turtle : public AreaTriggerScript
{
public:
    at_target_turtle() : AreaTriggerScript("at_target_turtle")
    {
    }

    enum spellId
    {
        SPELL_STAY_OUT_TURTLE   = 109972
    };

    bool OnTrigger(Player* player, AreaTriggerEntry const* /*areaTrigger*/)
    {
        if (!player->isGameMaster())
            player->CastSpell(player, SPELL_STAY_OUT_TURTLE, true);
        return true;
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
    new spell_df_summon_gnoll_aura();
    new spell_df_whack_gnoll();
    new spell_df_cannon_preparation();
    new spell_df_magic_wings();
    new npc_df_shoot_target_controller();
    new npc_df_darkmoon_target_bunny();
    new spell_df_ring_toss();
    new spell_df_ring_powerbar();
    new npc_df_dubenko();
    new at_target_turtle();
}
