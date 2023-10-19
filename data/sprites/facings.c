#include "../../constants.h"
#include "facings.h"

#define FacingStepDown2 FacingStepDown0
#define FacingWeirdTree0 FacingStepDown0
#define FacingWeirdTree2 FacingStepDown0
const struct Facing FacingStepDown0 = {
    .count = 4, .data = (struct FacingData[]){
        {0,  0, 0, 0x00},
        {0,  8, 0, 0x01},
        {8,  0, RELATIVE_ATTRIBUTES, 0x02},
        {8,  8, RELATIVE_ATTRIBUTES, 0x03},
    }
};

const struct Facing FacingStepDown1 = { // walking down 1
    .count = 4, .data = (struct FacingData[]){
        {0,  0, 0, 0x80},
        {0,  8, 0, 0x81},
        {8,  0, RELATIVE_ATTRIBUTES, 0x82},
        {8,  8, RELATIVE_ATTRIBUTES, 0x83},
    },
};

const struct Facing FacingStepDown3 = { // walking down 2
    .count = 4, .data = (struct FacingData[]){
        {0,  0, X_FLIP, 0x80},
        {0,  8, X_FLIP, 0x81},
        {8,  0, RELATIVE_ATTRIBUTES | X_FLIP, 0x82},
        {8,  8, RELATIVE_ATTRIBUTES | X_FLIP, 0x83},
    },
};

#define FacingStepUp2 FacingStepUp0
const struct Facing FacingStepUp0 = {
    .count = 4, .data = (struct FacingData[]){
        {0,  0, 0, 0x04},
        {0,  8, 0, 0x05},
        {8,  0, RELATIVE_ATTRIBUTES, 0x06},
        {8,  8, RELATIVE_ATTRIBUTES, 0x07},
    }
};

const struct Facing FacingStepUp1 = {
    .count = 4, .data = (struct FacingData[]){
        {0,  0, 0, 0x84},
        {0,  8, 0, 0x85},
        {8,  0, RELATIVE_ATTRIBUTES, 0x86},
        {8,  8, RELATIVE_ATTRIBUTES, 0x87},
    }
};

const struct Facing FacingStepUp3 = {
    .count = 4, .data = (struct FacingData[]){
        {0,  0, X_FLIP, 0x84},
        {0,  8, X_FLIP, 0x85},
        {8,  0, RELATIVE_ATTRIBUTES | X_FLIP, 0x86},
        {8,  8, RELATIVE_ATTRIBUTES | X_FLIP, 0x87},
    }
};

#define FacingStepLeft0 FacingStepLeft2
const struct Facing FacingStepLeft2 = { // standing left
	.count = 4, .data = (struct FacingData[]){
        {0,  0, 0, 0x08},
        {0,  8, 0, 0x09},
        {8,  0, RELATIVE_ATTRIBUTES, 0x0a},
        {8,  8, RELATIVE_ATTRIBUTES, 0x0b},
    },
};

#define FacingStepRight0 FacingStepRight2
const struct Facing FacingStepRight2 = { // standing right
	.count = 4, .data = (struct FacingData[]){
        {0,  8, X_FLIP, 0x08},
        {0,  0, X_FLIP, 0x09},
        {8,  8, RELATIVE_ATTRIBUTES | X_FLIP, 0x0a},
        {8,  0, RELATIVE_ATTRIBUTES | X_FLIP, 0x0b},
    },
};

#define FacingStepLeft1 FacingStepLeft3
const struct Facing FacingStepLeft3 = { // walking left
	.count = 4, .data = (struct FacingData[]){
        { 0,  0, 0, 0x88},
        { 0,  8, 0, 0x89},
        { 8,  0, RELATIVE_ATTRIBUTES, 0x8a},
        { 8,  8, RELATIVE_ATTRIBUTES, 0x8b},
    },
};

#define FacingStepRight1 FacingStepRight3
const struct Facing FacingStepRight3 = { // walking right
	.count = 4, .data = (struct FacingData[]){
        { 0,  8, X_FLIP, 0x88},
        { 0,  0, X_FLIP, 0x89},
        { 8,  8, RELATIVE_ATTRIBUTES | X_FLIP, 0x8a},
        { 8,  0, RELATIVE_ATTRIBUTES | X_FLIP, 0x8b},
    },
};

const struct Facing FacingFishDown = { // fishing down
	.count = 5, .data = (struct FacingData[]){
        { 0,  0, 0, 0x00},
        { 0,  8, 0, 0x01},
        { 8,  0, RELATIVE_ATTRIBUTES, 0x02},
        { 8,  8, RELATIVE_ATTRIBUTES, 0x03},
        {16,  0, ABSOLUTE_TILE_ID, 0xfc},
    },
};

const struct Facing FacingFishUp = { // fishing up
	.count = 5, .data = (struct FacingData[]){
        { 0,  0, 0, 0x04},
        { 0,  8, 0, 0x05},
        { 8,  0, RELATIVE_ATTRIBUTES, 0x06},
        { 8,  8, RELATIVE_ATTRIBUTES, 0x07},
        {-8,  0, ABSOLUTE_TILE_ID, 0xfc},
    },
};

const struct Facing FacingFishLeft = { // fishing left
	.count = 5, .data = (struct FacingData[]){
        { 0,  0, 0, 0x08},
        { 0,  8, 0, 0x09},
        { 8,  0, RELATIVE_ATTRIBUTES, 0x0a},
        { 8,  8, RELATIVE_ATTRIBUTES, 0x0b},
        { 5, -8, ABSOLUTE_TILE_ID | X_FLIP, 0xfd},
    },
};

const struct Facing FacingFishRight = { // fishing right
	.count = 5, .data = (struct FacingData[]){
        { 0,  8, X_FLIP, 0x08},
        { 0,  0, X_FLIP, 0x09},
        { 8,  8, RELATIVE_ATTRIBUTES | X_FLIP, 0x0a},
        { 8,  0, RELATIVE_ATTRIBUTES | X_FLIP, 0x0b},
        { 5, 16, ABSOLUTE_TILE_ID, 0xfd},
    },
};

const struct Facing FacingEmote = { // emote
	.count = 4, .data = (struct FacingData[]){
        { 0,  0, ABSOLUTE_TILE_ID, 0xf8},
        { 0,  8, ABSOLUTE_TILE_ID, 0xf9},
        { 8,  0, ABSOLUTE_TILE_ID, 0xfa},
        { 8,  8, ABSOLUTE_TILE_ID, 0xfb},
    },
};

const struct Facing FacingShadow = { // shadow
	.count=2, .data = (struct FacingData[]){
        {0,  0, ABSOLUTE_TILE_ID, 0xfc},
        {0,  8, ABSOLUTE_TILE_ID | X_FLIP, 0xfc},
    },
};

const struct Facing FacingBigDollSymmetric = { // big snorlax or lapras doll
	.count = 16, .data = (struct FacingData[]){
        { 0,  0, 0, 0x00},
        { 0,  8, 0, 0x01},
        { 8,  0, 0, 0x02},
        { 8,  8, 0, 0x03},
        {16,  0, 0, 0x04},
        {16,  8, 0, 0x05},
        {24,  0, 0, 0x06},
        {24,  8, 0, 0x07},
        { 0, 24, X_FLIP, 0x00},
        { 0, 16, X_FLIP, 0x01},
        { 8, 24, X_FLIP, 0x02},
        { 8, 16, X_FLIP, 0x03},
        {16, 24, X_FLIP, 0x04},
        {16, 16, X_FLIP, 0x05},
        {24, 24, X_FLIP, 0x06},
        {24, 16, X_FLIP, 0x07},
    },
};

const struct Facing FacingWeirdTree1 = {
	.count = 4, .data = (struct FacingData[]){
        {0,  0, 0, 0x04},
        {0,  8, 0, 0x05},
        {8,  0, 0, 0x06},
        {8,  8, 0, 0x07},
    },
};

const struct Facing FacingWeirdTree3 = {
	.count = 4, .data = (struct FacingData[]){
        {0,  8, X_FLIP, 0x04},
        {0,  0, X_FLIP, 0x05},
        {8,  8, X_FLIP, 0x06},
        {8,  0, X_FLIP, 0x07},
    }
};

const struct Facing FacingBigDollAsymmetric = { // big doll other than snorlax or lapras
    .count = 14, .data = (struct FacingData[]){
        { 0,  0, 0, 0x00},
        { 0,  8, 0, 0x01},
        { 8,  0, 0, 0x04},
        { 8,  8, 0, 0x05},
        {16,  8, 0, 0x07},
        {24,  8, 0, 0x0a},
        { 0, 24, 0, 0x03},
        { 0, 16, 0, 0x02},
        { 8, 24, X_FLIP, 0x02},
        { 8, 16, 0, 0x06},
        {16, 24, 0, 0x09},
        {16, 16, 0, 0x08},
        {24, 24, X_FLIP, 0x04},
        {24, 16, 0, 0x0b},
    },
};

const struct Facing FacingBoulderDust1 = { // boulder dust 1
	.count = 4, .data = (struct FacingData[]){
        {0,  0, ABSOLUTE_TILE_ID, 0xfe},
        {0,  8, ABSOLUTE_TILE_ID, 0xfe},
        {8,  0, ABSOLUTE_TILE_ID, 0xfe},
        {8,  8, ABSOLUTE_TILE_ID, 0xfe},
    }
};

const struct Facing FacingBoulderDust2 = { // boulder dust 2
    .count = 4, .data = (struct FacingData[]){
        {0,  0, ABSOLUTE_TILE_ID, 0xff},
        {0,  8, ABSOLUTE_TILE_ID, 0xff},
        {8,  0, ABSOLUTE_TILE_ID, 0xff},
        {8,  8, ABSOLUTE_TILE_ID, 0xff},
    }
};

const struct Facing FacingGrass1 = {
    .count = 2, .data = (struct FacingData[]){
        {8,  0, ABSOLUTE_TILE_ID, 0xfe},
        {8,  8, ABSOLUTE_TILE_ID | X_FLIP, 0xfe},
    }
};

const struct Facing FacingGrass2 = {
	.count = 2, .data = (struct FacingData[]){
        {9, -1, ABSOLUTE_TILE_ID, 0xfe},
        {9,  9, ABSOLUTE_TILE_ID | X_FLIP, 0xfe},
    }
};

const struct Facing* Facings[] = {
// entries correspond to FACING_* constants (see constants/map_object_constants.asm)
    [FACING_STEP_DOWN_0] = &FacingStepDown0,
    [FACING_STEP_DOWN_1] = &FacingStepDown1,
    [FACING_STEP_DOWN_2] = &FacingStepDown2,
    [FACING_STEP_DOWN_3] = &FacingStepDown3,
    [FACING_STEP_UP_0] = &FacingStepUp0,
    [FACING_STEP_UP_1] = &FacingStepUp1,
    [FACING_STEP_UP_2] = &FacingStepUp2,
    [FACING_STEP_UP_3] = &FacingStepUp3,
    [FACING_STEP_LEFT_0] = &FacingStepLeft0,
    [FACING_STEP_LEFT_1] = &FacingStepLeft1,
    [FACING_STEP_LEFT_2] = &FacingStepLeft2,
    [FACING_STEP_LEFT_3] = &FacingStepLeft3,
    [FACING_STEP_RIGHT_0] = &FacingStepRight0,
    [FACING_STEP_RIGHT_1] = &FacingStepRight1,
    [FACING_STEP_RIGHT_2] = &FacingStepRight2,
    [FACING_STEP_RIGHT_3] = &FacingStepRight3,
    [FACING_FISH_DOWN] = &FacingFishDown,
    [FACING_FISH_UP] = &FacingFishUp,
    [FACING_FISH_LEFT] = &FacingFishLeft,
    [FACING_FISH_RIGHT] = &FacingFishRight,
    [FACING_EMOTE] = &FacingEmote,
    [FACING_SHADOW] = &FacingShadow,
    [FACING_BIG_DOLL_ASYM] = &FacingBigDollAsymmetric,
    [FACING_BIG_DOLL_SYM] = &FacingBigDollSymmetric,
    [FACING_WEIRD_TREE_0] = &FacingWeirdTree0,
    [FACING_WEIRD_TREE_1] = &FacingWeirdTree1,
    [FACING_WEIRD_TREE_2] = &FacingWeirdTree2,
    [FACING_WEIRD_TREE_3] = &FacingWeirdTree3,
    [FACING_BOULDER_DUST_1] = &FacingBoulderDust1,
    [FACING_BOULDER_DUST_2] = &FacingBoulderDust2,
    [FACING_GRASS_1] = &FacingGrass1,
    [FACING_GRASS_2] = &FacingGrass2,
};