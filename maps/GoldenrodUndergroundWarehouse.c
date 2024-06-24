#include "../constants.h"
#include "../util/scripting.h"
#include "GoldenrodUndergroundWarehouse.h"
//// EVENTS
enum {
    GOLDENRODUNDERGROUNDWAREHOUSE_ROCKET1 = 2,
    GOLDENRODUNDERGROUNDWAREHOUSE_ROCKET2,
    GOLDENRODUNDERGROUNDWAREHOUSE_ROCKET3,
    GOLDENRODUNDERGROUNDWAREHOUSE_GENTLEMAN,
    GOLDENRODUNDERGROUNDWAREHOUSE_POKE_BALL1,
    GOLDENRODUNDERGROUNDWAREHOUSE_POKE_BALL2,
    GOLDENRODUNDERGROUNDWAREHOUSE_POKE_BALL3,
};

const Script_fn_t GoldenrodUndergroundWarehouse_SceneScripts[] = {
    0,
};

const struct MapCallback GoldenrodUndergroundWarehouse_MapCallbacks[] = {
    map_callback(MAPCALLBACK_NEWMAP, GoldenrodUndergroundWarehouse_MapScripts_ResetSwitches),
};

const struct MapScripts GoldenrodUndergroundWarehouse_MapScripts = {
    .scene_script_count = 0, // lengthof(GoldenrodUndergroundWarehouse_SceneScripts),
    .scene_scripts = GoldenrodUndergroundWarehouse_SceneScripts,

    .callback_count = lengthof(GoldenrodUndergroundWarehouse_MapCallbacks),
    .callbacks = GoldenrodUndergroundWarehouse_MapCallbacks,
};

static const struct CoordEvent GoldenrodUndergroundWarehouse_CoordEvents[] = {
    0,
};

static const struct BGEvent GoldenrodUndergroundWarehouse_BGEvents[] = {
    0,
};

static const struct WarpEventData GoldenrodUndergroundWarehouse_WarpEvents[] = {
    warp_event(2, 12, GOLDENROD_UNDERGROUND_SWITCH_ROOM_ENTRANCES, 2),
    warp_event(3, 12, GOLDENROD_UNDERGROUND_SWITCH_ROOM_ENTRANCES, 3),
    warp_event(17, 2, GOLDENROD_DEPT_STORE_B1F, 1),
};

static const struct ObjEvent GoldenrodUndergroundWarehouse_ObjectEvents[] = {
    object_event(9, 8, SPRITE_ROCKET, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, 0, OBJECTTYPE_TRAINER, 3, &TrainerGruntM24, EVENT_RADIO_TOWER_ROCKET_TAKEOVER),
    object_event(8, 15, SPRITE_ROCKET, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, 0, OBJECTTYPE_TRAINER, 3, &TrainerGruntM14, EVENT_RADIO_TOWER_ROCKET_TAKEOVER),
    object_event(14, 3, SPRITE_ROCKET, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_TRAINER, 4, &TrainerGruntM15, EVENT_RADIO_TOWER_ROCKET_TAKEOVER),
    object_event(12, 8, SPRITE_GENTLEMAN, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &GoldenrodUndergroundWarehouseDirectorScript, EVENT_RADIO_TOWER_ROCKET_TAKEOVER),
    object_event(18, 15, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &GoldenrodUndergroundWarehouseMaxEther, EVENT_GOLDENROD_UNDERGROUND_WAREHOUSE_MAX_ETHER),
    object_event(13, 9, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &GoldenrodUndergroundWarehouseTMSleepTalk, EVENT_GOLDENROD_UNDERGROUND_WAREHOUSE_TM_SLEEP_TALK),
    object_event(2, 1, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &GoldenrodUndergroundWarehouseUltraBall, EVENT_GOLDENROD_UNDERGROUND_WAREHOUSE_ULTRA_BALL),
};

const struct MapEvents GoldenrodUndergroundWarehouse_MapEvents = {
    .warp_event_count = lengthof(GoldenrodUndergroundWarehouse_WarpEvents),
    .warp_events = GoldenrodUndergroundWarehouse_WarpEvents,

    .coord_event_count = 0, // lengthof(GoldenrodUndergroundWarehouse_CoordEvents),
    .coord_events = GoldenrodUndergroundWarehouse_CoordEvents,

    .bg_event_count = 0, // lengthof(GoldenrodUndergroundWarehouse_BGEvents),
    .bg_events = GoldenrodUndergroundWarehouse_BGEvents,

    .obj_event_count = lengthof(GoldenrodUndergroundWarehouse_ObjectEvents),
    .obj_events = GoldenrodUndergroundWarehouse_ObjectEvents,
};

//// CODE

bool GoldenrodUndergroundWarehouse_MapScripts_ResetSwitches(script_s* s) {
    SCRIPT_BEGIN
    clearevent(EVENT_SWITCH_1)
    clearevent(EVENT_SWITCH_2)
    clearevent(EVENT_SWITCH_3)
    clearevent(EVENT_EMERGENCY_SWITCH)
    clearevent(EVENT_SWITCH_4)
    clearevent(EVENT_SWITCH_5)
    clearevent(EVENT_SWITCH_6)
    clearevent(EVENT_SWITCH_7)
    clearevent(EVENT_SWITCH_8)
    clearevent(EVENT_SWITCH_9)
    clearevent(EVENT_SWITCH_10)
    clearevent(EVENT_SWITCH_11)
    clearevent(EVENT_SWITCH_12)
    clearevent(EVENT_SWITCH_13)
    clearevent(EVENT_SWITCH_14)
    setval(0)
    writemem(wram_ptr(wUndergroundSwitchPositions))
    s_endcallback
    SCRIPT_END
}
const struct TrainerObj TrainerGruntM24 = {GRUNTM, GRUNTM_24, EVENT_BEAT_ROCKET_GRUNTM_24, GruntM24SeenText, GruntM24BeatenText, 0, TrainerGruntM24_Script};
bool TrainerGruntM24_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(GruntM24AfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerGruntM14 = {GRUNTM, GRUNTM_14, EVENT_BEAT_ROCKET_GRUNTM_14, GruntM14SeenText, GruntM14BeatenText, 0, TrainerGruntM14_Script};
bool TrainerGruntM14_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(GruntM14AfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerGruntM15 = {GRUNTM, GRUNTM_15, EVENT_BEAT_ROCKET_GRUNTM_15, GruntM15SeenText, GruntM15BeatenText, 0, TrainerGruntM15_Script};
bool TrainerGruntM15_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(GruntM15AfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool GoldenrodUndergroundWarehouseDirectorScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_RECEIVED_CARD_KEY)
    iftrue(GotCardKey)
    writetext(DirectorIntroText)
    promptbutton
    verbosegiveitem(CARD_KEY, 1)
    setevent(EVENT_RECEIVED_CARD_KEY)
    setevent(EVENT_GOLDENROD_DEPT_STORE_B1F_LAYOUT_1)
    clearevent(EVENT_GOLDENROD_DEPT_STORE_B1F_LAYOUT_2)
    clearevent(EVENT_GOLDENROD_DEPT_STORE_B1F_LAYOUT_3)
    writetext(DirectorCardKeyText)
    promptbutton
GotCardKey:
    writetext(DirectorAfterText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct ItemBall GoldenrodUndergroundWarehouseMaxEther = {MAX_ETHER, 1};
const struct ItemBall GoldenrodUndergroundWarehouseTMSleepTalk = {TM_SLEEP_TALK, 1};
const struct ItemBall GoldenrodUndergroundWarehouseUltraBall = {ULTRA_BALL, 1};
const txt_cmd_s GruntM24SeenText[] = {
    text_start("How did you get"
        t_line "this far?"
        t_para "I guess it can't"
        t_line "be helped. I'll"
        t_cont "dispose of you."
        t_done )
};
const txt_cmd_s GruntM24BeatenText[] = {
    text_start("I got disposed of…"
        t_done )
};
const txt_cmd_s GruntM24AfterBattleText[] = {
    text_start("TEAM ROCKET will"
        t_line "keep going, wait-"
        t_cont "ing for the return"
        t_cont "of GIOVANNI."
        t_para "We'll do whatever"
        t_line "it takes."
        t_done )
};
const txt_cmd_s GruntM14SeenText[] = {
    text_start("You're not going"
        t_line "any farther!"
        t_para "I don't show mercy"
        t_line "to my enemies, not"
        t_cont "even brats!"
        t_done )
};
const txt_cmd_s GruntM14BeatenText[] = {
    text_start("Blast it!"
        t_done )
};
const txt_cmd_s GruntM14AfterBattleText[] = {
    text_start("I lost…"
        t_para "Please forgive me,"
        t_line "GIOVANNI!"
        t_done )
};
const txt_cmd_s GruntM15SeenText[] = {
    text_start("Hyuck-hyuck-hyuck!"
        t_line "I remember you!"
        t_para "You got me good"
        t_line "at our hideout!"
        t_done )
};
const txt_cmd_s GruntM15BeatenText[] = {
    text_start("Hyuck-hyuck-hyuck!"
        t_line "So, that's how?"
        t_done )
};
const txt_cmd_s GruntM15AfterBattleText[] = {
    text_start("Hyuck-hyuck-hyuck!"
        t_line "That was a blast!"
        t_cont "I'll remember you!"
        t_done )
};
const txt_cmd_s DirectorIntroText[] = {
    text_start("DIRECTOR: Who?"
        t_line "What? You came to"
        t_cont "rescue me?"
        t_para "Thank you!"
        t_para "The RADIO TOWER!"
        t_para "What's happening"
        t_line "there?"
        t_para "Taken over by TEAM"
        t_line "ROCKET?"
        t_para "Here. Take this"
        t_line "CARD KEY."
        t_done )
};
const txt_cmd_s DirectorCardKeyText[] = {
    text_start("DIRECTOR: Use that"
        t_line "to open the shut-"
        t_cont "ters on 3F."
        t_done )
};
const txt_cmd_s DirectorAfterText[] = {
    text_start("I'm begging you to"
        t_line "help."
        t_para "There's no telling"
        t_line "what they'll do if"
        t_para "they control the"
        t_line "transmitter."
        t_para "They may even be"
        t_line "able to control"
        t_para "#MON using a"
        t_line "special signal!"
        t_para "You're the only"
        t_line "one I can call on."
        t_para "Please save the"
        t_line "RADIO TOWER…"
        t_para "And all the #-"
        t_line "MON nationwide!"
        t_done )
    //db(0, 0) // filler
};
