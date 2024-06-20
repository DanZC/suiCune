#include "../constants.h"
#include "../util/scripting.h"
#include "RuinsOfAlphHoOhChamber.h"
//// EVENTS
const Script_fn_t RuinsOfAlphHoOhChamber_SceneScripts[] = {
    RuinsOfAlphHoOhChamber_MapScripts_CheckWall , //  SCENE_DEFAULT,
    RuinsOfAlphHoOhChamber_MapScripts_DummyScene , //  SCENE_FINISHED,
};

const struct MapCallback RuinsOfAlphHoOhChamber_MapCallbacks[] = {
    map_callback(MAPCALLBACK_TILES, RuinsOfAlphHoOhChamber_MapScripts_HiddenDoors),
};

const struct MapScripts RuinsOfAlphHoOhChamber_MapScripts = {
    .scene_script_count = lengthof(RuinsOfAlphHoOhChamber_SceneScripts),
    .scene_scripts = RuinsOfAlphHoOhChamber_SceneScripts,

    .callback_count = lengthof(RuinsOfAlphHoOhChamber_MapCallbacks),
    .callbacks = RuinsOfAlphHoOhChamber_MapCallbacks,
};

static const struct CoordEvent RuinsOfAlphHoOhChamber_CoordEvents[] = {
    0,
};

static const struct BGEvent RuinsOfAlphHoOhChamber_BGEvents[] = {
    bg_event(2, 3, BGEVENT_READ, &RuinsOfAlphHoOhChamberAncientReplica),
    bg_event(5, 3, BGEVENT_READ, &RuinsOfAlphHoOhChamberAncientReplica),
    bg_event(3, 2, BGEVENT_UP, &RuinsOfAlphHoOhChamberPuzzle),
    bg_event(4, 2, BGEVENT_UP, &RuinsOfAlphHoOhChamberDescriptionSign),
    bg_event(3, 0, BGEVENT_UP, &RuinsOfAlphHoOhChamberWallPatternLeft),
    bg_event(4, 0, BGEVENT_UP, &RuinsOfAlphHoOhChamberWallPatternRight),
};

static const struct WarpEventData RuinsOfAlphHoOhChamber_WarpEvents[] = {
    warp_event(3, 9, RUINS_OF_ALPH_OUTSIDE, 1),
    warp_event(4, 9, RUINS_OF_ALPH_OUTSIDE, 1),
    warp_event(3, 3, RUINS_OF_ALPH_INNER_CHAMBER, 2),
    warp_event(4, 3, RUINS_OF_ALPH_INNER_CHAMBER, 3),
    warp_event(4, 0, RUINS_OF_ALPH_HO_OH_ITEM_ROOM, 1),
};

static const struct ObjEvent RuinsOfAlphHoOhChamber_ObjectEvents[] = {
    0,
};

const struct MapEvents RuinsOfAlphHoOhChamber_MapEvents = {
    .warp_event_count = lengthof(RuinsOfAlphHoOhChamber_WarpEvents),
    .warp_events = RuinsOfAlphHoOhChamber_WarpEvents,

    .coord_event_count = 0, // lengthof(RuinsOfAlphHoOhChamber_CoordEvents),
    .coord_events = RuinsOfAlphHoOhChamber_CoordEvents,

    .bg_event_count = lengthof(RuinsOfAlphHoOhChamber_BGEvents),
    .bg_events = RuinsOfAlphHoOhChamber_BGEvents,

    .obj_event_count = 0, // lengthof(RuinsOfAlphHoOhChamber_ObjectEvents),
    .obj_events = RuinsOfAlphHoOhChamber_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "RuinsOfAlphHoOhChamber.h"

bool RuinsOfAlphHoOhChamber_MapScripts_CheckWall(script_s* s) {
    SCRIPT_BEGIN
    special(HoOhChamber)
    checkevent(EVENT_WALL_OPENED_IN_HO_OH_CHAMBER)
    iftrue(OpenWall)
    s_end
OpenWall:
    sdefer(RuinsOfAlphHoOhChamber_MapScripts_WallOpenScript);
    s_end
    SCRIPT_END
}
bool RuinsOfAlphHoOhChamber_MapScripts_DummyScene(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool RuinsOfAlphHoOhChamber_MapScripts_HiddenDoors(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_WALL_OPENED_IN_HO_OH_CHAMBER)
    iftrue(WallOpen)
    changeblock(4, 0, 0x2e) // closed wall
WallOpen:
    checkevent(EVENT_SOLVED_HO_OH_PUZZLE)
    iffalse(FloorClosed)
    s_endcallback
FloorClosed:
    changeblock(2, 2, 0x01) // left floor
    changeblock(4, 2, 0x02) // right floor
    s_endcallback
    SCRIPT_END
}
bool RuinsOfAlphHoOhChamber_MapScripts_WallOpenScript(script_s* s) {
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
bool RuinsOfAlphHoOhChamberPuzzle(script_s* s) {
    SCRIPT_BEGIN
    refreshscreen
    setval(UNOWNPUZZLE_HO_OH)
    special(UnownPuzzle)
    closetext
    iftrue(PuzzleComplete)
    s_end
PuzzleComplete:
    setevent(EVENT_RUINS_OF_ALPH_INNER_CHAMBER_TOURISTS)
    setevent(EVENT_SOLVED_HO_OH_PUZZLE)
    setflag(ENGINE_UNLOCKED_UNOWNS_X_TO_Z)
    setmapscene(RUINS_OF_ALPH_INNER_CHAMBER, SCENE_RUINSOFALPHINNERCHAMBER_STRANGE_PRESENCE)
    earthquake(30)
    showemote(EMOTE_SHOCK, PLAYER, 15)
    changeblock(2, 2, 0x18) // left hole
    changeblock(4, 2, 0x19) // right hole
    reloadmappart
    playsound(SFX_STRENGTH)
    earthquake(80)
    applymovement(PLAYER, RuinsOfAlphHoOhChamberSkyfallTopMovement)
    playsound(SFX_KINESIS)
    waitsfx
    pause(20)
    warpcheck
    s_end
    SCRIPT_END
}
bool RuinsOfAlphHoOhChamberAncientReplica(script_s* s) {
    SCRIPT_BEGIN
    jumptext(RuinsOfAlphHoOhChamberAncientReplicaText)
    SCRIPT_END
}
bool RuinsOfAlphHoOhChamberDescriptionSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(RuinsOfAlphHoOhChamberDescriptionText)
    SCRIPT_END
}
bool RuinsOfAlphHoOhChamberWallPatternLeft(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(RuinsOfAlphHoOhChamberWallPatternLeftText)
    setval(UNOWNWORDS_HO_OH)
    special(DisplayUnownWords)
    closetext
    s_end
    SCRIPT_END
}
bool RuinsOfAlphHoOhChamberWallPatternRight(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_WALL_OPENED_IN_HO_OH_CHAMBER)
    iftrue(WallOpen)
    opentext
    writetext(RuinsOfAlphHoOhChamberWallPatternRightText)
    setval(UNOWNWORDS_HO_OH)
    special(DisplayUnownWords)
    closetext
    s_end
WallOpen:
    opentext
    writetext(RuinsOfAlphHoOhChamberWallHoleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const uint8_t RuinsOfAlphHoOhChamberSkyfallTopMovement[] = {
    movement_skyfall_top,
    movement_step_end,
};
const txt_cmd_s RuinsOfAlphHoOhChamberWallPatternLeftText[] = {
    text_start("Patterns appeared"
        t_line "on the walls…"
        t_done )
};
const txt_cmd_s RuinsOfAlphHoOhChamberUnownText[] = {
    text_start("It's UNOWN text!"
        t_done )
};
const txt_cmd_s RuinsOfAlphHoOhChamberWallPatternRightText[] = {
    text_start("Patterns appeared"
        t_line "on the walls…"
        t_done )
};
const txt_cmd_s RuinsOfAlphHoOhChamberWallHoleText[] = {
    text_start("There's a big hole"
        t_line "in the wall!"
        t_done )
};
const txt_cmd_s RuinsOfAlphHoOhChamberAncientReplicaText[] = {
    text_start("It's a replica of"
        t_line "an ancient #-"
        t_cont "MON."
        t_done )
};
const txt_cmd_s RuinsOfAlphHoOhChamberDescriptionText[] = {
    text_start("A #MON that"
        t_line "flew gracefully on"
        t_para "rainbow-colored"
        t_line "wings."
        t_done )
    //db(0, 0) // filler
};
