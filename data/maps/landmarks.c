#include "../../constants.h"

struct Landmark
{
    int8_t x;
    int8_t y;
    const char* const name;
};

// "N/A@" ; unreferenced ; "オバケやしき" ("HAUNTED HOUSE") in Japanese

static const char SpecialMapName[] = "SPECIAL@";
static const char NewBarkTownName[] = "NEW BARK¯TOWN@";
static const char Route29Name[] = "ROUTE 29@";
static const char CherrygroveCityName[] = "CHERRYGROVE¯CITY@";
static const char Route30Name[] = "ROUTE 30@";
static const char Route31Name[] = "ROUTE 31@";
static const char VioletCityName[] = "VIOLET CITY@";
static const char SproutTowerName[] = "SPROUT¯TOWER@";
static const char Route32Name[] = "ROUTE 32@";
static const char RuinsOfAlphName[] = "RUINS¯OF ALPH@";
static const char UnionCaveName[] = "UNION CAVE@";
static const char Route33Name[] = "ROUTE 33@";
static const char AzaleaTownName[] = "AZALEA TOWN@";
static const char SlowpokeWellName[] = "SLOWPOKE¯WELL@";
static const char IlexForestName[] = "ILEX¯FOREST@";
static const char Route34Name[] = "ROUTE 34@";
static const char GoldenrodCityName[] = "GOLDENROD¯CITY@";
static const char RadioTowerName[] = "RADIO TOWER@";
static const char Route35Name[] = "ROUTE 35@";
static const char NationalParkName[] = "NATIONAL¯PARK@";
static const char Route36Name[] = "ROUTE 36@";
static const char Route37Name[] = "ROUTE 37@";
static const char EcruteakCityName[] = "ECRUTEAK¯CITY@";
static const char TinTowerName[] = "TIN TOWER@";
static const char BurnedTowerName[] = "BURNED¯TOWER@";
static const char Route38Name[] = "ROUTE 38@";
static const char Route39Name[] = "ROUTE 39@";
static const char OlivineCityName[] = "OLIVINE¯CITY@";
static const char LighthouseName[] = "LIGHTHOUSE@";
static const char BattleTowerName[] = "BATTLE¯TOWER@";
static const char Route40Name[] = "ROUTE 40@";
static const char WhirlIslandsName[] = "WHIRL¯ISLANDS@";
static const char Route41Name[] = "ROUTE 41@";
static const char CianwoodCityName[] = "CIANWOOD¯CITY@";
static const char Route42Name[] = "ROUTE 42@";
static const char MtMortarName[] = "MT.MORTAR@";
static const char MahoganyTownName[] = "MAHOGANY¯TOWN@";
static const char Route43Name[] = "ROUTE 43@";
static const char LakeOfRageName[] = "LAKE OF¯RAGE@";
static const char Route44Name[] = "ROUTE 44@";
static const char IcePathName[] = "ICE PATH@";
static const char BlackthornCityName[] = "BLACKTHORN¯CITY@";
static const char DragonsDenName[] = "DRAGON'S¯DEN@";
static const char Route45Name[] = "ROUTE 45@";
static const char DarkCaveName[] = "DARK CAVE@";
static const char Route46Name[] = "ROUTE 46@";
static const char SilverCaveName[] = "SILVER CAVE@";
static const char PalletTownName[] = "PALLET TOWN@";
static const char Route1Name[] = "ROUTE 1@";
static const char ViridianCityName[] = "VIRIDIAN¯CITY@";
static const char Route2Name[] = "ROUTE 2@";
static const char PewterCityName[] = "PEWTER CITY@";
static const char Route3Name[] = "ROUTE 3@";
static const char MtMoonName[] = "MT.MOON@";
static const char Route4Name[] = "ROUTE 4@";
static const char CeruleanCityName[] = "CERULEAN¯CITY@";
static const char Route24Name[] = "ROUTE 24@";
static const char Route25Name[] = "ROUTE 25@";
static const char Route5Name[] = "ROUTE 5@";
static const char UndergroundName[] = "UNDERGROUND@";
static const char Route6Name[] = "ROUTE 6@";
static const char VermilionCityName[] = "VERMILION¯CITY@";
static const char DiglettsCaveName[] = "DIGLETT'S¯CAVE@";
static const char Route7Name[] = "ROUTE 7@";
static const char Route8Name[] = "ROUTE 8@";
static const char Route9Name[] = "ROUTE 9@";
static const char RockTunnelName[] = "ROCK TUNNEL@";
static const char Route10Name[] = "ROUTE 10@";
static const char PowerPlantName[] = "POWER PLANT@";
static const char LavenderTownName[] = "LAVENDER¯TOWN@";
static const char LavRadioTowerName[] = "LAV¯RADIO TOWER@";
static const char CeladonCityName[] = "CELADON¯CITY@";
static const char SaffronCityName[] = "SAFFRON¯CITY@";
static const char Route11Name[] = "ROUTE 11@";
static const char Route12Name[] = "ROUTE 12@";
static const char Route13Name[] = "ROUTE 13@";
static const char Route14Name[] = "ROUTE 14@";
static const char Route15Name[] = "ROUTE 15@";
static const char Route16Name[] = "ROUTE 16@";
static const char Route17Name[] = "ROUTE 17@";
static const char Route18Name[] = "ROUTE 18@";
static const char FuchsiaCityName[] = "FUCHSIA¯CITY@";
static const char Route19Name[] = "ROUTE 19@";
static const char Route20Name[] = "ROUTE 20@";
static const char SeafoamIslandsName[] = "SEAFOAM¯ISLANDS@";
static const char CinnabarIslandName[] = "CINNABAR¯ISLAND@";
static const char Route21Name[] = "ROUTE 21@";
static const char Route22Name[] = "ROUTE 22@";
static const char VictoryRoadName[] = "VICTORY¯ROAD@";
static const char Route23Name[] = "ROUTE 23@";
static const char IndigoPlateauName[] = "INDIGO¯PLATEAU@";
static const char Route26Name[] = "ROUTE 26@";
static const char Route27Name[] = "ROUTE 27@";
static const char TohjoFallsName[] = "TOHJO FALLS@";
static const char Route28Name[] = "ROUTE 28@";
static const char FastShipName[] = "FAST SHIP@";

const struct Landmark Landmarks[] = {
    { -8, -16, SpecialMapName},
    {140, 100, NewBarkTownName},
    {128, 100, Route29Name},
    {100, 100, CherrygroveCityName},
    {100,  80, Route30Name},
    { 96,  60, Route31Name},
    { 84,  60, VioletCityName},
    { 85,  58, SproutTowerName},
    { 84,  92, Route32Name},
    { 76,  76, RuinsOfAlphName},
    { 84, 124, UnionCaveName},
    { 82, 124, Route33Name},
    { 68, 124, AzaleaTownName},
    { 70, 122, SlowpokeWellName},
    { 52, 120, IlexForestName},
    { 52, 112, Route34Name},
    { 52,  92, GoldenrodCityName},
    { 50,  92, RadioTowerName},
    { 52,  76, Route35Name},
    { 52,  60, NationalParkName},
    { 64,  60, Route36Name},
    { 68,  52, Route37Name},
    { 68,  44, EcruteakCityName},
    { 70,  42, TinTowerName},
    { 66,  42, BurnedTowerName},
    { 52,  44, Route38Name},
    { 36,  48, Route39Name},
    { 36,  60, OlivineCityName},
    { 38,  62, LighthouseName},
    { 28,  56, BattleTowerName},
    { 28,  64, Route40Name},
    { 28,  92, WhirlIslandsName},
    { 28, 100, Route41Name},
    { 20, 100, CianwoodCityName},
    { 92,  44, Route42Name},
    { 84,  44, MtMortarName},
    {108,  44, MahoganyTownName},
    {108,  36, Route43Name},
    {108,  28, LakeOfRageName},
    {120,  44, Route44Name},
    {130,  38, IcePathName},
    {132,  44, BlackthornCityName},
    {132,  36, DragonsDenName},
    {132,  64, Route45Name},
    {112,  72, DarkCaveName},
    {124,  88, Route46Name},
    {148,  68, SilverCaveName},
// KANTO_LANDMARK
    { 52, 108, PalletTownName},
    { 52,  92, Route1Name},
    { 52,  76, ViridianCityName},
    { 52,  64, Route2Name},
    { 52,  52, PewterCityName},
    { 64,  52, Route3Name},
    { 76,  52, MtMoonName},
    { 88,  52, Route4Name},
    {100,  52, CeruleanCityName},
    {100,  44, Route24Name},
    {108,  36, Route25Name},
    {100,  60, Route5Name},
    {108,  76, UndergroundName},
    {100,  76, Route6Name},
    {100,  84, VermilionCityName},
    { 88,  60, DiglettsCaveName},
    { 88,  68, Route7Name},
    {116,  68, Route8Name},
    {116,  52, Route9Name},
    {132,  52, RockTunnelName},
    {132,  56, Route10Name},
    {132,  60, PowerPlantName},
    {132,  68, LavenderTownName},
    {140,  68, LavRadioTowerName},
    { 76,  68, CeladonCityName},
    {100,  68, SaffronCityName},
    {116,  84, Route11Name},
    {132,  80, Route12Name},
    {124, 100, Route13Name},
    {116, 112, Route14Name},
    {104, 116, Route15Name},
    { 68,  68, Route16Name},
    { 68,  92, Route17Name},
    { 80, 116, Route18Name},
    { 92, 116, FuchsiaCityName},
    { 92, 128, Route19Name},
    { 76, 132, Route20Name},
    { 68, 132, SeafoamIslandsName},
    { 52, 132, CinnabarIslandName},
    { 52, 120, Route21Name},
    { 36,  68, Route22Name},
    { 28,  52, VictoryRoadName},
    { 28,  44, Route23Name},
    { 28,  36, IndigoPlateauName},
    { 28,  92, Route26Name},
    { 20, 100, Route27Name},
    { 12, 100, TohjoFallsName},
    { 20,  68, Route28Name},
    {140, 116, FastShipName},
};

#if defined(__cplusplus) || defined(_MSC_VER)
static_assert(lengthof(Landmarks) == NUM_LANDMARKS, "");
#else
_Static_assert(lengthof(Landmarks) == NUM_LANDMARKS, "");
#endif