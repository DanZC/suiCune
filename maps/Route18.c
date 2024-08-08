#include "../constants.h"
#include "../util/scripting.h"
#include "Route18.h"
//// EVENTS
enum {
    ROUTE18_YOUNGSTER1 = 2,
    ROUTE18_YOUNGSTER2,
};

const Script_fn_t Route18_SceneScripts[] = {
    0,
};

const struct MapCallback Route18_MapCallbacks[] = {
    0,
};

const struct MapScripts Route18_MapScripts = {
    .scene_script_count = 0, // lengthof(Route18_SceneScripts),
    .scene_scripts = Route18_SceneScripts,

    .callback_count = 0, // lengthof(Route18_MapCallbacks),
    .callbacks = Route18_MapCallbacks,
};

static const struct CoordEvent Route18_CoordEvents[] = {
    0,
};

static const struct BGEvent Route18_BGEvents[] = {
    bg_event(9, 5, BGEVENT_READ, &Route18Sign),
};

static const struct WarpEventData Route18_WarpEvents[] = {
    warp_event(2, 6, ROUTE_17_ROUTE_18_GATE, 3),
    warp_event(2, 7, ROUTE_17_ROUTE_18_GATE, 4),
};

static const struct ObjEvent Route18_ObjectEvents[] = {
    object_event(9, 12, SPRITE_YOUNGSTER, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerBirdKeeperBoris, -1),
    object_event(13, 6, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerBirdKeeperBob, -1),
};

const struct MapEvents Route18_MapEvents = {
    .warp_event_count = lengthof(Route18_WarpEvents),
    .warp_events = Route18_WarpEvents,

    .coord_event_count = 0, // lengthof(Route18_CoordEvents),
    .coord_events = Route18_CoordEvents,

    .bg_event_count = lengthof(Route18_BGEvents),
    .bg_events = Route18_BGEvents,

    .obj_event_count = lengthof(Route18_ObjectEvents),
    .obj_events = Route18_ObjectEvents,
};

//// CODE

const struct TrainerObj TrainerBirdKeeperBoris = {BIRD_KEEPER, BORIS, EVENT_BEAT_BIRD_KEEPER_BORIS, BirdKeeperBorisSeenText, BirdKeeperBorisBeatenText, 0, TrainerBirdKeeperBoris_Script};
bool TrainerBirdKeeperBoris_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(BirdKeeperBorisAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerBirdKeeperBob = {BIRD_KEEPER, BOB, EVENT_BEAT_BIRD_KEEPER_BOB, BirdKeeperBobSeenText, BirdKeeperBobBeatenText, 0, TrainerBirdKeeperBob_Script};
bool TrainerBirdKeeperBob_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(BirdKeeperBobAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Route18Sign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route18SignText)
    SCRIPT_END
}
const txt_cmd_s BirdKeeperBorisSeenText[] = {
    text_start("If you're looking"
        t_line "for #MON, you"
        t_para "have to look in"
        t_line "the tall grass."
        t_done )
};
const txt_cmd_s BirdKeeperBorisBeatenText[] = {
    text_start("Ayieee!"
        t_done )
};
const txt_cmd_s BirdKeeperBorisAfterBattleText[] = {
    text_start("Since you're so"
        t_line "strong, it must be"
        t_cont "fun to battle."
        t_done )
};
const txt_cmd_s BirdKeeperBobSeenText[] = {
    text_start("CYCLING ROAD is a"
        t_line "quick shortcut to"
        t_cont "CELADON."
        t_done )
};
const txt_cmd_s BirdKeeperBobBeatenText[] = {
    text_start("…Whew!"
        t_done )
};
const txt_cmd_s BirdKeeperBobAfterBattleText[] = {
    text_start("If you don't have"
        t_line "a BICYCLE, you're"
        t_para "not allowed to use"
        t_line "the shortcut."
        t_done )
};
const txt_cmd_s Route18SignText[] = {
    text_start("ROUTE 18"
        t_para "CELADON CITY -"
        t_line "FUCHSIA CITY"
        t_done )
    //db(0, 0) // filler
};
