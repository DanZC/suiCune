#include "../constants.h"
#include "../util/scripting.h"
#include "TinTower1F.h"
//// EVENTS
enum {
    TINTOWER1F_SUICUNE = 2,
    TINTOWER1F_RAIKOU,
    TINTOWER1F_ENTEI,
    TINTOWER1F_EUSINE,
    TINTOWER1F_SAGE1,
    TINTOWER1F_SAGE2,
    TINTOWER1F_SAGE3,
    TINTOWER1F_SAGE4,
    TINTOWER1F_SAGE5,
    TINTOWER1F_SAGE6,
};

const Script_fn_t TinTower1F_SceneScripts[] = {
    TinTower1F_MapScripts_FaceSuicune , //  SCENE_DEFAULT,
    TinTower1F_MapScripts_DummyScene , //  SCENE_FINISHED,
};

const struct MapCallback TinTower1F_MapCallbacks[] = {
    map_callback(MAPCALLBACK_OBJECTS, TinTower1F_MapScripts_NPCsCallback),
    map_callback(MAPCALLBACK_TILES, TinTower1F_MapScripts_StairsCallback),
};

const struct MapScripts TinTower1F_MapScripts = {
    .scene_script_count = lengthof(TinTower1F_SceneScripts),
    .scene_scripts = TinTower1F_SceneScripts,

    .callback_count = lengthof(TinTower1F_MapCallbacks),
    .callbacks = TinTower1F_MapCallbacks,
};

static const struct CoordEvent TinTower1F_CoordEvents[] = {
    0,
};

static const struct BGEvent TinTower1F_BGEvents[] = {
    0,
};

static const struct WarpEventData TinTower1F_WarpEvents[] = {
    warp_event(9, 15, ECRUTEAK_CITY, 12),
    warp_event(10, 15, ECRUTEAK_CITY, 12),
    warp_event(10, 2, TIN_TOWER_2F, 2),
};

static const struct ObjEvent TinTower1F_ObjectEvents[] = {
    object_event(9, 9, SPRITE_SUICUNE, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, EVENT_TIN_TOWER_1F_SUICUNE),
    object_event(7, 9, SPRITE_RAIKOU, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, EVENT_TIN_TOWER_1F_RAIKOU),
    object_event(12, 9, SPRITE_ENTEI, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, EVENT_TIN_TOWER_1F_ENTEI),
    object_event(8, 3, SPRITE_SUPER_NERD, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &TinTower1FEusine, EVENT_TIN_TOWER_1F_EUSINE),
    object_event(5, 9, SPRITE_SAGE, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &TinTower1FSage1Script, EVENT_TIN_TOWER_1F_WISE_TRIO_1),
    object_event(11, 11, SPRITE_SAGE, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &TinTower1FSage2Script, EVENT_TIN_TOWER_1F_WISE_TRIO_1),
    object_event(14, 6, SPRITE_SAGE, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &TinTower1FSage3Script, EVENT_TIN_TOWER_1F_WISE_TRIO_1),
    object_event(4, 2, SPRITE_SAGE, SPRITEMOVEDATA_WALK_UP_DOWN, 0, 1, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &TinTower1FSage4Script, EVENT_TIN_TOWER_1F_WISE_TRIO_2),
    object_event(9, 1, SPRITE_SAGE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &TinTower1FSage5Script, EVENT_TIN_TOWER_1F_WISE_TRIO_2),
    object_event(14, 2, SPRITE_SAGE, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &TinTower1FSage6Script, EVENT_TIN_TOWER_1F_WISE_TRIO_2),
};

const struct MapEvents TinTower1F_MapEvents = {
    .warp_event_count = lengthof(TinTower1F_WarpEvents),
    .warp_events = TinTower1F_WarpEvents,

    .coord_event_count = 0, // lengthof(TinTower1F_CoordEvents),
    .coord_events = TinTower1F_CoordEvents,

    .bg_event_count = 0, // lengthof(TinTower1F_BGEvents),
    .bg_events = TinTower1F_BGEvents,

    .obj_event_count = lengthof(TinTower1F_ObjectEvents),
    .obj_events = TinTower1F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "TinTower1F.h"

bool TinTower1F_MapScripts_FaceSuicune(script_s* s) {
    SCRIPT_BEGIN
    sdefer(TinTower1F_MapScripts_SuicuneBattle);
    s_end
    SCRIPT_END
}
bool TinTower1F_MapScripts_DummyScene(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool TinTower1F_MapScripts_NPCsCallback(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_GOT_RAINBOW_WING)
    iftrue(GotRainbowWing)
    checkevent(EVENT_BEAT_ELITE_FOUR)
    iffalse(FaceBeasts)
    special(BeastsCheck)
    iffalse(FaceBeasts)
    clearevent(EVENT_TIN_TOWER_1F_WISE_TRIO_2)
    setevent(EVENT_TIN_TOWER_1F_WISE_TRIO_1)
GotRainbowWing:
    checkevent(EVENT_FOUGHT_HO_OH)
    iffalse(Done)
    appear(TINTOWER1F_EUSINE)
Done:
    s_endcallback
FaceBeasts:
    checkevent(EVENT_FOUGHT_SUICUNE)
    iftrue(FoughtSuicune)
    appear(TINTOWER1F_SUICUNE)
    setval(RAIKOU)
    special(MonCheck)
    iftrue(NoRaikou)
    appear(TINTOWER1F_RAIKOU)
    goto CheckEntei;
NoRaikou:
    disappear(TINTOWER1F_RAIKOU)
CheckEntei:
    setval(ENTEI)
    special(MonCheck)
    iftrue(NoEntei)
    appear(TINTOWER1F_ENTEI)
    goto BeastsDone;
NoEntei:
    disappear(TINTOWER1F_ENTEI)
BeastsDone:
    s_endcallback
FoughtSuicune:
    disappear(TINTOWER1F_SUICUNE)
    disappear(TINTOWER1F_RAIKOU)
    disappear(TINTOWER1F_ENTEI)
    clearevent(EVENT_TIN_TOWER_1F_WISE_TRIO_1)
    setevent(EVENT_TIN_TOWER_1F_WISE_TRIO_2)
    s_endcallback
    SCRIPT_END
}
bool TinTower1F_MapScripts_StairsCallback(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_GOT_RAINBOW_WING)
    iftrue(DontHideStairs)
    changeblock(10, 2, 0x09) // floor
DontHideStairs:
    s_endcallback
    SCRIPT_END
}
bool TinTower1F_MapScripts_SuicuneBattle(script_s* s) {
    SCRIPT_BEGIN
    applymovement(PLAYER, TinTower1FPlayerEntersMovement)
    pause(15)
    setval(RAIKOU)
    special(MonCheck)
    iftrue(Next1) // if player caught Raikou, it doesn't appear in Tin Tower
    applymovement(TINTOWER1F_RAIKOU, TinTower1FRaikouApproachesMovement)
    turnobject(PLAYER, LEFT)
    playcry(RAIKOU)
    pause(10)
    playsound(SFX_WARP_FROM)
    applymovement(TINTOWER1F_RAIKOU, TinTower1FRaikouLeavesMovement)
    disappear(TINTOWER1F_RAIKOU)
    playsound(SFX_EXIT_BUILDING)
    waitsfx
Next1:
    setval(ENTEI)
    special(MonCheck)
    iftrue(Next2) // if player caught Entei, it doesn't appear in Tin Tower
    applymovement(TINTOWER1F_ENTEI, TinTower1FEnteiApproachesMovement)
    turnobject(PLAYER, RIGHT)
    playcry(ENTEI)
    pause(10)
    playsound(SFX_WARP_FROM)
    applymovement(TINTOWER1F_ENTEI, TinTower1FEnteiLeavesMovement)
    disappear(TINTOWER1F_ENTEI)
    playsound(SFX_EXIT_BUILDING)
    waitsfx
Next2:
    turnobject(PLAYER, UP)
    pause(10)
    applymovement(PLAYER, TinTower1FPlayerBacksUpMovement)
    applymovement(TINTOWER1F_SUICUNE, TinTower1FSuicuneApproachesMovement)
    playcry(SUICUNE)
    pause(20)
    loadwildmon(SUICUNE, 40)
    loadvar(VAR_BATTLETYPE, BATTLETYPE_SUICUNE)
    startbattle
    dontrestartmapmusic
    disappear(TINTOWER1F_SUICUNE)
    setevent(EVENT_FOUGHT_SUICUNE)
    setevent(EVENT_SAW_SUICUNE_ON_ROUTE_42)
    setmapscene(ROUTE_42, SCENE_ROUTE42_NOTHING)
    setevent(EVENT_SAW_SUICUNE_ON_ROUTE_36)
    setmapscene(ROUTE_36, SCENE_ROUTE36_NOTHING)
    setevent(EVENT_SAW_SUICUNE_AT_CIANWOOD_CITY)
    setmapscene(CIANWOOD_CITY, SCENE_CIANWOODCITY_NOTHING)
    setscene(SCENE_FINISHED)
    clearevent(EVENT_SET_WHEN_FOUGHT_HO_OH)
    reloadmapafterbattle
    pause(20)
    turnobject(PLAYER, DOWN)
    playmusic(MUSIC_MYSTICALMAN_ENCOUNTER)
    playsound(SFX_ENTER_DOOR)
    moveobject(TINTOWER1F_EUSINE, 10, 15)
    appear(TINTOWER1F_EUSINE)
    applymovement(TINTOWER1F_EUSINE, TinTower1FEusineEntersMovement)
    playsound(SFX_ENTER_DOOR)
    moveobject(TINTOWER1F_SAGE1, 9, 15)
    appear(TINTOWER1F_SAGE1)
    applymovement(TINTOWER1F_SAGE1, TinTower1FSage1EntersMovement)
    playsound(SFX_ENTER_DOOR)
    moveobject(TINTOWER1F_SAGE2, 9, 15)
    appear(TINTOWER1F_SAGE2)
    applymovement(TINTOWER1F_SAGE2, TinTower1FSage2EntersMovement)
    playsound(SFX_ENTER_DOOR)
    moveobject(TINTOWER1F_SAGE3, 9, 15)
    appear(TINTOWER1F_SAGE3)
    applymovement(TINTOWER1F_SAGE3, TinTower1FSage3EntersMovement)
    moveobject(TINTOWER1F_SAGE1, 7, 13)
    moveobject(TINTOWER1F_SAGE2, 9, 13)
    moveobject(TINTOWER1F_SAGE3, 11, 13)
    turnobject(PLAYER, RIGHT)
    opentext
    writetext(TinTower1FEusineSuicuneText)
    waitbutton
    closetext
    applymovement(TINTOWER1F_EUSINE, TinTower1FEusineLeavesMovement)
    playsound(SFX_EXIT_BUILDING)
    disappear(TINTOWER1F_EUSINE)
    waitsfx
    special(FadeOutMusic)
    pause(20)
    playmapmusic
    s_end
    SCRIPT_END
}
bool TinTower1FSage1Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(TinTower1FSage1Text)
    SCRIPT_END
}
bool TinTower1FSage2Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(TinTower1FSage2Text)
    SCRIPT_END
}
bool TinTower1FSage3Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(TinTower1FSage3Text)
    SCRIPT_END
}
bool TinTower1FSage4Script(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_FOUGHT_HO_OH)
    iftrue(FoughtHoOh)
    jumptextfaceplayer(TinTower1FSage4Text1)
FoughtHoOh:
    jumptextfaceplayer(TinTower1FSage4Text2)
    SCRIPT_END
}
bool TinTower1FSage5Script(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_FOUGHT_HO_OH)
    iftrue(FoughtHoOh)
    checkevent(EVENT_GOT_RAINBOW_WING)
    iftrue(GotRainbowWing)
    writetext(TinTower1FSage5Text1)
    promptbutton
    verbosegiveitem(RAINBOW_WING, 1)
    closetext
    refreshscreen
    earthquake(72)
    waitsfx
    playsound(SFX_STRENGTH)
    changeblock(10, 2, 0x20) // stairs
    reloadmappart
    setevent(EVENT_GOT_RAINBOW_WING)
    closetext
    opentext
GotRainbowWing:
    writetext(TinTower1FSage5Text2)
    waitbutton
    closetext
    s_end
FoughtHoOh:
    writetext(TinTower1FSage5Text3)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool TinTower1FSage6Script(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_FOUGHT_HO_OH)
    iftrue(FoughtHoOh)
    jumptextfaceplayer(TinTower1FSage6Text1)
FoughtHoOh:
    jumptextfaceplayer(TinTower1FSage6Text2)
    SCRIPT_END
}
bool TinTower1FEusine(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(TinTower1FEusineHoOhText)
    SCRIPT_END
}
const uint8_t TinTower1FPlayerEntersMovement[] = {
    slow_step(UP),
    slow_step(UP),
    slow_step(UP),
    slow_step(UP),
    movement_step_end,
};
const uint8_t TinTower1FRaikouApproachesMovement[] = {
    movement_set_sliding,
    fast_jump_step(DOWN),
    movement_remove_sliding,
    movement_step_end,
};
const uint8_t TinTower1FRaikouLeavesMovement[] = {
    movement_set_sliding,
    fast_jump_step(DOWN),
    fast_jump_step(RIGHT),
    fast_jump_step(DOWN),
    movement_remove_sliding,
    movement_step_end,
};
const uint8_t TinTower1FEnteiApproachesMovement[] = {
    movement_set_sliding,
    fast_jump_step(DOWN),
    movement_remove_sliding,
    movement_step_end,
};
const uint8_t TinTower1FEnteiLeavesMovement[] = {
    movement_set_sliding,
    fast_jump_step(DOWN),
    fast_jump_step(LEFT),
    fast_jump_step(DOWN),
    movement_remove_sliding,
    movement_step_end,
};
const uint8_t TinTower1FSuicuneApproachesMovement[] = {
    movement_set_sliding,
    fast_jump_step(DOWN),
    movement_remove_sliding,
    movement_step_end,
};
const uint8_t TinTower1FPlayerBacksUpMovement[] = {
    movement_fix_facing,
    big_step(DOWN),
    movement_remove_fixed_facing,
    movement_step_end,
};
const uint8_t TinTower1FEusineEntersMovement[] = {
    step(UP),
    step(UP),
    step(UP),
    turn_head(LEFT),
    movement_step_end,
};
const uint8_t TinTower1FEusineLeavesMovement[] = {
    step(DOWN),
    step(DOWN),
    step(DOWN),
    movement_step_end,
};
const uint8_t TinTower1FSage1EntersMovement[] = {
    step(UP),
    step(UP),
    step(LEFT),
    step(LEFT),
    turn_head(UP),
    movement_step_end,
};
const uint8_t TinTower1FSage2EntersMovement[] = {
    step(UP),
    step(UP),
    movement_step_end,
};
const uint8_t TinTower1FSage3EntersMovement[] = {
    step(UP),
    step(RIGHT),
    step(RIGHT),
    step(UP),
    movement_step_end,
};
const txt_cmd_s TinTower1FEusineSuicuneText[] = {
    text_start("EUSINE: Awesome!"
        t_line "Too awesome, even!"
        t_para "I've never seen a"
        t_line "battle that great."
        t_para "That was truly"
        t_line "inspiring to see."
        t_para "SUICUNE was tough,"
        t_line "but you were even"
        t_para "more incredible,"
        t_line "<PLAYER>."
        t_para "I heard SUICUNE's"
        t_line "mystic power"
        t_para "summons a rainbow-"
        t_line "colored #MON."
        t_para "Maybe, just maybe,"
        t_line "what went on today"
        t_para "will cause that"
        t_line "#MON to appear."
        t_para "I'm going to study"
        t_line "the legends more."
        t_para "Thanks for showing"
        t_line "me that fantastic"
        t_cont "battle."
        t_para "Later, <PLAYER>!"
        t_done )
};
const txt_cmd_s TinTower1FSage1Text[] = {
    text_start("According to"
        t_line "legend…"
        t_para "When the souls of"
        t_line "#MON and humans"
        t_para "commune, from the"
        t_line "heavens descends a"
        t_para "#MON of rainbow"
        t_line "colors…"
        t_para "Could it mean the"
        t_line "legendary #MON"
        t_para "are testing us"
        t_line "humans?"
        t_done )
};
const txt_cmd_s TinTower1FSage2Text[] = {
    text_start("When the BRASS"
        t_line "TOWER burned down,"
        t_para "three nameless"
        t_line "#MON were said"
        t_para "to have perished."
        t_line "It was tragic."
        t_para "However…"
        t_para "A rainbow-colored"
        t_line "#MON…"
        t_para "In other words…"
        t_para "HO-OH descended"
        t_line "from the sky and"
        t_para "gave new life to"
        t_line "the three #MON."
        t_para "They are…"
        t_para "SUICUNE, ENTEI and"
        t_line "RAIKOU."
        t_para "That is what they"
        t_line "say."
        t_done )
};
const txt_cmd_s TinTower1FSage3Text[] = {
    text_start("The two TOWERS are"
        t_line "said to have been"
        t_para "built to foster"
        t_line "friendship and"
        t_para "hope between #-"
        t_line "MON and people."
        t_para "That was 700 years"
        t_line "ago, but the ideal"
        t_para "still remains"
        t_line "important today."
        t_done )
};
const txt_cmd_s TinTower1FSage4Text1[] = {
    text_start("HO-OH appears to"
        t_line "have descended"
        t_para "upon this, the TIN"
        t_line "TOWER!"
        t_done )
};
const txt_cmd_s TinTower1FSage5Text1[] = {
    text_start("This will protect"
        t_line "you. Take it."
        t_done )
};
const txt_cmd_s TinTower1FSage5Text2[] = {
    text_start("Now, go."
        t_done )
};
const txt_cmd_s TinTower1FSage6Text1[] = {
    text_start("I believe you are"
        t_line "being tested."
        t_para "Free your mind"
        t_line "from uncertainty,"
        t_cont "and advance."
        t_done )
};
const txt_cmd_s TinTower1FEusineHoOhText[] = {
    text_start("I knew it."
        t_para "I knew you'd get"
        t_line "to see the #MON"
        t_para "of rainbow colors,"
        t_line "<PLAYER>."
        t_para "It happened just"
        t_line "as I envisioned."
        t_para "My research isn't"
        t_line "bad, I might say."
        t_para "I'm going to keep"
        t_line "studying #MON"
        t_para "to become a famous"
        t_line "#MANIAC!"
        t_done )
};
const txt_cmd_s TinTower1FSage4Text2[] = {
    text_start("The legendary"
        t_line "#MON are said"
        t_para "to embody three"
        t_line "powers…"
        t_para "The lightning that"
        t_line "struck the TOWER."
        t_para "The fire that"
        t_line "burned the TOWER."
        t_para "And the rain that"
        t_line "put out the fire…"
        t_done )
};
const txt_cmd_s TinTower1FSage5Text3[] = {
    text_start("When the legendary"
        t_line "#MON appeared…"
        t_para "They struck terror"
        t_line "in those who saw"
        t_cont "their rise."
        t_para "And…"
        t_para "Some even took to"
        t_line "futile attacks."
        t_para "The legendary"
        t_line "#MON, knowing"
        t_para "their own power,"
        t_line "fled, ignoring the"
        t_cont "frightened people."
        t_done )
};
const txt_cmd_s TinTower1FSage6Text2[] = {
    text_start("Of the legendary"
        t_line "#MON, SUICUNE"
        t_para "is said to be the"
        t_line "closest to HO-OH."
        t_para "I hear there may"
        t_line "also be a link to"
        t_para "#MON known as"
        t_line "UNOWN."
        t_para "The #MON UNOWN"
        t_line "must be sharing a"
        t_para "cooperative bond"
        t_line "with SUICUNE."
        t_done )
    //db(0, 0) // filler
};
