#include "../constants.h"
#include "../util/scripting.h"
#include "IcePathB2FMahoganySide.h"
//// EVENTS
enum {
    ICEPATHB2FMAHOGANYSIDE_BOULDER1 = 2,
    ICEPATHB2FMAHOGANYSIDE_BOULDER2,
    ICEPATHB2FMAHOGANYSIDE_BOULDER3,
    ICEPATHB2FMAHOGANYSIDE_BOULDER4,
    ICEPATHB2FMAHOGANYSIDE_POKE_BALL1,
    ICEPATHB2FMAHOGANYSIDE_POKE_BALL2,
};

const Script_fn_t IcePathB2FMahoganySide_SceneScripts[] = {
    0,
};

const struct MapCallback IcePathB2FMahoganySide_MapCallbacks[] = {
    0,
};

const struct MapScripts IcePathB2FMahoganySide_MapScripts = {
    .scene_script_count = 0, // lengthof(IcePathB2FMahoganySide_SceneScripts),
    .scene_scripts = IcePathB2FMahoganySide_SceneScripts,

    .callback_count = 0, // lengthof(IcePathB2FMahoganySide_MapCallbacks),
    .callbacks = IcePathB2FMahoganySide_MapCallbacks,
};

static const struct CoordEvent IcePathB2FMahoganySide_CoordEvents[] = {
    0,
};

static const struct BGEvent IcePathB2FMahoganySide_BGEvents[] = {
    bg_event(0, 17, BGEVENT_ITEM, &IcePathB2FMahoganySideHiddenCarbos),
};

static const struct WarpEventData IcePathB2FMahoganySide_WarpEvents[] = {
    warp_event(17, 1, ICE_PATH_B1F, 2),
    warp_event(9, 11, ICE_PATH_B3F, 1),
    warp_event(11, 4, ICE_PATH_B1F, 3),
    warp_event(4, 6, ICE_PATH_B1F, 4),
    warp_event(4, 12, ICE_PATH_B1F, 5),
    warp_event(12, 12, ICE_PATH_B1F, 6),
};

static const struct ObjEvent IcePathB2FMahoganySide_ObjectEvents[] = {
    object_event(11, 3, SPRITE_BOULDER, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &IcePathB2FMahoganySideBoulder, EVENT_BOULDER_IN_ICE_PATH_1A),
    object_event(4, 7, SPRITE_BOULDER, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &IcePathB2FMahoganySideBoulder, EVENT_BOULDER_IN_ICE_PATH_2A),
    object_event(3, 12, SPRITE_BOULDER, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &IcePathB2FMahoganySideBoulder, EVENT_BOULDER_IN_ICE_PATH_3A),
    object_event(12, 13, SPRITE_BOULDER, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &IcePathB2FMahoganySideBoulder, EVENT_BOULDER_IN_ICE_PATH_4A),
    object_event(8, 9, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &IcePathB2FMahoganySideFullHeal, EVENT_ICE_PATH_B2F_MAHOGANY_SIDE_FULL_HEAL),
    object_event(0, 2, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &IcePathB2FMahoganySideMaxPotion, EVENT_ICE_PATH_B2F_MAHOGANY_SIDE_MAX_POTION),
};

const struct MapEvents IcePathB2FMahoganySide_MapEvents = {
    .warp_event_count = lengthof(IcePathB2FMahoganySide_WarpEvents),
    .warp_events = IcePathB2FMahoganySide_WarpEvents,

    .coord_event_count = 0, // lengthof(IcePathB2FMahoganySide_CoordEvents),
    .coord_events = IcePathB2FMahoganySide_CoordEvents,

    .bg_event_count = lengthof(IcePathB2FMahoganySide_BGEvents),
    .bg_events = IcePathB2FMahoganySide_BGEvents,

    .obj_event_count = lengthof(IcePathB2FMahoganySide_ObjectEvents),
    .obj_events = IcePathB2FMahoganySide_ObjectEvents,
};

//// CODE

bool IcePathB2FMahoganySideBoulder(script_s* s) {
    SCRIPT_BEGIN
    jumptext(IcePathB2FMahoganySideBoulderText)
    SCRIPT_END
}
const struct ItemBall IcePathB2FMahoganySideFullHeal = {FULL_HEAL, 1};
const struct ItemBall IcePathB2FMahoganySideMaxPotion = {MAX_POTION, 1};
const struct HiddenItem IcePathB2FMahoganySideHiddenCarbos = {CARBOS, EVENT_ICE_PATH_B2F_MAHOGANY_SIDE_HIDDEN_CARBOS};
const txt_cmd_s IcePathB2FMahoganySideBoulderText[] = {
    text_start("It's immovably"
        t_line "imbedded in ice."
        t_done )
    //db(0, 0) // filler
};
