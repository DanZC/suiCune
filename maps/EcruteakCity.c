#include "../constants.h"
#include "../util/scripting.h"
#include "EcruteakCity.h"
//// EVENTS
enum {
    ECRUTEAKCITY_GRAMPS1 = 2,
    ECRUTEAKCITY_GRAMPS2,
    ECRUTEAKCITY_LASS1,
    ECRUTEAKCITY_LASS2,
    ECRUTEAKCITY_FISHER,
    ECRUTEAKCITY_YOUNGSTER,
    ECRUTEAKCITY_GRAMPS3,
};

const Script_fn_t EcruteakCity_SceneScripts[] = {
    0,
};

const struct MapCallback EcruteakCity_MapCallbacks[] = {
    map_callback(MAPCALLBACK_NEWMAP, EcruteakCity_MapScripts_FlyPoint),
};

const struct MapScripts EcruteakCity_MapScripts = {
    .scene_script_count = 0, // lengthof(EcruteakCity_SceneScripts),
    .scene_scripts = EcruteakCity_SceneScripts,

    .callback_count = lengthof(EcruteakCity_MapCallbacks),
    .callbacks = EcruteakCity_MapCallbacks,
};

static const struct CoordEvent EcruteakCity_CoordEvents[] = {
    0,
};

static const struct BGEvent EcruteakCity_BGEvents[] = {
    bg_event(15, 21, BGEVENT_READ, &EcruteakCitySign),
    bg_event(38, 10, BGEVENT_READ, &TinTowerSign),
    bg_event(8, 28, BGEVENT_READ, &EcruteakGymSign),
    bg_event(21, 21, BGEVENT_READ, &EcruteakDanceTheaterSign),
    bg_event(2, 10, BGEVENT_READ, &BurnedTowerSign),
    bg_event(24, 27, BGEVENT_READ, &EcruteakCityPokecenterSign),
    bg_event(30, 21, BGEVENT_READ, &EcruteakCityMartSign),
    bg_event(23, 14, BGEVENT_ITEM, &EcruteakCityHiddenHyperPotion),
};

static const struct WarpEventData EcruteakCity_WarpEvents[] = {
    warp_event(35, 26, ROUTE_42_ECRUTEAK_GATE, 1),
    warp_event(35, 27, ROUTE_42_ECRUTEAK_GATE, 2),
    warp_event(18, 11, ECRUTEAK_TIN_TOWER_ENTRANCE, 1),
    warp_event(20, 2, WISE_TRIOS_ROOM, 1),
    warp_event(20, 3, WISE_TRIOS_ROOM, 2),
    warp_event(23, 27, ECRUTEAK_POKECENTER_1F, 1),
    warp_event(5, 21, ECRUTEAK_LUGIA_SPEECH_HOUSE, 1),
    warp_event(23, 21, DANCE_THEATRE, 1),
    warp_event(29, 21, ECRUTEAK_MART, 2),
    warp_event(6, 27, ECRUTEAK_GYM, 1),
    warp_event(13, 27, ECRUTEAK_ITEMFINDER_HOUSE, 1),
    warp_event(37, 7, TIN_TOWER_1F, 1),
    warp_event(5, 5, BURNED_TOWER_1F, 1),
    warp_event(0, 18, ROUTE_38_ECRUTEAK_GATE, 3),
    warp_event(0, 19, ROUTE_38_ECRUTEAK_GATE, 4),
};

static const struct ObjEvent EcruteakCity_ObjectEvents[] = {
    object_event(18, 15, SPRITE_GRAMPS, SPRITEMOVEDATA_WANDER, 1, 1, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &EcruteakCityGramps1Script, -1),
    object_event(20, 21, SPRITE_GRAMPS, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &EcruteakCityGramps2Script, -1),
    object_event(21, 29, SPRITE_LASS, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 2, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &EcruteakCityLass1Script, -1),
    object_event(3, 9, SPRITE_LASS, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &EcruteakCityLass2Script, -1),
    object_event(9, 22, SPRITE_FISHER, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &EcruteakCityFisherScript, -1),
    object_event(10, 14, SPRITE_YOUNGSTER, SPRITEMOVEDATA_WANDER, 1, 1, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &EcruteakCityYoungsterScript, -1),
    object_event(3, 7, SPRITE_GRAMPS, SPRITEMOVEDATA_WANDER, 1, 1, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &EcruteakCityGramps3Script, EVENT_ECRUTEAK_CITY_GRAMPS),
};

const struct MapEvents EcruteakCity_MapEvents = {
    .warp_event_count = lengthof(EcruteakCity_WarpEvents),
    .warp_events = EcruteakCity_WarpEvents,

    .coord_event_count = 0, // lengthof(EcruteakCity_CoordEvents),
    .coord_events = EcruteakCity_CoordEvents,

    .bg_event_count = lengthof(EcruteakCity_BGEvents),
    .bg_events = EcruteakCity_BGEvents,

    .obj_event_count = lengthof(EcruteakCity_ObjectEvents),
    .obj_events = EcruteakCity_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "EcruteakCity.h"

bool EcruteakCity_MapScripts_FlyPoint(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_FLYPOINT_ECRUTEAK)
    s_endcallback
    SCRIPT_END
}
bool EcruteakCityGramps1Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(EcruteakCityGramps1Text)
    SCRIPT_END
}
bool EcruteakCityGramps2Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(EcruteakCityGramps2Text)
    SCRIPT_END
}
bool EcruteakCityGramps3Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(EcruteakCityGramps3Text)
    SCRIPT_END
}
bool EcruteakCityLass1Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(EcruteakCityLass1Text)
    SCRIPT_END
}
bool EcruteakCityLass2Script(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_RELEASED_THE_BEASTS)
    iftrue(ReleasedBeasts)
    writetext(EcruteakCityLass2Text)
    waitbutton
    closetext
    s_end
ReleasedBeasts:
    writetext(EcruteakCityLass2Text_ReleasedBeasts)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool EcruteakCityFisherScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_JASMINE_RETURNED_TO_GYM)
    iftrue(JasmineReturned)
    writetext(EcruteakCityFisherText)
    waitbutton
    closetext
    s_end
JasmineReturned:
    writetext(EcruteakCityFisherText_JasmineReturned)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool EcruteakCityYoungsterScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(EcruteakCityYoungsterText)
    SCRIPT_END
}
bool EcruteakCitySign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(EcruteakCitySignText)
    SCRIPT_END
}
bool TinTowerSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(TinTowerSignText)
    SCRIPT_END
}
bool EcruteakGymSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(EcruteakGymSignText)
    SCRIPT_END
}
bool EcruteakDanceTheaterSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(EcruteakDanceTheaterSignText)
    SCRIPT_END
}
bool BurnedTowerSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(BurnedTowerSignText)
    SCRIPT_END
}
bool EcruteakCityPokecenterSign(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PokecenterSignScript)
    SCRIPT_END
}
bool EcruteakCityMartSign(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(MartSignScript)
    SCRIPT_END
}
const struct HiddenItem EcruteakCityHiddenHyperPotion = {HYPER_POTION, EVENT_ECRUTEAK_CITY_HIDDEN_HYPER_POTION};
const txt_cmd_s UnusedMissingDaughterText[] = {
    text_start("Oh, no. Oh, no…"
        t_para "My daughter is"
        t_line "missing."
        t_para "No… She couldn't"
        t_line "have gone to the"
        t_cont "BURNED TOWER."
        t_para "I told her not to"
        t_line "go near it…"
        t_para "People seem to"
        t_line "disappear there…"
        t_para "Oh, what should I"
        t_line "do…?"
        t_done )
};
const txt_cmd_s EcruteakCityGramps1Text[] = {
    text_start("ECRUTEAK used to"
        t_line "have two towers:"
        t_para "one each in the"
        t_line "east and west."
        t_done )
};
const txt_cmd_s EcruteakCityGramps2Text[] = {
    text_start("Ah, child."
        t_line "Have you learned"
        t_para "to dance like the"
        t_line "KIMONO GIRLS?"
        t_para "If you go to their"
        t_line "DANCE THEATER, an"
        t_para "odd old man will"
        t_line "give you something"
        t_cont "nice, I hear."
        t_done )
};
const txt_cmd_s EcruteakCityLass1Text[] = {
    text_start("I'm going to prac-"
        t_line "tice at the DANCE"
        t_para "THEATER. Care to"
        t_line "join me?"
        t_done )
};
const txt_cmd_s EcruteakCityLass2Text[] = {
    text_start("The tower that"
        t_line "used to be here…"
        t_para "My grandma told me"
        t_line "it used to be much"
        t_cont "taller."
        t_done )
};
const txt_cmd_s EcruteakCityLass2Text_ReleasedBeasts[] = {
    text_start("Three big #MON"
        t_line "ran off in differ-"
        t_cont "ent directions."
        t_cont "What were they?"
        t_done )
};
const txt_cmd_s EcruteakCityFisherText[] = {
    text_start("I heard a rumor"
        t_line "about OLIVINE"
        t_cont "LIGHTHOUSE."
        t_para "The #MON that"
        t_line "serves as the"
        t_para "beacon fell ill."
        t_line "Sounds like they"
        t_cont "are in trouble."
        t_done )
};
const txt_cmd_s EcruteakCityFisherText_JasmineReturned[] = {
    text_start("The #MON at"
        t_line "OLIVINE LIGHTHOUSE"
        t_cont "has been cured."
        t_para "Boats can safely"
        t_line "sail out to sea at"
        t_cont "night again."
        t_done )
};
const txt_cmd_s EcruteakCityYoungsterText[] = {
    text_start("I hear #MON are"
        t_line "rampaging at the"
        t_para "LAKE OF RAGE. I'd"
        t_line "like to see that."
        t_done )
};
const txt_cmd_s EcruteakCityGramps3Text[] = {
    text_start("In the distant"
        t_line "past…"
        t_para "This tower burned"
        t_line "in a fire. Three"
        t_para "nameless #MON"
        t_line "perished in it."
        t_para "A rainbow-colored"
        t_line "#MON descended"
        t_para "from the sky and"
        t_line "resurrected them…"
        t_para "It's a legend that"
        t_line "has been passed"
        t_para "down by ECRUTEAK"
        t_line "GYM LEADERS."
        t_para "Me?"
        t_para "I was a trainer"
        t_line "way back when."
        t_cont "Hohoho!"
        t_done )
};
const txt_cmd_s EcruteakCitySignText[] = {
    text_start("ECRUTEAK CITY"
        t_line "A Historical City"
        t_para "Where the Past"
        t_line "Meets the Present"
        t_done )
};
const txt_cmd_s TinTowerSignText[] = {
    text_start("TIN TOWER"
        t_para "A legendary #-"
        t_line "MON is said to"
        t_cont "roost here."
        t_done )
};
const txt_cmd_s EcruteakGymSignText[] = {
    text_start("ECRUTEAK CITY"
        t_line "#MON GYM"
        t_cont "LEADER: MORTY"
        t_para "The Mystic Seer of"
        t_line "the Future"
        t_done )
};
const txt_cmd_s EcruteakDanceTheaterSignText[] = {
    text_start("ECRUTEAK DANCE"
        t_line "THEATER"
        t_done )
};
const txt_cmd_s BurnedTowerSignText[] = {
    text_start("BURNED TOWER"
        t_para "It was destroyed"
        t_line "by a mysterious"
        t_cont "fire."
        t_para "Please stay away,"
        t_line "as it is unsafe."
        t_done )
    //db(0, 0) // filler
};
