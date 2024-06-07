#include "../constants.h"
#include "../util/scripting.h"
#include "OlivineLighthouse3F.h"
//// EVENTS
enum {
    OLIVINELIGHTHOUSE3F_SAILOR = 2,
    OLIVINELIGHTHOUSE3F_GENTLEMAN,
    OLIVINELIGHTHOUSE3F_YOUNGSTER,
    OLIVINELIGHTHOUSE3F_POKE_BALL,
};

const Script_fn_t OlivineLighthouse3F_SceneScripts[] = {
    0,
};

const struct MapCallback OlivineLighthouse3F_MapCallbacks[] = {
    0,
};

const struct MapScripts OlivineLighthouse3F_MapScripts = {
    .scene_script_count = 0, // lengthof(OlivineLighthouse3F_SceneScripts),
    .scene_scripts = OlivineLighthouse3F_SceneScripts,

    .callback_count = 0, // lengthof(OlivineLighthouse3F_MapCallbacks),
    .callbacks = OlivineLighthouse3F_MapCallbacks,
};

static const struct CoordEvent OlivineLighthouse3F_CoordEvents[] = {
    0,
};

static const struct BGEvent OlivineLighthouse3F_BGEvents[] = {
    0,
};

static const struct WarpEventData OlivineLighthouse3F_WarpEvents[] = {
    warp_event(13, 3, OLIVINE_LIGHTHOUSE_4F, 1),
    warp_event(5, 3, OLIVINE_LIGHTHOUSE_2F, 2),
    warp_event(9, 5, OLIVINE_LIGHTHOUSE_4F, 4),
    warp_event(16, 11, OLIVINE_LIGHTHOUSE_2F, 5),
    warp_event(17, 11, OLIVINE_LIGHTHOUSE_2F, 6),
    warp_event(16, 9, OLIVINE_LIGHTHOUSE_4F, 5),
    warp_event(17, 9, OLIVINE_LIGHTHOUSE_4F, 6),
    warp_event(8, 3, OLIVINE_LIGHTHOUSE_4F, 7),
    warp_event(9, 3, OLIVINE_LIGHTHOUSE_4F, 8),
};

static const struct ObjEvent OlivineLighthouse3F_ObjectEvents[] = {
    object_event(9, 2, SPRITE_SAILOR, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 1, &TrainerSailorTerrell, -1),
    object_event(13, 5, SPRITE_GENTLEMAN, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 4, &TrainerGentlemanPreston, -1),
    object_event(3, 9, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerBirdKeeperTheo, -1),
    object_event(8, 2, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &OlivineLighthouse3FEther, EVENT_OLIVINE_LIGHTHOUSE_3F_ETHER),
};

const struct MapEvents OlivineLighthouse3F_MapEvents = {
    .warp_event_count = lengthof(OlivineLighthouse3F_WarpEvents),
    .warp_events = OlivineLighthouse3F_WarpEvents,

    .coord_event_count = 0, // lengthof(OlivineLighthouse3F_CoordEvents),
    .coord_events = OlivineLighthouse3F_CoordEvents,

    .bg_event_count = 0, // lengthof(OlivineLighthouse3F_BGEvents),
    .bg_events = OlivineLighthouse3F_BGEvents,

    .obj_event_count = lengthof(OlivineLighthouse3F_ObjectEvents),
    .obj_events = OlivineLighthouse3F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "OlivineLighthouse3F.h"

const struct TrainerObj TrainerBirdKeeperTheo = {BIRD_KEEPER, THEO, EVENT_BEAT_BIRD_KEEPER_THEO, BirdKeeperTheoSeenText, BirdKeeperTheoBeatenText, 0, TrainerBirdKeeperTheo_Script};
bool TrainerBirdKeeperTheo_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(BirdKeeperTheoAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerGentlemanPreston = {GENTLEMAN, PRESTON, EVENT_BEAT_GENTLEMAN_PRESTON, GentlemanPrestonSeenText, GentlemanPrestonBeatenText, 0, TrainerGentlemanPreston_Script};
bool TrainerGentlemanPreston_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(GentlemanPrestonAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSailorTerrell = {SAILOR, TERRELL, EVENT_BEAT_SAILOR_TERRELL, SailorTerrellSeenText, SailorTerrellBeatenText, 0, TrainerSailorTerrell_Script};
bool TrainerSailorTerrell_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SailorTerrellAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct ItemBall OlivineLighthouse3FEther = {ETHER, 1};
const txt_cmd_s BirdKeeperTheoSeenText[] = {
    text_start("Why are you here?"
        t_line "Are you just going"
        t_para "to gawk? I suggest"
        t_line "that you leave!"
        t_done )
};
const txt_cmd_s BirdKeeperTheoBeatenText[] = {
    text_start("You really are"
        t_line "concerned…"
        t_done )
};
const txt_cmd_s BirdKeeperTheoAfterBattleText[] = {
    text_start("How the heck do"
        t_line "you go up?"
        t_para "I want to visit"
        t_line "the sick #MON,"
        t_para "but I can't get up"
        t_line "there…"
        t_done )
};
const txt_cmd_s SailorTerrellSeenText[] = {
    text_start("Sailors are both"
        t_line "kind and strong."
        t_cont "How about you?"
        t_done )
};
const txt_cmd_s SailorTerrellBeatenText[] = {
    text_start("You are both kind"
        t_line "and strong…"
        t_done )
};
const txt_cmd_s SailorTerrellAfterBattleText[] = {
    text_start("Every time I come"
        t_line "back to OLIVINE, I"
        t_cont "visit the GYM."
        t_para "The GYM LEADER's"
        t_line "#MON type has"
        t_para "changed without me"
        t_line "noticing."
        t_done )
};
const txt_cmd_s GentlemanPrestonSeenText[] = {
    text_start("I travel the world"
        t_line "to train my #-"
        t_cont "MON. I wish to"
        t_cont "battle with you."
        t_done )
};
const txt_cmd_s GentlemanPrestonBeatenText[] = {
    text_start("…sigh… I must"
        t_line "train some more…"
        t_done )
};
const txt_cmd_s GentlemanPrestonAfterBattleText[] = {
    text_start("JASMINE used to"
        t_line "use rock #MON"
        t_cont "like ONIX."
        t_done )
    //db(0, 0) // filler
};
