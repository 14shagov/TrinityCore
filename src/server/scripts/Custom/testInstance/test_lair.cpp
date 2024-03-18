#include "ScriptMgr.h"
#include "test_lair.h"
#include "ScriptedGossip.h"
#include "GameObject.h"
#include "GameObjectAI.h"
#include "InstanceScript.h"

class go_drakkari_tablets : public GameObjectScript
{
public: 
    go_drakkari_tablets() : GameObjectScript("go_drakkari_tablets") { }

    struct go_drakkari_tabletsAI : public GameObjectAI
    {
        go_drakkari_tabletsAI(GameObject* go) : GameObjectAI(go), instance(go->GetInstanceScript()) { }

        InstanceScript* instance;

        bool OnGossipHello(Player* player) override
        {
            me->SetGoState(GO_STATE_ACTIVE);
            me->SetFlag(GO_FLAG_NOT_SELECTABLE);
            instance->SetGuidData(DATA_DRAKKARI_TABLETS, me->GetGUID());
            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return GetTestLairAI<go_drakkari_tabletsAI>(go);
    }
};

void AddSC_test_lair()
{
    new go_drakkari_tablets();
}
