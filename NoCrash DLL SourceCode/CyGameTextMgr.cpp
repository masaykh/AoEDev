//
// Python wrapper class for CyGameTextMgr
//
#include "CvGameCoreDLL.h"
#include "CvGameTextMgr.h"
#include "CyGameTextMgr.h"
#include "CyCity.h"
#include "CyDeal.h"
#include "CyUnit.h"

CyGameTextMgr::CyGameTextMgr() :
m_pGameTextMgr(NULL)
{
	m_pGameTextMgr = &CvGameTextMgr::GetInstance();
}

CyGameTextMgr::CyGameTextMgr(CvGameTextMgr* pGameTextMgr) :
m_pGameTextMgr(pGameTextMgr)   // was m_pGameTextMgr(m_pGameTextMgr) — self-init bug
{}

void CyGameTextMgr::Reset()
{
	GAMETEXT.Reset();
}

std::wstring CyGameTextMgr::getTimeStr(int iGameTurn, bool bSave)
{
	CvWString str;
	GAMETEXT.setTimeStr(str, iGameTurn, bSave);
	return str;
}

std::wstring CyGameTextMgr::getDateStr(int iGameTurn, bool bSave, int /*CalendarTypes*/ eCalendar, int iStartYear, int /*GameSpeedTypes*/ eSpeed)
{
	CvWString str;
	GAMETEXT.setDateStr(str, iGameTurn, bSave, (CalendarTypes)eCalendar, iStartYear, (GameSpeedTypes)eSpeed);
	return str;
}

std::wstring CyGameTextMgr::getInterfaceTimeStr(int /*PlayerTypes*/ iPlayer)
{
	CvWString szBuffer;
	GAMETEXT.setInterfaceTime(szBuffer, ((PlayerTypes)iPlayer));
	return szBuffer;
}

std::wstring CyGameTextMgr::getGoldStr(int /*PlayerTypes*/ iPlayer)
{
	CvWString szBuffer;
	GAMETEXT.setGoldStr(szBuffer, ((PlayerTypes)iPlayer));
	return szBuffer;
}

std::wstring CyGameTextMgr::getResearchStr(int /*PlayerTypes*/ iPlayer)
{
	CvWString szBuffer;
	GAMETEXT.setResearchStr(szBuffer, ((PlayerTypes)iPlayer));
	return szBuffer;
}

std::wstring CyGameTextMgr::getOOSSeeds(int /*PlayerTypes*/ iPlayer)
{
	CvWString szBuffer;
	GAMETEXT.setOOSSeeds(szBuffer, ((PlayerTypes)iPlayer));
	return szBuffer;
}

std::wstring CyGameTextMgr::getNetStats(int /*PlayerTypes*/ iPlayer)
{
	CvWString szBuffer;
	GAMETEXT.setNetStats(szBuffer, ((PlayerTypes)iPlayer));
	return szBuffer;
}

std::wstring CyGameTextMgr::getTechHelp(int iTech, bool bCivilopediaText, bool bPlayerContext, bool bStrategyText, bool bTreeInfo, int iFromTech)
{
	CvWStringBuffer szBuffer;
	GAMETEXT.setTechHelp(szBuffer, (TechTypes)iTech, bCivilopediaText, bPlayerContext, bStrategyText, bTreeInfo, (TechTypes)iFromTech);
	return szBuffer.getCString();
}

std::wstring CyGameTextMgr::getUnitHelp(int iUnit, bool bCivilopediaText, bool bStrategyText, bool bTechChooserText, CyCity* pCity)
{
	CvWStringBuffer szBuffer;
	GAMETEXT.setUnitHelp(szBuffer, (UnitTypes)iUnit, bCivilopediaText, bStrategyText, bTechChooserText, ((pCity != NULL) ? pCity->getCity() : NULL));
	return szBuffer.getCString();
}

std::wstring CyGameTextMgr::getSpecificUnitHelp(CyUnit* pUnit, bool bOneLine, bool bShort)
{
	CvWStringBuffer szBuffer;
	if (pUnit && pUnit->getUnit())
	{
		GAMETEXT.setUnitHelp(szBuffer, pUnit->getUnit(), bOneLine, bShort);
	}
	return szBuffer.getCString();
}

std::wstring CyGameTextMgr::getBuildingHelp(int iBuilding, bool bCivilopediaText, bool bStrategyText, bool bTechChooserText, CyCity* pCity, bool bInGame)
{
	CvWStringBuffer szBuffer;
	GAMETEXT.setBuildingHelp(szBuffer, (BuildingTypes)iBuilding, bCivilopediaText, bStrategyText, bTechChooserText, ((pCity != NULL) ? pCity->getCity() : NULL),bInGame);
	return szBuffer.getCString();
}

std::wstring CyGameTextMgr::getProjectHelp(int iProject, bool bCivilopediaText, CyCity* pCity)
{
	CvWStringBuffer szBuffer;
	GAMETEXT.setProjectHelp(szBuffer, (ProjectTypes)iProject, bCivilopediaText, ((pCity != NULL) ? pCity->getCity() : NULL));
	return szBuffer.getCString();
}

std::wstring CyGameTextMgr::getPromotionHelp(int iPromotion, bool bCivilopediaText)
{
	CvWStringBuffer szBuffer;
	GAMETEXT.setPromotionHelp(szBuffer, (PromotionTypes)iPromotion, bCivilopediaText);
	return szBuffer.getCString();
}

//FfH Spell System: Added by Kael 07/23/2007
std::wstring CyGameTextMgr::getSpellHelp(int iSpell, bool bCivilopediaText)
{
	CvWStringBuffer szBuffer;
	GAMETEXT.setSpellHelp(szBuffer, (SpellTypes)iSpell, bCivilopediaText);
	return szBuffer.getCString();
}
//FfH: End Add

std::wstring CyGameTextMgr::getBonusHelp(int iBonus, bool bCivilopediaText)
{
	CvWStringBuffer szBuffer;
	GAMETEXT.setBonusHelp(szBuffer, (BonusTypes)iBonus, bCivilopediaText);
	return szBuffer.getCString();
}

std::wstring CyGameTextMgr::getReligionHelpCity(int iReligion, CyCity* pCity, bool bCityScreen, bool bForceReligion, bool bForceState, bool bNoStateReligion)
{
	CvWStringBuffer szBuffer;
	GAMETEXT.setReligionHelpCity(szBuffer, (ReligionTypes)iReligion, ((pCity != NULL) ? pCity->getCity() : NULL), bCityScreen, bForceReligion, bForceState, bNoStateReligion);
	return szBuffer.getCString();
}

std::wstring CyGameTextMgr::getCorporationHelpCity(int iCorporation, CyCity* pCity, bool bCityScreen, bool bForceCorporation)
{
	CvWStringBuffer szBuffer;
	GAMETEXT.setCorporationHelpCity(szBuffer, (CorporationTypes)iCorporation, ((pCity != NULL) ? pCity->getCity() : NULL), bCityScreen, bForceCorporation);
	return szBuffer.getCString();
}

std::wstring CyGameTextMgr::getImprovementHelp(int iImprovement, bool bCivilopediaText)
{
	CvWStringBuffer szBuffer;
	GAMETEXT.setImprovementHelp(szBuffer, (ImprovementTypes)iImprovement, bCivilopediaText);
	return szBuffer.getCString();
}

std::wstring CyGameTextMgr::getFeatureHelp(int iFeature, bool bCivilopediaText)
{
	CvWStringBuffer szBuffer;
	GAMETEXT.setFeatureHelp(szBuffer, (FeatureTypes)iFeature, bCivilopediaText);
	return szBuffer.getCString();
}

std::wstring CyGameTextMgr::getPlotEffectHelp(int iFeature, bool bCivilopediaText)
{
	CvWStringBuffer szBuffer;
	GAMETEXT.setPlotEffectHelp(szBuffer, (PlotEffectTypes)iFeature, bCivilopediaText);
	return szBuffer.getCString();
}

std::wstring CyGameTextMgr::getCityClassHelp(int iFeature, bool bCivilopediaText)
{
	CvWStringBuffer szBuffer;
	GAMETEXT.setCityClassHelp(szBuffer, (CityClassTypes)iFeature, bCivilopediaText);
	return szBuffer.getCString();
}
std::wstring CyGameTextMgr::getRouteHelp(int iFeature, bool bCivilopediaText)
{
	CvWStringBuffer szBuffer;
	GAMETEXT.setRouteHelp(szBuffer, (RouteTypes)iFeature, bCivilopediaText);
	return szBuffer.getCString();
}

std::wstring CyGameTextMgr::getTerrainHelp(int iTerrain, bool bCivilopediaText)
{
	CvWStringBuffer szBuffer;
	GAMETEXT.setTerrainHelp(szBuffer, (TerrainTypes)iTerrain, bCivilopediaText);
	return szBuffer.getCString();
}

std::wstring CyGameTextMgr::parseCivicInfo(int /*CivicTypes*/ iCivicType, bool bCivilopediaText, bool bPlayerContext, bool bSkipName)
{
	CvWStringBuffer szBuffer;
	GAMETEXT.parseCivicInfo(szBuffer, (CivicTypes) iCivicType, bCivilopediaText, bPlayerContext, bSkipName);
	return szBuffer.getCString();
}
/*************************************************************************************************/
/**	Xienwolf Tweak							07/12/09											**/
/**																								**/
/**		Allowed for "prettier" display of Civic Information in the Pedia by splitting it in 2	**/
/*************************************************************************************************/
std::wstring CyGameTextMgr::parseCivicInfoRequires(int /*CivicTypes*/ iCivicType, bool bCivilopediaText, bool bPlayerContext, bool bSkipName)
{
	CvWStringBuffer szBuffer;
	GAMETEXT.parseCivicInfoRequires(szBuffer, (CivicTypes) iCivicType, bCivilopediaText, bPlayerContext, bSkipName);
	return szBuffer.getCString();
}
std::wstring CyGameTextMgr::parseCivicInfoHelp(int /*CivicTypes*/ iCivicType, bool bCivilopediaText, bool bPlayerContext, bool bSkipName)
{
	CvWStringBuffer szBuffer;
	GAMETEXT.parseCivicInfoHelp(szBuffer, (CivicTypes) iCivicType, bCivilopediaText, bPlayerContext, bSkipName);
	return szBuffer.getCString();
}
std::wstring CyGameTextMgr::parseTraits(int /*TraitTypes*/ iTrait, int /*CivilizationTypes*/ iCivilization, bool bDawnOfMan)
{
	CvWStringBuffer szBuffer;
	GAMETEXT.parseTraits(szBuffer, (TraitTypes)iTrait, (CivilizationTypes) iCivilization, bDawnOfMan);
	return szBuffer.getCString();
}

/*************************************************************************************************/
/**	Spawn Groups						08/05/10									Valkrionn	**/
/**																								**/
/**					New spawn mechanic, allowing us to customize stacks							**/
/*************************************************************************************************/
std::wstring CyGameTextMgr::parseSpawnGroups(int /*SpawnGroupTypes*/ iSpawnGroup)
{
	CvWStringBuffer szBuffer;
	GAMETEXT.parseSpawnGroups(szBuffer, (SpawnGroupTypes)iSpawnGroup);
	return szBuffer.getCString();
}
/*************************************************************************************************/
/**	Spawn Groups							END													**/
/*************************************************************************************************/
/*************************************************************************************************/
/**	Better Affinity						01/30/11									Valkrionn	**/
/**																								**/
/**					Vastly improved Affinity system, open to many tags							**/
/*************************************************************************************************/
std::wstring CyGameTextMgr::parseAffinities(int /*AffinityTypes*/ iAffinity)
{
	CvWStringBuffer szBuffer;
	GAMETEXT.parseAffinities(szBuffer, (AffinityTypes)iAffinity);
	return szBuffer.getCString();
}
std::wstring CyGameTextMgr::parseAffinitiesReqs(int /*AffinityTypes*/ iAffinity)
{
	CvWStringBuffer szBuffer;
	GAMETEXT.parseAffinitiesReqs(szBuffer, (AffinityTypes)iAffinity);
	return szBuffer.getCString();
}
/*************************************************************************************************/
/**	Better Affinity							END													**/
/*************************************************************************************************/
/*************************************************************************************************/
/**	Tweak									END													**/
/*************************************************************************************************/

std::wstring CyGameTextMgr::parseReligionInfo(int /*ReligionTypes*/ iReligionType, bool bCivilopediaText)
{
	CvWStringBuffer szBuffer;
	GAMETEXT.setReligionHelp(szBuffer, (ReligionTypes) iReligionType, bCivilopediaText);
	return szBuffer.getCString();
}

std::wstring CyGameTextMgr::parseCorporationInfo(int /*CorporationTypes*/ iCorporationType, bool bCivilopediaText)
{
	CvWStringBuffer szBuffer;
	GAMETEXT.setCorporationHelp(szBuffer, (CorporationTypes) iCorporationType, bCivilopediaText);
	return szBuffer.getCString();
}

std::wstring CyGameTextMgr::parseCivInfos(int /*CivilizationTypes*/ iCivilization, bool bDawnOfMan)
{
	CvWStringBuffer szBuffer;
	GAMETEXT.parseCivInfos(szBuffer, (CivilizationTypes) iCivilization, bDawnOfMan);
	return szBuffer.getCString();
}

/*************************************************************************************************/
/** InterfaceComfort					Opera													**/
/*************************************************************************************************/
std::wstring CyGameTextMgr::parseMoreCivInfos(int /*CivilizationTypes*/ iCivilization, bool bDawnOfMan, bool bLinks, bool bCivilopediaText)
{
	CvWStringBuffer szBuffer;
	GAMETEXT.parseMoreCivInfos(szBuffer, (CivilizationTypes) iCivilization, bDawnOfMan, bLinks, bCivilopediaText);
	return szBuffer.getCString();
}
/*************************************************************************************************/
/** InterfaceComfort					END														**/
/*************************************************************************************************/

std::wstring CyGameTextMgr::parseLeaderTraits(int /*LeaderHeadTypes*/ iLeader, int /*CivilizationTypes*/ iCivilization, bool bDawnOfMan, bool bCivilopediaText)
{
	CvWStringBuffer szBuffer;
	GAMETEXT.parseLeaderTraits(szBuffer, (LeaderHeadTypes)iLeader, (CivilizationTypes) iCivilization, bDawnOfMan, bCivilopediaText);
	return szBuffer.getCString();
}

std::wstring CyGameTextMgr::getTradeString(TradeData* pTradeData, int iPlayer1, int iPlayer2)
{
	CvWStringBuffer szBuffer;
	if (NULL != pTradeData)
	{
		GAMETEXT.getTradeString(szBuffer, *pTradeData, (PlayerTypes)iPlayer1, (PlayerTypes) iPlayer2);
	}
	return szBuffer.getCString();
}

std::wstring CyGameTextMgr::getSpecialistHelp(int iSpecialist, bool bCivilopediaText)
{
	CvWStringBuffer szBuffer;
	GAMETEXT.parseSpecialistHelp(szBuffer, (SpecialistTypes) iSpecialist, NULL, bCivilopediaText);
	return szBuffer.getCString();
}

std::wstring CyGameTextMgr::buildHintsList()
{
	CvWStringBuffer szBuffer;
	GAMETEXT.buildHintsList(szBuffer);
	return szBuffer.getCString();
}

std::wstring CyGameTextMgr::getAttitudeString(int iPlayer, int iTargetPlayer)
{
	CvWStringBuffer szBuffer;
	GAMETEXT.getAttitudeString(szBuffer, (PlayerTypes)iPlayer, (PlayerTypes) iTargetPlayer);
	return szBuffer.getCString();
}

std::wstring CyGameTextMgr::setConvertHelp(int iPlayer, int iReligion)
{
	CvWStringBuffer szBuffer;
	GAMETEXT.setConvertHelp(szBuffer, (PlayerTypes)iPlayer, (ReligionTypes) iReligion);
	return szBuffer.getCString();
}

std::wstring CyGameTextMgr::setRevolutionHelp(int iPlayer)
{
	CvWStringBuffer szBuffer;
	GAMETEXT.setRevolutionHelp(szBuffer, (PlayerTypes)iPlayer);
	return szBuffer.getCString();
}

std::wstring CyGameTextMgr::setVassalRevoltHelp(int iMaster, int iVassal)
{
	CvWStringBuffer szBuffer;
	GAMETEXT.setVassalRevoltHelp(szBuffer, (TeamTypes)iMaster, (TeamTypes)iVassal);
	return szBuffer.getCString();
}

std::wstring CyGameTextMgr::getActiveDealsString(int iThisPlayer, int iOtherPlayer)
{
	CvWStringBuffer szBuffer;
	GAMETEXT.getActiveDealsString(szBuffer, (PlayerTypes)iThisPlayer, (PlayerTypes)iOtherPlayer);
	return szBuffer.getCString();
}

std::wstring CyGameTextMgr::getDealString(CyDeal* pDeal, int iPlayerPerspective)
{
	CvWStringBuffer szBuffer;
	if (pDeal && pDeal->getDeal())
	{
		GAMETEXT.getDealString(szBuffer, *(pDeal->getDeal()), (PlayerTypes)iPlayerPerspective);
	}
	return szBuffer.getCString();
}

// DynTraits Start
std::wstring CyGameTextMgr::parseTraitReqs(int /*TraitTypes*/ iTrait)
{
	CvWStringBuffer szBuffer;
	GAMETEXT.parseTraitReqs(szBuffer, (TraitTypes)iTrait);
	return szBuffer.getCString();
}
// DynTraits End