#include "../constants.h"
#include "../util/scripting.h"
#include "CeladonGameCorner.h"
//// EVENTS
enum {
    CELADONGAMECORNER_CLERK = 2,
    CELADONGAMECORNER_RECEPTIONIST,
    CELADONGAMECORNER_POKEFAN_M,
    CELADONGAMECORNER_TEACHER,
    CELADONGAMECORNER_FISHING_GURU,
    CELADONGAMECORNER_FISHER1,
    CELADONGAMECORNER_FISHER2,
    CELADONGAMECORNER_GYM_GUIDE,
    CELADONGAMECORNER_GRAMPS,
};

const Script_fn_t CeladonGameCorner_SceneScripts[] = {
    0,
};

const struct MapCallback CeladonGameCorner_MapCallbacks[] = {
    0,
};

const struct MapScripts CeladonGameCorner_MapScripts = {
    .scene_script_count = 0, // lengthof(CeladonGameCorner_SceneScripts),
    .scene_scripts = CeladonGameCorner_SceneScripts,

    .callback_count = 0, // lengthof(CeladonGameCorner_MapCallbacks),
    .callbacks = CeladonGameCorner_MapCallbacks,
};

static const struct CoordEvent CeladonGameCorner_CoordEvents[] = {
    0,
};

static const struct BGEvent CeladonGameCorner_BGEvents[] = {
    bg_event(1, 6, BGEVENT_READ, &CeladonGameCornerCardFlipScript),
    bg_event(1, 7, BGEVENT_READ, &CeladonGameCornerCardFlipScript),
    bg_event(1, 8, BGEVENT_READ, &CeladonGameCornerCardFlipScript),
    bg_event(1, 9, BGEVENT_READ, &CeladonGameCornerCardFlipScript),
    bg_event(1, 10, BGEVENT_READ, &CeladonGameCornerCardFlipScript),
    bg_event(1, 11, BGEVENT_LEFT, &CeladonGameCornerCardFlipScript),
    bg_event(6, 6, BGEVENT_READ, &CeladonGameCornerCardFlipScript),
    bg_event(6, 7, BGEVENT_READ, &CeladonGameCornerCardFlipScript),
    bg_event(6, 8, BGEVENT_READ, &CeladonGameCornerCardFlipScript),
    bg_event(6, 9, BGEVENT_READ, &CeladonGameCornerSodaCanScript),
    bg_event(6, 10, BGEVENT_READ, &CeladonGameCornerCardFlipScript),
    bg_event(6, 11, BGEVENT_RIGHT, &CeladonGameCornerCardFlipScript),
    bg_event(7, 6, BGEVENT_READ, &CeladonGameCornerLuckySlotMachineScript),
    bg_event(7, 7, BGEVENT_READ, &CeladonGameCornerLuckySlotMachineScript),
    bg_event(7, 8, BGEVENT_READ, &CeladonGameCornerLuckySlotMachineScript),
    bg_event(7, 9, BGEVENT_READ, &CeladonGameCornerLuckySlotMachineScript),
    bg_event(7, 10, BGEVENT_READ, &CeladonGameCornerSlotMachineScript),
    bg_event(7, 11, BGEVENT_LEFT, &CeladonGameCornerLuckySlotMachineScript),
    bg_event(12, 6, BGEVENT_READ, &CeladonGameCornerLuckySlotMachineScript),
    bg_event(12, 7, BGEVENT_READ, &CeladonGameCornerLuckySlotMachineScript),
    bg_event(12, 8, BGEVENT_READ, &CeladonGameCornerLuckySlotMachineScript),
    bg_event(12, 9, BGEVENT_READ, &CeladonGameCornerLuckySlotMachineScript),
    bg_event(12, 10, BGEVENT_READ, &CeladonGameCornerLuckySlotMachineScript),
    bg_event(12, 11, BGEVENT_RIGHT, &CeladonGameCornerLuckySlotMachineScript),
    bg_event(13, 6, BGEVENT_READ, &CeladonGameCornerLuckySlotMachineScript),
    bg_event(13, 7, BGEVENT_READ, &CeladonGameCornerLuckySlotMachineScript),
    bg_event(13, 8, BGEVENT_READ, &CeladonGameCornerLuckySlotMachineScript),
    bg_event(13, 9, BGEVENT_READ, &CeladonGameCornerLuckySlotMachineScript),
    bg_event(13, 10, BGEVENT_READ, &CeladonGameCornerLuckySlotMachineScript),
    bg_event(13, 11, BGEVENT_LEFT, &CeladonGameCornerLuckySlotMachineScript),
    bg_event(18, 6, BGEVENT_READ, &CeladonGameCornerLuckySlotMachineScript),
    bg_event(18, 7, BGEVENT_READ, &CeladonGameCornerLuckySlotMachineScript),
    bg_event(18, 8, BGEVENT_READ, &CeladonGameCornerLighterScript),
    bg_event(18, 9, BGEVENT_READ, &CeladonGameCornerLuckySlotMachineScript),
    bg_event(18, 10, BGEVENT_READ, &CeladonGameCornerLuckySlotMachineScript),
    bg_event(18, 11, BGEVENT_RIGHT, &CeladonGameCornerLuckySlotMachineScript),
    bg_event(15, 0, BGEVENT_READ, &CeladonGameCornerPoster1Script),
    bg_event(9, 0, BGEVENT_READ, &CeladonGameCornerPoster2Script),
};

static const struct WarpEventData CeladonGameCorner_WarpEvents[] = {
    warp_event(14, 13, CELADON_CITY, 6),
    warp_event(15, 13, CELADON_CITY, 6),
};

static const struct ObjEvent CeladonGameCorner_ObjectEvents[] = {
    object_event(5, 2, SPRITE_CLERK, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &CeladonGameCornerClerkScript, -1),
    object_event(3, 2, SPRITE_RECEPTIONIST, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &CeladonGameCornerReceptionistScript, -1),
    object_event(14, 10, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &CeladonGameCornerPokefanMScript, -1),
    object_event(17, 7, SPRITE_TEACHER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &CeladonGameCornerTeacherScript, -1),
    object_event(11, 7, SPRITE_FISHING_GURU, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &CeladonGameCornerFishingGuruScript, -1),
    object_event(8, 10, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, DAY, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &CeladonGameCornerFisherScript, -1),
    object_event(8, 10, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, NITE, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &CeladonGameCornerFisherScript, -1),
    object_event(11, 3, SPRITE_GYM_GUIDE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &CeladonGymGuideScript, -1),
    object_event(2, 8, SPRITE_GRAMPS, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &CeladonGameCornerGrampsScript, -1),
};

const struct MapEvents CeladonGameCorner_MapEvents = {
    .warp_event_count = lengthof(CeladonGameCorner_WarpEvents),
    .warp_events = CeladonGameCorner_WarpEvents,

    .coord_event_count = 0, // lengthof(CeladonGameCorner_CoordEvents),
    .coord_events = CeladonGameCorner_CoordEvents,

    .bg_event_count = lengthof(CeladonGameCorner_BGEvents),
    .bg_events = CeladonGameCorner_BGEvents,

    .obj_event_count = lengthof(CeladonGameCorner_ObjectEvents),
    .obj_events = CeladonGameCorner_ObjectEvents,
};

//// CODE

bool CeladonGameCornerClerkScript(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(GameCornerCoinVendorScript)
    SCRIPT_END
}
bool CeladonGameCornerReceptionistScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CeladonGameCornerReceptionistText)
    SCRIPT_END
}
bool CeladonGameCornerPokefanMScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(CeladonGameCornerPokefanMText)
    waitbutton
    closetext
    turnobject(CELADONGAMECORNER_POKEFAN_M, LEFT)
    s_end
    SCRIPT_END
}
bool CeladonGameCornerTeacherScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(CeladonGameCornerTeacherText)
    waitbutton
    closetext
    turnobject(CELADONGAMECORNER_TEACHER, RIGHT)
    s_end
    SCRIPT_END
}
bool CeladonGameCornerFishingGuruScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(CeladonGameCornerFishingGuruText)
    waitbutton
    closetext
    turnobject(CELADONGAMECORNER_FISHING_GURU, RIGHT)
    s_end
    SCRIPT_END
}
bool CeladonGameCornerFisherScript(script_s* s) {
static const char coinname[] = "COIN@";
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_COINS_FROM_GAMBLER_AT_CELADON)
    iftrue(GotCoins)
    writetext(CeladonGameCornerFisherText1)
    promptbutton
    checkitem(COIN_CASE)
    iffalse(NoCoinCase)
    checkcoins(MAX_COINS - 1)
    ifequal(HAVE_MORE, FullCoinCase)
    getstring(STRING_BUFFER_4, coinname)
    scall_local(GiveCoins);
    givecoins(18)
    setevent(EVENT_GOT_COINS_FROM_GAMBLER_AT_CELADON)
GotCoins:
    writetext(CeladonGameCornerFisherText2)
    waitbutton
    closetext
    turnobject(LAST_TALKED, LEFT)
    s_end
GiveCoins:
    jumpstd(ReceiveItemScript)
    s_end
NoCoinCase:
    writetext(CeladonGameCornerFisherNoCoinCaseText)
    waitbutton
    closetext
    turnobject(LAST_TALKED, LEFT)
    s_end
FullCoinCase:
    writetext(CeladonGameCornerFisherFullCoinCaseText)
    waitbutton
    closetext
    turnobject(LAST_TALKED, LEFT)
    s_end
    SCRIPT_END
}
bool CeladonGymGuideScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CeladonGymGuideText)
    SCRIPT_END
}
bool CeladonGameCornerGrampsScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(CeladonGameCornerGrampsText)
    waitbutton
    closetext
    turnobject(CELADONGAMECORNER_GRAMPS, LEFT)
    s_end
    SCRIPT_END
}
bool CeladonGameCornerPoster1Script(script_s* s) {
    SCRIPT_BEGIN
    jumptext(CeladonGameCornerPoster1Text)
    SCRIPT_END
}
bool CeladonGameCornerPoster2Script(script_s* s) {
    SCRIPT_BEGIN
    jumptext(CeladonGameCornerPoster2Text)
    SCRIPT_END
}
bool CeladonGameCornerLuckySlotMachineScript(script_s* s) {
    SCRIPT_BEGIN
    srandom(6)
    ifequal_jump(0, CeladonGameCornerSlotMachineScript)
    refreshscreen
    setval(FALSE)
    special(SlotMachine)
    closetext
    s_end
    SCRIPT_END
}
bool CeladonGameCornerSlotMachineScript(script_s* s) {
    SCRIPT_BEGIN
    refreshscreen
    setval(TRUE)
    special(SlotMachine)
    closetext
    s_end
    SCRIPT_END
}
bool CeladonGameCornerCardFlipScript(script_s* s) {
    SCRIPT_BEGIN
    refreshscreen
    special(CardFlip)
    closetext
    s_end
    SCRIPT_END
}
bool CeladonGameCornerLighterScript(script_s* s) {
    SCRIPT_BEGIN
    jumptext(CeladonGameCornerLighterText)
    SCRIPT_END
}
bool CeladonGameCornerSodaCanScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(CeladonGameCornerSodaCanText)
    waitbutton
    special(CardFlip)
    closetext
    s_end
    SCRIPT_END
}
const uint8_t CeladonGameCornerUnusedMovementData[] = {
    step(RIGHT),
    turn_head(LEFT),
    movement_step_end,
};
const txt_cmd_s CeladonGameCornerReceptionistText[] = {
    text_start("Welcome!"
        t_para "You may exchange"
        t_line "your coins for"
        t_para "fabulous prizes"
        t_line "next door."
        t_done )
};
const txt_cmd_s CeladonGameCornerPokefanMText[] = {
    text_start("The slot machines"
        t_line "are all state of"
        t_cont "the art."
        t_done )
};
const txt_cmd_s CeladonGameCornerTeacherText[] = {
#if _CRYSTAL_AU
    text_start("The weather"
        t_line "outside is very"
        t_cont "nice."
        t_done )
#else
    text_start("It's this machine"
        t_line "I want."
        t_para "It cleaned me out"
        t_line "yesterday, so it"
        t_para "should pay out"
        t_line "today."
        t_done )
#endif
};
const txt_cmd_s CeladonGameCornerFishingGuruText[] = {
#if _CRYSTAL_AU
    text_start("This machine looks"
        t_line "the same as the"
        t_cont "others."
        t_done )
#else
    text_start("I think this slot"
        t_line "machine will pay"
        t_cont "out…"
        t_para "The odds vary"
        t_line "among machines."
        t_done )
#endif
};
const txt_cmd_s CeladonGameCornerFisherText1[] = {
#if _CRYSTAL_AU
    text_start("Whoa!"
        t_para "What? You want to"
        t_line "play this machine?"
        t_para "Here, take my"
        t_line "coins."
        t_done )
#else
    text_start("Gahahaha!"
        t_para "The coins just"
        t_line "keep popping out!"
        t_para "Hm? What, kid? You"
        t_line "want to play?"
        t_para "I'll share my luck"
        t_line "with you!"
        t_done )
#endif
};
const txt_cmd_s CeladonGameCornerFisherText2[] = {
    text_start("Gahahaha!"
        t_para "It makes me feel"
        t_line "good to do nice"
        t_para "things for other"
        t_line "people!"
        t_done )
};
const txt_cmd_s CeladonGameCornerFisherNoCoinCaseText[] = {
    text_start("Hey, you don't"
        t_line "have a COIN CASE."
        t_para "How am I supposed"
        t_line "to give you any"
        t_cont "coins, kid?"
        t_done )
};
const txt_cmd_s CeladonGameCornerFisherFullCoinCaseText[] = {
#if _CRYSTAL_AU
    text_start("Your COIN CASE is"
        t_line "full."
        t_done )
#else
    text_start("Hey, your COIN"
        t_line "CASE is full, kid."
        t_para "You must be riding"
        t_line "a winning streak"
        t_cont "too."
        t_done )
#endif
};
const txt_cmd_s CeladonGymGuideText[] = {
#if _CRYSTAL_AU
    text_start("Hey! CHAMP in"
        t_line "making!"
        t_para "Are you playing"
        t_line "too?"
        t_para "I'm trying to get"
        t_line "enough coins for a"
        t_cont "prize #MON."
        t_para "But I don't have"
        t_line "enough coins yet…"
        t_done )
#else
    text_start("Hey! CHAMP in"
        t_line "making!"
        t_para "Are you playing"
        t_line "the slots too?"
        t_para "I'm trying to get"
        t_line "enough coins for a"
        t_cont "prize #MON."
        t_para "But I don't have"
        t_line "enough coins yet…"
        t_done )
#endif
};
const txt_cmd_s CeladonGameCornerGrampsText[] = {
#if _CRYSTAL_AU
    text_start("Is there any"
        t_line "difference between"
        t_cont "these lines?"
        t_done )
#else
    text_start("Hmmm… The odds are"
        t_line "surely better for"
        t_para "PIKACHU's line,"
        t_line "but… What to do?"
        t_done )
#endif
};
const txt_cmd_s CeladonGameCornerPoster1Text[] = {
    text_start("Hey!"
        t_para "Underneath this"
        t_line "poster…"
        t_para "There's nothing!"
        t_done )
};
const txt_cmd_s CeladonGameCornerPoster2Text[] = {
    text_start("Hey!"
        t_para "Underneath this"
        t_line "poster…"
        t_para "There's nothing!"
        t_done )
};
const txt_cmd_s CeladonGameCornerLighterText[] = {
    text_start("There's a lighter"
        t_line "here."
        t_done )
};
const txt_cmd_s CeladonGameCornerSodaCanText[] = {
    text_start("A can of soda…"
        t_para "Someone must be"
        t_line "coming back…"
        t_para "Huh? It's empty!"
        t_done )
    //db(0, 0) // filler
};
