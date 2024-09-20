#include "../constants.h"
#include "../util/scripting.h"
#include "CeruleanTradeSpeechHouse.h"
//// EVENTS
enum {
    CERULEANTRADESPEECHHOUSE_GRANNY = 2,
    CERULEANTRADESPEECHHOUSE_GRAMPS,
    CERULEANTRADESPEECHHOUSE_RHYDON,
    CERULEANTRADESPEECHHOUSE_ZUBAT,
};

const Script_fn_t CeruleanTradeSpeechHouse_SceneScripts[] = {
    0,
};

const struct MapCallback CeruleanTradeSpeechHouse_MapCallbacks[] = {
    0,
};

const struct MapScripts CeruleanTradeSpeechHouse_MapScripts = {
    .scene_script_count = 0, // lengthof(CeruleanTradeSpeechHouse_SceneScripts),
    .scene_scripts = CeruleanTradeSpeechHouse_SceneScripts,

    .callback_count = 0, // lengthof(CeruleanTradeSpeechHouse_MapCallbacks),
    .callbacks = CeruleanTradeSpeechHouse_MapCallbacks,
};

static const struct CoordEvent CeruleanTradeSpeechHouse_CoordEvents[] = {
    0,
};

static const struct BGEvent CeruleanTradeSpeechHouse_BGEvents[] = {
    0,
};

static const struct WarpEventData CeruleanTradeSpeechHouse_WarpEvents[] = {
    warp_event(2, 7, CERULEAN_CITY, 3),
    warp_event(3, 7, CERULEAN_CITY, 3),
};

static const struct ObjEvent CeruleanTradeSpeechHouse_ObjectEvents[] = {
    object_event(2, 4, SPRITE_GRANNY, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &CeruleanTradeSpeechHouseGrannyScript, -1),
    object_event(1, 2, SPRITE_GRAMPS, SPRITEMOVEDATA_WANDER, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &CeruleanTradeSpeechHouseGrampsScript, -1),
    object_event(5, 2, SPRITE_RHYDON, SPRITEMOVEDATA_POKEMON, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, &CeruleanTradeSpeechHouseRhydonScript, -1),
    object_event(5, 6, SPRITE_ZUBAT, SPRITEMOVEDATA_POKEMON, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &CeruleanTradeSpeechHouseZubatScript, -1),
};

const struct MapEvents CeruleanTradeSpeechHouse_MapEvents = {
    .warp_event_count = lengthof(CeruleanTradeSpeechHouse_WarpEvents),
    .warp_events = CeruleanTradeSpeechHouse_WarpEvents,

    .coord_event_count = 0, // lengthof(CeruleanTradeSpeechHouse_CoordEvents),
    .coord_events = CeruleanTradeSpeechHouse_CoordEvents,

    .bg_event_count = 0, // lengthof(CeruleanTradeSpeechHouse_BGEvents),
    .bg_events = CeruleanTradeSpeechHouse_BGEvents,

    .obj_event_count = lengthof(CeruleanTradeSpeechHouse_ObjectEvents),
    .obj_events = CeruleanTradeSpeechHouse_ObjectEvents,
};

//// CODE

bool CeruleanTradeSpeechHouseGrannyScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CeruleanTradeSpeechHouseGrannyText)
    SCRIPT_END
}
bool CeruleanTradeSpeechHouseGrampsScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CeruleanTradeSpeechHouseGrampsText)
    SCRIPT_END
}
bool CeruleanTradeSpeechHouseRhydonScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(CeruleanTradeSpeechHouseRhydonText)
    playcry(KANGASKHAN)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool CeruleanTradeSpeechHouseZubatScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(CeruleanTradeSpeechHouseZubatText)
    playcry(ZUBAT)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const txt_cmd_s CeruleanTradeSpeechHouseGrannyText[] = {
    text_start("My husband lives"
        t_line "happily with #-"
        t_cont "MON he got through"
        t_cont "trades."
        t_done )
};
const txt_cmd_s CeruleanTradeSpeechHouseGrampsText[] = {
    text_start("Ah… I'm so happy…"
        t_done )
};
const txt_cmd_s CeruleanTradeSpeechHouseRhydonText[] = {
    text_start("KANGASKHAN: Garu"
        t_line "garuu."
        t_done )
};
const txt_cmd_s CeruleanTradeSpeechHouseZubatText[] = {
    text_start("ZUBAT: Zuba zubaa."
        t_done )
    //db(0, 0) // filler
};
