#include "../constants.h"
#include "../util/scripting.h"
#include "GoldenrodDeptStore6F.h"
//// EVENTS
enum {
    GOLDENRODDEPTSTORE6F_LASS = 2,
    GOLDENRODDEPTSTORE6F_SUPER_NERD,
};

const Script_fn_t GoldenrodDeptStore6F_SceneScripts[] = {
    0,
};

const struct MapCallback GoldenrodDeptStore6F_MapCallbacks[] = {
    0,
};

const struct MapScripts GoldenrodDeptStore6F_MapScripts = {
    .scene_script_count = 0, // lengthof(GoldenrodDeptStore6F_SceneScripts),
    .scene_scripts = GoldenrodDeptStore6F_SceneScripts,

    .callback_count = 0, // lengthof(GoldenrodDeptStore6F_MapCallbacks),
    .callbacks = GoldenrodDeptStore6F_MapCallbacks,
};

static const struct CoordEvent GoldenrodDeptStore6F_CoordEvents[] = {
    0,
};

static const struct BGEvent GoldenrodDeptStore6F_BGEvents[] = {
    bg_event(14, 0, BGEVENT_READ, &GoldenrodDeptStore6FDirectory),
    bg_event(3, 0, BGEVENT_READ, &GoldenrodDeptStore6FElevatorButton),
    bg_event(8, 1, BGEVENT_UP, &GoldenrodVendingMachine),
    bg_event(9, 1, BGEVENT_UP, &GoldenrodVendingMachine),
    bg_event(10, 1, BGEVENT_UP, &GoldenrodVendingMachine),
    bg_event(11, 1, BGEVENT_UP, &GoldenrodVendingMachine),
};

static const struct WarpEventData GoldenrodDeptStore6F_WarpEvents[] = {
    warp_event(15, 0, GOLDENROD_DEPT_STORE_5F, 2),
    warp_event(2, 0, GOLDENROD_DEPT_STORE_ELEVATOR, 1),
    warp_event(13, 0, GOLDENROD_DEPT_STORE_ROOF, 1),
};

static const struct ObjEvent GoldenrodDeptStore6F_ObjectEvents[] = {
    object_event(10, 2, SPRITE_LASS, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &GoldenrodDeptStore6FLassScript, -1),
    object_event(8, 2, SPRITE_SUPER_NERD, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &GoldenrodDeptStore6FSuperNerdScript, -1),
};

const struct MapEvents GoldenrodDeptStore6F_MapEvents = {
    .warp_event_count = lengthof(GoldenrodDeptStore6F_WarpEvents),
    .warp_events = GoldenrodDeptStore6F_WarpEvents,

    .coord_event_count = 0, // lengthof(GoldenrodDeptStore6F_CoordEvents),
    .coord_events = GoldenrodDeptStore6F_CoordEvents,

    .bg_event_count = lengthof(GoldenrodDeptStore6F_BGEvents),
    .bg_events = GoldenrodDeptStore6F_BGEvents,

    .obj_event_count = lengthof(GoldenrodDeptStore6F_ObjectEvents),
    .obj_events = GoldenrodDeptStore6F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "GoldenrodDeptStore6F.h"

#define GOLDENRODDEPTSTORE6F_FRESH_WATER_PRICE 200
#define GOLDENRODDEPTSTORE6F_SODA_POP_PRICE 300
#define GOLDENRODDEPTSTORE6F_LEMONADE_PRICE 350

static const struct MenuHeader GoldenrodVendingMachine_MenuHeader = {
    .flags = MENU_BACKUP_TILES, // flags
    .coord = menu_coords(0, 2, SCREEN_WIDTH - 1, TEXTBOX_Y - 1),
    .data = &(struct MenuData) {
    // MenuData:
        .flags = STATICMENU_CURSOR, // flags
        .verticalMenu = {
            .count = 4, // items
            .options = (const char*[]) {
                "FRESH WATER  ¥" _s(GOLDENRODDEPTSTORE6F_FRESH_WATER_PRICE) "@",
                "SODA POP     ¥" _s(GOLDENRODDEPTSTORE6F_SODA_POP_PRICE)    "@",
                "LEMONADE     ¥" _s(GOLDENRODDEPTSTORE6F_LEMONADE_PRICE)    "@",
                "CANCEL@",
            },
        },
    },
    .defaultOption = 1, // default option
};

bool GoldenrodVendingMachine(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(GoldenrodVendingText)
Start:
    special(PlaceMoneyTopRight)
    loadmenu(&GoldenrodVendingMachine_MenuHeader)
    verticalmenu
    closewindow
    ifequal(1, FreshWater)
    ifequal(2, SodaPop)
    ifequal(3, Lemonade)
    closetext
    s_end
FreshWater:
    checkmoney(YOUR_MONEY, GOLDENRODDEPTSTORE6F_FRESH_WATER_PRICE)
    ifequal(HAVE_LESS, NotEnoughMoney)
    giveitem(FRESH_WATER, 1)
    iffalse(NotEnoughSpace)
    takemoney(YOUR_MONEY, GOLDENRODDEPTSTORE6F_FRESH_WATER_PRICE)
    getitemname(STRING_BUFFER_3, FRESH_WATER)
    goto VendItem;
SodaPop:
    checkmoney(YOUR_MONEY, GOLDENRODDEPTSTORE6F_SODA_POP_PRICE)
    ifequal(HAVE_LESS, NotEnoughMoney)
    giveitem(SODA_POP, 1)
    iffalse(NotEnoughSpace)
    takemoney(YOUR_MONEY, GOLDENRODDEPTSTORE6F_SODA_POP_PRICE)
    getitemname(STRING_BUFFER_3, SODA_POP)
    goto VendItem;
Lemonade:
    checkmoney(YOUR_MONEY, GOLDENRODDEPTSTORE6F_LEMONADE_PRICE)
    ifequal(HAVE_LESS, NotEnoughMoney)
    giveitem(LEMONADE, 1)
    iffalse(NotEnoughSpace)
    takemoney(YOUR_MONEY, GOLDENRODDEPTSTORE6F_LEMONADE_PRICE)
    getitemname(STRING_BUFFER_3, LEMONADE)
    goto VendItem;
VendItem:
    pause(10)
    playsound(SFX_ENTER_DOOR)
    writetext(GoldenrodClangText)
    promptbutton
    itemnotify
    goto Start;
NotEnoughMoney:
    writetext(GoldenrodVendingNoMoneyText)
    waitbutton
    goto Start;
NotEnoughSpace:
    writetext(GoldenrodVendingNoSpaceText)
    waitbutton
    goto Start;
    SCRIPT_FALLTHROUGH(GoldenrodDeptStore6FLassScript)
}
bool GoldenrodDeptStore6FLassScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(GoldenrodDeptStore6FLassText)
    SCRIPT_END
}
bool GoldenrodDeptStore6FSuperNerdScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(GoldenrodDeptStore6FSuperNerdText)
    SCRIPT_END
}
bool GoldenrodDeptStore6FDirectory(script_s* s) {
    SCRIPT_BEGIN
    jumptext(GoldenrodDeptStore6FDirectoryText)
    SCRIPT_END
}
bool GoldenrodDeptStore6FElevatorButton(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(ElevatorButtonScript)
    SCRIPT_END
}
const txt_cmd_s GoldenrodVendingText[] = {
    text_start("A vending machine!"
        t_line "Here's the menu."
        t_done )
};
const txt_cmd_s GoldenrodClangText[] = {
    text_start("Clang! A can of"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(
        t_cont "popped out!"
        t_done )
};
const txt_cmd_s GoldenrodVendingNoMoneyText[] = {
    text_start("Oops, not enough"
        t_line "money."
        t_done )
};
const txt_cmd_s GoldenrodVendingNoSpaceText[] = {
    text_start("There's no more"
        t_line "room for stuff."
        t_done )
};
const txt_cmd_s GoldenrodDeptStore6FLassText[] = {
    text_start("Do you listen to"
        t_line "LUCKY CHANNEL?"
        t_para "If you want to"
        t_line "win, trade #MON"
        t_para "with as many peo-"
        t_line "ple as possible to"
        t_para "get different ID"
        t_line "numbers."
        t_done )
};
const txt_cmd_s GoldenrodDeptStore6FSuperNerdText[] = {
    text_start("If you're tired,"
        t_line "try the vending"
        t_cont "machine's drinks."
        t_para "Your #MON will"
        t_line "love them too."
        t_done )
};
const txt_cmd_s GoldenrodDeptStore6FDirectoryText[] = {
    text_start("Take a Break from"
        t_line "Shopping!"
        t_para "6F TRANQUIL SQUARE"
        t_done )
    //db(0, 0) // filler
};
