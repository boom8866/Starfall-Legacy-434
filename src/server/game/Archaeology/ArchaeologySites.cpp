#include "Archaeology.h"
#include "DBCStore.h"
#include "Player.h"

// use squared distances so we don't have to use the squareroot
enum DigSiteDist
{
    DIST_FAR            = 10000,    // 100 yards
    DIST_MED            = 900,      // 30  yards
    DIST_CLOSE          = 100,      // 10  yards
};

enum SurveyBot
{
    FAR_SURVEYBOT       = 206590,
    MED_SURVEYBOT       = 206589,
    CLOSE_SURVEYBOT     = 204272,
};

void Archaeology::LoadSitesFromDB()
{
    QueryResult result = CharacterDatabase.PQuery("select site, type, finds from character_archaeology_sites where guid=%u", _player->GetGUIDLow());

    if (!result)
        return;

    uint32 count = 0;
    do {
        Field *fields = result->Fetch();
        uint32 site = fields[0].GetUInt8();
        uint16 type = fields[1].GetUInt16();
        uint8 finds = fields[2].GetUInt8();
        SetSite(site, type, finds);
        count++;
    } while (result->NextRow());
}

void Archaeology::VerifySites()
{
    uint16 skillValue = _player->GetSkillValue(SKILL_ARCHAEOLOGY);

    if (skillValue >= SKILL_OUTLAND)
        _continentState[CONT_OUTLAND] = STATE_USE;
    else
        _continentState[CONT_OUTLAND] = STATE_NULL;

    if (skillValue >= SKILL_NORTHREND)
        _continentState[CONT_NORTHREND] = STATE_USE;
    else
        _continentState[CONT_NORTHREND] = STATE_NULL;

    if (skillValue >= SKILL_CATA)
    {
        _continentState[CONT_EASTERN] = STATE_EXT;
        _continentState[CONT_KALIMDOR] = STATE_EXT;
    }
    else
    {
        _continentState[CONT_EASTERN] = STATE_USE;
        _continentState[CONT_KALIMDOR] = STATE_USE;
    }

    RegenerateAllSites();
}

void Archaeology::UseSite()
{
    float dist;
    uint32 position = GetNearestSite(dist);

    if (0 == position)
        return;

    position--;

    if (dist > DIST_CLOSE)
    {
        uint32 goID;
        float angle = atan2(_site[position].y - _player->GetPositionY(), _site[position].x - _player->GetPositionX());

        if (dist < DIST_MED)
        {
            goID = CLOSE_SURVEYBOT;     // within the med radius -> green light
            angle += frand(-M_PI / 12, M_PI / 12);
        }
        else if (dist < DIST_FAR)
        {
            goID = MED_SURVEYBOT;       // within the far radius -> yellow light
            angle += frand(-M_PI / 6, M_PI / 6);
        }
        else
        {
            goID = FAR_SURVEYBOT;       // outside far radius -> red light
            angle += frand(-M_PI / 3, M_PI / 3);
        }

        while (angle < 0)
            angle += 2 * M_PI;

        while (angle > 2 * M_PI)
            angle -= 2 * M_PI;

        float x      = _player->GetPositionX() + cos(angle) * 2.0f;
        float y      = _player->GetPositionY() + sin(angle) * 2.0f;
        float z      = _player->GetPositionZ();
        float ground = _player->GetMap()->GetWaterOrGroundLevel(x, y, z, &ground, false, true);

        if (abs(z - ground) < 1.5f)
        {
            _player->SummonGameObject(goID, x, y, ground, angle, 0, 0, 0, 0, 4);
            return;
        }
        else
        {
            _player->GetSession()->SendNotification("You can't use that here");
            return;
        }
    }

    // Spawn the correct Find Object Here
    uint32 goId  = sArchaeologyMgr->GetSiteType(_site[position].entry);
    float x      = _player->GetPositionX() + cos(_player->GetOrientation() + M_PI) * 2.0f;
    float y      = _player->GetPositionY() + sin(_player->GetOrientation() + M_PI) * 2.0f;
    float z      = _player->GetPositionZ();
    float ground = _player->GetMap()->GetWaterOrGroundLevel(x, y, z, &ground, false, true);

    // Spawn object
    _player->SummonGameObject(goId, x, y, ground, 0, 0, 0, 0, 0, 60);
    (_site[position].state)++;

    if (_site[position].state >= DIGS_PER_SITE)
         RegeneratePosition(position, GetContinent());
    else
    {
        CharacterDatabase.PExecute("update character_archaeology_sites set finds =%u where site=%u and guid=%u", _site[position].state, position, _player->GetGUIDLow());
        sArchaeologyMgr->SetSiteCoords(_site[position]);
    }
}

Continent Archaeology::GetContinent()
{
    switch (_player->GetMapId())
    {
        case 0:
            return CONT_EASTERN;
        case 1:
            return CONT_KALIMDOR;
        case 530:
            return CONT_OUTLAND;
        case 571:
            return CONT_NORTHREND;
    }
    return COUNT_CONT;
}

uint32 Archaeology::GetNearestSite(float &distance)
{
    uint32 cont = GetContinent();
    
    if (COUNT_CONT == cont)
        return 0;
    
    uint32 position = cont * CONTINENT_SITES;

    float pX = _player->GetPositionX();
    float pY = _player->GetPositionY();

    float dist = (pX - _site[position].x) * (pX - _site[position].x) + (pY - _site[position].y) * (pY - _site[position].y);

    for (uint32 i = cont * CONTINENT_SITES + 1; i < (cont + 1) * CONTINENT_SITES; i++)
    {
        float dist2 = (pX -_site[i].x) * (pX -_site[i].x) + (pY - _site[i].y) * (pY - _site[i].y);
        if (dist2 < dist)
        {
            position = i;
            dist = dist2;
        }
    }
    distance = dist;

    return position + 1;
}

void Archaeology::SetSite(uint32 position, uint16 entry, uint32 state)
{
    _site[position].entry = entry;
    _site[position].state = state;
    _player->SetUInt16Value(PLAYER_FIELD_RESEARCH_SITE_1 + (position / 2), position % 2, entry);
    
    if (entry == 0)
    {
        _site[position].x = 0.f;
        _site[position].y = 0.f;
    }
    else
        sArchaeologyMgr->SetSiteCoords(_site[position]);
}

void Archaeology::RegeneratePosition(uint32 position, Continent continent)
{
    if (_site[position].entry && sResearchSiteStore.LookupEntry(_site[position].entry) && _site[position].state < DIGS_PER_SITE)
        return;

    uint16 entry = sArchaeologyMgr->GetNewSite(continent, _site, _continentState[continent] == STATE_EXT, _player->getLevel());
    SetSite(position, entry);
    CharacterDatabase.PExecute("replace into character_archaeology_sites values (%u, %u, %u, %u);", _player->GetGUIDLow(), position, entry, _site[position].state);
}

void Archaeology::RegenerateContinent(Continent continent)
{
    if (_continentState[continent] == STATE_NULL)
    {
        uint32 position = continent * CONTINENT_SITES;

        for (int i = 0; i < CONTINENT_SITES; i++)
            SetSite(position + i, 0);
        return;
    }

    uint32 position = continent * CONTINENT_SITES;
    
    for (uint32 i = 0; i < CONTINENT_SITES; i++)
        RegeneratePosition(position + i, continent);
}

void Archaeology::RegenerateAllSites()
{
    for (uint32 i = 0; i < COUNT_CONT; i++)
        RegenerateContinent(Continent(i));
}
