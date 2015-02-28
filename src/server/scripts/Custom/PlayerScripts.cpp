#include "Player.h"
#include "ScriptMgr.h"

class PetHandlingScripts : public PlayerScript
{
    public:
        PetHandlingScripts() : PlayerScript("player_pet_handling_scripts") { }

        void OnLogin(Player* player)
        {
            if (player->getClass() == CLASS_DEATH_KNIGHT)
            {
                if (player->HasAura(81130))// Name: Scarlet Fever
                    player->RemoveAura(81130);
                else if (player->HasAura(81325)) // Name: Brittle Bones (Rank 1)
                    player->RemoveAura(81325);
            }

            // Vanishing Powder
            if (player->getLevel() >= 25 && player->getLevel() <= 80 && !player->HasSpell(89964))
                player->learnSpell(89964, true);

            // Dust of Disappearance
            if (player->getLevel() >= 81)
            {
                if (player->HasSpell(89964))
                    player->removeSpell(89964);
                if (!player->HasSpell(90647))
                    player->learnSpell(90647, true);
            }

            switch (player->getClass())
            {
                case CLASS_HUNTER:
                    player->GetSession()->SendStablePet(0);
                    return;
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
            if (player->getClass() == CLASS_DEATH_KNIGHT)
            {
                if (player->GetPrimaryTalentTree(player->GetActiveSpec()) == TALENT_TREE_DEATH_KNIGHT_FROST)
                {
                    player->RemoveAurasDueToSpell(54637);
                    player->AddAura(54637, player);
                }
            }
        }

    protected:
        float x, y, z;
};

class LoginMaster : public PlayerScript
{
    public:
        LoginMaster() : PlayerScript("player_login_master") { }

        void OnLogin(Player* player)
        {
            if (player->getClass() == CLASS_DEATH_KNIGHT)
                if (player->HasAura(81326))
                    player->RemoveAurasDueToSpell(81326);
        }
};

void AddSC_Player_scripts()
{
    new PetHandlingScripts();
    new TolvirWeather();
    new TeleportUnstucker();
    new LoginMaster();
}
