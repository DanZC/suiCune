#include "../constants.h"
#include "../util/scripting.h"
#include "Route1.h"
//// EVENTS
enum {
    ROUTE1_YOUNGSTER = 2,
    ROUTE1_COOLTRAINER_F,
    ROUTE1_FRUIT_TREE,
};

const Script_fn_t Route1_SceneScripts[] = {
    0,
};

const struct MapCallback Route1_MapCallbacks[] = {
    0,
};

const struct MapScripts Route1_MapScripts = {
    .scene_script_count = 0, // lengthof(Route1_SceneScripts),
    .scene_scripts = Route1_SceneScripts,

    .callback_count = 0, // lengthof(Route1_MapCallbacks),
    .callbacks = Route1_MapCallbacks,
};

static const struct CoordEvent Route1_CoordEvents[] = {
    0,
};

static const struct BGEvent Route1_BGEvents[] = {
    bg_event(7, 27, BGEVENT_READ, &Route1Sign),
};

static const struct WarpEventData Route1_WarpEvents[] = {
    0,
};

static const struct ObjEvent Route1_ObjectEvents[] = {
    object_event(4, 12, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 4, &TrainerSchoolboyDanny, -1),
    object_event(9, 25, SPRITE_COOLTRAINER_F, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 2, &TrainerCooltrainerfQuinn, -1),
    object_event(3, 7, SPRITE_FRUIT_TREE, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Route1FruitTree, -1),
};

const struct MapEvents Route1_MapEvents = {
    .warp_event_count = 0, // lengthof(Route1_WarpEvents),
    .warp_events = Route1_WarpEvents,

    .coord_event_count = 0, // lengthof(Route1_CoordEvents),
    .coord_events = Route1_CoordEvents,

    .bg_event_count = lengthof(Route1_BGEvents),
    .bg_events = Route1_BGEvents,

    .obj_event_count = lengthof(Route1_ObjectEvents),
    .obj_events = Route1_ObjectEvents,
};

//// CODE

const struct TrainerObj TrainerSchoolboyDanny = {SCHOOLBOY, DANNY, EVENT_BEAT_SCHOOLBOY_DANNY, SchoolboyDannySeenText, SchoolboyDannyBeatenText, 0, TrainerSchoolboyDanny_Script};
bool TrainerSchoolboyDanny_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SchoolboyDannyAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerCooltrainerfQuinn = {COOLTRAINERF, QUINN, EVENT_BEAT_COOLTRAINERF_QUINN, CooltrainerfQuinnSeenText, CooltrainerfQuinnBeatenText, 0, TrainerCooltrainerfQuinn_Script};
bool TrainerCooltrainerfQuinn_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(CooltrainerfQuinnAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Route1Sign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route1SignText)
    SCRIPT_END
}
bool Route1FruitTree(script_s* s) {
    SCRIPT_BEGIN
    fruittree(FRUITTREE_ROUTE_1)
    SCRIPT_END
}
const txt_cmd_s SchoolboyDannySeenText[] = {
    text_start("If trainers meet,"
        t_line "the first thing to"
        t_cont "do is battle."
        t_done )
};
const txt_cmd_s SchoolboyDannyBeatenText[] = {
    text_start("Awww… I've got a"
        t_line "losing record…"
        t_done )
};
const txt_cmd_s SchoolboyDannyAfterBattleText[] = {
    text_start("For trainers, it's"
        t_line "a given that we'll"
        t_para "battle whenever we"
        t_line "meet."
        t_done )
};
const txt_cmd_s CooltrainerfQuinnSeenText[] = {
    text_start("You there!"
        t_line "Want to battle?"
        t_done )
};
const txt_cmd_s CooltrainerfQuinnBeatenText[] = {
    text_start("Down and out…"
        t_done )
};
const txt_cmd_s CooltrainerfQuinnAfterBattleText[] = {
    text_start("You're strong."
        t_para "You obviously must"
        t_line "have trained hard."
        t_done )
};
const txt_cmd_s Route1SignText[] = {
    text_start("ROUTE 1"
        t_para "PALLET TOWN -"
        t_line "VIRIDIAN CITY"
        t_done )
    //db(0, 0) // filler
};
