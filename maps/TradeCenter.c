#include "../constants.h"
#include "../util/scripting.h"
#include "TradeCenter.h"
#include "Colosseum.h"
//// EVENTS
enum {
    TRADECENTER_CHRIS1 = 2,
    TRADECENTER_CHRIS2,
};

const Script_fn_t TradeCenter_SceneScripts[] = {
    TradeCenter_MapScripts_InitializeTradeCenter , //  SCENE_DEFAULT,
    TradeCenter_MapScripts_DummyScene , //  SCENE_FINISHED,
};

const struct MapCallback TradeCenter_MapCallbacks[] = {
    map_callback(MAPCALLBACK_OBJECTS, TradeCenter_MapScripts_SetWhichChris),
};

const struct MapScripts TradeCenter_MapScripts = {
    .scene_script_count = lengthof(TradeCenter_SceneScripts),
    .scene_scripts = TradeCenter_SceneScripts,

    .callback_count = lengthof(TradeCenter_MapCallbacks),
    .callbacks = TradeCenter_MapCallbacks,
};

static const struct CoordEvent TradeCenter_CoordEvents[] = {
    0,
};

static const struct BGEvent TradeCenter_BGEvents[] = {
    bg_event(4, 4, BGEVENT_RIGHT, &TradeCenterConsoleScript),
    bg_event(5, 4, BGEVENT_LEFT, &TradeCenterConsoleScript),
};

static const struct WarpEventData TradeCenter_WarpEvents[] = {
    warp_event(4, 7, POKECENTER_2F, 2),
    warp_event(5, 7, POKECENTER_2F, 2),
};

static const struct ObjEvent TradeCenter_ObjectEvents[] = {
    object_event(3, 4, SPRITE_CHRIS, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &CableClubFriendScript, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1),
    object_event(6, 4, SPRITE_CHRIS, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &CableClubFriendScript, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2),
};

const struct MapEvents TradeCenter_MapEvents = {
    .warp_event_count = lengthof(TradeCenter_WarpEvents),
    .warp_events = TradeCenter_WarpEvents,

    .coord_event_count = 0, // lengthof(TradeCenter_CoordEvents),
    .coord_events = TradeCenter_CoordEvents,

    .bg_event_count = lengthof(TradeCenter_BGEvents),
    .bg_events = TradeCenter_BGEvents,

    .obj_event_count = lengthof(TradeCenter_ObjectEvents),
    .obj_events = TradeCenter_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "TradeCenter.h"

bool TradeCenter_MapScripts_InitializeTradeCenter(script_s* s) {
    SCRIPT_BEGIN
    sdefer(TradeCenter_MapScripts_InitializeAndPreparePokecenter2F);
    s_end
    SCRIPT_END
}
bool TradeCenter_MapScripts_DummyScene(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool TradeCenter_MapScripts_SetWhichChris(script_s* s) {
    SCRIPT_BEGIN
    special(CableClubCheckWhichChris)
    iffalse_jump(TradeCenter_MapScripts_Chris2)
    disappear(TRADECENTER_CHRIS2)
    appear(TRADECENTER_CHRIS1)
    s_endcallback
    SCRIPT_END
}
bool TradeCenter_MapScripts_Chris2(script_s* s) {
    SCRIPT_BEGIN
    disappear(TRADECENTER_CHRIS1)
    appear(TRADECENTER_CHRIS2)
    s_endcallback
    SCRIPT_END
}
bool TradeCenter_MapScripts_InitializeAndPreparePokecenter2F(script_s* s) {
    SCRIPT_BEGIN
    setscene(SCENE_FINISHED)
    setmapscene(POKECENTER_2F, SCENE_POKECENTER2F_LEAVE_TRADE_CENTER)
    s_end
    SCRIPT_END
}
bool TradeCenterConsoleScript(script_s* s) {
    SCRIPT_BEGIN
    special(TradeCenter)
    newloadmap(MAPSETUP_LINKRETURN)
    s_end
    SCRIPT_END
}
bool TradeCenterFriendScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(TradeCenterFriendReadyText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const txt_cmd_s TradeCenterFriendReadyText[] = {
    text_start("Your friend is"
        t_line "ready."
        t_done )
    //db(0, 0) // filler
};
