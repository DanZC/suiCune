#include "../constants.h"
#include "../util/scripting.h"
#include "PalletTown.h"
//// EVENTS
enum {
    PALLETTOWN_TEACHER = 2,
    PALLETTOWN_FISHER,
};

const Script_fn_t PalletTown_SceneScripts[] = {
    0,
};

const struct MapCallback PalletTown_MapCallbacks[] = {
    map_callback(MAPCALLBACK_NEWMAP, PalletTown_MapScripts_FlyPoint),
};

const struct MapScripts PalletTown_MapScripts = {
    .scene_script_count = 0, // lengthof(PalletTown_SceneScripts),
    .scene_scripts = PalletTown_SceneScripts,

    .callback_count = lengthof(PalletTown_MapCallbacks),
    .callbacks = PalletTown_MapCallbacks,
};

static const struct CoordEvent PalletTown_CoordEvents[] = {
    0,
};

static const struct BGEvent PalletTown_BGEvents[] = {
    bg_event(7, 9, BGEVENT_READ, &PalletTownSign),
    bg_event(3, 5, BGEVENT_READ, &RedsHouseSign),
    bg_event(13, 13, BGEVENT_READ, &OaksLabSign),
    bg_event(11, 5, BGEVENT_READ, &BluesHouseSign),
};

static const struct WarpEventData PalletTown_WarpEvents[] = {
    warp_event(5, 5, REDS_HOUSE_1F, 1),
    warp_event(13, 5, BLUES_HOUSE, 1),
    warp_event(12, 11, OAKS_LAB, 1),
};

static const struct ObjEvent PalletTown_ObjectEvents[] = {
    object_event(3, 8, SPRITE_TEACHER, SPRITEMOVEDATA_WANDER, 2, 2, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &PalletTownTeacherScript, -1),
    object_event(12, 14, SPRITE_FISHER, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 2, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &PalletTownFisherScript, -1),
};

const struct MapEvents PalletTown_MapEvents = {
    .warp_event_count = lengthof(PalletTown_WarpEvents),
    .warp_events = PalletTown_WarpEvents,

    .coord_event_count = 0, // lengthof(PalletTown_CoordEvents),
    .coord_events = PalletTown_CoordEvents,

    .bg_event_count = lengthof(PalletTown_BGEvents),
    .bg_events = PalletTown_BGEvents,

    .obj_event_count = lengthof(PalletTown_ObjectEvents),
    .obj_events = PalletTown_ObjectEvents,
};

//// CODE

bool PalletTown_MapScripts_FlyPoint(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_FLYPOINT_PALLET)
    s_endcallback
    SCRIPT_END
}
bool PalletTownTeacherScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(PalletTownTeacherText)
    SCRIPT_END
}
bool PalletTownFisherScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(PalletTownFisherText)
    SCRIPT_END
}
bool PalletTownSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(PalletTownSignText)
    SCRIPT_END
}
bool RedsHouseSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(RedsHouseSignText)
    SCRIPT_END
}
bool OaksLabSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(OaksLabSignText)
    SCRIPT_END
}
bool BluesHouseSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(BluesHouseSignText)
    SCRIPT_END
}
const txt_cmd_s PalletTownTeacherText[] = {
    text_start("I'm raising #-"
        t_line "MON too."
        t_para "They serve as my"
        t_line "private guards."
        t_done )
};
const txt_cmd_s PalletTownFisherText[] = {
    text_start("Technology is"
        t_line "incredible!"
        t_para "You can now trade"
        t_line "#MON across"
        t_cont "time like e-mail."
        t_done )
};
const txt_cmd_s PalletTownSignText[] = {
    text_start("PALLET TOWN"
        t_para "A Tranquil Setting"
        t_line "of Peace & Purity"
        t_done )
};
const txt_cmd_s RedsHouseSignText[] = {
    text_start("RED'S HOUSE"
        t_done )
};
const txt_cmd_s OaksLabSignText[] = {
    text_start("OAK #MON"
        t_line "RESEARCH LAB"
        t_done )
};
const txt_cmd_s BluesHouseSignText[] = {
    text_start("BLUE'S HOUSE"
        t_done )
    //db(0, 0) // filler
};
