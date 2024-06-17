#include "../constants.h"
#include "../util/scripting.h"
#include "CianwoodPharmacy.h"
//// EVENTS
enum {
    CIANWOODPHARMACY_PHARMACIST = 2,
};

const Script_fn_t CianwoodPharmacy_SceneScripts[] = {
    CianwoodPharmacy_MapScripts_DummyScene,
};

const struct MapCallback CianwoodPharmacy_MapCallbacks[] = {
    0,
};

const struct MapScripts CianwoodPharmacy_MapScripts = {
    .scene_script_count = lengthof(CianwoodPharmacy_SceneScripts),
    .scene_scripts = CianwoodPharmacy_SceneScripts,

    .callback_count = 0, // lengthof(CianwoodPharmacy_MapCallbacks),
    .callbacks = CianwoodPharmacy_MapCallbacks,
};

static const struct CoordEvent CianwoodPharmacy_CoordEvents[] = {
    0,
};

static const struct BGEvent CianwoodPharmacy_BGEvents[] = {
    bg_event(0, 1, BGEVENT_READ, &CianwoodPharmacyBookshelf),
    bg_event(1, 1, BGEVENT_READ, &CianwoodPharmacyBookshelf),
};

static const struct WarpEventData CianwoodPharmacy_WarpEvents[] = {
    warp_event(2, 7, CIANWOOD_CITY, 4),
    warp_event(3, 7, CIANWOOD_CITY, 4),
};

static const struct ObjEvent CianwoodPharmacy_ObjectEvents[] = {
    object_event(2, 3, SPRITE_PHARMACIST, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &CianwoodPharmacist, -1),
};

const struct MapEvents CianwoodPharmacy_MapEvents = {
    .warp_event_count = lengthof(CianwoodPharmacy_WarpEvents),
    .warp_events = CianwoodPharmacy_WarpEvents,

    .coord_event_count = 0, // lengthof(CianwoodPharmacy_CoordEvents),
    .coord_events = CianwoodPharmacy_CoordEvents,

    .bg_event_count = lengthof(CianwoodPharmacy_BGEvents),
    .bg_events = CianwoodPharmacy_BGEvents,

    .obj_event_count = lengthof(CianwoodPharmacy_ObjectEvents),
    .obj_events = CianwoodPharmacy_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "CianwoodPharmacy.h"

bool CianwoodPharmacy_MapScripts_DummyScene(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool CianwoodPharmacist(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_SECRETPOTION_FROM_PHARMACY)
    iftrue(Mart)
    checkevent(EVENT_JASMINE_EXPLAINED_AMPHYS_SICKNESS)
    iffalse(Mart)
    writetext(PharmacistGiveSecretpotionText)
    promptbutton
    giveitem(SECRETPOTION, 1)
    writetext(ReceivedSecretpotionText)
    playsound(SFX_KEY_ITEM)
    waitsfx
    itemnotify
    setevent(EVENT_GOT_SECRETPOTION_FROM_PHARMACY)
    writetext(PharmacistDescribeSecretpotionText)
    waitbutton
    closetext
    s_end
Mart:
    pokemart(MARTTYPE_PHARMACY, MART_CIANWOOD)
    closetext
    s_end
    SCRIPT_END
}
bool CianwoodPharmacyBookshelf(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(DifficultBookshelfScript)
    SCRIPT_END
}
const txt_cmd_s PharmacistGiveSecretpotionText[] = {
    text_start("Your #MON ap-"
        t_line "pear to be fine."
        t_para "Is something wor- "
        t_line "rying you?"
        t_para "…"
        t_para "The LIGHTHOUSE"
        t_line "#MON is in"
        t_cont "trouble?"
        t_para "I got it!"
        t_para "This ought to do"
        t_line "the trick."
        t_done )
};
const txt_cmd_s ReceivedSecretpotionText[] = {
    text_start("<PLAYER> received"
        t_line "SECRETPOTION."
        t_done )
};
const txt_cmd_s PharmacistDescribeSecretpotionText[] = {
    text_start("My SECRETPOTION is"
        t_line "a tad too strong."
        t_para "I only offer it in"
        t_line "an emergency."
        t_done )
    //db(0, 0) // filler
};
