/*
 * Copyright (C) 2008-2013 TrinityCore <http://www.trinitycore.org/>
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

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "Player.h"

/*######
## Quest 25134: Lazy Peons
## npc_lazy_peon
######*/

enum LazyPeonYells
{
    SAY_SPELL_HIT                                 = 0
};

enum LazyPeon
{
    QUEST_LAZY_PEONS    = 25134,
    GO_LUMBERPILE       = 175784,
    SPELL_BUFF_SLEEP    = 17743,
    SPELL_AWAKEN_PEON   = 19938
};

class npc_lazy_peon : public CreatureScript
{
public:
    npc_lazy_peon() : CreatureScript("npc_lazy_peon") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_lazy_peonAI(creature);
    }

    struct npc_lazy_peonAI : public ScriptedAI
    {
        npc_lazy_peonAI(Creature* creature) : ScriptedAI(creature) {}

        uint64 PlayerGUID;

        uint32 RebuffTimer;
        bool work;

        void Reset()
        {
            PlayerGUID = 0;
            RebuffTimer = 0;
            work = false;
        }

        void MovementInform(uint32 /*type*/, uint32 id)
        {
            if (id == 1)
                work = true;
        }

        void SpellHit(Unit* caster, const SpellInfo* spell)
        {
            if (spell->Id == SPELL_AWAKEN_PEON && caster->GetTypeId() == TYPEID_PLAYER
                && CAST_PLR(caster)->GetQuestStatus(QUEST_LAZY_PEONS) == QUEST_STATUS_INCOMPLETE)
            {
                caster->ToPlayer()->KilledMonsterCredit(me->GetEntry(), me->GetGUID());
                Talk(SAY_SPELL_HIT, caster->GetGUID());
                me->RemoveAllAuras();
                if (GameObject* Lumberpile = me->FindNearestGameObject(GO_LUMBERPILE, 20))
                    me->GetMotionMaster()->MovePoint(1, Lumberpile->GetPositionX()-1, Lumberpile->GetPositionY(), Lumberpile->GetPositionZ());
            }
        }

        void UpdateAI(uint32 Diff)
        {
            if (work == true)
                me->HandleEmoteCommand(EMOTE_ONESHOT_WORK_CHOPWOOD);
            if (RebuffTimer <= Diff)
            {
                DoCast(me, SPELL_BUFF_SLEEP);
                RebuffTimer = 300000; //Rebuff agian in 5 minutes
            }
            else
                RebuffTimer -= Diff;
            if (!UpdateVictim())
                return;
            DoMeleeAttackIfReady();
        }
    };
};

enum VoodooSpells
{
    SPELL_BREW      = 16712, // Special Brew
    SPELL_GHOSTLY   = 16713, // Ghostly
    SPELL_HEX1      = 16707, // Hex
    SPELL_HEX2      = 16708, // Hex
    SPELL_HEX3      = 16709, // Hex
    SPELL_GROW      = 16711, // Grow
    SPELL_LAUNCH    = 16716, // Launch (Whee!)
};

// 17009
class spell_voodoo : public SpellScriptLoader
{
    public:
        spell_voodoo() : SpellScriptLoader("spell_voodoo") {}

        class spell_voodoo_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_voodoo_SpellScript);

            bool Validate(SpellInfo const* /*spell*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_BREW) || !sSpellMgr->GetSpellInfo(SPELL_GHOSTLY) ||
                    !sSpellMgr->GetSpellInfo(SPELL_HEX1) || !sSpellMgr->GetSpellInfo(SPELL_HEX2) ||
                    !sSpellMgr->GetSpellInfo(SPELL_HEX3) || !sSpellMgr->GetSpellInfo(SPELL_GROW) ||
                    !sSpellMgr->GetSpellInfo(SPELL_LAUNCH))
                    return false;
                return true;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                uint32 spellid = RAND(SPELL_BREW, SPELL_GHOSTLY, RAND(SPELL_HEX1, SPELL_HEX2, SPELL_HEX3), SPELL_GROW, SPELL_LAUNCH);
                if (Unit* target = GetHitUnit())
                    GetCaster()->CastSpell(target, spellid, false);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_voodoo_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_voodoo_SpellScript();
        }
};

class npc_drowned_thunder_lizard : public CreatureScript
{
public:
    npc_drowned_thunder_lizard() : CreatureScript("npc_drowned_thunder_lizard") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_drowned_thunder_lizardAI (creature);
    }

    enum Id
    {
        QUEST_THUNDER_DOWN_UNDER        = 25236,
        QUEST_CREDIT_LIZARD             = 39464
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->IsActiveQuest(QUEST_THUNDER_DOWN_UNDER))
        {
            player->KilledMonsterCredit(QUEST_CREDIT_LIZARD);
            creature->DespawnOrUnsummon(1);
            return true;
        }
        return true;
    }

    struct npc_drowned_thunder_lizardAI : public ScriptedAI
    {
        npc_drowned_thunder_lizardAI(Creature* creature) : ScriptedAI(creature) {}
    };

};

class npc_thonk : public CreatureScript
{
public:
    npc_thonk() : CreatureScript("npc_thonk") { }

    enum Id
    {
        QUEST_WATERSHED_PATROL              = 25188,
        CREDIT_PATROL_TEKLA                 = 39331,
        CREDIT_PATROL_RAGGARAN              = 39332,
        CREDIT_PATROL_MISHA                 = 39333,
        CREDIT_PATROL_ZENTAJI               = 39334,
        QUEST_SPIRITS_BE_PRAISED            = 25189,
        QUEST_RAGGARAN_FURY                 = 25192,
        QUEST_LOST_BUT_NOT_FORGOTTEN        = 25193,
        QUEST_THAT_THE_END_OF_THE_RAPTOR    = 25195
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_thonkAI (creature);
    }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_WATERSHED_PATROL)
        {
            if (player->GetQuestStatus(QUEST_THAT_THE_END_OF_THE_RAPTOR) == QUEST_STATUS_REWARDED)
                player->KilledMonsterCredit(CREDIT_PATROL_ZENTAJI);
            if (player->GetQuestStatus(QUEST_LOST_BUT_NOT_FORGOTTEN) == QUEST_STATUS_REWARDED)
                player->KilledMonsterCredit(CREDIT_PATROL_MISHA);
            if (player->GetQuestStatus(QUEST_SPIRITS_BE_PRAISED) == QUEST_STATUS_REWARDED)
                player->KilledMonsterCredit(CREDIT_PATROL_TEKLA);
            if (player->GetQuestStatus(QUEST_RAGGARAN_FURY) == QUEST_STATUS_REWARDED)
                player->KilledMonsterCredit(CREDIT_PATROL_RAGGARAN);
        }
        return true;
    }

    struct npc_thonkAI : public ScriptedAI
    {
        npc_thonkAI(Creature *c) : ScriptedAI(c) {}
    };
};

class npc_zentaji : public CreatureScript
{
public:
    npc_zentaji() : CreatureScript("npc_zentaji") { }

    enum Id
    {
        CREDIT_PATROL_ZENTAJI               = 39334,
        QUEST_THAT_THE_END_OF_THE_RAPTOR    = 25195
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_zentajiAI (creature);
    }

    bool OnQuestReward(Player* player, Creature* /*creature*/, Quest const* quest, uint32 /*opt*/)
    {
        if (quest->GetQuestId() == QUEST_THAT_THE_END_OF_THE_RAPTOR)
            player->KilledMonsterCredit(CREDIT_PATROL_ZENTAJI);
        return true;
    }

    struct npc_zentajiAI : public ScriptedAI
    {
        npc_zentajiAI(Creature *c) : ScriptedAI(c) {}
    };
};

class npc_raggaran : public CreatureScript
{
public:
    npc_raggaran() : CreatureScript("npc_raggaran") { }

    enum Id
    {
        CREDIT_PATROL_RAGGARAN              = 39332,
        QUEST_RAGGARAN_FURY                 = 25192
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_raggaranAI (creature);
    }

    bool OnQuestReward(Player* player, Creature* /*creature*/, Quest const* quest, uint32 /*opt*/)
    {
        if (quest->GetQuestId() == QUEST_RAGGARAN_FURY)
            player->KilledMonsterCredit(CREDIT_PATROL_RAGGARAN);
        return true;
    }

    struct npc_raggaranAI : public ScriptedAI
    {
        npc_raggaranAI(Creature *c) : ScriptedAI(c) {}
    };
};

/* TEKLA TODO */
/* SCRIPT ALL THE EVENT WITH TALK AND ESCORT */
/* Progress: 20% */

class npc_tekla : public CreatureScript
{
public:
    npc_tekla() : CreatureScript("npc_tekla") { }

    enum Id
    {
        CREDIT_PATROL_TEKLA                 = 39331,
        QUEST_SPIRITS_BE_PRAISED            = 25189,
        NPC_TEKLA                           = 39325,
        NPC_RAGGARAN                        = 39326,
        SPELL_WATER_WALKING                 = 73887,
        SPELL_AIR_SPIRIT_BOON               = 73889
    };

    bool OnQuestReward(Player* player, Creature* /*creature*/, Quest const* quest, uint32 /*opt*/)
    {
        if (quest->GetQuestId() == QUEST_SPIRITS_BE_PRAISED)
            player->KilledMonsterCredit(CREDIT_PATROL_TEKLA);
        return true;
    }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_SPIRITS_BE_PRAISED)
        {
            player->SummonCreature(NPC_TEKLA, creature->GetPositionX(), creature->GetPositionY(), creature->GetPositionZ(), creature->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 600000, const_cast<SummonPropertiesEntry*>(sSummonPropertiesStore.LookupEntry(67)));
            creature->AddAura(3680, creature);
        }
        return true;
    }

    struct npc_teklaAI : public ScriptedAI
    {
        npc_teklaAI(Creature *creature) : ScriptedAI(creature)
        {
            playerOwner = NULL;
        }

        void Reset()
        {
            timerCheck = 3000;
        }

        void IsSummonedBy(Unit* owner)
        {
            me->CastSpell(me, SPELL_WATER_WALKING, true);
            me->CastSpell(owner, SPELL_WATER_WALKING, true);
            me->SetWalk(false);
            me->SetSpeed(MOVE_RUN, 1.4f, true);
            me->SetSpeed(MOVE_WALK, 1.4f, true);
            me->SetSpeed(MOVE_SWIM, 2.4f, true);
            owner->GetMotionMaster()->MoveJump(owner->GetPositionX(), owner->GetPositionY(), 17.88f, 10.0f, 10.0f, 0);
            me->GetMotionMaster()->MoveFollow(owner, 2.0f, owner->GetOrientation());
            playerOwner = owner;
        }

        void UpdateAI(uint32 diff)
        {
            if (UpdateVictim())
                return;

            if (timerCheck <= diff)
            {
                if (Creature* raggaran = me->FindNearestCreature(NPC_RAGGARAN, 7.5f, true))
                {
                    if (playerOwner && playerOwner != NULL && playerOwner->GetTypeId() == TYPEID_PLAYER)
                    {
                        playerOwner->ToPlayer()->CompleteQuest(QUEST_SPIRITS_BE_PRAISED);
                        playerOwner->ToPlayer()->KilledMonsterCredit(CREDIT_PATROL_TEKLA);
                        me->DespawnOrUnsummon(1);
                    }
                }
                timerCheck = 3000;
            }
            else
                timerCheck -= diff;
        }

    private:
        uint16 timerCheck;
        Unit* playerOwner;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_teklaAI(creature);
    }
};

class npc_misha : public CreatureScript
{
public:
    npc_misha() : CreatureScript("npc_misha") { }

    enum Id
    {
        CREDIT_PATROL_MISHA                 = 39333,
        QUEST_LOST_BUT_NOT_FORGOTTEN        = 25193
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_mishaAI (creature);
    }

    bool OnQuestReward(Player* player, Creature* /*creature*/, Quest const* quest, uint32 /*opt*/)
    {
        if (quest->GetQuestId() == QUEST_LOST_BUT_NOT_FORGOTTEN)
            player->KilledMonsterCredit(CREDIT_PATROL_MISHA);
        return true;
    }

    struct npc_mishaAI : public ScriptedAI
    {
        npc_mishaAI(Creature *c) : ScriptedAI(c) {}
    };
};

void AddSC_durotar()
{
    new npc_lazy_peon();
    new spell_voodoo();
    new npc_drowned_thunder_lizard();
    new npc_thonk();
    new npc_zentaji();
    new npc_raggaran();
    new npc_tekla();
    new npc_misha();
}
