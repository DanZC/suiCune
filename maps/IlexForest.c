#include "../constants.h"
#include "../util/scripting.h"
#include "IlexForest.h"
//// EVENTS
enum {
    ILEXFOREST_FARFETCHD = 2,
    ILEXFOREST_YOUNGSTER1,
    ILEXFOREST_BLACK_BELT,
    ILEXFOREST_ROCKER,
    ILEXFOREST_POKE_BALL1,
    ILEXFOREST_KURT,
    ILEXFOREST_LASS,
    ILEXFOREST_YOUNGSTER2,
    ILEXFOREST_POKE_BALL2,
    ILEXFOREST_POKE_BALL3,
    ILEXFOREST_POKE_BALL4,
};

const Script_fn_t IlexForest_SceneScripts[] = {
    0,
};

const struct MapCallback IlexForest_MapCallbacks[] = {
    map_callback(MAPCALLBACK_OBJECTS, IlexForest_MapScripts_FarfetchdCallback),
};

const struct MapScripts IlexForest_MapScripts = {
    .scene_script_count = 0, // lengthof(IlexForest_SceneScripts),
    .scene_scripts = IlexForest_SceneScripts,

    .callback_count = lengthof(IlexForest_MapCallbacks),
    .callbacks = IlexForest_MapCallbacks,
};

static const struct CoordEvent IlexForest_CoordEvents[] = {
    0,
};

static const struct BGEvent IlexForest_BGEvents[] = {
    bg_event(3, 17, BGEVENT_READ, &IlexForestSignpost),
    bg_event(11, 7, BGEVENT_ITEM, &IlexForestHiddenEther),
    bg_event(22, 14, BGEVENT_ITEM, &IlexForestHiddenSuperPotion),
    bg_event(1, 17, BGEVENT_ITEM, &IlexForestHiddenFullHeal),
    bg_event(8, 22, BGEVENT_UP, &IlexForestShrineScript),
};

static const struct WarpEventData IlexForest_WarpEvents[] = {
    warp_event(1, 5, ROUTE_34_ILEX_FOREST_GATE, 3),
    warp_event(3, 42, ILEX_FOREST_AZALEA_GATE, 1),
    warp_event(3, 43, ILEX_FOREST_AZALEA_GATE, 2),
};

static const struct ObjEvent IlexForest_ObjectEvents[] = {
    object_event(14, 31, SPRITE_BIRD, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, &IlexForestFarfetchdScript, EVENT_ILEX_FOREST_FARFETCHD),
    object_event(7, 28, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &IlexForestCharcoalApprenticeScript, EVENT_ILEX_FOREST_APPRENTICE),
    object_event(5, 28, SPRITE_BLACK_BELT, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &IlexForestCharcoalMasterScript, EVENT_ILEX_FOREST_CHARCOAL_MASTER),
    object_event(15, 14, SPRITE_ROCKER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &IlexForestHeadbuttGuyScript, -1),
    object_event(20, 32, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &IlexForestRevive, EVENT_ILEX_FOREST_REVIVE),
    object_event(8, 29, SPRITE_KURT, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, EVENT_ILEX_FOREST_KURT),
    object_event(3, 24, SPRITE_LASS, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &IlexForestLassScript, EVENT_ILEX_FOREST_LASS),
    object_event(12, 1, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 0, &TrainerBugCatcherWayne, -1),
    object_event(9, 17, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &IlexForestXAttack, EVENT_ILEX_FOREST_X_ATTACK),
    object_event(17, 7, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &IlexForestAntidote, EVENT_ILEX_FOREST_ANTIDOTE),
    object_event(27, 1, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &IlexForestEther, EVENT_ILEX_FOREST_ETHER),
};

const struct MapEvents IlexForest_MapEvents = {
    .warp_event_count = lengthof(IlexForest_WarpEvents),
    .warp_events = IlexForest_WarpEvents,

    .coord_event_count = 0, // lengthof(IlexForest_CoordEvents),
    .coord_events = IlexForest_CoordEvents,

    .bg_event_count = lengthof(IlexForest_BGEvents),
    .bg_events = IlexForest_BGEvents,

    .obj_event_count = lengthof(IlexForest_ObjectEvents),
    .obj_events = IlexForest_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "IlexForest.h"

bool IlexForest_MapScripts_FarfetchdCallback(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_GOT_HM01_CUT)
    iftrue_jump(IlexForest_MapScripts_Static)
    readmem(&gPlayer.farfetchdPosition)
    ifequal_jump(1, IlexForest_MapScripts_PositionOne)
    ifequal_jump(2, IlexForest_MapScripts_PositionTwo)
    ifequal_jump(3, IlexForest_MapScripts_PositionThree)
    ifequal_jump(4, IlexForest_MapScripts_PositionFour)
    ifequal_jump(5, IlexForest_MapScripts_PositionFive)
    ifequal_jump(6, IlexForest_MapScripts_PositionSix)
    ifequal_jump(7, IlexForest_MapScripts_PositionSeven)
    ifequal_jump(8, IlexForest_MapScripts_PositionEight)
    ifequal_jump(9, IlexForest_MapScripts_PositionNine)
    ifequal_jump(10, IlexForest_MapScripts_PositionTen)
    SCRIPT_FALLTHROUGH(IlexForest_MapScripts_Static)
}
bool IlexForest_MapScripts_Static(script_s* s) {
    SCRIPT_BEGIN
    s_endcallback
    SCRIPT_END
}
bool IlexForest_MapScripts_PositionOne(script_s* s) {
    SCRIPT_BEGIN
    moveobject(ILEXFOREST_FARFETCHD, 14, 31)
    appear(ILEXFOREST_FARFETCHD)
    s_endcallback
    SCRIPT_END
}
bool IlexForest_MapScripts_PositionTwo(script_s* s) {
    SCRIPT_BEGIN
    moveobject(ILEXFOREST_FARFETCHD, 15, 25)
    appear(ILEXFOREST_FARFETCHD)
    s_endcallback
    SCRIPT_END
}
bool IlexForest_MapScripts_PositionThree(script_s* s) {
    SCRIPT_BEGIN
    moveobject(ILEXFOREST_FARFETCHD, 20, 24)
    appear(ILEXFOREST_FARFETCHD)
    s_endcallback
    SCRIPT_END
}
bool IlexForest_MapScripts_PositionFour(script_s* s) {
    SCRIPT_BEGIN
    moveobject(ILEXFOREST_FARFETCHD, 29, 22)
    appear(ILEXFOREST_FARFETCHD)
    s_endcallback
    SCRIPT_END
}
bool IlexForest_MapScripts_PositionFive(script_s* s) {
    SCRIPT_BEGIN
    moveobject(ILEXFOREST_FARFETCHD, 28, 31)
    appear(ILEXFOREST_FARFETCHD)
    s_endcallback
    SCRIPT_END
}
bool IlexForest_MapScripts_PositionSix(script_s* s) {
    SCRIPT_BEGIN
    moveobject(ILEXFOREST_FARFETCHD, 24, 35)
    appear(ILEXFOREST_FARFETCHD)
    s_endcallback
    SCRIPT_END
}
bool IlexForest_MapScripts_PositionSeven(script_s* s) {
    SCRIPT_BEGIN
    moveobject(ILEXFOREST_FARFETCHD, 22, 31)
    appear(ILEXFOREST_FARFETCHD)
    s_endcallback
    SCRIPT_END
}
bool IlexForest_MapScripts_PositionEight(script_s* s) {
    SCRIPT_BEGIN
    moveobject(ILEXFOREST_FARFETCHD, 15, 29)
    appear(ILEXFOREST_FARFETCHD)
    s_endcallback
    SCRIPT_END
}
bool IlexForest_MapScripts_PositionNine(script_s* s) {
    SCRIPT_BEGIN
    moveobject(ILEXFOREST_FARFETCHD, 10, 35)
    appear(ILEXFOREST_FARFETCHD)
    s_endcallback
    SCRIPT_END
}
bool IlexForest_MapScripts_PositionTen(script_s* s) {
    SCRIPT_BEGIN
    moveobject(ILEXFOREST_FARFETCHD, 6, 28)
    appear(ILEXFOREST_FARFETCHD)
    s_endcallback
    SCRIPT_END
}
bool IlexForestCharcoalApprenticeScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_HERDED_FARFETCHD)
    iftrue(DoneFarfetchd)
    writetext(IlexForestApprenticeIntroText)
    waitbutton
    closetext
    s_end
DoneFarfetchd:
    writetext(IlexForestApprenticeAfterText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool IlexForestFarfetchdScript(script_s* s) {
    SCRIPT_BEGIN
    readmem(&gPlayer.farfetchdPosition)
    ifequal(1, Position1)
    ifequal(2, Position2)
    ifequal(3, Position3)
    ifequal(4, Position4)
    ifequal(5, Position5)
    ifequal(6, Position6)
    ifequal(7, Position7)
    ifequal(8, Position8)
    ifequal(9, Position9)
    ifequal(10, Position10)
Position1:
    faceplayer
    opentext
    writetext(Text_ItsTheMissingPokemon)
    promptbutton
    writetext(Text_Kwaaaa)
    playcry(FARFETCH_D)
    waitbutton
    closetext
    applymovement(ILEXFOREST_FARFETCHD, MovementData_Farfetchd_Pos1_Pos2)
    moveobject(ILEXFOREST_FARFETCHD, 15, 25)
    disappear(ILEXFOREST_FARFETCHD)
    appear(ILEXFOREST_FARFETCHD)
    loadmem(&gPlayer.farfetchdPosition, 2)
    s_end
Position2:
    scall_local(CryAndCheckFacing);
    ifequal(DOWN, Position2_Down)
    applymovement(ILEXFOREST_FARFETCHD, MovementData_Farfetchd_Pos2_Pos3)
    moveobject(ILEXFOREST_FARFETCHD, 20, 24)
    disappear(ILEXFOREST_FARFETCHD)
    appear(ILEXFOREST_FARFETCHD)
    loadmem(&gPlayer.farfetchdPosition, 3)
    s_end
Position2_Down:
    applymovement(ILEXFOREST_FARFETCHD, MovementData_Farfetchd_Pos2_Pos8)
    moveobject(ILEXFOREST_FARFETCHD, 15, 29)
    disappear(ILEXFOREST_FARFETCHD)
    appear(ILEXFOREST_FARFETCHD)
    loadmem(&gPlayer.farfetchdPosition, 8)
    s_end
Position3:
    scall_local(CryAndCheckFacing);
    ifequal(LEFT, Position3_Left)
    applymovement(ILEXFOREST_FARFETCHD, MovementData_Farfetchd_Pos3_Pos4)
    moveobject(ILEXFOREST_FARFETCHD, 29, 22)
    disappear(ILEXFOREST_FARFETCHD)
    appear(ILEXFOREST_FARFETCHD)
    loadmem(&gPlayer.farfetchdPosition, 4)
    s_end
Position3_Left:
    applymovement(ILEXFOREST_FARFETCHD, MovementData_Farfetchd_Pos3_Pos2)
    moveobject(ILEXFOREST_FARFETCHD, 15, 25)
    disappear(ILEXFOREST_FARFETCHD)
    appear(ILEXFOREST_FARFETCHD)
    loadmem(&gPlayer.farfetchdPosition, 2)
    s_end
Position4:
    scall_local(CryAndCheckFacing);
    ifequal(UP, Position4_Up)
    applymovement(ILEXFOREST_FARFETCHD, MovementData_Farfetchd_Pos4_Pos5)
    moveobject(ILEXFOREST_FARFETCHD, 28, 31)
    disappear(ILEXFOREST_FARFETCHD)
    appear(ILEXFOREST_FARFETCHD)
    loadmem(&gPlayer.farfetchdPosition, 5)
    s_end
Position4_Up:
    applymovement(ILEXFOREST_FARFETCHD, MovementData_Farfetchd_Pos4_Pos3)
    moveobject(ILEXFOREST_FARFETCHD, 20, 24)
    disappear(ILEXFOREST_FARFETCHD)
    appear(ILEXFOREST_FARFETCHD)
    loadmem(&gPlayer.farfetchdPosition, 3)
    s_end
Position5:
    scall_local(CryAndCheckFacing);
    ifequal(UP, Position5_Up)
    ifequal(LEFT, Position5_Left)
    ifequal(RIGHT, Position5_Right)
    applymovement(ILEXFOREST_FARFETCHD, MovementData_Farfetchd_Pos5_Pos6)
    moveobject(ILEXFOREST_FARFETCHD, 24, 35)
    disappear(ILEXFOREST_FARFETCHD)
    appear(ILEXFOREST_FARFETCHD)
    loadmem(&gPlayer.farfetchdPosition, 6)
    s_end
Position5_Left:
    applymovement(ILEXFOREST_FARFETCHD, MovementData_Farfetchd_Pos5_Pos7)
    moveobject(ILEXFOREST_FARFETCHD, 22, 31)
    disappear(ILEXFOREST_FARFETCHD)
    appear(ILEXFOREST_FARFETCHD)
    loadmem(&gPlayer.farfetchdPosition, 7)
    s_end
Position5_Up:
    applymovement(ILEXFOREST_FARFETCHD, MovementData_Farfetched_Pos5_Pos4_Up)
    moveobject(ILEXFOREST_FARFETCHD, 29, 22)
    disappear(ILEXFOREST_FARFETCHD)
    appear(ILEXFOREST_FARFETCHD)
    loadmem(&gPlayer.farfetchdPosition, 4)
    s_end
Position5_Right:
    applymovement(ILEXFOREST_FARFETCHD, MovementData_Farfetched_Pos5_Pos4_Right)
    moveobject(ILEXFOREST_FARFETCHD, 29, 22)
    disappear(ILEXFOREST_FARFETCHD)
    appear(ILEXFOREST_FARFETCHD)
    loadmem(&gPlayer.farfetchdPosition, 4)
    s_end
Position6:
    scall_local(CryAndCheckFacing);
    ifequal(RIGHT, Position6_Right)
    applymovement(ILEXFOREST_FARFETCHD, MovementData_Farfetched_Pos6_Pos7)
    moveobject(ILEXFOREST_FARFETCHD, 22, 31)
    disappear(ILEXFOREST_FARFETCHD)
    appear(ILEXFOREST_FARFETCHD)
    loadmem(&gPlayer.farfetchdPosition, 7)
    s_end
Position6_Right:
    applymovement(ILEXFOREST_FARFETCHD, MovementData_Farfetched_Pos6_Pos5)
    moveobject(ILEXFOREST_FARFETCHD, 28, 31)
    disappear(ILEXFOREST_FARFETCHD)
    appear(ILEXFOREST_FARFETCHD)
    loadmem(&gPlayer.farfetchdPosition, 5)
    s_end
Position7:
    scall_local(CryAndCheckFacing);
    ifequal(DOWN, Position7_Down)
    ifequal(LEFT, Position7_Left)
    applymovement(ILEXFOREST_FARFETCHD, MovementData_Farfetched_Pos7_Pos8)
    moveobject(ILEXFOREST_FARFETCHD, 15, 29)
    disappear(ILEXFOREST_FARFETCHD)
    appear(ILEXFOREST_FARFETCHD)
    loadmem(&gPlayer.farfetchdPosition, 8)
    s_end
Position7_Left:
    applymovement(ILEXFOREST_FARFETCHD, MovementData_Farfetched_Pos7_Pos6)
    moveobject(ILEXFOREST_FARFETCHD, 24, 35)
    disappear(ILEXFOREST_FARFETCHD)
    appear(ILEXFOREST_FARFETCHD)
    loadmem(&gPlayer.farfetchdPosition, 6)
    s_end
Position7_Down:
    applymovement(ILEXFOREST_FARFETCHD, MovementData_Farfetched_Pos7_Pos5)
    moveobject(ILEXFOREST_FARFETCHD, 28, 31)
    disappear(ILEXFOREST_FARFETCHD)
    appear(ILEXFOREST_FARFETCHD)
    loadmem(&gPlayer.farfetchdPosition, 5)
    s_end
Position8:
    scall_local(CryAndCheckFacing);
    ifequal(UP, Position8_Up)
    ifequal(LEFT, Position8_Left)
    ifequal(RIGHT, Position8_Right)
    applymovement(ILEXFOREST_FARFETCHD, MovementData_Farfetched_Pos8_Pos9)
    moveobject(ILEXFOREST_FARFETCHD, 10, 35)
    disappear(ILEXFOREST_FARFETCHD)
    appear(ILEXFOREST_FARFETCHD)
    loadmem(&gPlayer.farfetchdPosition, 9)
    s_end
Position8_Right:
    applymovement(ILEXFOREST_FARFETCHD, MovementData_Farfetched_Pos8_Pos7)
    moveobject(ILEXFOREST_FARFETCHD, 22, 31)
    disappear(ILEXFOREST_FARFETCHD)
    appear(ILEXFOREST_FARFETCHD)
    loadmem(&gPlayer.farfetchdPosition, 7)
    s_end
Position8_Up:
Position8_Left:
    applymovement(ILEXFOREST_FARFETCHD, MovementData_Farfetched_Pos8_Pos2)
    moveobject(ILEXFOREST_FARFETCHD, 15, 25)
    disappear(ILEXFOREST_FARFETCHD)
    appear(ILEXFOREST_FARFETCHD)
    loadmem(&gPlayer.farfetchdPosition, 2)
    s_end
Position9:
    scall_local(CryAndCheckFacing);
    ifequal(DOWN, Position9_Down)
    ifequal(RIGHT, Position9_Right)
    applymovement(ILEXFOREST_FARFETCHD, MovementData_Farfetched_Pos9_Pos10)
    moveobject(ILEXFOREST_FARFETCHD, 6, 28)
    disappear(ILEXFOREST_FARFETCHD)
    appear(ILEXFOREST_FARFETCHD)
    loadmem(&gPlayer.farfetchdPosition, 10)
    appear(ILEXFOREST_BLACK_BELT)
    setevent(EVENT_CHARCOAL_KILN_BOSS)
    setevent(EVENT_HERDED_FARFETCHD)
    s_end
Position9_Right:
    applymovement(ILEXFOREST_FARFETCHD, MovementData_Farfetched_Pos9_Pos8_Right)
    moveobject(ILEXFOREST_FARFETCHD, 15, 29)
    disappear(ILEXFOREST_FARFETCHD)
    appear(ILEXFOREST_FARFETCHD)
    loadmem(&gPlayer.farfetchdPosition, 8)
    s_end
Position9_Down:
    applymovement(ILEXFOREST_FARFETCHD, MovementData_Farfetched_Pos9_Pos8_Down)
    moveobject(ILEXFOREST_FARFETCHD, 15, 29)
    disappear(ILEXFOREST_FARFETCHD)
    appear(ILEXFOREST_FARFETCHD)
    loadmem(&gPlayer.farfetchdPosition, 8)
    s_end
Position10:
    faceplayer
    opentext
    writetext(Text_Kwaaaa)
    playcry(FARFETCH_D)
    waitbutton
    closetext
    s_end
CryAndCheckFacing:
    faceplayer
    opentext
    writetext(Text_Kwaaaa)
    playcry(FARFETCH_D)
    waitbutton
    closetext
    readvar(VAR_FACING)
    s_end
    SCRIPT_END
}
bool IlexForestCharcoalMasterScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_HM01_CUT)
    iftrue(AlreadyGotCut)
    writetext(Text_CharcoalMasterIntro)
    promptbutton
    verbosegiveitem(HM_CUT, 1)
    setevent(EVENT_GOT_HM01_CUT)
    writetext(Text_CharcoalMasterOutro)
    waitbutton
    closetext
    setevent(EVENT_ILEX_FOREST_FARFETCHD)
    setevent(EVENT_ILEX_FOREST_APPRENTICE)
    setevent(EVENT_ILEX_FOREST_CHARCOAL_MASTER)
    clearevent(EVENT_CHARCOAL_KILN_FARFETCH_D)
    clearevent(EVENT_CHARCOAL_KILN_APPRENTICE)
    clearevent(EVENT_CHARCOAL_KILN_BOSS)
    s_end
AlreadyGotCut:
    writetext(Text_CharcoalMasterTalkAfter)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool IlexForestHeadbuttGuyScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_TM02_HEADBUTT)
    iftrue(AlreadyGotHeadbutt)
    writetext(Text_HeadbuttIntro)
    promptbutton
    verbosegiveitem(TM_HEADBUTT, 1)
    iffalse(BagFull)
    setevent(EVENT_GOT_TM02_HEADBUTT)
AlreadyGotHeadbutt:
    writetext(Text_HeadbuttOutro)
    waitbutton
BagFull:
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerBugCatcherWayne = {BUG_CATCHER, WAYNE, EVENT_BEAT_BUG_CATCHER_WAYNE, BugCatcherWayneSeenText, BugCatcherWayneBeatenText, 0, TrainerBugCatcherWayne_Script};
bool TrainerBugCatcherWayne_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(BugCatcherWayneAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool IlexForestLassScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(Text_IlexForestLass)
    SCRIPT_END
}
const struct ItemBall IlexForestRevive = {REVIVE, 1};
const struct ItemBall IlexForestXAttack = {X_ATTACK, 1};
const struct ItemBall IlexForestAntidote = {ANTIDOTE, 1};
const struct ItemBall IlexForestEther = {ETHER, 1};
const struct HiddenItem IlexForestHiddenEther = {ETHER, EVENT_ILEX_FOREST_HIDDEN_ETHER};
const struct HiddenItem IlexForestHiddenSuperPotion = {SUPER_POTION, EVENT_ILEX_FOREST_HIDDEN_SUPER_POTION};
const struct HiddenItem IlexForestHiddenFullHeal = {FULL_HEAL, EVENT_ILEX_FOREST_HIDDEN_FULL_HEAL};
bool IlexForestBoulder(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(StrengthBoulderScript)
    SCRIPT_END
}
bool IlexForestSignpost(script_s* s) {
    SCRIPT_BEGIN
    jumptext(IlexForestSignpostText)
    SCRIPT_END
}
bool IlexForestShrineScript(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_FOREST_IS_RESTLESS)
    iftrue(ForestIsRestless)
    goto DontDoCelebiEvent;
ForestIsRestless:
    checkitem(GS_BALL)
    iftrue(AskCelebiEvent)
DontDoCelebiEvent:
    jumptext(Text_IlexForestShrine)
AskCelebiEvent:
    opentext
    writetext(Text_ShrineCelebiEvent)
    yesorno
    iftrue(CelebiEvent)
    closetext
    s_end
CelebiEvent:
    takeitem(GS_BALL, 1)
    clearevent(EVENT_FOREST_IS_RESTLESS)
    setevent(EVENT_AZALEA_TOWN_KURT)
    disappear(ILEXFOREST_LASS)
    clearevent(EVENT_ROUTE_34_ILEX_FOREST_GATE_LASS)
    writetext(Text_InsertGSBall)
    waitbutton
    closetext
    pause(20)
    showemote(EMOTE_SHOCK, PLAYER, 20)
    special(FadeOutMusic)
    applymovement(PLAYER, IlexForestPlayerStepsDownMovement)
    pause(30)
    turnobject(PLAYER, DOWN)
    pause(20)
    clearflag(ENGINE_FOREST_IS_RESTLESS)
    special(CelebiShrineEvent)
    loadwildmon(CELEBI, 30)
    startbattle
    reloadmapafterbattle
    pause(20)
    special(CheckCaughtCelebi)
    iffalse(DidntCatchCelebi)
    appear(ILEXFOREST_KURT)
    applymovement(ILEXFOREST_KURT, IlexForestKurtStepsUpMovement)
    opentext
    writetext(Text_KurtCaughtCelebi)
    waitbutton
    closetext
    applymovement(ILEXFOREST_KURT, IlexFOrestKurtStepsDownMovement)
    disappear(ILEXFOREST_KURT)
DidntCatchCelebi:
    s_end
    SCRIPT_END
}
const uint8_t MovementData_Farfetchd_Pos1_Pos2[] = {
    big_step(UP),
    big_step(UP),
    big_step(UP),
    big_step(UP),
    big_step(UP),
    movement_step_end,
};
const uint8_t MovementData_Farfetchd_Pos2_Pos3[] = {
    big_step(UP),
    big_step(UP),
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(DOWN),
    movement_step_end,
};
const uint8_t MovementData_Farfetchd_Pos2_Pos8[] = {
    big_step(DOWN),
    big_step(DOWN),
    big_step(DOWN),
    big_step(DOWN),
    big_step(DOWN),
    movement_step_end,
};
const uint8_t MovementData_Farfetchd_Pos3_Pos4[] = {
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(RIGHT),
    movement_step_end,
};
const uint8_t MovementData_Farfetchd_Pos3_Pos2[] = {
    big_step(UP),
    big_step(LEFT),
    big_step(LEFT),
    big_step(LEFT),
    big_step(LEFT),
    movement_step_end,
};
const uint8_t MovementData_Farfetchd_Pos4_Pos5[] = {
    big_step(DOWN),
    big_step(DOWN),
    big_step(DOWN),
    big_step(DOWN),
    big_step(DOWN),
    big_step(DOWN),
    movement_step_end,
};
const uint8_t MovementData_Farfetchd_Pos4_Pos3[] = {
    big_step(LEFT),
    jump_step(LEFT),
    big_step(LEFT),
    big_step(LEFT),
    movement_step_end,
};
const uint8_t MovementData_Farfetchd_Pos5_Pos6[] = {
    big_step(DOWN),
    big_step(DOWN),
    big_step(DOWN),
    big_step(DOWN),
    big_step(DOWN),
    big_step(LEFT),
    big_step(LEFT),
    big_step(LEFT),
    big_step(LEFT),
    movement_step_end,
};
const uint8_t MovementData_Farfetchd_Pos5_Pos7[] = {
    big_step(LEFT),
    big_step(LEFT),
    big_step(LEFT),
    big_step(LEFT),
    movement_step_end,
};
const uint8_t MovementData_Farfetched_Pos5_Pos4_Up[] = {
    big_step(UP),
    big_step(UP),
    big_step(UP),
    big_step(RIGHT),
    big_step(UP),
    movement_step_end,
};
const uint8_t MovementData_Farfetched_Pos5_Pos4_Right[] = {
    big_step(RIGHT),
    turn_head(UP),
    step_sleep(1),
    turn_head(DOWN),
    step_sleep(1),
    turn_head(UP),
    step_sleep(1),
    big_step(DOWN),
    big_step(DOWN),
    movement_fix_facing,
    jump_step(UP),
    step_sleep(8),
    step_sleep(8),
    movement_remove_fixed_facing,
    big_step(UP),
    big_step(UP),
    big_step(UP),
    big_step(UP),
    big_step(UP),
    movement_step_end,
};
const uint8_t MovementData_Farfetched_Pos6_Pos7[] = {
    big_step(LEFT),
    big_step(LEFT),
    big_step(LEFT),
    big_step(UP),
    big_step(UP),
    big_step(RIGHT),
    big_step(UP),
    big_step(UP),
    movement_step_end,
};
const uint8_t MovementData_Farfetched_Pos6_Pos5[] = {
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(UP),
    big_step(UP),
    big_step(UP),
    big_step(UP),
    movement_step_end,
};
const uint8_t MovementData_Farfetched_Pos7_Pos8[] = {
    big_step(UP),
    big_step(UP),
    big_step(LEFT),
    big_step(LEFT),
    big_step(LEFT),
    big_step(LEFT),
    big_step(LEFT),
    movement_step_end,
};
const uint8_t MovementData_Farfetched_Pos7_Pos6[] = {
    big_step(DOWN),
    big_step(DOWN),
    big_step(LEFT),
    big_step(DOWN),
    big_step(DOWN),
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(RIGHT),
    movement_step_end,
};
const uint8_t MovementData_Farfetched_Pos7_Pos5[] = {
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(RIGHT),
    movement_step_end,
};
const uint8_t MovementData_Farfetched_Pos8_Pos9[] = {
    big_step(DOWN),
    big_step(LEFT),
    big_step(DOWN),
    big_step(DOWN),
    big_step(DOWN),
    big_step(DOWN),
    big_step(DOWN),
    movement_step_end,
};
const uint8_t MovementData_Farfetched_Pos8_Pos7[] = {
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(RIGHT),
    movement_step_end,
};
const uint8_t MovementData_Farfetched_Pos8_Pos2[] = {
    big_step(UP),
    big_step(UP),
    big_step(UP),
    big_step(UP),
    movement_step_end,
};
const uint8_t MovementData_Farfetched_Pos9_Pos10[] = {
    big_step(LEFT),
    big_step(LEFT),
    movement_fix_facing,
    jump_step(RIGHT),
    step_sleep(8),
    step_sleep(8),
    movement_remove_fixed_facing,
    big_step(LEFT),
    big_step(LEFT),
    big_step(UP),
    big_step(UP),
    big_step(UP),
    big_step(UP),
    big_step(UP),
    big_step(UP),
    movement_step_end,
};
const uint8_t MovementData_Farfetched_Pos9_Pos8_Right[] = {
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(UP),
    big_step(UP),
    big_step(UP),
    big_step(UP),
    big_step(UP),
    movement_step_end,
};
const uint8_t MovementData_Farfetched_Pos9_Pos8_Down[] = {
    big_step(LEFT),
    big_step(LEFT),
    movement_fix_facing,
    jump_step(RIGHT),
    step_sleep(8),
    step_sleep(8),
    movement_remove_fixed_facing,
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(UP),
    big_step(UP),
    big_step(UP),
    big_step(UP),
    big_step(UP),
    movement_step_end,
};
const uint8_t IlexForestKurtStepsUpMovement[] = {
    step(UP),
    step(UP),
    step(UP),
    step(UP),
    movement_step_end,
};
const uint8_t IlexFOrestKurtStepsDownMovement[] = {
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    movement_step_end,
};
const uint8_t IlexForestPlayerStepsDownMovement[] = {
    movement_fix_facing,
    slow_step(DOWN),
    movement_remove_fixed_facing,
    movement_step_end,
};
const txt_cmd_s IlexForestApprenticeIntroText[] = {
    text_start("Oh, man… My boss"
        t_line "is going to be"
        t_cont "steaming…"
        t_para "The FARFETCH'D"
        t_line "that CUTS trees"
        t_para "for charcoal took"
        t_line "off on me."
        t_para "I can't go looking"
        t_line "for it here in the"
        t_cont "ILEX FOREST."
        t_para "It's too big, dark"
        t_line "and scary for me…"
        t_done )
};
const txt_cmd_s IlexForestApprenticeAfterText[] = {
    text_start("Wow! Thanks a"
        t_line "whole bunch!"
        t_para "My boss's #MON"
        t_line "won't obey me be-"
        t_cont "cause I don't have"
        t_cont "a BADGE."
        t_done )
};
const txt_cmd_s Text_ItsTheMissingPokemon[] = {
    text_start("It's the missing"
        t_line "#MON!"
        t_done )
};
const txt_cmd_s Text_Kwaaaa[] = {
    text_start("FARFETCH'D: Kwaa!"
        t_done )
};
const txt_cmd_s Text_CharcoalMasterIntro[] = {
    text_start("Ah! My FARFETCH'D!"
        t_para "You found it for"
        t_line "us, kid?"
        t_para "Without it, we"
        t_line "wouldn't be able"
        t_para "to CUT trees for"
        t_line "charcoal."
        t_para "Thanks, kid!"
        t_para "Now, how can I"
        t_line "thank you…"
        t_para "I know! Here, take"
        t_line "this."
        t_done )
};
const txt_cmd_s Text_CharcoalMasterOutro[] = {
    text_start("That's the CUT HM."
        t_line "Teach that to a"
        t_para "#MON to clear"
        t_line "small trees."
        t_para "Of course, you"
        t_line "have to have the"
        t_para "GYM BADGE from"
        t_line "AZALEA to use it."
        t_done )
};
const txt_cmd_s Text_CharcoalMasterTalkAfter[] = {
    text_start("Do you want to"
        t_line "apprentice as a"
        t_para "charcoal maker"
        t_line "with me?"
        t_para "You'll be first-"
        t_line "rate in ten years!"
        t_done )
};
const txt_cmd_s Text_HeadbuttIntro[] = {
    text_start("What am I doing?"
        t_para "I'm shaking trees"
        t_line "using HEADBUTT."
        t_para "It's fun. Here,"
        t_line "you try it too!"
        t_done )
};
const txt_cmd_s Text_HeadbuttOutro[] = {
    text_start("Rattle trees with"
        t_line "HEADBUTT. Some-"
        t_cont "times, sleeping"
        t_cont "#MON fall out."
        t_done )
};
const txt_cmd_s Text_IlexForestLass[] = {
    text_start("Did something"
        t_line "happen to the"
        t_cont "forest's guardian?"
        t_done )
};
const txt_cmd_s IlexForestSignpostText[] = {
    text_start("ILEX FOREST is"
        t_line "so overgrown with"
        t_para "trees that you"
        t_line "can't see the sky."
        t_para "Please watch out"
        t_line "for items that may"
        t_cont "have been dropped."
        t_done )
};
const txt_cmd_s Text_IlexForestShrine[] = {
    text_start("ILEX FOREST"
        t_line "SHRINE…"
        t_para "It's in honor of"
        t_line "the forest's"
        t_cont "protector…"
        t_done )
};
const txt_cmd_s Text_ShrineCelebiEvent[] = {
    text_start("ILEX FOREST"
        t_line "SHRINE…"
        t_para "It's in honor of"
        t_line "the forest's"
        t_cont "protector…"
        t_para "Oh? What is this?"
        t_para "It's a hole."
        t_line "It looks like the"
        t_para "GS BALL would fit"
        t_line "inside it."
        t_para "Want to put the GS"
        t_line "BALL here?"
        t_done )
};
const txt_cmd_s Text_InsertGSBall[] = {
    text_start("<PLAYER> put in the"
        t_line "GS BALL."
        t_done )
};
const txt_cmd_s Text_KurtCaughtCelebi[] = {
    text_start("Whew, wasn't that"
        t_line "something!"
        t_para "<PLAYER>, that was"
        t_line "fantastic. Thanks!"
        t_para "The legends about"
        t_line "that SHRINE were"
        t_cont "real after all."
        t_para "I feel inspired by"
        t_line "what I just saw."
        t_para "It motivates me to"
        t_line "make better BALLS!"
        t_para "I'm going!"
        t_done )
};
const txt_cmd_s BugCatcherWayneSeenText[] = {
    text_start("Don't sneak up on"
        t_line "me like that!"
        t_para "You frightened a"
        t_line "#MON away!"
        t_done )
};
const txt_cmd_s BugCatcherWayneBeatenText[] = {
    text_start("I hadn't seen that"
        t_line "#MON before…"
        t_done )
};
const txt_cmd_s BugCatcherWayneAfterBattleText[] = {
    text_start("A #MON I've"
        t_line "never seen before"
        t_para "fell out of the"
        t_line "tree when I used"
        t_cont "HEADBUTT."
        t_para "I ought to use"
        t_line "HEADBUTT in other"
        t_cont "places too."
        t_done )
    //db(0, 0) // filler
};
