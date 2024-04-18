#include "../constants.h"
#include "../util/scripting.h"
#include "SproutTower1F.h"
//// EVENTS
enum {
    SPROUTTOWER1F_SAGE1 = 2,
    SPROUTTOWER1F_SAGE2,
    SPROUTTOWER1F_GRANNY,
    SPROUTTOWER1F_TEACHER,
    SPROUTTOWER1F_SAGE3,
    SPROUTTOWER1F_POKE_BALL,
};

const Script_fn_t SproutTower1F_SceneScripts[] = {
    0,
};

const struct MapCallback SproutTower1F_MapCallbacks[] = {
    0,
};

const struct MapScripts SproutTower1F_MapScripts = {
    .scene_script_count = 0, // lengthof(SproutTower1F_SceneScripts),
    .scene_scripts = SproutTower1F_SceneScripts,

    .callback_count = 0, // lengthof(SproutTower1F_MapCallbacks),
    .callbacks = SproutTower1F_MapCallbacks,
};

static const struct CoordEvent SproutTower1F_CoordEvents[] = {
    0,
};

static const struct BGEvent SproutTower1F_BGEvents[] = {
    bg_event(7, 15, BGEVENT_READ, &SproutTower1FStatue),
    bg_event(12, 15, BGEVENT_READ, &SproutTower1FStatue),
};

static const struct WarpEventData SproutTower1F_WarpEvents[] = {
    warp_event(9, 15, VIOLET_CITY, 7),
    warp_event(10, 15, VIOLET_CITY, 7),
    warp_event(6, 4, SPROUT_TOWER_2F, 1),
    warp_event(2, 6, SPROUT_TOWER_2F, 2),
    warp_event(17, 3, SPROUT_TOWER_2F, 3),
};

static const struct ObjEvent SproutTower1F_ObjectEvents[] = {
    object_event(7, 4, SPRITE_SAGE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &SproutTower1FSage1Script, -1),
    object_event(6, 7, SPRITE_SAGE, SPRITEMOVEDATA_WANDER, 1, 1, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &SproutTower1FSage2Script, -1),
    object_event(11, 12, SPRITE_GRANNY, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &SproutTower1FGrannyScript, -1),
    object_event(9, 9, SPRITE_TEACHER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &SproutTower1FTeacherScript, -1),
    object_event(3, 5, SPRITE_SAGE, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 4, &TrainerSageChow, -1),
    object_event(16, 7, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &SproutTower1FParlyzHeal, EVENT_SPROUT_TOWER_1F_PARLYZ_HEAL),
};

const struct MapEvents SproutTower1F_MapEvents = {
    .warp_event_count = lengthof(SproutTower1F_WarpEvents),
    .warp_events = SproutTower1F_WarpEvents,

    .coord_event_count = 0, // lengthof(SproutTower1F_CoordEvents),
    .coord_events = SproutTower1F_CoordEvents,

    .bg_event_count = lengthof(SproutTower1F_BGEvents),
    .bg_events = SproutTower1F_BGEvents,

    .obj_event_count = lengthof(SproutTower1F_ObjectEvents),
    .obj_events = SproutTower1F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "SproutTower1F.h"

bool SproutTower1FSage1Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(SproutTower1FSage1Text)
    SCRIPT_END
}
bool SproutTower1FSage2Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(SproutTower1FSage2Text)
    SCRIPT_END
}
bool SproutTower1FGrannyScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(SproutTower1FGrannyText)
    SCRIPT_END
}
bool SproutTower1FTeacherScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(SproutTower1FTeacherText)
    SCRIPT_END
}
const struct TrainerObj TrainerSageChow = {SAGE, CHOW, EVENT_BEAT_SAGE_CHOW, SageChowSeenText, SageChowBeatenText, 0, TrainerSageChow_Script};
bool TrainerSageChow_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SageChowAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct ItemBall SproutTower1FParlyzHeal = {PARLYZ_HEAL, 1};
bool SproutTower1FStatue(script_s* s) {
    SCRIPT_BEGIN
    jumptext(SproutTower1FStatueText)
    SCRIPT_END
}
const txt_cmd_s SageChowSeenText[] = {
    text_start("We stand guard in"
        t_line "this tower."
        t_para "Here, we express"
        t_line "our gratitude to"
        t_cont "honor all #MON."
        t_done )
};
const txt_cmd_s SageChowBeatenText[] = {
    text_start("Th-Thank you!"
        t_done )
};
const txt_cmd_s SageChowAfterBattleText[] = {
    text_start("All living beings"
        t_line "coexist through"
        t_cont "cooperation."
        t_para "We must always be"
        t_line "thankful for this."
        t_done )
};
const txt_cmd_s SproutTower1FSage1Text[] = {
    text_start("Only if you reach"
        t_line "the top will you"
        t_cont "obtain an HM."
        t_done )
};
const txt_cmd_s SproutTower1FSage2Text[] = {
    text_start("SPROUT TOWER was"
        t_line "built long ago"
        t_para "as a place for"
        t_line "#MON training."
        t_done )
};
const txt_cmd_s SproutTower1FGrannyText[] = {
    text_start("A BELLSPROUT over"
        t_line "100 feet tall…"
        t_para "People say that it"
        t_line "became the center"
        t_cont "pillar here."
        t_done )
};
const txt_cmd_s SproutTower1FTeacherText[] = {
    text_start("See the pillar"
        t_line "shaking?"
        t_para "People are train-"
        t_line "ing upstairs."
        t_done )
};
const txt_cmd_s SproutTower1FStatueText[] = {
    text_start("A #MON statue…"
        t_para "It looks very"
        t_line "distinguished."
        t_done )
    //db(0, 0) // filler
};
