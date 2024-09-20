#include "../constants.h"
#include "../util/scripting.h"
#include "CeladonCafe.h"
//// EVENTS
enum {
    CELADONCAFE_SUPER_NERD = 2,
    CELADONCAFE_FISHER1,
    CELADONCAFE_FISHER2,
    CELADONCAFE_FISHER3,
    CELADONCAFE_TEACHER,
};

const Script_fn_t CeladonCafe_SceneScripts[] = {
    0,
};

const struct MapCallback CeladonCafe_MapCallbacks[] = {
    0,
};

const struct MapScripts CeladonCafe_MapScripts = {
    .scene_script_count = 0, // lengthof(CeladonCafe_SceneScripts),
    .scene_scripts = CeladonCafe_SceneScripts,

    .callback_count = 0, // lengthof(CeladonCafe_MapCallbacks),
    .callbacks = CeladonCafe_MapCallbacks,
};

static const struct CoordEvent CeladonCafe_CoordEvents[] = {
    0,
};

static const struct BGEvent CeladonCafe_BGEvents[] = {
    bg_event(5, 0, BGEVENT_READ, &EatathonContestPoster),
    bg_event(7, 1, BGEVENT_READ, &CeladonCafeTrashcan),
};

static const struct WarpEventData CeladonCafe_WarpEvents[] = {
    warp_event(6, 7, CELADON_CITY, 9),
    warp_event(7, 7, CELADON_CITY, 9),
};

static const struct ObjEvent CeladonCafe_ObjectEvents[] = {
    object_event(9, 3, SPRITE_SUPER_NERD, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, &CeladonCafeChef, -1),
    object_event(4, 6, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &CeladonCafeFisher1, -1),
    object_event(1, 7, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &CeladonCafeFisher2, -1),
    object_event(1, 2, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &CeladonCafeFisher3, -1),
    object_event(4, 3, SPRITE_TEACHER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &CeladonCafeTeacher, -1),
};

const struct MapEvents CeladonCafe_MapEvents = {
    .warp_event_count = lengthof(CeladonCafe_WarpEvents),
    .warp_events = CeladonCafe_WarpEvents,

    .coord_event_count = 0, // lengthof(CeladonCafe_CoordEvents),
    .coord_events = CeladonCafe_CoordEvents,

    .bg_event_count = lengthof(CeladonCafe_BGEvents),
    .bg_events = CeladonCafe_BGEvents,

    .obj_event_count = lengthof(CeladonCafe_ObjectEvents),
    .obj_events = CeladonCafe_ObjectEvents,
};

//// CODE

bool CeladonCafeChef(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(ChefText_Eatathon)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool CeladonCafeFisher1(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(Fisher1Text_Snarfle)
    waitbutton
    closetext
    faceplayer
    opentext
    writetext(Fisher1Text_Concentration)
    waitbutton
    closetext
    turnobject(CELADONCAFE_FISHER1, LEFT)
    s_end
    SCRIPT_END
}
bool CeladonCafeFisher2(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(Fisher2Text_GulpChew)
    waitbutton
    closetext
    faceplayer
    opentext
    writetext(Fisher2Text_Quantity)
    waitbutton
    closetext
    turnobject(CELADONCAFE_FISHER2, RIGHT)
    s_end
    SCRIPT_END
}
bool CeladonCafeFisher3(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(Fisher3Text_MunchMunch)
    waitbutton
    closetext
    faceplayer
    opentext
    writetext(Fisher3Text_GoldenrodIsBest)
    waitbutton
    closetext
    turnobject(CELADONCAFE_FISHER3, RIGHT)
    s_end
    SCRIPT_END
}
bool CeladonCafeTeacher(script_s* s) {
    SCRIPT_BEGIN
    checkitem(COIN_CASE)
    iftrue(HasCoinCase)
    opentext
    writetext(TeacherText_CrunchCrunch)
    waitbutton
    closetext
    faceplayer
    opentext
    writetext(TeacherText_NoCoinCase)
    waitbutton
    closetext
    turnobject(CELADONCAFE_TEACHER, LEFT)
    s_end
HasCoinCase:
    opentext
    writetext(TeacherText_KeepEating)
    waitbutton
    closetext
    turnobject(CELADONCAFE_TEACHER, RIGHT)
    opentext
    writetext(TeacherText_MoreChef)
    waitbutton
    closetext
    turnobject(CELADONCAFE_TEACHER, LEFT)
    s_end
    SCRIPT_END
}
bool EatathonContestPoster(script_s* s) {
    SCRIPT_BEGIN
    jumptext(EatathonContestPosterText)
    SCRIPT_END
}
bool CeladonCafeTrashcan(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_FOUND_LEFTOVERS_IN_CELADON_CAFE)
    iftrue(TrashEmpty)
    giveitem(LEFTOVERS, 1)
    iffalse(PackFull)
    opentext
    getitemname(STRING_BUFFER_3, LEFTOVERS)
    writetext(FoundLeftoversText)
    playsound(SFX_ITEM)
    waitsfx
    itemnotify
    closetext
    setevent(EVENT_FOUND_LEFTOVERS_IN_CELADON_CAFE)
    s_end
PackFull:
    opentext
    getitemname(STRING_BUFFER_3, LEFTOVERS)
    writetext(FoundLeftoversText)
    promptbutton
    writetext(NoRoomForLeftoversText)
    waitbutton
    closetext
    s_end
TrashEmpty:
    jumpstd(TrashCanScript)
    SCRIPT_END
}
const txt_cmd_s ChefText_Eatathon[] = {
    text_start("Hi!"
        t_para "We're holding an"
        t_line "eatathon contest."
        t_para "We can't serve you"
        t_line "right now. Sorry."
        t_done )
};
const txt_cmd_s Fisher1Text_Snarfle[] = {
    text_start("…Snarfle, chew…"
        t_done )
};
const txt_cmd_s Fisher1Text_Concentration[] = {
    text_start("Don't talk to me!"
        t_para "You'll break my"
        t_line "concentration!"
        t_done )
};
const txt_cmd_s Fisher2Text_GulpChew[] = {
    text_start("…Gulp… Chew…"
        t_done )
};
const txt_cmd_s Fisher2Text_Quantity[] = {
    text_start("I take quantity"
        t_line "over quality!"
        t_para "I'm happy when I'm"
        t_line "full!"
        t_done )
};
const txt_cmd_s Fisher3Text_MunchMunch[] = {
    text_start("Munch, munch…"
        t_done )
};
const txt_cmd_s Fisher3Text_GoldenrodIsBest[] = {
    text_start("The food is good"
        t_line "here, but GOLDEN-"
        t_cont "ROD has the best"
        t_cont "food anywhere."
        t_done )
};
const txt_cmd_s TeacherText_CrunchCrunch[] = {
    text_start("Crunch… Crunch…"
        t_done )
};
const txt_cmd_s TeacherText_NoCoinCase[] = {
    text_start("Nobody here will"
        t_line "give you a COIN"
        t_para "CASE. You should"
        t_line "look in JOHTO."
        t_done )
};
const txt_cmd_s TeacherText_KeepEating[] = {
    text_start("Crunch… Crunch…"
        t_para "I can keep eating!"
        t_done )
};
const txt_cmd_s TeacherText_MoreChef[] = {
    text_start("More, CHEF!"
        t_done )
};
const txt_cmd_s EatathonContestPosterText[] = {
    text_start("Eatathon Contest!"
        t_line "No time limit!"
        t_para "A battle without"
        t_line "end! The biggest"
        t_para "muncher gets it"
        t_line "all for free!"
        t_done )
};
const txt_cmd_s FoundLeftoversText[] = {
    text_start("<PLAYER> found"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("!"
        t_done )
};
const txt_cmd_s NoRoomForLeftoversText[] = {
    text_start("But <PLAYER> can't"
        t_line "hold another item…"
        t_done )
    //db(0, 0) // filler
};
