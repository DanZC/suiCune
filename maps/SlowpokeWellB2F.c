#include "../constants.h"
#include "../util/scripting.h"
#include "SlowpokeWellB2F.h"
//// EVENTS
enum {
    SLOWPOKEWELLB2F_GYM_GUIDE = 2,
    SLOWPOKEWELLB2F_POKE_BALL,
};

const Script_fn_t SlowpokeWellB2F_SceneScripts[] = {
    0,
};

const struct MapCallback SlowpokeWellB2F_MapCallbacks[] = {
    0,
};

const struct MapScripts SlowpokeWellB2F_MapScripts = {
    .scene_script_count = 0, // lengthof(SlowpokeWellB2F_SceneScripts),
    .scene_scripts = SlowpokeWellB2F_SceneScripts,

    .callback_count = 0, // lengthof(SlowpokeWellB2F_MapCallbacks),
    .callbacks = SlowpokeWellB2F_MapCallbacks,
};

static const struct CoordEvent SlowpokeWellB2F_CoordEvents[] = {
    0,
};

static const struct BGEvent SlowpokeWellB2F_BGEvents[] = {
    0,
};

static const struct WarpEventData SlowpokeWellB2F_WarpEvents[] = {
    warp_event(9, 11, SLOWPOKE_WELL_B1F, 2),
};

static const struct ObjEvent SlowpokeWellB2F_ObjectEvents[] = {
    object_event(5, 4, SPRITE_GYM_GUIDE, SPRITEMOVEDATA_WANDER, 1, 2, -1, -1, 0, OBJECTTYPE_SCRIPT, 1, &SlowpokeWellB2FGymGuideScript, -1),
    object_event(15, 5, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &SlowpokeWellB2FTMRainDance, EVENT_SLOWPOKE_WELL_B2F_TM_RAIN_DANCE),
};

const struct MapEvents SlowpokeWellB2F_MapEvents = {
    .warp_event_count = lengthof(SlowpokeWellB2F_WarpEvents),
    .warp_events = SlowpokeWellB2F_WarpEvents,

    .coord_event_count = 0, // lengthof(SlowpokeWellB2F_CoordEvents),
    .coord_events = SlowpokeWellB2F_CoordEvents,

    .bg_event_count = 0, // lengthof(SlowpokeWellB2F_BGEvents),
    .bg_events = SlowpokeWellB2F_BGEvents,

    .obj_event_count = lengthof(SlowpokeWellB2F_ObjectEvents),
    .obj_events = SlowpokeWellB2F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "SlowpokeWellB2F.h"

bool SlowpokeWellB2FGymGuideScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_KINGS_ROCK_IN_SLOWPOKE_WELL)
    iftrue(GotKingsRock)
    writetext(SlowpokeWellB2FGymGuideText)
    promptbutton
    verbosegiveitem(KINGS_ROCK, 1)
    iffalse(NoRoom)
    setevent(EVENT_GOT_KINGS_ROCK_IN_SLOWPOKE_WELL)
NoRoom:
    closetext
    s_end
GotKingsRock:
    writetext(SlowpokeWellB2FGymGuideText_GotKingsRock)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct ItemBall SlowpokeWellB2FTMRainDance = {TM_RAIN_DANCE, 1};
const txt_cmd_s SlowpokeWellB2FGymGuideText[] = {
    text_start("I'm waiting to see"
        t_line "SLOWPOKE's moment"
        t_cont "of evolution."
        t_para "Through observa-"
        t_line "tion, I made a new"
        t_cont "discovery."
        t_para "A SLOWPOKE with a"
        t_line "KING'S ROCK often"
        t_para "gets bitten by a"
        t_line "SHELLDER."
        t_para "Here, I'll share a"
        t_line "KING'S ROCK with"
        t_cont "you."
        t_done )
};
const txt_cmd_s SlowpokeWellB2FGymGuideText_GotKingsRock[] = {
    text_start("I'm going to be"
        t_line "like SLOWPOKE."
        t_para "I'll wait patient-"
        t_line "ly, so I can see"
        t_cont "one evolve."
        t_done )
    //db(0, 0) // filler
};
