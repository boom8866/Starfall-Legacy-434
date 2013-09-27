
#include "ScriptPCH.h"
#include "Unit.h"
#include "ScriptedEscortAI.h"
#include "Vehicle.h"

/*
    Gnome Starting Zone
*/

/*
 *  @Npc   : Sanitron 500 (46185)
 *  @Quest : Decontamination (27635)
 *  @Descr : Board the Sanitron 500 to begin the decontamination process.
 */

enum NpcSanotron500
{
    SAY_CONTAMINATION_START     = 0,
    SAY_CONTAMINATION_3         = 1,
    SAY_CONTAMINATION_OVERLOAD  = 2,

    SAY_UGH_NOT_THIS            = 0,
    SAY_OH_NO                   = 1,
    
    NPC_DECONTAMINATION_BUNNY   = 46165,
    NPC_CLEAN_CANNON            = 46208,
    NPC_SAFE_TECHNICAN          = 46230,

    SPELL_DECONTAMINATION_STAGE_1       = 86075,
    SPELL_DECONTAMINATION_STAGE_2       = 86084,
    SPELL_DECONTAMINATION_STAGE_3       = 86086,
    SPELL_DECONTAMINATION_STAGE_2_ALT   = 86098,
    SPELL_DECONTAMINATION               = 86106,
    SPELL_CLEAN_CANNON_CLEAN_BURST      = 86080,
    SPELL_IRRADIATED                    = 80653,
    SPELL_EXPLOSION                     = 30934,
};

class DistanceSelector
{
    public:
        DistanceSelector(Unit* source, uint32 const distance) : _source(source), _distance(distance) {}

        bool operator()(Creature* creature)
        {
            return _source->GetDistance(creature) > _distance;
        }

    private:
        Unit* _source;
        uint32 const _distance;
};

class npc_sanotron_500 : public CreatureScript
{
public:
    npc_sanotron_500() : CreatureScript("npc_sanotron_500") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->IsActiveQuest(27635))
        {
            player->EnterVehicle(creature, 0);
            return true;
        }
        return true;
    }

    struct npc_sanotron_500AI : public npc_escortAI
    {
        npc_sanotron_500AI(Creature* creature) : npc_escortAI(creature) {}

        void Reset()
        {
            Position const& pos = me->GetHomePosition();
            me->NearTeleportTo(pos.m_positionX, pos.m_positionY, pos.m_positionZ, pos.m_orientation);
        }

        void PassengerBoarded(Unit* who, int8 /*seatId*/, bool apply)
        {
            if (who->GetTypeId() != TYPEID_PLAYER || !apply)
                return;

            Start(false, true, who->GetGUID());
            Talk(SAY_CONTAMINATION_START);
        }

        void OnCharmed(bool /*apply*/) {}

        void WaypointReached(uint32 point)
        {
            Player* player = GetPlayerForEscort();

            switch(point)
            {
            case 2:
                HandleStop(NPC_DECONTAMINATION_BUNNY, 10, SPELL_DECONTAMINATION_STAGE_1);
                break;
            case 3:
                TechnicanTalk(SAY_UGH_NOT_THIS);
                HandleStop(NPC_CLEAN_CANNON, 35, SPELL_CLEAN_CANNON_CLEAN_BURST);
                me->CastSpell(player, SPELL_DECONTAMINATION_STAGE_2, true);
                player->RemoveAura(SPELL_IRRADIATED);
                break;
            case 4:
                Talk(SAY_CONTAMINATION_3);
                HandleStop(NPC_DECONTAMINATION_BUNNY, 10, SPELL_DECONTAMINATION_STAGE_3);
                break;
            case 5:
                Talk(SAY_CONTAMINATION_OVERLOAD);
                DoCast(SPELL_EXPLOSION);
                me->DespawnOrUnsummon(1500);
                TechnicanTalk(SAY_OH_NO);
                break;
            }
        }

    private:
        void HandleStop(uint32 const entry, uint32 const distance, uint32 const spellId)
        {
            Player* player = GetPlayerForEscort();
            if (!player)
                return;

            std::list<Creature*> creatures;
            GetCreatureListWithEntryInGrid(creatures, me, entry, float(distance + 3));
            creatures.remove_if(DistanceSelector(me, distance));

            for (std::list<Creature*>::const_iterator itr = creatures.begin(); itr != creatures.end(); ++itr)
                (*itr)->CastSpell(player, spellId, true);
        }

        void TechnicanTalk(uint32 const groupId)
        {
            if (Creature* technican = me->FindNearestCreature(NPC_SAFE_TECHNICAN, 20.f))
                technican->AI()->Talk(groupId);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_sanotron_500AI (creature);
    }
};

class npc_wounded_infantry : public CreatureScript
{
public:
    npc_wounded_infantry() : CreatureScript("npc_wounded_infantry") { }

    struct npc_wounded_infantryAI : public ScriptedAI
    {
        npc_wounded_infantryAI(Creature* creature) : ScriptedAI(creature) {}

        enum Spells
        {
            SPELL_FLASH_HEAL    = 2061
        };

        enum Quests
        {
            QUEST_THE_ARTS_OF_A_PRIEST = 26200
        };

        enum Credits
        {
            QUEST_CREDIT_WOUNDED_INFANTRY = 44175
        };

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            if (caster->GetTypeId() == TYPEID_PLAYER)
            {
                switch (spell->Id)
                {
                    case 2061: // Flash Heal
                        if (caster->ToPlayer()->GetQuestStatus(QUEST_THE_ARTS_OF_A_PRIEST) != QUEST_STATUS_COMPLETE)
                            caster->ToPlayer()->KilledMonsterCredit(QUEST_CREDIT_WOUNDED_INFANTRY);
                        break;
                    default:
                        break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_wounded_infantryAI (creature);
    }
};

void AddSC_dun_morogh()
{
    new npc_sanotron_500();
    new npc_wounded_infantry();
}
