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