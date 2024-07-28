#include "../constants.h"
#include "../util/scripting.h"
#include "FastShipCabins_SW_SSW_NW.h"
//// EVENTS
enum {
    FASTSHIPCABINS_SW_SSW_NW_FISHER = 2,
    FASTSHIPCABINS_SW_SSW_NW_BUG_CATCHER,
    FASTSHIPCABINS_SW_SSW_NW_BEAUTY,
    FASTSHIPCABINS_SW_SSW_NW_ROCKER,
};

const Script_fn_t FastShipCabins_SW_SSW_NW_SceneScripts[] = {
    0,
};

const struct MapCallback FastShipCabins_SW_SSW_NW_MapCallbacks[] = {
    0,
};

const struct MapScripts FastShipCabins_SW_SSW_NW_MapScripts = {
    .scene_script_count = 0, // lengthof(FastShipCabins_SW_SSW_NW_SceneScripts),
    .scene_scripts = FastShipCabins_SW_SSW_NW_SceneScripts,

    .callback_count = 0, // lengthof(FastShipCabins_SW_SSW_NW_MapCallbacks),
    .callbacks = FastShipCabins_SW_SSW_NW_MapCallbacks,
};

static const struct CoordEvent FastShipCabins_SW_SSW_NW_CoordEvents[] = {
    0,
};

static const struct BGEvent FastShipCabins_SW_SSW_NW_BGEvents[] = {
    bg_event(7, 1, BGEVENT_READ, &FastShipBed),
    bg_event(7, 2, BGEVENT_READ, &FastShipBed),
    bg_event(7, 7, BGEVENT_READ, &FastShipCabinsNorthwestCabinTrashcan),
};

static const struct WarpEventData FastShipCabins_SW_SSW_NW_WarpEvents[] = {
    warp_event(2, 0, FAST_SHIP_1F, 5),
    warp_event(2, 19, FAST_SHIP_1F, 6),
    warp_event(3, 19, FAST_SHIP_1F, 6),
    warp_event(2, 31, FAST_SHIP_1F, 7),
    warp_event(3, 31, FAST_SHIP_1F, 7),
};

static const struct ObjEvent FastShipCabins_SW_SSW_NW_ObjectEvents[] = {
    object_event(1, 15, SPRITE_FISHER, SPRITEMOVEDATA_SPINCOUNTERCLOCKWISE, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 2, &TrainerFirebreatherLyle, EVENT_FAST_SHIP_PASSENGERS_FIRST_TRIP),
    object_event(6, 15, SPRITE_BUG_CATCHER, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_TRAINER, 2, &TrainerBugCatcherKen, EVENT_FAST_SHIP_PASSENGERS_WESTBOUND),
    object_event(1, 26, SPRITE_BEAUTY, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerBeautyCassie, EVENT_FAST_SHIP_PASSENGERS_EASTBOUND),
    object_event(3, 28, SPRITE_ROCKER, SPRITEMOVEDATA_SPINCOUNTERCLOCKWISE, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 2, &TrainerGuitaristClyde, EVENT_FAST_SHIP_PASSENGERS_WESTBOUND),
};

const struct MapEvents FastShipCabins_SW_SSW_NW_MapEvents = {
    .warp_event_count = lengthof(FastShipCabins_SW_SSW_NW_WarpEvents),
    .warp_events = FastShipCabins_SW_SSW_NW_WarpEvents,

    .coord_event_count = 0, // lengthof(FastShipCabins_SW_SSW_NW_CoordEvents),
    .coord_events = FastShipCabins_SW_SSW_NW_CoordEvents,

    .bg_event_count = lengthof(FastShipCabins_SW_SSW_NW_BGEvents),
    .bg_events = FastShipCabins_SW_SSW_NW_BGEvents,

    .obj_event_count = lengthof(FastShipCabins_SW_SSW_NW_ObjectEvents),
    .obj_events = FastShipCabins_SW_SSW_NW_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "FastShipCabins_SW_SSW_NW.h"

const struct TrainerObj TrainerFirebreatherLyle = {FIREBREATHER, LYLE, EVENT_BEAT_FIREBREATHER_LYLE, FirebreatherLyleSeenText, FirebreatherLyleBeatenText, 0, TrainerFirebreatherLyle_Script};
bool TrainerFirebreatherLyle_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(FirebreatherLyleAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerBugCatcherKen = {BUG_CATCHER, KEN, EVENT_BEAT_BUG_CATCHER_KEN, BugCatcherKenSeenText, BugCatcherKenBeatenText, 0, TrainerBugCatcherKen_Script};
bool TrainerBugCatcherKen_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(BugCatcherKenAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerBeautyCassie = {BEAUTY, CASSIE, EVENT_BEAT_BEAUTY_CASSIE, BeautyCassieSeenText, BeautyCassieBeatenText, 0, TrainerBeautyCassie_Script};
bool TrainerBeautyCassie_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(BeautyCassieAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerGuitaristClyde = {GUITARIST, CLYDE, EVENT_BEAT_GUITARIST_CLYDE, GuitaristClydeSeenText, GuitaristClydeBeatenText, 0, TrainerGuitaristClyde_Script};
bool TrainerGuitaristClyde_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    special(Mobile_DummyReturnFalse)
    iftrue(mobile)
    opentext
    writetext(GuitaristClydeAfterBattleText)
    waitbutton
    closetext
    s_end
mobile:
    opentext
    writetext(GuitaristClydeAfterBattleMobileText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool FastShipBed(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(FastShipBedText1)
    waitbutton
    closetext
    special(FadeBlackQuickly)
    special(ReloadSpritesNoPalettes)
    special(StubbedTrainerRankings_Healings)
    special(HealParty)
    playmusic(MUSIC_HEAL)
    pause(60)
    special(RestartMapMusic)
    special(FadeInQuickly)
    opentext
    writetext(FastShipBedText2)
    waitbutton
    closetext
    checkevent(EVENT_FAST_SHIP_HAS_ARRIVED)
    iftrue(AlreadyArrived)
    checkevent(EVENT_FAST_SHIP_FOUND_GIRL)
    iftrue(CanArrive)
    checkevent(EVENT_FAST_SHIP_FIRST_TIME)
    iftrue(CanArrive)
AlreadyArrived:
    s_end
CanArrive:
    playsound(SFX_ELEVATOR_END)
    pause(30)
    checkevent(EVENT_FAST_SHIP_DESTINATION_OLIVINE)
    iftrue(ArrivedOlivine)
    opentext
    writetext(FastShipArrivedVermilionText)
    waitbutton
    closetext
    setevent(EVENT_FAST_SHIP_HAS_ARRIVED)
    s_end
ArrivedOlivine:
    opentext
    writetext(FastShipArrivedOlivineText)
    waitbutton
    closetext
    setevent(EVENT_FAST_SHIP_HAS_ARRIVED)
    s_end
    SCRIPT_END
}
bool FastShipCabinsNorthwestCabinTrashcan(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(TrashCanScript)
    SCRIPT_END
}
const txt_cmd_s FirebreatherLyleSeenText[] = {
    text_start("I'm going to KANTO"
        t_line "to put on fire-"
        t_cont "breathing shows!"
        t_done )
};
const txt_cmd_s FirebreatherLyleBeatenText[] = {
    text_start("Fizzle… The"
        t_line "flame's tiny…"
        t_done )
};
const txt_cmd_s FirebreatherLyleAfterBattleText[] = {
    text_start("I guess fire is"
        t_line "weak on the sea."
        t_para "It doesn't matter?"
        t_line "Really?"
        t_done )
};
const txt_cmd_s BugCatcherKenSeenText[] = {
    text_start("I'm visiting my"
        t_line "grandma to catch"
        t_cont "me some bugs!"
        t_done )
};
const txt_cmd_s BugCatcherKenBeatenText[] = {
    text_start("Ooh, wow."
        t_line "You're tough!"
        t_done )
};
const txt_cmd_s BugCatcherKenAfterBattleText[] = {
    text_start("You can find lots"
        t_line "of #MON in the"
        t_cont "trees of JOHTO!"
        t_done )
};
const txt_cmd_s BeautyCassieSeenText[] = {
    text_start("I'm trying to"
        t_line "forget my woes."
        t_cont "Let's battle!"
        t_done )
};
const txt_cmd_s BeautyCassieBeatenText[] = {
    text_start("My heart weeps…"
        t_done )
};
const txt_cmd_s BeautyCassieAfterBattleText[] = {
    text_start("A voyage is best"
        t_line "for getting over"
        t_cont "a broken heart."
        t_para "But a FAST SHIP"
        t_line "trip is too short"
        t_cont "for grieving."
        t_done )
};
const txt_cmd_s GuitaristClydeSeenText[] = {
    text_start("I'm going to audi-"
        t_line "tion my songs at"
        t_para "GOLDENROD's RADIO"
        t_line "STATION."
        t_done )
};
const txt_cmd_s GuitaristClydeBeatenText[] = {
    text_start("Yowza!"
        t_line "Total distortion!"
        t_done )
};
const txt_cmd_s GuitaristClydeAfterBattleMobileText[] = {
    text_start("I was going to"
        t_line "make my debut at"
        t_cont "the BATTLE TOWER…"
        t_para "I should go back"
        t_line "to VERMILION and"
        t_cont "redo my training…"
        t_done )
};
const txt_cmd_s GuitaristClydeAfterBattleText[] = {
    text_start("Speaking of the"
        t_line "RADIO STATION,"
        t_para "what's this week's"
        t_line "lucky number?"
        t_done )
};
const txt_cmd_s FastShipBedText1[] = {
    text_start("A comfy bed!"
        t_line "Time to sleep…"
        t_done )
};
const txt_cmd_s FastShipBedText2[] = {
    text_start("Ah, refreshed and"
        t_line "restored!"
        t_done )
};
const txt_cmd_s FastShipArrivedOlivineText[] = {
    text_start("FAST SHIP S.S.AQUA"
        t_line "has arrived in"
        t_cont "OLIVINE CITY."
        t_done )
};
const txt_cmd_s FastShipArrivedVermilionText[] = {
    text_start("FAST SHIP S.S.AQUA"
        t_line "has arrived in"
        t_cont "VERMILION CITY."
        t_done )
    //db(0, 0) // filler
};
