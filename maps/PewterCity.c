#include "../constants.h"
#include "../util/scripting.h"
#include "PewterCity.h"
//// EVENTS
enum {
    PEWTERCITY_COOLTRAINER_F = 2,
    PEWTERCITY_BUG_CATCHER,
    PEWTERCITY_GRAMPS,
    PEWTERCITY_FRUIT_TREE1,
    PEWTERCITY_FRUIT_TREE2,
};

const Script_fn_t PewterCity_SceneScripts[] = {
    0,
};

const struct MapCallback PewterCity_MapCallbacks[] = {
    map_callback(MAPCALLBACK_NEWMAP, PewterCity_MapScripts_FlyPoint),
};

const struct MapScripts PewterCity_MapScripts = {
    .scene_script_count = 0, // lengthof(PewterCity_SceneScripts),
    .scene_scripts = PewterCity_SceneScripts,

    .callback_count = lengthof(PewterCity_MapCallbacks),
    .callbacks = PewterCity_MapCallbacks,
};

static const struct CoordEvent PewterCity_CoordEvents[] = {
    0,
};

static const struct BGEvent PewterCity_BGEvents[] = {
    bg_event(25, 23, BGEVENT_READ, &PewterCitySign),
    bg_event(11, 17, BGEVENT_READ, &PewterGymSign),
    bg_event(15, 9, BGEVENT_READ, &PewterMuseumSign),
    bg_event(33, 19, BGEVENT_READ, &PewterCityMtMoonGiftShopSign),
    bg_event(19, 29, BGEVENT_READ, &PewterCityWelcomeSign),
    bg_event(14, 25, BGEVENT_READ, &PewterCityPokecenterSign),
    bg_event(24, 17, BGEVENT_READ, &PewterCityMartSign),
};

static const struct WarpEventData PewterCity_WarpEvents[] = {
    warp_event(29, 13, PEWTER_NIDORAN_SPEECH_HOUSE, 1),
    warp_event(16, 17, PEWTER_GYM, 1),
    warp_event(23, 17, PEWTER_MART, 2),
    warp_event(13, 25, PEWTER_POKECENTER_1F, 1),
    warp_event(7, 29, PEWTER_SNOOZE_SPEECH_HOUSE, 1),
};

static const struct ObjEvent PewterCity_ObjectEvents[] = {
    object_event(19, 11, SPRITE_COOLTRAINER_F, SPRITEMOVEDATA_WANDER, 2, 2, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &PewterCityCooltrainerFScript, -1),
    object_event(14, 29, SPRITE_BUG_CATCHER, SPRITEMOVEDATA_WANDER, 2, 2, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &PewterCityBugCatcherScript, -1),
    object_event(29, 17, SPRITE_GRAMPS, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 2, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &PewterCityGrampsScript, -1),
    object_event(32, 3, SPRITE_FRUIT_TREE, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &PewterCityFruitTree1, -1),
    object_event(30, 3, SPRITE_FRUIT_TREE, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &PewterCityFruitTree2, -1),
};

const struct MapEvents PewterCity_MapEvents = {
    .warp_event_count = lengthof(PewterCity_WarpEvents),
    .warp_events = PewterCity_WarpEvents,

    .coord_event_count = 0, // lengthof(PewterCity_CoordEvents),
    .coord_events = PewterCity_CoordEvents,

    .bg_event_count = lengthof(PewterCity_BGEvents),
    .bg_events = PewterCity_BGEvents,

    .obj_event_count = lengthof(PewterCity_ObjectEvents),
    .obj_events = PewterCity_ObjectEvents,
};

//// CODE

bool PewterCity_MapScripts_FlyPoint(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_FLYPOINT_PEWTER)
    s_endcallback
    SCRIPT_END
}
bool PewterCityCooltrainerFScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(PewterCityCooltrainerFText)
    SCRIPT_END
}
bool PewterCityBugCatcherScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(PewterCityBugCatcherText)
    SCRIPT_END
}
bool PewterCityGrampsScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_SILVER_WING)
    iftrue(GotSilverWing)
    writetext(PewterCityGrampsText)
    promptbutton
    verbosegiveitem(SILVER_WING, 1)
    setevent(EVENT_GOT_SILVER_WING)
    closetext
    s_end
GotSilverWing:
    writetext(PewterCityGrampsText_GotSilverWing)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool PewterCitySign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(PewterCitySignText)
    SCRIPT_END
}
bool PewterGymSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(PewterGymSignText)
    SCRIPT_END
}
bool PewterMuseumSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(PewterMuseumSignText)
    SCRIPT_END
}
bool PewterCityMtMoonGiftShopSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(PewterCityMtMoonGiftShopSignText)
    SCRIPT_END
}
bool PewterCityWelcomeSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(PewterCityWelcomeSignText)
    SCRIPT_END
}
bool PewterCityPokecenterSign(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PokecenterSignScript)
    SCRIPT_END
}
bool PewterCityMartSign(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(MartSignScript)
    SCRIPT_END
}
bool PewterCityFruitTree1(script_s* s) {
    SCRIPT_BEGIN
    fruittree(FRUITTREE_PEWTER_CITY_1)
    SCRIPT_FALLTHROUGH(PewterCityFruitTree2)
}
bool PewterCityFruitTree2(script_s* s) {
    SCRIPT_BEGIN
    fruittree(FRUITTREE_PEWTER_CITY_2)
    SCRIPT_END
}
const txt_cmd_s PewterCityCooltrainerFText[] = {
    text_start("Have you visited"
        t_line "PEWTER GYM?"
        t_para "The LEADER uses"
        t_line "rock-type #MON."
        t_done )
};
const txt_cmd_s PewterCityBugCatcherText[] = {
    text_start("At night, CLEFAIRY"
        t_line "come out to play"
        t_cont "at MT.MOON."
        t_para "But not every"
        t_line "night."
        t_done )
};
const txt_cmd_s PewterCityGrampsText[] = {
    text_start("Ah, you came all"
        t_line "the way out here"
        t_cont "from JOHTO?"
        t_para "That brings back"
        t_line "memories. When I"
        t_para "was young, I went"
        t_line "to JOHTO to train."
        t_para "You remind me so"
        t_line "much of what I was"
        t_para "like as a young"
        t_line "man."
        t_para "Here. I want you"
        t_line "to have this item"
        t_cont "I found in JOHTO."
        t_done )
};
const txt_cmd_s PewterCityGrampsText_GotSilverWing[] = {
    text_start("Going to new, un-"
        t_line "known places and"
        t_cont "seeing new people…"
        t_para "Those are the joys"
        t_line "of travel."
        t_done )
};
const txt_cmd_s PewterCitySignText[] = {
    text_start("PEWTER CITY"
        t_line "A Stone Gray City"
        t_done )
};
const txt_cmd_s PewterGymSignText[] = {
    text_start("PEWTER CITY"
        t_line "#MON GYM"
        t_cont "LEADER: BROCK"
        t_para "The Rock Solid"
        t_line "#MON Trainer"
        t_done )
};
const txt_cmd_s PewterMuseumSignText[] = {
    text_start("There's a notice"
        t_line "here…"
        t_para "PEWTER MUSEUM OF"
        t_line "SCIENCE is closed"
        t_cont "for renovations…"
        t_done )
};
const txt_cmd_s PewterCityMtMoonGiftShopSignText[] = {
    text_start("There's a notice"
        t_line "here…"
        t_para "MT.MOON GIFT SHOP"
        t_line "NOW OPEN!"
        t_done )
};
const txt_cmd_s PewterCityWelcomeSignText[] = {
    text_start("WELCOME TO"
        t_line "PEWTER CITY!"
        t_done )
    //db(0, 0) // filler
};
