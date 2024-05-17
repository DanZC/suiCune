#include "../constants.h"
#include "../util/scripting.h"
#include "PokecomCenterAdminOfficeMobile.h"
//// EVENTS
enum {
    POKECOMCENTERADMINOFFICEMOBILE_SCIENTIST1 = 2,
    POKECOMCENTERADMINOFFICEMOBILE_SCIENTIST2,
    POKECOMCENTERADMINOFFICEMOBILE_SCIENTIST3,
};

const Script_fn_t PokecomCenterAdminOfficeMobile_SceneScripts[] = {
    0,
};

const struct MapCallback PokecomCenterAdminOfficeMobile_MapCallbacks[] = {
    0,
};

const struct MapScripts PokecomCenterAdminOfficeMobile_MapScripts = {
    .scene_script_count = 0, // lengthof(PokecomCenterAdminOfficeMobile_SceneScripts),
    .scene_scripts = PokecomCenterAdminOfficeMobile_SceneScripts,

    .callback_count = 0, // lengthof(PokecomCenterAdminOfficeMobile_MapCallbacks),
    .callbacks = PokecomCenterAdminOfficeMobile_MapCallbacks,
};

static const struct CoordEvent PokecomCenterAdminOfficeMobile_CoordEvents[] = {
    0,
};

static const struct BGEvent PokecomCenterAdminOfficeMobile_BGEvents[] = {
    bg_event(6, 26, BGEVENT_UP, &PokecomCenterAdminOfficeMobileComputer1),
    bg_event(6, 28, BGEVENT_UP, &PokecomCenterAdminOfficeMobileComputer2),
    bg_event(3, 26, BGEVENT_UP, &PokecomCenterAdminOfficeMobileComputer3),
};

static const struct WarpEventData PokecomCenterAdminOfficeMobile_WarpEvents[] = {
    warp_event(0, 31, GOLDENROD_POKECENTER_1F, 3),
    warp_event(1, 31, GOLDENROD_POKECENTER_1F, 3),
};

static const struct ObjEvent PokecomCenterAdminOfficeMobile_ObjectEvents[] = {
    object_event(4, 28, SPRITE_SCIENTIST, SPRITEMOVEDATA_WALK_UP_DOWN, 0, 1, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &PokecomCenterAdminOfficeMobileScientist1Script, -1),
    object_event(7, 27, SPRITE_SCIENTIST, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &PokecomCenterAdminOfficeMobileScientist2Script, -1),
    object_event(7, 29, SPRITE_SCIENTIST, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &PokecomCenterAdminOfficeMobileScientist3Script, -1),
};

const struct MapEvents PokecomCenterAdminOfficeMobile_MapEvents = {
    .warp_event_count = lengthof(PokecomCenterAdminOfficeMobile_WarpEvents),
    .warp_events = PokecomCenterAdminOfficeMobile_WarpEvents,

    .coord_event_count = 0, // lengthof(PokecomCenterAdminOfficeMobile_CoordEvents),
    .coord_events = PokecomCenterAdminOfficeMobile_CoordEvents,

    .bg_event_count = lengthof(PokecomCenterAdminOfficeMobile_BGEvents),
    .bg_events = PokecomCenterAdminOfficeMobile_BGEvents,

    .obj_event_count = lengthof(PokecomCenterAdminOfficeMobile_ObjectEvents),
    .obj_events = PokecomCenterAdminOfficeMobile_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "PokecomCenterAdminOfficeMobile.h"

bool PokecomCenterAdminOfficeMobileScientist1Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(PokecomCenterAdminOfficeMobileScientist1Text)
    SCRIPT_END
}
bool PokecomCenterAdminOfficeMobileScientist2Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(PokecomCenterAdminOfficeMobileScientist2Text)
    SCRIPT_END
}
bool PokecomCenterAdminOfficeMobileScientist3Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(PokecomCenterAdminOfficeMobileScientist3Text)
    SCRIPT_END
}

static const struct MenuHeader Computer1MenuHeader = {
    .flags = MENU_BACKUP_TILES, // flags
    .coord = menu_coords(0, 0, 15, 8),
    .data = &(struct MenuData) {
    // MenuData:
        .flags = STATICMENU_CURSOR, // flags
        .verticalMenu = {
            .count = 3, // items
            .options = (const char*[]) {
                "#COM CLUB@", // "#　つうしん　クラブ@" ; # COM CLUB
                "MOBILE CENTER@", // "モバイルセンター@" ; MOBILE CENTER
                "QUIT@", // "やめる@" ; QUIT
            },
        },
    },
    .defaultOption = 1, // default option
};
bool PokecomCenterAdminOfficeMobileComputer1(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(PokecomCenterAdminOfficeMobileComputer1Text)
    waitbutton
loop:
    reloadmappart
    loadmenu(&Computer1MenuHeader)
    verticalmenu
    closewindow
    ifequal(1, PokeComClub)
    ifequal(2, MobileCenter)
    goto Quit;
PokeComClub:
    opentext
    writetext(PokecomCenterAdminOfficeMobileComputer1Text_PokeComClub)
    waitbutton
    goto loop;
MobileCenter:
    opentext
    writetext(PokecomCenterAdminOfficeMobileComputer1Text_MobileCenter)
    waitbutton
    goto loop;
Quit:
    closetext
    s_end
    SCRIPT_END
}

static const struct MenuHeader Computer2MenuHeader = {
    .flags = MENU_BACKUP_TILES, // flags
    .coord = menu_coords(0, 0, 15, 8),
    .data = &(struct MenuData) {
    // MenuData:
        .flags = STATICMENU_CURSOR, // flags
        .verticalMenu = {
            .count = 3, // items
            .options = (const char*[]) {
                "USE PHONE@", //db("でんわ<WO>つかうとき@") // Use phone
                "NO PHONE@", //db("でんわ<GA>つながらないとき@") // Don't use phone
                "QUIT@", //db("やめる@") // QUIT
            },
        },
    },
    .defaultOption = 1, // default option
};
bool PokecomCenterAdminOfficeMobileComputer2(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(PokecomCenterAdminOfficeMobileComputer2Text)
    waitbutton
loop:
    reloadmappart
    loadmenu(&Computer2MenuHeader)
    verticalmenu
    closewindow
    ifequal(1, UsePhone)
    ifequal(2, DontUsePhone)
    goto Quit;
UsePhone:
    opentext
    writetext(PokecomCenterAdminOfficeMobileComputer2Text_UsePhone)
    waitbutton
    goto loop;
DontUsePhone:
    opentext
    writetext(PokecomCenterAdminOfficeMobileComputer2Text_DontUsePhone)
    waitbutton
    goto loop;
Quit:
    closetext
    s_end
    SCRIPT_END
}
bool PokecomCenterAdminOfficeMobileComputer3(script_s* s) {
    SCRIPT_BEGIN
    jumptext(PokecomCenterAdminOfficeMobileComputer3Text)
    SCRIPT_END
}
const txt_cmd_s PokecomCenterAdminOfficeMobileScientist1Text[] = {
    text_start("#COM CENTER and"
        t_line "MOBILE CENTER were"
        t_para "built to satisfy"
        t_line "demands for trades"
        t_para "and battles with"
        t_line "trainers far away"
        t_para "and with total"
        t_line "strangers."
        t_done )
};
const txt_cmd_s PokecomCenterAdminOfficeMobileScientist2Text[] = {
    text_start("When you linked"
        t_line "with someone by"
        t_para "mobile phone for"
        t_line "the first time,"
        t_para "weren't you"
        t_line "impressed?"
        t_para "When my first try"
        t_line "worked, I was so"
        t_para "impressed that I"
        t_line "got the shakes!"
        t_done )
};
const txt_cmd_s PokecomCenterAdminOfficeMobileScientist3Text[] = {
    text_start("They were able to"
        t_line "build this huge"
        t_para "facility thanks to"
        t_line "advances in wire-"
        t_cont "less technology."
        t_done )
};
const txt_cmd_s PokecomCenterAdminOfficeMobileComputer1Text[] = {
    text_start("It's a notice"
        t_line "about where MOBILE"
        t_para "ADAPTERS are to be"
        t_line "used…"
        t_done )
};
const txt_cmd_s PokecomCenterAdminOfficeMobileComputer1Text_PokeComClub[] = {
    text_start("There's a #COM"
        t_line "CLUB upstairs in"
        t_para "any #MON"
        t_line "CENTER."
        t_para "There, you can"
        t_line "battle or trade"
        t_para "with a friend far"
        t_line "away by using a"
        t_cont "MOBILE ADAPTER."
        t_para "To link up, your"
        t_line "friend must have"
        t_para "the same kind of"
        t_line "MOBILE ADAPTER as"
        t_cont "you."
        t_done )
};
const txt_cmd_s PokecomCenterAdminOfficeMobileComputer1Text_MobileCenter[] = {
    text_start("To use the TRADE"
        t_line "CORNER or read the"
        t_para "#MON NEWS, you"
        t_line "need to phone the"
        t_cont "MOBILE CENTER."
        t_para "You must register"
        t_line "at the MOBILE"
        t_para "CENTER before"
        t_line "connecting there."
        t_done )
};
const txt_cmd_s PokecomCenterAdminOfficeMobileComputer2Text[] = {
    text_start("It's a notice"
        t_line "about using the"
        t_cont "phone…"
        t_done )
};
const txt_cmd_s PokecomCenterAdminOfficeMobileComputer2Text_UsePhone[] = {
    text_start("Please ensure that"
        t_line "your phone and"
        t_para "MOBILE ADAPTER are"
        t_line "properly linked."
        t_para "Please make sure"
        t_line "the wireless phone"
        t_cont "signal is strong."
        t_para "Don't touch or"
        t_line "hang up the phone"
        t_cont "while linking."
        t_done )
};
const txt_cmd_s PokecomCenterAdminOfficeMobileComputer2Text_DontUsePhone[] = {
    text_start("If the server is"
        t_line "busy, it may not"
        t_para "be possible to log"
        t_line "on."
        t_para "If so, please call"
        t_line "back later."
        t_para "If you are unable"
        t_line "to log on or don't"
        t_para "understand the"
        t_line "error messages,"
        t_para "call a support"
        t_line "center or read the"
        t_cont "instructions."
        t_done )
};
const txt_cmd_s PokecomCenterAdminOfficeMobileComputer3Text[] = {
    text_start("The ADMINISTRATION"
        t_line "OFFICE received an"
        t_cont "e-mail. It says…"
        t_para "<……> <……> <……>"
        t_para "To the #COM"
        t_line "CENTER staff…"
        t_para "Wireless communi-"
        t_line "cation has enabled"
        t_para "#MON trainers"
        t_line "to interact across"
        t_para "the nation. Let's"
        t_line "keep working for"
        t_para "the day when all"
        t_line "the trainers in"
        t_para "the world can link"
        t_line "without barriers!"
        t_para "<……> <……> <……>"
        t_done )
    //db(0, 0) // filler
};
