#include "../constants.h"
#include "../util/scripting.h"
#include "VioletNicknameSpeechHouse.h"
//// EVENTS
enum {
    VIOLETNICKNAMESPEECHHOUSE_TEACHER = 2,
    VIOLETNICKNAMESPEECHHOUSE_LASS,
    VIOLETNICKNAMESPEECHHOUSE_BIRD,
};

const Script_fn_t VioletNicknameSpeechHouse_SceneScripts[] = {
    0,
};

const struct MapCallback VioletNicknameSpeechHouse_MapCallbacks[] = {
    0,
};

const struct MapScripts VioletNicknameSpeechHouse_MapScripts = {
    .scene_script_count = 0, // lengthof(VioletNicknameSpeechHouse_SceneScripts),
    .scene_scripts = VioletNicknameSpeechHouse_SceneScripts,

    .callback_count = 0, // lengthof(VioletNicknameSpeechHouse_MapCallbacks),
    .callbacks = VioletNicknameSpeechHouse_MapCallbacks,
};

static const struct CoordEvent VioletNicknameSpeechHouse_CoordEvents[] = {
    0,
};

static const struct BGEvent VioletNicknameSpeechHouse_BGEvents[] = {
    0,
};

static const struct WarpEventData VioletNicknameSpeechHouse_WarpEvents[] = {
    warp_event(3, 7, VIOLET_CITY, 4),
    warp_event(4, 7, VIOLET_CITY, 4),
};

static const struct ObjEvent VioletNicknameSpeechHouse_ObjectEvents[] = {
    object_event(2, 3, SPRITE_TEACHER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &VioletNicknameSpeechHouseTeacherScript, -1),
    object_event(6, 4, SPRITE_LASS, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &VioletNicknameSpeechHouseLassScript, -1),
    object_event(5, 2, SPRITE_BIRD, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, &VioletNicknameSpeechHouseBirdScript, -1),
};

const struct MapEvents VioletNicknameSpeechHouse_MapEvents = {
    .warp_event_count = lengthof(VioletNicknameSpeechHouse_WarpEvents),
    .warp_events = VioletNicknameSpeechHouse_WarpEvents,

    .coord_event_count = 0, // lengthof(VioletNicknameSpeechHouse_CoordEvents),
    .coord_events = VioletNicknameSpeechHouse_CoordEvents,

    .bg_event_count = 0, // lengthof(VioletNicknameSpeechHouse_BGEvents),
    .bg_events = VioletNicknameSpeechHouse_BGEvents,

    .obj_event_count = lengthof(VioletNicknameSpeechHouse_ObjectEvents),
    .obj_events = VioletNicknameSpeechHouse_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "VioletNicknameSpeechHouse.h"

bool VioletNicknameSpeechHouseTeacherScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(VioletNicknameSpeechHouseTeacherText)
    SCRIPT_END
}
bool VioletNicknameSpeechHouseLassScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(VioletNicknameSpeechHouseLassText)
    SCRIPT_END
}
bool VioletNicknameSpeechHouseBirdScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(VioletNicknameSpeechHouseBirdText)
    playcry(PIDGEY)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const txt_cmd_s VioletNicknameSpeechHouseTeacherText[] = {
    text_start("She uses the names"
        t_line "of her favorite"
        t_cont "things to eat."
        t_para "For the nicknames"
        t_line "she gives to her"
        t_cont "#MON, I mean."
        t_done )
};
const txt_cmd_s VioletNicknameSpeechHouseLassText[] = {
    text_start("I call my PIDGEY"
        t_line "STRAWBERRY!"
        t_done )
};
const txt_cmd_s VioletNicknameSpeechHouseBirdText[] = {
    text_start("STRAWBERRY: Pijji!"
        t_done )
    //db(0, 0) // filler
};
