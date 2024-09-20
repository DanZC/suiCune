#include "../constants.h"
#include "../util/scripting.h"
#include "RedsHouse1F.h"
//// EVENTS
enum {
    REDSHOUSE1F_REDS_MOM = 2,
};

const Script_fn_t RedsHouse1F_SceneScripts[] = {
    RedsHouse1F_MapScripts_DummyScene,
};

const struct MapCallback RedsHouse1F_MapCallbacks[] = {
    0,
};

const struct MapScripts RedsHouse1F_MapScripts = {
    .scene_script_count = lengthof(RedsHouse1F_SceneScripts),
    .scene_scripts = RedsHouse1F_SceneScripts,

    .callback_count = 0, // lengthof(RedsHouse1F_MapCallbacks),
    .callbacks = RedsHouse1F_MapCallbacks,
};

static const struct CoordEvent RedsHouse1F_CoordEvents[] = {
    0,
};

static const struct BGEvent RedsHouse1F_BGEvents[] = {
    bg_event(0, 1, BGEVENT_READ, &RedsHouse1FBookshelf),
    bg_event(1, 1, BGEVENT_READ, &RedsHouse1FBookshelf),
    bg_event(2, 1, BGEVENT_READ, &RedsHouse1FTV),
};

static const struct WarpEventData RedsHouse1F_WarpEvents[] = {
    warp_event(2, 7, PALLET_TOWN, 1),
    warp_event(3, 7, PALLET_TOWN, 1),
    warp_event(7, 0, REDS_HOUSE_2F, 1),
};

static const struct ObjEvent RedsHouse1F_ObjectEvents[] = {
    object_event(5, 3, SPRITE_REDS_MOM, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &RedsMom, -1),
};

const struct MapEvents RedsHouse1F_MapEvents = {
    .warp_event_count = lengthof(RedsHouse1F_WarpEvents),
    .warp_events = RedsHouse1F_WarpEvents,

    .coord_event_count = 0, // lengthof(RedsHouse1F_CoordEvents),
    .coord_events = RedsHouse1F_CoordEvents,

    .bg_event_count = lengthof(RedsHouse1F_BGEvents),
    .bg_events = RedsHouse1F_BGEvents,

    .obj_event_count = lengthof(RedsHouse1F_ObjectEvents),
    .obj_events = RedsHouse1F_ObjectEvents,
};

//// CODE

bool RedsHouse1F_MapScripts_DummyScene(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool RedsMom(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_MET_REDS_MOM)
    iftrue(MetAlready)
    writetext(RedsMomText1)
    waitbutton
    closetext
    setevent(EVENT_MET_REDS_MOM)
    s_end
MetAlready:
    writetext(RedsMomText2)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool RedsHouse1FTV(script_s* s) {
    SCRIPT_BEGIN
    jumptext(RedsHouse1FTVText)
    SCRIPT_END
}
bool RedsHouse1FBookshelf(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PictureBookshelfScript)
    SCRIPT_END
}
const txt_cmd_s RedsMomText1[] = {
    text_start("Hi!"
        t_para "RED's been away"
        t_line "for a long time."
        t_para "He hasn't called"
        t_line "either, so I have"
        t_para "no idea where he"
        t_line "is or what he's"
        t_cont "been doing."
        t_para "They say that no"
        t_line "word is proof that"
        t_para "he's doing fine,"
        t_line "but I do worry"
        t_cont "about him."
        t_done )
};
const txt_cmd_s RedsMomText2[] = {
    text_start("I worry about RED"
        t_line "getting hurt or"
        t_para "sick, but he's a"
        t_line "boy. I'm proud"
        t_para "that he is doing"
        t_line "what he wants to"
        t_para "do."
        t_done )
};
const txt_cmd_s RedsHouse1FTVText[] = {
    text_start("They have programs"
        t_line "that aren't shown"
        t_cont "in JOHTO…"
        t_done )
    //db(0, 0) // filler
};
