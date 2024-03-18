#include "ScriptMgr.h"
#include "Creature.h"
#include "test_lair.h"
#include "InstanceScript.h"
#include "GameObject.h"
#include "CreatureAI.h"
#include "Map.h"
#include "TemporarySummon.h"
#include <numeric>
#include <random>

enum TLSpell
{
    SPELL_LOW_POLY_BLUE_FIRE = 46679,
    SPELL_LOW_POLY_FIRE      = 51195
};

DoorData const doorData[] =
{
    { GO_ICEWALL,           DATA_DRAKKARI_TABLETS,     DOOR_TYPE_PASSAGE },
    { 0,                    0,                         DOOR_TYPE_ROOM } // END
};

Position const LadySpawnsPos[] =
{
    { 1439.09f, -3483.89f, -20.9984f, 5.38388f },
    { 1457.30f, -3475.69f, -20.9992f, 4.84588f },
    { 1472.84f, -3481.59f, -20.9982f, 3.95839f },
    { 1482.81f, -3497.07f, -20.9996f, 3.87591f }
};

class instance_test_lair : public InstanceMapScript
{
public:
    instance_test_lair() : InstanceMapScript(TLScriptName, 169) { }

    struct instance_test_lair_InstanceMapScript : public InstanceScript
    {
        instance_test_lair_InstanceMapScript(InstanceMap* map) : InstanceScript(map)
        {
            SetHeaders(DataHeader);
            SetBossNumber(EncounterCount);
            LoadDoorData(doorData);
            InitializeRandomSequence();
            _aliveLadies = 0;
            _tabletGUIDs.clear();
            _flameGUIDs.clear();
        }

        void OnGameObjectCreate(GameObject* go) override
        {
            switch (go->GetEntry())
            {
            case GO_ICEWALL:
                AddDoor(go, true);
                break;
            case GO_DRAKKARI_TABLETS:
            {
                _tabletGUIDs.push_back(go->GetGUID());
                Position pos = go->GetPosition();
                pos.m_positionZ = pos.GetPositionZ() + 5.0f;
                if (Creature* creature = go->SummonCreature(NPC_LOW_POLY_FIRE, pos))
                    _flameGUIDs.push_back(creature->GetGUID());
            }
            break;
            default:
                break;
            }
        }

        void OnGameObjectRemove(GameObject* go) override
        {
            switch (go->GetEntry())
            {
            case GO_ICEWALL:
                AddDoor(go, false);
                break;
            default:
                break;
            }
        }

        void OnUnitDeath(Unit* unit) override
        {
            switch (unit->GetEntry())
            {
            case NPC_LADY:
                --_aliveLadies;
                if (_aliveLadies <= 0)
                {
                    for (const ObjectGuid objectGuid : _tempLadiesGUIDs)
                        if (Creature* creature = instance->GetCreature(objectGuid))
                            creature->DespawnOrUnsummon();
                    _tempLadiesGUIDs.clear();
                    LockTablet(false);
                    AddRedFire(false);
                }
                break;
            default:
                break;
            }
        }

        void SetGuidData(uint32 DataId, ObjectGuid data) override
        {
            switch (DataId)
            {
            case DATA_DRAKKARI_TABLETS:
                for (uint8 i = 0; i < _rand.size(); ++i)
                {
                    // Check if the data associated with the current index in '_tabletGUIDs' matches the given 'data'
                    if (_tabletGUIDs[_rand[i]] == data)
                    {
                        if (i == 0)
                        {
                            // If 'i' is 0, we just activate the tablet.
                            if (Creature* creature = instance->GetCreature(_flameGUIDs[_rand[i]]))
                                creature->AddAura(SPELL_LOW_POLY_BLUE_FIRE, creature);
                        }
                        else
                        {
                            //In other cases, evaluate the defined state.
                            if (EvaluateTablet(instance->GetGameObject(_tabletGUIDs[_rand[i - 1]]), instance->GetCreature(_flameGUIDs[_rand[i]])))
                                if (i == 4) // if 'i' is 4, it means that it is the last tablet and the door should open
                                    SetBossState(DATA_DRAKKARI_TABLETS, DONE);
                        }
                    }
                }
                break;
            default:
                break;
            }
        }

        void InitializeRandomSequence()
        {
            std::iota(std::begin(_rand), std::end(_rand), 0);       // fill the array
            std::random_device rd = std::random_device{};           // create a different sequence each time it is run
            std::mt19937 rng = std::default_random_engine{ rd() };  // random number generator
            std::shuffle(std::begin(_rand), std::end(_rand), rng);  // shuffle the elements
        }

        bool EvaluateTablet(GameObject* go, Creature* creature)
        {
            if (go && creature)
            {
                // Check that the order of the selected tablets is correct
                if (go->GetGoState() != GO_STATE_ACTIVE)
                {
                    SetTabletInactive(); // Restart the tablets
                    return false;
                }
                else
                    creature->AddAura(SPELL_LOW_POLY_BLUE_FIRE, creature); // Mark the tablet as used
            }
            return true;
        }

        void LockTablet(bool lock)
        {
            for (const ObjectGuid objectGuid : _tabletGUIDs)
            {
                if (GameObject* go = instance->GetGameObject(objectGuid))
                {
                    if (lock)
                        go->SetFlag(GO_FLAG_NOT_SELECTABLE);
                    else
                    {
                        go->SetGoState(GO_STATE_READY);
                        go->RemoveFlag(GO_FLAG_NOT_SELECTABLE);
                    }
                }
            }
        }

        void AddRedFire(bool add)
        {
            for (const ObjectGuid objectGuid : _flameGUIDs)
            {
                if (Creature* creature = instance->GetCreature(objectGuid))
                {
                    if (add)
                    {
                        creature->RemoveAura(SPELL_LOW_POLY_BLUE_FIRE);
                        creature->AddAura(SPELL_LOW_POLY_FIRE, creature); // Mark the tablet as locked
                    }
                    else
                        creature->RemoveAura(SPELL_LOW_POLY_FIRE);
                }
            }
        }

        void SetTabletInactive()
        {
            LockTablet(true);
            AddRedFire(true);
            for (uint8 i = 0; i < 4; ++i)
                if (Creature* creature = instance->SummonCreature(NPC_LADY, LadySpawnsPos[i]))
                    _tempLadiesGUIDs.push_back(creature->GetGUID());
            _aliveLadies = 4;
        }

    private:
        GuidVector _tabletGUIDs;
        GuidVector _flameGUIDs;
        GuidVector _tempLadiesGUIDs;
        std::array<uint8, 5> _rand;
        uint32 _aliveLadies;
    };

    InstanceScript* GetInstanceScript(InstanceMap* map) const override
    {
        return new instance_test_lair_InstanceMapScript(map);
    }
};

void AddSC_instance_test_lair()
{
    new instance_test_lair();
}
