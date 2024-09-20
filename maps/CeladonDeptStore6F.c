#include "../constants.h"
#include "../util/scripting.h"
#include "CeladonDeptStore6F.h"
#include "CeladonDeptStore1F.h"
//// EVENTS
enum {
    CELADONDEPTSTORE6F_SUPER_NERD = 2,
    CELADONDEPTSTORE6F_YOUNGSTER,
};

const Script_fn_t CeladonDeptStore6F_SceneScripts[] = {
    0,
};

const struct MapCallback CeladonDeptStore6F_MapCallbacks[] = {
    map_callback(MAPCALLBACK_TILES, CeladonDeptStore6F_MapScripts_HideRooftopStairs),
};

const struct MapScripts CeladonDeptStore6F_MapScripts = {
    .scene_script_count = 0, // lengthof(CeladonDeptStore6F_SceneScripts),
    .scene_scripts = CeladonDeptStore6F_SceneScripts,

    .callback_count = lengthof(CeladonDeptStore6F_MapCallbacks),
    .callbacks = CeladonDeptStore6F_MapCallbacks,
};

static const struct CoordEvent CeladonDeptStore6F_CoordEvents[] = {
    0,
};

static const struct BGEvent CeladonDeptStore6F_BGEvents[] = {
    bg_event(14, 0, BGEVENT_READ, &CeladonDeptStore6FDirectory),
    bg_event(3, 0, BGEVENT_READ, &CeladonDeptStore1FElevatorButton),
    bg_event(8, 1, BGEVENT_UP, &CeladonDeptStore6FVendingMachine),
    bg_event(9, 1, BGEVENT_UP, &CeladonDeptStore6FVendingMachine),
    bg_event(10, 1, BGEVENT_UP, &CeladonDeptStore6FVendingMachine),
    bg_event(11, 1, BGEVENT_UP, &CeladonDeptStore6FVendingMachine),
};

static const struct WarpEventData CeladonDeptStore6F_WarpEvents[] = {
    warp_event(15, 0, CELADON_DEPT_STORE_5F, 2),
    warp_event(2, 0, CELADON_DEPT_STORE_ELEVATOR, 1),
};

static const struct ObjEvent CeladonDeptStore6F_ObjectEvents[] = {
    object_event(9, 2, SPRITE_SUPER_NERD, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &CeladonDeptStore6FSuperNerdScript, -1),
    object_event(12, 5, SPRITE_YOUNGSTER, SPRITEMOVEDATA_WANDER, 2, 1, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &CeladonDeptStore6FYoungsterScript, -1),
};

const struct MapEvents CeladonDeptStore6F_MapEvents = {
    .warp_event_count = lengthof(CeladonDeptStore6F_WarpEvents),
    .warp_events = CeladonDeptStore6F_WarpEvents,

    .coord_event_count = 0, // lengthof(CeladonDeptStore6F_CoordEvents),
    .coord_events = CeladonDeptStore6F_CoordEvents,

    .bg_event_count = lengthof(CeladonDeptStore6F_BGEvents),
    .bg_events = CeladonDeptStore6F_BGEvents,

    .obj_event_count = lengthof(CeladonDeptStore6F_ObjectEvents),
    .obj_events = CeladonDeptStore6F_ObjectEvents,
};

//// CODE

#define CELADONDEPTSTORE6F_FRESH_WATER_PRICE 200
#define CELADONDEPTSTORE6F_SODA_POP_PRICE 300
#define CELADONDEPTSTORE6F_LEMONADE_PRICE 350
bool CeladonDeptStore6F_MapScripts_HideRooftopStairs(script_s* s) {
    SCRIPT_BEGIN
    changeblock(12, 0, 0x03) // wall
    s_endcallback
    SCRIPT_END
}
bool CeladonDeptStore6FSuperNerdScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CeladonDeptStore6FSuperNerdText)
    SCRIPT_END
}
bool CeladonDeptStore6FYoungsterScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CeladonDeptStore6FYoungsterText)
    SCRIPT_END
}
static const struct MenuHeader CeladonDeptStore6FVendingMachine_MenuHeader = {
    .flags = MENU_BACKUP_TILES, // flags
    .coord = menu_coords(0, 2, SCREEN_WIDTH - 1, TEXTBOX_Y - 1),
    .data = &(struct MenuData) {
    // MenuData:
        .flags = STATICMENU_CURSOR, // flags
        .verticalMenu = {
            .count = 4, // items
            .options = (const char*[]) {
                "FRESH WATER  ¥" _s(CELADONDEPTSTORE6F_FRESH_WATER_PRICE) "@",
                "SODA POP     ¥" _s(CELADONDEPTSTORE6F_SODA_POP_PRICE) "@",
                "LEMONADE     ¥" _s(CELADONDEPTSTORE6F_LEMONADE_PRICE) "@",
                "CANCEL@",
            },
        },
    },//dw(.MenuData)
    .defaultOption = 1, // default option
};
bool CeladonDeptStore6FVendingMachine(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(CeladonVendingText)
Start:
    special(PlaceMoneyTopRight)
    loadmenu(&CeladonDeptStore6FVendingMachine_MenuHeader)
    verticalmenu
    closewindow
    ifequal(1, FreshWater)
    ifequal(2, SodaPop)
    ifequal(3, Lemonade)
    closetext
    s_end
FreshWater:
    checkmoney(YOUR_MONEY, CELADONDEPTSTORE6F_FRESH_WATER_PRICE)
    ifequal(HAVE_LESS, NotEnoughMoney)
    giveitem(FRESH_WATER, 1)
    iffalse(NotEnoughSpace)
    takemoney(YOUR_MONEY, CELADONDEPTSTORE6F_FRESH_WATER_PRICE)
    getitemname(STRING_BUFFER_3, FRESH_WATER)
    goto VendItem;
SodaPop:
    checkmoney(YOUR_MONEY, CELADONDEPTSTORE6F_SODA_POP_PRICE)
    ifequal(HAVE_LESS, NotEnoughMoney)
    giveitem(SODA_POP, 1)
    iffalse(NotEnoughSpace)
    takemoney(YOUR_MONEY, CELADONDEPTSTORE6F_SODA_POP_PRICE)
    getitemname(STRING_BUFFER_3, SODA_POP)
    goto VendItem;
Lemonade:
    checkmoney(YOUR_MONEY, CELADONDEPTSTORE6F_LEMONADE_PRICE)
    ifequal(HAVE_LESS, NotEnoughMoney)
    giveitem(LEMONADE, 1)
    iffalse(NotEnoughSpace)
    takemoney(YOUR_MONEY, CELADONDEPTSTORE6F_LEMONADE_PRICE)
    getitemname(STRING_BUFFER_3, LEMONADE)
    goto VendItem;
VendItem:
    pause(10)
    playsound(SFX_ENTER_DOOR)
    writetext(CeladonClangText)
    promptbutton
    itemnotify
    goto Start;
NotEnoughMoney:
    writetext(CeladonVendingNoMoneyText)
    waitbutton
    goto Start;
NotEnoughSpace:
    writetext(CeladonVendingNoSpaceText)
    waitbutton
    goto Start;
    SCRIPT_FALLTHROUGH(CeladonDeptStore6FDirectory)
}
bool CeladonDeptStore6FDirectory(script_s* s) {
    SCRIPT_BEGIN
    jumptext(CeladonDeptStore6FDirectoryText)
    SCRIPT_END
}
bool CeladonDeptStore6FElevatorButton(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(ElevatorButtonScript)
    SCRIPT_END
}
const txt_cmd_s CeladonVendingText[] = {
    text_start("A vending machine!"
        t_line "Here's the menu."
        t_done )
};
const txt_cmd_s CeladonClangText[] = {
    text_start("Clang!"
        t_para "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(
        t_line "popped out."
        t_done )
};
const txt_cmd_s CeladonVendingNoMoneyText[] = {
    text_start("Oops, not enough"
        t_line "money…"
        t_done )
};
const txt_cmd_s CeladonVendingNoSpaceText[] = {
    text_start("There's no more"
        t_line "room for stuff…"
        t_done )
};
const txt_cmd_s CeladonDeptStore6FSuperNerdText[] = {
    text_start("A vending machine"
        t_line "with a prize rou-"
        t_cont "lette…"
        t_para "You never see"
        t_line "those anymore."
        t_done )
};
const txt_cmd_s CeladonDeptStore6FYoungsterText[] = {
    text_start("Aww! There's no"
        t_line "games here!"
        t_para "I wanted to play…"
        t_done )
};
const txt_cmd_s CeladonDeptStore6FDirectoryText[] = {
    text_start("6F: ROOFTOP SQUARE"
        t_line "VENDING MACHINES"
        t_done )
    //db(0, 0) // filler
};
