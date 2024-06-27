#include "../constants.h"
#include "../util/scripting.h"
#include "VictoryRoad.h"
//// EVENTS
enum {
    VICTORYROAD_SILVER = 2,
    VICTORYROAD_POKE_BALL1,
    VICTORYROAD_POKE_BALL2,
    VICTORYROAD_POKE_BALL3,
    VICTORYROAD_POKE_BALL4,
    VICTORYROAD_POKE_BALL5,
};

const Script_fn_t VictoryRoad_SceneScripts[] = {
    VictoryRoad_MapScripts_DummyScene0 , //  SCENE_DEFAULT,
    VictoryRoad_MapScripts_DummyScene1 , //  SCENE_FINISHED,
};

const struct MapCallback VictoryRoad_MapCallbacks[] = {
    0,
};

const struct MapScripts VictoryRoad_MapScripts = {
    .scene_script_count = lengthof(VictoryRoad_SceneScripts),
    .scene_scripts = VictoryRoad_SceneScripts,

    .callback_count = 0, // lengthof(VictoryRoad_MapCallbacks),
    .callbacks = VictoryRoad_MapCallbacks,
};

static const struct CoordEvent VictoryRoad_CoordEvents[] = {
    coord_event(12, 8, SCENE_DEFAULT, &VictoryRoadRivalLeft),
    coord_event(13, 8, SCENE_DEFAULT, &VictoryRoadRivalRight),
};

static const struct BGEvent VictoryRoad_BGEvents[] = {
    bg_event(3, 29, BGEVENT_ITEM, &VictoryRoadHiddenMaxPotion),
    bg_event(3, 65, BGEVENT_ITEM, &VictoryRoadHiddenFullHeal),
};

static const struct WarpEventData VictoryRoad_WarpEvents[] = {
    warp_event(9, 67, VICTORY_ROAD_GATE, 5),
    warp_event(1, 49, VICTORY_ROAD, 3),
    warp_event(1, 35, VICTORY_ROAD, 2),
    warp_event(13, 31, VICTORY_ROAD, 5),
    warp_event(13, 17, VICTORY_ROAD, 4),
    warp_event(17, 33, VICTORY_ROAD, 7),
    warp_event(17, 19, VICTORY_ROAD, 6),
    warp_event(0, 11, VICTORY_ROAD, 9),
    warp_event(0, 27, VICTORY_ROAD, 8),
    warp_event(13, 5, ROUTE_23, 3),
};

static const struct ObjEvent VictoryRoad_ObjectEvents[] = {
    object_event(18, 13, SPRITE_SILVER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, EVENT_RIVAL_VICTORY_ROAD),
    object_event(3, 28, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &VictoryRoadTMEarthquake, EVENT_VICTORY_ROAD_TM_EARTHQUAKE),
    object_event(12, 48, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &VictoryRoadMaxRevive, EVENT_VICTORY_ROAD_MAX_REVIVE),
    object_event(18, 29, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &VictoryRoadFullRestore, EVENT_VICTORY_ROAD_FULL_RESTORE),
    object_event(15, 48, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &VictoryRoadFullHeal, EVENT_VICTORY_ROAD_FULL_HEAL),
    object_event(7, 38, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &VictoryRoadHPUp, EVENT_VICTORY_ROAD_HP_UP),
};

const struct MapEvents VictoryRoad_MapEvents = {
    .warp_event_count = lengthof(VictoryRoad_WarpEvents),
    .warp_events = VictoryRoad_WarpEvents,

    .coord_event_count = lengthof(VictoryRoad_CoordEvents),
    .coord_events = VictoryRoad_CoordEvents,

    .bg_event_count = lengthof(VictoryRoad_BGEvents),
    .bg_events = VictoryRoad_BGEvents,

    .obj_event_count = lengthof(VictoryRoad_ObjectEvents),
    .obj_events = VictoryRoad_ObjectEvents,
};

//// CODE

bool VictoryRoad_MapScripts_DummyScene0(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool VictoryRoad_MapScripts_DummyScene1(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool VictoryRoadRivalLeft(script_s* s) {
    SCRIPT_BEGIN
    moveobject(VICTORYROAD_SILVER, 18, 11)
    turnobject(PLAYER, DOWN)
    showemote(EMOTE_SHOCK, PLAYER, 15)
    special(FadeOutMusic)
    pause(15)
    appear(VICTORYROAD_SILVER)
    applymovement(VICTORYROAD_SILVER, VictoryRoadRivalBattleApproachMovement1)
    scall(VictoryRoadRivalNext)
    applymovement(VICTORYROAD_SILVER, VictoryRoadRivalBattleExitMovement1)
    disappear(VICTORYROAD_SILVER)
    setscene(SCENE_FINISHED)
    playmapmusic
    s_end
    SCRIPT_END
}
bool VictoryRoadRivalRight(script_s* s) {
    SCRIPT_BEGIN
    turnobject(PLAYER, DOWN)
    showemote(EMOTE_SHOCK, PLAYER, 15)
    special(FadeOutMusic)
    pause(15)
    appear(VICTORYROAD_SILVER)
    applymovement(VICTORYROAD_SILVER, VictoryRoadRivalBattleApproachMovement2)
    scall(VictoryRoadRivalNext)
    applymovement(VICTORYROAD_SILVER, VictoryRoadRivalBattleExitMovement2)
    disappear(VICTORYROAD_SILVER)
    setscene(SCENE_FINISHED)
    playmapmusic
    s_end
    SCRIPT_END
}
bool VictoryRoadRivalNext(script_s* s) {
    SCRIPT_BEGIN
    turnobject(PLAYER, DOWN)
    playmusic(MUSIC_RIVAL_ENCOUNTER)
    opentext
    writetext(VictoryRoadRivalBeforeText)
    waitbutton
    closetext
    setevent(EVENT_RIVAL_VICTORY_ROAD)
    checkevent(EVENT_GOT_TOTODILE_FROM_ELM)
    iftrue(GotTotodile)
    checkevent(EVENT_GOT_CHIKORITA_FROM_ELM)
    iftrue(GotChikorita)
    winlosstext(VictoryRoadRivalDefeatText, VictoryRoadRivalVictoryText)
    setlasttalked(VICTORYROAD_SILVER)
    loadtrainer(RIVAL1, RIVAL1_5_TOTODILE)
    startbattle
    dontrestartmapmusic
    reloadmapafterbattle
    goto AfterBattle;
GotTotodile:
    winlosstext(VictoryRoadRivalDefeatText, VictoryRoadRivalVictoryText)
    setlasttalked(VICTORYROAD_SILVER)
    loadtrainer(RIVAL1, RIVAL1_5_CHIKORITA)
    startbattle
    dontrestartmapmusic
    reloadmapafterbattle
    goto AfterBattle;
GotChikorita:
    winlosstext(VictoryRoadRivalDefeatText, VictoryRoadRivalVictoryText)
    setlasttalked(VICTORYROAD_SILVER)
    loadtrainer(RIVAL1, RIVAL1_5_CYNDAQUIL)
    startbattle
    dontrestartmapmusic
    reloadmapafterbattle
    goto AfterBattle;
AfterBattle:
    playmusic(MUSIC_RIVAL_AFTER)
    opentext
    writetext(VictoryRoadRivalAfterText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct ItemBall VictoryRoadTMEarthquake = {TM_EARTHQUAKE, 1};
const struct ItemBall VictoryRoadMaxRevive = {MAX_REVIVE, 1};
const struct ItemBall VictoryRoadFullRestore = {FULL_RESTORE, 1};
const struct ItemBall VictoryRoadFullHeal = {FULL_HEAL, 1};
const struct ItemBall VictoryRoadHPUp = {HP_UP, 1};
const struct HiddenItem VictoryRoadHiddenMaxPotion = {MAX_POTION, EVENT_VICTORY_ROAD_HIDDEN_MAX_POTION};
const struct HiddenItem VictoryRoadHiddenFullHeal = {FULL_HEAL, EVENT_VICTORY_ROAD_HIDDEN_FULL_HEAL};
const uint8_t VictoryRoadRivalBattleApproachMovement1[] = {
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(UP),
    step(UP),
    movement_step_end,
};
const uint8_t VictoryRoadRivalBattleApproachMovement2[] = {
    step(UP),
    step(UP),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(UP),
    step(UP),
    movement_step_end,
};
const uint8_t VictoryRoadRivalBattleExitMovement1[] = {
    step(DOWN),
    step(DOWN),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    movement_step_end,
};
const uint8_t VictoryRoadRivalBattleExitMovement2[] = {
    step(DOWN),
    step(DOWN),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    step(DOWN),
    step(DOWN),
    movement_step_end,
};
const txt_cmd_s VictoryRoadRivalBeforeText[] = {
    text_start("Hold it."
        t_para "…Are you going to"
        t_line "take the #MON"
        t_cont "LEAGUE challenge?"
        t_para "…Don't make me"
        t_line "laugh."
        t_para "You're so much"
        t_line "weaker than I am."
        t_para "I'm not like I was"
        t_line "before."
        t_para "I now have the"
        t_line "best and strongest"
        t_para "#MON with me."
        t_line "I'm invincible!"
        t_para "<PLAYER>!"
        t_line "I challenge you!"
        t_done )
};
const txt_cmd_s VictoryRoadRivalDefeatText[] = {
    text_start("…I couldn't win…"
        t_para "I gave it every-"
        t_line "thing I had…"
        t_para "What you possess,"
        t_line "and what I lack…"
        t_para "I'm beginning to"
        t_line "understand what"
        t_para "that dragon master"
        t_line "said to me…"
        t_done )
};
const txt_cmd_s VictoryRoadRivalAfterText[] = {
    text_start("…I haven't given up"
        t_line "on becoming the"
        t_cont "greatest trainer…"
        t_para "I'm going to find"
        t_line "out why I can't"
        t_para "win and become"
        t_line "stronger…"
        t_para "When I do, I will"
        t_line "challenge you."
        t_para "And I'll beat you"
        t_line "down with all my"
        t_cont "power."
        t_para "…Humph! You keep"
        t_line "at it until then."
        t_done )
};
const txt_cmd_s VictoryRoadRivalVictoryText[] = {
    text_start("…Humph!"
        t_para "When it comes down"
        t_line "to it, nothing can"
        t_cont "beat power."
        t_para "I don't need any-"
        t_line "thing else."
        t_done )
    //db(0, 0) // filler
};
