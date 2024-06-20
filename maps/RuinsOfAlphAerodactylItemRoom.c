#include "../constants.h"
#include "../util/scripting.h"
#include "RuinsOfAlphAerodactylItemRoom.h"
//// EVENTS
enum {
    RUINSOFALPHAERODACTYLITEMROOM_POKE_BALL1 = 2,
    RUINSOFALPHAERODACTYLITEMROOM_POKE_BALL2,
    RUINSOFALPHAERODACTYLITEMROOM_POKE_BALL3,
    RUINSOFALPHAERODACTYLITEMROOM_POKE_BALL4,
};

const Script_fn_t RuinsOfAlphAerodactylItemRoom_SceneScripts[] = {
    0,
};

const struct MapCallback RuinsOfAlphAerodactylItemRoom_MapCallbacks[] = {
    0,
};

const struct MapScripts RuinsOfAlphAerodactylItemRoom_MapScripts = {
    .scene_script_count = 0, // lengthof(RuinsOfAlphAerodactylItemRoom_SceneScripts),
    .scene_scripts = RuinsOfAlphAerodactylItemRoom_SceneScripts,

    .callback_count = 0, // lengthof(RuinsOfAlphAerodactylItemRoom_MapCallbacks),
    .callbacks = RuinsOfAlphAerodactylItemRoom_MapCallbacks,
};

static const struct CoordEvent RuinsOfAlphAerodactylItemRoom_CoordEvents[] = {
    0,
};

static const struct BGEvent RuinsOfAlphAerodactylItemRoom_BGEvents[] = {
    bg_event(2, 1, BGEVENT_READ, &RuinsOfAlphAerodactylItemRoomAncientReplica),
    bg_event(5, 1, BGEVENT_READ, &RuinsOfAlphAerodactylItemRoomAncientReplica),
};

static const struct WarpEventData RuinsOfAlphAerodactylItemRoom_WarpEvents[] = {
    warp_event(3, 9, RUINS_OF_ALPH_AERODACTYL_CHAMBER, 5),
    warp_event(4, 9, RUINS_OF_ALPH_AERODACTYL_CHAMBER, 5),
    warp_event(3, 1, RUINS_OF_ALPH_AERODACTYL_WORD_ROOM, 1),
    warp_event(4, 1, RUINS_OF_ALPH_AERODACTYL_WORD_ROOM, 2),
};

static const struct ObjEvent RuinsOfAlphAerodactylItemRoom_ObjectEvents[] = {
    object_event(2, 6, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &RuinsOfAlphAerodactylItemRoomGoldBerry, EVENT_PICKED_UP_GOLD_BERRY_FROM_AERODACTYL_ITEM_ROOM),
    object_event(5, 6, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &RuinsOfAlphAerodactylItemRoomMoonStone, EVENT_PICKED_UP_MOON_STONE_FROM_AERODACTYL_ITEM_ROOM),
    object_event(2, 4, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &RuinsOfAlphAerodactylItemRoomHealPowder, EVENT_PICKED_UP_HEAL_POWDER_FROM_AERODACTYL_ITEM_ROOM),
    object_event(5, 4, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &RuinsOfAlphAerodactylItemRoomEnergyRoot, EVENT_PICKED_UP_ENERGY_ROOT_FROM_AERODACTYL_ITEM_ROOM),
};

const struct MapEvents RuinsOfAlphAerodactylItemRoom_MapEvents = {
    .warp_event_count = lengthof(RuinsOfAlphAerodactylItemRoom_WarpEvents),
    .warp_events = RuinsOfAlphAerodactylItemRoom_WarpEvents,

    .coord_event_count = 0, // lengthof(RuinsOfAlphAerodactylItemRoom_CoordEvents),
    .coord_events = RuinsOfAlphAerodactylItemRoom_CoordEvents,

    .bg_event_count = lengthof(RuinsOfAlphAerodactylItemRoom_BGEvents),
    .bg_events = RuinsOfAlphAerodactylItemRoom_BGEvents,

    .obj_event_count = lengthof(RuinsOfAlphAerodactylItemRoom_ObjectEvents),
    .obj_events = RuinsOfAlphAerodactylItemRoom_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "RuinsOfAlphAerodactylItemRoom.h"

const struct ItemBall RuinsOfAlphAerodactylItemRoomGoldBerry = {GOLD_BERRY, 1};
const struct ItemBall RuinsOfAlphAerodactylItemRoomMoonStone = {MOON_STONE, 1};
const struct ItemBall RuinsOfAlphAerodactylItemRoomHealPowder = {HEAL_POWDER, 1};
const struct ItemBall RuinsOfAlphAerodactylItemRoomEnergyRoot = {ENERGY_ROOT, 1};
bool RuinsOfAlphAerodactylItemRoomAncientReplica(script_s* s) {
    SCRIPT_BEGIN
    jumptext(RuinsOfAlphAerodactylItemRoomAncientReplicaText)
    SCRIPT_END
}
const txt_cmd_s RuinsOfAlphAerodactylItemRoomAncientReplicaText[] = {
    text_start("It's a replica of"
        t_line "an ancient #-"
        t_cont "MON."
        t_done )
    //db(0, 0) // filler
};
