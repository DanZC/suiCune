#include "../constants.h"
#include "../util/scripting.h"
#include "Route41.h"
//// EVENTS
enum {
    ROUTE41_OLIVINE_RIVAL1 = 2,
    ROUTE41_OLIVINE_RIVAL2,
    ROUTE41_OLIVINE_RIVAL3,
    ROUTE41_OLIVINE_RIVAL4,
    ROUTE41_OLIVINE_RIVAL5,
    ROUTE41_SWIMMER_GIRL1,
    ROUTE41_SWIMMER_GIRL2,
    ROUTE41_SWIMMER_GIRL3,
    ROUTE41_SWIMMER_GIRL4,
    ROUTE41_SWIMMER_GIRL5,
};

const Script_fn_t Route41_SceneScripts[] = {
    0,
};

const struct MapCallback Route41_MapCallbacks[] = {
    0,
};

const struct MapScripts Route41_MapScripts = {
    .scene_script_count = 0, // lengthof(Route41_SceneScripts),
    .scene_scripts = Route41_SceneScripts,

    .callback_count = 0, // lengthof(Route41_MapCallbacks),
    .callbacks = Route41_MapCallbacks,
};

static const struct CoordEvent Route41_CoordEvents[] = {
    0,
};

static const struct BGEvent Route41_BGEvents[] = {
    bg_event(9, 35, BGEVENT_ITEM, &Route41HiddenMaxEther),
};

static const struct WarpEventData Route41_WarpEvents[] = {
    warp_event(12, 17, WHIRL_ISLAND_NW, 1),
    warp_event(36, 19, WHIRL_ISLAND_NE, 1),
    warp_event(12, 37, WHIRL_ISLAND_SW, 1),
    warp_event(36, 45, WHIRL_ISLAND_SE, 1),
};

static const struct ObjEvent Route41_ObjectEvents[] = {
    object_event(32, 6, SPRITE_OLIVINE_RIVAL, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 3, &TrainerSwimmermCharlie, -1),
    object_event(46, 8, SPRITE_OLIVINE_RIVAL, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 3, &TrainerSwimmermGeorge, -1),
    object_event(20, 26, SPRITE_OLIVINE_RIVAL, SPRITEMOVEDATA_SPINCOUNTERCLOCKWISE, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 3, &TrainerSwimmermBerke, -1),
    object_event(32, 30, SPRITE_OLIVINE_RIVAL, SPRITEMOVEDATA_SPINCLOCKWISE, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 3, &TrainerSwimmermKirk, -1),
    object_event(19, 46, SPRITE_OLIVINE_RIVAL, SPRITEMOVEDATA_SPINCOUNTERCLOCKWISE, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 3, &TrainerSwimmermMathew, -1),
    object_event(17, 4, SPRITE_SWIMMER_GIRL, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 3, &TrainerSwimmerfKaylee, -1),
    object_event(23, 19, SPRITE_SWIMMER_GIRL, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 3, &TrainerSwimmerfSusie, -1),
    object_event(27, 34, SPRITE_SWIMMER_GIRL, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 3, &TrainerSwimmerfDenise, -1),
    object_event(44, 28, SPRITE_SWIMMER_GIRL, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 4, &TrainerSwimmerfKara, -1),
    object_event(9, 50, SPRITE_SWIMMER_GIRL, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 2, &TrainerSwimmerfWendy, -1),
};

const struct MapEvents Route41_MapEvents = {
    .warp_event_count = lengthof(Route41_WarpEvents),
    .warp_events = Route41_WarpEvents,

    .coord_event_count = 0, // lengthof(Route41_CoordEvents),
    .coord_events = Route41_CoordEvents,

    .bg_event_count = lengthof(Route41_BGEvents),
    .bg_events = Route41_BGEvents,

    .obj_event_count = lengthof(Route41_ObjectEvents),
    .obj_events = Route41_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "Route41.h"

const struct TrainerObj TrainerSwimmerfKaylee = {SWIMMERF, KAYLEE, EVENT_BEAT_SWIMMERF_KAYLEE, SwimmerfKayleeSeenText, SwimmerfKayleeBeatenText, 0, TrainerSwimmerfKaylee_Script};
bool TrainerSwimmerfKaylee_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SwimmerfKayleeAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSwimmerfSusie = {SWIMMERF, SUSIE, EVENT_BEAT_SWIMMERF_SUSIE, SwimmerfSusieSeenText, SwimmerfSusieBeatenText, 0, TrainerSwimmerfSusie_Script};
bool TrainerSwimmerfSusie_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SwimmerfSusieAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSwimmerfDenise = {SWIMMERF, DENISE, EVENT_BEAT_SWIMMERF_DENISE, SwimmerfDeniseSeenText, SwimmerfDeniseBeatenText, 0, TrainerSwimmerfDenise_Script};
bool TrainerSwimmerfDenise_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SwimmerfDeniseAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSwimmerfKara = {SWIMMERF, KARA, EVENT_BEAT_SWIMMERF_KARA, SwimmerfKaraSeenText, SwimmerfKaraBeatenText, 0, TrainerSwimmerfKara_Script};
bool TrainerSwimmerfKara_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SwimmerfKaraAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSwimmerfWendy = {SWIMMERF, WENDY, EVENT_BEAT_SWIMMERF_WENDY, SwimmerfWendySeenText, SwimmerfWendyBeatenText, 0, TrainerSwimmerfWendy_Script};
bool TrainerSwimmerfWendy_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SwimmerfWendyAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSwimmermCharlie = {SWIMMERM, CHARLIE, EVENT_BEAT_SWIMMERM_CHARLIE, SwimmermCharlieSeenText, SwimmermCharlieBeatenText, 0, TrainerSwimmermCharlie_Script};
bool TrainerSwimmermCharlie_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SwimmermCharlieAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSwimmermGeorge = {SWIMMERM, GEORGE, EVENT_BEAT_SWIMMERM_GEORGE, SwimmermGeorgeSeenText, SwimmermGeorgeBeatenText, 0, TrainerSwimmermGeorge_Script};
bool TrainerSwimmermGeorge_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SwimmermGeorgeAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSwimmermBerke = {SWIMMERM, BERKE, EVENT_BEAT_SWIMMERM_BERKE, SwimmermBerkeSeenText, SwimmermBerkeBeatenText, 0, TrainerSwimmermBerke_Script};
bool TrainerSwimmermBerke_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SwimmermBerkeAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSwimmermKirk = {SWIMMERM, KIRK, EVENT_BEAT_SWIMMERM_KIRK, SwimmermKirkSeenText, SwimmermKirkBeatenText, 0, TrainerSwimmermKirk_Script};
bool TrainerSwimmermKirk_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SwimmermKirkAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSwimmermMathew = {SWIMMERM, MATHEW, EVENT_BEAT_SWIMMERM_MATHEW, SwimmermMathewSeenText, SwimmermMathewBeatenText, 0, TrainerSwimmermMathew_Script};
bool TrainerSwimmermMathew_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SwimmermMathewAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Route41Rock(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(SmashRockScript)
    SCRIPT_END
}
const struct HiddenItem Route41HiddenMaxEther = {MAX_ETHER, EVENT_ROUTE_41_HIDDEN_MAX_ETHER};
const txt_cmd_s SwimmermCharlieSeenText[] = {
    text_start("The water's warm"
        t_line "here. I'm loose"
        t_cont "and limber."
        t_para "Sure, I'll take"
        t_line "you on!"
        t_done )
};
const txt_cmd_s SwimmermCharlieBeatenText[] = {
    text_start("Yikes! I've got"
        t_line "prune skin!"
        t_done )
};
const txt_cmd_s SwimmermCharlieAfterBattleText[] = {
    text_start("Isn't it relaxing"
        t_line "just floating like"
        t_cont "this?"
        t_done )
};
const txt_cmd_s SwimmermGeorgeSeenText[] = {
    text_start("I'm a bit tired."
        t_line "If I win, lend me"
        t_cont "your #MON."
        t_done )
};
const txt_cmd_s SwimmermGeorgeBeatenText[] = {
    text_start("Pant, pant…"
        t_done )
};
const txt_cmd_s SwimmermGeorgeAfterBattleText[] = {
    text_start("It's so far to"
        t_line "CIANWOOD."
        t_para "But it's no easy"
        t_line "return trip to"
        t_cont "OLIVINE either."
        t_para "What should I do?"
        t_done )
};
const txt_cmd_s SwimmermBerkeSeenText[] = {
    text_start("See those islands"
        t_line "that are blocked"
        t_cont "by whirlpools?"
        t_para "There just has to"
        t_line "be a secret!"
        t_done )
};
const txt_cmd_s SwimmermBerkeBeatenText[] = {
    text_start("What's the secret"
        t_line "to your strength?"
        t_done )
};
const txt_cmd_s SwimmermBerkeAfterBattleText[] = {
    text_start("It was a dark and"
        t_line "stormy night…"
        t_para "I saw this giant"
        t_line "#MON flying"
        t_cont "from the islands."
        t_para "It was scattering"
        t_line "feathers from its"
        t_cont "silver wings."
        t_done )
};
const txt_cmd_s SwimmermKirkSeenText[] = {
    text_start("The waves are wild"
        t_line "here."
        t_para "They tire you out"
        t_line "while you swim."
        t_done )
};
const txt_cmd_s SwimmermKirkBeatenText[] = {
    text_start("I'm beat!"
        t_done )
};
const txt_cmd_s SwimmermKirkAfterBattleText[] = {
    text_start("The currents keep"
        t_line "me from reaching"
        t_cont "that island."
        t_done )
};
const txt_cmd_s SwimmermMathewSeenText[] = {
    text_start("Are you seeking"
        t_line "the secrets of"
        t_cont "WHIRL ISLANDS?"
        t_done )
};
const txt_cmd_s SwimmermMathewBeatenText[] = {
    text_start("Ooh, you've got"
        t_line "great endurance!"
        t_done )
};
const txt_cmd_s SwimmermMathewAfterBattleText[] = {
    text_start("A secret about"
        t_line "WHIRL ISLANDS…"
        t_para "It's pitch-black"
        t_line "inside!"
        t_done )
};
const txt_cmd_s SwimmerfKayleeSeenText[] = {
    text_start("I'm on my way to"
        t_line "WHIRL ISLANDS."
        t_para "I'm going explor-"
        t_line "ing with friends."
        t_done )
};
const txt_cmd_s SwimmerfKayleeBeatenText[] = {
    text_start("Is that how you do"
        t_line "it?"
        t_done )
};
const txt_cmd_s SwimmerfKayleeAfterBattleText[] = {
    text_start("There's supposed"
        t_line "to be a big #-"
        t_cont "MON deep beneath"
        t_cont "WHIRL ISLANDS."
        t_para "I wonder what it"
        t_line "could be?"
        t_done )
};
const txt_cmd_s SwimmerfSusieSeenText[] = {
    text_start("You look so ele-"
        t_line "gant, riding your"
        t_cont "#MON."
        t_done )
};
const txt_cmd_s SwimmerfSusieBeatenText[] = {
    text_start("I'm crushed…"
        t_done )
};
const txt_cmd_s SwimmerfSusieAfterBattleText[] = {
    text_start("Wasn't there a hit"
        t_line "song about a boy"
        t_cont "riding a LAPRAS?"
        t_done )
};
const txt_cmd_s SwimmerfDeniseSeenText[] = {
    text_start("The weather is so"
        t_line "beautiful, I'm in"
        t_cont "a daze!"
        t_done )
};
const txt_cmd_s SwimmerfDeniseBeatenText[] = {
    text_start("Ohhh!"
        t_done )
};
const txt_cmd_s SwimmerfDeniseAfterBattleText[] = {
    text_start("A sunburn is the"
        t_line "worst for skin."
        t_para "But I don't use a"
        t_line "sunblock."
        t_para "I won't pollute"
        t_line "the water."
        t_done )
};
const txt_cmd_s SwimmerfKaraSeenText[] = {
    text_start("If you need to"
        t_line "rest, just tread"
        t_cont "water."
        t_para "You'll get your"
        t_line "wind back, so you"
        t_para "can keep on going"
        t_line "strong."
        t_done )
};
const txt_cmd_s SwimmerfKaraBeatenText[] = {
    text_start("Oh! You have more"
        t_line "energy than I do."
        t_done )
};
const txt_cmd_s SwimmerfKaraAfterBattleText[] = {
    text_start("I heard roars from"
        t_line "deep inside the"
        t_cont "ISLANDS."
        t_done )
};
const txt_cmd_s SwimmerfWendySeenText[] = {
    text_start("At night, STARYU"
        t_line "gather near the"
        t_cont "water's surface."
        t_done )
};
const txt_cmd_s SwimmerfWendyBeatenText[] = {
    text_start("Oh, dear…"
        t_done )
};
const txt_cmd_s SwimmerfWendyAfterBattleText[] = {
    text_start("The clusters of"
        t_line "STARYU light up"
        t_cont "at the same time."
        t_para "It's so beautiful,"
        t_line "it's scary."
        t_done )
    //db(0, 0) // filler
};
