#include "../constants.h"
#include "../util/scripting.h"
#include "AzaleaPokecenter1F.h"
//// EVENTS
enum {
    AZALEAPOKECENTER1F_NURSE = 2,
    AZALEAPOKECENTER1F_GENTLEMAN,
    AZALEAPOKECENTER1F_FISHING_GURU,
    AZALEAPOKECENTER1F_POKEFAN_F,
};

const Script_fn_t AzaleaPokecenter1F_SceneScripts[] = {
    AzaleaPokecenter1F_MapScripts_DummyScene,
};

const struct MapCallback AzaleaPokecenter1F_MapCallbacks[] = {
    0,
};

const struct MapScripts AzaleaPokecenter1F_MapScripts = {
    .scene_script_count = lengthof(AzaleaPokecenter1F_SceneScripts),
    .scene_scripts = AzaleaPokecenter1F_SceneScripts,

    .callback_count = 0, // lengthof(AzaleaPokecenter1F_MapCallbacks),
    .callbacks = AzaleaPokecenter1F_MapCallbacks,
};

static const struct CoordEvent AzaleaPokecenter1F_CoordEvents[] = {
    0,
};

static const struct BGEvent AzaleaPokecenter1F_BGEvents[] = {
    0,
};

static const struct WarpEventData AzaleaPokecenter1F_WarpEvents[] = {
    warp_event(3, 7, AZALEA_TOWN, 1),
    warp_event(4, 7, AZALEA_TOWN, 1),
    warp_event(0, 7, POKECENTER_2F, 1),
};

static const struct ObjEvent AzaleaPokecenter1F_ObjectEvents[] = {
    object_event(3, 1, SPRITE_NURSE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &AzaleaPokecenter1FNurseScript, -1),
    object_event(9, 6, SPRITE_GENTLEMAN, SPRITEMOVEDATA_WALK_UP_DOWN, 0, 1, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &AzaleaPokecenter1FGentlemanScript, -1),
    object_event(6, 1, SPRITE_FISHING_GURU, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &AzaleaPokecenter1FFishingGuruScript, -1),
    object_event(1, 4, SPRITE_POKEFAN_F, SPRITEMOVEDATA_WANDER, 1, 2, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &AzaleaPokecenter1FPokefanFScript, -1),
};

const struct MapEvents AzaleaPokecenter1F_MapEvents = {
    .warp_event_count = lengthof(AzaleaPokecenter1F_WarpEvents),
    .warp_events = AzaleaPokecenter1F_WarpEvents,

    .coord_event_count = 0, // lengthof(AzaleaPokecenter1F_CoordEvents),
    .coord_events = AzaleaPokecenter1F_CoordEvents,

    .bg_event_count = 0, // lengthof(AzaleaPokecenter1F_BGEvents),
    .bg_events = AzaleaPokecenter1F_BGEvents,

    .obj_event_count = lengthof(AzaleaPokecenter1F_ObjectEvents),
    .obj_events = AzaleaPokecenter1F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "AzaleaPokecenter1F.h"

bool AzaleaPokecenter1F_MapScripts_DummyScene(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool AzaleaPokecenter1FNurseScript(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PokecenterNurseScript)
    SCRIPT_END
}
bool AzaleaPokecenter1FGentlemanScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(AzaleaPokecenter1FGentlemanText)
    SCRIPT_END
}
bool AzaleaPokecenter1FFishingGuruScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(AzaleaPokecenter1FFishingGuruText)
    SCRIPT_END
}
bool AzaleaPokecenter1FPokefanFScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(AzaleaPokecenter1FPokefanFText)
    SCRIPT_END
}
const txt_cmd_s AzaleaPokecenter1FGentlemanText[] = {
    text_start("Do your #MON"
        t_line "know HM moves?"
        t_para "Those moves can"
        t_line "be used even if"
        t_para "your #MON has"
        t_line "fainted."
        t_done )
};
const txt_cmd_s AzaleaPokecenter1FUnusedText[] = {
    text_start("This BILL guy"
        t_line "created the system"
        t_para "for storing"
        t_line "#MON in a PC."
        t_para "BILL's PC can"
        t_line "store up to 20"
        t_cont "#MON per BOX."
        t_done )
};
const txt_cmd_s AzaleaPokecenter1FFishingGuruText[] = {
    text_start("BILL's PC can"
        t_line "store up to 20"
        t_cont "#MON per BOX."
        t_done )
};
const txt_cmd_s AzaleaPokecenter1FPokefanFText[] = {
    text_start("Do you know about"
        t_line "APRICORNS?"
        t_para "Crack one open,"
        t_line "hollow it out and"
        t_para "fit it with a"
        t_line "special device."
        t_para "Then you can catch"
        t_line "#MON with it."
        t_para "Before # BALLS"
        t_line "were invented,"
        t_para "everyone used"
        t_line "APRICORNS."
        t_done )
    //db(0, 0) // filler
};
