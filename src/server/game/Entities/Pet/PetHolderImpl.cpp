#include "PetHolderImpl.h"
#include "Pet.h"
#include "Player.h"
#include "DatabaseEnv.h"

PetSlot PetHolderHunter::GetSlotForPet(uint32 entry)
{
    if (entry)
    {
        for (uint8 slot = PET_SLOT_FIRST_SLOT; slot < m_size; ++slot)
            if (m_petData[slot].state != PET_STATE_NONE && m_petData[slot].entry == entry)
                return PetSlot(slot);
    }
    else
    {
        uint8 max = 0;
        if (m_player->HasSpell(83245))
            max = 5;
        else if (m_player->HasSpell(83244))
            max = 4;
        else if (m_player->HasSpell(83243))
            max = 3;
        else if (m_player->HasSpell(83242))
            max = 2;
        else if (m_player->HasSpell(883))
            max = 1;

        for (uint8 slot = PET_SLOT_FIRST_SLOT; slot < max; ++slot)
            if (m_petData[slot].state == PET_STATE_NONE)
                return PetSlot(slot);
    }

    return PET_SLOT_NULL_SLOT;
}

void PetHolderHunter::SwitchSlots(PetSlot slot1, PetSlot slot2)
{
    PlayerPet temp(m_petData[slot1]);

    memcpy(&(m_petData[slot1]), &(m_petData[slot2]), sizeof(PlayerPet));
    memcpy(&(m_petData[slot2]), &(temp), sizeof(PlayerPet));

    // We have to correct the slot values
    m_petData[slot1].slot = slot1;
    m_petData[slot2].slot = slot2;
    
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_CHAR_PET_SLOT);
    stmt->setUInt8(0, uint8(slot2));
    stmt->setUInt32(1, m_petData[slot2].id);
    CharacterDatabase.Execute(stmt);


    if (m_petData[slot1].state != PET_STATE_NONE)
    {
        PreparedStatement* stmt2 = CharacterDatabase.GetPreparedStatement(CHAR_UPD_CHAR_PET_SLOT);
        stmt2->setUInt8(0, uint8(slot1));
        stmt2->setUInt32(1, m_petData[slot1].id);
        CharacterDatabase.Execute(stmt2);
    }
}

PetSlot PetHolderWarlock::GetSlotForPet(uint32 entry)
{
    switch (entry)
    {
        case 416:
            return PET_SLOT_FIRST_SLOT;
        case 1860:
            return PetSlot(PET_SLOT_FIRST_SLOT + 1);
        case 1863:
            return PetSlot(PET_SLOT_FIRST_SLOT + 2);
        case 417:
            return PetSlot(PET_SLOT_FIRST_SLOT + 3);
        case 17252:
            return PetSlot(PET_SLOT_FIRST_SLOT + 4);
        default:
            return PET_SLOT_NULL_SLOT;
    }
}

PetSlot PetHolderDK::GetSlotForPet(uint32 entry)
{
    if (entry == 26125)
        return PET_SLOT_FIRST_SLOT;

    return PET_SLOT_NULL_SLOT;
}

PetSlot PetHolderMage::GetSlotForPet(uint32 entry)
{
    if (entry == 510)
        return PET_SLOT_FIRST_SLOT;

    return PET_SLOT_NULL_SLOT;
}
