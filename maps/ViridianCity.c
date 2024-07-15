#include "../constants.h"
#include "../util/scripting.h"
#include "ViridianCity.h"
//// EVENTS
enum {
    VIRIDIANCITY_GRAMPS1 = 2,
    VIRIDIANCITY_GRAMPS2,
    VIRIDIANCITY_FISHER,
    VIRIDIANCITY_YOUNGSTER,
};

const Script_fn_t ViridianCity_SceneScripts[] = {
    0,
};

const struct MapCallback ViridianCity_MapCallbacks[] = {
    map_callback(MAPCALLBACK_NEWMAP, ViridianCity_MapScripts_FlyPoint),
};

const struct MapScripts ViridianCity_MapScripts = {
    .scene_script_count = 0, // lengthof(ViridianCity_SceneScripts),
    .scene_scripts = ViridianCity_SceneScripts,

    .callback_count = lengthof(ViridianCity_MapCallbacks),
    .callbacks = ViridianCity_MapCallbacks,
};

static const struct CoordEvent ViridianCity_CoordEvents[] = {
    0,
};

static const struct BGEvent ViridianCity_BGEvents[] = {
    bg_event(17, 17, BGEVENT_READ, &ViridianCitySign),
    bg_event(27, 7, BGEVENT_READ, &ViridianGymSign),
    bg_event(19, 1, BGEVENT_READ, &ViridianCityWelcomeSign),
    bg_event(21, 15, BGEVENT_READ, &TrainerHouseSign),
    bg_event(24, 25, BGEVENT_READ, &ViridianCityPokecenterSign),
    bg_event(30, 19, BGEVENT_READ, &ViridianCityMartSign),
};

static const struct WarpEventData ViridianCity_WarpEvents[] = {
    warp_event(32, 7, VIRIDIAN_GYM, 1),
    warp_event(21, 9, VIRIDIAN_NICKNAME_SPEECH_HOUSE, 1),
    warp_event(23, 15, TRAINER_HOUSE_1F, 1),
    warp_event(29, 19, VIRIDIAN_MART, 2),
    warp_event(23, 25, VIRIDIAN_POKECENTER_1F, 1),
};

static const struct ObjEvent ViridianCity_ObjectEvents[] = {
    object_event(18, 5, SPRITE_GRAMPS, SPRITEMOVEDATA_WANDER, 2, 2, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &ViridianCityCoffeeGramps, -1),
    object_event(30, 8, SPRITE_GRAMPS, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &ViridianCityGrampsNearGym, -1),
    object_event(6, 23, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &ViridianCityDreamEaterFisher, -1),
    object_event(17, 21, SPRITE_YOUNGSTER, SPRITEMOVEDATA_WANDER, 3, 3, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &ViridianCityYoungsterScript, -1),
};

const struct MapEvents ViridianCity_MapEvents = {
    .warp_event_count = lengthof(ViridianCity_WarpEvents),
    .warp_events = ViridianCity_WarpEvents,

    .coord_event_count = 0, // lengthof(ViridianCity_CoordEvents),
    .coord_events = ViridianCity_CoordEvents,

    .bg_event_count = lengthof(ViridianCity_BGEvents),
    .bg_events = ViridianCity_BGEvents,

    .obj_event_count = lengthof(ViridianCity_ObjectEvents),
    .obj_events = ViridianCity_ObjectEvents,
};

//// CODE

bool ViridianCity_MapScripts_FlyPoint(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_FLYPOINT_VIRIDIAN)
    s_endcallback
    SCRIPT_END
}
bool ViridianCityCoffeeGramps(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(ViridianCityCoffeeGrampsQuestionText)
    yesorno
    iffalse(no)
    writetext(ViridianCityCoffeeGrampsBelievedText)
    waitbutton
    closetext
    s_end
no:
    writetext(ViridianCityCoffeeGrampsDoubtedText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool ViridianCityGrampsNearGym(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_BLUE_IN_CINNABAR)
    iftrue(BlueReturned)
    writetext(ViridianCityGrampsNearGymText)
    waitbutton
    closetext
    s_end
BlueReturned:
    writetext(ViridianCityGrampsNearGymBlueReturnedText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool ViridianCityDreamEaterFisher(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_TM42_DREAM_EATER)
    iftrue(GotDreamEater)
    writetext(ViridianCityDreamEaterFisherText)
    promptbutton
    verbosegiveitem(TM_DREAM_EATER, 1)
    iffalse(NoRoomForDreamEater)
    setevent(EVENT_GOT_TM42_DREAM_EATER)
GotDreamEater:
    writetext(ViridianCityDreamEaterFisherGotDreamEaterText)
    waitbutton
NoRoomForDreamEater:
    closetext
    s_end
    SCRIPT_END
}
bool ViridianCityYoungsterScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(ViridianCityYoungsterText)
    SCRIPT_END
}
bool ViridianCitySign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(ViridianCitySignText)
    SCRIPT_END
}
bool ViridianGymSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(ViridianGymSignText)
    SCRIPT_END
}
bool ViridianCityWelcomeSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(ViridianCityWelcomeSignText)
    SCRIPT_END
}
bool TrainerHouseSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(TrainerHouseSignText)
    SCRIPT_END
}
bool ViridianCityPokecenterSign(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PokecenterSignScript)
    SCRIPT_END
}
bool ViridianCityMartSign(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(MartSignScript)
    SCRIPT_END
}
const txt_cmd_s ViridianCityCoffeeGrampsQuestionText[] = {
    text_start("Hey, kid! I just"
        t_line "had a double shot"
        t_para "of espresso, and"
        t_line "I am wired!"
        t_para "I need to talk to"
        t_line "someone, so you'll"
        t_cont "have to do!"
        t_para "I might not look"
        t_line "like much now, but"
        t_para "I was an expert at"
        t_line "catching #MON."
        t_para "Do you believe me?"
        t_done )
};
const txt_cmd_s ViridianCityCoffeeGrampsBelievedText[] = {
    text_start("Good, good. Yes, I"
        t_line "was something out"
        t_para "of the ordinary,"
        t_line "let me tell you!"
        t_done )
};
const txt_cmd_s ViridianCityCoffeeGrampsDoubtedText[] = {
    text_start("What? You little"
        t_line "whelp!"
        t_para "If I were just a"
        t_line "bit younger, I'd"
        t_para "show you a thing"
        t_line "or two. Humph!"
        t_done )
};
const txt_cmd_s ViridianCityGrampsNearGymText[] = {
    text_start("This GYM didn't"
        t_line "have a LEADER"
        t_cont "until recently."
        t_para "A young man from"
        t_line "PALLET became the"
        t_para "LEADER, but he's"
        t_line "often away."
        t_done )
};
const txt_cmd_s ViridianCityGrampsNearGymBlueReturnedText[] = {
    text_start("Are you going to"
        t_line "battle the LEADER?"
        t_para "Good luck to you."
        t_line "You'll need it."
        t_done )
};
const txt_cmd_s ViridianCityDreamEaterFisherText[] = {
    text_start("Yawn!"
        t_para "I must have dozed"
        t_line "off in the sun."
        t_para "…I had this dream"
        t_line "about a DROWZEE"
        t_para "eating my dream."
        t_line "Weird, huh?"
        t_para "Huh?"
        t_line "What's this?"
        t_para "Where did this TM"
        t_line "come from?"
        t_para "This is spooky!"
        t_line "Here, you can have"
        t_cont "this TM."
        t_done )
};
const txt_cmd_s ViridianCityDreamEaterFisherGotDreamEaterText[] = {
    text_start("TM42 contains"
        t_line "DREAM EATER…"
        t_para "…Zzzzz…"
        t_done )
};
const txt_cmd_s ViridianCityYoungsterText[] = {
    text_start("I heard that there"
        t_line "are many items on"
        t_para "the ground in"
        t_line "VIRIDIAN FOREST."
        t_done )
};
const txt_cmd_s ViridianCitySignText[] = {
    text_start("VIRIDIAN CITY"
        t_para "The Eternally"
        t_line "Green Paradise"
        t_done )
};
const txt_cmd_s ViridianGymSignText[] = {
    text_start("VIRIDIAN CITY"
        t_line "#MON GYM"
        t_cont "LEADER: …"
        t_para "The rest of the"
        t_line "text is illegible…"
        t_done )
};
const txt_cmd_s ViridianCityWelcomeSignText[] = {
    text_start("WELCOME TO"
        t_line "VIRIDIAN CITY,"
        t_para "THE GATEWAY TO"
        t_line "INDIGO PLATEAU"
        t_done )
};
const txt_cmd_s TrainerHouseSignText[] = {
    text_start("TRAINER HOUSE"
        t_para "The Club for Top"
        t_line "Trainer Battles"
        t_done )
    //db(0, 0) // filler
};
