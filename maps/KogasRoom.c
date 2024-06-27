#include "../constants.h"
#include "../util/scripting.h"
#include "KogasRoom.h"
//// EVENTS
enum {
    KOGASROOM_KOGA = 2,
};

const Script_fn_t KogasRoom_SceneScripts[] = {
    KogasRoom_MapScripts_LockDoor , //  SCENE_DEFAULT,
    KogasRoom_MapScripts_DummyScene , //  SCENE_FINISHED,
};

const struct MapCallback KogasRoom_MapCallbacks[] = {
    map_callback(MAPCALLBACK_TILES, KogasRoom_MapScripts_KogasRoomDoors),
};

const struct MapScripts KogasRoom_MapScripts = {
    .scene_script_count = lengthof(KogasRoom_SceneScripts),
    .scene_scripts = KogasRoom_SceneScripts,

    .callback_count = lengthof(KogasRoom_MapCallbacks),
    .callbacks = KogasRoom_MapCallbacks,
};

static const struct CoordEvent KogasRoom_CoordEvents[] = {
    0,
};

static const struct BGEvent KogasRoom_BGEvents[] = {
    0,
};

static const struct WarpEventData KogasRoom_WarpEvents[] = {
    warp_event(4, 17, WILLS_ROOM, 2),
    warp_event(5, 17, WILLS_ROOM, 3),
    warp_event(4, 2, BRUNOS_ROOM, 1),
    warp_event(5, 2, BRUNOS_ROOM, 2),
};

static const struct ObjEvent KogasRoom_ObjectEvents[] = {
    object_event(5, 7, SPRITE_KOGA, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &KogaScript_Battle, -1),
};

const struct MapEvents KogasRoom_MapEvents = {
    .warp_event_count = lengthof(KogasRoom_WarpEvents),
    .warp_events = KogasRoom_WarpEvents,

    .coord_event_count = 0, // lengthof(KogasRoom_CoordEvents),
    .coord_events = KogasRoom_CoordEvents,

    .bg_event_count = 0, // lengthof(KogasRoom_BGEvents),
    .bg_events = KogasRoom_BGEvents,

    .obj_event_count = lengthof(KogasRoom_ObjectEvents),
    .obj_events = KogasRoom_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "KogasRoom.h"

bool KogasRoom_MapScripts_LockDoor(script_s* s) {
    SCRIPT_BEGIN
    sdefer(KogasRoom_MapScripts_KogasDoorLocksBehindYou);
    s_end
    SCRIPT_END
}
bool KogasRoom_MapScripts_DummyScene(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool KogasRoom_MapScripts_KogasRoomDoors(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_KOGAS_ROOM_ENTRANCE_CLOSED)
    iffalse(KeepEntranceOpen)
    changeblock(4, 14, 0x2a) // wall
KeepEntranceOpen:
    checkevent(EVENT_KOGAS_ROOM_EXIT_OPEN)
    iffalse(KeepExitClosed)
    changeblock(4, 2, 0x16) // open door
KeepExitClosed:
    s_endcallback
    SCRIPT_END
}
bool KogasRoom_MapScripts_KogasDoorLocksBehindYou(script_s* s) {
    SCRIPT_BEGIN
    applymovement(PLAYER, KogasRoom_EnterMovement)
    refreshscreen
    playsound(SFX_STRENGTH)
    earthquake(80)
    changeblock(4, 14, 0x2a) // wall
    reloadmappart
    closetext
    setscene(SCENE_FINISHED)
    setevent(EVENT_KOGAS_ROOM_ENTRANCE_CLOSED)
    waitsfx
    s_end
    SCRIPT_END
}
bool KogaScript_Battle(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_BEAT_ELITE_4_KOGA)
    iftrue_jump(KogaScript_AfterBattle)
    writetext(KogaScript_KogaBeforeText)
    waitbutton
    closetext
    winlosstext(KogaScript_KogaBeatenText, 0)
    loadtrainer(KOGA, KOGA1)
    startbattle
    reloadmapafterbattle
    setevent(EVENT_BEAT_ELITE_4_KOGA)
    opentext
    writetext(KogaScript_KogaDefeatText)
    waitbutton
    closetext
    playsound(SFX_ENTER_DOOR)
    changeblock(4, 2, 0x16) // open door
    reloadmappart
    closetext
    setevent(EVENT_KOGAS_ROOM_EXIT_OPEN)
    waitsfx
    s_end
    SCRIPT_END
}
bool KogaScript_AfterBattle(script_s* s) {
    SCRIPT_BEGIN
    writetext(KogaScript_KogaDefeatText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const uint8_t KogasRoom_EnterMovement[] = {
    step(UP),
    step(UP),
    step(UP),
    step(UP),
    movement_step_end,
};
const txt_cmd_s KogaScript_KogaBeforeText[] = {
    text_start("Fwahahahaha!"
        t_para "I am KOGA of the"
        t_line "ELITE FOUR."
        t_para "I live in shadows,"
        t_line "a ninja!"
        t_para "My intricate style"
        t_line "will confound and"
        t_cont "destroy you!"
        t_para "Confusion, sleep,"
        t_line "poison…"
        t_para "Prepare to be the"
        t_line "victim of my sin-"
        t_cont "ister technique!"
        t_para "Fwahahahaha!"
        t_para "#MON is not"
        t_line "merely about brute"
        t_para "force--you shall"
        t_line "see soon enough!"
        t_done )
};
const txt_cmd_s KogaScript_KogaBeatenText[] = {
    text_start("Ah!"
        t_line "You have proven"
        t_cont "your worth!"
        t_done )
};
const txt_cmd_s KogaScript_KogaDefeatText[] = {
    text_start("I subjected you to"
        t_line "everything I could"
        t_cont "muster."
        t_para "But my efforts"
        t_line "failed. I must"
        t_cont "hone my skills."
        t_para "Go on to the next"
        t_line "room, and put your"
        t_cont "abilities to test!"
        t_done )
    //db(0, 0) // filler
};
