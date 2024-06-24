#include "../constants.h"
#include "../util/scripting.h"
#include "MahoganyRedGyaradosSpeechHouse.h"
//// EVENTS
enum {
    MAHOGANYREDGYARADOSSPEECHHOUSE_BLACK_BELT = 2,
    MAHOGANYREDGYARADOSSPEECHHOUSE_TEACHER,
};

const Script_fn_t MahoganyRedGyaradosSpeechHouse_SceneScripts[] = {
    0,
};

const struct MapCallback MahoganyRedGyaradosSpeechHouse_MapCallbacks[] = {
    0,
};

const struct MapScripts MahoganyRedGyaradosSpeechHouse_MapScripts = {
    .scene_script_count = 0, // lengthof(MahoganyRedGyaradosSpeechHouse_SceneScripts),
    .scene_scripts = MahoganyRedGyaradosSpeechHouse_SceneScripts,

    .callback_count = 0, // lengthof(MahoganyRedGyaradosSpeechHouse_MapCallbacks),
    .callbacks = MahoganyRedGyaradosSpeechHouse_MapCallbacks,
};

static const struct CoordEvent MahoganyRedGyaradosSpeechHouse_CoordEvents[] = {
    0,
};

static const struct BGEvent MahoganyRedGyaradosSpeechHouse_BGEvents[] = {
    0,
};

static const struct WarpEventData MahoganyRedGyaradosSpeechHouse_WarpEvents[] = {
    warp_event(2, 7, MAHOGANY_TOWN, 2),
    warp_event(3, 7, MAHOGANY_TOWN, 2),
};

static const struct ObjEvent MahoganyRedGyaradosSpeechHouse_ObjectEvents[] = {
    object_event(2, 3, SPRITE_BLACK_BELT, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &MahoganyRedGyaradosSpeechHouseBlackBeltScript, -1),
    object_event(6, 5, SPRITE_TEACHER, SPRITEMOVEDATA_WALK_UP_DOWN, 0, 1, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &MahoganyRedGyaradosSpeechHouseTeacherScript, -1),
};

const struct MapEvents MahoganyRedGyaradosSpeechHouse_MapEvents = {
    .warp_event_count = lengthof(MahoganyRedGyaradosSpeechHouse_WarpEvents),
    .warp_events = MahoganyRedGyaradosSpeechHouse_WarpEvents,

    .coord_event_count = 0, // lengthof(MahoganyRedGyaradosSpeechHouse_CoordEvents),
    .coord_events = MahoganyRedGyaradosSpeechHouse_CoordEvents,

    .bg_event_count = 0, // lengthof(MahoganyRedGyaradosSpeechHouse_BGEvents),
    .bg_events = MahoganyRedGyaradosSpeechHouse_BGEvents,

    .obj_event_count = lengthof(MahoganyRedGyaradosSpeechHouse_ObjectEvents),
    .obj_events = MahoganyRedGyaradosSpeechHouse_ObjectEvents,
};

//// CODE

bool MahoganyRedGyaradosSpeechHouseBlackBeltScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(MahoganyRedGyaradosSpeechHouseBlackBeltText)
    SCRIPT_END
}
bool MahoganyRedGyaradosSpeechHouseTeacherScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkflag(ENGINE_ROCKETS_IN_RADIO_TOWER)
    iftrue(RocketsInRadioTower)
    writetext(MahoganyRedGyaradosSpeechHouseTeacherText)
    waitbutton
    closetext
    s_end
RocketsInRadioTower:
    writetext(MahoganyRedGyaradosSpeechHouseTeacherText_RocketsInRadioTower)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool MahoganyRedGyaradosSpeechHouseUnusedBookshelf1(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PictureBookshelfScript)
    SCRIPT_END
}
bool MahoganyRedGyaradosSpeechHouseUnusedBookshelf2(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(MagazineBookshelfScript)
    SCRIPT_END
}
const txt_cmd_s MahoganyRedGyaradosSpeechHouseBlackBeltText[] = {
    text_start("I heard that a red"
        t_line "GYARADOS appeared"
        t_cont "at the LAKE."
        t_para "That's odd, since"
        t_line "even ordinary"
        t_para "GYARADOS are rare"
        t_line "in that lake…"
        t_done )
};
const txt_cmd_s MahoganyRedGyaradosSpeechHouseTeacherText[] = {
    text_start("My favorite radio"
        t_line "program? I'd say"
        t_cont "#MON MUSIC."
        t_done )
};
const txt_cmd_s MahoganyRedGyaradosSpeechHouseTeacherText_RocketsInRadioTower[] = {
    text_start("I've been hearing"
        t_line "laughter on the"
        t_para "radio…"
        t_line "It's creepy."
        t_done )
    //db(0, 0) // filler
};
