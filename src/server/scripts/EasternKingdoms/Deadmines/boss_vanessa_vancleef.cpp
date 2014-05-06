/*
 * Copyright (C) 2012-2013 Atlantiss Server <http://www.atlantiss.pl/>
 * Copyright (C) 2012-2013 Raknar <Atlantiss Developer>
 */

#include "ScriptMgr.h"
#include "deadmines.h"
#include "Vehicle.h"

enum Spells
{
    SPELL_BACKSLASH         = 92619,
    SPELL_DEFLECTION        = 92614,
    SPELL_DEADLY_BLADES     = 92622,
    SPELL_VENGEANCE         = 95542,
    SPELL_POWDER_EXP        = 96283,
    SPELL_FIERY_BLAZE       = 93484,
    SPELL_FIERY_BLAZE_DMG   = 93485,
    SPELL_CLICK_ME          = 95527,
    // Vanessa event
    SPELL_SITTING            = 89279,
    SPELL_NOXIOUS_CONCOCTION = 92100,
    SPELL_NIGHTMARE_ELIXIR   = 92113,
    SPELL_BLACKOUT           = 92120,
    SPELL_RIDE_VEHICLE       = 46598,

    //1 Nightmare
    SPELL_EFFECT_1           = 92563,
    SPELL_ICYCLE             = 92189,
    SPELL_SPIRIT_STRIKE      = 59304,
    SPELL_SPRINT             = 92604
};

enum Events
{
    EVENT_BACKSLASH,
    EVENT_VENGEANCE,
    EVENT_DEFLECTION,
    EVENT_DEADLY_BLADES,
    EVENT_POWDER_EXP,
    EVENT_FIERY_BLAZE,
    EVENT_SHADOWGUARD,
    EVENT_SUMMON_ROPE,
    EVENT_ROPE_READY,
    EVENT_DISSAPEAR,
    EVENT_FIRE_BOOM,
    EVENT_CLEAR_SHIP
};

Position const Shadowspawn[] =
{
    {-74.61f, -822.91f, 40.22f, 6.24f},
    {-74.98f, -816.88f, 40.18f, 6.24f},
    {-76.12f, -819.95f, 40.08f, 6.24f},
};

Position const RopeSpawn [] =
{
    {-64.01f, -839.84f, 41.22f, 0},
    {-66.82f, -839.92f, 40.97f, 0},
    {-69.75f, -839.87f, 40.71f, 0},
    {-72.32f, -839.71f, 40.48f, 0},
    {-75.76f, -839.33f, 40.18f, 0},
};

class boss_vanessa_vancleef : public CreatureScript
{
public:
    boss_vanessa_vancleef() : CreatureScript("boss_vanessa_vancleef") { }


    struct boss_vanessa_vancleefAI : public BossAI
    {
        boss_vanessa_vancleefAI(Creature* creature) : BossAI(creature, DATA_VANESSA_VAN_CLEEF) { }

        void Reset()
        {
        }

        void EnterCombat(Unit* who)
        {
        }

        void JustDied(Unit* /*killer*/)
        {
        }

        void JustSummoned(Creature* summoned)
        {
            summons.Summon(summoned);
        }


        void DamageTaken(Unit* damager, uint32 & damage)
        {
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_DEFLECTION:
                        break;
                }
            }
            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_boss_vanessa_vancleef()
{
    new boss_vanessa_vancleef();
}
