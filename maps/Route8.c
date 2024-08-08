#include "../constants.h"
#include "../util/scripting.h"
#include "Route8.h"
//// EVENTS
enum {
    ROUTE8_BIKER1 = 2,
    ROUTE8_BIKER2,
    ROUTE8_BIKER3,
    ROUTE8_SUPER_NERD1,
    ROUTE8_SUPER_NERD2,
    ROUTE8_FRUIT_TREE,
};

const Script_fn_t Route8_SceneScripts[] = {
    0,
};

const struct MapCallback Route8_MapCallbacks[] = {
    0,
};

const struct MapScripts Route8_MapScripts = {
    .scene_script_count = 0, // lengthof(Route8_SceneScripts),
    .scene_scripts = Route8_SceneScripts,

    .callback_count = 0, // lengthof(Route8_MapCallbacks),
    .callbacks = Route8_MapCallbacks,
};

static const struct CoordEvent Route8_CoordEvents[] = {
    0,
};

static const struct BGEvent Route8_BGEvents[] = {
    bg_event(11, 7, BGEVENT_READ, &Route8UndergroundPathSign),
    bg_event(10, 5, BGEVENT_READ, &Route8LockedDoor),
};

static const struct WarpEventData Route8_WarpEvents[] = {
    warp_event(4, 4, ROUTE_8_SAFFRON_GATE, 3),
    warp_event(4, 5, ROUTE_8_SAFFRON_GATE, 4),
};

static const struct ObjEvent Route8_ObjectEvents[] = {
    object_event(10, 8, SPRITE_BIKER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 5, &TrainerBikerDwayne, -1),
    object_event(10, 9, SPRITE_BIKER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 5, &TrainerBikerHarris, -1),
    object_event(10, 10, SPRITE_BIKER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 5, &TrainerBikerZeke, -1),
    object_event(23, 2, SPRITE_SUPER_NERD, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_TRAINER, 3, &TrainerSupernerdSam, -1),
    object_event(31, 12, SPRITE_SUPER_NERD, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_TRAINER, 4, &TrainerSupernerdTom, -1),
    object_event(33, 5, SPRITE_FRUIT_TREE, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Route8FruitTree, -1),
};

const struct MapEvents Route8_MapEvents = {
    .warp_event_count = lengthof(Route8_WarpEvents),
    .warp_events = Route8_WarpEvents,

    .coord_event_count = 0, // lengthof(Route8_CoordEvents),
    .coord_events = Route8_CoordEvents,

    .bg_event_count = lengthof(Route8_BGEvents),
    .bg_events = Route8_BGEvents,

    .obj_event_count = lengthof(Route8_ObjectEvents),
    .obj_events = Route8_ObjectEvents,
};

//// CODE

const struct TrainerObj TrainerBikerDwayne = {BIKER, DWAYNE, EVENT_BEAT_BIKER_DWAYNE, BikerDwayneSeenText, BikerDwayneBeatenText, 0, TrainerBikerDwayne_Script};
bool TrainerBikerDwayne_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(BikerDwayneAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerBikerHarris = {BIKER, HARRIS, EVENT_BEAT_BIKER_HARRIS, BikerHarrisSeenText, BikerHarrisBeatenText, 0, TrainerBikerHarris_Script};
bool TrainerBikerHarris_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(BikerHarrisAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerBikerZeke = {BIKER, ZEKE, EVENT_BEAT_BIKER_ZEKE, BikerZekeSeenText, BikerZekeBeatenText, 0, TrainerBikerZeke_Script};
bool TrainerBikerZeke_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(BikerZekeAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSupernerdSam = {SUPER_NERD, SAM, EVENT_BEAT_SUPER_NERD_SAM, SupernerdSamSeenText, SupernerdSamBeatenText, 0, TrainerSupernerdSam_Script};
bool TrainerSupernerdSam_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SupernerdSamAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSupernerdTom = {SUPER_NERD, TOM, EVENT_BEAT_SUPER_NERD_TOM, SupernerdTomSeenText, SupernerdTomBeatenText, 0, TrainerSupernerdTom_Script};
bool TrainerSupernerdTom_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SupernerdTomAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Route8LockedDoor(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route8LockedDoorText)
    SCRIPT_END
}
bool Route8UndergroundPathSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route8UndergroundPathSignText)
    SCRIPT_END
}
bool Route8FruitTree(script_s* s) {
    SCRIPT_BEGIN
    fruittree(FRUITTREE_ROUTE_8)
    SCRIPT_END
}
const txt_cmd_s BikerDwayneSeenText[] = {
    text_start("We're the KANTO"
        t_line "#MON FEDERATION"
        t_cont "trainer group."
        t_para "We'll drive you"
        t_line "under our wheels!"
        t_done )
};
const txt_cmd_s BikerDwayneBeatenText[] = {
    text_start("S-sorry!"
        t_done )
};
const txt_cmd_s BikerDwayneAfterBattleText[] = {
    text_start("The KANTO #MON"
        t_line "FEDERATION will"
        t_cont "never fall!"
        t_done )
};
const txt_cmd_s BikerHarrisSeenText[] = {
    text_start("The cops shut down"
        t_line "our UNDERGROUND"
        t_para "PATH! That really"
        t_line "fries me!"
        t_done )
};
const txt_cmd_s BikerHarrisBeatenText[] = {
    text_start("F-forgive me!"
        t_done )
};
const txt_cmd_s BikerHarrisAfterBattleText[] = {
    text_start("Wiped out by some"
        t_line "punk from JOHTO…"
        t_done )
};
const txt_cmd_s BikerZekeSeenText[] = {
    text_start("We're the KANTO"
        t_line "#MON FEDERA-"
        t_cont "TION!"
        t_cont "Right on!"
        t_done )
};
const txt_cmd_s BikerZekeBeatenText[] = {
    text_start("Yikes! Sorry!"
        t_done )
};
const txt_cmd_s BikerZekeAfterBattleText[] = {
    text_start("We'll try not to"
        t_line "disturb anyone"
        t_cont "from now on…"
        t_done )
};
const txt_cmd_s SupernerdSamSeenText[] = {
    text_start("How does the MAG-"
        t_line "NET TRAIN work?"
        t_done )
};
const txt_cmd_s SupernerdSamBeatenText[] = {
    text_start("I just want to see"
        t_line "the MAGNET TRAIN…"
        t_done )
};
const txt_cmd_s SupernerdSamAfterBattleText[] = {
    text_start("The power of mag-"
        t_line "nets is awesome!"
        t_done )
};
const txt_cmd_s SupernerdTomSeenText[] = {
    text_start("Hm… You've got"
        t_line "many GYM BADGES."
        t_done )
};
const txt_cmd_s SupernerdTomBeatenText[] = {
    text_start("Just as I thought…"
        t_line "You're tough!"
        t_done )
};
const txt_cmd_s SupernerdTomAfterBattleText[] = {
    text_start("GYM BADGES give"
        t_line "you advantages in"
        t_cont "battles."
        t_done )
};
const txt_cmd_s Route8LockedDoorText[] = {
    text_start("It's locked…"
        t_done )
};
const txt_cmd_s Route8UndergroundPathSignText[] = {
    text_start("The flyer's torn."
        t_para "It's impossible to"
        t_line "read…"
        t_done )
    //db(0, 0) // filler
};
