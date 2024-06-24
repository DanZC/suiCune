#include "../constants.h"
#include "../util/scripting.h"
#include "MountMortar1FInside.h"
//// EVENTS
enum {
    MOUNTMORTAR1FINSIDE_BOULDER = 2,
    MOUNTMORTAR1FINSIDE_POKE_BALL1,
    MOUNTMORTAR1FINSIDE_POKE_BALL2,
    MOUNTMORTAR1FINSIDE_POKE_BALL3,
    MOUNTMORTAR1FINSIDE_POKE_BALL4,
    MOUNTMORTAR1FINSIDE_POKE_BALL5,
    MOUNTMORTAR1FINSIDE_SUPER_NERD1,
    MOUNTMORTAR1FINSIDE_SUPER_NERD2,
    MOUNTMORTAR1FINSIDE_POKE_BALL6,
    MOUNTMORTAR1FINSIDE_POKE_BALL7,
};

const Script_fn_t MountMortar1FInside_SceneScripts[] = {
    0,
};

const struct MapCallback MountMortar1FInside_MapCallbacks[] = {
    0,
};

const struct MapScripts MountMortar1FInside_MapScripts = {
    .scene_script_count = 0, // lengthof(MountMortar1FInside_SceneScripts),
    .scene_scripts = MountMortar1FInside_SceneScripts,

    .callback_count = 0, // lengthof(MountMortar1FInside_MapCallbacks),
    .callbacks = MountMortar1FInside_MapCallbacks,
};

static const struct CoordEvent MountMortar1FInside_CoordEvents[] = {
    0,
};

static const struct BGEvent MountMortar1FInside_BGEvents[] = {
    bg_event(30, 11, BGEVENT_ITEM, &MountMortar1FInsideHiddenMaxRepel),
};

static const struct WarpEventData MountMortar1FInside_WarpEvents[] = {
    warp_event(11, 47, MOUNT_MORTAR_1F_OUTSIDE, 5),
    warp_event(29, 47, MOUNT_MORTAR_1F_OUTSIDE, 6),
    warp_event(5, 39, MOUNT_MORTAR_1F_OUTSIDE, 8),
    warp_event(33, 41, MOUNT_MORTAR_1F_OUTSIDE, 9),
    warp_event(3, 19, MOUNT_MORTAR_B1F, 1),
    warp_event(9, 9, MOUNT_MORTAR_2F_INSIDE, 2),
};

static const struct ObjEvent MountMortar1FInside_ObjectEvents[] = {
    object_event(21, 43, SPRITE_BOULDER, SPRITEMOVEDATA_STRENGTH_BOULDER, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &MountMortar1FBoulder, -1),
    object_event(35, 38, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &MountMortar1FInsideEscapeRope, EVENT_MOUNT_MORTAR_1F_INSIDE_ESCAPE_ROPE),
    object_event(16, 10, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &MountMortar1FInsideMaxRevive, EVENT_MOUNT_MORTAR_1F_INSIDE_MAX_REVIVE),
    object_event(10, 27, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &MountMortar1FInsideHyperPotion, EVENT_MOUNT_MORTAR_1F_INSIDE_HYPER_POTION),
    object_event(22, 20, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &MountMortar1FInsideMaxPotion, EVENT_MOUNT_MORTAR_1F_INSIDE_MAX_POTION),
    object_event(35, 19, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &MountMortar1FInsideNugget, EVENT_MOUNT_MORTAR_1F_INSIDE_NUGGET),
    object_event(33, 43, SPRITE_SUPER_NERD, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerPokemaniacMiller, -1),
    object_event(24, 28, SPRITE_SUPER_NERD, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_TRAINER, 3, &TrainerSupernerdMarkus, -1),
    object_event(8, 16, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &MountMortar1FInsideIron, EVENT_MOUNT_MORTAR_1F_INSIDE_IRON),
    object_event(17, 17, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &MountMortar1FInsideUltraBall, EVENT_MOUNT_MORTAR_1F_INSIDE_ULTRA_BALL),
};

const struct MapEvents MountMortar1FInside_MapEvents = {
    .warp_event_count = lengthof(MountMortar1FInside_WarpEvents),
    .warp_events = MountMortar1FInside_WarpEvents,

    .coord_event_count = 0, // lengthof(MountMortar1FInside_CoordEvents),
    .coord_events = MountMortar1FInside_CoordEvents,

    .bg_event_count = lengthof(MountMortar1FInside_BGEvents),
    .bg_events = MountMortar1FInside_BGEvents,

    .obj_event_count = lengthof(MountMortar1FInside_ObjectEvents),
    .obj_events = MountMortar1FInside_ObjectEvents,
};

//// CODE

const struct TrainerObj TrainerPokemaniacMiller = {POKEMANIAC, MILLER, EVENT_BEAT_POKEMANIAC_MILLER, PokemaniacMillerSeenText, PokemaniacMillerBeatenText, 0, TrainerPokemaniacMiller_Script};
bool TrainerPokemaniacMiller_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(PokemaniacMillerAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSupernerdMarkus = {SUPER_NERD, MARKUS, EVENT_BEAT_SUPER_NERD_MARKUS, SupernerdMarkusSeenText, SupernerdMarkusBeatenText, 0, TrainerSupernerdMarkus_Script};
bool TrainerSupernerdMarkus_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SupernerdMarkusAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool MountMortar1FBoulder(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(StrengthBoulderScript)
    SCRIPT_END
}
const struct ItemBall MountMortar1FInsideEscapeRope = {ESCAPE_ROPE, 1};
const struct ItemBall MountMortar1FInsideMaxRevive = {MAX_REVIVE, 1};
const struct ItemBall MountMortar1FInsideHyperPotion = {HYPER_POTION, 1};
const struct ItemBall MountMortar1FInsideMaxPotion = {MAX_POTION, 1};
const struct ItemBall MountMortar1FInsideNugget = {NUGGET, 1};
const struct ItemBall MountMortar1FInsideIron = {IRON, 1};
const struct ItemBall MountMortar1FInsideUltraBall = {ULTRA_BALL, 1};
const struct HiddenItem MountMortar1FInsideHiddenMaxRepel = {MAX_REPEL, EVENT_MOUNT_MORTAR_1F_INSIDE_HIDDEN_MAX_REPEL};
const txt_cmd_s PokemaniacMillerSeenText[] = {
    text_start("I'm not losing"
        t_line "this time!"
        t_done )
};
const txt_cmd_s PokemaniacMillerBeatenText[] = {
    text_start("I lost to some"
        t_line "kid…?"
        t_done )
};
const txt_cmd_s PokemaniacMillerAfterBattleText[] = {
    text_start("A while back, this"
        t_line "karate dude wanted"
        t_para "to battle. He was"
        t_line "ridiculously good."
        t_para "He just thrashed"
        t_line "us silly."
        t_para "He went in deeper"
        t_line "saying it was for"
        t_para "his training. I"
        t_line "wonder how he is?"
        t_done )
};
const txt_cmd_s SupernerdMarkusSeenText[] = {
    text_start("Hey! HUGH!"
        t_done )
};
const txt_cmd_s SupernerdMarkusBeatenText[] = {
    text_start("I mistook you for"
        t_line "someone else…"
        t_done )
};
const txt_cmd_s SupernerdMarkusAfterBattleText[] = {
    text_start("I came to explore"
        t_line "MT.MORTAR, but I"
        t_para "got separated from"
        t_line "my partner…"
        t_para "Did you run into a"
        t_line "trainer who uses a"
        t_para "SEADRA that knows"
        t_line "WATERFALL?"
        t_done )
    //db(0, 0) // filler
};
