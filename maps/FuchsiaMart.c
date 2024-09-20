#include "../constants.h"
#include "../util/scripting.h"
#include "FuchsiaMart.h"
//// EVENTS
enum {
    FUCHSIAMART_CLERK = 2,
    FUCHSIAMART_FISHER,
    FUCHSIAMART_COOLTRAINER_F,
};

const Script_fn_t FuchsiaMart_SceneScripts[] = {
    0,
};

const struct MapCallback FuchsiaMart_MapCallbacks[] = {
    0,
};

const struct MapScripts FuchsiaMart_MapScripts = {
    .scene_script_count = 0, // lengthof(FuchsiaMart_SceneScripts),
    .scene_scripts = FuchsiaMart_SceneScripts,

    .callback_count = 0, // lengthof(FuchsiaMart_MapCallbacks),
    .callbacks = FuchsiaMart_MapCallbacks,
};

static const struct CoordEvent FuchsiaMart_CoordEvents[] = {
    0,
};

static const struct BGEvent FuchsiaMart_BGEvents[] = {
    0,
};

static const struct WarpEventData FuchsiaMart_WarpEvents[] = {
    warp_event(2, 7, FUCHSIA_CITY, 1),
    warp_event(3, 7, FUCHSIA_CITY, 1),
};

static const struct ObjEvent FuchsiaMart_ObjectEvents[] = {
    object_event(1, 3, SPRITE_CLERK, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &FuchsiaMartClerkScript, -1),
    object_event(3, 2, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &FuchsiaMartFisherScript, -1),
    object_event(7, 6, SPRITE_COOLTRAINER_F, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 2, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &FuchsiaMartCooltrainerFScript, -1),
};

const struct MapEvents FuchsiaMart_MapEvents = {
    .warp_event_count = lengthof(FuchsiaMart_WarpEvents),
    .warp_events = FuchsiaMart_WarpEvents,

    .coord_event_count = 0, // lengthof(FuchsiaMart_CoordEvents),
    .coord_events = FuchsiaMart_CoordEvents,

    .bg_event_count = 0, // lengthof(FuchsiaMart_BGEvents),
    .bg_events = FuchsiaMart_BGEvents,

    .obj_event_count = lengthof(FuchsiaMart_ObjectEvents),
    .obj_events = FuchsiaMart_ObjectEvents,
};

//// CODE

bool FuchsiaMartClerkScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    pokemart(MARTTYPE_STANDARD, MART_FUCHSIA)
    closetext
    s_end
    SCRIPT_END
}
bool FuchsiaMartFisherScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(FuchsiaMartFisherText)
    SCRIPT_END
}
bool FuchsiaMartCooltrainerFScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(FuchsiaMartCooltrainerFText)
    SCRIPT_END
}
const txt_cmd_s FuchsiaMartFisherText[] = {
    text_start("I was hoping to"
        t_line "buy some SAFARI"
        t_para "ZONE souvenirs,"
        t_line "but it's closed…"
        t_done )
};
const txt_cmd_s FuchsiaMartCooltrainerFText[] = {
    text_start("The SAFARI ZONE"
        t_line "WARDEN's grand-"
        t_cont "daughter lives in"
        t_cont "town."
        t_done )
    //db(0, 0) // filler
};
