#include "../constants.h"
#include "../util/scripting.h"
#include "VioletCity.h"
//// EVENTS
enum {
    VIOLETCITY_EARL = 2,
    VIOLETCITY_LASS,
    VIOLETCITY_SUPER_NERD,
    VIOLETCITY_GRAMPS,
    VIOLETCITY_YOUNGSTER,
    VIOLETCITY_FRUIT_TREE,
    VIOLETCITY_POKE_BALL1,
    VIOLETCITY_POKE_BALL2,
};

const Script_fn_t VioletCity_SceneScripts[] = {
};

const struct MapCallback VioletCity_MapCallbacks[] = {
    map_callback(MAPCALLBACK_NEWMAP, VioletCity_MapScripts_FlyPoint),
};

const struct MapScripts VioletCity_MapScripts = {
    .scene_script_count = lengthof(VioletCity_SceneScripts),
    .scene_scripts = VioletCity_SceneScripts,

    .callback_count = lengthof(VioletCity_MapCallbacks),
    .callbacks = VioletCity_MapCallbacks,
};

static const struct CoordEvent VioletCity_CoordEvents[] = {
};

static const struct BGEvent VioletCity_BGEvents[] = {
    bg_event(24, 20, BGEVENT_READ, &VioletCitySign),
    bg_event(15, 17, BGEVENT_READ, &VioletGymSign),
    bg_event(24, 8, BGEVENT_READ, &SproutTowerSign),
    bg_event(27, 17, BGEVENT_READ, &EarlsPokemonAcademySign),
    bg_event(32, 25, BGEVENT_READ, &VioletCityPokecenterSign),
    bg_event(10, 17, BGEVENT_READ, &VioletCityMartSign),
    bg_event(37, 14, BGEVENT_ITEM, &VioletCityHiddenHyperPotion),
};

static const struct WarpEventData VioletCity_WarpEvents[] = {
    warp_event(9, 17, VIOLET_MART, 2),
    warp_event(18, 17, VIOLET_GYM, 1),
    warp_event(30, 17, EARLS_POKEMON_ACADEMY, 1),
    warp_event(3, 15, VIOLET_NICKNAME_SPEECH_HOUSE, 1),
    warp_event(31, 25, VIOLET_POKECENTER_1F, 1),
    warp_event(21, 29, VIOLET_KYLES_HOUSE, 1),
    warp_event(23, 5, SPROUT_TOWER_1F, 1),
    warp_event(39, 24, ROUTE_31_VIOLET_GATE, 1),
    warp_event(39, 25, ROUTE_31_VIOLET_GATE, 2),
};

static const struct ObjEvent VioletCity_ObjectEvents[] = {
    object_event(13, 16, SPRITE_FISHER, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &VioletCityEarlScript, EVENT_VIOLET_CITY_EARL),
    object_event(28, 28, SPRITE_LASS, SPRITEMOVEDATA_WANDER, 2, 2, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &VioletCityLassScript, -1),
    object_event(24, 14, SPRITE_SUPER_NERD, SPRITEMOVEDATA_WANDER, 1, 2, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &VioletCitySuperNerdScript, -1),
    object_event(17, 20, SPRITE_GRAMPS, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &VioletCityGrampsScript, -1),
    object_event(5, 18, SPRITE_YOUNGSTER, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &VioletCityYoungsterScript, -1),
    object_event(14, 29, SPRITE_FRUIT_TREE, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &VioletCityFruitTree, -1),
    object_event(4, 1, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &VioletCityPPUp, EVENT_VIOLET_CITY_PP_UP),
    object_event(35, 5, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &VioletCityRareCandy, EVENT_VIOLET_CITY_RARE_CANDY),
};

const struct MapEvents VioletCity_MapEvents = {
    .warp_event_count = lengthof(VioletCity_WarpEvents),
    .warp_events = VioletCity_WarpEvents,

    .coord_event_count = lengthof(VioletCity_CoordEvents),
    .coord_events = VioletCity_CoordEvents,

    .bg_event_count = lengthof(VioletCity_BGEvents),
    .bg_events = VioletCity_BGEvents,

    .obj_event_count = lengthof(VioletCity_ObjectEvents),
    .obj_events = VioletCity_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "VioletCity.h"

bool VioletCity_MapScripts_FlyPoint(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_FLYPOINT_VIOLET)
    s_endcallback
    SCRIPT_END
}
bool VioletCityEarlScript(script_s* s) {
    SCRIPT_BEGIN
    applymovement(VIOLETCITY_EARL, VioletCitySpinningEarl_MovementData)
    faceplayer
    opentext
    writetext(Text_EarlAsksIfYouBeatFalkner)
    yesorno
    iffalse(FollowEarl)
PointlessJump:
    writetext(Text_VeryNiceIndeed)
    waitbutton
    closetext
    s_end
FollowEarl:
    writetext(Text_FollowEarl)
    waitbutton
    closetext
    playmusic(MUSIC_SHOW_ME_AROUND)
    follow(VIOLETCITY_EARL, PLAYER)
    applymovement(VIOLETCITY_EARL, VioletCityFollowEarl_MovementData)
    turnobject(PLAYER, UP)
    applymovement(VIOLETCITY_EARL, VioletCitySpinningEarl_MovementData)
    stopfollow
    special(RestartMapMusic)
    opentext
    writetext(Text_HereTeacherIAm)
    waitbutton
    closetext
    applymovement(VIOLETCITY_EARL, VioletCitySpinningEarl_MovementData)
    applymovement(VIOLETCITY_EARL, VioletCityFinishFollowEarl_MovementData)
    playsound(SFX_ENTER_DOOR)
    disappear(VIOLETCITY_EARL)
    clearevent(EVENT_EARLS_ACADEMY_EARL)
    waitsfx
    s_end
    SCRIPT_END
}
bool VioletCityLassScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(VioletCityLassText)
    SCRIPT_END
}
bool VioletCitySuperNerdScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(VioletCitySuperNerdText)
    SCRIPT_END
}
bool VioletCityGrampsScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(VioletCityGrampsText)
    SCRIPT_END
}
bool VioletCityYoungsterScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(VioletCityYoungsterText)
    SCRIPT_END
}
bool VioletCitySign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(VioletCitySignText)
    SCRIPT_END
}
bool VioletGymSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(VioletGymSignText)
    SCRIPT_END
}
bool SproutTowerSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(SproutTowerSignText)
    SCRIPT_END
}
bool EarlsPokemonAcademySign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(EarlsPokemonAcademySignText)
    SCRIPT_END
}
bool VioletCityPokecenterSign(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PokecenterSignScript)
    SCRIPT_END
}
bool VioletCityMartSign(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(MartSignScript)
    SCRIPT_END
}
const struct ItemBall VioletCityPPUp = {PP_UP, 1};
const struct ItemBall VioletCityRareCandy = {RARE_CANDY, 1};
bool VioletCityFruitTree(script_s* s) {
    SCRIPT_BEGIN
    fruittree(FRUITTREE_VIOLET_CITY)
    SCRIPT_END
}
const struct HiddenItem VioletCityHiddenHyperPotion = {HYPER_POTION, EVENT_VIOLET_CITY_HIDDEN_HYPER_POTION};
const uint8_t VioletCityFollowEarl_MovementData[] = {
    big_step(DOWN),
    big_step(DOWN),
    turn_head(DOWN),
    turn_head(LEFT),
    turn_head(UP),
    turn_head(RIGHT),
    turn_head(DOWN),
    turn_head(LEFT),
    turn_head(UP),
    turn_head(RIGHT),
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(RIGHT),
    turn_head(RIGHT),
    turn_head(DOWN),
    turn_head(LEFT),
    turn_head(UP),
    turn_head(RIGHT),
    turn_head(DOWN),
    turn_head(LEFT),
    turn_head(UP),
    turn_head(RIGHT),
    turn_head(DOWN),
    big_step(DOWN),
    turn_head(DOWN),
    turn_head(LEFT),
    turn_head(UP),
    turn_head(RIGHT),
    turn_head(DOWN),
    turn_head(LEFT),
    turn_head(UP),
    turn_head(RIGHT),
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(RIGHT),
    turn_head(RIGHT),
    turn_head(DOWN),
    turn_head(LEFT),
    turn_head(UP),
    turn_head(RIGHT),
    turn_head(DOWN),
    turn_head(LEFT),
    turn_head(UP),
    big_step(UP),
    turn_head(DOWN),
    movement_step_end,
};
const uint8_t VioletCityFinishFollowEarl_MovementData[] = {
    step(UP),
    movement_step_end,
};
const uint8_t VioletCitySpinningEarl_MovementData[] = {
    turn_head(DOWN),
    turn_head(LEFT),
    turn_head(UP),
    turn_head(RIGHT),
    turn_head(DOWN),
    turn_head(LEFT),
    turn_head(UP),
    turn_head(RIGHT),
    turn_head(DOWN),
    turn_head(LEFT),
    turn_head(UP),
    turn_head(RIGHT),
    turn_head(DOWN),
    movement_step_end,
};
const txt_cmd_s Text_EarlAsksIfYouBeatFalkner[] = {
    text_start("Hello!"
        t_line "You are trainer?"
        t_para "Battle GYM LEADER,"
        t_line "win you did?"
        t_done )
};
const txt_cmd_s Text_VeryNiceIndeed[] = {
    text_start("Ooh, la la!"
        t_line "Very indeed nice!"
        t_done )
};
const txt_cmd_s Text_FollowEarl[] = {
    text_start("Is that so? Then"
        t_line "study shall you!"
        t_cont "Follow me!"
        t_done )
};
const txt_cmd_s Text_HereTeacherIAm[] = {
    text_start("Here, teacher I"
        t_line "am. Good it is"
        t_cont "you study here!"
        t_done )
};
const txt_cmd_s VioletCityLassText[] = {
    text_start("Ghosts are rumored"
        t_line "to appear in"
        t_cont "SPROUT TOWER."
        t_para "They said normal-"
        t_line "type #MON moves"
        t_para "had no effect on"
        t_line "ghosts."
        t_done )
};
const txt_cmd_s VioletCitySuperNerdText[] = {
    text_start("Hey, you're a"
        t_line "#MON trainer?"
        t_para "If you beat the"
        t_line "GYM LEADER here,"
        t_para "you'll be ready"
        t_line "for prime time!"
        t_done )
};
const txt_cmd_s VioletCityGrampsText[] = {
    text_start("FALKNER, from the"
        t_line "VIOLET #MON"
        t_para "GYM, is a fine"
        t_line "trainer!"
        t_para "He inherited his"
        t_line "father's gym and"
        t_para "has done a great"
        t_line "job with it."
        t_done )
};
const txt_cmd_s VioletCityYoungsterText[] = {
    text_start("I saw a wiggly"
        t_line "tree up ahead!"
        t_para "If you touch it,"
        t_line "it squirms and"
        t_cont "dances! Cool!"
        t_done )
};
const txt_cmd_s VioletCitySignText[] = {
    text_start("VIOLET CITY"
        t_para "The City of"
        t_line "Nostalgic Scents"
        t_done )
};
const txt_cmd_s VioletGymSignText[] = {
    text_start("VIOLET CITY"
        t_line "#MON GYM"
        t_cont "LEADER: FALKNER"
        t_para "The Elegant Master"
        t_line "of Flying #MON"
        t_done )
};
const txt_cmd_s SproutTowerSignText[] = {
    text_start("SPROUT TOWER"
        t_para "Experience the"
        t_line "Way of #MON"
        t_done )
};
const txt_cmd_s EarlsPokemonAcademySignText[] = {
    text_start("EARL'S #MON"
        t_line "ACADEMY"
        t_done )
    //db(0, 0) // filler
};
