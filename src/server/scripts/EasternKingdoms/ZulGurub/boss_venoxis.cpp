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

#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "Spell.h"
#include "zulgurub.h"

enum Yells
{
    SAY_AGGRO               = 0,
    SAY_BLOODVENOM          = 1, // ID - 96842 Venomous Effusion
    SAY_TRANSFROM           = 2, // ID - 97354 Blessing of the Snake God
    SAY_WORD_OF_HETHISS     = 3, // ID - 96560 Word of Hethiss
    EMOTE_BLOODVENOM        = 4, // ID - 96842 Bloodvenom
    EMOTE_VENOM_WITHDRAWAL  = 5, // ID - 96653 Venom Withdrawal
    SAY_PLAYER_KILL         = 6,
    SAY_DEATH               = 7
};

enum Spells
{
    // Venoxis

    // Totems
    SPELL_VENOM_TOTEM_BEAM_LEFT     = 96536,
    SPELL_VENOM_TOTEM_BEAM_RIGHT    = 96537,
    SPELL_VENOM_TOTEM               = 96534,

    SPELL_WORD_OF_HETHISS           = 96560,
    SPELL_WHISPER_OF_HETHIS         = 96466,

    SPELL_TOXIC_LINK                = 96475,

    SPELL_BLESSING_OF_THE_SNAKE_GOD = 96512,
    SPELL_POOL_OF_ACRID_TEARS       = 96515,
    SPELL_BREATH_OF_HETHISS         = 96509,
    SPELL_TRANSFORM_REMOVAL_PRIMER  = 96617,
    SPELL_BLOOD_VENOM               = 96842, // Resize to 3 target
    SPELL_VENOMOUS_WITHDRAWAL       = 96653,

    // Bloodvenom
    SPELL_BLOOD_VENOM_VISUAL        = 97110,
    SPELL_VENOM_TOTAM_BEAM_CENTER   = 97098,
    SPELL_BLOOD_VENOM_TRIGGER       = 97099,

    // Venomous Effusion Stalker
    SPELL_VENOMOUS_EFFUSION_TRIGGER = 96678,

    // Venomous Effusion
    SPELL_VENOMOUS_EFFUSION         = 96681,
};

enum Events
{
};

Position const venomousEffusionStalkerPos[] =
{
    { -12013.51f, -1684.175f, 32.36689f, 2.490533f },
    { -12003.96f, -1698.644f, 32.36689f, 5.730771f },
};

class boss_venoxis : public CreatureScript
{
    public:
        boss_venoxis() : CreatureScript("boss_venoxis") { }

        struct boss_venoxisAI : public BossAI
        {
            boss_venoxisAI(Creature* creature) : BossAI(creature, DATA_VENOXIS) { }

            void Reset()
            {
                _Reset();
            }

            void EnterCombat(Unit* /*who*/)
            {
                _EnterCombat();
                Talk(SAY_AGGRO);
            }

            void JustDied(Unit* /*killer*/)
            {
                _JustDied();
                Talk(SAY_DEATH);
            }

            void KilledUnit(Unit* victim)
            {
                if (victim->GetTypeId() == TYPEID_PLAYER)
                    Talk(SAY_PLAYER_KILL);
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;
            /*
                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        default:
                            break;
                    }
                }
            */

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return GetZulGurubAI<boss_venoxisAI>(creature);
        }
};

void AddSC_boss_venoxis()
{
    new boss_venoxis();
}
