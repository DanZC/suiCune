#include "../constants.h"
#include "../util/scripting.h"
#include "Route32Pokecenter1F.h"
//// EVENTS
enum {
    ROUTE32POKECENTER1F_NURSE = 2,
    ROUTE32POKECENTER1F_FISHING_GURU,
    ROUTE32POKECENTER1F_COOLTRAINER_F,
};

const Script_fn_t Route32Pokecenter1F_SceneScripts[] = {
    0,
};

const struct MapCallback Route32Pokecenter1F_MapCallbacks[] = {
    0,
};

const struct MapScripts Route32Pokecenter1F_MapScripts = {
    .scene_script_count = 0, // lengthof(Route32Pokecenter1F_SceneScripts),
    .scene_scripts = Route32Pokecenter1F_SceneScripts,

    .callback_count = 0, // lengthof(Route32Pokecenter1F_MapCallbacks),
    .callbacks = Route32Pokecenter1F_MapCallbacks,
};

static const struct CoordEvent Route32Pokecenter1F_CoordEvents[] = {
    0,
};

static const struct BGEvent Route32Pokecenter1F_BGEvents[] = {
    0,
};

static const struct WarpEventData Route32Pokecenter1F_WarpEvents[] = {
    warp_event(3, 7, ROUTE_32, 1),
    warp_event(4, 7, ROUTE_32, 1),
    warp_event(0, 7, POKECENTER_2F, 1),
};

static const struct ObjEvent Route32Pokecenter1F_ObjectEvents[] = {
    object_event(3, 1, SPRITE_NURSE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Route32Pokecenter1FNurseScript, -1),
    object_event(1, 4, SPRITE_FISHING_GURU, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &Route32Pokecenter1FFishingGuruScript, -1),
    object_event(6, 2, SPRITE_COOLTRAINER_F, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &Route32Pokecenter1FCooltrainerFScript, -1),
};

const struct MapEvents Route32Pokecenter1F_MapEvents = {
    .warp_event_count = lengthof(Route32Pokecenter1F_WarpEvents),
    .warp_events = Route32Pokecenter1F_WarpEvents,

    .coord_event_count = 0, // lengthof(Route32Pokecenter1F_CoordEvents),
    .coord_events = Route32Pokecenter1F_CoordEvents,

    .bg_event_count = 0, // lengthof(Route32Pokecenter1F_BGEvents),
    .bg_events = Route32Pokecenter1F_BGEvents,

    .obj_event_count = lengthof(Route32Pokecenter1F_ObjectEvents),
    .obj_events = Route32Pokecenter1F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "Route32Pokecenter1F.h"

bool Route32Pokecenter1FNurseScript(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PokecenterNurseScript)
    SCRIPT_END
}
bool Route32Pokecenter1FFishingGuruScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_OLD_ROD)
    iftrue(GotOldRod)
    writetext(Route32Pokecenter1FFishingGuruText_Question)
    yesorno
    iffalse(Refused)
    writetext(Route32Pokecenter1FFishingGuruText_Yes)
    promptbutton
    verbosegiveitem(OLD_ROD, 1)
    writetext(Route32Pokecenter1FFishingGuruText_GiveOldRod)
    waitbutton
    closetext
    setevent(EVENT_GOT_OLD_ROD)
    s_end
Refused:
    writetext(Route32Pokecenter1FFishingGuruText_No)
    waitbutton
    closetext
    s_end
GotOldRod:
    writetext(Route32Pokecenter1FFishingGuruText_After)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Route32Pokecenter1FCooltrainerFScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(Route32Pokecenter1FCooltrainerFText)
    SCRIPT_END
}
const txt_cmd_s Route32Pokecenter1FFishingGuruText_Question[] = {
    text_start("This is a great"
        t_line "fishing spot."
        t_para "You saw people"
        t_line "fishing? How"
        t_cont "about you?"
        t_para "Would you like one"
        t_line "of my RODS?"
        t_done )
};
const txt_cmd_s Route32Pokecenter1FFishingGuruText_Yes[] = {
    text_start("Heh, that's good"
        t_line "to hear."
        t_para "Now you're an"
        t_line "angler too!"
        t_done )
};
const txt_cmd_s Route32Pokecenter1FFishingGuruText_GiveOldRod[] = {
    text_start("Fishing is great!"
        t_para "If there's water,"
        t_line "be it the sea or a"
        t_para "stream, try out"
        t_line "your ROD."
        t_done )
};
const txt_cmd_s Route32Pokecenter1FFishingGuruText_No[] = {
    text_start("Oh. That's rather"
        t_line "disappointing…"
        t_done )
};
const txt_cmd_s Route32Pokecenter1FFishingGuruText_After[] = {
    text_start("Yo, kid. How are"
        t_line "they biting?"
        t_done )
};
const txt_cmd_s Route32Pokecenter1FCooltrainerFText[] = {
    text_start("What should I make"
        t_line "my #MON hold?"
        t_para "Maybe an item that"
        t_line "increases ATTACK"
        t_cont "power…"
        t_done )
    //db(0, 0) // filler
};
