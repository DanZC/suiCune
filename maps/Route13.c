#include "../constants.h"
#include "../util/scripting.h"
#include "Route13.h"
//// EVENTS
enum {
    ROUTE13_YOUNGSTER1 = 2,
    ROUTE13_YOUNGSTER2,
    ROUTE13_POKEFAN_M1,
    ROUTE13_POKEFAN_M2,
    ROUTE13_POKEFAN_M3,
};

const Script_fn_t Route13_SceneScripts[] = {
    0,
};

const struct MapCallback Route13_MapCallbacks[] = {
    0,
};

const struct MapScripts Route13_MapScripts = {
    .scene_script_count = 0, // lengthof(Route13_SceneScripts),
    .scene_scripts = Route13_SceneScripts,

    .callback_count = 0, // lengthof(Route13_MapCallbacks),
    .callbacks = Route13_MapCallbacks,
};

static const struct CoordEvent Route13_CoordEvents[] = {
    0,
};

static const struct BGEvent Route13_BGEvents[] = {
    bg_event(29, 13, BGEVENT_READ, &Route13TrainerTips),
    bg_event(41, 11, BGEVENT_READ, &Route13Sign),
    bg_event(17, 13, BGEVENT_READ, &Route13DirectionsSign),
    bg_event(30, 13, BGEVENT_ITEM, &Route13HiddenCalcium),
};

static const struct WarpEventData Route13_WarpEvents[] = {
    0,
};

static const struct ObjEvent Route13_ObjectEvents[] = {
    object_event(42, 6, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 2, &TrainerBirdKeeperPerry, -1),
    object_event(43, 6, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 2, &TrainerBirdKeeperBret, -1),
    object_event(32, 8, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 3, &TrainerPokefanmJoshua, -1),
    object_event(14, 10, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 4, &TrainerHikerKenny, -1),
    object_event(25, 6, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 4, &TrainerPokefanmAlex, -1),
};

const struct MapEvents Route13_MapEvents = {
    .warp_event_count = 0, // lengthof(Route13_WarpEvents),
    .warp_events = Route13_WarpEvents,

    .coord_event_count = 0, // lengthof(Route13_CoordEvents),
    .coord_events = Route13_CoordEvents,

    .bg_event_count = lengthof(Route13_BGEvents),
    .bg_events = Route13_BGEvents,

    .obj_event_count = lengthof(Route13_ObjectEvents),
    .obj_events = Route13_ObjectEvents,
};

//// CODE

const struct TrainerObj TrainerPokefanmAlex = {POKEFANM, ALEX, EVENT_BEAT_POKEFANM_ALEX, PokefanmAlexSeenText, PokefanmAlexBeatenText, 0, TrainerPokefanmAlex_Script};
bool TrainerPokefanmAlex_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(PokefanmAlexAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerPokefanmJoshua = {POKEFANM, JOSHUA, EVENT_BEAT_POKEFANM_JOSHUA, PokefanmJoshuaSeenText, PokefanmJoshuaBeatenText, 0, TrainerPokefanmJoshua_Script};
bool TrainerPokefanmJoshua_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(PokefanmJoshuaAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerBirdKeeperPerry = {BIRD_KEEPER, PERRY, EVENT_BEAT_BIRD_KEEPER_PERRY, BirdKeeperPerrySeenText, BirdKeeperPerryBeatenText, 0, TrainerBirdKeeperPerry_Script};
bool TrainerBirdKeeperPerry_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(BirdKeeperPerryAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerBirdKeeperBret = {BIRD_KEEPER, BRET, EVENT_BEAT_BIRD_KEEPER_BRET, BirdKeeperBretSeenText, BirdKeeperBretBeatenText, 0, TrainerBirdKeeperBret_Script};
bool TrainerBirdKeeperBret_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(BirdKeeperBretAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerHikerKenny = {HIKER, KENNY, EVENT_BEAT_HIKER_KENNY, HikerKennySeenText, HikerKennyBeatenText, 0, TrainerHikerKenny_Script};
bool TrainerHikerKenny_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(HikerKennyAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Route13TrainerTips(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route13TrainerTipsText)
    SCRIPT_END
}
bool Route13Sign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route13SignText)
    SCRIPT_END
}
bool Route13DirectionsSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route13DirectionsSignText)
    SCRIPT_END
}
const struct HiddenItem Route13HiddenCalcium = {CALCIUM, EVENT_ROUTE_13_HIDDEN_CALCIUM};
const txt_cmd_s PokefanmAlexSeenText[] = {
    text_start("Bow down before my"
        t_line "regal #MON!"
        t_done )
};
const txt_cmd_s PokefanmAlexBeatenText[] = {
    text_start("How… How dare you"
        t_line "mock royalty!"
        t_done )
};
const txt_cmd_s PokefanmAlexAfterBattleText[] = {
    text_start("Doesn't everyone"
        t_line "wish to someday be"
        t_cont "a king?"
        t_done )
};
const txt_cmd_s PokefanmJoshuaSeenText[] = {
    text_start("Nihihi! Would you"
        t_line "like to battle my"
        t_cont "PIKACHU gang?"
        t_done )
};
const txt_cmd_s PokefanmJoshuaBeatenText[] = {
    text_start("PI-PIKACHU!"
        t_done )
};
const txt_cmd_s PokefanmJoshuaAfterBattleText[] = {
    text_start("You look like you"
        t_line "have many #MON,"
        t_para "but PIKACHU is"
        t_line "still the best."
        t_done )
};
const txt_cmd_s BirdKeeperPerrySeenText[] = {
    text_start("Agility is the key"
        t_line "attribute of bird"
        t_cont "#MON."
        t_done )
};
const txt_cmd_s BirdKeeperPerryBeatenText[] = {
    text_start("You beat me with"
        t_line "your speed…"
        t_done )
};
const txt_cmd_s BirdKeeperPerryAfterBattleText[] = {
    text_start("Your #MON are"
        t_line "remarkably well-"
        t_cont "trained."
        t_done )
};
const txt_cmd_s BirdKeeperBretSeenText[] = {
    text_start("Check out my #-"
        t_line "MON. Just look at"
        t_para "their coloring and"
        t_line "their plumage."
        t_done )
};
const txt_cmd_s BirdKeeperBretBeatenText[] = {
    text_start("Shoot!"
        t_line "Not good enough!"
        t_done )
};
const txt_cmd_s BirdKeeperBretAfterBattleText[] = {
    text_start("If you groom them,"
        t_line "#MON get happy."
        t_done )
};
const txt_cmd_s HikerKennySeenText[] = {
    text_start("I should go to"
        t_line "ROCK TUNNEL to get"
        t_cont "myself an ONIX."
        t_done )
};
const txt_cmd_s HikerKennyBeatenText[] = {
    text_start("I lost…"
        t_done )
};
const txt_cmd_s HikerKennyAfterBattleText[] = {
    text_start("Geological fea-"
        t_line "tures don't appear"
        t_cont "to change."
        t_para "But they actually"
        t_line "change, little by"
        t_cont "little."
        t_done )
};
const txt_cmd_s Route13TrainerTipsText[] = {
    text_start("TRAINER TIPS"
        t_para "Look! Right there,"
        t_line "at the left side"
        t_cont "of the post."
        t_done )
};
const txt_cmd_s Route13SignText[] = {
    text_start("ROUTE 13"
        t_para "NORTH TO SILENCE"
        t_line "BRIDGE"
        t_done )
};
const txt_cmd_s Route13DirectionsSignText[] = {
    text_start("NORTH TO LAVENDER"
        t_line "TOWN"
        t_para "WEST TO FUCHSIA"
        t_line "CITY"
        t_done )
    //db(0, 0) // filler
};
