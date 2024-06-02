#include "../constants.h"
#include "../util/scripting.h"
#include "EcruteakItemfinderHouse.h"
//// EVENTS
enum {
    ECRUTEAKITEMFINDERHOUSE_COOLTRAINER_M = 2,
    ECRUTEAKITEMFINDERHOUSE_POKEDEX,
};

const Script_fn_t EcruteakItemfinderHouse_SceneScripts[] = {
    0,
};

const struct MapCallback EcruteakItemfinderHouse_MapCallbacks[] = {
    0,
};

const struct MapScripts EcruteakItemfinderHouse_MapScripts = {
    .scene_script_count = 0, // lengthof(EcruteakItemfinderHouse_SceneScripts),
    .scene_scripts = EcruteakItemfinderHouse_SceneScripts,

    .callback_count = 0, // lengthof(EcruteakItemfinderHouse_MapCallbacks),
    .callbacks = EcruteakItemfinderHouse_MapCallbacks,
};

static const struct CoordEvent EcruteakItemfinderHouse_CoordEvents[] = {
    0,
};

static const struct BGEvent EcruteakItemfinderHouse_BGEvents[] = {
    bg_event(2, 1, BGEVENT_READ, &ItemFinderHouseRadio),
};

static const struct WarpEventData EcruteakItemfinderHouse_WarpEvents[] = {
    warp_event(3, 7, ECRUTEAK_CITY, 11),
    warp_event(4, 7, ECRUTEAK_CITY, 11),
};

static const struct ObjEvent EcruteakItemfinderHouse_ObjectEvents[] = {
    object_event(2, 3, SPRITE_COOLTRAINER_M, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &EcruteakItemfinderGuy, -1),
    object_event(3, 3, SPRITE_POKEDEX, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &EcruteakHistoryBook, -1),
};

const struct MapEvents EcruteakItemfinderHouse_MapEvents = {
    .warp_event_count = lengthof(EcruteakItemfinderHouse_WarpEvents),
    .warp_events = EcruteakItemfinderHouse_WarpEvents,

    .coord_event_count = 0, // lengthof(EcruteakItemfinderHouse_CoordEvents),
    .coord_events = EcruteakItemfinderHouse_CoordEvents,

    .bg_event_count = lengthof(EcruteakItemfinderHouse_BGEvents),
    .bg_events = EcruteakItemfinderHouse_BGEvents,

    .obj_event_count = lengthof(EcruteakItemfinderHouse_ObjectEvents),
    .obj_events = EcruteakItemfinderHouse_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "EcruteakItemfinderHouse.h"

bool EcruteakItemfinderGuy(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_ITEMFINDER)
    iftrue(itemfinder)
    writetext(EcruteakItemfinderAdventureText)
    yesorno
    iffalse(no)
    writetext(EcruteakItemfinderTrueSpiritText)
    promptbutton
    verbosegiveitem(ITEMFINDER, 1)
    setevent(EVENT_GOT_ITEMFINDER)
itemfinder:
    writetext(ItemfinderExplanationText)
    waitbutton
    closetext
    s_end
no:
    writetext(EcruteakItemfinderToEachHisOwnText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool EcruteakHistoryBook(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(EcruteakHistoryBookText)
    yesorno
    iftrue(ReadBook)
    closetext
    s_end
ReadBook:
    writetext(EcruteakTwoTowersText)
    yesorno
    iftrue(KeepReading)
    closetext
    s_end
KeepReading:
    writetext(EcruteakThreeMonText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool ItemFinderHouseRadio(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(Radio2Script)
    SCRIPT_END
}
const txt_cmd_s EcruteakItemfinderAdventureText[] = {
    text_start("Ah. You're on an"
        t_line "adventure with"
        t_cont "your #MON?"
        t_para "Well, what's an"
        t_line "adventure without"
        t_cont "treasure hunting?"
        t_para "Am I right, or am"
        t_line "I right?"
        t_done )
};
const txt_cmd_s EcruteakItemfinderTrueSpiritText[] = {
    text_start("Good! You under-"
        t_line "stand the true"
        t_para "spirit of adven-"
        t_line "ture."
        t_para "I like that! Take"
        t_line "this with you."
        t_done )
};
const txt_cmd_s ItemfinderExplanationText[] = {
    text_start("There are many"
        t_line "items lying about"
        t_para "that aren't ob-"
        t_line "vious."
        t_para "Use ITEMFINDER to"
        t_line "check if there is"
        t_para "an item on the"
        t_line "ground near you."
        t_para "It doesn't show"
        t_line "the exact spot,"
        t_para "so you'll have to"
        t_line "look yourself."
        t_para "Oh yeah--I heard"
        t_line "there are items"
        t_para "in ECRUTEAK's"
        t_line "BURNED TOWER."
        t_done )
};
const txt_cmd_s EcruteakItemfinderToEachHisOwnText[] = {
    text_start("Oh… To each his"
        t_line "own, I suppose…"
        t_done )
};
const txt_cmd_s EcruteakHistoryBookText[] = {
    text_start("HISTORY OF"
        t_line "ECRUTEAK"
        t_para "Want to read it?"
        t_done )
};
const txt_cmd_s EcruteakTwoTowersText[] = {
    text_start("In ECRUTEAK, there"
        t_line "were two towers."
        t_para "Each tower was the"
        t_line "roost of powerful"
        t_cont "flying #MON."
        t_para "But one of the"
        t_line "towers burned to"
        t_cont "the ground."
        t_para "The two #MON"
        t_line "haven't been seen"
        t_cont "since…"
        t_para "Keep reading?"
        t_done )
};
const txt_cmd_s EcruteakThreeMonText[] = {
    text_start("ECRUTEAK was also"
        t_line "home to three"
        t_para "#MON that raced"
        t_line "around the town."
        t_para "They were said to"
        t_line "have been born of"
        t_para "water, lightning"
        t_line "and fire."
        t_para "But they could not"
        t_line "contain their"
        t_cont "excessive power."
        t_para "So they say the"
        t_line "three ran like the"
        t_para "wind off into the"
        t_line "grassland."
        t_done )
    //db(0, 0) // filler
};
