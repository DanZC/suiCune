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

    entry(CIANWOOD_CITY, 0, CianwoodCityYoungster);
    entry(CIANWOOD_CITY, 1, CianwoodCityPokefanM);
    entry(CIANWOOD_CITY, 2, CianwoodCityLass);
    entry(CIANWOOD_CITY, 3, CianwoodCityRock);
    entry(CIANWOOD_CITY, 4, CianwoodCityRock);
    entry(CIANWOOD_CITY, 5, CianwoodCityRock);
    entry(CIANWOOD_CITY, 6, CianwoodCityRock);
    entry(CIANWOOD_CITY, 7, CianwoodCityRock);
    entry(CIANWOOD_CITY, 8, CianwoodCityRock);
    entry(CIANWOOD_CITY, 9, CianwoodCityChucksWife);
    entry(CIANWOOD_CITY, 10, ObjectEvent);
    entry(CIANWOOD_CITY, 11, ObjectEvent);

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

    entry(OLIVINE_CITY, 0, OlivineCitySailor1Script);
    entry(OLIVINE_CITY, 1, OlivineCityStandingYoungsterScript);
    entry(OLIVINE_CITY, 2, OlivineCitySailor2Script);
    entry(OLIVINE_CITY, 3, ObjectEvent);

    entry(ECRUTEAK_CITY, 0, EcruteakCityGramps1Script);
    entry(ECRUTEAK_CITY, 1, EcruteakCityGramps2Script);
    entry(ECRUTEAK_CITY, 2, EcruteakCityLass1Script);
    entry(ECRUTEAK_CITY, 3, EcruteakCityLass2Script);
    entry(ECRUTEAK_CITY, 4, EcruteakCityFisherScript);
    entry(ECRUTEAK_CITY, 5, EcruteakCityYoungsterScript);
    entry(ECRUTEAK_CITY, 6, EcruteakCityGramps3Script);

    entry(MAHOGANY_TOWN, 0, MahoganyTownPokefanMScript);
    entry(MAHOGANY_TOWN, 1, MahoganyTownGrampsScript);
    entry(MAHOGANY_TOWN, 2, MahoganyTownFisherScript);
    entry(MAHOGANY_TOWN, 3, MahoganyTownLassScript);

    entry(LAKE_OF_RAGE, 0, LakeOfRageLanceScript);
    entry(LAKE_OF_RAGE, 1, LakeOfRageGrampsScript);
    entry(LAKE_OF_RAGE, 2, LakeOfRageSuperNerdScript);
    entry(LAKE_OF_RAGE, 3, LakeOfRageCooltrainerFScript);
    entry(LAKE_OF_RAGE, 4, TrainerFisherAndre);
    entry(LAKE_OF_RAGE, 5, TrainerFisherRaymond);
    entry(LAKE_OF_RAGE, 6, TrainerCooltrainermAaron);
    entry(LAKE_OF_RAGE, 7, TrainerCooltrainerfLois);
    entry(LAKE_OF_RAGE, 8, RedGyarados);
    entry(LAKE_OF_RAGE, 9, WesleyScript);
    entry(LAKE_OF_RAGE, 10, LakeOfRageElixer);
    entry(LAKE_OF_RAGE, 11, LakeOfRageTMDetect);

    entry(BLACKTHORN_CITY, 0, BlackthornSuperNerdScript);
    entry(BLACKTHORN_CITY, 1, BlackthornSuperNerdScript);
    entry(BLACKTHORN_CITY, 2, BlackthornGramps1Script);
    entry(BLACKTHORN_CITY, 3, BlackthornGramps2Script);
    entry(BLACKTHORN_CITY, 4, BlackthornBlackBeltScript);
    entry(BLACKTHORN_CITY, 5, BlackthornCooltrainerF1Script);
    entry(BLACKTHORN_CITY, 6, BlackthornYoungsterScript);
    entry(BLACKTHORN_CITY, 7, SantosScript);
    entry(BLACKTHORN_CITY, 8, BlackthornCooltrainerF2Script);

    entry(VIRIDIAN_CITY, 0, ViridianCityCoffeeGramps);
    entry(VIRIDIAN_CITY, 1, ViridianCityGrampsNearGym);
    entry(VIRIDIAN_CITY, 2, ViridianCityDreamEaterFisher);
    entry(VIRIDIAN_CITY, 3, ViridianCityYoungsterScript);

    entry(ROUTE_1, 0, TrainerSchoolboyDanny);
    entry(ROUTE_1, 1, TrainerCooltrainerfQuinn);
    entry(ROUTE_1, 2, Route1FruitTree);

    entry(ROUTE_2, 0, TrainerBugCatcherRob);
    entry(ROUTE_2, 1, TrainerBugCatcherEd);
    entry(ROUTE_2, 2, TrainerBugCatcherDoug);
    entry(ROUTE_2, 3, Route2DireHit);
    entry(ROUTE_2, 4, Route2MaxPotion);
    entry(ROUTE_2, 5, Route2Carbos);
    entry(ROUTE_2, 6, Route2Elixer);
    entry(ROUTE_2, 7, Route2FruitTree);

    entry(ROUTE_2_GATE, 0, Route2GateScientistScript);

    entry(ROUTE_2_NUGGET_HOUSE, 0, Route2NuggetHouseFisherScript);

    entry(ROUTE_26, 0, TrainerCooltrainermJake);
    entry(ROUTE_26, 1, TrainerCooltrainermGaven3);
    entry(ROUTE_26, 2, TrainerCooltrainerfJoyce);
    entry(ROUTE_26, 3, TrainerCooltrainerfBeth1);
    entry(ROUTE_26, 4, TrainerPsychicRichard);
    entry(ROUTE_26, 5, TrainerFisherScott);
    entry(ROUTE_26, 6, Route26FruitTree);
    entry(ROUTE_26, 7, Route26MaxElixer);
    
    entry(ROUTE_26_HEAL_HOUSE, 0, Route26HealHouseTeacherScript);
    
    entry(ROUTE_27, 0, TrainerCooltrainermBlake);
    entry(ROUTE_27, 1, TrainerCooltrainermBrian);
    entry(ROUTE_27, 2, TrainerCooltrainerfReena);
    entry(ROUTE_27, 3, TrainerCooltrainerfMegan);
    entry(ROUTE_27, 4, TrainerPsychicGilbert);
    entry(ROUTE_27, 5, TrainerBirdKeeperJose2);
    entry(ROUTE_27, 6, Route27TMSolarbeam);
    entry(ROUTE_27, 7, Route27RareCandy);
    entry(ROUTE_27, 8, Route27FisherScript);

    entry(ROUTE_27_SANDSTORM_HOUSE, 0, SandstormHouseWoman);

    entry(ROUTE_28_STEEL_WING_HOUSE, 0, Celebrity);
    entry(ROUTE_28_STEEL_WING_HOUSE, 1, CelebritysFearow);

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

    entry(ROUTE_37, 0, TrainerTwinsAnnandanne1);
    entry(ROUTE_37, 1, TrainerTwinsAnnandanne2);
    entry(ROUTE_37, 2, TrainerPsychicGreg);
    entry(ROUTE_37, 3, Route37FruitTree1);
    entry(ROUTE_37, 4, SunnyScript);
    entry(ROUTE_37, 5, Route37FruitTree2);
    entry(ROUTE_37, 6, Route37FruitTree3);

    entry(ROUTE_38, 0, TrainerSchoolboyChad1);
    entry(ROUTE_38, 1, TrainerLassDana1);
    entry(ROUTE_38, 2, TrainerBirdKeeperToby);
    entry(ROUTE_38, 3, TrainerBeautyValerie);
    entry(ROUTE_38, 4, TrainerSailorHarry);
    entry(ROUTE_38, 5, Route38FruitTree);
    entry(ROUTE_38, 6, TrainerBeautyOlivia);

    entry(ROUTE_38_ECRUTEAK_GATE, 0, Route38EcruteakGateOfficerScript);

    entry(ROUTE_39, 0, TrainerSailorEugene);
    entry(ROUTE_39, 1, TrainerPokefanmDerek);
    entry(ROUTE_39, 2, TrainerPokefanfRuth);
    entry(ROUTE_39, 3, Route39Miltank);
    entry(ROUTE_39, 4, Route39Miltank);
    entry(ROUTE_39, 5, Route39Miltank);
    entry(ROUTE_39, 6, Route39Miltank);
    entry(ROUTE_39, 7, TrainerPsychicNorman);
    entry(ROUTE_39, 8, Route39FruitTree);
    entry(ROUTE_39, 9, TrainerPokefanfJaime);

    entry(ROUTE_39_BARN, 0, Route39BarnTwin1Script);
    entry(ROUTE_39_BARN, 1, Route39BarnTwin2Script);
    entry(ROUTE_39_BARN, 2, MoomooScript);

    entry(ROUTE_39_FARMHOUSE, 0, PokefanM_DairyFarmer);
    entry(ROUTE_39_FARMHOUSE, 1, PokefanF_SnoreFarmer);

    entry(ROUTE_40, 0, TrainerSwimmermSimon);
    entry(ROUTE_40, 1, TrainerSwimmermRandall);
    entry(ROUTE_40, 2, TrainerSwimmerfElaine);
    entry(ROUTE_40, 3, TrainerSwimmerfPaula);
    entry(ROUTE_40, 4, Route40Rock);
    entry(ROUTE_40, 5, Route40Rock);
    entry(ROUTE_40, 6, Route40Rock);
    entry(ROUTE_40, 7, Route40Lass1Script);
    entry(ROUTE_40, 8, MonicaScript);
    entry(ROUTE_40, 9, Route40PokefanMScript);
    entry(ROUTE_40, 10, Route40Lass2Script);
    entry(ROUTE_40, 11, Route40StandingYoungsterScript);

    entry(ROUTE_40_BATTLE_TOWER_GATE, 0, Route40BattleTowerGateRockerScript);
    entry(ROUTE_40_BATTLE_TOWER_GATE, 1, Route40BattleTowerGateTwinScript);

    entry(ROUTE_41, 0, TrainerSwimmermCharlie);
    entry(ROUTE_41, 1, TrainerSwimmermGeorge);
    entry(ROUTE_41, 2, TrainerSwimmermBerke);
    entry(ROUTE_41, 3, TrainerSwimmermKirk);
    entry(ROUTE_41, 4, TrainerSwimmermMathew);
    entry(ROUTE_41, 5, TrainerSwimmerfKaylee);
    entry(ROUTE_41, 6, TrainerSwimmerfSusie);
    entry(ROUTE_41, 7, TrainerSwimmerfDenise);
    entry(ROUTE_41, 8, TrainerSwimmerfKara);
    entry(ROUTE_41, 9, TrainerSwimmerfWendy);

    entry(ROUTE_42, 0, TrainerFisherTully);
    entry(ROUTE_42, 1, TrainerHikerBenjamin);
    entry(ROUTE_42, 2, TrainerPokemaniacShane);
    entry(ROUTE_42, 3, Route42FruitTree1);
    entry(ROUTE_42, 4, Route42FruitTree2);
    entry(ROUTE_42, 5, Route42FruitTree3);
    entry(ROUTE_42, 6, Route42UltraBall);
    entry(ROUTE_42, 7, Route42SuperPotion);
    entry(ROUTE_42, 8, ObjectEvent);

    entry(ROUTE_42_ECRUTEAK_GATE, 0, Route42EcruteakGateOfficerScript);

    entry(ROUTE_43, 0, TrainerPokemaniacBen);
    entry(ROUTE_43, 1, TrainerPokemaniacBrent);
    entry(ROUTE_43, 2, TrainerPokemaniacRon);
    entry(ROUTE_43, 3, TrainerFisherMarvin);
    entry(ROUTE_43, 4, TrainerPicnickerTiffany);
    entry(ROUTE_43, 5, TrainerCamperSpencer);
    entry(ROUTE_43, 6, Route43FruitTree);
    entry(ROUTE_43, 7, Route43MaxEther);
    
    entry(ROUTE_43_MAHOGANY_GATE, 0, Route43MahoganyGateOfficer);

    entry(ROUTE_43_GATE, 0, OfficerScript_GuardWithSludgeBomb);
    entry(ROUTE_43_GATE, 1, RocketScript_MakingABundle);
    entry(ROUTE_43_GATE, 2, RocketScript_MakingABundle);

    entry(ROUTE_44, 0, TrainerFisherWilton1);
    entry(ROUTE_44, 1, TrainerFisherEdgar);
    entry(ROUTE_44, 2, TrainerPsychicPhil);
    entry(ROUTE_44, 3, TrainerPokemaniacZach);
    entry(ROUTE_44, 4, TrainerBirdKeeperVance1);
    entry(ROUTE_44, 5, TrainerCooltrainermAllen);
    entry(ROUTE_44, 6, TrainerCooltrainerfCybil);
    entry(ROUTE_44, 7, Route44FruitTree);
    entry(ROUTE_44, 8, Route44MaxRevive);
    entry(ROUTE_44, 9, Route44UltraBall);
    entry(ROUTE_44, 10, Route44MaxRepel);

    entry(ROUTE_45, 0, TrainerHikerErik);
    entry(ROUTE_45, 1, TrainerHikerMichael);
    entry(ROUTE_45, 2, TrainerHikerParry);
    entry(ROUTE_45, 3, TrainerHikerTimothy);
    entry(ROUTE_45, 4, TrainerBlackbeltKenji);
    entry(ROUTE_45, 5, TrainerCooltrainermRyan);
    entry(ROUTE_45, 6, TrainerCooltrainerfKelly);
    entry(ROUTE_45, 7, Route45FruitTree);
    entry(ROUTE_45, 8, Route45Nugget);
    entry(ROUTE_45, 9, Route45Revive);
    entry(ROUTE_45, 10, Route45Elixer);
    entry(ROUTE_45, 11, Route45MaxPotion);
    entry(ROUTE_45, 12, TrainerCamperQuentin);
    
    entry(ROUTE_46, 0, TrainerHikerBailey);
    entry(ROUTE_46, 1, TrainerCamperTed);
    entry(ROUTE_46, 2, TrainerPicnickerErin1);
    entry(ROUTE_46, 3, Route46FruitTree1);
    entry(ROUTE_46, 4, Route46FruitTree2);
    entry(ROUTE_46, 5, Route46XSpeed);

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

    entry(GOLDENROD_UNDERGROUND_WAREHOUSE, 0, TrainerGruntM24);
    entry(GOLDENROD_UNDERGROUND_WAREHOUSE, 1, TrainerGruntM14);
    entry(GOLDENROD_UNDERGROUND_WAREHOUSE, 2, TrainerGruntM15);
    entry(GOLDENROD_UNDERGROUND_WAREHOUSE, 3, GoldenrodUndergroundWarehouseDirectorScript);
    entry(GOLDENROD_UNDERGROUND_WAREHOUSE, 4, GoldenrodUndergroundWarehouseMaxEther);
    entry(GOLDENROD_UNDERGROUND_WAREHOUSE, 5, GoldenrodUndergroundWarehouseTMSleepTalk);
    entry(GOLDENROD_UNDERGROUND_WAREHOUSE, 6, GoldenrodUndergroundWarehouseUltraBall);

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

    entry(ECRUTEAK_GYM, 0, EcruteakGymMortyScript);
    entry(ECRUTEAK_GYM, 1, TrainerSageJeffrey);
    entry(ECRUTEAK_GYM, 2, TrainerSagePing);
    entry(ECRUTEAK_GYM, 3, TrainerMediumMartha);
    entry(ECRUTEAK_GYM, 4, TrainerMediumGrace);
    entry(ECRUTEAK_GYM, 5, EcruteakGymGuideScript);
    entry(ECRUTEAK_GYM, 6, ObjectEvent);

    entry(ECRUTEAK_ITEMFINDER_HOUSE, 0, EcruteakItemfinderGuy);
    entry(ECRUTEAK_ITEMFINDER_HOUSE, 1, EcruteakHistoryBook);

    entry(ECRUTEAK_LUGIA_SPEECH_HOUSE, 0, EcruteakLugiaSpeechHouseGrampsScript);
    entry(ECRUTEAK_LUGIA_SPEECH_HOUSE, 1, EcruteakLugiaSpeechHouseYoungsterScript);

    entry(ECRUTEAK_MART, 0, EcruteakMartClerkScript);
    entry(ECRUTEAK_MART, 1, EcruteakMartSuperNerdScript);
    entry(ECRUTEAK_MART, 2, EcruteakMartGrannyScript);

    entry(ECRUTEAK_POKECENTER_1F, 0, EcruteakPokecenter1FNurseScript);
    entry(ECRUTEAK_POKECENTER_1F, 1, EcruteakPokecenter1FPokefanMScript);
    entry(ECRUTEAK_POKECENTER_1F, 2, EcruteakPokecenter1FCooltrainerFScript);
    entry(ECRUTEAK_POKECENTER_1F, 3, EcruteakPokecenter1FGymGuideScript);
    entry(ECRUTEAK_POKECENTER_1F, 4, ObjectEvent);

    entry(ECRUTEAK_TIN_TOWER_ENTRANCE, 0, EcruteakTinTowerEntranceSageScript);
    entry(ECRUTEAK_TIN_TOWER_ENTRANCE, 1, EcruteakTinTowerEntranceSageScript);
    entry(ECRUTEAK_TIN_TOWER_ENTRANCE, 2, EcruteakTinTowerEntranceWanderingSageScript);
    entry(ECRUTEAK_TIN_TOWER_ENTRANCE, 3, EcruteakTinTowerEntranceGrampsScript);

    entry(DANCE_THEATRE, 0, TrainerKimonoGirlNaoko);
    entry(DANCE_THEATRE, 1, TrainerKimonoGirlSayo);
    entry(DANCE_THEATRE, 2, TrainerKimonoGirlZuki);
    entry(DANCE_THEATRE, 3, TrainerKimonoGirlKuni);
    entry(DANCE_THEATRE, 4, TrainerKimonoGirlMiki);
    entry(DANCE_THEATRE, 5, DanceTheaterSurfGuy);
    entry(DANCE_THEATRE, 6, DanceTheaterRhydon);
    entry(DANCE_THEATRE, 7, DanceTheatreCooltrainerMScript);
    entry(DANCE_THEATRE, 8, DanceTheatreGrannyScript);

    entry(WISE_TRIOS_ROOM, 0, WiseTriosRoomSage1Script);
    entry(WISE_TRIOS_ROOM, 1, WiseTriosRoomSage2Script);
    entry(WISE_TRIOS_ROOM, 2, WiseTriosRoomSage3Script);
    entry(WISE_TRIOS_ROOM, 3, TrainerSageGaku);
    entry(WISE_TRIOS_ROOM, 4, TrainerSageMasa);
    entry(WISE_TRIOS_ROOM, 5, TrainerSageKoji);

    entry(OLIVINE_CAFE, 0, OlivineCafeStrengthSailorScript);
    entry(OLIVINE_CAFE, 1, OlivineCafeFishingGuruScript);
    entry(OLIVINE_CAFE, 2, OlivineCafeSailorScript);

    entry(OLIVINE_GOOD_ROD_HOUSE, 0, GoodRodGuru);

    entry(OLIVINE_GYM, 0, OlivineGymJasmineScript);
    entry(OLIVINE_GYM, 1, OlivineGymGuideScript);

    entry(OLIVINE_LIGHTHOUSE_1F, 0, OlivineLighthouse1FSailorScript);
    entry(OLIVINE_LIGHTHOUSE_1F, 1, OlivineLighthouse1FPokefanFScript);

    entry(OLIVINE_LIGHTHOUSE_2F, 0, TrainerSailorHuey);
    entry(OLIVINE_LIGHTHOUSE_2F, 1, TrainerGentlemanAlfred);

    entry(OLIVINE_LIGHTHOUSE_3F, 0, TrainerSailorTerrell);
    entry(OLIVINE_LIGHTHOUSE_3F, 1, TrainerGentlemanPreston);
    entry(OLIVINE_LIGHTHOUSE_3F, 2, TrainerBirdKeeperTheo);
    entry(OLIVINE_LIGHTHOUSE_3F, 3, OlivineLighthouse3FEther);

    entry(OLIVINE_LIGHTHOUSE_4F, 0, TrainerSailorKent);
    entry(OLIVINE_LIGHTHOUSE_4F, 1, TrainerLassConnie);

    entry(OLIVINE_LIGHTHOUSE_5F, 0, TrainerSailorErnest);
    entry(OLIVINE_LIGHTHOUSE_5F, 1, TrainerBirdKeeperDenis);
    entry(OLIVINE_LIGHTHOUSE_5F, 2, OlivineLighthouse5FRareCandy);
    entry(OLIVINE_LIGHTHOUSE_5F, 3, OlivineLighthouse5FSuperRepel);
    entry(OLIVINE_LIGHTHOUSE_5F, 4, OlivineLighthouse5FTMSwagger);

    entry(OLIVINE_LIGHTHOUSE_6F, 0, OlivineLighthouseJasmine);
    entry(OLIVINE_LIGHTHOUSE_6F, 1, OlivineLighthouseAmphy);
    entry(OLIVINE_LIGHTHOUSE_6F, 2, OlivineLighthouse6FSuperPotion);

    entry(OLIVINE_MART, 0, OlivineMartClerkScript);
    entry(OLIVINE_MART, 1, OlivineMartCooltrainerFScript);
    entry(OLIVINE_MART, 2, OlivineMartLassScript);

    entry(OLIVINE_POKECENTER_1F, 0, OlivinePokecenter1FNurseScript);
    entry(OLIVINE_POKECENTER_1F, 1, OlivinePokecenter1FFishingGuruScript);
    entry(OLIVINE_POKECENTER_1F, 2, OlivinePokecenter1FFisherScript);
    entry(OLIVINE_POKECENTER_1F, 3, OlivinePokecenter1FTeacherScript);

    entry(OLIVINE_PORT, 0, OlivinePortSailorAtGangwayScript);
    entry(OLIVINE_PORT, 1, OlivinePortSailorBeforeHOFScript);
    entry(OLIVINE_PORT, 2, OlivinePortSailorAfterHOFScript);
    entry(OLIVINE_PORT, 3, OlivinePortFishingGuru1Script);
    entry(OLIVINE_PORT, 4, OlivinePortFishingGuru2Script);
    entry(OLIVINE_PORT, 5, OlivinePortYoungsterScript);
    entry(OLIVINE_PORT, 6, OlivinePortCooltrainerFScript);

    entry(OLIVINE_PORT_PASSAGE, 0, OlivinePortPassagePokefanMScript);

    entry(OLIVINE_PUNISHMENT_SPEECH_HOUSE, 0, OlivinePunishmentSpeechHouseDad);
    entry(OLIVINE_PUNISHMENT_SPEECH_HOUSE, 1, OlivinePunishmentSpeechHouseDaughter);

    entry(OLIVINE_TIMS_HOUSE, 0, Tim);

    entry(BATTLE_TOWER_1F, 0, BattleTower1FReceptionistScript);
    entry(BATTLE_TOWER_1F, 1, BattleTower1FYoungsterScript);
    entry(BATTLE_TOWER_1F, 2, BattleTower1FCooltrainerFScript);
    entry(BATTLE_TOWER_1F, 3, BattleTower1FBugCatcherScript);
    entry(BATTLE_TOWER_1F, 4, BattleTower1FGrannyScript);

    entry(CIANWOOD_GYM, 0, CianwoodGymChuckScript);
    entry(CIANWOOD_GYM, 1, TrainerBlackbeltYoshi);
    entry(CIANWOOD_GYM, 2, TrainerBlackbeltLao);
    entry(CIANWOOD_GYM, 3, TrainerBlackbeltNob);
    entry(CIANWOOD_GYM, 4, TrainerBlackbeltLung);
    entry(CIANWOOD_GYM, 5, CianwoodGymBoulder);
    entry(CIANWOOD_GYM, 6, CianwoodGymBoulder);
    entry(CIANWOOD_GYM, 7, CianwoodGymBoulder);
    entry(CIANWOOD_GYM, 8, CianwoodGymBoulder);

    entry(CIANWOOD_LUGIA_SPEECH_HOUSE, 0, CianwoodLugiaSpeechHouseTeacherScript);
    entry(CIANWOOD_LUGIA_SPEECH_HOUSE, 1, CianwoodLugiaSpeechHouseLassScript);
    entry(CIANWOOD_LUGIA_SPEECH_HOUSE, 2, CianwoodLugiaSpeechHouseTwinScript);

    entry(CIANWOOD_PHARMACY, 0, CianwoodPharmacist);

    entry(CIANWOOD_PHOTO_STUDIO, 0, CianwoodPhotoStudioFishingGuruScript);

    entry(CIANWOOD_POKECENTER_1F, 0, CianwoodPokecenter1FNurseScript);
    entry(CIANWOOD_POKECENTER_1F, 1, CianwoodPokecenter1FLassScript);
    entry(CIANWOOD_POKECENTER_1F, 2, CianwoodGymGuideScript);
    entry(CIANWOOD_POKECENTER_1F, 3, CianwoodPokecenter1FSuperNerdScript);

    entry(MANIAS_HOUSE, 0, ManiaScript);

    entry(POKE_SEERS_HOUSE, 0, SeerScript);

    entry(MAHOGANY_GYM, 0, MahoganyGymPryceScript);
    entry(MAHOGANY_GYM, 1, TrainerSkierRoxanne);
    entry(MAHOGANY_GYM, 2, TrainerBoarderRonald);
    entry(MAHOGANY_GYM, 3, TrainerSkierClarissa);
    entry(MAHOGANY_GYM, 4, TrainerBoarderBrad);
    entry(MAHOGANY_GYM, 5, TrainerBoarderDouglas);
    entry(MAHOGANY_GYM, 6, MahoganyGymGuideScript);

    entry(MAHOGANY_MART_1F, 0, MahoganyMart1FPharmacistScript);
    entry(MAHOGANY_MART_1F, 1, MahoganyMart1FBlackBeltScript);
    entry(MAHOGANY_MART_1F, 2, ObjectEvent);
    entry(MAHOGANY_MART_1F, 3, ObjectEvent);
    entry(MAHOGANY_MART_1F, 4, MahoganyMart1FGrannyScript);

    entry(MAHOGANY_POKECENTER_1F, 0, MahoganyPokecenter1FNurseScript);
    entry(MAHOGANY_POKECENTER_1F, 1, MahoganyPokecenter1FPokefanMScript);
    entry(MAHOGANY_POKECENTER_1F, 2, MahoganyPokecenter1FYoungsterScript);
    entry(MAHOGANY_POKECENTER_1F, 3, MahoganyPokecenter1FCooltrainerFScript);

    entry(MAHOGANY_RED_GYARADOS_SPEECH_HOUSE, 0, MahoganyRedGyaradosSpeechHouseBlackBeltScript);
    entry(MAHOGANY_RED_GYARADOS_SPEECH_HOUSE, 1, MahoganyRedGyaradosSpeechHouseTeacherScript);

    entry(LAKE_OF_RAGE_HIDDEN_POWER_HOUSE, 0, HiddenPowerGuy);

    entry(LAKE_OF_RAGE_MAGIKARP_HOUSE, 0, MagikarpLengthRaterScript);

    entry(BLACKTHORN_DRAGON_SPEECH_HOUSE, 0, BlackthornDragonSpeechHouseGrannyScript);
    entry(BLACKTHORN_DRAGON_SPEECH_HOUSE, 1, BlackthornDragonSpeechHouseDratiniScript);

    entry(BLACKTHORN_EMYS_HOUSE, 0, Emy);

    entry(BLACKTHORN_GYM_1F, 0, BlackthornGymClairScript);
    entry(BLACKTHORN_GYM_1F, 1, TrainerCooltrainermMike);
    entry(BLACKTHORN_GYM_1F, 2, TrainerCooltrainermPaul);
    entry(BLACKTHORN_GYM_1F, 3, TrainerCooltrainerfLola);
    entry(BLACKTHORN_GYM_1F, 4, BlackthornGymGuideScript);
    
    entry(BLACKTHORN_GYM_2F, 0, TrainerCooltrainermCody);
    entry(BLACKTHORN_GYM_2F, 1, TrainerCooltrainerfFran);
    entry(BLACKTHORN_GYM_2F, 2, BlackthornGymBoulder);
    entry(BLACKTHORN_GYM_2F, 3, BlackthornGymBoulder);
    entry(BLACKTHORN_GYM_2F, 4, BlackthornGymBoulder);
    entry(BLACKTHORN_GYM_2F, 5, BlackthornGymBoulder);
    entry(BLACKTHORN_GYM_2F, 6, BlackthornGymBoulder);
    entry(BLACKTHORN_GYM_2F, 7, BlackthornGymBoulder);

    entry(BLACKTHORN_MART, 0, BlackthornMartClerkScript);
    entry(BLACKTHORN_MART, 1, BlackthornMartCooltrainerMScript);
    entry(BLACKTHORN_MART, 2, BlackthornMartBlackBeltScript);

    entry(BLACKTHORN_POKECENTER_1F, 0, BlackthornPokecenter1FNurseScript);
    entry(BLACKTHORN_POKECENTER_1F, 1, BlackthornPokecenter1FGentlemanScript);
    entry(BLACKTHORN_POKECENTER_1F, 2, BlackthornPokecenter1FTwinScript);
    entry(BLACKTHORN_POKECENTER_1F, 3, BlackthornPokecenter1FCooltrainerMScript);
    
    entry(MOVE_DELETERS_HOUSE, 0, MoveDeleter);

    entry(INDIGO_PLATEAU_POKECENTER_1F, 0, IndigoPlateauPokecenter1FNurseScript);
    entry(INDIGO_PLATEAU_POKECENTER_1F, 1, IndigoPlateauPokecenter1FClerkScript);
    entry(INDIGO_PLATEAU_POKECENTER_1F, 2, IndigoPlateauPokecenter1FCooltrainerMScript);
    entry(INDIGO_PLATEAU_POKECENTER_1F, 3, ObjectEvent);
    entry(INDIGO_PLATEAU_POKECENTER_1F, 4, TeleportGuyScript);
    entry(INDIGO_PLATEAU_POKECENTER_1F, 5, AbraScript);

    entry(WILLS_ROOM, 0, WillScript_Battle);

    entry(KOGAS_ROOM, 0, KogaScript_Battle);

    entry(BRUNOS_ROOM, 0, BrunoScript_Battle);

    entry(KARENS_ROOM, 0, KarenScript_Battle);

    entry(LANCES_ROOM, 0, LancesRoomLanceScript);
    entry(LANCES_ROOM, 1, ObjectEvent);
    entry(LANCES_ROOM, 2, ObjectEvent);

    entry(HALL_OF_FAME, 0, ObjectEvent);

    entry(VIRIDIAN_GYM, 0, ViridianGymBlueScript);
    entry(VIRIDIAN_GYM, 1, ViridianGymGuideScript);

    entry(VIRIDIAN_MART, 0, ViridianMartClerkScript);
    entry(VIRIDIAN_MART, 1, ViridianMartLassScript);
    entry(VIRIDIAN_MART, 2, ViridianMartCooltrainerMScript);

    entry(VIRIDIAN_NICKNAME_SPEECH_HOUSE, 0, ViridianNicknameSpeechHousePokefanMScript);
    entry(VIRIDIAN_NICKNAME_SPEECH_HOUSE, 1, ViridianNicknameSpeechHouseLassScript);
    entry(VIRIDIAN_NICKNAME_SPEECH_HOUSE, 2, Speary);
    entry(VIRIDIAN_NICKNAME_SPEECH_HOUSE, 3, Rattey);

    entry(VIRIDIAN_POKECENTER_1F, 0, ViridianPokecenter1FNurseScript);
    entry(VIRIDIAN_POKECENTER_1F, 1, ViridianPokecenter1FCooltrainerMScript);
    entry(VIRIDIAN_POKECENTER_1F, 2, ViridianPokecenter1FCooltrainerFScript);
    entry(VIRIDIAN_POKECENTER_1F, 3, ViridianPokecenter1FBugCatcherScript);

    entry(TRAINER_HOUSE_1F, 0, TrainerHouse1FReceptionistScript);
    entry(TRAINER_HOUSE_1F, 1, TrainerHouse1FCooltrainerMScript);
    entry(TRAINER_HOUSE_1F, 2, TrainerHouse1FCooltrainerFScript);
    entry(TRAINER_HOUSE_1F, 3, TrainerHouse1FYoungsterScript);
    entry(TRAINER_HOUSE_1F, 4, TrainerHouse1FGentlemanScript);

    entry(TRAINER_HOUSE_B1F, 0, ObjectEvent);
    entry(TRAINER_HOUSE_B1F, 1, ObjectEvent);

    entry(SILVER_CAVE_POKECENTER_1F, 0, SilverCavePokecenter1FNurseScript);
    entry(SILVER_CAVE_POKECENTER_1F, 1, SilverCavePokecenter1FGrannyScript);

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

    entry(RUINS_OF_ALPH_OMANYTE_ITEM_ROOM, 0, RuinsOfAlphOmanyteItemRoomMysteryberry);
    entry(RUINS_OF_ALPH_OMANYTE_ITEM_ROOM, 1, RuinsOfAlphOmanyteItemRoomMysticWater);
    entry(RUINS_OF_ALPH_OMANYTE_ITEM_ROOM, 2, RuinsOfAlphOmanyteItemRoomStardust);
    entry(RUINS_OF_ALPH_OMANYTE_ITEM_ROOM, 3, RuinsOfAlphOmanyteItemRoomStarPiece);

    entry(RUINS_OF_ALPH_AERODACTYL_ITEM_ROOM, 0, RuinsOfAlphAerodactylItemRoomGoldBerry);
    entry(RUINS_OF_ALPH_AERODACTYL_ITEM_ROOM, 1, RuinsOfAlphAerodactylItemRoomMoonStone);
    entry(RUINS_OF_ALPH_AERODACTYL_ITEM_ROOM, 2, RuinsOfAlphAerodactylItemRoomHealPowder);
    entry(RUINS_OF_ALPH_AERODACTYL_ITEM_ROOM, 3, RuinsOfAlphAerodactylItemRoomEnergyRoot);

    entry(RUINS_OF_ALPH_HO_OH_ITEM_ROOM, 0, RuinsOfAlphHoOhItemRoomGoldBerry);
    entry(RUINS_OF_ALPH_HO_OH_ITEM_ROOM, 1, RuinsOfAlphHoOhItemRoomMysteryberry);
    entry(RUINS_OF_ALPH_HO_OH_ITEM_ROOM, 2, RuinsOfAlphHoOhItemRoomRevivalHerb);
    entry(RUINS_OF_ALPH_HO_OH_ITEM_ROOM, 3, RuinsOfAlphHoOhItemRoomCharcoal);

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

    entry(RADIO_TOWER_3F, 0, RadioTower3FSuperNerdScript);
    entry(RADIO_TOWER_3F, 1, RadioTower3FGymGuideScript);
    entry(RADIO_TOWER_3F, 2, RadioTower3FCooltrainerFScript);
    entry(RADIO_TOWER_3F, 3, TrainerGruntM7);
    entry(RADIO_TOWER_3F, 4, TrainerGruntM8);
    entry(RADIO_TOWER_3F, 5, TrainerGruntM9);
    entry(RADIO_TOWER_3F, 6, TrainerScientistMarc);

    entry(RADIO_TOWER_4F, 0, RadioTower4FFisherScript);
    entry(RADIO_TOWER_4F, 1, RadioTower4FDJMaryScript);
    entry(RADIO_TOWER_4F, 2, RadioTowerMeowth);
    entry(RADIO_TOWER_4F, 3, TrainerGruntM10);
    entry(RADIO_TOWER_4F, 4, TrainerExecutivem2);
    entry(RADIO_TOWER_4F, 5, TrainerGruntF4);
    entry(RADIO_TOWER_4F, 6, TrainerScientistRich);

    entry(RADIO_TOWER_5F, 0, Director);
    entry(RADIO_TOWER_5F, 1, ObjectEvent);
    entry(RADIO_TOWER_5F, 2, TrainerExecutivef1);
    entry(RADIO_TOWER_5F, 3, Ben);
    entry(RADIO_TOWER_5F, 4, RadioTower5FUltraBall);

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

    entry(BURNED_TOWER_1F, 0, BurnedTower1FRock);
    entry(BURNED_TOWER_1F, 1, BurnedTower1FEusineScript);
    entry(BURNED_TOWER_1F, 2, ObjectEvent);
    entry(BURNED_TOWER_1F, 3, BurnedTower1FMortyScript);
    entry(BURNED_TOWER_1F, 4, BurnedTower1FHPUp);

    entry(BURNED_TOWER_B1F, 0, BurnedTowerB1FBoulder);
    entry(BURNED_TOWER_B1F, 1, ObjectEvent);
    entry(BURNED_TOWER_B1F, 2, ObjectEvent);
    entry(BURNED_TOWER_B1F, 3, ObjectEvent);
    entry(BURNED_TOWER_B1F, 4, ObjectEvent);
    entry(BURNED_TOWER_B1F, 5, ObjectEvent);
    entry(BURNED_TOWER_B1F, 6, ObjectEvent);
    entry(BURNED_TOWER_B1F, 7, BurnedTowerB1FTMEndure);
    entry(BURNED_TOWER_B1F, 8, BurnedTowerB1FEusine);

    entry(BATTLE_TOWER_OUTSIDE, 0, BattleTowerOutsideYoungsterScript);
    entry(BATTLE_TOWER_OUTSIDE, 1, BattleTowerOutsideBeautyScript);
    entry(BATTLE_TOWER_OUTSIDE, 2, BattleTowerOutsideSailorScript);
    entry(BATTLE_TOWER_OUTSIDE, 3, ObjectEvent);

    entry(WHIRL_ISLAND_SW, 0, WhirlIslandSWUltraBall);

    entry(WHIRL_ISLAND_B1F, 0, WhirlIslandB1FFullRestore);
    entry(WHIRL_ISLAND_B1F, 1, WhirlIslandB1FCarbos);
    entry(WHIRL_ISLAND_B1F, 2, WhirlIslandB1FCalcium);
    entry(WHIRL_ISLAND_B1F, 3, WhirlIslandB1FNugget);
    entry(WHIRL_ISLAND_B1F, 4, WhirlIslandB1FEscapeRope);
    entry(WHIRL_ISLAND_B1F, 5, WhirlIslandB1FBoulder);

    entry(WHIRL_ISLAND_B2F, 0, WhirlIslandB2FFullRestore);
    entry(WHIRL_ISLAND_B2F, 1, WhirlIslandB2FMaxRevive);
    entry(WHIRL_ISLAND_B2F, 2, WhirlIslandB2FMaxElixer);

    entry(WHIRL_ISLAND_LUGIA_CHAMBER, 0, Lugia);

    entry(MOUNT_MORTAR_1F_INSIDE, 0, MountMortar1FBoulder);
    entry(MOUNT_MORTAR_1F_INSIDE, 1, MountMortar1FInsideEscapeRope);
    entry(MOUNT_MORTAR_1F_INSIDE, 2, MountMortar1FInsideMaxRevive);
    entry(MOUNT_MORTAR_1F_INSIDE, 3, MountMortar1FInsideHyperPotion);
    entry(MOUNT_MORTAR_1F_INSIDE, 4, MountMortar1FInsideMaxPotion);
    entry(MOUNT_MORTAR_1F_INSIDE, 5, MountMortar1FInsideNugget);
    entry(MOUNT_MORTAR_1F_INSIDE, 6, TrainerPokemaniacMiller);
    entry(MOUNT_MORTAR_1F_INSIDE, 7, TrainerSupernerdMarkus);
    entry(MOUNT_MORTAR_1F_INSIDE, 8, MountMortar1FInsideIron);
    entry(MOUNT_MORTAR_1F_INSIDE, 9, MountMortar1FInsideUltraBall);

    entry(MOUNT_MORTAR_1F_OUTSIDE, 0, MountMortar1FOutsideEther);
    entry(MOUNT_MORTAR_1F_OUTSIDE, 1, MountMortar1FOutsideRevive);

    entry(MOUNT_MORTAR_2F_INSIDE, 0, MountMortar2FInsideMaxPotion);
    entry(MOUNT_MORTAR_2F_INSIDE, 1, MountMortar2FInsideRareCandy);
    entry(MOUNT_MORTAR_2F_INSIDE, 2, MountMortar2FInsideTMDefenseCurl);
    entry(MOUNT_MORTAR_2F_INSIDE, 3, MountMortar2FInsideDragonScale);
    entry(MOUNT_MORTAR_2F_INSIDE, 4, MountMortar2FInsideElixer);
    entry(MOUNT_MORTAR_2F_INSIDE, 5, MountMortar2FInsideEscapeRope);
    entry(MOUNT_MORTAR_2F_INSIDE, 6, TrainerSupernerdHugh);

    entry(MOUNT_MORTAR_B1F, 0, MountMortarB1FHyperPotion);
    entry(MOUNT_MORTAR_B1F, 1, MountMortarB1FCarbos);
    entry(MOUNT_MORTAR_B1F, 2, MountMortarB1FBoulder);
    entry(MOUNT_MORTAR_B1F, 3, MountMortarB1FKiyoScript);
    entry(MOUNT_MORTAR_B1F, 4, MountMortarB1FFullRestore);
    entry(MOUNT_MORTAR_B1F, 5, MountMortarB1FMaxEther);
    entry(MOUNT_MORTAR_B1F, 6, MountMortarB1FPPUp);

    entry(TEAM_ROCKET_BASE_B1F, 0, ObjectEvent);
    entry(TEAM_ROCKET_BASE_B1F, 1, TrainerGruntM16);
    entry(TEAM_ROCKET_BASE_B1F, 2, TrainerScientistJed);
    entry(TEAM_ROCKET_BASE_B1F, 3, TeamRocketBaseB1FHyperPotion);
    entry(TEAM_ROCKET_BASE_B1F, 4, TeamRocketBaseB1FNugget);
    entry(TEAM_ROCKET_BASE_B1F, 5, TeamRocketBaseB1FGuardSpec);

    entry(TEAM_ROCKET_BASE_B2F, 0, ObjectEvent);
    entry(TEAM_ROCKET_BASE_B2F, 1, ObjectEvent);
    entry(TEAM_ROCKET_BASE_B2F, 2, ObjectEvent);
    entry(TEAM_ROCKET_BASE_B2F, 3, ObjectEvent);
    entry(TEAM_ROCKET_BASE_B2F, 4, RocketElectrode1);
    entry(TEAM_ROCKET_BASE_B2F, 5, RocketElectrode2);
    entry(TEAM_ROCKET_BASE_B2F, 6, RocketElectrode3);
    entry(TEAM_ROCKET_BASE_B2F, 7, ObjectEvent);
    entry(TEAM_ROCKET_BASE_B2F, 8, ObjectEvent);
    entry(TEAM_ROCKET_BASE_B2F, 9, ObjectEvent);
    entry(TEAM_ROCKET_BASE_B2F, 10, TrainerGruntM17);
    entry(TEAM_ROCKET_BASE_B2F, 11, TrainerGruntM18);
    entry(TEAM_ROCKET_BASE_B2F, 12, TrainerGruntM19);
    entry(TEAM_ROCKET_BASE_B2F, 13, TeamRocketBaseB2FTMThief);

    entry(TEAM_ROCKET_BASE_B3F, 0, LanceGetPasswordScript);
    entry(TEAM_ROCKET_BASE_B3F, 1, ObjectEvent);
    entry(TEAM_ROCKET_BASE_B3F, 2, RocketBaseMurkrow);
    entry(TEAM_ROCKET_BASE_B3F, 3, SlowpokeTailGrunt);
    entry(TEAM_ROCKET_BASE_B3F, 4, RaticateTailGrunt);
    entry(TEAM_ROCKET_BASE_B3F, 5, TrainerScientistRoss);
    entry(TEAM_ROCKET_BASE_B3F, 6, TrainerScientistMitch);
    entry(TEAM_ROCKET_BASE_B3F, 7, TeamRocketBaseB3FRocketScript);
    entry(TEAM_ROCKET_BASE_B3F, 8, ObjectEvent);
    entry(TEAM_ROCKET_BASE_B3F, 9, TeamRocketBaseB3FProtein);
    entry(TEAM_ROCKET_BASE_B3F, 10, TeamRocketBaseB3FXSpecial);
    entry(TEAM_ROCKET_BASE_B3F, 11, TeamRocketBaseB3FFullHeal);
    entry(TEAM_ROCKET_BASE_B3F, 12, TeamRocketBaseB3FIceHeal);
    entry(TEAM_ROCKET_BASE_B3F, 13, TeamRocketBaseB3FUltraBall);

    entry(ICE_PATH_1F, 0, IcePath1FHMWaterfall);
    entry(ICE_PATH_1F, 1, IcePath1FPPUp);
    entry(ICE_PATH_1F, 2, IcePath1FProtein);

    entry(ICE_PATH_B1F, 0, IcePathB1FBoulder);
    entry(ICE_PATH_B1F, 1, IcePathB1FBoulder);
    entry(ICE_PATH_B1F, 2, IcePathB1FBoulder);
    entry(ICE_PATH_B1F, 3, IcePathB1FBoulder);
    entry(ICE_PATH_B1F, 4, IcePathB1FIron);

    entry(ICE_PATH_B2F_BLACKTHORN_SIDE, 0, IcePathB2FBlackthornSideTMRest);

    entry(ICE_PATH_B2F_MAHOGANY_SIDE, 0, IcePathB2FMahoganySideBoulder);
    entry(ICE_PATH_B2F_MAHOGANY_SIDE, 1, IcePathB2FMahoganySideBoulder);
    entry(ICE_PATH_B2F_MAHOGANY_SIDE, 2, IcePathB2FMahoganySideBoulder);
    entry(ICE_PATH_B2F_MAHOGANY_SIDE, 3, IcePathB2FMahoganySideBoulder);
    entry(ICE_PATH_B2F_MAHOGANY_SIDE, 4, IcePathB2FMahoganySideFullHeal);
    entry(ICE_PATH_B2F_MAHOGANY_SIDE, 5, IcePathB2FMahoganySideMaxPotion);

    entry(ICE_PATH_B3F, 0, IcePathB3FNevermeltice);
    entry(ICE_PATH_B3F, 1, IcePathB3FRock);

    entry(DRAGONS_DEN_B1F, 0, DragonsDenB1FDragonFangScript);
    entry(DRAGONS_DEN_B1F, 1, ObjectEvent);
    entry(DRAGONS_DEN_B1F, 2, DragonsDenB1FSilverScript);
    entry(DRAGONS_DEN_B1F, 3, TrainerCooltrainermDarin);
    entry(DRAGONS_DEN_B1F, 4, TrainerCooltrainerfCara);
    entry(DRAGONS_DEN_B1F, 5, TrainerTwinsLeaandpia1);
    entry(DRAGONS_DEN_B1F, 6, TrainerTwinsLeaandpia2);
    entry(DRAGONS_DEN_B1F, 7, DragonsDenB1FCalcium);
    entry(DRAGONS_DEN_B1F, 8, DragonsDenB1FMaxElixer);

    entry(DRAGON_SHRINE, 0, DragonShrineElder1Script);
    entry(DRAGON_SHRINE, 1, DragonShrineElder2Script);
    entry(DRAGON_SHRINE, 2, DragonShrineElder3Script);
    entry(DRAGON_SHRINE, 3, ObjectEvent);

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

    entry(TIN_TOWER_1F, 0, ObjectEvent);
    entry(TIN_TOWER_1F, 1, ObjectEvent);
    entry(TIN_TOWER_1F, 2, ObjectEvent);
    entry(TIN_TOWER_1F, 3, TinTower1FEusine);
    entry(TIN_TOWER_1F, 4, TinTower1FSage1Script);
    entry(TIN_TOWER_1F, 5, TinTower1FSage2Script);
    entry(TIN_TOWER_1F, 6, TinTower1FSage3Script);
    entry(TIN_TOWER_1F, 7, TinTower1FSage4Script);
    entry(TIN_TOWER_1F, 8, TinTower1FSage5Script);
    entry(TIN_TOWER_1F, 9, TinTower1FSage6Script);

    entry(TIN_TOWER_3F, 0, TinTower3FFullHeal);

    entry(TIN_TOWER_4F, 0, TinTower4FUltraBall);
    entry(TIN_TOWER_4F, 1, TinTower4FPPUp);
    entry(TIN_TOWER_4F, 2, TinTower4FEscapeRope);

    entry(TIN_TOWER_5F, 0, TinTower5FRareCandy);

    entry(TIN_TOWER_6F, 0, TinTower6FMaxPotion);

    entry(TIN_TOWER_7F, 0, TinTower7FMaxRevive);

    entry(TIN_TOWER_8F, 0, TinTower8FNugget);
    entry(TIN_TOWER_8F, 1, TinTower8FMaxElixer);
    entry(TIN_TOWER_8F, 2, TinTower8FFullRestore);

    entry(TIN_TOWER_9F, 0, TinTower9FHPUp);

    entry(TIN_TOWER_ROOF, 0, TinTowerHoOh);

    entry(TOHJO_FALLS, 0, TohjoFallsMoonStone);

    entry(VICTORY_ROAD_GATE, 0, VictoryRoadGateOfficerScript);
    entry(VICTORY_ROAD_GATE, 1, VictoryRoadGateLeftBlackBeltScript);
    entry(VICTORY_ROAD_GATE, 2, VictoryRoadGateRightBlackBeltScript);

    entry(VICTORY_ROAD, 0, ObjectEvent);
    entry(VICTORY_ROAD, 1, VictoryRoadTMEarthquake);
    entry(VICTORY_ROAD, 2, VictoryRoadMaxRevive);
    entry(VICTORY_ROAD, 3, VictoryRoadFullRestore);
    entry(VICTORY_ROAD, 4, VictoryRoadFullHeal);
    entry(VICTORY_ROAD, 5, VictoryRoadHPUp);

    entry(SILVER_CAVE_ITEM_ROOMS, 0, SilverCaveItemRoomsMaxRevive);
    entry(SILVER_CAVE_ITEM_ROOMS, 1, SilverCaveItemRoomsFullRestore);

    entry(SILVER_CAVE_ROOM_1, 0, SilverCaveRoom1MaxElixer);
    entry(SILVER_CAVE_ROOM_1, 1, SilverCaveRoom1Protein);
    entry(SILVER_CAVE_ROOM_1, 2, SilverCaveRoom1EscapeRope);
    entry(SILVER_CAVE_ROOM_1, 3, SilverCaveRoom1UltraBall);

    entry(SILVER_CAVE_ROOM_2, 0, SilverCaveRoom2Calcium);
    entry(SILVER_CAVE_ROOM_2, 1, SilverCaveRoom2UltraBall);
    entry(SILVER_CAVE_ROOM_2, 2, SilverCaveRoom2PPUp);

    entry(SILVER_CAVE_ROOM_3, 0, Red);
    
    entry(FAST_SHIP_1F, 0, FastShip1FSailor1Script);
    entry(FAST_SHIP_1F, 1, FastShip1FSailor2Script);
    entry(FAST_SHIP_1F, 2, FastShip1FSailor3Script);
    entry(FAST_SHIP_1F, 3, ObjectEvent);

    entry(FAST_SHIP_B1F, 0, FastShipB1FSailorScript);
    entry(FAST_SHIP_B1F, 1, FastShipB1FSailorScript);
    entry(FAST_SHIP_B1F, 2, TrainerSailorJeff);
    entry(FAST_SHIP_B1F, 3, TrainerPicnickerDebra);
    entry(FAST_SHIP_B1F, 4, TrainerJugglerFritz);
    entry(FAST_SHIP_B1F, 5, TrainerSailorGarrett);
    entry(FAST_SHIP_B1F, 6, TrainerFisherJonah);
    entry(FAST_SHIP_B1F, 7, TrainerBlackbeltWai);
    entry(FAST_SHIP_B1F, 8, TrainerSailorKenneth);
    entry(FAST_SHIP_B1F, 9, TrainerTeacherShirley);
    entry(FAST_SHIP_B1F, 10, TrainerSchoolboyNate);
    entry(FAST_SHIP_B1F, 11, TrainerSchoolboyRicky);

    entry(FAST_SHIP_CABINS_NNW_NNE_NE, 0, TrainerCooltrainermSean);
    entry(FAST_SHIP_CABINS_NNW_NNE_NE, 1, TrainerCooltrainerfCarol);
    entry(FAST_SHIP_CABINS_NNW_NNE_NE, 2, TrainerPokemaniacEthan);
    entry(FAST_SHIP_CABINS_NNW_NNE_NE, 3, TrainerHikerNoland);
    entry(FAST_SHIP_CABINS_NNW_NNE_NE, 4, FastShipLazySailorScript);
    entry(FAST_SHIP_CABINS_NNW_NNE_NE, 5, TrainerGentlemanEdward);
    entry(FAST_SHIP_CABINS_NNW_NNE_NE, 6, TrainerBurglarCorey);

    entry(FAST_SHIP_CABINS_SE_SSE_CAPTAINS_CABIN, 0, SSAquaCaptain);
    entry(FAST_SHIP_CABINS_SE_SSE_CAPTAINS_CABIN, 1, SSAquaGrandpa);
    entry(FAST_SHIP_CABINS_SE_SSE_CAPTAINS_CABIN, 2, SSAquaGranddaughterAfter);
    entry(FAST_SHIP_CABINS_SE_SSE_CAPTAINS_CABIN, 3, SSAquaGranddaughterBefore);
    entry(FAST_SHIP_CABINS_SE_SSE_CAPTAINS_CABIN, 4, TrainerPokefanmColin);
    entry(FAST_SHIP_CABINS_SE_SSE_CAPTAINS_CABIN, 5, TrainerTwinsMegandpeg1);
    entry(FAST_SHIP_CABINS_SE_SSE_CAPTAINS_CABIN, 6, TrainerTwinsMegandpeg2);
    entry(FAST_SHIP_CABINS_SE_SSE_CAPTAINS_CABIN, 7, TrainerPsychicRodney);
    entry(FAST_SHIP_CABINS_SE_SSE_CAPTAINS_CABIN, 8, TrainerPokefanmJeremy);
    entry(FAST_SHIP_CABINS_SE_SSE_CAPTAINS_CABIN, 9, TrainerPokefanfGeorgia);
    entry(FAST_SHIP_CABINS_SE_SSE_CAPTAINS_CABIN, 10, TrainerSupernerdShawn);

    entry(FAST_SHIP_CABINS_SW_SSW_NW, 0, TrainerFirebreatherLyle);
    entry(FAST_SHIP_CABINS_SW_SSW_NW, 1, TrainerBugCatcherKen);
    entry(FAST_SHIP_CABINS_SW_SSW_NW, 2, TrainerBeautyCassie);
    entry(FAST_SHIP_CABINS_SW_SSW_NW, 3, TrainerGuitaristClyde);

    entry(VERMILION_PORT, 0, VermilionPortSailorAtGangwayScript);
    entry(VERMILION_PORT, 1, VermilionPortSailorScript);
    entry(VERMILION_PORT, 2, VermilionPortSuperNerdScript);

    entry(VERMILION_PORT_PASSAGE, 0, VermilionPortPassageTeacherScript);
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