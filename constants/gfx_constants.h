

#define TILE_WIDTH 8                    // pixels
#define LEN_1BPP_TILE (1 * TILE_WIDTH)  // bytes
#define LEN_2BPP_TILE (2 * TILE_WIDTH)  // bytes

#define NUM_PAL_COLORS 4
#define PAL_COLOR_SIZE 2
#define PALETTE_SIZE (NUM_PAL_COLORS * PAL_COLOR_SIZE)

#define PALRGB_WHITE 0x7fff // palred 31 + palgreen 31 + palblue 31  // 0x7fff

#define SCREEN_WIDTH 20                                // tiles
#define SCREEN_HEIGHT 18                               // tiles
#define SCREEN_WIDTH_PX (SCREEN_WIDTH * TILE_WIDTH)    // pixels
#define SCREEN_HEIGHT_PX (SCREEN_HEIGHT * TILE_WIDTH)  // pixels

#define BG_MAP_WIDTH 32   // tiles
#define BG_MAP_HEIGHT 32  // tiles

#define METATILE_WIDTH 4                                          // tiles
#define SCREEN_META_WIDTH 6                                       // metatiles
#define SCREEN_META_HEIGHT 5                                      // metatiles
#define SURROUNDING_WIDTH (SCREEN_META_WIDTH * METATILE_WIDTH)    // tiles
#define SURROUNDING_HEIGHT (SCREEN_META_HEIGHT * METATILE_WIDTH)  // tiles
#define MAP_CONNECTION_PADDING_WIDTH 3                            // metatiles

#define HP_BAR_LENGTH 6                                  // tiles
#define EXP_BAR_LENGTH 8                                 // tiles
#define HP_BAR_LENGTH_PX (HP_BAR_LENGTH * TILE_WIDTH)    // pixels
#define EXP_BAR_LENGTH_PX (EXP_BAR_LENGTH * TILE_WIDTH)  // pixels

// GetHPPal return values (see home/tilemap.asm)
#define HP_GREEN 0
#define HP_YELLOW 1
#define HP_RED 2

// sprite_oam_struct members (see macros/wram.asm)
enum {
    SPRITEOAMSTRUCT_YCOORD = 0,
    SPRITEOAMSTRUCT_XCOORD,      // 1
    SPRITEOAMSTRUCT_TILE_ID,     // 2
    SPRITEOAMSTRUCT_ATTRIBUTES,  // 3
};
#define SPRITEOAMSTRUCT_LENGTH 4
#define NUM_SPRITE_OAM_STRUCTS 40  // see wVirtualOAM

#define SPRITE_GFX_LIST_CAPACITY 32  // see wUsedSprites

// PokeAnims indexes (see engine/gfx/pic_animation.asm)
enum {
    ANIM_MON_SLOW,
    ANIM_MON_NORMAL,
    ANIM_MON_MENU,
    ANIM_MON_TRADE,
    ANIM_MON_EVOLVE,
    ANIM_MON_HATCH,
    ANIM_MON_HOF,
    ANIM_MON_EGG1,
    ANIM_MON_EGG2,
};
