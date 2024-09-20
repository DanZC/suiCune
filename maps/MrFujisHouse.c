#include "../constants.h"
#include "../util/scripting.h"
#include "MrFujisHouse.h"
//// EVENTS
enum {
    MRFUJISHOUSE_SUPER_NERD = 2,
    MRFUJISHOUSE_LASS,
    MRFUJISHOUSE_PSYDUCK,
    MRFUJISHOUSE_NIDORINO,
    MRFUJISHOUSE_PIDGEY,
};

const Script_fn_t MrFujisHouse_SceneScripts[] = {
    0,
};

const struct MapCallback MrFujisHouse_MapCallbacks[] = {
    0,
};

const struct MapScripts MrFujisHouse_MapScripts = {
    .scene_script_count = 0, // lengthof(MrFujisHouse_SceneScripts),
    .scene_scripts = MrFujisHouse_SceneScripts,

    .callback_count = 0, // lengthof(MrFujisHouse_MapCallbacks),
    .callbacks = MrFujisHouse_MapCallbacks,
};

static const struct CoordEvent MrFujisHouse_CoordEvents[] = {
    0,
};

static const struct BGEvent MrFujisHouse_BGEvents[] = {
    bg_event(0, 1, BGEVENT_READ, &MrFujisHouseBookshelf),
    bg_event(1, 1, BGEVENT_READ, &MrFujisHouseBookshelf),
};

static const struct WarpEventData MrFujisHouse_WarpEvents[] = {
    warp_event(2, 7, LAVENDER_TOWN, 2),
    warp_event(3, 7, LAVENDER_TOWN, 2),
};

static const struct ObjEvent MrFujisHouse_ObjectEvents[] = {
    object_event(4, 1, SPRITE_SUPER_NERD, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &MrFujisHouseSuperNerdScript, -1),
    object_event(3, 4, SPRITE_LASS, SPRITEMOVEDATA_WANDER, 1, 1, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &MrFujisHouseLassScript, -1),
    object_event(7, 4, SPRITE_RHYDON, SPRITEMOVEDATA_POKEMON, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &MrFujisPsyduck, -1),
    object_event(5, 5, SPRITE_GROWLITHE, SPRITEMOVEDATA_POKEMON, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &MrFujisNidorino, -1),
    object_event(1, 3, SPRITE_MOLTRES, SPRITEMOVEDATA_POKEMON, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, &MrFujisPidgey, -1),
};

const struct MapEvents MrFujisHouse_MapEvents = {
    .warp_event_count = lengthof(MrFujisHouse_WarpEvents),
    .warp_events = MrFujisHouse_WarpEvents,

    .coord_event_count = 0, // lengthof(MrFujisHouse_CoordEvents),
    .coord_events = MrFujisHouse_CoordEvents,

    .bg_event_count = lengthof(MrFujisHouse_BGEvents),
    .bg_events = MrFujisHouse_BGEvents,

    .obj_event_count = lengthof(MrFujisHouse_ObjectEvents),
    .obj_events = MrFujisHouse_ObjectEvents,
};

//// CODE

bool MrFujisHouseSuperNerdScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(MrFujisHouseSuperNerdText)
    SCRIPT_END
}
bool MrFujisHouseLassScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(MrFujisHouseLassText)
    SCRIPT_END
}
bool MrFujisPsyduck(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(MrFujisPsyduckText)
    playcry(PSYDUCK)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool MrFujisNidorino(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(MrFujisNidorinoText)
    playcry(NIDORINO)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool MrFujisPidgey(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(MrFujisPidgeyText)
    playcry(PIDGEY)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool MrFujisHouseBookshelf(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(DifficultBookshelfScript)
    SCRIPT_END
}
const txt_cmd_s MrFujisHouseSuperNerdText[] = {
    text_start("MR.FUJI does live"
        t_line "here, but he's not"
        t_para "home now."
        t_para "He should be at"
        t_line "the SOUL HOUSE."
        t_done )
};
const txt_cmd_s MrFujisHouseLassText[] = {
    text_start("Some cold-hearted"
        t_line "people stop caring"
        t_cont "for their #MON."
        t_para "Grandpa takes in"
        t_line "the poor homeless"
        t_para "#MON and takes"
        t_line "care of them."
        t_done )
};
const txt_cmd_s MrFujisPsyduckText[] = {
    text_start("PSYDUCK: Gu-guwa?"
        t_done )
};
const txt_cmd_s MrFujisNidorinoText[] = {
    text_start("NIDORINO: Gyun!"
        t_done )
};
const txt_cmd_s MrFujisPidgeyText[] = {
    text_start("PIDGEY: Pijji!"
        t_done )
    //db(0, 0) // filler
};
