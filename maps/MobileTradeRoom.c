#include "../constants.h"
#include "../util/scripting.h"
#include "MobileTradeRoom.h"
//// EVENTS
const Script_fn_t MobileTradeRoom_SceneScripts[] = {
    MobileTradeRoom_MapScripts_InitializeMobileTradeRoom , //  SCENE_DEFAULT,
    MobileTradeRoom_MapScripts_DummyScene , //  SCENE_FINISHED,
};

const struct MapCallback MobileTradeRoom_MapCallbacks[] = {
    0,
};

const struct MapScripts MobileTradeRoom_MapScripts = {
    .scene_script_count = lengthof(MobileTradeRoom_SceneScripts),
    .scene_scripts = MobileTradeRoom_SceneScripts,

    .callback_count = 0, // lengthof(MobileTradeRoom_MapCallbacks),
    .callbacks = MobileTradeRoom_MapCallbacks,
};

static const struct CoordEvent MobileTradeRoom_CoordEvents[] = {
    0,
};

static const struct BGEvent MobileTradeRoom_BGEvents[] = {
    bg_event(4, 2, BGEVENT_UP, &MobileTradeRoomConsoleScript),
};

static const struct WarpEventData MobileTradeRoom_WarpEvents[] = {
    warp_event(4, 7, POKECENTER_2F, 5),
    warp_event(5, 7, POKECENTER_2F, 5),
};

static const struct ObjEvent MobileTradeRoom_ObjectEvents[] = {
    0,
};

const struct MapEvents MobileTradeRoom_MapEvents = {
    .warp_event_count = lengthof(MobileTradeRoom_WarpEvents),
    .warp_events = MobileTradeRoom_WarpEvents,

    .coord_event_count = 0, // lengthof(MobileTradeRoom_CoordEvents),
    .coord_events = MobileTradeRoom_CoordEvents,

    .bg_event_count = lengthof(MobileTradeRoom_BGEvents),
    .bg_events = MobileTradeRoom_BGEvents,

    .obj_event_count = 0, // lengthof(MobileTradeRoom_ObjectEvents),
    .obj_events = MobileTradeRoom_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "MobileTradeRoom.h"

bool MobileTradeRoom_MapScripts_InitializeMobileTradeRoom(script_s* s) {
    SCRIPT_BEGIN
    sdefer(MobileTradeRoom_MapScripts_InitializeAndPreparePokecenter2F);
    s_end
    SCRIPT_END
}
bool MobileTradeRoom_MapScripts_DummyScene(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool MobileTradeRoom_MapScripts_InitializeAndPreparePokecenter2F(script_s* s) {
    SCRIPT_BEGIN
    setscene(SCENE_FINISHED)
    setmapscene(POKECENTER_2F, SCENE_POKECENTER2F_LEAVE_MOBILE_TRADE_ROOM)
    s_end
    SCRIPT_END
}
bool MobileTradeRoomConsoleScript(script_s* s) {
    SCRIPT_BEGIN
    refreshscreen
    special(Function1037c2)
    writetext(MobileTradeRoom_EstablishingCommsText)
    waitbutton
    reloadmappart
    special(Function101231)
    closetext
    s_end
    SCRIPT_END
}
const txt_cmd_s MobileTradeRoom_EstablishingCommsText[] = {
    text_start("Establishing"
        t_line "communications…"
        t_done )
    //db(0, 0) // filler
};
