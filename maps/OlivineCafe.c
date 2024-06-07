#include "../constants.h"
#include "../util/scripting.h"
#include "OlivineCafe.h"
//// EVENTS
enum {
    OLIVINECAFE_SAILOR1 = 2,
    OLIVINECAFE_FISHING_GURU,
    OLIVINECAFE_SAILOR2,
};

const Script_fn_t OlivineCafe_SceneScripts[] = {
    0,
};

const struct MapCallback OlivineCafe_MapCallbacks[] = {
    0,
};

const struct MapScripts OlivineCafe_MapScripts = {
    .scene_script_count = 0, // lengthof(OlivineCafe_SceneScripts),
    .scene_scripts = OlivineCafe_SceneScripts,

    .callback_count = 0, // lengthof(OlivineCafe_MapCallbacks),
    .callbacks = OlivineCafe_MapCallbacks,
};

static const struct CoordEvent OlivineCafe_CoordEvents[] = {
    0,
};

static const struct BGEvent OlivineCafe_BGEvents[] = {
    0,
};

static const struct WarpEventData OlivineCafe_WarpEvents[] = {
    warp_event(2, 7, OLIVINE_CITY, 7),
    warp_event(3, 7, OLIVINE_CITY, 7),
};

static const struct ObjEvent OlivineCafe_ObjectEvents[] = {
    object_event(4, 3, SPRITE_SAILOR, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &OlivineCafeStrengthSailorScript, -1),
    object_event(7, 3, SPRITE_FISHING_GURU, SPRITEMOVEDATA_WALK_UP_DOWN, 0, 1, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &OlivineCafeFishingGuruScript, -1),
    object_event(6, 6, SPRITE_SAILOR, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &OlivineCafeSailorScript, -1),
};

const struct MapEvents OlivineCafe_MapEvents = {
    .warp_event_count = lengthof(OlivineCafe_WarpEvents),
    .warp_events = OlivineCafe_WarpEvents,

    .coord_event_count = 0, // lengthof(OlivineCafe_CoordEvents),
    .coord_events = OlivineCafe_CoordEvents,

    .bg_event_count = 0, // lengthof(OlivineCafe_BGEvents),
    .bg_events = OlivineCafe_BGEvents,

    .obj_event_count = lengthof(OlivineCafe_ObjectEvents),
    .obj_events = OlivineCafe_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "OlivineCafe.h"

bool OlivineCafeStrengthSailorScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_HM04_STRENGTH)
    iftrue(GotStrength)
    writetext(OlivineCafeStrengthSailorText)
    promptbutton
    verbosegiveitem(HM_STRENGTH, 1)
    setevent(EVENT_GOT_HM04_STRENGTH)
GotStrength:
    writetext(OlivineCafeStrengthSailorText_GotStrength)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool OlivineCafeFishingGuruScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(OlivineCafeFishingGuruText)
    SCRIPT_END
}
bool OlivineCafeSailorScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(OlivineCafeSailorText)
    SCRIPT_END
}
const txt_cmd_s OlivineCafeStrengthSailorText[] = {
    text_start("Hah! Your #MON"
        t_line "sure look like"
        t_cont "lightweights!"
        t_para "They don't have"
        t_line "the power to move"
        t_cont "boulders aside."
        t_para "Here, use this"
        t_line "and teach them"
        t_cont "STRENGTH!"
        t_done )
};
const txt_cmd_s OlivineCafeStrengthSailorText_GotStrength[] = {
    text_start("On the sea, the"
        t_line "only thing you can"
        t_para "count on is your"
        t_line "own good self!"
        t_para "I'm so proud of my"
        t_line "buff bod!"
        t_done )
};
const txt_cmd_s OlivineCafeFishingGuruText[] = {
    text_start("OLIVINE CAFE's"
        t_line "menu is chock full"
        t_para "of hearty fare for"
        t_line "beefy SAILORS!"
        t_done )
};
const txt_cmd_s OlivineCafeSailorText[] = {
    text_start("Whenever I roll"
        t_line "into this town, I"
        t_para "always visit the"
        t_line "OLIVINE CAFE."
        t_para "Everything on the"
        t_line "menu makes me feel"
        t_para "stronger. I can't"
        t_line "stop eating!"
        t_done )
    //db(0, 0) // filler
};
