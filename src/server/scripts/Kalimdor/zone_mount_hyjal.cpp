#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptPCH.h"
#include "ScriptedEscortAI.h"
#include "Vehicle.h"

/*
Hyjal Zone Scripts
Author: NorthStrider
Complete: 3%
Supported Quests:
-25551 (The Fire Lord) WIP
-
-
Todo:
---Fire Lord Quest:
-implement add summoning
-implement lava wave rushing
-implement outro
-correct quest complete

Notes:
Coords (3964.029, -2847.486, 615.50, 1)
It's located under the Sulfuron Peak
*/

//##############################################################################
// RAGNAROS END QUEST (The Fire Lord)                                         #
//#############################################################################

enum RagnarosQuest
{
    QUEST_THE_FIRELORD  = 25551,
};

enum RagnarosEventSay
{
    //Ragnaros
    SAY_ARRIVE          = 0, // soundID 22574
    SAY_AGGRO           = 1, // soundID 22575
    SAY_LAVA_WAVE_1     = 2, // soundID 22576
    SAY_LAVA_WAVE_2     = 3, // soundID 22577
    SAY_SUMMON_1        = 4, // soundID 22578
    SAY_SUMMON_2        = 5, // soundID 22579
    SAY_UNK             = 6, // soundID 22580 -> need to find out when he say that
    SAY_DEATH           = 7, // soundID 22581

    //Cenarius
    SAY_CEN_INTRO_1     = 1, // soundID 21639
    SAY_CEN_INTRO_2     = 2, // soundID 21641
    SAY_CEN_INTRO_3     = 3, // soundID 21642
    SAY_CEN_ENCOUNTER   = 4, // soundID 21640

    //Malfurion
    SAY_MAL_INTRO       = 1, // soundID 20805
    SAY_MAL_ATTACK      = 2, // soundID 20806
    SAY_MAL_OUTRO       = 3, // soundID 20807

    //Amuul
    SAY_AMU_INTRO       = 1,
    SAY_AMU_ATTACK      = 2,
    SAY_AMU_OUTRO       = 3,
};

enum RagnarosCreatures
{
    //Mainchars
    NPC_RAGNAROS        = 41634,
    NPC_CENARIUS        = 41631,
    NPC_MALFURION       = 41632,
    NPC_HAMUUL          = 40805,

    //Misc
    NPC_FIREWALL        = 40859,
    NPC_TSUNAMI         = 40938,
};

enum RagnarosSpells
{
    //Ragnaros
    BERSERK                 = 64238,
    MAGMA_STRIKE            = 76380,
    SEARING_FLAME           = 76246,

    //Cenarius
    COLD_OF_ICECROWN_AURA   = 76395,
    COLD_OF_ICECROWN_CAST   = 76251,
    COLD_OF_CENARIUS_RAY    = 76253,

    //Malfurion
    FURY_OF_THE_STORM       = 76232,

    //Hamuul
    EARTH_RAGE              = 95724,

    //Flame Tsunami
    //FLAME_TSUNAMI_DMG       = 76430,
    //FLAME_TSUNAMI_VISUAL    = 57494,
    //FLAME_TSUNAMI_KNOCK     = 60241,

    SPELL_FLAME_TSUNAMI                         = 57494,
    SPELL_FLAME_TSUNAMI_LEAP                    = 60241,
    SPELL_FLAME_TSUNAMI_DMG_AURA                = 57491,
};

enum RangnarosActions
{
    ACTION_EMERGE               = 1,
    ACTION_START_ENCOUNTER      = 2,
    ACTION_MOVE_MALFURION       = 3,
    ACTION_MOVE_HAMUUL          = 4,
    ACTION_CAST_HAM             = 12,
    ACTION_CANCEL_HAM           = 13,
    ACTION_CAST_MALF            = 14,
    ACTION_CANCEL_MALF          = 15,
};

enum CenariusActions
{
    ACTION_START        = 1,
    ACTION_FREEZE       = 2,
    ACTION_STAIR_MALF   = 3,
    ACTION_STAIR_HAM    = 4,
    ACTION_PLAT_MALF    = 5,
    ACTION_PLAT_HAM     = 6,
};

enum RagnarosEvents
{
    EVENT_TALK_2        = 1,
    EVENT_START         = 2,
    EVENT_ATTACK_EMOTE  = 3,
    EVENT_SUBMERGE      = 4,
    EVENT_EMERGE        = 5,
    EVENT_LAVA_WAVE     = 6,
};

Position const Portalentrance       = {3944.640f, -2809.877f, 618.748f, 5.071f};
Position const Malfurionentrance    = {3942.408f, -2832.650f, 618.748f, 4.608f};
Position const Hamuulentrance       = {3961.329f, -2825.724f, 618.748f, 5.597f};
//Stairs and Waypoints
Position const Hamuulwp1            = {3999.122f, -2916.101f, 598.991f, 4.907f};
Position const Hamuulwp2            = {4012.394f, -2983.431f, 575.785f, 4.871f};
Position const Hamuulwp3            = {4054.438f, -3011.446f, 575.390f, 5.546f};
Position const Hamuulwp4            = {4075.202f, -3031.875f, 580.764f, 5.378f};
Position const Hamuulwp5            = {4090.057f, -3049.111f, 582.538f, 3.273f};
Position const Malfurionwp1         = {3980.785f, -2915.647f, 600.174f, 5.027f};
Position const Malfurionwp2         = {3997.865f, -2986.944f, 575.916f, 5.178f};
Position const Malfurionwp3         = {3984.026f, -3035.833f, 575.390f, 4.516f};
Position const Malfurionwp4         = {3976.727f, -3061.502f, 580.593f, 4.343f};
Position const Malfurionwp5         = {3978.036f, -3086.519f, 582.538f, 0.525f};
//Flame Tsunami Waypoints
Position const Tsunamispawn1        = {4101.128f, -3145.802f, 571.806f, 1.658f};
Position const Tsunamiwp1_1         = {4066.274f, -2949.773f, 571.807f, 1.890f};

Position const Tsunamispawn2        = {4000.850f, -3159.903f, 571.806f, 1.801f};
Position const Tsunamiwp2_1         = {3939.807f, -2991.081f, 570.281f, 2.087f};

Position const Tsunamispawn3        = {4038.387f, -3128.361f, 571.806f, 1.824f};
Position const Tsunamiwp3_1         = {3988.388f, -2993.367f, 571.806f, 1.824f};

Position const Tsunamispawn4        = {4065.915f, -3122.088f, 571.806f, 1.824f};
Position const Tsunamiwp4_1         = {4023.090f, -2975.569f, 576.460f, 1.824f};

enum Tsunapoints
{
    POINT_TSUNA_1_1     = 15,
    POINT_TSUNA_1_2     = 16,

    POINT_TSUNA_2_1     = 17,
    POINT_TSUNA_2_2     = 18,

    POINT_TSUNA_3_1     = 19,
    POINT_TSUNA_3_2     = 20,

    POINT_TSUNA_4_1     = 21,
    POINT_TSUNA_4_2     = 22,
};

class npc_ragnaros : public CreatureScript
{
public:
    npc_ragnaros() : CreatureScript("npc_ragnaros_mh") { }

    struct npc_ragnarosAI : public ScriptedAI
    {
        npc_ragnarosAI(Creature* creature) : ScriptedAI(creature)
        {
            SetCombatMovement(false);
            //me->HandleEmoteCommand(EMOTE_ONESHOT_SUBMERGE);
            DoCastAOE(37550);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_NOT_SELECTABLE);
            me->setActive(true);
            me->SetMaxHealth(22339500);
            arrived = 0;
            win = 0;
            started = 0;
        }

        EventMap events;
        uint8 arrived;
        uint8 win;
        uint8 started;

        void Reset()
        {
            DoCastAOE(37550);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_NOT_SELECTABLE);
            arrived = 0;
            win = 0;
            events.Reset();
        }

        void Emerge()
        {
            me->HandleEmoteCommand(EMOTE_ONESHOT_EMERGE);
            me->RemoveAurasDueToSpell(37550);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_NOT_SELECTABLE);

            if (Creature* malf = me->FindNearestCreature(NPC_MALFURION, 500))
                if (malf)
                    malf->AI()->DoAction(ACTION_CAST_MALF);

            if (Creature* ham = me->FindNearestCreature(NPC_HAMUUL, 500))
                if (ham)
                    ham->AI()->DoAction(ACTION_CAST_HAM);
        }

        void Submerge()
        {
            DoCastAOE(37550);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_NOT_SELECTABLE);

            if (Creature* malf = me->FindNearestCreature(NPC_MALFURION, 500))
                if (malf)
                    malf->AI()->DoAction(ACTION_CANCEL_MALF);

            if (Creature* ham = me->FindNearestCreature(NPC_HAMUUL, 500))
                if (ham)
                    ham->AI()->DoAction(ACTION_CANCEL_HAM);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_EMERGE:
                    Arrive();
                    me->SetHealth(22339500);
                    break;
                case ACTION_START_ENCOUNTER:
                    {
                        events.ScheduleEvent(EVENT_TALK_2, 2000);
                    }
                    break;
                default:
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {

            if (me->HealthBelowPct(5))
            {
                if (started == 1)
                {
                    if (win == 0)
                    {
                        Submerge();
                        me->PlayDirectSound(22581);
                        me->MonsterYell("IHR HABT NUR DAS UNAUSWEICHLICHE VERZOEGERT, CENARIUS! IN DEN FEUERLANDEN WERDEN MEINE ARMEEN NEU GEBOREN!", LANG_UNIVERSAL, 0);
                        win = 1;
                        events.CancelEvent(EVENT_SUBMERGE);

                        if (Player* plr = me->FindNearestPlayer(500))
                            if (plr)
                                plr->CompleteQuest(QUEST_THE_FIRELORD);
                    }
                }
            }

            events.Update(diff);

            while(uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_TALK_2:
                        me->MonsterYell("STELLT EUCH, INSEKTEN. ICH WERDE EUCH EIGENHAENDIG ZERQUETSCHEN!", LANG_UNIVERSAL, 0);
                        me->PlayDistanceSound(22575);
                        events.ScheduleEvent(EVENT_START, 5000);
                        break;
                    case EVENT_START:
                        {
                            Creature* cenarius = me->FindNearestCreature(NPC_CENARIUS, 500);
                            if (cenarius)
                            {
                                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_NPC_FLAG_GOSSIP);
                                me->Attack(cenarius, false);
                                events.ScheduleEvent(EVENT_ATTACK_EMOTE, 1);
                                cenarius->AI()->DoAction(ACTION_FREEZE);
                            }
                            events.ScheduleEvent(EVENT_SUBMERGE, 25000);
                            started = 1;
                        }
                        break;
                    case EVENT_ATTACK_EMOTE:
                        {
                            me->HandleEmoteCommand(EMOTE_ONESHOT_ATTACK1H);
                            events.ScheduleEvent(EVENT_ATTACK_EMOTE, 100);
                        }
                        break;
                    case EVENT_SUBMERGE:
                        Submerge();
                        events.CancelEvent(EVENT_ATTACK_EMOTE);
                        events.ScheduleEvent(EVENT_EMERGE, 10000);
                        events.ScheduleEvent(EVENT_LAVA_WAVE, 1);
                        break;
                    case EVENT_EMERGE:
                        Emerge();
                        events.ScheduleEvent(EVENT_SUBMERGE, 25000);
                        events.ScheduleEvent(EVENT_ATTACK_EMOTE, 2000);
                        break;
                    case EVENT_LAVA_WAVE:
                        switch (urand(0, 1))
                        {
                            case 0:
                                {
                                    Creature* tsuna1 = me->SummonCreature(NPC_TSUNAMI, Tsunamispawn1, TEMPSUMMON_TIMED_DESPAWN, 12000);
                                    tsuna1->GetMotionMaster()->MovePoint(0, Tsunamiwp1_1);
                                    Creature* tsuna2 = me->SummonCreature(NPC_TSUNAMI, Tsunamispawn2, TEMPSUMMON_TIMED_DESPAWN, 12000);
                                    tsuna2->GetMotionMaster()->MovePoint(0, Tsunamiwp2_1);
                                    me->MonsterYell("BRENNT IN FLUESSIGEN FLAMMEN!", LANG_UNIVERSAL, 0);
                                    me->PlayDirectSound(22577);
                                    break;
                                }
                            case 1:
                                {
                                    Creature* tsuna3 = me->SummonCreature(NPC_TSUNAMI, Tsunamispawn3, TEMPSUMMON_TIMED_DESPAWN, 12000);
                                    tsuna3->GetMotionMaster()->MovePoint(0, Tsunamiwp3_1);
                                    Creature* tsuna4 = me->SummonCreature(NPC_TSUNAMI, Tsunamispawn4, TEMPSUMMON_TIMED_DESPAWN, 12000);
                                    tsuna4->GetMotionMaster()->MovePoint(0, Tsunamiwp4_1);
                                    me->MonsterYell("BADET IN DEN FLAMMEN!", LANG_UNIVERSAL, 0);
                                    me->PlayDirectSound(22576);
                                    break;
                                }
                        }
                }
            }
        }

        void Arrive()
        {
            if (arrived == 0)
            {
                me->HandleEmoteCommand(EMOTE_ONESHOT_EMERGE);
                me->RemoveAurasDueToSpell(37550);
                me->MonsterYell("WER WAGT ES, DIE HALLEN DER LEBENDEN FLAMMEN ZU ENTWEIHEN? ICH BRENNE EURE ESSENZ AUS EUREM FLEISCH!", LANG_UNIVERSAL, 0);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                me->PlayDistanceSound(22574);
                arrived = 1;
            }
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_ragnarosAI(creature);
    }
};

enum CenrariusEvents
{
    EVENT_TALK_INTRO_1  = 1,
    EVENT_TALK_INTRO_2  = 2,
    EVENT_TALK_INTRO_3  = 3,
    EVENT_MOVE_1        = 4,
    EVENT_MOVE_2        = 5,
    EVENT_MOVE_3        = 6,
};

Position const Ragnapos1        = {3989.109f, -2915.699f, 599.376f, 4.970f};
Position const Ragnapos2        = {4006.934f, -2987.435f, 575.448f, 5.000f};
Position const Ragnapos3        = {4019.379f, -3030.759f, 575.300f, 5.018f};

enum CenariusPoints
{
    POINT_DOWN_1        = 1,
    POINT_DOWN_2        = 2,
    POINT_MOVE_1        = 3,
    POINT_MALF_1        = 4,
    POINT_HAM_1         = 5,
    POINT_MALF_2        = 6,
    POINT_MALF_3        = 8,
    POINT_MALF_4        = 9,
    POINT_MALF_5        = 10,
    POINT_HAM_2         = 7,
    POINT_HAM_3         = 11,
    POINT_HAM_4         = 12,
    POINT_HAM_5         = 13,
};

class npc_cenarius : public CreatureScript
{
public:
    npc_cenarius() : CreatureScript("npc_cenarius_mh") {}

    struct npc_cenariusAI : public ScriptedAI
    {
        npc_cenariusAI(Creature* creature) : ScriptedAI(creature) 
        {
            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            me->setActive(true);
            me->SetHealth(22339500);
        }

        EventMap events;

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_START:
                    {
                        me->MonsterSay("Sobald Hamuul und Malfurion eingetroffen sind, werden wir beginnen...", LANG_UNIVERSAL, 0);
                        me->SummonCreature(NPC_HAMUUL, Portalentrance, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3000);
                        me->SummonCreature(NPC_MALFURION, Portalentrance, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3000);
                        events.ScheduleEvent(EVENT_TALK_INTRO_1, 12000);
                    }
                    break;
                case ACTION_FREEZE:
                    {
                        Creature* ragnaros = me->FindNearestCreature(NPC_RAGNAROS, 500);
                        if (ragnaros)
                            DoCast(ragnaros, COLD_OF_ICECROWN_CAST);
                    }
                    break;
                default:
                    break;
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_DOWN_1:
                    events.ScheduleEvent(EVENT_MOVE_2, 1);
                    break;
                case POINT_DOWN_2:
                    {
                        events.ScheduleEvent(EVENT_MOVE_3, 10000);
                        Creature* ragnaros = me->FindNearestCreature(NPC_RAGNAROS, 500.0f);
                        if (ragnaros)
                            ragnaros->AI()->DoAction(ACTION_EMERGE);
                    }
                    break;
                case POINT_MOVE_1:
                    Creature* ragnaros = me->FindNearestCreature(NPC_RAGNAROS, 500);
                    if (ragnaros)
                        ragnaros->AI()->DoAction(ACTION_START_ENCOUNTER);
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
                    case EVENT_TALK_INTRO_1:
                        me->MonsterSay("Wir werden uns dem Feuerlord stellen und nicht ruhen, bis auch sein letzter Funke aus dieser Welt vertrieben ist!", LANG_UNIVERSAL, 0);
                        me->PlayDistanceSound(21639);
                        events.ScheduleEvent(EVENT_TALK_INTRO_2, 10000);
                        break;
                    case EVENT_TALK_INTRO_2:
                        me->MonsterSay("Ich werde die eisigen Bergwinde anrufen, uns vor Ragnaros' Flammen zu beschuetzen. Malfurion und Hamuul durchbrechen seine Verteidigung, so koennen wir ihn zuruecktreiben.", LANG_UNIVERSAL, 0);
                        me->PlayDistanceSound(21641);
                        events.ScheduleEvent(EVENT_TALK_INTRO_3, 14500);
                        break;
                    case EVENT_TALK_INTRO_3:
                        me->MonsterSay("Lasst uns beginnen. Es wird nicht lange dauern, bis unsere Anweisenheit dem Feuerlord auffaellt und er die Spitze verteidigt.", LANG_UNIVERSAL, 0);
                        me->PlayDistanceSound(21642);
                        events.ScheduleEvent(EVENT_MOVE_1, 7000);
                        break;
                    case EVENT_MOVE_1:
                        me->GetMotionMaster()->MovePoint(POINT_DOWN_1, Ragnapos1);
                        if (Creature* malf = me->FindNearestCreature(NPC_MALFURION, 500))
                            if (malf)
                                malf->AI()->DoAction(ACTION_STAIR_MALF);

                        if (Creature* ham = me->FindNearestCreature(NPC_HAMUUL, 500))
                            if (ham)
                                ham->AI()->DoAction(ACTION_STAIR_HAM);
                        break;
                    case EVENT_MOVE_2:
                        me->GetMotionMaster()->MovePoint(POINT_DOWN_2, Ragnapos2);
                        break;
                    case EVENT_MOVE_3:
                        me->GetMotionMaster()->MovePoint(POINT_MOVE_1, Ragnapos3);
                        me->MonsterYell("Schnell! Alle auf ihre Positionen! Treibt ihn zurueck in die Feuerlande!", LANG_UNIVERSAL, 0);
                        me->PlayDistanceSound(21640);
                        if (Creature* malf = me->FindNearestCreature(NPC_MALFURION, 500))
                            if (malf)
                                malf->AI()->DoAction(ACTION_PLAT_MALF);

                        if (Creature* ham = me->FindNearestCreature(NPC_HAMUUL, 500))
                            if (ham)
                                ham->AI()->DoAction(ACTION_PLAT_HAM);
                        break;
                    default:
                        break;
                }
            }
        }
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Ich bin bereit, mich in die Schlacht gegen Ragnaros zu stuerzen.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
        player->SEND_GOSSIP_MENU(1, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 uiSender, uint32 uiAction)
    {
        player->PlayerTalkClass->ClearMenus();
        player->CLOSE_GOSSIP_MENU();
        creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        CAST_AI(npc_cenariusAI, creature->AI())->DoAction(ACTION_START);
        return true;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_cenariusAI(creature);
    }
};

enum Stairevents
{
    EVENT_MALF_MOVE_1       = 1,
    EVENT_MALF_MOVE_2       = 2,
    EVENT_MALF_MOVE_3       = 3,
    EVENT_MALF_MOVE_4       = 4,
    EVENT_HAM_MOVE_1        = 5,
    EVENT_HAM_MOVE_2        = 6,
    EVENT_HAM_MOVE_3        = 7,
    EVENT_HAM_MOVE_4        = 8,
    EVENT_FURY              = 9,
    EVENT_EARTH             = 10,
};

class npc_malfurion : public CreatureScript
{
public:
    npc_malfurion() : CreatureScript("npc_malfurion_mh") {}

    struct npc_malfurionAI : public ScriptedAI
    {
        npc_malfurionAI(Creature* creature) : ScriptedAI(creature) 
        {
        }

        EventMap events;

        void IsSummonedBy(Unit* /*summoner*/)
        {
            me->setActive(true);
            me->GetMotionMaster()->MovePoint(POINT_MALF_1, Malfurionentrance);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_STAIR_MALF:
                    me->GetMotionMaster()->MovePoint(POINT_MALF_2, Malfurionwp1);
                    break;
                case ACTION_PLAT_MALF:
                    me->GetMotionMaster()->MovePoint(POINT_MALF_3, Malfurionwp3);
                    break;
                case ACTION_CANCEL_MALF:
                    events.CancelEvent(EVENT_FURY);
                    me->RemoveAurasDueToSpell(FURY_OF_THE_STORM);
                    break;
                case ACTION_CAST_MALF:
                    events.ScheduleEvent(EVENT_FURY, 1);
                    break;
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_MALF_1:
                    me->MonsterSay("Wir sind bereit, Cenarius.", LANG_UNIVERSAL, 0);
                    me->PlayDirectSound(20805);
                    break;
                case POINT_MALF_2:
                    events.ScheduleEvent(EVENT_MALF_MOVE_1, 1);
                    break;
                case POINT_MALF_3:
                    events.ScheduleEvent(EVENT_MALF_MOVE_2, 1);
                    break;
                case POINT_MALF_4:
                    events.ScheduleEvent(EVENT_MALF_MOVE_3, 1);
                    break;
                case POINT_MALF_5:
                    events.ScheduleEvent(EVENT_FURY, 1);
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
                    case EVENT_MALF_MOVE_1:
                        me->GetMotionMaster()->MovePoint(POINT_MALF_2, Malfurionwp2);
                        break;
                    case EVENT_MALF_MOVE_2:
                        me->GetMotionMaster()->MovePoint(POINT_MALF_4, Malfurionwp4);
                        break;
                    case EVENT_MALF_MOVE_3:
                        me->GetMotionMaster()->MovePoint(POINT_MALF_5, Malfurionwp5);
                        break;
                    case EVENT_FURY:
                        if (Creature* ragna = me->FindNearestCreature(NPC_RAGNAROS, 1000))
                            if (ragna)
                                DoCast(ragna, FURY_OF_THE_STORM);

                        events.ScheduleEvent(EVENT_FURY, 3000);
                        break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_malfurionAI(creature);
    }
};

class npc_hamuul : public CreatureScript
{
public:
    npc_hamuul() : CreatureScript("npc_hamuul_mh") {}

    struct npc_hamuulAI : public ScriptedAI
    {
        npc_hamuulAI(Creature* creature) : ScriptedAI(creature) 
        {
        }

        EventMap events;

        void IsSummonedBy(Unit* /*summoner*/)
        {
            me->setActive(true);
            me->GetMotionMaster()->MovePoint(POINT_HAM_1, Hamuulentrance);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_STAIR_HAM:
                    me->GetMotionMaster()->MovePoint(POINT_HAM_2, Hamuulwp1);
                    break;
                case ACTION_PLAT_HAM:
                    me->GetMotionMaster()->MovePoint(POINT_HAM_3, Hamuulwp3);
                    break;
                case ACTION_CANCEL_HAM:
                    events.CancelEvent(EVENT_EARTH);
                    me->RemoveAurasDueToSpell(EARTH_RAGE);
                    break;
                case ACTION_CAST_HAM:
                    events.ScheduleEvent(EVENT_EARTH, 1);
                    break;
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_HAM_2:
                    events.ScheduleEvent(EVENT_HAM_MOVE_1, 1);
                    break;
                case POINT_HAM_3:
                    events.ScheduleEvent(EVENT_HAM_MOVE_2, 1);
                    break;
                case POINT_HAM_4:
                    events.ScheduleEvent(EVENT_HAM_MOVE_3, 1);
                    break;
                case POINT_HAM_5:
                    events.ScheduleEvent(EVENT_EARTH, 1);
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
                    case EVENT_HAM_MOVE_1:
                        me->GetMotionMaster()->MovePoint(POINT_HAM_2, Hamuulwp2);
                        break;
                    case EVENT_HAM_MOVE_2:
                        me->GetMotionMaster()->MovePoint(POINT_HAM_4, Hamuulwp4);
                        break;
                    case EVENT_HAM_MOVE_3:
                        me->GetMotionMaster()->MovePoint(POINT_HAM_5, Hamuulwp5);
                        break;
                    case EVENT_EARTH:
                        if (Creature* ragna = me->FindNearestCreature(NPC_RAGNAROS, 1000))
                            if (ragna)
                                DoCast(ragna, EARTH_RAGE);

                        events.ScheduleEvent(EVENT_EARTH, 3000);
                        break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_hamuulAI(creature);
    }
};

enum Tsunaevents
{
    EVENT_TSUNA_WP_1_1  = 1,
    EVENT_TSUNA_WP_1_2  = 2,

    EVENT_TSUNA_WP_2_1  = 3,
    EVENT_TSUBA_WP_2_2  = 4,

    EVENT_TSUNA_WP_3_1  = 5,
    EVENT_TSUBA_WP_3_2  = 6,

    EVENT_TSUNA_WP_4_1  = 7,
    EVENT_TSUBA_WP_4_2  = 8,
};

class npc_flame_tsunami2 : public CreatureScript    // Beacause npc flame tsunami  is already used in sartharions script
{
public:
    npc_flame_tsunami2() : CreatureScript("npc_flame_tsunami_mh") {}

    struct npc_flame_tsunami2AI : public ScriptedAI
    {
        npc_flame_tsunami2AI(Creature* creature) : ScriptedAI(creature) 
        {
        }

        EventMap events;

        void IsSummonedBy(Unit* /*summoner*/)
        {
            me->SetDisplayId(11686);
            me->AddAura(SPELL_FLAME_TSUNAMI, me);
            //me->SetSpeed(MOVE_FLIGHT, 3.0f);
            //me->SetSpeed(MOVE_RUN, 1.5f);
            me->setActive(true);
            me->SetCanFly(true);
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            //switch (pointId)
            //{
            //}
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            //while(uint32 eventId = events.ExecuteEvent())
            //{
            //    switch (eventId)
            //    {
            //    }
            //}
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_flame_tsunami2AI(creature);
    }
};

//##############################################################################

/*
 *  @Npc   : Twilight Proveditor (39436)
 *  @Quest : End of the Supply Line (25233)
 *  @Descr : Slay 4 Twilight Proveditors at Wolf's Run in Hyjal.
 */

enum NpcTwilightProveditor
{
    NPC_TWILIGHT_PROVEDITOR  = 39436,
    NPC_TWILIGHT_SLAVE       = 39431,
    NPC_TWILIGHT_SLAVEDRIVER = 39438,
    SPELL_SUMMON_SUPPLIES    = 73959,
    POINT_LAST               = 52
};

class npc_twilight_proveditor : public CreatureScript
{
public:
    npc_twilight_proveditor() : CreatureScript("npc_twilight_proveditor") { }

    struct npc_twilight_proveditorAI : public npc_escortAI
    {
        npc_twilight_proveditorAI(Creature* creature) : npc_escortAI(creature), summons(creature) {}

        void IsSummonedBy(Unit* who)
        {
            for (uint8 i = 0; i < 3; ++i)
                if (Creature* slave = me->SummonCreature(NPC_TWILIGHT_SLAVE, *me))
                {
                    slave->GetMotionMaster()->MoveFollow(me, (i == 1) ? 2.f : 1.3f, (i + 1) * 90.f);
                    summons.push_back(slave->GetGUID());
                }

            if (Creature* slaveDriver = me->SummonCreature(NPC_TWILIGHT_SLAVEDRIVER, *me))
            {
                slaveDriver->GetMotionMaster()->MoveFollow(me, 5.f, 0.f);
                summons.push_back(slaveDriver->GetGUID());
            }

            double distance = 200.;
            uint32 pointId = POINT_LAST;
            ScriptPointVector const& waypoints = sScriptSystemMgr->GetPointMoveList(me->GetEntry());
            for (ScriptPointVector::const_iterator itr = waypoints.begin(); itr != waypoints.end(); ++itr)
            {
                double const dc = me->GetDistance(itr->fX, itr->fY, itr->fZ);
                if (dc < distance)
                {
                    distance = dc;
                    pointId = itr->uiPointId;
                }
            }

            SetNextWaypoint(pointId, false, false);
            Start(true, false, 0, NULL, false, false, false);
        }

        void WaypointReached(uint32 point)
        {
            if (point == POINT_LAST)
            {
                summons.DespawnAll();
                me->DespawnOrUnsummon();
            }
        }

        void JustDied(Unit* /*killer*/)
        {
            for (SummonList::const_iterator itr = summons.begin(); itr != summons.end(); ++itr)
                if (Creature* creature = me->GetCreature(*me, *itr))
                {
                    if (creature->GetEntry() == NPC_TWILIGHT_SLAVE)
                    {
                        creature->RemoveAllAuras();
                        creature->AI()->DoCast(SPELL_SUMMON_SUPPLIES);
                        creature->GetMotionMaster()->MoveRandom(20.f);
                        creature->DespawnOrUnsummon(15000);
                    }
                    else
                        creature->DespawnOrUnsummon(40000);
                }
        }

    private:
        SummonList summons;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_twilight_proveditorAI (creature);
    }
};

// 73972 Check for a Proveditor
class spell_check_for_proveditor : public SpellScriptLoader
{
    public:
        spell_check_for_proveditor() : SpellScriptLoader("spell_check_for_proveditor") { }

        class spell_check_for_proveditor_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_check_for_proveditor_SpellScript);

            void HandleAfterCast()
            {
                if (!GetCaster()->FindNearestCreature(NPC_TWILIGHT_PROVEDITOR, 40.f, true))
                    GetCaster()->SummonCreature(NPC_TWILIGHT_PROVEDITOR, *GetCaster(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 40000);
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_check_for_proveditor_SpellScript::HandleAfterCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_check_for_proveditor_SpellScript();
        }
};

/*
 *  @Spell : Weakening (75192)
 *  @Quest : The Return of Baron Geddon (25464)
 *  @Descr : Channel the Flameseer's Staff to weaken Baron Geddon.
 */

enum TheReturnOfBaronGeddon
{
    NPC_BARON_GEDDON_KILLCREDTIT = 40334
};

class spell_mount_hyjal_weakening : public SpellScriptLoader
{
    public:
        spell_mount_hyjal_weakening() : SpellScriptLoader("spell_mount_hyjal_weakening") { }

        class spell_mount_hyjal_weakening_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_mount_hyjal_weakening_AuraScript);

            bool Load()
            {
                return GetCaster()->GetTypeId() == TYPEID_PLAYER;
            }

            void HandlePeriodicTick(AuraEffect const* /*aurEff*/)
            {
                PreventDefaultAction();
                if (Unit* caster = GetCaster())
                    caster->ToPlayer()->KilledMonsterCredit(NPC_BARON_GEDDON_KILLCREDTIT);
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_mount_hyjal_weakening_AuraScript::HandlePeriodicTick, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_mount_hyjal_weakening_AuraScript();
        }
};

/*
 *  @Npc   : Aronus (39128)
 *  @Quest : As Hyjal Burns (25316)
 *  @Descr : Fly to Hyjal using Aronus and speak to Ysera once you're there.
 */

enum NpcAronus
{
    SAY_NO_IT_CANT_BE           = 0,
    SAY_FEEL_DEATHWING          = 1,
    SAY_FIRELORD_HAS_RISEN      = 2,

    NPC_ARONUS                  = 39128,
    NPC_RAGNAROS_AS_HYJAL       = 38806,
    NPC_DEATHWING_AS_HYJAL      = 39867,
    NPC_HYJAL_INTRO_CAMERA      = 54309,

    SPELL_HYJAL_INTRO_TELE      = 73519,
    SPELL_ARONUS_RIDE           = 76649,
    SPELL_PATACHUTE             = 44795,
    SPELL_FLAME_BREATH          = 92815,
    SPELL_SUMMON_RAGAROS        = 74436,

    SUM_PROP_ARONUS             = 827,

    ZONE_ID_MOUNT_HYJAL         = 616,
};

class npc_aronus : public CreatureScript
{
public:
    npc_aronus() : CreatureScript("npc_aronus") { }

    class AronusControllerEvent : public BasicEvent
    {
        public:
            AronusControllerEvent(Player* player) : _player(player) {}

            bool Execute(uint64 execTime, uint32 /*diff*/)
            {
                if (_player->GetZoneId() == ZONE_ID_MOUNT_HYJAL && !_player->IsBeingTeleported())
                {
                    if (CreatureTemplate const* ct = sObjectMgr->GetCreatureTemplate(NPC_ARONUS))
                        if (Creature* creature = _player->SummonCreature(ct->Entry, *_player, TEMPSUMMON_MANUAL_DESPAWN, 0, ct->VehicleId, sSummonPropertiesStore.LookupEntry(SUM_PROP_ARONUS)))
                        {
                            _player->RemoveAura(SPELL_ARONUS_RIDE);
                            _player->RemoveAura(SPELL_PATACHUTE);
                            _player->CastSpell(creature, SPELL_ARONUS_RIDE, TRIGGERED_FULL_MASK);
                        }

                    return true;
                }
                else
                {
                    _player->m_Events.AddEvent(this, execTime + 100);
                    return false;
                }
            }

        private:
            Player* _player;
    };

    struct npc_aronusAI : public npc_escortAI
    {
        npc_aronusAI(Creature* creature) : npc_escortAI(creature) {}

        void PassengerBoarded(Unit* who, int8 /*seatId*/, bool apply)
        {
            if (who->GetTypeId() != TYPEID_PLAYER || !apply)
                return;

            if (me->GetZoneId() == ZONE_ID_MOUNT_HYJAL)
            {
                SetNextWaypoint(4, false, false);
                Start(false, true, who->GetGUID(), NULL, false, false, false);
                SetDespawnAtEnd(false);
                SetSpeed(3.2f);
            }
            else
            {
                SetSpeed(2.f);
                Start(false, true, who->GetGUID());
                SetDespawnAtEnd(true);
            }
        }

        void OnCharmed(bool /*apply*/) {}

        void WaypointReached(uint32 point)
        {
            switch (point)
            {
                case 3:  // Teleport to Mount Hyjal
                {
                    if (Player* player = GetPlayerForEscort())
                    {
                        player->m_Events.AddEvent(new AronusControllerEvent(player), me->m_Events.CalculateTime(200));
                        player->CastSpell(player, SPELL_HYJAL_INTRO_TELE, TRIGGERED_FULL_MASK);
                        player->SetCanFly(true);
                    }
                    break;
                }
                case 6:  // Talk 0
                    Talk(SAY_NO_IT_CANT_BE);
                    break;
                case 11: // Talk 1
                    Talk(SAY_FEEL_DEATHWING);
                    break;
                case 13: // Start "Deathwing revives Ragnaros" Event
                {
                    if (Player* player = GetPlayerForEscort())
                    {
                        if (Creature* deathwing = player->FindNearestCreature(NPC_DEATHWING_AS_HYJAL, 250.f))
                            deathwing->CastSpell(deathwing, SPELL_FLAME_BREATH, true);

                        player->CastWithDelay(1500, player, SPELL_SUMMON_RAGAROS, true);
                    }
                    break;
                }
                case 14: // Talk 2
                    Talk(SAY_FIRELORD_HAS_RISEN);
                    SetSpeed(4.5f);
                    break;
                case 34:
                    SetSpeed(1.5f);
                    break;
                case 42: // Remove Player
                {
                    SetSpeed(3.f);
                    if (Vehicle* vehicle = me->GetVehicleKit())
                    {
                        if (me->GetVehicleKit()->GetPassenger(0))
                            me->GetVehicleKit()->GetPassenger(0)->SetCanFly(false);
                        vehicle->RemoveAllPassengers();
                    }
                    break;
                }
                case 45:
                    me->DespawnOrUnsummon();
                    break;
            }
        }

    private:
        void SetSpeed(float const speed)
        {
            for (uint32 i = 0; i < MAX_MOVE_TYPE; ++i)
                me->SetSpeed(UnitMoveType(i), speed);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_aronusAI (creature);
    }
};

class npc_aronus_desperiona_event : public CreatureScript
{
public:
    npc_aronus_desperiona_event() : CreatureScript("npc_aronus_desperiona_event") {}

    struct npc_aronus_desperiona_eventAI : public ScriptedAI
    {
        npc_aronus_desperiona_eventAI(Creature* creature) : ScriptedAI(creature) {playerCharmer = NULL;}

        EventMap events;

        enum Id
        {
            NPC_ENTRY_DESPERIONA    = 40974,
            NPC_ENTRY_AVIANA        = 40982
        };

        enum pointId
        {
            ARONUS_POINT_1 = 1
        };

        enum actionId
        {
            ACTION_SUMMON_DESPERIONA = 1,
            ACTION_TALK_MAGIC
        };

        void IsSummonedBy(Unit* summoner)
        {
            me->GetMotionMaster()->MovePoint(ARONUS_POINT_1, 3765.65f, -3231.24f, 980.50f, false);
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
            me->AI()->TalkWithDelay(1000, 0, summoner->GetGUID());
            me->DespawnOrUnsummon(180000);
            playerCharmer = summoner;
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_SUMMON_DESPERIONA:
                {
                    // Charmer will summon Desperiona
                    playerCharmer->SummonCreature(NPC_ENTRY_DESPERIONA, 3809.14f, -3179.13f, 1000.77f, 4.15f);
                    me->AI()->TalkWithDelay(12000, 1, playerCharmer->GetGUID());
                    break;
                }
                default:
                    break;
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case ARONUS_POINT_1:
                    me->AI()->DoAction(ACTION_SUMMON_DESPERIONA);
                    break;
                default:
                    break;
            }
        }

    protected:
        Unit* playerCharmer;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_aronus_desperiona_eventAI(creature);
    }
};

class npc_desperiona_event : public CreatureScript
{
public:
    npc_desperiona_event() : CreatureScript("npc_desperiona_event") {}

    struct npc_desperiona_eventAI : public ScriptedAI
    {
        npc_desperiona_eventAI(Creature* creature) : ScriptedAI(creature) {playerCharmer = NULL;}

        EventMap events;

        enum Id
        {
            NPC_ENTRY_AVIANA        = 40982,
            SPELL_WINDS_OF_AVIANA   = 76531
        };

        enum pointId
        {
            DESPERIONA_POINT_1 = 1
        };

        enum actionId
        {
            ACTION_SUMMON_AVIANA        = 1,
            ACTION_DO_WINDS_OF_AVIANA
        };

        void IsSummonedBy(Unit* summoner)
        {
            me->GetMotionMaster()->MovePoint(DESPERIONA_POINT_1, 3783.30f, -3232.56f, 977.68f, false);
            me->AI()->TalkWithDelay(1500, 0, summoner->GetGUID());
            me->DespawnOrUnsummon(180000);
            playerCharmer = summoner;
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_SUMMON_AVIANA:
                {
                    // Charmer will summon Aviana
                    playerCharmer->SummonCreature(NPC_ENTRY_AVIANA, 3780.48f, -3248.37f, 983.77f, 1.23f);
                    break;
                }
                case ACTION_DO_WINDS_OF_AVIANA:
                {
                    me->CastSpell(me, SPELL_WINDS_OF_AVIANA, true);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, 67142400);
                    break;
                }
                default:
                    break;
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case DESPERIONA_POINT_1:
                    me->AI()->DoAction(ACTION_SUMMON_AVIANA);
                    break;
                default:
                    break;
            }
        }

    protected:
        Unit* playerCharmer;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_desperiona_eventAI(creature);
    }
};

class npc_aviana_event : public CreatureScript
{
public:
    npc_aviana_event() : CreatureScript("npc_aviana_event") {}

    struct npc_aviana_eventAI : public ScriptedAI
    {
        npc_aviana_eventAI(Creature* creature) : ScriptedAI(creature) {playerCharmer = NULL;}

        EventMap events;

        enum Id
        {
            NPC_ENTRY_DESPERIONA    = 40974
        };

        void IsSummonedBy(Unit* summoner)
        {
            if (Creature* desperiona = me->FindNearestCreature(NPC_ENTRY_DESPERIONA, 100.0f, true))
                desperiona->AI()->DoAction(2);
            me->AI()->TalkWithDelay(1000, 0, summoner->GetGUID());
            me->AI()->TalkWithDelay(35000, 1, summoner->GetGUID());
            me->DespawnOrUnsummon(180000);
            playerCharmer = summoner;
        }

    protected:
        Unit* playerCharmer;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_aviana_eventAI(creature);
    }
};

void AddSC_mount_hyjal()
{
    new npc_ragnaros();
    new npc_cenarius();
    new npc_malfurion();
    new npc_hamuul();
    new npc_flame_tsunami2();
    new npc_twilight_proveditor();
    new spell_check_for_proveditor();
    new spell_mount_hyjal_weakening();
    new npc_aronus();
    new npc_aronus_desperiona_event();
    new npc_desperiona_event();
    new npc_aviana_event();
}
