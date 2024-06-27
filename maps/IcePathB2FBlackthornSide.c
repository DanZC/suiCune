#include "../constants.h"
#include "../util/scripting.h"
#include "IcePathB2FBlackthornSide.h"
//// EVENTS
enum {
    ICEPATHB2FBLACKTHORNSIDE_POKE_BALL = 2,
};

const Script_fn_t IcePathB2FBlackthornSide_SceneScripts[] = {
    0,
};

const struct MapCallback IcePathB2FBlackthornSide_MapCallbacks[] = {
    0,
};

const struct MapScripts IcePathB2FBlackthornSide_MapScripts = {
    .scene_script_count = 0, // lengthof(IcePathB2FBlackthornSide_SceneScripts),
    .scene_scripts = IcePathB2FBlackthornSide_SceneScripts,

    .callback_count = 0, // lengthof(IcePathB2FBlackthornSide_MapCallbacks),
    .callbacks = IcePathB2FBlackthornSide_MapCallbacks,
};

static const struct CoordEvent IcePathB2FBlackthornSide_CoordEvents[] = {
    0,
};

static const struct BGEvent IcePathB2FBlackthornSide_BGEvents[] = {
    bg_event(2, 10, BGEVENT_ITEM, &IcePathB2FBlackthornSideHiddenIceHeal),
};

static const struct WarpEventData IcePathB2FBlackthornSide_WarpEvents[] = {
    warp_event(3, 15, ICE_PATH_B1F, 8),
    warp_event(3, 3, ICE_PATH_B3F, 2),
};

static const struct ObjEvent IcePathB2FBlackthornSide_ObjectEvents[] = {
    object_event(8, 16, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &IcePathB2FBlackthornSideTMRest, EVENT_ICE_PATH_B2F_BLACKTHORN_SIDE_TM_REST),
};

const struct MapEvents IcePathB2FBlackthornSide_MapEvents = {
    .warp_event_count = lengthof(IcePathB2FBlackthornSide_WarpEvents),
    .warp_events = IcePathB2FBlackthornSide_WarpEvents,

    .coord_event_count = 0, // lengthof(IcePathB2FBlackthornSide_CoordEvents),
    .coord_events = IcePathB2FBlackthornSide_CoordEvents,

    .bg_event_count = lengthof(IcePathB2FBlackthornSide_BGEvents),
    .bg_events = IcePathB2FBlackthornSide_BGEvents,

    .obj_event_count = lengthof(IcePathB2FBlackthornSide_ObjectEvents),
    .obj_events = IcePathB2FBlackthornSide_ObjectEvents,
};

//// CODE

const struct ItemBall IcePathB2FBlackthornSideTMRest = {TM_REST, 1};
const struct HiddenItem IcePathB2FBlackthornSideHiddenIceHeal = {ICE_HEAL, EVENT_ICE_PATH_B2F_BLACKTHORN_SIDE_HIDDEN_ICE_HEAL};
    //db(0, 0) // filler
