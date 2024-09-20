#include "../constants.h"
#include "../util/scripting.h"
#include "CopycatsHouse1F.h"
//// EVENTS
enum {
    COPYCATSHOUSE1F_POKEFAN_M = 2,
    COPYCATSHOUSE1F_POKEFAN_F,
    COPYCATSHOUSE1F_CLEFAIRY,
};

const Script_fn_t CopycatsHouse1F_SceneScripts[] = {
    0,
};

const struct MapCallback CopycatsHouse1F_MapCallbacks[] = {
    0,
};

const struct MapScripts CopycatsHouse1F_MapScripts = {
    .scene_script_count = 0, // lengthof(CopycatsHouse1F_SceneScripts),
    .scene_scripts = CopycatsHouse1F_SceneScripts,

    .callback_count = 0, // lengthof(CopycatsHouse1F_MapCallbacks),
    .callbacks = CopycatsHouse1F_MapCallbacks,
};

static const struct CoordEvent CopycatsHouse1F_CoordEvents[] = {
    0,
};

static const struct BGEvent CopycatsHouse1F_BGEvents[] = {
    0,
};

static const struct WarpEventData CopycatsHouse1F_WarpEvents[] = {
    warp_event(2, 7, SAFFRON_CITY, 8),
    warp_event(3, 7, SAFFRON_CITY, 8),
    warp_event(2, 0, COPYCATS_HOUSE_2F, 1),
};

static const struct ObjEvent CopycatsHouse1F_ObjectEvents[] = {
    object_event(2, 3, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &CopycatsHouse1FPokefanMScript, -1),
    object_event(5, 4, SPRITE_POKEFAN_F, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &CopycatsHouse1FPokefanFScript, -1),
    object_event(6, 6, SPRITE_CLEFAIRY, SPRITEMOVEDATA_POKEMON, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &CopycatsHouse1FBlisseyScript, -1),
};

const struct MapEvents CopycatsHouse1F_MapEvents = {
    .warp_event_count = lengthof(CopycatsHouse1F_WarpEvents),
    .warp_events = CopycatsHouse1F_WarpEvents,

    .coord_event_count = 0, // lengthof(CopycatsHouse1F_CoordEvents),
    .coord_events = CopycatsHouse1F_CoordEvents,

    .bg_event_count = 0, // lengthof(CopycatsHouse1F_BGEvents),
    .bg_events = CopycatsHouse1F_BGEvents,

    .obj_event_count = lengthof(CopycatsHouse1F_ObjectEvents),
    .obj_events = CopycatsHouse1F_ObjectEvents,
};

//// CODE

bool CopycatsHouse1FPokefanMScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CopycatsHouse1FPokefanMText)
    SCRIPT_END
}
bool CopycatsHouse1FPokefanFScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_RETURNED_MACHINE_PART)
    iftrue(ReturnedMachinePart)
    writetext(CopycatsHouse1FPokefanFText)
    waitbutton
    closetext
    s_end
ReturnedMachinePart:
    writetext(CopycatsHouse1FPokefanFText_ReturnedMachinePart)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool CopycatsHouse1FBlisseyScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(CopycatsHouse1FBlisseyText)
    playcry(BLISSEY)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const txt_cmd_s CopycatsHouse1FPokefanMText[] = {
    text_start("My daughter likes"
        t_line "to mimic people."
        t_para "Her mimicry has"
        t_line "earned her the"
        t_para "nickname COPYCAT"
        t_line "around here."
        t_done )
};
const txt_cmd_s CopycatsHouse1FPokefanFText[] = {
    text_start("My daughter is so"
        t_line "self-centered…"
        t_para "She only has a few"
        t_line "friends."
        t_done )
};
const txt_cmd_s CopycatsHouse1FPokefanFText_ReturnedMachinePart[] = {
    text_start("She recently lost"
        t_line "the # DOLL that"
        t_para "a boy gave her"
        t_line "three years ago."
        t_para "Ever since then,"
        t_line "she's gotten even"
        t_cont "better at mimicry…"
        t_done )
};
const txt_cmd_s CopycatsHouse1FBlisseyText[] = {
    text_start("BLISSEY: Bliisii!"
        t_done )
    //db(0, 0) // filler
};
