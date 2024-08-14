// overworld_sprite struct members (see data/sprites/sprites.asm)
enum {
    SPRITEDATA_ADDR,
    SPRITEDATA_SIZE = 2,
    SPRITEDATA_BANK,
    SPRITEDATA_TYPE,
    SPRITEDATA_PALETTE,
    NUM_SPRITEDATA_FIELDS,
};

// sprite types
enum {
    WALKING_SPRITE = 1,  // 1
    STANDING_SPRITE, // 2
    STILL_SPRITE,    // 3
};

// sprite palettes
enum {
    PAL_OW_RED,    // 0
    PAL_OW_BLUE,   // 1
    PAL_OW_GREEN,  // 2
    PAL_OW_BROWN,  // 3
    PAL_OW_PINK,   // 4
    PAL_OW_SILVER, // 5
    PAL_OW_TREE,   // 6
    PAL_OW_ROCK,   // 7
};

// object_events set bit 3 so as not to use the sprite's default palette
// MapObjectPals indexes (see gfx/overworld/npc_sprites.pal)
enum {
    PAL_NPC_RED = 8,    // 8
    PAL_NPC_BLUE,   // 9
    PAL_NPC_GREEN,  // a
    PAL_NPC_BROWN,  // b
    PAL_NPC_PINK,   // c
    PAL_NPC_SILVER, // d
    PAL_NPC_TREE,   // e
    PAL_NPC_ROCK,   // f
};
