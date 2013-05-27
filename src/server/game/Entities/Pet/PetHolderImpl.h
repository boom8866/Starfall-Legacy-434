#ifndef _PET_HOLDER_IMPL_H_
#define _PET_HOLDER_IMPL_H_

#include "PetHolder.h"

class PetHolderHunter : public PetHolder
{
    public:
        PetHolderHunter(Player *player) : PetHolder(PET_STORAGE_SIZE_HUNTER, player) { }
        ~PetHolderHunter() { }

        PetSlot GetSlotForPet(uint32 entry);
        void SwitchSlots(PetSlot slot1, PetSlot slot2);
};

class PetHolderWarlock : public PetHolder
{
    public:
        PetHolderWarlock(Player *player) : PetHolder(PET_STORAGE_SIZE_WARLOCK, player) { }
        ~PetHolderWarlock() { }

        PetSlot GetSlotForPet(uint32 entry);
};

class PetHolderDK : public PetHolder
{
    public:
        PetHolderDK(Player *player) : PetHolder(PET_STORAGE_SIZE_DK, player) { }
        ~PetHolderDK() { }

        PetSlot GetSlotForPet(uint32 entry);
};

class PetHolderMage : public PetHolder
{
    public:
        PetHolderMage(Player *player) : PetHolder(PET_STORAGE_SIZE_MAGE, player) { }
        ~PetHolderMage() { }

        PetSlot GetSlotForPet(uint32 entry);
};

#endif /* _PET_HOLDER_IMPL_H_ */
