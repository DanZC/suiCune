#include "../constants.h"
#include "../util/scripting.h"
#include "NationalParkBugContest.h"
//// EVENTS
enum {
    NATIONALPARKBUGCONTEST_YOUNGSTER1 = 2,
    NATIONALPARKBUGCONTEST_YOUNGSTER2,
    NATIONALPARKBUGCONTEST_ROCKER,
    NATIONALPARKBUGCONTEST_POKEFAN_M,
    NATIONALPARKBUGCONTEST_YOUNGSTER3,
    NATIONALPARKBUGCONTEST_YOUNGSTER4,
    NATIONALPARKBUGCONTEST_LASS,
    NATIONALPARKBUGCONTEST_YOUNGSTER5,
    NATIONALPARKBUGCONTEST_YOUNGSTER6,
    NATIONALPARKBUGCONTEST_YOUNGSTER7,
    NATIONALPARKBUGCONTEST_POKE_BALL1,
    NATIONALPARKBUGCONTEST_POKE_BALL2,
};

const Script_fn_t NationalParkBugContest_SceneScripts[] = {
    0,
};

const struct MapCallback NationalParkBugContest_MapCallbacks[] = {
    0,
};

const struct MapScripts NationalParkBugContest_MapScripts = {
    .scene_script_count = 0, // lengthof(NationalParkBugContest_SceneScripts),
    .scene_scripts = NationalParkBugContest_SceneScripts,

    .callback_count = 0, // lengthof(NationalParkBugContest_MapCallbacks),
    .callbacks = NationalParkBugContest_MapCallbacks,
};

static const struct CoordEvent NationalParkBugContest_CoordEvents[] = {
    0,
};

static const struct BGEvent NationalParkBugContest_BGEvents[] = {
    bg_event(14, 44, BGEVENT_READ, &NationalParkBugContestRelaxationSquareSign),
    bg_event(27, 31, BGEVENT_READ, &NationalParkBugContestBattleNoticeSign),
    bg_event(6, 47, BGEVENT_ITEM, &NationalParkBugContestHiddenFullHeal),
    bg_event(12, 4, BGEVENT_READ, &NationalParkBugContestTrainerTipsSign),
};

static const struct WarpEventData NationalParkBugContest_WarpEvents[] = {
    warp_event(33, 18, ROUTE_36_NATIONAL_PARK_GATE, 1),
    warp_event(33, 19, ROUTE_36_NATIONAL_PARK_GATE, 1),
    warp_event(10, 47, ROUTE_35_NATIONAL_PARK_GATE, 1),
    warp_event(11, 47, ROUTE_35_NATIONAL_PARK_GATE, 1),
};

static const struct ObjEvent NationalParkBugContest_ObjectEvents[] = {
    object_event(19, 29, SPRITE_YOUNGSTER, SPRITEMOVEDATA_WANDER, 2, 2, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &BugCatchingContestant1AScript, EVENT_BUG_CATCHING_CONTESTANT_1A),
    object_event(28, 22, SPRITE_YOUNGSTER, SPRITEMOVEDATA_WANDER, 2, 2, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &BugCatchingContestant2AScript, EVENT_BUG_CATCHING_CONTESTANT_2A),
    object_event(9, 18, SPRITE_ROCKER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &BugCatchingContestant3AScript, EVENT_BUG_CATCHING_CONTESTANT_3A),
    object_event(7, 13, SPRITE_POKEFAN_M, SPRITEMOVEDATA_WALK_UP_DOWN, 1, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, &BugCatchingContestant4AScript, EVENT_BUG_CATCHING_CONTESTANT_4A),
    object_event(23, 9, SPRITE_YOUNGSTER, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &BugCatchingContestant5AScript, EVENT_BUG_CATCHING_CONTESTANT_5A),
    object_event(27, 13, SPRITE_YOUNGSTER, SPRITEMOVEDATA_WANDER, 3, 3, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &BugCatchingContestant6AScript, EVENT_BUG_CATCHING_CONTESTANT_6A),
    object_event(7, 23, SPRITE_LASS, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 2, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &BugCatchingContestant7AScript, EVENT_BUG_CATCHING_CONTESTANT_7A),
    object_event(11, 27, SPRITE_YOUNGSTER, SPRITEMOVEDATA_WANDER, 1, 1, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &BugCatchingContestant8AScript, EVENT_BUG_CATCHING_CONTESTANT_8A),
    object_event(16, 8, SPRITE_YOUNGSTER, SPRITEMOVEDATA_WANDER, 1, 1, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &BugCatchingContestant9AScript, EVENT_BUG_CATCHING_CONTESTANT_9A),
    object_event(17, 34, SPRITE_YOUNGSTER, SPRITEMOVEDATA_WANDER, 3, 3, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &BugCatchingContestant10AScript, EVENT_BUG_CATCHING_CONTESTANT_10A),
    object_event(35, 12, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &NationalParkBugContestParlyzHeal, EVENT_NATIONAL_PARK_PARLYZ_HEAL),
    object_event(1, 43, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &NationalParkBugContestTMDig, EVENT_NATIONAL_PARK_TM_DIG),
};

const struct MapEvents NationalParkBugContest_MapEvents = {
    .warp_event_count = lengthof(NationalParkBugContest_WarpEvents),
    .warp_events = NationalParkBugContest_WarpEvents,

    .coord_event_count = 0, // lengthof(NationalParkBugContest_CoordEvents),
    .coord_events = NationalParkBugContest_CoordEvents,

    .bg_event_count = lengthof(NationalParkBugContest_BGEvents),
    .bg_events = NationalParkBugContest_BGEvents,

    .obj_event_count = lengthof(NationalParkBugContest_ObjectEvents),
    .obj_events = NationalParkBugContest_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "NationalParkBugContest.h"

bool BugCatchingContestant1AScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(BugCatchingContestant1AText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool BugCatchingContestant2AScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(BugCatchingContestant2AText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool BugCatchingContestant3AScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(BugCatchingContestant3AText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool BugCatchingContestant4AScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(BugCatchingContestant4AText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool BugCatchingContestant5AScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(BugCatchingContestant5AText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool BugCatchingContestant6AScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(BugCatchingContestant6AText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool BugCatchingContestant7AScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(BugCatchingContestant7AText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool BugCatchingContestant8AScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(BugCatchingContestant8AText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool BugCatchingContestant9AScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(BugCatchingContestant9AText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool BugCatchingContestant10AScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(BugCatchingContestant10AText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool NationalParkBugContestRelaxationSquareSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(NationalParkBugContestRelaxationSquareText)
    SCRIPT_END
}
bool NationalParkBugContestBattleNoticeSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(NationalParkBugContestBattleNoticeText)
    SCRIPT_END
}
bool NationalParkBugContestTrainerTipsSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(NationalParkBugContestTrainerTipsText)
    SCRIPT_END
}
const struct ItemBall NationalParkBugContestParlyzHeal = {PARLYZ_HEAL, 1};
const struct ItemBall NationalParkBugContestTMDig = {TM_DIG, 1};
const struct HiddenItem NationalParkBugContestHiddenFullHeal = {FULL_HEAL, EVENT_NATIONAL_PARK_HIDDEN_FULL_HEAL};
const txt_cmd_s BugCatchingContestant1AText[] = {
    text_start("DON: I'm going to"
        t_line "win! Don't bother"
        t_cont "me."
        t_done )
};
const txt_cmd_s BugCatchingContestant2AText[] = {
    text_start("ED: My PARASECT"
        t_line "puts #MON to"
        t_cont "sleep with SPORE."
        t_done )
};
const txt_cmd_s BugCatchingContestant3AText[] = {
    text_start("NICK: I'm raising"
        t_line "fast #MON for"
        t_cont "battles."
        t_done )
};
const txt_cmd_s BugCatchingContestant4AText[] = {
    text_start("WILLIAM: I'm not"
        t_line "concerned about"
        t_cont "winning."
        t_para "I'm just looking"
        t_line "for rare #MON."
        t_done )
};
const txt_cmd_s BugCatchingContestant5AText[] = {
    text_start("BENNY: Ssh! You'll"
        t_line "scare off SCYTHER."
        t_para "I'll talk to you"
        t_line "later."
        t_done )
};
const txt_cmd_s BugCatchingContestant6AText[] = {
    text_start("BARRY: You should"
        t_line "weaken bug #MON"
        t_para "first, then throw"
        t_line "a BALL."
        t_done )
};
const txt_cmd_s BugCatchingContestant7AText[] = {
    text_start("CINDY: I love bug"
        t_line "#MON."
        t_para "I guess you must"
        t_line "like them too."
        t_done )
};
const txt_cmd_s BugCatchingContestant8AText[] = {
    text_start("JOSH: I've been"
        t_line "collecting bug"
        t_para "#MON since I"
        t_line "was just a baby."
        t_para "There's no way I'm"
        t_line "going to lose!"
        t_done )
};
const txt_cmd_s BugCatchingContestant9AText[] = {
    text_start("SAMUEL: If you've"
        t_line "got the time to"
        t_para "chat, go find some"
        t_line "bug #MON."
        t_done )
};
const txt_cmd_s BugCatchingContestant10AText[] = {
    text_start("KIPP: I've studied"
        t_line "about bug #MON"
        t_cont "a lot."
        t_para "I'm going to win"
        t_line "for sure."
        t_done )
};
const txt_cmd_s NationalParkBugContestRelaxationSquareText[] = {
    text_start("RELAXATION SQUARE"
        t_line "NATIONAL PARK"
        t_done )
};
const txt_cmd_s NationalParkBugContestBattleNoticeText[] = {
    text_start("What is this"
        t_line "notice?"
        t_para "Please battle only"
        t_line "in the grass."
        t_para "NATIONAL PARK"
        t_line "WARDEN'S OFFICE"
        t_done )
};
const txt_cmd_s NationalParkBugContestTrainerTipsText[] = {
    text_start("TRAINER TIPS"
        t_para "Print out MAIL by"
        t_line "opening it then"
        t_cont "pressing START."
        t_done )
    //db(0, 0) // filler
};
