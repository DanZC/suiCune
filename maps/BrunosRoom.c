#include "../constants.h"
#include "../util/scripting.h"
#include "BrunosRoom.h"
//// EVENTS
enum {
    BRUNOSROOM_BRUNO = 2,
};

const Script_fn_t BrunosRoom_SceneScripts[] = {
    BrunosRoom_MapScripts_LockDoor , //  SCENE_DEFAULT,
    BrunosRoom_MapScripts_DummyScene , //  SCENE_FINISHED,
};

const struct MapCallback BrunosRoom_MapCallbacks[] = {
    map_callback(MAPCALLBACK_TILES, BrunosRoom_MapScripts_BrunosRoomDoors),
};

const struct MapScripts BrunosRoom_MapScripts = {
    .scene_script_count = lengthof(BrunosRoom_SceneScripts),
    .scene_scripts = BrunosRoom_SceneScripts,

    .callback_count = lengthof(BrunosRoom_MapCallbacks),
    .callbacks = BrunosRoom_MapCallbacks,
};

static const struct CoordEvent BrunosRoom_CoordEvents[] = {
    0,
};

static const struct BGEvent BrunosRoom_BGEvents[] = {
    0,
};

static const struct WarpEventData BrunosRoom_WarpEvents[] = {
    warp_event(4, 17, KOGAS_ROOM, 3),
    warp_event(5, 17, KOGAS_ROOM, 4),
    warp_event(4, 2, KARENS_ROOM, 1),
    warp_event(5, 2, KARENS_ROOM, 2),
};

static const struct ObjEvent BrunosRoom_ObjectEvents[] = {
    object_event(5, 7, SPRITE_BRUNO, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, &BrunoScript_Battle, -1),
};

const struct MapEvents BrunosRoom_MapEvents = {
    .warp_event_count = lengthof(BrunosRoom_WarpEvents),
    .warp_events = BrunosRoom_WarpEvents,

    .coord_event_count = 0, // lengthof(BrunosRoom_CoordEvents),
    .coord_events = BrunosRoom_CoordEvents,

    .bg_event_count = 0, // lengthof(BrunosRoom_BGEvents),
    .bg_events = BrunosRoom_BGEvents,

    .obj_event_count = lengthof(BrunosRoom_ObjectEvents),
    .obj_events = BrunosRoom_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "BrunosRoom.h"

bool BrunosRoom_MapScripts_LockDoor(script_s* s) {
    SCRIPT_BEGIN
    sdefer(BrunosRoom_MapScripts_BrunosDoorLocksBehindYou);
    s_end
    SCRIPT_END
}
bool BrunosRoom_MapScripts_DummyScene(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool BrunosRoom_MapScripts_BrunosRoomDoors(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_BRUNOS_ROOM_ENTRANCE_CLOSED)
    iffalse(KeepEntranceOpen)
    changeblock(4, 14, 0x2a) // wall
KeepEntranceOpen:
    checkevent(EVENT_BRUNOS_ROOM_EXIT_OPEN)
    iffalse(KeepExitClosed)
    changeblock(4, 2, 0x16) // open door
KeepExitClosed:
    s_endcallback
    SCRIPT_END
}
bool BrunosRoom_MapScripts_BrunosDoorLocksBehindYou(script_s* s) {
    SCRIPT_BEGIN
    applymovement(PLAYER, BrunosRoom_EnterMovement)
    refreshscreen
    playsound(SFX_STRENGTH)
    earthquake(80)
    changeblock(4, 14, 0x2a) // wall
    reloadmappart
    closetext
    setscene(SCENE_FINISHED)
    setevent(EVENT_BRUNOS_ROOM_ENTRANCE_CLOSED)
    waitsfx
    s_end
    SCRIPT_END
}
bool BrunoScript_Battle(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_BEAT_ELITE_4_BRUNO)
    iftrue_jump(BrunoScript_AfterBattle)
    writetext(BrunoScript_BrunoBeforeText)
    waitbutton
    closetext
    winlosstext(BrunoScript_BrunoBeatenText, 0)
    loadtrainer(BRUNO, BRUNO1)
    startbattle
    reloadmapafterbattle
    setevent(EVENT_BEAT_ELITE_4_BRUNO)
    opentext
    writetext(BrunoScript_BrunoDefeatText)
    waitbutton
    closetext
    playsound(SFX_ENTER_DOOR)
    changeblock(4, 2, 0x16) // open door
    reloadmappart
    closetext
    setevent(EVENT_BRUNOS_ROOM_EXIT_OPEN)
    waitsfx
    s_end
    SCRIPT_END
}
bool BrunoScript_AfterBattle(script_s* s) {
    SCRIPT_BEGIN
    writetext(BrunoScript_BrunoDefeatText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const uint8_t BrunosRoom_EnterMovement[] = {
    step(UP),
    step(UP),
    step(UP),
    step(UP),
    movement_step_end,
};
const txt_cmd_s BrunoScript_BrunoBeforeText[] = {
    text_start("I am BRUNO of the"
        t_line "ELITE FOUR."
        t_para "I always train to"
        t_line "the extreme be-"
        t_cont "cause I believe in"
        t_cont "our potential."
        t_para "That is how we"
        t_line "became strong."
        t_para "Can you withstand"
        t_line "our power?"
        t_para "Hm? I see no fear"
        t_line "in you. You look"
        t_para "determined. Per-"
        t_line "fect for battle!"
        t_para "Ready, <PLAYER>?"
        t_line "You will bow down"
        t_para "to our overwhelm-"
        t_line "ing power!"
        t_para "Hoo hah!"
        t_done )
};
const txt_cmd_s BrunoScript_BrunoBeatenText[] = {
    text_start("Why? How could we"
        t_line "lose?"
        t_done )
};
const txt_cmd_s BrunoScript_BrunoDefeatText[] = {
    text_start("Having lost, I"
        t_line "have no right to"
        t_cont "say anything…"
        t_para "Go face your next"
        t_line "challenge!"
        t_done )
    //db(0, 0) // filler
};
