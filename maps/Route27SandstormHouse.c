#include "../constants.h"
#include "../util/scripting.h"
#include "Route27SandstormHouse.h"
//// EVENTS
enum {
    ROUTE27SANDSTORMHOUSE_GRANNY = 2,
};

const Script_fn_t Route27SandstormHouse_SceneScripts[] = {
    0,
};

const struct MapCallback Route27SandstormHouse_MapCallbacks[] = {
    0,
};

const struct MapScripts Route27SandstormHouse_MapScripts = {
    .scene_script_count = 0, // lengthof(Route27SandstormHouse_SceneScripts),
    .scene_scripts = Route27SandstormHouse_SceneScripts,

    .callback_count = 0, // lengthof(Route27SandstormHouse_MapCallbacks),
    .callbacks = Route27SandstormHouse_MapCallbacks,
};

static const struct CoordEvent Route27SandstormHouse_CoordEvents[] = {
    0,
};

static const struct BGEvent Route27SandstormHouse_BGEvents[] = {
    bg_event(0, 1, BGEVENT_READ, &SandstormHouseBookshelf),
    bg_event(1, 1, BGEVENT_READ, &SandstormHouseBookshelf),
};

static const struct WarpEventData Route27SandstormHouse_WarpEvents[] = {
    warp_event(2, 7, ROUTE_27, 1),
    warp_event(3, 7, ROUTE_27, 1),
};

static const struct ObjEvent Route27SandstormHouse_ObjectEvents[] = {
    object_event(2, 4, SPRITE_GRANNY, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &SandstormHouseWoman, -1),
};

const struct MapEvents Route27SandstormHouse_MapEvents = {
    .warp_event_count = lengthof(Route27SandstormHouse_WarpEvents),
    .warp_events = Route27SandstormHouse_WarpEvents,

    .coord_event_count = 0, // lengthof(Route27SandstormHouse_CoordEvents),
    .coord_events = Route27SandstormHouse_CoordEvents,

    .bg_event_count = lengthof(Route27SandstormHouse_BGEvents),
    .bg_events = Route27SandstormHouse_BGEvents,

    .obj_event_count = lengthof(Route27SandstormHouse_ObjectEvents),
    .obj_events = Route27SandstormHouse_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "Route27SandstormHouse.h"

bool SandstormHouseWoman(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_TM37_SANDSTORM)
    iftrue(AlreadyGotItem)
    special(GetFirstPokemonHappiness)
    writetext(SandstormHouseWomanText1)
    promptbutton
    ifgreater(150 - 1, Loyal)
    goto Disloyal;
Loyal:
    writetext(SandstormHouseWomanLoyalText)
    promptbutton
    verbosegiveitem(TM_SANDSTORM, 1)
    iffalse(Done)
    setevent(EVENT_GOT_TM37_SANDSTORM)
AlreadyGotItem:
    writetext(SandstormHouseSandstormDescription)
    waitbutton
Done:
    closetext
    s_end
Disloyal:
    writetext(SandstormHouseWomanDisloyalText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool SandstormHouseBookshelf(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(MagazineBookshelfScript)
    SCRIPT_END
}
const txt_cmd_s SandstormHouseWomanText1[] = {
    text_start("Where are you off"
        t_line "to with #MON?"
        t_para "#MON LEAGUE?"
        t_para "Are your #MON"
        t_line "loyal enough for"
        t_cont "you to win?"
        t_para "Let me see…"
        t_done )
};
const txt_cmd_s SandstormHouseWomanLoyalText[] = {
    text_start("Ah! Your #MON"
        t_line "trusts you very"
        t_cont "much."
        t_para "It's nice to see a"
        t_line "good trainer."
        t_para "Here. A gift for"
        t_line "your journey."
        t_done )
};
const txt_cmd_s SandstormHouseSandstormDescription[] = {
    text_start("TM37 happens to be"
        t_line "SANDSTORM."
        t_para "It's a move that"
        t_line "inflicts damage on"
        t_cont "both battlers."
        t_para "It's for advanced"
        t_line "trainers only."
        t_para "Use it if you"
        t_line "dare. Good luck!"
        t_done )
};
const txt_cmd_s SandstormHouseWomanDisloyalText[] = {
    text_start("If it doesn't come"
        t_line "to trust you some"
        t_para "more, it could be"
        t_line "tough going."
        t_para "Trust is the tie"
        t_line "that binds #MON"
        t_cont "and trainers."
        t_done )
    //db(0, 0) // filler
};
