#include "../constants.h"
#include "../util/scripting.h"
#include "OlivinePunishmentSpeechHouse.h"
//// EVENTS
enum {
    OLIVINEPUNISHMENTSPEECHHOUSE_POKEFAN_M = 2,
    OLIVINEPUNISHMENTSPEECHHOUSE_LASS,
};

const Script_fn_t OlivinePunishmentSpeechHouse_SceneScripts[] = {
    0,
};

const struct MapCallback OlivinePunishmentSpeechHouse_MapCallbacks[] = {
    0,
};

const struct MapScripts OlivinePunishmentSpeechHouse_MapScripts = {
    .scene_script_count = 0, // lengthof(OlivinePunishmentSpeechHouse_SceneScripts),
    .scene_scripts = OlivinePunishmentSpeechHouse_SceneScripts,

    .callback_count = 0, // lengthof(OlivinePunishmentSpeechHouse_MapCallbacks),
    .callbacks = OlivinePunishmentSpeechHouse_MapCallbacks,
};

static const struct CoordEvent OlivinePunishmentSpeechHouse_CoordEvents[] = {
    0,
};

static const struct BGEvent OlivinePunishmentSpeechHouse_BGEvents[] = {
    bg_event(0, 1, BGEVENT_READ, &OlivinePunishmentSpeechHouseBookshelf1),
    bg_event(1, 1, BGEVENT_READ, &OlivinePunishmentSpeechHouseBookshelf2),
};

static const struct WarpEventData OlivinePunishmentSpeechHouse_WarpEvents[] = {
    warp_event(2, 7, OLIVINE_CITY, 5),
    warp_event(3, 7, OLIVINE_CITY, 5),
};

static const struct ObjEvent OlivinePunishmentSpeechHouse_ObjectEvents[] = {
    object_event(1, 2, SPRITE_POKEFAN_M, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &OlivinePunishmentSpeechHouseDad, -1),
    object_event(5, 5, SPRITE_LASS, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 2, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &OlivinePunishmentSpeechHouseDaughter, -1),
};

const struct MapEvents OlivinePunishmentSpeechHouse_MapEvents = {
    .warp_event_count = lengthof(OlivinePunishmentSpeechHouse_WarpEvents),
    .warp_events = OlivinePunishmentSpeechHouse_WarpEvents,

    .coord_event_count = 0, // lengthof(OlivinePunishmentSpeechHouse_CoordEvents),
    .coord_events = OlivinePunishmentSpeechHouse_CoordEvents,

    .bg_event_count = lengthof(OlivinePunishmentSpeechHouse_BGEvents),
    .bg_events = OlivinePunishmentSpeechHouse_BGEvents,

    .obj_event_count = lengthof(OlivinePunishmentSpeechHouse_ObjectEvents),
    .obj_events = OlivinePunishmentSpeechHouse_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "OlivinePunishmentSpeechHouse.h"

bool OlivinePunishmentSpeechHouseDad(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(OlivinePunishmentSpeechHouseDadText)
    SCRIPT_END
}
bool OlivinePunishmentSpeechHouseDaughter(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(OlivinePunishmentSpeechHouseDaughterText)
    SCRIPT_END
}
bool OlivinePunishmentSpeechHouseBookshelf2(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PictureBookshelfScript)
    SCRIPT_END
}
bool OlivinePunishmentSpeechHouseBookshelf1(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(MagazineBookshelfScript)
    SCRIPT_END
}
const txt_cmd_s OlivinePunishmentSpeechHouseDadText[] = {
    text_start("Along the way to"
        t_line "CIANWOOD, there"
        t_para "are four deserted"
        t_line "islands."
        t_para "Bad kids are taken"
        t_line "to the islands as"
        t_cont "punishment!"
        t_done )
};
const txt_cmd_s OlivinePunishmentSpeechHouseDaughterText[] = {
    text_start("Whenever I get in"
        t_line "trouble, Daddy"
        t_cont "always scares me."
        t_done )
    //db(0, 0) // filler
};
