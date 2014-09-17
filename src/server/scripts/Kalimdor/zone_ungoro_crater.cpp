/*
* Copyright (C) 2008-2013 TrinityCore <http://www.trinitycore.org/>
* Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation; either version 2 of the License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License along
* with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "ScriptPCH.h"
#include "ScriptedEscortAI.h"
#include "ScriptedFollowerAI.h"

/* For Nablya quest line */
Unit* whisperTarget = NULL;

/*####
# npc_ringo
####*/

enum Ringo
{
    SAY_RIN_START = 0,
    SAY_FAINT = 1,
    SAY_WAKE = 2,
    SAY_RIN_END_1 = 3,
    SAY_SPR_END_2 = 0,
    SAY_RIN_END_3 = 4,
    EMOTE_RIN_END_4 = 5,
    EMOTE_RIN_END_5 = 6,
    SAY_RIN_END_6 = 7,
    SAY_SPR_END_7 = 1,
    EMOTE_RIN_END_8 = 8,

    SPELL_REVIVE_RINGO = 15591,
    QUEST_A_LITTLE_HELP = 24735,
    NPC_SPRAGGLE = 9997,
    FACTION_ESCORTEE = 113
};

class npc_ringo : public CreatureScript
{
public:
    npc_ringo() : CreatureScript("npc_ringo") { }

    bool OnQuestAccept(Player* player, Creature* creature, const Quest* quest) override
    {
        if (quest->GetQuestId() == QUEST_A_LITTLE_HELP)
        {
            if (npc_ringoAI* ringoAI = CAST_AI(npc_ringo::npc_ringoAI, creature->AI()))
            {
                creature->SetStandState(UNIT_STAND_STATE_STAND);
                ringoAI->StartFollow(player, FACTION_ESCORTEE, quest);
                ringoAI->Talk(SAY_RIN_START, player->GetGUID());
            }
        }
        return true;
    }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_ringoAI(creature);
    }

    struct npc_ringoAI : public FollowerAI
    {
        npc_ringoAI(Creature* creature) : FollowerAI(creature)
        {
            Initialize();
        }

        void Initialize()
        {
            FaintTimer = urand(30000, 60000);
            EndEventProgress = 0;
            EndEventTimer = 1000;
            SpraggleGUID = 0;
        }

        uint32 FaintTimer;
        uint32 EndEventProgress;
        uint32 EndEventTimer;
        uint64 SpraggleGUID;

        void Reset()
        {
            Initialize();
        }

        void MoveInLineOfSight(Unit* who)
        {
            FollowerAI::MoveInLineOfSight(who);
            if (!me->getVictim() && !HasFollowState(STATE_FOLLOW_COMPLETE) && who->GetEntry() == NPC_SPRAGGLE)
            {
                if (me->IsWithinDistInMap(who, INTERACTION_DISTANCE))
                {
                    if (Player* player = GetLeaderForFollower())
                    {
                        if (player->GetQuestStatus(QUEST_A_LITTLE_HELP) == QUEST_STATUS_INCOMPLETE)
                            player->GroupEventHappens(QUEST_A_LITTLE_HELP, me);
                    }

                    SpraggleGUID = who->GetGUID();
                    SetFollowComplete(true);
                }
            }
        }

        void SpellHit(Unit* /*pCaster*/, const SpellInfo* pSpell) override
        {
            if (HasFollowState(STATE_FOLLOW_INPROGRESS | STATE_FOLLOW_PAUSED) && pSpell->Id == SPELL_REVIVE_RINGO)
                ClearFaint();
        }

        void SetFaint()
        {
            if (!HasFollowState(STATE_FOLLOW_POSTEVENT))
            {
                SetFollowPaused(true);
                Talk(SAY_FAINT);
            }

            //what does actually happen here? Emote? Aura?
            me->SetStandState(UNIT_STAND_STATE_SLEEP);
        }

        void ClearFaint()
        {
            me->SetStandState(UNIT_STAND_STATE_STAND);

            if (HasFollowState(STATE_FOLLOW_POSTEVENT))
                return;

            Talk(SAY_WAKE);
            SetFollowPaused(false);
        }

        void UpdateFollowerAI(uint32 Diff)
        {
            if (!UpdateVictim())
            {
                if (HasFollowState(STATE_FOLLOW_POSTEVENT))
                {
                    if (EndEventTimer <= Diff)
                    {
                        Creature* spraggle = ObjectAccessor::GetCreature(*me, SpraggleGUID);
                        if (!spraggle || !spraggle->isAlive())
                        {
                            SetFollowComplete();
                            return;
                        }

                        switch (EndEventProgress)
                        {
                            case 1:
                                Talk(SAY_RIN_END_1);
                                EndEventTimer = 3000;
                                break;
                            case 2:
                                spraggle->AI()->Talk(SAY_SPR_END_2);
                                EndEventTimer = 5000;
                                break;
                            case 3:
                                Talk(SAY_RIN_END_3);
                                EndEventTimer = 1000;
                                break;
                            case 4:
                                Talk(EMOTE_RIN_END_4);
                                SetFaint();
                                EndEventTimer = 9000;
                                break;
                            case 5:
                                Talk(EMOTE_RIN_END_5);
                                ClearFaint();
                                EndEventTimer = 1000;
                                break;
                            case 6:
                                Talk(SAY_RIN_END_6);
                                EndEventTimer = 3000;
                                break;
                            case 7:
                                spraggle->AI()->Talk(SAY_SPR_END_7);
                                EndEventTimer = 10000;
                                break;
                            case 8:
                                Talk(EMOTE_RIN_END_8);
                                EndEventTimer = 5000;
                                break;
                            case 9:
                                SetFollowComplete();
                                break;
                        }

                        ++EndEventProgress;
                    }
                    else
                        EndEventTimer -= Diff;
                }
                else if (HasFollowState(STATE_FOLLOW_INPROGRESS) && !HasFollowState(STATE_FOLLOW_PAUSED))
                {
                    if (FaintTimer <= Diff)
                    {
                        SetFaint();
                        FaintTimer = urand(60000, 120000);
                    }
                    else
                        FaintTimer -= Diff;
                }

                return;
            }

            DoMeleeAttackIfReady();
        }
    };
};

class spell_ever_watching_from_above : public SpellScriptLoader
{
    public:
        spell_ever_watching_from_above() : SpellScriptLoader("spell_ever_watching_from_above") { }

        class spell_ever_watching_from_above_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_ever_watching_from_above_SpellScript);

            enum spellId
            {
                // Bloodpetal
                EWFA_BLOODPETAL_AURA        = 72168,

                // Ptherodax
                EWFA_PTHERRORDAX_AURA       = 72179,

                // Gorilla
                EWFA_GORILLA_AURA           = 72187,

                // Diemetradon
                EWFA_DIEMETRADON_AURA       = 72197
            };

            enum npcId
            {
                NPC_ENTRY_NABLYA    = 38502
            };

            enum actionId
            {
                ACTION_INFORM_NABLYA_BLOODPETAL     = 1,
                ACTION_INFORM_NABLYA_PTHERRORDAX,
                ACTION_INFORM_NABLYA_GORILLA,
                ACTION_INFORM_NABLYA_DIEMETRADON
            };

            void SendInformations()
            {
                if (Unit* target = GetHitUnit())
                {
                    if (target->GetTypeId() != TYPEID_PLAYER)
                        return;

                    switch (GetSpellInfo()->Id)
                    {
                        case EWFA_BLOODPETAL_AURA:
                        {
                            if (Creature* nablya = target->FindNearestCreature(NPC_ENTRY_NABLYA, 80.0f, true))
                            {
                                whisperTarget = target;
                                nablya->AI()->DoAction(ACTION_INFORM_NABLYA_BLOODPETAL);
                            }
                            target->NearTeleportTo(-6717.03f, -1953.75f, -272.00f, 4.52f, true);
                            break;
                        }
                        case EWFA_PTHERRORDAX_AURA:
                        {
                            if (Creature* nablya = target->FindNearestCreature(NPC_ENTRY_NABLYA, 80.0f, true))
                            {
                                whisperTarget = target;
                                nablya->AI()->DoAction(ACTION_INFORM_NABLYA_PTHERRORDAX);
                            }
                            target->NearTeleportTo(-6687.30f, -977.64f, -271.75f, 4.14f, true);
                            break;
                        }
                        case EWFA_GORILLA_AURA:
                        {
                            if (Creature* nablya = target->FindNearestCreature(NPC_ENTRY_NABLYA, 80.0f, true))
                            {
                                whisperTarget = target;
                                nablya->AI()->DoAction(ACTION_INFORM_NABLYA_GORILLA);
                            }
                            target->NearTeleportTo(-6400.02f, -1795.92f, -269.74f, 1.22f, true);
                            break;
                        }
                        case EWFA_DIEMETRADON_AURA:
                        {
                            if (Creature* nablya = target->FindNearestCreature(NPC_ENTRY_NABLYA, 80.0f, true))
                            {
                                whisperTarget = target;
                                nablya->AI()->DoAction(ACTION_INFORM_NABLYA_DIEMETRADON);
                            }
                            target->NearTeleportTo(-7462.08f, -1477.98f, -271.89f, 3.53f, true);
                            break;
                        }
                        default:
                            break;
                    }
                }
            }

            void Register()
            {
                AfterHit += SpellHitFn(spell_ever_watching_from_above_SpellScript::SendInformations);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_ever_watching_from_above_SpellScript();
        }
};

class npc_nablya : public CreatureScript
{
public:
    npc_nablya() : CreatureScript("npc_nablya") { }

    enum actionId
    {
        ACTION_INFORM_NABLYA_BLOODPETAL     = 1,
        ACTION_INFORM_NABLYA_PTHERRORDAX,
        ACTION_INFORM_NABLYA_GORILLA,
        ACTION_INFORM_NABLYA_DIEMETRADON
    };

    struct npc_nablyaAI : public ScriptedAI
    {
        npc_nablyaAI(Creature* creature) : ScriptedAI(creature) {}

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_INFORM_NABLYA_BLOODPETAL:
                {
                    if (whisperTarget && whisperTarget != NULL)
                    {
                        Talk(0, whisperTarget->GetGUID());
                        Talk(1, whisperTarget->GetGUID());
                    }
                    break;
                }
                case ACTION_INFORM_NABLYA_GORILLA:
                {
                    if (whisperTarget && whisperTarget != NULL)
                    {
                        Talk(2, whisperTarget->GetGUID());
                        Talk(3, whisperTarget->GetGUID());
                    }
                    break;
                }
                case ACTION_INFORM_NABLYA_PTHERRORDAX:
                {
                    if (whisperTarget && whisperTarget != NULL)
                    {
                        Talk(4, whisperTarget->GetGUID());
                        Talk(5, whisperTarget->GetGUID());
                    }
                    break;
                }
                case ACTION_INFORM_NABLYA_DIEMETRADON:
                {
                    if (whisperTarget && whisperTarget != NULL)
                    {
                        Talk(7, whisperTarget->GetGUID());
                        Talk(8, whisperTarget->GetGUID());
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
        return new npc_nablyaAI(creature);
    }
};

class npc_ithis_moonwarden : public CreatureScript
{
public:
    npc_ithis_moonwarden() : CreatureScript("npc_ithis_moonwarden") { }

    enum questId
    {
        QUEST_ENTRY_THE_EASTERN_PYLON   = 24721
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_ENTRY_THE_EASTERN_PYLON)
        {
            player->TeleportTo(1, -7197.63f, -2326.65f, -228.59f, 1.93f);
            return false;
        }
        return true;
    }
};

class spell_bite_diemetradon : public SpellScriptLoader
{
    public:
        spell_bite_diemetradon() : SpellScriptLoader("spell_bite_diemetradon") { }

        class spell_bite_diemetradon_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_bite_diemetradon_SpellScript);

            enum Id
            {
                QUEST_CREDIT_DIEMETRADON    = 72192
            };

            SpellCastResult CheckCast()
            {
                if (Unit* caster = GetCaster())
                {
                    if (Unit* target = GetExplTargetUnit())
                    {
                        if (target->ToCreature() && target->ToCreature()->GetCreatureType() == CREATURE_TYPE_HUMANOID)
                            return SPELL_CAST_OK;
                    }
                }
                return SPELL_FAILED_BAD_IMPLICIT_TARGETS;
            }

            void HandleQuestCredit()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        if (roll_chance_f(33))
                            caster->CastSpell(caster, QUEST_CREDIT_DIEMETRADON, true);
                    }
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_bite_diemetradon_SpellScript::CheckCast);
                AfterCast += SpellCastFn(spell_bite_diemetradon_SpellScript::HandleQuestCredit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_bite_diemetradon_SpellScript();
        }
};

class spell_ptherrordax_dash : public SpellScriptLoader
{
    public:
        spell_ptherrordax_dash() : SpellScriptLoader("spell_ptherrordax_dash") { }

        class spell_ptherrordax_dash_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_ptherrordax_dash_SpellScript);

            enum Id
            {
                QUEST_CREDIT_PTHERRORDAX    = 72193
            };

            void HandleQuestCredit()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        if (roll_chance_f(15))
                            caster->CastSpell(caster, QUEST_CREDIT_PTHERRORDAX, true);
                    }
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_ptherrordax_dash_SpellScript::HandleQuestCredit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_ptherrordax_dash_SpellScript();
        }
};

void AddSC_ungoro_crater()
{
    new npc_ringo();
    new spell_ever_watching_from_above();
    new npc_nablya();
    new npc_ithis_moonwarden();
    new spell_bite_diemetradon();
    new spell_ptherrordax_dash();
}
