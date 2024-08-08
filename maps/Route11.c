#include "../constants.h"
#include "../util/scripting.h"
#include "Route11.h"
//// EVENTS
enum {
    ROUTE11_YOUNGSTER1 = 2,
    ROUTE11_YOUNGSTER2,
    ROUTE11_YOUNGSTER3,
    ROUTE11_YOUNGSTER4,
    ROUTE11_FRUIT_TREE,
};

const Script_fn_t Route11_SceneScripts[] = {
    0,
};

const struct MapCallback Route11_MapCallbacks[] = {
    0,
};

const struct MapScripts Route11_MapScripts = {
    .scene_script_count = 0, // lengthof(Route11_SceneScripts),
    .scene_scripts = Route11_SceneScripts,

    .callback_count = 0, // lengthof(Route11_MapCallbacks),
    .callbacks = Route11_MapCallbacks,
};

static const struct CoordEvent Route11_CoordEvents[] = {
    0,
};

static const struct BGEvent Route11_BGEvents[] = {
    bg_event(3, 7, BGEVENT_READ, &Route11Sign),
    bg_event(32, 5, BGEVENT_ITEM, &Route11HiddenRevive),
};

static const struct WarpEventData Route11_WarpEvents[] = {
    0,
};

static const struct ObjEvent Route11_ObjectEvents[] = {
    object_event(22, 14, SPRITE_YOUNGSTER, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerYoungsterOwen, -1),
    object_event(20, 4, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerYoungsterJason, -1),
    object_event(28, 7, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 1, &TrainerPsychicHerman, -1),
    object_event(8, 6, SPRITE_YOUNGSTER, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerPsychicFidel, -1),
    object_event(32, 2, SPRITE_FRUIT_TREE, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Route11FruitTree, -1),
};

const struct MapEvents Route11_MapEvents = {
    .warp_event_count = 0, // lengthof(Route11_WarpEvents),
    .warp_events = Route11_WarpEvents,

    .coord_event_count = 0, // lengthof(Route11_CoordEvents),
    .coord_events = Route11_CoordEvents,

    .bg_event_count = lengthof(Route11_BGEvents),
    .bg_events = Route11_BGEvents,

    .obj_event_count = lengthof(Route11_ObjectEvents),
    .obj_events = Route11_ObjectEvents,
};

//// CODE

const struct TrainerObj TrainerYoungsterOwen = {YOUNGSTER, OWEN, EVENT_BEAT_YOUNGSTER_OWEN, YoungsterOwenSeenText, YoungsterOwenBeatenText, 0, TrainerYoungsterOwen_Script};
bool TrainerYoungsterOwen_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(YoungsterOwenAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerYoungsterJason = {YOUNGSTER, JASON, EVENT_BEAT_YOUNGSTER_JASON, YoungsterJasonSeenText, YoungsterJasonBeatenText, 0, TrainerYoungsterJason_Script};
bool TrainerYoungsterJason_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(YoungsterJasonAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerPsychicHerman = {PSYCHIC_T, HERMAN, EVENT_BEAT_PSYCHIC_HERMAN, PsychicHermanSeenText, PsychicHermanBeatenText, 0, TrainerPsychicHerman_Script};
bool TrainerPsychicHerman_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(PsychicHermanAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerPsychicFidel = {PSYCHIC_T, FIDEL, EVENT_BEAT_PSYCHIC_FIDEL, PsychicFidelSeenText, PsychicFidelBeatenText, 0, TrainerPsychicFidel_Script};
bool TrainerPsychicFidel_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(PsychicFidelAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Route11Sign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route11SignText)
    SCRIPT_END
}
bool Route11FruitTree(script_s* s) {
    SCRIPT_BEGIN
    fruittree(FRUITTREE_ROUTE_11)
    SCRIPT_END
}
const struct HiddenItem Route11HiddenRevive = {REVIVE, EVENT_ROUTE_11_HIDDEN_REVIVE};
const txt_cmd_s YoungsterOwenSeenText[] = {
    text_start("There's no cheat-"
        t_line "ing in #MON."
        t_para "Let's keep it fair"
        t_line "and square!"
        t_done )
};
const txt_cmd_s YoungsterOwenBeatenText[] = {
    text_start("Huh? How did this"
        t_line "happen?"
        t_done )
};
const txt_cmd_s YoungsterOwenAfterBattleText[] = {
    text_start("I fought fair and"
        t_line "square with honor."
        t_para "I don't regret"
        t_line "this at all."
        t_done )
};
const txt_cmd_s YoungsterJasonSeenText[] = {
    text_start("It itches and"
        t_line "tickles a bit when"
        t_para "I wear shorts in"
        t_line "the grass."
        t_done )
};
const txt_cmd_s YoungsterJasonBeatenText[] = {
    text_start("Aiyaaah!"
        t_line "I got stomped!"
        t_done )
};
const txt_cmd_s YoungsterJasonAfterBattleText[] = {
    text_start("I'm going to catch"
        t_line "more #MON in"
        t_cont "the grass."
        t_done )
};
const txt_cmd_s PsychicHermanSeenText[] = {
    text_start("…"
        t_done )
};
const txt_cmd_s PsychicHermanBeatenText[] = {
    text_start("…"
        t_done )
};
const txt_cmd_s PsychicHermanAfterBattleText[] = {
    text_start("…"
        t_para "I lost while I had"
        t_line "my eyes closed…"
        t_done )
};
const txt_cmd_s PsychicFidelSeenText[] = {
    text_start("I can see it…"
        t_para "Everything to see"
        t_line "about you…"
        t_done )
};
const txt_cmd_s PsychicFidelBeatenText[] = {
    text_start("I couldn't foresee"
        t_line "your power…"
        t_done )
};
const txt_cmd_s PsychicFidelAfterBattleText[] = {
    text_start("Strength in con-"
        t_line "viction…"
        t_para "You're strong be-"
        t_line "cause you believe"
        t_cont "in your #MON."
        t_done )
};
const txt_cmd_s Route11SignText[] = {
    text_start("ROUTE 11"
        t_done )
    //db(0, 0) // filler
};
