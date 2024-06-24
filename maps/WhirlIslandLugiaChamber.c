#include "../constants.h"
#include "../util/scripting.h"
#include "WhirlIslandLugiaChamber.h"
//// EVENTS
enum {
    WHIRLISLANDLUGIACHAMBER_LUGIA = 2,
};

const Script_fn_t WhirlIslandLugiaChamber_SceneScripts[] = {
    0,
};

const struct MapCallback WhirlIslandLugiaChamber_MapCallbacks[] = {
    map_callback(MAPCALLBACK_OBJECTS, WhirlIslandLugiaChamber_MapScripts_Lugia),
};

const struct MapScripts WhirlIslandLugiaChamber_MapScripts = {
    .scene_script_count = 0, // lengthof(WhirlIslandLugiaChamber_SceneScripts),
    .scene_scripts = WhirlIslandLugiaChamber_SceneScripts,

    .callback_count = lengthof(WhirlIslandLugiaChamber_MapCallbacks),
    .callbacks = WhirlIslandLugiaChamber_MapCallbacks,
};

static const struct CoordEvent WhirlIslandLugiaChamber_CoordEvents[] = {
    0,
};

static const struct BGEvent WhirlIslandLugiaChamber_BGEvents[] = {
    0,
};

static const struct WarpEventData WhirlIslandLugiaChamber_WarpEvents[] = {
    warp_event(9, 13, WHIRL_ISLAND_B2F, 3),
};

static const struct ObjEvent WhirlIslandLugiaChamber_ObjectEvents[] = {
    object_event(9, 5, SPRITE_LUGIA, SPRITEMOVEDATA_POKEMON, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &Lugia, EVENT_WHIRL_ISLAND_LUGIA_CHAMBER_LUGIA),
};

const struct MapEvents WhirlIslandLugiaChamber_MapEvents = {
    .warp_event_count = lengthof(WhirlIslandLugiaChamber_WarpEvents),
    .warp_events = WhirlIslandLugiaChamber_WarpEvents,

    .coord_event_count = 0, // lengthof(WhirlIslandLugiaChamber_CoordEvents),
    .coord_events = WhirlIslandLugiaChamber_CoordEvents,

    .bg_event_count = 0, // lengthof(WhirlIslandLugiaChamber_BGEvents),
    .bg_events = WhirlIslandLugiaChamber_BGEvents,

    .obj_event_count = lengthof(WhirlIslandLugiaChamber_ObjectEvents),
    .obj_events = WhirlIslandLugiaChamber_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "WhirlIslandLugiaChamber.h"

bool WhirlIslandLugiaChamber_MapScripts_Lugia(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_FOUGHT_LUGIA)
    iftrue(NoAppear)
    checkitem(SILVER_WING)
    iftrue(Appear)
    goto NoAppear;
Appear:
    appear(WHIRLISLANDLUGIACHAMBER_LUGIA)
    s_endcallback
NoAppear:
    disappear(WHIRLISLANDLUGIACHAMBER_LUGIA)
    s_endcallback
    SCRIPT_END
}
bool Lugia(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(LugiaText)
    playcry(LUGIA)
    pause(15)
    closetext
    setevent(EVENT_FOUGHT_LUGIA)
    loadvar(VAR_BATTLETYPE, BATTLETYPE_FORCEITEM)
    loadwildmon(LUGIA, 60)
    startbattle
    disappear(WHIRLISLANDLUGIACHAMBER_LUGIA)
    reloadmapafterbattle
    s_end
    SCRIPT_END
}
const txt_cmd_s LugiaText[] = {
    text_start("Gyaaas!"
        t_done )
    //db(0, 0) // filler
};
