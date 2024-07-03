#include "../constants.h"
#include "../util/scripting.h"
#include "Pokecenter2F.h"
#include "../engine/link/lan.h"
//// EVENTS
enum {
    POKECENTER2F_TRADE_RECEPTIONIST = 2,
    POKECENTER2F_BATTLE_RECEPTIONIST,
    POKECENTER2F_TIME_CAPSULE_RECEPTIONIST,
    POKECENTER2F_OFFICER,
};

const Script_fn_t Pokecenter2F_SceneScripts[] = {
    Pokecenter2F_MapScripts_Scene0 , //  SCENE_DEFAULT,
    Pokecenter2F_MapScripts_Scene1 , //  SCENE_POKECENTER2F_LEAVE_TRADE_CENTER,
    Pokecenter2F_MapScripts_Scene2 , //  SCENE_POKECENTER2F_LEAVE_COLOSSEUM,
    Pokecenter2F_MapScripts_Scene3 , //  SCENE_POKECENTER2F_LEAVE_TIME_CAPSULE,
    Pokecenter2F_MapScripts_Scene4 , //  SCENE_POKECENTER2F_LEAVE_MOBILE_TRADE_ROOM,
    Pokecenter2F_MapScripts_Scene5 , //  SCENE_POKECENTER2F_LEAVE_MOBILE_BATTLE_ROOM,
};

const struct MapCallback Pokecenter2F_MapCallbacks[] = {
    0,
};

const struct MapScripts Pokecenter2F_MapScripts = {
    .scene_script_count = lengthof(Pokecenter2F_SceneScripts),
    .scene_scripts = Pokecenter2F_SceneScripts,

    .callback_count = 0, // lengthof(Pokecenter2F_MapCallbacks),
    .callbacks = Pokecenter2F_MapCallbacks,
};

static const struct CoordEvent Pokecenter2F_CoordEvents[] = {
    0,
};

static const struct BGEvent Pokecenter2F_BGEvents[] = {
    bg_event(7, 3, BGEVENT_READ, Pokecenter2FLinkRecordSign),
};

static const struct WarpEventData Pokecenter2F_WarpEvents[] = {
    warp_event(0, 7, POKECENTER_2F, -1),
    warp_event(4, 0, TRADE_CENTER, 1),
    warp_event(8, 0, COLOSSEUM, 1),
    warp_event(13, 2, TIME_CAPSULE, 1),
    warp_event(6, 0, MOBILE_TRADE_ROOM, 1),
    warp_event(10, 0, MOBILE_BATTLE_ROOM, 1),
};

static const struct ObjEvent Pokecenter2F_ObjectEvents[] = {
    object_event(5, 2, SPRITE_LINK_RECEPTIONIST, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, LinkReceptionistScript_Trade, -1),
    object_event(9, 2, SPRITE_LINK_RECEPTIONIST, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, LinkReceptionistScript_Battle, -1),
    object_event(13, 3, SPRITE_LINK_RECEPTIONIST, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, LinkReceptionistScript_TimeCapsule, -1),
    object_event(1, 1, SPRITE_OFFICER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, Pokecenter2FOfficerScript, EVENT_MYSTERY_GIFT_DELIVERY_GUY),
};

const struct MapEvents Pokecenter2F_MapEvents = {
    .warp_event_count = lengthof(Pokecenter2F_WarpEvents),
    .warp_events = Pokecenter2F_WarpEvents,

    .coord_event_count = 0, // lengthof(Pokecenter2F_CoordEvents),
    .coord_events = Pokecenter2F_CoordEvents,

    .bg_event_count = lengthof(Pokecenter2F_BGEvents),
    .bg_events = Pokecenter2F_BGEvents,

    .obj_event_count = lengthof(Pokecenter2F_ObjectEvents),
    .obj_events = Pokecenter2F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "Pokecenter2F.h"

bool Pokecenter2F_MapScripts_Scene0(script_s* s) {
    SCRIPT_BEGIN
    special(CheckMysteryGift)
    ifequal_jump(0x0, Pokecenter2F_MapScripts_Scene0Done)
    clearevent(EVENT_MYSTERY_GIFT_DELIVERY_GUY)
    checkevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2)
    iftrue_jump(Pokecenter2F_MapScripts_Scene0Done)
    sdefer(Pokecenter2F_AppearMysteryGiftDeliveryGuy)
    SCRIPT_FALLTHROUGH(Pokecenter2F_MapScripts_Scene0Done)
}
bool Pokecenter2F_MapScripts_Scene0Done(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool Pokecenter2F_MapScripts_Scene1(script_s* s) {
    SCRIPT_BEGIN
    sdefer(Script_LeftCableTradeCenter)
    s_end
    SCRIPT_END
}
bool Pokecenter2F_MapScripts_Scene2(script_s* s) {
    SCRIPT_BEGIN
    sdefer(Script_LeftCableColosseum)
    s_end
    SCRIPT_END
}
bool Pokecenter2F_MapScripts_Scene3(script_s* s) {
    SCRIPT_BEGIN
    sdefer(Script_LeftTimeCapsule)
    s_end
    SCRIPT_END
}
bool Pokecenter2F_MapScripts_Scene4(script_s* s) {
    SCRIPT_BEGIN
    sdefer(Script_LeftMobileTradeRoom)
    s_end
    SCRIPT_END
}
bool Pokecenter2F_MapScripts_Scene5(script_s* s) {
    SCRIPT_BEGIN
    sdefer(Script_LeftMobileBattleRoom)
    s_end
    SCRIPT_END
}
bool Pokecenter2F_AppearMysteryGiftDeliveryGuy(script_s* s) {
    SCRIPT_BEGIN
    appear(POKECENTER2F_OFFICER)
    setevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2)
    s_end
    SCRIPT_END
}
bool Script_TradeCenterClosed(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(Text_TradeRoomClosed)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Script_BattleRoomClosed(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(Text_BattleRoomClosed)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool LinkReceptionistScript_Trade(script_s* s) {
    SCRIPT_BEGIN
    // checkevent(EVENT_GAVE_MYSTERY_EGG_TO_ELM)
    // iffalse_jump(Script_TradeCenterClosed)
    opentext
    writetext(Text_TradeReceptionistIntro)
    yesorno
    iffalse(Cancel)
    special(Mobile_DummyReturnFalse) // always returns false
    iffalse(NoMobile)
    writetext(Text_TradeReceptionistMobile)
    special(AskMobileOrCable)
    iffalse(Cancel)
    ifequal(0x1, Mobile)
NoMobile:
    LANConnection();
    iffalse(DidNotSave)
    special(SetBitsForLinkTradeRequest)
    writetext(Text_PleaseWait)
    special(WaitForLinkedFriend)
    iffalse(FriendNotReady)
    writetext(Text_MustSaveGame)
    yesorno
    iffalse(DidNotSave)
    special(TryQuickSave)
    iffalse(DidNotSave)
    writetext(Text_PleaseWait)
    special(CheckLinkTimeout_Receptionist)
    iffalse(LinkTimedOut)
    readmem(&wram->wOtherPlayerLinkMode)
    iffalse(LinkedToFirstGen)
    special(CheckBothSelectedSameRoom)
    iffalse(IncompatibleRooms)
    writetext(Text_PleaseComeIn)
    waitbutton
    closetext
    scall(Pokecenter2F_CheckGender)
    warpcheck
    s_end
FriendNotReady:
    special(WaitForOtherPlayerToExit)
    LANCloseConnection();
    writetext(YourFriendIsNotReadyText)
    closetext
    s_end
LinkedToFirstGen:
    special(FailedLinkToPast)
    writetext(Text_CantLinkToThePast)
    special(CloseLink)
    closetext
    s_end
IncompatibleRooms:
    writetext(Text_IncompatibleRooms)
    special(CloseLink)
    closetext
    s_end
LinkTimedOut:
    writetext(Text_LinkTimedOut)
    goto AbortLink;
DidNotSave:
    writetext(Text_PleaseComeAgain)
AbortLink:
    special(WaitForOtherPlayerToExit)
    LANCloseConnection();
Cancel:
    closetext
    s_end
Mobile:
    scall_local(Mobile_TrySave);
    iftrue(Mobile_Abort)
    scall(BattleTradeMobile_WalkIn)
    warpcheck
    s_end
Mobile_Abort:
    s_end
Mobile_TrySave:
    writetext(Text_MustSaveGame)
    yesorno
    iffalse(Mobile_DidNotSave)
    special(TryQuickSave)
    iffalse(Mobile_DidNotSave)
    special(Function1011f1)
    writetext(Text_PleaseComeIn)
    waitbutton
    closetext
    setval(FALSE)
    s_end
Mobile_DidNotSave:
    writetext(Text_PleaseComeAgain)
    closetext
    setval(TRUE)
    s_end
    SCRIPT_END
}
bool BattleTradeMobile_WalkIn(script_s* s) {
    SCRIPT_BEGIN
    applymovementlasttalked(Pokecenter2FMobileMobileMovementData_ReceptionistWalksUpAndLeft_LookDown)
    applymovement(PLAYER, Pokecenter2FMobileMovementData_PlayerWalksIntoMobileBattleRoom)
    s_end
    SCRIPT_END
}
bool LinkReceptionistScript_Battle(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_GAVE_MYSTERY_EGG_TO_ELM)
    iffalse_jump(Script_BattleRoomClosed)
    opentext
    writetext(Text_BattleReceptionistIntro)
    yesorno
    iffalse(Cancel)
    special(Mobile_DummyReturnFalse) // always returns false
    iffalse(NoMobile)
    writetext(Text_BattleReceptionistMobile)
    special(AskMobileOrCable)
    iffalse(Cancel)
    ifequal(0x1, Mobile)
NoMobile:
    LANConnection();
    iffalse(DidNotSave)
    special(SetBitsForBattleRequest)
    writetext(Text_PleaseWait)
    special(WaitForLinkedFriend)
    iffalse(FriendNotReady)
    writetext(Text_MustSaveGame)
    yesorno
    iffalse(DidNotSave)
    special(TryQuickSave)
    iffalse(DidNotSave)
    writetext(Text_PleaseWait)
    special(CheckLinkTimeout_Receptionist)
    iffalse(LinkTimedOut)
    readmem(&wram->wOtherPlayerLinkMode)
    iffalse(LinkedToFirstGen)
    special(CheckBothSelectedSameRoom)
    iffalse(IncompatibleRooms)
    writetext(Text_PleaseComeIn)
    waitbutton
    closetext
    scall(Pokecenter2F_CheckGender)
    warpcheck
    s_end
FriendNotReady:
    special(WaitForOtherPlayerToExit)
    writetext(YourFriendIsNotReadyText)
    closetext
    s_end
LinkedToFirstGen:
    special(FailedLinkToPast)
    writetext(Text_CantLinkToThePast)
    special(CloseLink)
    closetext
    s_end
IncompatibleRooms:
    writetext(Text_IncompatibleRooms)
    special(CloseLink)
    closetext
    s_end
LinkTimedOut:
    writetext(Text_LinkTimedOut)
    goto AbortLink;
DidNotSave:
    writetext(Text_PleaseComeAgain)
AbortLink:
    special(WaitForOtherPlayerToExit)
Cancel:
    closetext
    s_end
Mobile:
    scall_local(SelectThreeMons);
    iffalse(Mobile_Abort)
    scall_local(Mobile_TrySave);
    iftrue(Mobile_Abort)
    scall(BattleTradeMobile_WalkIn)
    warpcheck
    s_end
Mobile_Abort:
    s_end
Mobile_TrySave:
    writetext(Text_MustSaveGame)
    yesorno
    iffalse(Mobile_DidNotSave)
    special(Function103780)
    iffalse(Mobile_DidNotSave)
    special(Function1011f1)
    writetext(Text_PleaseComeIn)
    waitbutton
    closetext
    setval(FALSE)
    s_end
Mobile_DidNotSave:
    writetext(Text_PleaseComeAgain)
    closetext
    setval(TRUE)
    s_end
SelectThreeMons:
    special(Mobile_SelectThreeMons)
    iffalse(Mobile_DidNotSelect)
    ifequal(0x1, Mobile_OK)
    ifequal(0x2, Mobile_OK)
    ifequal(0x3, Mobile_InvalidParty)
    goto Mobile_DidNotSelect;
Mobile_InvalidParty:
    writetext(Text_BrokeStadiumRules)
    waitbutton
Mobile_DidNotSelect:
    closetext
    setval(FALSE)
    s_end
Mobile_OK:
    setval(TRUE)
    s_end
    SCRIPT_END
}
bool Script_TimeCapsuleClosed(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(Text_TimeCapsuleClosed)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool LinkReceptionistScript_TimeCapsule(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_MET_BILL)
    iftrue_jump(Script_TimeCapsuleClosed)
    checkflag(ENGINE_TIME_CAPSULE)
    iftrue_jump(Script_TimeCapsuleClosed)
    special(SetBitsForTimeCapsuleRequest)
    faceplayer
    opentext
    writetext(Text_TimeCapsuleReceptionistIntro)
    yesorno
    iffalse(Cancel)
    special(CheckTimeCapsuleCompatibility)
    ifequal(0x1, MonTooNew)
    ifequal(0x2, MonMoveTooNew)
    ifequal(0x3, MonHasMail)
    writetext(Text_PleaseWait)
    special(WaitForLinkedFriend)
    iffalse(FriendNotReady)
    writetext(Text_MustSaveGame)
    yesorno
    iffalse(DidNotSave)
    special(TryQuickSave)
    iffalse(DidNotSave)
    writetext(Text_PleaseWait)
    special(CheckLinkTimeout_Receptionist)
    iffalse(LinkTimedOut)
    readmem(&wram->wOtherPlayerLinkMode)
    iffalse(OK)
    special(CheckBothSelectedSameRoom)
    writetext(Text_IncompatibleRooms)
    special(CloseLink)
    closetext
    s_end
OK:
    special(EnterTimeCapsule)
    writetext(Text_PleaseComeIn)
    waitbutton
    closetext
    scall(TimeCapsuleScript_CheckPlayerGender)
    warpcheck
    s_end
FriendNotReady:
    special(WaitForOtherPlayerToExit)
    writetext(YourFriendIsNotReadyText)
    closetext
    s_end
LinkTimedOut:
    writetext(Text_LinkTimedOut)
    goto Cancel;
DidNotSave:
    writetext(Text_PleaseComeAgain)
Cancel:
    special(WaitForOtherPlayerToExit)
    closetext
    s_end
MonTooNew:
    writetext(Text_RejectNewMon)
    closetext
    s_end
MonMoveTooNew:
    writetext(Text_RejectMonWithNewMove)
    closetext
    s_end
MonHasMail:
    writetext(Text_RejectMonWithMail)
    closetext
    s_end
    SCRIPT_END
}
bool Script_LeftCableTradeCenter(script_s* s) {
    SCRIPT_BEGIN
    special(WaitForOtherPlayerToExit)
    scall(Script_WalkOutOfLinkTradeRoom)
    setscene(SCENE_DEFAULT)
    setmapscene(TRADE_CENTER, SCENE_DEFAULT)
    s_end
    SCRIPT_END
}
bool Script_LeftMobileTradeRoom(script_s* s) {
    SCRIPT_BEGIN
    special(Function101220)
    scall(Script_WalkOutOfMobileTradeRoom)
    setscene(SCENE_DEFAULT)
    setmapscene(MOBILE_TRADE_ROOM, SCENE_DEFAULT)
    s_end
    SCRIPT_END
}
bool Script_WalkOutOfMobileTradeRoom(script_s* s) {
    SCRIPT_BEGIN
    applymovement(POKECENTER2F_TRADE_RECEPTIONIST, Pokecenter2FMobileMovementData_ReceptionistWalksUpAndLeft)
    applymovement(PLAYER, Pokecenter2FMovementData_PlayerWalksOutOfMobileRoom)
    applymovement(POKECENTER2F_TRADE_RECEPTIONIST, Pokecenter2FMobileMovementData_ReceptionistWalksRightAndDown)
    s_end
    SCRIPT_END
}
bool Script_LeftCableColosseum(script_s* s) {
    SCRIPT_BEGIN
    special(WaitForOtherPlayerToExit)
    scall(Script_WalkOutOfLinkBattleRoom)
    setscene(SCENE_DEFAULT)
    setmapscene(COLOSSEUM, SCENE_DEFAULT)
    s_end
    SCRIPT_END
}
bool Script_LeftMobileBattleRoom(script_s* s) {
    SCRIPT_BEGIN
    special(Function101220)
    scall(Script_WalkOutOfMobileBattleRoom)
    setscene(SCENE_DEFAULT)
    setmapscene(MOBILE_BATTLE_ROOM, SCENE_DEFAULT)
    s_end
    SCRIPT_END
}
bool Script_WalkOutOfMobileBattleRoom(script_s* s) {
    SCRIPT_BEGIN
    applymovement(POKECENTER2F_BATTLE_RECEPTIONIST, Pokecenter2FMobileMovementData_ReceptionistWalksUpAndLeft)
    applymovement(PLAYER, Pokecenter2FMovementData_PlayerWalksOutOfMobileRoom)
    applymovement(POKECENTER2F_BATTLE_RECEPTIONIST, Pokecenter2FMobileMovementData_ReceptionistWalksRightAndDown)
    s_end
    SCRIPT_END
}
bool Pokecenter2F_CheckGender(script_s* s) {
    SCRIPT_BEGIN
    checkflag(ENGINE_PLAYER_IS_FEMALE)
    iftrue(Female)
    // applymovementlasttalked(Pokecenter2FMovementData_ReceptionistWalksUpAndLeft_LookRight)
    applymovementlasttalked(Pokecenter2FMovementData_ReceptionistWalksUpAndRight_LookLeft)
    // applymovement(PLAYER, Pokecenter2FMovementData_PlayerTakesThreeStepsUp)
    applymovement(PLAYER, Pokecenter2FMobileMovementData_PlayerWalksIntoCableRoom)
    s_end
Female:
    // applymovementlasttalked(Pokecenter2FMovementData_ReceptionistWalksUpAndLeft_LookRight_2)
    applymovementlasttalked(Pokecenter2FMovementData_ReceptionistWalksUpAndRight_LookLeft)
    applymovement(PLAYER, Pokecenter2FMovementData_PlayerTakesTwoStepsUp)
    opentext
    writetext(Text_OhPleaseWait)
    waitbutton
    closetext
    // applymovementlasttalked(Pokecenter2FMovementData_ReceptionistLooksRight)
    // turnobject(PLAYER, LEFT)
    applymovementlasttalked(Pokecenter2FMovementData_ReceptionistLooksLeft)
    turnobject(PLAYER, RIGHT)
    opentext
    writetext(Text_ChangeTheLook)
    waitbutton
    closetext
    playsound(SFX_TINGLE)
    // applymovement(PLAYER, Pokecenter2FMovementData_PlayerSpinsClockwiseEndsFacingRight)
    applymovement(PLAYER, Pokecenter2FMovementData_PlayerSpinsClockwiseEndsFacingLeft)
    setval((PAL_NPC_RED << 4))
    special(SetPlayerPalette)
    // applymovement(PLAYER, Pokecenter2FMovementData_PlayerSpinsClockwiseEndsFacingLeft)
    applymovement(PLAYER, Pokecenter2FMovementData_PlayerSpinsClockwiseEndsFacingRight)
    setflag(ENGINE_KRIS_IN_CABLE_CLUB)
    special(UpdatePlayerSprite)
    opentext
    writetext(Text_LikeTheLook)
    waitbutton
    closetext
    showemote(EMOTE_SHOCK, PLAYER, 15)
    // applymovement(PLAYER, Pokecenter2FMovementData_PlayerTakesOneStepUp)
    applymovement(PLAYER, Pokecenter2FMovementData_PlayerTakesOneStepLeftOneStepUp_2)
    s_end
    SCRIPT_END
}
bool Script_WalkOutOfLinkTradeRoom(script_s* s) {
    SCRIPT_BEGIN
    checkflag(ENGINE_KRIS_IN_CABLE_CLUB)
    iftrue(Female)
    // applymovement(POKECENTER2F_TRADE_RECEPTIONIST, Pokecenter2FMovementData_ReceptionistStepsRightLooksDown_3)
    // applymovement(PLAYER, Pokecenter2FMovementData_PlayerTakesThreeStepsDown)
    // applymovement(POKECENTER2F_TRADE_RECEPTIONIST, Pokecenter2FMovementData_ReceptionistStepsRightAndDown)
    applymovement(POKECENTER2F_TRADE_RECEPTIONIST, Pokecenter2FMobileMovementData_ReceptionistWalksUpAndRight)
    applymovement(PLAYER, Pokecenter2FMovementData_PlayerWalksOutOfCableRoom)
    applymovement(POKECENTER2F_TRADE_RECEPTIONIST, Pokecenter2FMobileMovementData_ReceptionistWalksLeftAndDown)
    s_end
Female:
    // applymovement(POKECENTER2F_TRADE_RECEPTIONIST, Pokecenter2FMovementData_ReceptionistStepsRightLooksDown_3)
    applymovement(POKECENTER2F_TRADE_RECEPTIONIST, Pokecenter2FMobileMovementData_ReceptionistWalksUpAndRight)
    applymovement(PLAYER, Pokecenter2FMovementData_PlayerTakesOneStepDown_2)
    clearflag(ENGINE_KRIS_IN_CABLE_CLUB)
    playsound(SFX_TINGLE)
    applymovement(PLAYER, Pokecenter2FMovementData_PlayerSpinsClockwiseEndsFacingRight)
    setval((PAL_NPC_BLUE << 4))
    special(SetPlayerPalette)
    applymovement(PLAYER, Pokecenter2FMovementData_PlayerSpinsClockwiseEndsFacingLeft)
    special(UpdatePlayerSprite)
    // applymovement(PLAYER, Pokecenter2FMovementData_PlayerTakesTwoStepsDown_2)
    applymovement(PLAYER, Pokecenter2FMovementData_PlayerTakesOneStepRightTwoStepsDown_2)
    // applymovement(POKECENTER2F_TRADE_RECEPTIONIST, Pokecenter2FMovementData_ReceptionistStepsRightAndDown)
    applymovement(POKECENTER2F_TRADE_RECEPTIONIST, Pokecenter2FMobileMovementData_ReceptionistWalksLeftAndDown)
    s_end
    SCRIPT_END
}
bool Script_WalkOutOfLinkBattleRoom(script_s* s) {
    SCRIPT_BEGIN
    checkflag(ENGINE_KRIS_IN_CABLE_CLUB)
    iftrue(Female)
    // applymovement(POKECENTER2F_BATTLE_RECEPTIONIST, Pokecenter2FMovementData_ReceptionistStepsRightLooksDown_3)
    // applymovement(PLAYER, Pokecenter2FMovementData_PlayerTakesThreeStepsDown)
    // applymovement(POKECENTER2F_BATTLE_RECEPTIONIST, Pokecenter2FMovementData_ReceptionistStepsRightAndDown)
    applymovement(POKECENTER2F_BATTLE_RECEPTIONIST, Pokecenter2FMobileMovementData_ReceptionistWalksUpAndRight)
    applymovement(PLAYER, Pokecenter2FMovementData_PlayerWalksOutOfCableRoom)
    applymovement(POKECENTER2F_BATTLE_RECEPTIONIST, Pokecenter2FMobileMovementData_ReceptionistWalksLeftAndDown)
    s_end
Female:
    // applymovement(POKECENTER2F_BATTLE_RECEPTIONIST, Pokecenter2FMovementData_ReceptionistStepsRightLooksDown_3)
    applymovement(POKECENTER2F_BATTLE_RECEPTIONIST, Pokecenter2FMobileMovementData_ReceptionistWalksUpAndRight)
    applymovement(PLAYER, Pokecenter2FMovementData_PlayerTakesOneStepDown_2)
    clearflag(ENGINE_KRIS_IN_CABLE_CLUB)
    playsound(SFX_TINGLE)
    applymovement(PLAYER, Pokecenter2FMovementData_PlayerSpinsClockwiseEndsFacingRight)
    setval((PAL_NPC_BLUE << 4))
    special(SetPlayerPalette)
    applymovement(PLAYER, Pokecenter2FMovementData_PlayerSpinsClockwiseEndsFacingLeft)
    special(UpdatePlayerSprite)
    // applymovement(PLAYER, Pokecenter2FMovementData_PlayerTakesTwoStepsDown_2)
    applymovement(PLAYER, Pokecenter2FMovementData_PlayerTakesOneStepRightTwoStepsDown_2)
    // applymovement(POKECENTER2F_BATTLE_RECEPTIONIST, Pokecenter2FMovementData_ReceptionistStepsRightAndDown)
    applymovement(POKECENTER2F_BATTLE_RECEPTIONIST, Pokecenter2FMobileMovementData_ReceptionistWalksLeftAndDown)
    s_end
    SCRIPT_END
}
bool TimeCapsuleScript_CheckPlayerGender(script_s* s) {
    SCRIPT_BEGIN
    checkflag(ENGINE_PLAYER_IS_FEMALE)
    iftrue(Female)
    readvar(VAR_FACING)
    ifequal(LEFT, MaleFacingLeft)
    ifequal(RIGHT, MaleFacingRight)
    applymovementlasttalked(Pokecenter2FMovementData_ReceptionistStepsLeftLooksDown)
    applymovement(PLAYER, Pokecenter2FMovementData_PlayerTakesTwoStepsUp_2)
    s_end
MaleFacingLeft:
    applymovementlasttalked(Pokecenter2FMovementData_ReceptionistStepsLeftLooksDown)
    applymovement(PLAYER, Pokecenter2FMovementData_PlayerWalksLeftAndUp)
    s_end
MaleFacingRight:
    applymovementlasttalked(Pokecenter2FMovementData_ReceptionistStepsRightLooksDown)
    applymovement(PLAYER, Pokecenter2FMovementData_PlayerWalksRightAndUp)
    s_end
Female:
    readvar(VAR_FACING)
    ifequal(RIGHT, FemaleFacingRight)
    ifequal(LEFT, FemaleFacingLeft)
    applymovementlasttalked(Pokecenter2FMovementData_ReceptionistStepsLeftLooksRight_2)
    applymovement(PLAYER, Pokecenter2FMovementData_PlayerTakesOneStepUp_2)
    goto FemaleContinue;
FemaleFacingRight:
    applymovementlasttalked(Pokecenter2FMovementData_ReceptionistStepsRightLooksLeft_2)
    applymovement(PLAYER, Pokecenter2FMovementData_PlayerTakesOneStepRight)
    goto FemaleContinue;
FemaleFacingLeft:
    applymovementlasttalked(Pokecenter2FMovementData_ReceptionistStepsLeftLooksRight_2)
    applymovement(PLAYER, Pokecenter2FMovementData_PlayerTakesOneStepLeft)
FemaleContinue:
    opentext
    writetext(Text_OhPleaseWait)
    waitbutton
    closetext
    readvar(VAR_FACING)
    ifnotequal(UP, FemaleChangeApperance)
    turnobject(PLAYER, LEFT)
FemaleChangeApperance:
    opentext
    writetext(Text_ChangeTheLook)
    waitbutton
    closetext
    playsound(SFX_TINGLE)
    applymovement(PLAYER, Pokecenter2FMovementData_PlayerSpinsClockwiseEndsFacingRight)
    setval((PAL_NPC_RED << 4))
    special(SetPlayerPalette)
    applymovement(PLAYER, Pokecenter2FMovementData_PlayerSpinsClockwiseEndsFacingDown)
    faceobject(PLAYER, POKECENTER2F_TIME_CAPSULE_RECEPTIONIST)
    setflag(ENGINE_KRIS_IN_CABLE_CLUB)
    special(UpdatePlayerSprite)
    opentext
    writetext(Text_LikeTheLook)
    waitbutton
    closetext
    showemote(EMOTE_SHOCK, PLAYER, 15)
    applymovement(PLAYER, Pokecenter2FMovementData_PlayerTakesOneStepUp_2)
    s_end
    SCRIPT_END
}
bool Script_LeftTimeCapsule(script_s* s) {
    SCRIPT_BEGIN
    special(WaitForOtherPlayerToExit)
    checkflag(ENGINE_KRIS_IN_CABLE_CLUB)
    iftrue(Female)
    applymovement(POKECENTER2F_TIME_CAPSULE_RECEPTIONIST, Pokecenter2FMovementData_ReceptionistStepsLeftLooksRight)
    applymovement(PLAYER, Pokecenter2FMovementData_PlayerTakesTwoStepsDown)
    applymovement(POKECENTER2F_TIME_CAPSULE_RECEPTIONIST, Pokecenter2FMovementData_ReceptionistStepsRightLooksDown_2)
    goto Done;
Female:
    applymovement(POKECENTER2F_TIME_CAPSULE_RECEPTIONIST, Pokecenter2FMovementData_ReceptionistStepsLeftLooksRight)
    applymovement(PLAYER, Pokecenter2FMovementData_PlayerTakesOneStepDown)
    clearflag(ENGINE_KRIS_IN_CABLE_CLUB)
    playsound(SFX_TINGLE)
    applymovement(PLAYER, Pokecenter2FMovementData_PlayerSpinsClockwiseEndsFacingRight)
    setval((PAL_NPC_BLUE << 4))
    special(SetPlayerPalette)
    applymovement(PLAYER, Pokecenter2FMovementData_PlayerSpinsClockwiseEndsFacingLeft)
    special(UpdatePlayerSprite)
    applymovement(PLAYER, Pokecenter2FMovementData_PlayerTakesOneStepDown)
    applymovement(POKECENTER2F_TIME_CAPSULE_RECEPTIONIST, Pokecenter2FMovementData_ReceptionistStepsRightLooksDown_2)
Done:
    setscene(SCENE_DEFAULT)
    setmapscene(TIME_CAPSULE, SCENE_DEFAULT)
    s_end
    SCRIPT_END
}
bool Pokecenter2FLinkRecordSign(script_s* s) {
    SCRIPT_BEGIN
    refreshscreen
    special(DisplayLinkRecord)
    closetext
    s_end
    SCRIPT_END
}
bool Pokecenter2FOfficerScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_MYSTERY_GIFT_DELIVERY_GUY)
    iftrue(AlreadyGotGift)
    writetext(Text_MysteryGiftDeliveryGuy_Intro)
    yesorno
    iffalse(RefusedGift)
    writetext(Text_MysteryGiftDeliveryGuy_HereYouGo)
    promptbutton
    waitsfx
    special(GetMysteryGiftItem)
    iffalse(BagIsFull)
    itemnotify
    setevent(EVENT_MYSTERY_GIFT_DELIVERY_GUY)
AlreadyGotGift:
    writetext(Text_MysteryGiftDeliveryGuy_Outro)
    waitbutton
    closetext
    s_end
BagIsFull:
    writetext(Text_MysteryGiftDeliveryGuy_NoRoom)
    waitbutton
    closetext
    s_end
RefusedGift:
    writetext(Text_MysteryGiftDeliveryGuy_SaidNo)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const uint8_t Pokecenter2FMovementData_ReceptionistWalksUpAndLeft_LookRight[] = {
    slow_step(UP),
    slow_step(LEFT),
    turn_head(RIGHT),
    movement_step_end,
};
const uint8_t Pokecenter2FMovementData_ReceptionistWalksUpAndRight_LookLeft[] = {
    slow_step(UP),
    slow_step(RIGHT),
    turn_head(LEFT),
    movement_step_end,
};
const uint8_t Pokecenter2FMobileMobileMovementData_ReceptionistWalksUpAndLeft_LookDown[] = {
    slow_step(UP),
    slow_step(LEFT),
    turn_head(DOWN),
    movement_step_end,
};
const uint8_t Pokecenter2FMovementData_ReceptionistStepsLeftLooksDown[] = {
    slow_step(LEFT),
    turn_head(DOWN),
    movement_step_end,
};
const uint8_t Pokecenter2FMovementData_ReceptionistStepsRightLooksDown[] = {
    slow_step(RIGHT),
    turn_head(DOWN),
    movement_step_end,
};
const uint8_t Pokecenter2FMovementData_ReceptionistWalksUpAndLeft_LookRight_2[] = {
    slow_step(UP),
    slow_step(LEFT),
    turn_head(RIGHT),
    movement_step_end,
};
const uint8_t Pokecenter2FMovementData_ReceptionistLooksRight[] = {
    turn_head(RIGHT),
    movement_step_end,
};
const uint8_t Pokecenter2FMovementData_ReceptionistLooksLeft[] = {
    turn_head(RIGHT),
    movement_step_end,
};
const uint8_t Pokecenter2FMovementData_PlayerTakesThreeStepsUp[] = {
    step(UP),
    step(UP),
    step(UP),
    movement_step_end,
};
const uint8_t Pokecenter2FMovementData_PlayerTakesTwoStepsUp[] = {
    step(UP),
    step(UP),
    movement_step_end,
};
const uint8_t Pokecenter2FMovementData_PlayerTakesOneStepUp[] = {
    step(UP),
    movement_step_end,
};
const uint8_t Pokecenter2FMobileMovementData_PlayerWalksIntoMobileBattleRoom[] = {
    step(UP),
    step(UP),
    step(RIGHT),
    step(UP),
    movement_step_end,
};
const uint8_t Pokecenter2FMobileMovementData_PlayerWalksIntoCableRoom[] = {
    step(UP),
    step(UP),
    step(LEFT),
    step(UP),
    movement_step_end,
};
const uint8_t Pokecenter2FMovementData_PlayerTakesTwoStepsUp_2[] = {
    step(UP),
    step(UP),
    movement_step_end,
};
const uint8_t Pokecenter2FMovementData_PlayerWalksLeftAndUp[] = {
    step(LEFT),
    step(UP),
    movement_step_end,
};
const uint8_t Pokecenter2FMovementData_PlayerWalksRightAndUp[] = {
    step(RIGHT),
    step(UP),
    movement_step_end,
};
const uint8_t Pokecenter2FMovementData_PlayerTakesThreeStepsDown[] = {
    step(DOWN),
    step(DOWN),
    step(DOWN),
    movement_step_end,
};
const uint8_t Pokecenter2FMovementData_PlayerTakesTwoStepsDown[] = {
    step(DOWN),
    step(DOWN),
    movement_step_end,
};
const uint8_t Pokecenter2FMovementData_PlayerTakesOneStepDown[] = {
    step(DOWN),
    movement_step_end,
};
const uint8_t Pokecenter2FMovementData_ReceptionistStepsRightAndDown[] = {
    slow_step(RIGHT),
    slow_step(DOWN),
    movement_step_end,
};
const uint8_t Pokecenter2FMovementData_ReceptionistStepsRightLooksDown_2[] = {
    slow_step(RIGHT),
    turn_head(DOWN),
    movement_step_end,
};
const uint8_t Pokecenter2FMovementData_ReceptionistStepsRightLooksDown_3[] = {
    slow_step(UP),
    slow_step(LEFT),
    turn_head(RIGHT),
    movement_step_end,
};
const uint8_t Pokecenter2FMovementData_ReceptionistStepsLeftLooksRight[] = {
    slow_step(LEFT),
    turn_head(RIGHT),
    movement_step_end,
};
const uint8_t Pokecenter2FMobileMovementData_ReceptionistWalksUpAndLeft[] = {
    slow_step(UP),
    slow_step(LEFT),
    turn_head(RIGHT),
    movement_step_end,
};
const uint8_t Pokecenter2FMovementData_PlayerWalksOutOfMobileRoom[] = {
    step(DOWN),
    step(LEFT),
    step(DOWN),
    step(DOWN),
    movement_step_end,
};
const uint8_t Pokecenter2FMobileMovementData_ReceptionistWalksRightAndDown[] = {
    slow_step(RIGHT),
    slow_step(DOWN),
    movement_step_end,
};
const uint8_t Pokecenter2FMobileMovementData_ReceptionistWalksUpAndRight[] = {
    slow_step(UP),
    slow_step(RIGHT),
    turn_head(LEFT),
    movement_step_end,
};
const uint8_t Pokecenter2FMovementData_PlayerWalksOutOfCableRoom[] = {
    step(DOWN),
    step(RIGHT),
    step(DOWN),
    step(DOWN),
    movement_step_end,
};
const uint8_t Pokecenter2FMobileMovementData_ReceptionistWalksLeftAndDown[] = {
    slow_step(LEFT),
    slow_step(DOWN),
    movement_step_end,
};
const uint8_t Pokecenter2FMovementData_PlayerSpinsClockwiseEndsFacingRight[] = {
    turn_head(DOWN),
    turn_head(LEFT),
    turn_head(UP),
    turn_head(RIGHT),
    movement_step_end,
};
const uint8_t Pokecenter2FMovementData_PlayerSpinsClockwiseEndsFacingLeft[] = {
    turn_head(DOWN),
    turn_head(LEFT),
    turn_head(UP),
    turn_head(RIGHT),
    turn_head(LEFT),
    movement_step_end,
};
const uint8_t Pokecenter2FMovementData_PlayerSpinsClockwiseEndsFacingDown[] = {
    turn_head(DOWN),
    turn_head(LEFT),
    turn_head(UP),
    turn_head(RIGHT),
    turn_head(DOWN),
    movement_step_end,
};
const uint8_t Pokecenter2FMovementData_PlayerTakesOneStepDown_2[] = {
    step(DOWN),
    movement_step_end,
};
const uint8_t Pokecenter2FMovementData_PlayerTakesTwoStepsDown_2[] = {
    step(DOWN),
    step(DOWN),
    movement_step_end,
};
const uint8_t Pokecenter2FMovementData_PlayerTakesOneStepRightTwoStepsDown_2[] = {
    step(RIGHT),
    step(DOWN),
    step(DOWN),
    movement_step_end,
};
const uint8_t Pokecenter2FMovementData_PlayerTakesOneStepLeftOneStepUp_2[] = {
    step(LEFT),
    step(UP),
    movement_step_end,
};
const uint8_t Pokecenter2FMovementData_PlayerTakesOneStepUp_2[] = {
    step(UP),
    movement_step_end,
};
const uint8_t Pokecenter2FMovementData_PlayerTakesOneStepRight[] = {
    step(RIGHT),
    movement_step_end,
};
const uint8_t Pokecenter2FMovementData_PlayerTakesOneStepLeft[] = {
    step(LEFT),
    movement_step_end,
};
const uint8_t Pokecenter2FMovementData_ReceptionistStepsLeftLooksRight_2[] = {
    slow_step(LEFT),
    turn_head(RIGHT),
    movement_step_end,
};
const uint8_t Pokecenter2FMovementData_ReceptionistStepsRightLooksLeft_2[] = {
    slow_step(RIGHT),
    turn_head(LEFT),
    movement_step_end,
};
const txt_cmd_s Text_BattleReceptionistMobile[] = {
    text_start("Would you like to"
        t_line "battle over a GAME"
        t_para "LINK cable or by"
        t_line "mobile phone?"
        t_done )
};
const txt_cmd_s Text_TradeReceptionistMobile[] = {
    text_start("Would you like to"
        t_line "trade over a GAME"
        t_para "LINK cable or by"
        t_line "mobile phone?"
        t_done )
};
const txt_cmd_s Text_ThisWayToMobileRoom[] = {
    text_start("This way to the"
        t_line "MOBILE ROOM."
        t_done )
};
const txt_cmd_s Text_BattleReceptionistIntro[] = {
    text_start("Welcome to CABLE"
        t_line "CLUB COLOSSEUM."
        t_para "You may battle a"
        t_line "friend here."
        t_para "Would you like to"
        t_line "battle?"
        t_done )
};
const txt_cmd_s Text_TradeReceptionistIntro[] = {
    text_start("Welcome to CABLE"
        t_line "TRADE CENTER."
        t_para "You may trade your"
        t_line "#MON here with"
        t_cont "a friend."
        t_para "Would you like to"
        t_line "trade?"
        t_done )
};
const txt_cmd_s Text_TimeCapsuleReceptionistIntro[] = {
    text_start("Welcome to CABLE"
        t_line "CLUB TIME CAPSULE."
        t_para "You can travel to"
        t_line "the past and trade"
        t_cont "your #MON."
        t_para "Would you like to"
        t_line "trade across time?"
        t_done )
};
const txt_cmd_s YourFriendIsNotReadyText[] = {
    text_start("Your friend is not"
        t_line "ready."
        t_prompt )
};
const txt_cmd_s Text_MustSaveGame[] = {
    text_start("Before opening the"
        t_line "link, you must"
        t_cont "save your game."
        t_done )
};
const txt_cmd_s Text_PleaseWait[] = {
    text_start("Please wait."
        t_done )
};
const txt_cmd_s Text_LinkTimedOut[] = {
    text_start("The link has been"
        t_line "closed because of"
        t_cont "inactivity."
        t_para "Please contact"
        t_line "your friend and"
        t_cont "come again."
        t_prompt )
};
const txt_cmd_s Text_PleaseComeAgain[] = {
    text_start("Please come again."
        t_prompt )
};
const txt_cmd_s Text_PleaseComeInDuplicate[] = {
    text_start("Please come in."
        t_prompt )
};
const txt_cmd_s Text_TemporaryStagingInLinkRoom[] = {
    text_start("We'll put you in"
        t_line "the link room for"
        t_cont "the time being."
        t_done )
};
const txt_cmd_s Text_CantLinkToThePast[] = {
    text_start("You can't link to"
        t_line "the past here."
        t_prompt )
};
const txt_cmd_s Text_IncompatibleRooms[] = {
    text_start("Incompatible rooms"
        t_line "were chosen."
        t_prompt )
};
const txt_cmd_s Text_PleaseComeIn[] = {
    text_start("Please come in."
        t_done )
};
const txt_cmd_s Text_PleaseEnter[] = {
    text_start("Please enter."
        t_prompt )
};
const txt_cmd_s Text_RejectNewMon[] = {
    text_start("Sorry--@")
    text_ram(wram_ptr(wStringBuffer1))
    text_start(
        t_line "can't be taken."
        t_prompt )
};
const txt_cmd_s Text_RejectMonWithNewMove[] = {
    text_start("You can't take the"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer1))
    text_start(" with a"
        t_cont "@")
    text_ram(wram_ptr(wStringBuffer2))
    text_start("."
        t_prompt )
};
const txt_cmd_s Text_RejectMonWithMail[] = {
    text_start("You can't take the"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer1))
    text_start(" that"
        t_cont "has MAIL with you."
        t_prompt )
};
const txt_cmd_s Text_TimeCapsuleClosed[] = {
    text_start("I'm sorry--the"
        t_line "TIME CAPSULE is"
        t_cont "being adjusted."
        t_done )
};
const txt_cmd_s Text_TradeRoomClosed[] = {
    text_start("I'm sorry--the"
        t_line "TRADE MACHINE is"
        t_cont "being adjusted."
        t_done )
};
const txt_cmd_s Text_BattleRoomClosed[] = {
    text_start("I'm sorry--the"
        t_line "BATTLE MACHINE is"
        t_cont "being adjusted."
        t_done )
};
const txt_cmd_s Text_MysteryGiftDeliveryGuy_Intro[] = {
    text_start("Hello! You're"
        t_line "<PLAYER>, right?"
        t_para "I have some-"
        t_line "thing for you."
        t_done )
};
const txt_cmd_s Text_MysteryGiftDeliveryGuy_HereYouGo[] = {
    text_start("Here you go!"
        t_done )
};
const txt_cmd_s Text_MysteryGiftDeliveryGuy_Outro[] = {
    text_start("We hope to serve"
        t_line "you again."
        t_done )
};
const txt_cmd_s Text_MysteryGiftDeliveryGuy_NoRoom[] = {
    text_start("Oh, you have no"
        t_line "space for this."
        t_para "Stop in at any"
        t_line "#MON CENTER"
        t_para "across the country"
        t_line "to pick it up."
        t_done )
};
const txt_cmd_s Text_MysteryGiftDeliveryGuy_SaidNo[] = {
    text_start("No? That's very"
        t_line "strange…"
        t_done )
};
const txt_cmd_s Text_OhPleaseWait[] = {
    text_start("Oh, please wait."
        t_done )
};
const txt_cmd_s Text_ChangeTheLook[] = {
    text_start("We need to change"
        t_line "the look here…"
        t_done )
};
const txt_cmd_s Text_LikeTheLook[] = {
    text_start("How does this"
        t_line "style look to you?"
        t_done )
};
const txt_cmd_s Text_BrokeStadiumRules[] = {
    text_start("Excuse me!"
        t_para "For STADIUM rules,"
        t_line "please bring six"
        t_para "different #MON,"
        t_line "excluding EGGS."
        t_para "The six #MON"
        t_line "must be different."
        t_para "Also, they must"
        t_line "not be holding"
        t_cont "identical items."
        t_para "Please come back"
        t_line "when you're ready."
        t_done )
    //db(0, 0) // filler
};
