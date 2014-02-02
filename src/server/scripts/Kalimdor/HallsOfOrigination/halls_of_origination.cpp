
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
#include "halls_of_origination.h"

class go_hoo_lift_console : public GameObjectScript
{
public:
    go_hoo_lift_console() : GameObjectScript("go_hoo_lift_console") { }

    bool OnGossipSelect(Player* player, GameObject* go, uint32 sender, uint32 action)
    {
            if (sender != GOSSIP_SENDER_MAIN)
                return false;
            if (!player->getAttackers().empty())
                return false;
        switch (action)
        {
            case 200: // Bring to first floor
                if (player->GetPositionZ() > 90.0f)
                    if (GameObject* elevator = go->FindNearestGameObject(GO_LIFT_OF_THE_MAKERS, 500.0f))
                    {
                        elevator->SetLootState(GO_READY);
                        elevator->UseDoorOrButton(5000);
                    }
                break;
            case 201: // Bring to second floor
                if (player->GetPositionZ() < 90.0f)
                    if (GameObject* elevator = go->FindNearestGameObject(GO_LIFT_OF_THE_MAKERS, 500.0f))
                    {
                        elevator->SetLootState(GO_READY);
                        elevator->UseDoorOrButton(5000);
                    }
                break;
        }
        player->CLOSE_GOSSIP_MENU();
        return true;
    }

    bool OnGossipHello(Player* player, GameObject* go)
    {

        if (InstanceScript* instance = go->GetInstanceScript())
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Bring elevator to first floor.", GOSSIP_SENDER_MAIN, 200);
            if (instance->GetBossState(DATA_ANRAPHET) == DONE || instance->GetBossState(DATA_EARTHRAGER_PTAH) == DONE) //count of 2 collossus death
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Bring elevator to second floor.", GOSSIP_SENDER_MAIN, 201);
        }

        player->SEND_GOSSIP_MENU(go->GetGOInfo()->GetGossipMenuId(), go->GetGUID());
        return true;
    }
};

void AddSC_halls_of_origination()
{
    new go_hoo_lift_console();
}
