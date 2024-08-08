#include "../constants.h"
#include "../util/scripting.h"
#include "Route3.h"
//// EVENTS
enum {
    ROUTE3_FISHER1 = 2,
    ROUTE3_YOUNGSTER1,
    ROUTE3_YOUNGSTER2,
    ROUTE3_FISHER2,
};

const Script_fn_t Route3_SceneScripts[] = {
    0,
};

const struct MapCallback Route3_MapCallbacks[] = {
    0,
};

const struct MapScripts Route3_MapScripts = {
    .scene_script_count = 0, // lengthof(Route3_SceneScripts),
    .scene_scripts = Route3_SceneScripts,

    .callback_count = 0, // lengthof(Route3_MapCallbacks),
    .callbacks = Route3_MapCallbacks,
};

static const struct CoordEvent Route3_CoordEvents[] = {
    0,
};

static const struct BGEvent Route3_BGEvents[] = {
    bg_event(49, 13, BGEVENT_READ, &Route3MtMoonSquareSign),
};

static const struct WarpEventData Route3_WarpEvents[] = {
    warp_event(52, 1, MOUNT_MOON, 1),
};

static const struct ObjEvent Route3_ObjectEvents[] = {
    object_event(26, 12, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 2, &TrainerFirebreatherOtis, -1),
    object_event(10, 7, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerYoungsterWarren, -1),
    object_event(16, 3, SPRITE_YOUNGSTER, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 1, &TrainerYoungsterJimmy, -1),
    object_event(49, 5, SPRITE_FISHER, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 3, &TrainerFirebreatherBurt, -1),
};

const struct MapEvents Route3_MapEvents = {
    .warp_event_count = lengthof(Route3_WarpEvents),
    .warp_events = Route3_WarpEvents,

    .coord_event_count = 0, // lengthof(Route3_CoordEvents),
    .coord_events = Route3_CoordEvents,

    .bg_event_count = lengthof(Route3_BGEvents),
    .bg_events = Route3_BGEvents,

    .obj_event_count = lengthof(Route3_ObjectEvents),
    .obj_events = Route3_ObjectEvents,
};

//// CODE

const struct TrainerObj TrainerFirebreatherOtis = {FIREBREATHER, OTIS, EVENT_BEAT_FIREBREATHER_OTIS, FirebreatherOtisSeenText, FirebreatherOtisBeatenText, 0, TrainerFirebreatherOtis_Script};
bool TrainerFirebreatherOtis_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(FirebreatherOtisAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerYoungsterWarren = {YOUNGSTER, WARREN, EVENT_BEAT_YOUNGSTER_WARREN, YoungsterWarrenSeenText, YoungsterWarrenBeatenText, 0, TrainerYoungsterWarren_Script};
bool TrainerYoungsterWarren_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(YoungsterWarrenAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerYoungsterJimmy = {YOUNGSTER, JIMMY, EVENT_BEAT_YOUNGSTER_JIMMY, YoungsterJimmySeenText, YoungsterJimmyBeatenText, 0, TrainerYoungsterJimmy_Script};
bool TrainerYoungsterJimmy_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(YoungsterJimmyAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerFirebreatherBurt = {FIREBREATHER, BURT, EVENT_BEAT_FIREBREATHER_BURT, FirebreatherBurtSeenText, FirebreatherBurtBeatenText, 0, TrainerFirebreatherBurt_Script};
bool TrainerFirebreatherBurt_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(FirebreatherBurtAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Route3MtMoonSquareSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route3MtMoonSquareSignText)
    SCRIPT_END
}
const txt_cmd_s FirebreatherOtisSeenText[] = {
    text_start("Ah! The weather's"
        t_line "as fine as ever."
        t_done )
};
const txt_cmd_s FirebreatherOtisBeatenText[] = {
    text_start("It's sunny, but"
        t_line "I'm all wet…"
        t_done )
};
const txt_cmd_s FirebreatherOtisAfterBattleText[] = {
    text_start("When it rains,"
        t_line "it's hard to get"
        t_cont "ignition…"
        t_done )
};
const txt_cmd_s YoungsterWarrenSeenText[] = {
    text_start("Hmmm… I don't know"
        t_line "what to do…"
        t_done )
};
const txt_cmd_s YoungsterWarrenBeatenText[] = {
    text_start("I knew I'd lose…"
        t_done )
};
const txt_cmd_s YoungsterWarrenAfterBattleText[] = {
    text_start("You looked strong."
        t_para "I was afraid to"
        t_line "take you on…"
        t_done )
};
const txt_cmd_s YoungsterJimmySeenText[] = {
    text_start("I can run like the"
        t_line "wind!"
        t_done )
};
const txt_cmd_s YoungsterJimmyBeatenText[] = {
    text_start("Blown away!"
        t_done )
};
const txt_cmd_s YoungsterJimmyAfterBattleText[] = {
    text_start("I wear shorts the"
        t_line "whole year round."
        t_para "That's my fashion"
        t_line "policy."
        t_done )
};
const txt_cmd_s FirebreatherBurtSeenText[] = {
    text_start("Step right up and"
        t_line "take a look!"
        t_done )
};
const txt_cmd_s FirebreatherBurtBeatenText[] = {
    text_start("Yow! That's hot!"
        t_done )
};
const txt_cmd_s FirebreatherBurtAfterBattleText[] = {
    text_start("The greatest fire-"
        t_line "breather in KANTO,"
        t_cont "that's me."
        t_para "But not the best"
        t_line "trainer…"
        t_done )
};
const txt_cmd_s Route3MtMoonSquareSignText[] = {
    text_start("MT.MOON SQUARE"
        t_para "Just go up the"
        t_line "stairs."
        t_done )
    //db(0, 0) // filler
};
