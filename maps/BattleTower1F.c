#include "../constants.h"
#include "../util/scripting.h"
#include "BattleTower1F.h"
#include "BattleTowerBattleRoom.h"
//// EVENTS
enum {
    BATTLETOWER1F_RECEPTIONIST = 2,
    BATTLETOWER1F_YOUNGSTER,
    BATTLETOWER1F_COOLTRAINER_F,
    BATTLETOWER1F_BUG_CATCHER,
    BATTLETOWER1F_GRANNY,
};

const Script_fn_t BattleTower1F_SceneScripts[] = {
    BattleTower1F_MapScripts_Scene0 , //  SCENE_DEFAULT,
    BattleTower1F_MapScripts_Scene1 , //  SCENE_FINISHED,
};

const struct MapCallback BattleTower1F_MapCallbacks[] = {
    0,
};

const struct MapScripts BattleTower1F_MapScripts = {
    .scene_script_count = lengthof(BattleTower1F_SceneScripts),
    .scene_scripts = BattleTower1F_SceneScripts,

    .callback_count = 0, // lengthof(BattleTower1F_MapCallbacks),
    .callbacks = BattleTower1F_MapCallbacks,
};

static const struct CoordEvent BattleTower1F_CoordEvents[] = {
    0,
};

static const struct BGEvent BattleTower1F_BGEvents[] = {
    bg_event(6, 6, BGEVENT_READ, &BattleTower1FRulesSign),
};

static const struct WarpEventData BattleTower1F_WarpEvents[] = {
    warp_event(7, 9, BATTLE_TOWER_OUTSIDE, 3),
    warp_event(8, 9, BATTLE_TOWER_OUTSIDE, 4),
    warp_event(7, 0, BATTLE_TOWER_ELEVATOR, 1),
};

static const struct ObjEvent BattleTower1F_ObjectEvents[] = {
    object_event(7, 6, SPRITE_RECEPTIONIST, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &BattleTower1FReceptionistScript, -1),
    object_event(14, 9, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, &BattleTower1FYoungsterScript, -1),
    object_event(4, 9, SPRITE_COOLTRAINER_F, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &BattleTower1FCooltrainerFScript, -1),
    object_event(1, 3, SPRITE_BUG_CATCHER, SPRITEMOVEDATA_WANDER, 1, 1, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &BattleTower1FBugCatcherScript, -1),
    object_event(14, 3, SPRITE_GRANNY, SPRITEMOVEDATA_WALK_UP_DOWN, 0, 1, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &BattleTower1FGrannyScript, -1),
};

const struct MapEvents BattleTower1F_MapEvents = {
    .warp_event_count = lengthof(BattleTower1F_WarpEvents),
    .warp_events = BattleTower1F_WarpEvents,

    .coord_event_count = 0, // lengthof(BattleTower1F_CoordEvents),
    .coord_events = BattleTower1F_CoordEvents,

    .bg_event_count = lengthof(BattleTower1F_BGEvents),
    .bg_events = BattleTower1F_BGEvents,

    .obj_event_count = lengthof(BattleTower1F_ObjectEvents),
    .obj_events = BattleTower1F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "BattleTower1F.h"

bool BattleTower1F_MapScripts_Scene0(script_s* s) {
    SCRIPT_BEGIN
    setval(BATTLETOWERACTION_CHECKSAVEFILEISYOURS)
    special(BattleTowerAction)
    iffalse(SkipEverything)
    setval(BATTLETOWERACTION_GET_CHALLENGE_STATE) // readmem sBattleTowerChallengeState
    special(BattleTowerAction)
    ifequal(0x0, SkipEverything)
    ifequal(0x2, LeftWithoutSaving)
    ifequal(0x3, SkipEverything)
    ifequal(0x4, SkipEverything)
    opentext
    writetext(Text_WeveBeenWaitingForYou)
    waitbutton
    closetext
    sdefer(Script_ResumeBattleTowerChallenge)
    s_end
LeftWithoutSaving:
    sdefer(BattleTower_LeftWithoutSaving)
    setval(BATTLETOWERACTION_CHALLENGECANCELED)
    special(BattleTowerAction)
    setval(BATTLETOWERACTION_06)
    special(BattleTowerAction)
SkipEverything:
    setscene(SCENE_FINISHED)
    SCRIPT_FALLTHROUGH(BattleTower1F_MapScripts_Scene1)
}
bool BattleTower1F_MapScripts_Scene1(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool BattleTower1FRulesSign(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(Text_ReadBattleTowerRules)
    yesorno
    iffalse(skip)
    writetext(Text_BattleTowerRules)
    waitbutton
skip:
    closetext
    s_end
    SCRIPT_END
}
bool BattleTower1FReceptionistScript(script_s* s) {
    SCRIPT_BEGIN
    setval(BATTLETOWERACTION_GET_CHALLENGE_STATE) // readmem sBattleTowerChallengeState
    special(BattleTowerAction)
    ifequal_jump(0x3, Script_BeatenAllTrainers2) // maps/BattleTowerBattleRoom.asm
    opentext
    writetext(Text_BattleTowerWelcomesYou)
    promptbutton
    setval(BATTLETOWERACTION_CHECK_EXPLANATION_READ) // if new save file: bit 1, [sBattleTowerSaveFileFlags]
    special(BattleTowerAction)
    ifnotequal_jump(0x0, Script_Menu_ChallengeExplanationCancel)
    sjump(Script_BattleTowerIntroductionYesNo)
    SCRIPT_END
}
bool Script_Menu_ChallengeExplanationCancel(script_s* s) {
    SCRIPT_BEGIN
    writetext(Text_WantToGoIntoABattleRoom)
    setval(TRUE)
    special(Menu_ChallengeExplanationCancel)
    ifequal_jump(1, Script_ChooseChallenge)
    ifequal_jump(2, Script_BattleTowerExplanation)
    sjump(Script_BattleTowerHopeToServeYouAgain)
    SCRIPT_END
}
bool Script_ChooseChallenge(script_s* s) {
    SCRIPT_BEGIN
    setval(BATTLETOWERACTION_RESETDATA) // ResetBattleTowerTrainerSRAM
    special(BattleTowerAction)
    special(CheckForBattleTowerRules)
    ifnotequal_jump(FALSE, Script_WaitButton)
    writetext(Text_SaveBeforeEnteringBattleRoom)
    yesorno
    iffalse_jump(Script_Menu_ChallengeExplanationCancel)
    setscene(SCENE_DEFAULT)
    special(TryQuickSave)
    iffalse_jump(Script_Menu_ChallengeExplanationCancel)
    setscene(SCENE_FINISHED)
    setval(BATTLETOWERACTION_SET_EXPLANATION_READ) // set 1, [sBattleTowerSaveFileFlags]
    special(BattleTowerAction)
    special(BattleTowerRoomMenu)
    ifequal_jump(0xa, Script_Menu_ChallengeExplanationCancel)
    ifnotequal_jump(0x0, Script_MobileError)
    setval(BATTLETOWERACTION_11)
    special(BattleTowerAction)
    writetext(Text_RightThisWayToYourBattleRoom)
    waitbutton
    closetext
    setval(BATTLETOWERACTION_CHOOSEREWARD)
    special(BattleTowerAction)
    sjump(Script_WalkToBattleTowerElevator)
    SCRIPT_END
}
bool Script_ResumeBattleTowerChallenge(script_s* s) {
    SCRIPT_BEGIN
    closetext
    setval(BATTLETOWERACTION_LOADLEVELGROUP) // load choice of level group
    special(BattleTowerAction)
    SCRIPT_FALLTHROUGH(Script_WalkToBattleTowerElevator)
}
bool Script_WalkToBattleTowerElevator(script_s* s) {
    SCRIPT_BEGIN
    musicfadeout(MUSIC_NONE, 8)
    setmapscene(BATTLE_TOWER_BATTLE_ROOM, SCENE_DEFAULT)
    setmapscene(BATTLE_TOWER_ELEVATOR, SCENE_DEFAULT)
    setmapscene(BATTLE_TOWER_HALLWAY, SCENE_DEFAULT)
    follow(BATTLETOWER1F_RECEPTIONIST, PLAYER)
    applymovement(BATTLETOWER1F_RECEPTIONIST, MovementData_BattleTower1FWalkToElevator)
    setval(BATTLETOWERACTION_0A)
    special(BattleTowerAction)
    warpsound
    disappear(BATTLETOWER1F_RECEPTIONIST)
    stopfollow
    applymovement(PLAYER, MovementData_BattleTowerHallwayPlayerEntersBattleRoom)
    warpcheck
    s_end
    SCRIPT_END
}
bool Script_GivePlayerHisPrize(script_s* s) {
    SCRIPT_BEGIN
    setval(BATTLETOWERACTION_1C)
    special(BattleTowerAction)
    setval(BATTLETOWERACTION_GIVEREWARD)
    special(BattleTowerAction)
    ifequal_jump(POTION, Script_YourPackIsStuffedFull)
    getitemname(STRING_BUFFER_4, USE_SCRIPT_VAR)
    giveitem(ITEM_FROM_MEM, 5)
    writetext(Text_PlayerGotFive)
    setval(BATTLETOWERACTION_1D)
    special(BattleTowerAction)
    closetext
    s_end
    SCRIPT_END
}
bool Script_YourPackIsStuffedFull(script_s* s) {
    SCRIPT_BEGIN
    writetext(Text_YourPackIsStuffedFull)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Script_BattleTowerIntroductionYesNo(script_s* s) {
    SCRIPT_BEGIN
    writetext(Text_WouldYouLikeToHearAboutTheBattleTower)
    yesorno
    iffalse_jump(Script_BattleTowerSkipExplanation)
    SCRIPT_FALLTHROUGH(Script_BattleTowerExplanation)
}
bool Script_BattleTowerExplanation(script_s* s) {
    SCRIPT_BEGIN
    writetext(Text_BattleTowerIntroduction_2)
    SCRIPT_FALLTHROUGH(Script_BattleTowerSkipExplanation)
}
bool Script_BattleTowerSkipExplanation(script_s* s) {
    SCRIPT_BEGIN
    setval(BATTLETOWERACTION_SET_EXPLANATION_READ)
    special(BattleTowerAction)
    sjump(Script_Menu_ChallengeExplanationCancel)
    SCRIPT_END
}
bool Script_BattleTowerHopeToServeYouAgain(script_s* s) {
    SCRIPT_BEGIN
    writetext(Text_WeHopeToServeYouAgain)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Script_MobileError2(script_s* s) {
    SCRIPT_BEGIN
    special(BattleTowerMobileError)
    closetext
    s_end
    SCRIPT_END
}
bool Script_WaitButton(script_s* s) {
    SCRIPT_BEGIN
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Script_ChooseChallenge2(script_s* s) {
    SCRIPT_BEGIN
    writetext(Text_SaveBeforeEnteringBattleRoom)
    yesorno
    iffalse_jump(Script_Menu_ChallengeExplanationCancel)
    special(TryQuickSave)
    iffalse_jump(Script_Menu_ChallengeExplanationCancel)
    setval(BATTLETOWERACTION_SET_EXPLANATION_READ)
    special(BattleTowerAction)
    special(Function1700ba)
    ifequal_jump(0xa, Script_Menu_ChallengeExplanationCancel)
    ifnotequal_jump(0x0, Script_MobileError)
    writetext(Text_ReceivedAListOfLeadersOnTheHonorRoll)
    turnobject(BATTLETOWER1F_RECEPTIONIST, LEFT)
    writetext(Text_PleaseConfirmOnThisMonitor)
    waitbutton
    turnobject(BATTLETOWER1F_RECEPTIONIST, DOWN)
    closetext
    s_end
    SCRIPT_END
}
bool Script_StartChallenge(script_s* s) {
    SCRIPT_BEGIN
    setval(BATTLETOWERACTION_LEVEL_CHECK)
    special(BattleTowerAction)
    ifnotequal_jump(0x0, Script_AMonLevelExceeds)
    setval(BATTLETOWERACTION_UBERS_CHECK)
    special(BattleTowerAction)
    ifnotequal_jump(0x0, Script_MayNotEnterABattleRoomUnderL70)
    special(CheckForBattleTowerRules)
    ifnotequal_jump(FALSE, Script_WaitButton)
    setval(BATTLETOWERACTION_05)
    special(BattleTowerAction)
    ifequal(0x0, zero)
    writetext(Text_CantBeRegistered_PreviousRecordDeleted)
    goto continue_;
zero:
    writetext(Text_CantBeRegistered)
continue_:
    yesorno
    iffalse_jump(Script_Menu_ChallengeExplanationCancel)
    writetext(Text_SaveBeforeReentry)
    yesorno
    iffalse_jump(Script_Menu_ChallengeExplanationCancel)
    setscene(SCENE_DEFAULT)
    special(TryQuickSave)
    iffalse_jump(Script_Menu_ChallengeExplanationCancel)
    setscene(SCENE_FINISHED)
    setval(BATTLETOWERACTION_06)
    special(BattleTowerAction)
    setval(BATTLETOWERACTION_12)
    special(BattleTowerAction)
    writetext(Text_RightThisWayToYourBattleRoom)
    waitbutton
    sjump(Script_ResumeBattleTowerChallenge)
    SCRIPT_END
}
bool Script_ReachedBattleLimit(script_s* s) {
    SCRIPT_BEGIN
    writetext(Text_FiveDayBattleLimit_Mobile)
    waitbutton
    sjump(Script_BattleTowerHopeToServeYouAgain)
    SCRIPT_END
}
bool Script_AMonLevelExceeds(script_s* s) {
    SCRIPT_BEGIN
    writetext(Text_AMonLevelExceeds)
    waitbutton
    sjump(Script_Menu_ChallengeExplanationCancel)
    SCRIPT_END
}
bool Script_MayNotEnterABattleRoomUnderL70(script_s* s) {
    SCRIPT_BEGIN
    writetext(Text_MayNotEnterABattleRoomUnderL70)
    waitbutton
    sjump(Script_Menu_ChallengeExplanationCancel)
    SCRIPT_END
}
bool Script_MobileError(script_s* s) {
    SCRIPT_BEGIN
    special(BattleTowerMobileError)
    closetext
    s_end
    SCRIPT_END
}
bool BattleTower_LeftWithoutSaving(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(Text_BattleTower_LeftWithoutSaving)
    waitbutton
    sjump(Script_BattleTowerHopeToServeYouAgain)
    SCRIPT_END
}
bool BattleTower1FYoungsterScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(Text_BattleTowerYoungster)
    waitbutton
    closetext
    turnobject(BATTLETOWER1F_YOUNGSTER, RIGHT)
    s_end
    SCRIPT_END
}
bool BattleTower1FCooltrainerFScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(Text_BattleTowerCooltrainerF)
    SCRIPT_END
}
bool BattleTower1FBugCatcherScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(Text_BattleTowerBugCatcher)
    SCRIPT_END
}
bool BattleTower1FGrannyScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(Text_BattleTowerGranny)
    SCRIPT_END
}
const uint8_t MovementData_BattleTower1FWalkToElevator[] = {
    step(UP),
    step(UP),
    step(UP),
    step(UP),
    step(UP),
    step(UP),
    movement_step_end,
};
const uint8_t MovementData_BattleTowerHallwayPlayerEntersBattleRoom[] = {
    step(UP),
    movement_step_end,
};
const uint8_t MovementData_BattleTowerElevatorExitElevator[] = {
    step(DOWN),
    movement_step_end,
};
const uint8_t MovementData_BattleTowerHallwayWalkTo1020Room[] = {
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    step(UP),
    step(RIGHT),
    turn_head(LEFT),
    movement_step_end,
};
const uint8_t MovementData_BattleTowerHallwayWalkTo3040Room[] = {
    step(RIGHT),
    step(RIGHT),
    step(UP),
    step(RIGHT),
    turn_head(LEFT),
    movement_step_end,
};
const uint8_t MovementData_BattleTowerHallwayWalkTo90100Room[] = {
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(UP),
    step(LEFT),
    turn_head(RIGHT),
    movement_step_end,
};
const uint8_t MovementData_BattleTowerHallwayWalkTo7080Room[] = {
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(UP),
    step(LEFT),
    turn_head(RIGHT),
    movement_step_end,
};
const uint8_t MovementData_BattleTowerHallwayWalkTo5060Room[] = {
    step(LEFT),
    step(LEFT),
    step(UP),
    step(LEFT),
    turn_head(RIGHT),
    movement_step_end,
};
const uint8_t MovementData_BattleTowerBattleRoomPlayerWalksIn[] = {
    step(UP),
    step(UP),
    step(UP),
    step(UP),
    turn_head(RIGHT),
    movement_step_end,
};
const uint8_t MovementData_BattleTowerBattleRoomOpponentWalksIn[] = {
    slow_step(DOWN),
    slow_step(DOWN),
    slow_step(DOWN),
    turn_head(LEFT),
    movement_step_end,
};
const uint8_t MovementData_BattleTowerBattleRoomOpponentWalksOut[] = {
    turn_head(UP),
    slow_step(UP),
    slow_step(UP),
    slow_step(UP),
    movement_step_end,
};
const uint8_t MovementData_BattleTowerBattleRoomReceptionistWalksToPlayer[] = {
    slow_step(RIGHT),
    slow_step(RIGHT),
    slow_step(UP),
    slow_step(UP),
    movement_step_end,
};
const uint8_t MovementData_BattleTowerBattleRoomReceptionistWalksAway[] = {
    slow_step(DOWN),
    slow_step(DOWN),
    slow_step(LEFT),
    slow_step(LEFT),
    turn_head(RIGHT),
    movement_step_end,
};
const uint8_t MovementData_BattleTowerBattleRoomPlayerTurnsToFaceReceptionist[] = {
    turn_head(DOWN),
    movement_step_end,
};
const uint8_t MovementData_BattleTowerBattleRoomPlayerTurnsToFaceNextOpponent[] = {
    turn_head(RIGHT),
    movement_step_end,
};
const txt_cmd_s Text_BattleTowerWelcomesYou[] = {
    text_start("BATTLE TOWER"
        t_line "welcomes you!"
        t_para "I could show you"
        t_line "to a BATTLE ROOM."
        t_done )
};
const txt_cmd_s Text_WantToGoIntoABattleRoom[] = {
    text_start("Want to go into a"
        t_line "BATTLE ROOM?"
        t_done )
};
const txt_cmd_s Text_RightThisWayToYourBattleRoom[] = {
    text_start("Right this way to"
        t_line "your BATTLE ROOM."
        t_done )
};
const txt_cmd_s Text_BattleTowerIntroduction_1[] = {
    text_start("BATTLE TOWER is a"
        t_line "facility made for"
        t_cont "#MON battles."
        t_para "Countless #MON"
        t_line "trainers gather"
        t_para "from all over to"
        t_line "hold battles in"
        t_para "specially designed"
        t_line "BATTLE ROOMS."
        t_para "There are many"
        t_line "BATTLE ROOMS in"
        t_cont "the BATTLE TOWER."
        t_para "Each ROOM holds"
        t_line "seven trainers."
        t_para "If you defeat the"
        t_line "seven in a ROOM,"
        t_para "and you have a"
        t_line "good record, you"
        t_para "could become the"
        t_line "ROOM's LEADER."
        t_para "All LEADERS will"
        t_line "be recorded in the"
        t_para "HONOR ROLL for"
        t_line "posterity."
        t_para "You may challenge"
        t_line "in up to five"
        t_para "BATTLE ROOMS each"
        t_line "day."
        t_para "However, you may"
        t_line "battle only once a"
        t_para "day in any given"
        t_line "ROOM."
        t_para "To interrupt a"
        t_line "session, you must"
        t_para "SAVE. If not, you"
        t_line "won't be able to"
        t_para "resume your ROOM"
        t_line "challenge."
        t_para ""
        t_done )
};
const txt_cmd_s Text_BattleTowerIntroduction_2[] = {
    text_start("BATTLE TOWER is a"
        t_line "facility made for"
        t_cont "#MON battles."
        t_para "Countless #MON"
        t_line "trainers gather"
        t_para "from all over to"
        t_line "hold battles in"
        t_para "specially designed"
        t_line "BATTLE ROOMS."
        t_para "There are many"
        t_line "BATTLE ROOMS in"
        t_cont "the BATTLE TOWER."
        t_para "Each ROOM holds"
        t_line "seven trainers."
        t_para "Beat them all, and"
        t_line "win a prize."
        t_para "To interrupt a"
        t_line "session, you must"
        t_para "SAVE. If not, you"
        t_line "won't be able to"
        t_para "resume your ROOM"
        t_line "challenge."
        t_para ""
        t_done )
};
const txt_cmd_s Text_ReceivedAListOfLeadersOnTheHonorRoll[] = {
    text_start("Received a list of"
        t_line "LEADERS on the"
        t_cont "HONOR ROLL."
        t_para ""
        t_done )
};
const txt_cmd_s Text_PleaseConfirmOnThisMonitor[] = {
    text_start("Please confirm on"
        t_line "this monitor."
        t_done )
};
const txt_cmd_s Text_ThankYou[] = {
    text_start("Thank you!"
        t_para ""
        t_done )
};
const txt_cmd_s Text_ThanksForVisiting[] = {
    text_start("Thanks for"
        t_line "visiting!"
        t_done )
};
const txt_cmd_s Text_BeatenAllTheTrainers_Mobile[] = {
    text_start("Congratulations!"
        t_para "You've beaten all"
        t_line "the trainers!"
        t_para "Your feat may be"
        t_line "worth registering,"
        t_para "<PLAYER>. With your"
        t_line "results, you may"
        t_para "be chosen as a"
        t_line "ROOM LEADER."
        t_para ""
        t_done )
};
const txt_cmd_s Text_CongratulationsYouveBeatenAllTheTrainers[] = {
    text_start("Congratulations!"
        t_para "You've beaten all"
        t_line "the trainers!"
        t_para "For that, you get"
        t_line "this great prize!"
        t_para ""
        t_done )
};
const txt_cmd_s Text_AskRegisterRecord_Mobile[] = {
    text_start("Would you like to"
        t_line "register your"
        t_para "record with the"
        t_line "CENTER?"
        t_done )
};
const txt_cmd_s Text_PlayerGotFive[] = {
    text_start("<PLAYER> got five"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start("!@")
    sound_item
    text_promptbutton
    text_end
};
const txt_cmd_s Text_YourPackIsStuffedFull[] = {
    text_start("Oops, your PACK is"
        t_line "stuffed full."
        t_para "Please make room"
        t_line "and come back."
        t_done )
};
const txt_cmd_s Text_YourRegistrationIsComplete[] = {
    text_start("Your registration"
        t_line "is complete."
        t_para "Please come again!"
        t_done )
};
const txt_cmd_s Text_WeHopeToServeYouAgain[] = {
    text_start("We hope to serve"
        t_line "you again."
        t_done )
};
const txt_cmd_s Text_PleaseStepThisWay[] = {
    text_start("Please step this"
        t_line "way."
        t_done )
};
const txt_cmd_s Text_WouldYouLikeToHearAboutTheBattleTower[] = {
    text_start("Would you like to"
        t_line "hear about the"
        t_cont "BATTLE TOWER?"
        t_done )
};
const txt_cmd_s Text_CantBeRegistered[] = {
    text_start("Your record from"
        t_line "the previous"
        t_para "BATTLE ROOM can't"
        t_line "be registered. OK?"
        t_done )
};
const txt_cmd_s Text_CantBeRegistered_PreviousRecordDeleted[] = {
    text_start("Your record from"
        t_line "the previous"
        t_para "BATTLE ROOM can't"
        t_line "be registered."
        t_para "Also, the existing"
        t_line "record will be"
        t_cont "deleted. OK?"
        t_done )
};
const txt_cmd_s Text_CheckTheLeaderHonorRoll[] = {
    text_start("Check the LEADER"
        t_line "HONOR ROLL?"
        t_done )
};
const txt_cmd_s Text_ReadBattleTowerRules[] = {
    text_start("BATTLE TOWER rules"
        t_line "are written here."
        t_para "Read the rules?"
        t_done )
};
const txt_cmd_s Text_BattleTowerRules[] = {
    text_start("Three #MON may"
        t_line "enter battles."
        t_para "All three must be"
        t_line "different."
        t_para "The items they"
        t_line "hold must also be"
        t_cont "different."
        t_para "Certain #MON"
        t_line "may also have"
        t_para "level restrictions"
        t_line "placed on them."
        t_done )
};
const txt_cmd_s Text_BattleTower_LeftWithoutSaving[] = {
    text_start("Excuse me!"
        t_line "You didn't SAVE"
        t_para "before exiting"
        t_line "the BATTLE ROOM."
        t_para "I'm awfully sorry,"
        t_line "but your challenge"
        t_para "will be declared"
        t_line "invalid."
        t_done )
};
const txt_cmd_s Text_YourMonWillBeHealedToFullHealth[] = {
    text_start("Your #MON will"
        t_line "be healed to full"
        t_cont "health."
        t_done )
};
const txt_cmd_s Text_NextUpOpponentNo[] = {
    text_start("Next up, opponent"
        t_line "no.@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(". Ready?"
        t_done )
};
const txt_cmd_s Text_SaveBeforeConnecting_Mobile[] = {
    text_start("Your session will"
        t_line "be SAVED before"
        t_para "connecting with"
        t_line "the CENTER."
        t_done )
};
const txt_cmd_s Text_SaveBeforeEnteringBattleRoom[] = {
    text_start("Before entering"
        t_line "the BATTLE ROOM,"
        t_para "your progress will"
        t_line "be saved."
        t_done )
};
const txt_cmd_s Text_SaveAndEndTheSession[] = {
    text_start("SAVE and end the"
        t_line "session?"
        t_done )
};
const txt_cmd_s Text_SaveBeforeReentry[] = {
    text_start("Your record will"
        t_line "be SAVED before"
        t_para "you go back into"
        t_line "the previous ROOM."
        t_done )
};
const txt_cmd_s Text_CancelYourBattleRoomChallenge[] = {
    text_start("Cancel your BATTLE"
        t_line "ROOM challenge?"
        t_done )
};
const txt_cmd_s Text_RegisterRecordOnFile_Mobile[] = {
    text_start("We have your"
        t_line "previous record on"
        t_para "file. Would you"
        t_line "like to register"
        t_cont "it at the CENTER?"
        t_done )
};
const txt_cmd_s Text_WeveBeenWaitingForYou[] = {
    text_start("We've been waiting"
        t_line "for you. This way"
        t_para "to a BATTLE ROOM,"
        t_line "please."
        t_done )
};
const txt_cmd_s Text_FiveDayBattleLimit_Mobile[] = {
    text_start("You may enter only"
        t_line "five BATTLE ROOMS"
        t_cont "each day."
        t_para "Please come back"
        t_line "tomorrow."
        t_done )
};
const txt_cmd_s Text_TooMuchTimeElapsedNoRegister[] = {
    text_start("Sorry, but it's"
        t_line "not possible to"
        t_para "register your"
        t_line "current record at"
        t_para "the CENTER because"
        t_line "too much time has"
        t_para "elapsed since the"
        t_line "start of your"
        t_cont "challenge."
        t_done )
};
const txt_cmd_s Text_RegisterRecordTimedOut_Mobile[] = {
// duplicate of Text_TooMuchTimeElapsedNoRegister
    text_start("Sorry, but it's"
        t_line "not possible to"
        t_para "register your most"
        t_line "recent record at"
        t_para "the CENTER because"
        t_line "too much time has"
        t_para "elapsed since the"
        t_line "start of your"
        t_cont "challenge."
        t_done )
};
const txt_cmd_s Text_AMonLevelExceeds[] = {
    text_start("One or more of"
        t_line "your #MON's"
        t_cont "levels exceeds @")
    text_decimal(wram_ptr(wScriptVar), 1, 3)
    text_start("."
        t_done )
};
const txt_cmd_s Text_MayNotEnterABattleRoomUnderL70[] = {
    text_ram(wram_ptr(wcd49))
    text_start(" may not"
        t_line "enter a BATTLE"
        t_cont "ROOM under L70."
        t_para "This BATTLE ROOM"
        t_line "is for L@")
    text_decimal(wram_ptr(wScriptVar), 1, 3)
    text_start("."
        t_done )
};
const txt_cmd_s Text_BattleTowerYoungster[] = {
    text_start("Destroyed by the"
        t_line "first opponent in"
        t_para "no time at all…"
        t_line "I'm no good…"
        t_done )
};
const txt_cmd_s Text_BattleTowerCooltrainerF[] = {
    text_start("There are lots of"
        t_line "BATTLE ROOMS, but"
        t_para "I'm going to win"
        t_line "them all!"
        t_done )
};
const txt_cmd_s Text_BattleTowerGranny[] = {
    text_start("It's a grueling"
        t_line "task, not being"
        t_para "able to use items"
        t_line "in battle."
        t_para "Making your"
        t_line "#MON hold items"
        t_para "is the key to"
        t_line "winning battles."
        t_done )
};
const txt_cmd_s Text_BattleTowerBugCatcher[] = {
    text_start("I'm trying to see"
        t_line "how far I can go"
        t_para "using just bug"
        t_line "#MON."
        t_para "Don't let there be"
        t_line "any fire #MON…"
        t_done )
    //db(0, 0) // filler
};
