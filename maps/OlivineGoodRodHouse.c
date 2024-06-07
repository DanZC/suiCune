#include "../constants.h"
#include "../util/scripting.h"
#include "OlivineGoodRodHouse.h"
//// EVENTS
enum {
    OLIVINEGOODRODHOUSE_FISHING_GURU = 2,
};

const Script_fn_t OlivineGoodRodHouse_SceneScripts[] = {
    0,
};

const struct MapCallback OlivineGoodRodHouse_MapCallbacks[] = {
    0,
};

const struct MapScripts OlivineGoodRodHouse_MapScripts = {
    .scene_script_count = 0, // lengthof(OlivineGoodRodHouse_SceneScripts),
    .scene_scripts = OlivineGoodRodHouse_SceneScripts,

    .callback_count = 0, // lengthof(OlivineGoodRodHouse_MapCallbacks),
    .callbacks = OlivineGoodRodHouse_MapCallbacks,
};

static const struct CoordEvent OlivineGoodRodHouse_CoordEvents[] = {
    0,
};

static const struct BGEvent OlivineGoodRodHouse_BGEvents[] = {
    0,
};

static const struct WarpEventData OlivineGoodRodHouse_WarpEvents[] = {
    warp_event(2, 7, OLIVINE_CITY, 6),
    warp_event(3, 7, OLIVINE_CITY, 6),
};

static const struct ObjEvent OlivineGoodRodHouse_ObjectEvents[] = {
    object_event(2, 3, SPRITE_FISHING_GURU, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &GoodRodGuru, -1),
};

const struct MapEvents OlivineGoodRodHouse_MapEvents = {
    .warp_event_count = lengthof(OlivineGoodRodHouse_WarpEvents),
    .warp_events = OlivineGoodRodHouse_WarpEvents,

    .coord_event_count = 0, // lengthof(OlivineGoodRodHouse_CoordEvents),
    .coord_events = OlivineGoodRodHouse_CoordEvents,

    .bg_event_count = 0, // lengthof(OlivineGoodRodHouse_BGEvents),
    .bg_events = OlivineGoodRodHouse_BGEvents,

    .obj_event_count = lengthof(OlivineGoodRodHouse_ObjectEvents),
    .obj_events = OlivineGoodRodHouse_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "OlivineGoodRodHouse.h"

bool GoodRodGuru(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_GOOD_ROD)
    iftrue(AlreadyGotItem)
    writetext(OfferGoodRodText)
    yesorno
    iffalse(DontWantIt)
    writetext(GiveGoodRodText)
    promptbutton
    verbosegiveitem(GOOD_ROD, 1)
    writetext(GaveGoodRodText)
    waitbutton
    closetext
    setevent(EVENT_GOT_GOOD_ROD)
    s_end
DontWantIt:
    writetext(DontWantGoodRodText)
    waitbutton
    closetext
    s_end
AlreadyGotItem:
    writetext(HaveGoodRodText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool GoodRodHouseBookshelf(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PictureBookshelfScript)
    SCRIPT_END
}
const txt_cmd_s OfferGoodRodText[] = {
    text_start("OLIVINE is on the"
        t_line "sea!"
        t_para "And if it's on the"
        t_line "sea, there are"
        t_cont "bound to be fish!"
        t_para "I've fished here"
        t_line "for 30 years."
        t_para "Would you like to"
        t_line "face the sea and"
        t_cont "fish?"
        t_done )
};
const txt_cmd_s GiveGoodRodText[] = {
    text_start("Ah, hahah!"
        t_line "We have ourselves"
        t_cont "a new angler!"
        t_done )
};
const txt_cmd_s GaveGoodRodText[] = {
    text_start("Fish aren't found"
        t_line "in the sea alone."
        t_para "They go wherever"
        t_line "there is water."
        t_done )
};
const txt_cmd_s DontWantGoodRodText[] = {
    text_start("Whaaat? You don't"
        t_line "like to fish!?"
        t_cont "Incomprehensible!"
        t_done )
};
const txt_cmd_s HaveGoodRodText[] = {
    text_start("How are things?"
        t_line "Land the big one?"
        t_done )
    //db(0, 0) // filler
};
