#include "../constants.h"
#include "../util/scripting.h"
#include "KarensRoom.h"
//// EVENTS
enum {
    KARENSROOM_KAREN = 2,
};

const Script_fn_t KarensRoom_SceneScripts[] = {
    KarensRoom_MapScripts_LockDoor , //  SCENE_DEFAULT,
    KarensRoom_MapScripts_DummyScene , //  SCENE_FINISHED,
};

const struct MapCallback KarensRoom_MapCallbacks[] = {
    map_callback(MAPCALLBACK_TILES, KarensRoom_MapScripts_KarensRoomDoors),
};

const struct MapScripts KarensRoom_MapScripts = {
    .scene_script_count = lengthof(KarensRoom_SceneScripts),
    .scene_scripts = KarensRoom_SceneScripts,

    .callback_count = lengthof(KarensRoom_MapCallbacks),
    .callbacks = KarensRoom_MapCallbacks,
};

static const struct CoordEvent KarensRoom_CoordEvents[] = {
    0,
};

static const struct BGEvent KarensRoom_BGEvents[] = {
    0,
};

static const struct WarpEventData KarensRoom_WarpEvents[] = {
    warp_event(4, 17, BRUNOS_ROOM, 3),
    warp_event(5, 17, BRUNOS_ROOM, 4),
    warp_event(4, 2, LANCES_ROOM, 1),
    warp_event(5, 2, LANCES_ROOM, 2),
};

static const struct ObjEvent KarensRoom_ObjectEvents[] = {
    object_event(5, 7, SPRITE_KAREN, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &KarenScript_Battle, -1),
};

const struct MapEvents KarensRoom_MapEvents = {
    .warp_event_count = lengthof(KarensRoom_WarpEvents),
    .warp_events = KarensRoom_WarpEvents,

    .coord_event_count = 0, // lengthof(KarensRoom_CoordEvents),
    .coord_events = KarensRoom_CoordEvents,

    .bg_event_count = 0, // lengthof(KarensRoom_BGEvents),
    .bg_events = KarensRoom_BGEvents,

    .obj_event_count = lengthof(KarensRoom_ObjectEvents),
    .obj_events = KarensRoom_ObjectEvents,
};

//// CODE

bool KarensRoom_MapScripts_LockDoor(script_s* s) {
    SCRIPT_BEGIN
    sdefer(KarensRoom_MapScripts_KarensDoorLocksBehindYou);
    s_end
    SCRIPT_END
}
bool KarensRoom_MapScripts_DummyScene(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool KarensRoom_MapScripts_KarensRoomDoors(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_KARENS_ROOM_ENTRANCE_CLOSED)
    iffalse(KeepEntranceOpen)
    changeblock(4, 14, 0x2a) // wall
KeepEntranceOpen:
    checkevent(EVENT_KARENS_ROOM_EXIT_OPEN)
    iffalse(KeepExitClosed)
    changeblock(4, 2, 0x16) // open door
KeepExitClosed:
    s_endcallback
    SCRIPT_END
}
bool KarensRoom_MapScripts_KarensDoorLocksBehindYou(script_s* s) {
    SCRIPT_BEGIN
    applymovement(PLAYER, KarensRoom_EnterMovement)
    refreshscreen
    playsound(SFX_STRENGTH)
    earthquake(80)
    changeblock(4, 14, 0x2a) // wall
    reloadmappart
    closetext
    setscene(SCENE_FINISHED)
    setevent(EVENT_KARENS_ROOM_ENTRANCE_CLOSED)
    waitsfx
    s_end
    SCRIPT_END
}
bool KarenScript_Battle(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_BEAT_ELITE_4_KAREN)
    iftrue_jump(KarenScript_AfterBattle)
    writetext(KarenScript_KarenBeforeText)
    waitbutton
    closetext
    winlosstext(KarenScript_KarenBeatenText, 0)
    loadtrainer(KAREN, KAREN1)
    startbattle
    reloadmapafterbattle
    setevent(EVENT_BEAT_ELITE_4_KAREN)
    opentext
    writetext(KarenScript_KarenDefeatText)
    waitbutton
    closetext
    playsound(SFX_ENTER_DOOR)
    changeblock(4, 2, 0x16) // open door
    reloadmappart
    closetext
    setevent(EVENT_KARENS_ROOM_EXIT_OPEN)
    waitsfx
    s_end
    SCRIPT_END
}
bool KarenScript_AfterBattle(script_s* s) {
    SCRIPT_BEGIN
    writetext(KarenScript_KarenDefeatText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const uint8_t KarensRoom_EnterMovement[] = {
    step(UP),
    step(UP),
    step(UP),
    step(UP),
    movement_step_end,
};
const txt_cmd_s KarenScript_KarenBeforeText[] = {
    text_start("I am KAREN of the"
        t_line "ELITE FOUR."
        t_para "You're <PLAYER>?"
        t_line "How amusing."
        t_para "I love dark-type"
        t_line "#MON."
        t_para "I find their wild,"
        t_line "tough image to be"
        t_para "so appealing. And"
        t_line "they're so strong."
        t_para "Think you can take"
        t_line "them? Just try to"
        t_cont "entertain me."
        t_para "Let's go."
        t_done )
};
const txt_cmd_s KarenScript_KarenBeatenText[] = {
    text_start("Well, aren't you"
        t_line "good. I like that"
        t_cont "in a trainer."
        t_done )
};
const txt_cmd_s KarenScript_KarenDefeatText[] = {
    text_start("Strong #MON."
        t_para "Weak #MON."
        t_para "That is only the"
        t_line "selfish perception"
        t_cont "of people."
        t_para "Truly skilled"
        t_line "trainers should"
        t_para "try to win with"
        t_line "their favorites."
        t_para "I like your style."
        t_line "You understand"
        t_cont "what's important."
        t_para "Go on--the CHAM-"
        t_line "PION is waiting."
        t_done )
    //db(0, 0) // filler
};
