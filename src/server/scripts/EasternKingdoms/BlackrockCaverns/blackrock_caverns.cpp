
/*
 * Copyright (C) 2011 - 2013 Naios <https://github.com/Naios>
 *
 * THIS particular file is NOT free software.
 * You are not allowed to share or redistribute it.
 */

#include "ScriptPCH.h"
#include "blackrock_caverns.h"
#include "ScriptedEscortAI.h"

enum Spells
{
    SPELL_SHADOW_PRISON             = 79725,
    SPELL_FURIOUS_RAGE              = 80218,
    SPELL_FURIOUS_SWIPE             = 80340,
    SPELL_AGGRO_NEARBY_TARGETS      = 80189,
    SPELL_STOP_HEART                = 82393,

    SPELL_NETHER_DRAGON_ESSENCE_VISUAL_1 = 75650,
    SPELL_NETHER_DRAGON_ESSENCE_VISUAL_2 = 75653,
    SPELL_NETHER_DRAGON_ESSENCE_VISUAL_3 = 75654
};

enum Say
{
    SAY_RAZ_SQUEEZ,
    SAY_DEATH
};

enum Positions
{
    POSITION_SEARCHER_CORLA,
    POSITION_SEARCHER_OBSIDIUS,
    POSITION_JUMP_OUT_OF_CAGE,
    POSITION_JUMP_BRIDGE_TO_MIDDLE,
    POSITION_JUMP_BRIDGE_TO_DOWNSTAIRS,
    POSITION_JUMP_OVER_KARSHS_ROOM,
    POSITION_TELE_SKIP_DISTANCE,
    POSITION_TELE_BEFORE_OBSIDIUS,
    POSITION_JUMP_TO_OBSIDIUS,
    POSITION_MAX
};

Position const razPositions[POSITION_MAX] =
{

    {432.821f, 818.703f, 107.327f, 0},      // After Corlas room
    {289.600f, 557.608f, 067.950f, 0},      // Before Obsidius
    {222.984f, 949.365f, 191.568f, 3.92f},  // Jump: Out of the Cage
    {406.193f, 906.012f, 163.492f, 4.31f},  // Jump: Bridge Position (from high to middle)
    {400.602f, 816.687f, 102.319f, 3.97f},  // Jump: Bridge Position (from middle to lower)
    {207.718f, 717.324f, 104.404f, 4.75f},  // Jump: To Skip Karsh Room
    {468.957f, 905.216f, 165.840f, 0},      // Tele: Location to skip a little time
    {305.165f, 636.298f, 64.4708f, 4.74f},  // Tele: Location before Obsidius
    {309.441f, 590.289f, 69.4896f, 4.85f}   // Jump: Location to the group before Obsidius
};

uint32 const enemyList[6] = {39980, 39982, 39978, 39987, 39985, 40017};

enum Step
{
    STEP_WAITING_BEFORE_ROMOGG,
    STEP_WAITING_AFTER_CORLA,
    STEP_WAITING_BEFORE_OBSIDIUS
};

class DeathAndBuguseCheck
{
public:
    DeathAndBuguseCheck(Unit* unit) : me(unit) {}

    bool operator() (Unit* unit)
    {
        if (unit->isDead())
            return true;

        Creature* enemy = unit->ToCreature();

        // Prevents Raz bugusing by pulling the mobs to him...
        return (!enemy) || me->GetDistance(enemy->GetHomePosition()) > 25.f;
    }

private:
    Unit* me;
};

class npc_raz_the_crazed : public CreatureScript
{
public:
    npc_raz_the_crazed() : CreatureScript("npc_raz_the_crazed") { }

    struct npc_raz_the_crazedAI : public npc_escortAI
    {
        npc_raz_the_crazedAI(Creature* creature) : npc_escortAI(creature), instance(creature->GetInstanceScript())
        {
            Restore();
        }

        InstanceScript* instance;
        bool isWaiting;
        uint8 step;
        uint32 uiTimer;
        Creature* enemyTarget;
        std::set<Creature*> enemyKillList;
        bool isTwilightguardsOk;

        void Restore()
        {
            isTwilightguardsOk = false;
            isWaiting = true;
            step = STEP_WAITING_BEFORE_ROMOGG;
            uiTimer = 500;

            enemyTarget = NULL;

            if (instance->GetBossState(DATA_KARSH_STEELBENDER) == DONE || instance->GetBossState(DATA_BEAUTY) == DONE)
            {
                isTwilightguardsOk = true;
                DoTeleportTo(POSITION_TELE_BEFORE_OBSIDIUS);
                DoWaitOnStep(STEP_WAITING_BEFORE_OBSIDIUS);

            }
            else if (instance->GetBossState(DATA_ROMOGG_BONECRUSHER) == DONE)
            {
                DoTeleportTo(POSITION_TELE_SKIP_DISTANCE);
                DoWaitOnStep(STEP_WAITING_AFTER_CORLA);
            }

            SetDespawnAtEnd(false);
        }

        void UpdateAI(uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);

            if (uiTimer <= diff)
            {
                uiTimer = 700;

                if (isWaiting)
                {
                    if (step == STEP_WAITING_BEFORE_ROMOGG)
                        return;

                    Map::PlayerList const &players = me->GetMap()->GetPlayers();

                    for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                        if (itr->getSource()->GetDistance(razPositions[step-1]) < 13.f && !itr->getSource()->isGameMaster())
                        {
                            if (instance->GetBossState(step == 1 ? DATA_CORLA_HERALD_OF_TWILIGHT : DATA_KARSH_STEELBENDER) != DONE)
                                return;

                            isWaiting = false;
                            me->SetVisible(true);
                            SetEscortPaused(false);
                            return;
                        }

                }
                else
                {
                    if (enemyTarget && enemyTarget->isAlive())
                    {
                        me->SetFacingToObject(enemyTarget);
                        me->HandleEmoteCommand(EMOTE_ONESHOT_ATTACK_UNARMED);
                        DoCast(enemyTarget, SPELL_FURIOUS_SWIPE);

                        Aura* rageBuff = me->GetAura(SPELL_FURIOUS_RAGE);
                        if (rageBuff)
                        {
                            uint8 stacks = rageBuff->GetStackAmount();
                            me->DealDamage(enemyTarget, (stacks == 1) ? 70000 : 70000*stacks*stacks);
                        }

                        if (!rageBuff || rageBuff->GetStackAmount() <= 4)
                            DoCast(me, SPELL_FURIOUS_RAGE);

                    }
                    else
                    {
                        enemyTarget = NULL;

                        if (enemyKillList.empty())
                        {
                            for (uint8 i = 0; i < sizeof(enemyList) - (isTwilightguardsOk ? 0 : 1); i++)
                            {
                                std::list<Creature*> creatures;
                                GetCreatureListWithEntryInGrid(creatures, me, enemyList[i], 15.f);
                                creatures.remove_if (DeathAndBuguseCheck(me));

                                for (std::list<Creature*>::const_iterator itr = creatures.begin(); itr != creatures.end(); ++itr)
                                    if (enemyKillList.find(*itr) == enemyKillList.end())
                                        enemyKillList.insert(*itr);
                            }
                        }

                        if (!enemyKillList.empty())
                        {
                            // Try to find the nearest creature
                            float closestDistance = 15.f; // Also max range
                            std::set<Creature*>::const_iterator closestCreature = enemyKillList.begin();

                            for (std::set<Creature*>::const_iterator itr = enemyKillList.begin(); itr != enemyKillList.end(); ++itr)
                            {
                                if ((*itr)->GetDistance(me) < closestDistance)
                                {
                                    closestCreature = itr;
                                    closestDistance = (*itr)->GetDistance(me);
                                }
                            }

                            enemyTarget = *closestCreature;
                            enemyKillList.erase(closestCreature);

                            if (!npc_escortAI::HasEscortState(STATE_ESCORT_PAUSED))
                                SetEscortPaused(true);

                            me->SetFacingToObject(enemyTarget);
                            enemyTarget->SetFacingToObject(me);
                        }

                        if (!enemyTarget && npc_escortAI::HasEscortState(STATE_ESCORT_PAUSED))
                        {
                            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_NONE);
                            SetEscortPaused(false);
                        }
                    }
                }

                uiTimer = enemyKillList.empty() ? 1000 : 200;
            } else uiTimer -= diff;
        }

        void DoAction(int32 action)
        {
            if (action != INST_ACTION_RAZ_START_EVENT)
                return;

            isWaiting = false;
            me->RemoveAurasDueToSpell(SPELL_SHADOW_PRISON);

            DoJumpTo(POSITION_JUMP_OUT_OF_CAGE);
            Talk(SAY_RAZ_SQUEEZ);
            Start(true, true);
        }      

        void WaypointReached(uint32 point)
        {
            switch(point)
            {
                case 6:
                    DoJumpTo(POSITION_JUMP_BRIDGE_TO_MIDDLE);
                    break;
                case 7:
                    DoWaitOnStep(STEP_WAITING_AFTER_CORLA);
                    DoTeleportTo(POSITION_TELE_SKIP_DISTANCE);
                    break;
                case 8:
                    DoJumpTo(POSITION_JUMP_BRIDGE_TO_DOWNSTAIRS);
                    break;
                case 9:
                    Talk(SAY_RAZ_SQUEEZ);
                    break;
                case 10:
                    DoJumpTo(POSITION_JUMP_OVER_KARSHS_ROOM);
                    break;
                case 12:
                    DoWaitOnStep(STEP_WAITING_BEFORE_OBSIDIUS);
                    DoTeleportTo(POSITION_TELE_BEFORE_OBSIDIUS);
                    break;
                case 13:
                    isTwilightguardsOk = true;
                    DoJumpTo(POSITION_JUMP_TO_OBSIDIUS);
                    Talk(SAY_RAZ_SQUEEZ);
                    break;
                case 15:
                    {
                        SetEscortPaused(true);
                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_TWILIGHT_GUARD, 30.f);

                        for (std::list<Creature*>::iterator itr = creatures.begin(); itr != creatures.end(); ++itr)
                        {
                            (*itr)->RemoveAllAuras();
                            (*itr)->InterruptNonMeleeSpells(false);
                            (*itr)->GetMotionMaster()->MovePoint(0, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ());
                        }
                        break;
                    }
                case 16:
                    {
                        if (Creature* obsidius = me->GetCreature(*me, instance->GetData64(BOSS_ASCENDANT_LORD_OBSIDIUS)))
                        {
                            obsidius->RemoveAllAuras();
                            obsidius->AI()->DoCast(SPELL_STOP_HEART);
                        }
                        break;
                    }
                case 17:
                    {
                        SetEscortPaused(true);

                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, NPC_TWILIGHT_GUARD, 30.f);
                        for (std::list<Creature*>::iterator itr = creatures.begin(); itr != creatures.end(); ++itr)
                            (*itr)->DespawnOrUnsummon(urand(3000, 6000));

                        Talk(SAY_DEATH);
                        me->Kill(me);
                        break;
                    }
            }
        }

        void DoWaitOnStep(Step const& nextWaitstep)
        {
            enemyKillList.clear();
            me->SetVisible(false);
            me->RemoveAllAuras();
            SetEscortPaused(true);
            isWaiting = true;
            step = nextWaitstep;
            uiTimer = 1000;
        }

        void DoJumpTo(Positions const& pos)
        {
            me->HandleEmoteCommand(EMOTE_ONESHOT_JUMPSTART);
            me->GetMotionMaster()->MoveJump(razPositions[pos].GetPositionX(), razPositions[pos].GetPositionY(), razPositions[pos].GetPositionZ(), 15, 15);
        }

        void DoTeleportTo(Positions const& pos)
        {
            me->NearTeleportTo(razPositions[pos].GetPositionX(), razPositions[pos].GetPositionY(), razPositions[pos].GetPositionZ(), 0);
            me->UpdateObjectVisibility();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_raz_the_crazedAI(creature);
    }
};

// 75649 Nether Dragon Essence
class spell_nether_dragon_essence : public SpellScriptLoader
{
    public:
        spell_nether_dragon_essence() : SpellScriptLoader("spell_nether_dragon_essence") { }

        class spell_nether_dragon_essence_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_nether_dragon_essence_AuraScript);

            void HandlePeriodicTick(AuraEffect const* /*aurEff*/)
            {
                PreventDefaultAction();
                GetCaster()->CastSpell(GetCaster(),
                    RAND(SPELL_NETHER_DRAGON_ESSENCE_VISUAL_1, SPELL_NETHER_DRAGON_ESSENCE_VISUAL_2, SPELL_NETHER_DRAGON_ESSENCE_VISUAL_3),
                        TRIGGERED_FULL_MASK);
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_nether_dragon_essence_AuraScript::HandlePeriodicTick, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_nether_dragon_essence_AuraScript();
        }
};

void AddSC_blackrock_caverns()
{
    new npc_raz_the_crazed();
    new spell_nether_dragon_essence();
}
