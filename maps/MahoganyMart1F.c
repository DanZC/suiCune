#include "../constants.h"
#include "../util/scripting.h"
#include "MahoganyMart1F.h"
//// EVENTS
enum {
    MAHOGANYMART1F_PHARMACIST = 2,
    MAHOGANYMART1F_BLACK_BELT,
    MAHOGANYMART1F_LANCE,
    MAHOGANYMART1F_DRAGONITE,
    MAHOGANYMART1F_GRANNY,
};

const Script_fn_t MahoganyMart1F_SceneScripts[] = {
    MahoganyMart1F_MapScripts_DummyScene0 , //  SCENE_MAHOGANYMART1F_NOTHING,
    MahoganyMart1F_MapScripts_LanceUncoversStaircase , //  SCENE_MAHOGANYMART1F_LANCE_UNCOVERS_STAIRS,
};

const struct MapCallback MahoganyMart1F_MapCallbacks[] = {
    map_callback(MAPCALLBACK_TILES, MahoganyMart1F_MapScripts_MahoganyMart1FStaircase),
};

const struct MapScripts MahoganyMart1F_MapScripts = {
    .scene_script_count = lengthof(MahoganyMart1F_SceneScripts),
    .scene_scripts = MahoganyMart1F_SceneScripts,

    .callback_count = lengthof(MahoganyMart1F_MapCallbacks),
    .callbacks = MahoganyMart1F_MapCallbacks,
};

static const struct CoordEvent MahoganyMart1F_CoordEvents[] = {
    0,
};

static const struct BGEvent MahoganyMart1F_BGEvents[] = {
    0,
};

static const struct WarpEventData MahoganyMart1F_WarpEvents[] = {
    warp_event(3, 7, MAHOGANY_TOWN, 1),
    warp_event(4, 7, MAHOGANY_TOWN, 1),
    warp_event(7, 3, TEAM_ROCKET_BASE_B1F, 1),
};

static const struct ObjEvent MahoganyMart1F_ObjectEvents[] = {
    object_event(4, 3, SPRITE_PHARMACIST, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &MahoganyMart1FPharmacistScript, EVENT_TEAM_ROCKET_BASE_POPULATION),
    object_event(1, 6, SPRITE_BLACK_BELT, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &MahoganyMart1FBlackBeltScript, EVENT_TEAM_ROCKET_BASE_POPULATION),
    object_event(4, 6, SPRITE_LANCE, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, EVENT_MAHOGANY_MART_LANCE_AND_DRAGONITE),
    object_event(3, 6, SPRITE_DRAGON, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, EVENT_MAHOGANY_MART_LANCE_AND_DRAGONITE),
    object_event(1, 3, SPRITE_GRANNY, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &MahoganyMart1FGrannyScript, EVENT_MAHOGANY_MART_OWNERS),
};

const struct MapEvents MahoganyMart1F_MapEvents = {
    .warp_event_count = lengthof(MahoganyMart1F_WarpEvents),
    .warp_events = MahoganyMart1F_WarpEvents,

    .coord_event_count = 0, // lengthof(MahoganyMart1F_CoordEvents),
    .coord_events = MahoganyMart1F_CoordEvents,

    .bg_event_count = 0, // lengthof(MahoganyMart1F_BGEvents),
    .bg_events = MahoganyMart1F_BGEvents,

    .obj_event_count = lengthof(MahoganyMart1F_ObjectEvents),
    .obj_events = MahoganyMart1F_ObjectEvents,
};

//// CODE

bool MahoganyMart1F_MapScripts_DummyScene0(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool MahoganyMart1F_MapScripts_LanceUncoversStaircase(script_s* s) {
    SCRIPT_BEGIN
    sdefer(MahoganyMart1FLanceUncoversStaircaseScript)
    s_end
    SCRIPT_END
}
bool MahoganyMart1F_MapScripts_MahoganyMart1FStaircase(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_UNCOVERED_STAIRCASE_IN_MAHOGANY_MART)
    iftrue(ShowStairs)
    s_endcallback
ShowStairs:
    changeblock(6, 2, 0x1e) // stairs
    s_endcallback
    SCRIPT_END
}
bool MahoganyMart1FPharmacistScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_DECIDED_TO_HELP_LANCE)
    iftrue(LanceEntered)
    pokemart(MARTTYPE_STANDARD, MART_MAHOGANY_1)
    closetext
    s_end
LanceEntered:
    writetext(MahoganyMart1FPharmacistText_LanceEntered)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool MahoganyMart1FBlackBeltScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_DECIDED_TO_HELP_LANCE)
    iftrue(LanceEntered)
    writetext(MahoganyMart1FBlackBeltText)
    waitbutton
    closetext
    s_end
LanceEntered:
    writetext(MahoganyMart1FBlackBeltText_LanceEntered)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool MahoganyMart1FLanceUncoversStaircaseScript(script_s* s) {
    SCRIPT_BEGIN
    pause(15)
    opentext
    writetext(MahoganyMart1FLanceDragoniteHyperBeamText)
    pause(15)
    closetext
    playsound(SFX_TACKLE)
    applymovement(MAHOGANYMART1F_DRAGONITE, MahoganyMart1FDragoniteTackleMovement)
    applymovement(MAHOGANYMART1F_BLACK_BELT, MahoganyMart1FBlackBeltKnockedBackMovement)
    pause(15)
    disappear(MAHOGANYMART1F_DRAGONITE)
    pause(15)
    applymovement(MAHOGANYMART1F_LANCE, MahoganyMart1FLanceApproachPlayerMovement)
    opentext
    writetext(MahoganyMart1FLanceRadioText)
    waitbutton
    closetext
    follow(MAHOGANYMART1F_LANCE, PLAYER)
    applymovement(MAHOGANYMART1F_LANCE, MahoganyMart1FLanceApproachPharmacistMovement)
    applymovement(MAHOGANYMART1F_PHARMACIST, MahoganyMart1FPharmacistShovedAsideMovement)
    applymovement(MAHOGANYMART1F_LANCE, MahoganyMart1FLanceApproachHiddenStairsMovement)
    stopfollow
    opentext
    writetext(MahoganyMart1FLanceStairsText)
    waitbutton
    showemote(EMOTE_SHOCK, MAHOGANYMART1F_PHARMACIST, 10)
    playsound(SFX_FAINT)
    changeblock(6, 2, 0x1e) // stairs
    reloadmappart
    closetext
    setevent(EVENT_UNCOVERED_STAIRCASE_IN_MAHOGANY_MART)
    turnobject(MAHOGANYMART1F_LANCE, LEFT)
    opentext
    writetext(MahoganyMart1FLanceSplitUpText)
    waitbutton
    closetext
    applymovement(MAHOGANYMART1F_LANCE, MahoganyMart1FLanceGoDownStairsMovement)
    playsound(SFX_EXIT_BUILDING)
    disappear(MAHOGANYMART1F_LANCE)
    setscene(SCENE_MAHOGANYMART1F_NOTHING)
    waitsfx
    s_end
    SCRIPT_END
}
bool MahoganyMart1FGrannyScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    pokemart(MARTTYPE_STANDARD, MART_MAHOGANY_2)
    closetext
    s_end
    SCRIPT_END
}
const uint8_t MahoganyMart1FDragoniteTackleMovement[] = {
    movement_fix_facing,
    big_step(LEFT),
    big_step(RIGHT),
    movement_remove_fixed_facing,
    movement_step_end,
};
const uint8_t MahoganyMart1FBlackBeltKnockedBackMovement[] = {
    movement_fix_facing,
    big_step(LEFT),
    movement_remove_fixed_facing,
    turn_head(DOWN),
    turn_head(LEFT),
    turn_head(UP),
    turn_head(RIGHT),
    movement_step_end,
};
const uint8_t MahoganyMart1FPharmacistShovedAsideMovement[] = {
    movement_fix_facing,
    big_step(LEFT),
    movement_remove_fixed_facing,
    movement_step_end,
};
const uint8_t MahoganyMart1FLanceApproachPlayerMovement[] = {
    slow_step(LEFT),
    turn_head(DOWN),
    movement_step_end,
};
const uint8_t MahoganyMart1FLanceApproachPharmacistMovement[] = {
    slow_step(RIGHT),
    slow_step(UP),
    slow_step(UP),
    movement_step_end,
};
const uint8_t MahoganyMart1FLanceApproachHiddenStairsMovement[] = {
    slow_step(UP),
    slow_step(RIGHT),
    slow_step(RIGHT),
    movement_step_end,
};
const uint8_t MahoganyMart1FLanceGoDownStairsMovement[] = {
    slow_step(RIGHT),
    movement_step_end,
};
const txt_cmd_s MahoganyMart1FRageCandyBarText[] = {
    text_start("Hello, kiddo!"
        t_para "How would you like"
        t_line "some RAGECANDYBAR?"
        t_para "It's the thing to"
        t_line "eat in MAHOGANY!"
        t_done )
};
const txt_cmd_s MahoganyMart1FPharmacistText_LanceEntered[] = {
    text_start("Arrgh… You found"
        t_line "the secret stair-"
        t_cont "way…"
        t_done )
};
const txt_cmd_s MahoganyMart1FBlackBeltText[] = {
    text_start("Heheh! The experi-"
        t_line "ment worked like a"
        t_cont "charm."
        t_para "MAGIKARP are just"
        t_line "worthless, but"
        t_para "GYARADOS are big"
        t_line "moneymakers."
        t_done )
};
const txt_cmd_s MahoganyMart1FBlackBeltText_LanceEntered[] = {
    text_start("Urrgh…"
        t_para "That guy's dragon"
        t_line "#MON are tough…"
        t_done )
};
const txt_cmd_s MahoganyMart1FLanceDragoniteHyperBeamText[] = {
    text_start("LANCE: DRAGONITE,"
        t_line "HYPER BEAM."
        t_done )
};
const txt_cmd_s MahoganyMart1FLanceRadioText[] = {
    text_start("What took you,"
        t_line "<PLAY_G>?"
        t_para "Just as I thought,"
        t_line "that strange radio"
        t_para "signal is coming"
        t_line "from here."
        t_done )
};
const txt_cmd_s MahoganyMart1FLanceStairsText[] = {
    text_start("The stairs are"
        t_line "right here."
        t_done )
};
const txt_cmd_s MahoganyMart1FLanceSplitUpText[] = {
    text_start("LANCE: <PLAY_G>, we"
        t_line "should split up to"
        t_para "check this place."
        t_line "I'll go first."
        t_done )
    //db(0, 0) // filler
};
