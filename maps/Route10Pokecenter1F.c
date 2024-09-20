#include "../constants.h"
#include "../util/scripting.h"
#include "Route10Pokecenter1F.h"
//// EVENTS
enum {
    ROUTE10POKECENTER1F_NURSE = 2,
    ROUTE10POKECENTER1F_GENTLEMAN,
    ROUTE10POKECENTER1F_GYM_GUIDE,
    ROUTE10POKECENTER1F_COOLTRAINER_F,
};

const Script_fn_t Route10Pokecenter1F_SceneScripts[] = {
    0,
};

const struct MapCallback Route10Pokecenter1F_MapCallbacks[] = {
    0,
};

const struct MapScripts Route10Pokecenter1F_MapScripts = {
    .scene_script_count = 0, // lengthof(Route10Pokecenter1F_SceneScripts),
    .scene_scripts = Route10Pokecenter1F_SceneScripts,

    .callback_count = 0, // lengthof(Route10Pokecenter1F_MapCallbacks),
    .callbacks = Route10Pokecenter1F_MapCallbacks,
};

static const struct CoordEvent Route10Pokecenter1F_CoordEvents[] = {
    0,
};

static const struct BGEvent Route10Pokecenter1F_BGEvents[] = {
    0,
};

static const struct WarpEventData Route10Pokecenter1F_WarpEvents[] = {
    warp_event(3, 7, ROUTE_10_NORTH, 1),
    warp_event(4, 7, ROUTE_10_NORTH, 1),
    warp_event(0, 7, POKECENTER_2F, 1),
};

static const struct ObjEvent Route10Pokecenter1F_ObjectEvents[] = {
    object_event(3, 1, SPRITE_NURSE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Route10Pokecenter1FNurseScript, -1),
    object_event(7, 6, SPRITE_GENTLEMAN, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &Route10Pokecenter1FGentlemanScript, -1),
    object_event(7, 2, SPRITE_GYM_GUIDE, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &Route10Pokecenter1FGymGuideScript, -1),
    object_event(1, 3, SPRITE_COOLTRAINER_F, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Route10Pokecenter1FCooltrainerFScript, -1),
};

const struct MapEvents Route10Pokecenter1F_MapEvents = {
    .warp_event_count = lengthof(Route10Pokecenter1F_WarpEvents),
    .warp_events = Route10Pokecenter1F_WarpEvents,

    .coord_event_count = 0, // lengthof(Route10Pokecenter1F_CoordEvents),
    .coord_events = Route10Pokecenter1F_CoordEvents,

    .bg_event_count = 0, // lengthof(Route10Pokecenter1F_BGEvents),
    .bg_events = Route10Pokecenter1F_BGEvents,

    .obj_event_count = lengthof(Route10Pokecenter1F_ObjectEvents),
    .obj_events = Route10Pokecenter1F_ObjectEvents,
};

//// CODE

bool Route10Pokecenter1FNurseScript(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PokecenterNurseScript)
    SCRIPT_END
}
bool Route10Pokecenter1FGentlemanScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(Route10Pokecenter1FGentlemanText)
    SCRIPT_END
}
bool Route10Pokecenter1FGymGuideScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_RETURNED_MACHINE_PART)
    iftrue(ReturnedMachinePart)
    writetext(Route10Pokecenter1FGymGuideText)
    waitbutton
    closetext
    s_end
ReturnedMachinePart:
    writetext(Route10Pokecenter1FGymGuideText_ReturnedMachinePart)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Route10Pokecenter1FCooltrainerFScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(Route10Pokecenter1FCooltrainerFText)
    SCRIPT_END
}
const txt_cmd_s Route10Pokecenter1FGentlemanText[] = {
    text_start("A #MON CENTER"
        t_line "near a cave?"
        t_para "That's mighty"
        t_line "convenient."
        t_done )
};
const txt_cmd_s Route10Pokecenter1FGymGuideText[] = {
    text_start("The POWER PLANT's"
        t_line "MANAGER is looking"
        t_para "for a strong #-"
        t_line "MON trainer."
        t_para "He needs help"
        t_line "getting back"
        t_para "something that"
        t_line "was stolen."
        t_done )
};
const txt_cmd_s Route10Pokecenter1FGymGuideText_ReturnedMachinePart[] = {
    text_start("I hear TEAM ROCKET"
        t_line "got back together"
        t_para "in JOHTO but fell"
        t_line "apart right away."
        t_para "I didn't know any-"
        t_line "thing about that."
        t_done )
};
const txt_cmd_s Route10Pokecenter1FCooltrainerFText[] = {
    text_start("When you go out-"
        t_line "side, you can see"
        t_para "the roof of a big"
        t_line "building."
        t_para "That's the POWER"
        t_line "PLANT."
        t_done )
    //db(0, 0) // filler
};
