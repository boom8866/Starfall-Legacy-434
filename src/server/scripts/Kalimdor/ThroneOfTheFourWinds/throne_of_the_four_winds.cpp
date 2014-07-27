
/*
 * Copyright (C) 2011 - 2013 Naios <https://github.com/Naios>
 *
 * THIS particular file is NOT free software.
 * You are not allowed to share or redistribute it.
 */

#include "throne_of_the_four_winds.h"
#include "ScriptSystem.h"
#include "MapManager.h"
#include "GameObjectAI.h"

class go_winddraft : public GameObjectScript
{
public:
    go_winddraft() : GameObjectScript("go_winddraft") { }

    struct go_winddraftAI : public GameObjectAI
    {
        go_winddraftAI(GameObject* g) : GameObjectAI(g), isOutOfCombatWindDraft(_IsOutOfCombatWindDraft())
        {
            for (uint8 i = 0; i < 8; i++)
                if (windDrafts[i].entry == go->GetEntry())
                {
                    windDraftData = windDrafts[i];
                    return;
                }
        }

        bool const isOutOfCombatWindDraft;
        WindDraftData windDraftData;

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_WINDDRAFT_IN_COMBAT:
                {
                    if (isOutOfCombatWindDraft)
                        go->SetGoState(GO_STATE_ACTIVE);

                    break;
                }
                case ACTION_WINDDRAFT_OUT_OF_COMBAT:
                {
                    go->SetGoState(GO_STATE_READY);
                    break;
                }
                case ACTION_WINDDRAFT_ULTIMATE_BEGIN:
                {
                    if (!isOutOfCombatWindDraft && go->GetGoState() == GO_STATE_READY)
                        go->SetGoState(GO_STATE_ACTIVE);

                    break;
                }
                case ACTION_WINDDRAFT_ULTIMATE_END:
                {
                    if (!isOutOfCombatWindDraft && go->GetGoState() == GO_STATE_ACTIVE)
                        go->SetGoState(GO_STATE_READY);

                    break;
                }
            }
        }

        inline bool _IsOutOfCombatWindDraft() const
        {
            switch (go->GetEntry())
            {
                case GOB_WIND_DRAFTEFFECT_1:
                case GOB_WIND_DRAFTEFFECT_2:
                case GOB_WIND_DRAFTEFFECT_3:
                case GOB_WIND_DRAFTEFFECT_6:
                    return true;
            }
            return false;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const
    {
        return new go_winddraftAI(go);
    }
};

inline float GetDiffOrientation(float o1, float o2)
{
    if (o1 > o2)
        std::swap(o1, o2);

    return o2 - o1;
}

class at_winddraft : public AreaTriggerScript
{
public:
    at_winddraft() : AreaTriggerScript("at_winddraft") { }

    bool OnTrigger(Player* player, const AreaTriggerEntry* at)
    {
        InstanceScript* instance = player->GetInstanceScript();

        if (instance->GetBossState(DATA_ALAKIR) == IN_PROGRESS)
            return false;

        if (player->HasAura(SPELL_JETSTREAM_PREVENT))
            return false;

        for (uint8 i = 0; i < 8; i++)
            if (windDrafts[i].areatrigger == at->id)
            {
                InstanceScript* instance = player->GetInstanceScript();
                if (!instance)
                    return false;

                GameObject* windDraft = ObjectAccessor::GetGameObject(*player, instance->GetData64(windDrafts[i].entry));
                if (!windDraft || windDraft->GetGoState() == GO_STATE_ACTIVE)
                    return false;

                float diff = GetDiffOrientation(player->GetOrientation(), windDraft->GetOrientation());

                if ((static_cast<float>(M_PI) - WINDDRAFT_DIFF_O) > diff || diff > (static_cast<float>(M_PI) + WINDDRAFT_DIFF_O))
                    player->SetOrientation(Position::NormalizeOrientation(windDraft->GetOrientation() + static_cast<float>(M_PI)));

                player->CastSpell(player, SPELL_WINDDRAFT, true);
                return true;
            }

        return false;
    }
};

class spell_jet_stream : public SpellScriptLoader
{
public:
    spell_jet_stream() : SpellScriptLoader("spell_jet_stream") { }

    class spell_jet_stream_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_jet_stream_SpellScript);

        void SelectDestination()
        {
            Unit* caster = GetOriginalCaster();
            if (!caster)
                return;

            // Same calculation as in Spell::EffectKnockBack because we want to overwrite the position target
            // only speedxy is modified due to wrong calculation in spelleffects.cpp
            float const speedxy = float(GetSpellInfo()->Effects[0].MiscValue) * 0.0845f;
            float const speedz = 50.f;

            Position pos = *caster;
            caster->MovePosition(pos, -2.f, 0);

            caster->KnockbackFrom(pos.GetPositionX(), pos.GetPositionY(), speedxy, speedz);
            caster->CastSpell(caster, SPELL_SLIPSTREAM_VISUAL, true);

            PreventHitEffect(EFFECT_0);
            PreventHitDefaultEffect(EFFECT_0);
        }

        void Register()
        {
            BeforeHit += SpellHitFn(spell_jet_stream_SpellScript::SelectDestination);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_jet_stream_SpellScript();
    }
};

void AddSC_throne_of_the_four_winds()
{
    new go_winddraft();
    new at_winddraft();
    new spell_jet_stream();
}
