#include "../constants.h"
#include "../util/scripting.h"
#include "Route43Gate.h"
//// EVENTS
enum {
    ROUTE43GATE_OFFICER = 2,
    ROUTE43GATE_ROCKET1,
    ROUTE43GATE_ROCKET2,
};

const Script_fn_t Route43Gate_SceneScripts[] = {
    Route43Gate_MapScripts_RocketShakedown , //  SCENE_DEFAULT,
    Route43Gate_MapScripts_DummyScene , //  SCENE_FINISHED,
};

const struct MapCallback Route43Gate_MapCallbacks[] = {
    map_callback(MAPCALLBACK_NEWMAP, Route43Gate_MapScripts_CheckIfRockets),
};

const struct MapScripts Route43Gate_MapScripts = {
    .scene_script_count = lengthof(Route43Gate_SceneScripts),
    .scene_scripts = Route43Gate_SceneScripts,

    .callback_count = lengthof(Route43Gate_MapCallbacks),
    .callbacks = Route43Gate_MapCallbacks,
};

static const struct CoordEvent Route43Gate_CoordEvents[] = {
    0,
};

static const struct BGEvent Route43Gate_BGEvents[] = {
    0,
};

static const struct WarpEventData Route43Gate_WarpEvents[] = {
    warp_event(4, 0, ROUTE_43, 4),
    warp_event(5, 0, ROUTE_43, 5),
    warp_event(4, 7, ROUTE_43, 3),
    warp_event(5, 7, ROUTE_43, 3),
};

static const struct ObjEvent Route43Gate_ObjectEvents[] = {
    object_event(0, 4, SPRITE_OFFICER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &OfficerScript_GuardWithSludgeBomb, EVENT_LAKE_OF_RAGE_CIVILIANS),
    object_event(2, 4, SPRITE_ROCKET, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &RocketScript_MakingABundle, EVENT_ROUTE_43_GATE_ROCKETS),
    object_event(7, 4, SPRITE_ROCKET, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &RocketScript_MakingABundle, EVENT_ROUTE_43_GATE_ROCKETS),
};

const struct MapEvents Route43Gate_MapEvents = {
    .warp_event_count = lengthof(Route43Gate_WarpEvents),
    .warp_events = Route43Gate_WarpEvents,

    .coord_event_count = 0, // lengthof(Route43Gate_CoordEvents),
    .coord_events = Route43Gate_CoordEvents,

    .bg_event_count = 0, // lengthof(Route43Gate_BGEvents),
    .bg_events = Route43Gate_BGEvents,

    .obj_event_count = lengthof(Route43Gate_ObjectEvents),
    .obj_events = Route43Gate_ObjectEvents,
};

//// CODE

#define ROUTE43GATE_TOLL 1000
bool Route43Gate_MapScripts_RocketShakedown(script_s* s) {
    SCRIPT_BEGIN
    sdefer(Route43Gate_MapScripts_RocketTakeover);
    s_end
    SCRIPT_END
}
bool Route43Gate_MapScripts_DummyScene(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool Route43Gate_MapScripts_CheckIfRockets(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_CLEARED_ROCKET_HIDEOUT)
    iftrue(NoRockets)
    setmapscene(ROUTE_43, 0) // Route 43 does not have a scene variable
    s_endcallback
NoRockets:
    setmapscene(ROUTE_43, 1) // Route 43 does not have a scene variable
    s_endcallback
    SCRIPT_END
}
bool Route43Gate_MapScripts_RocketTakeover(script_s* s) {
    SCRIPT_BEGIN
    playmusic(MUSIC_ROCKET_ENCOUNTER)
    readvar(VAR_FACING)
    ifequal_jump(DOWN, RocketScript_Southbound)
    ifequal_jump(UP, RocketScript_Northbound)
    setscene(SCENE_FINISHED)
    s_end
    SCRIPT_END
}
bool RocketScript_Southbound(script_s* s) {
    SCRIPT_BEGIN
    applymovement(PLAYER, PlayerStepsIn)
    showemote(EMOTE_SHOCK, ROUTE43GATE_ROCKET2, 15)
    applymovement(ROUTE43GATE_ROCKET2, Rocket2Script_BlocksYouSouth)
    turnobject(ROUTE43GATE_ROCKET1, UP)
    showemote(EMOTE_SHOCK, ROUTE43GATE_ROCKET1, 15)
    applymovement(ROUTE43GATE_ROCKET1, Rocket1Script_BlocksYouSouth)
    opentext
    writetext(RocketText_TollFee)
    promptbutton
    checkmoney(YOUR_MONEY, ROUTE43GATE_TOLL - 1)
    ifequal_jump(HAVE_MORE, RocketScript_TollSouth)
    sjump(RocketScript_YoureBrokeSouth)
    SCRIPT_END
}
bool RocketScript_TollSouth(script_s* s) {
    SCRIPT_BEGIN
    takemoney(YOUR_MONEY, ROUTE43GATE_TOLL)
    writetext(RocketText_ThankYou)
    sjump(RocketScript_ShakeDownSouth)
    SCRIPT_END
}
bool RocketScript_YoureBrokeSouth(script_s* s) {
    SCRIPT_BEGIN
    takemoney(YOUR_MONEY, ROUTE43GATE_TOLL)
    writetext(RocketText_AllYouGot)
    sjump(RocketScript_ShakeDownSouth)
    SCRIPT_END
}
bool RocketScript_ShakeDownSouth(script_s* s) {
    SCRIPT_BEGIN
    promptbutton
    closetext
    applymovement(ROUTE43GATE_ROCKET1, Rocket1Script_LetsYouPassSouth)
    applymovement(ROUTE43GATE_ROCKET2, Rocket2Script_LetsYouPassSouth)
    setscene(SCENE_FINISHED)
    special(RestartMapMusic)
    s_end
    SCRIPT_END
}
bool RocketScript_Northbound(script_s* s) {
    SCRIPT_BEGIN
    showemote(EMOTE_SHOCK, ROUTE43GATE_ROCKET1, 15)
    applymovement(ROUTE43GATE_ROCKET1, Rocket1Script_BlocksYouNorth)
    turnobject(ROUTE43GATE_ROCKET2, DOWN)
    showemote(EMOTE_SHOCK, ROUTE43GATE_ROCKET2, 15)
    applymovement(ROUTE43GATE_ROCKET2, Rocket2Script_BlocksYouNorth)
    opentext
    writetext(RocketText_TollFee)
    promptbutton
    checkmoney(YOUR_MONEY, ROUTE43GATE_TOLL - 1)
    ifequal_jump(HAVE_MORE, RocketScript_TollNorth)
    sjump(RocketScript_YoureBrokeNorth)
    SCRIPT_END
}
bool RocketScript_TollNorth(script_s* s) {
    SCRIPT_BEGIN
    takemoney(YOUR_MONEY, ROUTE43GATE_TOLL)
    writetext(RocketText_ThankYou)
    sjump(RocketScript_ShakeDownNorth)
    SCRIPT_END
}
bool RocketScript_YoureBrokeNorth(script_s* s) {
    SCRIPT_BEGIN
    takemoney(YOUR_MONEY, ROUTE43GATE_TOLL)
    writetext(RocketText_AllYouGot)
    sjump(RocketScript_ShakeDownNorth)
    SCRIPT_END
}
bool RocketScript_ShakeDownNorth(script_s* s) {
    SCRIPT_BEGIN
    promptbutton
    closetext
    applymovement(ROUTE43GATE_ROCKET2, Rocket2Script_LetsYouPassNorth)
    applymovement(ROUTE43GATE_ROCKET1, Rocket1Script_LetsYouPassNorth)
    setscene(SCENE_FINISHED)
    special(RestartMapMusic)
    s_end
    SCRIPT_END
}
bool RocketScript_MakingABundle(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(RocketText_MakingABundle)
    SCRIPT_END
}
bool OfficerScript_GuardWithSludgeBomb(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_TM36_SLUDGE_BOMB)
    iftrue(GotSludgeBomb)
    writetext(OfficerText_FoundTM)
    promptbutton
    verbosegiveitem(TM_SLUDGE_BOMB, 1)
    iffalse(NoRoomForSludgeBomb)
    setevent(EVENT_GOT_TM36_SLUDGE_BOMB)
    closetext
    s_end
GotSludgeBomb:
    writetext(OfficerText_AvoidGrass)
    waitbutton
NoRoomForSludgeBomb:
    closetext
    s_end
    SCRIPT_END
}
const uint8_t PlayerStepsIn[] = {
    step(DOWN),
    movement_step_end,
};
const uint8_t Rocket1Script_BlocksYouSouth[] = {
    big_step(UP),
    big_step(UP),
    big_step(RIGHT),
    big_step(RIGHT),
    turn_head(UP),
    movement_step_end,
};
const uint8_t Rocket1Script_LetsYouPassSouth[] = {
    big_step(LEFT),
    big_step(LEFT),
    big_step(DOWN),
    big_step(DOWN),
    movement_step_end,
};
const uint8_t Rocket1Script_BlocksYouNorth[] = {
    big_step(DOWN),
    big_step(DOWN),
    big_step(RIGHT),
    big_step(RIGHT),
    turn_head(DOWN),
    movement_step_end,
};
const uint8_t Rocket1Script_LetsYouPassNorth[] = {
    big_step(LEFT),
    big_step(LEFT),
    big_step(UP),
    big_step(UP),
    turn_head(DOWN),
    movement_step_end,
};
const uint8_t Rocket2Script_BlocksYouSouth[] = {
    big_step(UP),
    big_step(UP),
    big_step(LEFT),
    big_step(LEFT),
    turn_head(UP),
    movement_step_end,
};
const uint8_t Rocket2Script_LetsYouPassSouth[] = {
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(DOWN),
    big_step(DOWN),
    turn_head(UP),
    movement_step_end,
};
const uint8_t Rocket2Script_BlocksYouNorth[] = {
    big_step(DOWN),
    big_step(DOWN),
    big_step(LEFT),
    big_step(LEFT),
    turn_head(DOWN),
    movement_step_end,
};
const uint8_t Rocket2Script_LetsYouPassNorth[] = {
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(UP),
    big_step(UP),
    movement_step_end,
};
const txt_cmd_s RocketText_TollFee[] = {
    text_start("Hold it there,"
        t_line "kiddo!"
        t_para "The toll is ¥{d:ROUTE43GATE_TOLL}"
        t_line "to go through."
        t_done )
};
const txt_cmd_s RocketText_ThankYou[] = {
    text_start("Thank you very"
        t_line "much!"
        t_done )
};
const txt_cmd_s RocketText_AllYouGot[] = {
    text_start("Then pay what you"
        t_line "have, please."
        t_done )
};
const txt_cmd_s RocketText_MakingABundle[] = {
    text_start("He-he-he. We're"
        t_line "making a bundle."
        t_para "Everyone wants to"
        t_line "see what's going"
        t_para "on up at LAKE OF"
        t_line "RAGE."
        t_done )
};
const txt_cmd_s OfficerText_FoundTM[] = {
    text_start("I got chased from"
        t_line "my post by these"
        t_cont "thugs in black."
        t_para "They left this"
        t_line "behind."
        t_para "It makes me uncom-"
        t_line "fortable. Could"
        t_cont "you take it away?"
        t_done )
};
const txt_cmd_s Text_ReceivedTM30[] = {
    text_start("<PLAYER> received"
        t_line "TM30."
        t_done )
};
const txt_cmd_s OfficerText_AvoidGrass[] = {
    text_start("Use this gate to"
        t_line "avoid walking in"
        t_cont "the grass."
        t_done )
    //db(0, 0) // filler
};
