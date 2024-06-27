#include "../constants.h"
#include "../util/scripting.h"
#include "LancesRoom.h"
//// EVENTS
enum {
    LANCESROOM_LANCE = 2,
    LANCESROOM_MARY,
    LANCESROOM_OAK,
};

const Script_fn_t LancesRoom_SceneScripts[] = {
    LancesRoom_MapScripts_LockDoor , //  SCENE_DEFAULT,
    LancesRoom_MapScripts_DummyScene , //  SCENE_LANCESROOM_APPROACH_LANCE,
};

const struct MapCallback LancesRoom_MapCallbacks[] = {
    map_callback(MAPCALLBACK_TILES, LancesRoom_MapScripts_LancesRoomDoors),
};

const struct MapScripts LancesRoom_MapScripts = {
    .scene_script_count = lengthof(LancesRoom_SceneScripts),
    .scene_scripts = LancesRoom_SceneScripts,

    .callback_count = lengthof(LancesRoom_MapCallbacks),
    .callbacks = LancesRoom_MapCallbacks,
};

static const struct CoordEvent LancesRoom_CoordEvents[] = {
    coord_event(4, 5, SCENE_LANCESROOM_APPROACH_LANCE, &Script_ApproachLanceFromLeft),
    coord_event(5, 5, SCENE_LANCESROOM_APPROACH_LANCE, &Script_ApproachLanceFromRight),
};

static const struct BGEvent LancesRoom_BGEvents[] = {
    0,
};

static const struct WarpEventData LancesRoom_WarpEvents[] = {
    warp_event(4, 23, KARENS_ROOM, 3),
    warp_event(5, 23, KARENS_ROOM, 4),
    warp_event(4, 1, HALL_OF_FAME, 1),
    warp_event(5, 1, HALL_OF_FAME, 2),
};

static const struct ObjEvent LancesRoom_ObjectEvents[] = {
    object_event(5, 3, SPRITE_LANCE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &LancesRoomLanceScript, -1),
    object_event(4, 7, SPRITE_TEACHER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, EVENT_LANCES_ROOM_OAK_AND_MARY),
    object_event(4, 7, SPRITE_OAK, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, EVENT_LANCES_ROOM_OAK_AND_MARY),
};

const struct MapEvents LancesRoom_MapEvents = {
    .warp_event_count = lengthof(LancesRoom_WarpEvents),
    .warp_events = LancesRoom_WarpEvents,

    .coord_event_count = lengthof(LancesRoom_CoordEvents),
    .coord_events = LancesRoom_CoordEvents,

    .bg_event_count = 0, // lengthof(LancesRoom_BGEvents),
    .bg_events = LancesRoom_BGEvents,

    .obj_event_count = lengthof(LancesRoom_ObjectEvents),
    .obj_events = LancesRoom_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "LancesRoom.h"

bool LancesRoom_MapScripts_LockDoor(script_s* s) {
    SCRIPT_BEGIN
    sdefer(LancesRoom_MapScripts_LancesDoorLocksBehindYou);
    s_end
    SCRIPT_END
}
bool LancesRoom_MapScripts_DummyScene(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool LancesRoom_MapScripts_LancesRoomDoors(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_LANCES_ROOM_ENTRANCE_CLOSED)
    iffalse(KeepEntranceOpen)
    changeblock(4, 22, 0x34) // wall
KeepEntranceOpen:
    checkevent(EVENT_LANCES_ROOM_EXIT_OPEN)
    iffalse(KeepExitClosed)
    changeblock(4, 0, 0x0b) // open door
KeepExitClosed:
    s_endcallback
    SCRIPT_END
}
bool LancesRoom_MapScripts_LancesDoorLocksBehindYou(script_s* s) {
    SCRIPT_BEGIN
    applymovement(PLAYER, LancesRoom_EnterMovement)
    refreshscreen
    playsound(SFX_STRENGTH)
    earthquake(80)
    changeblock(4, 22, 0x34) // wall
    reloadmappart
    closetext
    setscene(SCENE_LANCESROOM_APPROACH_LANCE)
    setevent(EVENT_LANCES_ROOM_ENTRANCE_CLOSED)
    s_end
    SCRIPT_END
}
bool Script_ApproachLanceFromLeft(script_s* s) {
    SCRIPT_BEGIN
    special(FadeOutMusic)
    applymovement(PLAYER, MovementData_ApproachLanceFromLeft)
    sjump(LancesRoomLanceScript)
    SCRIPT_END
}
bool Script_ApproachLanceFromRight(script_s* s) {
    SCRIPT_BEGIN
    special(FadeOutMusic)
    applymovement(PLAYER, MovementData_ApproachLanceFromRight)
    SCRIPT_FALLTHROUGH(LancesRoomLanceScript)
}
bool LancesRoomLanceScript(script_s* s) {
    SCRIPT_BEGIN
    turnobject(LANCESROOM_LANCE, LEFT)
    opentext
    writetext(LanceBattleIntroText)
    waitbutton
    closetext
    winlosstext(LanceBattleWinText, 0)
    setlasttalked(LANCESROOM_LANCE)
    loadtrainer(CHAMPION, LANCE)
    startbattle
    dontrestartmapmusic
    reloadmapafterbattle
    setevent(EVENT_BEAT_CHAMPION_LANCE)
    opentext
    writetext(LanceBattleAfterText)
    waitbutton
    closetext
    playsound(SFX_ENTER_DOOR)
    changeblock(4, 0, 0x0b) // open door
    reloadmappart
    closetext
    setevent(EVENT_LANCES_ROOM_ENTRANCE_CLOSED)
    musicfadeout(MUSIC_BEAUTY_ENCOUNTER, 16)
    pause(30)
    showemote(EMOTE_SHOCK, LANCESROOM_LANCE, 15)
    turnobject(LANCESROOM_LANCE, DOWN)
    pause(10)
    turnobject(PLAYER, DOWN)
    appear(LANCESROOM_MARY)
    applymovement(LANCESROOM_MARY, LancesRoomMovementData_MaryRushesIn)
    opentext
    writetext(LancesRoomMaryOhNoOakText)
    waitbutton
    closetext
    appear(LANCESROOM_OAK)
    applymovement(LANCESROOM_OAK, LancesRoomMovementData_OakWalksIn)
    follow(LANCESROOM_MARY, LANCESROOM_OAK)
    applymovement(LANCESROOM_MARY, LancesRoomMovementData_MaryYieldsToOak)
    stopfollow
    turnobject(LANCESROOM_OAK, UP)
    turnobject(LANCESROOM_LANCE, LEFT)
    opentext
    writetext(LancesRoomOakCongratulationsText)
    waitbutton
    closetext
    applymovement(LANCESROOM_MARY, LancesRoomMovementData_MaryInterviewChampion)
    turnobject(PLAYER, LEFT)
    opentext
    writetext(LancesRoomMaryInterviewText)
    waitbutton
    closetext
    applymovement(LANCESROOM_LANCE, LancesRoomMovementData_LancePositionsSelfToGuidePlayerAway)
    turnobject(PLAYER, UP)
    opentext
    writetext(LancesRoomNoisyText)
    waitbutton
    closetext
    follow(LANCESROOM_LANCE, PLAYER)
    turnobject(LANCESROOM_MARY, UP)
    turnobject(LANCESROOM_OAK, UP)
    applymovement(LANCESROOM_LANCE, LancesRoomMovementData_LanceLeadsPlayerToHallOfFame)
    stopfollow
    playsound(SFX_EXIT_BUILDING)
    disappear(LANCESROOM_LANCE)
    applymovement(PLAYER, LancesRoomMovementData_PlayerExits)
    playsound(SFX_EXIT_BUILDING)
    disappear(PLAYER)
    applymovement(LANCESROOM_MARY, LancesRoomMovementData_MaryTriesToFollow)
    showemote(EMOTE_SHOCK, LANCESROOM_MARY, 15)
    opentext
    writetext(LancesRoomMaryNoInterviewText)
    pause(30)
    closetext
    applymovement(LANCESROOM_MARY, LancesRoomMovementData_MaryRunsBackAndForth)
    special(FadeOutPalettes)
    pause(15)
    warpfacing(UP, HALL_OF_FAME, 4, 13)
    s_end
    SCRIPT_END
}
const uint8_t LancesRoom_EnterMovement[] = {
    step(UP),
    step(UP),
    step(UP),
    step(UP),
    movement_step_end,
};
const uint8_t MovementData_ApproachLanceFromLeft[] = {
    step(UP),
    step(UP),
    turn_head(RIGHT),
    movement_step_end,
};
const uint8_t MovementData_ApproachLanceFromRight[] = {
    step(UP),
    step(LEFT),
    step(UP),
    turn_head(RIGHT),
    movement_step_end,
};
const uint8_t LancesRoomMovementData_MaryRushesIn[] = {
    big_step(UP),
    big_step(UP),
    big_step(UP),
    turn_head(DOWN),
    movement_step_end,
};
const uint8_t LancesRoomMovementData_OakWalksIn[] = {
    step(UP),
    step(UP),
    movement_step_end,
};
const uint8_t LancesRoomMovementData_MaryYieldsToOak[] = {
    step(LEFT),
    turn_head(RIGHT),
    movement_step_end,
};
const uint8_t LancesRoomMovementData_MaryInterviewChampion[] = {
    big_step(UP),
    turn_head(RIGHT),
    movement_step_end,
};
const uint8_t LancesRoomMovementData_LancePositionsSelfToGuidePlayerAway[] = {
    step(UP),
    step(LEFT),
    turn_head(DOWN),
    movement_step_end,
};
const uint8_t LancesRoomMovementData_LanceLeadsPlayerToHallOfFame[] = {
    step(UP),
    movement_step_end,
};
const uint8_t LancesRoomMovementData_PlayerExits[] = {
    step(UP),
    movement_step_end,
};
const uint8_t LancesRoomMovementData_MaryTriesToFollow[] = {
    step(UP),
    step(RIGHT),
    turn_head(UP),
    movement_step_end,
};
const uint8_t LancesRoomMovementData_MaryRunsBackAndForth[] = {
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(LEFT),
    big_step(LEFT),
    big_step(LEFT),
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(LEFT),
    big_step(LEFT),
    turn_head(UP),
    movement_step_end,
};
const txt_cmd_s LanceBattleIntroText[] = {
    text_start("LANCE: I've been"
        t_line "waiting for you."
        t_para "<PLAY_G>!"
        t_para "I knew that you,"
        t_line "with your skills,"
        t_para "would eventually"
        t_line "reach me here."
        t_para "There's no need"
        t_line "for words now."
        t_para "We will battle to"
        t_line "determine who is"
        t_para "the stronger of"
        t_line "the two of us."
        t_para "As the most power-"
        t_line "ful trainer and as"
        t_para "the #MON LEAGUE"
        t_line "CHAMPION…"
        t_para "I, LANCE the drag-"
        t_line "on master, accept"
        t_cont "your challenge!"
        t_done )
};
const txt_cmd_s LanceBattleWinText[] = {
    text_start("…It's over."
        t_para "But it's an odd"
        t_line "feeling."
        t_para "I'm not angry that"
        t_line "I lost. In fact, I"
        t_cont "feel happy."
        t_para "Happy that I"
        t_line "witnessed the rise"
        t_para "of a great new"
        t_line "CHAMPION!"
        t_done )
};
const txt_cmd_s LanceBattleAfterText[] = {
    text_start("…Whew."
        t_para "You have become"
        t_line "truly powerful,"
        t_cont "<PLAY_G>."
        t_para "Your #MON have"
        t_line "responded to your"
        t_para "strong and up-"
        t_line "standing nature."
        t_para "As a trainer, you"
        t_line "will continue to"
        t_para "grow strong with"
        t_line "your #MON."
        t_done )
};
const txt_cmd_s LancesRoomMaryOhNoOakText[] = {
    text_start("MARY: Oh, no!"
        t_line "It's all over!"
        t_para "PROF.OAK, if you"
        t_line "weren't so slow…"
        t_done )
};
const txt_cmd_s LancesRoomOakCongratulationsText[] = {
    text_start("PROF.OAK: Ah,"
        t_line "<PLAY_G>!"
        t_para "It's been a long"
        t_line "while."
        t_para "You certainly look"
        t_line "more impressive."
        t_para "Your conquest of"
        t_line "the LEAGUE is just"
        t_cont "fantastic!"
        t_para "Your dedication,"
        t_line "trust and love for"
        t_para "your #MON made"
        t_line "this happen."
        t_para "Your #MON were"
        t_line "outstanding too."
        t_para "Because they be-"
        t_line "lieved in you as a"
        t_para "trainer, they per-"
        t_line "severed."
        t_para "Congratulations,"
        t_line "<PLAY_G>!"
        t_done )
};
const txt_cmd_s LancesRoomMaryInterviewText[] = {
    text_start("MARY: Let's inter-"
        t_line "view the brand new"
        t_cont "CHAMPION!"
        t_done )
};
const txt_cmd_s LancesRoomNoisyText[] = {
    text_start("LANCE: This is"
        t_line "getting to be a"
        t_cont "bit too noisy…"
        t_para "<PLAY_G>, could you"
        t_line "come with me?"
        t_done )
};
const txt_cmd_s LancesRoomMaryNoInterviewText[] = {
    text_start("MARY: Oh, wait!"
        t_line "We haven't done"
        t_cont "the interview!"
        t_done )
    //db(0, 0) // filler
};
