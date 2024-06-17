#include "../constants.h"
#include "../util/scripting.h"
#include "CianwoodPhotoStudio.h"
//// EVENTS
enum {
    CIANWOODPHOTOSTUDIO_FISHING_GURU = 2,
};

const Script_fn_t CianwoodPhotoStudio_SceneScripts[] = {
    0,
};

const struct MapCallback CianwoodPhotoStudio_MapCallbacks[] = {
    0,
};

const struct MapScripts CianwoodPhotoStudio_MapScripts = {
    .scene_script_count = 0, // lengthof(CianwoodPhotoStudio_SceneScripts),
    .scene_scripts = CianwoodPhotoStudio_SceneScripts,

    .callback_count = 0, // lengthof(CianwoodPhotoStudio_MapCallbacks),
    .callbacks = CianwoodPhotoStudio_MapCallbacks,
};

static const struct CoordEvent CianwoodPhotoStudio_CoordEvents[] = {
    0,
};

static const struct BGEvent CianwoodPhotoStudio_BGEvents[] = {
    0,
};

static const struct WarpEventData CianwoodPhotoStudio_WarpEvents[] = {
    warp_event(2, 7, CIANWOOD_CITY, 5),
    warp_event(3, 7, CIANWOOD_CITY, 5),
};

static const struct ObjEvent CianwoodPhotoStudio_ObjectEvents[] = {
    object_event(2, 3, SPRITE_FISHING_GURU, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &CianwoodPhotoStudioFishingGuruScript, -1),
};

const struct MapEvents CianwoodPhotoStudio_MapEvents = {
    .warp_event_count = lengthof(CianwoodPhotoStudio_WarpEvents),
    .warp_events = CianwoodPhotoStudio_WarpEvents,

    .coord_event_count = 0, // lengthof(CianwoodPhotoStudio_CoordEvents),
    .coord_events = CianwoodPhotoStudio_CoordEvents,

    .bg_event_count = 0, // lengthof(CianwoodPhotoStudio_BGEvents),
    .bg_events = CianwoodPhotoStudio_BGEvents,

    .obj_event_count = lengthof(CianwoodPhotoStudio_ObjectEvents),
    .obj_events = CianwoodPhotoStudio_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "CianwoodPhotoStudio.h"

bool CianwoodPhotoStudioFishingGuruScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(CianwoodPhotoStudioFishingGuruText_Question)
    yesorno
    iffalse(Refused)
    writetext(CianwoodPhotoStudioFishingGuruText_Yes)
    waitbutton
    special(PhotoStudio)
    waitbutton
    closetext
    s_end
Refused:
    writetext(CianwoodPhotoStudioFishingGuruText_No)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const txt_cmd_s CianwoodPhotoStudioFishingGuruText_Question[] = {
    text_start("You have magnifi-"
        t_line "cent #MON with"
        t_cont "you."
        t_para "How about a photo"
        t_line "for a souvenir?"
        t_done )
};
const txt_cmd_s CianwoodPhotoStudioFishingGuruText_Yes[] = {
    text_start("OK! Big smile now!"
        t_done )
};
const txt_cmd_s CianwoodPhotoStudioFishingGuruText_No[] = {
    text_start("Oh, that's too"
        t_line "bad. I thought it"
        t_para "would be a great"
        t_line "memento…"
        t_done )
    //db(0, 0) // filler
};
