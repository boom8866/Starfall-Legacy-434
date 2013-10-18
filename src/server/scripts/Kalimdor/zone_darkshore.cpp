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

class npc_darkscale_priestess : public CreatureScript
{
public:
    npc_darkscale_priestess() : CreatureScript("npc_darkscale_priestess") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_darkscale_priestessAI(creature);
    }

    struct npc_darkscale_priestessAI : public ScriptedAI
    {
        npc_darkscale_priestessAI(Creature* creature) : ScriptedAI(creature) {}

        enum Id
        {
            // Npc
            NPC_DARKSCALE_PRIESTESS = 34415,
            NPC_QUEEN_AZSHARA       = 34416,

            // Spells
            SPELL_FROSTBOLT         = 9672,
            SPELL_FROST_NOVA        = 75062,

            // Timers
            TIMER_QUEEN_DESPAWN     = 60000,
            TIMER_CAST_FROSTBOLT    = 4000,
            TIMER_CAST_FROST_NOVA   = 9500
        };

        void Reset()
        {
            timerFrostBolt = TIMER_CAST_FROSTBOLT;
            timerFrostNova = TIMER_CAST_FROST_NOVA;
        }

        void JustDied(Unit* /*victim*/)
        {
            Unit* darkscalePriestess = me->FindNearestCreature(NPC_DARKSCALE_PRIESTESS, 200.0f, true);
            if (!darkscalePriestess)
                me->SummonCreature(NPC_QUEEN_AZSHARA, 4598.72f, 889.15f, 40.71f, 2.39f);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (Unit* target = me->getVictim())
            {
                if (timerFrostBolt <= diff)
                {
                    DoCast(target, SPELL_FROSTBOLT);
                    timerFrostBolt = TIMER_CAST_FROSTBOLT;
                }
                else
                    timerFrostBolt -= diff;

                if (timerFrostNova <= diff)
                {
                    if (me->IsInRange(target, 0.5f, 0.10f, false))
                        DoCast(target, SPELL_FROST_NOVA);
                    timerFrostNova = TIMER_CAST_FROST_NOVA;
                }
                else
                    timerFrostNova -= diff;
            }

            DoMeleeAttackIfReady();
        }

    private:
        uint16 timerFrostBolt;
        uint16 timerFrostNova;

    };
};

void AddSC_darkshore()
{
    new npc_darkscale_priestess();
}
