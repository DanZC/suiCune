#include "../constants.h"
#include "../util/scripting.h"
#include "SproutTower2F.h"
//// EVENTS
enum {
    SPROUTTOWER2F_SAGE1 = 2,
    SPROUTTOWER2F_SAGE2,
    SPROUTTOWER2F_POKE_BALL,
};

const Script_fn_t SproutTower2F_SceneScripts[] = {
    0,
};

const struct MapCallback SproutTower2F_MapCallbacks[] = {
    0,
};

const struct MapScripts SproutTower2F_MapScripts = {
    .scene_script_count = 0, // lengthof(SproutTower2F_SceneScripts),
    .scene_scripts = SproutTower2F_SceneScripts,

    .callback_count = 0, // lengthof(SproutTower2F_MapCallbacks),
    .callbacks = SproutTower2F_MapCallbacks,
};

static const struct CoordEvent SproutTower2F_CoordEvents[] = {
    0,
};

static const struct BGEvent SproutTower2F_BGEvents[] = {
    bg_event(12, 15, BGEVENT_READ, &SproutTower2FStatue),
};

static const struct WarpEventData SproutTower2F_WarpEvents[] = {
    warp_event(6, 4, SPROUT_TOWER_1F, 3),
    warp_event(2, 6, SPROUT_TOWER_1F, 4),
    warp_event(17, 3, SPROUT_TOWER_1F, 5),
    warp_event(10, 14, SPROUT_TOWER_3F, 1),
};

static const struct ObjEvent SproutTower2F_ObjectEvents[] = {
    object_event(12, 3, SPRITE_SAGE, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 4, &TrainerSageNico, -1),
    object_event(9, 14, SPRITE_SAGE, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 5, &TrainerSageEdmond, -1),
    object_event(3, 1, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &SproutTower2FXAccuracy, EVENT_SPROUT_TOWER_2F_X_ACCURACY),
};

const struct MapEvents SproutTower2F_MapEvents = {
    .warp_event_count = lengthof(SproutTower2F_WarpEvents),
    .warp_events = SproutTower2F_WarpEvents,

    .coord_event_count = 0, // lengthof(SproutTower2F_CoordEvents),
    .coord_events = SproutTower2F_CoordEvents,

    .bg_event_count = lengthof(SproutTower2F_BGEvents),
    .bg_events = SproutTower2F_BGEvents,

    .obj_event_count = lengthof(SproutTower2F_ObjectEvents),
    .obj_events = SproutTower2F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "SproutTower2F.h"

const struct TrainerObj TrainerSageNico = {SAGE, NICO, EVENT_BEAT_SAGE_NICO, SageNicoSeenText, SageNicoBeatenText, 0, TrainerSageNico_Script};
bool TrainerSageNico_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SageNicoAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSageEdmond = {SAGE, EDMOND, EVENT_BEAT_SAGE_EDMOND, SageEdmondSeenText, SageEdmondBeatenText, 0, TrainerSageEdmond_Script};
bool TrainerSageEdmond_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SageEdmondAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool SproutTower2FStatue(script_s* s) {
    SCRIPT_BEGIN
    jumptext(SproutTower2FStatueText)
    SCRIPT_END
}
const struct ItemBall SproutTower2FXAccuracy = {X_ACCURACY, 1};
const txt_cmd_s SageNicoSeenText[] = {
    text_start("However hard we"
        t_line "battle, the TOWER"
        t_cont "will stand strong."
        t_done )
};
const txt_cmd_s SageNicoBeatenText[] = {
    text_start("I fought hard but"
        t_line "I'm too weak."
        t_done )
};
const txt_cmd_s SageNicoAfterBattleText[] = {
    text_start("The flexible pil-"
        t_line "lar protects the"
        t_para "TOWER, even from"
        t_line "earthquakes."
        t_done )
};
const txt_cmd_s SageEdmondSeenText[] = {
    text_start("…Sway like leaves"
        t_line "in the wind…"
        t_done )
};
const txt_cmd_s SageEdmondBeatenText[] = {
    text_start("Oh, I'm weak!"
        t_done )
};
const txt_cmd_s SageEdmondAfterBattleText[] = {
    text_start("I tried to copy"
        t_line "BELLSPROUT's"
        t_para "gentle movements"
        t_line "for battle…"
        t_para "But I didn't train"
        t_line "well enough."
        t_done )
};
const txt_cmd_s SproutTower2FStatueText[] = {
    text_start("A #MON statue…"
        t_para "It looks very"
        t_line "distinguished."
        t_done )
    //db(0, 0) // filler
};
