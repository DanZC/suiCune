#include "../constants.h"

#define MALE_PLAYER_NAMES "CHRIS", "MAT", "ALLAN", "JON"
#define FEMALE_PLAYER_NAMES "KRIS", "AMANDA", "JUANA", "JODI"
#define NAMES_COUNT(_x) sizeof((const char*[]){_x}) / sizeof(const char*)

const char* MalePlayerNameArray[] = {MALE_PLAYER_NAMES};
const char* FemalePlayerNameArray[] = {FEMALE_PLAYER_NAMES};

static const struct MenuData MaleNames = {
    .flags = STATICMENU_CURSOR | STATICMENU_PLACE_TITLE | STATICMENU_DISABLE_B, // flags
    .verticalMenu = {
        .count = NAMES_COUNT(MALE_PLAYER_NAMES) + 1, // items
        .options = (const char*[]) {
            "NEW NAME@",
            MALE_PLAYER_NAMES
        },
        .title = {
            .indent = 2, // title indent
            .label = " NAME @", // title
        },
    },
};

const struct MenuHeader ChrisNameMenuHeader = {
    .flags = MENU_BACKUP_TILES, // flags
    .coord = menu_coords(0, 0, 10, TEXTBOX_Y - 1),
    // dw .MaleNames
    .data = &MaleNames,
    .defaultOption = 1, // default option
};
    // db 0 ; ????

static const struct MenuData FemaleNames = {
    .flags = STATICMENU_CURSOR | STATICMENU_PLACE_TITLE | STATICMENU_DISABLE_B, // flags
    .verticalMenu = {
        .count = NAMES_COUNT(FEMALE_PLAYER_NAMES) + 1, // items
        .options = (const char*[]) {
            "NEW NAME@",
            FEMALE_PLAYER_NAMES
        },
        .title = {
            .indent = 2, // title indent
            .label = " NAME @", // title
        },
    },
};

const struct MenuHeader KrisNameMenuHeader = {
    .flags = MENU_BACKUP_TILES, // flags
    .coord = menu_coords(0, 0, 10, TEXTBOX_Y - 1),
    // dw .FemaleNames
    .data = &FemaleNames,
    .defaultOption = 1, // default option
};
    // db 0 ; ????
