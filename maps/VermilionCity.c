#include "../constants.h"
#include "../util/scripting.h"
#include "VermilionCity.h"
//// EVENTS
enum {
    VERMILIONCITY_TEACHER = 2,
    VERMILIONCITY_GRAMPS,
    VERMILIONCITY_MACHOP,
    VERMILIONCITY_SUPER_NERD,
    VERMILIONCITY_BIG_SNORLAX,
    VERMILIONCITY_POKEFAN_M,
};

const Script_fn_t VermilionCity_SceneScripts[] = {
    0,
};

const struct MapCallback VermilionCity_MapCallbacks[] = {
    map_callback(MAPCALLBACK_NEWMAP, VermilionCity_MapScripts_FlyPoint),
};

const struct MapScripts VermilionCity_MapScripts = {
    .scene_script_count = 0, // lengthof(VermilionCity_SceneScripts),
    .scene_scripts = VermilionCity_SceneScripts,

    .callback_count = lengthof(VermilionCity_MapCallbacks),
    .callbacks = VermilionCity_MapCallbacks,
};

static const struct CoordEvent VermilionCity_CoordEvents[] = {
    0,
};

static const struct BGEvent VermilionCity_BGEvents[] = {
    bg_event(25, 3, BGEVENT_READ, &VermilionCitySign),
    bg_event(5, 19, BGEVENT_READ, &VermilionGymSign),
    bg_event(5, 13, BGEVENT_READ, &PokemonFanClubSign),
    bg_event(33, 9, BGEVENT_READ, &VermilionCityDiglettsCaveSign),
    bg_event(27, 15, BGEVENT_READ, &VermilionCityPortSign),
    bg_event(10, 5, BGEVENT_READ, &VermilionCityPokecenterSign),
    bg_event(22, 13, BGEVENT_READ, &VermilionCityMartSign),
    bg_event(12, 19, BGEVENT_ITEM, &VermilionCityHiddenFullHeal),
};

static const struct WarpEventData VermilionCity_WarpEvents[] = {
    warp_event(5, 5, VERMILION_FISHING_SPEECH_HOUSE, 1),
    warp_event(9, 5, VERMILION_POKECENTER_1F, 1),
    warp_event(7, 13, POKEMON_FAN_CLUB, 1),
    warp_event(13, 13, VERMILION_MAGNET_TRAIN_SPEECH_HOUSE, 1),
    warp_event(21, 13, VERMILION_MART, 2),
    warp_event(21, 17, VERMILION_DIGLETTS_CAVE_SPEECH_HOUSE, 1),
    warp_event(10, 19, VERMILION_GYM, 1),
    warp_event(19, 31, VERMILION_PORT_PASSAGE, 1),
    warp_event(20, 31, VERMILION_PORT_PASSAGE, 2),
    warp_event(34, 7, DIGLETTS_CAVE, 1),
};

static const struct ObjEvent VermilionCity_ObjectEvents[] = {
    object_event(18, 9, SPRITE_TEACHER, SPRITEMOVEDATA_WANDER, 1, 1, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &VermilionCityTeacherScript, -1),
    object_event(23, 6, SPRITE_GRAMPS, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &VermilionMachopOwner, -1),
    object_event(26, 7, SPRITE_MACHOP, SPRITEMOVEDATA_POKEMON, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &VermilionMachop, -1),
    object_event(14, 16, SPRITE_SUPER_NERD, SPRITEMOVEDATA_WANDER, 1, 1, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &VermilionCitySuperNerdScript, -1),
    object_event(34, 8, SPRITE_BIG_SNORLAX, SPRITEMOVEDATA_BIGDOLLSYM, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &VermilionSnorlax, EVENT_VERMILION_CITY_SNORLAX),
    object_event(31, 12, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &VermilionGymBadgeGuy, -1),
};

const struct MapEvents VermilionCity_MapEvents = {
    .warp_event_count = lengthof(VermilionCity_WarpEvents),
    .warp_events = VermilionCity_WarpEvents,

    .coord_event_count = 0, // lengthof(VermilionCity_CoordEvents),
    .coord_events = VermilionCity_CoordEvents,

    .bg_event_count = lengthof(VermilionCity_BGEvents),
    .bg_events = VermilionCity_BGEvents,

    .obj_event_count = lengthof(VermilionCity_ObjectEvents),
    .obj_events = VermilionCity_ObjectEvents,
};

//// CODE

bool VermilionCity_MapScripts_FlyPoint(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_FLYPOINT_VERMILION)
    s_endcallback
    SCRIPT_END
}
bool VermilionCityTeacherScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(VermilionCityTeacherText)
    SCRIPT_END
}
bool VermilionMachopOwner(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(VermilionMachopOwnerText)
    SCRIPT_END
}
bool VermilionMachop(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(VermilionMachopText1)
    playcry(MACHOP)
    waitbutton
    closetext
    earthquake(30)
    opentext
    writetext(VermilionMachopText2)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool VermilionCitySuperNerdScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(VermilionCitySuperNerdText)
    SCRIPT_END
}
bool VermilionSnorlax(script_s* s) {
    SCRIPT_BEGIN
    opentext
    special(SnorlaxAwake)
    iftrue(Awake)
    writetext(VermilionCitySnorlaxSleepingText)
    waitbutton
    closetext
    s_end
Awake:
    writetext(VermilionCityRadioNearSnorlaxText)
    pause(15)
    playcry(SNORLAX)
    closetext
    loadvar(VAR_BATTLETYPE, BATTLETYPE_FORCEITEM)
    loadwildmon(SNORLAX, 50)
    startbattle
    disappear(VERMILIONCITY_BIG_SNORLAX)
    setevent(EVENT_FOUGHT_SNORLAX)
    reloadmapafterbattle
    s_end
    SCRIPT_END
}
bool VermilionGymBadgeGuy(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_HP_UP_FROM_VERMILION_GUY)
    iftrue(AlreadyGotItem)
    readvar(VAR_BADGES)
    ifequal(NUM_BADGES, AllBadges)
    ifgreater(13, MostBadges)
    ifgreater(9, SomeBadges)
    writetext(VermilionCityBadgeGuyTrainerText)
    waitbutton
    closetext
    s_end
SomeBadges:
    writetext(VermilionCityBadgeGuySomeBadgesText)
    waitbutton
    closetext
    s_end
MostBadges:
    writetext(VermilionCityBadgeGuyMostBadgesText)
    waitbutton
    closetext
    s_end
AllBadges:
    writetext(VermilionCityBadgeGuyAllBadgesText)
    promptbutton
    verbosegiveitem(HP_UP, 1)
    iffalse(Done)
    setevent(EVENT_GOT_HP_UP_FROM_VERMILION_GUY)
AlreadyGotItem:
    writetext(VermilionCityBadgeGuyBattleEdgeText)
    waitbutton
Done:
    closetext
    s_end
    SCRIPT_END
}
bool VermilionCitySign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(VermilionCitySignText)
    SCRIPT_END
}
bool VermilionGymSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(VermilionGymSignText)
    SCRIPT_END
}
bool PokemonFanClubSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(PokemonFanClubSignText)
    SCRIPT_END
}
bool VermilionCityDiglettsCaveSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(VermilionCityDiglettsCaveSignText)
    SCRIPT_END
}
bool VermilionCityPortSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(VermilionCityPortSignText)
    SCRIPT_END
}
bool VermilionCityPokecenterSign(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PokecenterSignScript)
    SCRIPT_END
}
bool VermilionCityMartSign(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(MartSignScript)
    SCRIPT_END
}
const struct HiddenItem VermilionCityHiddenFullHeal = {FULL_HEAL, EVENT_VERMILION_CITY_HIDDEN_FULL_HEAL};
const txt_cmd_s VermilionCityTeacherText[] = {
    text_start("VERMILION PORT is"
        t_line "KANTO's seaside"
        t_cont "gateway."
        t_para "Luxury liners from"
        t_line "around the world"
        t_cont "dock here."
        t_done )
};
const txt_cmd_s VermilionMachopOwnerText[] = {
    text_start("My #MON is"
        t_line "preparing the land"
        t_cont "for construction."
        t_para "But I have no"
        t_line "money to start the"
        t_cont "project…"
        t_done )
};
const txt_cmd_s VermilionMachopText1[] = {
    text_start("MACHOP: Guooh"
        t_line "gogogoh!"
        t_done )
};
const txt_cmd_s VermilionMachopText2[] = {
    text_start("A MACHOP is growl-"
        t_line "ing while stomping"
        t_cont "the ground flat."
        t_done )
};
const txt_cmd_s VermilionCitySuperNerdText[] = {
    text_start("There are eight"
        t_line "GYMS in KANTO."
        t_para "That big building"
        t_line "is VERMILION's"
        t_cont "#MON GYM."
        t_done )
};
const txt_cmd_s VermilionCitySnorlaxSleepingText[] = {
    text_start("SNORLAX is snoring"
        t_line "peacefully…"
        t_done )
};
const txt_cmd_s VermilionCityRadioNearSnorlaxText[] = {
    text_start("The #GEAR was"
        t_line "placed near the"
        t_cont "sleeping SNORLAX…"
        t_para "…"
        t_para "SNORLAX woke up!"
        t_done )
};
const txt_cmd_s VermilionCityBadgeGuyTrainerText[] = {
    text_start("Skilled trainers"
        t_line "gather in KANTO."
        t_para "GYM LEADERS are"
        t_line "especially strong."
        t_para "They won't be easy"
        t_line "to defeat."
        t_done )
};
const txt_cmd_s VermilionCityBadgeGuySomeBadgesText[] = {
    text_start("You've started to"
        t_line "collect KANTO GYM"
        t_cont "BADGES?"
        t_para "Don't you agree"
        t_line "that the trainers"
        t_cont "here are tough?"
        t_done )
};
const txt_cmd_s VermilionCityBadgeGuyMostBadgesText[] = {
    text_start("I guess you'll be"
        t_line "finished with your"
        t_para "conquest of KANTO"
        t_line "GYMS soon."
        t_para "Let me know if"
        t_line "you get all eight"
        t_cont "BADGES."
        t_done )
};
const txt_cmd_s VermilionCityBadgeGuyAllBadgesText[] = {
    text_start("Congratulations!"
        t_para "You got all the"
        t_line "KANTO GYM BADGES."
        t_para "I've got a reward"
        t_line "for your efforts."
        t_done )
};
const txt_cmd_s VermilionCityBadgeGuyBattleEdgeText[] = {
    text_start("Having a variety"
        t_line "of #MON types"
        t_para "should give you an"
        t_line "edge in battle."
        t_para "I'm sure the KANTO"
        t_line "GYM BADGES will"
        t_cont "help you."
        t_done )
};
const txt_cmd_s VermilionCitySignText[] = {
    text_start("VERMILION CITY"
        t_para "The Port of"
        t_line "Exquisite Sunsets"
        t_done )
};
const txt_cmd_s VermilionGymSignText[] = {
    text_start("VERMILION CITY"
        t_line "#MON GYM"
        t_cont "LEADER: LT.SURGE"
        t_para "The Lightning"
        t_line "American"
        t_done )
};
const txt_cmd_s PokemonFanClubSignText[] = {
    text_start("#MON FAN CLUB"
        t_para "All #MON Fans"
        t_line "Welcome!"
        t_done )
};
const txt_cmd_s VermilionCityDiglettsCaveSignText[] = {
    text_start("DIGLETT'S CAVE"
        t_done )
};
const txt_cmd_s VermilionCityPortSignText[] = {
    text_start("VERMILION PORT"
        t_line "ENTRANCE"
        t_done )
    //db(0, 0) // filler
};
