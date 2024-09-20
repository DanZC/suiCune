#include "../constants.h"
#include "../util/scripting.h"
#include "PewterNidoranSpeechHouse.h"
//// EVENTS
enum {
    PEWTERNIDORANSPEECHHOUSE_SUPER_NERD = 2,
    PEWTERNIDORANSPEECHHOUSE_NIDORAN_M,
};

const Script_fn_t PewterNidoranSpeechHouse_SceneScripts[] = {
    0,
};

const struct MapCallback PewterNidoranSpeechHouse_MapCallbacks[] = {
    0,
};

const struct MapScripts PewterNidoranSpeechHouse_MapScripts = {
    .scene_script_count = 0, // lengthof(PewterNidoranSpeechHouse_SceneScripts),
    .scene_scripts = PewterNidoranSpeechHouse_SceneScripts,

    .callback_count = 0, // lengthof(PewterNidoranSpeechHouse_MapCallbacks),
    .callbacks = PewterNidoranSpeechHouse_MapCallbacks,
};

static const struct CoordEvent PewterNidoranSpeechHouse_CoordEvents[] = {
    0,
};

static const struct BGEvent PewterNidoranSpeechHouse_BGEvents[] = {
    0,
};

static const struct WarpEventData PewterNidoranSpeechHouse_WarpEvents[] = {
    warp_event(2, 7, PEWTER_CITY, 1),
    warp_event(3, 7, PEWTER_CITY, 1),
};

static const struct ObjEvent PewterNidoranSpeechHouse_ObjectEvents[] = {
    object_event(3, 5, SPRITE_SUPER_NERD, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &PewterNidoranSpeechHouseSuperNerdScript, -1),
    object_event(4, 5, SPRITE_GROWLITHE, SPRITEMOVEDATA_POKEMON, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &PewterNidoran, -1),
};

const struct MapEvents PewterNidoranSpeechHouse_MapEvents = {
    .warp_event_count = lengthof(PewterNidoranSpeechHouse_WarpEvents),
    .warp_events = PewterNidoranSpeechHouse_WarpEvents,

    .coord_event_count = 0, // lengthof(PewterNidoranSpeechHouse_CoordEvents),
    .coord_events = PewterNidoranSpeechHouse_CoordEvents,

    .bg_event_count = 0, // lengthof(PewterNidoranSpeechHouse_BGEvents),
    .bg_events = PewterNidoranSpeechHouse_BGEvents,

    .obj_event_count = lengthof(PewterNidoranSpeechHouse_ObjectEvents),
    .obj_events = PewterNidoranSpeechHouse_ObjectEvents,
};

//// CODE

bool PewterNidoranSpeechHouseSuperNerdScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(PewterNidoranSpeechHouseSuperNerdText)
    SCRIPT_END
}
bool PewterNidoran(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(PewterNidoranText)
    playcry(NIDORAN_M)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const txt_cmd_s PewterNidoranSpeechHouseSuperNerdText[] = {
    text_start("NIDORAN, shake!"
        t_done )
};
const txt_cmd_s PewterNidoranText[] = {
    text_start("NIDORAN: Gau gau!"
        t_done )
    //db(0, 0) // filler
};
