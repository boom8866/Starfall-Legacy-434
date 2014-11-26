/*
 * Copyright (C) 2014 NorthStrider
 */

#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "PassiveAI.h"
#include "SpellScript.h"
#include "MoveSplineInit.h"
#include "Cell.h"
#include "CellImpl.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "lost_city_of_the_tolvir.h"

enum Texts
{
    SAY_AGGRO   = 0,
    SAY_PHASE_2 = 1,
    SAY_SLAY    = 2,
    SAY_DEATH   = 3,
};

enum Spells
{
    // Barim
    SPELL_HEAVENS_FURY_SUMMON           = 81939,
    SPELL_SUMMON_BLAZE_OF_THE_HEAVENS   = 91180,
    SPELL_SUMMON_BLAZE_DUMMY            = 91181,
    SPELL_FIFTY_LASHINGS                = 82506,
    SPELL_PLAGUE_OF_AGES                = 82622,

    // Repenteance
    SPELL_REPENTEANCE_GROUND            = 82320,
    SPELL_REPENTEANCE_PULL              = 82168,
    SPELL_REPENTEANCE_STUN              = 81947, // Triggers 81958 = summon npc
    SPELL_REPENTEANCE_IMAGE_SUMMON      = 81958, // triggered by knockback
    SPELL_REPENTEANCE_KNOCKBACK         = 82012,
    SPELL_REPENTEANCE_SCREEN_EFFECT     = 82139, 

    SPELL_WAIL_OF_DARKNES               = 82195, // castet at the same time as knockback
    SPELL_VAIL_OF_DARKNES_AURA          = 82197,
    SPELL_VAIL_OF_DARKNES_SUMMON        = 82203, // summons harbringer of darknes

    // Repenteance Dummy
    SPELL_REPENTEANCE_SCRIPT            = 82009, // Triggers 81961 which clones the summoner
    SPELL_REPENTEANCE_CLONE             = 81961,
    SPELL_REPENTEANCE_CLONE_WEAPON      = 81960,
    SPELL_REPENTEANCE_PULL_SPRIRIT      = 82430, // Yay, we're back in body :)
    // SPELL_COPY_WEAPON                = 69893, // Not needed for now

    // Heavens Fury
    SPELL_HEAVENS_FURY_VISUAL           = 81940,
    SPELL_HEAVENS_FURY_AURA             = 81941,

    // Blaze of the Heaven
    SPELL_BLAZE_SUMMON_VISUAL           = 91179,
    SPELL_BLAZE_OF_THE_HEAVENS          = 95248,
    SPELL_SUMMON_BLAZE_FIRE_DUMMY       = 91185,
    SPELL_BLAZE_FIRE_AURA               = 91195,

    // Harbinger of Darkness
    SPELL_WAIL_OF_DARKNESS_DAMAGE       = 82533,
    SPELL_SOUL_SEVER_AURA               = 82255,

    // Soul Fragment
    SPELL_SOUL_FRAGMENT_COPY            = 82219,
    SPELL_MERGED_SOUL                   = 82263,
};

enum Events
{
    // High Prophet Barim
    EVENT_SUMMON_BLAZE_OF_THE_HEAVENS = 1,
    EVENT_FIFTY_LASHINGS,
    EVENT_PLAGUE_OF_AGES,
    EVENT_HEAVENS_FURY,

    EVENT_REPENTANCE_CAST,
    EVENT_REPENTANCE_PULL,
    EVENT_REPENTANCE_STUN,
    EVENT_REPENTANCE_KNOCKBACK,
    EVENT_REPENTANCE_TALK,

    // Blaze of the Heavens
    EVENT_SUMMON_BLAZE,
    EVENT_SUMMON_HARBRINGER,
    EVENT_ATTACK,
    EVENT_REGENERATE,
    EVENT_CHECK_HP,

    // General
    EVENT_CHECK_BARIM,

    // Harbinger of Darkness
    EVENT_WAIL_OF_DARKNESS,
    EVENT_SOUL_SEVER,
    EVENT_MOVE,
};

enum Actions
{
    ACTION_RELEASE_SPIRITS = 1,
};

enum Models
{
    MODEL_EGG       = 20245,
    MODEL_PHOENIX   = 19682,
};

class boss_high_prophet_barim : public CreatureScript
{
public:
    boss_high_prophet_barim() : CreatureScript("boss_high_prophet_barim") { }

    struct boss_high_prophet_barimAI : public BossAI
    {
        boss_high_prophet_barimAI(Creature* creature) : BossAI(creature, DATA_HIGH_PROPHET_BARIM)
        {
            _repentanceCasted = false;
        }

        void Reset()
        {
            _repentanceCasted = false;
        }

        bool _repentanceCasted;

        void EnterCombat(Unit* /*who*/)
        {
            Talk(SAY_AGGRO);
            _EnterCombat();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            events.ScheduleEvent(EVENT_HEAVENS_FURY, 8000);
            events.ScheduleEvent(EVENT_PLAGUE_OF_AGES, 8000);
            events.ScheduleEvent(EVENT_FIFTY_LASHINGS, 9500);
            if (IsHeroic())
                events.ScheduleEvent(EVENT_SUMMON_BLAZE_OF_THE_HEAVENS, 10000);
        }

        void JustDied(Unit* /*killer*/)
        {
            Talk(SAY_DEATH);
            _JustDied();
            me->DespawnCreaturesInArea(NPC_BLAZE_FIRE_DUMMY, 500.0f);
            me->DespawnCreaturesInArea(NPC_SOUL_FRAGMENT, 500.0f);
            me->DespawnCreaturesInArea(NPC_REPENTEANCE_IMAGE, 500.0f);
            me->DespawnCreaturesInArea(NPC_HEAVENS_FURY, 500.0f);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_REPENTEANCE_SCREEN_EFFECT);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            events.Reset();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            me->GetMotionMaster()->MoveTargetedHome();
            me->DespawnCreaturesInArea(NPC_BLAZE_FIRE_DUMMY, 500.0f);
            me->DespawnCreaturesInArea(NPC_SOUL_FRAGMENT, 500.0f);
            me->DespawnCreaturesInArea(NPC_REPENTEANCE_IMAGE, 500.0f);
            me->DespawnCreaturesInArea(NPC_HEAVENS_FURY, 500.0f);
            me->SetReactState(REACT_AGGRESSIVE);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_REPENTEANCE_SCREEN_EFFECT);
            _repentanceCasted = false;
        }

        void JustSummoned(Creature* summon)
        {
            switch (summon->GetEntry())
            {
                case NPC_BLAZE_DUMMY:
                    summons.Summon(summon);
                    break;
            }
        }

        void DamageTaken(Unit* /*attacker*/, uint32& /*damage*/)
        {
            if (me->HealthBelowPct(50) && !_repentanceCasted)
            {
                me->CastStop();
                me->AttackStop();
                me->SetReactState(REACT_PASSIVE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
                me->GetMotionMaster()->MovementExpired();
                events.ScheduleEvent(EVENT_REPENTANCE_CAST, 1);
                _repentanceCasted = true;
            }
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_RELEASE_SPIRITS:
                {
                    // Tempfix
                    events.ScheduleEvent(EVENT_ATTACK, 1500);
                    DoCastAOE(SPELL_REPENTEANCE_PULL);
                    me->RemoveAurasDueToSpell(SPELL_REPENTEANCE_GROUND);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
                    instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_REPENTEANCE_SCREEN_EFFECT);
                    events.ScheduleEvent(EVENT_HEAVENS_FURY, 8000);
                    events.ScheduleEvent(EVENT_PLAGUE_OF_AGES, 8000);
                    events.ScheduleEvent(EVENT_FIFTY_LASHINGS, 9500);
                    if (IsHeroic())
                        events.ScheduleEvent(EVENT_SUMMON_BLAZE_OF_THE_HEAVENS, 10000);
                    break;
                }
                default:
                    break;
            }
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
                    case EVENT_HEAVENS_FURY:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                            DoCast(target, SPELL_HEAVENS_FURY_SUMMON);
                        events.ScheduleEvent(EVENT_HEAVENS_FURY, 75000);
                        break;
                    case EVENT_PLAGUE_OF_AGES:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                            DoCast(target, SPELL_PLAGUE_OF_AGES);
                        events.ScheduleEvent(EVENT_PLAGUE_OF_AGES, 75000);
                        break;
                    case EVENT_FIFTY_LASHINGS:
                        DoCastAOE(SPELL_FIFTY_LASHINGS);
                        break;
                    case EVENT_SUMMON_BLAZE_OF_THE_HEAVENS:
                        if (!me->FindNearestCreature(NPC_BLAZE_OF_HEAVENS, 500.0, true))
                            DoCastAOE(SPELL_SUMMON_BLAZE_DUMMY);
                        events.ScheduleEvent(EVENT_SUMMON_BLAZE_OF_THE_HEAVENS, 1000);
                        break;
                    case EVENT_REPENTANCE_CAST:
                        events.Reset();
                        me->GetMotionMaster()->MovementExpired();
                        DoCastAOE(SPELL_REPENTEANCE_GROUND);
                        events.ScheduleEvent(EVENT_REPENTANCE_PULL, 3000);  
                        break;
                    case EVENT_REPENTANCE_PULL:
                        DoCastAOE(SPELL_REPENTEANCE_PULL);
                        events.ScheduleEvent(EVENT_REPENTANCE_TALK, 200);
                        events.ScheduleEvent(EVENT_REPENTANCE_STUN, 1200);
                        break;
                    case EVENT_REPENTANCE_TALK:
                        Talk(SAY_PHASE_2);
                        break;
                    case EVENT_REPENTANCE_STUN:
                        DoCastAOE(SPELL_REPENTEANCE_STUN);
                        events.ScheduleEvent(EVENT_REPENTANCE_KNOCKBACK, 6000);
                        break;
                    case EVENT_REPENTANCE_KNOCKBACK:
                        DoCastAOE(SPELL_REPENTEANCE_KNOCKBACK);
                        DoCastAOE(SPELL_REPENTEANCE_SCREEN_EFFECT);
                        DoCastAOE(SPELL_WAIL_OF_DARKNES);
                        break;
                    case EVENT_ATTACK:
                        me->RemoveAllAuras();
                        me->SetReactState(REACT_AGGRESSIVE);
                        me->DespawnCreaturesInArea(NPC_REPENTEANCE_IMAGE, 500.0f);
                        break;
                    default:
                        break;
                }
            }
            DoMeleeAttackIfReady();
        }
    
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_high_prophet_barimAI(creature);
    }
};

class npc_lct_blaze_of_the_heavens : public CreatureScript
{
    public:
        npc_lct_blaze_of_the_heavens() :  CreatureScript("npc_lct_blaze_of_the_heavens") { }

        struct npc_lct_blaze_of_the_heavensAI : public ScriptedAI
        {
            npc_lct_blaze_of_the_heavensAI(Creature* creature) : ScriptedAI(creature)
            {
                instance = me->GetInstanceScript();
                _egg = false;
                _ready = false;
            }

            EventMap events;
            InstanceScript* instance;
            bool _egg;
            bool _ready;

            void InitializeAI()
            {
                me->SetReactState(REACT_PASSIVE);
            }

            void IsSummonedBy(Unit* /*summoner*/)
            {
                //me->HandleEmoteCommand(EMOTE_ONESHOT_EMERGE);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
                events.ScheduleEvent(EVENT_ATTACK, 3000);
                events.ScheduleEvent(EVENT_CHECK_BARIM, 500);
                _egg = false;
            }

            void JustDied(Unit* /*killer*/)
            {
                if (_egg)
                {
                    instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
                    me->DespawnOrUnsummon(4000);
                }
            }

            void DamageTaken(Unit* /*attacker*/, uint32& damage)
            {
                if (damage >= me->GetHealth() && !_egg)
                {
                    me->SetUInt32Value(UNIT_FIELD_DISPLAYID, MODEL_EGG);
                    me->GetMotionMaster()->MovementExpired();
                    events.ScheduleEvent(EVENT_REGENERATE, 1000);
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    me->AttackStop();
                    me->RemoveAllAuras();
                    me->SetReactState(REACT_PASSIVE);
                    damage = 0;
                    me->SetHealth(10000);
                    _egg = true;
                    _ready = false;
                }
            }

            void AttackRandomPlayer()
            {
                std::list<Player*> playerList = me->GetNearestPlayersList(500.0f, true);
                if (playerList.empty())
                    return;

                if (Unit* victim = Trinity::Containers::SelectRandomContainerElement(playerList))
                    me->AI()->AttackStart(victim);

                me->SetReactState(REACT_AGGRESSIVE);
                me->SetInCombatWithZone();
            }

            void UpdateAI(uint32 diff)
            {
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_ATTACK:
                        {
                            DoCastAOE(SPELL_SUMMON_BLAZE_FIRE_DUMMY);
                            DoCastAOE(SPELL_BLAZE_OF_THE_HEAVENS);
                            _ready = true;
                            AttackRandomPlayer();
                            break;
                        }
                        case EVENT_REGENERATE:
                            if (Creature* barim = me->FindNearestCreature(BOSS_HIGH_PROPHET_BARIM, 500.0f, true))
                            {
                                if (!barim->HasAura(SPELL_REPENTEANCE_GROUND))
                                {
                                    me->SetHealth(me->GetHealth() + me->GetMaxHealth() / 20);
                                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                                }
                            }
                            if (me->HealthAbovePct(95))
                            {
                                _egg = false;
                                _ready = true;
                                events.CancelEvent(EVENT_REGENERATE);
                                DoCastAOE(SPELL_SUMMON_BLAZE_FIRE_DUMMY);
                                DoCastAOE(SPELL_BLAZE_OF_THE_HEAVENS);
                                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                                me->SetUInt32Value(UNIT_FIELD_DISPLAYID, MODEL_PHOENIX);
                                AttackRandomPlayer();
                            }
                            events.ScheduleEvent(EVENT_REGENERATE, 1000);
                            break;
                        case EVENT_CHECK_BARIM:
                            if (Creature* barim = me->FindNearestCreature(BOSS_HIGH_PROPHET_BARIM, 500.0f, true))
                            {
                                if (!barim->isInCombat())
                                {
                                    me->DespawnCreaturesInArea(NPC_BLAZE_FIRE_DUMMY, 500.0f);
                                    instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
                                    me->DespawnOrUnsummon(100);
                                }
                            }
                            else
                            {
                                me->DespawnCreaturesInArea(NPC_BLAZE_FIRE_DUMMY, 500.0f);
                                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
                                me->DespawnOrUnsummon(100);
                            }

                            if (Creature* barim = me->FindNearestCreature(BOSS_HIGH_PROPHET_BARIM, 500.0f, true))
                            {
                                if (_ready && barim->HasAura(SPELL_REPENTEANCE_GROUND))
                                {
                                    instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
                                    me->AttackStop();
                                    me->GetMotionMaster()->MovementExpired();
                                    me->SetReactState(REACT_PASSIVE);
                                    _ready = false;
                                }
                            }
                            else if (_ready)
                            {
                                AttackRandomPlayer();
                            }

                            events.ScheduleEvent(EVENT_CHECK_BARIM, 500);
                            break;
                    }
                }
                DoMeleeAttackIfReady();
            }
        };
        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_lct_blaze_of_the_heavensAI(creature);
        }
};

class npc_lct_harbringer_of_darknes : public CreatureScript
{
    public:
        npc_lct_harbringer_of_darknes() :  CreatureScript("npc_lct_harbringer_of_darkness") { }

        struct npc_lct_harbringer_of_darknesAI : public ScriptedAI
        {
            npc_lct_harbringer_of_darknesAI(Creature* creature) : ScriptedAI(creature)
            {
                instance = me->GetInstanceScript();
            }

            EventMap events;
            InstanceScript* instance;

            void InitializeAI()
            {
                me->SetReactState(REACT_PASSIVE);
            }

            void IsSummonedBy(Unit* /*summoner*/)
            {
                //me->HandleEmoteCommand(EMOTE_ONESHOT_EMERGE);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
                events.ScheduleEvent(EVENT_ATTACK, 3000);
                events.ScheduleEvent(EVENT_WAIL_OF_DARKNESS, 6000);
                events.ScheduleEvent(EVENT_SOUL_SEVER, 5000);
            }

            void JustDied(Unit* /*killer*/)
            {
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
                if (Creature* barim = me->FindNearestCreature(BOSS_HIGH_PROPHET_BARIM, 500.0f, true))
                    barim->AI()->DoAction(ACTION_RELEASE_SPIRITS);
                me->DespawnOrUnsummon(1000);
            }

            void AttackRandomPlayer()
            {
                std::list<Player*> playerList = me->GetNearestPlayersList(500.0f, true);
                if (playerList.empty())
                    return;

                if (Unit* victim = Trinity::Containers::SelectRandomContainerElement(playerList))
                    me->AI()->AttackStart(victim);

                me->SetReactState(REACT_AGGRESSIVE);
                me->SetInCombatWithZone();
            }

            void UpdateAI(uint32 diff)
            {
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_ATTACK:
                            events.ScheduleEvent(EVENT_CHECK_BARIM, 500);
                            AttackRandomPlayer();
                            break;
                        case EVENT_CHECK_BARIM:
                            if (Creature* barim = me->FindNearestCreature(BOSS_HIGH_PROPHET_BARIM, 500.0f, true))
                            {
                                if (!barim->isInCombat())
                                {
                                    instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
                                    me->DespawnOrUnsummon(1000);
                                }
                            }
                            events.ScheduleEvent(EVENT_CHECK_BARIM, 500);
                            break;
                        case EVENT_WAIL_OF_DARKNESS:
                            DoCastAOE(SPELL_WAIL_OF_DARKNESS_DAMAGE);
                            events.ScheduleEvent(EVENT_WAIL_OF_DARKNESS, 3000);
                            break;
                        case EVENT_SOUL_SEVER:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                                DoCast(target, SPELL_SOUL_SEVER_AURA);
                            events.ScheduleEvent(EVENT_SOUL_SEVER, 11000);
                            break;
                    }
                }
                DoMeleeAttackIfReady();
            }
        };
        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_lct_harbringer_of_darknesAI(creature);
        }
};

class npc_lct_soul_fragment : public CreatureScript
{
    public:
        npc_lct_soul_fragment() :  CreatureScript("npc_lct_soul_fragment") { }

        struct npc_lct_soul_fragmentAI : public ScriptedAI
        {
            npc_lct_soul_fragmentAI(Creature* creature) : ScriptedAI(creature)
            {
                casted = false;
            }

            EventMap events;
            bool casted;

            void InitializeAI()
            {
                me->SetReactState(REACT_PASSIVE);
            }

            void IsSummonedBy(Unit* /*summoner*/)
            {
                me->SetReactState(REACT_PASSIVE);
                if (Player* player = me->FindNearestPlayer(20.0f, true))
                    player->CastSpell(me, SPELL_SOUL_FRAGMENT_COPY);
                events.ScheduleEvent(EVENT_MOVE, 500);
                me->SetWalk(true);
                casted = false;
            }

            void UpdateAI(uint32 diff)
            {
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_MOVE:
                            if (Creature* harbinger = me->FindNearestCreature(NPC_HARBRINGER_OF_DARKNESS, 500.0f, false))
                                me->DespawnOrUnsummon(1);

                            if (!me->FindNearestCreature(NPC_HARBRINGER_OF_DARKNESS, 500.0f))
                                me->DespawnOrUnsummon(1);

                            if (Creature* harbinger = me->FindNearestCreature(NPC_HARBRINGER_OF_DARKNESS, 500.0f, true))
                                me->GetMotionMaster()->MoveFollow(harbinger, 0.0f, 0.0f);

                            if (Creature* harbinger = me->FindNearestCreature(NPC_HARBRINGER_OF_DARKNESS, 2.0f, true))
                            {
                                me->RemoveAllAuras();
                                if (!casted)
                                {
                                    DoCastAOE(SPELL_MERGED_SOUL);
                                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_NOT_SELECTABLE);
                                    me->DespawnOrUnsummon(3000);
                                    casted = true;
                                }
                            }
                            events.ScheduleEvent(EVENT_MOVE, 1000);
                            break;
                        default:
                            break;
                    }
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_lct_soul_fragmentAI(creature);
        }
};

class npc_lct_repenteance : public CreatureScript
{
    public:
        npc_lct_repenteance() :  CreatureScript("npc_lct_repenteance") { }

        struct npc_lct_repenteanceAI : public ScriptedAI
        {
            npc_lct_repenteanceAI(Creature* creature) : ScriptedAI(creature)
            {
                player = NULL;
            }

            Player* player;

            void InitializeAI()
            {
                me->SetReactState(REACT_PASSIVE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC);
            }

            void IsSummonedBy(Unit* summoner)
            {
                me->SetStandState(UNIT_STAND_STATE_KNEEL);

                if (player = me->FindNearestPlayer(0.1f))
                {
                    player->CastSpell(me, SPELL_REPENTEANCE_CLONE);
                    player->SetFacingToObject(summoner);
                    me->SetFacingToObject(summoner);
                }
            }

            void DoAction(int32 action)
            {
                switch (action)
                {
                    case ACTION_RELEASE_SPIRITS:
                        DoCastAOE(SPELL_REPENTEANCE_PULL_SPRIRIT);
                        break;
                    default:
                        break;
                }
            }

            void UpdateAI(uint32 diff)
            {
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_lct_repenteanceAI(creature);
        }
};

class npc_lct_heavens_fury : public CreatureScript
{
    public:
        npc_lct_heavens_fury() :  CreatureScript("npc_lct_heavens_fury") { }

        struct npc_lct_heavens_furyAI : public ScriptedAI
        {
            npc_lct_heavens_furyAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            void InitializeAI()
            {
                me->SetReactState(REACT_PASSIVE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC);
            }

            void IsSummonedBy(Unit* /*summoner*/)
            {
                DoCastAOE(SPELL_HEAVENS_FURY_VISUAL);
                DoCastAOE(SPELL_HEAVENS_FURY_AURA);
            }

            void UpdateAI(uint32 diff)
            {
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_lct_heavens_furyAI(creature);
        }
};

class npc_lct_blaze_of_the_heavens_dummy : public CreatureScript
{
    public:
        npc_lct_blaze_of_the_heavens_dummy() :  CreatureScript("npc_lct_blaze_of_the_heavens_dummy") { }

        struct npc_lct_blaze_of_the_heavens_dummyAI : public ScriptedAI
        {
            npc_lct_blaze_of_the_heavens_dummyAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            EventMap events;

            void IsSummonedBy(Unit* /*summoner*/)
            {
                if (me->GetEntry() == NPC_BLAZE_DUMMY)
                {
                    DoCastAOE(SPELL_BLAZE_SUMMON_VISUAL);
                    events.ScheduleEvent(EVENT_SUMMON_BLAZE, 500);
                }
                else
                {
                    DoCastAOE(SPELL_VAIL_OF_DARKNES_AURA);
                    events.ScheduleEvent(EVENT_SUMMON_HARBRINGER, 500);
                }
            }

            void UpdateAI(uint32 diff)
            {
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_SUMMON_BLAZE:
                            DoCastAOE(SPELL_SUMMON_BLAZE_OF_THE_HEAVENS);
                            me->DespawnOrUnsummon(2000);
                            break;
                        case EVENT_SUMMON_HARBRINGER:
                            DoCastAOE(SPELL_VAIL_OF_DARKNES_SUMMON);
                            me->DespawnOrUnsummon(2000);
                            break;
                        default:
                            break;
                    }
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_lct_blaze_of_the_heavens_dummyAI(creature);
        }
};

class npc_lct_blaze_fire_dummy : public CreatureScript
{
    public:
        npc_lct_blaze_fire_dummy() :  CreatureScript("npc_lct_blaze_fire_dummy") { }

        struct npc_lct_blaze_fire_dummyAI : public ScriptedAI
        {
            npc_lct_blaze_fire_dummyAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            void InitializeAI()
            {
                me->SetReactState(REACT_PASSIVE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC);
            }

            void IsSummonedBy(Unit* /*summoner*/)
            {
                DoCastAOE(SPELL_BLAZE_FIRE_AURA);
            }

            void UpdateAI(uint32 diff)
            {
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_lct_blaze_fire_dummyAI(creature);
        }
};

class spell_lct_fifty_lashings : public SpellScriptLoader
{
    public:
        spell_lct_fifty_lashings() : SpellScriptLoader("spell_lct_fifty_lashings") { }

        class spell_lct_fifty_lashings_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_lct_fifty_lashings_AuraScript)

            void OnProc(AuraEffect const* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
            {
                PreventDefaultAction();
                if (GetCaster()->getVictim())
                    GetCaster()->CastSpell(GetCaster()->getVictim(), GetSpellInfo()->Effects[EFFECT_0].TriggerSpell, true);
            }

            void Register()
            {
                OnEffectProc += AuraEffectProcFn(spell_lct_fifty_lashings_AuraScript::OnProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_lct_fifty_lashings_AuraScript();
        }
};

class spell_lct_repenteance_pull : public SpellScriptLoader
{
    public:
        spell_lct_repenteance_pull() : SpellScriptLoader("spell_lct_repenteance_pull") { }

        class spell_lct_repenteance_pull_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_lct_repenteance_pull_SpellScript);

            void HandleJump(SpellEffIndex effIndex)
            {
                if (Unit* caster = GetCaster())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        PreventHitEffect(effIndex);
                        target->SetFacingToObject(caster);
                        float angle = target->GetAngle(caster);
                        float distance = caster->GetDistance2d(target->GetPositionX(), target->GetPositionY());
                        float x = (target->GetPositionX()+cos(angle)*distance) - caster->GetFloatValue(UNIT_FIELD_COMBATREACH);
                        float y = (target->GetPositionY()+sin(angle)*distance) - caster->GetFloatValue(UNIT_FIELD_COMBATREACH);
                        float z = caster->GetPositionZ();
                        target->GetMotionMaster()->MoveJump(x, y, z, 15.0f, 15.0f, 0);
                    }
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_lct_repenteance_pull_SpellScript::HandleJump, EFFECT_0, SPELL_EFFECT_PULL_TOWARDS);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_lct_repenteance_pull_SpellScript();
        }
};

void AddSC_boss_high_prophet_barim()
{
    new boss_high_prophet_barim();
    new npc_lct_blaze_of_the_heavens();
    new npc_lct_harbringer_of_darknes();
    new npc_lct_soul_fragment();
    new npc_lct_repenteance();
    new npc_lct_heavens_fury();
    new npc_lct_blaze_of_the_heavens_dummy();
    new npc_lct_blaze_fire_dummy();
    new spell_lct_fifty_lashings();
    new spell_lct_repenteance_pull();
}
