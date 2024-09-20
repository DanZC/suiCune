#include "../constants.h"
#include "../util/scripting.h"
#include "FuchsiaPokecenter1F.h"
//// EVENTS
enum {
    FUCHSIAPOKECENTER1F_NURSE = 2,
    FUCHSIAPOKECENTER1F_COOLTRAINER_M,
    FUCHSIAPOKECENTER1F_COOLTRAINER_F,
    FUCHSIAPOKECENTER1F_JANINE_IMPERSONATOR,
};

const Script_fn_t FuchsiaPokecenter1F_SceneScripts[] = {
    FuchsiaPokecenter1F_MapScripts_DummyScene,
};

const struct MapCallback FuchsiaPokecenter1F_MapCallbacks[] = {
    0,
};

const struct MapScripts FuchsiaPokecenter1F_MapScripts = {
    .scene_script_count = lengthof(FuchsiaPokecenter1F_SceneScripts),
    .scene_scripts = FuchsiaPokecenter1F_SceneScripts,

    .callback_count = 0, // lengthof(FuchsiaPokecenter1F_MapCallbacks),
    .callbacks = FuchsiaPokecenter1F_MapCallbacks,
};

static const struct CoordEvent FuchsiaPokecenter1F_CoordEvents[] = {
    0,
};

static const struct BGEvent FuchsiaPokecenter1F_BGEvents[] = {
    0,
};

static const struct WarpEventData FuchsiaPokecenter1F_WarpEvents[] = {
    warp_event(3, 7, FUCHSIA_CITY, 5),
    warp_event(4, 7, FUCHSIA_CITY, 5),
    warp_event(0, 7, POKECENTER_2F, 1),
};

static const struct ObjEvent FuchsiaPokecenter1F_ObjectEvents[] = {
    object_event(3, 1, SPRITE_NURSE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &FuchsiaPokecenter1FNurseScript, -1),
    object_event(8, 4, SPRITE_COOLTRAINER_M, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &FuchsiaPokecenter1FCooltrainerMScript, -1),
    object_event(1, 4, SPRITE_COOLTRAINER_F, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &FuchsiaPokecenter1FCooltrainerFScript, -1),
    object_event(5, 3, SPRITE_JANINE_IMPERSONATOR, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &FuchsiaPokecenter1FJanineImpersonatorScript, -1),
};

const struct MapEvents FuchsiaPokecenter1F_MapEvents = {
    .warp_event_count = lengthof(FuchsiaPokecenter1F_WarpEvents),
    .warp_events = FuchsiaPokecenter1F_WarpEvents,

    .coord_event_count = 0, // lengthof(FuchsiaPokecenter1F_CoordEvents),
    .coord_events = FuchsiaPokecenter1F_CoordEvents,

    .bg_event_count = 0, // lengthof(FuchsiaPokecenter1F_BGEvents),
    .bg_events = FuchsiaPokecenter1F_BGEvents,

    .obj_event_count = lengthof(FuchsiaPokecenter1F_ObjectEvents),
    .obj_events = FuchsiaPokecenter1F_ObjectEvents,
};

//// CODE

bool FuchsiaPokecenter1F_MapScripts_DummyScene(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool FuchsiaPokecenter1FNurseScript(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PokecenterNurseScript)
    SCRIPT_END
}
bool FuchsiaPokecenter1FCooltrainerMScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(FuchsiaPokecenter1FCooltrainerMText)
    SCRIPT_END
}
bool FuchsiaPokecenter1FCooltrainerFScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(FuchsiaPokecenter1FCooltrainerFText)
    SCRIPT_END
}
bool FuchsiaPokecenter1FJanineImpersonatorScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(FuchsiaPokecenter1FJanineImpersonatorText1)
    waitbutton
    closetext
    applymovement(FUCHSIAPOKECENTER1F_JANINE_IMPERSONATOR, FuchsiaPokecenter1FJanineImpersonatorSpinMovement)
    faceplayer
    variablesprite(SPRITE_JANINE_IMPERSONATOR, SPRITE_JANINE)
    special(LoadUsedSpritesGFX)
    opentext
    writetext(FuchsiaPokecenter1FJanineImpersonatorText2)
    waitbutton
    closetext
    applymovement(FUCHSIAPOKECENTER1F_JANINE_IMPERSONATOR, FuchsiaPokecenter1FJanineImpersonatorSpinMovement)
    faceplayer
    variablesprite(SPRITE_JANINE_IMPERSONATOR, SPRITE_LASS)
    special(LoadUsedSpritesGFX)
    s_end
    SCRIPT_END
}
const uint8_t FuchsiaPokecenter1FJanineImpersonatorSpinMovement[] = {
    turn_head(DOWN),
    turn_head(LEFT),
    turn_head(UP),
    turn_head(RIGHT),
    turn_head(DOWN),
    turn_head(LEFT),
    turn_head(UP),
    turn_head(RIGHT),
    turn_head(DOWN),
    turn_head(LEFT),
    turn_head(UP),
    turn_head(RIGHT),
    turn_head(DOWN),
    movement_step_end,
};
const txt_cmd_s FuchsiaPokecenter1FCooltrainerMText[] = {
    text_start("Hey! You have a"
        t_line "brand new kind of"
        t_cont "#DEX."
        t_para "Did PROF.OAK give"
        t_line "that to you?"
        t_done )
};
const txt_cmd_s FuchsiaPokecenter1FCooltrainerFText[] = {
    text_start("I got quite a"
        t_line "shock at the GYM."
        t_para "There were all"
        t_line "these girls who"
        t_cont "looked identical."
        t_done )
};
const txt_cmd_s FuchsiaPokecenter1FJanineImpersonatorText1[] = {
    text_start("I'm JANINE! Hocus-"
        t_line "pocus… Poof!"
        t_done )
};
const txt_cmd_s FuchsiaPokecenter1FJanineImpersonatorText2[] = {
    text_start("See? I look just"
        t_line "like her now!"
        t_done )
    //db(0, 0) // filler
};
