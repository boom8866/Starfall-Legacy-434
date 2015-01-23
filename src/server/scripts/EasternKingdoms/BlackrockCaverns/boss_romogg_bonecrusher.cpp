/*
 * Copyright (C) 2011 - 2013 TMM <https://bitbucket.org/TMM>
 *
 * THIS particular file is NOT free software.
 * You are not allowed to share or redistribute it.
 */

#include "ScriptPCH.h"
#include "blackrock_caverns.h"

/* ScriptData
SDName: blackrock_caverns
SD%Complete: 100
SDComment: Based script TMM
SDCategory: Blackrock Caverns
EndScriptData

39665 Rom'ogg Bonecrusher
Race    Ogre lord (Humanoid)
Level    82 - 87 Elite
Health   893,580 - 4,564,670 (heroic)

Rom'ogg Bonecrusher Info:

Abilities:
Call for Help—Rom'ogg calls for nearby minions to assist him! 1.5 sec cast
Chains of Woe—Slams the ground, causing an earthquake. 2 sec cast
Quake 40 yd range—Slams the ground, causing an earthquake that inflicts 9000 Physical damage to all nearby enemies over 3 seconds.
The Skullcracker—A powerful attack that inflicts 95000 to 105000 Physical damage to all enemies within 12 yards of the caster. 12 sec cast (8 sec cast Heroic
Wounding Strike Melee range—Inflicts 125% weapon damage and leaves the target wounded, reducing the effectiveness of any healing by 25% for 6 sec. (10 sec. Heroic)

Achievements:
[Crushing Bones and Cracking Skulls] Info:
Defeat Rom'ogg Bonecrusher after using his Skullcracker ability to kill 10 Angered Earth elementals in Blackrock Caverns on Heroic Difficulty.

Quotes:
Aggro
    Boss Cho'gall not gonna be happy 'bout dis!
Skullcracker:
    Stand still! Rom'ogg crack your skulls!
Killing a player:
    That what you get! Nothing!
Death:
    Rom'ogg...sorry...
*/

enum Spells
{
    SPELL_CALL_FOR_HELP                 = 82137,
    SPELL_QUAKE_N                       = 75272,
    SPELL_QUAKE_HC                      = 95317,
    SPELL_CHAINS_OF_WOE                 = 75539,
    SPELL_CHAINS_OF_WOE_VISUAL          = 75441,
    SPELL_CHAINS_OF_WOE_EFFECT          = 82192,
    SPELL_CHAINS_OF_WOE_TELE            = 75464,
    SPELL_THE_SKULLCRACKER_N            = 95324,
    SPELL_THE_SKULLCRACKER_TRIGGER_N    = 75428,
    SPELL_THE_SKULLCRACKER_HC           = 75543,
    SPELL_THE_SKULLCRACKER_TRIGGER_HC   = 95326,
    SPELL_WOUNDING_STRIKE               = 69651,

    // Adds
    SPELL_QUAKE_SUM_N                   = 75372,
    SPELL_QUAKE_SUM_HC                  = 95318,
    SPELL_QUAKE_EFFECT                  = 30658,
    SPELL_GROUND_RUPTURE                = 75347
};

enum Events
{
    EVENT_QUAKE             = 1,
    EVENT_CHAINS_OF_WOE,
    EVENT_THE_SCULLCRACKER,
    EVENT_WOUNDING_STRIKE
};

enum Actions
{
    ACTION_RAZ_START_EVENT
};

enum Texts
{
    // Rom'ogg Bonecrusher
    SAY_AGGRO           = 0, // Boss Cho'gall not gonna be happy 'bout dis!
    SAY_SKULLCRACKER    = 1, // Stand still! Rom'ogg crack your skulls!
    SAY_KILL            = 2, // That what you get! Nothing!
    SAY_DEATH           = 3  // Rom'ogg...sorry...
};

#define CRUSHING_BONES_AND_CRACKING_SKULLS 70337

uint32 const helpers[4] =
{
    NPC_TWILIGHT_TORTURER,
    NPC_TWILIGHT_SADIST,
    NPC_CRAZED_MAGE,
    NPC_MAD_PRISONER
};

//-----------------------------------------------------------------------
// 39665,39666 Rom'ogg Bonecrusher boss script
//-----------------------------------------------------------------------
class boss_romogg_bonecrusher : public CreatureScript
{
public:
    boss_romogg_bonecrusher() : CreatureScript("boss_romogg_bonecrusher") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_romogg_bonecrusherAI (creature);
    }

    struct boss_romogg_bonecrusherAI : public BossAI
    {
        boss_romogg_bonecrusherAI(Creature* creature) : BossAI(creature, DATA_ROMOGG_BONECRUSHER)
        {
            instance = creature->GetInstanceScript();
            me->ApplySpellImmune(0, IMMUNITY_ID, SPELL_THE_SKULLCRACKER_TRIGGER_N, true);
            me->ApplySpellImmune(0, IMMUNITY_ID, SPELL_THE_SKULLCRACKER_TRIGGER_HC, true);
            angeredKilled = 0;
        }

        enum actionId
        {
            ACTION_SET_ACHIEVEMENT  = 1
        };

        enum achievementId
        {
            ACHIEVEMENT_CRUSHING_BONE_AND_CRACKING_SKULLS   = 5281
        };

        InstanceScript* instance;
        bool bHealth66;
        bool bHealth33;
        uint32 _CrushingBones;

        void Reset()
        {
            _Reset();

            bHealth66 = false;
            bHealth33 = false;

            _CrushingBones = 0;

            me->DespawnCreaturesInArea(NPC_CHAINS_OF_WOE);
            me->DespawnCreaturesInArea(NPC_ANGERED_EARTH);
            instance->SetBossState(DATA_ROMOGG_BONECRUSHER, NOT_STARTED);
            RemoveEncounterFrame();
            angeredKilled = 0;
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_SET_ACHIEVEMENT:
                {
                    angeredKilled++;
                    break;
                }
                default:
                    break;
            }
        }

        void JustSummoned(Creature* summon)
        {
            switch (summon->GetEntry())
            {
                case NPC_ANGERED_EARTH:
                    summon->SetReactState(REACT_PASSIVE);
                    summon->SetInCombatWithZone();
                default:
                    break;
            }

            BossAI::JustSummoned(summon);
        }

        void EnterCombat(Unit* /*who*/)
        {
            _EnterCombat();

            AddEncounterFrame();
            DoCastAOE(SPELL_CALL_FOR_HELP);
            events.ScheduleEvent(EVENT_QUAKE, 13000);
            instance->SetBossState(DATA_ROMOGG_BONECRUSHER, IN_PROGRESS);
            if (IsHeroic())
                events.ScheduleEvent(EVENT_WOUNDING_STRIKE, 7000);
            angeredKilled = 0;
        }

        void JustDied(Unit* /*killer*/)
        {
            if (Creature* razTheCrazed = me->FindNearestCreature(NPC_RAZ_THE_CRAZED, 180.f, true))
                razTheCrazed->AI()->DoAction(ACTION_RAZ_START_EVENT);
            Talk(SAY_DEATH);
            me->DespawnCreaturesInArea(NPC_CHAINS_OF_WOE);
            me->DespawnCreaturesInArea(NPC_ANGERED_EARTH);
            RemoveEncounterFrame();
            instance->SetBossState(DATA_ROMOGG_BONECRUSHER, DONE);
            if (IsHeroic() && angeredKilled >= 10)
                instance->DoCompleteAchievement(ACHIEVEMENT_CRUSHING_BONE_AND_CRACKING_SKULLS);
            _JustDied();
        }

        void KilledUnit(Unit* victim)
        {
            if (victim->GetTypeId() == TYPEID_PLAYER)
                Talk(SAY_KILL);
        }

        uint32 GetData(uint32 type) const
        {
            switch (type)
            {
                case CRUSHING_BONES_AND_CRACKING_SKULLS:
                    return _CrushingBones;
                default:
                    break;
            }

            return 0;
        }

        void SetData(uint32 type, uint32 value)
        {
            switch (type)
            {
                case CRUSHING_BONES_AND_CRACKING_SKULLS:
                    _CrushingBones += std::max(value, _CrushingBones);
                    break;
                default:
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_QUAKE:
                        DoCastAOE(DUNGEON_MODE(SPELL_QUAKE_N, SPELL_QUAKE_HC));
                        events.ScheduleEvent(EVENT_QUAKE, 25000);
                        break;
                    case EVENT_CHAINS_OF_WOE:
                        DoCastAOE(SPELL_CHAINS_OF_WOE);
                        events.ScheduleEvent(EVENT_THE_SCULLCRACKER, 1000);
                        events.RescheduleEvent(EVENT_QUAKE, 25000);
                        if(IsHeroic())
                            events.RescheduleEvent(EVENT_WOUNDING_STRIKE, 15000);
                        break;
                    case EVENT_THE_SCULLCRACKER:
                        Talk(SAY_SKULLCRACKER);
                        DoCastVictim(DUNGEON_MODE(SPELL_THE_SKULLCRACKER_N, SPELL_THE_SKULLCRACKER_HC));
                        break;
                    case EVENT_WOUNDING_STRIKE:
                        DoCastVictim(SPELL_WOUNDING_STRIKE);
                        events.ScheduleEvent(EVENT_WOUNDING_STRIKE, 15000);
                        break;
                }
            }

            if (!bHealth66 && !HealthAbovePct(66))
            {
                me->AttackStop();
                events.ScheduleEvent(EVENT_CHAINS_OF_WOE, 100);

                bHealth66 = true;
            }

            if (!bHealth33 && !HealthAbovePct(33))
            {
                me->AttackStop();
                events.ScheduleEvent(EVENT_CHAINS_OF_WOE, 100);

                bHealth33 = true;
            }

            DoMeleeAttackIfReady();
        }

        protected:
            uint8 angeredKilled;
    };
};

//-----------------------------------------------------------------------
// 40447,50379,51407  npc Chains of Woe script
//-----------------------------------------------------------------------
class npc_chains_of_woe : public CreatureScript
{
public:
    npc_chains_of_woe() : CreatureScript("npc_chains_of_woe") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_chains_of_woeAI (creature);
    }

    struct npc_chains_of_woeAI : public ScriptedAI
    {
        npc_chains_of_woeAI(Creature* creature) : ScriptedAI(creature), stopEffect(false)
        {
            instance = creature->GetInstanceScript();
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
            me->CastSpell(me, SPELL_CHAINS_OF_WOE_VISUAL, true);
            me->SetDisplayId(11686); // Invisible
            TeleportPlayers();
        }

        bool stopEffect;
        InstanceScript* instance;

        //Teleport players
        void TeleportPlayers()
        {
            Map::PlayerList const &PlayerList = me->GetMap()->GetPlayers();
            if (!PlayerList.isEmpty())
            {
                for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                {
                    if (Player* player = i->getSource())
                    {
                        if (player->isAlive())
                            player->CastSpell(me, SPELL_CHAINS_OF_WOE_TELE, true);
                    }
                }
            }
        }

        void UpdateAI(uint32 diff)
        {
            if(!stopEffect)
                HandleEffect(true);
        }

        void HandleEffect(bool apply)
        {
            Map::PlayerList const &PlayerList = me->GetMap()->GetPlayers();
            if (!PlayerList.isEmpty())
            {
                for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                {
                    if (apply)
                    {
                        if (!i->getSource()->HasAura(SPELL_CHAINS_OF_WOE_EFFECT))
                            me->AddAura(SPELL_CHAINS_OF_WOE_EFFECT, i->getSource());
                    }
                    else
                        i->getSource()->RemoveAurasDueToSpell(SPELL_CHAINS_OF_WOE_EFFECT);
                }
            }
        }

        void JustDied(Unit* /*killer*/)
        {
            Map::PlayerList const &PlayerList = me->GetMap()->GetPlayers();
            if (!PlayerList.isEmpty())
            {
                for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                    i->getSource()->RemoveAurasDueToSpell(SPELL_CHAINS_OF_WOE_EFFECT);
            }
        }
    };
};

enum QakeEvents
{
    EVENT_GROUND_RUPTURE = 1,
    EVENT_QUAKE_EFFECT,
    EVENT_DESPAWN
};

//-----------------------------------------------------------------------
// 40401, 51406  npc Quake script
//-----------------------------------------------------------------------
class npc_quake : public CreatureScript
{
public:
    npc_quake() : CreatureScript("npc_quake") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_quakeAI (creature);
    }

    struct npc_quakeAI : public ScriptedAI
    {
        npc_quakeAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;

        void InitializeAI()
        {
            ScriptedAI::InitializeAI();

            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE);
            me->SetDisplayId(11686); // Invisible
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
            events.ScheduleEvent(EVENT_QUAKE_EFFECT, 200);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_QUAKE_EFFECT:
                    {
                        me->CastSpell(me, SPELL_QUAKE_EFFECT, true);
                        events.ScheduleEvent(EVENT_GROUND_RUPTURE, 2000);
                        break;
                    }
                    case EVENT_GROUND_RUPTURE:
                    {
                        DoCastAOE(SPELL_GROUND_RUPTURE);
                        events.CancelEvent(EVENT_QUAKE_EFFECT);
                        events.ScheduleEvent(EVENT_DESPAWN, 2000);
                        break;
                    }
                    case EVENT_DESPAWN:
                    {
                        me->DespawnOrUnsummon(1000);
                        break;
                    }
                    default:
                        break;
                }
            }
        }

    private:
        EventMap events;
    };
};

class npc_angered_earth : public CreatureScript
{
public:
    npc_angered_earth() : CreatureScript("npc_angered_earth")
    {
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_angered_earthAI(creature);
    }

    struct npc_angered_earthAI : public ScriptedAI
    {
        npc_angered_earthAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        enum npcId
        {
            NPC_ROMOGG_BONECRUSHER  = 39665
        };

        enum spellId
        {
            SPELL_THE_SKULLCRAKER_N     = 75428,
            SPELL_THE_SKULLCRAKER_H     = 93454
        };

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            switch (spell->Id)
            {
                case SPELL_THE_SKULLCRAKER_N:
                case SPELL_THE_SKULLCRAKER_H:
                {
                    if (Creature* romogg = me->FindNearestCreature(NPC_ROMOGG_BONECRUSHER, 200.0f, true))
                        romogg->AI()->DoAction(1);
                    break;
                }
                default:
                    break;
            }
        }
    };
};

//-----------------------------------------------------------------------
// 75272, 95317 Quake set target summon location
//-----------------------------------------------------------------------
class spell_quake_summon_target : public SpellScriptLoader
{
public:
    spell_quake_summon_target() : SpellScriptLoader("spell_quake_summon_target") { }

    class spell_quake_summon_target_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_quake_summon_target_SpellScript);

        void FilterTargets(std::list<WorldObject*>& unitList)
        {
            unitList.remove_if(InstancePlayerCheck());
        }

        void HandleOnSummon(SpellEffIndex effIndex)
        {
            PreventHitDefaultEffect(effIndex);
            Unit* caster = GetOriginalCaster();
            if (!caster)
                return;

            InstanceScript* instance = caster->GetInstanceScript();
            if (!instance)
                return;

            uint32 entry = uint32(GetSpellInfo()->Effects[1].BasePoints);
            caster->CastSpell(GetHitUnit(), entry, true);
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_quake_summon_target_SpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_SRC_AREA_ENEMY);
            OnEffectHitTarget += SpellEffectFn(spell_quake_summon_target_SpellScript::HandleOnSummon, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_quake_summon_target_SpellScript();
    }
};

//-----------------------------------------------------------------------
// 75464 Chains of Woe set target teleport location
//-----------------------------------------------------------------------
class spell_chains_of_woe : public SpellScriptLoader
{
public:
    spell_chains_of_woe() : SpellScriptLoader("spell_chains_of_woe") { }

    class spell_chains_of_woe_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_chains_of_woe_SpellScript);

        void HandleSummon(SpellEffIndex effIndex)
        {
            PreventHitDefaultEffect(effIndex);
            Unit* caster = GetOriginalCaster();
            if (!caster)
                return;

            InstanceScript* instance = caster->GetInstanceScript();
            if (!instance)
                return;

            if (Creature* woe = caster->FindNearestCreature(NPC_CHAINS_OF_WOE, 200))
                caster->NearTeleportTo(woe->GetPositionX() + urand(1, 3), woe->GetPositionY() + urand(1, 3) , woe->GetPositionZ(), caster->GetOrientation());
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_chains_of_woe_SpellScript::HandleSummon, EFFECT_0, SPELL_EFFECT_TELEPORT_UNITS);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_chains_of_woe_SpellScript();
    }
};

// 82137 Call for Help
class spell_call_for_help : public SpellScriptLoader
{
public:
    spell_call_for_help() : SpellScriptLoader("spell_call_for_help") { }

    class spell_call_for_help_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_call_for_help_SpellScript);

        void HandleScript(SpellEffIndex effIndex)
        {
            if (Unit* caster = GetCaster())
            {
                Creature* me = caster->ToCreature();
                if (!me)
                    return;

                Unit* victim = me->getVictim();
                if (!victim)
                    return;

                std::list<Creature*> helperList;
                for (uint8 i = 0; i < sizeof(helpers); ++i)
                {
                    std::list<Creature*> creatures;
                    GetCreatureListWithEntryInGrid(creatures, me, helpers[i], 20.0f);

                    for (std::list<Creature*>::const_iterator itr = creatures.begin(); itr != creatures.end(); ++itr)
                        if ((*itr)->isAlive())
                            helperList.push_back(*itr);
                }

                me->AI()->DoZoneInCombat();
                for (std::list<Creature*>::const_iterator itr = helperList.begin(); itr != helperList.end(); ++itr)
                {
                    (*itr)->SetInCombatWithZone();
                    (*itr)->GetMotionMaster()->MoveChase(victim);
                }

                if (me->GetEntry() == BOSS_ROMOGG_BONECRUSHER)
                    me->AI()->Talk(SAY_AGGRO, me->GetGUID());
            }
        }

        void Register()
        {
            OnEffectLaunch += SpellEffectFn(spell_call_for_help_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_call_for_help_SpellScript();
    }
};

//-----------------------------------------------------------------------
// Crushing Bones and Cracking Skulls achievement 5281
//-----------------------------------------------------------------------
class achievement_crushing_bones_and_cracking_skulls : public AchievementCriteriaScript
{
public:
    achievement_crushing_bones_and_cracking_skulls() : AchievementCriteriaScript("achievement_crushing_bones_and_cracking_skulls") { }

    bool OnCheck(Player* /*source*/, Unit* target)
    {
        return false;
    }
};

void AddSC_boss_romogg_bonecrusher()
{
    new boss_romogg_bonecrusher();
    new npc_chains_of_woe();
    new npc_quake();
    new npc_angered_earth();

    // spell scripts
    new spell_quake_summon_target();
    new spell_chains_of_woe();
    new spell_call_for_help();

    // Crushing Bones and Cracking Skulls achievement
    new achievement_crushing_bones_and_cracking_skulls();
}
