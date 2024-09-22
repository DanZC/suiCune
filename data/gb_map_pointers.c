#include "../constants.h"
#include <string.h>
#include <assert.h>
#include "maps/attributes.h"
#include "../home/map.h"
#include "../input_system/uthash.h"

// This is needed to keep compatability with OG Crystal, since Crystal expects map data pointers to be preloaded with a save file.

struct MapGBPtr {
    int idx;
    uint32_t attr_ptr;
    uint32_t blocks_ptr;
    uint32_t scripts_ptr;
    uint32_t events_ptr;
    UT_hash_handle hh;
};
struct MapGBPtr *gb_map_table = NULL;

#define _idx(_group, _map) ((_group << 8) | _map)
#define entry(_map, _name) add_entry(GROUP_##_map, MAP_##_map, a##_name##_MapAttributes, a##_name##_Blocks, a##_name##_MapScripts, a##_name##_MapEvents)

static void add_entry(uint8_t group, uint8_t map, uint32_t attr_ptr, uint32_t blocks_ptr, uint32_t scripts_ptr, uint32_t events_ptr) {
    struct MapGBPtr* item = malloc(sizeof(*item));
    item->idx = _idx(group, map);
    item->attr_ptr = attr_ptr;
    item->blocks_ptr = blocks_ptr;
    item->scripts_ptr = scripts_ptr;
    item->events_ptr = events_ptr;
    HASH_ADD_INT(gb_map_table,idx, item);
}

void PopulateMapPointerTable(void) {
    entry(NEW_BARK_TOWN, NewBarkTown);
    entry(CHERRYGROVE_CITY, CherrygroveCity);
    entry(VIOLET_CITY, VioletCity);
    entry(AZALEA_TOWN, AzaleaTown);
    entry(CIANWOOD_CITY, CianwoodCity);
    entry(GOLDENROD_CITY, GoldenrodCity);
    entry(OLIVINE_CITY, OlivineCity);
    entry(ECRUTEAK_CITY, EcruteakCity);
    entry(MAHOGANY_TOWN, MahoganyTown);
    entry(LAKE_OF_RAGE, LakeOfRage);
    entry(BLACKTHORN_CITY, BlackthornCity);
    entry(SILVER_CAVE_OUTSIDE, SilverCaveOutside);
    entry(ROUTE_26, Route26);
    entry(ROUTE_27, Route27);
    entry(ROUTE_28, Route28);
    entry(ROUTE_29, Route29);
    entry(ROUTE_30, Route30);
    entry(ROUTE_31, Route31);
    entry(ROUTE_32, Route32);
    entry(ROUTE_33, Route33);
    entry(ROUTE_34, Route34);
    entry(ROUTE_35, Route35);
    entry(ROUTE_36, Route36);
    entry(ROUTE_37, Route37);
    entry(ROUTE_38, Route38);
    entry(ROUTE_39, Route39);
    entry(ROUTE_40, Route40);
    entry(ROUTE_41, Route41);
    entry(ROUTE_42, Route42);
    entry(ROUTE_43, Route43);
    entry(ROUTE_44, Route44);
    entry(ROUTE_45, Route45);
    entry(ROUTE_46, Route46);
    entry(PEWTER_CITY, PewterCity);
    entry(ROUTE_2, Route2);
    entry(VIRIDIAN_CITY, ViridianCity);
    entry(ROUTE_22, Route22);
    entry(ROUTE_1, Route1);
    entry(PALLET_TOWN, PalletTown);
    entry(ROUTE_21, Route21);
    entry(CINNABAR_ISLAND, CinnabarIsland);
    entry(ROUTE_20, Route20);
    entry(ROUTE_19, Route19);
    entry(FUCHSIA_CITY, FuchsiaCity);
    entry(ROUTE_18, Route18);
    entry(ROUTE_17, Route17);
    entry(ROUTE_16, Route16);
    entry(CELADON_CITY, CeladonCity);
    entry(ROUTE_7, Route7);
    entry(ROUTE_15, Route15);
    entry(ROUTE_14, Route14);
    entry(ROUTE_13, Route13);
    entry(ROUTE_12, Route12);
    entry(ROUTE_11, Route11);
    entry(LAVENDER_TOWN, LavenderTown);
    entry(VERMILION_CITY, VermilionCity);
    entry(ROUTE_6, Route6);
    entry(SAFFRON_CITY, SaffronCity);
    entry(ROUTE_5, Route5);
    entry(CERULEAN_CITY, CeruleanCity);
    entry(ROUTE_9, Route9);
    entry(ROUTE_24, Route24);
    entry(ROUTE_25, Route25);
    entry(ROUTE_3, Route3);
    entry(ROUTE_4, Route4);
    entry(ROUTE_8, Route8);
    entry(ROUTE_10_NORTH, Route10North);
    entry(ROUTE_10_SOUTH, Route10South);
    entry(ROUTE_23, Route23);
    entry(SPROUT_TOWER_1F, SproutTower1F);
    entry(SPROUT_TOWER_2F, SproutTower2F);
    entry(SPROUT_TOWER_3F, SproutTower3F);
    entry(TIN_TOWER_1F, TinTower1F);
    entry(TIN_TOWER_2F, TinTower2F);
    entry(TIN_TOWER_3F, TinTower3F);
    entry(TIN_TOWER_4F, TinTower4F);
    entry(TIN_TOWER_5F, TinTower5F);
    entry(TIN_TOWER_6F, TinTower6F);
    entry(TIN_TOWER_7F, TinTower7F);
    entry(TIN_TOWER_8F, TinTower8F);
    entry(TIN_TOWER_9F, TinTower9F);
    entry(BURNED_TOWER_1F, BurnedTower1F);
    entry(BURNED_TOWER_B1F, BurnedTowerB1F);
    entry(NATIONAL_PARK, NationalPark);
    entry(NATIONAL_PARK_BUG_CONTEST, NationalParkBugContest);
    entry(RADIO_TOWER_1F, RadioTower1F);
    entry(RADIO_TOWER_2F, RadioTower2F);
    entry(RADIO_TOWER_3F, RadioTower3F);
    entry(RADIO_TOWER_4F, RadioTower4F);
    entry(RADIO_TOWER_5F, RadioTower5F);
    entry(RUINS_OF_ALPH_OUTSIDE, RuinsOfAlphOutside);
    entry(RUINS_OF_ALPH_HO_OH_CHAMBER, RuinsOfAlphHoOhChamber);
    entry(RUINS_OF_ALPH_KABUTO_CHAMBER, RuinsOfAlphKabutoChamber);
    entry(RUINS_OF_ALPH_OMANYTE_CHAMBER, RuinsOfAlphOmanyteChamber);
    entry(RUINS_OF_ALPH_AERODACTYL_CHAMBER, RuinsOfAlphAerodactylChamber);
    entry(RUINS_OF_ALPH_INNER_CHAMBER, RuinsOfAlphInnerChamber);
    entry(RUINS_OF_ALPH_RESEARCH_CENTER, RuinsOfAlphResearchCenter);
    entry(RUINS_OF_ALPH_HO_OH_ITEM_ROOM, RuinsOfAlphHoOhItemRoom);
    entry(RUINS_OF_ALPH_KABUTO_ITEM_ROOM, RuinsOfAlphKabutoItemRoom);
    entry(RUINS_OF_ALPH_OMANYTE_ITEM_ROOM, RuinsOfAlphOmanyteItemRoom);
    entry(RUINS_OF_ALPH_AERODACTYL_ITEM_ROOM, RuinsOfAlphAerodactylItemRoom);
    entry(RUINS_OF_ALPH_HO_OH_WORD_ROOM, RuinsOfAlphHoOhWordRoom);
    entry(RUINS_OF_ALPH_KABUTO_WORD_ROOM, RuinsOfAlphKabutoWordRoom);
    entry(RUINS_OF_ALPH_OMANYTE_WORD_ROOM, RuinsOfAlphOmanyteWordRoom);
    entry(RUINS_OF_ALPH_AERODACTYL_WORD_ROOM, RuinsOfAlphAerodactylWordRoom);
    entry(UNION_CAVE_1F, UnionCave1F);
    entry(UNION_CAVE_B1F, UnionCaveB1F);
    entry(UNION_CAVE_B2F, UnionCaveB2F);
    entry(SLOWPOKE_WELL_B1F, SlowpokeWellB1F);
    entry(SLOWPOKE_WELL_B2F, SlowpokeWellB2F);
    entry(OLIVINE_LIGHTHOUSE_1F, OlivineLighthouse1F);
    entry(OLIVINE_LIGHTHOUSE_2F, OlivineLighthouse2F);
    entry(OLIVINE_LIGHTHOUSE_3F, OlivineLighthouse3F);
    entry(OLIVINE_LIGHTHOUSE_4F, OlivineLighthouse4F);
    entry(OLIVINE_LIGHTHOUSE_5F, OlivineLighthouse5F);
    entry(OLIVINE_LIGHTHOUSE_6F, OlivineLighthouse6F);
    entry(MAHOGANY_MART_1F, MahoganyMart1F);
    entry(TEAM_ROCKET_BASE_B1F, TeamRocketBaseB1F);
    entry(TEAM_ROCKET_BASE_B2F, TeamRocketBaseB2F);
    entry(TEAM_ROCKET_BASE_B3F, TeamRocketBaseB3F);
    entry(ILEX_FOREST, IlexForest);
    entry(GOLDENROD_UNDERGROUND, GoldenrodUnderground);
    entry(GOLDENROD_UNDERGROUND_SWITCH_ROOM_ENTRANCES, GoldenrodUndergroundSwitchRoomEntrances);
    entry(GOLDENROD_DEPT_STORE_B1F, GoldenrodDeptStoreB1F);
    entry(GOLDENROD_UNDERGROUND_WAREHOUSE, GoldenrodUndergroundWarehouse);
    entry(MOUNT_MORTAR_1F_OUTSIDE, MountMortar1FOutside);
    entry(MOUNT_MORTAR_1F_INSIDE, MountMortar1FInside);
    entry(MOUNT_MORTAR_2F_INSIDE, MountMortar2FInside);
    entry(MOUNT_MORTAR_B1F, MountMortarB1F);
    entry(ICE_PATH_1F, IcePath1F);
    entry(ICE_PATH_B1F, IcePathB1F);
    entry(ICE_PATH_B2F_MAHOGANY_SIDE, IcePathB2FMahoganySide);
    entry(ICE_PATH_B2F_BLACKTHORN_SIDE, IcePathB2FBlackthornSide);
    entry(ICE_PATH_B3F, IcePathB3F);
    entry(WHIRL_ISLAND_NW, WhirlIslandNW);
    entry(WHIRL_ISLAND_NE, WhirlIslandNE);
    entry(WHIRL_ISLAND_SW, WhirlIslandSW);
    entry(WHIRL_ISLAND_CAVE, WhirlIslandCave);
    entry(WHIRL_ISLAND_SE, WhirlIslandSE);
    entry(WHIRL_ISLAND_B1F, WhirlIslandB1F);
    entry(WHIRL_ISLAND_B2F, WhirlIslandB2F);
    entry(WHIRL_ISLAND_LUGIA_CHAMBER, WhirlIslandLugiaChamber);
    entry(SILVER_CAVE_ROOM_1, SilverCaveRoom1);
    entry(SILVER_CAVE_ROOM_2, SilverCaveRoom2);
    entry(SILVER_CAVE_ROOM_3, SilverCaveRoom3);
    entry(SILVER_CAVE_ITEM_ROOMS, SilverCaveItemRooms);
    entry(DARK_CAVE_VIOLET_ENTRANCE, DarkCaveVioletEntrance);
    entry(DARK_CAVE_BLACKTHORN_ENTRANCE, DarkCaveBlackthornEntrance);
    entry(DRAGONS_DEN_1F, DragonsDen1F);
    entry(DRAGONS_DEN_B1F, DragonsDenB1F);
    entry(DRAGON_SHRINE, DragonShrine);
    entry(TOHJO_FALLS, TohjoFalls);
    entry(OLIVINE_POKECENTER_1F, OlivinePokecenter1F);
    entry(OLIVINE_GYM, OlivineGym);
    entry(OLIVINE_TIMS_HOUSE, OlivineTimsHouse);
    // entry(OLIVINE_HOUSE_BETA, OlivineHouseBeta);
    entry(OLIVINE_PUNISHMENT_SPEECH_HOUSE, OlivinePunishmentSpeechHouse);
    entry(OLIVINE_GOOD_ROD_HOUSE, OlivineGoodRodHouse);
    entry(OLIVINE_CAFE, OlivineCafe);
    entry(OLIVINE_MART, OlivineMart);
    entry(ROUTE_38_ECRUTEAK_GATE, Route38EcruteakGate);
    entry(ROUTE_39_BARN, Route39Barn);
    entry(ROUTE_39_FARMHOUSE, Route39Farmhouse);
    entry(MAHOGANY_RED_GYARADOS_SPEECH_HOUSE, MahoganyRedGyaradosSpeechHouse);
    entry(MAHOGANY_GYM, MahoganyGym);
    entry(MAHOGANY_POKECENTER_1F, MahoganyPokecenter1F);
    entry(ROUTE_42_ECRUTEAK_GATE, Route42EcruteakGate);
    entry(DIGLETTS_CAVE, DiglettsCave);
    entry(MOUNT_MOON, MountMoon);
    entry(UNDERGROUND_PATH, UndergroundPath);
    entry(ROCK_TUNNEL_1F, RockTunnel1F);
    entry(ROCK_TUNNEL_B1F, RockTunnelB1F);
    // entry(SAFARI_ZONE_FUCHSIA_GATE_BETA, SafariZoneFuchsiaGateBeta);
    // entry(SAFARI_ZONE_BETA, SafariZoneBeta);
    entry(VICTORY_ROAD, VictoryRoad);
    entry(ECRUTEAK_TIN_TOWER_ENTRANCE, EcruteakTinTowerEntrance);
    entry(WISE_TRIOS_ROOM, WiseTriosRoom);
    entry(ECRUTEAK_POKECENTER_1F, EcruteakPokecenter1F);
    entry(ECRUTEAK_LUGIA_SPEECH_HOUSE, EcruteakLugiaSpeechHouse);
    entry(DANCE_THEATRE, DanceTheatre);
    entry(ECRUTEAK_MART, EcruteakMart);
    entry(ECRUTEAK_GYM, EcruteakGym);
    entry(ECRUTEAK_ITEMFINDER_HOUSE, EcruteakItemfinderHouse);
    entry(BLACKTHORN_GYM_1F, BlackthornGym1F);
    entry(BLACKTHORN_GYM_2F, BlackthornGym2F);
    entry(BLACKTHORN_DRAGON_SPEECH_HOUSE, BlackthornDragonSpeechHouse);
    entry(BLACKTHORN_EMYS_HOUSE, BlackthornEmysHouse);
    entry(BLACKTHORN_MART, BlackthornMart);
    entry(BLACKTHORN_POKECENTER_1F, BlackthornPokecenter1F);
    entry(MOVE_DELETERS_HOUSE, MoveDeletersHouse);
    entry(CINNABAR_POKECENTER_1F, CinnabarPokecenter1F);
    // entry(CINNABAR_POKECENTER_2F_BETA, CinnabarPokecenter2FBeta);
    entry(ROUTE_19_FUCHSIA_GATE, Route19FuchsiaGate);
    entry(SEAFOAM_GYM, SeafoamGym);
    entry(CERULEAN_GYM_BADGE_SPEECH_HOUSE, CeruleanGymBadgeSpeechHouse);
    entry(CERULEAN_POLICE_STATION, CeruleanPoliceStation);
    entry(CERULEAN_TRADE_SPEECH_HOUSE, CeruleanTradeSpeechHouse);
    entry(CERULEAN_POKECENTER_1F, CeruleanPokecenter1F);
    // entry(CERULEAN_POKECENTER_2F_BETA, CeruleanPokecenter2FBeta);
    entry(CERULEAN_GYM, CeruleanGym);
    entry(CERULEAN_MART, CeruleanMart);
    entry(ROUTE_10_POKECENTER_1F, Route10Pokecenter1F);
    // entry(ROUTE_10_POKECENTER_2F_BETA, Route10Pokecenter2FBeta);
    entry(POWER_PLANT, PowerPlant);
    entry(BILLS_HOUSE, BillsHouse);
    entry(AZALEA_POKECENTER_1F, AzaleaPokecenter1F);
    entry(CHARCOAL_KILN, CharcoalKiln);
    entry(AZALEA_MART, AzaleaMart);
    entry(KURTS_HOUSE, KurtsHouse);
    entry(AZALEA_GYM, AzaleaGym);
    entry(LAKE_OF_RAGE_HIDDEN_POWER_HOUSE, LakeOfRageHiddenPowerHouse);
    entry(LAKE_OF_RAGE_MAGIKARP_HOUSE, LakeOfRageMagikarpHouse);
    entry(ROUTE_43_MAHOGANY_GATE, Route43MahoganyGate);
    entry(ROUTE_43_GATE, Route43Gate);
    entry(VIOLET_MART, VioletMart);
    entry(VIOLET_GYM, VioletGym);
    entry(EARLS_POKEMON_ACADEMY, EarlsPokemonAcademy);
    entry(VIOLET_NICKNAME_SPEECH_HOUSE, VioletNicknameSpeechHouse);
    entry(VIOLET_POKECENTER_1F, VioletPokecenter1F);
    entry(VIOLET_KYLES_HOUSE, VioletKylesHouse);
    entry(ROUTE_32_RUINS_OF_ALPH_GATE, Route32RuinsOfAlphGate);
    entry(ROUTE_32_POKECENTER_1F, Route32Pokecenter1F);
    entry(ROUTE_35_GOLDENROD_GATE, Route35GoldenrodGate);
    entry(ROUTE_35_NATIONAL_PARK_GATE, Route35NationalParkGate);
    entry(ROUTE_36_RUINS_OF_ALPH_GATE, Route36RuinsOfAlphGate);
    entry(ROUTE_36_NATIONAL_PARK_GATE, Route36NationalParkGate);
    entry(GOLDENROD_GYM, GoldenrodGym);
    entry(GOLDENROD_BIKE_SHOP, GoldenrodBikeShop);
    entry(GOLDENROD_HAPPINESS_RATER, GoldenrodHappinessRater);
    entry(BILLS_FAMILYS_HOUSE, BillsFamilysHouse);
    entry(GOLDENROD_MAGNET_TRAIN_STATION, GoldenrodMagnetTrainStation);
    entry(GOLDENROD_FLOWER_SHOP, GoldenrodFlowerShop);
    entry(GOLDENROD_PP_SPEECH_HOUSE, GoldenrodPPSpeechHouse);
    entry(GOLDENROD_NAME_RATER, GoldenrodNameRater);
    entry(GOLDENROD_DEPT_STORE_1F, GoldenrodDeptStore1F);
    entry(GOLDENROD_DEPT_STORE_2F, GoldenrodDeptStore2F);
    entry(GOLDENROD_DEPT_STORE_3F, GoldenrodDeptStore3F);
    entry(GOLDENROD_DEPT_STORE_4F, GoldenrodDeptStore4F);
    entry(GOLDENROD_DEPT_STORE_5F, GoldenrodDeptStore5F);
    entry(GOLDENROD_DEPT_STORE_6F, GoldenrodDeptStore6F);
    entry(GOLDENROD_DEPT_STORE_ELEVATOR, GoldenrodDeptStoreElevator);
    entry(GOLDENROD_DEPT_STORE_ROOF, GoldenrodDeptStoreRoof);
    entry(GOLDENROD_GAME_CORNER, GoldenrodGameCorner);
    entry(GOLDENROD_POKECENTER_1F, GoldenrodPokecenter1F);
    // entry(GOLDENROD_POKECENTER_1F, PokecomCenter);
    entry(POKECOM_CENTER_ADMIN_OFFICE_MOBILE, PokecomCenterAdminOfficeMobile);
    entry(ILEX_FOREST_AZALEA_GATE, IlexForestAzaleaGate);
    entry(ROUTE_34_ILEX_FOREST_GATE, Route34IlexForestGate);
    entry(DAY_CARE, DayCare);
    entry(VERMILION_FISHING_SPEECH_HOUSE, VermilionFishingSpeechHouse);
    entry(VERMILION_POKECENTER_1F, VermilionPokecenter1F);
    // entry(VERMILION_POKECENTER_2F_BETA, VermilionPokecenter2FBeta);
    entry(POKEMON_FAN_CLUB, PokemonFanClub);
    entry(VERMILION_MAGNET_TRAIN_SPEECH_HOUSE, VermilionMagnetTrainSpeechHouse);
    entry(VERMILION_MART, VermilionMart);
    entry(VERMILION_DIGLETTS_CAVE_SPEECH_HOUSE, VermilionDiglettsCaveSpeechHouse);
    entry(VERMILION_GYM, VermilionGym);
    entry(ROUTE_6_SAFFRON_GATE, Route6SaffronGate);
    entry(ROUTE_6_UNDERGROUND_PATH_ENTRANCE, Route6UndergroundPathEntrance);
    entry(REDS_HOUSE_1F, RedsHouse1F);
    entry(REDS_HOUSE_2F, RedsHouse2F);
    entry(BLUES_HOUSE, BluesHouse);
    entry(OAKS_LAB, OaksLab);
    entry(PEWTER_NIDORAN_SPEECH_HOUSE, PewterNidoranSpeechHouse);
    entry(PEWTER_GYM, PewterGym);
    entry(PEWTER_MART, PewterMart);
    entry(PEWTER_POKECENTER_1F, PewterPokecenter1F);
    // entry(PEWTER_POKECENTER_2F_BETA, PewterPokecenter2FBeta);
    entry(PEWTER_SNOOZE_SPEECH_HOUSE, PewterSnoozeSpeechHouse);
    entry(OLIVINE_PORT, OlivinePort);
    entry(VERMILION_PORT, VermilionPort);
    entry(FAST_SHIP_1F, FastShip1F);
    entry(FAST_SHIP_CABINS_NNW_NNE_NE, FastShipCabins_NNW_NNE_NE);
    entry(FAST_SHIP_CABINS_SW_SSW_NW, FastShipCabins_SW_SSW_NW);
    entry(FAST_SHIP_CABINS_SE_SSE_CAPTAINS_CABIN, FastShipCabins_SE_SSE_CaptainsCabin);
    entry(FAST_SHIP_B1F, FastShipB1F);
    entry(OLIVINE_PORT_PASSAGE, OlivinePortPassage);
    entry(VERMILION_PORT_PASSAGE, VermilionPortPassage);
    entry(MOUNT_MOON_SQUARE, MountMoonSquare);
    entry(MOUNT_MOON_GIFT_SHOP, MountMoonGiftShop);
    entry(TIN_TOWER_ROOF, TinTowerRoof);
    entry(INDIGO_PLATEAU_POKECENTER_1F, IndigoPlateauPokecenter1F);
    entry(WILLS_ROOM, WillsRoom);
    entry(KOGAS_ROOM, KogasRoom);
    entry(BRUNOS_ROOM, BrunosRoom);
    entry(KARENS_ROOM, KarensRoom);
    entry(LANCES_ROOM, LancesRoom);
    entry(HALL_OF_FAME, HallOfFame);
    entry(FUCHSIA_MART, FuchsiaMart);
    entry(SAFARI_ZONE_MAIN_OFFICE, SafariZoneMainOffice);
    entry(FUCHSIA_GYM, FuchsiaGym);
    entry(BILLS_BROTHERS_HOUSE, BillsBrothersHouse);
    entry(FUCHSIA_POKECENTER_1F, FuchsiaPokecenter1F);
    // entry(FUCHSIA_POKECENTER_2F_BETA, FuchsiaPokecenter2FBeta);
    entry(SAFARI_ZONE_WARDENS_HOME, SafariZoneWardensHome);
    entry(ROUTE_15_FUCHSIA_GATE, Route15FuchsiaGate);
    entry(LAVENDER_POKECENTER_1F, LavenderPokecenter1F);
    // entry(LAVENDER_POKECENTER_2F_BETA, LavenderPokecenter2FBeta);
    entry(MR_FUJIS_HOUSE, MrFujisHouse);
    entry(LAVENDER_SPEECH_HOUSE, LavenderSpeechHouse);
    entry(LAVENDER_NAME_RATER, LavenderNameRater);
    entry(LAVENDER_MART, LavenderMart);
    entry(SOUL_HOUSE, SoulHouse);
    entry(LAV_RADIO_TOWER_1F, LavRadioTower1F);
    entry(ROUTE_8_SAFFRON_GATE, Route8SaffronGate);
    entry(ROUTE_12_SUPER_ROD_HOUSE, Route12SuperRodHouse);
    entry(SILVER_CAVE_POKECENTER_1F, SilverCavePokecenter1F);
    entry(ROUTE_28_STEEL_WING_HOUSE, Route28SteelWingHouse);
    entry(POKECENTER_2F, Pokecenter2F);
    entry(TRADE_CENTER, TradeCenter);
    entry(COLOSSEUM, Colosseum);
    // entry(TIME_CAPSULE, TimeCapsule);
    entry(MOBILE_TRADE_ROOM, MobileTradeRoom);
    entry(MOBILE_BATTLE_ROOM, MobileBattleRoom);
    entry(CELADON_DEPT_STORE_1F, CeladonDeptStore1F);
    entry(CELADON_DEPT_STORE_2F, CeladonDeptStore2F);
    entry(CELADON_DEPT_STORE_3F, CeladonDeptStore3F);
    entry(CELADON_DEPT_STORE_4F, CeladonDeptStore4F);
    entry(CELADON_DEPT_STORE_5F, CeladonDeptStore5F);
    entry(CELADON_DEPT_STORE_6F, CeladonDeptStore6F);
    entry(CELADON_DEPT_STORE_ELEVATOR, CeladonDeptStoreElevator);
    entry(CELADON_MANSION_1F, CeladonMansion1F);
    entry(CELADON_MANSION_2F, CeladonMansion2F);
    entry(CELADON_MANSION_3F, CeladonMansion3F);
    entry(CELADON_MANSION_ROOF, CeladonMansionRoof);
    entry(CELADON_MANSION_ROOF_HOUSE, CeladonMansionRoofHouse);
    entry(CELADON_POKECENTER_1F, CeladonPokecenter1F);
    // entry(CELADON_POKECENTER_2F_BETA, CeladonPokecenter2FBeta);
    entry(CELADON_GAME_CORNER, CeladonGameCorner);
    entry(CELADON_GAME_CORNER_PRIZE_ROOM, CeladonGameCornerPrizeRoom);
    entry(CELADON_GYM, CeladonGym);
    entry(CELADON_CAFE, CeladonCafe);
    entry(ROUTE_16_FUCHSIA_SPEECH_HOUSE, Route16FuchsiaSpeechHouse);
    entry(ROUTE_16_GATE, Route16Gate);
    entry(ROUTE_7_SAFFRON_GATE, Route7SaffronGate);
    entry(ROUTE_17_ROUTE_18_GATE, Route17Route18Gate);
    entry(MANIAS_HOUSE, ManiasHouse);
    entry(CIANWOOD_GYM, CianwoodGym);
    entry(CIANWOOD_POKECENTER_1F, CianwoodPokecenter1F);
    entry(CIANWOOD_PHARMACY, CianwoodPharmacy);
    entry(CIANWOOD_PHOTO_STUDIO, CianwoodPhotoStudio);
    entry(CIANWOOD_LUGIA_SPEECH_HOUSE, CianwoodLugiaSpeechHouse);
    entry(POKE_SEERS_HOUSE, PokeSeersHouse);
    entry(BATTLE_TOWER_1F, BattleTower1F);
    entry(BATTLE_TOWER_BATTLE_ROOM, BattleTowerBattleRoom);
    entry(BATTLE_TOWER_ELEVATOR, BattleTowerElevator);
    entry(BATTLE_TOWER_HALLWAY, BattleTowerHallway);
    entry(ROUTE_40_BATTLE_TOWER_GATE, Route40BattleTowerGate);
    entry(BATTLE_TOWER_OUTSIDE, BattleTowerOutside);
    entry(VIRIDIAN_GYM, ViridianGym);
    entry(VIRIDIAN_NICKNAME_SPEECH_HOUSE, ViridianNicknameSpeechHouse);
    entry(TRAINER_HOUSE_1F, TrainerHouse1F);
    entry(TRAINER_HOUSE_B1F, TrainerHouseB1F);
    entry(VIRIDIAN_MART, ViridianMart);
    entry(VIRIDIAN_POKECENTER_1F, ViridianPokecenter1F);
    // entry(VIRIDIAN_POKECENTER_2F_BETA, ViridianPokecenter2FBeta);
    entry(ROUTE_2_NUGGET_HOUSE, Route2NuggetHouse);
    entry(ROUTE_2_GATE, Route2Gate);
    entry(VICTORY_ROAD_GATE, VictoryRoadGate);
    entry(ELMS_LAB, ElmsLab);
    entry(PLAYERS_HOUSE_1F, PlayersHouse1F);
    entry(PLAYERS_HOUSE_2F, PlayersHouse2F);
    entry(PLAYERS_NEIGHBORS_HOUSE, PlayersNeighborsHouse);
    entry(ELMS_HOUSE, ElmsHouse);
    entry(ROUTE_26_HEAL_HOUSE, Route26HealHouse);
    entry(DAY_OF_WEEK_SIBLINGS_HOUSE, DayOfWeekSiblingsHouse);
    entry(ROUTE_27_SANDSTORM_HOUSE, Route27SandstormHouse);
    entry(ROUTE_29_ROUTE_46_GATE, Route29Route46Gate);
    entry(FIGHTING_DOJO, FightingDojo);
    entry(SAFFRON_GYM, SaffronGym);
    entry(SAFFRON_MART, SaffronMart);
    entry(SAFFRON_POKECENTER_1F, SaffronPokecenter1F);
    // entry(SAFFRON_POKECENTER_2F_BETA, SaffronPokecenter2FBeta);
    entry(MR_PSYCHICS_HOUSE, MrPsychicsHouse);
    entry(SAFFRON_MAGNET_TRAIN_STATION, SaffronMagnetTrainStation);
    entry(SILPH_CO_1F, SilphCo1F);
    entry(COPYCATS_HOUSE_1F, CopycatsHouse1F);
    entry(COPYCATS_HOUSE_2F, CopycatsHouse2F);
    entry(ROUTE_5_UNDERGROUND_PATH_ENTRANCE, Route5UndergroundPathEntrance);
    entry(ROUTE_5_SAFFRON_GATE, Route5SaffronGate);
    entry(ROUTE_5_CLEANSE_TAG_HOUSE, Route5CleanseTagHouse);
    entry(CHERRYGROVE_MART, CherrygroveMart);
    entry(CHERRYGROVE_POKECENTER_1F, CherrygrovePokecenter1F);
    entry(CHERRYGROVE_GYM_SPEECH_HOUSE, CherrygroveGymSpeechHouse);
    entry(GUIDE_GENTS_HOUSE, GuideGentsHouse);
    entry(CHERRYGROVE_EVOLUTION_SPEECH_HOUSE, CherrygroveEvolutionSpeechHouse);
    entry(ROUTE_30_BERRY_HOUSE, Route30BerryHouse);
    entry(MR_POKEMONS_HOUSE, MrPokemonsHouse);
    entry(ROUTE_31_VIOLET_GATE, Route31VioletGate);
}

uint32_t GetGBMapAttributePointer(uint8_t group, uint8_t map) {
    struct MapGBPtr* out;
    int idx = _idx(group, map);
    HASH_FIND_INT(gb_map_table,&idx, out);
    if(out) {
        return out->attr_ptr;
    }
    return 0;
}

uint32_t GetGBMapBlocksPointer(uint8_t group, uint8_t map) {
    struct MapGBPtr* out;
    int idx = _idx(group, map);
    HASH_FIND_INT(gb_map_table,&idx, out);
    if(out) {
        return out->blocks_ptr;
    }
    return 0;
}

uint32_t GetGBMapScriptsPointer(uint8_t group, uint8_t map) {
    struct MapGBPtr* out;
    int idx = _idx(group, map);
    HASH_FIND_INT(gb_map_table,&idx, out);
    if(out) {
        return out->scripts_ptr;
    }
    return 0;
}

uint32_t GetGBMapEventsPointer(uint8_t group, uint8_t map) {
    struct MapGBPtr* out;
    int idx = _idx(group, map);
    HASH_FIND_INT(gb_map_table,&idx, out);
    if(out) {
        return out->events_ptr;
    }
    return 0;
}
