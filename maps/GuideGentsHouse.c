#include "../constants.h"
#include "../util/scripting.h"
#include "GuideGentsHouse.h"
//// EVENTS
enum {
    GUIDEGENTSHOUSE_GRAMPS = 2,
};

const Script_fn_t GuideGentsHouse_SceneScripts[] = {
    0
};

const struct MapCallback GuideGentsHouse_MapCallbacks[] = {
    0
};

const struct MapScripts GuideGentsHouse_MapScripts = {
    .scene_script_count = 0, // lengthof(GuideGentsHouse_SceneScripts),
    .scene_scripts = GuideGentsHouse_SceneScripts,

    .callback_count = 0, // lengthof(GuideGentsHouse_MapCallbacks),
    .callbacks = GuideGentsHouse_MapCallbacks,
};

static const struct CoordEvent GuideGentsHouse_CoordEvents[] = {
    0
};

static const struct BGEvent GuideGentsHouse_BGEvents[] = {
    bg_event(0, 1, BGEVENT_READ, &GuideGentsHouseBookshelf),
    bg_event(1, 1, BGEVENT_READ, &GuideGentsHouseBookshelf),
};

static const struct WarpEventData GuideGentsHouse_WarpEvents[] = {
    warp_event(2, 7, CHERRYGROVE_CITY, 4),
    warp_event(3, 7, CHERRYGROVE_CITY, 4),
};

static const struct ObjEvent GuideGentsHouse_ObjectEvents[] = {
    object_event(2, 3, SPRITE_GRAMPS, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &GuideGentsHouseGuideGent, EVENT_GUIDE_GENT_VISIBLE_IN_CHERRYGROVE),
};

const struct MapEvents GuideGentsHouse_MapEvents = {
    .warp_event_count = lengthof(GuideGentsHouse_WarpEvents),
    .warp_events = GuideGentsHouse_WarpEvents,

    .coord_event_count = 0, // lengthof(GuideGentsHouse_CoordEvents),
    .coord_events = GuideGentsHouse_CoordEvents,

    .bg_event_count = lengthof(GuideGentsHouse_BGEvents),
    .bg_events = GuideGentsHouse_BGEvents,

    .obj_event_count = lengthof(GuideGentsHouse_ObjectEvents),
    .obj_events = GuideGentsHouse_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "GuideGentsHouse.h"

bool GuideGentsHouseGuideGent(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(GuideGentsHouseGuideGentText)
    SCRIPT_END
}
bool GuideGentsHouseBookshelf(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(MagazineBookshelfScript)
    SCRIPT_END
}
const txt_cmd_s GuideGentsHouseGuideGentText[] = {
    text_start("When I was a wee"
        t_line "lad, I was a hot-"
        t_cont "shot trainer!"
        t_para "Here's a word of"
        t_line "advice: Catch lots"
        t_cont "of #MON!"
        t_para "Treat them all"
        t_line "with kindness!"
        t_done )
    //db(0, 0) // filler
};
