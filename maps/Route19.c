#include "../constants.h"
#include "../util/scripting.h"
#include "Route19.h"
//// EVENTS
enum {
    ROUTE19_SWIMMER_GIRL = 2,
    ROUTE19_SWIMMER_GUY1,
    ROUTE19_SWIMMER_GUY2,
    ROUTE19_SWIMMER_GUY3,
    ROUTE19_FISHER1,
    ROUTE19_FISHER2,
};

const Script_fn_t Route19_SceneScripts[] = {
    0,
};

const struct MapCallback Route19_MapCallbacks[] = {
    map_callback(MAPCALLBACK_TILES, Route19_MapScripts_ClearRocks),
};

const struct MapScripts Route19_MapScripts = {
    .scene_script_count = 0, // lengthof(Route19_SceneScripts),
    .scene_scripts = Route19_SceneScripts,

    .callback_count = lengthof(Route19_MapCallbacks),
    .callbacks = Route19_MapCallbacks,
};

static const struct CoordEvent Route19_CoordEvents[] = {
    0,
};

static const struct BGEvent Route19_BGEvents[] = {
    bg_event(11, 13, BGEVENT_READ, &Route19Sign),
    bg_event(11, 1, BGEVENT_READ, &CarefulSwimmingSign),
};

static const struct WarpEventData Route19_WarpEvents[] = {
    warp_event(7, 3, ROUTE_19_FUCHSIA_GATE, 3),
};

static const struct ObjEvent Route19_ObjectEvents[] = {
    object_event(9, 23, SPRITE_SWIMMER_GIRL, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 0, &TrainerSwimmerfDawn, -1),
    object_event(13, 28, SPRITE_SWIMMER_GUY, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 3, &TrainerSwimmermHarold, -1),
    object_event(11, 17, SPRITE_SWIMMER_GUY, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 3, &TrainerSwimmermJerome, -1),
    object_event(8, 23, SPRITE_SWIMMER_GUY, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 0, &TrainerSwimmermTucker, -1),
    object_event(9, 5, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 1, &Route19Fisher1Script, -1),
    object_event(11, 5, SPRITE_FISHER, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 1, &Route19Fisher2Script, -1),
};

const struct MapEvents Route19_MapEvents = {
    .warp_event_count = lengthof(Route19_WarpEvents),
    .warp_events = Route19_WarpEvents,

    .coord_event_count = 0, // lengthof(Route19_CoordEvents),
    .coord_events = Route19_CoordEvents,

    .bg_event_count = lengthof(Route19_BGEvents),
    .bg_events = Route19_BGEvents,

    .obj_event_count = lengthof(Route19_ObjectEvents),
    .obj_events = Route19_ObjectEvents,
};

//// CODE

bool Route19_MapScripts_ClearRocks(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_CINNABAR_ROCKS_CLEARED)
    iftrue(Done)
    changeblock(6, 6, 0x7a) // rock
    changeblock(8, 6, 0x7a) // rock
    changeblock(10, 6, 0x7a) // rock
    changeblock(12, 8, 0x7a) // rock
    changeblock(4, 8, 0x7a) // rock
    changeblock(10, 10, 0x7a) // rock
Done:
    s_endcallback
    SCRIPT_END
}
const struct TrainerObj TrainerSwimmerfDawn = {SWIMMERF, DAWN, EVENT_BEAT_SWIMMERF_DAWN, SwimmerfDawnSeenText, SwimmerfDawnBeatenText, 0, TrainerSwimmerfDawn_Script};
bool TrainerSwimmerfDawn_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SwimmerfDawnAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSwimmermHarold = {SWIMMERM, HAROLD, EVENT_BEAT_SWIMMERM_HAROLD, SwimmermHaroldSeenText, SwimmermHaroldBeatenText, 0, TrainerSwimmermHarold_Script};
bool TrainerSwimmermHarold_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SwimmermHaroldAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSwimmermJerome = {SWIMMERM, JEROME, EVENT_BEAT_SWIMMERM_JEROME, SwimmermJeromeSeenText, SwimmermJeromeBeatenText, 0, TrainerSwimmermJerome_Script};
bool TrainerSwimmermJerome_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SwimmermJeromeAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSwimmermTucker = {SWIMMERM, TUCKER, EVENT_BEAT_SWIMMERM_TUCKER, SwimmermTuckerSeenText, SwimmermTuckerBeatenText, 0, TrainerSwimmermTucker_Script};
bool TrainerSwimmermTucker_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SwimmermTuckerAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Route19Fisher1Script(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_CINNABAR_ROCKS_CLEARED)
    iftrue(RocksCleared)
    writetext(Route19Fisher1Text)
    waitbutton
    closetext
    s_end
RocksCleared:
    writetext(Route19Fisher1Text_RocksCleared)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Route19Fisher2Script(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_CINNABAR_ROCKS_CLEARED)
    iftrue(RocksCleared)
    writetext(Route19Fisher2Text)
    waitbutton
    closetext
    s_end
RocksCleared:
    writetext(Route19Fisher2Text_RocksCleared)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Route19Sign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route19SignText)
    SCRIPT_END
}
bool CarefulSwimmingSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(CarefulSwimmingSignText)
    SCRIPT_END
}
const txt_cmd_s SwimmermHaroldSeenText[] = {
    text_start("Have you ever gone"
        t_line "swimming in the"
        t_cont "sea at night?"
        t_done )
};
const txt_cmd_s SwimmermHaroldBeatenText[] = {
    text_start("Glub…"
        t_done )
};
const txt_cmd_s SwimmermHaroldAfterBattleText[] = {
    text_start("At night, the sea"
        t_line "turns black. It"
        t_para "feels like it will"
        t_line "swallow you up."
        t_done )
};
const txt_cmd_s SwimmermTuckerSeenText[] = {
    text_start("Pant, pant…"
        t_line "Just… a little…"
        t_para "farther… to…"
        t_line "FUCHSIA…"
        t_done )
};
const txt_cmd_s SwimmermTuckerBeatenText[] = {
    text_start("I'm drowning!"
        t_done )
};
const txt_cmd_s SwimmermTuckerAfterBattleText[] = {
    text_start("I… asked my girl-"
        t_line "friend to swim to"
        t_cont "FUCHSIA… Gasp…"
        t_done )
};
const txt_cmd_s SwimmerfDawnSeenText[] = {
    text_start("I'm disgusted by"
        t_line "wimpy people!"
        t_done )
};
const txt_cmd_s SwimmerfDawnBeatenText[] = {
    text_start("I could beat you"
        t_line "at swimming…"
        t_done )
};
const txt_cmd_s SwimmerfDawnAfterBattleText[] = {
    text_start("It's a quick swim"
        t_line "between FUCHSIA"
        t_para "and SEAFOAM IS-"
        t_line "LANDS…"
        t_para "Sheesh, some big"
        t_line "man my boyfriend"
        t_para "is! What a wimp!"
        t_done )
};
const txt_cmd_s SwimmermJeromeSeenText[] = {
    text_start("Swimming?"
        t_line "I'm lousy at it."
        t_para "I'm just splashing"
        t_line "around in these"
        t_cont "shallow waters."
        t_done )
};
const txt_cmd_s SwimmermJeromeBeatenText[] = {
    text_start("I thought I could"
        t_line "win."
        t_done )
};
const txt_cmd_s SwimmermJeromeAfterBattleText[] = {
    text_start("I might be bad at"
        t_line "swimming, but I"
        t_cont "love the sea."
        t_done )
};
const txt_cmd_s Route19Fisher1Text[] = {
    text_start("Sorry. This road"
        t_line "is closed for"
        t_cont "construction."
        t_para "If you want to get"
        t_line "to CINNABAR, you'd"
        t_para "better go south"
        t_line "from PALLET TOWN."
        t_done )
};
const txt_cmd_s Route19Fisher1Text_RocksCleared[] = {
    text_start("I'm all sweaty."
        t_line "Time for a swim!"
        t_done )
};
const txt_cmd_s Route19Fisher2Text[] = {
    text_start("Who knows how long"
        t_line "it would take to"
        t_cont "move this boulder…"
        t_done )
};
const txt_cmd_s Route19Fisher2Text_RocksCleared[] = {
    text_start("The roadwork is"
        t_line "finally finished."
        t_para "Now I can go"
        t_line "fishing again."
        t_done )
};
const txt_cmd_s Route19SignText[] = {
    text_start("ROUTE 19"
        t_para "FUCHSIA CITY -"
        t_line "SEAFOAM ISLANDS"
        t_done )
};
const txt_cmd_s CarefulSwimmingSignText[] = {
    text_start("Please be careful"
        t_line "if you are swim-"
        t_cont "ming to SEAFOAM"
        t_cont "ISLANDS."
        t_para "FUCHSIA POLICE"
        t_done )
    //db(0, 0) // filler
};
