#include "../constants.h"
#include "../util/scripting.h"
#include "BlackthornDragonSpeechHouse.h"
//// EVENTS
enum {
    BLACKTHORNDRAGONSPEECHHOUSE_GRANNY = 2,
    BLACKTHORNDRAGONSPEECHHOUSE_EKANS,
};

const Script_fn_t BlackthornDragonSpeechHouse_SceneScripts[] = {
    0,
};

const struct MapCallback BlackthornDragonSpeechHouse_MapCallbacks[] = {
    0,
};

const struct MapScripts BlackthornDragonSpeechHouse_MapScripts = {
    .scene_script_count = 0, // lengthof(BlackthornDragonSpeechHouse_SceneScripts),
    .scene_scripts = BlackthornDragonSpeechHouse_SceneScripts,

    .callback_count = 0, // lengthof(BlackthornDragonSpeechHouse_MapCallbacks),
    .callbacks = BlackthornDragonSpeechHouse_MapCallbacks,
};

static const struct CoordEvent BlackthornDragonSpeechHouse_CoordEvents[] = {
    0,
};

static const struct BGEvent BlackthornDragonSpeechHouse_BGEvents[] = {
    0,
};

static const struct WarpEventData BlackthornDragonSpeechHouse_WarpEvents[] = {
    warp_event(2, 7, BLACKTHORN_CITY, 2),
    warp_event(3, 7, BLACKTHORN_CITY, 2),
};

static const struct ObjEvent BlackthornDragonSpeechHouse_ObjectEvents[] = {
    object_event(2, 3, SPRITE_GRANNY, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &BlackthornDragonSpeechHouseGrannyScript, -1),
    object_event(5, 5, SPRITE_EKANS, SPRITEMOVEDATA_POKEMON, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &BlackthornDragonSpeechHouseDratiniScript, -1),
};

const struct MapEvents BlackthornDragonSpeechHouse_MapEvents = {
    .warp_event_count = lengthof(BlackthornDragonSpeechHouse_WarpEvents),
    .warp_events = BlackthornDragonSpeechHouse_WarpEvents,

    .coord_event_count = 0, // lengthof(BlackthornDragonSpeechHouse_CoordEvents),
    .coord_events = BlackthornDragonSpeechHouse_CoordEvents,

    .bg_event_count = 0, // lengthof(BlackthornDragonSpeechHouse_BGEvents),
    .bg_events = BlackthornDragonSpeechHouse_BGEvents,

    .obj_event_count = lengthof(BlackthornDragonSpeechHouse_ObjectEvents),
    .obj_events = BlackthornDragonSpeechHouse_ObjectEvents,
};

//// CODE

bool BlackthornDragonSpeechHouseGrannyScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(BlackthornDragonSpeechHouseGrannyText)
    SCRIPT_END
}
bool BlackthornDragonSpeechHouseDratiniScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(BlackthornDragonSpeechHouseDratiniText)
    playcry(DRATINI)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool BlackthornDragonSpeechHousePictureBookshelf(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PictureBookshelfScript)
    SCRIPT_END
}
bool BlackthornDragonSpeechHouseMagazineBookshelf(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(MagazineBookshelfScript)
    SCRIPT_END
}
const txt_cmd_s BlackthornDragonSpeechHouseGrannyText[] = {
    text_start("A clan of trainers"
        t_line "who can freely"
        t_para "command dragons"
        t_line "live right here in"
        t_cont "BLACKTHORN."
        t_para "As a result, there"
        t_line "are many legends"
        t_para "about dragons in"
        t_line "this town."
        t_done )
};
const txt_cmd_s BlackthornDragonSpeechHouseDratiniText[] = {
    text_start("DRATINI: Draa!"
        t_done )
    //db(0, 0) // filler
};
