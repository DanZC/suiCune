#include "../constants.h"
#include "../util/scripting.h"
#include "MountMoonSquare.h"
//// EVENTS
enum {
    MOUNTMOONSQUARE_FAIRY1 = 2,
    MOUNTMOONSQUARE_FAIRY2,
    MOUNTMOONSQUARE_ROCK,
};

const Script_fn_t MountMoonSquare_SceneScripts[] = {
    MountMoonSquare_MapScripts_DummyScene , //  SCENE_DEFAULT,
};

const struct MapCallback MountMoonSquare_MapCallbacks[] = {
    map_callback(MAPCALLBACK_NEWMAP, MountMoonSquare_MapScripts_DisappearMoonStone),
    map_callback(MAPCALLBACK_OBJECTS, MountMoonSquare_MapScripts_DisappearRock),
};

const struct MapScripts MountMoonSquare_MapScripts = {
    .scene_script_count = lengthof(MountMoonSquare_SceneScripts),
    .scene_scripts = MountMoonSquare_SceneScripts,

    .callback_count = lengthof(MountMoonSquare_MapCallbacks),
    .callbacks = MountMoonSquare_MapCallbacks,
};

static const struct CoordEvent MountMoonSquare_CoordEvents[] = {
    coord_event(7, 11, SCENE_DEFAULT, &ClefairyDance),
};

static const struct BGEvent MountMoonSquare_BGEvents[] = {
    bg_event(7, 7, BGEVENT_ITEM, &MountMoonSquareHiddenMoonStone),
    bg_event(17, 7, BGEVENT_READ, &DontLitterSign),
};

static const struct WarpEventData MountMoonSquare_WarpEvents[] = {
    warp_event(20, 5, MOUNT_MOON, 5),
    warp_event(22, 11, MOUNT_MOON, 6),
    warp_event(13, 7, MOUNT_MOON_GIFT_SHOP, 1),
};

static const struct ObjEvent MountMoonSquare_ObjectEvents[] = {
    object_event(6, 6, SPRITE_FAIRY, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, EVENT_MT_MOON_SQUARE_CLEFAIRY),
    object_event(7, 6, SPRITE_FAIRY, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, EVENT_MT_MOON_SQUARE_CLEFAIRY),
    object_event(7, 7, SPRITE_ROCK, SPRITEMOVEDATA_SMASHABLE_ROCK, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &MtMoonSquareRock, EVENT_MT_MOON_SQUARE_ROCK),
};

const struct MapEvents MountMoonSquare_MapEvents = {
    .warp_event_count = lengthof(MountMoonSquare_WarpEvents),
    .warp_events = MountMoonSquare_WarpEvents,

    .coord_event_count = lengthof(MountMoonSquare_CoordEvents),
    .coord_events = MountMoonSquare_CoordEvents,

    .bg_event_count = lengthof(MountMoonSquare_BGEvents),
    .bg_events = MountMoonSquare_BGEvents,

    .obj_event_count = lengthof(MountMoonSquare_ObjectEvents),
    .obj_events = MountMoonSquare_ObjectEvents,
};

//// CODE

bool MountMoonSquare_MapScripts_DummyScene(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool MountMoonSquare_MapScripts_DisappearMoonStone(script_s* s) {
    SCRIPT_BEGIN
    setevent(EVENT_MOUNT_MOON_SQUARE_HIDDEN_MOON_STONE)
    s_endcallback
    SCRIPT_END
}
bool MountMoonSquare_MapScripts_DisappearRock(script_s* s) {
    SCRIPT_BEGIN
    disappear(MOUNTMOONSQUARE_ROCK)
    s_endcallback
    SCRIPT_END
}
bool ClefairyDance(script_s* s) {
    SCRIPT_BEGIN
    checkflag(ENGINE_MT_MOON_SQUARE_CLEFAIRY)
    iftrue(NoDancing)
    readvar(VAR_WEEKDAY)
    ifnotequal(MONDAY, NoDancing)
    checktime(NITE)
    iffalse(NoDancing)
    appear(MOUNTMOONSQUARE_FAIRY1)
    appear(MOUNTMOONSQUARE_FAIRY2)
    applymovement(PLAYER, PlayerWalksUpToDancingClefairies)
    pause(15)
    appear(MOUNTMOONSQUARE_ROCK)
    turnobject(MOUNTMOONSQUARE_FAIRY1, RIGHT)
    playcry(CLEFAIRY)
    waitsfx
    pause(30)
    follow(MOUNTMOONSQUARE_FAIRY1, MOUNTMOONSQUARE_FAIRY2)
    playcry(CLEFAIRY)
    applymovement(MOUNTMOONSQUARE_FAIRY1, ClefairyDanceStep1)
    playcry(CLEFAIRY)
    applymovement(MOUNTMOONSQUARE_FAIRY1, ClefairyDanceStep2)
    playcry(CLEFAIRY)
    applymovement(MOUNTMOONSQUARE_FAIRY1, ClefairyDanceStep3)
    playcry(CLEFAIRY)
    applymovement(MOUNTMOONSQUARE_FAIRY1, ClefairyDanceStep4)
    playcry(CLEFAIRY)
    applymovement(MOUNTMOONSQUARE_FAIRY1, ClefairyDanceStep5)
    stopfollow
    applymovement(MOUNTMOONSQUARE_FAIRY2, ClefairyDanceStep6)
    follow(MOUNTMOONSQUARE_FAIRY1, MOUNTMOONSQUARE_FAIRY2)
    applymovement(MOUNTMOONSQUARE_FAIRY1, ClefairyDanceStep7)
    stopfollow
    turnobject(MOUNTMOONSQUARE_FAIRY1, DOWN)
    pause(10)
    showemote(EMOTE_SHOCK, MOUNTMOONSQUARE_FAIRY1, 15)
    turnobject(MOUNTMOONSQUARE_FAIRY1, DOWN)
    playcry(CLEFAIRY)
    pause(15)
    follow(MOUNTMOONSQUARE_FAIRY1, MOUNTMOONSQUARE_FAIRY2)
    applymovement(MOUNTMOONSQUARE_FAIRY1, ClefairyFleeMovement)
    disappear(MOUNTMOONSQUARE_FAIRY1)
    disappear(MOUNTMOONSQUARE_FAIRY2)
    stopfollow
    clearevent(EVENT_MOUNT_MOON_SQUARE_HIDDEN_MOON_STONE)
    setflag(ENGINE_MT_MOON_SQUARE_CLEFAIRY)
    s_end
NoDancing:
    s_end
    SCRIPT_END
}
const struct HiddenItem MountMoonSquareHiddenMoonStone = {MOON_STONE, EVENT_MOUNT_MOON_SQUARE_HIDDEN_MOON_STONE};
bool DontLitterSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(DontLitterSignText)
    SCRIPT_END
}
bool MtMoonSquareRock(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(SmashRockScript)
    SCRIPT_END
}
const uint8_t PlayerWalksUpToDancingClefairies[] = {
    step(UP),
    movement_step_end,
};
const uint8_t ClefairyDanceStep1[] = {
    slow_step(DOWN),
    slow_jump_step(DOWN),
    movement_step_end,
};
const uint8_t ClefairyDanceStep2[] = {
    slow_jump_step(RIGHT),
    movement_step_end,
};
const uint8_t ClefairyDanceStep3[] = {
    slow_step(UP),
    slow_jump_step(UP),
    movement_step_end,
};
const uint8_t ClefairyDanceStep4[] = {
    slow_jump_step(LEFT),
    movement_step_end,
};
const uint8_t ClefairyDanceStep5[] = {
    slow_step(DOWN),
    slow_jump_step(DOWN),
    movement_step_end,
};
const uint8_t ClefairyDanceStep6[] = {
    slow_step(DOWN),
    movement_step_end,
};
const uint8_t ClefairyDanceStep7[] = {
    slow_step(RIGHT),
    movement_step_end,
};
const uint8_t ClefairyFleeMovement[] = {
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    jump_step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    movement_step_end,
};
const txt_cmd_s DontLitterSignText[] = {
    text_start("MT.MOON SQUARE"
        t_line "DON'T LITTER"
        t_done )
    //db(0, 0) // filler
};
