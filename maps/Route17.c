#include "../constants.h"
#include "../util/scripting.h"
#include "Route17.h"
//// EVENTS
enum {
    ROUTE17_BIKER1 = 2,
    ROUTE17_BIKER2,
    ROUTE17_BIKER3,
    ROUTE17_BIKER4,
};

const Script_fn_t Route17_SceneScripts[] = {
    0,
};

const struct MapCallback Route17_MapCallbacks[] = {
    map_callback(MAPCALLBACK_NEWMAP, Route17_MapScripts_AlwaysOnBike),
};

const struct MapScripts Route17_MapScripts = {
    .scene_script_count = 0, // lengthof(Route17_SceneScripts),
    .scene_scripts = Route17_SceneScripts,

    .callback_count = lengthof(Route17_MapCallbacks),
    .callbacks = Route17_MapCallbacks,
};

static const struct CoordEvent Route17_CoordEvents[] = {
    0,
};

static const struct BGEvent Route17_BGEvents[] = {
    bg_event(9, 54, BGEVENT_ITEM, &Route17HiddenMaxEther),
    bg_event(8, 77, BGEVENT_ITEM, &Route17HiddenMaxElixer),
};

static const struct WarpEventData Route17_WarpEvents[] = {
    warp_event(17, 82, ROUTE_17_ROUTE_18_GATE, 1),
    warp_event(17, 83, ROUTE_17_ROUTE_18_GATE, 2),
};

static const struct ObjEvent Route17_ObjectEvents[] = {
    object_event(4, 17, SPRITE_BIKER, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_TRAINER, 4, &TrainerBikerRiley, -1),
    object_event(9, 68, SPRITE_BIKER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_TRAINER, 1, &TrainerBikerJoel, -1),
    object_event(3, 53, SPRITE_BIKER, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_TRAINER, 3, &TrainerBikerGlenn, -1),
    object_event(6, 80, SPRITE_BIKER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_TRAINER, 4, &TrainerBikerCharles, -1),
};

const struct MapEvents Route17_MapEvents = {
    .warp_event_count = lengthof(Route17_WarpEvents),
    .warp_events = Route17_WarpEvents,

    .coord_event_count = 0, // lengthof(Route17_CoordEvents),
    .coord_events = Route17_CoordEvents,

    .bg_event_count = lengthof(Route17_BGEvents),
    .bg_events = Route17_BGEvents,

    .obj_event_count = lengthof(Route17_ObjectEvents),
    .obj_events = Route17_ObjectEvents,
};

//// CODE

bool Route17_MapScripts_AlwaysOnBike(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_ALWAYS_ON_BIKE)
    setflag(ENGINE_DOWNHILL)
    s_endcallback
    SCRIPT_END
}
const struct TrainerObj TrainerBikerCharles = {BIKER, CHARLES, EVENT_BEAT_BIKER_CHARLES, BikerCharlesSeenText, BikerCharlesBeatenText, 0, TrainerBikerCharles_Script};
bool TrainerBikerCharles_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(BikerCharlesAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerBikerRiley = {BIKER, RILEY, EVENT_BEAT_BIKER_RILEY, BikerRileySeenText, BikerRileyBeatenText, 0, TrainerBikerRiley_Script};
bool TrainerBikerRiley_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(BikerRileyAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerBikerJoel = {BIKER, JOEL, EVENT_BEAT_BIKER_JOEL, BikerJoelSeenText, BikerJoelBeatenText, 0, TrainerBikerJoel_Script};
bool TrainerBikerJoel_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(BikerJoelAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerBikerGlenn = {BIKER, GLENN, EVENT_BEAT_BIKER_GLENN, BikerGlennSeenText, BikerGlennBeatenText, 0, TrainerBikerGlenn_Script};
bool TrainerBikerGlenn_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(BikerGlennAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct HiddenItem Route17HiddenMaxEther = {MAX_ETHER, EVENT_ROUTE_17_HIDDEN_MAX_ETHER};
const struct HiddenItem Route17HiddenMaxElixer = {MAX_ELIXER, EVENT_ROUTE_17_HIDDEN_MAX_ELIXER};
const txt_cmd_s BikerRileySeenText[] = {
    text_start("Hey, you! You're"
        t_line "from JOHTO, huh?"
        t_done )
};
const txt_cmd_s BikerRileyBeatenText[] = {
    text_start("Whoa, you kick!"
        t_done )
};
const txt_cmd_s BikerRileyAfterBattleText[] = {
    text_start("Don't get cocky,"
        t_line "you JOHTO punk!"
        t_done )
};
const txt_cmd_s BikerJoelSeenText[] = {
    text_start("Wow. That's a cool"
        t_line "BICYCLE!"
        t_done )
};
const txt_cmd_s BikerJoelBeatenText[] = {
    text_start("But you don't just"
        t_line "look cool…"
        t_done )
};
const txt_cmd_s BikerJoelAfterBattleText[] = {
    text_start("I look cool, but"
        t_line "I'm weak, so I'm"
        t_cont "not really cool."
        t_para "I have to train"
        t_line "harder…"
        t_done )
};
const txt_cmd_s BikerGlennSeenText[] = {
    text_start("Hey! Want to have"
        t_line "a speed battle?"
        t_done )
};
const txt_cmd_s BikerGlennBeatenText[] = {
    text_start("Yikes! You've got"
        t_line "awesome torque!"
        t_done )
};
const txt_cmd_s BikerGlennAfterBattleText[] = {
    text_start("Hands-free riding"
        t_line "is considered cool"
        t_cont "on CYCLING ROAD."
        t_done )
};
const txt_cmd_s BikerCharlesSeenText[] = {
    text_start("We're fearless"
        t_line "highway stars!"
        t_done )
};
const txt_cmd_s BikerCharlesBeatenText[] = {
    text_start("Arrrgh! Crash and"
        t_line "burn!"
        t_done )
};
const txt_cmd_s BikerCharlesAfterBattleText[] = {
    text_start("Reckless driving"
        t_line "causes accidents!"
        t_cont "Take it easy!"
        t_done )
    //db(0, 0) // filler
};
