#include "../constants.h"
#include "../util/scripting.h"
#include "SoulHouse.h"
//// EVENTS
enum {
    SOULHOUSE_MRFUJI = 2,
    SOULHOUSE_TEACHER,
    SOULHOUSE_LASS,
    SOULHOUSE_GRANNY,
};

const Script_fn_t SoulHouse_SceneScripts[] = {
    0,
};

const struct MapCallback SoulHouse_MapCallbacks[] = {
    0,
};

const struct MapScripts SoulHouse_MapScripts = {
    .scene_script_count = 0, // lengthof(SoulHouse_SceneScripts),
    .scene_scripts = SoulHouse_SceneScripts,

    .callback_count = 0, // lengthof(SoulHouse_MapCallbacks),
    .callbacks = SoulHouse_MapCallbacks,
};

static const struct CoordEvent SoulHouse_CoordEvents[] = {
    0,
};

static const struct BGEvent SoulHouse_BGEvents[] = {
    0,
};

static const struct WarpEventData SoulHouse_WarpEvents[] = {
    warp_event(4, 7, LAVENDER_TOWN, 6),
    warp_event(5, 7, LAVENDER_TOWN, 6),
};

static const struct ObjEvent SoulHouse_ObjectEvents[] = {
    object_event(4, 2, SPRITE_GRAMPS, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &MrFuji, -1),
    object_event(7, 3, SPRITE_TEACHER, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &SoulHouseTeacherScript, -1),
    object_event(2, 5, SPRITE_LASS, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &SoulHouseLassScript, -1),
    object_event(1, 3, SPRITE_GRANNY, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &SoulHouseGrannyScript, -1),
};

const struct MapEvents SoulHouse_MapEvents = {
    .warp_event_count = lengthof(SoulHouse_WarpEvents),
    .warp_events = SoulHouse_WarpEvents,

    .coord_event_count = 0, // lengthof(SoulHouse_CoordEvents),
    .coord_events = SoulHouse_CoordEvents,

    .bg_event_count = 0, // lengthof(SoulHouse_BGEvents),
    .bg_events = SoulHouse_BGEvents,

    .obj_event_count = lengthof(SoulHouse_ObjectEvents),
    .obj_events = SoulHouse_ObjectEvents,
};

//// CODE

bool MrFuji(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(MrFujiText)
    SCRIPT_END
}
bool SoulHouseTeacherScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(SoulHouseTeacherText)
    SCRIPT_END
}
bool SoulHouseLassScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(SoulHouseLassText)
    SCRIPT_END
}
bool SoulHouseGrannyScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(SoulHouseGrannyText)
    SCRIPT_END
}
const txt_cmd_s MrFujiText[] = {
    text_start("MR.FUJI: Welcome."
        t_para "Hmm… You appear to"
        t_line "be raising your"
        t_para "#MON in a kind"
        t_line "and loving manner."
        t_para "#MON lovers"
        t_line "come here to pay"
        t_para "their respects to"
        t_line "departed #MON."
        t_para "Please offer con-"
        t_line "dolences for the"
        t_para "souls of the de-"
        t_line "parted #MON."
        t_para "I'm sure that will"
        t_line "make them happy."
        t_done )
};
const txt_cmd_s SoulHouseTeacherText[] = {
    text_start("There are other"
        t_line "graves of #MON"
        t_cont "here, I think."
        t_para "There are many"
        t_line "chambers that only"
        t_cont "MR.FUJI may enter."
        t_done )
};
const txt_cmd_s SoulHouseLassText[] = {
    text_start("I came with my mom"
        t_line "to visit #MON"
        t_cont "graves…"
        t_done )
};
const txt_cmd_s SoulHouseGrannyText[] = {
    text_start("The #MON that"
        t_line "lived with me…"
        t_para "I loved them like"
        t_line "my grandchildren…"
        t_done )
    //db(0, 0) // filler
};
