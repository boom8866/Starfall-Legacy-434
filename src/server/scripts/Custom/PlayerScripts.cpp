#include "Player.h"
#include "ScriptMgr.h"

class PetHandlingScripts : public PlayerScript
{
    public:
        PetHandlingScripts() : PlayerScript("player_pet_handling_scripts") { }

        void OnLogin(Player* player)
        {
            if(player->getClass() == CLASS_DEATH_KNIGHT)
            {
                if(player->HasAura(81130))// Name: Scarlet Fever
                    player->RemoveAura(81130);
                else if (player->HasAura(81325)) // Name: Brittle Bones (Rank 1)
                    player->RemoveAura(81325);
            }

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

class TolvirWeather : public PlayerScript
{
    public:
        TolvirWeather() : PlayerScript("player_tolvir_weather") { }

        void OnMapChanged(Player* player)
        {
            if (player->HasAura(82651) && player->GetMapId() != 755)
                player->RemoveAurasDueToSpell(82651);
        }
};

class TeleportUnstucker : public PlayerScript
{
    public:
        TeleportUnstucker() : PlayerScript("player_teleport_unstucker") { }

        void OnMapChanged(Player* player)
        {
            player->SendMovementFlagUpdate(true);

            if (player->getClass() == CLASS_DEATH_KNIGHT)
                if (player->GetPrimaryTalentTree(player->GetActiveSpec()) == TALENT_TREE_DEATH_KNIGHT_FROST)
                {
                    player->RemoveAurasDueToSpell(54637);
                    player->AddAura(54637, player);
                }
        }
};

void AddSC_Player_scripts()
{
    new PetHandlingScripts();
    new TolvirWeather();
    new TeleportUnstucker();
}
