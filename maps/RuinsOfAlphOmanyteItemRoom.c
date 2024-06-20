#include "../constants.h"
#include "../util/scripting.h"
#include "RuinsOfAlphOmanyteItemRoom.h"
//// EVENTS
enum {
    RUINSOFALPHOMANYTEITEMROOM_POKE_BALL1 = 2,
    RUINSOFALPHOMANYTEITEMROOM_POKE_BALL2,
    RUINSOFALPHOMANYTEITEMROOM_POKE_BALL3,
    RUINSOFALPHOMANYTEITEMROOM_POKE_BALL4,
};

const Script_fn_t RuinsOfAlphOmanyteItemRoom_SceneScripts[] = {
    0,
};

const struct MapCallback RuinsOfAlphOmanyteItemRoom_MapCallbacks[] = {
    0,
};

const struct MapScripts RuinsOfAlphOmanyteItemRoom_MapScripts = {
    .scene_script_count = 0, // lengthof(RuinsOfAlphOmanyteItemRoom_SceneScripts),
    .scene_scripts = RuinsOfAlphOmanyteItemRoom_SceneScripts,

    .callback_count = 0, // lengthof(RuinsOfAlphOmanyteItemRoom_MapCallbacks),
    .callbacks = RuinsOfAlphOmanyteItemRoom_MapCallbacks,
};

static const struct CoordEvent RuinsOfAlphOmanyteItemRoom_CoordEvents[] = {
    0,
};

static const struct BGEvent RuinsOfAlphOmanyteItemRoom_BGEvents[] = {
    bg_event(2, 1, BGEVENT_READ, &RuinsOfAlphOmanyteItemRoomAncientReplica),
    bg_event(5, 1, BGEVENT_READ, &RuinsOfAlphOmanyteItemRoomAncientReplica),
};

static const struct WarpEventData RuinsOfAlphOmanyteItemRoom_WarpEvents[] = {
    warp_event(3, 9, RUINS_OF_ALPH_OMANYTE_CHAMBER, 5),
    warp_event(4, 9, RUINS_OF_ALPH_OMANYTE_CHAMBER, 5),
    warp_event(3, 1, RUINS_OF_ALPH_OMANYTE_WORD_ROOM, 1),
    warp_event(4, 1, RUINS_OF_ALPH_OMANYTE_WORD_ROOM, 2),
};

static const struct ObjEvent RuinsOfAlphOmanyteItemRoom_ObjectEvents[] = {
    object_event(2, 6, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &RuinsOfAlphOmanyteItemRoomMysteryberry, EVENT_PICKED_UP_MYSTERYBERRY_FROM_OMANYTE_ITEM_ROOM),
    object_event(5, 6, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &RuinsOfAlphOmanyteItemRoomMysticWater, EVENT_PICKED_UP_MYSTIC_WATER_FROM_OMANYTE_ITEM_ROOM),
    object_event(2, 4, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &RuinsOfAlphOmanyteItemRoomStardust, EVENT_PICKED_UP_STARDUST_FROM_OMANYTE_ITEM_ROOM),
    object_event(5, 4, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &RuinsOfAlphOmanyteItemRoomStarPiece, EVENT_PICKED_UP_STAR_PIECE_FROM_OMANYTE_ITEM_ROOM),
};

const struct MapEvents RuinsOfAlphOmanyteItemRoom_MapEvents = {
    .warp_event_count = lengthof(RuinsOfAlphOmanyteItemRoom_WarpEvents),
    .warp_events = RuinsOfAlphOmanyteItemRoom_WarpEvents,

    .coord_event_count = 0, // lengthof(RuinsOfAlphOmanyteItemRoom_CoordEvents),
    .coord_events = RuinsOfAlphOmanyteItemRoom_CoordEvents,

    .bg_event_count = lengthof(RuinsOfAlphOmanyteItemRoom_BGEvents),
    .bg_events = RuinsOfAlphOmanyteItemRoom_BGEvents,

    .obj_event_count = lengthof(RuinsOfAlphOmanyteItemRoom_ObjectEvents),
    .obj_events = RuinsOfAlphOmanyteItemRoom_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "RuinsOfAlphOmanyteItemRoom.h"

const struct ItemBall RuinsOfAlphOmanyteItemRoomMysteryberry = {MYSTERYBERRY, 1};
const struct ItemBall RuinsOfAlphOmanyteItemRoomMysticWater = {MYSTIC_WATER, 1};
const struct ItemBall RuinsOfAlphOmanyteItemRoomStardust = {STARDUST, 1};
const struct ItemBall RuinsOfAlphOmanyteItemRoomStarPiece = {STAR_PIECE, 1};
bool RuinsOfAlphOmanyteItemRoomAncientReplica(script_s* s) {
    SCRIPT_BEGIN
    jumptext(RuinsOfAlphOmanyteItemRoomAncientReplicaText)
    SCRIPT_END
}
const txt_cmd_s RuinsOfAlphOmanyteItemRoomAncientReplicaText[] = {
    text_start("It's a replica of"
        t_line "an ancient #-"
        t_cont "MON."
        t_done )
    //db(0, 0) // filler
};
