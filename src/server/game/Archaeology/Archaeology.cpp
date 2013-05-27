#include "Archaeology.h"
#include "DBCStore.h"
#include "Player.h"

Archaeology::Archaeology(Player *player): _player(player)
{
    memset(_site, 0, sizeof(struct SiteData) * CONTINENT_SITES * COUNT_CONT);

    _continentState[CONT_EASTERN] = STATE_NULL;
    _continentState[CONT_KALIMDOR] = STATE_NULL;
    _continentState[CONT_OUTLAND] = STATE_NULL;
    _continentState[CONT_NORTHREND] = STATE_NULL;
}

void Archaeology::Initialize()
{
    if (!_player || !_player->HasSkill(SKILL_ARCHAEOLOGY))
        return;

    LoadSitesFromDB();
    VerifySites();

    LoadCompletedProjectsFromDB();
    LoadCurrentProjectsFromDB();
    VerifyProjects();
}

void Archaeology::Learn()
{
    _continentState[CONT_EASTERN] = STATE_USE;
    _continentState[CONT_KALIMDOR] = STATE_USE;
    _continentState[CONT_OUTLAND] = STATE_NULL;
    _continentState[CONT_NORTHREND] = STATE_NULL;
    RegenerateAllSites();

    InitBranches();
    VerifyProjects();
}

void Archaeology::UnLearn()
{
    _continentState[CONT_EASTERN] = STATE_NULL;
    _continentState[CONT_KALIMDOR] = STATE_NULL;
    _continentState[CONT_OUTLAND] = STATE_NULL;
    _continentState[CONT_NORTHREND] = STATE_NULL;
    RegenerateAllSites();

    CleanProjects();
}

void Archaeology::Update()
{
    uint16 skillValue = _player->GetSkillValue(SKILL_ARCHAEOLOGY);

    if (SKILL_OUTLAND <= skillValue && _continentState[CONT_OUTLAND] == STATE_NULL)
    {
        _continentState[CONT_OUTLAND] = STATE_USE;
        RegenerateContinent(CONT_OUTLAND);
    }

    if(SKILL_NORTHREND <= skillValue && _continentState[CONT_NORTHREND] == STATE_NULL)
    {
        _continentState[CONT_NORTHREND] = STATE_USE;
        RegenerateContinent(CONT_NORTHREND);
    }

    if(SKILL_CATA <= skillValue)
    {
        _continentState[CONT_EASTERN] = STATE_EXT;
        _continentState[CONT_KALIMDOR] = STATE_EXT;
    }
}
