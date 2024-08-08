#include "../constants.h"
#include "../util/scripting.h"
#include "FuchsiaCity.h"
//// EVENTS
enum {
    FUCHSIACITY_YOUNGSTER = 2,
    FUCHSIACITY_POKEFAN_M,
    FUCHSIACITY_TEACHER,
    FUCHSIACITY_FRUIT_TREE,
};

const Script_fn_t FuchsiaCity_SceneScripts[] = {
    0,
};

const struct MapCallback FuchsiaCity_MapCallbacks[] = {
    map_callback(MAPCALLBACK_NEWMAP, FuchsiaCity_MapScripts_FlyPoint),
};

const struct MapScripts FuchsiaCity_MapScripts = {
    .scene_script_count = 0, // lengthof(FuchsiaCity_SceneScripts),
    .scene_scripts = FuchsiaCity_SceneScripts,

    .callback_count = lengthof(FuchsiaCity_MapCallbacks),
    .callbacks = FuchsiaCity_MapCallbacks,
};

static const struct CoordEvent FuchsiaCity_CoordEvents[] = {
    0,
};

static const struct BGEvent FuchsiaCity_BGEvents[] = {
    bg_event(21, 15, BGEVENT_READ, &FuchsiaCitySign),
    bg_event(5, 29, BGEVENT_READ, &FuchsiaGymSign),
    bg_event(25, 15, BGEVENT_READ, &SafariZoneOfficeSign),
    bg_event(27, 29, BGEVENT_READ, &WardensHomeSign),
    bg_event(17, 5, BGEVENT_READ, &SafariZoneClosedSign),
    bg_event(13, 15, BGEVENT_READ, &NoLitteringSign),
    bg_event(20, 27, BGEVENT_READ, &FuchsiaCityPokecenterSign),
    bg_event(6, 13, BGEVENT_READ, &FuchsiaCityMartSign),
};

static const struct WarpEventData FuchsiaCity_WarpEvents[] = {
    warp_event(5, 13, FUCHSIA_MART, 2),
    warp_event(22, 13, SAFARI_ZONE_MAIN_OFFICE, 1),
    warp_event(8, 27, FUCHSIA_GYM, 1),
    warp_event(11, 27, BILLS_BROTHERS_HOUSE, 1),
    warp_event(19, 27, FUCHSIA_POKECENTER_1F, 1),
    warp_event(27, 27, SAFARI_ZONE_WARDENS_HOME, 1),
    warp_event(18, 3, SAFARI_ZONE_FUCHSIA_GATE_BETA, 3),
    warp_event(37, 22, ROUTE_15_FUCHSIA_GATE, 1),
    warp_event(37, 23, ROUTE_15_FUCHSIA_GATE, 2),
    warp_event(7, 35, ROUTE_19_FUCHSIA_GATE, 1),
    warp_event(8, 35, ROUTE_19_FUCHSIA_GATE, 2),
};

static const struct ObjEvent FuchsiaCity_ObjectEvents[] = {
    object_event(23, 18, SPRITE_YOUNGSTER, SPRITEMOVEDATA_WANDER, 1, 1, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &FuchsiaCityYoungster, -1),
    object_event(13, 8, SPRITE_POKEFAN_M, SPRITEMOVEDATA_WANDER, 1, 1, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, &FuchsiaCityPokefanM, -1),
    object_event(16, 14, SPRITE_TEACHER, SPRITEMOVEDATA_WANDER, 1, 1, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &FuchsiaCityTeacher, -1),
    object_event(8, 1, SPRITE_FRUIT_TREE, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &FuchsiaCityFruitTree, -1),
};

const struct MapEvents FuchsiaCity_MapEvents = {
    .warp_event_count = lengthof(FuchsiaCity_WarpEvents),
    .warp_events = FuchsiaCity_WarpEvents,

    .coord_event_count = 0, // lengthof(FuchsiaCity_CoordEvents),
    .coord_events = FuchsiaCity_CoordEvents,

    .bg_event_count = lengthof(FuchsiaCity_BGEvents),
    .bg_events = FuchsiaCity_BGEvents,

    .obj_event_count = lengthof(FuchsiaCity_ObjectEvents),
    .obj_events = FuchsiaCity_ObjectEvents,
};

//// CODE

bool FuchsiaCity_MapScripts_FlyPoint(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_FLYPOINT_FUCHSIA)
    s_endcallback
    SCRIPT_END
}
bool FuchsiaCityYoungster(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(FuchsiaCityYoungsterText)
    SCRIPT_END
}
bool FuchsiaCityPokefanM(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(FuchsiaCityPokefanMText)
    SCRIPT_END
}
bool FuchsiaCityTeacher(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(FuchsiaCityTeacherText)
    SCRIPT_END
}
bool FuchsiaCitySign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(FuchsiaCitySignText)
    SCRIPT_END
}
bool FuchsiaGymSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(FuchsiaGymSignText)
    SCRIPT_END
}
bool SafariZoneOfficeSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(SafariZoneOfficeSignText)
    SCRIPT_END
}
bool WardensHomeSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(WardensHomeSignText)
    SCRIPT_END
}
bool SafariZoneClosedSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(SafariZoneClosedSignText)
    SCRIPT_END
}
bool NoLitteringSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(NoLitteringSignText)
    SCRIPT_END
}
bool FuchsiaCityPokecenterSign(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PokecenterSignScript)
    SCRIPT_END
}
bool FuchsiaCityMartSign(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(MartSignScript)
    SCRIPT_END
}
bool FuchsiaCityFruitTree(script_s* s) {
    SCRIPT_BEGIN
    fruittree(FRUITTREE_FUCHSIA_CITY)
    SCRIPT_END
}
const txt_cmd_s FuchsiaCityYoungsterText[] = {
    text_start("One of the ELITE"
        t_line "FOUR used to be"
        t_para "the LEADER of"
        t_line "FUCHSIA's GYM."
        t_done )
};
const txt_cmd_s FuchsiaCityPokefanMText[] = {
    text_start("KOGA's daughter"
        t_line "succeeded him as"
        t_para "the GYM LEADER"
        t_line "after he joined"
        t_cont "the ELITE FOUR."
        t_done )
};
const txt_cmd_s FuchsiaCityTeacherText[] = {
    text_start("The SAFARI ZONE is"
        t_line "closed… It's sad,"
        t_para "considering it's"
        t_line "FUCHSIA's main"
        t_cont "attraction."
        t_done )
};
const txt_cmd_s FuchsiaCitySignText[] = {
    text_start("FUCHSIA CITY"
        t_para "Behold! It's"
        t_line "Passion Pink!"
        t_done )
};
const txt_cmd_s FuchsiaGymSignText[] = {
    text_start("FUCHSIA CITY"
        t_line "#MON GYM"
        t_cont "LEADER: JANINE"
        t_para "The Poisonous"
        t_line "Ninja Master"
        t_done )
};
const txt_cmd_s SafariZoneOfficeSignText[] = {
    text_start("There's a notice"
        t_line "here…"
        t_para "SAFARI ZONE OFFICE"
        t_line "is closed until"
        t_cont "further notice."
        t_done )
};
const txt_cmd_s WardensHomeSignText[] = {
    text_start("SAFARI ZONE"
        t_line "WARDEN'S HOME"
        t_done )
};
const txt_cmd_s SafariZoneClosedSignText[] = {
    text_start("The WARDEN is"
        t_line "traveling abroad."
        t_para "Therefore, the"
        t_line "SAFARI ZONE is"
        t_cont "closed."
        t_done )
};
const txt_cmd_s NoLitteringSignText[] = {
    text_start("No littering."
        t_para "Please take your"
        t_line "waste with you."
        t_done )
    //db(0, 0) // filler
};
