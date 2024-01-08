#include "../../constants.h"
#include "blocks.h"
#include "scripts.h"

#define map_attributes(name, id, block, _connections) const struct MapAttr name##_MapAttributes = {\
    .width = id##_WIDTH, .height = id##_HEIGHT, .borderBlock = block, .blocksPath = name##_Blocks, \
    .events = &name##_MapEvents, .scripts = &name##_MapScripts, .connections={ _connections }}

#define calc_tile_src(_x) ((((_x) + 3) < 0)? -(((_x) + 3) < 0): 0)
#define calc_tile_tgt(_x) ((((_x) + 3) < 0)? 0: ((_x) + 3))
#define calc_map_blk_n(_name, _x) (calc_tile_src(_x))
#define calc_map_blk_s(_name, _x) ((_name##_WIDTH * (_name##_HEIGHT - 3)) + calc_tile_src(_x))
#define calc_map_blk_w(_name, _x) ((_name##_WIDTH * calc_tile_src(_x)) + _name##_WIDTH - 3)
#define calc_map_blk_e(_name, _x) (_name##_WIDTH * calc_tile_src(_x))
#define calc_map_map_n(_name, _x) (calc_tile_tgt(_x))
#define calc_map_map_s(_name, _x) ((_name##_WIDTH + 6) * (_name##_HEIGHT + 3) + calc_tile_tgt(_x))
#define calc_map_map_w(_name, _x) ((_name##_WIDTH + 6) * calc_tile_tgt(_x))
#define calc_map_map_e(_name, _x) ((_name##_WIDTH + 6) * calc_tile_tgt(_x) + _name##_WIDTH + 3)
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
#define calc_map_len(_name, _x) ((_name##_WIDTH + 3 - (_x) > _name##_WIDTH)? _name##_WIDTH: _name##_WIDTH + 3 - (_x))
#define connection_north(name, name2, x) [NORTH_F] = &(struct MapConnectionData){.connectedMapGroup=GROUP_##name2,\
    .connectedMapNumber=MAP_##name2, .connectionStripOffset= calc_map_blk_n(name2, x),\
    .connectionStripLocation = wram_ptr(wOverworldMapBlocks) + calc_map_map_n(name2, x), \
    .connectionStripLength = calc_map_len(name2, x) - calc_tile_src(x), \
    .connectedMapLength = name2##_WIDTH, \
    .connectionStripYOffset = calc_map_y_n(name2, x), \
    .connectionStripXOffset = calc_map_x_v(name2, x), \
    .connectionWindow = wram_ptr(wOverworldMapBlocks) + calc_map_win_n(name2), \
    },
#define connection_south(name, name2, x) [SOUTH_F] = &(struct MapConnectionData){.connectedMapGroup=GROUP_##name2,\
    .connectedMapNumber=MAP_##name2, .connectionStripOffset= calc_map_blk_s(name2, x),\
    .connectionStripLocation = wram_ptr(wOverworldMapBlocks) + calc_map_map_s(name2, x), \
    .connectionStripLength = calc_map_len(name2, x) - calc_tile_src(x), \
    .connectedMapLength = name2##_WIDTH, \
    .connectionStripYOffset = calc_map_y_s(name2, x), \
    .connectionStripXOffset = calc_map_x_v(name2, x), \
    .connectionWindow = wram_ptr(wOverworldMapBlocks) + calc_map_win_s(name2), \
    },
#define connection_west(name, name2, x) [WEST_F] = &(struct MapConnectionData){.connectedMapGroup=GROUP_##name2,\
    .connectedMapNumber=MAP_##name2, .connectionStripOffset=(calc_map_blk_w(name2, x)),\
    .connectionStripLocation = wram_ptr(wOverworldMapBlocks) + calc_map_map_w(name2, x), \
    .connectionStripLength = calc_map_len(name2, x) - calc_tile_src(x), \
    .connectedMapLength = name2##_WIDTH, \
    .connectionStripYOffset = calc_map_y_h(name2, x), \
    .connectionStripXOffset = calc_map_x_w(name2, x), \
    .connectionWindow = wram_ptr(wOverworldMapBlocks) + calc_map_win_w(name2), \
    },
#define connection_east(name, name2, x) [EAST_F] = &(struct MapConnectionData){.connectedMapGroup=GROUP_##name2,\
    .connectedMapNumber=MAP_##name2, .connectionStripOffset=(calc_map_blk_e(name2, x)),\
    .connectionStripLocation = wram_ptr(wOverworldMapBlocks) + calc_map_map_e(name2, x), \
    .connectionStripLength = calc_map_len(name2, x) - calc_tile_src(x), \
    .connectedMapLength = name2##_WIDTH, \
    .connectionStripYOffset = calc_map_y_h(name2, x), \
    .connectionStripXOffset = calc_map_x_e(name2, x), \
    .connectionWindow = wram_ptr(wOverworldMapBlocks) + calc_map_win_e(name2), \
    },

#define connection(dir, name, name2, x) connection_##dir (name, name2, x)

map_attributes(NewBarkTown, NEW_BARK_TOWN, 0x05,
    connection(west, Route29, ROUTE_29, 0)
    connection(east, Route27, ROUTE_27, 0));

map_attributes(Route29, ROUTE_29, 0x05, 
    connection(north, Route46, ROUTE_46, 10)
    connection(west, CherrygroveCity, CHERRYGROVE_CITY, 0)
    connection(east, NewBarkTown, NEW_BARK_TOWN, 0));

map_attributes(Pokecenter2F, POKECENTER_2F, 0x00, 0);
