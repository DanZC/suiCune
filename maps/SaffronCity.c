#include "../constants.h"
#include "../util/scripting.h"
#include "SaffronCity.h"
//// EVENTS
enum {
    SAFFRONCITY_LASS1 = 2,
    SAFFRONCITY_POKEFAN_M,
    SAFFRONCITY_COOLTRAINER_M,
    SAFFRONCITY_COOLTRAINER_F,
    SAFFRONCITY_FISHER,
    SAFFRONCITY_YOUNGSTER1,
    SAFFRONCITY_YOUNGSTER2,
    SAFFRONCITY_LASS2,
};

const Script_fn_t SaffronCity_SceneScripts[] = {
    0,
};

const struct MapCallback SaffronCity_MapCallbacks[] = {
    map_callback(MAPCALLBACK_NEWMAP, SaffronCity_MapScripts_FlyPoint),
};

const struct MapScripts SaffronCity_MapScripts = {
    .scene_script_count = 0, // lengthof(SaffronCity_SceneScripts),
    .scene_scripts = SaffronCity_SceneScripts,

    .callback_count = lengthof(SaffronCity_MapCallbacks),
    .callbacks = SaffronCity_MapCallbacks,
};

static const struct CoordEvent SaffronCity_CoordEvents[] = {
    0,
};

static const struct BGEvent SaffronCity_BGEvents[] = {
    bg_event(21, 5, BGEVENT_READ, &SaffronCitySign),
    bg_event(33, 5, BGEVENT_READ, &SaffronGymSign),
    bg_event(25, 5, BGEVENT_READ, &FightingDojoSign),
    bg_event(15, 21, BGEVENT_READ, &SilphCoSign),
    bg_event(25, 29, BGEVENT_READ, &MrPsychicsHouseSign),
    bg_event(11, 5, BGEVENT_READ, &SaffronCityMagnetTrainStationSign),
    bg_event(10, 29, BGEVENT_READ, &SaffronCityPokecenterSign),
    bg_event(26, 11, BGEVENT_READ, &SaffronCityMartSign),
};

static const struct WarpEventData SaffronCity_WarpEvents[] = {
    warp_event(26, 3, FIGHTING_DOJO, 1),
    warp_event(34, 3, SAFFRON_GYM, 1),
    warp_event(25, 11, SAFFRON_MART, 2),
    warp_event(9, 29, SAFFRON_POKECENTER_1F, 1),
    warp_event(27, 29, MR_PSYCHICS_HOUSE, 1),
    warp_event(8, 3, SAFFRON_MAGNET_TRAIN_STATION, 2),
    warp_event(18, 21, SILPH_CO_1F, 1),
    warp_event(9, 11, COPYCATS_HOUSE_1F, 1),
    warp_event(18, 3, ROUTE_5_SAFFRON_GATE, 3),
    warp_event(0, 24, ROUTE_7_SAFFRON_GATE, 3),
    warp_event(0, 25, ROUTE_7_SAFFRON_GATE, 4),
    warp_event(16, 33, ROUTE_6_SAFFRON_GATE, 1),
    warp_event(17, 33, ROUTE_6_SAFFRON_GATE, 2),
    warp_event(39, 22, ROUTE_8_SAFFRON_GATE, 1),
    warp_event(39, 23, ROUTE_8_SAFFRON_GATE, 2),
};

static const struct ObjEvent SaffronCity_ObjectEvents[] = {
    object_event(7, 14, SPRITE_LASS, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 2, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &SaffronCityLass1Script, -1),
    object_event(19, 30, SPRITE_POKEFAN_M, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 2, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, &SaffronCityPokefanMScript, -1),
    object_event(32, 7, SPRITE_COOLTRAINER_M, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &SaffronCityCooltrainerMScript, -1),
    object_event(20, 24, SPRITE_COOLTRAINER_F, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 2, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &SaffronCityCooltrainerFScript, -1),
    object_event(27, 12, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &SaffronCityFisherScript, -1),
    object_event(15, 19, SPRITE_YOUNGSTER, SPRITEMOVEDATA_WALK_UP_DOWN, 0, 1, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &SaffronCityYoungster1Script, -1),
    object_event(35, 22, SPRITE_YOUNGSTER, SPRITEMOVEDATA_WANDER, 1, 1, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &SaffronCityYoungster2Script, -1),
    object_event(19, 8, SPRITE_LASS, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &SaffronCityLass2Script, -1),
};

const struct MapEvents SaffronCity_MapEvents = {
    .warp_event_count = lengthof(SaffronCity_WarpEvents),
    .warp_events = SaffronCity_WarpEvents,

    .coord_event_count = 0, // lengthof(SaffronCity_CoordEvents),
    .coord_events = SaffronCity_CoordEvents,

    .bg_event_count = lengthof(SaffronCity_BGEvents),
    .bg_events = SaffronCity_BGEvents,

    .obj_event_count = lengthof(SaffronCity_ObjectEvents),
    .obj_events = SaffronCity_ObjectEvents,
};

//// CODE

bool SaffronCity_MapScripts_FlyPoint(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_FLYPOINT_SAFFRON)
    s_endcallback
    SCRIPT_END
}
bool SaffronCityLass1Script(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_RETURNED_MACHINE_PART)
    iftrue(ReturnedMachinePart)
    writetext(SaffronCityLass1Text)
    waitbutton
    closetext
    s_end
ReturnedMachinePart:
    writetext(SaffronCityLass1Text_ReturnedMachinePart)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool SaffronCityPokefanMScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_RETURNED_MACHINE_PART)
    iftrue(ReturnedMachinePart)
    writetext(SaffronCityPokefanMText)
    waitbutton
    closetext
    s_end
ReturnedMachinePart:
    writetext(SaffronCityPokefanMText_ReturnedMachinePart)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool SaffronCityCooltrainerMScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(SaffronCityCooltrainerMText)
    SCRIPT_END
}
bool SaffronCityCooltrainerFScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(SaffronCityCooltrainerFText)
    SCRIPT_END
}
bool SaffronCityFisherScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_RETURNED_MACHINE_PART)
    iftrue(ReturnedMachinePart)
    writetext(SaffronCityFisherText)
    waitbutton
    closetext
    s_end
ReturnedMachinePart:
    writetext(SaffronCityFisherText_ReturnedMachinePart)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool SaffronCityYoungster1Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(SaffronCityYoungster1Text)
    SCRIPT_END
}
bool SaffronCityYoungster2Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(SaffronCityYoungster2Text)
    SCRIPT_END
}
bool SaffronCityLass2Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(SaffronCityLass2Text)
    SCRIPT_END
}
bool SaffronCitySign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(SaffronCitySignText)
    SCRIPT_END
}
bool SaffronGymSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(SaffronGymSignText)
    SCRIPT_END
}
bool FightingDojoSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(FightingDojoSignText)
    SCRIPT_END
}
bool SilphCoSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(SilphCoSignText)
    SCRIPT_END
}
bool MrPsychicsHouseSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(MrPsychicsHouseSignText)
    SCRIPT_END
}
bool SaffronCityMagnetTrainStationSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(SaffronCityMagnetTrainStationSignText)
    SCRIPT_END
}
bool SaffronCityPokecenterSign(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PokecenterSignScript)
    SCRIPT_END
}
bool SaffronCityMartSign(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(MartSignScript)
    SCRIPT_END
}
const txt_cmd_s SaffronCityLass1Text[] = {
    text_start("A little girl who"
        t_line "is an expert at"
        t_para "mimicking people"
        t_line "lives here."
        t_para "She even mimics"
        t_line "the people she's"
        t_para "conversing with."
        t_line "It's confusing."
        t_done )
};
const txt_cmd_s SaffronCityLass1Text_ReturnedMachinePart[] = {
    text_start("The COPYCAT girl"
        t_line "looked unhappy."
        t_para "She said she lost"
        t_line "her favorite #"
        t_cont "DOLL--CLEFAIRY."
        t_done )
};
const txt_cmd_s SaffronCityPokefanMText[] = {
    text_start("You came out from"
        t_line "JOHTO?"
        t_para "You can zip back"
        t_line "home if the MAGNET"
        t_cont "TRAIN's running."
        t_done )
};
const txt_cmd_s SaffronCityPokefanMText_ReturnedMachinePart[] = {
    text_start("You came out from"
        t_line "JOHTO?"
        t_para "You can zip back"
        t_line "home by hopping on"
        t_cont "the MAGNET TRAIN."
        t_done )
};
const txt_cmd_s SaffronCityCooltrainerMText[] = {
    text_start("I went to the GYM,"
        t_line "raring for battles"
        t_cont "against trainers…"
        t_para "It turns out, I"
        t_line "stumbled into the"
        t_para "unused GYM next"
        t_line "door."
        t_para "Boy, I was pretty"
        t_line "embarrassed."
        t_done )
};
const txt_cmd_s SaffronCityCooltrainerFText[] = {
    text_start("This is SILPH CO.,"
        t_line "famous for #MON"
        t_cont "merchandise."
        t_para "In the past, TEAM"
        t_line "ROCKET wanted the"
        t_para "company because of"
        t_line "that."
        t_done )
};
const txt_cmd_s SaffronCityFisherText[] = {
    text_start("Chew… Chew…"
        t_para "I hear there's big"
        t_line "trouble brewing at"
        t_cont "the POWER PLANT."
        t_para "Chew… Chew…"
        t_done )
};
const txt_cmd_s SaffronCityFisherText_ReturnedMachinePart[] = {
    text_start("Chew… Chew…"
        t_para "I hear there was"
        t_line "big trouble at the"
        t_cont "POWER PLANT."
        t_para "Chew… Chew…"
        t_line "Haaah, I'm full!"
        t_done )
};
const txt_cmd_s SaffronCityYoungster1Text[] = {
    text_start("Going into an"
        t_line "alley for the"
        t_para "first time makes"
        t_line "me sorta anxious."
        t_done )
};
const txt_cmd_s SaffronCityYoungster2Text[] = {
    text_start("There's a place"
        t_line "called TRAINER"
        t_para "HOUSE in VIRIDIAN"
        t_line "where trainers"
        t_para "gather from all"
        t_line "over the place."
        t_done )
};
const txt_cmd_s SaffronCityLass2Text[] = {
    text_start("Our city was"
        t_line "featured on a"
        t_cont "radio program."
        t_para "It's nice to hear"
        t_line "praise for your"
        t_para "city, but it's a"
        t_line "bit embarrassing"
        t_cont "too."
        t_done )
};
const txt_cmd_s SaffronCitySignText[] = {
    text_start("SAFFRON CITY"
        t_para "Shining, Golden"
        t_line "Land of Commerce"
        t_done )
};
const txt_cmd_s SaffronGymSignText[] = {
    text_start("SAFFRON CITY"
        t_line "#MON GYM"
        t_cont "LEADER: SABRINA"
        t_para "The Master of"
        t_line "Psychic #MON!"
        t_done )
};
const txt_cmd_s FightingDojoSignText[] = {
    text_start("Everyone Welcome!"
        t_line "FIGHTING DOJO"
        t_done )
};
const txt_cmd_s SilphCoSignText[] = {
    text_start("SILPH CO."
        t_line "OFFICE BUILDING"
        t_done )
};
const txt_cmd_s MrPsychicsHouseSignText[] = {
    text_start("MR.PSYCHIC'S"
        t_line "HOUSE"
        t_done )
};
const txt_cmd_s SaffronCityMagnetTrainStationSignText[] = {
    text_start("SAFFRON CITY"
        t_line "MAGNET TRAIN"
        t_cont "STATION"
        t_done )
    //db(0, 0) // filler
};
