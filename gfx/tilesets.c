#include "../constants.h"
#include "tilesets.h"

// tilecoll: MACRO
// ; used in data/tilesets/*_collision.asm
// 	db COLL_\1, COLL_\2, COLL_\3, COLL_\4
// ENDM
#define tilecoll(_x, _y, _z, _w) COLL_##_x, COLL_##_y, COLL_##_z, COLL_##_w, 

// SECTION "Tileset Data 1", ROMX

const char TilesetKantoGFX[] = "gfx/tilesets/kanto.png";
const char TilesetKantoMeta[] = "data/tilesets/kanto_metatiles.bin";
const uint8_t TilesetKantoColl[] = {
#include "../data/tilesets/kanto_collision.h"
};

#define Tileset0GFX TilesetJohtoGFX
const char TilesetJohtoGFX[] = "gfx/tilesets/johto.png";

#define Tileset0Meta TilesetJohtoMeta
const char TilesetJohtoMeta[] = "data/tilesets/johto_metatiles.bin";

#define Tileset0Coll TilesetJohtoColl
const uint8_t TilesetJohtoColl[] = {
#include "../data/tilesets/johto_collision.h"
};

const char TilesetIcePathGFX[] = "gfx/tilesets/ice_path.png";
const char TilesetIcePathMeta[] = "data/tilesets/ice_path_metatiles.bin";
const uint8_t TilesetIcePathColl[] = {
#include "../data/tilesets/ice_path_collision.h"
};

const char TilesetPlayersRoomGFX[] = "gfx/tilesets/players_room.png";
const char TilesetPlayersRoomMeta[] = "data/tilesets/players_room_metatiles.bin";
const uint8_t TilesetPlayersRoomColl[] = {
#include "../data/tilesets/players_room_collision.h"
};


// SECTION "Tileset Data 2", ROMX

const char TilesetPokecenterGFX[] = "gfx/tilesets/pokecenter.png";
const char TilesetPokecenterMeta[] = "data/tilesets/pokecenter_metatiles.bin";
const uint8_t TilesetPokecenterColl[] = {
#include "../data/tilesets/pokecenter_collision.h"
};

const char TilesetPortGFX[] = "gfx/tilesets/port.png";
const char TilesetPortMeta[] = "data/tilesets/port_metatiles.bin";
const uint8_t TilesetPortColl[] = {
// #include "../data/tilesets/port_collision.h"
};

const char TilesetPlayersHouseGFX[] = "gfx/tilesets/players_house.png";
const char TilesetPlayersHouseMeta[] = "data/tilesets/players_house_metatiles.bin";
const uint8_t TilesetPlayersHouseColl[] = {
// #include "data/tilesets/players_house_collision.h"
};

const char TilesetMansionGFX[] = "gfx/tilesets/mansion.png";
const char TilesetMansionMeta[] = "data/tilesets/mansion_metatiles.bin";
const uint8_t TilesetMansionColl[] = {
// #include "data/tilesets/mansion_collision.h"
};

const char TilesetCaveGFX[] = "gfx/tilesets/cave.png";
#define TilesetDarkCaveMeta TilesetCaveMeta
const char TilesetCaveMeta[] = "data/tilesets/cave_metatiles.bin";
#define TilesetDarkCaveColl TilesetCaveColl
const uint8_t TilesetCaveColl[] = {
// #include "data/tilesets/cave_collision.h"
};

// SECTION "Tileset Data 3", ROMX

const char TilesetTowerGFX[] = "gfx/tilesets/tower.png";
const char TilesetTowerMeta[] = "data/tilesets/tower_metatiles.bin";
const uint8_t TilesetTowerColl[] = {
// #include "data/tilesets/tower_collision.h"
};

const char TilesetLabGFX[] = "gfx/tilesets/lab.png";
const char TilesetLabMeta[] = "data/tilesets/lab_metatiles.bin";
const uint8_t TilesetLabColl[] = {
// #include "data/tilesets/lab_collision.h"
};

const char TilesetMartGFX[] = "gfx/tilesets/mart.png";
const char TilesetMartMeta[] = "data/tilesets/mart_metatiles.bin";
const uint8_t TilesetMartColl[] = {
#include "../data/tilesets/mart_collision.h"
};

const char TilesetGameCornerGFX[] = "gfx/tilesets/game_corner.png";
const char TilesetGameCornerMeta[] = "data/tilesets/game_corner_metatiles.bin";
const uint8_t TilesetGameCornerColl[] = {
// #include "data/tilesets/game_corner_collision.h"
};

const char TilesetTrainStationGFX[] = "gfx/tilesets/train_station.png";
const char TilesetTrainStationMeta[] = "data/tilesets/train_station_metatiles.bin";
const uint8_t TilesetTrainStationColl[] = {
// #include "data/tilesets/train_station_collision.h"
};
const char TilesetForestMeta[] = "data/tilesets/forest_metatiles.bin";


// SECTION "Tileset Data 4", ROMX

const char TilesetEliteFourRoomGFX[] = "gfx/tilesets/elite_four_room.png";
const char TilesetEliteFourRoomMeta[] = "data/tilesets/elite_four_room_metatiles.bin";
const uint8_t TilesetEliteFourRoomColl[] = {
// #include "data/tilesets/elite_four_room_collision.h"
};

const char TilesetParkGFX[] = "gfx/tilesets/park.png";
const char TilesetParkMeta[] = "data/tilesets/park_metatiles.bin";
const uint8_t TilesetParkColl[] = {
// #include "data/tilesets/park_collision.h"
};

const char TilesetRadioTowerGFX[] = "gfx/tilesets/radio_tower.png";
const char TilesetRadioTowerMeta[] = "data/tilesets/radio_tower_metatiles.bin";
const uint8_t TilesetRadioTowerColl[] = {
// #include "data/tilesets/radio_tower_collision.h"
};

const char TilesetUndergroundGFX[] = "gfx/tilesets/underground.png";
const char TilesetUndergroundMeta[] = "data/tilesets/underground_metatiles.bin";
const uint8_t TilesetUndergroundColl[] = {
// #include "data/tilesets/underground_collision.h"
};

const char TilesetDarkCaveGFX[] = "gfx/tilesets/dark_cave.png";

// UnusedTilesetJohtoMeta:: ; unreferenced
// INCBIN "data/tilesets/unused_johto_metatiles.bin"

// UnusedTilesetJohtoColl:: ; unreferenced
// INCLUDE "data/tilesets/unused_johto_collision.asm"


// SECTION "Tileset Data 5", ROMX

const char TilesetPokeComCenterGFX[] = "gfx/tilesets/pokecom_center.png";
const char TilesetPokeComCenterMeta[] = "data/tilesets/pokecom_center_metatiles.bin";
const uint8_t TilesetPokeComCenterColl[] = {
#include "../data/tilesets/pokecom_center_collision.h"
};

const char TilesetBattleTowerInsideGFX[] = "gfx/tilesets/battle_tower_inside.png";
const char TilesetBattleTowerInsideMeta[] = "data/tilesets/battle_tower_inside_metatiles.bin";
const uint8_t TilesetBattleTowerInsideColl[] = {
// #include "data/tilesets/battle_tower_inside_collision.h"
};

const char TilesetGateGFX[] = "gfx/tilesets/gate.png";
const char TilesetGateMeta[] = "data/tilesets/gate_metatiles.bin";
const uint8_t TilesetGateColl[] = {
// #include "data/tilesets/gate_collision.h"
};

#define TilesetBattleTowerOutsideGFX TilesetJohtoModernGFX
const char TilesetJohtoModernGFX[] = "gfx/tilesets/johto_modern.png";
const char TilesetJohtoModernMeta[] = "data/tilesets/johto_modern_metatiles.bin";
const uint8_t TilesetJohtoModernColl[] = {
// #include "data/tilesets/johto_modern_collision.h"
};

const char TilesetTraditionalHouseGFX[] = "gfx/tilesets/traditional_house.png";
const char TilesetTraditionalHouseMeta[] = "data/tilesets/traditional_house_metatiles.bin";
const uint8_t TilesetTraditionalHouseColl[] = {
// #include "data/tilesets/traditional_house_collision.h"
};


// SECTION "Tileset Data 6", ROMX

const char TilesetForestGFX[] = "gfx/tilesets/forest.png";

const char TilesetChampionsRoomGFX[] = "gfx/tilesets/champions_room.png";
const char TilesetChampionsRoomMeta[] = "data/tilesets/champions_room_metatiles.bin";
const uint8_t TilesetChampionsRoomColl[] = {
// #include "data/tilesets/champions_room_collision.h"
};

const char TilesetHouseGFX[] = "gfx/tilesets/house.png";
const char TilesetHouseMeta[] = "data/tilesets/house_metatiles.bin";
const uint8_t TilesetHouseColl[] = {
#include "../data/tilesets/house_collision.h"
};

const char TilesetLighthouseGFX[] = "gfx/tilesets/lighthouse.png";
const char TilesetLighthouseMeta[] = "data/tilesets/lighthouse_metatiles.bin";
const uint8_t TilesetLighthouseColl[] = {
// #include "data/tilesets/lighthouse_collision.h"
};
const uint8_t TilesetForestColl[] = {
// #include "data/tilesets/forest_collision.h"
};

const char TilesetFacilityGFX[] = "gfx/tilesets/facility.png";
const char TilesetFacilityMeta[] = "data/tilesets/facility_metatiles.bin";
const uint8_t TilesetFacilityColl[] = {
// #include "data/tilesets/facility_collision.h"
};
const char TilesetBattleTowerOutsideMeta[] = "data/tilesets/battle_tower_outside_metatiles.bin";
const uint8_t TilesetBattleTowerOutsideColl[] = {
// #include "data/tilesets/battle_tower_outside_collision.h"
};
const char TilesetBetaWordRoomMeta[] = "data/tilesets/beta_word_room_metatiles.bin";

// TilesetAerodactylWordRoomColl TilesetBetaWordRoomColl::
// TilesetHoOhWordRoomColl::
// TilesetKabutoWordRoomColl::
// TilesetOmanyteWordRoomColl::
const uint8_t TilesetBetaWordRoomColl[] = {
// #include "data/tilesets/beta_word_room_collision.h"
};


// SECTION "Tileset Data 7", ROMX

#define TilesetAerodactylWordRoomGFX TilesetRuinsOfAlphGFX
#define TilesetBetaWordRoomGFX TilesetRuinsOfAlphGFX
#define TilesetHoOhWordRoomGFX TilesetRuinsOfAlphGFX
#define TilesetKabutoWordRoomGFX TilesetRuinsOfAlphGFX
#define TilesetOmanyteWordRoomGFX TilesetRuinsOfAlphGFX
const char TilesetRuinsOfAlphGFX[] = "gfx/tilesets/ruins_of_alph.png";
const char TilesetRuinsOfAlphMeta[] = "data/tilesets/ruins_of_alph_metatiles.bin";
const uint8_t TilesetRuinsOfAlphColl[] = {
// #include "data/tilesets/ruins_of_alph_collision.h"
};


// SECTION "Tileset Data 8", ROMX
const char TilesetHoOhWordRoomMeta[] = "data/tilesets/ho_oh_word_room_metatiles.bin";
const char TilesetKabutoWordRoomMeta[] = "data/tilesets/kabuto_word_room_metatiles.bin";
const char TilesetOmanyteWordRoomMeta[] = "data/tilesets/omanyte_word_room_metatiles.bin";
const char TilesetAerodactylWordRoomMeta[] = "data/tilesets/aerodactyl_word_room_metatiles.bin";
