#include "../../constants.h"

// treemon_map: MACRO
// 	map_id \1
// 	db \2 ; treemon set
// ENDM

const struct TreeMonMap TreeMonMaps[] = {
    {MAP_ID(ROUTE_26),                  TREEMON_SET_KANTO},
    {MAP_ID(ROUTE_27),                  TREEMON_SET_KANTO},
    {MAP_ID(ROUTE_28),                  TREEMON_SET_CITY},
    {MAP_ID(ROUTE_29),                  TREEMON_SET_ROUTE},
    {MAP_ID(ROUTE_30),                  TREEMON_SET_ROUTE},
    {MAP_ID(ROUTE_31),                  TREEMON_SET_ROUTE},
    {MAP_ID(ROUTE_32),                  TREEMON_SET_KANTO},
    {MAP_ID(ROUTE_33),                  TREEMON_SET_TOWN},
    {MAP_ID(ROUTE_34),                  TREEMON_SET_ROUTE},
    {MAP_ID(ROUTE_35),                  TREEMON_SET_ROUTE},
    {MAP_ID(ROUTE_36),                  TREEMON_SET_ROUTE},
    {MAP_ID(ROUTE_37),                  TREEMON_SET_ROUTE},
    {MAP_ID(ROUTE_38),                  TREEMON_SET_ROUTE},
    {MAP_ID(ROUTE_39),                  TREEMON_SET_ROUTE},
    {MAP_ID(ROUTE_40),                  TREEMON_SET_CITY},
    {MAP_ID(ROUTE_41),                  TREEMON_SET_CITY},
    {MAP_ID(ROUTE_42),                  TREEMON_SET_TOWN},
    {MAP_ID(ROUTE_43),                  TREEMON_SET_LAKE},
    {MAP_ID(ROUTE_44),                  TREEMON_SET_CANYON},
    {MAP_ID(ROUTE_45),                  TREEMON_SET_CANYON},
    {MAP_ID(ROUTE_46),                  TREEMON_SET_CANYON},
    {MAP_ID(NEW_BARK_TOWN),             TREEMON_SET_CITY},
    {MAP_ID(CHERRYGROVE_CITY),          TREEMON_SET_CITY},
    {MAP_ID(VIOLET_CITY),               TREEMON_SET_CITY},
    {MAP_ID(AZALEA_TOWN),               TREEMON_SET_TOWN},
    {MAP_ID(CIANWOOD_CITY),             TREEMON_SET_CITY},
    {MAP_ID(GOLDENROD_CITY),            TREEMON_SET_CITY},
    {MAP_ID(OLIVINE_CITY),              TREEMON_SET_CITY},
    {MAP_ID(ECRUTEAK_CITY),             TREEMON_SET_CITY},
    {MAP_ID(MAHOGANY_TOWN),             TREEMON_SET_CITY},
    {MAP_ID(LAKE_OF_RAGE),              TREEMON_SET_LAKE},
    {MAP_ID(BLACKTHORN_CITY),           TREEMON_SET_CITY},
    {MAP_ID(SILVER_CAVE_OUTSIDE),       TREEMON_SET_CITY},
    {MAP_ID(ILEX_FOREST),               TREEMON_SET_FOREST},
};
const size_t TreeMonMaps_Size = lengthof(TreeMonMaps);

const struct TreeMonMap RockMonMaps[] = {
    {MAP_ID(CIANWOOD_CITY),             TREEMON_SET_ROCK},
    {MAP_ID(ROUTE_40),                  TREEMON_SET_ROCK},
    {MAP_ID(DARK_CAVE_VIOLET_ENTRANCE), TREEMON_SET_ROCK},
    {MAP_ID(SLOWPOKE_WELL_B1F),         TREEMON_SET_ROCK},
};
const size_t RockMonMaps_Size = lengthof(RockMonMaps);
