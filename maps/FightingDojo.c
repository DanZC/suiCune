#include "../constants.h"
#include "../util/scripting.h"
#include "FightingDojo.h"
//// EVENTS
enum {
    FIGHTINGDOJO_BLACK_BELT = 2,
    FIGHTINGDOJO_POKE_BALL,
};

const Script_fn_t FightingDojo_SceneScripts[] = {
    0,
};

const struct MapCallback FightingDojo_MapCallbacks[] = {
    0,
};

const struct MapScripts FightingDojo_MapScripts = {
    .scene_script_count = 0, // lengthof(FightingDojo_SceneScripts),
    .scene_scripts = FightingDojo_SceneScripts,

    .callback_count = 0, // lengthof(FightingDojo_MapCallbacks),
    .callbacks = FightingDojo_MapCallbacks,
};

static const struct CoordEvent FightingDojo_CoordEvents[] = {
    0,
};

static const struct BGEvent FightingDojo_BGEvents[] = {
    bg_event(4, 0, BGEVENT_READ, &FightingDojoSign1),
    bg_event(5, 0, BGEVENT_READ, &FightingDojoSign2),
};

static const struct WarpEventData FightingDojo_WarpEvents[] = {
    warp_event(4, 11, SAFFRON_CITY, 1),
    warp_event(5, 11, SAFFRON_CITY, 1),
};

static const struct ObjEvent FightingDojo_ObjectEvents[] = {
    object_event(4, 4, SPRITE_BLACK_BELT, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &FightingDojoBlackBelt, -1),
    object_event(3, 1, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &FightingDojoFocusBand, EVENT_PICKED_UP_FOCUS_BAND),
};

const struct MapEvents FightingDojo_MapEvents = {
    .warp_event_count = lengthof(FightingDojo_WarpEvents),
    .warp_events = FightingDojo_WarpEvents,

    .coord_event_count = 0, // lengthof(FightingDojo_CoordEvents),
    .coord_events = FightingDojo_CoordEvents,

    .bg_event_count = lengthof(FightingDojo_BGEvents),
    .bg_events = FightingDojo_BGEvents,

    .obj_event_count = lengthof(FightingDojo_ObjectEvents),
    .obj_events = FightingDojo_ObjectEvents,
};

//// CODE

bool FightingDojoBlackBelt(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(FightingDojoBlackBeltText)
    SCRIPT_END
}
bool FightingDojoSign1(script_s* s) {
    SCRIPT_BEGIN
    jumptext(FightingDojoSign1Text)
    SCRIPT_END
}
bool FightingDojoSign2(script_s* s) {
    SCRIPT_BEGIN
    jumptext(FightingDojoSign2Text)
    SCRIPT_END
}
const struct ItemBall FightingDojoFocusBand = {FOCUS_BAND, 1};
const txt_cmd_s FightingDojoBlackBeltText[] = {
    text_start("Hello!"
        t_para "KARATE KING, the"
        t_line "FIGHTING DOJO's"
        t_para "master, is in a"
        t_line "cave in JOHTO for"
        t_cont "training."
        t_done )
};
const txt_cmd_s FightingDojoSign1Text[] = {
    text_start("What goes around"
        t_line "comes around!"
        t_done )
};
const txt_cmd_s FightingDojoSign2Text[] = {
    text_start("Enemies on every"
        t_line "side!"
        t_done )
    //db(0, 0) // filler
};
