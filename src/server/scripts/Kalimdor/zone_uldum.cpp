
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

// Quest 28250: Thieving Little Pluckers
class spell_uldum_hammer : public SpellScriptLoader
{
    public:
        spell_uldum_hammer() : SpellScriptLoader("spell_uldum_hammer") { }

        class spell_uldum_hammer_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_uldum_hammer_SpellScript);

            void HandleDummy1(SpellEffIndex /*effIndex*/)
            {
                if (Unit* caster = GetCaster())
                    if (Unit* target = GetHitCreature())
                    {
                        if (target->GetEntry() == 48040)
                        {
                            float ori = frand(0.0f, M_PI);
                            caster->Kill(target);
                            target->GetMotionMaster()->MoveKnockbackFrom(caster->GetPositionX()+cos(ori)*10, caster->GetPositionY()+sin(ori)*10, 10.0f, 5.0f);
                            caster->ToPlayer()->KilledMonsterCredit(48105);
                        }
                    }
            }

            void HandleDummy2(SpellEffIndex /*effIndex*/)
            {
                if (Unit* caster = GetCaster())
                    if (Unit* target = GetHitCreature())
                    {
                        if (target->GetEntry() ==48041)
                        {
                            float ori = frand(0.0f, M_PI);
                            caster->Kill(target);
                            target->GetMotionMaster()->MoveKnockbackFrom(caster->GetPositionX()+cos(ori)*10, caster->GetPositionY()+sin(ori)*10, 10.0f, 5.0f);
                            caster->ToPlayer()->KilledMonsterCredit(48105);
                        }
                    }
            }

            void HandleDummy3(SpellEffIndex /*effIndex*/)
            {
                if (Unit* caster = GetCaster())
                    if (Unit* target = GetHitCreature())
                    {
                        if (target->GetEntry() == 48043)
                        {
                            float ori = frand(0.0f, M_PI);
                            caster->Kill(target);
                            target->GetMotionMaster()->MoveKnockbackFrom(caster->GetPositionX()+cos(ori)*10, caster->GetPositionY()+sin(ori)*10, 10.0f, 5.0f);
                            caster->ToPlayer()->KilledMonsterCredit(48105);
                        }
                    }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_uldum_hammer_SpellScript::HandleDummy1, EFFECT_0, SPELL_EFFECT_DUMMY);
                OnEffectHitTarget += SpellEffectFn(spell_uldum_hammer_SpellScript::HandleDummy2, EFFECT_1, SPELL_EFFECT_DUMMY);
                OnEffectHitTarget += SpellEffectFn(spell_uldum_hammer_SpellScript::HandleDummy3, EFFECT_2, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_uldum_hammer_SpellScript();
        }
};

void AddSC_uldum()
{
    new spell_uldum_hammer();
}
