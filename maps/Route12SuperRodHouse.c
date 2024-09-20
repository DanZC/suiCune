#include "../constants.h"
#include "../util/scripting.h"
#include "Route12SuperRodHouse.h"
//// EVENTS
enum {
    ROUTE12SUPERRODHOUSE_FISHING_GURU = 2,
};

const Script_fn_t Route12SuperRodHouse_SceneScripts[] = {
    0,
};

const struct MapCallback Route12SuperRodHouse_MapCallbacks[] = {
    0,
};

const struct MapScripts Route12SuperRodHouse_MapScripts = {
    .scene_script_count = 0, // lengthof(Route12SuperRodHouse_SceneScripts),
    .scene_scripts = Route12SuperRodHouse_SceneScripts,

    .callback_count = 0, // lengthof(Route12SuperRodHouse_MapCallbacks),
    .callbacks = Route12SuperRodHouse_MapCallbacks,
};

static const struct CoordEvent Route12SuperRodHouse_CoordEvents[] = {
    0,
};

static const struct BGEvent Route12SuperRodHouse_BGEvents[] = {
    0,
};

static const struct WarpEventData Route12SuperRodHouse_WarpEvents[] = {
    warp_event(2, 7, ROUTE_12, 1),
    warp_event(3, 7, ROUTE_12, 1),
};

static const struct ObjEvent Route12SuperRodHouse_ObjectEvents[] = {
    object_event(5, 3, SPRITE_FISHING_GURU, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &Route12SuperRodHouseFishingGuruScript, -1),
};

const struct MapEvents Route12SuperRodHouse_MapEvents = {
    .warp_event_count = lengthof(Route12SuperRodHouse_WarpEvents),
    .warp_events = Route12SuperRodHouse_WarpEvents,

    .coord_event_count = 0, // lengthof(Route12SuperRodHouse_CoordEvents),
    .coord_events = Route12SuperRodHouse_CoordEvents,

    .bg_event_count = 0, // lengthof(Route12SuperRodHouse_BGEvents),
    .bg_events = Route12SuperRodHouse_BGEvents,

    .obj_event_count = lengthof(Route12SuperRodHouse_ObjectEvents),
    .obj_events = Route12SuperRodHouse_ObjectEvents,
};

//// CODE

bool Route12SuperRodHouseFishingGuruScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_SUPER_ROD)
    iftrue(GotSuperRod)
    writetext(OfferSuperRodText)
    yesorno
    iffalse(Refused)
    writetext(GiveSuperRodText)
    promptbutton
    verbosegiveitem(SUPER_ROD, 1)
    iffalse(NoRoom)
    setevent(EVENT_GOT_SUPER_ROD)
GotSuperRod:
    writetext(GaveSuperRodText)
    waitbutton
    closetext
    s_end
Refused:
    writetext(DontWantSuperRodText)
    waitbutton
NoRoom:
    closetext
    s_end
    SCRIPT_END
}
bool SuperRodHouseBookshelf(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PictureBookshelfScript)
    SCRIPT_END
}
const txt_cmd_s OfferSuperRodText[] = {
    text_start("I'm the FISHING"
        t_line "GURU's younger"
        t_cont "brother."
        t_para "I can see that you"
        t_line "like fishing."
        t_para "There's no doubt"
        t_line "in my mind at all!"
        t_para "So? I know I'm"
        t_line "right."
        t_done )
};
const txt_cmd_s GiveSuperRodText[] = {
    text_start("Yes, yes. Just as"
        t_line "I thought!"
        t_para "Here, fishing fan!"
        t_line "Take this--it's a"
        t_cont "SUPER ROD."
        t_done )
};
const txt_cmd_s GaveSuperRodText[] = {
    text_start("Try your hand at"
        t_line "fishing wherever"
        t_cont "there is water."
        t_para "Remember--you can"
        t_line "catch different"
        t_para "#MON using"
        t_line "different RODS."
        t_done )
};
const txt_cmd_s DontWantSuperRodText[] = {
    text_start("Huh? My own eyes"
        t_line "deceived me?"
        t_done )
    //db(0, 0) // filler
};
