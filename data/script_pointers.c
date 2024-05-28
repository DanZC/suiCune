#include "../constants.h"
#include <string.h>
#include <assert.h>
#include "maps/scripts.h"
#include "../home/map.h"
#include "../input_system/uthash.h"

// This is needed to keep compatability with OG Crystal, since Crystal expects event script pointers to be preloaded with a save file.
// To accomadate this, we use the object's event script index, map group, and map number as a key and store both the script pointer and the GB pointer together.
// When we initialize the object events from a map, we use this index to copy the GB pointer into the event. When the events are saved to the save file, the GB
// pointer will already be there. When we load an event's script from the event, we use the redirection system to map the GB pointer to the final pointer.

struct ScriptGBPtr {
    int idx;
    uint32_t gb_ptr;
    const void* script;
    UT_hash_handle hh;
};
struct ScriptGBPtr *gb_script_table = NULL;

#define _idx(_group, _id, _i) (_group << 16) | (_id << 8) | _i
#define entry(_map, _i, _script) add_entry(GROUP_##_map, MAP_##_map, _i, &_script, a##_script)
#define entry2(_map, _i, _script, _gb) add_entry(GROUP_##_map, MAP_##_map, _i, &_script, _gb)

static void add_entry(uint8_t group, uint8_t map, uint8_t index, const void* script, uint32_t gb_ptr) {
    struct ScriptGBPtr* item = malloc(sizeof(*item));
    item->gb_ptr = gb_ptr;
    item->idx = _idx(group, map, index);
    item->script = script;
    HASH_ADD_INT(gb_script_table,idx, item);
}

#define OBJ_OFFSET 0
#define BG_OFFSET 32
#define COORD_OFFSET 64

void PopulateMapScriptTable(void) {
    entry(NEW_BARK_TOWN,    0, NewBarkTownTeacherScript);
    entry(NEW_BARK_TOWN,    1, NewBarkTownFisherScript);
    entry(NEW_BARK_TOWN,    2, NewBarkTownSilverScript);
    entry(NEW_BARK_TOWN,    BG_OFFSET    + 0, NewBarkTownSign);
    entry(NEW_BARK_TOWN,    BG_OFFSET    + 1, NewBarkTownPlayersHouseSign);
    entry(NEW_BARK_TOWN,    BG_OFFSET    + 2, NewBarkTownElmsLabSign);
    entry(NEW_BARK_TOWN,    BG_OFFSET    + 3, NewBarkTownElmsHouseSign);
    entry(NEW_BARK_TOWN,    COORD_OFFSET + 0, NewBarkTown_TeacherStopsYouScene1);
    entry(NEW_BARK_TOWN,    COORD_OFFSET + 1, NewBarkTown_TeacherStopsYouScene2);

    entry(CHERRYGROVE_CITY, 0, CherrygroveCityGuideGent);
    entry(CHERRYGROVE_CITY, 2, CherrygroveTeacherScript);
    entry(CHERRYGROVE_CITY, 3, CherrygroveYoungsterScript);
    entry(CHERRYGROVE_CITY, 4, MysticWaterGuy);
    entry(CHERRYGROVE_CITY, BG_OFFSET    + 0, CherrygroveCitySign);
    entry(CHERRYGROVE_CITY, BG_OFFSET    + 1, GuideGentsHouseSign);
    entry(CHERRYGROVE_CITY, BG_OFFSET    + 2, CherrygroveCityMartSign);
    entry(CHERRYGROVE_CITY, BG_OFFSET    + 3, CherrygroveCityPokecenterSign);
    entry(CHERRYGROVE_CITY, COORD_OFFSET + 0, CherrygroveSilverSceneNorth);
    entry(CHERRYGROVE_CITY, COORD_OFFSET + 1, CherrygroveSilverSceneSouth);

    entry(VIOLET_CITY, 0, VioletCityEarlScript);
    entry(VIOLET_CITY, 1, VioletCityLassScript);
    entry(VIOLET_CITY, 2, VioletCitySuperNerdScript);
    entry(VIOLET_CITY, 3, VioletCityGrampsScript);
    entry(VIOLET_CITY, 4, VioletCityYoungsterScript);
    entry(VIOLET_CITY, 5, VioletCityFruitTree);
    entry(VIOLET_CITY, 6, VioletCityPPUp);
    entry(VIOLET_CITY, 7, VioletCityRareCandy);

    entry(AZALEA_TOWN, 0, AzaleaTownRocket1Script);
    entry(AZALEA_TOWN, 1, AzaleaTownGrampsScript);
    entry(AZALEA_TOWN, 2, AzaleaTownTeacherScript);
    entry(AZALEA_TOWN, 3, AzaleaTownYoungsterScript);
    entry(AZALEA_TOWN, 4, AzaleaTownSlowpokeScript);
    entry(AZALEA_TOWN, 5, AzaleaTownSlowpokeScript);
    entry(AZALEA_TOWN, 6, AzaleaTownSlowpokeScript);
    entry(AZALEA_TOWN, 7, AzaleaTownSlowpokeScript);
    entry(AZALEA_TOWN, 8, WhiteApricornTree);
    entry(AZALEA_TOWN, 9, ObjectEvent);
    entry(AZALEA_TOWN, 10, AzaleaTownRocket2Script);
    entry(AZALEA_TOWN, 11, AzaleaTownKurtScript);

    entry(GOLDENROD_CITY, 0, GoldenrodCityPokefanMScript);
    entry(GOLDENROD_CITY, 1, GoldenrodCityYoungster1Script);
    entry(GOLDENROD_CITY, 2, GoldenrodCityCooltrainerF1Script);
    entry(GOLDENROD_CITY, 3, GoldenrodCityCooltrainerF2Script);
    entry(GOLDENROD_CITY, 4, GoldenrodCityYoungster2Script);
    entry(GOLDENROD_CITY, 5, GoldenrodCityLassScript);
    entry(GOLDENROD_CITY, 6, GoldenrodCityGrampsScript);
    entry(GOLDENROD_CITY, 7, GoldenrodCityRocketScoutScript);
    entry(GOLDENROD_CITY, 8, GoldenrodCityRocket1Script);
    entry(GOLDENROD_CITY, 9, GoldenrodCityRocket2Script);
    entry(GOLDENROD_CITY, 10, GoldenrodCityRocket3Script);
    entry(GOLDENROD_CITY, 11, GoldenrodCityRocket4Script);
    entry(GOLDENROD_CITY, 12, GoldenrodCityRocket5Script);
    entry(GOLDENROD_CITY, 13, GoldenrodCityRocket6Script);
    entry(GOLDENROD_CITY, 14, MoveTutorScript);

    entry(ROUTE_29, 0, CatchingTutorialDudeScript);
    entry(ROUTE_29, 1, Route29YoungsterScript);
    entry(ROUTE_29, 2, Route29TeacherScript);
    entry(ROUTE_29, 3, Route29FruitTree);
    entry(ROUTE_29, 4, Route29FisherScript);
    entry(ROUTE_29, 5, Route29CooltrainerMScript);
    entry(ROUTE_29, 6, TuscanyScript);
    entry(ROUTE_29, 7, Route29Potion);
    entry(ROUTE_29, BG_OFFSET + 0, Route29Sign1);
    entry(ROUTE_29, BG_OFFSET + 1, Route29Sign2);
    entry(ROUTE_29, COORD_OFFSET + 0, Route29Tutorial1);
    entry(ROUTE_29, COORD_OFFSET + 1, Route29Tutorial2);

    entry(ROUTE_29_ROUTE_46_GATE, 0, Route29Route46GateOfficerScript);
    entry(ROUTE_29_ROUTE_46_GATE, 1, Route29Route46GateYoungsterScript);

    entry(ROUTE_30, 0, YoungsterJoey_ImportantBattleScript);
    entry(ROUTE_30, 1, TrainerYoungsterJoey);
    entry(ROUTE_30, 2, TrainerYoungsterMikey);
    entry(ROUTE_30, 3, TrainerBugCatcherDon);
    entry(ROUTE_30, 4, Route30YoungsterScript);
    entry(ROUTE_30, 5, ObjectEvent);
    entry(ROUTE_30, 6, ObjectEvent);
    entry(ROUTE_30, 7, Route30FruitTree1);
    entry(ROUTE_30, 8, Route30FruitTree2);
    entry(ROUTE_30, 9, Route30CooltrainerFScript);
    entry(ROUTE_30, 10, Route30Antidote);

    entry(ROUTE_30_BERRY_HOUSE, 0, Route30BerryHousePokefanMScript);

    entry(ROUTE_31, 0, Route31MailRecipientScript);
    entry(ROUTE_31, 1, Route31YoungsterScript);
    entry(ROUTE_31, 2, TrainerBugCatcherWade1);
    entry(ROUTE_31, 3, Route31CooltrainerMScript);
    entry(ROUTE_31, 4, Route31FruitTree);
    entry(ROUTE_31, 5, Route31Potion);
    entry(ROUTE_31, 6, Route31PokeBall);

    entry(ROUTE_31_VIOLET_GATE, 0, Route31VioletGateOfficerScript);
    entry(ROUTE_31_VIOLET_GATE, 1, Route31VioletGateCooltrainerFScript);

    entry(ROUTE_32, 0,  TrainerFisherJustin);
    entry(ROUTE_32, 1,  TrainerFisherRalph1);
    entry(ROUTE_32, 2,  TrainerFisherHenry);
    entry(ROUTE_32, 3,  TrainerYoungsterAlbert);
    entry(ROUTE_32, 4,  TrainerYoungsterGordon);
    entry(ROUTE_32, 5,  TrainerCamperRoland);
    entry(ROUTE_32, 6,  TrainerPicnickerLiz1);
    entry(ROUTE_32, 7,  Route32CooltrainerMScript);
    entry(ROUTE_32, 8,  TrainerBirdKeeperPeter);
    entry(ROUTE_32, 9,  SlowpokeTailSalesmanScript);
    entry(ROUTE_32, 10, Route32GreatBall);
    entry(ROUTE_32, 11, Route32RoarTMGuyScript);
    entry(ROUTE_32, 12, FriedaScript);
    entry(ROUTE_32, 13, Route32Repel);

    entry(ROUTE_32_RUINS_OF_ALPH_GATE, 0, Route32RuinsOfAlphGateOfficerScript);
    entry(ROUTE_32_RUINS_OF_ALPH_GATE, 1, Route32RuinsOfAlphGatePokefanMScript);
    entry(ROUTE_32_RUINS_OF_ALPH_GATE, 2, Route32RuinsOfAlphGateYoungsterScript);

    entry(ROUTE_32_POKECENTER_1F, 0, Route32Pokecenter1FNurseScript);
    entry(ROUTE_32_POKECENTER_1F, 1, Route32Pokecenter1FFishingGuruScript);
    entry(ROUTE_32_POKECENTER_1F, 2, Route32Pokecenter1FCooltrainerFScript);

    entry(ROUTE_33, 0, TrainerHikerAnthony);
    entry(ROUTE_33, 1, Route33LassScript);
    entry(ROUTE_33, 2, Route33FruitTree);

    entry(ROUTE_34, 0, TrainerCamperTodd1);
    entry(ROUTE_34, 1, TrainerYoungsterSamuel);
    entry(ROUTE_34, 2, TrainerYoungsterIan);
    entry(ROUTE_34, 3, TrainerPicnickerGina1);
    entry(ROUTE_34, 4, OfficerKeithScript);
    entry(ROUTE_34, 5, TrainerPokefanmBrandon);
    entry(ROUTE_34, 6, DayCareManScript_Outside);
    entry(ROUTE_34, 7, DayCareMon1Script);
    entry(ROUTE_34, 8, DayCareMon2Script);
    entry(ROUTE_34, 9, TrainerCooltrainerfIrene);
    entry(ROUTE_34, 10, TrainerCooltrainerfJenn);
    entry(ROUTE_34, 11, TrainerCooltrainerfKate);
    entry(ROUTE_34, 12, Route34Nugget);

    entry(ROUTE_34_ILEX_FOREST_GATE, 0, Route34IlexForestGateTeacherScript);
    entry(ROUTE_34_ILEX_FOREST_GATE, 1, Route34IlexForestGateButterfreeScript);
    entry(ROUTE_34_ILEX_FOREST_GATE, 2, Route34IlexForestGateLassScript);
    entry(ROUTE_34_ILEX_FOREST_GATE, 3, Route34IlexForestGateTeacherScript);

    // maps/DayCare.c
    entry(DAY_CARE, 0, DayCareManScript_Inside);
    entry(DAY_CARE, 1, DayCareLadyScript);

    entry(ROUTE_35, 0,  TrainerCamperIvan);
    entry(ROUTE_35, 1,  TrainerCamperElliot);
    entry(ROUTE_35, 2,  TrainerPicnickerBrooke);
    entry(ROUTE_35, 3,  TrainerPicnickerKim);
    entry(ROUTE_35, 4,  TrainerBirdKeeperBryan);
    entry(ROUTE_35, 5,  TrainerFirebreatherWalt);
    entry(ROUTE_35, 6,  TrainerBugCatcherArnie);
    entry(ROUTE_35, 7,  TrainerJugglerIrwin);
    entry(ROUTE_35, 8,  TrainerOfficerDirk);
    entry(ROUTE_35, 9,  Route35FruitTree);
    entry(ROUTE_35, 10, Route35TMRollout);

    // maps/Route35GoldenrodGate.c
    entry(ROUTE_35_GOLDENROD_GATE, 0, RandyScript);
    entry(ROUTE_35_GOLDENROD_GATE, 1, Route35GoldenrodGatePokefanFScript);
    entry(ROUTE_35_GOLDENROD_GATE, 2, Route35GoldenrodGateFisherScript);

    entry(ROUTE_35_NATIONAL_PARK_GATE, 0, Route35OfficerScriptContest);
    entry(ROUTE_35_NATIONAL_PARK_GATE, 1, Route35NationalParkGateYoungsterScript);
    entry(ROUTE_35_NATIONAL_PARK_GATE, 2, Route35NationalParkGateOfficerScript);

    entry(ROUTE_36, 0, TrainerPsychicMark);
    entry(ROUTE_36, 1, TrainerSchoolboyAlan1);
    entry(ROUTE_36, 2, SudowoodoScript);
    entry(ROUTE_36, 3, Route36LassScript);
    entry(ROUTE_36, 4, Route36RockSmashGuyScript);
    entry(ROUTE_36, 5, Route36FruitTree);
    entry(ROUTE_36, 6, ArthurScript);
    entry(ROUTE_36, 7, Route36FloriaScript);
    entry(ROUTE_36, 8, ObjectEvent);

    entry(ROUTE_36_NATIONAL_PARK_GATE, 0,  Route36OfficerScriptContest);
    entry(ROUTE_36_NATIONAL_PARK_GATE, 1,  BugCatchingContestant1BScript);
    entry(ROUTE_36_NATIONAL_PARK_GATE, 2,  BugCatchingContestant2BScript);
    entry(ROUTE_36_NATIONAL_PARK_GATE, 3,  BugCatchingContestant3BScript);
    entry(ROUTE_36_NATIONAL_PARK_GATE, 4,  BugCatchingContestant4BScript);
    entry(ROUTE_36_NATIONAL_PARK_GATE, 5,  BugCatchingContestant5BScript);
    entry(ROUTE_36_NATIONAL_PARK_GATE, 6,  BugCatchingContestant6BScript);
    entry(ROUTE_36_NATIONAL_PARK_GATE, 7,  BugCatchingContestant7BScript);
    entry(ROUTE_36_NATIONAL_PARK_GATE, 8,  BugCatchingContestant8BScript);
    entry(ROUTE_36_NATIONAL_PARK_GATE, 9,  BugCatchingContestant9BScript);
    entry(ROUTE_36_NATIONAL_PARK_GATE, 10, BugCatchingContestant10BScript);
    entry(ROUTE_36_NATIONAL_PARK_GATE, 11, Route36NationalParkGateOfficerScript);

    entry(ROUTE_36_RUINS_OF_ALPH_GATE, 0, Route36RuinsOfAlphGateOfficerScript);
    entry(ROUTE_36_RUINS_OF_ALPH_GATE, 1, Route36RuinsOfAlphGateGrampsScript);

    entry(CHERRYGROVE_EVOLUTION_SPEECH_HOUSE, 0, CherrygroveEvolutionSpeechHouseLassScript);
    entry(CHERRYGROVE_EVOLUTION_SPEECH_HOUSE, 1, CherrygroveEvolutionSpeechHouseYoungsterScript);

    entry(CHERRYGROVE_GYM_SPEECH_HOUSE, 0, CherrygroveGymSpeechHousePokefanMScript);
    entry(CHERRYGROVE_GYM_SPEECH_HOUSE, 1, CherrygroveGymSpeechHouseBugCatcherScript);

    entry(CHERRYGROVE_POKECENTER_1F, 0, CherrygrovePokecenter1FNurseScript);
    entry(CHERRYGROVE_POKECENTER_1F, 1, CherrygrovePokecenter1FFisherScript);
    entry(CHERRYGROVE_POKECENTER_1F, 2, CherrygrovePokecenter1FGentlemanScript);
    entry(CHERRYGROVE_POKECENTER_1F, 3, CherrygrovePokecenter1FTeacherScript);

    entry(CHERRYGROVE_MART, 0, CherrygroveMartClerkScript);
    entry(CHERRYGROVE_MART, 1, CherrygroveMartCooltrainerMScript);
    entry(CHERRYGROVE_MART, 2, CherrygroveMartYoungsterScript);

    entry(GUIDE_GENTS_HOUSE, 0, GuideGentsHouseGuideGent);

    entry(POKECENTER_2F, 0, LinkReceptionistScript_Trade);
    entry(POKECENTER_2F, 1, LinkReceptionistScript_Battle);
    entry(POKECENTER_2F, 2, LinkReceptionistScript_TimeCapsule);
    entry(POKECENTER_2F, 3, Pokecenter2FOfficerScript);

    entry(MR_POKEMONS_HOUSE, 0, MrPokemonsHouse_MrPokemonScript);
    entry(MR_POKEMONS_HOUSE, 1, ObjectEvent);

    entry(PLAYERS_NEIGHBORS_HOUSE, 0, PlayersNeighborsDaughterScript);
    entry(PLAYERS_NEIGHBORS_HOUSE, 1, PlayersNeighborScript);

    entry(ELMS_LAB, 0, ProfElmScript);
    entry(ELMS_LAB, 1, ElmsAideScript);
    entry(ELMS_LAB, 2, CyndaquilPokeBallScript);
    entry(ELMS_LAB, 3, TotodilePokeBallScript);
    entry(ELMS_LAB, 4, ChikoritaPokeBallScript);
    entry(ELMS_LAB, 5, CopScript);

    entry(ELMS_HOUSE, 0, ElmsWife);
    entry(ELMS_HOUSE, 1, ElmsSon);

    entry(PLAYERS_HOUSE_1F, 0, MomScript);
    entry(PLAYERS_HOUSE_1F, 1, MomScript);
    entry(PLAYERS_HOUSE_1F, 2, MomScript);
    entry(PLAYERS_HOUSE_1F, 3, MomScript);
    entry(PLAYERS_HOUSE_1F, 4, NeighborScript);

    entry(PLAYERS_HOUSE_2F, 0, PlayersHouseGameConsoleScript);
    entry(PLAYERS_HOUSE_2F, 1, PlayersHouseDoll1Script);
    entry(PLAYERS_HOUSE_2F, 2, PlayersHouseDoll2Script);
    entry(PLAYERS_HOUSE_2F, 3, PlayersHouseBigDollScript);

    entry(VIOLET_POKECENTER_1F, 0, VioletPokecenterNurse);
    entry(VIOLET_POKECENTER_1F, 1, VioletPokecenter1FGameboyKidScript);
    entry(VIOLET_POKECENTER_1F, 2, VioletPokecenter1FGentlemanScript);
    entry(VIOLET_POKECENTER_1F, 3, VioletPokecenter1FYoungsterScript);
    entry(VIOLET_POKECENTER_1F, 4, VioletPokecenter1F_ElmsAideScript);

    entry(VIOLET_MART, 0, VioletMartClerkScript);
    entry(VIOLET_MART, 1, VioletMartGrannyScript);
    entry(VIOLET_MART, 2, VioletMartCooltrainerMScript);

    entry(VIOLET_KYLES_HOUSE, 0, VioletKylesHousePokefanMScript);
    entry(VIOLET_KYLES_HOUSE, 1, Kyle);

    entry(EARLS_POKEMON_ACADEMY, 0, AcademyEarl);
    entry(EARLS_POKEMON_ACADEMY, 1, EarlsPokemonAcademyYoungster1Script);
    entry(EARLS_POKEMON_ACADEMY, 2, EarlsPokemonAcademyGameboyKid1Script);
    entry(EARLS_POKEMON_ACADEMY, 3, EarlsPokemonAcademyGameboyKid2Script);
    entry(EARLS_POKEMON_ACADEMY, 4, EarlsPokemonAcademyYoungster2Script);
    entry(EARLS_POKEMON_ACADEMY, 5, AcademyNotebook);

    entry(VIOLET_GYM, 0, VioletGymFalknerScript);
    entry(VIOLET_GYM, 1, TrainerBirdKeeperRod);
    entry(VIOLET_GYM, 2, TrainerBirdKeeperAbe);
    entry(VIOLET_GYM, 3, VioletGymGuideScript);

    entry(AZALEA_POKECENTER_1F, 0, AzaleaPokecenter1FNurseScript);
    entry(AZALEA_POKECENTER_1F, 1, AzaleaPokecenter1FGentlemanScript);
    entry(AZALEA_POKECENTER_1F, 2, AzaleaPokecenter1FFishingGuruScript);
    entry(AZALEA_POKECENTER_1F, 3, AzaleaPokecenter1FPokefanFScript);

    entry(AZALEA_MART, 0, AzaleaMartClerkScript);
    entry(AZALEA_MART, 1, AzaleaMartCooltrainerMScript);
    entry(AZALEA_MART, 2, AzaleaMartBugCatcherScript);

    entry(AZALEA_GYM, 0, AzaleaGymBugsyScript);
    entry(AZALEA_GYM, 1, TrainerBugCatcherBenny);
    entry(AZALEA_GYM, 2, TrainerBugCatcherAl);
    entry(AZALEA_GYM, 3, TrainerBugCatcherJosh);
    entry(AZALEA_GYM, 4, TrainerTwinsAmyandmay1);
    entry(AZALEA_GYM, 5, TrainerTwinsAmyandmay2);
    entry(AZALEA_GYM, 6, AzaleaGymGuideScript);

    entry(KURTS_HOUSE, 0, Kurt1);
    entry(KURTS_HOUSE, 1, KurtsGranddaughter1);
    entry(KURTS_HOUSE, 2, KurtsHouseSlowpoke);
    entry(KURTS_HOUSE, 3, Kurt2);
    entry(KURTS_HOUSE, 4, KurtsGranddaughter2);

    entry(CHARCOAL_KILN, 0, CharcoalKilnBoss);
    entry(CHARCOAL_KILN, 1, CharcoalKilnApprentice);
    entry(CHARCOAL_KILN, 2, CharcoalKilnFarfetchd);

    entry(GOLDENROD_BIKE_SHOP, 0, GoldenrodBikeShopClerkScript);

    entry(GOLDENROD_FLOWER_SHOP, 0, FlowerShopTeacherScript);
    entry(GOLDENROD_FLOWER_SHOP, 1, FlowerShopFloriaScript);

    entry(GOLDENROD_HAPPINESS_RATER, 0, GoldenrodHappinessRaterTeacherScript);
    entry(GOLDENROD_HAPPINESS_RATER, 1, GoldenrodHappinessRaterPokefanMScript);
    entry(GOLDENROD_HAPPINESS_RATER, 2, GoldenrodHappinessRaterTwinScript);

    entry(GOLDENROD_MAGNET_TRAIN_STATION, 0, GoldenrodMagnetTrainStationOfficerScript);
    entry(GOLDENROD_MAGNET_TRAIN_STATION, 1, GoldenrodMagnetTrainStationGentlemanScript);

    entry(GOLDENROD_NAME_RATER, 0, GoldenrodNameRater);

    entry(GOLDENROD_PP_SPEECH_HOUSE, 0, GoldenrodPPSpeechHouseFisherScript);
    entry(GOLDENROD_PP_SPEECH_HOUSE, 1, GoldenrodPPSpeechHouseLassScript);

    entry(BILLS_FAMILYS_HOUSE, 0, BillScript);
    entry(BILLS_FAMILYS_HOUSE, 1, BillsMomScript);
    entry(BILLS_FAMILYS_HOUSE, 2, BillsSisterScript);

    entry(GOLDENROD_GAME_CORNER, 0,  GoldenrodGameCornerCoinVendorScript);
    entry(GOLDENROD_GAME_CORNER, 1,  GoldenrodGameCornerTMVendorScript);
    entry(GOLDENROD_GAME_CORNER, 2,  GoldenrodGameCornerPrizeMonVendorScript);
    entry(GOLDENROD_GAME_CORNER, 3,  GoldenrodGameCornerPharmacistScript);
    entry(GOLDENROD_GAME_CORNER, 4,  GoldenrodGameCornerPharmacistScript);
    entry(GOLDENROD_GAME_CORNER, 5,  GoldenrodGameCornerPokefanM1Script);
    entry(GOLDENROD_GAME_CORNER, 6,  GoldenrodGameCornerCooltrainerMScript);
    entry(GOLDENROD_GAME_CORNER, 7,  GoldenrodGameCornerPokefanFScript);
    entry(GOLDENROD_GAME_CORNER, 8,  GoldenrodGameCornerCooltrainerFScript);
    entry(GOLDENROD_GAME_CORNER, 9,  GoldenrodGameCornerGentlemanScript);
    entry(GOLDENROD_GAME_CORNER, 10, GoldenrodGameCornerPokefanM2Script);
    entry(GOLDENROD_GAME_CORNER, 11, MoveTutorInsideScript);

    entry(GOLDENROD_GYM, 0, GoldenrodGymWhitneyScript);
    entry(GOLDENROD_GYM, 1, TrainerLassCarrie);
    entry(GOLDENROD_GYM, 2, TrainerLassBridget);
    entry(GOLDENROD_GYM, 3, TrainerBeautyVictoria);
    entry(GOLDENROD_GYM, 4, TrainerBeautySamantha);
    entry(GOLDENROD_GYM, 5, GoldenrodGymGuideScript);

    entry(GOLDENROD_UNDERGROUND, 0, TrainerSupernerdEric);
    entry(GOLDENROD_UNDERGROUND, 1, TrainerSupernerdTeru);
    entry(GOLDENROD_UNDERGROUND, 2, TrainerPokemaniacIssac);
    entry(GOLDENROD_UNDERGROUND, 3, TrainerPokemaniacDonald);
    entry(GOLDENROD_UNDERGROUND, 4, GoldenrodUndergroundCoinCase);
    entry(GOLDENROD_UNDERGROUND, 5, BargainMerchantScript);
    entry(GOLDENROD_UNDERGROUND, 6, OlderHaircutBrotherScript);
    entry(GOLDENROD_UNDERGROUND, 7, YoungerHaircutBrotherScript);
    entry(GOLDENROD_UNDERGROUND, 8, BitterMerchantScript);

    entry(GOLDENROD_UNDERGROUND_SWITCH_ROOM_ENTRANCES, 0, TrainerBurglarDuncan);
    entry(GOLDENROD_UNDERGROUND_SWITCH_ROOM_ENTRANCES, 1, TrainerBurglarEddie);
    entry(GOLDENROD_UNDERGROUND_SWITCH_ROOM_ENTRANCES, 2, TrainerGruntM13);
    entry(GOLDENROD_UNDERGROUND_SWITCH_ROOM_ENTRANCES, 3, TrainerGruntM11);
    entry(GOLDENROD_UNDERGROUND_SWITCH_ROOM_ENTRANCES, 4, TrainerGruntM25);
    entry(GOLDENROD_UNDERGROUND_SWITCH_ROOM_ENTRANCES, 5, TrainerGruntF3);
    entry(GOLDENROD_UNDERGROUND_SWITCH_ROOM_ENTRANCES, 6, GoldenrodUndergroundSwitchRoomEntrancesTeacherScript);
    entry(GOLDENROD_UNDERGROUND_SWITCH_ROOM_ENTRANCES, 7, GoldenrodUndergroundSwitchRoomEntrancesSuperNerdScript);
    entry(GOLDENROD_UNDERGROUND_SWITCH_ROOM_ENTRANCES, 8, GoldenrodUndergroundSwitchRoomEntrancesSmokeBall);
    entry(GOLDENROD_UNDERGROUND_SWITCH_ROOM_ENTRANCES, 9, GoldenrodUndergroundSwitchRoomEntrancesFullHeal);

    entry(GOLDENROD_DEPT_STORE_1F, 0, GoldenrodDeptStore1FReceptionistScript);
    entry(GOLDENROD_DEPT_STORE_1F, 1, GoldenrodDeptStore1FPokefanFScript);
    entry(GOLDENROD_DEPT_STORE_1F, 2, GoldenrodDeptStore1FBugCatcherScript);
    entry(GOLDENROD_DEPT_STORE_1F, 3, GoldenrodDeptStore1FGentlemanScript);

    // maps/GoldenrodDeptStore2F.c
    entry(GOLDENROD_DEPT_STORE_2F, 0, GoldenrodDeptStore2FClerk1Script);
    entry(GOLDENROD_DEPT_STORE_2F, 1, GoldenrodDeptStore2FClerk2Script);
    entry(GOLDENROD_DEPT_STORE_2F, 2, GoldenrodDeptStore2FYoungsterScript);
    entry(GOLDENROD_DEPT_STORE_2F, 3, GoldenrodDeptStore2FCooltrainerFScript);
    entry(GOLDENROD_DEPT_STORE_2F, 4, GoldenrodDeptStore2FGentlemanScript);

    // maps/GoldenrodDeptStore3F.c
    entry(GOLDENROD_DEPT_STORE_3F, 0, GoldenrodDeptStore3FClerkScript);
    entry(GOLDENROD_DEPT_STORE_3F, 1, GoldenrodDeptStore3FSuperNerdScript);
    entry(GOLDENROD_DEPT_STORE_3F, 2, GoldenrodDeptStore3FRockerScript);

    // maps/GoldenrodDeptStore4F.c
    entry(GOLDENROD_DEPT_STORE_4F, 0, GoldenrodDeptStore4FClerkScript);
    entry(GOLDENROD_DEPT_STORE_4F, 1, GoldenrodDeptStore4FCooltrainerMScript);
    entry(GOLDENROD_DEPT_STORE_4F, 2, GoldenrodDeptStore4FBugCatcherScript);
    entry(GOLDENROD_DEPT_STORE_4F, 3, GoldenrodDeptStore4FGameboyKidScript);

    // maps/GoldenrodDeptStore5F.c
    entry(GOLDENROD_DEPT_STORE_5F, 0, GoldenrodDeptStore5FClerkScript);
    entry(GOLDENROD_DEPT_STORE_5F, 1, GoldenrodDeptStore5FLassScript);
    entry(GOLDENROD_DEPT_STORE_5F, 2, Mike);
    entry(GOLDENROD_DEPT_STORE_5F, 3, GoldenrodDeptStore5FPokefanMScript);
    entry(GOLDENROD_DEPT_STORE_5F, 4, Carrie);
    entry(GOLDENROD_DEPT_STORE_5F, 5, GoldenrodDeptStore5FReceptionistScript);

    // maps/GoldenrodDeptStore6F.c
    entry(GOLDENROD_DEPT_STORE_6F, 0, GoldenrodDeptStore6FLassScript);
    entry(GOLDENROD_DEPT_STORE_6F, 1, GoldenrodDeptStore6FSuperNerdScript);

    // maps/GoldenrodDeptStoreB1F.c
    entry(GOLDENROD_DEPT_STORE_B1F, 0, GoldenrodDeptStoreB1FEther);
    entry(GOLDENROD_DEPT_STORE_B1F, 1, GoldenrodDeptStoreB1FAmuletCoin);
    entry(GOLDENROD_DEPT_STORE_B1F, 2, GoldenrodDeptStoreB1FBurnHeal);
    entry(GOLDENROD_DEPT_STORE_B1F, 3, GoldenrodDeptStoreB1FUltraBall);
    entry(GOLDENROD_DEPT_STORE_B1F, 4, GoldenrodDeptStoreB1FBlackBelt1Script);
    entry(GOLDENROD_DEPT_STORE_B1F, 5, GoldenrodDeptStoreB1FBlackBelt2Script);
    entry(GOLDENROD_DEPT_STORE_B1F, 6, GoldenrodDeptStoreB1FBlackBelt3Script);
    entry(GOLDENROD_DEPT_STORE_B1F, 7, GoldenrodDeptStoreB1FMachopScript);

    // maps/PokecomCenter.c
    entry(GOLDENROD_POKECENTER_1F, 0, GoldenrodPokecenter1FNurseScript);
    entry2(GOLDENROD_POKECENTER_1F, 1, GoldenrodPokecenter1FTradeCornerAttendantScript, aGoldenrodPokecenter1F_GSBallSceneLeft_gsball);
    entry2(GOLDENROD_POKECENTER_1F, 2, GoldenrodPokecenter1FSuperNerdScript, aGoldenrodPokecenter1F_GSBallSceneLeft_gsball + 1);
    entry(GOLDENROD_POKECENTER_1F, 3, GoldenrodPokecenter1FGameboyKidScript);
    entry(GOLDENROD_POKECENTER_1F, 4, GoldenrodPokecenter1FLassScript);
    entry(GOLDENROD_POKECENTER_1F, 5, GoldenrodPokecenter1FPokefanF);
    entry2(GOLDENROD_POKECENTER_1F, 6, GoldenrodPokecenter1FLass2Script, aGoldenrodPokecenter1F_GSBallSceneLeft_gsball + 2);
    entry2(GOLDENROD_POKECENTER_1F, 7, GoldenrodPokecenter1FYoungsterScript, aGoldenrodPokecenter1F_GSBallSceneLeft_gsball + 3);
    entry2(GOLDENROD_POKECENTER_1F, 8, GoldenrodPokecenter1FTeacherScript, aGoldenrodPokecenter1F_GSBallSceneLeft_gsball + 4);
    entry2(GOLDENROD_POKECENTER_1F, 9, GoldenrodPokecenter1FRockerScript, aGoldenrodPokecenter1F_GSBallSceneLeft_gsball + 5);
    entry2(GOLDENROD_POKECENTER_1F, 10, GoldenrodPokecenter1FGrampsScript, aGoldenrodPokecenter1F_GSBallSceneLeft_gsball + 6);

    // maps/PokecomCenterAdminOfficeMobile.c
    entry(POKECOM_CENTER_ADMIN_OFFICE_MOBILE, 0, PokecomCenterAdminOfficeMobileScientist1Script);
    entry(POKECOM_CENTER_ADMIN_OFFICE_MOBILE, 1, PokecomCenterAdminOfficeMobileScientist2Script);
    entry(POKECOM_CENTER_ADMIN_OFFICE_MOBILE, 2, PokecomCenterAdminOfficeMobileScientist3Script);

    entry(SPROUT_TOWER_1F, 0, SproutTower1FSage1Script);
    entry(SPROUT_TOWER_1F, 1, SproutTower1FSage2Script);
    entry(SPROUT_TOWER_1F, 2, SproutTower1FGrannyScript);
    entry(SPROUT_TOWER_1F, 3, SproutTower1FTeacherScript);
    entry(SPROUT_TOWER_1F, 4, TrainerSageChow);
    entry(SPROUT_TOWER_1F, 5, SproutTower1FParlyzHeal);

    entry(SPROUT_TOWER_2F, 0, TrainerSageNico);
    entry(SPROUT_TOWER_2F, 1, TrainerSageEdmond);
    entry(SPROUT_TOWER_2F, 2, SproutTower2FXAccuracy);

    entry(SPROUT_TOWER_3F, 0, TrainerSageJin);
    entry(SPROUT_TOWER_3F, 1, TrainerSageTroy);
    entry(SPROUT_TOWER_3F, 2, SageLiScript);
    entry(SPROUT_TOWER_3F, 3, TrainerSageNeal);
    entry(SPROUT_TOWER_3F, 4, SproutTower3FPotion);
    entry(SPROUT_TOWER_3F, 5, SproutTower3FEscapeRope);
    entry(SPROUT_TOWER_3F, 6, ObjectEvent);

    entry(RUINS_OF_ALPH_OUTSIDE, 0, TrainerPsychicNathan);
    entry(RUINS_OF_ALPH_OUTSIDE, 1, RuinsOfAlphOutsideScientistScript);
    entry(RUINS_OF_ALPH_OUTSIDE, 2, RuinsOfAlphOutsideFisherScript);
    entry(RUINS_OF_ALPH_OUTSIDE, 3, RuinsOfAlphOutsideYoungster1Script);
    entry(RUINS_OF_ALPH_OUTSIDE, 4, RuinsOfAlphOutsideYoungster2Script);

    entry(RUINS_OF_ALPH_INNER_CHAMBER, 0, RuinsOfAlphInnerChamberFisherScript);
    entry(RUINS_OF_ALPH_INNER_CHAMBER, 1, RuinsOfAlphInnerChamberTeacherScript);
    entry(RUINS_OF_ALPH_INNER_CHAMBER, 2, RuinsOfAlphInnerChamberGrampsScript);

    entry(RUINS_OF_ALPH_RESEARCH_CENTER, 0, RuinsOfAlphResearchCenterScientist1Script);
    entry(RUINS_OF_ALPH_RESEARCH_CENTER, 1, RuinsOfAlphResearchCenterScientist2Script);
    entry(RUINS_OF_ALPH_RESEARCH_CENTER, 2, RuinsOfAlphResearchCenterScientist3Script);

    entry(RUINS_OF_ALPH_KABUTO_CHAMBER, 0, RuinsOfAlphKabutoChamberReceptionistScript);
    entry(RUINS_OF_ALPH_KABUTO_CHAMBER, 1, RuinsOfAlphKabutoChamberScientistScript);

    entry(RUINS_OF_ALPH_KABUTO_ITEM_ROOM, 0, RuinsOfAlphKabutoItemRoomBerry);
    entry(RUINS_OF_ALPH_KABUTO_ITEM_ROOM, 1, RuinsOfAlphKabutoItemRoomPsncureberry);
    entry(RUINS_OF_ALPH_KABUTO_ITEM_ROOM, 2, RuinsOfAlphKabutoItemRoomHealPowder);
    entry(RUINS_OF_ALPH_KABUTO_ITEM_ROOM, 3, RuinsOfAlphKabutoItemRoomEnergypowder);

    entry(UNION_CAVE_1F, 0, TrainerHikerDaniel);
    entry(UNION_CAVE_1F, 1, TrainerPokemaniacLarry);
    entry(UNION_CAVE_1F, 2, TrainerHikerRussell);
    entry(UNION_CAVE_1F, 3, TrainerFirebreatherRay);
    entry(UNION_CAVE_1F, 4, TrainerFirebreatherBill);
    entry(UNION_CAVE_1F, 5, UnionCave1FGreatBall);
    entry(UNION_CAVE_1F, 6, UnionCave1FXAttack);
    entry(UNION_CAVE_1F, 7, UnionCave1FPotion);
    entry(UNION_CAVE_1F, 8, UnionCave1FAwakening);

    entry(UNION_CAVE_B1F, 0, TrainerHikerPhillip);
    entry(UNION_CAVE_B1F, 1, TrainerHikerLeonard);
    entry(UNION_CAVE_B1F, 2, TrainerPokemaniacAndrew);
    entry(UNION_CAVE_B1F, 3, TrainerPokemaniacCalvin);
    entry(UNION_CAVE_B1F, 4, UnionCaveB1FTMSwift);
    entry(UNION_CAVE_B1F, 5, UnionCaveB1FBoulder);
    entry(UNION_CAVE_B1F, 6, UnionCaveB1FXDefend);

    entry(UNION_CAVE_B2F, 0, TrainerCooltrainermNick);
    entry(UNION_CAVE_B2F, 1, TrainerCooltrainerfGwen);
    entry(UNION_CAVE_B2F, 2, TrainerCooltrainerfEmma);
    entry(UNION_CAVE_B2F, 3, UnionCaveB2FElixer);
    entry(UNION_CAVE_B2F, 4, UnionCaveB2FHyperPotion);
    entry(UNION_CAVE_B2F, 5, UnionCaveLapras);

    entry(SLOWPOKE_WELL_B1F, 0, TrainerGruntM29);
    entry(SLOWPOKE_WELL_B1F, 1, TrainerGruntM1);
    entry(SLOWPOKE_WELL_B1F, 2, TrainerGruntM2);
    entry(SLOWPOKE_WELL_B1F, 3, TrainerGruntF1);
    entry(SLOWPOKE_WELL_B1F, 4, SlowpokeWellB1FSlowpokeWithMailScript);
    entry(SLOWPOKE_WELL_B1F, 5, SlowpokeWellB1FTaillessSlowpokeScript);
    entry(SLOWPOKE_WELL_B1F, 6, SlowpokeWellB1FKurtScript);
    entry(SLOWPOKE_WELL_B1F, 7, SlowpokeWellB1FBoulder);
    entry(SLOWPOKE_WELL_B1F, 8, SlowpokeWellB1FSuperPotion);

    entry(SLOWPOKE_WELL_B2F, 0, SlowpokeWellB2FGymGuideScript);
    entry(SLOWPOKE_WELL_B2F, 1, SlowpokeWellB2FTMRainDance);

    entry(ILEX_FOREST, 0, IlexForestFarfetchdScript);
    entry(ILEX_FOREST, 1, IlexForestCharcoalApprenticeScript);
    entry(ILEX_FOREST, 2, IlexForestCharcoalMasterScript);
    entry(ILEX_FOREST, 3, IlexForestHeadbuttGuyScript);
    entry(ILEX_FOREST, 4, IlexForestRevive);
    entry(ILEX_FOREST, 5, ObjectEvent);
    entry(ILEX_FOREST, 6, IlexForestLassScript);
    entry(ILEX_FOREST, 7, TrainerBugCatcherWayne);
    entry(ILEX_FOREST, 8, IlexForestXAttack);
    entry(ILEX_FOREST, 9, IlexForestAntidote);
    entry(ILEX_FOREST, 10, IlexForestEther);

    entry(ILEX_FOREST_AZALEA_GATE, 0, IlexForestAzaleaGateOfficerScript);
    entry(ILEX_FOREST_AZALEA_GATE, 1, IlexForestAzaleaGateGrannyScript);

    // maps/RadioTower1F.c
    entry(RADIO_TOWER_1F, 0, RadioTower1FReceptionistScript);
    entry(RADIO_TOWER_1F, 1, RadioTower1FLassScript);
    entry(RADIO_TOWER_1F, 2, RadioTower1FYoungsterScript);
    entry(RADIO_TOWER_1F, 3, TrainerGruntM3);
    entry(RADIO_TOWER_1F, 4, RadioTower1FLuckyNumberManScript);
    entry(RADIO_TOWER_1F, 5, RadioTower1FRadioCardWomanScript);

    // maps/RadioTower2F.c
    entry(RADIO_TOWER_2F, 0,  RadioTower2FSuperNerdScript);
    entry(RADIO_TOWER_2F, 1,  RadioTower2FTeacherScript);
    entry(RADIO_TOWER_2F, 2,  TrainerGruntM4);
    entry(RADIO_TOWER_2F, 3,  TrainerGruntM5);
    entry(RADIO_TOWER_2F, 4,  TrainerGruntM6);
    entry(RADIO_TOWER_2F, 5,  TrainerGruntF2);
    entry(RADIO_TOWER_2F, 6,  RadioTower2FBlackBelt1Script);
    entry(RADIO_TOWER_2F, 7,  RadioTower2FBlackBelt2Script);
    entry(RADIO_TOWER_2F, 8,  RadioTowerJigglypuff);
    entry(RADIO_TOWER_2F, 9,  Buena);
    entry(RADIO_TOWER_2F, 10, RadioTowerBuenaPrizeReceptionist);

    entry(NATIONAL_PARK, 0,  NationalParkLassScript);
    entry(NATIONAL_PARK, 1,  NationalParkPokefanFScript);
    entry(NATIONAL_PARK, 2,  NationalParkTeacher1Script);
    entry(NATIONAL_PARK, 3,  NationalParkYoungster1Script);
    entry(NATIONAL_PARK, 4,  NationalParkYoungster2Script);
    entry(NATIONAL_PARK, 5,  NationalParkTeacher2Script);
    entry(NATIONAL_PARK, 6,  NationalParkPersian);
    entry(NATIONAL_PARK, 7,  TrainerSchoolboyJack1);
    entry(NATIONAL_PARK, 8,  TrainerPokefanfBeverly1);
    entry(NATIONAL_PARK, 9,  TrainerPokefanmWilliam);
    entry(NATIONAL_PARK, 10, TrainerLassKrise);
    entry(NATIONAL_PARK, 11, NationalParkParlyzHeal);
    entry(NATIONAL_PARK, 12, NationalParkGameboyKidScript);
    entry(NATIONAL_PARK, 13, NationalParkTMDig);

    entry(NATIONAL_PARK_BUG_CONTEST, 0,  BugCatchingContestant1AScript);
    entry(NATIONAL_PARK_BUG_CONTEST, 1,  BugCatchingContestant2AScript);
    entry(NATIONAL_PARK_BUG_CONTEST, 2,  BugCatchingContestant3AScript);
    entry(NATIONAL_PARK_BUG_CONTEST, 3,  BugCatchingContestant4AScript);
    entry(NATIONAL_PARK_BUG_CONTEST, 4,  BugCatchingContestant5AScript);
    entry(NATIONAL_PARK_BUG_CONTEST, 5,  BugCatchingContestant6AScript);
    entry(NATIONAL_PARK_BUG_CONTEST, 6,  BugCatchingContestant7AScript);
    entry(NATIONAL_PARK_BUG_CONTEST, 7,  BugCatchingContestant8AScript);
    entry(NATIONAL_PARK_BUG_CONTEST, 8,  BugCatchingContestant9AScript);
    entry(NATIONAL_PARK_BUG_CONTEST, 9,  BugCatchingContestant10AScript);
    entry(NATIONAL_PARK_BUG_CONTEST, 10, NationalParkBugContestParlyzHeal);
    entry(NATIONAL_PARK_BUG_CONTEST, 11, NationalParkBugContestTMDig);

    entry(DARK_CAVE_BLACKTHORN_ENTRANCE, 0, DarkCaveBlackthornEntrancePharmacistScript);
    entry(DARK_CAVE_BLACKTHORN_ENTRANCE, 1, DarkCaveBlackthornEntranceRevive);
    entry(DARK_CAVE_BLACKTHORN_ENTRANCE, 2, DarkCaveBlackthornEntranceTMSnore);

    entry(DARK_CAVE_VIOLET_ENTRANCE, 0, DarkCaveVioletEntrancePotion);
    entry(DARK_CAVE_VIOLET_ENTRANCE, 1, DarkCaveVioletEntranceRock);
    entry(DARK_CAVE_VIOLET_ENTRANCE, 2, DarkCaveVioletEntranceRock);
    entry(DARK_CAVE_VIOLET_ENTRANCE, 3, DarkCaveVioletEntranceRock);
    entry(DARK_CAVE_VIOLET_ENTRANCE, 4, DarkCaveVioletEntranceRock);
    entry(DARK_CAVE_VIOLET_ENTRANCE, 5, DarkCaveVioletEntranceFullHeal);
    entry(DARK_CAVE_VIOLET_ENTRANCE, 6, DarkCaveVioletEntranceHyperPotion);
    entry(DARK_CAVE_VIOLET_ENTRANCE, 7, DarkCaveVioletEntranceDireHit);
}

const void* GetRealScriptPointer(uint8_t group, uint8_t map, uint8_t index) {
    struct ScriptGBPtr* out;
    int idx = _idx(group, map, index);
    HASH_FIND_INT(gb_script_table,&idx, out);
    if(out) {
        return out->script;
    }
    return NULL;
}

uint32_t GetGBScriptPointer(uint8_t group, uint8_t map, uint8_t index) {
    struct ScriptGBPtr* out;
    int idx = _idx(group, map, index);
    HASH_FIND_INT(gb_script_table,&idx, out);
    if(out) {
        return out->gb_ptr;
    }
    return 0;
}