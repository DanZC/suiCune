#include "../constants.h"
#include "../util/scripting.h"
#include "RuinsOfAlphKabutoChamber.h"
#include "RuinsOfAlphResearchCenter.h"
//// EVENTS
enum {
    RUINSOFALPHKABUTOCHAMBER_RECEPTIONIST = 2,
    RUINSOFALPHKABUTOCHAMBER_SCIENTIST,
};

const Script_fn_t RuinsOfAlphKabutoChamber_SceneScripts[] = {
    RuinsOfAlphKabutoChamber_MapScripts_CheckWall , //  SCENE_DEFAULT,
    RuinsOfAlphKabutoChamber_MapScripts_DummyScene , //  SCENE_FINISHED,
};

const struct MapCallback RuinsOfAlphKabutoChamber_MapCallbacks[] = {
    map_callback(MAPCALLBACK_TILES, RuinsOfAlphKabutoChamber_MapScripts_HiddenDoors),
};

const struct MapScripts RuinsOfAlphKabutoChamber_MapScripts = {
    .scene_script_count = lengthof(RuinsOfAlphKabutoChamber_SceneScripts),
    .scene_scripts = RuinsOfAlphKabutoChamber_SceneScripts,

    .callback_count = lengthof(RuinsOfAlphKabutoChamber_MapCallbacks),
    .callbacks = RuinsOfAlphKabutoChamber_MapCallbacks,
};

static const struct CoordEvent RuinsOfAlphKabutoChamber_CoordEvents[] = {
    0,
};

static const struct BGEvent RuinsOfAlphKabutoChamber_BGEvents[] = {
    bg_event(2, 3, BGEVENT_READ, &RuinsOfAlphKabutoChamberAncientReplica),
    bg_event(5, 3, BGEVENT_READ, &RuinsOfAlphKabutoChamberAncientReplica),
    bg_event(3, 2, BGEVENT_UP, &RuinsOfAlphKabutoChamberPuzzle),
    bg_event(4, 2, BGEVENT_UP, &RuinsOfAlphKabutoChamberDescriptionSign),
    bg_event(3, 0, BGEVENT_UP, &RuinsOfAlphKabutoChamberWallPatternLeft),
    bg_event(4, 0, BGEVENT_UP, &RuinsOfAlphKabutoChamberWallPatternRight),
};

static const struct WarpEventData RuinsOfAlphKabutoChamber_WarpEvents[] = {
    warp_event(3, 9, RUINS_OF_ALPH_OUTSIDE, 2),
    warp_event(4, 9, RUINS_OF_ALPH_OUTSIDE, 2),
    warp_event(3, 3, RUINS_OF_ALPH_INNER_CHAMBER, 4),
    warp_event(4, 3, RUINS_OF_ALPH_INNER_CHAMBER, 5),
    warp_event(4, 0, RUINS_OF_ALPH_KABUTO_ITEM_ROOM, 1),
};

static const struct ObjEvent RuinsOfAlphKabutoChamber_ObjectEvents[] = {
    object_event(5, 5, SPRITE_RECEPTIONIST, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &RuinsOfAlphKabutoChamberReceptionistScript, EVENT_RUINS_OF_ALPH_KABUTO_CHAMBER_RECEPTIONIST),
    object_event(3, 1, SPRITE_SCIENTIST, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &RuinsOfAlphKabutoChamberScientistScript, -1),
};

const struct MapEvents RuinsOfAlphKabutoChamber_MapEvents = {
    .warp_event_count = lengthof(RuinsOfAlphKabutoChamber_WarpEvents),
    .warp_events = RuinsOfAlphKabutoChamber_WarpEvents,

    .coord_event_count = 0, // lengthof(RuinsOfAlphKabutoChamber_CoordEvents),
    .coord_events = RuinsOfAlphKabutoChamber_CoordEvents,

    .bg_event_count = lengthof(RuinsOfAlphKabutoChamber_BGEvents),
    .bg_events = RuinsOfAlphKabutoChamber_BGEvents,

    .obj_event_count = lengthof(RuinsOfAlphKabutoChamber_ObjectEvents),
    .obj_events = RuinsOfAlphKabutoChamber_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "RuinsOfAlphKabutoChamber.h"

bool RuinsOfAlphKabutoChamber_MapScripts_CheckWall(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_WALL_OPENED_IN_KABUTO_CHAMBER)
    iftrue(OpenWall)
    s_end
OpenWall:
    sdefer(RuinsOfAlphKabutoChamber_MapScripts_WallOpenScript);
    s_end
    SCRIPT_END
}
bool RuinsOfAlphKabutoChamber_MapScripts_DummyScene(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool RuinsOfAlphKabutoChamber_MapScripts_HiddenDoors(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_WALL_OPENED_IN_KABUTO_CHAMBER)
    iftrue(WallOpen)
    changeblock(4, 0, 0x2e) // closed wall
WallOpen:
    checkevent(EVENT_SOLVED_KABUTO_PUZZLE)
    iffalse(FloorClosed)
    s_endcallback
FloorClosed:
    changeblock(2, 2, 0x01) // left floor
    changeblock(4, 2, 0x02) // right floor
    s_endcallback
    SCRIPT_END
}
bool RuinsOfAlphKabutoChamber_MapScripts_WallOpenScript(script_s* s) {
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
bool RuinsOfAlphKabutoChamberReceptionistScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(RuinsOfAlphKabutoChamberReceptionistText)
    SCRIPT_END
}
bool RuinsOfAlphKabutoChamberPuzzle(script_s* s) {
    SCRIPT_BEGIN
    refreshscreen
    setval(UNOWNPUZZLE_KABUTO)
    special(UnownPuzzle)
    closetext
    iftrue(PuzzleComplete)
    s_end
PuzzleComplete:
    setevent(EVENT_RUINS_OF_ALPH_INNER_CHAMBER_TOURISTS)
    setevent(EVENT_SOLVED_KABUTO_PUZZLE)
    setflag(ENGINE_UNLOCKED_UNOWNS_A_TO_K)
    setevent(EVENT_RUINS_OF_ALPH_KABUTO_CHAMBER_RECEPTIONIST)
    setmapscene(RUINS_OF_ALPH_INNER_CHAMBER, SCENE_RUINSOFALPHINNERCHAMBER_STRANGE_PRESENCE)
    earthquake(30)
    showemote(EMOTE_SHOCK, PLAYER, 15)
    changeblock(2, 2, 0x18) // left hole
    changeblock(4, 2, 0x19) // right hole
    reloadmappart
    playsound(SFX_STRENGTH)
    earthquake(80)
    applymovement(PLAYER, RuinsOfAlphKabutoChamberSkyfallTopMovement)
    playsound(SFX_KINESIS)
    waitsfx
    pause(20)
    warpcheck
    s_end
    SCRIPT_END
}
bool RuinsOfAlphKabutoChamberScientistScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    readvar(VAR_UNOWNCOUNT)
    ifequal(NUM_UNOWN, AllUnownCaught)
    checkevent(EVENT_WALL_OPENED_IN_KABUTO_CHAMBER)
    iftrue(WallOpen)
    checkevent(EVENT_SOLVED_KABUTO_PUZZLE)
    iffalse(PuzzleIncomplete)
    writetext(RuinsOfAlphKabutoChamberScientistTremorText)
    promptbutton
PuzzleIncomplete:
    writetext(RuinsOfAlphKabutoChamberScientistCrypticText)
    waitbutton
    closetext
    turnobject(RUINSOFALPHKABUTOCHAMBER_SCIENTIST, UP)
    s_end
WallOpen:
    writetext(RuinsOfAlphKabutoChamberScientistHoleText)
    waitbutton
    closetext
    s_end
AllUnownCaught:
    writetext(RuinsOfAlphResearchCenterScientist1Text_GotAllUnown)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool RuinsOfAlphKabutoChamberAncientReplica(script_s* s) {
    SCRIPT_BEGIN
    jumptext(RuinsOfAlphKabutoChamberAncientReplicaText)
    SCRIPT_END
}
bool RuinsOfAlphKabutoChamberDescriptionSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(RuinsOfAlphKabutoChamberDescriptionText)
    SCRIPT_END
}
bool RuinsOfAlphKabutoChamberWallPatternLeft(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(RuinsOfAlphKabutoChamberWallPatternLeftText)
    setval(UNOWNWORDS_ESCAPE)
    special(DisplayUnownWords)
    closetext
    s_end
    SCRIPT_END
}
bool RuinsOfAlphKabutoChamberWallPatternRight(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_WALL_OPENED_IN_KABUTO_CHAMBER)
    iftrue(WallOpen)
    opentext
    writetext(RuinsOfAlphKabutoChamberWallPatternRightText)
    setval(UNOWNWORDS_ESCAPE)
    special(DisplayUnownWords)
    closetext
    s_end
WallOpen:
    opentext
    writetext(RuinsOfAlphKabutoChamberWallHoleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const uint8_t RuinsOfAlphKabutoChamberSkyfallTopMovement[] = {
    movement_skyfall_top,
    movement_step_end,
};
const txt_cmd_s RuinsOfAlphKabutoChamberReceptionistText[] = {
    text_start("Welcome to this"
        t_line "chamber."
        t_para "There are sliding"
        t_line "panels that depict"
        t_para "a #MON drawn by"
        t_line "the ancients."
        t_para "Slide the panels"
        t_line "around to form the"
        t_cont "picture."
        t_para "To the right is a"
        t_line "description of the"
        t_cont "#MON."
        t_para "Scientists in the"
        t_line "back are examining"
        t_para "some newly found"
        t_line "patterns."
        t_done )
};
const txt_cmd_s RuinsOfAlphKabutoChamberScientistCrypticText[] = {
    text_start("Recently, strange,"
        t_line "cryptic patterns"
        t_cont "have appeared."
        t_para "It's odd. They"
        t_line "weren't here a"
        t_cont "little while ago…"
        t_para "You should take a"
        t_line "look at the walls."
        t_done )
};
const txt_cmd_s RuinsOfAlphKabutoChamberScientistHoleText[] = {
    text_start("Ah! Here's another"
        t_line "huge hole!"
        t_para "It's big enough to"
        t_line "go through!"
        t_done )
};
const txt_cmd_s RuinsOfAlphKabutoChamberScientistTremorText[] = {
    text_start("That tremor was"
        t_line "pretty scary!"
        t_para "But I'm more"
        t_line "concerned about"
        t_cont "this wall here…"
        t_done )
};
const txt_cmd_s RuinsOfAlphKabutoChamberUnusedText[] = {
    text_start("The patterns on"
        t_line "the wall appear to"
        t_cont "be words!"
        t_para "And those sliding"
        t_line "stone panels seem"
        t_para "to be signals of"
        t_line "some kind."
        t_para "I think they make"
        t_line "#MON appear,"
        t_para "but it's not clear"
        t_line "yet…"
        t_done )
};
const txt_cmd_s RuinsOfAlphKabutoChamberWallPatternLeftText[] = {
    text_start("Patterns appeared"
        t_line "on the walls…"
        t_done )
};
const txt_cmd_s RuinsOfAlphKabutoChamberUnownText[] = {
    text_start("It's UNOWN text!"
        t_done )
};
const txt_cmd_s RuinsOfAlphKabutoChamberWallPatternRightText[] = {
    text_start("Patterns appeared"
        t_line "on the walls…"
        t_done )
};
const txt_cmd_s RuinsOfAlphKabutoChamberWallHoleText[] = {
    text_start("There's a big hole"
        t_line "in the wall!"
        t_done )
};
const txt_cmd_s RuinsOfAlphKabutoChamberAncientReplicaText[] = {
    text_start("It's a replica of"
        t_line "an ancient #-"
        t_cont "MON."
        t_done )
};
const txt_cmd_s RuinsOfAlphKabutoChamberDescriptionText[] = {
    text_start("A #MON that hid"
        t_line "on the sea floor."
        t_para "Eyes on its back"
        t_line "scanned the area."
        t_done )
    //db(0, 0) // filler
};
