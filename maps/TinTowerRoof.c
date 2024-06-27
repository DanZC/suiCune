#include "../constants.h"
#include "../util/scripting.h"
#include "TinTowerRoof.h"
//// EVENTS
enum {
    TINTOWERROOF_HO_OH = 2,
};

const Script_fn_t TinTowerRoof_SceneScripts[] = {
    0,
};

const struct MapCallback TinTowerRoof_MapCallbacks[] = {
    map_callback(MAPCALLBACK_OBJECTS, TinTowerRoof_MapScripts_HoOh),
};

const struct MapScripts TinTowerRoof_MapScripts = {
    .scene_script_count = 0, // lengthof(TinTowerRoof_SceneScripts),
    .scene_scripts = TinTowerRoof_SceneScripts,

    .callback_count = lengthof(TinTowerRoof_MapCallbacks),
    .callbacks = TinTowerRoof_MapCallbacks,
};

static const struct CoordEvent TinTowerRoof_CoordEvents[] = {
    0,
};

static const struct BGEvent TinTowerRoof_BGEvents[] = {
    0,
};

static const struct WarpEventData TinTowerRoof_WarpEvents[] = {
    warp_event(9, 13, TIN_TOWER_9F, 4),
};

static const struct ObjEvent TinTowerRoof_ObjectEvents[] = {
    object_event(9, 5, SPRITE_HO_OH, SPRITEMOVEDATA_POKEMON, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &TinTowerHoOh, EVENT_TIN_TOWER_ROOF_HO_OH),
};

const struct MapEvents TinTowerRoof_MapEvents = {
    .warp_event_count = lengthof(TinTowerRoof_WarpEvents),
    .warp_events = TinTowerRoof_WarpEvents,

    .coord_event_count = 0, // lengthof(TinTowerRoof_CoordEvents),
    .coord_events = TinTowerRoof_CoordEvents,

    .bg_event_count = 0, // lengthof(TinTowerRoof_BGEvents),
    .bg_events = TinTowerRoof_BGEvents,

    .obj_event_count = lengthof(TinTowerRoof_ObjectEvents),
    .obj_events = TinTowerRoof_ObjectEvents,
};

//// CODE

bool TinTowerRoof_MapScripts_HoOh(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_FOUGHT_HO_OH)
    iftrue(NoAppear)
    checkitem(RAINBOW_WING)
    iftrue(Appear)
    goto NoAppear;
Appear:
    appear(TINTOWERROOF_HO_OH)
    s_endcallback
NoAppear:
    disappear(TINTOWERROOF_HO_OH)
    s_endcallback
    SCRIPT_END
}
bool TinTowerHoOh(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(HoOhText)
    playcry(HO_OH)
    pause(15)
    closetext
    setevent(EVENT_FOUGHT_HO_OH)
    loadvar(VAR_BATTLETYPE, BATTLETYPE_FORCEITEM)
    loadwildmon(HO_OH, 60)
    startbattle
    disappear(TINTOWERROOF_HO_OH)
    reloadmapafterbattle
    setevent(EVENT_SET_WHEN_FOUGHT_HO_OH)
    s_end
    SCRIPT_END
}
const txt_cmd_s HoOhText[] = {
    text_start("Shaoooh!"
        t_done )
    //db(0, 0) // filler
};
