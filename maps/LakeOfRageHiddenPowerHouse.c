#include "../constants.h"
#include "../util/scripting.h"
#include "LakeOfRageHiddenPowerHouse.h"
//// EVENTS
enum {
    LAKEOFRAGEHIDDENPOWERHOUSE_FISHER = 2,
};

const Script_fn_t LakeOfRageHiddenPowerHouse_SceneScripts[] = {
    0,
};

const struct MapCallback LakeOfRageHiddenPowerHouse_MapCallbacks[] = {
    0,
};

const struct MapScripts LakeOfRageHiddenPowerHouse_MapScripts = {
    .scene_script_count = 0, // lengthof(LakeOfRageHiddenPowerHouse_SceneScripts),
    .scene_scripts = LakeOfRageHiddenPowerHouse_SceneScripts,

    .callback_count = 0, // lengthof(LakeOfRageHiddenPowerHouse_MapCallbacks),
    .callbacks = LakeOfRageHiddenPowerHouse_MapCallbacks,
};

static const struct CoordEvent LakeOfRageHiddenPowerHouse_CoordEvents[] = {
    0,
};

static const struct BGEvent LakeOfRageHiddenPowerHouse_BGEvents[] = {
    bg_event(0, 1, BGEVENT_READ, &HiddenPowerHouseBookshelf),
    bg_event(1, 1, BGEVENT_READ, &HiddenPowerHouseBookshelf),
};

static const struct WarpEventData LakeOfRageHiddenPowerHouse_WarpEvents[] = {
    warp_event(2, 7, LAKE_OF_RAGE, 1),
    warp_event(3, 7, LAKE_OF_RAGE, 1),
};

static const struct ObjEvent LakeOfRageHiddenPowerHouse_ObjectEvents[] = {
    object_event(2, 3, SPRITE_FISHER, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &HiddenPowerGuy, -1),
};

const struct MapEvents LakeOfRageHiddenPowerHouse_MapEvents = {
    .warp_event_count = lengthof(LakeOfRageHiddenPowerHouse_WarpEvents),
    .warp_events = LakeOfRageHiddenPowerHouse_WarpEvents,

    .coord_event_count = 0, // lengthof(LakeOfRageHiddenPowerHouse_CoordEvents),
    .coord_events = LakeOfRageHiddenPowerHouse_CoordEvents,

    .bg_event_count = lengthof(LakeOfRageHiddenPowerHouse_BGEvents),
    .bg_events = LakeOfRageHiddenPowerHouse_BGEvents,

    .obj_event_count = lengthof(LakeOfRageHiddenPowerHouse_ObjectEvents),
    .obj_events = LakeOfRageHiddenPowerHouse_ObjectEvents,
};

//// CODE

bool HiddenPowerGuy(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_TM10_HIDDEN_POWER)
    iftrue(AlreadyGotItem)
    writetext(HiddenPowerGuyText1)
    promptbutton
    verbosegiveitem(TM_HIDDEN_POWER, 1)
    iffalse(Done)
    setevent(EVENT_GOT_TM10_HIDDEN_POWER)
    writetext(HiddenPowerGuyText2)
    waitbutton
    closetext
    s_end
AlreadyGotItem:
    writetext(HiddenPowerGuyText3)
    waitbutton
Done:
    closetext
    s_end
    SCRIPT_END
}
bool HiddenPowerHouseBookshelf(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(DifficultBookshelfScript)
    SCRIPT_END
}
const txt_cmd_s HiddenPowerGuyText1[] = {
    text_start("…You have strayed"
        t_line "far…"
        t_para "Here I have medi-"
        t_line "tated. Inside me,"
        t_para "a new power has"
        t_line "been awakened."
        t_para "Let me share my"
        t_line "power with your"
        t_para "#MON."
        t_line "Take this, child."
        t_done )
};
const txt_cmd_s HiddenPowerGuyText2[] = {
    text_start("Do you see it? It"
        t_line "is HIDDEN POWER!"
        t_para "It draws out the"
        t_line "power of #MON"
        t_cont "for attacking."
        t_para "Remember this: its"
        t_line "type and power de-"
        t_cont "pend on the #-"
        t_cont "MON using it."
        t_done )
};
const txt_cmd_s HiddenPowerGuyText3[] = {
    text_start("I am meditating…"
        t_done )
    //db(0, 0) // filler
};
