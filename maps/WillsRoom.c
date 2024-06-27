#include "../constants.h"
#include "../util/scripting.h"
#include "WillsRoom.h"
//// EVENTS
enum {
    WILLSROOM_WILL = 2,
};

const Script_fn_t WillsRoom_SceneScripts[] = {
    WillsRoom_MapScripts_LockDoor , //  SCENE_DEFAULT,
    WillsRoom_MapScripts_DummyScene , //  SCENE_FINISHED,
};

const struct MapCallback WillsRoom_MapCallbacks[] = {
    map_callback(MAPCALLBACK_TILES, WillsRoom_MapScripts_WillsRoomDoors),
};

const struct MapScripts WillsRoom_MapScripts = {
    .scene_script_count = lengthof(WillsRoom_SceneScripts),
    .scene_scripts = WillsRoom_SceneScripts,

    .callback_count = lengthof(WillsRoom_MapCallbacks),
    .callbacks = WillsRoom_MapCallbacks,
};

static const struct CoordEvent WillsRoom_CoordEvents[] = {
    0,
};

static const struct BGEvent WillsRoom_BGEvents[] = {
    0,
};

static const struct WarpEventData WillsRoom_WarpEvents[] = {
    warp_event(5, 17, INDIGO_PLATEAU_POKECENTER_1F, 4),
    warp_event(4, 2, KOGAS_ROOM, 1),
    warp_event(5, 2, KOGAS_ROOM, 2),
};

static const struct ObjEvent WillsRoom_ObjectEvents[] = {
    object_event(5, 7, SPRITE_WILL, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &WillScript_Battle, -1),
};

const struct MapEvents WillsRoom_MapEvents = {
    .warp_event_count = lengthof(WillsRoom_WarpEvents),
    .warp_events = WillsRoom_WarpEvents,

    .coord_event_count = 0, // lengthof(WillsRoom_CoordEvents),
    .coord_events = WillsRoom_CoordEvents,

    .bg_event_count = 0, // lengthof(WillsRoom_BGEvents),
    .bg_events = WillsRoom_BGEvents,

    .obj_event_count = lengthof(WillsRoom_ObjectEvents),
    .obj_events = WillsRoom_ObjectEvents,
};

//// CODE

bool WillsRoom_MapScripts_LockDoor(script_s* s) {
    SCRIPT_BEGIN
    sdefer(WillsRoom_MapScripts_WillsDoorLocksBehindYou);
    s_end
    SCRIPT_END
}
bool WillsRoom_MapScripts_DummyScene(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool WillsRoom_MapScripts_WillsRoomDoors(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_WILLS_ROOM_ENTRANCE_CLOSED)
    iffalse(KeepEntranceOpen)
    changeblock(4, 14, 0x2a) // wall
KeepEntranceOpen:
    checkevent(EVENT_WILLS_ROOM_EXIT_OPEN)
    iffalse(KeepExitClosed)
    changeblock(4, 2, 0x16) // open door
KeepExitClosed:
    s_endcallback
    SCRIPT_END
}
bool WillsRoom_MapScripts_WillsDoorLocksBehindYou(script_s* s) {
    SCRIPT_BEGIN
    applymovement(PLAYER, WillsRoom_EnterMovement)
    refreshscreen
    playsound(SFX_STRENGTH)
    earthquake(80)
    changeblock(4, 14, 0x2a) // wall
    reloadmappart
    closetext
    setscene(SCENE_FINISHED)
    setevent(EVENT_WILLS_ROOM_ENTRANCE_CLOSED)
    waitsfx
    s_end
    SCRIPT_END
}
bool WillScript_Battle(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_BEAT_ELITE_4_WILL)
    iftrue_jump(WillScript_AfterBattle)
    writetext(WillScript_WillBeforeText)
    waitbutton
    closetext
    winlosstext(WillScript_WillBeatenText, 0)
    loadtrainer(WILL, WILL1)
    startbattle
    reloadmapafterbattle
    setevent(EVENT_BEAT_ELITE_4_WILL)
    opentext
    writetext(WillScript_WillDefeatText)
    waitbutton
    closetext
    playsound(SFX_ENTER_DOOR)
    changeblock(4, 2, 0x16) // open door
    reloadmappart
    closetext
    setevent(EVENT_WILLS_ROOM_EXIT_OPEN)
    waitsfx
    s_end
    SCRIPT_END
}
bool WillScript_AfterBattle(script_s* s) {
    SCRIPT_BEGIN
    writetext(WillScript_WillDefeatText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const uint8_t WillsRoom_EnterMovement[] = {
    step(UP),
    step(UP),
    step(UP),
    step(UP),
    movement_step_end,
};
const txt_cmd_s WillScript_WillBeforeText[] = {
    text_start("Welcome to #MON"
        t_line "LEAGUE, <PLAYER>."
        t_para "Allow me to intro-"
        t_line "duce myself. I am"
        t_cont "WILL."
        t_para "I have trained all"
        t_line "around the world,"
        t_para "making my psychic"
        t_line "#MON powerful."
        t_para "And, at last, I've"
        t_line "been accepted into"
        t_cont "the ELITE FOUR."
        t_para "I can only keep"
        t_line "getting better!"
        t_para "Losing is not an"
        t_line "option!"
        t_done )
};
const txt_cmd_s WillScript_WillBeatenText[] = {
    text_start("I… I can't…"
        t_line "believe it…"
        t_done )
};
const txt_cmd_s WillScript_WillDefeatText[] = {
    text_start("Even though I was"
        t_line "defeated, I won't"
        t_cont "change my course."
        t_para "I will continue"
        t_line "battling until I"
        t_para "stand above all"
        t_line "trainers!"
        t_para "Now, <PLAYER>, move"
        t_line "on and experience"
        t_para "the true ferocity"
        t_line "of the ELITE FOUR."
        t_done )
    //db(0, 0) // filler
};
