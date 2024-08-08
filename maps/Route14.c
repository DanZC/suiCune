#include "../constants.h"
#include "../util/scripting.h"
#include "Route14.h"
//// EVENTS
enum {
    ROUTE14_POKEFAN_M1 = 2,
    ROUTE14_YOUNGSTER,
    ROUTE14_POKEFAN_M2,
    ROUTE14_KIM,
};

const Script_fn_t Route14_SceneScripts[] = {
    0,
};

const struct MapCallback Route14_MapCallbacks[] = {
    0,
};

const struct MapScripts Route14_MapScripts = {
    .scene_script_count = 0, // lengthof(Route14_SceneScripts),
    .scene_scripts = Route14_SceneScripts,

    .callback_count = 0, // lengthof(Route14_MapCallbacks),
    .callbacks = Route14_MapCallbacks,
};

static const struct CoordEvent Route14_CoordEvents[] = {
    0,
};

static const struct BGEvent Route14_BGEvents[] = {
    0,
};

static const struct WarpEventData Route14_WarpEvents[] = {
    0,
};

static const struct ObjEvent Route14_ObjectEvents[] = {
    object_event(11, 15, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 3, &TrainerPokefanmCarter, -1),
    object_event(11, 27, SPRITE_YOUNGSTER, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerBirdKeeperRoy, -1),
    object_event(6, 11, SPRITE_POKEFAN_M, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 3, &TrainerPokefanmTrevor, -1),
    object_event(7, 5, SPRITE_TEACHER, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 4, &Kim, -1),
};

const struct MapEvents Route14_MapEvents = {
    .warp_event_count = 0, // lengthof(Route14_WarpEvents),
    .warp_events = Route14_WarpEvents,

    .coord_event_count = 0, // lengthof(Route14_CoordEvents),
    .coord_events = Route14_CoordEvents,

    .bg_event_count = 0, // lengthof(Route14_BGEvents),
    .bg_events = Route14_BGEvents,

    .obj_event_count = lengthof(Route14_ObjectEvents),
    .obj_events = Route14_ObjectEvents,
};

//// CODE

bool Kim(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    trade(NPC_TRADE_KIM)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerPokefanmCarter = {POKEFANM, CARTER, EVENT_BEAT_POKEFANM_CARTER, PokefanmCarterSeenText, PokefanmCarterBeatenText, 0, TrainerPokefanmCarter_Script};
bool TrainerPokefanmCarter_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(PokefanmCarterAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerBirdKeeperRoy = {BIRD_KEEPER, ROY, EVENT_BEAT_BIRD_KEEPER_ROY, BirdKeeperRoySeenText, BirdKeeperRoyBeatenText, 0, TrainerBirdKeeperRoy_Script};
bool TrainerBirdKeeperRoy_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(BirdKeeperRoyAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerPokefanmTrevor = {POKEFANM, TREVOR, EVENT_BEAT_POKEFANM_TREVOR, PokefanmTrevorSeenText, PokefanmTrevorBeatenText, 0, TrainerPokefanmTrevor_Script};
bool TrainerPokefanmTrevor_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(PokefanmTrevorAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const txt_cmd_s PokefanmCarterSeenText[] = {
    text_start("Let me tell you,"
        t_line "I had a hard time"
        t_para "catching my prized"
        t_line "#MON."
        t_done )
};
const txt_cmd_s PokefanmCarterBeatenText[] = {
    text_start("Awaaah!"
        t_done )
};
const txt_cmd_s PokefanmCarterAfterBattleText[] = {
    text_start("SQUIRTLE, CHARMAN-"
        t_line "DER and BULBASAUR…"
        t_para "I think that's a"
        t_line "well-balanced mix."
        t_done )
};
const txt_cmd_s BirdKeeperRoySeenText[] = {
    text_start("My dream is to fly"
        t_line "with my beloved"
        t_cont "bird #MON."
        t_done )
};
const txt_cmd_s BirdKeeperRoyBeatenText[] = {
    text_start("I can dream, but I"
        t_line "can't ever fly…"
        t_done )
};
const txt_cmd_s BirdKeeperRoyAfterBattleText[] = {
    text_start("You have #MON"
        t_line "that know the HM"
        t_para "move FLY, don't"
        t_line "you? I envy you."
        t_done )
};
const txt_cmd_s PokefanmTrevorSeenText[] = {
    text_start("Hi. Did you know…?"
        t_para "#MON get more"
        t_line "friendly if you"
        t_para "train them in a"
        t_line "place that they"
        t_cont "remember."
        t_done )
};
const txt_cmd_s PokefanmTrevorBeatenText[] = {
    text_start("Where did I meet"
        t_line "this PSYDUCK?"
        t_done )
};
const txt_cmd_s PokefanmTrevorAfterBattleText[] = {
    text_start("If only there were"
        t_line "an easy way to"
        t_para "identify where I"
        t_line "got my #MON…"
        t_done )
    //db(0, 0) // filler
};
