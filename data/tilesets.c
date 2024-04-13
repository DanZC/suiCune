#include "../constants.h"
#include "../gfx/tilesets.h"
#include "../gfx/tileset_palette_maps.h"
#include "../engine/tilesets/tileset_anims.h"
#include "tilesets.h"

#define tileset(_x) {.gfxPath=_x##GFX, .metaPath=_x##Meta, .coll=_x##Coll, .anim=_x##Anim, .palMap=_x##PalMap}

const struct Tileset Tilesets[] = {
    [0]                             = tileset(Tileset0),
    [TILESET_JOHTO]                 = tileset(TilesetJohto),
    [TILESET_JOHTO_MODERN]          = tileset(TilesetJohtoModern),
    [TILESET_KANTO]                 = tileset(TilesetKanto),
    [TILESET_BATTLE_TOWER_OUTSIDE]  = tileset(TilesetBattleTowerOutside),
    [TILESET_HOUSE]                 = tileset(TilesetHouse),
    [TILESET_PLAYERS_HOUSE]         = tileset(TilesetPlayersHouse),
    [TILESET_POKECENTER]            = tileset(TilesetPokecenter),
    [TILESET_GATE]                  = tileset(TilesetGate),
    [TILESET_PORT]                  = tileset(TilesetPort),
    [TILESET_LAB]                   = tileset(TilesetLab),
    [TILESET_FACILITY]              = tileset(TilesetFacility),
    [TILESET_MART]                  = tileset(TilesetMart),
    [TILESET_MANSION]               = tileset(TilesetMansion),
    [TILESET_GAME_CORNER]           = tileset(TilesetGameCorner),
    [TILESET_ELITE_FOUR_ROOM]       = tileset(TilesetEliteFourRoom),
    [TILESET_TRADITIONAL_HOUSE]     = tileset(TilesetTraditionalHouse),
    [TILESET_TRAIN_STATION]         = tileset(TilesetTrainStation),
    [TILESET_CHAMPIONS_ROOM]        = tileset(TilesetChampionsRoom),
    [TILESET_LIGHTHOUSE]            = tileset(TilesetLighthouse),
    [TILESET_PLAYERS_ROOM]          = tileset(TilesetPlayersRoom),
    [TILESET_POKECOM_CENTER]        = tileset(TilesetPlayersRoom),
    [TILESET_BATTLE_TOWER_INSIDE]   = tileset(TilesetBattleTowerInside),
    [TILESET_TOWER]                 = tileset(TilesetTower),
    [TILESET_CAVE]                  = tileset(TilesetCave),
    [TILESET_PARK]                  = tileset(TilesetPark),
    [TILESET_RUINS_OF_ALPH]         = tileset(TilesetRuinsOfAlph),
    [TILESET_RADIO_TOWER]           = tileset(TilesetRadioTower),
    [TILESET_UNDERGROUND]           = tileset(TilesetUnderground),
    [TILESET_ICE_PATH]              = tileset(TilesetIcePath),
    [TILESET_DARK_CAVE]             = tileset(TilesetDarkCave),
    [TILESET_FOREST]                = tileset(TilesetForest),
    [TILESET_BETA_WORD_ROOM]        = tileset(TilesetBetaWordRoom),
    [TILESET_HO_OH_WORD_ROOM]       = tileset(TilesetHoOhWordRoom),
    [TILESET_KABUTO_WORD_ROOM]      = tileset(TilesetKabutoWordRoom),
    [TILESET_OMANYTE_WORD_ROOM]     = tileset(TilesetOmanyteWordRoom),
    [TILESET_AERODACTYL_WORD_ROOM]  = tileset(TilesetAerodactylWordRoom),
};
