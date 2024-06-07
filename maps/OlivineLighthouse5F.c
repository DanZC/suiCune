#include "../constants.h"
#include "../util/scripting.h"
#include "OlivineLighthouse5F.h"
//// EVENTS
enum {
    OLIVINELIGHTHOUSE5F_SAILOR = 2,
    OLIVINELIGHTHOUSE5F_YOUNGSTER,
    OLIVINELIGHTHOUSE5F_POKE_BALL1,
    OLIVINELIGHTHOUSE5F_POKE_BALL2,
    OLIVINELIGHTHOUSE5F_POKE_BALL3,
};

const Script_fn_t OlivineLighthouse5F_SceneScripts[] = {
    0,
};

const struct MapCallback OlivineLighthouse5F_MapCallbacks[] = {
    0,
};

const struct MapScripts OlivineLighthouse5F_MapScripts = {
    .scene_script_count = 0, // lengthof(OlivineLighthouse5F_SceneScripts),
    .scene_scripts = OlivineLighthouse5F_SceneScripts,

    .callback_count = 0, // lengthof(OlivineLighthouse5F_MapCallbacks),
    .callbacks = OlivineLighthouse5F_MapCallbacks,
};

static const struct CoordEvent OlivineLighthouse5F_CoordEvents[] = {
    0,
};

static const struct BGEvent OlivineLighthouse5F_BGEvents[] = {
    bg_event(3, 13, BGEVENT_ITEM, &OlivineLighthouse5FHiddenHyperPotion),
};

static const struct WarpEventData OlivineLighthouse5F_WarpEvents[] = {
    warp_event(9, 15, OLIVINE_LIGHTHOUSE_6F, 1),
    warp_event(3, 5, OLIVINE_LIGHTHOUSE_4F, 2),
    warp_event(9, 7, OLIVINE_LIGHTHOUSE_4F, 3),
    warp_event(16, 7, OLIVINE_LIGHTHOUSE_4F, 9),
    warp_event(17, 7, OLIVINE_LIGHTHOUSE_4F, 10),
    warp_event(16, 5, OLIVINE_LIGHTHOUSE_6F, 2),
    warp_event(17, 5, OLIVINE_LIGHTHOUSE_6F, 3),
};

static const struct ObjEvent OlivineLighthouse5F_ObjectEvents[] = {
    object_event(8, 11, SPRITE_SAILOR, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerSailorErnest, -1),
    object_event(8, 3, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 4, &TrainerBirdKeeperDenis, -1),
    object_event(15, 12, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &OlivineLighthouse5FRareCandy, EVENT_OLIVINE_LIGHTHOUSE_5F_RARE_CANDY),
    object_event(6, 15, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &OlivineLighthouse5FSuperRepel, EVENT_OLIVINE_LIGHTHOUSE_5F_SUPER_REPEL),
    object_event(2, 13, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &OlivineLighthouse5FTMSwagger, EVENT_OLIVINE_LIGHTHOUSE_5F_TM_SWAGGER),
};

const struct MapEvents OlivineLighthouse5F_MapEvents = {
    .warp_event_count = lengthof(OlivineLighthouse5F_WarpEvents),
    .warp_events = OlivineLighthouse5F_WarpEvents,

    .coord_event_count = 0, // lengthof(OlivineLighthouse5F_CoordEvents),
    .coord_events = OlivineLighthouse5F_CoordEvents,

    .bg_event_count = lengthof(OlivineLighthouse5F_BGEvents),
    .bg_events = OlivineLighthouse5F_BGEvents,

    .obj_event_count = lengthof(OlivineLighthouse5F_ObjectEvents),
    .obj_events = OlivineLighthouse5F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "OlivineLighthouse5F.h"

const struct TrainerObj TrainerBirdKeeperDenis = {BIRD_KEEPER, DENIS, EVENT_BEAT_BIRD_KEEPER_DENIS, BirdKeeperDenisSeenText, BirdKeeperDenisBeatenText, 0, TrainerBirdKeeperDenis_Script};
bool TrainerBirdKeeperDenis_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(BirdKeeperDenisAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSailorErnest = {SAILOR, ERNEST, EVENT_BEAT_SAILOR_ERNEST, SailorErnestSeenText, SailorErnestBeatenText, 0, TrainerSailorErnest_Script};
bool TrainerSailorErnest_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SailorErnestAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct ItemBall OlivineLighthouse5FRareCandy = {RARE_CANDY, 1};
const struct ItemBall OlivineLighthouse5FSuperRepel = {SUPER_REPEL, 1};
const struct ItemBall OlivineLighthouse5FTMSwagger = {TM_SWAGGER, 1};
const struct HiddenItem OlivineLighthouse5FHiddenHyperPotion = {HYPER_POTION, EVENT_OLIVINE_LIGHTHOUSE_5F_HIDDEN_HYPER_POTION};
const txt_cmd_s SailorErnestSeenText[] = {
    text_start("I wanted to battle"
        t_line "JASMINE, but she's"
        t_para "not up to it now."
        t_line "So, how about you?"
        t_done )
};
const txt_cmd_s SailorErnestBeatenText[] = {
    text_start("Whoa, whoa. You're"
        t_line "overwhelming!"
        t_done )
};
const txt_cmd_s SailorErnestAfterBattleText[] = {
    text_start("A GYM LEADER isn't"
        t_line "just about being"
        t_para "strong. A LEADER"
        t_line "also needs to be"
        t_cont "compassionate."
        t_done )
};
const txt_cmd_s BirdKeeperDenisSeenText[] = {
    text_start("We're pretty high"
        t_line "up here. My bird"
        t_para "#MON are in"
        t_line "prime form."
        t_done )
};
const txt_cmd_s BirdKeeperDenisBeatenText[] = {
    text_start("Oops…They crashed…"
        t_done )
};
const txt_cmd_s BirdKeeperDenisAfterBattleText[] = {
    text_start("My #MON learned"
        t_line "how to use FLY in"
        t_cont "CIANWOOD."
        t_para "Well, since I'm a"
        t_line "loser, I'll FLY"
        t_cont "across the sea…"
        t_done )
    //db(0, 0) // filler
};
