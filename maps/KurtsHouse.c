#include "../constants.h"
#include "../util/scripting.h"
#include "KurtsHouse.h"
//// EVENTS
enum {
    KURTSHOUSE_KURT1 = 2,
    KURTSHOUSE_TWIN1,
    KURTSHOUSE_SLOWPOKE,
    KURTSHOUSE_KURT2,
    KURTSHOUSE_TWIN2,
};

const Script_fn_t KurtsHouse_SceneScripts[] = {
    0,
};

const struct MapCallback KurtsHouse_MapCallbacks[] = {
    map_callback(MAPCALLBACK_OBJECTS, KurtsHouse_MapScripts_KurtCallback),
};

const struct MapScripts KurtsHouse_MapScripts = {
    .scene_script_count = 0, // lengthof(KurtsHouse_SceneScripts),
    .scene_scripts = KurtsHouse_SceneScripts,

    .callback_count = lengthof(KurtsHouse_MapCallbacks),
    .callbacks = KurtsHouse_MapCallbacks,
};

static const struct CoordEvent KurtsHouse_CoordEvents[] = {
    0,
};

static const struct BGEvent KurtsHouse_BGEvents[] = {
    bg_event(6, 1, BGEVENT_READ, &KurtsHouseRadio),
    bg_event(8, 0, BGEVENT_READ, &KurtsHouseOakPhoto),
    bg_event(9, 0, BGEVENT_READ, &KurtsHouseOakPhoto),
    bg_event(5, 1, BGEVENT_READ, &KurtsHouseBookshelf),
    bg_event(2, 1, BGEVENT_READ, &KurtsHouseBookshelf),
    bg_event(3, 1, BGEVENT_READ, &KurtsHouseBookshelf),
    bg_event(4, 1, BGEVENT_READ, &KurtsHouseCelebiStatue),
};

static const struct WarpEventData KurtsHouse_WarpEvents[] = {
    warp_event(3, 7, AZALEA_TOWN, 4),
    warp_event(4, 7, AZALEA_TOWN, 4),
};

static const struct ObjEvent KurtsHouse_ObjectEvents[] = {
    object_event(3, 2, SPRITE_KURT, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Kurt1, EVENT_KURTS_HOUSE_KURT_1),
    object_event(5, 3, SPRITE_TWIN, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &KurtsGranddaughter1, EVENT_KURTS_HOUSE_GRANDDAUGHTER_1),
    object_event(6, 3, SPRITE_SLOWPOKE, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &KurtsHouseSlowpoke, EVENT_KURTS_HOUSE_SLOWPOKE),
    object_event(14, 3, SPRITE_KURT, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Kurt2, EVENT_KURTS_HOUSE_KURT_2),
    object_event(11, 4, SPRITE_TWIN, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &KurtsGranddaughter2, EVENT_KURTS_HOUSE_GRANDDAUGHTER_2),
};

const struct MapEvents KurtsHouse_MapEvents = {
    .warp_event_count = lengthof(KurtsHouse_WarpEvents),
    .warp_events = KurtsHouse_WarpEvents,

    .coord_event_count = 0, // lengthof(KurtsHouse_CoordEvents),
    .coord_events = KurtsHouse_CoordEvents,

    .bg_event_count = lengthof(KurtsHouse_BGEvents),
    .bg_events = KurtsHouse_BGEvents,

    .obj_event_count = lengthof(KurtsHouse_ObjectEvents),
    .obj_events = KurtsHouse_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "KurtsHouse.h"

bool KurtsHouse_MapScripts_KurtCallback(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_CLEARED_SLOWPOKE_WELL)
    iffalse_jump(KurtsHouse_MapScripts_Done)
    checkevent(EVENT_FOREST_IS_RESTLESS)
    iftrue_jump(KurtsHouse_MapScripts_Done)
    checkflag(ENGINE_KURT_MAKING_BALLS)
    iftrue_jump(KurtsHouse_MapScripts_MakingBalls)
    disappear(KURTSHOUSE_KURT2)
    appear(KURTSHOUSE_KURT1)
    disappear(KURTSHOUSE_TWIN2)
    appear(KURTSHOUSE_TWIN1)
    s_endcallback
    SCRIPT_END
}
bool KurtsHouse_MapScripts_MakingBalls(script_s* s) {
    SCRIPT_BEGIN
    disappear(KURTSHOUSE_KURT1)
    appear(KURTSHOUSE_KURT2)
    disappear(KURTSHOUSE_TWIN1)
    appear(KURTSHOUSE_TWIN2)
    SCRIPT_FALLTHROUGH(KurtsHouse_MapScripts_Done)
}
bool KurtsHouse_MapScripts_Done(script_s* s) {
    SCRIPT_BEGIN
    s_endcallback
    SCRIPT_END
}
bool Kurt1(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_KURT_GAVE_YOU_LURE_BALL)
    iftrue(GotLureBall)
    checkevent(EVENT_CLEARED_SLOWPOKE_WELL)
    iftrue(ClearedSlowpokeWell)
    writetext(KurtsHouseKurtMakingBallsMustWaitText)
    waitbutton
    closetext
    special(FadeOutMusic)
    setevent(EVENT_AZALEA_TOWN_SLOWPOKETAIL_ROCKET)
    readvar(VAR_FACING)
    ifequal(UP, RunAround)
    turnobject(PLAYER, DOWN)
    playsound(SFX_FLY)
    applymovement(KURTSHOUSE_KURT1, KurtsHouseKurtExitHouseMovement)
    playsound(SFX_EXIT_BUILDING)
    disappear(KURTSHOUSE_KURT1)
    waitsfx
    special(RestartMapMusic)
    s_end
RunAround:
    turnobject(PLAYER, DOWN)
    playsound(SFX_FLY)
    applymovement(KURTSHOUSE_KURT1, KurtsHouseKurtGoAroundPlayerThenExitHouseMovement)
    playsound(SFX_EXIT_BUILDING)
    disappear(KURTSHOUSE_KURT1)
    waitsfx
    special(RestartMapMusic)
    s_end
ClearedSlowpokeWell:
    writetext(KurtsHouseKurtHonoredToMakeBallsText)
    promptbutton
    verbosegiveitem(LURE_BALL, 1)
    iffalse(NoRoomForBall)
    setevent(EVENT_KURT_GAVE_YOU_LURE_BALL)
GotLureBall:
    checkevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1)
    iftrue(WaitForApricorns)
    checkevent(EVENT_GAVE_KURT_RED_APRICORN)
    iftrue(GiveLevelBall)
    checkevent(EVENT_GAVE_KURT_BLU_APRICORN)
    iftrue(GiveLureBall)
    checkevent(EVENT_GAVE_KURT_YLW_APRICORN)
    iftrue(GiveMoonBall)
    checkevent(EVENT_GAVE_KURT_GRN_APRICORN)
    iftrue(GiveFriendBall)
    checkevent(EVENT_GAVE_KURT_WHT_APRICORN)
    iftrue(GiveFastBall)
    checkevent(EVENT_GAVE_KURT_BLK_APRICORN)
    iftrue(GiveHeavyBall)
    checkevent(EVENT_GAVE_KURT_PNK_APRICORN)
    iftrue(GiveLoveBall)
    checkevent(EVENT_CAN_GIVE_GS_BALL_TO_KURT)
    iftrue(CanGiveGSBallToKurt)
NoGSBall:
    checkevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2)
    iftrue(CheckApricorns)
    checkevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_3)
    iftrue(CheckApricorns)
    writetext(KurtsHouseKurtBallsFromApricornsText)
    waitbutton
CheckApricorns:
    checkitem(RED_APRICORN)
    iftrue(AskApricorn)
    checkitem(BLU_APRICORN)
    iftrue(AskApricorn)
    checkitem(YLW_APRICORN)
    iftrue(AskApricorn)
    checkitem(GRN_APRICORN)
    iftrue(AskApricorn)
    checkitem(WHT_APRICORN)
    iftrue(AskApricorn)
    checkitem(BLK_APRICORN)
    iftrue(AskApricorn)
    checkitem(PNK_APRICORN)
    iftrue(AskApricorn)
    checkevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2)
    iftrue(ThatTurnedOutGreat)
    checkevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_3)
    iftrue(IMakeBallsFromApricorns)
    closetext
    s_end
IMakeBallsFromApricorns:
    writetext(KurtsHouseKurtBallsFromApricornsText)
    waitbutton
    closetext
    s_end
AskApricorn:
    writetext(KurtsHouseKurtAskYouHaveAnApricornText)
    promptbutton
    setevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_3)
    special(SelectApricornForKurt)
    ifequal(FALSE, Cancel)
    ifequal(BLU_APRICORN, Blu)
    ifequal(YLW_APRICORN, Ylw)
    ifequal(GRN_APRICORN, Grn)
    ifequal(WHT_APRICORN, Wht)
    ifequal(BLK_APRICORN, Blk)
    ifequal(PNK_APRICORN, Pnk)
// .Red
    setevent(EVENT_GAVE_KURT_RED_APRICORN)
    goto GaveKurtApricorns;
Blu:
    setevent(EVENT_GAVE_KURT_BLU_APRICORN)
    goto GaveKurtApricorns;
Ylw:
    setevent(EVENT_GAVE_KURT_YLW_APRICORN)
    goto GaveKurtApricorns;
Grn:
    setevent(EVENT_GAVE_KURT_GRN_APRICORN)
    goto GaveKurtApricorns;
Wht:
    setevent(EVENT_GAVE_KURT_WHT_APRICORN)
    goto GaveKurtApricorns;
Blk:
    setevent(EVENT_GAVE_KURT_BLK_APRICORN)
    goto GaveKurtApricorns;
Pnk:
    setevent(EVENT_GAVE_KURT_PNK_APRICORN)
    goto GaveKurtApricorns;
GaveKurtApricorns:
    setevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1)
    setflag(ENGINE_KURT_MAKING_BALLS)
WaitForApricorns:
    writetext(KurtsHouseKurtItWillTakeADayText)
    waitbutton
    closetext
    s_end
Cancel:
    writetext(KurtsHouseKurtThatsALetdownText)
    waitbutton
    closetext
    s_end
_ThatTurnedOutGreat:
    setevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2)
ThatTurnedOutGreat:
    writetext(KurtsHouseKurtTurnedOutGreatText)
    waitbutton
NoRoomForBall:
    closetext
    s_end
GiveLevelBall:
    checkflag(ENGINE_KURT_MAKING_BALLS)
    iftrue_jump(KurtMakingBallsScript)
    writetext(KurtsHouseKurtJustFinishedYourBallText)
    promptbutton
    verbosegiveitemvar(LEVEL_BALL, VAR_KURT_APRICORNS)
    iffalse(NoRoomForBall)
    clearevent(EVENT_GAVE_KURT_RED_APRICORN)
    goto _ThatTurnedOutGreat;
GiveLureBall:
    checkflag(ENGINE_KURT_MAKING_BALLS)
    iftrue_jump(KurtMakingBallsScript)
    writetext(KurtsHouseKurtJustFinishedYourBallText)
    promptbutton
    verbosegiveitemvar(LURE_BALL, VAR_KURT_APRICORNS)
    iffalse(NoRoomForBall)
    clearevent(EVENT_GAVE_KURT_BLU_APRICORN)
    goto _ThatTurnedOutGreat;
GiveMoonBall:
    checkflag(ENGINE_KURT_MAKING_BALLS)
    iftrue_jump(KurtMakingBallsScript)
    writetext(KurtsHouseKurtJustFinishedYourBallText)
    promptbutton
    verbosegiveitemvar(MOON_BALL, VAR_KURT_APRICORNS)
    iffalse(NoRoomForBall)
    clearevent(EVENT_GAVE_KURT_YLW_APRICORN)
    goto _ThatTurnedOutGreat;
GiveFriendBall:
    checkflag(ENGINE_KURT_MAKING_BALLS)
    iftrue_jump(KurtMakingBallsScript)
    writetext(KurtsHouseKurtJustFinishedYourBallText)
    promptbutton
    verbosegiveitemvar(FRIEND_BALL, VAR_KURT_APRICORNS)
    iffalse(NoRoomForBall)
    clearevent(EVENT_GAVE_KURT_GRN_APRICORN)
    goto _ThatTurnedOutGreat;
GiveFastBall:
    checkflag(ENGINE_KURT_MAKING_BALLS)
    iftrue_jump(KurtMakingBallsScript)
    writetext(KurtsHouseKurtJustFinishedYourBallText)
    promptbutton
    verbosegiveitemvar(FAST_BALL, VAR_KURT_APRICORNS)
    iffalse(NoRoomForBall)
    clearevent(EVENT_GAVE_KURT_WHT_APRICORN)
    goto _ThatTurnedOutGreat;
GiveHeavyBall:
    checkflag(ENGINE_KURT_MAKING_BALLS)
    iftrue_jump(KurtMakingBallsScript)
    writetext(KurtsHouseKurtJustFinishedYourBallText)
    promptbutton
    verbosegiveitemvar(HEAVY_BALL, VAR_KURT_APRICORNS)
    iffalse(NoRoomForBall)
    clearevent(EVENT_GAVE_KURT_BLK_APRICORN)
    goto _ThatTurnedOutGreat;
GiveLoveBall:
    checkflag(ENGINE_KURT_MAKING_BALLS)
    iftrue_jump(KurtMakingBallsScript)
    writetext(KurtsHouseKurtJustFinishedYourBallText)
    promptbutton
    verbosegiveitemvar(LOVE_BALL, VAR_KURT_APRICORNS)
    iffalse(NoRoomForBall)
    clearevent(EVENT_GAVE_KURT_PNK_APRICORN)
    goto _ThatTurnedOutGreat;
CanGiveGSBallToKurt:
    checkevent(EVENT_GAVE_GS_BALL_TO_KURT)
    iftrue(GaveGSBallToKurt)
    checkitem(GS_BALL)
    iffalse(NoGSBall)
    writetext(KurtsHouseKurtWhatIsThatText)
    waitbutton
    closetext
    setevent(EVENT_GAVE_GS_BALL_TO_KURT)
    takeitem(GS_BALL, 1)
    setflag(ENGINE_KURT_MAKING_BALLS)
    s_end
GaveGSBallToKurt:
    checkflag(ENGINE_KURT_MAKING_BALLS)
    iffalse(NotMakingBalls)
    writetext(KurtsHouseKurtImCheckingItNowText)
    waitbutton
    writetext(KurtsHouseKurtAhHaISeeText)
    waitbutton
    closetext
    s_end
NotMakingBalls:
    writetext(KurtsHouseKurtThisBallStartedToShakeText)
    waitbutton
    closetext
    setevent(EVENT_FOREST_IS_RESTLESS)
    clearevent(EVENT_CAN_GIVE_GS_BALL_TO_KURT)
    clearevent(EVENT_GAVE_GS_BALL_TO_KURT)
    special(FadeOutMusic)
    pause(20)
    showemote(EMOTE_SHOCK, KURTSHOUSE_KURT1, 30)
    readvar(VAR_FACING)
    ifequal(UP, GSBallRunAround)
    turnobject(PLAYER, DOWN)
    playsound(SFX_FLY)
    applymovement(KURTSHOUSE_KURT1, KurtsHouseKurtExitHouseMovement)
    goto KurtHasLeftTheBuilding;
GSBallRunAround:
    turnobject(PLAYER, DOWN)
    playsound(SFX_FLY)
    applymovement(KURTSHOUSE_KURT1, KurtsHouseKurtGoAroundPlayerThenExitHouseMovement)
KurtHasLeftTheBuilding:
    playsound(SFX_EXIT_BUILDING)
    disappear(KURTSHOUSE_KURT1)
    clearevent(EVENT_AZALEA_TOWN_KURT)
    waitsfx
    special(RestartMapMusic)
    setmapscene(AZALEA_TOWN, SCENE_AZALEATOWN_KURT_RETURNS_GS_BALL)
    s_end
    SCRIPT_END
}
bool Kurt2(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GAVE_GS_BALL_TO_KURT)
    iftrue_jump(KurtScript_ImCheckingItNow)
    SCRIPT_FALLTHROUGH(KurtMakingBallsScript)
}
bool KurtMakingBallsScript(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_BUGGING_KURT_TOO_MUCH)
    iffalse_jump(Script_FirstTimeBuggingKurt)
    writetext(KurtsHouseKurtDontBotherMeText)
    waitbutton
    closetext
    turnobject(KURTSHOUSE_KURT2, UP)
    s_end
    SCRIPT_END
}
bool Script_FirstTimeBuggingKurt(script_s* s) {
    SCRIPT_BEGIN
    writetext(KurtsHouseKurtGranddaughterHelpingWorkFasterText)
    waitbutton
    closetext
    turnobject(KURTSHOUSE_KURT2, UP)
    setevent(EVENT_BUGGING_KURT_TOO_MUCH)
    s_end
    SCRIPT_END
}
bool KurtScript_ImCheckingItNow(script_s* s) {
    SCRIPT_BEGIN
    writetext(KurtsHouseKurtImCheckingItNowText)
    waitbutton
    turnobject(KURTSHOUSE_KURT2, UP)
    writetext(KurtsHouseKurtAhHaISeeText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool KurtsGranddaughter1(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    checkevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1)
    iftrue_jump(KurtsGranddaughter2Subscript)
    checkevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2)
    iftrue_jump(KurtsGranddaughterFunScript)
    checkevent(EVENT_FOREST_IS_RESTLESS)
    iftrue(Lonely)
    checkevent(EVENT_FAST_SHIP_FIRST_TIME)
    iftrue(Dad)
    checkevent(EVENT_CLEARED_SLOWPOKE_WELL)
    iftrue(SlowpokeBack)
    checkevent(EVENT_AZALEA_TOWN_SLOWPOKETAIL_ROCKET)
    iftrue(Lonely)
    opentext
    writetext(KurtsGranddaughterSlowpokeGoneText)
    waitbutton
    closetext
    s_end
SlowpokeBack:
    opentext
    writetext(KurtsGranddaughterSlowpokeBackText)
    waitbutton
    closetext
    s_end
Lonely:
    opentext
    writetext(KurtsGranddaughterLonelyText)
    waitbutton
    closetext
    s_end
Dad:
    opentext
    writetext(KurtsGranddaughterDadText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool KurtsGranddaughter2(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    SCRIPT_FALLTHROUGH(KurtsGranddaughter2Subscript)
}
bool KurtsGranddaughter2Subscript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    checkevent(EVENT_GAVE_GS_BALL_TO_KURT)
    iftrue(GSBall)
    writetext(KurtsGranddaughterHelpText)
    waitbutton
    closetext
    turnobject(KURTSHOUSE_TWIN2, RIGHT)
    s_end
GSBall:
    writetext(KurtsGranddaughterGSBallText)
    waitbutton
    closetext
    turnobject(KURTSHOUSE_TWIN2, RIGHT)
    s_end
    SCRIPT_END
}
bool KurtsGranddaughterFunScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(KurtsGranddaughterFunText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool KurtsHouseSlowpoke(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(KurtsHouseSlowpokeText)
    playcry(SLOWPOKE)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool KurtsHouseOakPhoto(script_s* s) {
    SCRIPT_BEGIN
    jumptext(KurtsHouseOakPhotoText)
    SCRIPT_END
}
bool KurtsHouseCelebiStatue(script_s* s) {
    SCRIPT_BEGIN
    jumptext(KurtsHouseCelebiStatueText)
    SCRIPT_END
}
bool KurtsHouseBookshelf(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(DifficultBookshelfScript)
    SCRIPT_END
}
bool KurtsHouseRadio(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(Radio2Script)
    SCRIPT_END
}
const uint8_t KurtsHouseKurtExitHouseMovement[] = {
    big_step(DOWN),
    big_step(DOWN),
    big_step(DOWN),
    big_step(DOWN),
    big_step(DOWN),
    movement_step_end,
};
const uint8_t KurtsHouseKurtGoAroundPlayerThenExitHouseMovement[] = {
    big_step(RIGHT),
    big_step(DOWN),
    big_step(DOWN),
    big_step(DOWN),
    big_step(DOWN),
    big_step(DOWN),
    movement_step_end,
};
const txt_cmd_s KurtsHouseKurtMakingBallsMustWaitText[] = {
    text_start("Hm? Who are you?"
        t_para "<PLAYER>, eh? You"
        t_line "want me to make"
        t_cont "some BALLS?"
        t_para "Sorry, but that'll"
        t_line "have to wait."
        t_para "Do you know TEAM"
        t_line "ROCKET? Ah, don't"
        t_para "worry. I'll tell"
        t_line "you anyhow."
        t_para "TEAM ROCKET's an"
        t_line "evil gang that"
        t_para "uses #MON for"
        t_line "their dirty work."
        t_para "They're supposed"
        t_line "to have disbanded"
        t_cont "three years ago."
        t_para "Anyway, they're at"
        t_line "the WELL, cutting"
        t_para "off SLOWPOKETAILS"
        t_line "for sale!"
        t_para "So I'm going to"
        t_line "go give them a"
        t_cont "lesson in pain!"
        t_para "Hang on, SLOWPOKE!"
        t_line "Old KURT is on his"
        t_cont "way!"
        t_done )
};
const txt_cmd_s KurtsHouseKurtHonoredToMakeBallsText[] = {
    text_start("KURT: Hi, <PLAYER>!"
        t_para "You handled your-"
        t_line "self like a real"
        t_cont "hero at the WELL."
        t_para "I like your style!"
        t_para "I would be honored"
        t_line "to make BALLS for"
        t_para "a trainer like"
        t_line "you."
        t_para "This is all I have"
        t_line "now, but take it."
        t_done )
};
const txt_cmd_s KurtsHouseKurtBallsFromApricornsText[] = {
    text_start("KURT: I make BALLS"
        t_line "from APRICORNS."
        t_para "Collect them from"
        t_line "trees and bring"
        t_cont "'em to me."
        t_para "I'll make BALLS"
        t_line "out of them."
        t_done )
};
const txt_cmd_s KurtsHouseKurtAskYouHaveAnApricornText[] = {
    text_start("KURT: You have an"
        t_line "APRICORN for me?"
        t_para "Fine! I'll turn it"
        t_line "into a BALL."
        t_done )
};
const txt_cmd_s KurtsHouseKurtItWillTakeADayText[] = {
    text_start("KURT: It'll take a"
        t_line "day to make you a"
        t_para "BALL. Come back"
        t_line "for it later."
        t_done )
};
const txt_cmd_s KurtsHouseKurtThatsALetdownText[] = {
    text_start("KURT: Oh…"
        t_line "That's a letdown."
        t_done )
};
const txt_cmd_s KurtsHouseKurtDontBotherMeText[] = {
    text_start("KURT: I'm working!"
        t_line "Don't bother me!"
        t_done )
};
const txt_cmd_s KurtsHouseKurtJustFinishedYourBallText[] = {
    text_start("KURT: Ah, <PLAYER>!"
        t_line "I just finished"
        t_cont "your BALL. Here!"
        t_done )
};
const txt_cmd_s KurtsHouseKurtTurnedOutGreatText[] = {
    text_start("KURT: That turned"
        t_line "out great."
        t_para "Try catching"
        t_line "#MON with it."
        t_done )
};
const txt_cmd_s KurtsHouseKurtGranddaughterHelpingWorkFasterText[] = {
    text_start("KURT: Now that my"
        t_line "granddaughter is"
        t_para "helping me, I can"
        t_line "work much faster."
        t_done )
};
const txt_cmd_s KurtsHouseKurtWhatIsThatText[] = {
    text_start("Wh-what is that?"
        t_para "I've never seen"
        t_line "one before."
        t_para "It looks a lot"
        t_line "like a # BALL,"
        t_para "but it appears to"
        t_line "be something else."
        t_para "Let me check it"
        t_line "for you."
        t_done )
};
const txt_cmd_s KurtsHouseKurtImCheckingItNowText[] = {
    text_start("I'm checking it"
        t_line "now."
        t_done )
};
const txt_cmd_s KurtsHouseKurtAhHaISeeText[] = {
    text_start("Ah-ha! I see!"
        t_line "So…"
        t_done )
};
const txt_cmd_s KurtsHouseKurtThisBallStartedToShakeText[] = {
    text_start("<PLAYER>!"
        t_para "This BALL started"
        t_line "to shake while I"
        t_cont "was checking it."
        t_para "There must be"
        t_line "something to this!"
        t_done )
};
const txt_cmd_s KurtsGranddaughterSlowpokeGoneText[] = {
    text_start("The SLOWPOKE are"
        t_line "gone… Were they"
        t_para "taken away by bad"
        t_line "people?"
        t_done )
};
const txt_cmd_s KurtsGranddaughterLonelyText[] = {
    text_start("Grandpa's gone…"
        t_line "I'm so lonely…"
        t_done )
};
const txt_cmd_s KurtsGranddaughterSlowpokeBackText[] = {
    text_start("The SLOWPOKE my"
        t_line "dad gave me came"
        t_para "back! Its TAIL is"
        t_line "growing back too!"
        t_done )
};
const txt_cmd_s KurtsGranddaughterDadText[] = {
    text_start("Dad works at SILPH"
        t_line "where he studies"
        t_cont "# BALLS."
        t_para "I have to stay"
        t_line "home with Grandpa"
        t_cont "and SLOWPOKE."
        t_done )
};
const txt_cmd_s KurtsGranddaughterHelpText[] = {
    text_start("I get to help"
        t_line "Grandpa now!"
        t_para "We'll make good"
        t_line "BALLS for you, so"
        t_cont "please wait!"
        t_done )
};
const txt_cmd_s KurtsGranddaughterFunText[] = {
    text_start("It's fun to make"
        t_line "BALLS!"
        t_done )
};
const txt_cmd_s KurtsGranddaughterGSBallText[] = {
    text_start("Grandpa's checking"
        t_line "a BALL right now."
        t_para "So I'm waiting"
        t_line "till he's done."
        t_done )
};
const txt_cmd_s KurtsHouseSlowpokeText[] = {
    text_start("SLOWPOKE: …"
        t_line "Yawn?"
        t_done )
};
const txt_cmd_s KurtsHouseOakPhotoText[] = {
    text_start("…A young PROF."
        t_line "OAK?"
        t_done )
};
const txt_cmd_s KurtsHouseCelebiStatueText[] = {
    text_start("It's a statue of"
        t_line "the forest's pro-"
        t_cont "tector."
        t_done )
    //db(0, 0) // filler
};
