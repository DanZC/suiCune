#include "../constants.h"
#include "../util/scripting.h"
#include "RuinsOfAlphOmanyteChamber.h"
//// EVENTS
const Script_fn_t RuinsOfAlphOmanyteChamber_SceneScripts[] = {
    RuinsOfAlphOmanyteChamber_MapScripts_CheckWall , //  SCENE_DEFAULT,
    RuinsOfAlphOmanyteChamber_MapScripts_DummyScene , //  SCENE_FINISHED,
};

const struct MapCallback RuinsOfAlphOmanyteChamber_MapCallbacks[] = {
    map_callback(MAPCALLBACK_TILES, RuinsOfAlphOmanyteChamber_MapScripts_HiddenDoors),
};

const struct MapScripts RuinsOfAlphOmanyteChamber_MapScripts = {
    .scene_script_count = lengthof(RuinsOfAlphOmanyteChamber_SceneScripts),
    .scene_scripts = RuinsOfAlphOmanyteChamber_SceneScripts,

    .callback_count = lengthof(RuinsOfAlphOmanyteChamber_MapCallbacks),
    .callbacks = RuinsOfAlphOmanyteChamber_MapCallbacks,
};

static const struct CoordEvent RuinsOfAlphOmanyteChamber_CoordEvents[] = {
    0,
};

static const struct BGEvent RuinsOfAlphOmanyteChamber_BGEvents[] = {
    bg_event(2, 3, BGEVENT_READ, &RuinsOfAlphOmanyteChamberAncientReplica),
    bg_event(5, 3, BGEVENT_READ, &RuinsOfAlphOmanyteChamberAncientReplica),
    bg_event(3, 2, BGEVENT_UP, &RuinsOfAlphOmanyteChamberPuzzle),
    bg_event(4, 2, BGEVENT_UP, &RuinsOfAlphOmanyteChamberDescriptionSign),
    bg_event(3, 0, BGEVENT_UP, &RuinsOfAlphOmanyteChamberWallPatternLeft),
    bg_event(4, 0, BGEVENT_UP, &RuinsOfAlphOmanyteChamberWallPatternRight),
};

static const struct WarpEventData RuinsOfAlphOmanyteChamber_WarpEvents[] = {
    warp_event(3, 9, RUINS_OF_ALPH_OUTSIDE, 3),
    warp_event(4, 9, RUINS_OF_ALPH_OUTSIDE, 3),
    warp_event(3, 3, RUINS_OF_ALPH_INNER_CHAMBER, 6),
    warp_event(4, 3, RUINS_OF_ALPH_INNER_CHAMBER, 7),
    warp_event(4, 0, RUINS_OF_ALPH_OMANYTE_ITEM_ROOM, 1),
};

static const struct ObjEvent RuinsOfAlphOmanyteChamber_ObjectEvents[] = {
    0,
};

const struct MapEvents RuinsOfAlphOmanyteChamber_MapEvents = {
    .warp_event_count = lengthof(RuinsOfAlphOmanyteChamber_WarpEvents),
    .warp_events = RuinsOfAlphOmanyteChamber_WarpEvents,

    .coord_event_count = 0, // lengthof(RuinsOfAlphOmanyteChamber_CoordEvents),
    .coord_events = RuinsOfAlphOmanyteChamber_CoordEvents,

    .bg_event_count = lengthof(RuinsOfAlphOmanyteChamber_BGEvents),
    .bg_events = RuinsOfAlphOmanyteChamber_BGEvents,

    .obj_event_count = 0, // lengthof(RuinsOfAlphOmanyteChamber_ObjectEvents),
    .obj_events = RuinsOfAlphOmanyteChamber_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "RuinsOfAlphOmanyteChamber.h"

bool RuinsOfAlphOmanyteChamber_MapScripts_CheckWall(script_s* s) {
    SCRIPT_BEGIN
    special(OmanyteChamber)
    checkevent(EVENT_WALL_OPENED_IN_OMANYTE_CHAMBER)
    iftrue(OpenWall)
    s_end
OpenWall:
    sdefer(RuinsOfAlphOmanyteChamber_MapScripts_WallOpenScript);
    s_end
    SCRIPT_END
}
bool RuinsOfAlphOmanyteChamber_MapScripts_DummyScene(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool RuinsOfAlphOmanyteChamber_MapScripts_HiddenDoors(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_WALL_OPENED_IN_OMANYTE_CHAMBER)
    iftrue(WallOpen)
    changeblock(4, 0, 0x2e) // closed wall
WallOpen:
    checkevent(EVENT_SOLVED_OMANYTE_PUZZLE)
    iffalse(FloorClosed)
    s_endcallback
FloorClosed:
    changeblock(2, 2, 0x01) // left floor
    changeblock(4, 2, 0x02) // right floor
    s_endcallback
    SCRIPT_END
}
bool RuinsOfAlphOmanyteChamber_MapScripts_WallOpenScript(script_s* s) {
    SCRIPT_BEGIN
    pause(30)
    earthquake(30)
    showemote(EMOTE_SHOCK, PLAYER, 20)
    pause(30)
    playsound(SFX_STRENGTH)
    changeblock(4, 0, 0x30) // open wall
    reloadmappart
    earthquake(50)
    setscene(SCENE_FINISHED)
    closetext
    s_end
    SCRIPT_END
}
bool RuinsOfAlphOmanyteChamberPuzzle(script_s* s) {
    SCRIPT_BEGIN
    refreshscreen
    setval(UNOWNPUZZLE_OMANYTE)
    special(UnownPuzzle)
    closetext
    iftrue(PuzzleComplete)
    s_end
PuzzleComplete:
    setevent(EVENT_RUINS_OF_ALPH_INNER_CHAMBER_TOURISTS)
    setevent(EVENT_SOLVED_OMANYTE_PUZZLE)
    setflag(ENGINE_UNLOCKED_UNOWNS_L_TO_R)
    setmapscene(RUINS_OF_ALPH_INNER_CHAMBER, SCENE_RUINSOFALPHINNERCHAMBER_STRANGE_PRESENCE)
    earthquake(30)
    showemote(EMOTE_SHOCK, PLAYER, 15)
    changeblock(2, 2, 0x18) // left hole
    changeblock(4, 2, 0x19) // right hole
    reloadmappart
    playsound(SFX_STRENGTH)
    earthquake(80)
    applymovement(PLAYER, RuinsOfAlphOmanyteChamberSkyfallTopMovement)
    playsound(SFX_KINESIS)
    waitsfx
    pause(20)
    warpcheck
    s_end
    SCRIPT_END
}
bool RuinsOfAlphOmanyteChamberAncientReplica(script_s* s) {
    SCRIPT_BEGIN
    jumptext(RuinsOfAlphOmanyteChamberAncientReplicaText)
    SCRIPT_END
}
bool RuinsOfAlphOmanyteChamberDescriptionSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(RuinsOfAlphOmanyteChamberDescriptionText)
    SCRIPT_END
}
bool RuinsOfAlphOmanyteChamberWallPatternLeft(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(RuinsOfAlphOmanyteChamberWallPatternLeftText)
    setval(UNOWNWORDS_WATER)
    special(DisplayUnownWords)
    closetext
    s_end
    SCRIPT_END
}
bool RuinsOfAlphOmanyteChamberWallPatternRight(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_WALL_OPENED_IN_OMANYTE_CHAMBER)
    iftrue(WallOpen)
    opentext
    writetext(RuinsOfAlphOmanyteChamberWallPatternRightText)
    setval(UNOWNWORDS_WATER)
    special(DisplayUnownWords)
    closetext
    s_end
WallOpen:
    opentext
    writetext(RuinsOfAlphOmanyteChamberWallHoleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const uint8_t RuinsOfAlphOmanyteChamberSkyfallTopMovement[] = {
    movement_skyfall_top,
    movement_step_end,
};
const txt_cmd_s RuinsOfAlphOmanyteChamberWallPatternLeftText[] = {
    text_start("Patterns appeared"
        t_line "on the walls…"
        t_done )
};
const txt_cmd_s RuinsOfAlphOmanyteChamberUnownText[] = {
    text_start("It's UNOWN text!"
        t_done )
};
const txt_cmd_s RuinsOfAlphOmanyteChamberWallPatternRightText[] = {
    text_start("Patterns appeared"
        t_line "on the walls…"
        t_done )
};
const txt_cmd_s RuinsOfAlphOmanyteChamberWallHoleText[] = {
    text_start("There's a big hole"
        t_line "in the wall!"
        t_done )
};
const txt_cmd_s RuinsOfAlphOmanyteChamberAncientReplicaText[] = {
    text_start("It's a replica of"
        t_line "an ancient #-"
        t_cont "MON."
        t_done )
};
const txt_cmd_s RuinsOfAlphOmanyteChamberDescriptionText[] = {
    text_start("This #MON"
        t_line "drifted in the"
        t_para "sea by twisting"
        t_line "its ten tentacles."
        t_done )
    //db(0, 0) // filler
};
