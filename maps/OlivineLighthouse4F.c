#include "../constants.h"
#include "../util/scripting.h"
#include "OlivineLighthouse4F.h"
//// EVENTS
enum {
    OLIVINELIGHTHOUSE4F_SAILOR = 2,
    OLIVINELIGHTHOUSE4F_LASS,
};

const Script_fn_t OlivineLighthouse4F_SceneScripts[] = {
    0,
};

const struct MapCallback OlivineLighthouse4F_MapCallbacks[] = {
    0,
};

const struct MapScripts OlivineLighthouse4F_MapScripts = {
    .scene_script_count = 0, // lengthof(OlivineLighthouse4F_SceneScripts),
    .scene_scripts = OlivineLighthouse4F_SceneScripts,

    .callback_count = 0, // lengthof(OlivineLighthouse4F_MapCallbacks),
    .callbacks = OlivineLighthouse4F_MapCallbacks,
};

static const struct CoordEvent OlivineLighthouse4F_CoordEvents[] = {
    0,
};

static const struct BGEvent OlivineLighthouse4F_BGEvents[] = {
    0,
};

static const struct WarpEventData OlivineLighthouse4F_WarpEvents[] = {
    warp_event(13, 3, OLIVINE_LIGHTHOUSE_3F, 1),
    warp_event(3, 5, OLIVINE_LIGHTHOUSE_5F, 2),
    warp_event(9, 7, OLIVINE_LIGHTHOUSE_5F, 3),
    warp_event(9, 5, OLIVINE_LIGHTHOUSE_3F, 3),
    warp_event(16, 9, OLIVINE_LIGHTHOUSE_3F, 6),
    warp_event(17, 9, OLIVINE_LIGHTHOUSE_3F, 7),
    warp_event(8, 3, OLIVINE_LIGHTHOUSE_3F, 8),
    warp_event(9, 3, OLIVINE_LIGHTHOUSE_3F, 9),
    warp_event(16, 7, OLIVINE_LIGHTHOUSE_5F, 4),
    warp_event(17, 7, OLIVINE_LIGHTHOUSE_5F, 5),
};

static const struct ObjEvent OlivineLighthouse4F_ObjectEvents[] = {
    object_event(7, 14, SPRITE_SAILOR, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerSailorKent, -1),
    object_event(11, 2, SPRITE_LASS, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 1, &TrainerLassConnie, -1),
};

const struct MapEvents OlivineLighthouse4F_MapEvents = {
    .warp_event_count = lengthof(OlivineLighthouse4F_WarpEvents),
    .warp_events = OlivineLighthouse4F_WarpEvents,

    .coord_event_count = 0, // lengthof(OlivineLighthouse4F_CoordEvents),
    .coord_events = OlivineLighthouse4F_CoordEvents,

    .bg_event_count = 0, // lengthof(OlivineLighthouse4F_BGEvents),
    .bg_events = OlivineLighthouse4F_BGEvents,

    .obj_event_count = lengthof(OlivineLighthouse4F_ObjectEvents),
    .obj_events = OlivineLighthouse4F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "OlivineLighthouse4F.h"

const struct TrainerObj TrainerLassConnie = {LASS, CONNIE1, EVENT_BEAT_LASS_CONNIE, LassConnie1SeenText, LassConnie1BeatenText, 0, TrainerLassConnie_Script};
bool TrainerLassConnie_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(LassConnie1AfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSailorKent = {SAILOR, KENT, EVENT_BEAT_SAILOR_KENT, SailorKentSeenText, SailorKentBeatenText, 0, TrainerSailorKent_Script};
bool TrainerSailorKent_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SailorKentAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const txt_cmd_s SailorKentSeenText[] = {
    text_start("JASMINE must be"
        t_line "worried sick about"
        t_cont "the #MON here."
        t_para "She won't even"
        t_line "smile these days."
        t_done )
};
const txt_cmd_s SailorKentBeatenText[] = {
    text_start("I can't manage a"
        t_line "smile either…"
        t_done )
};
const txt_cmd_s SailorKentAfterBattleText[] = {
    text_start("Speaking of sick,"
        t_line "I've heard there's"
        t_para "a good PHARMACY in"
        t_line "CIANWOOD."
        t_done )
};
const txt_cmd_s LassConnie1SeenText[] = {
    text_start("JASMINE is this"
        t_line "city's GYM LEADER."
        t_para "I mean to bring"
        t_line "her back with me."
        t_para "Nobody had better"
        t_line "get in my way!"
        t_done )
};
const txt_cmd_s LassConnie1BeatenText[] = {
    text_start("Aaack! My #MON!"
        t_done )
};
const txt_cmd_s LassConnie1AfterBattleText[] = {
    text_start("Right. Anybody"
        t_line "would be worried"
        t_cont "if his or her own"
        t_cont "#MON were hurt."
        t_para "I'll pray for the"
        t_line "#MON here, so"
        t_para "JASMINE can come"
        t_line "back to the GYM."
        t_done )
    //db(0, 0) // filler
};
