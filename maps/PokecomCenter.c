#include "../constants.h"
#include "../util/scripting.h"
#include "PokecomCenter.h"
//// EVENTS
enum {
    GOLDENRODPOKECENTER1F_NURSE = 2,
    GOLDENRODPOKECENTER1F_LINK_RECEPTIONIST,
    GOLDENRODPOKECENTER1F_SUPER_NERD,
    GOLDENRODPOKECENTER1F_GAMEBOY_KID,
    GOLDENRODPOKECENTER1F_LASS,
    GOLDENRODPOKECENTER1F_POKEFAN_F,
    GOLDENRODPOKECENTER1F_LASS2,
    GOLDENRODPOKECENTER1F_YOUNGSTER,
    GOLDENRODPOKECENTER1F_TEACHER,
    GOLDENRODPOKECENTER1F_ROCKER,
    GOLDENRODPOKECENTER1F_GRAMPS,
};

const Script_fn_t PokecomCenter_SceneScripts[] = {
    PokecomCenter_MapScripts_Scene0 , //  SCENE_DEFAULT,
    PokecomCenter_MapScripts_Scene0 , //  SCENE_DEFAULT,
};

const struct MapCallback PokecomCenter_MapCallbacks[] = {
    map_callback(MAPCALLBACK_OBJECTS, GoldenrodPokecenter1F_prepareMap),
};

const struct MapScripts PokecomCenter_MapScripts = {
    .scene_script_count = lengthof(PokecomCenter_SceneScripts),
    .scene_scripts = PokecomCenter_SceneScripts,

    .callback_count = lengthof(PokecomCenter_MapCallbacks),
    .callbacks = PokecomCenter_MapCallbacks,
};

static const struct CoordEvent PokecomCenter_CoordEvents[] = {
    coord_event(6, 15, SCENE_DEFAULT, &GoldenrodPokecenter1F_GSBallSceneLeft),
    coord_event(7, 15, SCENE_DEFAULT, &GoldenrodPokecenter1F_GSBallSceneRight),
};

static const struct BGEvent PokecomCenter_BGEvents[] = {
    bg_event(24, 5, BGEVENT_READ, &GoldenrodPokecenter1F_NewsMachineScript),
    bg_event(24, 6, BGEVENT_READ, &GoldenrodPokecenter1F_NewsMachineScript),
    bg_event(24, 7, BGEVENT_READ, &GoldenrodPokecenter1F_NewsMachineScript),
    bg_event(24, 9, BGEVENT_READ, &GoldenrodPokecenter1F_NewsMachineScript),
    bg_event(24, 10, BGEVENT_READ, &GoldenrodPokecenter1F_NewsMachineScript),
    bg_event(25, 11, BGEVENT_READ, &GoldenrodPokecenter1F_NewsMachineScript),
    bg_event(26, 11, BGEVENT_READ, &GoldenrodPokecenter1F_NewsMachineScript),
    bg_event(27, 11, BGEVENT_READ, &GoldenrodPokecenter1F_NewsMachineScript),
    bg_event(28, 11, BGEVENT_READ, &GoldenrodPokecenter1F_NewsMachineScript),
    bg_event(29, 5, BGEVENT_READ, &GoldenrodPokecenter1F_NewsMachineScript),
    bg_event(29, 6, BGEVENT_READ, &GoldenrodPokecenter1F_NewsMachineScript),
    bg_event(29, 7, BGEVENT_READ, &GoldenrodPokecenter1F_NewsMachineScript),
    bg_event(29, 8, BGEVENT_READ, &GoldenrodPokecenter1F_NewsMachineScript),
    bg_event(29, 9, BGEVENT_READ, &GoldenrodPokecenter1F_NewsMachineScript),
    bg_event(29, 10, BGEVENT_READ, &GoldenrodPokecenter1F_NewsMachineScript),
    bg_event(2, 9, BGEVENT_UP, &PokeComCenterInfoSign),
};

static const struct WarpEventData PokecomCenter_WarpEvents[] = {
    warp_event(6, 15, GOLDENROD_CITY, 15),
    warp_event(7, 15, GOLDENROD_CITY, 15),
    warp_event(0, 6, POKECOM_CENTER_ADMIN_OFFICE_MOBILE, 1),
    warp_event(0, 15, POKECENTER_2F, 1),
};

static const struct ObjEvent PokecomCenter_ObjectEvents[] = {
    object_event(7, 7, SPRITE_NURSE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &GoldenrodPokecenter1FNurseScript, -1),
    object_event(16, 8, SPRITE_LINK_RECEPTIONIST, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &GoldenrodPokecenter1FTradeCornerAttendantScript, -1),
    object_event(13, 5, SPRITE_SUPER_NERD, SPRITEMOVEDATA_WALK_UP_DOWN, 16, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &GoldenrodPokecenter1FSuperNerdScript, -1),
    object_event(11, 12, SPRITE_GAMEBOY_KID, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &GoldenrodPokecenter1FGameboyKidScript, -1),
    object_event(4, 11, SPRITE_LASS, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &GoldenrodPokecenter1FLassScript, -1),
    object_event(15, 12, SPRITE_POKEFAN_F, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, &GoldenrodPokecenter1FPokefanF, -1),
    object_event(18, 9, SPRITE_LASS, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &GoldenrodPokecenter1FLass2Script, -1),
    object_event(23, 8, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &GoldenrodPokecenter1FYoungsterScript, -1),
    object_event(30, 9, SPRITE_TEACHER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &GoldenrodPokecenter1FTeacherScript, -1),
    object_event(30, 5, SPRITE_ROCKER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &GoldenrodPokecenter1FRockerScript, -1),
    object_event(19, 14, SPRITE_GRAMPS, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &GoldenrodPokecenter1FGrampsScript, -1),
};

const struct MapEvents PokecomCenter_MapEvents = {
    .warp_event_count = lengthof(PokecomCenter_WarpEvents),
    .warp_events = PokecomCenter_WarpEvents,

    .coord_event_count = lengthof(PokecomCenter_CoordEvents),
    .coord_events = PokecomCenter_CoordEvents,

    .bg_event_count = lengthof(PokecomCenter_BGEvents),
    .bg_events = PokecomCenter_BGEvents,

    .obj_event_count = lengthof(PokecomCenter_ObjectEvents),
    .obj_events = PokecomCenter_ObjectEvents,
};

//// CODE

bool PokecomCenter_MapScripts_Scene0(script_s* s) {
    SCRIPT_BEGIN
    s_end
    setval(BATTLETOWERACTION_10) // 5671d checks if a trade was made
    special(BattleTowerAction)
    iffalse_jump(GoldenrodPokecenter1F_noTrade) //$2967
    sdefer(GoldenrodPokecenter1F_scenejmp01) //$6F68 reveiced pokemon from trade corner dialogue
    s_end
    SCRIPT_END
}
bool GoldenrodPokecenter1F_scenejmp01(script_s* s) { // ???:
    SCRIPT_BEGIN
    setscene(0x01) //5686F
    refreshscreen
    writetext(GoldenrodPokecomCenterTradePartnerHasBeenFoundText) //$C46C partner has been found
    promptbutton
    writetext(GoldenrodPokecomCenterItsYourNewPartnerText) //$E66C its your new partner
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool GoldenrodPokecenter1F_noTrade(script_s* s) {
    SCRIPT_BEGIN
    setval(BATTLETOWERACTION_EGGTICKET) // check if player received the odd egg or still has the egg ticket
    special(BattleTowerAction) // 5672b
    iffalse(notReceivedOddEgg) //$3467 still has egg ticket
    sdefer(GoldenrodPokecenter1F_scenejmp02) //$B568 received odd egg dialogue
notReceivedOddEgg:
    s_end
    SCRIPT_END
}
bool GoldenrodPokecenter1F_scenejmp02(script_s* s) { // 568B5:
    SCRIPT_BEGIN
    opentext
    sjump(GoldenrodPokecenter1FTradeCornerAttendantScript_receivedOddEgg) //$A968
    SCRIPT_END
}
bool GoldenrodPokecenter1F_prepareMap(script_s* s) {
    SCRIPT_BEGIN
    special(Mobile_DummyReturnFalse)
    iftrue(mobile) //$5067
    moveobject(GOLDENRODPOKECENTER1F_LASS2, 0x10, 0x09) // this is 71 in jp crystal???
    moveobject(GOLDENRODPOKECENTER1F_GRAMPS, 0x00, 0x07)
    moveobject(GOLDENRODPOKECENTER1F_SUPER_NERD, 0x08, 0x0D)
    moveobject(GOLDENRODPOKECENTER1F_TEACHER, 0x1B, 0x0D)
    moveobject(GOLDENRODPOKECENTER1F_ROCKER, 0x15, 0x06)
    s_endcallback // this is 8f in jp crystal
mobile:
    setevent(EVENT_UNUSED_37)
    s_endcallback
    SCRIPT_END
}
bool GoldenrodPokecenter1FNurseScript(script_s* s) {
    SCRIPT_BEGIN
    setevent(EVENT_WELCOMED_TO_POKECOM_CENTER)
    jumpstd(PokecenterNurseScript)
    SCRIPT_END
}
bool GoldenrodPokecenter1FTradeCornerAttendantScript(script_s* s) {
    SCRIPT_BEGIN
    special(SetBitsForLinkTradeRequest)
    opentext
    writetext(GoldenrodPokecomCenterWelcomeToTradeCornerText) //$2d6a
    promptbutton // 54 in jp crystal?
    checkitem(EGG_TICKET) // 56762 in jp crystal
    iftrue(playerHasEggTicket) //$7c68
    special(Function11b879) // $71 check save file?
    ifequal(0x01, pokemonInTradeCorner) //$F667
    ifequal(0x02, leftPokemonInTradeCornerRecently) //$6968
    readvar(VAR_PARTYCOUNT)
    ifequal(0x01, onlyHaveOnePokemon) //$CF67 ; 56772
    writetext(GoldenrodPokecomCenterWeMustHoldYourMonText) //$726A
    yesorno
    iffalse(playerCancelled) //$D567
    //
    writetext(GoldenrodPokecomCenterSaveBeforeTradeCornerText) //$756E well save
    yesorno
    iffalse(playerCancelled)
    special(TryQuickSave)
    iffalse(playerCancelled)
    writetext(GoldenrodPokecomCenterWhichMonToTradeText) //$8F6E which pokemon do you want to trade?
    waitbutton // 53 in jp crystal?
    special(BillsGrandfather) // $4D; 56792
    ifequal(0x00, playerCancelled) //$D567
    ifequal(0xFD, cantAcceptEgg) //$EA67
    ifgreater(0xFB, pokemonAbnormal) //$F067
    special(Function11ba38) // $7B check party pokemon fainted
    ifnotequal(0x00, cantTradeLastPokemon) //$E467
    writetext(GoldenrodPokecomCenterWhatMonDoYouWantText) //$9E6A what kind of pokemon do you want in return?
    waitbutton
    special(Function11ac3e)
    ifequal(0x00, playerCancelled) //$D567
    ifequal(0x02, tradePokemonNeverSeen) //$BB67
    writetext(GoldenrodPokecomCenterWeWillTradeYourMonForMonText) //$B96A ; 567B5
    goto tradePokemon;
tradePokemonNeverSeen:
    writetext(GoldenrodPokecomCenterWeWillTradeYourMonForNewText) //$1E6B
tradePokemon:
    special(Function11b444) // $6E create data to send?
    ifequal(0x0A, playerCancelled) //$D567
    ifnotequal(0x00, mobileError) //$DB67
    writetext(GoldenrodPokecomCenterYourMonHasBeenReceivedText) //$A86B pokemon received
    waitbutton
    closetext
    s_end
    //
onlyHaveOnePokemon:
    writetext(GoldenrodPokecomCenterYouHaveOnlyOneMonText) //$D76B only have 1 pokemon
    waitbutton
    closetext
    s_end
    //
playerCancelled:
    writetext(GoldenrodPokecomCenterWeHopeToSeeYouAgainText) //$0F6C hope to see you again
    waitbutton
    closetext
    s_end
    //
mobileError:
    special(BattleTowerMobileError) // $8B mobile error
    writetext(GoldenrodPokecomCenterTradeCanceledText) //$AA6E we must cancel the trade
    waitbutton
    closetext
    s_end
    //
cantTradeLastPokemon:
    writetext(GoldenrodPokecomCenterCantAcceptLastMonText) //$2C6C if we accept this pokemon what will you battle with
    waitbutton
    closetext
    s_end
    //
cantAcceptEgg:
    writetext(GoldenrodPokecomCenterCantAcceptEggText) // sorry but we cant accept an egg
    waitbutton
    closetext
    s_end
    //
pokemonAbnormal:
    writetext(GoldenrodPokecomCenterCantAcceptAbnormalMonText) //$6F6C pokemon appears to be abnormal
    waitbutton
    closetext
    s_end
    //
pokemonInTradeCorner:
    writetext(GoldenrodPokecomCenterSaveBeforeTradeCornerText) //$756E well save
    yesorno
    iffalse(playerCancelled) //$D567
    special(TryQuickSave)
    iffalse(playerCancelled) //$D567 ; 56800
    writetext(GoldenrodPokecomCenterAlreadyHoldingMonText) //$896C arent we holding a pokemon of yours?
    promptbutton
    readvar(VAR_PARTYCOUNT)
    ifequal(0x06, partyFull) //$3868
    writetext(GoldenrodPokecomCenterCheckingTheRoomsText) //$A56C well check the rooms
    special(Function11b5e8) // $6F connect
    ifequal(0x0A, playerCancelled) //$D567
    ifnotequal(0x00, mobileError) //$DB67
    setval(BATTLETOWERACTION_0F)
    special(BattleTowerAction) // 86 = BattleTowerAction
    ifequal(0x00, noTradePartnerFound) //$3E68 ; 56820
    ifequal(0x01, receivePokemon) //$2B68
    goto pokemonInTradeCornerForALongTime; //$5668
    //
receivePokemon:
    writetext(GoldenrodPokecomCenterTradePartnerHasBeenFoundText) //$C46C partner has been found
    promptbutton
    special(Function11b7e5) // $70 receive a pokemon animation?
    writetext(GoldenrodPokecomCenterItsYourNewPartnerText) //$E66C its your new partner
    waitbutton
    closetext
    s_end
partyFull:
    writetext(GoldenrodPokecomCenterYourPartyIsFullText) //$216D ; 56838
    waitbutton
    closetext
    s_end
noTradePartnerFound:
    writetext(GoldenrodPokecomCenterNoTradePartnerFoundText) //$576D ; 5683E nobody found. would you like your pkm back?
    yesorno
    iffalse(continueHoldingPokemon) //$6368
    special(Function11b920) // $72 something with mobile
    ifequal(0x0A, playerCancelled) //$D567
    ifnotequal(0x00, mobileError) //$DB67
    writetext(GoldenrodPokecomCenterReturnedYourMonText) //$8A6D we have returned your pokemon
    waitbutton
    closetext
    s_end
    //
pokemonInTradeCornerForALongTime:
    writetext(GoldenrodPokecomCenterYourMonIsLonelyText) //$9A6D ; 56856 you left your pkm for a long time
    promptbutton
    special(Function11b93b) // $73 something with mobile
    writetext(GoldenrodPokecenter1FWeHopeToSeeYouAgainText_2) //$016E
    waitbutton
    closetext
    s_end
    //
continueHoldingPokemon:
    writetext(GoldenrodPokecomCenterContinueToHoldYourMonText) //$176E;56863 well continue to hold pkm
    waitbutton
    closetext
    s_end
    //
leftPokemonInTradeCornerRecently:
    writetext(GoldenrodPokecomCenterRecentlyLeftYourMonText) //$306E ; 56869
    waitbutton
    closetext
    s_end
    //
playerHasEggTicket:
    writetext(GoldenrodPokecomCenterEggTicketText) //$CD6E ; 5687C
    waitbutton
    readvar(VAR_PARTYCOUNT)
    ifequal(0x06, partyFull) //$3868
    writetext(GoldenrodPokecomCenterOddEggBriefingText) //$106F
    waitbutton
    writetext(GoldenrodPokecomCenterSaveBeforeTradeCornerText) //$756E
    yesorno
    iffalse(playerCancelled) //$D567
    special(TryQuickSave)
    iffalse(playerCancelled) //$D567
    writetext(GoldenrodPokecomCenterPleaseWaitAMomentText) //$CC6F
    special(GiveOddEgg) // $7D download odd egg
    ifequal(0x0B, eggTicketExchangeNotRunning) //$AF68
    ifequal(0x0A, playerCancelled) //$D567
    ifnotequal(0x00, mobileError) //$DB67
    sjump(GoldenrodPokecenter1FTradeCornerAttendantScript_receivedOddEgg)
eggTicketExchangeNotRunning:
    writetext(GoldenrodPokecomCenterNoEggTicketServiceText) //$2270 ; 568AF
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool GoldenrodPokecenter1FTradeCornerAttendantScript_receivedOddEgg(script_s* s) {
    SCRIPT_BEGIN
    writetext(GoldenrodPokecomCenterHereIsYourOddEggText) //$E66F
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool GoldenrodPokecenter1F_NewsMachineScript(script_s* s) {
    SCRIPT_BEGIN
    special(Mobile_DummyReturnFalse) // 568B9
    iftrue(mobileEnabled)
    jumptext(GoldenrodPokecomCenterNewsMachineNotYetText) // not in operation yet
    //
mobileEnabled:
    opentext
    writetext(GoldenrodPokecomCenterNewsMachineText) // its a pokemon news machine
    promptbutton
    setval(BATTLETOWERACTION_14)
    special(BattleTowerAction)
    ifnotequal(0x00, skipExplanation)
    setval(BATTLETOWERACTION_15)
    special(BattleTowerAction) // battle tower action (set battle tower save file flags?)
    writetext(GoldenrodPokecomCenterNewsMachineExplanationText) // news machine tut
    waitbutton
skipExplanation:
    writetext(GoldenrodPokecomCenterSaveBeforeNewsMachineText) // well save
    yesorno
    iffalse(cancel)
    special(TryQuickSave)
    iffalse(cancel)
    setval(BATTLETOWERACTION_15)
    special(BattleTowerAction) // battle tower action (set battle tower save file flags?)
showMenu:
    writetext(GoldenrodPokecomCenterWhatToDoText) //what would you like to do?
    setval(0x00)
    special(Menu_ChallengeExplanationCancel) // show news machine menu
    ifequal(0x01, getNews)
    ifequal(0x02, showNews)
    ifequal(0x03, showExplanation)
cancel:
    closetext
    s_end
showExplanation:
    writetext(GoldenrodPokecomCenterNewsMachineExplanationText) // news machine tut
    waitbutton
    goto showMenu;
    //
getNews:
    writetext(GoldenrodPokecomCenterWouldYouLikeTheNewsText) // would you like to get the news?
    yesorno
    iffalse(showMenu)
    writetext(GoldenrodPokecomCenterReadingTheLatestNewsText) // reading the latest news
    special(Function17d2b6) // download news?
    ifequal(0x0A, showMenu)
    ifnotequal(0x00, mobileError)
showNews:
    special(Function17d2ce) // show news?
    iffalse(quitViewingNews)
    ifequal(0x01, noOldNews)
    writetext(GoldenrodPokecomCenterCorruptedNewsDataText) //news corrupted
    waitbutton
    goto showMenu;
    //
noOldNews:
    writetext(GoldenrodPokecomCenterNoOldNewsText) //no old news
    waitbutton
quitViewingNews:
    goto showMenu;
    //
mobileError:
    special(BattleTowerMobileError) // mobile error
    closetext
    s_end
    SCRIPT_END
}
bool GoldenrodPokecenter1F_GSBallSceneLeft(script_s* s) {
    SCRIPT_BEGIN
    setval(BATTLETOWERACTION_CHECKMOBILEEVENT)
    special(BattleTowerAction)
    ifequal(MOBILE_EVENT_OBJECT_GS_BALL, gsball)
    s_end
gsball:
    checkevent(EVENT_GOT_GS_BALL_FROM_POKECOM_CENTER)
    iftrue(cancel)
    playsound(SFX_EXIT_BUILDING)
    moveobject(GOLDENRODPOKECENTER1F_LINK_RECEPTIONIST, 0, 7)
    disappear(GOLDENRODPOKECENTER1F_LINK_RECEPTIONIST)
    appear(GOLDENRODPOKECENTER1F_LINK_RECEPTIONIST)
    playmusic(MUSIC_SHOW_ME_AROUND)
    applymovement(GOLDENRODPOKECENTER1F_LINK_RECEPTIONIST, GoldenrodPokeCenter1FLinkReceptionistApproachPlayerAtLeftDoorwayTileMovement)
    turnobject(PLAYER, UP)
    opentext
    writetext(GoldenrodPokeCenter1FLinkReceptionistPleaseAcceptGSBallText)
    waitbutton
    verbosegiveitem(GS_BALL, 1)
    setevent(EVENT_GOT_GS_BALL_FROM_POKECOM_CENTER)
    setevent(EVENT_CAN_GIVE_GS_BALL_TO_KURT)
    writetext(GoldenrodPokeCenter1FLinkReceptionistPleaseDoComeAgainText)
    waitbutton
    closetext
    applymovement(GOLDENRODPOKECENTER1F_LINK_RECEPTIONIST, GoldenrodPokeCenter1FLinkReceptionistWalkToStairsFromLeftDoorwayTileMovement)
    special(RestartMapMusic)
    disappear(GOLDENRODPOKECENTER1F_LINK_RECEPTIONIST)
    playsound(SFX_EXIT_BUILDING)
cancel:
    s_end
    SCRIPT_END
}
bool GoldenrodPokecenter1F_GSBallSceneRight(script_s* s) {
    SCRIPT_BEGIN
    setval(BATTLETOWERACTION_CHECKMOBILEEVENT)
    special(BattleTowerAction)
    ifequal(MOBILE_EVENT_OBJECT_GS_BALL, gsball)
    s_end
gsball:
    checkevent(EVENT_GOT_GS_BALL_FROM_POKECOM_CENTER)
    iftrue(cancel)
    playsound(SFX_EXIT_BUILDING)
    moveobject(GOLDENRODPOKECENTER1F_LINK_RECEPTIONIST, 0, 7)
    disappear(GOLDENRODPOKECENTER1F_LINK_RECEPTIONIST)
    appear(GOLDENRODPOKECENTER1F_LINK_RECEPTIONIST)
    playmusic(MUSIC_SHOW_ME_AROUND)
    applymovement(GOLDENRODPOKECENTER1F_LINK_RECEPTIONIST, GoldenrodPokeCenter1FLinkReceptionistApproachPlayerAtRightDoorwayTileMovement)
    turnobject(PLAYER, UP)
    opentext
    writetext(GoldenrodPokeCenter1FLinkReceptionistPleaseAcceptGSBallText)
    waitbutton
    verbosegiveitem(GS_BALL, 1)
    setevent(EVENT_GOT_GS_BALL_FROM_POKECOM_CENTER)
    setevent(EVENT_CAN_GIVE_GS_BALL_TO_KURT)
    writetext(GoldenrodPokeCenter1FLinkReceptionistPleaseDoComeAgainText)
    waitbutton
    closetext
    applymovement(GOLDENRODPOKECENTER1F_LINK_RECEPTIONIST, GoldenrodPokeCenter1FLinkReceptionistWalkToStairsFromRightDoorwayTileMovement)
    special(RestartMapMusic)
    disappear(GOLDENRODPOKECENTER1F_LINK_RECEPTIONIST)
    playsound(SFX_EXIT_BUILDING)
cancel:
    s_end
    SCRIPT_END
}
bool GoldenrodPokecenter1FGameboyKidScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(GoldenrodPokecenter1FGameboyKidText)
    SCRIPT_END
}
bool GoldenrodPokecenter1FLassScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(GoldenrodPokecenter1FLassText)
    SCRIPT_END
}
bool GoldenrodPokecenter1FPokefanF(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(GoldenrodPokecenter1FPokefanFDoYouHaveEonMailText)
    waitbutton
    writetext(GoldenrodPokecenter1FAskGiveAwayAnEonMailText)
    yesorno
    iffalse(NoEonMail)
    takeitem(EON_MAIL, 1)
    iffalse(NoEonMail)
    writetext(GoldenrodPokecenter1FPlayerGaveAwayTheEonMailText)
    waitbutton
    writetext(GoldenrodPokecenter1FPokefanFThisIsForYouText)
    waitbutton
    verbosegiveitem(REVIVE, 1)
    iffalse(NoRoom)
    writetext(GoldenrodPokecenter1FPokefanFDaughterWillBeDelightedText)
    waitbutton
    closetext
    s_end
NoEonMail:
    writetext(GoldenrodPokecenter1FPokefanFTooBadText)
    waitbutton
    closetext
    s_end
NoRoom:
    giveitem(EON_MAIL, 1)
    writetext(GoldenrodPokecenter1FPokefanFAnotherTimeThenText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool GoldenrodPokecenter1FSuperNerdScript(script_s* s) {
    SCRIPT_BEGIN
    special(Mobile_DummyReturnFalse) // 56998
    iftrue(mobile)
    jumptextfaceplayer(GoldenrodPokecomCenterPerson1Text) //$E071
    //
mobile:
    jumptextfaceplayer(GoldenrodPokecomCenterPerson2Text) //$1E72
    SCRIPT_END
}
bool GoldenrodPokecenter1FLass2Script(script_s* s) {
    SCRIPT_BEGIN
    special(Mobile_DummyReturnFalse) // 569A4
    iftrue(mobile)
    jumptextfaceplayer(GoldenrodPokecomCenterPerson3Text) //$AD72
    //
mobile:
    checkevent(EVENT_UNUSED_37)
    iftrue(alreadyMoved) //$D369
    faceplayer
    opentext
    writetext(GoldenrodPokecomCenterPerson4Text) //$EB72
    waitbutton
    closetext
    readvar(VAR_FACING)
    ifequal(0x02, talkedToFromRight) //$C769
    applymovement(GOLDENRODPOKECENTER1F_LASS2, GoldenrodPokeCenter1FLass2WalkRightMovement) //$236A
    goto skip; //$CB69
talkedToFromRight:
    applymovement(GOLDENRODPOKECENTER1F_LASS2, GoldenrodPokeCenter1FLassWalkRightAroundPlayerMovement) //$276A
skip:
    setevent(EVENT_UNUSED_37)
    moveobject(GOLDENRODPOKECENTER1F_LASS2, 0x12, 0x09)
    s_end
alreadyMoved:
    jumptextfaceplayer(GoldenrodPokecomCenterPerson5Text) //$2373
    SCRIPT_END
}
bool GoldenrodPokecenter1FYoungsterScript(script_s* s) {
    SCRIPT_BEGIN
    special(Mobile_DummyReturnFalse) // 569D6
    iftrue(mobile)
    jumptextfaceplayer(GoldenrodPokecomCenterPerson6Text) //$5473
    //
mobile:
    jumptextfaceplayer(GoldenrodPokecomCenterPerson9Text) //$1074
    SCRIPT_END
}
bool GoldenrodPokecenter1FTeacherScript(script_s* s) {
    SCRIPT_BEGIN
    special(Mobile_DummyReturnFalse)
    iftrue(mobile)
    jumptextfaceplayer(GoldenrodPokecomCenterPerson7Text)
    //
mobile:
    jumptextfaceplayer(GoldenrodPokecomCenterPerson10Text)
    SCRIPT_END
}
bool GoldenrodPokecenter1FRockerScript(script_s* s) {
    SCRIPT_BEGIN
    special(Mobile_DummyReturnFalse) // 569EE
    iftrue(mobile) //$F769
    jumptextfaceplayer(GoldenrodPokecomCenterPerson8Text) //$D073
    //
mobile:
    jumptextfaceplayer(GoldenrodPokecomCenterPerson11Text) //$5474
    SCRIPT_END
}
bool GoldenrodPokecenter1FGrampsScript(script_s* s) {
    SCRIPT_BEGIN
    special(Mobile_DummyReturnFalse)
    iftrue(mobile)
    jumptextfaceplayer(GoldenrodPokecomCenterPerson12Text)
    //
mobile:
    jumptextfaceplayer(GoldenrodPokecomCenterPerson13Text)
    SCRIPT_END
}
bool PokeComCenterInfoSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(GoldenrodPokecomCenterSignText)
    SCRIPT_END
}
const uint8_t GoldenrodPokeCenter1FLinkReceptionistApproachPlayerAtLeftDoorwayTileMovement[] = {
    step(UP),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    turn_head(DOWN),
    movement_step_end,
};
const uint8_t GoldenrodPokeCenter1FLinkReceptionistWalkToStairsFromLeftDoorwayTileMovement[] = {
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(DOWN),
    movement_step_end,
};
const uint8_t GoldenrodPokeCenter1FLinkReceptionistApproachPlayerAtRightDoorwayTileMovement[] = {
    step(UP),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    turn_head(DOWN),
    movement_step_end,
};
const uint8_t GoldenrodPokeCenter1FLinkReceptionistWalkToStairsFromRightDoorwayTileMovement[] = {
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(DOWN),
    movement_step_end,
};
const uint8_t GoldenrodPokeCenter1FLass2WalkRightMovement[] = {
    slow_step(RIGHT), // $0B
    slow_step(RIGHT), // $0B
    turn_head(UP), // $01
    movement_step_end, // db $47
};
const uint8_t GoldenrodPokeCenter1FLassWalkRightAroundPlayerMovement[] = {
    slow_step(DOWN), // $08
    slow_step(RIGHT), // $0B
    slow_step(RIGHT), // $0B
    slow_step(UP), // $09
    turn_head(UP), // $01
    movement_step_end, // db $47
};
const txt_cmd_s GoldenrodPokecomCenterWelcomeToTradeCornerText[] = {
    text_start("Hello! Welcome to"
        t_line "#COM CENTER"
        t_cont "TRADE CORNER."
        t_para "You can trade"
        t_line "#MON with other"
        t_cont "people far away."
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterWeMustHoldYourMonText[] = {
    text_start("To make a trade,"
        t_line "we must hold your"
        t_cont "#MON."
        t_para "Would you like to"
        t_line "trade?"
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterWhatMonDoYouWantText[] = {
    text_start("What kind of"
        t_line "#MON do you"
        t_cont "want in return?"
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterWeWillTradeYourMonForMonText[] = {
    text_start("Fine. We will try"
        t_line "to trade your"
        t_para "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(" for"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start("."
        t_para "We'll have to hold"
        t_line "your #MON"
        t_cont "during the trade."
        t_para "Please wait while"
        t_line "we prepare the"
        t_cont "room for it."
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterWeWillTradeYourMonForNewText[] = {
    text_start("Fine. We will try"
        t_line "to trade your"
        t_para "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(" for a"
        t_line "#MON that you"
        t_cont "have never seen."
        t_para "We'll have to hold"
        t_line "your #MON"
        t_cont "during the trade."
        t_para "Please wait while"
        t_line "we prepare the"
        t_cont "room for it."
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterYourMonHasBeenReceivedText[] = {
    text_start("Your trade #MON"
        t_line "has been received."
        t_para "It will take time"
        t_line "to find a trade"
        t_para "partner. Please"
        t_line "come back later."
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterYouHaveOnlyOneMonText[] = {
    text_start("Oh? You have only"
        t_line "one #MON in"
        t_cont "your party. "
        t_para "Please come back"
        t_line "once you've in-"
        t_cont "creased the size"
        t_cont "of your party."
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterWeHopeToSeeYouAgainText[] = {
    text_start("We hope to see you"
        t_line "again."
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterCommunicationErrorText[] = {
    text_start("Communication"
        t_line "error…"
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterCantAcceptLastMonText[] = {
    text_start("If we accept that"
        t_line "#MON, what will"
        t_cont "you battle with?"
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterCantAcceptEggText[] = {
    text_start("Sorry. We can't"
        t_line "accept an EGG."
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterCantAcceptAbnormalMonText[] = {
    text_start("Sorry, but your"
        t_line "#MON appears to"
        t_para "be abnormal. We"
        t_line "can't accept it."
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterAlreadyHoldingMonText[] = {
    text_start("Oh? Aren't we"
        t_line "already holding a"
        t_cont "#MON of yours?"
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterCheckingTheRoomsText[] = {
    text_start("We'll check the"
        t_line "rooms."
        t_para "Please wait."
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterTradePartnerHasBeenFoundText[] = {
    text_start("Thank you for your"
        t_line "patience."
        t_para "A trade partner"
        t_line "has been found."
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterItsYourNewPartnerText[] = {
    text_start("It's your new"
        t_line "partner."
        t_para "Please take care"
        t_line "of it with love."
        t_para "We hope to see you"
        t_line "again."
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterYourPartyIsFullText[] = {
    text_start("Uh-oh. Your party"
        t_line "is already full."
        t_para "Please come back"
        t_line "when you have room"
        t_cont "in your party."
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterNoTradePartnerFoundText[] = {
    text_start("It's unfortunate,"
        t_line "but no one has"
        t_para "come forward as a"
        t_line "trade partner."
        t_para "Would you like"
        t_line "your #MON back?"
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterReturnedYourMonText[] = {
    text_start("We have returned"
        t_line "your #MON."
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterYourMonIsLonelyText[] = {
    text_start("It's unfortunate,"
        t_line "but no one has"
        t_para "come forward as a"
        t_line "trade partner."
        t_para "We've held your"
        t_line "#MON for a long"
        t_para "time. As a result,"
        t_line "it is very lonely."
        t_para "Sorry, but we must"
        t_line "return it to you."
        t_done )
};
const txt_cmd_s GoldenrodPokecenter1FWeHopeToSeeYouAgainText_2[] = {
    text_start("We hope to see you"
        t_line "again."
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterContinueToHoldYourMonText[] = {
    text_start("Fine. We will"
        t_line "continue to hold"
        t_cont "your #MON."
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterRecentlyLeftYourMonText[] = {
    text_start("Oh? You left your"
        t_line "#MON with us"
        t_cont "only recently."
        t_para "Please come back"
        t_line "later."
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterSaveBeforeTradeCornerText[] = {
    text_start("We'll SAVE before"
        t_line "connecting to the"
        t_cont "CENTER."
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterWhichMonToTradeText[] = {
    text_start("Which #MON do"
        t_line "you want to trade?"
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterTradeCanceledText[] = {
    text_start("Sorry, but we must"
        t_line "cancel the trade."
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterEggTicketText[] = {
    text_start("Oh!"
        t_para "I see you have an"
        t_line "EGG TICKET!"
        t_para "It's a coupon that"
        t_line "special people can"
        t_para "redeem for a"
        t_line "special #MON!"
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterOddEggBriefingText[] = {
    text_start("Let me give you a"
        t_line "quick briefing."
        t_para "Trades held at the"
        t_line "TRADE CORNER are"
        t_para "between two"
        t_line "trainers who don't"
        t_para "know each other's"
        t_line "identity."
        t_para "As a result, it"
        t_line "may take time."
        t_para "However, an ODD"
        t_line "EGG is available"
        t_cont "just for you."
        t_para "It will be sent to"
        t_line "you right away."
        t_para "Please choose one"
        t_line "of the rooms in"
        t_para "the CENTER."
        t_line "An ODD EGG will be"
        t_para "sent from the"
        t_line "chosen room."
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterPleaseWaitAMomentText[] = {
    text_start("Please wait a"
        t_line "moment."
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterHereIsYourOddEggText[] = {
    text_start("Thank you for"
        t_line "waiting."
        t_para "We received your"
        t_line "ODD EGG."
        t_para "Here it is!"
        t_para "Please raise it"
        t_line "with loving care."
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterNoEggTicketServiceText[] = {
    text_start("I'm awfully sorry."
        t_para "The EGG TICKET"
        t_line "exchange service"
        t_cont "isn't running now."
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterNewsMachineText[] = {
    text_start("It's a #MON"
        t_line "NEWS MACHINE."
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterWhatToDoText[] = {
    text_start("What would you"
        t_line "like to do?"
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterNewsMachineExplanationText[] = {
    text_start("#MON NEWS is"
        t_line "news compiled from"
        t_para "the SAVE files of"
        t_line "#MON trainers."
        t_para "When reading the"
        t_line "NEWS, your SAVE"
        t_para "file may be sent"
        t_line "out."
        t_para "The SAVE file data"
        t_line "will contain your"
        t_para "adventure log and"
        t_line "mobile profile."
        t_para "Your phone number"
        t_line "will not be sent."
        t_para "The contents of"
        t_line "the NEWS will vary"
        t_para "depending on the"
        t_line "SAVE files sent by"
        t_para "you and the other"
        t_line "#MON trainers."
        t_para "You might even be"
        t_line "in the NEWS!"
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterWouldYouLikeTheNewsText[] = {
    text_start("Would you like to"
        t_line "get the NEWS?"
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterReadingTheLatestNewsText[] = {
    text_start("Reading the latest"
        t_line "NEWS… Please wait."
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterNoOldNewsText[] = {
    text_start("There is no old"
        t_line "NEWS…"
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterCorruptedNewsDataText[] = {
    text_start("The NEWS data is"
        t_line "corrupted."
        t_para "Please download"
        t_line "the NEWS again."
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterMakingPreparationsText[] = {
    text_start("We're making"
        t_line "preparations."
        t_para "Please come back"
        t_line "later."
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterSaveBeforeNewsMachineText[] = {
    text_start("We will SAVE your"
        t_line "progress before"
        t_para "starting the NEWS"
        t_line "MACHINE."
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterPerson1Text[] = {
    text_start("Whoa, this #MON"
        t_line "CENTER is huge."
        t_para "They just built"
        t_line "this place. They"
        t_para "installed lots of"
        t_line "new machines too."
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterPerson2Text[] = {
    text_start("I thought up a fun"
        t_line "new thing for the"
        t_cont "TRADE CORNER!"
        t_para "I make a PIDGEY"
        t_line "hold MAIL, then"
        t_para "put it up for"
        t_line "trade for another"
        t_cont "one!"
        t_para "If everyone did"
        t_line "that, MAIL could"
        t_para "be traded with all"
        t_line "sorts of people!"
        t_para "I call it PIDGEY"
        t_line "MAIL!"
        t_para "If it becomes"
        t_line "popular, I might"
        t_para "make lots of new"
        t_line "friends!"
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterPerson3Text[] = {
    text_start("They said you can"
        t_line "trade #MON with"
        t_para "total strangers up"
        t_line "here."
        t_para "But they're still"
        t_line "adjusting things."
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterPerson4Text[] = {
    text_start("Some girl I don't"
        t_line "know sent me her"
        t_para "HOPPIP."
        t_line "You should trade"
        t_para "for a #MON that"
        t_line "you want."
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterPerson5Text[] = {
    text_start("I received a"
        t_line "female HOPPIP, but"
        t_cont "its named STANLEY!"
        t_para "That's my dad's"
        t_line "name!"
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterPerson6Text[] = {
    text_start("What is the NEWS"
        t_line "MACHINE?"
        t_para "Does it get news"
        t_line "from a wider area"
        t_cont "than the radio?"
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterPerson7Text[] = {
    text_start("The #COM CENTER"
        t_line "will link with all"
        t_para "#MON CENTERS in"
        t_line "a wireless net."
        t_para "That must mean"
        t_line "I'll be able to"
        t_para "link with all"
        t_line "sorts of people."
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterPerson8Text[] = {
    text_start("The machines here"
        t_line "can't be used yet."
        t_para "Still, it's nice"
        t_line "coming to a trendy"
        t_para "place before other"
        t_line "people."
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterPerson9Text[] = {
    text_start("My friend was in"
        t_line "the NEWS a while"
        t_para "back. I was really"
        t_line "surprised!"
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterPerson10Text[] = {
    text_start("I get anxious if I"
        t_line "don't check out"
        t_cont "the latest NEWS!"
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterPerson11Text[] = {
    text_start("If I get in the"
        t_line "NEWS and become"
        t_para "famous, I bet I'll"
        t_line "be adored."
        t_para "I wonder how I"
        t_line "could get in the"
        t_cont "NEWS?"
        t_done )
};
const txt_cmd_s GoldenrodPokecenter1FGameboyKidText[] = {
    text_start("The COLOSSEUM"
        t_line "upstairs is for"
        t_cont "link battles."
        t_para "Battle records are"
        t_line "posted on the"
        t_para "wall, so I can't"
        t_line "afford to lose."
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterPerson12Text[] = {
    text_start("I came over here"
        t_line "when I got word"
        t_para "that GOLDENROD's"
        t_line "#MON CENTER has"
        t_para "new machines that"
        t_line "no one's ever seen"
        t_cont "before."
        t_para "But it looks like"
        t_line "they're still busy"
        t_para "with all their"
        t_line "preparations…"
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterPerson13Text[] = {
    text_start("Just seeing all"
        t_line "these new things"
        t_para "here makes me feel"
        t_line "younger!"
        t_done )
};
const txt_cmd_s GoldenrodPokecenter1FLassText[] = {
    text_start("A higher level"
        t_line "#MON doesn't"
        t_cont "always win."
        t_para "After all, it may"
        t_line "have a type dis-"
        t_cont "advantage."
        t_para "I don't think"
        t_line "there is a single"
        t_para "#MON that is"
        t_line "the toughest."
        t_done )
};
const txt_cmd_s GoldenrodPokeCenter1FLinkReceptionistPleaseAcceptGSBallText[] = {
    text_start("<PLAYER>, isn't it?"
        t_para "Congratulations!"
        t_para "As a special deal,"
        t_line "a GS BALL has been"
        t_cont "sent just for you!"
        t_para "Please accept it!"
        t_done )
};
const txt_cmd_s GoldenrodPokeCenter1FLinkReceptionistPleaseDoComeAgainText[] = {
    text_start("Please do come"
        t_line "again!"
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterSignText[] = {
    text_start("#COM CENTER"
        t_line "1F INFORMATION"
        t_para "Left:"
        t_line "ADMINISTRATION"
        t_para "Center:"
        t_line "TRADE CORNER"
        t_para "Right:"
        t_line "#MON NEWS"
        t_done )
};
const txt_cmd_s GoldenrodPokecomCenterNewsMachineNotYetText[] = {
    text_start("It's a #MON"
        t_line "NEWS MACHINE!"
        t_para "It's not in"
        t_line "operation yet…"
        t_done )
};
const txt_cmd_s GoldenrodPokecenter1FPokefanFDoYouHaveEonMailText[] = {
    text_start("Oh my, your pack"
        t_line "looks so heavy!"
        t_para "Oh! Do you happen"
        t_line "to have something"
        t_cont "named EON MAIL?"
        t_para "My daughter is"
        t_line "after one."
        t_para "You can part with"
        t_line "one, can't you?"
        t_done )
};
const txt_cmd_s GoldenrodPokecenter1FAskGiveAwayAnEonMailText[] = {
    text_start("Give away an EON"
        t_line "MAIL?"
        t_done )
};
const txt_cmd_s GoldenrodPokecenter1FPokefanFThisIsForYouText[] = {
    text_start("Oh, that's great!"
        t_line "Thank you, honey!"
        t_para "Here, this is for"
        t_line "you in return!"
        t_done )
};
const txt_cmd_s GoldenrodPokecenter1FPokefanFDaughterWillBeDelightedText[] = {
    text_start("My daughter will"
        t_line "be delighted!"
        t_done )
};
const txt_cmd_s GoldenrodPokecenter1FPokefanFTooBadText[] = {
    text_start("Oh? You don't have"
        t_line "one? Too bad."
        t_done )
};
const txt_cmd_s GoldenrodPokecenter1FPokefanFAnotherTimeThenText[] = {
    text_start("Oh… Well, another"
        t_line "time, then."
        t_done )
};
const txt_cmd_s GoldenrodPokecenter1FPlayerGaveAwayTheEonMailText[] = {
    text_start("<PLAYER> gave away"
        t_line "the EON MAIL."
        t_done )
};
