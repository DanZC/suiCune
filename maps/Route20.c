#include "../constants.h"
#include "../util/scripting.h"
#include "Route20.h"
//// EVENTS
enum {
    ROUTE20_SWIMMER_GIRL1 = 2,
    ROUTE20_SWIMMER_GIRL2,
    ROUTE20_SWIMMER_GUY,
};

const Script_fn_t Route20_SceneScripts[] = {
    0,
};

const struct MapCallback Route20_MapCallbacks[] = {
    map_callback(MAPCALLBACK_NEWMAP, Route20_MapScripts_ClearRocks),
};

const struct MapScripts Route20_MapScripts = {
    .scene_script_count = 0, // lengthof(Route20_SceneScripts),
    .scene_scripts = Route20_SceneScripts,

    .callback_count = lengthof(Route20_MapCallbacks),
    .callbacks = Route20_MapCallbacks,
};

static const struct CoordEvent Route20_CoordEvents[] = {
    0,
};

static const struct BGEvent Route20_BGEvents[] = {
    bg_event(37, 11, BGEVENT_READ, &CinnabarGymSign),
};

static const struct WarpEventData Route20_WarpEvents[] = {
    warp_event(38, 7, SEAFOAM_GYM, 1),
};

static const struct ObjEvent Route20_ObjectEvents[] = {
    object_event(52, 8, SPRITE_SWIMMER_GIRL, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 3, &TrainerSwimmerfNicole, -1),
    object_event(45, 13, SPRITE_SWIMMER_GIRL, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 3, &TrainerSwimmerfLori, -1),
    object_event(12, 13, SPRITE_SWIMMER_GUY, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 3, &TrainerSwimmermCameron, -1),
};

const struct MapEvents Route20_MapEvents = {
    .warp_event_count = lengthof(Route20_WarpEvents),
    .warp_events = Route20_WarpEvents,

    .coord_event_count = 0, // lengthof(Route20_CoordEvents),
    .coord_events = Route20_CoordEvents,

    .bg_event_count = lengthof(Route20_BGEvents),
    .bg_events = Route20_BGEvents,

    .obj_event_count = lengthof(Route20_ObjectEvents),
    .obj_events = Route20_ObjectEvents,
};

//// CODE

bool Route20_MapScripts_ClearRocks(script_s* s) {
    SCRIPT_BEGIN
    setevent(EVENT_CINNABAR_ROCKS_CLEARED)
    s_endcallback
    SCRIPT_END
}
const struct TrainerObj TrainerSwimmerfNicole = {SWIMMERF, NICOLE, EVENT_BEAT_SWIMMERF_NICOLE, SwimmerfNicoleSeenText, SwimmerfNicoleBeatenText, 0, TrainerSwimmerfNicole_Script};
bool TrainerSwimmerfNicole_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SwimmerfNicoleAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSwimmerfLori = {SWIMMERF, LORI, EVENT_BEAT_SWIMMERF_LORI, SwimmerfLoriSeenText, SwimmerfLoriBeatenText, 0, TrainerSwimmerfLori_Script};
bool TrainerSwimmerfLori_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SwimmerfLoriAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSwimmermCameron = {SWIMMERM, CAMERON, EVENT_BEAT_SWIMMERM_CAMERON, SwimmermCameronSeenText, SwimmermCameronBeatenText, 0, TrainerSwimmermCameron_Script};
bool TrainerSwimmermCameron_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SwimmermCameronAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool CinnabarGymSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(CinnabarGymSignText)
    SCRIPT_END
}
const txt_cmd_s SwimmerfNicoleSeenText[] = {
    text_start("I feel so much"
        t_line "lighter in water."
        t_done )
};
const txt_cmd_s SwimmerfNicoleBeatenText[] = {
    text_start("Oh, no!"
        t_done )
};
const txt_cmd_s SwimmerfNicoleAfterBattleText[] = {
    text_start("Swimming exercises"
        t_line "your full body."
        t_para "It's really good"
        t_line "for you."
        t_done )
};
const txt_cmd_s SwimmerfLoriSeenText[] = {
    text_start("What an impressive"
        t_line "collection of GYM"
        t_para "BADGES. We should"
        t_line "battle!"
        t_done )
};
const txt_cmd_s SwimmerfLoriBeatenText[] = {
    text_start("No!"
        t_done )
};
const txt_cmd_s SwimmerfLoriAfterBattleText[] = {
    text_start("SURF is no longer"
        t_line "the only HM move"
        t_cont "you use in water."
        t_done )
};
const txt_cmd_s SwimmermCameronSeenText[] = {
    text_start("I guess it's im-"
        t_line "possible to swim"
        t_para "all the way to"
        t_line "JOHTO."
        t_done )
};
const txt_cmd_s SwimmermCameronBeatenText[] = {
    text_start("Aiyah!"
        t_done )
};
const txt_cmd_s SwimmermCameronAfterBattleText[] = {
    text_start("Besides the sea, I"
        t_line "can also swim in"
        t_cont "ponds and rivers."
        t_done )
};
const txt_cmd_s CinnabarGymSignText[] = {
    text_start("What does this"
        t_line "sign say?"
        t_para "CINNABAR GYM"
        t_line "LEADER: BLAINE"
        t_done )
    //db(0, 0) // filler
};
