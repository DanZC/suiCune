#include "../constants.h"
#include "../util/scripting.h"
#include "RadioTower1F.h"
//// EVENTS
enum {
    RADIOTOWER1F_RECEPTIONIST = 2,
    RADIOTOWER1F_LASS,
    RADIOTOWER1F_YOUNGSTER,
    RADIOTOWER1F_ROCKET,
    RADIOTOWER1F_LUCKYNUMBERMAN,
    RADIOTOWER1F_CARD_WOMAN,
};

const Script_fn_t RadioTower1F_SceneScripts[] = {
    0,
};

const struct MapCallback RadioTower1F_MapCallbacks[] = {
    0,
};

const struct MapScripts RadioTower1F_MapScripts = {
    .scene_script_count = 0, // lengthof(RadioTower1F_SceneScripts),
    .scene_scripts = RadioTower1F_SceneScripts,

    .callback_count = 0, // lengthof(RadioTower1F_MapCallbacks),
    .callbacks = RadioTower1F_MapCallbacks,
};

static const struct CoordEvent RadioTower1F_CoordEvents[] = {
    0,
};

static const struct BGEvent RadioTower1F_BGEvents[] = {
    bg_event(3, 0, BGEVENT_READ, &RadioTower1FDirectory),
    bg_event(13, 0, BGEVENT_READ, &RadioTower1FLuckyChannelSign),
};

static const struct WarpEventData RadioTower1F_WarpEvents[] = {
    warp_event(2, 7, GOLDENROD_CITY, 11),
    warp_event(3, 7, GOLDENROD_CITY, 11),
    warp_event(15, 0, RADIO_TOWER_2F, 2),
};

static const struct ObjEvent RadioTower1F_ObjectEvents[] = {
    object_event(5, 6, SPRITE_RECEPTIONIST, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &RadioTower1FReceptionistScript, -1),
    object_event(16, 4, SPRITE_LASS, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &RadioTower1FLassScript, EVENT_GOLDENROD_CITY_CIVILIANS),
    object_event(15, 4, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &RadioTower1FYoungsterScript, EVENT_GOLDENROD_CITY_CIVILIANS),
    object_event(14, 1, SPRITE_ROCKET, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_TRAINER, 3, &TrainerGruntM3, EVENT_RADIO_TOWER_ROCKET_TAKEOVER),
    object_event(8, 6, SPRITE_GENTLEMAN, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &RadioTower1FLuckyNumberManScript, EVENT_GOLDENROD_CITY_CIVILIANS),
    object_event(12, 6, SPRITE_COOLTRAINER_F, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &RadioTower1FRadioCardWomanScript, EVENT_GOLDENROD_CITY_CIVILIANS),
};

const struct MapEvents RadioTower1F_MapEvents = {
    .warp_event_count = lengthof(RadioTower1F_WarpEvents),
    .warp_events = RadioTower1F_WarpEvents,

    .coord_event_count = 0, // lengthof(RadioTower1F_CoordEvents),
    .coord_events = RadioTower1F_CoordEvents,

    .bg_event_count = lengthof(RadioTower1F_BGEvents),
    .bg_events = RadioTower1F_BGEvents,

    .obj_event_count = lengthof(RadioTower1F_ObjectEvents),
    .obj_events = RadioTower1F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "RadioTower1F.h"

bool RadioTower1FReceptionistScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkflag(ENGINE_ROCKETS_IN_RADIO_TOWER)
    iftrue(Rockets)
    writetext(RadioTower1FReceptionistWelcomeText)
    waitbutton
    closetext
    s_end
Rockets:
    writetext(RadioTower1FReceptionistNoToursText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool RadioTower1FLuckyNumberManScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(RadioTower1FLuckyNumberManAskToPlayText)
    promptbutton
    special(CheckLuckyNumberShowFlag)
    iffalse(skip)
    special(ResetLuckyNumberShowFlag)
skip:
    special(PrintTodaysLuckyNumber)
    checkflag(ENGINE_LUCKY_NUMBER_SHOW)
    iftrue(GameOver)
    writetext(RadioTower1FLuckyNumberManThisWeeksIdIsText)
    promptbutton
    closetext
    applymovement(RADIOTOWER1F_LUCKYNUMBERMAN, RadioTower1FLuckyNumberManGoToPCMovement)
    opentext
    writetext(RadioTower1FLuckyNumberManCheckIfMatchText)
    promptbutton
    waitsfx
    writetext(RadioTower1FLuckyNumberManDotDotDotText)
    playsound(SFX_DEX_FANFARE_20_49)
    waitsfx
    promptbutton
    special(CheckForLuckyNumberWinners)
    closetext
    applymovement(RADIOTOWER1F_LUCKYNUMBERMAN, RadioTower1FLuckyNumberManReturnToPlayerMovement)
    opentext
    ifequal(1, FirstPlace)
    ifequal(2, SecondPlace)
    ifequal(3, ThirdPlace)
    goto NoPrize;
GameOver:
    writetext(RadioTower1FLuckyNumberManComeAgainText)
    waitbutton
    closetext
    s_end
FirstPlace:
    writetext(RadioTower1FLuckyNumberManPerfectMatchText)
    playsound(SFX_1ST_PLACE)
    waitsfx
    promptbutton
    giveitem(MASTER_BALL, 1)
    iffalse(BagFull)
    itemnotify
    setflag(ENGINE_LUCKY_NUMBER_SHOW)
    goto GameOver;
SecondPlace:
    writetext(RadioTower1FLuckyNumberManOkayMatchText)
    playsound(SFX_2ND_PLACE)
    waitsfx
    promptbutton
    giveitem(EXP_SHARE, 1)
    iffalse(BagFull)
    itemnotify
    setflag(ENGINE_LUCKY_NUMBER_SHOW)
    goto GameOver;
ThirdPlace:
    writetext(RadioTower1FLuckyNumberManWeakMatchText)
    playsound(SFX_3RD_PLACE)
    waitsfx
    promptbutton
    giveitem(PP_UP, 1)
    iffalse(BagFull)
    itemnotify
    setflag(ENGINE_LUCKY_NUMBER_SHOW)
    goto GameOver;
NoPrize:
    writetext(RadioTower1FLuckyNumberManNoneOfYourIDNumbersMatchText)
    waitbutton
    closetext
    s_end
BagFull:
    writetext(RadioTower1FLuckyNumberManNoRoomForYourPrizeText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool RadioTower1FRadioCardWomanScript(script_s* s) {
    static const char RadioCardText[] = "RADIO CARD@";
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkflag(ENGINE_RADIO_CARD)
    iftrue(GotCard)
    writetext(RadioTower1FRadioCardWomanOfferQuizText)
    yesorno
    iffalse(NoQuiz)
    writetext(RadioTower1FRadioCardWomanQuestion1Text)
    yesorno
    iffalse(WrongAnswer)
    playsound(SFX_ELEVATOR_END)
    waitsfx
    writetext(RadioTower1FRadioCardWomanQuestion2Text)
    yesorno
    iffalse(WrongAnswer)
    playsound(SFX_ELEVATOR_END)
    waitsfx
    writetext(RadioTower1FRadioCardWomanQuestion3Text)
    yesorno
    iftrue(WrongAnswer)
    playsound(SFX_ELEVATOR_END)
    waitsfx
    writetext(RadioTower1FRadioCardWomanQuestion4Text)
    yesorno
    iffalse(WrongAnswer)
    playsound(SFX_ELEVATOR_END)
    waitsfx
    writetext(RadioTower1FRadioCardWomanQuestion5Text)
    yesorno
    iftrue(WrongAnswer)
    playsound(SFX_ELEVATOR_END)
    waitsfx
    writetext(RadioTower1FRadioCardWomanYouWinText)
    promptbutton
    getstring(STRING_BUFFER_4, RadioCardText)
    scall_local(ReceiveItem);
    writetext(RadioTower1FPokegearIsARadioText)
    promptbutton
    setflag(ENGINE_RADIO_CARD)
GotCard:
    writetext(RadioTower1FRadioCardWomanTuneInText)
    waitbutton
    closetext
    s_end
ReceiveItem:
    jumpstd(ReceiveItemScript)
    s_end
WrongAnswer:
    playsound(SFX_WRONG)
    writetext(RadioTower1FRadioCardWomanWrongAnswerText)
    waitbutton
    closetext
    s_end
NoQuiz:
    writetext(RadioTower1FRadioCardWomanNotTakingQuizText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool RadioTower1FLassScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(RadioTower1FLassText)
    SCRIPT_END
}
bool RadioTower1FYoungsterScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(RadioTower1FYoungsterText)
    SCRIPT_END
}
const struct TrainerObj TrainerGruntM3 = {GRUNTM, GRUNTM_3, EVENT_BEAT_ROCKET_GRUNTM_3, GruntM3SeenText, GruntM3BeatenText, 0, TrainerGruntM3_Script};
bool TrainerGruntM3_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(GruntM3AfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool RadioTower1FDirectory(script_s* s) {
    SCRIPT_BEGIN
    jumptext(RadioTower1FDirectoryText)
    SCRIPT_END
}
bool RadioTower1FLuckyChannelSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(RadioTower1FLuckyChannelSignText)
    SCRIPT_END
}
const uint8_t RadioTower1FLuckyNumberManGoToPCMovement[] = {
    step(RIGHT),
    turn_head(UP),
    movement_step_end,
};
const uint8_t RadioTower1FLuckyNumberManReturnToPlayerMovement[] = {
    step(LEFT),
    turn_head(UP),
    movement_step_end,
};
const txt_cmd_s RadioTower1FReceptionistWelcomeText[] = {
    text_start("Welcome!"
        t_done )
};
const txt_cmd_s RadioTower1FReceptionistNoToursText[] = {
    text_start("Hello. I'm sorry,"
        t_line "but we're not"
        t_cont "offering any tours"
        t_cont "today."
        t_done )
};
const txt_cmd_s RadioTower1FLuckyNumberManAskToPlayText[] = {
    text_start("Hi, are you here"
        t_line "for the LUCKY NUM-"
        t_cont "BER SHOW?"
        t_para "Want me to check"
        t_line "the ID numbers of"
        t_cont "your #MON?"
        t_para "If you get lucky,"
        t_line "you win a prize."
        t_done )
};
const txt_cmd_s RadioTower1FLuckyNumberManThisWeeksIdIsText[] = {
    text_start("This week's ID"
        t_line "number is @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_done )
};
const txt_cmd_s RadioTower1FLuckyNumberManCheckIfMatchText[] = {
    text_start("Let's see if you"
        t_line "have a match."
        t_done )
};
const txt_cmd_s RadioTower1FLuckyNumberManDotDotDotText[] = {
    text_start("<……>"
        t_line "<……>"
        t_done )
};
const txt_cmd_s RadioTower1FLuckyNumberManComeAgainText[] = {
    text_start("Please come back"
        t_line "next week for the"
        t_cont "next LUCKY NUMBER."
        t_done )
};
const txt_cmd_s RadioTower1FLuckyNumberManPerfectMatchText[] = {
    text_start("Wow! You have a"
        t_line "perfect match of"
        t_cont "all five numbers!"
        t_para "We have a grand"
        t_line "prize winner!"
        t_para "You have won a"
        t_line "MASTER BALL!"
        t_done )
};
const txt_cmd_s RadioTower1FLuckyNumberManOkayMatchText[] = {
    text_start("Hey! You've"
        t_line "matched the last"
        t_cont "three numbers!"
        t_para "You've won second"
        t_line "prize, an EXP."
        t_cont "SHARE!"
        t_done )
};
const txt_cmd_s RadioTower1FLuckyNumberManWeakMatchText[] = {
    text_start("Ooh, you've"
        t_line "matched the last"
        t_cont "two numbers."
        t_para "You've won third"
        t_line "prize, a PP UP."
        t_done )
};
const txt_cmd_s RadioTower1FLuckyNumberManNoneOfYourIDNumbersMatchText[] = {
    text_start("Nope, none of your"
        t_line "ID numbers match."
        t_done )
};
const txt_cmd_s RadioTower1FLuckyNumberManNoRoomForYourPrizeText[] = {
    text_start("You've got no room"
        t_line "for your prize."
        t_para "Make room and come"
        t_line "back right away."
        t_done )
};
const txt_cmd_s RadioTower1FRadioCardWomanOfferQuizText[] = {
    text_start("We have a special"
        t_line "quiz campaign on"
        t_cont "right now."
        t_para "Answer five ques-"
        t_line "tions correctly to"
        t_cont "win a RADIO CARD."
        t_para "Slide it into your"
        t_line "#GEAR to play"
        t_para "the radio anytime,"
        t_line "anywhere."
        t_para "Would you like to"
        t_line "take the quiz?"
        t_done )
};
const txt_cmd_s RadioTower1FRadioCardWomanQuestion1Text[] = {
    text_start("Question 1:"
        t_para "Is there a #MON"
        t_line "that appears only"
        t_cont "in the morning?"
        t_done )
};
const txt_cmd_s RadioTower1FRadioCardWomanQuestion2Text[] = {
    text_start("Correct!"
        t_line "Question 2:"
        t_para "Is this statement"
        t_line "correct?"
        t_para "You can't buy a"
        t_line "BERRY at a MART."
        t_done )
};
const txt_cmd_s RadioTower1FRadioCardWomanQuestion3Text[] = {
    text_start("Bull's-eye!"
        t_line "Question 3:"
        t_para "Does HM01 contain"
        t_line "the move FLASH?"
        t_done )
};
const txt_cmd_s RadioTower1FRadioCardWomanQuestion4Text[] = {
    text_start("So far so good!"
        t_line "Question 4:"
        t_para "Is FALKNER the"
        t_line "VIOLET GYM LEADER"
        t_para "who uses bird"
        t_line "#MON?"
        t_done )
};
const txt_cmd_s RadioTower1FRadioCardWomanQuestion5Text[] = {
    text_start("Wow! Right again!"
        t_line "Here's the final"
        t_cont "question:"
        t_para "Do GOLDENROD GAME"
        t_line "CORNER's slots"
        t_para "have CHARMANDER"
        t_line "on their reels?"
        t_done )
};
const txt_cmd_s RadioTower1FRadioCardWomanYouWinText[] = {
    text_start("Bingo! You got it!"
        t_line "Congratulations!"
        t_para "Here's your prize,"
        t_line "a RADIO CARD!"
        t_done )
};
const txt_cmd_s RadioTower1FPokegearIsARadioText[] = {
    text_start("<PLAYER>'s #GEAR"
        t_line "can now double as"
        t_cont "a radio!"
        t_done )
};
const txt_cmd_s RadioTower1FRadioCardWomanTuneInText[] = {
    text_start("Please tune in to"
        t_line "our radio shows."
        t_done )
};
const txt_cmd_s RadioTower1FRadioCardWomanWrongAnswerText[] = {
    text_start("Oh, dear."
        t_line "Sorry, but you"
        t_para "got it wrong."
        t_line "Please try again!"
        t_done )
};
const txt_cmd_s RadioTower1FRadioCardWomanNotTakingQuizText[] = {
    text_start("Oh. I see. Please"
        t_line "see me if you"
        t_cont "change your mind."
        t_done )
};
const txt_cmd_s RadioTower1FLassText[] = {
    text_start("BEN is a fabulous"
        t_line "DJ."
        t_para "His sweet voice"
        t_line "makes me melt!"
        t_done )
};
const txt_cmd_s RadioTower1FYoungsterText[] = {
    text_start("I love MARY, from"
        t_line "#MON TALK."
        t_para "I only know what"
        t_line "she sounds like,"
        t_cont "though."
        t_done )
};
const txt_cmd_s GruntM3SeenText[] = {
    text_start("We've finally"
        t_line "taken over the"
        t_cont "RADIO TOWER!"
        t_para "Now everyone will"
        t_line "get to experience"
        t_para "the true terror of"
        t_line "TEAM ROCKET!"
        t_para "We'll show you"
        t_line "how scary we are!"
        t_done )
};
const txt_cmd_s GruntM3BeatenText[] = {
    text_start("Too strong! We"
        t_line "must watch you…"
        t_done )
};
const txt_cmd_s GruntM3AfterBattleText[] = {
    text_start("You're too strong."
        t_para "Our plan could be"
        t_line "ruined. I must"
        t_cont "warn the others…"
        t_done )
};
const txt_cmd_s RadioTower1FDirectoryText[] = {
    text_start("1F RECEPTION"
        t_line "2F SALES"
        t_para "3F PERSONNEL"
        t_line "4F PRODUCTION"
        t_para "5F DIRECTOR'S"
        t_line "   OFFICE"
        t_done )
};
const txt_cmd_s RadioTower1FLuckyChannelSignText[] = {
    text_start("LUCKY CHANNEL!"
        t_para "Win with #MON"
        t_line "ID numbers!"
        t_para "Trade your #MON"
        t_line "to collect differ-"
        t_cont "ent ID numbers!"
        t_done )
    //db(0, 0) // filler
};
