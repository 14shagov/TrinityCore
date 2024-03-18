#ifndef TEST_LAIR_H_
#define TEST_LAIR_H_

#include "CreatureAIImpl.h"

#define TLScriptName "instance_test_lair"
#define DataHeader   "TL"

uint32 const EncounterCount = 1;

enum TLDataTypes
{
    // Encounter States/Boss GUIDs
    DATA_DRAKKARI_TABLETS       = 0,
};

enum TLCreatureIds
{
    NPC_LOW_POLY_FIRE           = 90016,
    NPC_LADY                    = 16065,
};

enum TLGameObjectIds
{
    GO_DRAKKARI_TABLETS         = 250001,
    GO_ICEWALL                  = 250006,
};

template <class AI, class T>
inline AI* GetTestLairAI(T* obj)
{
    return GetInstanceAI<AI>(obj, TLScriptName);
}

#endif // TEST_LAIR_H_
