/*
Script: Boss Anraphet + Event + Adds
Complete: 100%
Author: Northstrider
Todo: 
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptPCH.h"
#include "halls_of_origination.h"
#include "InstanceScript.h"

enum Texts
{
    //anraphet
    SAY_INTRO                   = 0,
    SAY_AGGRO                   = 1,
    SAY_OMEGA                   = 2,
    SAY_KILL                    = 3,
    SAY_DEATH                   = 4,
    SAY_ALPHA                   = 5,
    //Brann Bronzebeard
    SAY_INTRO_1                 = 0,
    SAY_INTRO_2                 = 1,
    SAY_INTRO_3                 = 2,
    SAY_INTRO_4                 = 3,
    SAY_INTRO_5                 = 4,
    SAY_INTRO_6                 = 5,
    SAY_INTRO_7                 = 6,
    SAY_WARDEN_KILLED_1         = 7,
    SAY_WARDEN_KILLED_2         = 8,
    SAY_WARDEN_KILLED_3         = 9,
    SAY_WARDEN_KILLED_4         = 10,
};

enum Spells
{
    //Anraphet
    SPELL_ALPHA_BEAMS_CAST      = 76184,
    SPELL_ALPHA_BEAMS_RAY       = 91210,
    SPELL_ALPHA_BEAMS_VISUAL    = 91205,
    SPELL_ALPHA_BEAMS_DUMMY     = 76907,
    ALPHA_BEAMS_TARGET          = 76912,

    SPELL_CRUMBLING_RUIN        = 75609,
    SPELL_CRUMBLING_RUIN_H      = 91206,
    SPELL_DESTRUCTION_PROTOCOL  = 77437,
    SPELL_NEMESIS_STRIKE        = 75604,
    SPELL_OMEGA_STANCE          = 75622,

    // Spell Omega Stance
    SPELL_DUMMY_VISUAL          = 77137,
    SPELL_OMEGA_STANCE_RAY      = 77121,
    SPELL_OMEGA_STANCE_AREA     = 77121,

    //Flame Warden
    SPELL_LAVA_ERUPTION         = 77273,
    SPELL_RAGING_INFERNO        = 77241,

    //Air Warden
    SPELL_WIND_SHEAR            = 77334,
    SPELL_SUMMON_WIND           = 77316,
    SPELL_WINDS_VISUAL          = 77321,

    //Earth Warden
    SPELL_IMPALE                = 77235,
    SPELL_ROCKWAVE              = 77234,

    //Water Warden
    SPELL_BUBBLE_BOUND          = 77337,
    SPELL_BUBBLE_STUN           = 77336,
};

enum Events
{
    // Anraphet
    EVENT_ALPHA_BEAMS           = 1,
    EVENT_CRUMBLING_RUIN        = 2,
    EVENT_DESTRUCTION_PROTOCOL  = 3,
    EVENT_NEMESIS_STRIKE        = 4,
    EVENT_OMEGA_STANCE          = 5,
    EVENT_CLEANUP1              = 6,
    EVENT_CLEANUP2              = 7,
    EVENT_CLEANUP3              = 8,
    EVENT_MOVE_DOWN             = 9,
    EVENT_MOVE_FIRST            = 10,
    EVENT_SUMMON_DUMMY          = 11,
    EVENT_CAST_DAMAGE           = 12,
    EVENT_CAST_RAY              = 13,
    EVENT_REMOVE                = 14,
    EVENT_INTRO_2               = 15,
    EVENT_INTRO_3               = 16,
    EVENT_INTRO_4               = 17,
    EVENT_INTRO_5               = 18,
    EVENT_INTRO_6               = 19,
    EVENT_INTRO_7               = 20,
    EVENT_TIMERUN               = 21,
    EVENT_OUTRO_1               = 22,
    EVENT_OUTRO_2               = 23,
    EVENT_BOSS_MOVE             = 24,
    EVENT_BRANN_TALK            = 25,
    EVENT_BRANN_TALK_2          = 26,
    EVENT_REMOVE_OMEGA          = 27,

    // Flame Warden
    EVENT_LAVA_ERUPTION         = 28,
    EVENT_RAGING_INFERNO        = 29,

    // Air Warden
    EVENT_WIND_SHEAR            = 30,
    EVENT_SUMMON_WHIRLING_WINDS = 31,
    EVENT_MOVE_ARROUND          = 32,
};

enum Actions
{
    ACTION_INTRO                = 0,
    ACTION_DOOR_OPEN_1          = 1,
    ACTION_DOOR_OPEN_2          = 2,
    ACTION_FINALE               = 3,
    ACTION_PAUSE                = 4,
};

enum MovePoints
{
    POINT_INTRO_1               = 1,
    POINT_INTRO_2               = 2,
    POINT_ENTRANCE              = 3,
};

enum Phases
{
    PHASE_INTRO             = 1,
    PHASE_BATTLE            = 2,
};

enum Objects
{
    //Brann
    GO_ENTRANCE                 = 202313,

    //Lights
    GO_FIRE_WARDEN_RAY          = 207662,
    GO_AIR_WARDEN_RAY           = 207663,
    GO_WATER_WARDEN_RAY         = 207664,
    GO_EARTH_WARDEN_RAY         = 207665,

    //Machines
    GO_EARTH_WARDEN_MACHINE     = 207377,
    GO_WATER_WARDEN_MACHINE     = 207376,
    GO_AIR_WARDEN_MACHINE       = 207375,
    GO_FIRE_WARDEN_MACHINE      = 207374,

    //Boss Entrance
    GO_BOSS_DOOR                = 202314,
    //GO_SUN_MIRROR               = 207726,
};

Position const Stairpos1    = {-143.308f, 366.794f, 89.760f, 3.058f};
Position const Stairpos2    = {-193.454f, 366.853f, 75.894f, 3.058f};
Position const Hallentrance = {-427.581f, 366.851f, 89.792f, 6.281f};

class boss_anraphet : public CreatureScript
{
public:
    boss_anraphet() : CreatureScript("boss_anraphet") { }

    struct boss_anraphetAI : public BossAI
    {
        boss_anraphetAI(Creature* creature) : BossAI(creature, DATA_ANRAPHET)
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_IMMUNE_TO_NPC);
            me->SetReactState(REACT_PASSIVE);
            me->setActive(true);
            wardenKilled = 0;
            introdone = false;
            instance = me->GetInstanceScript();
        }

        InstanceScript* instance;
        uint8 wardenKilled;
        bool introdone;

        void Reset()
        {
            wardenKilled = 0;
            events.Reset();
            events.SetPhase(PHASE_BATTLE);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            instance->SetBossState(DATA_ANRAPHET, NOT_STARTED);
            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_CRUMBLING_RUIN);
            if (IsHeroic())
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_CRUMBLING_RUIN_H);
            me->SetReactState(REACT_PASSIVE);
        }

        void EnterCombat(Unit* /*who*/)
        {
            if (introdone)
            {
                Talk(SAY_AGGRO);
                instance->SetBossState(DATA_ANRAPHET, IN_PROGRESS);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
                me->SetReactState(REACT_AGGRESSIVE);

                events.ScheduleEvent(EVENT_ALPHA_BEAMS, 10000, 0, PHASE_BATTLE);    // DBM
                events.ScheduleEvent(EVENT_OMEGA_STANCE, 35000, 0, PHASE_BATTLE);   // DBM
                events.ScheduleEvent(EVENT_NEMESIS_STRIKE, 30000, 0, PHASE_BATTLE); // Sniffed
            }
        }

        void KilledUnit(Unit* /*Killed*/)
        {
            if (introdone)
                Talk(SAY_KILL);
        }

        void WardenKilled()
        {
            wardenKilled++;

            if (wardenKilled == 4)
                DoAction(ACTION_INTRO);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_INTRO:
                    me->SetSpeed(MOVE_RUN, 2.0f, true);
                    events.SetPhase(PHASE_INTRO);
                    events.ScheduleEvent(EVENT_MOVE_FIRST, 21000, 0, PHASE_INTRO);
                    break;
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_INTRO_1:
                    events.ScheduleEvent(EVENT_MOVE_DOWN, 1, 0, PHASE_INTRO);
                    break;
                case POINT_INTRO_2:
                    if (!introdone )
                    {
                        Talk(SAY_INTRO);
                        events.ScheduleEvent(EVENT_CLEANUP1, 10000, 0, PHASE_INTRO);
                        SetCombatMovement(true);
                        me->SetHomePosition(Stairpos2);
                    }
                    break;
                default:
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!(events.IsInPhase(PHASE_INTRO))) // This will prevent the evade before Intro is done
                if (!UpdateVictim())
                    return;

            events.Update(diff);

            while(uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_MOVE_FIRST:
                        me->GetMotionMaster()->MovePoint(POINT_INTRO_1, Stairpos1);
                        break;
                    case EVENT_MOVE_DOWN:
                        me->GetMotionMaster()->MovePoint(POINT_INTRO_2, Stairpos2);
                        break;
                    case EVENT_CLEANUP1:
                    {
                        /*
                        me->ApplySpellImmune(0, IMMUNITY_ID, 77437, true); // Destruction Protocol immunity
                        Map::PlayerList const& player = me->GetMap()->GetPlayers();
                        for (Map::PlayerList::const_iterator itr = player.begin(); itr != player.end(); ++itr)
                            if (Player* player = itr->getSource())
                                player->ApplySpellImmune(0, IMMUNITY_ID, 77437, true);
                        */

                        events.ScheduleEvent(EVENT_CLEANUP2, 7000, 0, PHASE_INTRO);
                        break;
                    }
                    case EVENT_CLEANUP2:
                        DoCastAOE(SPELL_DESTRUCTION_PROTOCOL);
                        events.ScheduleEvent(EVENT_CLEANUP3, 10000, 0, PHASE_INTRO);
                        break;
                    case EVENT_CLEANUP3:
                        me->RemoveAllAuras();
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_IMMUNE_TO_NPC);
                        instance->DoRemoveAurasDueToSpellOnPlayers(40733);
                        events.SetPhase(PHASE_BATTLE);
                        introdone = true;
                        break;
                    case EVENT_ALPHA_BEAMS:
                        Talk(SAY_ALPHA);
                        DoCastAOE(SPELL_ALPHA_BEAMS_CAST);
                        events.ScheduleEvent(EVENT_CRUMBLING_RUIN, 18000, 0, PHASE_BATTLE);
                        events.ScheduleEvent(EVENT_NEMESIS_STRIKE, 23000, 0, PHASE_BATTLE);
                        events.ScheduleEvent(EVENT_ALPHA_BEAMS, 48000, 0, PHASE_BATTLE);
                        break;
                    case EVENT_CRUMBLING_RUIN:
                        DoCast(me->getVictim(), SPELL_CRUMBLING_RUIN);
                        break;
                    case EVENT_NEMESIS_STRIKE:
                        DoCastVictim(SPELL_NEMESIS_STRIKE);
                        events.ScheduleEvent(EVENT_NEMESIS_STRIKE, 20000, 0, PHASE_BATTLE);
                        break;
                    case EVENT_OMEGA_STANCE:
                        Talk(SAY_OMEGA);
                        DoCast(me, SPELL_OMEGA_STANCE);
                        //me->AddAura(SPELL_OMEGA_STANCE_RAY, me);
                        events.ScheduleEvent(EVENT_REMOVE_OMEGA, 8000, 0, PHASE_BATTLE);
                        events.ScheduleEvent(EVENT_CRUMBLING_RUIN, 11000, 0, PHASE_BATTLE);
                        events.ScheduleEvent(EVENT_NEMESIS_STRIKE, 16000, 0, PHASE_BATTLE);
                        events.ScheduleEvent(EVENT_OMEGA_STANCE, 48000, 0, PHASE_BATTLE);
                        break;
                    case EVENT_REMOVE_OMEGA:
                        me->RemoveAurasDueToSpell(SPELL_OMEGA_STANCE_RAY);
                        break;
                    default:
                        break;
                }
            }
            DoMeleeAttackIfReady();
        }

        void JustDied(Unit* /*who*/)
        {
            Talk(SAY_DEATH);

            if (instance)
            {
                instance->SetBossState(DATA_ANRAPHET, DONE);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_CRUMBLING_RUIN);
                if (IsHeroic())
                    instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_CRUMBLING_RUIN_H);
            }

            if (InstanceScript* instance = me->GetInstanceScript())
            {
                if (Creature* Brann = ObjectAccessor::GetCreature(*me, instance->GetData64(BOSS_BRANN)))
                {
                    Brann->AI()->DoAction(ACTION_FINALE);
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_anraphetAI(creature);
    }
};

class npc_alpha_circle : public CreatureScript
{
public:
    npc_alpha_circle() : CreatureScript("npc_alpha_circle") {}

    struct npc_alpha_circleAI : public ScriptedAI
    {
        npc_alpha_circleAI(Creature* creature) : ScriptedAI(creature) 
        {
            instance = me->GetInstanceScript();
            summoned = false;
        }

        InstanceScript* instance;
        bool summoned;

        void IsSummonedBy(Unit* /*summoner*/)
        {
            if (!summoned)
            {
                if (Creature* anraphet = me->FindNearestCreature(BOSS_ANRAPHET, 100))
                {
                    anraphet->CastStop();
                    anraphet->CastSpell(me, SPELL_ALPHA_BEAMS_RAY);
                }
                DoCastAOE(SPELL_ALPHA_BEAMS_VISUAL);
                me->setFaction(16);
                me->SetDisplayId(me->GetCreatureTemplate()->Modelid1);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_IMMUNE_TO_NPC);
                SetCombatMovement(false);
                summoned = true;
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (instance->GetBossState(DATA_ANRAPHET) == NOT_STARTED)
                me->DespawnOrUnsummon(1);

            if (instance->GetBossState(DATA_ANRAPHET) == DONE)
                me->DespawnOrUnsummon(1);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_alpha_circleAI(creature);
    }
};

class boss_brann : public CreatureScript
{
public:
    boss_brann() : CreatureScript("boss_brann_ho")
    {
        started = false;
    }

    bool started;

    bool OnGossipHello(Player* pPlayer, Creature* creature)
    {
        if (!started)
        {
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "We are ready! Go, Brann!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            pPlayer->SEND_GOSSIP_MENU(15794, creature->GetGUID());
        }
        return true;
    }

    bool OnGossipSelect(Player* pPlayer, Creature* creature, uint32 uiSender, uint32 uiAction)
    {
        pPlayer->PlayerTalkClass->ClearMenus();
        pPlayer->CLOSE_GOSSIP_MENU();
        creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);

        if (InstanceScript* instance = creature->GetInstanceScript())
        {
            if (Creature* Brann = ObjectAccessor::GetCreature(*creature, instance->GetData64(BOSS_BRANN)))
            {
                Brann->AI()->DoAction(ACTION_DOOR_OPEN_1);
                creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                started = true;
            }
        }
        return true;
    }

    struct boss_brannAI : public BossAI
    {
        boss_brannAI(Creature* creature) : BossAI(creature, DATA_BRANN)
        {
            instance = me->GetInstanceScript();
            gossipintro = false;
            timedachievement = true;
            wardenKilled = 0;
        }

        InstanceScript* instance;
        uint8 wardenKilled;
        bool timedachievement;

        void MoveInLineOfSight(Unit* who)
        {
            if (!gossipintro && me->IsWithinDistInMap(who, 20.0f))
            {
                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                me->MonsterSay("Dieses Symbol... Ich glaube, das habe ich schon mal gesehen...", LANG_UNIVERSAL, 0);
                gossipintro = true;
                timedachievement = true;
                me->setActive(true);
                wardenKilled = 0;
            }
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_DOOR_OPEN_1:
                    Talk(SAY_INTRO_1);
                    me->HandleEmoteCommand(EMOTE_STATE_USE_STANDING_NO_SHEATHE);
                    events.ScheduleEvent(EVENT_INTRO_2, 7200);
                    me->SetWalk(true);
                    break;
                case ACTION_DOOR_OPEN_2:
                {
                    GameObject* Entrance = me->FindNearestGameObject(GO_ENTRANCE, 1000);
                    if (Entrance)
                        Entrance->SetGoState(GO_STATE_ACTIVE);
                    break;
                }
                case ACTION_PAUSE:
                {
                    GameObject* Door = me->FindNearestGameObject(GO_BOSS_DOOR, 5000);
                    if (Door)
                        Door->SetGoState(GO_STATE_ACTIVE);

                    GameObject* Mirror = me->FindNearestGameObject(GO_SUN_MIRROR, 5000);
                    if (Mirror)
                        Mirror->SetGoState(GO_STATE_ACTIVE);
                    break;
                }
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_ENTRANCE:
                    Talk(SAY_INTRO_3);
                    events.ScheduleEvent(EVENT_INTRO_4, 14000);
                    break;
                default:
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while(uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_INTRO_2:
                        Talk(SAY_INTRO_2);
                        me->HandleEmoteCommand(EMOTE_STATE_STAND);
                        events.ScheduleEvent(EVENT_INTRO_3, 2000);
                        DoAction(ACTION_DOOR_OPEN_2);
                        break;
                    case EVENT_INTRO_3:
                        me->GetMotionMaster()->MovePoint(POINT_ENTRANCE, Hallentrance);
                        timedachievement = 0;
                        events.ScheduleEvent(EVENT_TIMERUN, 300000);
                        break;
                    case EVENT_INTRO_4:
                        Talk(SAY_INTRO_4);
                        events.ScheduleEvent(EVENT_INTRO_5, 6000);
                        break;
                    case EVENT_INTRO_5:
                        Talk(SAY_INTRO_5);
                        events.ScheduleEvent(EVENT_INTRO_6, 6000);
                        break;
                    case EVENT_INTRO_6:
                        Talk(SAY_INTRO_6);
                        events.ScheduleEvent(EVENT_INTRO_7, 6000);
                        break;
                    case EVENT_INTRO_7:
                        Talk(SAY_INTRO_7);
                        break;
                    case EVENT_TIMERUN:
                        timedachievement = false;
                        break;
                    case EVENT_BRANN_TALK:
                        DoAction(ACTION_PAUSE);
                        events.ScheduleEvent(EVENT_BRANN_TALK_2,5000);
                        break;
                    case EVENT_BRANN_TALK_2:
                        Talk(SAY_WARDEN_KILLED_4);
                        break;
                }
            }
        }

        void WardenKilled()
        {
            wardenKilled++;

            if (wardenKilled == 1)
                Talk(SAY_WARDEN_KILLED_1);

            if (wardenKilled == 2)
                Talk(SAY_WARDEN_KILLED_2);

            if (wardenKilled == 3)
                Talk(SAY_WARDEN_KILLED_3);

            if (wardenKilled == 4)
            {
                events.ScheduleEvent(EVENT_BRANN_TALK, 10000);

                if (IsHeroic())
                    if (timedachievement)
                        instance->DoCompleteAchievement(5296);
            }
        }
    private:
        bool gossipintro;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_brannAI(creature);
    }
};

class boss_flame_warden : public CreatureScript
{
public:
    boss_flame_warden() : CreatureScript("boss_flame_warden") { }

    struct boss_flame_wardenAI : public CreatureAI
    {
        boss_flame_wardenAI(Creature* creature) : CreatureAI(creature)
        {
            instance = me->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void Reset()
        {
            events.Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_LAVA_ERUPTION, 10000);
            events.ScheduleEvent(EVENT_RAGING_INFERNO, 14000);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            while(uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_LAVA_ERUPTION:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                            DoCast(target, SPELL_LAVA_ERUPTION);
                        events.ScheduleEvent(EVENT_LAVA_ERUPTION, 10000);
                        break;
                    case EVENT_RAGING_INFERNO:
                        DoCastAOE(SPELL_RAGING_INFERNO);
                        events.ScheduleEvent(EVENT_RAGING_INFERNO, 20000);
                }
            }

            DoMeleeAttackIfReady();
        }

        void JustDied(Unit* /*who*/)
        {
            if (Creature *anraphet = me->FindNearestCreature(BOSS_ANRAPHET, 1000, true))
                if (boss_anraphet::boss_anraphetAI* pAI = CAST_AI(boss_anraphet::boss_anraphetAI, anraphet->AI()))
                    pAI->WardenKilled();

            if (Creature *brann = me->FindNearestCreature(BOSS_BRANN, 1500, true))
                if (boss_brann::boss_brannAI* pAI = CAST_AI(boss_brann::boss_brannAI, brann->AI()))
                    pAI->WardenKilled();

            instance->SetData(DATA_FIRE_WARDEN, DONE);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_flame_wardenAI(creature);
    }
};

class boss_air_warden : public CreatureScript
{
public:
    boss_air_warden() : CreatureScript("boss_air_warden") { }

    struct boss_air_wardenAI : public CreatureAI
    {
        boss_air_wardenAI(Creature* creature) : CreatureAI(creature)
        {
            instance = me->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void Reset()
        {
            events.Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_WIND_SHEAR, 11000);
            events.ScheduleEvent(EVENT_SUMMON_WHIRLING_WINDS, 10000);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            while(uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_WIND_SHEAR:
                        if (Unit* target = (SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true)))
                            DoCast(target, SPELL_WIND_SHEAR);
                        events.ScheduleEvent(EVENT_WIND_SHEAR, 10000);
                        break;
                    case EVENT_SUMMON_WHIRLING_WINDS:
                        DoCastAOE(SPELL_SUMMON_WIND);
                        events.ScheduleEvent(EVENT_SUMMON_WHIRLING_WINDS, 20000);
                        break;
                }
            }
            DoMeleeAttackIfReady();
        }

        void JustDied(Unit* /*who*/)
        {
            if (Creature *anraphet = me->FindNearestCreature(BOSS_ANRAPHET, 1000, true))
                if (boss_anraphet::boss_anraphetAI* pAI = CAST_AI(boss_anraphet::boss_anraphetAI, anraphet->AI()))
                    pAI->WardenKilled();

            if (Creature *brann = me->FindNearestCreature(BOSS_BRANN, 1500, true))
                if (boss_brann::boss_brannAI* pAI = CAST_AI(boss_brann::boss_brannAI, brann->AI()))
                    pAI->WardenKilled();

            instance->SetData(DATA_AIR_WARDEN, DONE);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_air_wardenAI(creature);
    }
};

class npc_ho_whirling_wind : public CreatureScript
{
public:
    npc_ho_whirling_wind() : CreatureScript("npc_ho_whirling_wind") { }

    struct npc_ho_whirling_windAI : public CreatureAI
    {
        npc_ho_whirling_windAI(Creature* creature) : CreatureAI(creature)
        {
            instance = me->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void IsSummonedBy(Unit* summoner)
        {
            me->SetReactState(REACT_PASSIVE);
            me->setFaction(16);
            events.ScheduleEvent(EVENT_MOVE_ARROUND, 1);
            DoCastAOE(SPELL_WINDS_VISUAL);
            me->SetDisplayId(me->GetCreatureTemplate()->Modelid1);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_IMMUNE_TO_NPC);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while(uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_MOVE_ARROUND:
                        me->SetSpeed(MOVE_RUN, 0.9f);
                        if (Player* target = me->FindNearestPlayer(100.0f, true))
                            me->GetMotionMaster()->MovePoint(0, target->GetPositionX(), target->GetPositionY(), target->GetPositionZ());
                        events.ScheduleEvent(EVENT_MOVE_ARROUND, 1000);
                        break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_ho_whirling_windAI(creature);
    }
};

class boss_earth_warden : public CreatureScript
{
public:
    boss_earth_warden() : CreatureScript("boss_earth_warden") { }

    struct boss_earth_wardenAI : public CreatureAI
    {
        boss_earth_wardenAI(Creature* creature) : CreatureAI(creature)
        {
            instance = me->GetInstanceScript();
        }

        InstanceScript* instance;

        uint32 RockTimer;
        uint32 ImpaleTimer;

        void Reset()
        {
        }

        void EnterCombat(Unit* /*who*/)
        {
            RockTimer = 10000;
            ImpaleTimer = 5000;
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (RockTimer <= diff)
            {
                if (Unit* target = (SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true)))
                    DoCast(target, SPELL_WIND_SHEAR);
                RockTimer = 20000+rand()%7500;
            }
            else
                RockTimer -= diff;

            if (ImpaleTimer <= diff)
            {
                DoCast(me->getVictim(), SPELL_WIND_SHEAR);
                ImpaleTimer = 7500+rand()%7500;
            }
            else
                ImpaleTimer -= diff;

            DoMeleeAttackIfReady();
        }

        void JustDied(Unit* /*who*/)
        {
            if (Creature* anraphet = me->FindNearestCreature(BOSS_ANRAPHET, 1000, true))
                if (boss_anraphet::boss_anraphetAI* pAI = CAST_AI(boss_anraphet::boss_anraphetAI, anraphet->AI()))
                    pAI->WardenKilled();

            if (Creature* brann = me->FindNearestCreature(BOSS_BRANN, 1500, true))
                if (boss_brann::boss_brannAI* pAI = CAST_AI(boss_brann::boss_brannAI, brann->AI()))
                    pAI->WardenKilled();

            instance->SetData(DATA_EARTH_WARDEN, DONE);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_earth_wardenAI(creature);
    }
};

class boss_water_warden : public CreatureScript
{
public:
    boss_water_warden() : CreatureScript("boss_water_warden") { }

    struct boss_water_wardenAI : public CreatureAI
    {
        boss_water_wardenAI(Creature* creature) : CreatureAI(creature)
        {
            instance = me->GetInstanceScript();
        }

        InstanceScript* instance;

        uint32 BubbleTimer;

        void Reset()
        {
            BubbleTimer = 5000;
        }

        void EnterCombat(Unit* /*who*/)
        {
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (BubbleTimer <= diff)
            {
                if (Unit *target = (SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true)))
                    DoCast(target, SPELL_BUBBLE_BOUND);
                BubbleTimer = 15000+rand()%7500;
            }
            else
                BubbleTimer -= diff;

            DoMeleeAttackIfReady();
        }

        void JustDied(Unit* /*who*/)
        {
            if (Creature *anraphet = me->FindNearestCreature(BOSS_ANRAPHET, 1000, true))
                if (boss_anraphet::boss_anraphetAI* pAI = CAST_AI(boss_anraphet::boss_anraphetAI, anraphet->AI()))
                    pAI->WardenKilled();

            if (Creature *brann = me->FindNearestCreature(BOSS_BRANN, 1500, true))
                if (boss_brann::boss_brannAI* pAI = CAST_AI(boss_brann::boss_brannAI, brann->AI()))
                    pAI->WardenKilled();

            instance->SetData(DATA_WATER_WARDEN, DONE);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_water_wardenAI(creature);
    }
};

void AddSC_boss_anraphet()
{
    new boss_anraphet();
    new npc_alpha_circle();
    new boss_flame_warden();
    new boss_air_warden();
    new npc_ho_whirling_wind();
    new boss_earth_warden();
    new boss_water_warden();
    new boss_brann();
}
