#include "../constants.h"
#include "../util/scripting.h"
#include "CeladonGameCornerPrizeRoom.h"
//// EVENTS
enum {
    CELADONGAMECORNERPRIZEROOM_GENTLEMAN = 2,
    CELADONGAMECORNERPRIZEROOM_PHARMACIST,
};

const Script_fn_t CeladonGameCornerPrizeRoom_SceneScripts[] = {
    0,
};

const struct MapCallback CeladonGameCornerPrizeRoom_MapCallbacks[] = {
    0,
};

const struct MapScripts CeladonGameCornerPrizeRoom_MapScripts = {
    .scene_script_count = 0, // lengthof(CeladonGameCornerPrizeRoom_SceneScripts),
    .scene_scripts = CeladonGameCornerPrizeRoom_SceneScripts,

    .callback_count = 0, // lengthof(CeladonGameCornerPrizeRoom_MapCallbacks),
    .callbacks = CeladonGameCornerPrizeRoom_MapCallbacks,
};

static const struct CoordEvent CeladonGameCornerPrizeRoom_CoordEvents[] = {
    0,
};

static const struct BGEvent CeladonGameCornerPrizeRoom_BGEvents[] = {
    bg_event(2, 1, BGEVENT_READ, &CeladonGameCornerPrizeRoomTMVendor),
    bg_event(4, 1, BGEVENT_READ, &CeladonGameCornerPrizeRoomPokemonVendor),
};

static const struct WarpEventData CeladonGameCornerPrizeRoom_WarpEvents[] = {
    warp_event(2, 5, CELADON_CITY, 7),
    warp_event(3, 5, CELADON_CITY, 7),
};

static const struct ObjEvent CeladonGameCornerPrizeRoom_ObjectEvents[] = {
    object_event(0, 2, SPRITE_GENTLEMAN, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &CeladonGameCornerPrizeRoomGentlemanScript, -1),
    object_event(4, 4, SPRITE_PHARMACIST, SPRITEMOVEDATA_WALK_UP_DOWN, 0, 1, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &CeladonGameCornerPrizeRoomPharmacistScript, -1),
};

const struct MapEvents CeladonGameCornerPrizeRoom_MapEvents = {
    .warp_event_count = lengthof(CeladonGameCornerPrizeRoom_WarpEvents),
    .warp_events = CeladonGameCornerPrizeRoom_WarpEvents,

    .coord_event_count = 0, // lengthof(CeladonGameCornerPrizeRoom_CoordEvents),
    .coord_events = CeladonGameCornerPrizeRoom_CoordEvents,

    .bg_event_count = lengthof(CeladonGameCornerPrizeRoom_BGEvents),
    .bg_events = CeladonGameCornerPrizeRoom_BGEvents,

    .obj_event_count = lengthof(CeladonGameCornerPrizeRoom_ObjectEvents),
    .obj_events = CeladonGameCornerPrizeRoom_ObjectEvents,
};

//// CODE

#define CELADONGAMECORNERPRIZEROOM_TM32_COINS 1500
#define CELADONGAMECORNERPRIZEROOM_TM29_COINS 3500
#define CELADONGAMECORNERPRIZEROOM_TM15_COINS 7500
#define CELADONGAMECORNERPRIZEROOM_PIKACHU_COINS 2222
#define CELADONGAMECORNERPRIZEROOM_PORYGON_COINS 5555
#define CELADONGAMECORNERPRIZEROOM_LARVITAR_COINS 8888
bool CeladonGameCornerPrizeRoomGentlemanScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CeladonGameCornerPrizeRoomGentlemanText)
    SCRIPT_END
}
bool CeladonGameCornerPrizeRoomPharmacistScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CeladonGameCornerPrizeRoomPharmacistText)
    SCRIPT_END
}
bool CeladonGameCornerPrizeRoomTMVendor(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(CeladonPrizeRoom_PrizeVendorIntroText)
    waitbutton
    checkitem(COIN_CASE)
    iffalse_jump(CeladonPrizeRoom_NoCoinCase)
    writetext(CeladonPrizeRoom_AskWhichPrizeText)
    SCRIPT_FALLTHROUGH(CeladonPrizeRoom_tmcounterloop)
}
bool CeladonPrizeRoom_tmcounterloop(script_s* s) {
    SCRIPT_BEGIN
    special(DisplayCoinCaseBalance)
    loadmenu(&CeladonPrizeRoom_TMMenuHeader)
    verticalmenu
    closewindow
    ifequal(1, DoubleTeam)
    ifequal(2, Psychic)
    ifequal(3, HyperBeam)
    sjump(CeladonPrizeRoom_CancelPurchaseScript)
DoubleTeam:
    checkcoins(CELADONGAMECORNERPRIZEROOM_TM32_COINS)
    ifequal_jump(HAVE_LESS, CeladonPrizeRoom_notenoughcoins)
    getitemname(STRING_BUFFER_3, TM_DOUBLE_TEAM)
    scall(CeladonPrizeRoom_askbuy)
    iffalse_jump(CeladonPrizeRoom_CancelPurchaseScript)
    giveitem(TM_DOUBLE_TEAM, 1)
    iffalse_jump(CeladonPrizeRoom_notenoughroom)
    takecoins(CELADONGAMECORNERPRIZEROOM_TM32_COINS)
    sjump(CeladonPrizeRoom_purchased)
Psychic:
    checkcoins(CELADONGAMECORNERPRIZEROOM_TM29_COINS)
    ifequal_jump(HAVE_LESS, CeladonPrizeRoom_notenoughcoins)
    getitemname(STRING_BUFFER_3, TM_PSYCHIC_M)
    scall(CeladonPrizeRoom_askbuy)
    iffalse_jump(CeladonPrizeRoom_CancelPurchaseScript)
    giveitem(TM_PSYCHIC_M, 1)
    iffalse_jump(CeladonPrizeRoom_notenoughroom)
    takecoins(CELADONGAMECORNERPRIZEROOM_TM29_COINS)
    sjump(CeladonPrizeRoom_purchased)
HyperBeam:
    checkcoins(CELADONGAMECORNERPRIZEROOM_TM15_COINS)
    ifequal_jump(HAVE_LESS, CeladonPrizeRoom_notenoughcoins)
    getitemname(STRING_BUFFER_3, TM_HYPER_BEAM)
    scall(CeladonPrizeRoom_askbuy)
    iffalse_jump(CeladonPrizeRoom_CancelPurchaseScript)
    giveitem(TM_HYPER_BEAM, 1)
    iffalse_jump(CeladonPrizeRoom_notenoughroom)
    takecoins(CELADONGAMECORNERPRIZEROOM_TM15_COINS)
    sjump(CeladonPrizeRoom_purchased)
    SCRIPT_END
}
bool CeladonPrizeRoom_askbuy(script_s* s) {
    SCRIPT_BEGIN
    writetext(CeladonPrizeRoom_ConfirmPurchaseText)
    yesorno
    s_end
    SCRIPT_END
}
bool CeladonPrizeRoom_purchased(script_s* s) {
    SCRIPT_BEGIN
    waitsfx
    playsound(SFX_TRANSACTION)
    writetext(CeladonPrizeRoom_HereYouGoText)
    waitbutton
    sjump(CeladonPrizeRoom_tmcounterloop)
    SCRIPT_END
}
bool CeladonPrizeRoom_notenoughcoins(script_s* s) {
    SCRIPT_BEGIN
    writetext(CeladonPrizeRoom_NotEnoughCoinsText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool CeladonPrizeRoom_notenoughroom(script_s* s) {
    SCRIPT_BEGIN
    writetext(CeladonPrizeRoom_NotEnoughRoomText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool CeladonPrizeRoom_CancelPurchaseScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(CeladonPrizeRoom_ComeAgainText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool CeladonPrizeRoom_NoCoinCase(script_s* s) {
    SCRIPT_BEGIN
    writetext(CeladonPrizeRoom_NoCoinCaseText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct MenuHeader CeladonPrizeRoom_TMMenuHeader = {
    .flags = MENU_BACKUP_TILES, // flags
    .coord = menu_coords(0, 2, 15, TEXTBOX_Y - 1),
    .data = &(struct MenuData) {
    // MenuData:
        .flags = STATICMENU_CURSOR, // flags
        .verticalMenu = {
            .count = 4, // items
            .options = (const char*[]) {
                "TM32    " _s(CELADONGAMECORNERPRIZEROOM_TM32_COINS) "@",
                "TM29    " _s(CELADONGAMECORNERPRIZEROOM_TM29_COINS) "@",
                "TM15    " _s(CELADONGAMECORNERPRIZEROOM_TM15_COINS) "@",
                "CANCEL@"
            },
        },
    },
    //db(1) // default option
};
static const struct MenuHeader CeladonGameCornerPrizeRoomPokemonVendor_MenuHeader = {
    .flags = MENU_BACKUP_TILES, // flags
    .coord = menu_coords(0, 2, 17, TEXTBOX_Y - 1),
    .data = &(struct MenuData) {
    // MenuData:
        .flags = STATICMENU_CURSOR, // flags
        .verticalMenu = {
            .count = 4, // items
            .options = (const char*[]) {
                "PIKACHU    " _s(CELADONGAMECORNERPRIZEROOM_PIKACHU_COINS) "@",
                "PORYGON    " _s(CELADONGAMECORNERPRIZEROOM_PORYGON_COINS) "@",
                "LARVITAR   " _s(CELADONGAMECORNERPRIZEROOM_LARVITAR_COINS) "@",
                "CANCEL@",
            },
        },
    }, //dw(.MenuData)
    .defaultOption = 1, // default option
};

bool CeladonGameCornerPrizeRoomPokemonVendor(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(CeladonPrizeRoom_PrizeVendorIntroText)
    waitbutton
    checkitem(COIN_CASE)
    iffalse_jump(CeladonPrizeRoom_NoCoinCase)
loop:
    writetext(CeladonPrizeRoom_AskWhichPrizeText)
    special(DisplayCoinCaseBalance)
    loadmenu(&CeladonGameCornerPrizeRoomPokemonVendor_MenuHeader)
    verticalmenu
    closewindow
    ifequal(1, Pikachu)
    ifequal(2, Porygon)
    ifequal(3, Larvitar)
    sjump(CeladonPrizeRoom_CancelPurchaseScript)
Pikachu:
    checkcoins(CELADONGAMECORNERPRIZEROOM_PIKACHU_COINS)
    ifequal_jump(HAVE_LESS, CeladonPrizeRoom_notenoughcoins)
    readvar(VAR_PARTYCOUNT)
    ifequal_jump(PARTY_LENGTH, CeladonPrizeRoom_notenoughroom)
    getmonname(STRING_BUFFER_3, PIKACHU)
    scall(CeladonPrizeRoom_askbuy)
    iffalse_jump(CeladonPrizeRoom_CancelPurchaseScript)
    waitsfx
    playsound(SFX_TRANSACTION)
    writetext(CeladonPrizeRoom_HereYouGoText)
    waitbutton
    setval(PIKACHU)
    special(GameCornerPrizeMonCheckDex)
    givepoke(PIKACHU, 25, NO_ITEM)
    takecoins(CELADONGAMECORNERPRIZEROOM_PIKACHU_COINS)
    goto loop;
Porygon:
    checkcoins(CELADONGAMECORNERPRIZEROOM_PORYGON_COINS)
    ifequal_jump(HAVE_LESS, CeladonPrizeRoom_notenoughcoins)
    readvar(VAR_PARTYCOUNT)
    ifequal_jump(PARTY_LENGTH, CeladonPrizeRoom_notenoughroom)
    getmonname(STRING_BUFFER_3, PORYGON)
    scall(CeladonPrizeRoom_askbuy)
    iffalse_jump(CeladonPrizeRoom_CancelPurchaseScript)
    waitsfx
    playsound(SFX_TRANSACTION)
    writetext(CeladonPrizeRoom_HereYouGoText)
    waitbutton
    setval(PORYGON)
    special(GameCornerPrizeMonCheckDex)
    givepoke(PORYGON, 15, NO_ITEM)
    takecoins(CELADONGAMECORNERPRIZEROOM_PORYGON_COINS)
    goto loop;
Larvitar:
    checkcoins(CELADONGAMECORNERPRIZEROOM_LARVITAR_COINS)
    ifequal_jump(HAVE_LESS, CeladonPrizeRoom_notenoughcoins)
    readvar(VAR_PARTYCOUNT)
    ifequal_jump(PARTY_LENGTH, CeladonPrizeRoom_notenoughroom)
    getmonname(STRING_BUFFER_3, LARVITAR)
    scall(CeladonPrizeRoom_askbuy)
    iffalse_jump(CeladonPrizeRoom_CancelPurchaseScript)
    waitsfx
    playsound(SFX_TRANSACTION)
    writetext(CeladonPrizeRoom_HereYouGoText)
    waitbutton
    setval(LARVITAR)
    special(GameCornerPrizeMonCheckDex)
    givepoke(LARVITAR, 40, NO_ITEM)
    takecoins(CELADONGAMECORNERPRIZEROOM_LARVITAR_COINS)
    goto loop;
    SCRIPT_END
}
const txt_cmd_s CeladonGameCornerPrizeRoomGentlemanText[] = {
    text_start("I wanted PORYGON,"
        t_line "but I was short by"
        t_cont "100 coins…"
        t_done )
};
const txt_cmd_s CeladonGameCornerPrizeRoomPharmacistText[] = {
#if _CRYSTAL_AU
    text_start("I don't want to"
        t_line "lose my coins."
        t_done )
#else
    text_start("Whew…"
        t_para "I've got to stay"
        t_line "calm and cool…"
        t_para "I can't lose my"
        t_line "cool, or I'll lose"
        t_cont "all my money…"
        t_done )
#endif
};
const txt_cmd_s CeladonPrizeRoom_PrizeVendorIntroText[] = {
    text_start("Welcome!"
        t_para "We exchange your"
        t_line "coins for fabulous"
        t_cont "prizes!"
        t_done )
};
const txt_cmd_s CeladonPrizeRoom_AskWhichPrizeText[] = {
    text_start("Which prize would"
        t_line "you like?"
        t_done )
};
const txt_cmd_s CeladonPrizeRoom_ConfirmPurchaseText[] = {
    text_start("OK, so you wanted"
        t_line "a @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("?"
        t_done )
};
const txt_cmd_s CeladonPrizeRoom_HereYouGoText[] = {
    text_start("Here you go!"
        t_done )
};
const txt_cmd_s CeladonPrizeRoom_NotEnoughCoinsText[] = {
    text_start("You don't have"
        t_line "enough coins."
        t_done )
};
const txt_cmd_s CeladonPrizeRoom_NotEnoughRoomText[] = {
    text_start("You have no room"
        t_line "for it."
        t_done )
};
const txt_cmd_s CeladonPrizeRoom_ComeAgainText[] = {
    text_start("Oh. Please come"
        t_line "back with coins!"
        t_done )
};
const txt_cmd_s CeladonPrizeRoom_NoCoinCaseText[] = {
    text_start("Oh? You don't have"
        t_line "a COIN CASE."
        t_done )
    //db(0, 0) // filler
};
