#include "../constants.h"
#include "../util/scripting.h"
#include "Route4.h"
//// EVENTS
enum {
    ROUTE4_YOUNGSTER = 2,
    ROUTE4_LASS1,
    ROUTE4_LASS2,
    ROUTE4_POKE_BALL,
};

const Script_fn_t Route4_SceneScripts[] = {
    0,
};

const struct MapCallback Route4_MapCallbacks[] = {
    0,
};

const struct MapScripts Route4_MapScripts = {
    .scene_script_count = 0, // lengthof(Route4_SceneScripts),
    .scene_scripts = Route4_SceneScripts,

    .callback_count = 0, // lengthof(Route4_MapCallbacks),
    .callbacks = Route4_MapCallbacks,
};

static const struct CoordEvent Route4_CoordEvents[] = {
    0,
};

static const struct BGEvent Route4_BGEvents[] = {
    bg_event(3, 7, BGEVENT_READ, &MtMoonSquareSign),
    bg_event(10, 3, BGEVENT_ITEM, &Route4HiddenUltraBall),
};

static const struct WarpEventData Route4_WarpEvents[] = {
    warp_event(2, 5, MOUNT_MOON, 2),
};

static const struct ObjEvent Route4_ObjectEvents[] = {
    object_event(17, 9, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerBirdKeeperHank, -1),
    object_event(9, 8, SPRITE_LASS, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 4, &TrainerPicnickerHope, -1),
    object_event(21, 6, SPRITE_LASS, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 4, &TrainerPicnickerSharon, -1),
    object_event(26, 3, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &Route4HPUp, EVENT_ROUTE_4_HP_UP),
};

const struct MapEvents Route4_MapEvents = {
    .warp_event_count = lengthof(Route4_WarpEvents),
    .warp_events = Route4_WarpEvents,

    .coord_event_count = 0, // lengthof(Route4_CoordEvents),
    .coord_events = Route4_CoordEvents,

    .bg_event_count = lengthof(Route4_BGEvents),
    .bg_events = Route4_BGEvents,

    .obj_event_count = lengthof(Route4_ObjectEvents),
    .obj_events = Route4_ObjectEvents,
};

//// CODE

const struct TrainerObj TrainerBirdKeeperHank = {BIRD_KEEPER, HANK, EVENT_BEAT_BIRD_KEEPER_HANK, BirdKeeperHankSeenText, BirdKeeperHankBeatenText, 0, TrainerBirdKeeperHank_Script};
bool TrainerBirdKeeperHank_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(BirdKeeperHankAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerPicnickerHope = {PICNICKER, HOPE, EVENT_BEAT_PICNICKER_HOPE, PicnickerHopeSeenText, PicnickerHopeBeatenText, 0, TrainerPicnickerHope_Script};
bool TrainerPicnickerHope_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(PicnickerHopeAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerPicnickerSharon = {PICNICKER, SHARON, EVENT_BEAT_PICNICKER_SHARON, PicnickerSharonSeenText, PicnickerSharonBeatenText, 0, TrainerPicnickerSharon_Script};
bool TrainerPicnickerSharon_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(PicnickerSharonAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool MtMoonSquareSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(MtMoonSquareSignText)
    SCRIPT_END
}
const struct ItemBall Route4HPUp = {HP_UP, 1};
const struct HiddenItem Route4HiddenUltraBall = {ULTRA_BALL, EVENT_ROUTE_4_HIDDEN_ULTRA_BALL};
const txt_cmd_s BirdKeeperHankSeenText[] = {
    text_start("I'm raising my"
        t_line "#MON. Want to"
        t_cont "battle with me?"
        t_done )
};
const txt_cmd_s BirdKeeperHankBeatenText[] = {
    text_start("Ack! I lost that"
        t_line "one…"
        t_done )
};
const txt_cmd_s BirdKeeperHankAfterBattleText[] = {
    text_start("If you have a"
        t_line "specific #MON"
        t_para "that you want to"
        t_line "raise, put it out"
        t_para "first, then switch"
        t_line "it right away."
        t_para "That's how to do"
        t_line "it."
        t_done )
};
const txt_cmd_s PicnickerHopeSeenText[] = {
    text_start("I have a feeling"
        t_line "that I can win."
        t_para "Let's see if I'm"
        t_line "right!"
        t_done )
};
const txt_cmd_s PicnickerHopeBeatenText[] = {
    text_start("Aww, you are too"
        t_line "strong."
        t_done )
};
const txt_cmd_s PicnickerHopeAfterBattleText[] = {
    text_start("I heard CLEFAIRY"
        t_line "appear at MT.MOON."
        t_para "But where could"
        t_line "they be?"
        t_done )
};
const txt_cmd_s PicnickerSharonSeenText[] = {
    text_start("Um…"
        t_line "I…"
        t_done )
};
const txt_cmd_s PicnickerSharonBeatenText[] = {
    text_start("…"
        t_done )
};
const txt_cmd_s PicnickerSharonAfterBattleText[] = {
    text_start("……I'll go train"
        t_line "some more…"
        t_done )
};
const txt_cmd_s MtMoonSquareSignText[] = {
    text_start("MT.MOON SQUARE"
        t_para "Just go up the"
        t_line "stairs."
        t_done )
    //db(0, 0) // filler
};
