#include "../constants.h"
#include "../util/scripting.h"
#include "CeladonCity.h"
//// EVENTS
enum {
    CELADONCITY_FISHER = 2,
    CELADONCITY_POLIWAG,
    CELADONCITY_TEACHER1,
    CELADONCITY_GRAMPS1,
    CELADONCITY_GRAMPS2,
    CELADONCITY_YOUNGSTER1,
    CELADONCITY_YOUNGSTER2,
    CELADONCITY_TEACHER2,
    CELADONCITY_LASS,
};

const Script_fn_t CeladonCity_SceneScripts[] = {
    0,
};

const struct MapCallback CeladonCity_MapCallbacks[] = {
    map_callback(MAPCALLBACK_NEWMAP, CeladonCity_MapScripts_FlyPoint),
};

const struct MapScripts CeladonCity_MapScripts = {
    .scene_script_count = 0, // lengthof(CeladonCity_SceneScripts),
    .scene_scripts = CeladonCity_SceneScripts,

    .callback_count = lengthof(CeladonCity_MapCallbacks),
    .callbacks = CeladonCity_MapCallbacks,
};

static const struct CoordEvent CeladonCity_CoordEvents[] = {
    0,
};

static const struct BGEvent CeladonCity_BGEvents[] = {
    bg_event(23, 21, BGEVENT_READ, &CeladonCitySign),
    bg_event(11, 31, BGEVENT_READ, &CeladonGymSign),
    bg_event(6, 9, BGEVENT_READ, &CeladonCityDeptStoreSign),
    bg_event(13, 9, BGEVENT_READ, &CeladonCityMansionSign),
    bg_event(19, 21, BGEVENT_READ, &CeladonCityGameCornerSign),
    bg_event(29, 21, BGEVENT_READ, &CeladonCityTrainerTips),
    bg_event(30, 9, BGEVENT_READ, &CeladonCityPokecenterSign),
    bg_event(37, 21, BGEVENT_ITEM, &CeladonCityHiddenPpUp),
};

static const struct WarpEventData CeladonCity_WarpEvents[] = {
    warp_event(4, 9, CELADON_DEPT_STORE_1F, 1),
    warp_event(16, 9, CELADON_MANSION_1F, 1),
    warp_event(16, 3, CELADON_MANSION_1F, 3),
    warp_event(17, 3, CELADON_MANSION_1F, 3),
    warp_event(29, 9, CELADON_POKECENTER_1F, 1),
    warp_event(18, 19, CELADON_GAME_CORNER, 1),
    warp_event(23, 19, CELADON_GAME_CORNER_PRIZE_ROOM, 1),
    warp_event(10, 29, CELADON_GYM, 1),
    warp_event(25, 29, CELADON_CAFE, 1),
};

static const struct ObjEvent CeladonCity_ObjectEvents[] = {
    object_event(26, 11, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &CeladonCityFisherScript, -1),
    object_event(27, 11, SPRITE_POLIWAG, SPRITEMOVEDATA_POKEMON, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &CeladonCityPoliwrath, -1),
    object_event(20, 24, SPRITE_TEACHER, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 2, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &CeladonCityTeacher1Script, -1),
    object_event(14, 16, SPRITE_GRAMPS, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, &CeladonCityGramps1Script, -1),
    object_event(8, 31, SPRITE_GRAMPS, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &CeladonCityGramps2Script, -1),
    object_event(18, 13, SPRITE_YOUNGSTER, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 2, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &CeladonCityYoungster1Script, -1),
    object_event(24, 33, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &CeladonCityYoungster2Script, -1),
    object_event(6, 14, SPRITE_TEACHER, SPRITEMOVEDATA_WANDER, 2, 2, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &CeladonCityTeacher2Script, -1),
    object_event(7, 22, SPRITE_LASS, SPRITEMOVEDATA_WALK_UP_DOWN, 0, 2, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &CeladonCityLassScript, -1),
};

const struct MapEvents CeladonCity_MapEvents = {
    .warp_event_count = lengthof(CeladonCity_WarpEvents),
    .warp_events = CeladonCity_WarpEvents,

    .coord_event_count = 0, // lengthof(CeladonCity_CoordEvents),
    .coord_events = CeladonCity_CoordEvents,

    .bg_event_count = lengthof(CeladonCity_BGEvents),
    .bg_events = CeladonCity_BGEvents,

    .obj_event_count = lengthof(CeladonCity_ObjectEvents),
    .obj_events = CeladonCity_ObjectEvents,
};

//// CODE

bool CeladonCity_MapScripts_FlyPoint(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_FLYPOINT_CELADON)
    s_endcallback
    SCRIPT_END
}
bool CeladonCityFisherScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CeladonCityFisherText)
    SCRIPT_END
}
bool CeladonCityPoliwrath(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(CeladonCityPoliwrathText)
    playcry(POLIWRATH)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool CeladonCityTeacher1Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CeladonCityTeacher1Text)
    SCRIPT_END
}
bool CeladonCityGramps1Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CeladonCityGramps1Text)
    SCRIPT_END
}
bool CeladonCityGramps2Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CeladonCityGramps2Text)
    SCRIPT_END
}
bool CeladonCityYoungster1Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CeladonCityYoungster1Text)
    SCRIPT_END
}
bool CeladonCityYoungster2Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CeladonCityYoungster2Text)
    SCRIPT_END
}
bool CeladonCityTeacher2Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CeladonCityTeacher2Text)
    SCRIPT_END
}
bool CeladonCityLassScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CeladonCityLassText)
    SCRIPT_END
}
bool CeladonCitySign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(CeladonCitySignText)
    SCRIPT_END
}
bool CeladonGymSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(CeladonGymSignText)
    SCRIPT_END
}
bool CeladonCityDeptStoreSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(CeladonCityDeptStoreSignText)
    SCRIPT_END
}
bool CeladonCityMansionSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(CeladonCityMansionSignText)
    SCRIPT_END
}
bool CeladonCityGameCornerSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(CeladonCityGameCornerSignText)
    SCRIPT_END
}
bool CeladonCityTrainerTips(script_s* s) {
    SCRIPT_BEGIN
    jumptext(CeladonCityTrainerTipsText)
    SCRIPT_END
}
bool CeladonCityPokecenterSign(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PokecenterSignScript)
    SCRIPT_END
}
const struct HiddenItem CeladonCityHiddenPpUp = {PP_UP, EVENT_CELADON_CITY_HIDDEN_PP_UP};
const txt_cmd_s CeladonCityFisherText[] = {
    text_start("This POLIWRATH is"
        t_line "my partner."
        t_para "I wonder if it'll"
        t_line "ever evolve into a"
        t_cont "frog #MON."
        t_done )
};
const txt_cmd_s CeladonCityPoliwrathText[] = {
    text_start("POLIWRATH: Croak!"
        t_done )
};
const txt_cmd_s CeladonCityTeacher1Text[] = {
#if defined(_CRYSTAL_AU)
    text_start("I lost at the"
        t_line "machines."
        t_done )
#else
    text_start("I lost at the slot"
        t_line "machines again…"
        t_para "We girls also play"
        t_line "the slots now."
        t_para "You should check"
        t_line "them out too."
        t_done )
#endif
};
const txt_cmd_s CeladonCityGramps1Text[] = {
    text_start("GRIMER have been"
        t_line "appearing lately."
        t_para "See that pond out"
        t_line "in front of the"
        t_para "house? GRIMER live"
        t_line "there now."
        t_para "Where did they"
        t_line "come from? This is"
        t_cont "a serious problem…"
        t_done )
};
const txt_cmd_s CeladonCityGramps2Text[] = {
    text_start("Nihihi! This GYM"
        t_line "is great! Only"
        t_para "girls are allowed"
        t_line "here!"
        t_done )
};
const txt_cmd_s CeladonCityYoungster1Text[] = {
    text_start("Want to know a"
        t_line "secret?"
        t_para "CELADON MANSION"
        t_line "has a hidden back"
        t_cont "door."
        t_done )
};
const txt_cmd_s CeladonCityYoungster2Text[] = {
    text_start("They're holding an"
        t_line "eating contest at"
        t_cont "the restaurant."
        t_para "Just watching them"
        t_line "go at it makes me"
        t_cont "feel bloated…"
        t_done )
};
const txt_cmd_s CeladonCityTeacher2Text[] = {
    text_start("CELADON DEPT.STORE"
        t_line "has the biggest"
        t_para "and best selection"
        t_line "of merchandise."
        t_para "If you can't get"
        t_line "it there, you"
        t_para "can't get it any-"
        t_line "where."
        t_para "Gee… I sound like"
        t_line "a sales clerk."
        t_done )
};
const txt_cmd_s CeladonCityLassText_Mobile[] = {
    text_start("I love being"
        t_line "surrounded by tall"
        t_cont "buildings!"
        t_para "Isn't it true that"
        t_line "GOLDENROD #MON"
        t_para "CENTER was made"
        t_line "much, much bigger?"
        t_para "That is so neat!"
        t_line "I wish we had a"
        t_para "place like that in"
        t_line "KANTO…"
        t_done )
};
const txt_cmd_s CeladonCityLassText[] = {
    text_start("Looking at the"
        t_line "ground while I was"
        t_para "walking made me"
        t_line "dizzy."
        t_done )
};
const txt_cmd_s CeladonCitySignText[] = {
    text_start("CELADON CITY"
        t_para "The City of"
        t_line "Rainbow Dreams"
        t_done )
};
const txt_cmd_s CeladonGymSignText[] = {
    text_start("CELADON CITY"
        t_line "#MON GYM"
        t_cont "LEADER: ERIKA"
        t_para "The Nature-Loving"
        t_line "Princess"
        t_done )
};
const txt_cmd_s CeladonCityDeptStoreSignText[] = {
    text_start("Find What You"
        t_line "Need at CELADON"
        t_cont "DEPT.STORE!"
        t_done )
};
const txt_cmd_s CeladonCityMansionSignText[] = {
    text_start("CELADON MANSION"
        t_done )
};
const txt_cmd_s CeladonCityGameCornerSignText[] = {
#if defined(_CRYSTAL_AU)
    text_start("The Game Area for"
        t_line "Grown-ups--CELADON"
        t_cont "GAME CORNER"
        t_done )
#else
    text_start("The Playground for"
        t_line "Everybody--CELADON"
        t_cont "GAME CORNER"
        t_done )
#endif
};
const txt_cmd_s CeladonCityTrainerTipsText[] = {
    text_start("TRAINER TIPS"
        t_para "GUARD SPEC."
        t_line "protects #MON"
        t_para "against SPECIAL"
        t_line "attacks such as"
        t_cont "fire and water."
        t_para "Get your items at"
        t_line "CELADON DEPT."
        t_cont "STORE!"
        t_done )
    //db(0, 0) // filler
};
