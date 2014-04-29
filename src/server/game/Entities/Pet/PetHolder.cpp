#include "PetHolder.h"
#include "Player.h"
#include "Pet.h"

void PetHolder::LoadPets()
{
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHAR_PET_LIST);
    stmt->setUInt32(0, m_player->GetGUIDLow());
    stmt->setUInt8(1, uint8(m_size));
    PreparedQueryResult result = CharacterDatabase.Query(stmt);

    if (!result)
    {
        sLog->outDebug(LOG_FILTER_GENERAL, "PetHolder::LoadPets No pets for player:%u", m_player->GetGUIDLow());
        return;
    }

    do
    {
        Field* fields = result->Fetch();

        PetSlot slot = PetSlot(fields[11].GetUInt8());
        if (slot >= m_size || slot < PET_SLOT_FIRST_SLOT)
            sLog->outError(LOG_FILTER_GENERAL, "PetHolder::LoadPets trying to populate a not existant slot");
        else if (m_petData[slot].state != PET_STATE_NONE)
            sLog->outError(LOG_FILTER_GENERAL, "PetHolder::LoadPets trying to populate an already populated slot");
        else
        {
            m_petData[slot].id               = fields[0].GetUInt32();
            m_petData[slot].entry            = fields[1].GetUInt32();
            m_petData[slot].owner            = fields[2].GetUInt32();
            m_petData[slot].modelid          = fields[3].GetUInt32();
            m_petData[slot].summon_spell_id  = fields[4].GetUInt32();
            m_petData[slot].pet_type         = PetType(fields[5].GetUInt8());
            m_petData[slot].level            = fields[6].GetUInt16();
            m_petData[slot].exp              = fields[7].GetUInt32();
            m_petData[slot].reactstate       = ReactStates(fields[8].GetUInt8());
            m_petData[slot].name             = fields[9].GetString();
            m_petData[slot].renamed          = bool(fields[10].GetUInt8());
            m_petData[slot].slot             = slot;
            m_petData[slot].curhealth        = fields[12].GetUInt32();
            m_petData[slot].curmana          = fields[13].GetUInt32();
            m_petData[slot].savetime         = fields[14].GetUInt32();
            m_petData[slot].abdata           = fields[15].GetString();
            m_petData[slot].state            = PET_STATE_ALIVE;
        }
    }
    while (result->NextRow());

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_PET_SLOT);
    stmt->setUInt32(0, m_player->GetGUIDLow());
    result = CharacterDatabase.Query(stmt);

    // this should NEVER happen
    if (!result)
        return;

    Field* fields = result->Fetch();
    m_currentSlot = PetSlot(fields[0].GetInt8());

    if (m_currentSlot > m_size || m_currentSlot < PET_SLOT_FIRST_SLOT)
        SetCurrentSlot(PET_SLOT_FIRST_SLOT);
}

void PetHolder::SetCurrentSlot(PetSlot slot)
{
    if (slot >= 0 && slot < m_size)
    {
        m_currentSlot = slot;

        PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_PET_SLOT);
        stmt->setUInt8(0, int8(m_currentSlot));
        stmt->setUInt32(1, m_player->GetGUIDLow());
        CharacterDatabase.Execute(stmt);
    }
}

PlayerPet *PetHolder::GetPetData(PetSlot slot)
{
    if (PET_SLOT_CURRENT_PET == slot)
        return &(m_petData[m_currentSlot]);
    else if (m_size > slot && slot >= PET_SLOT_FIRST_SLOT)
        return &(m_petData[slot]);

    return NULL;
}

void PetHolder::SynchCurrentPet()
{
    Pet *pet = m_player->GetPet();

    if (!pet || (GetSlotForPet(pet->GetEntry()) == PET_SLOT_NULL_SLOT && pet->getPetType() != HUNTER_PET))
        return;

    if (m_currentSlot >= PET_SLOT_FIRST_SLOT && m_currentSlot < m_size)
    {
        std::ostringstream ss_abdata;

        for (uint32 i = ACTION_BAR_INDEX_START; i < ACTION_BAR_INDEX_END; ++i)
        {
            ss_abdata << uint32(pet->m_charmInfo->GetActionBarEntry(i)->GetType()) << ' '
                      << uint32(pet->m_charmInfo->GetActionBarEntry(i)->GetAction()) << ' ';
        }

        std::string const& str_abdata = ss_abdata.str();

        m_petData[m_currentSlot].id              = pet->m_charmInfo->GetPetNumber();
        m_petData[m_currentSlot].entry           = pet->GetEntry();
        m_petData[m_currentSlot].owner           = pet->GetOwner()->GetGUIDLow();
        m_petData[m_currentSlot].modelid         = pet->GetNativeDisplayId();
        m_petData[m_currentSlot].level           = uint16(pet->getLevel());
        m_petData[m_currentSlot].exp             = pet->GetUInt32Value(UNIT_FIELD_PETEXPERIENCE);
        m_petData[m_currentSlot].reactstate      = pet->GetReactState();
        m_petData[m_currentSlot].slot            = m_currentSlot;
        m_petData[m_currentSlot].name            = pet->GetName().c_str();
        m_petData[m_currentSlot].renamed         = pet->HasByteFlag(UNIT_FIELD_BYTES_2, 2, UNIT_CAN_BE_RENAMED);
        m_petData[m_currentSlot].curhealth       = pet->GetHealth();
        m_petData[m_currentSlot].curmana         = pet->IsPetGhoul() ? 100 : pet->GetPower(POWER_MANA);
        m_petData[m_currentSlot].abdata          = str_abdata.c_str();
        m_petData[m_currentSlot].summon_spell_id = pet->GetUInt32Value(UNIT_CREATED_BY_SPELL);
        m_petData[m_currentSlot].savetime        = time(NULL);
        m_petData[m_currentSlot].pet_type        = pet->getPetType();
        m_petData[m_currentSlot].state           = pet->GetHealth() ? PET_STATE_ALIVE : PET_STATE_DEAD;
    }
}

void PetHolder::SaveToDB()
{
    if (Pet *pet = m_player->GetPet())
        SynchCurrentPet();

    for (uint8 slot = PET_SLOT_FIRST_SLOT; slot < m_size; ++slot)
        SaveToDB(PetSlot(slot));
}

void PetHolder::SaveToDB(PetSlot slot)
{
    if (m_petData[slot].state == PET_STATE_NONE)
        return;

    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_REP_CHAR_PET);

    std::string name = m_petData[slot].name;
    CharacterDatabase.EscapeString(name);

    stmt->setUInt32(0, m_petData[slot].id);
    stmt->setUInt32(1, m_petData[slot].entry);
    stmt->setUInt32(2, m_petData[slot].owner);
    stmt->setUInt32(3, m_petData[slot].modelid);
    stmt->setUInt32(4, m_petData[slot].summon_spell_id);
    stmt->setUInt8(5, uint8(m_petData[slot].pet_type));
    stmt->setUInt16(6, m_petData[slot].level);
    stmt->setUInt32(7, m_petData[slot].exp);
    stmt->setUInt8(8, uint8(m_petData[slot].reactstate));
    stmt->setString(9, name);
    stmt->setUInt8(10, uint8(m_petData[slot].renamed));
    stmt->setUInt8(11, uint8(slot));
    stmt->setUInt32(12, m_petData[slot].curhealth);
    stmt->setUInt32(13, m_petData[slot].curmana);
    stmt->setUInt32(14, m_petData[slot].savetime);
    stmt->setString(15, m_petData[slot].abdata);

    CharacterDatabase.Execute(stmt);
}

void PetHolder::DeleteFromDB(PetSlot slot)
{
    if (slot == PET_SLOT_CURRENT_PET)
        slot = m_currentSlot;
    else if (slot >= m_size || slot < PET_SLOT_FIRST_SLOT)
        return;

    if (m_petData[slot].state == PET_STATE_NONE)
        return;

    Pet::DeleteFromDB(m_petData[slot].id);

    m_petData[slot].id = 0;
    m_petData[slot].entry = 0;
    m_petData[slot].owner = 0;
    m_petData[slot].modelid = 0;
    m_petData[slot].level = 0;
    m_petData[slot].exp = 0;
    m_petData[slot].reactstate = REACT_AGGRESSIVE;
    m_petData[slot].slot = PET_SLOT_NULL_SLOT;
    m_petData[slot].renamed = false;
    m_petData[slot].curhealth = 0;
    m_petData[slot].curmana = 0;
    m_petData[slot].savetime = 0;
    m_petData[slot].summon_spell_id = 0;
    m_petData[slot].pet_type = MAX_PET_TYPE;
    m_petData[slot].state = PET_STATE_NONE;
}
