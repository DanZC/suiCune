#include "../constants.h"
#include "../util/scripting.h"
#include "DarkCaveBlackthornEntrance.h"
//// EVENTS
enum {
    DARKCAVEBLACKTHORNENTRANCE_PHARMACIST = 2,
    DARKCAVEBLACKTHORNENTRANCE_POKE_BALL1,
    DARKCAVEBLACKTHORNENTRANCE_POKE_BALL2,
};

const Script_fn_t DarkCaveBlackthornEntrance_SceneScripts[] = {
    0,
};

const struct MapCallback DarkCaveBlackthornEntrance_MapCallbacks[] = {
    0,
};

const struct MapScripts DarkCaveBlackthornEntrance_MapScripts = {
    .scene_script_count = 0, // lengthof(DarkCaveBlackthornEntrance_SceneScripts),
    .scene_scripts = DarkCaveBlackthornEntrance_SceneScripts,

    .callback_count = 0, // lengthof(DarkCaveBlackthornEntrance_MapCallbacks),
    .callbacks = DarkCaveBlackthornEntrance_MapCallbacks,
};

static const struct CoordEvent DarkCaveBlackthornEntrance_CoordEvents[] = {
    0,
};

static const struct BGEvent DarkCaveBlackthornEntrance_BGEvents[] = {
    0,
};

static const struct WarpEventData DarkCaveBlackthornEntrance_WarpEvents[] = {
    warp_event(23, 3, ROUTE_45, 1),
    warp_event(3, 25, DARK_CAVE_VIOLET_ENTRANCE, 2),
};

static const struct ObjEvent DarkCaveBlackthornEntrance_ObjectEvents[] = {
    object_event(7, 3, SPRITE_PHARMACIST, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &DarkCaveBlackthornEntrancePharmacistScript, -1),
    object_event(21, 24, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &DarkCaveBlackthornEntranceRevive, EVENT_DARK_CAVE_BLACKTHORN_ENTRANCE_REVIVE),
    object_event(7, 22, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &DarkCaveBlackthornEntranceTMSnore, EVENT_DARK_CAVE_BLACKTHORN_ENTRANCE_TM_SNORE),
};

const struct MapEvents DarkCaveBlackthornEntrance_MapEvents = {
    .warp_event_count = lengthof(DarkCaveBlackthornEntrance_WarpEvents),
    .warp_events = DarkCaveBlackthornEntrance_WarpEvents,

    .coord_event_count = 0, // lengthof(DarkCaveBlackthornEntrance_CoordEvents),
    .coord_events = DarkCaveBlackthornEntrance_CoordEvents,

    .bg_event_count = 0, // lengthof(DarkCaveBlackthornEntrance_BGEvents),
    .bg_events = DarkCaveBlackthornEntrance_BGEvents,

    .obj_event_count = lengthof(DarkCaveBlackthornEntrance_ObjectEvents),
    .obj_events = DarkCaveBlackthornEntrance_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "DarkCaveBlackthornEntrance.h"

bool DarkCaveBlackthornEntrancePharmacistScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_BLACKGLASSES_IN_DARK_CAVE)
    iftrue(GotBlackglasses)
    writetext(DarkCaveBlackthornEntrancePharmacistText1)
    promptbutton
    verbosegiveitem(BLACKGLASSES, 1)
    iffalse(PackFull)
    setevent(EVENT_GOT_BLACKGLASSES_IN_DARK_CAVE)
GotBlackglasses:
    writetext(DarkCaveBlackthornEntrancePharmacistText2)
    waitbutton
PackFull:
    closetext
    s_end
    SCRIPT_END
}
const struct ItemBall DarkCaveBlackthornEntranceRevive = {REVIVE, 1};
const struct ItemBall DarkCaveBlackthornEntranceTMSnore = {TM_SNORE, 1};
const txt_cmd_s DarkCaveBlackthornEntrancePharmacistText1[] = {
    text_start("Whoa! You startled"
        t_line "me there!"
        t_para "I had my BLACK-"
        t_line "GLASSES on, so I"
        t_para "didn't notice you"
        t_line "at all."
        t_para "What am I doing"
        t_line "here?"
        t_para "Hey, don't you"
        t_line "worry about it."
        t_para "I'll give you a"
        t_line "pair of BLACK-"
        t_cont "GLASSES, so forget"
        t_cont "you saw me, OK?"
        t_done )
};
const txt_cmd_s DarkCaveBlackthornEntrancePharmacistText2[] = {
    text_start("BLACKGLASSES ups"
        t_line "the power of dark-"
        t_cont "type moves."
        t_done )
    //db(0, 0) // filler
};
