#include "../constants.h"
#include "../util/scripting.h"
#include "RuinsOfAlphHoOhItemRoom.h"
//// EVENTS
enum {
    RUINSOFALPHHOOHITEMROOM_POKE_BALL1 = 2,
    RUINSOFALPHHOOHITEMROOM_POKE_BALL2,
    RUINSOFALPHHOOHITEMROOM_POKE_BALL3,
    RUINSOFALPHHOOHITEMROOM_POKE_BALL4,
};

const Script_fn_t RuinsOfAlphHoOhItemRoom_SceneScripts[] = {
    0,
};

const struct MapCallback RuinsOfAlphHoOhItemRoom_MapCallbacks[] = {
    0,
};

const struct MapScripts RuinsOfAlphHoOhItemRoom_MapScripts = {
    .scene_script_count = 0, // lengthof(RuinsOfAlphHoOhItemRoom_SceneScripts),
    .scene_scripts = RuinsOfAlphHoOhItemRoom_SceneScripts,

    .callback_count = 0, // lengthof(RuinsOfAlphHoOhItemRoom_MapCallbacks),
    .callbacks = RuinsOfAlphHoOhItemRoom_MapCallbacks,
};

static const struct CoordEvent RuinsOfAlphHoOhItemRoom_CoordEvents[] = {
    0,
};

static const struct BGEvent RuinsOfAlphHoOhItemRoom_BGEvents[] = {
    bg_event(2, 1, BGEVENT_READ, &RuinsOfAlphHoOhItemRoomAncientReplica),
    bg_event(5, 1, BGEVENT_READ, &RuinsOfAlphHoOhItemRoomAncientReplica),
};

static const struct WarpEventData RuinsOfAlphHoOhItemRoom_WarpEvents[] = {
    warp_event(3, 9, RUINS_OF_ALPH_HO_OH_CHAMBER, 5),
    warp_event(4, 9, RUINS_OF_ALPH_HO_OH_CHAMBER, 5),
    warp_event(3, 1, RUINS_OF_ALPH_HO_OH_WORD_ROOM, 1),
    warp_event(4, 1, RUINS_OF_ALPH_HO_OH_WORD_ROOM, 2),
};

static const struct ObjEvent RuinsOfAlphHoOhItemRoom_ObjectEvents[] = {
    object_event(2, 6, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &RuinsOfAlphHoOhItemRoomGoldBerry, EVENT_PICKED_UP_GOLD_BERRY_FROM_HO_OH_ITEM_ROOM),
    object_event(5, 6, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &RuinsOfAlphHoOhItemRoomMysteryberry, EVENT_PICKED_UP_MYSTERYBERRY_FROM_HO_OH_ITEM_ROOM),
    object_event(2, 4, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &RuinsOfAlphHoOhItemRoomRevivalHerb, EVENT_PICKED_UP_REVIVAL_HERB_FROM_HO_OH_ITEM_ROOM),
    object_event(5, 4, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &RuinsOfAlphHoOhItemRoomCharcoal, EVENT_PICKED_UP_CHARCOAL_FROM_HO_OH_ITEM_ROOM),
};

const struct MapEvents RuinsOfAlphHoOhItemRoom_MapEvents = {
    .warp_event_count = lengthof(RuinsOfAlphHoOhItemRoom_WarpEvents),
    .warp_events = RuinsOfAlphHoOhItemRoom_WarpEvents,

    .coord_event_count = 0, // lengthof(RuinsOfAlphHoOhItemRoom_CoordEvents),
    .coord_events = RuinsOfAlphHoOhItemRoom_CoordEvents,

    .bg_event_count = lengthof(RuinsOfAlphHoOhItemRoom_BGEvents),
    .bg_events = RuinsOfAlphHoOhItemRoom_BGEvents,

    .obj_event_count = lengthof(RuinsOfAlphHoOhItemRoom_ObjectEvents),
    .obj_events = RuinsOfAlphHoOhItemRoom_ObjectEvents,
};

//// CODE

const struct ItemBall RuinsOfAlphHoOhItemRoomGoldBerry = {GOLD_BERRY, 1};
const struct ItemBall RuinsOfAlphHoOhItemRoomMysteryberry = {MYSTERYBERRY, 1};
const struct ItemBall RuinsOfAlphHoOhItemRoomRevivalHerb = {REVIVAL_HERB, 1};
const struct ItemBall RuinsOfAlphHoOhItemRoomCharcoal = {CHARCOAL, 1};
bool RuinsOfAlphHoOhItemRoomAncientReplica(script_s* s) {
    SCRIPT_BEGIN
    jumptext(RuinsOfAlphHoOhItemRoomAncientReplicaText)
    SCRIPT_END
}
const txt_cmd_s RuinsOfAlphHoOhItemRoomAncientReplicaText[] = {
    text_start("It's a replica of"
        t_line "an ancient #-"
        t_cont "MON."
        t_done )
    //db(0, 0) // filler
};
