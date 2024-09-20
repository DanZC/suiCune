#include "../constants.h"
#include "../util/scripting.h"
#include "MountMoon.h"
//// EVENTS
enum {
    MOUNTMOON_SILVER = 2,
};

const Script_fn_t MountMoon_SceneScripts[] = {
    MountMoon_MapScripts_RivalEncounter , //  SCENE_DEFAULT,
    MountMoon_MapScripts_DummyScene , //  SCENE_FINISHED,
};

const struct MapCallback MountMoon_MapCallbacks[] = {
    0,
};

const struct MapScripts MountMoon_MapScripts = {
    .scene_script_count = lengthof(MountMoon_SceneScripts),
    .scene_scripts = MountMoon_SceneScripts,

    .callback_count = 0, // lengthof(MountMoon_MapCallbacks),
    .callbacks = MountMoon_MapCallbacks,
};

static const struct CoordEvent MountMoon_CoordEvents[] = {
    0,
};

static const struct BGEvent MountMoon_BGEvents[] = {
    0,
};

static const struct WarpEventData MountMoon_WarpEvents[] = {
    warp_event(3, 3, ROUTE_3, 1),
    warp_event(15, 15, ROUTE_4, 1),
    warp_event(13, 3, MOUNT_MOON, 7),
    warp_event(15, 11, MOUNT_MOON, 8),
    warp_event(25, 5, MOUNT_MOON_SQUARE, 1),
    warp_event(25, 15, MOUNT_MOON_SQUARE, 2),
    warp_event(25, 3, MOUNT_MOON, 3),
    warp_event(25, 13, MOUNT_MOON, 4),
};

static const struct ObjEvent MountMoon_ObjectEvents[] = {
    object_event(7, 3, SPRITE_SILVER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, EVENT_MT_MOON_RIVAL),
};

const struct MapEvents MountMoon_MapEvents = {
    .warp_event_count = lengthof(MountMoon_WarpEvents),
    .warp_events = MountMoon_WarpEvents,

    .coord_event_count = 0, // lengthof(MountMoon_CoordEvents),
    .coord_events = MountMoon_CoordEvents,

    .bg_event_count = 0, // lengthof(MountMoon_BGEvents),
    .bg_events = MountMoon_BGEvents,

    .obj_event_count = lengthof(MountMoon_ObjectEvents),
    .obj_events = MountMoon_ObjectEvents,
};

//// CODE

bool MountMoon_MapScripts_RivalEncounter(script_s* s) {
    SCRIPT_BEGIN
    sdefer(MountMoon_MapScripts_RivalBattle);
    s_end
    SCRIPT_END
}
bool MountMoon_MapScripts_DummyScene(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool MountMoon_MapScripts_RivalBattle(script_s* s) {
    SCRIPT_BEGIN
    turnobject(PLAYER, RIGHT)
    showemote(EMOTE_SHOCK, PLAYER, 15)
    special(FadeOutMusic)
    pause(15)
    applymovement(MOUNTMOON_SILVER, MountMoonSilverMovementBefore)
    playmusic(MUSIC_RIVAL_ENCOUNTER)
    opentext
    writetext(MountMoonSilverTextBefore)
    waitbutton
    closetext
    checkevent(EVENT_GOT_TOTODILE_FROM_ELM)
    iftrue(Totodile)
    checkevent(EVENT_GOT_CHIKORITA_FROM_ELM)
    iftrue(Chikorita)
    winlosstext(MountMoonSilverTextWin, MountMoonSilverTextLoss)
    setlasttalked(MOUNTMOON_SILVER)
    loadtrainer(RIVAL2, RIVAL2_1_TOTODILE)
    startbattle
    dontrestartmapmusic
    reloadmapafterbattle
    goto FinishBattle;
Totodile:
    winlosstext(MountMoonSilverTextWin, MountMoonSilverTextLoss)
    setlasttalked(MOUNTMOON_SILVER)
    loadtrainer(RIVAL2, RIVAL2_1_CHIKORITA)
    startbattle
    dontrestartmapmusic
    reloadmapafterbattle
    goto FinishBattle;
Chikorita:
    winlosstext(MountMoonSilverTextWin, MountMoonSilverTextLoss)
    setlasttalked(MOUNTMOON_SILVER)
    loadtrainer(RIVAL2, RIVAL2_1_CYNDAQUIL)
    startbattle
    dontrestartmapmusic
    reloadmapafterbattle
    // goto FinishBattle;
FinishBattle:
    playmusic(MUSIC_RIVAL_AFTER)
    opentext
    writetext(MountMoonSilverTextAfter)
    waitbutton
    closetext
    applymovement(MOUNTMOON_SILVER, MountMoonSilverMovementAfter)
    disappear(MOUNTMOON_SILVER)
    setscene(SCENE_FINISHED)
    setevent(EVENT_BEAT_RIVAL_IN_MT_MOON)
    playmapmusic
    s_end
    SCRIPT_END
}
const uint8_t MountMoonSilverMovementBefore[] = {
    step(LEFT),
    step(LEFT),
    step(LEFT),
    movement_step_end,
};
const uint8_t MountMoonSilverMovementAfter[] = {
    step(RIGHT),
    step(RIGHT),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    movement_step_end,
};
const txt_cmd_s MountMoonSilverTextBefore[] = {
    text_start("<……> <……> <……>"
        t_para "It's been a while,"
        t_line "<PLAYER>."
        t_para "…Since I lost to"
        t_line "you, I thought"
        t_para "about what I was"
        t_line "lacking with my"
        t_cont "#MON…"
        t_para "And we came up"
        t_line "with an answer."
        t_para "<PLAYER>, now we'll"
        t_line "show you!"
        t_done )
};
const txt_cmd_s MountMoonSilverTextWin[] = {
    text_start("<……> <……> <……>"
        t_para "I thought I raised"
        t_line "my #MON to be"
        t_para "the best they"
        t_line "could be…"
        t_para "…But it still "
        t_line "wasn't enough…"
        t_done )
};
const txt_cmd_s MountMoonSilverTextAfter[] = {
    text_start("<……> <……> <……>"
        t_para "…You won, fair"
        t_line "and square."
        t_para "I admit it. But"
        t_line "this isn't the"
        t_cont "end."
        t_para "I'm going to be"
        t_line "the greatest #-"
        t_cont "MON trainer ever."
        t_para "Because these guys"
        t_line "are behind me."
        t_para "…Listen, <PLAYER>."
        t_para "One of these days"
        t_line "I'm going to prove"
        t_para "how good I am by"
        t_line "beating you."
        t_done )
};
const txt_cmd_s MountMoonSilverTextLoss[] = {
    text_start("<……> <……> <……>"
        t_para "I've repaid my"
        t_line "debt to you."
        t_para "With my #MON,"
        t_line "I'm going to beat"
        t_para "the CHAMPION and"
        t_line "become the world's"
        t_cont "greatest trainer."
        t_done )
    //db(0, 0) // filler
};
