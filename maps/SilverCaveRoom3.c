#include "../constants.h"
#include "../util/scripting.h"
#include "SilverCaveRoom3.h"
//// EVENTS
enum {
    SILVERCAVEROOM3_RED = 2,
};

const Script_fn_t SilverCaveRoom3_SceneScripts[] = {
    0,
};

const struct MapCallback SilverCaveRoom3_MapCallbacks[] = {
    0,
};

const struct MapScripts SilverCaveRoom3_MapScripts = {
    .scene_script_count = 0, // lengthof(SilverCaveRoom3_SceneScripts),
    .scene_scripts = SilverCaveRoom3_SceneScripts,

    .callback_count = 0, // lengthof(SilverCaveRoom3_MapCallbacks),
    .callbacks = SilverCaveRoom3_MapCallbacks,
};

static const struct CoordEvent SilverCaveRoom3_CoordEvents[] = {
    0,
};

static const struct BGEvent SilverCaveRoom3_BGEvents[] = {
    0,
};

static const struct WarpEventData SilverCaveRoom3_WarpEvents[] = {
    warp_event(9, 33, SILVER_CAVE_ROOM_2, 2),
};

static const struct ObjEvent SilverCaveRoom3_ObjectEvents[] = {
    object_event(9, 10, SPRITE_RED, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &Red, EVENT_RED_IN_MT_SILVER),
};

const struct MapEvents SilverCaveRoom3_MapEvents = {
    .warp_event_count = lengthof(SilverCaveRoom3_WarpEvents),
    .warp_events = SilverCaveRoom3_WarpEvents,

    .coord_event_count = 0, // lengthof(SilverCaveRoom3_CoordEvents),
    .coord_events = SilverCaveRoom3_CoordEvents,

    .bg_event_count = 0, // lengthof(SilverCaveRoom3_BGEvents),
    .bg_events = SilverCaveRoom3_BGEvents,

    .obj_event_count = lengthof(SilverCaveRoom3_ObjectEvents),
    .obj_events = SilverCaveRoom3_ObjectEvents,
};

//// CODE

bool Red(script_s* s) {
    SCRIPT_BEGIN
    special(FadeOutMusic)
    faceplayer
    opentext
    writetext(RedSeenText)
    waitbutton
    closetext
    winlosstext(RedWinLossText, RedWinLossText)
    loadtrainer(RED, RED1)
    startbattle
    dontrestartmapmusic
    reloadmapafterbattle
    special(FadeOutMusic)
    opentext
    writetext(RedLeavesText)
    waitbutton
    closetext
    special(FadeBlackQuickly)
    special(ReloadSpritesNoPalettes)
    disappear(SILVERCAVEROOM3_RED)
    pause(15)
    special(FadeInQuickly)
    pause(30)
    special(HealParty)
    refreshscreen
    credits
    s_end
    SCRIPT_END
}
const txt_cmd_s RedSeenText[] = {
    text_start("<……>"
        t_line "<……>"
        t_done )
};
const txt_cmd_s RedWinLossText[] = {
    text_start("…"
        t_done )
};
const txt_cmd_s RedLeavesText[] = {
    text_start("<……>"
        t_line "<……>"
        t_done )
    //db(0, 0) // filler
};
