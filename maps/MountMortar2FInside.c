#include "../constants.h"
#include "../util/scripting.h"
#include "MountMortar2FInside.h"
//// EVENTS
enum {
    MOUNTMORTAR2FINSIDE_POKE_BALL1 = 2,
    MOUNTMORTAR2FINSIDE_POKE_BALL2,
    MOUNTMORTAR2FINSIDE_POKE_BALL3,
    MOUNTMORTAR2FINSIDE_POKE_BALL4,
    MOUNTMORTAR2FINSIDE_POKE_BALL5,
    MOUNTMORTAR2FINSIDE_POKE_BALL6,
    MOUNTMORTAR2FINSIDE_SUPER_NERD,
};

const Script_fn_t MountMortar2FInside_SceneScripts[] = {
    0,
};

const struct MapCallback MountMortar2FInside_MapCallbacks[] = {
    0,
};

const struct MapScripts MountMortar2FInside_MapScripts = {
    .scene_script_count = 0, // lengthof(MountMortar2FInside_SceneScripts),
    .scene_scripts = MountMortar2FInside_SceneScripts,

    .callback_count = 0, // lengthof(MountMortar2FInside_MapCallbacks),
    .callbacks = MountMortar2FInside_MapCallbacks,
};

static const struct CoordEvent MountMortar2FInside_CoordEvents[] = {
    0,
};

static const struct BGEvent MountMortar2FInside_BGEvents[] = {
    bg_event(24, 8, BGEVENT_ITEM, &MountMortar2FInsideHiddenFullRestore),
};

static const struct WarpEventData MountMortar2FInside_WarpEvents[] = {
    warp_event(17, 33, MOUNT_MORTAR_1F_OUTSIDE, 4),
    warp_event(3, 5, MOUNT_MORTAR_1F_INSIDE, 6),
};

static const struct ObjEvent MountMortar2FInside_ObjectEvents[] = {
    object_event(28, 22, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &MountMortar2FInsideMaxPotion, EVENT_MOUNT_MORTAR_2F_INSIDE_MAX_POTION),
    object_event(2, 33, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &MountMortar2FInsideRareCandy, EVENT_MOUNT_MORTAR_2F_INSIDE_RARE_CANDY),
    object_event(19, 17, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &MountMortar2FInsideTMDefenseCurl, EVENT_MOUNT_MORTAR_2F_INSIDE_TM_DEFENSE_CURL),
    object_event(16, 5, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &MountMortar2FInsideDragonScale, EVENT_MOUNT_MORTAR_2F_INSIDE_DRAGON_SCALE),
    object_event(9, 11, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &MountMortar2FInsideElixer, EVENT_MOUNT_MORTAR_2F_INSIDE_ELIXER),
    object_event(28, 5, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &MountMortar2FInsideEscapeRope, EVENT_MOUNT_MORTAR_2F_INSIDE_ESCAPE_ROPE),
    object_event(13, 26, SPRITE_SUPER_NERD, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_TRAINER, 2, &TrainerSupernerdHugh, -1),
};

const struct MapEvents MountMortar2FInside_MapEvents = {
    .warp_event_count = lengthof(MountMortar2FInside_WarpEvents),
    .warp_events = MountMortar2FInside_WarpEvents,

    .coord_event_count = 0, // lengthof(MountMortar2FInside_CoordEvents),
    .coord_events = MountMortar2FInside_CoordEvents,

    .bg_event_count = lengthof(MountMortar2FInside_BGEvents),
    .bg_events = MountMortar2FInside_BGEvents,

    .obj_event_count = lengthof(MountMortar2FInside_ObjectEvents),
    .obj_events = MountMortar2FInside_ObjectEvents,
};

//// CODE

const struct TrainerObj TrainerSupernerdHugh = {SUPER_NERD, HUGH, EVENT_BEAT_SUPER_NERD_HUGH, SupernerdHughSeenText, SupernerdHughBeatenText, 0, TrainerSupernerdHugh_Script};
bool TrainerSupernerdHugh_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SupernerdHughAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct ItemBall MountMortar2FInsideMaxPotion = {MAX_POTION, 1};
const struct ItemBall MountMortar2FInsideRareCandy = {RARE_CANDY, 1};
const struct ItemBall MountMortar2FInsideTMDefenseCurl = {TM_DEFENSE_CURL, 1};
const struct ItemBall MountMortar2FInsideDragonScale = {DRAGON_SCALE, 1};
const struct ItemBall MountMortar2FInsideElixer = {ELIXER, 1};
const struct ItemBall MountMortar2FInsideEscapeRope = {ESCAPE_ROPE, 1};
const struct HiddenItem MountMortar2FInsideHiddenFullRestore = {FULL_RESTORE, EVENT_MOUNT_MORTAR_2F_INSIDE_HIDDEN_FULL_RESTORE};
const txt_cmd_s SupernerdHughSeenText[] = {
    text_start("Yo! MARKUS!"
        t_done )
};
const txt_cmd_s SupernerdHughBeatenText[] = {
    text_start("Sorry, my mistake."
        t_done )
};
const txt_cmd_s SupernerdHughAfterBattleText[] = {
    text_start("I'm investigating"
        t_line "MT.MORTAR, but my"
        t_cont "pal's gone AWOL."
        t_para "Have you seen a"
        t_line "trainer who has a"
        t_para "SLOWPOKE that can"
        t_line "use STRENGTH?"
        t_done )
    //db(0, 0) // filler
};
