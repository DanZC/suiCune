#include "../../constants.h"
#include "blocks.h"
#include "scripts.h"

#define map_attributes(name, id, block, _connections) const struct MapAttr name##_MapAttributes = {\
    .width = id##_WIDTH, .height = id##_HEIGHT, .borderBlock = block, .blocksPath = name##_Blocks, \
    .events = &name##_MapEvents, .scripts = &name##_MapScripts, .connections={ _connections }}

#define calc_tile_src(_x) ((((_x) + 3) < 0)? -((_x) + 3): 0)
#define calc_tile_tgt(_x) ((((_x) + 3) < 0)? 0: ((_x) + 3))
#define calc_map_blk_n(_name, _x) ((_name##_WIDTH * (_name##_HEIGHT - 3)) + calc_tile_src(_x))
#define calc_map_blk_s(_name, _x) (calc_tile_src(_x))
#define calc_map_blk_w(_name, _x) ((_name##_WIDTH * calc_tile_src(_x)) + _name##_WIDTH - 3)
// _blk = (\3_WIDTH * _src)
#define calc_map_blk_e(_name, _x) (_name##_WIDTH * calc_tile_src(_x))
#define calc_map_map_n(_name, _x) (calc_tile_tgt(_x))
// _map = (CURRENT_MAP_WIDTH + 6) * (CURRENT_MAP_HEIGHT + 3) + _tgt
#define calc_map_map_s(_curr, _x) ((_curr##_WIDTH + 6) * (_curr##_HEIGHT + 3) + calc_tile_tgt(_x))
// _map = (CURRENT_MAP_WIDTH + 6) * _tgt
#define calc_map_map_w(_curr, _x) ((_curr##_WIDTH + 6) * calc_tile_tgt(_x))
// _map = (CURRENT_MAP_WIDTH + 6) * _tgt + CURRENT_MAP_WIDTH + 3
#define calc_map_map_e(_curr, _x) (((_curr##_WIDTH + 6) * calc_tile_tgt(_x)) + _curr##_WIDTH + 3)
#define calc_map_win_n(_name) ((_name##_WIDTH + 6) * _name##_HEIGHT + 1)
#define calc_map_win_s(_name) (_name##_WIDTH + 7)
#define calc_map_win_w(_name) ((_name##_WIDTH + 6) * 2 - 6)
#define calc_map_win_e(_name) (_name##_WIDTH + 7)
#define calc_map_y_n(_name, _x) (_name##_HEIGHT * 2 - 1)
#define calc_map_y_s(_name, _x) (0)
#define calc_map_y_h(_name, _x) ((_x) * -2)
#define calc_map_x_v(_name, _x) ((_x) * -2)
#define calc_map_x_w(_name, _x) (_name##_WIDTH * 2 - 1)
#define calc_map_x_e(_name, _x) (0)
#define calc_map_len_v(_curr, _name, _x) ((_curr##_WIDTH + 3 - (_x) > _name##_WIDTH)? _name##_WIDTH: _curr##_WIDTH + 3 - (_x))
#define calc_map_len_h(_curr, _name, _x) ((_curr##_HEIGHT + 3 - (_x) > _name##_HEIGHT)? _name##_HEIGHT: _curr##_HEIGHT + 3 - (_x))
#define connection_north(current, name, name2, x) [NORTH_F] = &(struct MapConnectionData){.connectedMapGroup=GROUP_##name2,\
    .connectedMapNumber=MAP_##name2, .connectionStripOffset= calc_map_blk_n(name2, x),\
    .connectionStripLocation = wram_ptr(wOverworldMapBlocks) + calc_map_map_n(name2, x), \
    .connectionStripLength = calc_map_len_v(current, name2, x) - calc_tile_src(x), \
    .connectedMapWidth = name2##_WIDTH, \
    .connectionStripYOffset = calc_map_y_n(name2, x), \
    .connectionStripXOffset = calc_map_x_v(name2, x), \
    .connectionWindow = wram_ptr(wOverworldMapBlocks) + calc_map_win_n(name2), \
    },
#define connection_south(current, name, name2, x) [SOUTH_F] = &(struct MapConnectionData){.connectedMapGroup=GROUP_##name2,\
    .connectedMapNumber=MAP_##name2, .connectionStripOffset= calc_map_blk_s(name2, x),\
    .connectionStripLocation = wram_ptr(wOverworldMapBlocks) + calc_map_map_s(current, x), \
    .connectionStripLength = calc_map_len_v(current, name2, x) - calc_tile_src(x), \
    .connectedMapWidth = name2##_WIDTH, \
    .connectionStripYOffset = calc_map_y_s(name2, x), \
    .connectionStripXOffset = calc_map_x_v(name2, x), \
    .connectionWindow = wram_ptr(wOverworldMapBlocks) + calc_map_win_s(name2), \
    },
#define connection_west(current, name, name2, x) [WEST_F] = &(struct MapConnectionData){.connectedMapGroup=GROUP_##name2,\
    .connectedMapNumber=MAP_##name2, .connectionStripOffset=(calc_map_blk_w(name2, x)),\
    .connectionStripLocation = wram_ptr(wOverworldMapBlocks) + calc_map_map_w(current, x), \
    .connectionStripLength = calc_map_len_h(current, name2, x) - calc_tile_src(x), \
    .connectedMapWidth = name2##_WIDTH, \
    .connectionStripYOffset = calc_map_y_h(name2, x), \
    .connectionStripXOffset = calc_map_x_w(name2, x), \
    .connectionWindow = wram_ptr(wOverworldMapBlocks) + calc_map_win_w(name2), \
    },
#define connection_east(current, name, name2, x) [EAST_F] = &(struct MapConnectionData){.connectedMapGroup=GROUP_##name2,\
    .connectedMapNumber=MAP_##name2, .connectionStripOffset=(calc_map_blk_e(name2, x)),\
    .connectionStripLocation = wram_ptr(wOverworldMapBlocks) + calc_map_map_e(current, x), \
    .connectionStripLength = calc_map_len_h(current, name2, x) - calc_tile_src(x), \
    .connectedMapWidth = name2##_WIDTH, \
    .connectionStripYOffset = calc_map_y_h(name2, x), \
    .connectionStripXOffset = calc_map_x_e(name2, x), \
    .connectionWindow = wram_ptr(wOverworldMapBlocks) + calc_map_win_e(name2), \
    },

#define connection(current, dir, name, name2, x) connection_##dir (current, name, name2, x)

map_attributes(NewBarkTown, NEW_BARK_TOWN, 0x05,
    connection(NEW_BARK_TOWN, west, Route29, ROUTE_29, 0)
    connection(NEW_BARK_TOWN, east, Route27, ROUTE_27, 0));

map_attributes(CherrygroveCity, CHERRYGROVE_CITY, 0x35,
    connection(CHERRYGROVE_CITY, north, Route30, ROUTE_30, 5)
    connection(CHERRYGROVE_CITY, east, Route29, ROUTE_29, 0));

map_attributes(VioletCity, VIOLET_CITY, 0x05,
    connection(VIOLET_CITY, south, Route32, ROUTE_32, 0)
    connection(VIOLET_CITY, west, Route36, ROUTE_36, 0)
    connection(VIOLET_CITY, east, Route31, ROUTE_31, 9));

map_attributes(AzaleaTown, AZALEA_TOWN, 0x05,
    connection(AZALEA_TOWN, west, Route34, ROUTE_34, -18)
    connection(AZALEA_TOWN, east, Route33, ROUTE_33, 0));

map_attributes(CianwoodCity, CIANWOOD_CITY, 0x35,
    connection(CIANWOOD_CITY, east, Route41, ROUTE_41, 0));

map_attributes(GoldenrodCity, GOLDENROD_CITY, 0x35,
    connection(GOLDENROD_CITY, north, Route35, ROUTE_35, 5)
    connection(GOLDENROD_CITY, south, Route34, ROUTE_34, 5));

map_attributes(OlivineCity, OLIVINE_CITY, 0x35,
    connection(OLIVINE_CITY, north, Route39, ROUTE_39, 5)
    connection(OLIVINE_CITY, west, Route40, ROUTE_40, 9));

map_attributes(EcruteakCity, ECRUTEAK_CITY, 0x05,
    connection(ECRUTEAK_CITY, south, Route37, ROUTE_37, 5)
    connection(ECRUTEAK_CITY, west, Route38, ROUTE_38, 5)
    connection(ECRUTEAK_CITY, east, Route42, ROUTE_42, 9));

map_attributes(MahoganyTown, MAHOGANY_TOWN, 0x71,
    connection(MAHOGANY_TOWN, north, Route43, ROUTE_43, 0)
    connection(MAHOGANY_TOWN, west, Route42, ROUTE_42, 0)
    connection(MAHOGANY_TOWN, east, Route44, ROUTE_44, 0));

map_attributes(LakeOfRage, LAKE_OF_RAGE, 0x05,
    connection(LAKE_OF_RAGE, south, Route43, ROUTE_43, 5));

map_attributes(BlackthornCity, BLACKTHORN_CITY, 0x71,
    connection(BLACKTHORN_CITY, south, Route45, ROUTE_45, 0)
    connection(BLACKTHORN_CITY, west, Route44, ROUTE_44, 9));

map_attributes(SilverCaveOutside, SILVER_CAVE_OUTSIDE, 0x2c,
    connection(SILVER_CAVE_OUTSIDE, east, Route28, ROUTE_28, 9));

map_attributes(Route26, ROUTE_26, 0x05,
    connection(ROUTE_26, west, Route27, ROUTE_27, 45));

map_attributes(Route27, ROUTE_27, 0x35,
    connection(ROUTE_27, west, NewBarkTown, NEW_BARK_TOWN, 0)
    connection(ROUTE_27, east, Route26, ROUTE_26, -45));

map_attributes(Route28, ROUTE_28, 0x2c,
    connection(ROUTE_28, west, SilverCaveOutside, SILVER_CAVE_OUTSIDE, -9));

map_attributes(Route29, ROUTE_29, 0x05, 
    connection(ROUTE_29, north, Route46, ROUTE_46, 10)
    connection(ROUTE_29, west, CherrygroveCity, CHERRYGROVE_CITY, 0)
    connection(ROUTE_29, east, NewBarkTown, NEW_BARK_TOWN, 0));

map_attributes(Route30, ROUTE_30, 0x05, 
    connection(ROUTE_30, north, Route31, ROUTE_31, -10)
    connection(ROUTE_30, south, CherrygroveCity, CHERRYGROVE_CITY, -5));

map_attributes(Route31, ROUTE_31, 0x05,
    connection(ROUTE_31, south, Route30, ROUTE_30, 10)
    connection(ROUTE_31, west, VioletCity, VIOLET_CITY, -9));

map_attributes(Route32, ROUTE_32, 0x05,
    connection(ROUTE_32, north, VioletCity, VIOLET_CITY, 0)
    connection(ROUTE_32, south, Route33, ROUTE_33, 0));

map_attributes(Route33, ROUTE_33, 0x05,
    connection(ROUTE_33, north, Route32, ROUTE_32, 0)
    connection(ROUTE_33, west, AzaleaTown, AZALEA_TOWN, 0));

map_attributes(Route34, ROUTE_34, 0x05,
    connection(ROUTE_34, north, GoldenrodCity, GOLDENROD_CITY, -5)
    connection(ROUTE_34, east, AzaleaTown, AZALEA_TOWN, 18));

map_attributes(Route35, ROUTE_35, 0x05,
    connection(ROUTE_35, north, Route36, ROUTE_36, 0)
    connection(ROUTE_35, south, GoldenrodCity, GOLDENROD_CITY, -5));

map_attributes(Route36, ROUTE_36, 0x05,
    connection(ROUTE_36, north, Route37, ROUTE_37, 10)
    connection(ROUTE_36, south, Route35, ROUTE_35, 0)
    connection(ROUTE_36, east, VioletCity, VIOLET_CITY, 0));

map_attributes(Route37, ROUTE_37, 0x05,
    connection(ROUTE_37, north, EcruteakCity, ECRUTEAK_CITY, -5)
    connection(ROUTE_37, south, Route36, ROUTE_36, -10));

map_attributes(Route38, ROUTE_38, 0x05,
    connection(ROUTE_38, west, Route39, ROUTE_39, 0)
    connection(ROUTE_38, east, EcruteakCity, ECRUTEAK_CITY, -5));

map_attributes(Route39, ROUTE_39, 0x05,
    connection(ROUTE_39, south, OlivineCity, OLIVINE_CITY, -5)
    connection(ROUTE_39, east, Route38, ROUTE_38, 0));

map_attributes(Route40, ROUTE_40, 0x35,
    connection(ROUTE_40, south, Route41, ROUTE_41, -15)
    connection(ROUTE_40, east, OlivineCity, OLIVINE_CITY, -9));

map_attributes(Route41, ROUTE_41, 0x35,
    connection(ROUTE_41, north, Route40, ROUTE_40, 15)
    connection(ROUTE_41, west, CianwoodCity, CIANWOOD_CITY, 0));

map_attributes(Route42, ROUTE_42, 0x05,
    connection(ROUTE_42, west, EcruteakCity, ECRUTEAK_CITY, -9)
    connection(ROUTE_42, east, MahoganyTown, MAHOGANY_TOWN, 0));

map_attributes(Route43, ROUTE_43, 0x05,
    connection(ROUTE_43, north, LakeOfRage, LAKE_OF_RAGE, -5)
    connection(ROUTE_43, south, MahoganyTown, MAHOGANY_TOWN, 0));

map_attributes(Route44, ROUTE_44, 0x71,
    connection(ROUTE_44, west, MahoganyTown, MAHOGANY_TOWN, 0)
    connection(ROUTE_44, east, BlackthornCity, BLACKTHORN_CITY, -9));

map_attributes(Route45, ROUTE_45, 0x71,
    connection(ROUTE_45, north, BlackthornCity, BLACKTHORN_CITY, 0)
    connection(ROUTE_45, west, Route46, ROUTE_46, 36));

map_attributes(Route46, ROUTE_46, 0x05,
    connection(ROUTE_46, south, Route29, ROUTE_29, -10)
    connection(ROUTE_46, east, Route45, ROUTE_45, -36));

map_attributes(PewterCity, PEWTER_CITY, 0x0f,
    connection(PEWTER_CITY, south, Route2, ROUTE_2, 5)
    connection(PEWTER_CITY, east, Route3, ROUTE_3, 5));

map_attributes(Route2, ROUTE_2, 0x0f,
    connection(ROUTE_2, north, PewterCity, PEWTER_CITY, -5)
    connection(ROUTE_2, south, ViridianCity, VIRIDIAN_CITY, -5));

map_attributes(ViridianCity, VIRIDIAN_CITY, 0x0f,
    connection(VIRIDIAN_CITY, north, Route2, ROUTE_2, 5)
    connection(VIRIDIAN_CITY, south, Route1, ROUTE_1, 10)
    connection(VIRIDIAN_CITY, west, Route22, ROUTE_22, 4));

map_attributes(Route22, ROUTE_22, 0x2c,
    connection(ROUTE_22, east, ViridianCity, VIRIDIAN_CITY, -4));

map_attributes(Route1, ROUTE_1, 0x0f,
    connection(ROUTE_1, north, ViridianCity, VIRIDIAN_CITY, -10)
    connection(ROUTE_1, south, PalletTown, PALLET_TOWN, 0));

map_attributes(PalletTown, PALLET_TOWN, 0x0f,
    connection(PALLET_TOWN, north, Route1, ROUTE_1, 0)
    connection(PALLET_TOWN, south, Route21, ROUTE_21, 0));

map_attributes(Route21, ROUTE_21, 0x43,
    connection(ROUTE_21, north, PalletTown, PALLET_TOWN, 0)
    connection(ROUTE_21, south, CinnabarIsland, CINNABAR_ISLAND, 0));

map_attributes(CinnabarIsland, CINNABAR_ISLAND, 0x43,
    connection(CINNABAR_ISLAND, north, Route21, ROUTE_21, 0)
    connection(CINNABAR_ISLAND, east, Route20, ROUTE_20, 0));

map_attributes(Route20, ROUTE_20, 0x43,
    connection(ROUTE_20, west, CinnabarIsland, CINNABAR_ISLAND, 0)
    connection(ROUTE_20, east, Route19, ROUTE_19, -9));

map_attributes(Route19, ROUTE_19, 0x43,
    connection(ROUTE_19, north, FuchsiaCity, FUCHSIA_CITY, 0)
    connection(ROUTE_19, west, Route20, ROUTE_20, 9));

map_attributes(FuchsiaCity, FUCHSIA_CITY, 0x0f,
    connection(FUCHSIA_CITY, south, Route19, ROUTE_19, 0)
    connection(FUCHSIA_CITY, west, Route18, ROUTE_18, 7)
    connection(FUCHSIA_CITY, east, Route15, ROUTE_15, 9));

map_attributes(Route18, ROUTE_18, 0x43,
    connection(ROUTE_18, west, Route17, ROUTE_17, -38)
    connection(ROUTE_18, east, FuchsiaCity, FUCHSIA_CITY, -7));

map_attributes(Route17, ROUTE_17, 0x43,
    connection(ROUTE_17, north, Route16, ROUTE_16, 0)
    connection(ROUTE_17, east, Route18, ROUTE_18, 38));

map_attributes(Route16, ROUTE_16, 0x0f,
    connection(ROUTE_16, south, Route17, ROUTE_17, 0)
    connection(ROUTE_16, east, CeladonCity, CELADON_CITY, -9));

map_attributes(CeladonCity, CELADON_CITY, 0x0f,
    connection(CELADON_CITY, west, Route16, ROUTE_16, 9)
    connection(CELADON_CITY, east, Route7, ROUTE_7, 5));

map_attributes(Route7, ROUTE_7, 0x0f,
    connection(ROUTE_7, west, CeladonCity, CELADON_CITY, -5)
    connection(ROUTE_7, east, SaffronCity, SAFFRON_CITY, -9));

map_attributes(Route15, ROUTE_15, 0x0f,
    connection(ROUTE_15, west, FuchsiaCity, FUCHSIA_CITY, -9)
    connection(ROUTE_15, east, Route14, ROUTE_14, -9));

map_attributes(Route14, ROUTE_14, 0x43,
    connection(ROUTE_14, north, Route13, ROUTE_13, 0)
    connection(ROUTE_14, west, Route15, ROUTE_15, 9));

map_attributes(Route13, ROUTE_13, 0x43,
    connection(ROUTE_13, north, Route12, ROUTE_12, 20)
    connection(ROUTE_13, south, Route14, ROUTE_14, 0));

map_attributes(Route12, ROUTE_12, 0x43,
    connection(ROUTE_12, north, LavenderTown, LAVENDER_TOWN, 0)
    connection(ROUTE_12, south, Route13, ROUTE_13, -20)
    connection(ROUTE_12, west, Route11, ROUTE_11, 9));

map_attributes(Route11, ROUTE_11, 0x0f,
    connection(ROUTE_11, west, VermilionCity, VERMILION_CITY, 0)
    connection(ROUTE_11, east, Route12, ROUTE_12, -9));

map_attributes(LavenderTown, LAVENDER_TOWN, 0x2c,
    connection(LAVENDER_TOWN, north, Route10South, ROUTE_10_SOUTH, 0)
    connection(LAVENDER_TOWN, south, Route12, ROUTE_12, 0)
    connection(LAVENDER_TOWN, west, Route8, ROUTE_8, 0));

map_attributes(VermilionCity, VERMILION_CITY, 0x43,
    connection(VERMILION_CITY, north, Route6, ROUTE_6, 5)
    connection(VERMILION_CITY, east, Route11, ROUTE_11, 0));

map_attributes(Route6, ROUTE_6, 0x0f,
    connection(ROUTE_6, north, SaffronCity, SAFFRON_CITY, -5)
    connection(ROUTE_6, south, VermilionCity, VERMILION_CITY, -5));

map_attributes(SaffronCity, SAFFRON_CITY, 0x0f,
    connection(SAFFRON_CITY, north, Route5, ROUTE_5, 5)
    connection(SAFFRON_CITY, south, Route6, ROUTE_6, 5)
    connection(SAFFRON_CITY, west, Route7, ROUTE_7, 9)
    connection(SAFFRON_CITY, east, Route8, ROUTE_8, 9));

map_attributes(Route5, ROUTE_5, 0x0f,
    connection(ROUTE_5, north, CeruleanCity, CERULEAN_CITY, -5)
    connection(ROUTE_5, south, SaffronCity, SAFFRON_CITY, -5));

map_attributes(CeruleanCity, CERULEAN_CITY, 0x0f,
    connection(CERULEAN_CITY, north, Route24, ROUTE_24, 6)
    connection(CERULEAN_CITY, south, Route5, ROUTE_5, 5)
    connection(CERULEAN_CITY, west, Route4, ROUTE_4, 5)
    connection(CERULEAN_CITY, east, Route9, ROUTE_9, 9));

map_attributes(Route9, ROUTE_9, 0x2c,
    connection(ROUTE_9, south, Route10North, ROUTE_10_NORTH, 20)
    connection(ROUTE_9, west, CeruleanCity, CERULEAN_CITY, -9));

map_attributes(Route24, ROUTE_24, 0x2c,
    connection(ROUTE_24, north, Route25, ROUTE_25, 0)
    connection(ROUTE_24, south, CeruleanCity, CERULEAN_CITY, -6));

map_attributes(Route25, ROUTE_25, 0x2c,
    connection(ROUTE_25, south, Route24, ROUTE_24, 0));

map_attributes(Route3, ROUTE_3, 0x2c,
    connection(ROUTE_3, west, PewterCity, PEWTER_CITY, -5)
    connection(ROUTE_3, east, Route4, ROUTE_4, 0));

map_attributes(Route4, ROUTE_4, 0x2c,
    connection(ROUTE_4, west, Route3, ROUTE_3, 0)
    connection(ROUTE_4, east, CeruleanCity, CERULEAN_CITY, -5));

map_attributes(Route8, ROUTE_8, 0x2c,
    connection(ROUTE_8, west, SaffronCity, SAFFRON_CITY, -9)
    connection(ROUTE_8, east, LavenderTown, LAVENDER_TOWN, 0));

map_attributes(Route10North, ROUTE_10_NORTH, 0x2c,
    connection(ROUTE_10_NORTH, north, Route9, ROUTE_9, -20)
    connection(ROUTE_10_NORTH, south, Route10South, ROUTE_10_SOUTH, 0));

map_attributes(Route10South, ROUTE_10_SOUTH, 0x2c,
    connection(ROUTE_10_SOUTH, north, Route10North, ROUTE_10_NORTH, 0)
    connection(ROUTE_10_SOUTH, south, LavenderTown, LAVENDER_TOWN, 0));

map_attributes(Route23, ROUTE_23, 0x0f, 0);
map_attributes(SproutTower1F, SPROUT_TOWER_1F, 0x00, 0);
map_attributes(SproutTower2F, SPROUT_TOWER_2F, 0x00, 0);
map_attributes(SproutTower3F, SPROUT_TOWER_3F, 0x00, 0);
map_attributes(TinTower1F, TIN_TOWER_1F, 0x00, 0);
map_attributes(TinTower2F, TIN_TOWER_2F, 0x00, 0);
map_attributes(TinTower3F, TIN_TOWER_3F, 0x00, 0);
map_attributes(TinTower4F, TIN_TOWER_4F, 0x00, 0);
map_attributes(TinTower5F, TIN_TOWER_5F, 0x00, 0);
map_attributes(TinTower6F, TIN_TOWER_6F, 0x00, 0);
map_attributes(TinTower7F, TIN_TOWER_7F, 0x00, 0);
map_attributes(TinTower8F, TIN_TOWER_8F, 0x00, 0);
map_attributes(TinTower9F, TIN_TOWER_9F, 0x00, 0);
map_attributes(BurnedTower1F, BURNED_TOWER_1F, 0x00, 0);
map_attributes(BurnedTowerB1F, BURNED_TOWER_B1F, 0x09, 0);
map_attributes(NationalPark, NATIONAL_PARK, 0x00, 0);
map_attributes(NationalParkBugContest, NATIONAL_PARK_BUG_CONTEST, 0x00, 0);
map_attributes(RadioTower1F, RADIO_TOWER_1F, 0x00, 0);
map_attributes(RadioTower2F, RADIO_TOWER_2F, 0x00, 0);
map_attributes(RadioTower3F, RADIO_TOWER_3F, 0x00, 0);
map_attributes(RadioTower4F, RADIO_TOWER_4F, 0x00, 0);
map_attributes(RadioTower5F, RADIO_TOWER_5F, 0x00, 0);
map_attributes(RuinsOfAlphOutside, RUINS_OF_ALPH_OUTSIDE, 0x05, 0);
map_attributes(RuinsOfAlphHoOhChamber, RUINS_OF_ALPH_HO_OH_CHAMBER, 0x00, 0);
map_attributes(RuinsOfAlphKabutoChamber, RUINS_OF_ALPH_KABUTO_CHAMBER, 0x00, 0);
map_attributes(RuinsOfAlphOmanyteChamber, RUINS_OF_ALPH_OMANYTE_CHAMBER, 0x00, 0);
map_attributes(RuinsOfAlphAerodactylChamber, RUINS_OF_ALPH_AERODACTYL_CHAMBER, 0x00, 0);
map_attributes(RuinsOfAlphInnerChamber, RUINS_OF_ALPH_INNER_CHAMBER, 0x00, 0);
map_attributes(RuinsOfAlphResearchCenter, RUINS_OF_ALPH_RESEARCH_CENTER, 0x00, 0);
map_attributes(RuinsOfAlphHoOhItemRoom, RUINS_OF_ALPH_HO_OH_ITEM_ROOM, 0x00, 0);
map_attributes(RuinsOfAlphKabutoItemRoom, RUINS_OF_ALPH_KABUTO_ITEM_ROOM, 0x00, 0);
map_attributes(RuinsOfAlphOmanyteItemRoom, RUINS_OF_ALPH_OMANYTE_ITEM_ROOM, 0x00, 0);
map_attributes(RuinsOfAlphAerodactylItemRoom, RUINS_OF_ALPH_AERODACTYL_ITEM_ROOM, 0x00, 0);
map_attributes(RuinsOfAlphHoOhWordRoom, RUINS_OF_ALPH_HO_OH_WORD_ROOM, 0x00, 0);
map_attributes(RuinsOfAlphKabutoWordRoom, RUINS_OF_ALPH_KABUTO_WORD_ROOM, 0x00, 0);
map_attributes(RuinsOfAlphOmanyteWordRoom, RUINS_OF_ALPH_OMANYTE_WORD_ROOM, 0x00, 0);
map_attributes(RuinsOfAlphAerodactylWordRoom, RUINS_OF_ALPH_AERODACTYL_WORD_ROOM, 0x00, 0);
map_attributes(UnionCave1F, UNION_CAVE_1F, 0x09, 0);
map_attributes(UnionCaveB1F, UNION_CAVE_B1F, 0x09, 0);
map_attributes(UnionCaveB2F, UNION_CAVE_B2F, 0x09, 0);
map_attributes(SlowpokeWellB1F, SLOWPOKE_WELL_B1F, 0x09, 0);
map_attributes(SlowpokeWellB2F, SLOWPOKE_WELL_B2F, 0x09, 0);
map_attributes(OlivineLighthouse1F, OLIVINE_LIGHTHOUSE_1F, 0x00, 0);
map_attributes(OlivineLighthouse2F, OLIVINE_LIGHTHOUSE_2F, 0x00, 0);
map_attributes(OlivineLighthouse3F, OLIVINE_LIGHTHOUSE_3F, 0x00, 0);
map_attributes(OlivineLighthouse4F, OLIVINE_LIGHTHOUSE_4F, 0x00, 0);
map_attributes(OlivineLighthouse5F, OLIVINE_LIGHTHOUSE_5F, 0x00, 0);
map_attributes(OlivineLighthouse6F, OLIVINE_LIGHTHOUSE_6F, 0x00, 0);
map_attributes(MahoganyMart1F, MAHOGANY_MART_1F, 0x00, 0);
map_attributes(TeamRocketBaseB1F, TEAM_ROCKET_BASE_B1F, 0x00, 0);
map_attributes(TeamRocketBaseB2F, TEAM_ROCKET_BASE_B2F, 0x00, 0);
map_attributes(TeamRocketBaseB3F, TEAM_ROCKET_BASE_B3F, 0x00, 0);
map_attributes(IlexForest, ILEX_FOREST, 0x05, 0);
map_attributes(GoldenrodUnderground, GOLDENROD_UNDERGROUND, 0x00, 0);
map_attributes(GoldenrodUndergroundSwitchRoomEntrances, GOLDENROD_UNDERGROUND_SWITCH_ROOM_ENTRANCES, 0x00, 0);
map_attributes(GoldenrodDeptStoreB1F, GOLDENROD_DEPT_STORE_B1F, 0x00, 0);
map_attributes(GoldenrodUndergroundWarehouse, GOLDENROD_UNDERGROUND_WAREHOUSE, 0x00, 0);
map_attributes(MountMortar1FOutside, MOUNT_MORTAR_1F_OUTSIDE, 0x09, 0);
map_attributes(MountMortar1FInside, MOUNT_MORTAR_1F_INSIDE, 0x09, 0);
map_attributes(MountMortar2FInside, MOUNT_MORTAR_2F_INSIDE, 0x09, 0);
map_attributes(MountMortarB1F, MOUNT_MORTAR_B1F, 0x09, 0);
map_attributes(IcePath1F, ICE_PATH_1F, 0x09, 0);
map_attributes(IcePathB1F, ICE_PATH_B1F, 0x19, 0);
map_attributes(IcePathB2FMahoganySide, ICE_PATH_B2F_MAHOGANY_SIDE, 0x19, 0);
map_attributes(IcePathB2FBlackthornSide, ICE_PATH_B2F_BLACKTHORN_SIDE, 0x19, 0);
map_attributes(IcePathB3F, ICE_PATH_B3F, 0x19, 0);
map_attributes(WhirlIslandNW, WHIRL_ISLAND_NW, 0x09, 0);
map_attributes(WhirlIslandNE, WHIRL_ISLAND_NE, 0x09, 0);
map_attributes(WhirlIslandSW, WHIRL_ISLAND_SW, 0x09, 0);
map_attributes(WhirlIslandCave, WHIRL_ISLAND_CAVE, 0x09, 0);
map_attributes(WhirlIslandSE, WHIRL_ISLAND_SE, 0x0f, 0);
map_attributes(WhirlIslandB1F, WHIRL_ISLAND_B1F, 0x09, 0);
map_attributes(WhirlIslandB2F, WHIRL_ISLAND_B2F, 0x2e, 0);
map_attributes(WhirlIslandLugiaChamber, WHIRL_ISLAND_LUGIA_CHAMBER, 0x0f, 0);
map_attributes(SilverCaveRoom1, SILVER_CAVE_ROOM_1, 0x09, 0);
map_attributes(SilverCaveRoom2, SILVER_CAVE_ROOM_2, 0x09, 0);
map_attributes(SilverCaveRoom3, SILVER_CAVE_ROOM_3, 0x09, 0);
map_attributes(SilverCaveItemRooms, SILVER_CAVE_ITEM_ROOMS, 0x09, 0);
map_attributes(DarkCaveVioletEntrance, DARK_CAVE_VIOLET_ENTRANCE, 0x09, 0);
map_attributes(DarkCaveBlackthornEntrance, DARK_CAVE_BLACKTHORN_ENTRANCE, 0x09, 0);
map_attributes(DragonsDen1F, DRAGONS_DEN_1F, 0x09, 0);
map_attributes(DragonsDenB1F, DRAGONS_DEN_B1F, 0x71, 0);
map_attributes(DragonShrine, DRAGON_SHRINE, 0x00, 0);
map_attributes(TohjoFalls, TOHJO_FALLS, 0x09, 0);
map_attributes(OlivinePokecenter1F, OLIVINE_POKECENTER_1F, 0x00, 0);
map_attributes(OlivineGym, OLIVINE_GYM, 0x00, 0);
map_attributes(OlivineTimsHouse, OLIVINE_TIMS_HOUSE, 0x00, 0);
// map_attributes(OlivineHouseBeta, OLIVINE_HOUSE_BETA, 0x00, 0);
map_attributes(OlivinePunishmentSpeechHouse, OLIVINE_PUNISHMENT_SPEECH_HOUSE, 0x00, 0);
map_attributes(OlivineGoodRodHouse, OLIVINE_GOOD_ROD_HOUSE, 0x00, 0);
map_attributes(OlivineCafe, OLIVINE_CAFE, 0x00, 0);
map_attributes(OlivineMart, OLIVINE_MART, 0x00, 0);
map_attributes(Route38EcruteakGate, ROUTE_38_ECRUTEAK_GATE, 0x00, 0);
map_attributes(Route39Barn, ROUTE_39_BARN, 0x00, 0);
map_attributes(Route39Farmhouse, ROUTE_39_FARMHOUSE, 0x00, 0);
map_attributes(MahoganyRedGyaradosSpeechHouse, MAHOGANY_RED_GYARADOS_SPEECH_HOUSE, 0x00, 0);
map_attributes(MahoganyGym, MAHOGANY_GYM, 0x00, 0);
map_attributes(MahoganyPokecenter1F, MAHOGANY_POKECENTER_1F, 0x00, 0);
map_attributes(Route42EcruteakGate, ROUTE_42_ECRUTEAK_GATE, 0x00, 0);
map_attributes(DiglettsCave, DIGLETTS_CAVE, 0x09, 0);
map_attributes(MountMoon, MOUNT_MOON, 0x09, 0);
map_attributes(UndergroundPath, UNDERGROUND_PATH, 0x00, 0);
map_attributes(RockTunnel1F, ROCK_TUNNEL_1F, 0x09, 0);
map_attributes(RockTunnelB1F, ROCK_TUNNEL_B1F, 0x09, 0);
// map_attributes(SafariZoneFuchsiaGateBeta, SAFARI_ZONE_FUCHSIA_GATE_BETA, 0x00, 0);
// map_attributes(SafariZoneBeta, SAFARI_ZONE_BETA, 0x13, 0);
map_attributes(VictoryRoad, VICTORY_ROAD, 0x1d, 0);
map_attributes(EcruteakTinTowerEntrance, ECRUTEAK_TIN_TOWER_ENTRANCE, 0x00, 0);
map_attributes(WiseTriosRoom, WISE_TRIOS_ROOM, 0x00, 0);
map_attributes(EcruteakPokecenter1F, ECRUTEAK_POKECENTER_1F, 0x00, 0);
map_attributes(EcruteakLugiaSpeechHouse, ECRUTEAK_LUGIA_SPEECH_HOUSE, 0x00, 0);
map_attributes(DanceTheatre, DANCE_THEATRE, 0x00, 0);
map_attributes(EcruteakMart, ECRUTEAK_MART, 0x00, 0);
map_attributes(EcruteakGym, ECRUTEAK_GYM, 0x00, 0);
map_attributes(EcruteakItemfinderHouse, ECRUTEAK_ITEMFINDER_HOUSE, 0x00, 0);
map_attributes(BlackthornGym1F, BLACKTHORN_GYM_1F, 0x00, 0);
map_attributes(BlackthornGym2F, BLACKTHORN_GYM_2F, 0x00, 0);
map_attributes(BlackthornDragonSpeechHouse, BLACKTHORN_DRAGON_SPEECH_HOUSE, 0x00, 0);
map_attributes(BlackthornEmysHouse, BLACKTHORN_EMYS_HOUSE, 0x00, 0);
map_attributes(BlackthornMart, BLACKTHORN_MART, 0x00, 0);
map_attributes(BlackthornPokecenter1F, BLACKTHORN_POKECENTER_1F, 0x00, 0);
map_attributes(MoveDeletersHouse, MOVE_DELETERS_HOUSE, 0x00, 0);
map_attributes(CinnabarPokecenter1F, CINNABAR_POKECENTER_1F, 0x00, 0);
// map_attributes(CinnabarPokecenter2FBeta, CINNABAR_POKECENTER_2F_BETA, 0x00, 0);
map_attributes(Route19FuchsiaGate, ROUTE_19_FUCHSIA_GATE, 0x00, 0);
map_attributes(SeafoamGym, SEAFOAM_GYM, 0x09, 0);
map_attributes(CeruleanGymBadgeSpeechHouse, CERULEAN_GYM_BADGE_SPEECH_HOUSE, 0x00, 0);
map_attributes(CeruleanPoliceStation, CERULEAN_POLICE_STATION, 0x00, 0);
map_attributes(CeruleanTradeSpeechHouse, CERULEAN_TRADE_SPEECH_HOUSE, 0x00, 0);
map_attributes(CeruleanPokecenter1F, CERULEAN_POKECENTER_1F, 0x00, 0);
// map_attributes(CeruleanPokecenter2FBeta, CERULEAN_POKECENTER_2F_BETA, 0x00, 0);
map_attributes(CeruleanGym, CERULEAN_GYM, 0x00, 0);
map_attributes(CeruleanMart, CERULEAN_MART, 0x00, 0);
map_attributes(Route10Pokecenter1F, ROUTE_10_POKECENTER_1F, 0x00, 0);
// map_attributes(Route10Pokecenter2FBeta, ROUTE_10_POKECENTER_2F_BETA, 0x00, 0);
map_attributes(PowerPlant, POWER_PLANT, 0x00, 0);
map_attributes(BillsHouse, BILLS_HOUSE, 0x00, 0);
map_attributes(AzaleaPokecenter1F, AZALEA_POKECENTER_1F, 0x00, 0);
map_attributes(CharcoalKiln, CHARCOAL_KILN, 0x00, 0);
map_attributes(AzaleaMart, AZALEA_MART, 0x00, 0);
map_attributes(KurtsHouse, KURTS_HOUSE, 0x00, 0);
map_attributes(AzaleaGym, AZALEA_GYM, 0x00, 0);
map_attributes(LakeOfRageHiddenPowerHouse, LAKE_OF_RAGE_HIDDEN_POWER_HOUSE, 0x00, 0);
map_attributes(LakeOfRageMagikarpHouse, LAKE_OF_RAGE_MAGIKARP_HOUSE, 0x00, 0);
map_attributes(Route43MahoganyGate, ROUTE_43_MAHOGANY_GATE, 0x00, 0);
map_attributes(Route43Gate, ROUTE_43_GATE, 0x00, 0);
map_attributes(VioletMart, VIOLET_MART, 0x00, 0);
map_attributes(VioletGym, VIOLET_GYM, 0x00, 0);
map_attributes(EarlsPokemonAcademy, EARLS_POKEMON_ACADEMY, 0x00, 0);
map_attributes(VioletNicknameSpeechHouse, VIOLET_NICKNAME_SPEECH_HOUSE, 0x00, 0);
map_attributes(VioletPokecenter1F, VIOLET_POKECENTER_1F, 0x00, 0);
map_attributes(VioletKylesHouse, VIOLET_KYLES_HOUSE, 0x00, 0);
map_attributes(Route32RuinsOfAlphGate, ROUTE_32_RUINS_OF_ALPH_GATE, 0x00, 0);
map_attributes(Route32Pokecenter1F, ROUTE_32_POKECENTER_1F, 0x00, 0);
map_attributes(Route35GoldenrodGate, ROUTE_35_GOLDENROD_GATE, 0x00, 0);
map_attributes(Route35NationalParkGate, ROUTE_35_NATIONAL_PARK_GATE, 0x00, 0);
map_attributes(Route36RuinsOfAlphGate, ROUTE_36_RUINS_OF_ALPH_GATE, 0x00, 0);
map_attributes(Route36NationalParkGate, ROUTE_36_NATIONAL_PARK_GATE, 0x00, 0);
map_attributes(GoldenrodGym, GOLDENROD_GYM, 0x00, 0);
map_attributes(GoldenrodBikeShop, GOLDENROD_BIKE_SHOP, 0x00, 0);
map_attributes(GoldenrodHappinessRater, GOLDENROD_HAPPINESS_RATER, 0x00, 0);
map_attributes(BillsFamilysHouse, BILLS_FAMILYS_HOUSE, 0x00, 0);
map_attributes(GoldenrodMagnetTrainStation, GOLDENROD_MAGNET_TRAIN_STATION, 0x00, 0);
map_attributes(GoldenrodFlowerShop, GOLDENROD_FLOWER_SHOP, 0x00, 0);
map_attributes(GoldenrodPPSpeechHouse, GOLDENROD_PP_SPEECH_HOUSE, 0x00, 0);
map_attributes(GoldenrodNameRater, GOLDENROD_NAME_RATER, 0x00, 0);
map_attributes(GoldenrodDeptStore1F, GOLDENROD_DEPT_STORE_1F, 0x00, 0);
map_attributes(GoldenrodDeptStore2F, GOLDENROD_DEPT_STORE_2F, 0x00, 0);
map_attributes(GoldenrodDeptStore3F, GOLDENROD_DEPT_STORE_3F, 0x00, 0);
map_attributes(GoldenrodDeptStore4F, GOLDENROD_DEPT_STORE_4F, 0x00, 0);
map_attributes(GoldenrodDeptStore5F, GOLDENROD_DEPT_STORE_5F, 0x00, 0);
map_attributes(GoldenrodDeptStore6F, GOLDENROD_DEPT_STORE_6F, 0x00, 0);
map_attributes(GoldenrodDeptStoreElevator, GOLDENROD_DEPT_STORE_ELEVATOR, 0x00, 0);
map_attributes(GoldenrodDeptStoreRoof, GOLDENROD_DEPT_STORE_ROOF, 0x24, 0);
map_attributes(GoldenrodGameCorner, GOLDENROD_GAME_CORNER, 0x00, 0);
// map_attributes(GoldenrodPokecenter1F, GOLDENROD_POKECENTER_1F, 0x00, 0);
map_attributes(PokecomCenter, GOLDENROD_POKECENTER_1F, 0x00, 0);
map_attributes(PokecomCenterAdminOfficeMobile, POKECOM_CENTER_ADMIN_OFFICE_MOBILE, 0x00, 0);
map_attributes(IlexForestAzaleaGate, ILEX_FOREST_AZALEA_GATE, 0x00, 0);
map_attributes(Route34IlexForestGate, ROUTE_34_ILEX_FOREST_GATE, 0x00, 0);
map_attributes(DayCare, DAY_CARE, 0x00, 0);
map_attributes(VermilionFishingSpeechHouse, VERMILION_FISHING_SPEECH_HOUSE, 0x00, 0);
map_attributes(VermilionPokecenter1F, VERMILION_POKECENTER_1F, 0x00, 0);
// map_attributes(VermilionPokecenter2FBeta, VERMILION_POKECENTER_2F_BETA, 0x00, 0);
map_attributes(PokemonFanClub, POKEMON_FAN_CLUB, 0x00, 0);
map_attributes(VermilionMagnetTrainSpeechHouse, VERMILION_MAGNET_TRAIN_SPEECH_HOUSE, 0x00, 0);
map_attributes(VermilionMart, VERMILION_MART, 0x00, 0);
map_attributes(VermilionDiglettsCaveSpeechHouse, VERMILION_DIGLETTS_CAVE_SPEECH_HOUSE, 0x00, 0);
map_attributes(VermilionGym, VERMILION_GYM, 0x00, 0);
map_attributes(Route6SaffronGate, ROUTE_6_SAFFRON_GATE, 0x00, 0);
map_attributes(Route6UndergroundPathEntrance, ROUTE_6_UNDERGROUND_PATH_ENTRANCE, 0x00, 0);
map_attributes(RedsHouse1F, REDS_HOUSE_1F, 0x00, 0);
map_attributes(RedsHouse2F, REDS_HOUSE_2F, 0x00, 0);
map_attributes(BluesHouse, BLUES_HOUSE, 0x00, 0);
map_attributes(OaksLab, OAKS_LAB, 0x00, 0);
map_attributes(PewterNidoranSpeechHouse, PEWTER_NIDORAN_SPEECH_HOUSE, 0x00, 0);
map_attributes(PewterGym, PEWTER_GYM, 0x00, 0);
map_attributes(PewterMart, PEWTER_MART, 0x00, 0);
map_attributes(PewterPokecenter1F, PEWTER_POKECENTER_1F, 0x00, 0);
// map_attributes(PewterPokecenter2FBeta, PEWTER_POKECENTER_2F_BETA, 0x00, 0);
map_attributes(PewterSnoozeSpeechHouse, PEWTER_SNOOZE_SPEECH_HOUSE, 0x00, 0);
map_attributes(OlivinePort, OLIVINE_PORT, 0x0a, 0);
map_attributes(VermilionPort, VERMILION_PORT, 0x0a, 0);
map_attributes(FastShip1F, FAST_SHIP_1F, 0x00, 0);
map_attributes(FastShipCabins_NNW_NNE_NE, FAST_SHIP_CABINS_NNW_NNE_NE, 0x00, 0);
map_attributes(FastShipCabins_SW_SSW_NW, FAST_SHIP_CABINS_SW_SSW_NW, 0x00, 0);
map_attributes(FastShipCabins_SE_SSE_CaptainsCabin, FAST_SHIP_CABINS_SE_SSE_CAPTAINS_CABIN, 0x00, 0);
map_attributes(FastShipB1F, FAST_SHIP_B1F, 0x00, 0);
map_attributes(OlivinePortPassage, OLIVINE_PORT_PASSAGE, 0x00, 0);
map_attributes(VermilionPortPassage, VERMILION_PORT_PASSAGE, 0x00, 0);
map_attributes(MountMoonSquare, MOUNT_MOON_SQUARE, 0x2d, 0);
map_attributes(MountMoonGiftShop, MOUNT_MOON_GIFT_SHOP, 0x00, 0);
map_attributes(TinTowerRoof, TIN_TOWER_ROOF, 0x00, 0);
map_attributes(IndigoPlateauPokecenter1F, INDIGO_PLATEAU_POKECENTER_1F, 0x00, 0);
map_attributes(WillsRoom, WILLS_ROOM, 0x00, 0);
map_attributes(KogasRoom, KOGAS_ROOM, 0x00, 0);
map_attributes(BrunosRoom, BRUNOS_ROOM, 0x00, 0);
map_attributes(KarensRoom, KARENS_ROOM, 0x00, 0);
map_attributes(LancesRoom, LANCES_ROOM, 0x00, 0);
map_attributes(HallOfFame, HALL_OF_FAME, 0x00, 0);
map_attributes(FuchsiaMart, FUCHSIA_MART, 0x00, 0);
map_attributes(SafariZoneMainOffice, SAFARI_ZONE_MAIN_OFFICE, 0x00, 0);
map_attributes(FuchsiaGym, FUCHSIA_GYM, 0x00, 0);
map_attributes(BillsBrothersHouse, BILLS_BROTHERS_HOUSE, 0x00, 0);
map_attributes(FuchsiaPokecenter1F, FUCHSIA_POKECENTER_1F, 0x00, 0);
// map_attributes(FuchsiaPokecenter2FBeta, FUCHSIA_POKECENTER_2F_BETA, 0x00, 0);
map_attributes(SafariZoneWardensHome, SAFARI_ZONE_WARDENS_HOME, 0x00, 0);
map_attributes(Route15FuchsiaGate, ROUTE_15_FUCHSIA_GATE, 0x00, 0);
map_attributes(LavenderPokecenter1F, LAVENDER_POKECENTER_1F, 0x00, 0);
// map_attributes(LavenderPokecenter2FBeta, LAVENDER_POKECENTER_2F_BETA, 0x00, 0);
map_attributes(MrFujisHouse, MR_FUJIS_HOUSE, 0x00, 0);
map_attributes(LavenderSpeechHouse, LAVENDER_SPEECH_HOUSE, 0x00, 0);
map_attributes(LavenderNameRater, LAVENDER_NAME_RATER, 0x00, 0);
map_attributes(LavenderMart, LAVENDER_MART, 0x00, 0);
map_attributes(SoulHouse, SOUL_HOUSE, 0x00, 0);
map_attributes(LavRadioTower1F, LAV_RADIO_TOWER_1F, 0x00, 0);
map_attributes(Route8SaffronGate, ROUTE_8_SAFFRON_GATE, 0x00, 0);
map_attributes(Route12SuperRodHouse, ROUTE_12_SUPER_ROD_HOUSE, 0x00, 0);
map_attributes(SilverCavePokecenter1F, SILVER_CAVE_POKECENTER_1F, 0x00, 0);
map_attributes(Route28SteelWingHouse, ROUTE_28_STEEL_WING_HOUSE, 0x00, 0);
map_attributes(Pokecenter2F, POKECENTER_2F, 0x00, 0);
map_attributes(TradeCenter, TRADE_CENTER, 0x00, 0);
map_attributes(Colosseum, COLOSSEUM, 0x00, 0);
// map_attributes(TimeCapsule, TIME_CAPSULE, 0x00, 0);
map_attributes(MobileTradeRoom, MOBILE_TRADE_ROOM, 0x00, 0);
map_attributes(MobileBattleRoom, MOBILE_BATTLE_ROOM, 0x00, 0);
map_attributes(CeladonDeptStore1F, CELADON_DEPT_STORE_1F, 0x00, 0);
map_attributes(CeladonDeptStore2F, CELADON_DEPT_STORE_2F, 0x00, 0);
map_attributes(CeladonDeptStore3F, CELADON_DEPT_STORE_3F, 0x00, 0);
map_attributes(CeladonDeptStore4F, CELADON_DEPT_STORE_4F, 0x00, 0);
map_attributes(CeladonDeptStore5F, CELADON_DEPT_STORE_5F, 0x00, 0);
map_attributes(CeladonDeptStore6F, CELADON_DEPT_STORE_6F, 0x00, 0);
map_attributes(CeladonDeptStoreElevator, CELADON_DEPT_STORE_ELEVATOR, 0x00, 0);
map_attributes(CeladonMansion1F, CELADON_MANSION_1F, 0x00, 0);
map_attributes(CeladonMansion2F, CELADON_MANSION_2F, 0x00, 0);
map_attributes(CeladonMansion3F, CELADON_MANSION_3F, 0x00, 0);
map_attributes(CeladonMansionRoof, CELADON_MANSION_ROOF, 0x01, 0);
map_attributes(CeladonMansionRoofHouse, CELADON_MANSION_ROOF_HOUSE, 0x00, 0);
map_attributes(CeladonPokecenter1F, CELADON_POKECENTER_1F, 0x00, 0);
// map_attributes(CeladonPokecenter2FBeta, CELADON_POKECENTER_2F_BETA, 0x00, 0);
map_attributes(CeladonGameCorner, CELADON_GAME_CORNER, 0x00, 0);
map_attributes(CeladonGameCornerPrizeRoom, CELADON_GAME_CORNER_PRIZE_ROOM, 0x00, 0);
map_attributes(CeladonGym, CELADON_GYM, 0x00, 0);
map_attributes(CeladonCafe, CELADON_CAFE, 0x00, 0);
map_attributes(Route16FuchsiaSpeechHouse, ROUTE_16_FUCHSIA_SPEECH_HOUSE, 0x00, 0);
map_attributes(Route16Gate, ROUTE_16_GATE, 0x00, 0);
map_attributes(Route7SaffronGate, ROUTE_7_SAFFRON_GATE, 0x00, 0);
map_attributes(Route17Route18Gate, ROUTE_17_ROUTE_18_GATE, 0x00, 0);
map_attributes(ManiasHouse, MANIAS_HOUSE, 0x00, 0);
map_attributes(CianwoodGym, CIANWOOD_GYM, 0x00, 0);
map_attributes(CianwoodPokecenter1F, CIANWOOD_POKECENTER_1F, 0x00, 0);
map_attributes(CianwoodPharmacy, CIANWOOD_PHARMACY, 0x00, 0);
map_attributes(CianwoodPhotoStudio, CIANWOOD_PHOTO_STUDIO, 0x00, 0);
map_attributes(CianwoodLugiaSpeechHouse, CIANWOOD_LUGIA_SPEECH_HOUSE, 0x00, 0);
map_attributes(PokeSeersHouse, POKE_SEERS_HOUSE, 0x00, 0);
map_attributes(BattleTower1F, BATTLE_TOWER_1F, 0x00, 0);
map_attributes(BattleTowerBattleRoom, BATTLE_TOWER_BATTLE_ROOM, 0x00, 0);
map_attributes(BattleTowerElevator, BATTLE_TOWER_ELEVATOR, 0x00, 0);
map_attributes(BattleTowerHallway, BATTLE_TOWER_HALLWAY, 0x00, 0);
map_attributes(Route40BattleTowerGate, ROUTE_40_BATTLE_TOWER_GATE, 0x00, 0);
map_attributes(BattleTowerOutside, BATTLE_TOWER_OUTSIDE, 0x05, 0);
map_attributes(ViridianGym, VIRIDIAN_GYM, 0x00, 0);
map_attributes(ViridianNicknameSpeechHouse, VIRIDIAN_NICKNAME_SPEECH_HOUSE, 0x00, 0);
map_attributes(TrainerHouse1F, TRAINER_HOUSE_1F, 0x00, 0);
map_attributes(TrainerHouseB1F, TRAINER_HOUSE_B1F, 0x00, 0);
map_attributes(ViridianMart, VIRIDIAN_MART, 0x00, 0);
map_attributes(ViridianPokecenter1F, VIRIDIAN_POKECENTER_1F, 0x00, 0);
// map_attributes(ViridianPokecenter2FBeta, VIRIDIAN_POKECENTER_2F_BETA, 0x00, 0);
map_attributes(Route2NuggetHouse, ROUTE_2_NUGGET_HOUSE, 0x00, 0);
map_attributes(Route2Gate, ROUTE_2_GATE, 0x00, 0);
map_attributes(VictoryRoadGate, VICTORY_ROAD_GATE, 0x00, 0);
map_attributes(ElmsLab, ELMS_LAB, 0x00, 0);
map_attributes(PlayersHouse1F, PLAYERS_HOUSE_1F, 0x00, 0);
map_attributes(PlayersHouse2F, PLAYERS_HOUSE_2F, 0x00, 0);
map_attributes(PlayersNeighborsHouse, PLAYERS_NEIGHBORS_HOUSE, 0x00, 0);
map_attributes(ElmsHouse, ELMS_HOUSE, 0x00, 0);
map_attributes(Route26HealHouse, ROUTE_26_HEAL_HOUSE, 0x00, 0);
map_attributes(DayOfWeekSiblingsHouse, DAY_OF_WEEK_SIBLINGS_HOUSE, 0x00, 0);
map_attributes(Route27SandstormHouse, ROUTE_27_SANDSTORM_HOUSE, 0x00, 0);
map_attributes(Route29Route46Gate, ROUTE_29_ROUTE_46_GATE, 0x00, 0);
map_attributes(FightingDojo, FIGHTING_DOJO, 0x00, 0);
map_attributes(SaffronGym, SAFFRON_GYM, 0x00, 0);
map_attributes(SaffronMart, SAFFRON_MART, 0x00, 0);
map_attributes(SaffronPokecenter1F, SAFFRON_POKECENTER_1F, 0x00, 0);
// map_attributes(SaffronPokecenter2FBeta, SAFFRON_POKECENTER_2F_BETA, 0x00, 0);
map_attributes(MrPsychicsHouse, MR_PSYCHICS_HOUSE, 0x00, 0);
map_attributes(SaffronMagnetTrainStation, SAFFRON_MAGNET_TRAIN_STATION, 0x00, 0);
map_attributes(SilphCo1F, SILPH_CO_1F, 0x00, 0);
map_attributes(CopycatsHouse1F, COPYCATS_HOUSE_1F, 0x00, 0);
map_attributes(CopycatsHouse2F, COPYCATS_HOUSE_2F, 0x00, 0);
map_attributes(Route5UndergroundPathEntrance, ROUTE_5_UNDERGROUND_PATH_ENTRANCE, 0x00, 0);
map_attributes(Route5SaffronGate, ROUTE_5_SAFFRON_GATE, 0x00, 0);
map_attributes(Route5CleanseTagHouse, ROUTE_5_CLEANSE_TAG_HOUSE, 0x00, 0);
map_attributes(CherrygroveMart, CHERRYGROVE_MART, 0x00, 0);
map_attributes(CherrygrovePokecenter1F, CHERRYGROVE_POKECENTER_1F, 0x00, 0);
map_attributes(CherrygroveGymSpeechHouse, CHERRYGROVE_GYM_SPEECH_HOUSE, 0x00, 0);
map_attributes(GuideGentsHouse, GUIDE_GENTS_HOUSE, 0x00, 0);
map_attributes(CherrygroveEvolutionSpeechHouse, CHERRYGROVE_EVOLUTION_SPEECH_HOUSE, 0x00, 0);
map_attributes(Route30BerryHouse, ROUTE_30_BERRY_HOUSE, 0x00, 0);
map_attributes(MrPokemonsHouse, MR_POKEMONS_HOUSE, 0x00, 0);
map_attributes(Route31VioletGate, ROUTE_31_VIOLET_GATE, 0x00, 0);
