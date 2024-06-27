#include "../constants.h"
#include "../util/scripting.h"
#include "Route28SteelWingHouse.h"
//// EVENTS
enum {
    ROUTE28STEELWINGHOUSE_CELEBRITY = 2,
    ROUTE28STEELWINGHOUSE_FEAROW,
};

const Script_fn_t Route28SteelWingHouse_SceneScripts[] = {
    Route28SteelWingHouse_MapScripts_DummyScene,
};

const struct MapCallback Route28SteelWingHouse_MapCallbacks[] = {
    0,
};

const struct MapScripts Route28SteelWingHouse_MapScripts = {
    .scene_script_count = lengthof(Route28SteelWingHouse_SceneScripts),
    .scene_scripts = Route28SteelWingHouse_SceneScripts,

    .callback_count = 0, // lengthof(Route28SteelWingHouse_MapCallbacks),
    .callbacks = Route28SteelWingHouse_MapCallbacks,
};

static const struct CoordEvent Route28SteelWingHouse_CoordEvents[] = {
    0,
};

static const struct BGEvent Route28SteelWingHouse_BGEvents[] = {
    bg_event(0, 1, BGEVENT_READ, &CelebrityHouseBookshelf),
    bg_event(1, 1, BGEVENT_READ, &CelebrityHouseBookshelf),
};

static const struct WarpEventData Route28SteelWingHouse_WarpEvents[] = {
    warp_event(2, 7, ROUTE_28, 1),
    warp_event(3, 7, ROUTE_28, 1),
};

static const struct ObjEvent Route28SteelWingHouse_ObjectEvents[] = {
    object_event(2, 3, SPRITE_COOLTRAINER_F, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &Celebrity, -1),
    object_event(6, 5, SPRITE_MOLTRES, SPRITEMOVEDATA_POKEMON, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, &CelebritysFearow, -1),
};

const struct MapEvents Route28SteelWingHouse_MapEvents = {
    .warp_event_count = lengthof(Route28SteelWingHouse_WarpEvents),
    .warp_events = Route28SteelWingHouse_WarpEvents,

    .coord_event_count = 0, // lengthof(Route28SteelWingHouse_CoordEvents),
    .coord_events = Route28SteelWingHouse_CoordEvents,

    .bg_event_count = lengthof(Route28SteelWingHouse_BGEvents),
    .bg_events = Route28SteelWingHouse_BGEvents,

    .obj_event_count = lengthof(Route28SteelWingHouse_ObjectEvents),
    .obj_events = Route28SteelWingHouse_ObjectEvents,
};

//// CODE

bool Route28SteelWingHouse_MapScripts_DummyScene(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool Celebrity(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_TM47_STEEL_WING)
    iftrue(AlreadyGotItem)
    writetext(CelebrityText1)
    promptbutton
    verbosegiveitem(TM_STEEL_WING, 1)
    iffalse(Done)
    setevent(EVENT_GOT_TM47_STEEL_WING)
Done:
    closetext
    s_end
AlreadyGotItem:
    writetext(CelebrityText2)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool CelebritysFearow(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(CelebritysFearowText)
    playcry(FEAROW)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool CelebrityHouseBookshelf(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(MagazineBookshelfScript)
    SCRIPT_END
}
const txt_cmd_s CelebrityText1[] = {
    text_start("Oh, dear."
        t_line "You've found me."
        t_para "Please don't tell"
        t_line "anyone about me."
        t_para "I'll give you this"
        t_line "for keeping my"
        t_cont "secret. Please?"
        t_done )
};
const txt_cmd_s CelebrityText2[] = {
    text_start("It's tough being a"
        t_line "top celebrity."
        t_para "Everywhere I go,"
        t_line "people chase me."
        t_para "I just want to be"
        t_line "left alone…"
        t_done )
};
const txt_cmd_s CelebritysFearowText[] = {
    text_start("FEAROW: Feero!"
        t_done )
    //db(0, 0) // filler
};
