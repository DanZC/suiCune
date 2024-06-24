#include "../constants.h"
#include "../util/scripting.h"
#include "MahoganyTown.h"
//// EVENTS
enum {
    MAHOGANYTOWN_POKEFAN_M = 2,
    MAHOGANYTOWN_GRAMPS,
    MAHOGANYTOWN_FISHER,
    MAHOGANYTOWN_LASS,
};

const Script_fn_t MahoganyTown_SceneScripts[] = {
    MahoganyTown_MapScripts_DummyScene0 , //  SCENE_DEFAULT,
    MahoganyTown_MapScripts_DummyScene1 , //  SCENE_FINISHED,
};

const struct MapCallback MahoganyTown_MapCallbacks[] = {
    map_callback(MAPCALLBACK_NEWMAP, MahoganyTown_MapScripts_FlyPoint),
};

const struct MapScripts MahoganyTown_MapScripts = {
    .scene_script_count = lengthof(MahoganyTown_SceneScripts),
    .scene_scripts = MahoganyTown_SceneScripts,

    .callback_count = lengthof(MahoganyTown_MapCallbacks),
    .callbacks = MahoganyTown_MapCallbacks,
};

static const struct CoordEvent MahoganyTown_CoordEvents[] = {
    coord_event(19, 8, SCENE_DEFAULT, &MahoganyTownTryARageCandyBarScript),
    coord_event(19, 9, SCENE_DEFAULT, &MahoganyTownTryARageCandyBarScript),
};

static const struct BGEvent MahoganyTown_BGEvents[] = {
    bg_event(1, 5, BGEVENT_READ, &MahoganyTownSign),
    bg_event(9, 7, BGEVENT_READ, &MahoganyTownRagecandybarSign),
    bg_event(3, 13, BGEVENT_READ, &MahoganyGymSign),
    bg_event(16, 13, BGEVENT_READ, &MahoganyTownPokecenterSign),
};

static const struct WarpEventData MahoganyTown_WarpEvents[] = {
    warp_event(11, 7, MAHOGANY_MART_1F, 1),
    warp_event(17, 7, MAHOGANY_RED_GYARADOS_SPEECH_HOUSE, 1),
    warp_event(6, 13, MAHOGANY_GYM, 1),
    warp_event(15, 13, MAHOGANY_POKECENTER_1F, 1),
    warp_event(9, 1, ROUTE_43_MAHOGANY_GATE, 3),
};

static const struct ObjEvent MahoganyTown_ObjectEvents[] = {
    object_event(19, 8, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &MahoganyTownPokefanMScript, EVENT_MAHOGANY_TOWN_POKEFAN_M_BLOCKS_EAST),
    object_event(6, 9, SPRITE_GRAMPS, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &MahoganyTownGrampsScript, -1),
    object_event(6, 14, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &MahoganyTownFisherScript, EVENT_MAHOGANY_TOWN_POKEFAN_M_BLOCKS_GYM),
    object_event(12, 8, SPRITE_LASS, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &MahoganyTownLassScript, EVENT_MAHOGANY_MART_OWNERS),
};

const struct MapEvents MahoganyTown_MapEvents = {
    .warp_event_count = lengthof(MahoganyTown_WarpEvents),
    .warp_events = MahoganyTown_WarpEvents,

    .coord_event_count = lengthof(MahoganyTown_CoordEvents),
    .coord_events = MahoganyTown_CoordEvents,

    .bg_event_count = lengthof(MahoganyTown_BGEvents),
    .bg_events = MahoganyTown_BGEvents,

    .obj_event_count = lengthof(MahoganyTown_ObjectEvents),
    .obj_events = MahoganyTown_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "MahoganyTown.h"

#define MAHOGANYTOWN_RAGECANDYBAR_PRICE 300
bool MahoganyTown_MapScripts_DummyScene0(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool MahoganyTown_MapScripts_DummyScene1(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool MahoganyTown_MapScripts_FlyPoint(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_FLYPOINT_MAHOGANY)
    s_endcallback
    SCRIPT_END
}
bool MahoganyTownTryARageCandyBarScript(script_s* s) {
    SCRIPT_BEGIN
    showemote(EMOTE_SHOCK, MAHOGANYTOWN_POKEFAN_M, 15)
    applymovement(MAHOGANYTOWN_POKEFAN_M, MahoganyTownRageCandyBarMerchantBlocksYouMovement)
    follow(PLAYER, MAHOGANYTOWN_POKEFAN_M)
    applymovement(PLAYER, MahoganyTownPlayerStepLeftMovement)
    stopfollow
    turnobject(PLAYER, RIGHT)
    scall(RageCandyBarMerchantScript)
    applymovement(MAHOGANYTOWN_POKEFAN_M, MahoganyTownRageCandyBarMerchantReturnsMovement)
    s_end
    SCRIPT_END
}
bool MahoganyTownPokefanMScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    SCRIPT_FALLTHROUGH(RageCandyBarMerchantScript)
}
bool RageCandyBarMerchantScript(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_CLEARED_ROCKET_HIDEOUT)
    iftrue(ClearedRocketHideout)
    scall_local(SellRageCandyBars);
    s_end
ClearedRocketHideout:
    opentext
    writetext(RageCandyBarMerchantSoldOutText)
    waitbutton
    closetext
    s_end
SellRageCandyBars:
    opentext
    writetext(RageCandyBarMerchantTryOneText)
    special(PlaceMoneyTopRight)
    yesorno
    iffalse(Refused)
    checkmoney(YOUR_MONEY, MAHOGANYTOWN_RAGECANDYBAR_PRICE)
    ifequal(HAVE_LESS, NotEnoughMoney)
    giveitem(RAGECANDYBAR, 1)
    iffalse(NoRoom)
    waitsfx
    playsound(SFX_TRANSACTION)
    takemoney(YOUR_MONEY, MAHOGANYTOWN_RAGECANDYBAR_PRICE)
    special(PlaceMoneyTopRight)
    writetext(RageCandyBarMerchantSavorItText)
    waitbutton
    closetext
    s_end
NotEnoughMoney:
    writetext(RageCandyBarMerchantNotEnoughMoneyText)
    waitbutton
    closetext
    s_end
Refused:
    writetext(RageCandyBarMerchantRefusedText)
    waitbutton
    closetext
    s_end
NoRoom:
    writetext(RageCandyBarMerchantNoRoomText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool MahoganyTownGrampsScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_CLEARED_ROCKET_HIDEOUT)
    iftrue(ClearedRocketHideout)
    writetext(MahoganyTownGrampsText)
    waitbutton
    closetext
    s_end
ClearedRocketHideout:
    writetext(MahoganyTownGrampsText_ClearedRocketHideout)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool MahoganyTownFisherScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(MahoganyTownFisherText)
    SCRIPT_END
}
bool MahoganyTownLassScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(MahoganyTownLassText)
    SCRIPT_END
}
bool MahoganyTownSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(MahoganyTownSignText)
    SCRIPT_END
}
bool MahoganyTownRagecandybarSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(MahoganyTownRagecandybarSignText)
    SCRIPT_END
}
bool MahoganyGymSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(MahoganyGymSignText)
    SCRIPT_END
}
bool MahoganyTownPokecenterSign(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PokecenterSignScript)
    SCRIPT_END
}
const uint8_t MahoganyTownCollideDownFaceLeftMovement[] = {
    step(DOWN),
    big_step(UP),
    turn_head(DOWN),
};
const uint8_t MahoganyTownPlayerStepLeftMovement[] = {
    step(LEFT),
    movement_step_end,
};
const uint8_t MahoganyTownRageCandyBarMerchantBlocksYouMovement[] = {
    step(RIGHT),
    step(DOWN),
    turn_head(LEFT),
    movement_step_end,
};
const uint8_t MahoganyTownRageCandyBarMerchantReturnsMovement[] = {
    step(UP),
    turn_head(DOWN),
    movement_step_end,
};
const txt_cmd_s RageCandyBarMerchantTryOneText[] = {
    text_start("Hiya, kid!"
        t_para "I see you're new"
        t_line "in MAHOGANY TOWN."
        t_para "Since you're new,"
        t_line "you should try a"
        t_para "yummy RAGECANDY-"
        t_line "BAR!"
        t_para "Right now, it can"
        t_line "be yours for just"
        t_cont "¥300! Want one?"
        t_done )
};
const txt_cmd_s RageCandyBarMerchantSavorItText[] = {
    text_start("Good! Savor it!"
        t_done )
};
const txt_cmd_s RageCandyBarMerchantNotEnoughMoneyText[] = {
    text_start("You don't have"
        t_line "enough money."
        t_done )
};
const txt_cmd_s RageCandyBarMerchantRefusedText[] = {
    text_start("Oh, fine then…"
        t_done )
};
const txt_cmd_s RageCandyBarMerchantNoRoomText[] = {
    text_start("You don't have"
        t_line "room for this."
        t_done )
};
const txt_cmd_s RageCandyBarMerchantSoldOutText[] = {
    text_start("RAGECANDYBAR's"
        t_line "sold out."
        t_para "I'm packing up."
        t_line "Don't bother me,"
        t_cont "kiddo."
        t_done )
};
const txt_cmd_s MahoganyTownGrampsText[] = {
    text_start("Are you off to see"
        t_line "the GYARADOS ram-"
        t_cont "page at the LAKE?"
        t_done )
};
const txt_cmd_s MahoganyTownGrampsText_ClearedRocketHideout[] = {
    text_start("MAGIKARP have"
        t_line "returned to LAKE"
        t_cont "OF RAGE."
        t_para "That should be"
        t_line "good news for the"
        t_cont "anglers there."
        t_done )
};
const txt_cmd_s MahoganyTownFisherText[] = {
    text_start("Since you came"
        t_line "this far, take the"
        t_para "time to do some"
        t_line "sightseeing."
        t_para "You should head"
        t_line "north and check"
        t_para "out LAKE OF RAGE"
        t_line "right now."
        t_done )
};
const txt_cmd_s MahoganyTownLassText[] = {
    text_start("Visit Grandma's"
        t_line "shop. She sells"
        t_para "stuff that nobody"
        t_line "else has."
        t_done )
};
const txt_cmd_s MahoganyTownSignText[] = {
    text_start("MAHOGANY TOWN"
        t_para "Welcome to the"
        t_line "Home of the Ninja"
        t_done )
};
const txt_cmd_s MahoganyTownRagecandybarSignText[] = {
    text_start("While visiting"
        t_line "MAHOGANY TOWN, try"
        t_cont "a RAGECANDYBAR!"
        t_done )
};
const txt_cmd_s MahoganyGymSignText[] = {
    text_start("MAHOGANY TOWN"
        t_line "#MON GYM"
        t_cont "LEADER: PRYCE"
        t_para "The Teacher of"
        t_line "Winter's Harshness"
        t_done )
    //db(0, 0) // filler
};
