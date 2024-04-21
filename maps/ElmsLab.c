#include "../constants.h"
#include "../util/scripting.h"
#include "ElmsLab.h"
//// EVENTS
enum {
    ELMSLAB_ELM = 2,
    ELMSLAB_ELMS_AIDE,
    ELMSLAB_POKE_BALL1,
    ELMSLAB_POKE_BALL2,
    ELMSLAB_POKE_BALL3,
    ELMSLAB_OFFICER,
};

const Script_fn_t ElmsLab_SceneScripts[] = {
    ElmsLab_MapScripts_MeetElm , //  SCENE_DEFAULT,
    ElmsLab_MapScripts_DummyScene1 , //  SCENE_ELMSLAB_CANT_LEAVE,
    ElmsLab_MapScripts_DummyScene2 , //  SCENE_ELMSLAB_NOTHING,
    ElmsLab_MapScripts_DummyScene3 , //  SCENE_ELMSLAB_MEET_OFFICER,
    ElmsLab_MapScripts_DummyScene4 , //  SCENE_ELMSLAB_UNUSED,
    ElmsLab_MapScripts_DummyScene5 , //  SCENE_ELMSLAB_AIDE_GIVES_POTION,
};

const struct MapCallback ElmsLab_MapCallbacks[] = {
    map_callback(MAPCALLBACK_OBJECTS, ElmsLab_MapScripts_MoveElmCallback),
};

const struct MapScripts ElmsLab_MapScripts = {
    .scene_script_count = lengthof(ElmsLab_SceneScripts),
    .scene_scripts = ElmsLab_SceneScripts,

    .callback_count = lengthof(ElmsLab_MapCallbacks),
    .callbacks = ElmsLab_MapCallbacks,
};

static const struct CoordEvent ElmsLab_CoordEvents[] = {
    coord_event(4, 6, SCENE_ELMSLAB_CANT_LEAVE, &LabTryToLeaveScript),
    coord_event(5, 6, SCENE_ELMSLAB_CANT_LEAVE, &LabTryToLeaveScript),
    coord_event(4, 5, SCENE_ELMSLAB_MEET_OFFICER, &MeetCopScript),
    coord_event(5, 5, SCENE_ELMSLAB_MEET_OFFICER, &MeetCopScript2),
    coord_event(4, 8, SCENE_ELMSLAB_AIDE_GIVES_POTION, &AideScript_WalkPotion1),
    coord_event(5, 8, SCENE_ELMSLAB_AIDE_GIVES_POTION, &AideScript_WalkPotion2),
    coord_event(4, 8, SCENE_ELMSLAB_AIDE_GIVES_POKE_BALLS, &AideScript_WalkBalls1),
    coord_event(5, 8, SCENE_ELMSLAB_AIDE_GIVES_POKE_BALLS, &AideScript_WalkBalls2),
};

static const struct BGEvent ElmsLab_BGEvents[] = {
    bg_event(2, 1, BGEVENT_READ, &ElmsLabHealingMachine),
    bg_event(6, 1, BGEVENT_READ, &ElmsLabBookshelf),
    bg_event(7, 1, BGEVENT_READ, &ElmsLabBookshelf),
    bg_event(8, 1, BGEVENT_READ, &ElmsLabBookshelf),
    bg_event(9, 1, BGEVENT_READ, &ElmsLabBookshelf),
    bg_event(0, 7, BGEVENT_READ, &ElmsLabTravelTip1),
    bg_event(1, 7, BGEVENT_READ, &ElmsLabTravelTip2),
    bg_event(2, 7, BGEVENT_READ, &ElmsLabTravelTip3),
    bg_event(3, 7, BGEVENT_READ, &ElmsLabTravelTip4),
    bg_event(6, 7, BGEVENT_READ, &ElmsLabBookshelf),
    bg_event(7, 7, BGEVENT_READ, &ElmsLabBookshelf),
    bg_event(8, 7, BGEVENT_READ, &ElmsLabBookshelf),
    bg_event(9, 7, BGEVENT_READ, &ElmsLabBookshelf),
    bg_event(9, 3, BGEVENT_READ, &ElmsLabTrashcan),
    bg_event(5, 0, BGEVENT_READ, &ElmsLabWindow),
    bg_event(3, 5, BGEVENT_DOWN, &ElmsLabPC),
};

static const struct WarpEventData ElmsLab_WarpEvents[] = {
    warp_event(4, 11, NEW_BARK_TOWN, 1),
    warp_event(5, 11, NEW_BARK_TOWN, 1),
};

static const struct ObjEvent ElmsLab_ObjectEvents[] = {
    object_event(5, 2, SPRITE_ELM, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &ProfElmScript, -1),
    object_event(2, 9, SPRITE_SCIENTIST, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &ElmsAideScript, EVENT_ELMS_AIDE_IN_LAB),
    object_event(6, 3, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &CyndaquilPokeBallScript, EVENT_CYNDAQUIL_POKEBALL_IN_ELMS_LAB),
    object_event(7, 3, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &TotodilePokeBallScript, EVENT_TOTODILE_POKEBALL_IN_ELMS_LAB),
    object_event(8, 3, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &ChikoritaPokeBallScript, EVENT_CHIKORITA_POKEBALL_IN_ELMS_LAB),
    object_event(5, 3, SPRITE_OFFICER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &CopScript, EVENT_COP_IN_ELMS_LAB),
};

const struct MapEvents ElmsLab_MapEvents = {
    .warp_event_count = lengthof(ElmsLab_WarpEvents),
    .warp_events = ElmsLab_WarpEvents,

    .coord_event_count = lengthof(ElmsLab_CoordEvents),
    .coord_events = ElmsLab_CoordEvents,

    .bg_event_count = lengthof(ElmsLab_BGEvents),
    .bg_events = ElmsLab_BGEvents,

    .obj_event_count = lengthof(ElmsLab_ObjectEvents),
    .obj_events = ElmsLab_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "ElmsLab.h"

bool ElmsLab_MapScripts_MeetElm(script_s* s) {
    SCRIPT_BEGIN
    sdefer(ElmsLab_MapScripts_WalkUpToElm);
    s_end
    SCRIPT_END
}
bool ElmsLab_MapScripts_DummyScene1(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool ElmsLab_MapScripts_DummyScene2(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool ElmsLab_MapScripts_DummyScene3(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool ElmsLab_MapScripts_DummyScene4(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool ElmsLab_MapScripts_DummyScene5(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool ElmsLab_MapScripts_MoveElmCallback(script_s* s) {
    SCRIPT_BEGIN
    checkscene
    iftrue_jump(ElmsLab_MapScripts_Skip) // not SCENE_DEFAULT
    moveobject(ELMSLAB_ELM, 3, 4)
    SCRIPT_FALLTHROUGH(ElmsLab_MapScripts_Skip)
}
bool ElmsLab_MapScripts_Skip(script_s* s) {
    SCRIPT_BEGIN
    s_endcallback
    SCRIPT_END
}
bool ElmsLab_MapScripts_WalkUpToElm(script_s* s) {
    SCRIPT_BEGIN
    applymovement(PLAYER, ElmsLab_WalkUpToElmMovement)
    showemote(EMOTE_SHOCK, ELMSLAB_ELM, 15)
    turnobject(ELMSLAB_ELM, RIGHT)
    opentext
    writetext(ElmText_Intro)
    SCRIPT_FALLTHROUGH(ElmsLab_MapScripts_MustSayYes)
}
bool ElmsLab_MapScripts_MustSayYes(script_s* s) {
    SCRIPT_BEGIN
    yesorno
    iftrue_jump(ElmsLab_MapScripts_ElmGetsEmail)
    writetext(ElmText_Refused)
    sjump(ElmsLab_MapScripts_MustSayYes);
    SCRIPT_END
}
bool ElmsLab_MapScripts_ElmGetsEmail(script_s* s) {
    SCRIPT_BEGIN
    writetext(ElmText_Accepted)
    promptbutton
    writetext(ElmText_ResearchAmbitions)
    waitbutton
    closetext
    playsound(SFX_GLASS_TING)
    pause(30)
    showemote(EMOTE_SHOCK, ELMSLAB_ELM, 10)
    turnobject(ELMSLAB_ELM, DOWN)
    opentext
    writetext(ElmText_GotAnEmail)
    waitbutton
    closetext
    opentext
    turnobject(ELMSLAB_ELM, RIGHT)
    writetext(ElmText_MissionFromMrPokemon)
    waitbutton
    closetext
    applymovement(ELMSLAB_ELM, ElmsLab_ElmToDefaultPositionMovement1)
    turnobject(PLAYER, UP)
    applymovement(ELMSLAB_ELM, ElmsLab_ElmToDefaultPositionMovement2)
    turnobject(PLAYER, RIGHT)
    opentext
    writetext(ElmText_ChooseAPokemon)
    waitbutton
    setscene(SCENE_ELMSLAB_CANT_LEAVE)
    closetext
    s_end
    SCRIPT_END
}
bool ProfElmScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_SS_TICKET_FROM_ELM)
    iftrue_jump(ElmCheckMasterBall)
    checkevent(EVENT_BEAT_ELITE_FOUR)
    iftrue_jump(ElmGiveTicketScript)
    SCRIPT_FALLTHROUGH(ElmCheckMasterBall)
}
bool ElmCheckMasterBall(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_GOT_MASTER_BALL_FROM_ELM)
    iftrue_jump(ElmCheckEverstone)
    checkflag(ENGINE_RISINGBADGE)
    iftrue_jump(ElmGiveMasterBallScript)
    SCRIPT_FALLTHROUGH(ElmCheckEverstone)
}
bool ElmCheckEverstone(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_GOT_EVERSTONE_FROM_ELM)
    iftrue_jump(ElmScript_CallYou)
    checkevent(EVENT_SHOWED_TOGEPI_TO_ELM)
    iftrue_jump(ElmGiveEverstoneScript)
    checkevent(EVENT_TOLD_ELM_ABOUT_TOGEPI_OVER_THE_PHONE)
    iffalse_jump(ElmCheckTogepiEgg)
    setval(TOGEPI)
    special(FindPartyMonThatSpeciesYourTrainerID)
    iftrue_jump(ShowElmTogepiScript)
    setval(TOGETIC)
    special(FindPartyMonThatSpeciesYourTrainerID)
    iftrue_jump(ShowElmTogepiScript)
    writetext(ElmThoughtEggHatchedText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool ElmEggHatchedScript(script_s* s) {
    SCRIPT_BEGIN
    setval(TOGEPI)
    special(FindPartyMonThatSpeciesYourTrainerID)
    iftrue_jump(ShowElmTogepiScript)
    setval(TOGETIC)
    special(FindPartyMonThatSpeciesYourTrainerID)
    iftrue_jump(ShowElmTogepiScript)
    sjump(ElmCheckGotEggAgain)
    SCRIPT_END
}
bool ElmCheckTogepiEgg(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_GOT_TOGEPI_EGG_FROM_ELMS_AIDE)
    iffalse_jump(ElmCheckGotEggAgain)
    checkevent(EVENT_TOGEPI_HATCHED)
    iftrue_jump(ElmEggHatchedScript)
    SCRIPT_FALLTHROUGH(ElmCheckGotEggAgain)
}
bool ElmCheckGotEggAgain(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_GOT_TOGEPI_EGG_FROM_ELMS_AIDE) // why are we checking it again?
    iftrue_jump(ElmWaitingEggHatchScript)
    checkflag(ENGINE_ZEPHYRBADGE)
    iftrue_jump(ElmAideHasEggScript)
    checkevent(EVENT_GAVE_MYSTERY_EGG_TO_ELM)
    iftrue_jump(ElmStudyingEggScript)
    checkevent(EVENT_GOT_MYSTERY_EGG_FROM_MR_POKEMON)
    iftrue_jump(ElmAfterTheftScript)
    checkevent(EVENT_GOT_A_POKEMON_FROM_ELM)
    iftrue_jump(ElmDescribesMrPokemonScript)
    writetext(ElmText_LetYourMonBattleIt)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool LabTryToLeaveScript(script_s* s) {
    SCRIPT_BEGIN
    turnobject(ELMSLAB_ELM, DOWN)
    opentext
    writetext(LabWhereGoingText)
    waitbutton
    closetext
    applymovement(PLAYER, ElmsLab_CantLeaveMovement)
    s_end
    SCRIPT_END
}
bool CyndaquilPokeBallScript(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_GOT_A_POKEMON_FROM_ELM)
    iftrue_jump(LookAtElmPokeBallScript)
    turnobject(ELMSLAB_ELM, DOWN)
    refreshscreen
    pokepic(CYNDAQUIL)
    playcry(CYNDAQUIL)
    waitbutton
    closepokepic
    opentext
    writetext(TakeCyndaquilText)
    yesorno
    iffalse_jump(DidntChooseStarterScript)
    disappear(ELMSLAB_POKE_BALL1)
    setevent(EVENT_GOT_CYNDAQUIL_FROM_ELM)
    writetext(ChoseStarterText)
    promptbutton
    waitsfx
    getmonname(STRING_BUFFER_3, CYNDAQUIL)
    writetext(ReceivedStarterText)
    playsound(SFX_CAUGHT_MON)
    waitsfx
    promptbutton
    givepoke(CYNDAQUIL, 5, BERRY)
    closetext
    readvar(VAR_FACING)
    ifequal_jump(RIGHT, ElmDirectionsScript)
    applymovement(PLAYER, AfterCyndaquilMovement)
    sjump(ElmDirectionsScript)
    SCRIPT_END
}
bool TotodilePokeBallScript(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_GOT_A_POKEMON_FROM_ELM)
    iftrue_jump(LookAtElmPokeBallScript)
    turnobject(ELMSLAB_ELM, DOWN)
    refreshscreen
    pokepic(TOTODILE)
    playcry(TOTODILE)
    waitbutton
    closepokepic
    opentext
    writetext(TakeTotodileText)
    yesorno
    iffalse_jump(DidntChooseStarterScript)
    disappear(ELMSLAB_POKE_BALL2)
    setevent(EVENT_GOT_TOTODILE_FROM_ELM)
    writetext(ChoseStarterText)
    promptbutton
    waitsfx
    getmonname(STRING_BUFFER_3, TOTODILE)
    writetext(ReceivedStarterText)
    playsound(SFX_CAUGHT_MON)
    waitsfx
    promptbutton
    givepoke(TOTODILE, 5, BERRY)
    closetext
    applymovement(PLAYER, AfterTotodileMovement)
    sjump(ElmDirectionsScript)
    SCRIPT_END
}
bool ChikoritaPokeBallScript(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_GOT_A_POKEMON_FROM_ELM)
    iftrue_jump(LookAtElmPokeBallScript)
    turnobject(ELMSLAB_ELM, DOWN)
    refreshscreen
    pokepic(CHIKORITA)
    playcry(CHIKORITA)
    waitbutton
    closepokepic
    opentext
    writetext(TakeChikoritaText)
    yesorno
    iffalse_jump(DidntChooseStarterScript)
    disappear(ELMSLAB_POKE_BALL3)
    setevent(EVENT_GOT_CHIKORITA_FROM_ELM)
    writetext(ChoseStarterText)
    promptbutton
    waitsfx
    getmonname(STRING_BUFFER_3, CHIKORITA)
    writetext(ReceivedStarterText)
    playsound(SFX_CAUGHT_MON)
    waitsfx
    promptbutton
    givepoke(CHIKORITA, 5, BERRY)
    closetext
    applymovement(PLAYER, AfterChikoritaMovement)
    sjump(ElmDirectionsScript)
    SCRIPT_END
}
bool DidntChooseStarterScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(DidntChooseStarterText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool ElmDirectionsScript(script_s* s) {
    SCRIPT_BEGIN
    turnobject(PLAYER, UP)
    opentext
    writetext(ElmDirectionsText1)
    waitbutton
    closetext
    addcellnum(PHONE_ELM)
    opentext
    writetext(GotElmsNumberText)
    playsound(SFX_REGISTER_PHONE_NUMBER)
    waitsfx
    waitbutton
    closetext
    turnobject(ELMSLAB_ELM, LEFT)
    opentext
    writetext(ElmDirectionsText2)
    waitbutton
    closetext
    turnobject(ELMSLAB_ELM, DOWN)
    opentext
    writetext(ElmDirectionsText3)
    waitbutton
    closetext
    setevent(EVENT_GOT_A_POKEMON_FROM_ELM)
    setevent(EVENT_RIVAL_CHERRYGROVE_CITY)
    setscene(SCENE_ELMSLAB_AIDE_GIVES_POTION)
    setmapscene(NEW_BARK_TOWN, SCENE_FINISHED)
    s_end
    SCRIPT_END
}
bool ElmDescribesMrPokemonScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(ElmDescribesMrPokemonText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool LookAtElmPokeBallScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(ElmPokeBallText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool ElmsLabHealingMachine(script_s* s) {
    SCRIPT_BEGIN
    opentext
    checkevent(EVENT_GOT_A_POKEMON_FROM_ELM)
    iftrue(CanHeal)
    writetext(ElmsLabHealingMachineText1)
    waitbutton
    closetext
    s_end
CanHeal:
    writetext(ElmsLabHealingMachineText2)
    yesorno
    iftrue_jump(ElmsLabHealingMachine_HealParty)
    closetext
    s_end
    SCRIPT_END
}
bool ElmsLabHealingMachine_HealParty(script_s* s) {
    SCRIPT_BEGIN
    special(StubbedTrainerRankings_Healings)
    special(HealParty)
    playmusic(MUSIC_NONE)
    setval(HEALMACHINE_ELMS_LAB)
    special(HealMachineAnim)
    pause(30)
    special(RestartMapMusic)
    closetext
    s_end
    SCRIPT_END
}
bool ElmAfterTheftDoneScript(script_s* s) {
    SCRIPT_BEGIN
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool ElmAfterTheftScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(ElmAfterTheftText1)
    checkitem(MYSTERY_EGG)
    iffalse_jump(ElmAfterTheftDoneScript)
    promptbutton
    writetext(ElmAfterTheftText2)
    waitbutton
    takeitem(MYSTERY_EGG, 1)
    scall(ElmJumpBackScript1)
    writetext(ElmAfterTheftText3)
    waitbutton
    scall(ElmJumpBackScript2)
    writetext(ElmAfterTheftText4)
    promptbutton
    writetext(ElmAfterTheftText5)
    promptbutton
    setevent(EVENT_GAVE_MYSTERY_EGG_TO_ELM)
    setflag(ENGINE_MAIN_MENU_MOBILE_CHOICES)
    setmapscene(ROUTE_29, SCENE_ROUTE29_CATCH_TUTORIAL)
    clearevent(EVENT_ROUTE_30_YOUNGSTER_JOEY)
    setevent(EVENT_ROUTE_30_BATTLE)
    writetext(ElmAfterTheftText6)
    waitbutton
    closetext
    setscene(SCENE_ELMSLAB_AIDE_GIVES_POKE_BALLS)
    s_end
    SCRIPT_END
}
bool ElmStudyingEggScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(ElmStudyingEggText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool ElmAideHasEggScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(ElmAideHasEggText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool ElmWaitingEggHatchScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(ElmWaitingEggHatchText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool ShowElmTogepiScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(ShowElmTogepiText1)
    waitbutton
    closetext
    showemote(EMOTE_SHOCK, ELMSLAB_ELM, 15)
    setevent(EVENT_SHOWED_TOGEPI_TO_ELM)
    opentext
    writetext(ShowElmTogepiText2)
    promptbutton
    writetext(ShowElmTogepiText3)
    promptbutton
    SCRIPT_FALLTHROUGH(ElmGiveEverstoneScript)
}
bool ElmGiveEverstoneScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(ElmGiveEverstoneText1)
    promptbutton
    verbosegiveitem(EVERSTONE, 1)
    iffalse_jump(ElmScript_NoRoomForEverstone)
    writetext(ElmGiveEverstoneText2)
    waitbutton
    closetext
    setevent(EVENT_GOT_EVERSTONE_FROM_ELM)
    s_end
    SCRIPT_END
}
bool ElmScript_CallYou(script_s* s) {
    SCRIPT_BEGIN
    writetext(ElmText_CallYou)
    waitbutton
    SCRIPT_FALLTHROUGH(ElmScript_NoRoomForEverstone)
}
bool ElmScript_NoRoomForEverstone(script_s* s) {
    SCRIPT_BEGIN
    closetext
    s_end
    SCRIPT_END
}
bool ElmGiveMasterBallScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(ElmGiveMasterBallText1)
    promptbutton
    verbosegiveitem(MASTER_BALL, 1)
    iffalse(notdone)
    setevent(EVENT_GOT_MASTER_BALL_FROM_ELM)
    writetext(ElmGiveMasterBallText2)
    waitbutton
notdone:
    closetext
    s_end
    SCRIPT_END
}
bool ElmGiveTicketScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(ElmGiveTicketText1)
    promptbutton
    verbosegiveitem(S_S_TICKET, 1)
    setevent(EVENT_GOT_SS_TICKET_FROM_ELM)
    writetext(ElmGiveTicketText2)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool ElmJumpBackScript1(script_s* s) {
    SCRIPT_BEGIN
    closetext
    readvar(VAR_FACING)
    ifequal_jump(DOWN, ElmJumpDownScript)
    ifequal_jump(UP, ElmJumpUpScript)
    ifequal_jump(LEFT, ElmJumpLeftScript)
    ifequal_jump(RIGHT, ElmJumpRightScript)
    s_end
    SCRIPT_END
}
bool ElmJumpBackScript2(script_s* s) {
    SCRIPT_BEGIN
    closetext
    readvar(VAR_FACING)
    ifequal_jump(DOWN, ElmJumpUpScript)
    ifequal_jump(UP, ElmJumpDownScript)
    ifequal_jump(LEFT, ElmJumpRightScript)
    ifequal_jump(RIGHT, ElmJumpLeftScript)
    s_end
    SCRIPT_END
}
bool ElmJumpUpScript(script_s* s) {
    SCRIPT_BEGIN
    applymovement(ELMSLAB_ELM, ElmJumpUpMovement)
    opentext
    s_end
    SCRIPT_END
}
bool ElmJumpDownScript(script_s* s) {
    SCRIPT_BEGIN
    applymovement(ELMSLAB_ELM, ElmJumpDownMovement)
    opentext
    s_end
    SCRIPT_END
}
bool ElmJumpLeftScript(script_s* s) {
    SCRIPT_BEGIN
    applymovement(ELMSLAB_ELM, ElmJumpLeftMovement)
    opentext
    s_end
    SCRIPT_END
}
bool ElmJumpRightScript(script_s* s) {
    SCRIPT_BEGIN
    applymovement(ELMSLAB_ELM, ElmJumpRightMovement)
    opentext
    s_end
    SCRIPT_END
}
bool AideScript_WalkPotion1(script_s* s) {
    SCRIPT_BEGIN
    applymovement(ELMSLAB_ELMS_AIDE, AideWalksRight1)
    turnobject(PLAYER, DOWN)
    scall(AideScript_GivePotion)
    applymovement(ELMSLAB_ELMS_AIDE, AideWalksLeft1)
    s_end
    SCRIPT_END
}
bool AideScript_WalkPotion2(script_s* s) {
    SCRIPT_BEGIN
    applymovement(ELMSLAB_ELMS_AIDE, AideWalksRight2)
    turnobject(PLAYER, DOWN)
    scall(AideScript_GivePotion)
    applymovement(ELMSLAB_ELMS_AIDE, AideWalksLeft2)
    s_end
    SCRIPT_END
}
bool AideScript_GivePotion(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(AideText_GiveYouPotion)
    promptbutton
    verbosegiveitem(POTION, 1)
    writetext(AideText_AlwaysBusy)
    waitbutton
    closetext
    setscene(SCENE_ELMSLAB_NOTHING)
    s_end
    SCRIPT_END
}
bool AideScript_WalkBalls1(script_s* s) {
    SCRIPT_BEGIN
    applymovement(ELMSLAB_ELMS_AIDE, AideWalksRight1)
    turnobject(PLAYER, DOWN)
    scall(AideScript_GiveYouBalls)
    applymovement(ELMSLAB_ELMS_AIDE, AideWalksLeft1)
    s_end
    SCRIPT_END
}
bool AideScript_WalkBalls2(script_s* s) {
    SCRIPT_BEGIN
    applymovement(ELMSLAB_ELMS_AIDE, AideWalksRight2)
    turnobject(PLAYER, DOWN)
    scall(AideScript_GiveYouBalls)
    applymovement(ELMSLAB_ELMS_AIDE, AideWalksLeft2)
    s_end
    SCRIPT_END
}
bool AideScript_GiveYouBalls(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(AideText_GiveYouBalls)
    promptbutton
    getitemname(STRING_BUFFER_4, POKE_BALL)
    scall(AideScript_ReceiveTheBalls)
    giveitem(POKE_BALL, 5)
    writetext(AideText_ExplainBalls)
    promptbutton
    itemnotify
    closetext
    setscene(SCENE_ELMSLAB_NOTHING)
    s_end
    SCRIPT_END
}
bool AideScript_ReceiveTheBalls(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(ReceiveItemScript)
    s_end
    SCRIPT_END
}
bool ElmsAideScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_TOGEPI_EGG_FROM_ELMS_AIDE)
    iftrue_jump(AideScript_AfterTheft)
    checkevent(EVENT_GAVE_MYSTERY_EGG_TO_ELM)
    iftrue_jump(AideScript_ExplainBalls)
    checkevent(EVENT_GOT_MYSTERY_EGG_FROM_MR_POKEMON)
    iftrue_jump(AideScript_TheftTestimony)
    writetext(AideText_AlwaysBusy)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool AideScript_TheftTestimony(script_s* s) {
    SCRIPT_BEGIN
    writetext(AideText_TheftTestimony)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool AideScript_ExplainBalls(script_s* s) {
    SCRIPT_BEGIN
    writetext(AideText_ExplainBalls)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool AideScript_AfterTheft(script_s* s) {
    SCRIPT_BEGIN
    writetext(AideText_AfterTheft)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool MeetCopScript2(script_s* s) {
    SCRIPT_BEGIN
    applymovement(PLAYER, MeetCopScript2_StepLeft)
    SCRIPT_FALLTHROUGH(MeetCopScript)
}
bool MeetCopScript(script_s* s) {
    SCRIPT_BEGIN
    applymovement(PLAYER, MeetCopScript_WalkUp)
    SCRIPT_FALLTHROUGH(CopScript)
}
bool CopScript(script_s* s) {
    SCRIPT_BEGIN
    turnobject(ELMSLAB_OFFICER, LEFT)
    opentext
    writetext(ElmsLabOfficerText1)
    promptbutton
    special(NameRival)
    writetext(ElmsLabOfficerText2)
    waitbutton
    closetext
    applymovement(ELMSLAB_OFFICER, OfficerLeavesMovement)
    disappear(ELMSLAB_OFFICER)
    setscene(SCENE_ELMSLAB_NOTHING)
    s_end
    SCRIPT_END
}
bool ElmsLabWindow(script_s* s) {
    SCRIPT_BEGIN
    opentext
    checkflag(ENGINE_FLYPOINT_VIOLET)
    iftrue(Normal)
    checkevent(EVENT_ELM_CALLED_ABOUT_STOLEN_POKEMON)
    iftrue(BreakIn)
    goto Normal;
BreakIn:
    writetext(ElmsLabWindowText2)
    waitbutton
    closetext
    s_end
Normal:
    writetext(ElmsLabWindowText1)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool ElmsLabTravelTip1(script_s* s) {
    SCRIPT_BEGIN
    jumptext(ElmsLabTravelTip1Text)
    SCRIPT_END
}
bool ElmsLabTravelTip2(script_s* s) {
    SCRIPT_BEGIN
    jumptext(ElmsLabTravelTip2Text)
    SCRIPT_END
}
bool ElmsLabTravelTip3(script_s* s) {
    SCRIPT_BEGIN
    jumptext(ElmsLabTravelTip3Text)
    SCRIPT_END
}
bool ElmsLabTravelTip4(script_s* s) {
    SCRIPT_BEGIN
    jumptext(ElmsLabTravelTip4Text)
    SCRIPT_END
}
bool ElmsLabTrashcan(script_s* s) {
    SCRIPT_BEGIN
    jumptext(ElmsLabTrashcanText)
    SCRIPT_END
}
bool ElmsLabPC(script_s* s) {
    SCRIPT_BEGIN
    jumptext(ElmsLabPCText)
    SCRIPT_END
}
bool ElmsLabTrashcan2(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(TrashCanScript)
    SCRIPT_END
}
bool ElmsLabBookshelf(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(DifficultBookshelfScript)
    SCRIPT_END
}
const uint8_t ElmsLab_WalkUpToElmMovement[] = {
    step(UP),
    step(UP),
    step(UP),
    step(UP),
    step(UP),
    step(UP),
    step(UP),
    turn_head(LEFT),
    movement_step_end,
};
const uint8_t ElmsLab_CantLeaveMovement[] = {
    step(UP),
    movement_step_end,
};
const uint8_t MeetCopScript2_StepLeft[] = {
    step(LEFT),
    movement_step_end,
};
const uint8_t MeetCopScript_WalkUp[] = {
    step(UP),
    step(UP),
    turn_head(RIGHT),
    movement_step_end,
};
const uint8_t OfficerLeavesMovement[] = {
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    movement_step_end,
};
const uint8_t AideWalksRight1[] = {
    step(RIGHT),
    step(RIGHT),
    turn_head(UP),
    movement_step_end,
};
const uint8_t AideWalksRight2[] = {
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    turn_head(UP),
    movement_step_end,
};
const uint8_t AideWalksLeft1[] = {
    step(LEFT),
    step(LEFT),
    turn_head(DOWN),
    movement_step_end,
};
const uint8_t AideWalksLeft2[] = {
    step(LEFT),
    step(LEFT),
    step(LEFT),
    turn_head(DOWN),
    movement_step_end,
};
const uint8_t ElmJumpUpMovement[] = {
    movement_fix_facing,
    big_step(UP),
    movement_remove_fixed_facing,
    movement_step_end,
};
const uint8_t ElmJumpDownMovement[] = {
    movement_fix_facing,
    big_step(DOWN),
    movement_remove_fixed_facing,
    movement_step_end,
};
const uint8_t ElmJumpLeftMovement[] = {
    movement_fix_facing,
    big_step(LEFT),
    movement_remove_fixed_facing,
    movement_step_end,
};
const uint8_t ElmJumpRightMovement[] = {
    movement_fix_facing,
    big_step(RIGHT),
    movement_remove_fixed_facing,
    movement_step_end,
};
const uint8_t ElmsLab_ElmToDefaultPositionMovement1[] = {
    step(UP),
    movement_step_end,
};
const uint8_t ElmsLab_ElmToDefaultPositionMovement2[] = {
    step(RIGHT),
    step(RIGHT),
    step(UP),
    turn_head(DOWN),
    movement_step_end,
};
const uint8_t AfterCyndaquilMovement[] = {
    step(LEFT),
    step(UP),
    turn_head(UP),
    movement_step_end,
};
const uint8_t AfterTotodileMovement[] = {
    step(LEFT),
    step(LEFT),
    step(UP),
    turn_head(UP),
    movement_step_end,
};
const uint8_t AfterChikoritaMovement[] = {
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(UP),
    turn_head(UP),
    movement_step_end,
};
const txt_cmd_s ElmText_Intro[] = {
    text_start("ELM: <PLAY_G>!"
        t_line "There you are!"
        t_para "I needed to ask"
        t_line "you a favor."
        t_para "I'm conducting new"
        t_line "#MON research"
        t_para "right now. I was"
        t_line "wondering if you"
        t_para "could help me with"
        t_line "it, <PLAY_G>."
        t_para "You see…"
        t_para "I'm writing a"
        t_line "paper that I want"
        t_para "to present at a"
        t_line "conference."
        t_para "But there are some"
        t_line "things I don't"
        t_para "quite understand"
        t_line "yet."
        t_para "So!"
        t_para "I'd like you to"
        t_line "raise a #MON"
        t_para "that I recently"
        t_line "caught."
        t_done )
};
const txt_cmd_s ElmText_Accepted[] = {
    text_start("Thanks, <PLAY_G>!"
        t_para "You're a great"
        t_line "help!"
        t_done )
};
const txt_cmd_s ElmText_Refused[] = {
    text_start("But… Please, I"
        t_line "need your help!"
        t_done )
};
const txt_cmd_s ElmText_ResearchAmbitions[] = {
    text_start("When I announce my"
        t_line "findings, I'm sure"
        t_para "we'll delve a bit"
        t_line "deeper into the"
        t_para "many mysteries of"
        t_line "#MON."
        t_para "You can count on"
        t_line "it!"
        t_done )
};
const txt_cmd_s ElmText_GotAnEmail[] = {
    text_start("Oh, hey! I got an"
        t_line "e-mail!"
        t_para "<……><……><……>"
        t_line "Hm… Uh-huh…"
        t_para "Okay…"
        t_done )
};
const txt_cmd_s ElmText_MissionFromMrPokemon[] = {
    text_start("Hey, listen."
        t_para "I have an acquain-"
        t_line "tance called MR."
        t_cont "#MON."
        t_para "He keeps finding"
        t_line "weird things and"
        t_para "raving about his"
        t_line "discoveries."
        t_para "Anyway, I just got"
        t_line "an e-mail from him"
        t_para "saying that this"
        t_line "time it's real."
        t_para "It is intriguing,"
        t_line "but we're busy"
        t_para "with our #MON"
        t_line "research…"
        t_para "Wait!"
        t_para "I know!"
        t_para "<PLAY_G>, can you"
        t_line "go in our place?"
        t_done )
};
const txt_cmd_s ElmText_ChooseAPokemon[] = {
    text_start("I want you to"
        t_line "raise one of the"
        t_para "#MON contained"
        t_line "in these BALLS."
        t_para "You'll be that"
        t_line "#MON's first"
        t_cont "partner, <PLAY_G>!"
        t_para "Go on. Pick one!"
        t_done )
};
const txt_cmd_s ElmText_LetYourMonBattleIt[] = {
    text_start("If a wild #MON"
        t_line "appears, let your"
        t_cont "#MON battle it!"
        t_done )
};
const txt_cmd_s LabWhereGoingText[] = {
    text_start("ELM: Wait! Where"
        t_line "are you going?"
        t_done )
};
const txt_cmd_s TakeCyndaquilText[] = {
    text_start("ELM: You'll take"
        t_line "CYNDAQUIL, the"
        t_cont "fire #MON?"
        t_done )
};
const txt_cmd_s TakeTotodileText[] = {
    text_start("ELM: Do you want"
        t_line "TOTODILE, the"
        t_cont "water #MON?"
        t_done )
};
const txt_cmd_s TakeChikoritaText[] = {
    text_start("ELM: So, you like"
        t_line "CHIKORITA, the"
        t_cont "grass #MON?"
        t_done )
};
const txt_cmd_s DidntChooseStarterText[] = {
    text_start("ELM: Think it over"
        t_line "carefully."
        t_para "Your partner is"
        t_line "important."
        t_done )
};
const txt_cmd_s ChoseStarterText[] = {
    text_start("ELM: I think"
        t_line "that's a great"
        t_cont "#MON too!"
        t_done )
};
const txt_cmd_s ReceivedStarterText[] = {
    text_start("<PLAYER> received"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("!"
        t_done )
};
const txt_cmd_s ElmDirectionsText1[] = {
    text_start("MR.#MON lives a"
        t_line "little bit beyond"
        t_para "CHERRYGROVE, the"
        t_line "next city over."
        t_para "It's almost a"
        t_line "direct route"
        t_para "there, so you"
        t_line "can't miss it."
        t_para "But just in case,"
        t_line "here's my phone"
        t_para "number. Call me if"
        t_line "anything comes up!"
        t_done )
};
const txt_cmd_s ElmDirectionsText2[] = {
    text_start("If your #MON is"
        t_line "hurt, you should"
        t_para "heal it with this"
        t_line "machine."
        t_para "Feel free to use"
        t_line "it anytime."
        t_done )
};
const txt_cmd_s ElmDirectionsText3[] = {
    text_start("<PLAY_G>, I'm"
        t_line "counting on you!"
        t_done )
};
const txt_cmd_s GotElmsNumberText[] = {
    text_start("<PLAYER> got ELM's"
        t_line "phone number."
        t_done )
};
const txt_cmd_s ElmDescribesMrPokemonText[] = {
    text_start("MR.#MON goes"
        t_line "everywhere and"
        t_cont "finds rarities."
        t_para "Too bad they're"
        t_line "just rare and"
        t_cont "not very useful…"
        t_done )
};
const txt_cmd_s ElmPokeBallText[] = {
    text_start("It contains a"
        t_line "#MON caught by"
        t_cont "PROF.ELM."
        t_done )
};
const txt_cmd_s ElmsLabHealingMachineText1[] = {
    text_start("I wonder what this"
        t_line "does?"
        t_done )
};
const txt_cmd_s ElmsLabHealingMachineText2[] = {
    text_start("Would you like to"
        t_line "heal your #MON?"
        t_done )
};
const txt_cmd_s ElmAfterTheftText1[] = {
    text_start("ELM: <PLAY_G>, this"
        t_line "is terrible…"
        t_para "Oh, yes, what was"
        t_line "MR.#MON's big"
        t_cont "discovery?"
        t_done )
};
const txt_cmd_s ElmAfterTheftText2[] = {
    text_start("<PLAYER> handed"
        t_line "the MYSTERY EGG to"
        t_cont "PROF.ELM."
        t_done )
};
const txt_cmd_s ElmAfterTheftText3[] = {
    text_start("ELM: This?"
        t_done )
};
const txt_cmd_s ElmAfterTheftText4[] = {
    text_start("But… Is it a"
        t_line "#MON EGG?"
        t_para "If it is, it is a"
        t_line "great discovery!"
        t_done )
};
const txt_cmd_s ElmAfterTheftText5[] = {
    text_start("ELM: What?!?"
        t_para "PROF.OAK gave you"
        t_line "a #DEX?"
        t_para "<PLAY_G>, is that"
        t_line "true? Th-that's"
        t_cont "incredible!"
        t_para "He is superb at"
        t_line "seeing the poten-"
        t_cont "tial of people as"
        t_cont "trainers."
        t_para "Wow, <PLAY_G>. You"
        t_line "may have what it"
        t_para "takes to become"
        t_line "the CHAMPION."
        t_para "You seem to be"
        t_line "getting on great"
        t_cont "with #MON too."
        t_para "You should take"
        t_line "the #MON GYM"
        t_cont "challenge."
        t_para "The closest GYM"
        t_line "would be the one"
        t_cont "in VIOLET CITY."
        t_done )
};
const txt_cmd_s ElmAfterTheftText6[] = {
    text_start("…<PLAY_G>. The"
        t_line "road to the"
        t_para "championship will"
        t_line "be a long one."
        t_para "Before you leave,"
        t_line "make sure that you"
        t_cont "talk to your mom."
        t_done )
};
const txt_cmd_s ElmStudyingEggText[] = {
    text_start("ELM: Don't give"
        t_line "up! I'll call if"
        t_para "I learn anything"
        t_line "about that EGG!"
        t_done )
};
const txt_cmd_s ElmAideHasEggText[] = {
    text_start("ELM: <PLAY_G>?"
        t_line "Didn't you meet my"
        t_cont "assistant?"
        t_para "He should have met"
        t_line "you with the EGG"
        t_para "at VIOLET CITY's"
        t_line "#MON CENTER."
        t_para "You must have just"
        t_line "missed him. Try to"
        t_cont "catch him there."
        t_done )
};
const txt_cmd_s ElmWaitingEggHatchText[] = {
    text_start("ELM: Hey, has that"
        t_line "EGG changed any?"
        t_done )
};
const txt_cmd_s ElmThoughtEggHatchedText[] = {
    text_start("<PLAY_G>? I thought"
        t_line "the EGG hatched."
        t_para "Where is the"
        t_line "#MON?"
        t_done )
};
const txt_cmd_s ShowElmTogepiText1[] = {
    text_start("ELM: <PLAY_G>, you"
        t_line "look great!"
        t_done )
};
const txt_cmd_s ShowElmTogepiText2[] = {
    text_start("What?"
        t_line "That #MON!?!"
        t_done )
};
const txt_cmd_s ShowElmTogepiText3[] = {
    text_start("The EGG hatched!"
        t_line "So, #MON are"
        t_cont "born from EGGS…"
        t_para "No, perhaps not"
        t_line "all #MON are."
        t_para "Wow, there's still"
        t_line "a lot of research"
        t_cont "to be done."
        t_done )
};
const txt_cmd_s ElmGiveEverstoneText1[] = {
    text_start("Thanks, <PLAY_G>!"
        t_line "You're helping"
        t_para "unravel #MON"
        t_line "mysteries for us!"
        t_para "I want you to have"
        t_line "this as a token of"
        t_cont "our appreciation."
        t_done )
};
const txt_cmd_s ElmGiveEverstoneText2[] = {
    text_start("That's an"
        t_line "EVERSTONE."
        t_para "Some species of"
        t_line "#MON evolve"
        t_para "when they grow to"
        t_line "certain levels."
        t_para "A #MON holding"
        t_line "the EVERSTONE"
        t_cont "won't evolve."
        t_para "Give it to a #-"
        t_line "MON you don't want"
        t_cont "to evolve."
        t_done )
};
const txt_cmd_s ElmText_CallYou[] = {
    text_start("ELM: <PLAY_G>, I'll"
        t_line "call you if any-"
        t_cont "thing comes up."
        t_done )
};
const txt_cmd_s AideText_AfterTheft[] = {
    text_start("…sigh… That"
        t_line "stolen #MON."
        t_para "I wonder how it's"
        t_line "doing."
        t_para "They say a #MON"
        t_line "raised by a bad"
        t_para "person turns bad"
        t_line "itself."
        t_done )
};
const txt_cmd_s ElmGiveMasterBallText1[] = {
    text_start("ELM: Hi, <PLAY_G>!"
        t_line "Thanks to you, my"
        t_para "research is going"
        t_line "great!"
        t_para "Take this as a"
        t_line "token of my"
        t_cont "appreciation."
        t_done )
};
const txt_cmd_s ElmGiveMasterBallText2[] = {
    text_start("The MASTER BALL is"
        t_line "the best!"
        t_para "It's the ultimate"
        t_line "BALL! It'll catch"
        t_para "any #MON with-"
        t_line "out fail."
        t_para "It's given only to"
        t_line "recognized #MON"
        t_cont "researchers."
        t_para "I think you can"
        t_line "make much better"
        t_para "use of it than I"
        t_line "can, <PLAY_G>!"
        t_done )
};
const txt_cmd_s ElmGiveTicketText1[] = {
    text_start("ELM: <PLAY_G>!"
        t_line "There you are!"
        t_para "I called because I"
        t_line "have something for"
        t_cont "you."
        t_para "See? It's an"
        t_line "S.S.TICKET."
        t_para "Now you can catch"
        t_line "#MON in KANTO."
        t_done )
};
const txt_cmd_s ElmGiveTicketText2[] = {
    text_start("The ship departs"
        t_line "from OLIVINE CITY."
        t_para "But you knew that"
        t_line "already, <PLAY_G>."
        t_para "After all, you've"
        t_line "traveled all over"
        t_cont "with your #MON."
        t_para "Give my regards to"
        t_line "PROF.OAK in KANTO!"
        t_done )
};
const txt_cmd_s ElmsLabMonEggText[] = {
    text_start("It's the #MON"
        t_line "EGG being studied"
        t_cont "by PROF.ELM."
        t_done )
};
const txt_cmd_s AideText_GiveYouPotion[] = {
    text_start("<PLAY_G>, I want"
        t_line "you to have this"
        t_cont "for your errand."
        t_done )
};
const txt_cmd_s AideText_AlwaysBusy[] = {
    text_start("There are only two"
        t_line "of us, so we're"
        t_cont "always busy."
        t_done )
};
const txt_cmd_s AideText_TheftTestimony[] = {
    text_start("There was a loud"
        t_line "noise outside…"
        t_para "When we went to"
        t_line "look, someone"
        t_cont "stole a #MON."
        t_para "It's unbelievable"
        t_line "that anyone would"
        t_cont "do that!"
        t_para "…sigh… That"
        t_line "stolen #MON."
        t_para "I wonder how it's"
        t_line "doing."
        t_para "They say a #MON"
        t_line "raised by a bad"
        t_para "person turns bad"
        t_line "itself."
        t_done )
};
const txt_cmd_s AideText_GiveYouBalls[] = {
    text_start("<PLAY_G>!"
        t_para "Use these on your"
        t_line "#DEX quest!"
        t_done )
};
const txt_cmd_s AideText_ExplainBalls[] = {
    text_start("To add to your"
        t_line "#DEX, you have"
        t_cont "to catch #MON."
        t_para "Throw # BALLS"
        t_line "at wild #MON"
        t_cont "to get them."
        t_done )
};
const txt_cmd_s ElmsLabOfficerText1[] = {
    text_start("I heard a #MON"
        t_line "was stolen here…"
        t_para "I was just getting"
        t_line "some information"
        t_cont "from PROF.ELM."
        t_para "Apparently, it was"
        t_line "a young male with"
        t_cont "long, red hair…"
        t_para "What?"
        t_para "You battled a"
        t_line "trainer like that?"
        t_para "Did you happen to"
        t_line "get his name?"
        t_done )
};
const txt_cmd_s ElmsLabOfficerText2[] = {
    text_start("OK! So <RIVAL>"
        t_line "was his name."
        t_para "Thanks for helping"
        t_line "my investigation!"
        t_done )
};
const txt_cmd_s ElmsLabWindowText1[] = {
    text_start("The window's open."
        t_para "A pleasant breeze"
        t_line "is blowing in."
        t_done )
};
const txt_cmd_s ElmsLabWindowText2[] = {
    text_start("He broke in"
        t_line "through here!"
        t_done )
};
const txt_cmd_s ElmsLabTravelTip1Text[] = {
    text_start("<PLAYER> opened a"
        t_line "book."
        t_para "Travel Tip 1:"
        t_para "Press START to"
        t_line "open the MENU."
        t_done )
};
const txt_cmd_s ElmsLabTravelTip2Text[] = {
    text_start("<PLAYER> opened a"
        t_line "book."
        t_para "Travel Tip 2:"
        t_para "Record your trip"
        t_line "with SAVE!"
        t_done )
};
const txt_cmd_s ElmsLabTravelTip3Text[] = {
    text_start("<PLAYER> opened a"
        t_line "book."
        t_para "Travel Tip 3:"
        t_para "Open your PACK and"
        t_line "press SELECT to"
        t_cont "move items."
        t_done )
};
const txt_cmd_s ElmsLabTravelTip4Text[] = {
    text_start("<PLAYER> opened a"
        t_line "book."
        t_para "Travel Tip 4:"
        t_para "Check your #MON"
        t_line "moves. Press the"
        t_para "A Button to switch"
        t_line "moves."
        t_done )
};
const txt_cmd_s ElmsLabTrashcanText[] = {
    text_start("The wrapper from"
        t_line "the snack PROF.ELM"
        t_cont "ate is in there…"
        t_done )
};
const txt_cmd_s ElmsLabPCText[] = {
    text_start("OBSERVATIONS ON"
        t_line "#MON EVOLUTION"
        t_para "…It says on the"
        t_line "screen…"
        t_done )
    //db(0, 0) // filler
};
