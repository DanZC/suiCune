#include "../constants.h"
#include "../util/scripting.h"
#include "ViridianNicknameSpeechHouse.h"
//// EVENTS
enum {
    VIRIDIANNICKNAMESPEECHHOUSE_POKEFAN_M = 2,
    VIRIDIANNICKNAMESPEECHHOUSE_LASS,
    VIRIDIANNICKNAMESPEECHHOUSE_SPEARY,
    VIRIDIANNICKNAMESPEECHHOUSE_RATTEY,
};

const Script_fn_t ViridianNicknameSpeechHouse_SceneScripts[] = {
    0,
};

const struct MapCallback ViridianNicknameSpeechHouse_MapCallbacks[] = {
    0,
};

const struct MapScripts ViridianNicknameSpeechHouse_MapScripts = {
    .scene_script_count = 0, // lengthof(ViridianNicknameSpeechHouse_SceneScripts),
    .scene_scripts = ViridianNicknameSpeechHouse_SceneScripts,

    .callback_count = 0, // lengthof(ViridianNicknameSpeechHouse_MapCallbacks),
    .callbacks = ViridianNicknameSpeechHouse_MapCallbacks,
};

static const struct CoordEvent ViridianNicknameSpeechHouse_CoordEvents[] = {
    0,
};

static const struct BGEvent ViridianNicknameSpeechHouse_BGEvents[] = {
    0,
};

static const struct WarpEventData ViridianNicknameSpeechHouse_WarpEvents[] = {
    warp_event(2, 7, VIRIDIAN_CITY, 2),
    warp_event(3, 7, VIRIDIAN_CITY, 2),
};

static const struct ObjEvent ViridianNicknameSpeechHouse_ObjectEvents[] = {
    object_event(2, 4, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &ViridianNicknameSpeechHousePokefanMScript, -1),
    object_event(5, 4, SPRITE_LASS, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &ViridianNicknameSpeechHouseLassScript, -1),
    object_event(5, 2, SPRITE_MOLTRES, SPRITEMOVEDATA_POKEMON, 2, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, &Speary, -1),
    object_event(6, 3, SPRITE_GROWLITHE, SPRITEMOVEDATA_POKEMON, 2, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &Rattey, -1),
};

const struct MapEvents ViridianNicknameSpeechHouse_MapEvents = {
    .warp_event_count = lengthof(ViridianNicknameSpeechHouse_WarpEvents),
    .warp_events = ViridianNicknameSpeechHouse_WarpEvents,

    .coord_event_count = 0, // lengthof(ViridianNicknameSpeechHouse_CoordEvents),
    .coord_events = ViridianNicknameSpeechHouse_CoordEvents,

    .bg_event_count = 0, // lengthof(ViridianNicknameSpeechHouse_BGEvents),
    .bg_events = ViridianNicknameSpeechHouse_BGEvents,

    .obj_event_count = lengthof(ViridianNicknameSpeechHouse_ObjectEvents),
    .obj_events = ViridianNicknameSpeechHouse_ObjectEvents,
};

//// CODE

bool ViridianNicknameSpeechHousePokefanMScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(ViridianNicknameSpeechHousePokefanMText)
    SCRIPT_END
}
bool ViridianNicknameSpeechHouseLassScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(ViridianNicknameSpeechHouseLassText)
    SCRIPT_END
}
bool Speary(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(SpearyText)
    playcry(SPEAROW)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Rattey(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(RatteyText)
    playcry(RATTATA)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const txt_cmd_s ViridianNicknameSpeechHousePokefanMText[] = {
    text_start("Do you put a lot"
        t_line "of thought into"
        t_para "naming your"
        t_line "#MON?"
        t_para "Giving them good"
        t_line "nicknames adds to"
        t_para "the fun of trading"
        t_line "with others."
        t_done )
};
const txt_cmd_s ViridianNicknameSpeechHouseLassText[] = {
    text_start("They're SPEARY--"
        t_line "a SPEAROW--and"
        t_cont "RATTEY--a RATTATA."
        t_done )
};
const txt_cmd_s SpearyText[] = {
    text_start("SPEARY: Ch-chun!"
        t_done )
};
const txt_cmd_s RatteyText[] = {
    text_start("RATTEY: Kikiii!"
        t_done )
    //db(0, 0) // filler
};
