#include "../constants.h"
#include "../util/scripting.h"
#include "Route2.h"
//// EVENTS
enum {
    ROUTE2_BUG_CATCHER1 = 2,
    ROUTE2_BUG_CATCHER2,
    ROUTE2_BUG_CATCHER3,
    ROUTE2_POKE_BALL1,
    ROUTE2_POKE_BALL2,
    ROUTE2_POKE_BALL3,
    ROUTE2_POKE_BALL4,
    ROUTE2_FRUIT_TREE,
};

const Script_fn_t Route2_SceneScripts[] = {
    0,
};

const struct MapCallback Route2_MapCallbacks[] = {
    0,
};

const struct MapScripts Route2_MapScripts = {
    .scene_script_count = 0, // lengthof(Route2_SceneScripts),
    .scene_scripts = Route2_SceneScripts,

    .callback_count = 0, // lengthof(Route2_MapCallbacks),
    .callbacks = Route2_MapCallbacks,
};

static const struct CoordEvent Route2_CoordEvents[] = {
    0,
};

static const struct BGEvent Route2_BGEvents[] = {
    bg_event(7, 51, BGEVENT_READ, &Route2Sign),
    bg_event(11, 9, BGEVENT_READ, &Route2DiglettsCaveSign),
    bg_event(7, 23, BGEVENT_ITEM, &Route2HiddenMaxEther),
    bg_event(4, 14, BGEVENT_ITEM, &Route2HiddenFullHeal),
    bg_event(4, 27, BGEVENT_ITEM, &Route2HiddenFullRestore),
    bg_event(11, 30, BGEVENT_ITEM, &Route2HiddenRevive),
};

static const struct WarpEventData Route2_WarpEvents[] = {
    warp_event(15, 15, ROUTE_2_NUGGET_HOUSE, 1),
    warp_event(15, 31, ROUTE_2_GATE, 3),
    warp_event(16, 27, ROUTE_2_GATE, 1),
    warp_event(17, 27, ROUTE_2_GATE, 2),
    warp_event(12, 7, DIGLETTS_CAVE, 3),
};

static const struct ObjEvent Route2_ObjectEvents[] = {
    object_event(10, 45, SPRITE_BUG_CATCHER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_TRAINER, 5, &TrainerBugCatcherRob, -1),
    object_event(6, 4, SPRITE_BUG_CATCHER, SPRITEMOVEDATA_SPINCLOCKWISE, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_TRAINER, 3, &TrainerBugCatcherEd, -1),
    object_event(0, 40, SPRITE_BUG_CATCHER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_TRAINER, 3, &TrainerBugCatcherDoug, -1),
    object_event(0, 29, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &Route2DireHit, EVENT_ROUTE_2_DIRE_HIT),
    object_event(2, 23, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &Route2MaxPotion, EVENT_ROUTE_2_MAX_POTION),
    object_event(19, 2, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &Route2Carbos, EVENT_ROUTE_2_CARBOS),
    object_event(14, 50, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &Route2Elixer, EVENT_ROUTE_2_ELIXER),
    object_event(10, 14, SPRITE_FRUIT_TREE, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Route2FruitTree, -1),
};

const struct MapEvents Route2_MapEvents = {
    .warp_event_count = lengthof(Route2_WarpEvents),
    .warp_events = Route2_WarpEvents,

    .coord_event_count = 0, // lengthof(Route2_CoordEvents),
    .coord_events = Route2_CoordEvents,

    .bg_event_count = lengthof(Route2_BGEvents),
    .bg_events = Route2_BGEvents,

    .obj_event_count = lengthof(Route2_ObjectEvents),
    .obj_events = Route2_ObjectEvents,
};

//// CODE

const struct TrainerObj TrainerBugCatcherRob = {BUG_CATCHER, ROB, EVENT_BEAT_BUG_CATCHER_ROB, BugCatcherRobSeenText, BugCatcherRobBeatenText, 0, TrainerBugCatcherRob_Script};
bool TrainerBugCatcherRob_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(BugCatcherRobAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerBugCatcherEd = {BUG_CATCHER, ED, EVENT_BEAT_BUG_CATCHER_ED, BugCatcherEdSeenText, BugCatcherEdBeatenText, 0, TrainerBugCatcherEd_Script};
bool TrainerBugCatcherEd_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(BugCatcherEdAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerBugCatcherDoug = {BUG_CATCHER, DOUG, EVENT_BEAT_BUG_CATCHER_DOUG, BugCatcherDougSeenText, BugCatcherDougBeatenText, 0, TrainerBugCatcherDoug_Script};
bool TrainerBugCatcherDoug_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(BugCatcherDougAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Route2Sign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route2SignText)
    SCRIPT_END
}
bool Route2DiglettsCaveSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route2DiglettsCaveSignText)
    SCRIPT_END
}
const struct ItemBall Route2DireHit = {DIRE_HIT, 1};
const struct ItemBall Route2MaxPotion = {MAX_POTION, 1};
const struct ItemBall Route2Carbos = {CARBOS, 1};
const struct ItemBall Route2Elixer = {ELIXER, 1};
bool Route2FruitTree(script_s* s) {
    SCRIPT_BEGIN
    fruittree(FRUITTREE_ROUTE_2)
    SCRIPT_END
}
const struct HiddenItem Route2HiddenMaxEther = {MAX_ETHER, EVENT_ROUTE_2_HIDDEN_MAX_ETHER};
const struct HiddenItem Route2HiddenFullHeal = {FULL_HEAL, EVENT_ROUTE_2_HIDDEN_FULL_HEAL};
const struct HiddenItem Route2HiddenFullRestore = {FULL_RESTORE, EVENT_ROUTE_2_HIDDEN_FULL_RESTORE};
const struct HiddenItem Route2HiddenRevive = {REVIVE, EVENT_ROUTE_2_HIDDEN_REVIVE};
const txt_cmd_s BugCatcherRobSeenText[] = {
    text_start("My bug #MON are"
        t_line "tough. Prepare to"
        t_cont "lose!"
        t_done )
};
const txt_cmd_s BugCatcherRobBeatenText[] = {
    text_start("I was whipped…"
        t_done )
};
const txt_cmd_s BugCatcherRobAfterBattleText[] = {
    text_start("I'm going to look"
        t_line "for stronger bug"
        t_cont "#MON."
        t_done )
};
const txt_cmd_s BugCatcherEdSeenText[] = {
    text_start("If you walk in"
        t_line "tall grass wearing"
        t_para "shorts, do you get"
        t_line "nicks and cuts?"
        t_done )
};
const txt_cmd_s BugCatcherEdBeatenText[] = {
    text_start("Ouch, ouch, ouch!"
        t_done )
};
const txt_cmd_s BugCatcherEdAfterBattleText[] = {
    text_start("They'll really"
        t_line "sting when you"
        t_cont "take a bath."
        t_done )
};
const txt_cmd_s BugCatcherDougSeenText[] = {
    text_start("Why don't girls"
        t_line "like bug #MON?"
        t_done )
};
const txt_cmd_s BugCatcherDougBeatenText[] = {
    text_start("No good!"
        t_done )
};
const txt_cmd_s BugCatcherDougAfterBattleText[] = {
    text_start("Bug #MON squish"
        t_line "like plush toys"
        t_para "when you squeeze"
        t_line "their bellies."
        t_para "I love how they"
        t_line "feel!"
        t_done )
};
const txt_cmd_s Route2SignText[] = {
    text_start("ROUTE 2"
        t_para "VIRIDIAN CITY -"
        t_line "PEWTER CITY"
        t_done )
};
const txt_cmd_s Route2DiglettsCaveSignText[] = {
    text_start("DIGLETT'S CAVE"
        t_done )
    //db(0, 0) // filler
};
