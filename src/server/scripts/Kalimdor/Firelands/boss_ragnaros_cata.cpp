
#include "firelands.h"

enum Texts
{
    SAY_ARRIVE          = 0,
    SAY_DEATH_NORMAL    = 1,
    SAY_DEATH_HEROIC    = 2,
    SAY_SLAY            = 3,
    SAY_ANNOUNCE_SPLIT  = 4,
    SAY_SUBMERGE        = 5,
    SAY_EMERGE_ANNOUNCE = 6,
    SAY_EMERGE          = 7,
    SAY_MAGMA_TRAP      = 8,
    SAY_SULFURAS_SMASH  = 9,
};

enum Spells
{
    // Ragnaros Base Auras
    SPELL_BASE_VISUAL                       = 98860,
    SPELL_BURNING_WOUNDS_AURA               = 99401,

    // Spell Sulfuras Smash
    SPELL_SULFURAS_SMASH_DUMMY              = 98703, // Seems like this summoned npc is just the orientation dummy
    SPELL_SULFURAS_SMASH                    = 98710,
    SPELL_SULFURAS_SMASH_MISSILE            = 98708,
    SPELL_SULFURAS_SMASH_TARGET             = 98706,

    // Lava Wave Summons
    SPELL_LAVA_WAVE_DUMMY_NORTH             = 98874,
    SPELL_LAVA_WAVE_DUMMY_EAST              = 98875,
    SPELL_LAVA_WAVE_DUMMY_WEST              = 98876,
    SPELL_LAVA_POOL                         = 98712,
    SPELL_SCORCHED_GROUND                   = 98871,

    // Magma Trap
    SPELL_MAGMA_TRAP                        = 98164,
    SPELL_MAGMA_TRAP_SONAR                  = 98159, // For what is this ?
    SPELL_MAGMA_TRAP_VISUAL                 = 98179,
    SPELL_MAGMA_TRAP_PERIODIC               = 98172,
    SPELL_MAGMA_TRAP_PERIODIC_TICK          = 98171,
    SPELL_MAGMA_TRAP_ERUPTION               = 98175,

    // Hand of Ragnaros
    SPELL_HAND_OF_RAGNAROS                  = 98237,

    // Wrath of Ragnaros
    SPELL_WRATH_OF_RAGNAROS                 = 98263,

    // Lava Wave
    SPELL_LAVA_WAVE                         = 98873,

    SPELL_SUBMERGED                         = 98982,
    SPELL_SPLITTING_BLOW_EAST               = 98953,
    SPELL_SPLITTING_BLOW_NORTH              = 98952,
    SPELL_SPLITTING_BLOW_WEST               = 98951,
    SPELL_ENGULFING_FLAMES_BOTTOM           = 99236,
    SPELL_ENGULFING_FLAMES_CENTER           = 99235,
    SPELL_ENGULFING_FLAMES_MELEE            = 99172,
    SPELL_ENGULFING_FLAMES_VISUAL_MELEE     = 99216,
    SPELL_ENGULFING_FLAMES_VISUAL_CENTER    = 99217,
    SPELL_ENGULFING_FLAMES_VISUAL_BOTTOM    = 99218,
    SPELL_ENGULFING_FLAMES_EXPLOSION        = 99225,
    SPELL_LIVING_METEOR_VISUAL              = 99215,

    //Sulfuras Hand of Ragnaros
    SPELL_SULFURAS_KNOCKBACK                = 100455,
    SPELL_FLAMES_OF_SULFURAS                = 101245,
    SPELL_SULFURAS_AURA                     = 100456,

    //Splitting Blow
    SPELL_CALL_SONS                         = 99054,
    SPELL_CALL_SONS_MISSILE                 = 99050,

    //Son of Flame
    SPELL_HIT_ME                            = 100446,
    SPELL_PRE_VISUAL                        = 100134,
    SPELL_BURNING_SPEED                     = 98473,
};

enum Phases
{
    PHASE_INTRO             = 1,
    PHASE_1                 = 2,
    PHASE_2                 = 3,
    PHASE_3                 = 4,
    PHASE_SUBMERGED         = 5,
    PHASE_HEROIC            = 6,
};

enum Events
{
    // Ragnaros
    EVENT_INTRO                     = 1,
    EVENT_ATTACK                    = 2,
    EVENT_SULFURAS_SMASH_TRIGGER    = 3,
    EVENT_SULFURAS_SMASH            = 4,
    EVENT_MAGMA_TRAP                = 5,
    EVENT_WRATH_OF_RAGNAROS         = 6,
    EVENT_HAND_OF_RAGNAROS          = 7,

    // Sulfuras Smash
    EVENT_SCORCH                    = 20,
    EVENT_MOVE_LAVA_WAVE            = 21,
    EVENT_SUMMON_WAVE_1             = 22,
    EVENT_SUMMON_WAVE_2             = 23,
    EVENT_SUMMON_WAVE_3             = 24,

    // Magma Trap
    EVENT_PREPARE_TRAP              = 25,
};

enum AnimKits
{
    ANIM_KIT_RESURFACE  = 1465,
    ANIM_KIT_EMERGE     = 1467,
    ANIM_KIT_TAUNT      = 1468,
    ANIM_KIT_STAND_UP   = 1486,
};

Position const RagnarosSummonPosition = {1075.201f, -57.84896f, 55.42427f,  3.159046f   };

const Position EngulfingFlamesMelee[] =
{
    {1086.55f, -18.0885f, 55.4228f, 1.57080f},
    {1091.83f, -21.9254f, 55.4241f, 4.71239f},
    {1092.52f, -92.3924f, 55.4241f, 4.71239f},
    {1079.15f, -15.5312f, 55.4230f, 4.71239f},
    {1078.01f, -97.7760f, 55.4227f, 1.57080f},
    {1065.44f, -17.7049f, 55.4250f, 5.00910f},
    {1063.59f, -97.0573f, 55.4934f, 1.23918f},
    {1051.80f, -24.0903f, 55.4258f, 5.41052f},
    {1049.27f, -90.6892f, 55.4259f, 0.89011f},
    {1042.34f, -32.1059f, 55.4254f, 5.68977f},
    {1041.26f, -81.4340f, 55.4240f, 0.57595f},
    {1036.82f, -44.3385f, 55.4425f, 6.02139f},
    {1036.34f, -69.8281f, 55.4425f, 0.31415f},
    {1034.76f, -63.9583f, 55.4397f, 6.26573f},
    {1033.93f, -57.0920f, 55.4225f, 6.26573f},
    {1086.42f, -96.7812f, 55.4226f, 1.57080f},
};

const Position EngulfingFlamesRange[] =
{
    {1035.17f, -125.646f, 55.4471f, 0.0f},
    {1032.48f,  13.2708f, 55.4469f, 0.0f},
    {1023.83f,  12.9774f, 55.4470f, 0.0f},
    {1023.05f, -128.257f, 55.4471f, 0.0f},
    {1019.60f,  7.76910f, 55.4470f, 0.0f},
    {1018.29f, -117.833f, 55.4471f, 0.0f},
    {1012.70f, -4.83333f, 55.6050f, 0.0f},
    {1009.56f, -108.161f, 55.4697f, 0.0f},
    {1005.80f, -8.81771f, 55.4672f, 0.0f},
    {1000.81f, -14.5069f, 55.4566f, 0.0f},
    {999.755f, -98.4792f, 55.4426f, 0.0f},
    {991.799f, -25.0955f, 55.4441f, 0.0f},
    {991.738f, -87.1632f, 55.4445f, 0.0f},
    {989.866f, -66.0868f, 55.4331f, 0.0f},
    {988.208f, -50.3646f, 55.4291f, 0.0f},
    {986.608f, -37.7656f, 55.4411f, 0.0f},
    {985.180f, -77.3785f, 55.4409f, 0.0f},
    {980.927f, -58.2656f, 55.4542f, 0.0f},
};

const Position EngulfingFlamesCenter[] =
{
    {1069.66f, -4.53993f, 55.4308f, 0.0f},
    {1062.94f, -4.34201f, 55.5682f, 0.0f},
    {1062.13f, -109.005f, 55.4259f, 0.0f},
    {1055.34f, 5.06771f,  55.4471f, 0.0f},
    {1057.03f, -4.10417f, 55.4258f, 0.0f},
    {1049.74f, -118.396f, 55.5661f, 0.0f},
    {1052.59f, -120.562f, 55.4563f, 0.0f},
    {1049.33f, 5.0434f,   55.4633f, 0.0f},
    {1049.98f, -7.22396f, 55.4537f, 0.0f},
    {1049.66f, -104.906f, 55.4556f, 0.0f},
    {1035.91f, 0.909722f, 55.4470f, 0.0f},
    {1035.56f, -114.156f, 55.4471f, 0.0f},
    {1038.53f, -100.254f, 55.6012f, 0.0f},
    {1036.90f, -14.6181f, 55.5715f, 0.0f},
    {1016.99f, -57.5642f, 55.4133f, 0.0f},
    {1030.22f, -92.8403f, 55.4344f, 0.0f},
    {1024.45f, -8.13889f, 55.4470f, 0.0f},
    {1024.45f, -8.13889f, 55.4470f, 0.0f},
    {1024.91f, -106.852f, 55.4471f, 0.0f},
    {1025.34f, -25.8472f, 55.4069f, 0.0f},
    {1025.29f, -86.2326f, 55.4071f, 0.0f},
    {1021.84f, -33.7483f, 55.4239f, 0.0f},
    {1021.49f, -79.6076f, 55.4261f, 0.0f},
    {1018.47f, -43.7674f, 55.4218f, 0.0f},
    {1069.91f, -109.651f, 55.4277f, 0.0f},
    {1014.15f, -17.3281f, 55.4629f, 0.0f},
    {1018.29f, -70.1875f, 55.4231f, 0.0f},
    {1012.09f, -97.5122f, 55.4570f, 0.0f},
    {1006.10f, -27.3681f, 55.4277f, 0.0f},
    {1005.49f, -86.4566f, 55.4275f, 0.0f},
    {1002.72f, -40.7431f, 55.4063f, 0.0f},
    {1003.44f, -74.0243f, 55.4063f, 0.0f},
    {1003.44f, -74.0243f, 55.4063f, 0.0f},
    {1003.07f, -66.4913f, 55.4067f, 0.0f},
    {1002.21f, -49.7049f, 55.4075f, 0.0f},
    {1002.00f, -58.2396f, 55.4331f, 0.0f},
};

class at_sulfuron_keep : public AreaTriggerScript
{
    public:
        at_sulfuron_keep() : AreaTriggerScript("at_sulfuron_keep") { }

        bool OnTrigger(Player* player, AreaTriggerEntry const* /*areaTrigger*/)
        {
            if (InstanceScript* instance = player->GetInstanceScript())
                if (!instance->GetData64(DATA_RAGNAROS))
                    player->SummonCreature(BOSS_RAGNAROS, RagnarosSummonPosition, TEMPSUMMON_MANUAL_DESPAWN, 0);
            return true;
        }
};

class boss_ragnaros_cata : public CreatureScript
{
public:
    boss_ragnaros_cata() : CreatureScript("boss_ragnaros_cata") { }

    struct boss_ragnaros_cataAI : public BossAI
    {
        boss_ragnaros_cataAI(Creature* creature) : BossAI(creature, DATA_RAGNAROS)
        {
        }

        void Reset()
        {
            _Reset();
            events.SetPhase(PHASE_1);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            me->SetByteValue(UNIT_FIELD_BYTES_1, 3, UNIT_BYTE1_FLAG_ALWAYS_STAND | UNIT_BYTE1_FLAG_HOVER);
            me->AddAura(SPELL_BASE_VISUAL, me);
            me->AddAura(SPELL_BURNING_WOUNDS_AURA, me);
            me->SetReactState(REACT_PASSIVE);
        }

        void EnterCombat(Unit* /*who*/)
        {
            _EnterCombat();
            HandleDoor();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            me->SetReactState(REACT_AGGRESSIVE);
            events.SetPhase(PHASE_1);
            events.ScheduleEvent(EVENT_SULFURAS_SMASH_TRIGGER, 30000, 0, PHASE_1);
            events.ScheduleEvent(EVENT_MAGMA_TRAP, 15500, 0, PHASE_1);
            events.ScheduleEvent(EVENT_WRATH_OF_RAGNAROS, 6000, 0, PHASE_1);
            events.ScheduleEvent(EVENT_HAND_OF_RAGNAROS, 25000, 0, PHASE_1);
        }

        void JustDied(Unit* /*killer*/)
        {
            _JustDied();
            HandleDoor();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();
            HandleDoor();
            Reset();
            Cleanup();
        }

        void IsSummonedBy(Unit* /*summoner*/)
        {
            events.SetPhase(PHASE_INTRO);
            events.ScheduleEvent(EVENT_INTRO, 5500, 0, PHASE_INTRO);
            me->setActive(true);
            me->PlayOneShotAnimKit(ANIM_KIT_EMERGE);
            SetCombatMovement(false);
        }

        void KilledUnit(Unit* killed)
        {
            if (killed->GetTypeId() == TYPEID_PLAYER)
                Talk(SAY_SLAY);
        }

        void JustSummoned(Creature* summon)
        {
            switch (summon->GetEntry())
            {
                case NPC_SULFURAS_SMASH_TARGET:
                    summon->AddAura(SPELL_LAVA_POOL, summon);
                    break;
                default:
                    break;
            }
        }

        void HandleDoor() // Needed because the instancescript needs db guids
        {
            if (GameObject* door = me->FindNearestGameObject(GO_RAGNAROS_DOOR, 200.0f))
            {
                if (door->GetGoState() == GO_STATE_ACTIVE)
                    door->SetGoState(GO_STATE_READY);
                else
                    door->SetGoState(GO_STATE_ACTIVE);
            }

        }

        void Cleanup()
        {
            std::list<Creature*> units;

            GetCreatureListWithEntryInGrid(units, me, NPC_SULFURAS_SMASH_TARGET, 200.0f);
            for (std::list<Creature*>::iterator itr = units.begin(); itr != units.end(); ++itr)
                (*itr)->DespawnOrUnsummon();

            GetCreatureListWithEntryInGrid(units, me, NPC_MAGMA_TRAP, 200.0f);
            for (std::list<Creature*>::iterator itr = units.begin(); itr != units.end(); ++itr)
                (*itr)->DespawnOrUnsummon();

            GetCreatureListWithEntryInGrid(units, me, NPC_LAVA_WAVE, 200.0f);
            for (std::list<Creature*>::iterator itr = units.begin(); itr != units.end(); ++itr)
                (*itr)->DespawnOrUnsummon();
        }

        void UpdateAI(uint32 diff)
        {
            if (!(events.IsInPhase(PHASE_INTRO)))
                if (!UpdateVictim())
                    return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_INTRO:
                        Talk(SAY_ARRIVE);
                        me->AddAura(SPELL_BASE_VISUAL, me);
                        me->AddAura(SPELL_BURNING_WOUNDS_AURA, me);
                        me->PlayOneShotAnimKit(ANIM_KIT_TAUNT);
                        break;
                    case EVENT_ATTACK:
                        me->SetReactState(REACT_AGGRESSIVE);
                        me->Attack(me->getVictim(), false);
                        me->AddAura(SPELL_BASE_VISUAL, me);
                        me->AddAura(SPELL_BURNING_WOUNDS_AURA, me);
                        break;
                    case EVENT_SULFURAS_SMASH_TRIGGER:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                        {
                            me->SetFacingToObject(target);
                            DoCast(SPELL_SULFURAS_SMASH_DUMMY);
                            events.ScheduleEvent(EVENT_SULFURAS_SMASH, 500, 0, PHASE_1);
                            events.ScheduleEvent(EVENT_SULFURAS_SMASH_TRIGGER, 30000, 0, PHASE_1);
                        }
                        break;
                    case EVENT_SULFURAS_SMASH:
                        if (Unit* trigger = me->FindNearestCreature(NPC_SULFURAS_SMASH_TRIGGER, 60.0f, true))
                        {
                            Talk(SAY_SULFURAS_SMASH);
                            me->AttackStop();
                            me->SetReactState(REACT_PASSIVE);
                            me->SetFacingToObject(trigger);
                            DoCast(SPELL_SULFURAS_SMASH);
                            DoCast(SPELL_SULFURAS_SMASH_TARGET);
                            events.ScheduleEvent(EVENT_ATTACK, 6000);
                        }
                        break;
                    case EVENT_MAGMA_TRAP:
                        Talk(SAY_MAGMA_TRAP);
                        if (Unit* target = SelectTarget(SELECT_TARGET_FARTHEST, 0))
                            DoCast(target, SPELL_MAGMA_TRAP);
                        events.ScheduleEvent(EVENT_MAGMA_TRAP, 25000, 0, PHASE_1);
                        break;
                    case EVENT_WRATH_OF_RAGNAROS:
                        DoCastAOE(SPELL_WRATH_OF_RAGNAROS);
                        events.ScheduleEvent(EVENT_WRATH_OF_RAGNAROS, 36000, 0, PHASE_1);
                        break;
                    case EVENT_HAND_OF_RAGNAROS:
                        DoCastAOE(SPELL_HAND_OF_RAGNAROS);
                        events.ScheduleEvent(EVENT_HAND_OF_RAGNAROS, 25000, 0, PHASE_1);
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
        return new boss_ragnaros_cataAI(creature);
    }
};

class npc_magma_trap : public CreatureScript
{
    public:
        npc_magma_trap() :  CreatureScript("npc_magma_trap") { }

        struct npc_magma_trapAI : public ScriptedAI
        {
            npc_magma_trapAI(Creature* creature) : ScriptedAI(creature)
            {
                _exploded = false;
            }

            bool _exploded;

            void IsSummonedBy(Unit* /*summoner*/)
            {
                events.ScheduleEvent(EVENT_PREPARE_TRAP, 5000);
                me->AddAura(SPELL_MAGMA_TRAP_VISUAL, me);
                me->SetReactState(REACT_PASSIVE);
                SetCombatMovement(false);
            }

            void SpellHitTarget(Unit* /*target*/, SpellInfo const* spell)
            {
                if (spell->Id == SPELL_MAGMA_TRAP_PERIODIC_TICK && !_exploded)
                {
                    DoCastAOE(SPELL_MAGMA_TRAP_ERUPTION);
                    me->RemoveAurasDueToSpell(SPELL_MAGMA_TRAP_VISUAL);
                    _exploded = true;
                    me->DespawnOrUnsummon(3000);
                }
            }

            void UpdateAI(uint32 diff)
            {
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_PREPARE_TRAP:
                            DoCast(SPELL_MAGMA_TRAP_PERIODIC);
                            break;
                        default:
                            break;
                    }
                }
            }

        private:
            EventMap events;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_magma_trapAI(creature);
        }
};

class npc_sulfuras_smash : public CreatureScript
{
    public:
        npc_sulfuras_smash() :  CreatureScript("npc_sulfuras_smash") { }

        struct npc_sulfuras_smashAI : public ScriptedAI
        {
            npc_sulfuras_smashAI(Creature* creature) : ScriptedAI(creature)
            {
                _summonCounter = 0;
            }

            uint8 _summonCounter;

            void IsSummonedBy(Unit* summoner)
            {
                events.ScheduleEvent(EVENT_SCORCH, 3400);
                events.ScheduleEvent(EVENT_SUMMON_WAVE_1, 3400);
                me->SetOrientation(summoner->GetOrientation());
                me->setFaction(summoner->getFaction());
            }

            void JustSummoned(Creature* summon)
            {
                summon->setFaction(me->getFaction());
                _summonCounter++;
                if (_summonCounter == 2)
                    summon->SetOrientation(me->GetOrientation() + M_PI/2);
                else if (_summonCounter == 3)
                {
                    summon->SetOrientation(me->GetOrientation() - M_PI/2);
                    _summonCounter = 0;
                }
            }

            void UpdateAI(uint32 diff)
            {
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_SCORCH:
                            me->RemoveAurasDueToSpell(SPELL_LAVA_POOL);
                            me->AddAura(SPELL_SCORCHED_GROUND, me);
                            break;
                        case EVENT_SUMMON_WAVE_1:
                            DoCastAOE(SPELL_LAVA_WAVE_DUMMY_NORTH);
                            events.ScheduleEvent(EVENT_SUMMON_WAVE_2, 50);
                            break;
                        case EVENT_SUMMON_WAVE_2:
                            DoCastAOE(SPELL_LAVA_WAVE_DUMMY_WEST);
                            events.ScheduleEvent(EVENT_SUMMON_WAVE_3, 50);
                            break;
                        case EVENT_SUMMON_WAVE_3:
                            DoCastAOE(SPELL_LAVA_WAVE_DUMMY_EAST);
                            break;
                        default:
                            break;
                    }
                }
            }
    private:
        EventMap events;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_sulfuras_smashAI(creature);
        }
};

class npc_fl_lava_wave : public CreatureScript
{
    public:
        npc_fl_lava_wave() :  CreatureScript("npc_fl_lava_wave") { }

        struct npc_fl_lava_waveAI : public ScriptedAI
        {
            npc_fl_lava_waveAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            void IsSummonedBy(Unit* summoner)
            {
                events.ScheduleEvent(EVENT_MOVE_LAVA_WAVE, 100);
                me->SetSpeed(MOVE_RUN, 2.0f);
            }

            void UpdateAI(uint32 diff)
            {
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_MOVE_LAVA_WAVE:
                            DoCast(SPELL_LAVA_WAVE);
                            me->GetMotionMaster()->MovePoint(0, me->GetPositionX()+cos(me->GetOrientation())*100, me->GetPositionY()+sin(me->GetOrientation())*100, me->GetPositionZ(), false);
                            break;
                        default:
                            break;
                    }
                }
            }

        private:
            EventMap events;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_fl_lava_waveAI(creature);
        }
};

class npc_engulfing_flame : public CreatureScript
{
    public:
        npc_engulfing_flame() :  CreatureScript("npc_engulfing_flame") { }

        struct npc_engulfing_flameAI : public ScriptedAI
        {
            npc_engulfing_flameAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            void IsSummonedBy(Unit* /*summoner*/)
            {
            }

            void UpdateAI(uint32 diff)
            {
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_engulfing_flameAI(creature);
        }
};

class npc_sulfuras_hammer : public CreatureScript
{
    public:
        npc_sulfuras_hammer() :  CreatureScript("npc_sulfuras_hammer") { }

        struct npc_sulfuras_hammerAI : public ScriptedAI
        {
            npc_sulfuras_hammerAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            void IsSummonedBy(Unit* /*summoner*/)
            {
                DoCastAOE(SPELL_SULFURAS_KNOCKBACK);
                me->SetReactState(REACT_PASSIVE);
                me->AddAura(SPELL_SULFURAS_AURA, me);
            }

            void UpdateAI(uint32 diff)
            {
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_sulfuras_hammerAI(creature);
        }
};

class npc_son_of_flame : public CreatureScript
{
    public:
        npc_son_of_flame() :  CreatureScript("npc_son_of_flame") { }

        struct npc_son_of_flameAI : public ScriptedAI
        {
            npc_son_of_flameAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            void IsSummonedBy(Unit* /*summoner*/)
            {
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

                while (uint32 eventId = events.ExecuteEvent())
                {
                    //switch (eventId)
                    //{
                    //}
                }
            }

        private:
            EventMap events;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_son_of_flameAI(creature);
        }
};

void AddSC_boss_ragnaros_cata()
{
    new at_sulfuron_keep();
    new boss_ragnaros_cata();
    new npc_magma_trap();
    new npc_sulfuras_smash();
    new npc_fl_lava_wave();
    new npc_engulfing_flame();
    new npc_sulfuras_hammer();
    new npc_son_of_flame();
}