#include "../constants.h"
#include "../util/scripting.h"
#include "GoldenrodBikeShop.h"
//// EVENTS
enum {
    GOLDENRODBIKESHOP_CLERK = 2,
};

const Script_fn_t GoldenrodBikeShop_SceneScripts[] = {
    0,
};

const struct MapCallback GoldenrodBikeShop_MapCallbacks[] = {
    0,
};

const struct MapScripts GoldenrodBikeShop_MapScripts = {
    .scene_script_count = 0, // lengthof(GoldenrodBikeShop_SceneScripts),
    .scene_scripts = GoldenrodBikeShop_SceneScripts,

    .callback_count = 0, // lengthof(GoldenrodBikeShop_MapCallbacks),
    .callbacks = GoldenrodBikeShop_MapCallbacks,
};

static const struct CoordEvent GoldenrodBikeShop_CoordEvents[] = {
    0,
};

static const struct BGEvent GoldenrodBikeShop_BGEvents[] = {
    bg_event(1, 2, BGEVENT_READ, &GoldenrodBikeShopBicycle),
    bg_event(0, 3, BGEVENT_READ, &GoldenrodBikeShopBicycle),
    bg_event(1, 3, BGEVENT_READ, &GoldenrodBikeShopBicycle),
    bg_event(0, 5, BGEVENT_READ, &GoldenrodBikeShopBicycle),
    bg_event(1, 5, BGEVENT_READ, &GoldenrodBikeShopBicycle),
    bg_event(0, 6, BGEVENT_READ, &GoldenrodBikeShopBicycle),
    bg_event(1, 6, BGEVENT_READ, &GoldenrodBikeShopBicycle),
    bg_event(6, 6, BGEVENT_READ, &GoldenrodBikeShopBicycle),
    bg_event(7, 6, BGEVENT_READ, &GoldenrodBikeShopBicycle),
};

static const struct WarpEventData GoldenrodBikeShop_WarpEvents[] = {
    warp_event(2, 7, GOLDENROD_CITY, 2),
    warp_event(3, 7, GOLDENROD_CITY, 2),
};

static const struct ObjEvent GoldenrodBikeShop_ObjectEvents[] = {
    object_event(7, 2, SPRITE_CLERK, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &GoldenrodBikeShopClerkScript, -1),
};

const struct MapEvents GoldenrodBikeShop_MapEvents = {
    .warp_event_count = lengthof(GoldenrodBikeShop_WarpEvents),
    .warp_events = GoldenrodBikeShop_WarpEvents,

    .coord_event_count = 0, // lengthof(GoldenrodBikeShop_CoordEvents),
    .coord_events = GoldenrodBikeShop_CoordEvents,

    .bg_event_count = lengthof(GoldenrodBikeShop_BGEvents),
    .bg_events = GoldenrodBikeShop_BGEvents,

    .obj_event_count = lengthof(GoldenrodBikeShop_ObjectEvents),
    .obj_events = GoldenrodBikeShop_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "GoldenrodBikeShop.h"

bool GoldenrodBikeShop_MapScripts_DummyScene(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool GoldenrodBikeShopClerkScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_BICYCLE)
    iftrue(GotBicycle)
    writetext(GoldenrodBikeShopClerkIntroText)
    yesorno
    iffalse(Refused)
    writetext(GoldenrodBikeShopClerkAgreedText)
    promptbutton
    waitsfx
    giveitem(BICYCLE, 1)
    writetext(BorrowedABicycleText)
    playsound(SFX_KEY_ITEM)
    waitsfx
    itemnotify
    setflag(ENGINE_BIKE_SHOP_CALL_ENABLED)
    setevent(EVENT_GOT_BICYCLE)
GotBicycle:
    writetext(GoldenrodBikeShopClerkFirstRateBikesText)
    waitbutton
    closetext
    s_end
Refused:
    writetext(GoldenrodBikeShopClerkRefusedText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool GoldenrodBikeShopJustReleasedCompactBike(script_s* s) {
    SCRIPT_BEGIN
    jumptext(GoldenrodBikeShopJustReleasedCompactBikeText)
    SCRIPT_END
}
bool GoldenrodBikeShopBicycle(script_s* s) {
    SCRIPT_BEGIN
    jumptext(GoldenrodBikeShopBicycleText)
    SCRIPT_END
}
const txt_cmd_s GoldenrodBikeShopClerkIntroText[] = {
    text_start("…sigh… I moved"
        t_line "here, but I can't"
        t_para "sell my BICYCLES."
        t_line "Why is that?"
        t_para "Could you ride a"
        t_line "BICYCLE and adver-"
        t_cont "tise for me?"
        t_done )
};
const txt_cmd_s GoldenrodBikeShopClerkAgreedText[] = {
    text_start("Really? Great!"
        t_para "Give me your name"
        t_line "and phone number,"
        t_para "and I'll loan you"
        t_line "a BICYCLE."
        t_done )
};
const txt_cmd_s BorrowedABicycleText[] = {
    text_start("<PLAYER> borrowed a"
        t_line "BICYCLE."
        t_done )
};
const txt_cmd_s GoldenrodBikeShopClerkFirstRateBikesText[] = {
    text_start("My BICYCLES are"
        t_line "first-rate! You"
        t_para "can ride them"
        t_line "anywhere."
        t_done )
};
const txt_cmd_s GoldenrodBikeShopClerkRefusedText[] = {
    text_start("…sigh… Oh, for"
        t_line "the kindness of"
        t_cont "people…"
        t_done )
};
const txt_cmd_s GoldenrodBikeShopJustReleasedCompactBikeText[] = {
    text_start("Just released!"
        t_para "First-rate compact"
        t_line "BICYCLES!"
        t_done )
};
const txt_cmd_s GoldenrodBikeShopBicycleText[] = {
    text_start("It's a shiny new"
        t_line "BICYCLE!"
        t_done )
    //db(0, 0) // filler
};
