#include "../constants.h"
#include "../util/scripting.h"
#include "Route12.h"
//// EVENTS
enum {
    ROUTE12_FISHER1 = 2,
    ROUTE12_FISHER2,
    ROUTE12_FISHER3,
    ROUTE12_FISHER4,
    ROUTE12_POKE_BALL1,
    ROUTE12_POKE_BALL2,
};

const Script_fn_t Route12_SceneScripts[] = {
    0,
};

const struct MapCallback Route12_MapCallbacks[] = {
    0,
};

const struct MapScripts Route12_MapScripts = {
    .scene_script_count = 0, // lengthof(Route12_SceneScripts),
    .scene_scripts = Route12_SceneScripts,

    .callback_count = 0, // lengthof(Route12_MapCallbacks),
    .callbacks = Route12_MapCallbacks,
};

static const struct CoordEvent Route12_CoordEvents[] = {
    0,
};

static const struct BGEvent Route12_BGEvents[] = {
    bg_event(11, 27, BGEVENT_READ, &Route12Sign),
    bg_event(13, 9, BGEVENT_READ, &FishingSpotSign),
    bg_event(14, 13, BGEVENT_ITEM, &Route12HiddenElixer),
};

static const struct WarpEventData Route12_WarpEvents[] = {
    warp_event(11, 33, ROUTE_12_SUPER_ROD_HOUSE, 1),
};

static const struct ObjEvent Route12_ObjectEvents[] = {
    object_event(5, 13, SPRITE_FISHER, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 1, &TrainerFisherMartin, -1),
    object_event(14, 23, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 1, &TrainerFisherStephen, -1),
    object_event(10, 38, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 5, &TrainerFisherBarney, -1),
    object_event(6, 7, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 3, &TrainerFisherKyle, -1),
    object_event(5, 43, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &Route12Calcium, EVENT_ROUTE_12_CALCIUM),
    object_event(5, 51, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &Route12Nugget, EVENT_ROUTE_12_NUGGET),
};

const struct MapEvents Route12_MapEvents = {
    .warp_event_count = lengthof(Route12_WarpEvents),
    .warp_events = Route12_WarpEvents,

    .coord_event_count = 0, // lengthof(Route12_CoordEvents),
    .coord_events = Route12_CoordEvents,

    .bg_event_count = lengthof(Route12_BGEvents),
    .bg_events = Route12_BGEvents,

    .obj_event_count = lengthof(Route12_ObjectEvents),
    .obj_events = Route12_ObjectEvents,
};

//// CODE

const struct TrainerObj TrainerFisherKyle = {FISHER, KYLE, EVENT_BEAT_FISHER_KYLE, FisherKyleSeenText, FisherKyleBeatenText, 0, TrainerFisherKyle_Script};
bool TrainerFisherKyle_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(FisherKyleAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerFisherMartin = {FISHER, MARTIN, EVENT_BEAT_FISHER_MARTIN, FisherMartinSeenText, FisherMartinBeatenText, 0, TrainerFisherMartin_Script};
bool TrainerFisherMartin_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(FisherMartinAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerFisherStephen = {FISHER, STEPHEN, EVENT_BEAT_FISHER_STEPHEN, FisherStephenSeenText, FisherStephenBeatenText, 0, TrainerFisherStephen_Script};
bool TrainerFisherStephen_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(FisherStephenAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerFisherBarney = {FISHER, BARNEY, EVENT_BEAT_FISHER_BARNEY, FisherBarneySeenText, FisherBarneyBeatenText, 0, TrainerFisherBarney_Script};
bool TrainerFisherBarney_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(FisherBarneyAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Route12Sign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route12SignText)
    SCRIPT_END
}
bool FishingSpotSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(FishingSpotSignText)
    SCRIPT_END
}
const struct ItemBall Route12Calcium = {CALCIUM, 1};
const struct ItemBall Route12Nugget = {NUGGET, 1};
const struct HiddenItem Route12HiddenElixer = {ELIXER, EVENT_ROUTE_12_HIDDEN_ELIXER};
const txt_cmd_s FisherMartinSeenText[] = {
    text_start("Patience is the"
        t_line "key to both fish-"
        t_cont "ing and #MON."
        t_done )
};
const txt_cmd_s FisherMartinBeatenText[] = {
    text_start("Gwaaah!"
        t_done )
};
const txt_cmd_s FisherMartinAfterBattleText[] = {
    text_start("I'm too impatient"
        t_line "for fishing…"
        t_done )
};
const txt_cmd_s FisherStephenSeenText[] = {
    text_start("I feel so content,"
        t_line "fishing while lis-"
        t_cont "tening to some"
        t_cont "tunes on my radio."
        t_done )
};
const txt_cmd_s FisherStephenBeatenText[] = {
    text_start("My stupid radio"
        t_line "distracted me!"
        t_done )
};
const txt_cmd_s FisherStephenAfterBattleText[] = {
    text_start("Have you checked"
        t_line "out KANTO's radio"
        t_para "programs? We get a"
        t_line "good variety here."
        t_done )
};
const txt_cmd_s FisherBarneySeenText[] = {
    text_start("What's most impor-"
        t_line "tant in our every-"
        t_cont "day lives?"
        t_done )
};
const txt_cmd_s FisherBarneyBeatenText[] = {
    text_start("The answer is"
        t_line "coming up next!"
        t_done )
};
const txt_cmd_s FisherBarneyAfterBattleText[] = {
    text_start("I think electric-"
        t_line "ity is the most"
        t_para "important thing in"
        t_line "our daily lives."
        t_para "If it weren't,"
        t_line "people wouldn't"
        t_para "have made such a"
        t_line "fuss when the"
        t_para "POWER PLANT went"
        t_line "out of commission."
        t_done )
};
const txt_cmd_s FisherKyleSeenText[] = {
    text_start("Do you remember?"
        t_done )
};
const txt_cmd_s FisherKyleBeatenText[] = {
    text_start("You do remember?"
        t_done )
};
const txt_cmd_s FisherKyleAfterBattleText[] = {
    text_start("The tug you feel"
        t_line "on the ROD when"
        t_para "you hook a #-"
        t_line "MON…"
        t_para "That's the best"
        t_line "feeling ever for"
        t_cont "an angler like me."
        t_done )
};
const txt_cmd_s Route12SignText[] = {
    text_start("ROUTE 12"
        t_para "NORTH TO LAVENDER"
        t_line "TOWN"
        t_done )
};
const txt_cmd_s FishingSpotSignText[] = {
    text_start("FISHING SPOT"
        t_done )
    //db(0, 0) // filler
};
