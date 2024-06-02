#include "../constants.h"
#include "../util/scripting.h"
#include "BurnedTowerB1F.h"
//// EVENTS
enum {
    BURNEDTOWERB1F_BOULDER = 2,
    BURNEDTOWERB1F_RAIKOU1,
    BURNEDTOWERB1F_ENTEI1,
    BURNEDTOWERB1F_SUICUNE1,
    BURNEDTOWERB1F_RAIKOU2,
    BURNEDTOWERB1F_ENTEI2,
    BURNEDTOWERB1F_SUICUNE2,
    BURNEDTOWERB1F_POKE_BALL,
    BURNEDTOWERB1F_EUSINE,
};

const Script_fn_t BurnedTowerB1F_SceneScripts[] = {
    BurnedTowerB1F_MapScripts_DummyScene0 , //  SCENE_DEFAULT,
    BurnedTowerB1F_MapScripts_DummyScene1 , //  SCENE_FINISHED,
};

const struct MapCallback BurnedTowerB1F_MapCallbacks[] = {
    map_callback(MAPCALLBACK_TILES, BurnedTowerB1F_MapScripts_LadderCallback),
};

const struct MapScripts BurnedTowerB1F_MapScripts = {
    .scene_script_count = lengthof(BurnedTowerB1F_SceneScripts),
    .scene_scripts = BurnedTowerB1F_SceneScripts,

    .callback_count = lengthof(BurnedTowerB1F_MapCallbacks),
    .callbacks = BurnedTowerB1F_MapCallbacks,
};

static const struct CoordEvent BurnedTowerB1F_CoordEvents[] = {
    coord_event(10, 6, SCENE_DEFAULT, &ReleaseTheBeasts),
};

static const struct BGEvent BurnedTowerB1F_BGEvents[] = {
    0,
};

static const struct WarpEventData BurnedTowerB1F_WarpEvents[] = {
    warp_event(10, 9, BURNED_TOWER_1F, 3),
    warp_event(17, 7, BURNED_TOWER_1F, 7),
    warp_event(10, 8, BURNED_TOWER_1F, 9),
    warp_event(3, 13, BURNED_TOWER_1F, 10),
    warp_event(17, 14, BURNED_TOWER_1F, 12),
    warp_event(7, 15, BURNED_TOWER_1F, 14),
};

static const struct ObjEvent BurnedTowerB1F_ObjectEvents[] = {
    object_event(17, 8, SPRITE_BOULDER, SPRITEMOVEDATA_STRENGTH_BOULDER, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &BurnedTowerB1FBoulder, -1),
    object_event(7, 3, SPRITE_RAIKOU, SPRITEMOVEDATA_POKEMON, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, EVENT_BURNED_TOWER_B1F_BEASTS_1),
    object_event(12, 3, SPRITE_ENTEI, SPRITEMOVEDATA_POKEMON, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, EVENT_BURNED_TOWER_B1F_BEASTS_1),
    object_event(10, 4, SPRITE_SUICUNE, SPRITEMOVEDATA_POKEMON, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, EVENT_BURNED_TOWER_B1F_BEASTS_1),
    object_event(7, 3, SPRITE_RAIKOU, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_SILVER, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, EVENT_BURNED_TOWER_B1F_BEASTS_2),
    object_event(12, 3, SPRITE_ENTEI, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_SILVER, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, EVENT_BURNED_TOWER_B1F_BEASTS_2),
    object_event(10, 4, SPRITE_SUICUNE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_SILVER, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, EVENT_BURNED_TOWER_B1F_BEASTS_2),
    object_event(16, 4, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &BurnedTowerB1FTMEndure, EVENT_BURNED_TOWER_B1F_TM_ENDURE),
    object_event(10, 12, SPRITE_SUPER_NERD, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &BurnedTowerB1FEusine, EVENT_EUSINE_IN_BURNED_TOWER),
};

const struct MapEvents BurnedTowerB1F_MapEvents = {
    .warp_event_count = lengthof(BurnedTowerB1F_WarpEvents),
    .warp_events = BurnedTowerB1F_WarpEvents,

    .coord_event_count = lengthof(BurnedTowerB1F_CoordEvents),
    .coord_events = BurnedTowerB1F_CoordEvents,

    .bg_event_count = 0, // lengthof(BurnedTowerB1F_BGEvents),
    .bg_events = BurnedTowerB1F_BGEvents,

    .obj_event_count = lengthof(BurnedTowerB1F_ObjectEvents),
    .obj_events = BurnedTowerB1F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "BurnedTowerB1F.h"

bool BurnedTowerB1F_MapScripts_DummyScene0(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool BurnedTowerB1F_MapScripts_DummyScene1(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool BurnedTowerB1F_MapScripts_LadderCallback(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_RELEASED_THE_BEASTS)
    iftrue(HideLadder)
    changeblock(6, 14, 0x02) // floor
HideLadder:
    s_endcallback
    SCRIPT_END
}
bool ReleaseTheBeasts(script_s* s) {
    SCRIPT_BEGIN
    playmusic(MUSIC_NONE)
    pause(30)
    appear(BURNEDTOWERB1F_RAIKOU1)
    turnobject(PLAYER, UP)
    pause(5)
    disappear(BURNEDTOWERB1F_RAIKOU2)
    pause(15)
    playcry(RAIKOU)
    appear(BURNEDTOWERB1F_ENTEI1)
    turnobject(PLAYER, UP)
    pause(5)
    disappear(BURNEDTOWERB1F_ENTEI2)
    pause(15)
    playcry(ENTEI)
    appear(BURNEDTOWERB1F_SUICUNE1)
    turnobject(PLAYER, UP)
    pause(5)
    disappear(BURNEDTOWERB1F_SUICUNE2)
    pause(15)
    playcry(SUICUNE)
    pause(15)
    playsound(SFX_WARP_FROM)
    turnobject(PLAYER, LEFT)
    applymovement(BURNEDTOWERB1F_RAIKOU1, BurnedTowerRaikouMovement)
    disappear(BURNEDTOWERB1F_RAIKOU1)
    waitsfx
    playsound(SFX_WARP_FROM)
    turnobject(PLAYER, RIGHT)
    applymovement(BURNEDTOWERB1F_ENTEI1, BurnedTowerEnteiMovement)
    disappear(BURNEDTOWERB1F_ENTEI1)
    waitsfx
    pause(15)
    playsound(SFX_WARP_FROM)
    turnobject(PLAYER, UP)
    applymovement(BURNEDTOWERB1F_SUICUNE1, BurnedTowerSuicuneMovement1)
    playsound(SFX_WARP_FROM)
    turnobject(PLAYER, DOWN)
    applymovement(BURNEDTOWERB1F_SUICUNE1, BurnedTowerSuicuneMovement2)
    turnobject(PLAYER, UP)
    pause(20)
    playcry(SUICUNE)
    pause(30)
    playsound(SFX_WARP_FROM)
    applymovement(BURNEDTOWERB1F_SUICUNE1, BurnedTowerSuicuneMovement3)
    turnobject(PLAYER, DOWN)
    disappear(BURNEDTOWERB1F_SUICUNE1)
    waitsfx
    special(RestartMapMusic)
    setscene(SCENE_FINISHED)
    setevent(EVENT_RELEASED_THE_BEASTS)
    special(InitRoamMons)
    setmapscene(ECRUTEAK_GYM, SCENE_FINISHED)
    setmapscene(CIANWOOD_CITY, SCENE_CIANWOODCITY_SUICUNE_AND_EUSINE)
    clearevent(EVENT_SAW_SUICUNE_AT_CIANWOOD_CITY)
    setevent(EVENT_ECRUTEAK_GYM_GRAMPS)
    clearevent(EVENT_ECRUTEAK_CITY_GRAMPS)
    setevent(EVENT_BURNED_TOWER_MORTY)
    setevent(EVENT_BURNED_TOWER_1F_EUSINE)
    appear(BURNEDTOWERB1F_EUSINE)
    refreshscreen
    changeblock(6, 14, 0x1b) // ladder
    reloadmappart
    closetext
    setscene(SCENE_FINISHED)
    s_end
    SCRIPT_END
}
bool BurnedTowerB1FEusine(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(BurnedTowerB1FEusineText)
    waitbutton
    closetext
    readvar(VAR_FACING)
    ifequal(UP, Movement2)
    applymovement(BURNEDTOWERB1F_EUSINE, BurnedTowerB1FEusineMovement1)
    goto Finish;
Movement2:
    applymovement(BURNEDTOWERB1F_EUSINE, BurnedTowerB1FEusineMovement2)
Finish:
    disappear(BURNEDTOWERB1F_EUSINE)
    playsound(SFX_EXIT_BUILDING)
    waitsfx
    s_end
    SCRIPT_END
}
const struct ItemBall BurnedTowerB1FTMEndure = {TM_ENDURE, 1};
bool BurnedTowerB1FBoulder(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(StrengthBoulderScript)
    SCRIPT_END
}
const uint8_t BurnedTowerRaikouMovement[] = {
    movement_set_sliding,
    fast_jump_step(DOWN),
    fast_jump_step(LEFT),
    movement_remove_sliding,
    movement_step_end,
};
const uint8_t BurnedTowerEnteiMovement[] = {
    movement_set_sliding,
    fast_jump_step(RIGHT),
    fast_jump_step(DOWN),
    fast_jump_step(RIGHT),
    movement_remove_sliding,
    movement_step_end,
};
const uint8_t BurnedTowerSuicuneMovement1[] = {
    movement_set_sliding,
    fast_jump_step(RIGHT),
    fast_jump_step(DOWN),
    fast_jump_step(DOWN),
    fast_jump_step(LEFT),
    movement_remove_sliding,
    movement_step_end,
};
const uint8_t BurnedTowerSuicuneMovement2[] = {
    movement_set_sliding,
    fast_jump_step(LEFT),
    fast_jump_step(UP),
    big_step(UP),
    fast_jump_step(RIGHT),
    movement_remove_sliding,
    movement_step_end,
};
const uint8_t BurnedTowerUnusedMovement[] = {
    movement_set_sliding,
    big_step(DOWN),
    movement_remove_sliding,
    movement_step_end,
};
const uint8_t BurnedTowerSuicuneMovement3[] = {
    movement_set_sliding,
    big_step(UP),
    fast_jump_step(RIGHT),
    fast_jump_step(DOWN),
    fast_jump_step(DOWN),
    fast_jump_step(DOWN),
    fast_jump_step(DOWN),
    movement_remove_sliding,
    movement_step_end,
};
const uint8_t BurnedTowerB1FEusineMovement2[] = {
    step(LEFT),
    step(LEFT),
    step(DOWN),
    step(DOWN),
    step(LEFT),
    step(DOWN),
    movement_step_end,
};
const uint8_t BurnedTowerB1FEusineMovement1[] = {
    step(DOWN),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(DOWN),
    step(DOWN),
    movement_step_end,
};
const txt_cmd_s BurnedTowerB1FEusineText[] = {
    text_start("EUSINE: I dug a"
        t_line "hole here, too…"
        t_para "I was shocked!"
        t_para "SUICUNE raced by"
        t_line "like a blur, right"
        t_para "in front of my"
        t_line "eyes!"
        t_para "For ten years I"
        t_line "chased SUICUNE,"
        t_para "and I finally got"
        t_line "to see it."
        t_para "I'm all choked up!"
        t_para "<PLAYER>, I owe"
        t_line "this all to you!"
        t_para "Thank you!"
        t_para "I heard that the"
        t_line "legendary #MON"
        t_para "of ECRUTEAK test"
        t_line "chosen humans by"
        t_para "allowing them to"
        t_line "get close."
        t_para "I'm going to track"
        t_line "SUICUNE."
        t_para "<PLAYER>, let's"
        t_line "meet again!"
        t_para "Farewell!"
        t_done )
    //db(0, 0) // filler
};
