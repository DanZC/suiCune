#include "../constants.h"
#include "../util/scripting.h"
#include "Route21.h"
//// EVENTS
enum {
    ROUTE21_SWIMMER_GIRL = 2,
    ROUTE21_SWIMMER_GUY,
    ROUTE21_FISHER,
};

const Script_fn_t Route21_SceneScripts[] = {
    0,
};

const struct MapCallback Route21_MapCallbacks[] = {
    0,
};

const struct MapScripts Route21_MapScripts = {
    .scene_script_count = 0, // lengthof(Route21_SceneScripts),
    .scene_scripts = Route21_SceneScripts,

    .callback_count = 0, // lengthof(Route21_MapCallbacks),
    .callbacks = Route21_MapCallbacks,
};

static const struct CoordEvent Route21_CoordEvents[] = {
    0,
};

static const struct BGEvent Route21_BGEvents[] = {
    0,
};

static const struct WarpEventData Route21_WarpEvents[] = {
    0,
};

static const struct ObjEvent Route21_ObjectEvents[] = {
    object_event(11, 16, SPRITE_SWIMMER_GIRL, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 3, &TrainerSwimmerfNikki, -1),
    object_event(2, 30, SPRITE_SWIMMER_GUY, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 4, &TrainerSwimmermSeth, -1),
    object_event(14, 22, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 1, &TrainerFisherArnold, -1),
};

const struct MapEvents Route21_MapEvents = {
    .warp_event_count = 0, // lengthof(Route21_WarpEvents),
    .warp_events = Route21_WarpEvents,

    .coord_event_count = 0, // lengthof(Route21_CoordEvents),
    .coord_events = Route21_CoordEvents,

    .bg_event_count = 0, // lengthof(Route21_BGEvents),
    .bg_events = Route21_BGEvents,

    .obj_event_count = lengthof(Route21_ObjectEvents),
    .obj_events = Route21_ObjectEvents,
};

//// CODE

const struct TrainerObj TrainerSwimmermSeth = {SWIMMERM, SETH, EVENT_BEAT_SWIMMERM_SETH, SwimmermSethSeenText, SwimmermSethBeatenText, 0, TrainerSwimmermSeth_Script};
bool TrainerSwimmermSeth_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SwimmermSethAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSwimmerfNikki = {SWIMMERF, NIKKI, EVENT_BEAT_SWIMMERF_NIKKI, SwimmerfNikkiSeenText, SwimmerfNikkiBeatenText, 0, TrainerSwimmerfNikki_Script};
bool TrainerSwimmerfNikki_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SwimmerfNikkiAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerFisherArnold = {FISHER, ARNOLD, EVENT_BEAT_FISHER_ARNOLD, FisherArnoldSeenText, FisherArnoldBeatenText, 0, TrainerFisherArnold_Script};
bool TrainerFisherArnold_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(FisherArnoldAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const txt_cmd_s SwimmermSethSeenText[] = {
    text_start("Land ho! Gotta"
        t_line "keep going!"
        t_done )
};
const txt_cmd_s SwimmermSethBeatenText[] = {
    text_start("Glug…"
        t_done )
};
const txt_cmd_s SwimmermSethAfterBattleText[] = {
    text_start("This arrogant guy"
        t_line "was at CINNABAR's"
        t_cont "volcano."
        t_done )
};
const txt_cmd_s SwimmerfNikkiSeenText[] = {
    text_start("If I win, you have"
        t_line "to help me with my"
        t_cont "suntan lotion!"
        t_done )
};
const txt_cmd_s SwimmerfNikkiBeatenText[] = {
    text_start("I'm worried about"
        t_line "sunburn…"
        t_done )
};
const txt_cmd_s SwimmerfNikkiAfterBattleText[] = {
    text_start("I have to watch"
        t_line "out for blemishes"
        t_cont "caused by the sun."
        t_done )
};
const txt_cmd_s FisherArnoldSeenText[] = {
    text_start("I'm bored by fish-"
        t_line "ing. Let's battle!"
        t_done )
};
const txt_cmd_s FisherArnoldBeatenText[] = {
    text_start("Utter failure…"
        t_done )
};
const txt_cmd_s FisherArnoldAfterBattleText[] = {
    text_start("I'll just go back"
        t_line "to fishing…"
        t_done )
    //db(0, 0) // filler
};
