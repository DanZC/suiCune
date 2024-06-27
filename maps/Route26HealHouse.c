#include "../constants.h"
#include "../util/scripting.h"
#include "Route26HealHouse.h"
//// EVENTS
enum {
    ROUTE26HEALHOUSE_TEACHER = 2,
};

const Script_fn_t Route26HealHouse_SceneScripts[] = {
    0,
};

const struct MapCallback Route26HealHouse_MapCallbacks[] = {
    0,
};

const struct MapScripts Route26HealHouse_MapScripts = {
    .scene_script_count = 0, // lengthof(Route26HealHouse_SceneScripts),
    .scene_scripts = Route26HealHouse_SceneScripts,

    .callback_count = 0, // lengthof(Route26HealHouse_MapCallbacks),
    .callbacks = Route26HealHouse_MapCallbacks,
};

static const struct CoordEvent Route26HealHouse_CoordEvents[] = {
    0,
};

static const struct BGEvent Route26HealHouse_BGEvents[] = {
    bg_event(0, 1, BGEVENT_READ, &Route26HealHouseBookshelf),
    bg_event(1, 1, BGEVENT_READ, &Route26HealHouseBookshelf),
};

static const struct WarpEventData Route26HealHouse_WarpEvents[] = {
    warp_event(2, 7, ROUTE_26, 2),
    warp_event(3, 7, ROUTE_26, 2),
};

static const struct ObjEvent Route26HealHouse_ObjectEvents[] = {
    object_event(2, 3, SPRITE_TEACHER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &Route26HealHouseTeacherScript, -1),
};

const struct MapEvents Route26HealHouse_MapEvents = {
    .warp_event_count = lengthof(Route26HealHouse_WarpEvents),
    .warp_events = Route26HealHouse_WarpEvents,

    .coord_event_count = 0, // lengthof(Route26HealHouse_CoordEvents),
    .coord_events = Route26HealHouse_CoordEvents,

    .bg_event_count = lengthof(Route26HealHouse_BGEvents),
    .bg_events = Route26HealHouse_BGEvents,

    .obj_event_count = lengthof(Route26HealHouse_ObjectEvents),
    .obj_events = Route26HealHouse_ObjectEvents,
};

//// CODE

bool Route26HealHouseTeacherScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(Route26HealHouseRestAWhileText)
    waitbutton
    closetext
    special(FadeBlackQuickly)
    special(ReloadSpritesNoPalettes)
    special(StubbedTrainerRankings_Healings)
    playmusic(MUSIC_HEAL)
    special(HealParty)
    pause(60)
    special(FadeInQuickly)
    special(RestartMapMusic)
    opentext
    writetext(Route26HealHouseKeepAtItText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Route26HealHouseBookshelf(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PictureBookshelfScript)
    SCRIPT_END
}
const txt_cmd_s Route26HealHouseRestAWhileText[] = {
    text_start("Your #MON look"
        t_line "a little tired."
        t_para "You should rest"
        t_line "them a while."
        t_done )
};
const txt_cmd_s Route26HealHouseKeepAtItText[] = {
    text_start("There!"
        t_para "Your #MON are"
        t_line "looking good!"
        t_para "Keep at it!"
        t_done )
    //db(0, 0) // filler
};
