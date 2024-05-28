#include "../constants.h"
#include "../util/scripting.h"
#include "RuinsOfAlphKabutoItemRoom.h"
//// EVENTS
enum {
    RUINSOFALPHKABUTOITEMROOM_POKE_BALL1 = 2,
    RUINSOFALPHKABUTOITEMROOM_POKE_BALL2,
    RUINSOFALPHKABUTOITEMROOM_POKE_BALL3,
    RUINSOFALPHKABUTOITEMROOM_POKE_BALL4,
};

const Script_fn_t RuinsOfAlphKabutoItemRoom_SceneScripts[] = {
    0,
};

const struct MapCallback RuinsOfAlphKabutoItemRoom_MapCallbacks[] = {
    0,
};

const struct MapScripts RuinsOfAlphKabutoItemRoom_MapScripts = {
    .scene_script_count = 0, // lengthof(RuinsOfAlphKabutoItemRoom_SceneScripts),
    .scene_scripts = RuinsOfAlphKabutoItemRoom_SceneScripts,

    .callback_count = 0, // lengthof(RuinsOfAlphKabutoItemRoom_MapCallbacks),
    .callbacks = RuinsOfAlphKabutoItemRoom_MapCallbacks,
};

static const struct CoordEvent RuinsOfAlphKabutoItemRoom_CoordEvents[] = {
    0,
};

static const struct BGEvent RuinsOfAlphKabutoItemRoom_BGEvents[] = {
    bg_event(2, 1, BGEVENT_READ, &RuinsOfAlphKabutoItemRoomAncientReplica),
    bg_event(5, 1, BGEVENT_READ, &RuinsOfAlphKabutoItemRoomAncientReplica),
};

static const struct WarpEventData RuinsOfAlphKabutoItemRoom_WarpEvents[] = {
    warp_event(3, 9, RUINS_OF_ALPH_KABUTO_CHAMBER, 5),
    warp_event(4, 9, RUINS_OF_ALPH_KABUTO_CHAMBER, 5),
    warp_event(3, 1, RUINS_OF_ALPH_KABUTO_WORD_ROOM, 1),
    warp_event(4, 1, RUINS_OF_ALPH_KABUTO_WORD_ROOM, 2),
};

static const struct ObjEvent RuinsOfAlphKabutoItemRoom_ObjectEvents[] = {
    object_event(2, 6, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &RuinsOfAlphKabutoItemRoomBerry, EVENT_PICKED_UP_BERRY_FROM_KABUTO_ITEM_ROOM),
    object_event(5, 6, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &RuinsOfAlphKabutoItemRoomPsncureberry, EVENT_PICKED_UP_PSNCUREBERRY_FROM_KABUTO_ITEM_ROOM),
    object_event(2, 4, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &RuinsOfAlphKabutoItemRoomHealPowder, EVENT_PICKED_UP_HEAL_POWDER_FROM_KABUTO_ITEM_ROOM),
    object_event(5, 4, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &RuinsOfAlphKabutoItemRoomEnergypowder, EVENT_PICKED_UP_ENERGYPOWDER_FROM_KABUTO_ITEM_ROOM),
};

const struct MapEvents RuinsOfAlphKabutoItemRoom_MapEvents = {
    .warp_event_count = lengthof(RuinsOfAlphKabutoItemRoom_WarpEvents),
    .warp_events = RuinsOfAlphKabutoItemRoom_WarpEvents,

    .coord_event_count = 0, // lengthof(RuinsOfAlphKabutoItemRoom_CoordEvents),
    .coord_events = RuinsOfAlphKabutoItemRoom_CoordEvents,

    .bg_event_count = lengthof(RuinsOfAlphKabutoItemRoom_BGEvents),
    .bg_events = RuinsOfAlphKabutoItemRoom_BGEvents,

    .obj_event_count = lengthof(RuinsOfAlphKabutoItemRoom_ObjectEvents),
    .obj_events = RuinsOfAlphKabutoItemRoom_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "RuinsOfAlphKabutoItemRoom.h"

const struct ItemBall RuinsOfAlphKabutoItemRoomBerry = {BERRY, 1};
const struct ItemBall RuinsOfAlphKabutoItemRoomPsncureberry = {PSNCUREBERRY, 1};
const struct ItemBall RuinsOfAlphKabutoItemRoomHealPowder = {HEAL_POWDER, 1};
const struct ItemBall RuinsOfAlphKabutoItemRoomEnergypowder = {ENERGYPOWDER, 1};
bool RuinsOfAlphKabutoItemRoomAncientReplica(script_s* s) {
    SCRIPT_BEGIN
    jumptext(RuinsOfAlphKabutoItemRoomAncientReplicaText)
    SCRIPT_END
}
const txt_cmd_s RuinsOfAlphKabutoItemRoomAncientReplicaText[] = {
    text_start("It's a replica of"
        t_line "an ancient #-"
        t_cont "MON."
        t_done )
    //db(0, 0) // filler
};
