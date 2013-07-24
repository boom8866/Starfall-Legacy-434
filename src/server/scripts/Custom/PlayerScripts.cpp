#include "Player.h"
#include "ScriptMgr.h"

class PetHandlingScripts : public PlayerScript
{
    public:
        PetHandlingScripts() : PlayerScript("player_pet_handling_scripts") { }

        void OnLogin(Player* player)
        {
            // Clear Glyph
            if (player->getLevel() >= 25 && !player->HasSpell(89964))
                player->learnSpell(89964, true);

            switch (player->getClass())
            {
                case CLASS_HUNTER:
                    player->GetSession()->SendStablePet(0);
                case CLASS_DEATH_KNIGHT:
                case CLASS_MAGE:
                case CLASS_WARLOCK:
                    player->SummonPet(PET_SLOT_CURRENT_PET);
                    return;
            }
        }
};
void AddSC_Player_scripts()
{
    new PetHandlingScripts();
}
