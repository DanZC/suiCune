#include "../constants.h"
#include "../util/scripting.h"
#include "OlivineCity.h"
//// EVENTS
enum {
    OLIVINECITY_SAILOR1 = 2,
    OLIVINECITY_STANDING_YOUNGSTER,
    OLIVINECITY_SAILOR2,
    OLIVINECITY_OLIVINE_RIVAL,
};

const Script_fn_t OlivineCity_SceneScripts[] = {
    OlivineCity_MapScripts_DummyScene0 , //  SCENE_DEFAULT,
    OlivineCity_MapScripts_DummyScene1 , //  SCENE_FINISHED,
};

const struct MapCallback OlivineCity_MapCallbacks[] = {
    map_callback(MAPCALLBACK_NEWMAP, OlivineCity_MapScripts_FlyPoint),
};

const struct MapScripts OlivineCity_MapScripts = {
    .scene_script_count = lengthof(OlivineCity_SceneScripts),
    .scene_scripts = OlivineCity_SceneScripts,

    .callback_count = lengthof(OlivineCity_MapCallbacks),
    .callbacks = OlivineCity_MapCallbacks,
};

static const struct CoordEvent OlivineCity_CoordEvents[] = {
    coord_event(13, 12, SCENE_DEFAULT, &OlivineCityRivalSceneTop),
    coord_event(13, 13, SCENE_DEFAULT, &OlivineCityRivalSceneBottom),
};

static const struct BGEvent OlivineCity_BGEvents[] = {
    bg_event(17, 11, BGEVENT_READ, &OlivineCitySign),
    bg_event(20, 24, BGEVENT_READ, &OlivineCityPortSign),
    bg_event(7, 11, BGEVENT_READ, &OlivineGymSign),
    bg_event(30, 28, BGEVENT_READ, &OlivineLighthouseSign),
    bg_event(3, 23, BGEVENT_READ, &OlivineCityBattleTowerSign),
    bg_event(14, 21, BGEVENT_READ, &OlivineCityPokecenterSign),
    bg_event(20, 17, BGEVENT_READ, &OlivineCityMartSign),
};

static const struct WarpEventData OlivineCity_WarpEvents[] = {
    warp_event(13, 21, OLIVINE_POKECENTER_1F, 1),
    warp_event(10, 11, OLIVINE_GYM, 1),
    warp_event(25, 11, OLIVINE_TIMS_HOUSE, 1),
    warp_event(0, 0, OLIVINE_HOUSE_BETA, 1), // inaccessible
    warp_event(29, 11, OLIVINE_PUNISHMENT_SPEECH_HOUSE, 1),
    warp_event(13, 15, OLIVINE_GOOD_ROD_HOUSE, 1),
    warp_event(7, 21, OLIVINE_CAFE, 1),
    warp_event(19, 17, OLIVINE_MART, 2),
    warp_event(29, 27, OLIVINE_LIGHTHOUSE_1F, 1),
    warp_event(19, 27, OLIVINE_PORT_PASSAGE, 1),
    warp_event(20, 27, OLIVINE_PORT_PASSAGE, 2),
};

static const struct ObjEvent OlivineCity_ObjectEvents[] = {
    object_event(26, 27, SPRITE_SAILOR, SPRITEMOVEDATA_WALK_UP_DOWN, 0, 1, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &OlivineCitySailor1Script, -1),
    object_event(20, 13, SPRITE_STANDING_YOUNGSTER, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &OlivineCityStandingYoungsterScript, -1),
    object_event(17, 21, SPRITE_SAILOR, SPRITEMOVEDATA_WANDER, 1, 1, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &OlivineCitySailor2Script, -1),
    object_event(10, 11, SPRITE_OLIVINE_RIVAL, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, EVENT_RIVAL_OLIVINE_CITY),
};

const struct MapEvents OlivineCity_MapEvents = {
    .warp_event_count = lengthof(OlivineCity_WarpEvents),
    .warp_events = OlivineCity_WarpEvents,

    .coord_event_count = lengthof(OlivineCity_CoordEvents),
    .coord_events = OlivineCity_CoordEvents,

    .bg_event_count = lengthof(OlivineCity_BGEvents),
    .bg_events = OlivineCity_BGEvents,

    .obj_event_count = lengthof(OlivineCity_ObjectEvents),
    .obj_events = OlivineCity_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "OlivineCity.h"

bool OlivineCity_MapScripts_DummyScene0(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool OlivineCity_MapScripts_DummyScene1(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool OlivineCity_MapScripts_FlyPoint(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_FLYPOINT_OLIVINE)
    s_endcallback
    SCRIPT_END
}
bool OlivineCityRivalSceneTop(script_s* s) {
    SCRIPT_BEGIN
    turnobject(PLAYER, LEFT)
    showemote(EMOTE_SHOCK, PLAYER, 15)
    special(FadeOutMusic)
    pause(15)
    playsound(SFX_ENTER_DOOR)
    appear(OLIVINECITY_OLIVINE_RIVAL)
    waitsfx
    applymovement(OLIVINECITY_OLIVINE_RIVAL, OlivineCityRivalApproachesTopMovement)
    playmusic(MUSIC_RIVAL_ENCOUNTER)
    opentext
    writetext(OlivineCityRivalText)
    waitbutton
    closetext
    applymovement(PLAYER, OlivineCityPlayerStepsAsideTopMovement)
    turnobject(PLAYER, RIGHT)
    applymovement(OLIVINECITY_OLIVINE_RIVAL, OlivineCityRivalLeavesTopMovement)
    setscene(SCENE_FINISHED)
    disappear(OLIVINECITY_OLIVINE_RIVAL)
    special(RestartMapMusic)
    variablesprite(SPRITE_OLIVINE_RIVAL, SPRITE_SWIMMER_GUY)
    special(LoadUsedSpritesGFX)
    s_end
    SCRIPT_END
}
bool OlivineCityRivalSceneBottom(script_s* s) {
    SCRIPT_BEGIN
    turnobject(PLAYER, LEFT)
    showemote(EMOTE_SHOCK, PLAYER, 15)
    special(FadeOutMusic)
    pause(15)
    playsound(SFX_ENTER_DOOR)
    appear(OLIVINECITY_OLIVINE_RIVAL)
    waitsfx
    applymovement(OLIVINECITY_OLIVINE_RIVAL, OlivineCityRivalApproachesBottomMovement)
    playmusic(MUSIC_RIVAL_ENCOUNTER)
    opentext
    writetext(OlivineCityRivalText)
    waitbutton
    closetext
    applymovement(PLAYER, OlivineCityPlayerStepsAsideBottomMovement)
    turnobject(PLAYER, RIGHT)
    applymovement(OLIVINECITY_OLIVINE_RIVAL, OlivineCityRivalLeavesBottomMovement)
    disappear(OLIVINECITY_OLIVINE_RIVAL)
    setscene(SCENE_FINISHED)
    special(RestartMapMusic)
    variablesprite(SPRITE_OLIVINE_RIVAL, SPRITE_SWIMMER_GUY)
    special(LoadUsedSpritesGFX)
    s_end
    SCRIPT_END
}
bool OlivineCitySailor1Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(OlivineCitySailor1Text)
    SCRIPT_END
}
bool OlivineCityStandingYoungsterScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    srandom(2)
    ifequal(0, FiftyFifty)
    writetext(OlivineCityStandingYoungsterPokegearText)
    waitbutton
    closetext
    s_end
FiftyFifty:
    writetext(OlivineCityStandingYoungsterPokedexText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool OlivineCitySailor2Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(OlivineCitySailor2Text)
    SCRIPT_END
}
bool OlivineCitySign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(OlivineCitySignText)
    SCRIPT_END
}
bool OlivineCityPortSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(OlivineCityPortSignText)
    SCRIPT_END
}
bool OlivineGymSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(OlivineGymSignText)
    SCRIPT_END
}
bool OlivineLighthouseSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(OlivineLighthouseSignText)
    SCRIPT_END
}
bool OlivineCityBattleTowerSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(OlivineCityBattleTowerSignText)
    SCRIPT_END
}
bool OlivineCityPokecenterSign(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PokecenterSignScript)
    SCRIPT_END
}
bool OlivineCityMartSign(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(MartSignScript)
    SCRIPT_END
}
const uint8_t OlivineCityRivalApproachesTopMovement[] = {
    step(DOWN),
    step(RIGHT),
    step(RIGHT),
    movement_step_end,
};
const uint8_t OlivineCityRivalApproachesBottomMovement[] = {
    step(DOWN),
    step(DOWN),
    step(RIGHT),
    step(RIGHT),
    movement_step_end,
};
const uint8_t OlivineCityRivalLeavesTopMovement[] = {
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    step(UP),
    step(UP),
    step(UP),
    step(UP),
    step(UP),
    step(UP),
    movement_step_end,
};
const uint8_t OlivineCityRivalLeavesBottomMovement[] = {
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    step(UP),
    step(UP),
    step(UP),
    step(UP),
    step(UP),
    movement_step_end,
};
const uint8_t OlivineCityPlayerStepsAsideTopMovement[] = {
    step(DOWN),
    turn_head(UP),
    movement_step_end,
};
const uint8_t OlivineCityPlayerStepsAsideBottomMovement[] = {
    step(UP),
    turn_head(DOWN),
    movement_step_end,
};
const txt_cmd_s OlivineCityRivalText[] = {
    text_start("…"
        t_para "You again?"
        t_para "There's no need to"
        t_line "panic. I don't"
        t_para "bother with wimps"
        t_line "like you."
        t_para "Speaking of weak-"
        t_line "lings, the city's"
        t_para "GYM LEADER isn't"
        t_line "here."
        t_para "Supposedly taking"
        t_line "care of a sick"
        t_para "#MON at the"
        t_line "LIGHTHOUSE."
        t_para "Humph! Boo-hoo!"
        t_line "Just let sick"
        t_cont "#MON go!"
        t_para "A #MON that"
        t_line "can't battle is"
        t_cont "worthless!"
        t_para "Why don't you go"
        t_line "train at the"
        t_cont "LIGHTHOUSE?"
        t_para "Who knows. It may"
        t_line "make you a bit"
        t_cont "less weak!"
        t_done )
};
const txt_cmd_s OlivineCitySailor1Text[] = {
    text_start("Dark roads are"
        t_line "dangerous at"
        t_cont "night."
        t_para "But in the pitch-"
        t_line "black of night,"
        t_para "the sea is even"
        t_line "more treacherous!"
        t_para "Without the beacon"
        t_line "of the LIGHTHOUSE"
        t_para "to guide it, no"
        t_line "ship can sail."
        t_done )
};
const txt_cmd_s OlivineCityStandingYoungsterPokegearText[] = {
    text_start("That thing you"
        t_line "have--it's a #-"
        t_cont "GEAR, right? Wow,"
        t_cont "that's cool."
        t_done )
};
const txt_cmd_s OlivineCityStandingYoungsterPokedexText[] = {
    text_start("Wow, you have a"
        t_line "#DEX!"
        t_para "That is just so"
        t_line "awesome."
        t_done )
};
const txt_cmd_s OlivineCitySailor2Text[] = {
    text_start("The sea is sweet!"
        t_para "Sunsets on the sea"
        t_line "are marvelous!"
        t_para "Sing with me! "
        t_line "Yo-ho! Blow the"
        t_cont "man down!…"
        t_done )
};
const txt_cmd_s OlivineCitySignText[] = {
    text_start("OLIVINE CITY"
        t_para "The Port Closest"
        t_line "to Foreign Lands"
        t_done )
};
const txt_cmd_s OlivineCityPortSignText[] = {
    text_start("OLIVINE PORT"
        t_line "FAST SHIP PIER"
        t_done )
};
const txt_cmd_s OlivineGymSignText[] = {
    text_start("OLIVINE CITY"
        t_line "#MON GYM"
        t_cont "LEADER: JASMINE"
        t_para "The Steel-Clad"
        t_line "Defense Girl"
        t_done )
};
const txt_cmd_s OlivineLighthouseSignText[] = {
    text_start("OLIVINE LIGHTHOUSE"
        t_line "Also known as the"
        t_cont "GLITTER LIGHTHOUSE"
        t_done )
};
const txt_cmd_s OlivineCityBattleTowerSignText[] = {
    text_start("BATTLE TOWER AHEAD"
        t_line "Opening Now!"
        t_done )
};
const txt_cmd_s OlivineCityBattleTowerSignText_NotYetOpen[] = {
// originally shown when the Battle Tower was closed
    text_start("BATTLE TOWER AHEAD"
        t_done )
    //db(0, 0) // filler
};
