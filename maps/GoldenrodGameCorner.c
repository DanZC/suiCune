#include "../constants.h"
#include "../util/scripting.h"
#include "GoldenrodGameCorner.h"
//// EVENTS
enum {
    GOLDENRODGAMECORNER_CLERK = 2,
    GOLDENRODGAMECORNER_RECEPTIONIST1,
    GOLDENRODGAMECORNER_RECEPTIONIST2,
    GOLDENRODGAMECORNER_PHARMACIST1,
    GOLDENRODGAMECORNER_PHARMACIST2,
    GOLDENRODGAMECORNER_POKEFAN_M1,
    GOLDENRODGAMECORNER_COOLTRAINER_M,
    GOLDENRODGAMECORNER_POKEFAN_F,
    GOLDENRODGAMECORNER_COOLTRAINER_F,
    GOLDENRODGAMECORNER_GENTLEMAN,
    GOLDENRODGAMECORNER_POKEFAN_M2,
    GOLDENRODGAMECORNER_MOVETUTOR,
};

const Script_fn_t GoldenrodGameCorner_SceneScripts[] = {
    0,
};

const struct MapCallback GoldenrodGameCorner_MapCallbacks[] = {
    map_callback(MAPCALLBACK_OBJECTS, GoldenrodGameCorner_MapScripts_MoveTutor),
};

const struct MapScripts GoldenrodGameCorner_MapScripts = {
    .scene_script_count = 0, // lengthof(GoldenrodGameCorner_SceneScripts),
    .scene_scripts = GoldenrodGameCorner_SceneScripts,

    .callback_count = lengthof(GoldenrodGameCorner_MapCallbacks),
    .callbacks = GoldenrodGameCorner_MapCallbacks,
};

static const struct CoordEvent GoldenrodGameCorner_CoordEvents[] = {
    0,
};

static const struct BGEvent GoldenrodGameCorner_BGEvents[] = {
    bg_event(6, 6, BGEVENT_READ, &GoldenrodGameCornerSlotsMachineScript),
    bg_event(6, 7, BGEVENT_READ, &GoldenrodGameCornerSlotsMachineScript),
    bg_event(6, 8, BGEVENT_READ, &GoldenrodGameCornerSlotsMachineScript),
    bg_event(6, 9, BGEVENT_READ, &GoldenrodGameCornerSlotsMachineScript),
    bg_event(6, 10, BGEVENT_READ, &GoldenrodGameCornerSlotsMachineScript),
    bg_event(6, 11, BGEVENT_RIGHT, &GoldenrodGameCornerSlotsMachineScript),
    bg_event(7, 6, BGEVENT_READ, &GoldenrodGameCornerSlotsMachineScript),
    bg_event(7, 7, BGEVENT_READ, &GoldenrodGameCornerLuckySlotsMachineScript),
    bg_event(7, 8, BGEVENT_READ, &GoldenrodGameCornerSlotsMachineScript),
    bg_event(7, 9, BGEVENT_READ, &GoldenrodGameCornerSlotsMachineScript),
    bg_event(7, 10, BGEVENT_READ, &GoldenrodGameCornerSlotsMachineScript),
    bg_event(7, 11, BGEVENT_LEFT, &GoldenrodGameCornerSlotsMachineScript),
    bg_event(12, 6, BGEVENT_READ, &GoldenrodGameCornerSlotsMachineScript),
    bg_event(12, 7, BGEVENT_READ, &GoldenrodGameCornerSlotsMachineScript),
    bg_event(12, 8, BGEVENT_READ, &GoldenrodGameCornerSlotsMachineScript),
    bg_event(12, 9, BGEVENT_READ, &GoldenrodGameCornerSlotsMachineScript),
    bg_event(12, 10, BGEVENT_READ, &GoldenrodGameCornerSlotsMachineScript),
    bg_event(12, 11, BGEVENT_RIGHT, &GoldenrodGameCornerSlotsMachineScript),
    bg_event(13, 6, BGEVENT_READ, &GoldenrodGameCornerCardFlipMachineScript),
    bg_event(13, 7, BGEVENT_READ, &GoldenrodGameCornerCardFlipMachineScript),
    bg_event(13, 8, BGEVENT_READ, &GoldenrodGameCornerCardFlipMachineScript),
    bg_event(13, 9, BGEVENT_READ, &GoldenrodGameCornerCardFlipMachineScript),
    bg_event(13, 10, BGEVENT_READ, &GoldenrodGameCornerCardFlipMachineScript),
    bg_event(13, 11, BGEVENT_LEFT, &GoldenrodGameCornerCardFlipMachineScript),
    bg_event(18, 6, BGEVENT_READ, &GoldenrodGameCornerCardFlipMachineScript),
    bg_event(18, 7, BGEVENT_READ, &GoldenrodGameCornerCardFlipMachineScript),
    bg_event(18, 8, BGEVENT_READ, &GoldenrodGameCornerCardFlipMachineScript),
    bg_event(18, 9, BGEVENT_READ, &GoldenrodGameCornerCardFlipMachineScript),
    bg_event(18, 10, BGEVENT_READ, &GoldenrodGameCornerCardFlipMachineScript),
    bg_event(18, 11, BGEVENT_RIGHT, &GoldenrodGameCornerCardFlipMachineScript),
    bg_event(12, 1, BGEVENT_LEFT, &GoldenrodGameCornerLeftTheirDrinkScript),
};

static const struct WarpEventData GoldenrodGameCorner_WarpEvents[] = {
    warp_event(2, 13, GOLDENROD_CITY, 10),
    warp_event(3, 13, GOLDENROD_CITY, 10),
};

static const struct ObjEvent GoldenrodGameCorner_ObjectEvents[] = {
    object_event(3, 2, SPRITE_CLERK, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &GoldenrodGameCornerCoinVendorScript, -1),
    object_event(16, 2, SPRITE_RECEPTIONIST, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &GoldenrodGameCornerTMVendorScript, -1),
    object_event(18, 2, SPRITE_RECEPTIONIST, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &GoldenrodGameCornerPrizeMonVendorScript, -1),
    object_event(8, 7, SPRITE_PHARMACIST, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, DAY, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &GoldenrodGameCornerPharmacistScript, -1),
    object_event(8, 7, SPRITE_PHARMACIST, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, NITE, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &GoldenrodGameCornerPharmacistScript, -1),
    object_event(11, 10, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, &GoldenrodGameCornerPokefanM1Script, -1),
    object_event(14, 8, SPRITE_COOLTRAINER_M, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &GoldenrodGameCornerCooltrainerMScript, -1),
    object_event(17, 6, SPRITE_POKEFAN_F, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &GoldenrodGameCornerPokefanFScript, -1),
    object_event(10, 3, SPRITE_COOLTRAINER_F, SPRITEMOVEDATA_WANDER, 2, 1, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &GoldenrodGameCornerCooltrainerFScript, -1),
    object_event(5, 10, SPRITE_GENTLEMAN, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &GoldenrodGameCornerGentlemanScript, -1),
    object_event(2, 9, SPRITE_POKEFAN_M, SPRITEMOVEDATA_WANDER, 1, 1, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, &GoldenrodGameCornerPokefanM2Script, -1),
    object_event(17, 10, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &MoveTutorInsideScript, EVENT_GOLDENROD_GAME_CORNER_MOVE_TUTOR),
};

const struct MapEvents GoldenrodGameCorner_MapEvents = {
    .warp_event_count = lengthof(GoldenrodGameCorner_WarpEvents),
    .warp_events = GoldenrodGameCorner_WarpEvents,

    .coord_event_count = 0, // lengthof(GoldenrodGameCorner_CoordEvents),
    .coord_events = GoldenrodGameCorner_CoordEvents,

    .bg_event_count = lengthof(GoldenrodGameCorner_BGEvents),
    .bg_events = GoldenrodGameCorner_BGEvents,

    .obj_event_count = lengthof(GoldenrodGameCorner_ObjectEvents),
    .obj_events = GoldenrodGameCorner_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "GoldenrodGameCorner.h"

#define GOLDENRODGAMECORNER_TM25_COINS 5500
#define GOLDENRODGAMECORNER_TM14_COINS 5500
#define GOLDENRODGAMECORNER_TM38_COINS 5500
#define GOLDENRODGAMECORNER_ABRA_COINS 100
#define GOLDENRODGAMECORNER_CUBONE_COINS 800
#define GOLDENRODGAMECORNER_WOBBUFFET_COINS 1500

static const struct MenuHeader GoldenrodGameCornerTMVendorMenuHeader = {
    .flags = MENU_BACKUP_TILES, // flags
    .coord = menu_coords(0, 2, 15, TEXTBOX_Y - 1),
    //dw(.MenuData)
    .data = &(struct MenuData) {
    // MenuData:
        .flags = STATICMENU_CURSOR, // flags
        .verticalMenu = {
            .count = 4, // items
            .options = (const char*[]) {
                "TM25    5500@",
                "TM14    5500@",
                "TM38    5500@",
                "CANCEL@",
            },
        },
    },
    .defaultOption = 1, // default option
};

bool GoldenrodGameCorner_MapScripts_MoveTutor(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_BEAT_ELITE_FOUR)
    iffalse_jump(GoldenrodGameCorner_MapScripts_finish)
    checkitem(COIN_CASE)
    iffalse_jump(GoldenrodGameCorner_MapScripts_move_tutor_inside)
    readvar(VAR_WEEKDAY)
    ifequal_jump(WEDNESDAY, GoldenrodGameCorner_MapScripts_move_tutor_outside)
    ifequal_jump(SATURDAY, GoldenrodGameCorner_MapScripts_move_tutor_outside)
    SCRIPT_FALLTHROUGH(GoldenrodGameCorner_MapScripts_move_tutor_inside)
}
bool GoldenrodGameCorner_MapScripts_move_tutor_inside(script_s* s) {
    SCRIPT_BEGIN
    appear(GOLDENRODGAMECORNER_MOVETUTOR)
    s_endcallback
    SCRIPT_END
}
bool GoldenrodGameCorner_MapScripts_move_tutor_outside(script_s* s) {
    SCRIPT_BEGIN
    checkflag(ENGINE_DAILY_MOVE_TUTOR)
    iftrue_jump(GoldenrodGameCorner_MapScripts_finish)
    disappear(GOLDENRODGAMECORNER_MOVETUTOR)
    SCRIPT_FALLTHROUGH(GoldenrodGameCorner_MapScripts_finish)
}
bool GoldenrodGameCorner_MapScripts_finish(script_s* s) {
    SCRIPT_BEGIN
    s_endcallback
    SCRIPT_END
}
bool MoveTutorInsideScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(MoveTutorInsideText)
    waitbutton
    closetext
    turnobject(GOLDENRODGAMECORNER_MOVETUTOR, RIGHT)
    s_end
    SCRIPT_END
}
bool GoldenrodGameCornerCoinVendorScript(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(GameCornerCoinVendorScript)
    SCRIPT_END
}
bool GoldenrodGameCornerTMVendorScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(GoldenrodGameCornerPrizeVendorIntroText)
    waitbutton
    checkitem(COIN_CASE)
    iffalse_jump(GoldenrodGameCornerPrizeVendor_NoCoinCaseScript)
    writetext(GoldenrodGameCornerPrizeVendorWhichPrizeText)
    SCRIPT_FALLTHROUGH(GoldenrodGameCornerTMVendor_LoopScript)
}
bool GoldenrodGameCornerTMVendor_LoopScript(script_s* s) {
    SCRIPT_BEGIN
    special(DisplayCoinCaseBalance)
    loadmenu(&GoldenrodGameCornerTMVendorMenuHeader)
    verticalmenu
    closewindow
    ifequal(1, Thunder)
    ifequal(2, Blizzard)
    ifequal(3, FireBlast)
    sjump(GoldenrodGameCornerPrizeVendor_CancelPurchaseScript)
Thunder:
    checkcoins(GOLDENRODGAMECORNER_TM25_COINS)
    ifequal_jump(HAVE_LESS, GoldenrodGameCornerPrizeVendor_NotEnoughCoinsScript)
    getitemname(STRING_BUFFER_3, TM_THUNDER)
    scall(GoldenrodGameCornerPrizeVendor_ConfirmPurchaseScript)
    iffalse_jump(GoldenrodGameCornerPrizeVendor_CancelPurchaseScript)
    giveitem(TM_THUNDER, 1)
    iffalse_jump(GoldenrodGameCornerPrizeMonVendor_NoRoomForPrizeScript)
    takecoins(GOLDENRODGAMECORNER_TM25_COINS)
    sjump(GoldenrodGameCornerTMVendor_FinishScript)
Blizzard:
    checkcoins(GOLDENRODGAMECORNER_TM14_COINS)
    ifequal_jump(HAVE_LESS, GoldenrodGameCornerPrizeVendor_NotEnoughCoinsScript)
    getitemname(STRING_BUFFER_3, TM_BLIZZARD)
    scall(GoldenrodGameCornerPrizeVendor_ConfirmPurchaseScript)
    iffalse_jump(GoldenrodGameCornerPrizeVendor_CancelPurchaseScript)
    giveitem(TM_BLIZZARD, 1)
    iffalse_jump(GoldenrodGameCornerPrizeMonVendor_NoRoomForPrizeScript)
    takecoins(GOLDENRODGAMECORNER_TM14_COINS)
    sjump(GoldenrodGameCornerTMVendor_FinishScript)
FireBlast:
    checkcoins(GOLDENRODGAMECORNER_TM38_COINS)
    ifequal_jump(HAVE_LESS, GoldenrodGameCornerPrizeVendor_NotEnoughCoinsScript)
    getitemname(STRING_BUFFER_3, TM_FIRE_BLAST)
    scall(GoldenrodGameCornerPrizeVendor_ConfirmPurchaseScript)
    iffalse_jump(GoldenrodGameCornerPrizeVendor_CancelPurchaseScript)
    giveitem(TM_FIRE_BLAST, 1)
    iffalse_jump(GoldenrodGameCornerPrizeMonVendor_NoRoomForPrizeScript)
    takecoins(GOLDENRODGAMECORNER_TM38_COINS)
    sjump(GoldenrodGameCornerTMVendor_FinishScript)
    SCRIPT_END
}
bool GoldenrodGameCornerPrizeVendor_ConfirmPurchaseScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(GoldenrodGameCornerPrizeVendorConfirmPrizeText)
    yesorno
    s_end
    SCRIPT_END
}
bool GoldenrodGameCornerTMVendor_FinishScript(script_s* s) {
    SCRIPT_BEGIN
    waitsfx
    playsound(SFX_TRANSACTION)
    writetext(GoldenrodGameCornerPrizeVendorHereYouGoText)
    waitbutton
    sjump(GoldenrodGameCornerTMVendor_LoopScript)
    SCRIPT_END
}
bool GoldenrodGameCornerPrizeVendor_NotEnoughCoinsScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(GoldenrodGameCornerPrizeVendorNeedMoreCoinsText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool GoldenrodGameCornerPrizeMonVendor_NoRoomForPrizeScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(GoldenrodGameCornerPrizeVendorNoMoreRoomText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool GoldenrodGameCornerPrizeVendor_CancelPurchaseScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(GoldenrodGameCornerPrizeVendorQuitText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool GoldenrodGameCornerPrizeVendor_NoCoinCaseScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(GoldenrodGameCornerPrizeVendorNoCoinCaseText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}

static const struct MenuHeader PrizeMonMenuHeader = {
    .flags = MENU_BACKUP_TILES, // flags
    .coord = menu_coords(0, 2, 17, TEXTBOX_Y - 1),
    .data = &(struct MenuData) {
    // MenuData:
        .flags = STATICMENU_CURSOR, // flags
        .verticalMenu = {
            .count = 4, // items
            .options = (const char*[]) {
                "ABRA        100@",
                "CUBONE      800@",
                "WOBBUFFET  1500@",
                "CANCEL@",
            },
        },
    },
    .defaultOption = 1, // default option
};

bool GoldenrodGameCornerPrizeMonVendorScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(GoldenrodGameCornerPrizeVendorIntroText)
    waitbutton
    checkitem(COIN_CASE)
    iffalse_jump(GoldenrodGameCornerPrizeVendor_NoCoinCaseScript)
loop:
    writetext(GoldenrodGameCornerPrizeVendorWhichPrizeText)
    special(DisplayCoinCaseBalance)
    loadmenu(&PrizeMonMenuHeader)
    verticalmenu
    closewindow
    ifequal(1, Abra)
    ifequal(2, Cubone)
    ifequal(3, Wobbuffet)
    sjump(GoldenrodGameCornerPrizeVendor_CancelPurchaseScript)
Abra:
    checkcoins(GOLDENRODGAMECORNER_ABRA_COINS)
    ifequal_jump(HAVE_LESS, GoldenrodGameCornerPrizeVendor_NotEnoughCoinsScript)
    readvar(VAR_PARTYCOUNT)
    ifequal_jump(PARTY_LENGTH, GoldenrodGameCornerPrizeMonVendor_NoRoomForPrizeScript)
    getmonname(STRING_BUFFER_3, ABRA)
    scall(GoldenrodGameCornerPrizeVendor_ConfirmPurchaseScript)
    iffalse_jump(GoldenrodGameCornerPrizeVendor_CancelPurchaseScript)
    waitsfx
    playsound(SFX_TRANSACTION)
    writetext(GoldenrodGameCornerPrizeVendorHereYouGoText)
    waitbutton
    setval(ABRA)
    special(GameCornerPrizeMonCheckDex)
    givepoke(ABRA, 5, NO_ITEM)
    takecoins(GOLDENRODGAMECORNER_ABRA_COINS)
    goto loop;
Cubone:
    checkcoins(GOLDENRODGAMECORNER_CUBONE_COINS)
    ifequal_jump(HAVE_LESS, GoldenrodGameCornerPrizeVendor_NotEnoughCoinsScript)
    readvar(VAR_PARTYCOUNT)
    ifequal_jump(PARTY_LENGTH, GoldenrodGameCornerPrizeMonVendor_NoRoomForPrizeScript)
    getmonname(STRING_BUFFER_3, CUBONE)
    scall(GoldenrodGameCornerPrizeVendor_ConfirmPurchaseScript)
    iffalse_jump(GoldenrodGameCornerPrizeVendor_CancelPurchaseScript)
    waitsfx
    playsound(SFX_TRANSACTION)
    writetext(GoldenrodGameCornerPrizeVendorHereYouGoText)
    waitbutton
    setval(CUBONE)
    special(GameCornerPrizeMonCheckDex)
    givepoke(CUBONE, 15, NO_ITEM)
    takecoins(GOLDENRODGAMECORNER_CUBONE_COINS)
    goto loop;
Wobbuffet:
    checkcoins(GOLDENRODGAMECORNER_WOBBUFFET_COINS)
    ifequal_jump(HAVE_LESS, GoldenrodGameCornerPrizeVendor_NotEnoughCoinsScript)
    readvar(VAR_PARTYCOUNT)
    ifequal_jump(PARTY_LENGTH, GoldenrodGameCornerPrizeMonVendor_NoRoomForPrizeScript)
    getmonname(STRING_BUFFER_3, WOBBUFFET)
    scall(GoldenrodGameCornerPrizeVendor_ConfirmPurchaseScript)
    iffalse_jump(GoldenrodGameCornerPrizeVendor_CancelPurchaseScript)
    waitsfx
    playsound(SFX_TRANSACTION)
    writetext(GoldenrodGameCornerPrizeVendorHereYouGoText)
    waitbutton
    setval(WOBBUFFET)
    special(GameCornerPrizeMonCheckDex)
    givepoke(WOBBUFFET, 15, NO_ITEM)
    takecoins(GOLDENRODGAMECORNER_WOBBUFFET_COINS)
    goto loop;
    SCRIPT_FALLTHROUGH(GoldenrodGameCornerPharmacistScript)
}
bool GoldenrodGameCornerPharmacistScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(GoldenrodGameCornerPharmacistText)
    waitbutton
    closetext
    turnobject(LAST_TALKED, LEFT)
    s_end
    SCRIPT_END
}
bool GoldenrodGameCornerPokefanM1Script(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(GoldenrodGameCornerPokefanM1Text)
    waitbutton
    closetext
    turnobject(GOLDENRODGAMECORNER_POKEFAN_M1, RIGHT)
    s_end
    SCRIPT_END
}
bool GoldenrodGameCornerCooltrainerMScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(GoldenrodGameCornerCooltrainerMText)
    waitbutton
    closetext
    turnobject(GOLDENRODGAMECORNER_COOLTRAINER_M, LEFT)
    s_end
    SCRIPT_END
}
bool GoldenrodGameCornerPokefanFScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(GoldenrodGameCornerPokefanFText)
    waitbutton
    closetext
    turnobject(GOLDENRODGAMECORNER_POKEFAN_F, RIGHT)
    s_end
    SCRIPT_END
}
bool GoldenrodGameCornerCooltrainerFScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(GoldenrodGameCornerCooltrainerFText)
    SCRIPT_END
}
bool GoldenrodGameCornerGentlemanScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(GoldenrodGameCornerGentlemanText)
    waitbutton
    closetext
    turnobject(GOLDENRODGAMECORNER_GENTLEMAN, RIGHT)
    s_end
    SCRIPT_END
}
bool GoldenrodGameCornerPokefanM2Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(GoldenrodGameCornerPokefanM2Text)
    SCRIPT_END
}
bool GoldenrodGameCornerLeftTheirDrinkScript(script_s* s) {
    SCRIPT_BEGIN
    jumptext(GoldenrodGameCornerLeftTheirDrinkText)
    SCRIPT_END
}
bool GoldenrodGameCornerSlotsMachineScript(script_s* s) {
    SCRIPT_BEGIN
    srandom(6)
    ifequal_jump(0, GoldenrodGameCornerLuckySlotsMachineScript)
    refreshscreen
    setval(FALSE)
    special(SlotMachine)
    closetext
    s_end
    SCRIPT_END
}
bool GoldenrodGameCornerLuckySlotsMachineScript(script_s* s) {
    SCRIPT_BEGIN
    refreshscreen
    setval(TRUE)
    special(SlotMachine)
    closetext
    s_end
    SCRIPT_END
}
bool GoldenrodGameCornerCardFlipMachineScript(script_s* s) {
    SCRIPT_BEGIN
    refreshscreen
    special(CardFlip)
    closetext
    s_end
    SCRIPT_END
}
const txt_cmd_s GoldenrodGameCornerPrizeVendorIntroText[] = {
    text_start("Welcome!"
        t_para "We exchange your"
        t_line "game coins for"
        t_cont "fabulous prizes!"
        t_done )
};
const txt_cmd_s GoldenrodGameCornerPrizeVendorWhichPrizeText[] = {
    text_start("Which prize would"
        t_line "you like?"
        t_done )
};
const txt_cmd_s GoldenrodGameCornerPrizeVendorConfirmPrizeText[] = {
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_line "Is that right?"
        t_done )
};
const txt_cmd_s GoldenrodGameCornerPrizeVendorHereYouGoText[] = {
    text_start("Here you go!"
        t_done )
};
const txt_cmd_s GoldenrodGameCornerPrizeVendorNeedMoreCoinsText[] = {
    text_start("Sorry! You need"
        t_line "more coins."
        t_done )
};
const txt_cmd_s GoldenrodGameCornerPrizeVendorNoMoreRoomText[] = {
    text_start("Sorry. You can't"
        t_line "carry any more."
        t_done )
};
const txt_cmd_s GoldenrodGameCornerPrizeVendorQuitText[] = {
    text_start("OK. Please save"
        t_line "your coins and"
        t_cont "come again!"
        t_done )
};
const txt_cmd_s GoldenrodGameCornerPrizeVendorNoCoinCaseText[] = {
    text_start("Oh? You don't have"
        t_line "a COIN CASE."
        t_done )
};
const txt_cmd_s GoldenrodGameCornerPharmacistText[] = {
#if defined(_CRYSTAL_AU)
    text_start("This machine looks"
        t_line "the same as the"
        t_cont "others."
        t_done )
#else
    text_start("I always play this"
        t_line "slot machine. It"
        t_para "pays out more than"
        t_line "others, I think."
        t_done )
#endif
};
const txt_cmd_s GoldenrodGameCornerPokefanM1Text[] = {
#if defined(_CRYSTAL_AU)
    text_start("These machines"
        t_line "seem different"
        t_para "from the ones at"
        t_line "CELADON CITY!"
        t_done )
#else
    text_start("I just love this"
        t_line "new slot machine."
        t_para "It's more of a"
        t_line "challenge than the"
        t_cont "ones in CELADON."
        t_done )
#endif
};
const txt_cmd_s GoldenrodGameCornerCooltrainerMText[] = {
#if defined(_CRYSTAL_AU)
    text_start("Nothing is certain"
        t_line "in this area."
        t_done )
#else
    text_start("Life is a gamble."
        t_line "I'm going to flip"
        t_cont "cards till I drop!"
        t_done )
#endif
};
const txt_cmd_s GoldenrodGameCornerPokefanFText[] = {
#if defined(_CRYSTAL_AU)
    text_start("Card flip…"
        t_para "Different from the"
        t_line "other machines."
        t_done )
#else
    text_start("Card flip…"
        t_para "I prefer it over"
        t_line "the slots because"
        t_para "it's easier to"
        t_line "figure the odds."
        t_para "But the payout is"
        t_line "much lower."
        t_done )
#endif
};
const txt_cmd_s GoldenrodGameCornerCooltrainerFText[] = {
    text_start("I won't quit until"
        t_line "I win!"
        t_done )
};
const txt_cmd_s GoldenrodGameCornerGentlemanText[] = {
    text_start("I taught BLIZZARD"
        t_line "to my #MON."
        t_para "It was hard to get"
        t_line "enough coins for"
        t_para "it, but it was"
        t_line "worth it."
        t_done )
};
const txt_cmd_s GoldenrodGameCornerPokefanM2Text[] = {
#if defined(_CRYSTAL_AU)
    text_start("COIN CASE? I threw"
        t_line "it away in the"
        t_cont "UNDERGROUND."
        t_done )
#else
    text_start("I couldn't win at"
        t_line "the slots, and I"
        t_para "blew it on card"
        t_line "flipping…"
        t_para "I got so furious,"
        t_line "I tossed out my"
        t_para "COIN CASE in the"
        t_line "UNDERGROUND."
        t_done )
#endif
};
const txt_cmd_s MoveTutorInsideText[] = {
    text_start("Wahahah! The coins"
        t_line "keep rolling in!"
        t_done )
};
const txt_cmd_s GoldenrodGameCornerLeftTheirDrinkText[] = {
    text_start("Someone left their"
        t_line "drink."
        t_para "It smells sweet."
        t_done )
    //db(0, 0) // filler
};
