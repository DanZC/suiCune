#include "../constants.h"
#include "../util/scripting.h"
#include "CeladonMansionRoofHouse.h"
//// EVENTS
enum {
    CELADONMANSIONROOFHOUSE_PHARMACIST = 2,
};

const Script_fn_t CeladonMansionRoofHouse_SceneScripts[] = {
    0,
};

const struct MapCallback CeladonMansionRoofHouse_MapCallbacks[] = {
    0,
};

const struct MapScripts CeladonMansionRoofHouse_MapScripts = {
    .scene_script_count = 0, // lengthof(CeladonMansionRoofHouse_SceneScripts),
    .scene_scripts = CeladonMansionRoofHouse_SceneScripts,

    .callback_count = 0, // lengthof(CeladonMansionRoofHouse_MapCallbacks),
    .callbacks = CeladonMansionRoofHouse_MapCallbacks,
};

static const struct CoordEvent CeladonMansionRoofHouse_CoordEvents[] = {
    0,
};

static const struct BGEvent CeladonMansionRoofHouse_BGEvents[] = {
    0,
};

static const struct WarpEventData CeladonMansionRoofHouse_WarpEvents[] = {
    warp_event(2, 7, CELADON_MANSION_ROOF, 3),
    warp_event(3, 7, CELADON_MANSION_ROOF, 3),
};

static const struct ObjEvent CeladonMansionRoofHouse_ObjectEvents[] = {
    object_event(3, 2, SPRITE_PHARMACIST, SPRITEMOVEDATA_STANDING_DOWN, 0, 2, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &CeladonMansionRoofHousePharmacistScript, -1),
};

const struct MapEvents CeladonMansionRoofHouse_MapEvents = {
    .warp_event_count = lengthof(CeladonMansionRoofHouse_WarpEvents),
    .warp_events = CeladonMansionRoofHouse_WarpEvents,

    .coord_event_count = 0, // lengthof(CeladonMansionRoofHouse_CoordEvents),
    .coord_events = CeladonMansionRoofHouse_CoordEvents,

    .bg_event_count = 0, // lengthof(CeladonMansionRoofHouse_BGEvents),
    .bg_events = CeladonMansionRoofHouse_BGEvents,

    .obj_event_count = lengthof(CeladonMansionRoofHouse_ObjectEvents),
    .obj_events = CeladonMansionRoofHouse_ObjectEvents,
};

//// CODE

bool CeladonMansionRoofHousePharmacistScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_TM03_CURSE)
    iftrue(GotCurse)
    writetext(CeladonMansionRoofHousePharmacistIntroText)
    promptbutton
    checktime(NITE)
    iftrue(Night)
    writetext(CeladonMansionRoofHousePharmacistNotNightText)
    waitbutton
    closetext
    s_end
Night:
    writetext(CeladonMansionRoofHousePharmacistStoryText)
    promptbutton
    verbosegiveitem(TM_CURSE, 1)
    iffalse(NoRoom)
    setevent(EVENT_GOT_TM03_CURSE)
GotCurse:
    writetext(CeladonMansionRoofHousePharmacistCurseText)
    waitbutton
NoRoom:
    closetext
    s_end
    SCRIPT_END
}
const txt_cmd_s CeladonMansionRoofHousePharmacistIntroText[] = {
    text_start("Let me recount a"
        t_line "terrifying tale…"
        t_done )
};
const txt_cmd_s CeladonMansionRoofHousePharmacistNotNightText[] = {
    text_start("Then again, it's"
        t_line "not as scary while"
        t_para "it's still light"
        t_line "outside."
        t_para "Come back after"
        t_line "sunset, OK?"
        t_done )
};
const txt_cmd_s CeladonMansionRoofHousePharmacistStoryText[] = {
    text_start("Once upon a time,"
        t_line "there was a little"
        t_para "boy who was given"
        t_line "a new BICYCLE…"
        t_para "He wanted to try"
        t_line "it right away…"
        t_para "He was having so"
        t_line "much fun that he"
        t_para "didn't notice the"
        t_line "sun had set…"
        t_para "While riding home"
        t_line "in the pitch-black"
        t_para "night, the bike"
        t_line "suddenly slowed!"
        t_para "The pedals became"
        t_line "heavy!"
        t_para "When he stopped"
        t_line "pedaling, the bike"
        t_para "began slipping"
        t_line "backwards!"
        t_para "It was as if the"
        t_line "bike were cursed"
        t_para "and trying to drag"
        t_line "him into oblivion!"
        t_para "…"
        t_para "…"
        t_para "SHRIEEEEK!"
        t_para "The boy had been"
        t_line "riding uphill on"
        t_cont "CYCLING ROAD!"
        t_para "…"
        t_line "Ba-dum ba-dum!"
        t_para "For listening so"
        t_line "patiently, you may"
        t_cont "take this--TM03!"
        t_done )
};
const txt_cmd_s CeladonMansionRoofHousePharmacistCurseText[] = {
    text_start("TM03 is CURSE."
        t_para "It's a terrifying"
        t_line "move that slowly"
        t_para "whittles down the"
        t_line "victim's HP."
        t_done )
    //db(0, 0) // filler
};
