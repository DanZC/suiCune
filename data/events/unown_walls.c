#include "../../constants.h"

// unownwall: MACRO
// for n, CHARLEN(\1)
// x = CHARSUB(\1, n + 1)
// if x == "-"
// 	db $64
// elif x >= "Y"
// 	db 2 * (x - "Y") + $60
// elif x >= "Q"
// 	db 2 * (x - "Q") + $40
// elif x >= "I"
// 	db 2 * (x - "I") + $20
// else
// 	db 2 * (x - "A")
// endc
// endr
// 	db -1 ; end
// ENDM

const uint8_t* UnownWalls[] = {
// UNOWNWORDS_ESCAPE
    // unownwall "ESCAPE"
    [UNOWNWORDS_ESCAPE] = (uint8_t[]){0x08, 0x44, 0x04, 0x00, 0x2e, 0x08, (uint8_t)-1},
// UNOWNWORDS_LIGHT
    // unownwall "LIGHT"
    [UNOWNWORDS_LIGHT] = (uint8_t[]){0x26, 0x20, 0x0c, 0x0e, 0x46, (uint8_t)-1},
// UNOWNWORDS_WATER
    // unownwall "WATER"
    [UNOWNWORDS_WATER] = (uint8_t[]){0x4c, 0x00, 0x46, 0x08, 0x42, (uint8_t)-1},
// UNOWNWORDS_HO_OH
    // unownwall "HO-OH"
    [UNOWNWORDS_HO_OH] = (uint8_t[]){0x0e, 0x2c, 0x64, 0x2c, 0x0e, (uint8_t)-1},
};

const struct MenuHeader MenuHeaders_UnownWalls[] = {
    [UNOWNWORDS_ESCAPE] = {
        .flags = MENU_BACKUP_TILES, // flags
        .coord = menu_coords(3, 4, 16, 9),
    },
    [UNOWNWORDS_LIGHT] = {
        .flags = MENU_BACKUP_TILES, // flags
        .coord = menu_coords(4, 4, 15, 9),
    },
    [UNOWNWORDS_WATER] = {
        .flags = MENU_BACKUP_TILES, // flags
        .coord = menu_coords(4, 4, 15, 9),
    },
    [UNOWNWORDS_HO_OH] = {
        .flags = MENU_BACKUP_TILES, // flags
        .coord = menu_coords(4, 4, 15, 9),
    }
};