#include "../constants.h"
#include "../util/scripting.h"
#include "GoldenrodDeptStoreB1F.h"
//// EVENTS
enum {
    GOLDENRODDEPTSTOREB1F_POKE_BALL1 = 2,
    GOLDENRODDEPTSTOREB1F_POKE_BALL2,
    GOLDENRODDEPTSTOREB1F_POKE_BALL3,
    GOLDENRODDEPTSTOREB1F_POKE_BALL4,
    GOLDENRODDEPTSTOREB1F_BLACK_BELT1,
    GOLDENRODDEPTSTOREB1F_BLACK_BELT2,
    GOLDENRODDEPTSTOREB1F_BLACK_BELT3,
    GOLDENRODDEPTSTOREB1F_MACHOP,
};

const Script_fn_t GoldenrodDeptStoreB1F_SceneScripts[] = {
    0,
};

const struct MapCallback GoldenrodDeptStoreB1F_MapCallbacks[] = {
    map_callback(MAPCALLBACK_TILES, GoldenrodDeptStoreB1F_MapScripts_ClearBoxes),
    map_callback(MAPCALLBACK_NEWMAP, GoldenrodDeptStoreB1F_MapScripts_Unblock),
};

const struct MapScripts GoldenrodDeptStoreB1F_MapScripts = {
    .scene_script_count = 0, // lengthof(GoldenrodDeptStoreB1F_SceneScripts),
    .scene_scripts = GoldenrodDeptStoreB1F_SceneScripts,

    .callback_count = lengthof(GoldenrodDeptStoreB1F_MapCallbacks),
    .callbacks = GoldenrodDeptStoreB1F_MapCallbacks,
};

static const struct CoordEvent GoldenrodDeptStoreB1F_CoordEvents[] = {
    0,
};

static const struct BGEvent GoldenrodDeptStoreB1F_BGEvents[] = {
    0,
};

static const struct WarpEventData GoldenrodDeptStoreB1F_WarpEvents[] = {
    warp_event(17, 2, GOLDENROD_UNDERGROUND_WAREHOUSE, 3),
    warp_event(9, 4, GOLDENROD_DEPT_STORE_ELEVATOR, 1),
    warp_event(10, 4, GOLDENROD_DEPT_STORE_ELEVATOR, 2),
};

static const struct ObjEvent GoldenrodDeptStoreB1F_ObjectEvents[] = {
    object_event(10, 15, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &GoldenrodDeptStoreB1FEther, EVENT_GOLDENROD_DEPT_STORE_B1F_ETHER),
    object_event(14, 2, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &GoldenrodDeptStoreB1FAmuletCoin, EVENT_GOLDENROD_DEPT_STORE_B1F_AMULET_COIN),
    object_event(6, 3, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &GoldenrodDeptStoreB1FBurnHeal, EVENT_GOLDENROD_DEPT_STORE_B1F_BURN_HEAL),
    object_event(15, 15, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &GoldenrodDeptStoreB1FUltraBall, EVENT_GOLDENROD_DEPT_STORE_B1F_ULTRA_BALL),
    object_event(9, 10, SPRITE_BLACK_BELT, SPRITEMOVEDATA_WALK_UP_DOWN, 0, 1, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &GoldenrodDeptStoreB1FBlackBelt1Script, -1),
    object_event(4, 8, SPRITE_BLACK_BELT, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &GoldenrodDeptStoreB1FBlackBelt2Script, -1),
    object_event(6, 13, SPRITE_BLACK_BELT, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &GoldenrodDeptStoreB1FBlackBelt3Script, -1),
    object_event(7, 7, SPRITE_MACHOP, SPRITEMOVEDATA_POKEMON, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &GoldenrodDeptStoreB1FMachopScript, -1),
};

const struct MapEvents GoldenrodDeptStoreB1F_MapEvents = {
    .warp_event_count = lengthof(GoldenrodDeptStoreB1F_WarpEvents),
    .warp_events = GoldenrodDeptStoreB1F_WarpEvents,

    .coord_event_count = 0, // lengthof(GoldenrodDeptStoreB1F_CoordEvents),
    .coord_events = GoldenrodDeptStoreB1F_CoordEvents,

    .bg_event_count = 0, // lengthof(GoldenrodDeptStoreB1F_BGEvents),
    .bg_events = GoldenrodDeptStoreB1F_BGEvents,

    .obj_event_count = lengthof(GoldenrodDeptStoreB1F_ObjectEvents),
    .obj_events = GoldenrodDeptStoreB1F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "GoldenrodDeptStoreB1F.h"

bool GoldenrodDeptStoreB1F_MapScripts_ClearBoxes(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_RECEIVED_CARD_KEY)
    iftrue(GotCardKey)
    goto Continue;
GotCardKey:
    changeblock(16, 4, 0x0d) // floor
Continue:
    checkevent(EVENT_GOLDENROD_DEPT_STORE_B1F_LAYOUT_2)
    iftrue(Layout2)
    checkevent(EVENT_GOLDENROD_DEPT_STORE_B1F_LAYOUT_3)
    iftrue(Layout3)
    changeblock(10, 8, 0x0d) // floor
    s_endcallback
Layout2:
    changeblock(4, 10, 0x0d) // floor
    s_endcallback
Layout3:
    changeblock(10, 12, 0x0d) // floor
    s_endcallback
    SCRIPT_END
}
bool GoldenrodDeptStoreB1F_MapScripts_Unblock(script_s* s) {
    SCRIPT_BEGIN
    clearevent(EVENT_GOLDENROD_UNDERGROUND_WAREHOUSE_BLOCKED_OFF)
    s_endcallback
    SCRIPT_END
}
bool GoldenrodDeptStoreB1FBlackBelt1Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(GoldenrodDeptStoreB1FBlackBelt1Text)
    SCRIPT_END
}
bool GoldenrodDeptStoreB1FBlackBelt2Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(GoldenrodDeptStoreB1FBlackBelt2Text)
    SCRIPT_END
}
bool GoldenrodDeptStoreB1FBlackBelt3Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(GoldenrodDeptStoreB1FBlackBelt3Text)
    SCRIPT_END
}
bool GoldenrodDeptStoreB1FMachopScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(GoldenrodDeptStoreB1FMachokeText)
    playcry(MACHOKE)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct ItemBall GoldenrodDeptStoreB1FEther = {ETHER, 1};
const struct ItemBall GoldenrodDeptStoreB1FAmuletCoin = {AMULET_COIN, 1};
const struct ItemBall GoldenrodDeptStoreB1FBurnHeal = {BURN_HEAL, 1};
const struct ItemBall GoldenrodDeptStoreB1FUltraBall = {ULTRA_BALL, 1};
const txt_cmd_s GoldenrodDeptStoreB1FBlackBelt1Text[] = {
    text_start("Hey, kid! You're"
        t_line "holding us up!"
        t_para "Our policy is to"
        t_line "work behind the"
        t_para "scenes where no"
        t_line "one can see us!"
        t_done )
};
const txt_cmd_s GoldenrodDeptStoreB1FBlackBelt2Text[] = {
    text_start("I lose my passion"
        t_line "for work if some-"
        t_cont "one's watching."
        t_para "Come on, kid,"
        t_line "scoot!"
        t_done )
};
const txt_cmd_s GoldenrodDeptStoreB1FBlackBelt3Text[] = {
    text_start("Oohah! Oohah!"
        t_para "The stuff on the"
        t_line "ground's junk."
        t_para "Take it if you"
        t_line "want it!"
        t_done )
};
const txt_cmd_s GoldenrodDeptStoreB1FMachokeText[] = {
    text_start("MACHOKE: Maaacho!"
        t_done )
    //db(0, 0) // filler
};
