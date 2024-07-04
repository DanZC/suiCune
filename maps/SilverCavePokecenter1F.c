#include "../constants.h"
#include "../util/scripting.h"
#include "SilverCavePokecenter1F.h"
//// EVENTS
enum {
    SILVERCAVEPOKECENTER1F_NURSE = 2,
    SILVERCAVEPOKECENTER1F_GRANNY,
};

const Script_fn_t SilverCavePokecenter1F_SceneScripts[] = {
    0,
};

const struct MapCallback SilverCavePokecenter1F_MapCallbacks[] = {
    0,
};

const struct MapScripts SilverCavePokecenter1F_MapScripts = {
    .scene_script_count = 0, // lengthof(SilverCavePokecenter1F_SceneScripts),
    .scene_scripts = SilverCavePokecenter1F_SceneScripts,

    .callback_count = 0, // lengthof(SilverCavePokecenter1F_MapCallbacks),
    .callbacks = SilverCavePokecenter1F_MapCallbacks,
};

static const struct CoordEvent SilverCavePokecenter1F_CoordEvents[] = {
    0,
};

static const struct BGEvent SilverCavePokecenter1F_BGEvents[] = {
    0,
};

static const struct WarpEventData SilverCavePokecenter1F_WarpEvents[] = {
    warp_event(3, 7, SILVER_CAVE_OUTSIDE, 1),
    warp_event(4, 7, SILVER_CAVE_OUTSIDE, 1),
    warp_event(0, 7, POKECENTER_2F, 1),
};

static const struct ObjEvent SilverCavePokecenter1F_ObjectEvents[] = {
    object_event(3, 1, SPRITE_NURSE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &SilverCavePokecenter1FNurseScript, -1),
    object_event(1, 5, SPRITE_GRANNY, SPRITEMOVEDATA_STANDING_LEFT, 2, 1, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &SilverCavePokecenter1FGrannyScript, -1),
};

const struct MapEvents SilverCavePokecenter1F_MapEvents = {
    .warp_event_count = lengthof(SilverCavePokecenter1F_WarpEvents),
    .warp_events = SilverCavePokecenter1F_WarpEvents,

    .coord_event_count = 0, // lengthof(SilverCavePokecenter1F_CoordEvents),
    .coord_events = SilverCavePokecenter1F_CoordEvents,

    .bg_event_count = 0, // lengthof(SilverCavePokecenter1F_BGEvents),
    .bg_events = SilverCavePokecenter1F_BGEvents,

    .obj_event_count = lengthof(SilverCavePokecenter1F_ObjectEvents),
    .obj_events = SilverCavePokecenter1F_ObjectEvents,
};

//// CODE

bool SilverCavePokecenter1FNurseScript(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PokecenterNurseScript)
    SCRIPT_END
}
bool SilverCavePokecenter1FGrannyScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(SilverCavePokecenter1FGrannyText)
    SCRIPT_END
}
const txt_cmd_s SilverCavePokecenter1FGrannyText[] = {
    text_start("Trainers who seek"
        t_line "power climb MT."
        t_para "SILVER despite its"
        t_line "many dangers…"
        t_para "With their trusted"
        t_line "#MON, they must"
        t_para "feel they can go"
        t_line "anywhere…"
        t_done )
    //db(0, 0) // filler
};
