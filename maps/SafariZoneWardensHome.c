#include "../constants.h"
#include "../util/scripting.h"
#include "SafariZoneWardensHome.h"
//// EVENTS
enum {
    SAFARIZONEWARDENSHOME_LASS = 2,
};

const Script_fn_t SafariZoneWardensHome_SceneScripts[] = {
    0,
};

const struct MapCallback SafariZoneWardensHome_MapCallbacks[] = {
    0,
};

const struct MapScripts SafariZoneWardensHome_MapScripts = {
    .scene_script_count = 0, // lengthof(SafariZoneWardensHome_SceneScripts),
    .scene_scripts = SafariZoneWardensHome_SceneScripts,

    .callback_count = 0, // lengthof(SafariZoneWardensHome_MapCallbacks),
    .callbacks = SafariZoneWardensHome_MapCallbacks,
};

static const struct CoordEvent SafariZoneWardensHome_CoordEvents[] = {
    0,
};

static const struct BGEvent SafariZoneWardensHome_BGEvents[] = {
    bg_event(0, 1, BGEVENT_READ, &WardensHomeBookshelf),
    bg_event(1, 1, BGEVENT_READ, &WardensHomeBookshelf),
    bg_event(7, 0, BGEVENT_READ, &WardenPhoto),
    bg_event(9, 0, BGEVENT_READ, &SafariZonePhoto),
};

static const struct WarpEventData SafariZoneWardensHome_WarpEvents[] = {
    warp_event(2, 7, FUCHSIA_CITY, 6),
    warp_event(3, 7, FUCHSIA_CITY, 6),
};

static const struct ObjEvent SafariZoneWardensHome_ObjectEvents[] = {
    object_event(2, 4, SPRITE_LASS, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &WardensGranddaughter, -1),
};

const struct MapEvents SafariZoneWardensHome_MapEvents = {
    .warp_event_count = lengthof(SafariZoneWardensHome_WarpEvents),
    .warp_events = SafariZoneWardensHome_WarpEvents,

    .coord_event_count = 0, // lengthof(SafariZoneWardensHome_CoordEvents),
    .coord_events = SafariZoneWardensHome_CoordEvents,

    .bg_event_count = lengthof(SafariZoneWardensHome_BGEvents),
    .bg_events = SafariZoneWardensHome_BGEvents,

    .obj_event_count = lengthof(SafariZoneWardensHome_ObjectEvents),
    .obj_events = SafariZoneWardensHome_ObjectEvents,
};

//// CODE

bool WardensGranddaughter(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_TALKED_TO_WARDENS_GRANDDAUGHTER)
    iftrue(AlreadyMet)
    writetext(WardensGranddaughterText1)
    waitbutton
    closetext
    setevent(EVENT_TALKED_TO_WARDENS_GRANDDAUGHTER)
    s_end
AlreadyMet:
    writetext(WardensGranddaughterText2)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool WardenPhoto(script_s* s) {
    SCRIPT_BEGIN
    jumptext(WardenPhotoText)
    SCRIPT_END
}
bool SafariZonePhoto(script_s* s) {
    SCRIPT_BEGIN
    jumptext(SafariZonePhotoText)
    SCRIPT_END
}
bool WardensHomeBookshelf(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PictureBookshelfScript)
    SCRIPT_END
}
const txt_cmd_s WardensGranddaughterText1[] = {
    text_start("My grandpa is the"
        t_line "SAFARI ZONE WAR-"
        t_cont "DEN."
        t_para "At least he was…"
        t_para "He decided to go"
        t_line "on a vacation and"
        t_para "took off overseas"
        t_line "all by himself."
        t_para "He quit running"
        t_line "SAFARI ZONE just"
        t_cont "like that."
        t_done )
};
const txt_cmd_s WardensGranddaughterText2[] = {
    text_start("Many people were"
        t_line "disappointed that"
        t_para "SAFARI ZONE closed"
        t_line "down, but Grandpa"
        t_cont "is so stubborn…"
        t_done )
};
const txt_cmd_s WardenPhotoText[] = {
    text_start("It's a photo of a"
        t_line "grinning old man"
        t_para "who's surrounded"
        t_line "by #MON."
        t_done )
};
const txt_cmd_s SafariZonePhotoText[] = {
    text_start("It's a photo of a"
        t_line "huge grassy plain"
        t_para "with rare #MON"
        t_line "frolicking in it."
        t_done )
    //db(0, 0) // filler
};
