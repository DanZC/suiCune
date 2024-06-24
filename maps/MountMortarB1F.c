#include "../constants.h"
#include "../util/scripting.h"
#include "MountMortarB1F.h"
//// EVENTS
enum {
    MOUNTMORTARB1F_POKE_BALL1 = 2,
    MOUNTMORTARB1F_POKE_BALL2,
    MOUNTMORTARB1F_BOULDER,
    MOUNTMORTARB1F_KIYO,
    MOUNTMORTARB1F_POKE_BALL3,
    MOUNTMORTARB1F_POKE_BALL4,
    MOUNTMORTARB1F_POKE_BALL5,
};

const Script_fn_t MountMortarB1F_SceneScripts[] = {
    0,
};

const struct MapCallback MountMortarB1F_MapCallbacks[] = {
    0,
};

const struct MapScripts MountMortarB1F_MapScripts = {
    .scene_script_count = 0, // lengthof(MountMortarB1F_SceneScripts),
    .scene_scripts = MountMortarB1F_SceneScripts,

    .callback_count = 0, // lengthof(MountMortarB1F_MapCallbacks),
    .callbacks = MountMortarB1F_MapCallbacks,
};

static const struct CoordEvent MountMortarB1F_CoordEvents[] = {
    0,
};

static const struct BGEvent MountMortarB1F_BGEvents[] = {
    bg_event(4, 6, BGEVENT_ITEM, &MountMortarB1FHiddenMaxRevive),
};

static const struct WarpEventData MountMortarB1F_WarpEvents[] = {
    warp_event(3, 3, MOUNT_MORTAR_1F_INSIDE, 5),
    warp_event(19, 29, MOUNT_MORTAR_1F_OUTSIDE, 7),
};

static const struct ObjEvent MountMortarB1F_ObjectEvents[] = {
    object_event(29, 12, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &MountMortarB1FHyperPotion, EVENT_MOUNT_MORTAR_B1F_HYPER_POTION),
    object_event(4, 16, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &MountMortarB1FCarbos, EVENT_MOUNT_MORTAR_B1F_CARBOS),
    object_event(9, 10, SPRITE_BOULDER, SPRITEMOVEDATA_STRENGTH_BOULDER, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &MountMortarB1FBoulder, -1),
    object_event(16, 4, SPRITE_BLACK_BELT, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, &MountMortarB1FKiyoScript, -1),
    object_event(34, 24, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &MountMortarB1FFullRestore, EVENT_MOUNT_MORTAR_B1F_FULL_RESTORE),
    object_event(32, 3, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &MountMortarB1FMaxEther, EVENT_MOUNT_MORTAR_B1F_MAX_ETHER),
    object_event(21, 26, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &MountMortarB1FPPUp, EVENT_MOUNT_MORTAR_B1F_PP_UP),
};

const struct MapEvents MountMortarB1F_MapEvents = {
    .warp_event_count = lengthof(MountMortarB1F_WarpEvents),
    .warp_events = MountMortarB1F_WarpEvents,

    .coord_event_count = 0, // lengthof(MountMortarB1F_CoordEvents),
    .coord_events = MountMortarB1F_CoordEvents,

    .bg_event_count = lengthof(MountMortarB1F_BGEvents),
    .bg_events = MountMortarB1F_BGEvents,

    .obj_event_count = lengthof(MountMortarB1F_ObjectEvents),
    .obj_events = MountMortarB1F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "MountMortarB1F.h"

bool MountMortarB1FKiyoScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_TYROGUE_FROM_KIYO)
    iftrue(GotTyrogue)
    checkevent(EVENT_BEAT_BLACKBELT_KIYO)
    iftrue(BeatKiyo)
    writetext(MountMortarB1FKiyoIntroText)
    waitbutton
    closetext
    winlosstext(MountMortarB1FKiyoWinText, 0)
    loadtrainer(BLACKBELT_T, KIYO)
    startbattle
    reloadmapafterbattle
    setevent(EVENT_BEAT_BLACKBELT_KIYO)
    opentext
BeatKiyo:
    writetext(MountMortarB1FTyrogueRewardText)
    promptbutton
    waitsfx
    readvar(VAR_PARTYCOUNT)
    ifequal(PARTY_LENGTH, NoRoom)
    writetext(MountMortarB1FReceiveMonText)
    playsound(SFX_CAUGHT_MON)
    waitsfx
    givepoke(TYROGUE, 10, NO_ITEM)
    setevent(EVENT_GOT_TYROGUE_FROM_KIYO)
GotTyrogue:
    writetext(MountMortarB1FKiyoGotTyrogueText)
    waitbutton
    closetext
    s_end
NoRoom:
    writetext(MountMortarB1FKiyoFullPartyText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool MountMortarB1FBoulder(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(StrengthBoulderScript)
    SCRIPT_END
}
const struct ItemBall MountMortarB1FHyperPotion = {HYPER_POTION, 1};
const struct ItemBall MountMortarB1FCarbos = {CARBOS, 1};
const struct ItemBall MountMortarB1FFullRestore = {FULL_RESTORE, 1};
const struct ItemBall MountMortarB1FMaxEther = {MAX_ETHER, 1};
const struct ItemBall MountMortarB1FPPUp = {PP_UP, 1};
const struct HiddenItem MountMortarB1FHiddenMaxRevive = {MAX_REVIVE, EVENT_MOUNT_MORTAR_B1F_HIDDEN_MAX_REVIVE};
const txt_cmd_s MountMortarB1FKiyoIntroText[] = {
    text_start("Hey!"
        t_para "I am the KARATE"
        t_line "KING!"
        t_para "I train alone here"
        t_line "in the dark!"
        t_para "You!"
        t_line "Battle with me!"
        t_para "Hwaaarggh!"
        t_done )
};
const txt_cmd_s MountMortarB1FKiyoWinText[] = {
    text_start("Waaaarggh!"
        t_line "I'm beaten!"
        t_done )
};
const txt_cmd_s MountMortarB1FTyrogueRewardText[] = {
    text_start("I… I'm crushed…"
        t_para "My training is"
        t_line "still not enough…"
        t_para "But a loss is a"
        t_line "loss. I admit it."
        t_para "As proof that you"
        t_line "defeated me, I'll"
        t_para "give you a rare"
        t_line "fighting #MON."
        t_done )
};
const txt_cmd_s MountMortarB1FReceiveMonText[] = {
    text_start("<PLAYER> received"
        t_line "TYROGUE."
        t_done )
};
const txt_cmd_s MountMortarB1FKiyoGotTyrogueText[] = {
    text_start("TYROGUE is a"
        t_line "fighting-type."
        t_para "It evolves into a"
        t_line "tougher #MON."
        t_para "Keep up the hard"
        t_line "work. I'll keep"
        t_cont "training too."
        t_para "Farewell!"
        t_done )
};
const txt_cmd_s MountMortarB1FKiyoFullPartyText[] = {
    text_start("You have no room"
        t_line "in your party!"
        t_done )
    //db(0, 0) // filler
};
