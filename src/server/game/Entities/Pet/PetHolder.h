#ifndef _PET_HOLDER_H_
#define _PET_HOLDER_H_

#include "PetDefines.h"
#include "Define.h"
#include "SharedDefines.h"
#include "Unit.h"
#include "Errors.h"

struct PlayerPet
{
    PlayerPet() : id(0), entry(0), owner(0), modelid(0), level(0), exp(0), reactstate(REACT_AGGRESSIVE), slot(PET_SLOT_NULL_SLOT), renamed(false), curhealth(0), curmana(0), savetime(0), summon_spell_id(0), pet_type(MAX_PET_TYPE), state(PET_STATE_NONE) {}    
    //  0   1       2      3         4     5        6        7     8      9      10          11      12         13         14          15
    // id, entry, owner, modelid, level, exp, Reactstate, slot, name, renamed, curhealth, curmana, abdata, savetime, CreatedBySpell, PetType

    uint32 id;
    uint32 entry;
    uint32 owner;
    uint32 modelid;
    uint16 level;
    uint32 exp;
    ReactStates reactstate;
    PetSlot slot;   
    std::string name;
    bool renamed;
    uint32 curhealth;
    uint32 curmana;
    std::string abdata;
    uint32 summon_spell_id;
    uint32 savetime;
    PetType pet_type;
    PetState state;
};

class Player;

class PetHolder
{
    public:
        virtual void LoadPets();

        PetSlot GetCurrentPetSlot() const { return m_currentSlot; }
        void SetCurrentSlot(PetSlot slot);

        PlayerPet *GetPetData(PetSlot slot);

        void SynchCurrentPet();

        void SaveToDB();
        void DeleteFromDB(PetSlot slot);

        virtual PetSlot GetSlotForPet(uint32 entry) { return PET_SLOT_NULL_SLOT; }
        virtual void SwitchSlots(PetSlot slot1, PetSlot slot2) { }

    protected:
        PetHolder(uint8 PetStorageSize, Player* player) : m_size(PetStorageSize), m_player(player)
        {
            ASSERT(m_player);
            m_petData = new PlayerPet[m_size];
            m_currentSlot = PET_SLOT_FIRST_SLOT;
        }

        virtual ~PetHolder() { delete m_petData; }

        void SaveToDB(PetSlot slot);

        Player *m_player;
        PetSlot m_currentSlot;

        uint8 m_size;
        PlayerPet *m_petData;
};

#endif /* _PET_HOLDER_H_ */
