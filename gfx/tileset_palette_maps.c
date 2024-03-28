#include <stdint.h>
#include "tileset_palette_maps.h"
#include "../constants/tileset_constants.h"
#include "../constants/hardware_constants.h"
#include "../util/variadic_macros.h"

// tilepal: MACRO
// ; used in gfx/tilesets/*_palette_map.asm
// ; vram bank, pals
// x = \1 << OAM_TILE_BANK
// rept (_NARG - 1) / 2
// 	dn (x | PAL_BG_\3), (x | PAL_BG_\2)
// 	shift 2
// endr
// ENDM
#define tilepal_bank_(_b) (_b << OAM_TILE_BANK)
#define tilepal_value_(_b, _x) (tilepal_bank_(_b) | PAL_BG_##_x)
#define tilepal(_0, ...) CPPX_INVOKE( CPPX_CONCAT ( tilepal_value_, PP_NARG(__VA_ARGS__) ) , (_0, __VA_ARGS__) )
#define tilepal_value_1(_b, _0) tilepal_value_(_b, _0)
#define tilepal_value_2(_b, _0, _1) tilepal_value_(_b, _0), tilepal_value_(_b, _1)
#define tilepal_value_3(_b, _0, _1, _2) tilepal_value_2(_b, _0, _1), tilepal_value_(_b, _2)
#define tilepal_value_4(_b, _0, _1, _2, _3) tilepal_value_3(_b, _0, _1, _2), tilepal_value_(_b, _3)
#define tilepal_value_5(_b, _0, _1, _2, _3, _4) tilepal_value_4(_b, _0, _1, _2, _3), tilepal_value_(_b, _4)
#define tilepal_value_6(_b, _0, _1, _2, _3, _4, _5) tilepal_value_5(_b, _0, _1, _2, _3, _4), tilepal_value_(_b, _5)
#define tilepal_value_7(_b, _0, _1, _2, _3, _4, _5, _6) tilepal_value_6(_b, _0, _1, _2, _3, _4, _5), tilepal_value_(_b, _6)
#define tilepal_value_8(_b, _0, _1, _2, _3, _4, _5, _6, _7) tilepal_value_7(_b, _0, _1, _2, _3, _4, _5, _6), tilepal_value_(_b, _7)

const uint8_t TilesetKantoPalMap[] = {
#include "tilesets/kanto_palette_map.h"
};
#define Tileset0PalMap TilesetJohtoPalMap
const uint8_t TilesetJohtoPalMap[] = {
#include "tilesets/johto_palette_map.h"
};
const uint8_t TilesetJohtoModernPalMap[] = {
#include "tilesets/johto_modern_palette_map.h"
};
const uint8_t TilesetHousePalMap[] = {
#include "tilesets/house_palette_map.h"
};
const uint8_t TilesetPlayersHousePalMap[] = {
#include "tilesets/players_house_palette_map.h"
};
const uint8_t TilesetPokecenterPalMap[] = {
#include "tilesets/pokecenter_palette_map.h"
};
const uint8_t TilesetGatePalMap[] = {
#include "tilesets/gate_palette_map.h"
};
const uint8_t TilesetPortPalMap[] = {
#include "tilesets/port_palette_map.h"
};
const uint8_t TilesetLabPalMap[] = {
#include "tilesets/lab_palette_map.h"
};
const uint8_t TilesetFacilityPalMap[] = {
#include "tilesets/facility_palette_map.h"
};
const uint8_t TilesetMartPalMap[] = {
#include "tilesets/mart_palette_map.h"
};
const uint8_t TilesetMansionPalMap[] = {
#include "tilesets/mansion_palette_map.h"
};
const uint8_t TilesetGameCornerPalMap[] = {
#include "tilesets/game_corner_palette_map.h"
};
const uint8_t TilesetEliteFourRoomPalMap[] = {
#include "tilesets/elite_four_room_palette_map.h"
};
const uint8_t TilesetTraditionalHousePalMap[] = {
#include "tilesets/traditional_house_palette_map.h"
};
const uint8_t TilesetTowerPalMap[] = {
#include "tilesets/tower_palette_map.h"
};
#define TilesetCavePalMap TilesetDarkCavePalMap
const uint8_t TilesetDarkCavePalMap[] = {
#include "tilesets/cave_palette_map.h"
};
const uint8_t TilesetParkPalMap[] = {
#include "tilesets/park_palette_map.h"
};
#define TilesetRuinsOfAlphPalMap TilesetAerodactylWordRoomPalMap
#define TilesetBetaWordRoomPalMap TilesetAerodactylWordRoomPalMap
#define TilesetHoOhWordRoomPalMap TilesetAerodactylWordRoomPalMap
#define TilesetKabutoWordRoomPalMap TilesetAerodactylWordRoomPalMap
#define TilesetOmanyteWordRoomPalMap TilesetAerodactylWordRoomPalMap
const uint8_t TilesetAerodactylWordRoomPalMap[] = {
#include "tilesets/ruins_of_alph_palette_map.h"
};
const uint8_t TilesetRadioTowerPalMap[] = {
#include "tilesets/radio_tower_palette_map.h"
};
const uint8_t TilesetTrainStationPalMap[] = {
#include "tilesets/train_station_palette_map.h"
};
const uint8_t TilesetUndergroundPalMap[] = {
#include "tilesets/underground_palette_map.h"
};
const uint8_t TilesetChampionsRoomPalMap[] = {
#include "tilesets/champions_room_palette_map.h"
};
const uint8_t TilesetLighthousePalMap[] = {
#include "tilesets/lighthouse_palette_map.h"
};
const uint8_t TilesetPlayersRoomPalMap[] = {
#include "tilesets/players_room_palette_map.h"
};
// UnusedMuseumPalMap: ; unreferenced
// INCLUDE "gfx/tilesets/unused_museum_palette_map.h"

const uint8_t TilesetIcePathPalMap[] = {
#include "tilesets/ice_path_palette_map.h"
};
const uint8_t TilesetForestPalMap[] = {
#include "tilesets/forest_palette_map.h"
};
const uint8_t TilesetPokeComCenterPalMap[] = {
#include "tilesets/pokecom_center_palette_map.h"
};
const uint8_t TilesetBattleTowerInsidePalMap[] = {
#include "tilesets/battle_tower_inside_palette_map.h"
};
const uint8_t TilesetBattleTowerOutsidePalMap[] = {
#include "tilesets/battle_tower_outside_palette_map.h"
};
// MapGroupPalettes: ; unreferenced
// ; entries correspond to MAPGROUP_* constants
// rept NUM_MAP_GROUPS
// 	db PAL_BG_ROOF
// endr
