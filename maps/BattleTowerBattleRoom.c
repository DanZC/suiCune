#include "../constants.h"
#include "../util/scripting.h"
#include "BattleTowerBattleRoom.h"
#include "BattleTower1F.h"
//// EVENTS
enum {
    BATTLETOWERBATTLEROOM_YOUNGSTER = 2,
    BATTLETOWERBATTLEROOM_RECEPTIONIST,
};

const Script_fn_t BattleTowerBattleRoom_SceneScripts[] = {
    BattleTowerBattleRoom_MapScripts_EnterBattleRoom , //  SCENE_DEFAULT,
    BattleTowerBattleRoom_MapScripts_DummyScene , //  SCENE_FINISHED,
};

const struct MapCallback BattleTowerBattleRoom_MapCallbacks[] = {
    0,
};

const struct MapScripts BattleTowerBattleRoom_MapScripts = {
    .scene_script_count = lengthof(BattleTowerBattleRoom_SceneScripts),
    .scene_scripts = BattleTowerBattleRoom_SceneScripts,

    .callback_count = 0, // lengthof(BattleTowerBattleRoom_MapCallbacks),
    .callbacks = BattleTowerBattleRoom_MapCallbacks,
};

static const struct CoordEvent BattleTowerBattleRoom_CoordEvents[] = {
    0,
};

static const struct BGEvent BattleTowerBattleRoom_BGEvents[] = {
    0,
};

static const struct WarpEventData BattleTowerBattleRoom_WarpEvents[] = {
    warp_event(3, 7, BATTLE_TOWER_HALLWAY, 4),
    warp_event(4, 7, BATTLE_TOWER_HALLWAY, 4),
};

static const struct ObjEvent BattleTowerBattleRoom_ObjectEvents[] = {
    object_event(4, 0, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, EVENT_BATTLE_TOWER_BATTLE_ROOM_YOUNGSTER),
    object_event(1, 6, SPRITE_RECEPTIONIST, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, -1),
};

const struct MapEvents BattleTowerBattleRoom_MapEvents = {
    .warp_event_count = lengthof(BattleTowerBattleRoom_WarpEvents),
    .warp_events = BattleTowerBattleRoom_WarpEvents,

    .coord_event_count = 0, // lengthof(BattleTowerBattleRoom_CoordEvents),
    .coord_events = BattleTowerBattleRoom_CoordEvents,

    .bg_event_count = 0, // lengthof(BattleTowerBattleRoom_BGEvents),
    .bg_events = BattleTowerBattleRoom_BGEvents,

    .obj_event_count = lengthof(BattleTowerBattleRoom_ObjectEvents),
    .obj_events = BattleTowerBattleRoom_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "../engine/events/battle_tower/battle_tower.h"
#include "BattleTowerBattleRoom.h"

bool BattleTowerBattleRoom_MapScripts_EnterBattleRoom(script_s* s) {
    SCRIPT_BEGIN
    disappear(BATTLETOWERBATTLEROOM_YOUNGSTER)
    sdefer(Script_BattleRoom)
    setscene(SCENE_FINISHED)
    SCRIPT_FALLTHROUGH(BattleTowerBattleRoom_MapScripts_DummyScene)
}
bool BattleTowerBattleRoom_MapScripts_DummyScene(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool Script_BattleRoom(script_s* s) {
    SCRIPT_BEGIN
    applymovement(PLAYER, MovementData_BattleTowerBattleRoomPlayerWalksIn)
// beat all 7 opponents in a row
    SCRIPT_FALLTHROUGH(Script_BattleRoomLoop)
}
bool Script_BattleRoomLoop(script_s* s) {
    SCRIPT_BEGIN
    setval(BATTLETOWERBATTLEROOM_YOUNGSTER)
    special(LoadOpponentTrainerAndPokemonWithOTSprite)
    appear(BATTLETOWERBATTLEROOM_YOUNGSTER)
    warpsound
    waitsfx
    applymovement(BATTLETOWERBATTLEROOM_YOUNGSTER, MovementData_BattleTowerBattleRoomOpponentWalksIn)
    opentext
    battletowertext(BATTLETOWERTEXT_INTRO)
    promptbutton
    closetext
    special(BattleTowerBattle) // predef StartBattle
    special(FadeOutPalettes)
    reloadmap
    ifnotequal_jump(0x0, Script_FailedBattleTowerChallenge)
    readmem(wram_ptr(wNrOfBeatenBattleTowerTrainers))
    ifequal_jump(BATTLETOWER_STREAK_LENGTH, Script_BeatenAllTrainers)
    applymovement(BATTLETOWERBATTLEROOM_YOUNGSTER, MovementData_BattleTowerBattleRoomOpponentWalksOut)
    warpsound
    disappear(BATTLETOWERBATTLEROOM_YOUNGSTER)
    applymovement(BATTLETOWERBATTLEROOM_RECEPTIONIST, MovementData_BattleTowerBattleRoomReceptionistWalksToPlayer)
    applymovement(PLAYER, MovementData_BattleTowerBattleRoomPlayerTurnsToFaceReceptionist)
    opentext
    writetext(Text_YourMonWillBeHealedToFullHealth)
    waitbutton
    closetext
    playmusic(MUSIC_HEAL)
    special(FadeOutPalettes)
    special(LoadMapPalettes)
    pause(60)
    special(FadeInPalettes)
    special(RestartMapMusic)
    opentext
    writetext(Text_NextUpOpponentNo)
    yesorno
    iffalse_jump(Script_DontBattleNextOpponent)
    SCRIPT_FALLTHROUGH(Script_ContinueAndBattleNextOpponent)
}
bool Script_ContinueAndBattleNextOpponent(script_s* s) {
    SCRIPT_BEGIN
    closetext
    applymovement(PLAYER, MovementData_BattleTowerBattleRoomPlayerTurnsToFaceNextOpponent)
    applymovement(BATTLETOWERBATTLEROOM_RECEPTIONIST, MovementData_BattleTowerBattleRoomReceptionistWalksAway)
    sjump(Script_BattleRoomLoop)
    SCRIPT_END
}
bool Script_DontBattleNextOpponent(script_s* s) {
    SCRIPT_BEGIN
    writetext(Text_SaveAndEndTheSession)
    yesorno
    iffalse_jump(Script_DontSaveAndEndTheSession)
    readmem(&gBattleTowerType)
    ifequal(BATTLE_TOWER_MOBILE, mobile)
    setval(BATTLETOWERACTION_SAVELEVELGROUP) // save level group
    special(BattleTowerAction)
    setval(BATTLETOWERACTION_SAVEOPTIONS) // choose reward
    special(BattleTowerAction)
mobile:
    setval(BATTLETOWERACTION_SAVE_AND_QUIT) // quicksave
    special(BattleTowerAction)
    playsound(SFX_SAVE)
    waitsfx
    special(FadeOutPalettes)
    special(Reset)
    SCRIPT_FALLTHROUGH(Script_DontSaveAndEndTheSession)
}
bool Script_DontSaveAndEndTheSession(script_s* s) {
    SCRIPT_BEGIN
    writetext(Text_CancelYourBattleRoomChallenge)
    yesorno
    iffalse_jump(Script_ContinueAndBattleNextOpponent)
    setval(BATTLETOWERACTION_CHALLENGECANCELED)
    special(BattleTowerAction)
    setval(BATTLETOWERACTION_06)
    special(BattleTowerAction)
    closetext
    special(FadeOutPalettes)
    warpfacing(UP, BATTLE_TOWER_1F, 7, 7)
    opentext
    sjump(Script_BattleTowerHopeToServeYouAgain)
    SCRIPT_END
}
bool Script_FailedBattleTowerChallenge(script_s* s) {
    SCRIPT_BEGIN
    pause(60)
    special(BattleTowerFade)
    warpfacing(UP, BATTLE_TOWER_1F, 7, 7)
    setval(BATTLETOWERACTION_CHALLENGECANCELED)
    special(BattleTowerAction)
    opentext
    readmem(&gBattleTowerType)
    ifequal(BATTLE_TOWER_MOBILE, mobile)
    writetext(Text_ThanksForVisiting)
    waitbutton
    closetext
    s_end
mobile:
    writetext(Text_ThankYou)
    sjump(Script_AskRegisterRecord)
    SCRIPT_END
}
bool Script_BeatenAllTrainers(script_s* s) {
    SCRIPT_BEGIN
    pause(60)
    special(BattleTowerFade)
    warpfacing(UP, BATTLE_TOWER_1F, 7, 7)
    SCRIPT_FALLTHROUGH(Script_BeatenAllTrainers2)
}
bool Script_BeatenAllTrainers2(script_s* s) {
    SCRIPT_BEGIN
    readmem(&gBattleTowerType)
    ifequal(BATTLE_TOWER_MOBILE, mobile)
    opentext
    writetext(Text_CongratulationsYouveBeatenAllTheTrainers)
    sjump(Script_GivePlayerHisPrize)
mobile:
    setval(BATTLETOWERACTION_13)
	special(BattleTowerAction)
	ifequal_jump(1, Script_ChallengeCanceled) // $7a90
	setval(BATTLETOWERACTION_05)
	special(BattleTowerAction)
	ifequal_jump(8, Script_TooMuchTimeElapsedNoRegister) //$7a84
	setval(BATTLETOWERACTION_CHALLENGECANCELED)
	special(BattleTowerAction)
	opentext
	writetext(Text_BeatenAllTheTrainers_Mobile)//$74ca
	sjump(Script_AskRegisterRecord)//$71b4
    SCRIPT_END
}
bool Script_TooMuchTimeElapsedNoRegister(script_s* s) {
    SCRIPT_BEGIN
    setval(BATTLETOWERACTION_CHALLENGECANCELED)
    special(BattleTowerAction)
    opentext
    writetext(Text_TooMuchTimeElapsedNoRegister)
    waitbutton
    closetext
    battletoweraction(BATTLETOWERACTION_RELOAD_PARTY)
    s_end
    SCRIPT_END
}
bool Script_ChallengeCanceled(script_s* s) {
    SCRIPT_BEGIN
    setval(BATTLETOWERACTION_CHALLENGECANCELED)
    special(BattleTowerAction)
    setval(BATTLETOWERACTION_06)
    special(BattleTowerAction)
    opentext
    writetext(Text_ThanksForVisiting)
    writetext(Text_WeHopeToServeYouAgain)
    waitbutton
    closetext
    battletoweraction(BATTLETOWERACTION_RELOAD_PARTY)
    s_end
    SCRIPT_END
}
const txt_cmd_s Text_ReturnedAfterSave_Mobile[] = {
    text_start("You'll be returned"
        t_line "after you SAVE."
        t_done )
    //db(0, 0) // filler
};
