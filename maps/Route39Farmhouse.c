#include "../constants.h"
#include "../util/scripting.h"
#include "Route39Farmhouse.h"
//// EVENTS
enum {
    ROUTE39FARMHOUSE_POKEFAN_M = 2,
    ROUTE39FARMHOUSE_POKEFAN_F,
};

const Script_fn_t Route39Farmhouse_SceneScripts[] = {
    0,
};

const struct MapCallback Route39Farmhouse_MapCallbacks[] = {
    0,
};

const struct MapScripts Route39Farmhouse_MapScripts = {
    .scene_script_count = 0, // lengthof(Route39Farmhouse_SceneScripts),
    .scene_scripts = Route39Farmhouse_SceneScripts,

    .callback_count = 0, // lengthof(Route39Farmhouse_MapCallbacks),
    .callbacks = Route39Farmhouse_MapCallbacks,
};

static const struct CoordEvent Route39Farmhouse_CoordEvents[] = {
    0,
};

static const struct BGEvent Route39Farmhouse_BGEvents[] = {
    bg_event(0, 1, BGEVENT_READ, &FarmhouseBookshelf),
    bg_event(1, 1, BGEVENT_READ, &FarmhouseBookshelf),
};

static const struct WarpEventData Route39Farmhouse_WarpEvents[] = {
    warp_event(2, 7, ROUTE_39, 2),
    warp_event(3, 7, ROUTE_39, 2),
};

static const struct ObjEvent Route39Farmhouse_ObjectEvents[] = {
    object_event(3, 2, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &PokefanM_DairyFarmer, -1),
    object_event(5, 4, SPRITE_POKEFAN_F, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, &PokefanF_SnoreFarmer, -1),
};

const struct MapEvents Route39Farmhouse_MapEvents = {
    .warp_event_count = lengthof(Route39Farmhouse_WarpEvents),
    .warp_events = Route39Farmhouse_WarpEvents,

    .coord_event_count = 0, // lengthof(Route39Farmhouse_CoordEvents),
    .coord_events = Route39Farmhouse_CoordEvents,

    .bg_event_count = lengthof(Route39Farmhouse_BGEvents),
    .bg_events = Route39Farmhouse_BGEvents,

    .obj_event_count = lengthof(Route39Farmhouse_ObjectEvents),
    .obj_events = Route39Farmhouse_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "Route39Farmhouse.h"

#define ROUTE39FARMHOUSE_MILK_PRICE 500
bool PokefanM_DairyFarmer(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_HEALED_MOOMOO)
    iftrue_jump(FarmerMScript_SellMilk)
    writetext(FarmerMText_SickCow)
    waitbutton
    closetext
    setevent(EVENT_TALKED_TO_FARMER_ABOUT_MOOMOO)
    s_end
    SCRIPT_END
}
bool FarmerMScript_SellMilk(script_s* s) {
    SCRIPT_BEGIN
    checkitem(MOOMOO_MILK)
    iftrue_jump(FarmerMScript_Milking)
    writetext(FarmerMText_BuyMilk)
    special(PlaceMoneyTopRight)
    yesorno
    iffalse_jump(FarmerMScript_NoSale)
    checkmoney(YOUR_MONEY, ROUTE39FARMHOUSE_MILK_PRICE)
    ifequal_jump(HAVE_LESS, FarmerMScript_NoMoney)
    giveitem(MOOMOO_MILK, 1)
    iffalse_jump(FarmerMScript_NoRoom)
    takemoney(YOUR_MONEY, ROUTE39FARMHOUSE_MILK_PRICE)
    special(PlaceMoneyTopRight)
    waitsfx
    playsound(SFX_TRANSACTION)
    writetext(FarmerMText_GotMilk)
    promptbutton
    itemnotify
    closetext
    s_end
    SCRIPT_END
}
bool FarmerMScript_NoMoney(script_s* s) {
    SCRIPT_BEGIN
    writetext(FarmerMText_NoMoney)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool FarmerMScript_NoRoom(script_s* s) {
    SCRIPT_BEGIN
    writetext(FarmerMText_NoRoom)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool FarmerMScript_NoSale(script_s* s) {
    SCRIPT_BEGIN
    writetext(FarmerMText_NoSale)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool FarmerMScript_Milking(script_s* s) {
    SCRIPT_BEGIN
    writetext(FarmerMText_Milking)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool PokefanF_SnoreFarmer(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_TM13_SNORE_FROM_MOOMOO_FARM)
    iftrue_jump(FarmerFScript_GotSnore)
    checkevent(EVENT_HEALED_MOOMOO)
    iftrue_jump(FarmerFScript_GiveSnore)
    writetext(FarmerFText_InTrouble)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool FarmerFScript_GiveSnore(script_s* s) {
    SCRIPT_BEGIN
    writetext(FarmerFText_HealedMiltank)
    promptbutton
    verbosegiveitem(TM_SNORE, 1)
    iffalse_jump(FarmerFScript_NoRoomForSnore)
    setevent(EVENT_GOT_TM13_SNORE_FROM_MOOMOO_FARM)
    SCRIPT_FALLTHROUGH(FarmerFScript_GotSnore)
}
bool FarmerFScript_GotSnore(script_s* s) {
    SCRIPT_BEGIN
    writetext(FarmerFText_SnoreSpeech)
    waitbutton
    SCRIPT_FALLTHROUGH(FarmerFScript_NoRoomForSnore)
}
bool FarmerFScript_NoRoomForSnore(script_s* s) {
    SCRIPT_BEGIN
    closetext
    s_end
    SCRIPT_END
}
bool FarmhouseBookshelf(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PictureBookshelfScript)
    SCRIPT_END
}
const txt_cmd_s FarmerMText_SickCow[] = {
    text_start("My MILTANK ain't"
        t_line "givin' me milk"
        t_cont "n'more."
        t_para "This here FARM's"
        t_line "got famous milk."
        t_para "Most everyone"
        t_line "wants a drink."
        t_para "It'll give me lots"
        t_line "o' milk if'n I"
        t_para "feed it lots o'"
        t_line "BERRIES, I reckon."
        t_done )
};
const txt_cmd_s FarmerMText_BuyMilk[] = {
    text_start("How'd you like my"
        t_line "MOOMOO MILK?"
        t_para "It's my pride and"
        t_line "joy, there."
        t_para "Give it to #MON"
        t_line "to restore HP!"
        t_para "I'll give it to ya"
        t_line "fer just ¥{d:ROUTE39FARMHOUSE_MILK_PRICE}."
        t_done )
};
const txt_cmd_s FarmerMText_GotMilk[] = {
    text_start("Here ya go!"
        t_line "Drink up'n enjoy!"
        t_done )
};
const txt_cmd_s FarmerMText_NoMoney[] = {
    text_start("Sorry, there."
        t_line "No cash, no sale!"
        t_done )
};
const txt_cmd_s FarmerMText_NoRoom[] = {
    text_start("I reckon yer"
        t_line "PACK's full."
        t_done )
};
const txt_cmd_s FarmerMText_NoSale[] = {
    text_start("You don't want it?"
        t_line "Come again, hear?"
        t_done )
};
const txt_cmd_s FarmerMText_Milking[] = {
    text_start("I best go do my"
        t_line "milkin'."
        t_done )
};
const txt_cmd_s FarmerFText_InTrouble[] = {
    text_start("Our milk even goes"
        t_line "out to KANTO."
        t_para "So if our own"
        t_line "MILTANK won't give"
        t_para "us any milk, we're"
        t_line "in trouble."
        t_done )
};
const txt_cmd_s FarmerFText_HealedMiltank[] = {
    text_start("You fixed our"
        t_line "MILTANK, hon. Now"
        t_para "it gives MOOMOO"
        t_line "MILK again."
        t_para "Here's somethin'"
        t_line "fer your trouble."
        t_done )
};
const txt_cmd_s Text_ReceivedTM13[] = {
    text_start("<PLAYER> received"
        t_line "TM13."
        t_done )
};
const txt_cmd_s FarmerFText_SnoreSpeech[] = {
    text_start("That there's"
        t_line "SNORE."
        t_para "It's a rare move"
        t_line "that only works"
        t_para "while the #MON"
        t_line "is asleep."
        t_para "You best think how"
        t_line "you ought to use"
        t_cont "it, hon."
        t_done )
    //db(0, 0) // filler
};
