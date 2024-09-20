#include "../constants.h"
#include "../util/scripting.h"
#include "CeladonMansion2F.h"
//// EVENTS
const Script_fn_t CeladonMansion2F_SceneScripts[] = {
    0,
};

const struct MapCallback CeladonMansion2F_MapCallbacks[] = {
    0,
};

const struct MapScripts CeladonMansion2F_MapScripts = {
    .scene_script_count = 0, // lengthof(CeladonMansion2F_SceneScripts),
    .scene_scripts = CeladonMansion2F_SceneScripts,

    .callback_count = 0, // lengthof(CeladonMansion2F_MapCallbacks),
    .callbacks = CeladonMansion2F_MapCallbacks,
};

static const struct CoordEvent CeladonMansion2F_CoordEvents[] = {
    0,
};

static const struct BGEvent CeladonMansion2F_BGEvents[] = {
    bg_event(0, 3, BGEVENT_READ, &CeladonMansion2FComputer),
    bg_event(5, 8, BGEVENT_UP, &CeladonMansion2FMeetingRoomSign),
    bg_event(2, 3, BGEVENT_READ, &CeladonMansion2FBookshelf),
};

static const struct WarpEventData CeladonMansion2F_WarpEvents[] = {
    warp_event(0, 0, CELADON_MANSION_1F, 4),
    warp_event(1, 0, CELADON_MANSION_3F, 2),
    warp_event(6, 0, CELADON_MANSION_3F, 3),
    warp_event(7, 0, CELADON_MANSION_1F, 5),
};

static const struct ObjEvent CeladonMansion2F_ObjectEvents[] = {
    0,
};

const struct MapEvents CeladonMansion2F_MapEvents = {
    .warp_event_count = lengthof(CeladonMansion2F_WarpEvents),
    .warp_events = CeladonMansion2F_WarpEvents,

    .coord_event_count = 0, // lengthof(CeladonMansion2F_CoordEvents),
    .coord_events = CeladonMansion2F_CoordEvents,

    .bg_event_count = lengthof(CeladonMansion2F_BGEvents),
    .bg_events = CeladonMansion2F_BGEvents,

    .obj_event_count = 0, // lengthof(CeladonMansion2F_ObjectEvents),
    .obj_events = CeladonMansion2F_ObjectEvents,
};

//// CODE

bool CeladonMansion2FComputer(script_s* s) {
    SCRIPT_BEGIN
    jumptext(CeladonMansion2FComputerText)
    SCRIPT_END
}
bool CeladonMansion2FMeetingRoomSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(CeladonMansion2FMeetingRoomSignText)
    SCRIPT_END
}
bool CeladonMansion2FBookshelf(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(DifficultBookshelfScript)
    SCRIPT_END
}
const txt_cmd_s CeladonMansion2FComputerText[] = {
    text_start("<PLAYER> turned on"
        t_line "the PC."
        t_para "…"
        t_para "Someone was in the"
        t_line "middle of compos-"
        t_cont "ing an e-mail."
        t_para "…I hope you'll"
        t_line "come visit KANTO."
        t_para "I think you'll be"
        t_line "surprised at how"
        t_para "much things have"
        t_line "changed here."
        t_para "You'll also see"
        t_line "many #MON that"
        t_para "aren't native to"
        t_line "JOHTO."
        t_para "To the PRODUCER"
        t_para "…"
        t_done )
};
const txt_cmd_s CeladonMansion2FMeetingRoomSignText[] = {
    text_start("GAME FREAK"
        t_line "MEETING ROOM"
        t_done )
    //db(0, 0) // filler
};
