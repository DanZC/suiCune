#include "../constants.h"
#include "../util/scripting.h"
#include "RuinsOfAlphAerodactylChamber.h"
//// EVENTS
const Script_fn_t RuinsOfAlphAerodactylChamber_SceneScripts[] = {
    RuinsOfAlphAerodactylChamber_MapScripts_CheckWall , //  SCENE_DEFAULT,
    RuinsOfAlphAerodactylChamber_MapScripts_DummyScene , //  SCENE_FINISHED,
};

const struct MapCallback RuinsOfAlphAerodactylChamber_MapCallbacks[] = {
    map_callback(MAPCALLBACK_TILES, RuinsOfAlphAerodactylChamber_MapScripts_HiddenDoors),
};

const struct MapScripts RuinsOfAlphAerodactylChamber_MapScripts = {
    .scene_script_count = lengthof(RuinsOfAlphAerodactylChamber_SceneScripts),
    .scene_scripts = RuinsOfAlphAerodactylChamber_SceneScripts,

    .callback_count = lengthof(RuinsOfAlphAerodactylChamber_MapCallbacks),
    .callbacks = RuinsOfAlphAerodactylChamber_MapCallbacks,
};

static const struct CoordEvent RuinsOfAlphAerodactylChamber_CoordEvents[] = {
    0,
};

static const struct BGEvent RuinsOfAlphAerodactylChamber_BGEvents[] = {
    bg_event(2, 3, BGEVENT_READ, &RuinsOfAlphAerodactylChamberAncientReplica),
    bg_event(5, 3, BGEVENT_READ, &RuinsOfAlphAerodactylChamberAncientReplica),
    bg_event(3, 2, BGEVENT_UP, &RuinsOfAlphAerodactylChamberPuzzle),
    bg_event(4, 2, BGEVENT_UP, &RuinsOfAlphAerodactylChamberDescriptionSign),
    bg_event(3, 0, BGEVENT_UP, &RuinsOfAlphAerodactylChamberWallPatternLeft),
    bg_event(4, 0, BGEVENT_UP, &RuinsOfAlphAerodactylChamberWallPatternRight),
};

static const struct WarpEventData RuinsOfAlphAerodactylChamber_WarpEvents[] = {
    warp_event(3, 9, RUINS_OF_ALPH_OUTSIDE, 4),
    warp_event(4, 9, RUINS_OF_ALPH_OUTSIDE, 4),
    warp_event(3, 3, RUINS_OF_ALPH_INNER_CHAMBER, 8),
    warp_event(4, 3, RUINS_OF_ALPH_INNER_CHAMBER, 9),
    warp_event(4, 0, RUINS_OF_ALPH_AERODACTYL_ITEM_ROOM, 1),
};

static const struct ObjEvent RuinsOfAlphAerodactylChamber_ObjectEvents[] = {
    0,
};

const struct MapEvents RuinsOfAlphAerodactylChamber_MapEvents = {
    .warp_event_count = lengthof(RuinsOfAlphAerodactylChamber_WarpEvents),
    .warp_events = RuinsOfAlphAerodactylChamber_WarpEvents,

    .coord_event_count = 0, // lengthof(RuinsOfAlphAerodactylChamber_CoordEvents),
    .coord_events = RuinsOfAlphAerodactylChamber_CoordEvents,

    .bg_event_count = lengthof(RuinsOfAlphAerodactylChamber_BGEvents),
    .bg_events = RuinsOfAlphAerodactylChamber_BGEvents,

    .obj_event_count = 0, // lengthof(RuinsOfAlphAerodactylChamber_ObjectEvents),
    .obj_events = RuinsOfAlphAerodactylChamber_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "RuinsOfAlphAerodactylChamber.h"

bool RuinsOfAlphAerodactylChamber_MapScripts_CheckWall(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_WALL_OPENED_IN_AERODACTYL_CHAMBER)
    iftrue_jump(RuinsOfAlphAerodactylChamber_MapScripts_OpenWall)
    s_end
    SCRIPT_END
}
bool RuinsOfAlphAerodactylChamber_MapScripts_OpenWall(script_s* s) {
    SCRIPT_BEGIN
    sdefer(RuinsOfAlphAerodactylChamber_MapScripts_WallOpenScript)
    s_end
    SCRIPT_END
}
bool RuinsOfAlphAerodactylChamber_MapScripts_DummyScene(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool RuinsOfAlphAerodactylChamber_MapScripts_HiddenDoors(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_WALL_OPENED_IN_AERODACTYL_CHAMBER)
    iftrue_jump(RuinsOfAlphAerodactylChamber_MapScripts_WallOpen)
    changeblock(4, 0, 0x2e) // closed wall
    SCRIPT_FALLTHROUGH(RuinsOfAlphAerodactylChamber_MapScripts_WallOpen)
}
bool RuinsOfAlphAerodactylChamber_MapScripts_WallOpen(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_SOLVED_AERODACTYL_PUZZLE)
    iffalse_jump(RuinsOfAlphAerodactylChamber_MapScripts_FloorClosed)
    s_endcallback
    SCRIPT_END
}
bool RuinsOfAlphAerodactylChamber_MapScripts_FloorClosed(script_s* s) {
    SCRIPT_BEGIN
    changeblock(2, 2, 0x01) // left floor
    changeblock(4, 2, 0x02) // right floor
    s_endcallback
    SCRIPT_END
}
bool RuinsOfAlphAerodactylChamber_MapScripts_WallOpenScript(script_s* s) {
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
bool RuinsOfAlphAerodactylChamberPuzzle(script_s* s) {
    SCRIPT_BEGIN
    refreshscreen
    setval(UNOWNPUZZLE_AERODACTYL)
    special(UnownPuzzle)
    closetext
    iftrue(PuzzleComplete)
    s_end
PuzzleComplete:
    setevent(EVENT_RUINS_OF_ALPH_INNER_CHAMBER_TOURISTS)
    setevent(EVENT_SOLVED_AERODACTYL_PUZZLE)
    setflag(ENGINE_UNLOCKED_UNOWNS_S_TO_W)
    setmapscene(RUINS_OF_ALPH_INNER_CHAMBER, SCENE_RUINSOFALPHINNERCHAMBER_STRANGE_PRESENCE)
    earthquake(30)
    showemote(EMOTE_SHOCK, PLAYER, 15)
    changeblock(2, 2, 0x18) // left hole
    changeblock(4, 2, 0x19) // right hole
    reloadmappart
    playsound(SFX_STRENGTH)
    earthquake(80)
    applymovement(PLAYER, RuinsOfAlphAerodactylChamberSkyfallTopMovement)
    playsound(SFX_KINESIS)
    waitsfx
    pause(20)
    warpcheck
    s_end
    SCRIPT_END
}
bool RuinsOfAlphAerodactylChamberAncientReplica(script_s* s) {
    SCRIPT_BEGIN
    jumptext(RuinsOfAlphAerodactylChamberAncientReplicaText)
    SCRIPT_END
}
bool RuinsOfAlphAerodactylChamberDescriptionSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(RuinsOfAlphAerodactylChamberDescriptionText)
    SCRIPT_END
}
bool RuinsOfAlphAerodactylChamberWallPatternLeft(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(RuinsOfAlphAerodactylChamberWallPatternLeftText)
    setval(UNOWNWORDS_LIGHT)
    special(DisplayUnownWords)
    closetext
    s_end
    SCRIPT_END
}
bool RuinsOfAlphAerodactylChamberWallPatternRight(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_WALL_OPENED_IN_AERODACTYL_CHAMBER)
    iftrue(WallOpen)
    opentext
    writetext(RuinsOfAlphAerodactylChamberWallPatternRightText)
    setval(UNOWNWORDS_LIGHT)
    special(DisplayUnownWords)
    closetext
    s_end
WallOpen:
    opentext
    writetext(RuinsOfAlphAerodactylChamberWallHoleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const uint8_t RuinsOfAlphAerodactylChamberSkyfallTopMovement[] = {
    movement_skyfall_top,
    movement_step_end
};
const txt_cmd_s RuinsOfAlphAerodactylChamberWallPatternLeftText[] = {
    text_start("Patterns appeared"
        t_line "on the walls…"
        t_done )
};
const txt_cmd_s RuinsOfAlphAerodactylChamberUnownText[] = {
    text_start("It's UNOWN text!"
        t_done )
};
const txt_cmd_s RuinsOfAlphAerodactylChamberWallPatternRightText[] = {
    text_start("Patterns appeared"
        t_line "on the walls…"
        t_done )
};
const txt_cmd_s RuinsOfAlphAerodactylChamberWallHoleText[] = {
    text_start("There's a big hole"
        t_line "in the wall!"
        t_done )
};
const txt_cmd_s RuinsOfAlphAerodactylChamberAncientReplicaText[] = {
    text_start("It's a replica of"
        t_line "an ancient #-"
        t_cont "MON."
        t_done )
};
const txt_cmd_s RuinsOfAlphAerodactylChamberDescriptionText[] = {
    text_start("This flying #-"
        t_line "MON attacked its"
        t_para "prey with saw-like"
        t_line "fangs."
        t_done )
    //db(0, 0) // filler
};
