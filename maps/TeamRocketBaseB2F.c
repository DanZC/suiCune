#include "../constants.h"
#include "../util/scripting.h"
#include "TeamRocketBaseB2F.h"
//// EVENTS
enum {
    TEAMROCKETBASEB2F_ROCKET1 = 2,
    TEAMROCKETBASEB2F_ROCKET_GIRL,
    TEAMROCKETBASEB2F_LANCE,
    TEAMROCKETBASEB2F_DRAGON,
    TEAMROCKETBASEB2F_ELECTRODE1,
    TEAMROCKETBASEB2F_ELECTRODE2,
    TEAMROCKETBASEB2F_ELECTRODE3,
    TEAMROCKETBASEB2F_ELECTRODE4,
    TEAMROCKETBASEB2F_ELECTRODE5,
    TEAMROCKETBASEB2F_ELECTRODE6,
    TEAMROCKETBASEB2F_ROCKET2,
    TEAMROCKETBASEB2F_ROCKET3,
    TEAMROCKETBASEB2F_ROCKET4,
    TEAMROCKETBASEB2F_POKE_BALL,
};

const Script_fn_t TeamRocketBaseB2F_SceneScripts[] = {
    TeamRocketBaseB2F_MapScripts_DummyScene0 , //  SCENE_DEFAULT,
    TeamRocketBaseB2F_MapScripts_DummyScene1 , //  SCENE_TEAMROCKETBASEB2F_ROCKET_BOSS,
    TeamRocketBaseB2F_MapScripts_DummyScene2 , //  SCENE_TEAMROCKETBASEB2F_ELECTRODES,
    TeamRocketBaseB2F_MapScripts_DummyScene3 , //  SCENE_TEAMROCKETBASEB2F_NOTHING,
};

const struct MapCallback TeamRocketBaseB2F_MapCallbacks[] = {
    map_callback(MAPCALLBACK_TILES, TeamRocketBaseB2F_MapScripts_TransmitterDoorCallback),
};

const struct MapScripts TeamRocketBaseB2F_MapScripts = {
    .scene_script_count = lengthof(TeamRocketBaseB2F_SceneScripts),
    .scene_scripts = TeamRocketBaseB2F_SceneScripts,

    .callback_count = lengthof(TeamRocketBaseB2F_MapCallbacks),
    .callbacks = TeamRocketBaseB2F_MapCallbacks,
};

static const struct CoordEvent TeamRocketBaseB2F_CoordEvents[] = {
    coord_event(5, 14, SCENE_DEFAULT, &LanceHealsScript1),
    coord_event(4, 13, SCENE_DEFAULT, &LanceHealsScript2),
    coord_event(14, 11, SCENE_TEAMROCKETBASEB2F_ROCKET_BOSS, &RocketBaseBossFLeft),
    coord_event(15, 11, SCENE_TEAMROCKETBASEB2F_ROCKET_BOSS, &RocketBaseBossFRight),
    coord_event(14, 12, SCENE_TEAMROCKETBASEB2F_ELECTRODES, &RocketBaseCantLeaveScript),
    coord_event(15, 12, SCENE_TEAMROCKETBASEB2F_ELECTRODES, &RocketBaseCantLeaveScript),
    coord_event(12, 3, SCENE_TEAMROCKETBASEB2F_ELECTRODES, &RocketBaseLancesSideScript),
    coord_event(12, 10, SCENE_TEAMROCKETBASEB2F_ELECTRODES, &RocketBaseLancesSideScript),
    coord_event(12, 11, SCENE_TEAMROCKETBASEB2F_ELECTRODES, &RocketBaseLancesSideScript),
};

static const struct BGEvent TeamRocketBaseB2F_BGEvents[] = {
    bg_event(14, 12, BGEVENT_IFNOTSET, &TeamRocketBaseB2FLockedDoor),
    bg_event(15, 12, BGEVENT_IFNOTSET, &TeamRocketBaseB2FLockedDoor),
    bg_event(17, 9, BGEVENT_READ, &TeamRocketBaseB2FTransmitterScript),
    bg_event(16, 9, BGEVENT_READ, &TeamRocketBaseB2FTransmitterScript),
    bg_event(15, 9, BGEVENT_READ, &TeamRocketBaseB2FTransmitterScript),
    bg_event(14, 9, BGEVENT_READ, &TeamRocketBaseB2FTransmitterScript),
    bg_event(13, 9, BGEVENT_READ, &TeamRocketBaseB2FTransmitterScript),
    bg_event(12, 9, BGEVENT_READ, &TeamRocketBaseB2FTransmitterScript),
    bg_event(12, 8, BGEVENT_READ, &TeamRocketBaseB2FTransmitterScript),
    bg_event(12, 7, BGEVENT_READ, &TeamRocketBaseB2FTransmitterScript),
    bg_event(12, 6, BGEVENT_READ, &TeamRocketBaseB2FTransmitterScript),
    bg_event(12, 5, BGEVENT_READ, &TeamRocketBaseB2FTransmitterScript),
    bg_event(12, 4, BGEVENT_READ, &TeamRocketBaseB2FTransmitterScript),
    bg_event(13, 4, BGEVENT_READ, &TeamRocketBaseB2FTransmitterScript),
    bg_event(14, 4, BGEVENT_READ, &TeamRocketBaseB2FTransmitterScript),
    bg_event(15, 4, BGEVENT_READ, &TeamRocketBaseB2FTransmitterScript),
    bg_event(16, 4, BGEVENT_READ, &TeamRocketBaseB2FTransmitterScript),
    bg_event(17, 4, BGEVENT_READ, &TeamRocketBaseB2FTransmitterScript),
    bg_event(17, 5, BGEVENT_READ, &TeamRocketBaseB2FTransmitterScript),
    bg_event(17, 6, BGEVENT_READ, &TeamRocketBaseB2FTransmitterScript),
    bg_event(17, 7, BGEVENT_READ, &TeamRocketBaseB2FTransmitterScript),
    bg_event(17, 8, BGEVENT_READ, &TeamRocketBaseB2FTransmitterScript),
    bg_event(26, 7, BGEVENT_ITEM, &TeamRocketBaseB2FHiddenFullHeal),
};

static const struct WarpEventData TeamRocketBaseB2F_WarpEvents[] = {
    warp_event(3, 14, TEAM_ROCKET_BASE_B1F, 2),
    warp_event(3, 2, TEAM_ROCKET_BASE_B3F, 1),
    warp_event(27, 2, TEAM_ROCKET_BASE_B3F, 2),
    warp_event(3, 6, TEAM_ROCKET_BASE_B3F, 3),
    warp_event(27, 14, TEAM_ROCKET_BASE_B3F, 4),
};

static const struct ObjEvent TeamRocketBaseB2F_ObjectEvents[] = {
    object_event(20, 16, SPRITE_ROCKET, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, EVENT_TEAM_ROCKET_BASE_B2F_GRUNT_WITH_EXECUTIVE),
    object_event(20, 16, SPRITE_ROCKET_GIRL, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, EVENT_TEAM_ROCKET_BASE_B2F_EXECUTIVE),
    object_event(5, 13, SPRITE_LANCE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, EVENT_TEAM_ROCKET_BASE_B2F_LANCE),
    object_event(9, 13, SPRITE_DRAGON, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, EVENT_TEAM_ROCKET_BASE_B2F_DRAGONITE),
    object_event(7, 5, SPRITE_VOLTORB, SPRITEMOVEDATA_POKEMON, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &RocketElectrode1, EVENT_TEAM_ROCKET_BASE_B2F_ELECTRODE_1),
    object_event(7, 7, SPRITE_VOLTORB, SPRITEMOVEDATA_POKEMON, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &RocketElectrode2, EVENT_TEAM_ROCKET_BASE_B2F_ELECTRODE_2),
    object_event(7, 9, SPRITE_VOLTORB, SPRITEMOVEDATA_POKEMON, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &RocketElectrode3, EVENT_TEAM_ROCKET_BASE_B2F_ELECTRODE_3),
    object_event(22, 5, SPRITE_VOLTORB, SPRITEMOVEDATA_POKEMON, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, EVENT_TEAM_ROCKET_BASE_B2F_ELECTRODE_1),
    object_event(22, 7, SPRITE_VOLTORB, SPRITEMOVEDATA_POKEMON, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, EVENT_TEAM_ROCKET_BASE_B2F_ELECTRODE_2),
    object_event(22, 9, SPRITE_VOLTORB, SPRITEMOVEDATA_POKEMON, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, EVENT_TEAM_ROCKET_BASE_B2F_ELECTRODE_3),
    object_event(25, 13, SPRITE_ROCKET, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_TRAINER, 3, &TrainerGruntM17, EVENT_TEAM_ROCKET_BASE_POPULATION),
    object_event(4, 1, SPRITE_ROCKET, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, 0, OBJECTTYPE_TRAINER, 1, &TrainerGruntM18, EVENT_TEAM_ROCKET_BASE_POPULATION),
    object_event(21, 14, SPRITE_ROCKET, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, 0, OBJECTTYPE_TRAINER, 4, &TrainerGruntM19, EVENT_TEAM_ROCKET_BASE_POPULATION),
    object_event(3, 10, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &TeamRocketBaseB2FTMThief, EVENT_TEAM_ROCKET_BASE_B2F_TM_THIEF),
};

const struct MapEvents TeamRocketBaseB2F_MapEvents = {
    .warp_event_count = lengthof(TeamRocketBaseB2F_WarpEvents),
    .warp_events = TeamRocketBaseB2F_WarpEvents,

    .coord_event_count = lengthof(TeamRocketBaseB2F_CoordEvents),
    .coord_events = TeamRocketBaseB2F_CoordEvents,

    .bg_event_count = lengthof(TeamRocketBaseB2F_BGEvents),
    .bg_events = TeamRocketBaseB2F_BGEvents,

    .obj_event_count = lengthof(TeamRocketBaseB2F_ObjectEvents),
    .obj_events = TeamRocketBaseB2F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "TeamRocketBaseB2F.h"

bool TeamRocketBaseB2F_MapScripts_DummyScene0(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool TeamRocketBaseB2F_MapScripts_DummyScene1(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool TeamRocketBaseB2F_MapScripts_DummyScene2(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool TeamRocketBaseB2F_MapScripts_DummyScene3(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool TeamRocketBaseB2F_MapScripts_TransmitterDoorCallback(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_OPENED_DOOR_TO_ROCKET_HIDEOUT_TRANSMITTER)
    iftrue(OpenDoor)
    s_endcallback
OpenDoor:
    changeblock(14, 12, 0x07) // floor
    s_endcallback
    SCRIPT_END
}
bool RocketBaseBossFLeft(script_s* s) {
    SCRIPT_BEGIN
    moveobject(TEAMROCKETBASEB2F_LANCE, 9, 13)
    sjump(RocketBaseBossFScript)
    SCRIPT_END
}
bool RocketBaseBossFRight(script_s* s) {
    SCRIPT_BEGIN
    moveobject(TEAMROCKETBASEB2F_ROCKET_GIRL, 21, 16)
    moveobject(TEAMROCKETBASEB2F_ROCKET1, 21, 16)
    moveobject(TEAMROCKETBASEB2F_DRAGON, 10, 13)
    moveobject(TEAMROCKETBASEB2F_LANCE, 10, 13)
    SCRIPT_FALLTHROUGH(RocketBaseBossFScript)
}
bool RocketBaseBossFScript(script_s* s) {
    SCRIPT_BEGIN
    appear(TEAMROCKETBASEB2F_ROCKET_GIRL)
    appear(TEAMROCKETBASEB2F_ROCKET1)
    opentext
    writetext(RocketBaseExecutiveFHoldItText)
    waitbutton
    closetext
    turnobject(PLAYER, DOWN)
    showemote(EMOTE_SHOCK, PLAYER, 15)
    applymovement(PLAYER, RocketBasePlayerApproachesBossFMovement)
    playmusic(MUSIC_ROCKET_ENCOUNTER)
    applymovement(TEAMROCKETBASEB2F_ROCKET_GIRL, RocketBaseBossFApproachesPlayerMovement)
    turnobject(PLAYER, UP)
    applymovement(TEAMROCKETBASEB2F_ROCKET1, RocketBaseGruntApproachesPlayerMovement)
    opentext
    writetext(RocketBaseBossFThrashText)
    waitbutton
    closetext
    playcry(DRAGONITE)
    turnobject(TEAMROCKETBASEB2F_ROCKET_GIRL, LEFT)
    turnobject(PLAYER, LEFT)
    appear(TEAMROCKETBASEB2F_DRAGON)
    applymovement(TEAMROCKETBASEB2F_DRAGON, RocketBaseDragoniteAttacksMovement)
    applymovement(TEAMROCKETBASEB2F_ROCKET_GIRL, RocketBaseBossFHitMovement)
    applymovement(TEAMROCKETBASEB2F_ROCKET1, RocketBaseGruntProtectsBossFMovement)
    appear(TEAMROCKETBASEB2F_LANCE)
    applymovement(TEAMROCKETBASEB2F_LANCE, RocketBaseLanceApproachesBossFMovement)
    opentext
    writetext(RocketBaseLanceShareFunText)
    waitbutton
    closetext
    turnobject(PLAYER, RIGHT)
    applymovement(TEAMROCKETBASEB2F_ROCKET_GIRL, RocketBaseBossFFacesPlayerMovement)
    opentext
    writetext(RocketBaseBossDontMeddleText)
    waitbutton
    closetext
    applymovement(TEAMROCKETBASEB2F_ROCKET1, RocketBaseGruntBattlesLanceMovement)
    applymovement(TEAMROCKETBASEB2F_ROCKET_GIRL, RocketBaseBossFBattlesPlayerMovement)
    winlosstext(RocketBaseBossWinText, 0)
    setlasttalked(TEAMROCKETBASEB2F_ROCKET_GIRL)
    loadtrainer(EXECUTIVEF, EXECUTIVEF_2)
    startbattle
    disappear(TEAMROCKETBASEB2F_DRAGON)
    setevent(EVENT_TEAM_ROCKET_BASE_B2F_EXECUTIVE)
    setevent(EVENT_TEAM_ROCKET_BASE_B2F_GRUNT_WITH_EXECUTIVE)
    setevent(EVENT_TEAM_ROCKET_BASE_B2F_LANCE)
    reloadmapafterbattle
    setevent(EVENT_BEAT_ROCKET_EXECUTIVEF_2)
    opentext
    writetext(RocketBaseBossRetreatText)
    waitbutton
    closetext
    special(FadeBlackQuickly)
    special(ReloadSpritesNoPalettes)
    disappear(TEAMROCKETBASEB2F_ROCKET1)
    disappear(TEAMROCKETBASEB2F_ROCKET_GIRL)
    disappear(TEAMROCKETBASEB2F_ROCKET2)
    disappear(TEAMROCKETBASEB2F_ROCKET3)
    disappear(TEAMROCKETBASEB2F_ROCKET4)
    pause(15)
    special(FadeInQuickly)
    setscene(SCENE_TEAMROCKETBASEB2F_ELECTRODES)
    clearevent(EVENT_TEAM_ROCKET_BASE_B2F_LANCE)
    turnobject(TEAMROCKETBASEB2F_LANCE, DOWN)
    opentext
    writetext(RocketBaseLancePostBattleText)
    waitbutton
    closetext
    applymovement(TEAMROCKETBASEB2F_LANCE, RocketBaseLanceChecksPlayerMovement)
    turnobject(PLAYER, UP)
    opentext
    writetext(RocketBaseLancePowerOffText)
    waitbutton
    closetext
    follow(TEAMROCKETBASEB2F_LANCE, PLAYER)
    applymovement(TEAMROCKETBASEB2F_LANCE, RocketBaseLanceApproachesMachineMovement)
    stopfollow
    applymovement(TEAMROCKETBASEB2F_LANCE, RocketBaseLancePacesMovement)
    opentext
    writetext(RockerBaseLanceElectrodeFaintText)
    waitbutton
    closetext
    applymovement(TEAMROCKETBASEB2F_LANCE, RocketBaseLanceApproachesElectrodesMovement)
    disappear(TEAMROCKETBASEB2F_LANCE)
    SCRIPT_FALLTHROUGH(RocketBaseCantLeaveScript)
}
bool RocketBaseCantLeaveScript(script_s* s) {
    SCRIPT_BEGIN
    applymovement(PLAYER, RocketBasePlayerCantLeaveElectrodesMovement)
    s_end
    SCRIPT_END
}
bool RocketBaseLancesSideScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(RocketBaseLancesSideText)
    waitbutton
    closetext
    applymovement(PLAYER, RocketBasePlayerCantGoRightMovement)
    s_end
    SCRIPT_END
}
bool LanceHealsScript1(script_s* s) {
    SCRIPT_BEGIN
    turnobject(PLAYER, UP)
    sjump(LanceHealsCommon)
    SCRIPT_END
}
bool LanceHealsScript2(script_s* s) {
    SCRIPT_BEGIN
    turnobject(PLAYER, RIGHT)
    turnobject(TEAMROCKETBASEB2F_LANCE, LEFT)
    SCRIPT_FALLTHROUGH(LanceHealsCommon)
}
bool LanceHealsCommon(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(LanceHealsText1)
    waitbutton
    closetext
    special(FadeOutPalettes)
    special(StubbedTrainerRankings_Healings)
    playsound(SFX_FULL_HEAL)
    special(HealParty)
    special(FadeInPalettes)
    opentext
    writetext(LanceHealsText2)
    waitbutton
    closetext
    setscene(SCENE_TEAMROCKETBASEB2F_ROCKET_BOSS)
    setevent(EVENT_LANCE_HEALED_YOU_IN_TEAM_ROCKET_BASE)
    readvar(VAR_FACING)
    ifequal(RIGHT, FacingRight)
    applymovement(TEAMROCKETBASEB2F_LANCE, RocketBaseLanceLeavesAfterHealMovement)
    disappear(TEAMROCKETBASEB2F_LANCE)
    s_end
FacingRight:
    applymovement(TEAMROCKETBASEB2F_LANCE, RocketBaseLanceLeavesAfterHealRightMovement)
    disappear(TEAMROCKETBASEB2F_LANCE)
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerGruntM17 = {GRUNTM, GRUNTM_17, EVENT_BEAT_ROCKET_GRUNTM_17, GruntM17SeenText, GruntM17BeatenText, 0, TrainerGruntM17_Script};
bool TrainerGruntM17_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(GruntM17AfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerGruntM18 = {GRUNTM, GRUNTM_18, EVENT_BEAT_ROCKET_GRUNTM_18, GruntM18SeenText, GruntM18BeatenText, 0, TrainerGruntM18_Script};
bool TrainerGruntM18_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(GruntM18AfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerGruntM19 = {GRUNTM, GRUNTM_19, EVENT_BEAT_ROCKET_GRUNTM_19, GruntM19SeenText, GruntM19BeatenText, 0, TrainerGruntM19_Script};
bool TrainerGruntM19_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(GruntM19AfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool RocketElectrode1(script_s* s) {
    SCRIPT_BEGIN
    playcry(ELECTRODE)
    loadwildmon(ELECTRODE, 23)
    startbattle
    iftrue_jump(TeamRocketBaseB2FReloadMap)
    disappear(TEAMROCKETBASEB2F_ELECTRODE1)
    disappear(TEAMROCKETBASEB2F_ELECTRODE4)
    checkevent(EVENT_TEAM_ROCKET_BASE_B2F_ELECTRODE_1)
    iffalse_jump(TeamRocketBaseB2FReloadMap)
    checkevent(EVENT_TEAM_ROCKET_BASE_B2F_ELECTRODE_2)
    iffalse_jump(TeamRocketBaseB2FReloadMap)
    checkevent(EVENT_TEAM_ROCKET_BASE_B2F_ELECTRODE_3)
    iffalse_jump(TeamRocketBaseB2FReloadMap)
    reloadmapafterbattle
    special(PlayMapMusic)
    applymovement(PLAYER, RocketBasePlayerLeavesElectrodesMovement1)
    sjump(RocketBaseElectrodeScript)
    SCRIPT_END
}
bool RocketElectrode2(script_s* s) {
    SCRIPT_BEGIN
    playcry(ELECTRODE)
    loadwildmon(ELECTRODE, 23)
    startbattle
    iftrue_jump(TeamRocketBaseB2FReloadMap)
    disappear(TEAMROCKETBASEB2F_ELECTRODE2)
    disappear(TEAMROCKETBASEB2F_ELECTRODE5)
    checkevent(EVENT_TEAM_ROCKET_BASE_B2F_ELECTRODE_1)
    iffalse_jump(TeamRocketBaseB2FReloadMap)
    checkevent(EVENT_TEAM_ROCKET_BASE_B2F_ELECTRODE_2)
    iffalse_jump(TeamRocketBaseB2FReloadMap)
    checkevent(EVENT_TEAM_ROCKET_BASE_B2F_ELECTRODE_3)
    iffalse_jump(TeamRocketBaseB2FReloadMap)
    reloadmapafterbattle
    special(PlayMapMusic)
    applymovement(PLAYER, RocketBasePlayerLeavesElectrodesMovement2)
    sjump(RocketBaseElectrodeScript)
    SCRIPT_END
}
bool RocketElectrode3(script_s* s) {
    SCRIPT_BEGIN
    playcry(ELECTRODE)
    loadwildmon(ELECTRODE, 23)
    startbattle
    iftrue_jump(TeamRocketBaseB2FReloadMap)
    disappear(TEAMROCKETBASEB2F_ELECTRODE3)
    disappear(TEAMROCKETBASEB2F_ELECTRODE6)
    checkevent(EVENT_TEAM_ROCKET_BASE_B2F_ELECTRODE_1)
    iffalse_jump(TeamRocketBaseB2FReloadMap)
    checkevent(EVENT_TEAM_ROCKET_BASE_B2F_ELECTRODE_2)
    iffalse_jump(TeamRocketBaseB2FReloadMap)
    checkevent(EVENT_TEAM_ROCKET_BASE_B2F_ELECTRODE_3)
    iffalse_jump(TeamRocketBaseB2FReloadMap)
    reloadmapafterbattle
    special(PlayMapMusic)
    applymovement(PLAYER, RocketBasePlayerLeavesElectrodesMovement3)
    sjump(RocketBaseElectrodeScript)
    SCRIPT_END
}
bool TeamRocketBaseB2FReloadMap(script_s* s) {
    SCRIPT_BEGIN
    reloadmapafterbattle
    s_end
    SCRIPT_END
}
bool RocketBaseElectrodeScript(script_s* s) {
    SCRIPT_BEGIN
    moveobject(TEAMROCKETBASEB2F_LANCE, 18, 6)
    appear(TEAMROCKETBASEB2F_LANCE)
    applymovement(TEAMROCKETBASEB2F_LANCE, RocketBaseLanceLeavesElectrodesMovement)
    turnobject(PLAYER, RIGHT)
    opentext
    writetext(RocketBaseLanceElectrodeDoneText)
    promptbutton
    verbosegiveitem(HM_WHIRLPOOL, 1)
    setevent(EVENT_GOT_HM06_WHIRLPOOL)
    writetext(RocketBaseLanceWhirlpoolText)
    waitbutton
    closetext
    turnobject(TEAMROCKETBASEB2F_LANCE, DOWN)
    opentext
    writetext(RocketBaseLanceMonMasterText)
    waitbutton
    closetext
    turnobject(PLAYER, DOWN)
    applymovement(TEAMROCKETBASEB2F_LANCE, RocketBaseLanceLeavesBaseMovement)
    disappear(TEAMROCKETBASEB2F_LANCE)
    setevent(EVENT_CLEARED_ROCKET_HIDEOUT)
    clearflag(ENGINE_ROCKET_SIGNAL_ON_CH20)
    setevent(EVENT_ROUTE_43_GATE_ROCKETS)
    setevent(EVENT_MAHOGANY_TOWN_POKEFAN_M_BLOCKS_GYM)
    setscene(SCENE_TEAMROCKETBASEB2F_NOTHING)
    clearevent(EVENT_LAKE_OF_RAGE_CIVILIANS)
    setevent(EVENT_TURNED_OFF_SECURITY_CAMERAS)
    setevent(EVENT_SECURITY_CAMERA_1)
    setevent(EVENT_SECURITY_CAMERA_2)
    setevent(EVENT_SECURITY_CAMERA_3)
    setevent(EVENT_SECURITY_CAMERA_4)
    setevent(EVENT_SECURITY_CAMERA_5)
    s_end
    SCRIPT_END
}
bool TeamRocketBaseB2FLockedDoor(script_s* s) {
    SCRIPT_BEGIN
    //conditional_event(EVENT_OPENED_DOOR_TO_ROCKET_HIDEOUT_TRANSMITTER, .Script)
Script:
    opentext
    checkevent(EVENT_LEARNED_HAIL_GIOVANNI)
    iftrue(KnowsPassword)
    writetext(RocketBaseDoorNoPasswordText)
    waitbutton
    closetext
    s_end
KnowsPassword:
    writetext(RocketBaseDoorKnowPasswordText)
    waitbutton
    playsound(SFX_ENTER_DOOR)
    changeblock(14, 12, 0x07) // floor
    reloadmappart
    closetext
    setevent(EVENT_OPENED_DOOR_TO_ROCKET_HIDEOUT_TRANSMITTER)
    waitsfx
    s_end
    SCRIPT_END
}
bool TeamRocketBaseB2FTransmitterScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    checkevent(EVENT_CLEARED_ROCKET_HIDEOUT)
    iftrue(Deactivated)
    writetext(RocketBaseB2FTransmitterText)
    waitbutton
    closetext
    s_end
Deactivated:
    writetext(RocketBaseB2FDeactivateTransmitterText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct ItemBall TeamRocketBaseB2FTMThief = {TM_THIEF, 1};
const struct HiddenItem TeamRocketBaseB2FHiddenFullHeal = {FULL_HEAL, EVENT_TEAM_ROCKET_BASE_B2F_HIDDEN_FULL_HEAL};
const uint8_t RocketBaseLanceLeavesAfterHealMovement[] = {
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    movement_step_end,
};
const uint8_t RocketBaseLanceLeavesAfterHealRightMovement[] = {
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    movement_step_end,
};
const uint8_t RocketBasePlayerApproachesBossFMovement[] = {
    step(DOWN),
    step(DOWN),
    step(DOWN),
    turn_head(RIGHT),
    movement_step_end,
};
const uint8_t RocketBaseBossFApproachesPlayerMovement[] = {
    big_step(LEFT),
    big_step(LEFT),
    big_step(UP),
    big_step(UP),
    big_step(UP),
    big_step(LEFT),
    big_step(LEFT),
    big_step(LEFT),
    big_step(LEFT),
    turn_head(DOWN),
    movement_step_end,
};
const uint8_t RocketBaseGruntApproachesPlayerMovement[] = {
    big_step(LEFT),
    big_step(LEFT),
    big_step(UP),
    big_step(UP),
    big_step(LEFT),
    big_step(LEFT),
    movement_step_end,
};
const uint8_t RocketBaseDragoniteAttacksMovement[] = {
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(RIGHT),
    movement_step_end,
};
const uint8_t RocketBaseBossFHitMovement[] = {
    movement_fix_facing,
    movement_set_sliding,
    jump_step(RIGHT),
    movement_remove_sliding,
    movement_remove_fixed_facing,
    movement_step_end,
};
const uint8_t RocketBaseBossFFacesPlayerMovement[] = {
    slow_step(DOWN),
    turn_head(LEFT),
    movement_step_end,
};
const uint8_t RocketBaseLanceApproachesBossFMovement[] = {
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    movement_step_end,
};
const uint8_t RocketBaseBossFBattlesPlayerMovement[] = {
    big_step(LEFT),
    movement_step_end,
};
const uint8_t RocketBaseGruntBattlesLanceMovement[] = {
    big_step(LEFT),
    movement_step_end,
};
const uint8_t RocketBaseGruntProtectsBossFMovement[] = {
    big_step(LEFT),
    big_step(UP),
    turn_head(LEFT),
    movement_step_end,
};
const uint8_t RocketBaseLanceChecksPlayerMovement[] = {
    step(RIGHT),
    step(RIGHT),
    turn_head(DOWN),
    movement_step_end,
};
const uint8_t RocketBaseLanceApproachesMachineMovement[] = {
    step(UP),
    step(UP),
    step(UP),
    movement_step_end,
};
const uint8_t RocketBaseLancePacesMovement[] = {
    step_sleep(8),
    step(LEFT),
    step(LEFT),
    turn_head(UP),
    step_sleep(8),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    turn_head(UP),
    step_sleep(8),
    step(LEFT),
    step(LEFT),
    turn_head(DOWN),
    movement_step_end,
};
const uint8_t RocketBaseLanceApproachesElectrodesMovement[] = {
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    step(UP),
    step(UP),
    step(UP),
    step(UP),
    step(UP),
    movement_step_end,
};
const uint8_t RocketBasePlayerCantLeaveElectrodesMovement[] = {
    step(UP),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    turn_head(UP),
    movement_step_end,
};
const uint8_t RocketBasePlayerCantGoRightMovement[] = {
    step(LEFT),
    movement_step_end,
};
const uint8_t RocketBaseLanceLeavesElectrodesMovement[] = {
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    movement_step_end,
};
const uint8_t RocketBaseLanceLeavesBaseMovement[] = {
    step(DOWN),
    step(DOWN),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    movement_step_end,
};
const uint8_t RocketBasePlayerLeavesElectrodesMovement1[] = {
    step(RIGHT),
    step(RIGHT),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    movement_step_end,
};
const uint8_t RocketBasePlayerLeavesElectrodesMovement2[] = {
    step(RIGHT),
    step(RIGHT),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    movement_step_end,
};
const uint8_t RocketBasePlayerLeavesElectrodesMovement3[] = {
    step(RIGHT),
    step(RIGHT),
    step(DOWN),
    step(DOWN),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    movement_step_end,
};
const txt_cmd_s RocketBaseExecutiveFHoldItText[] = {
    text_start("Hold it right"
        t_line "there!"
        t_done )
};
const txt_cmd_s RocketBaseBossFThrashText[] = {
    text_start("We can't have a"
        t_line "brat like you on"
        t_cont "the loose."
        t_para "It's harmful to"
        t_line "TEAM ROCKET's"
        t_cont "pride, you see."
        t_para "However strong you"
        t_line "may be, you can't"
        t_para "take both of us at"
        t_line "the same time."
        t_para "Sorry, baby. Now"
        t_line "get ready to be"
        t_cont "thrashed."
        t_done )
};
const txt_cmd_s RocketBaseLanceShareFunText[] = {
    text_start("Hey! Don't be so"
        t_line "selfish. Spread"
        t_cont "the fun around."
        t_done )
};
const txt_cmd_s RocketBaseBossDontMeddleText[] = {
    text_start("What? You had an"
        t_line "accomplice?"
        t_para "Where is your"
        t_line "sense of honor?"
        t_para "As the interim"
        t_line "boss in place of"
        t_para "GIOVANNI, I'll"
        t_line "show you how wrong"
        t_para "it is to meddle"
        t_line "with TEAM ROCKET!"
        t_done )
};
const txt_cmd_s RocketBaseBossWinText[] = {
    text_start("Tch, you really"
        t_line "are strong."
        t_para "It's too bad."
        t_para "If you were to"
        t_line "join TEAM ROCKET,"
        t_para "you could become"
        t_line "an EXECUTIVE."
        t_done )
};
const txt_cmd_s RocketBaseBossRetreatText[] = {
    text_start("…This hideout is"
        t_line "done for…"
        t_para "But that's fine."
        t_line "The broadcast ex-"
        t_cont "periment was a"
        t_cont "total success."
        t_para "It doesn't matter"
        t_line "what happens to"
        t_cont "this hideout now."
        t_para "We have much big-"
        t_line "ger plans."
        t_para "You'll come to"
        t_line "appreciate TEAM"
        t_para "ROCKET's true"
        t_line "power soon enough."
        t_para "Enjoy yourself"
        t_line "while you can…"
        t_para "Fufufufu…"
        t_done )
};
const txt_cmd_s RocketBaseLancePostBattleText[] = {
    text_start("LANCE: That did"
        t_line "it. We defeated"
        t_para "all the ROCKETS"
        t_line "here."
        t_para "But I'm concerned"
        t_line "about the young"
        t_para "guy I battled in"
        t_line "the process…"
        t_done )
};
const txt_cmd_s RocketBaseLancePowerOffText[] = {
    text_start("Sorry, <PLAY_G>."
        t_line "I saw how well you"
        t_para "were doing, so I"
        t_line "just hung back."
        t_para "Now all there is"
        t_line "left to do is to"
        t_para "turn off that odd"
        t_line "radio signal."
        t_done )
};
const txt_cmd_s RockerBaseLanceElectrodeFaintText[] = {
    text_start("It's this machine"
        t_line "that's causing all"
        t_cont "the problems."
        t_para "I don't see a"
        t_line "switch on it…"
        t_para "We have no choice."
        t_line "We have to make"
        t_para "all the ELECTRODE"
        t_line "faint."
        t_para "That should stop"
        t_line "this machine from"
        t_para "transmitting that"
        t_line "strange signal."
        t_para "It's no fault of"
        t_line "the #MON, so it"
        t_para "makes me feel"
        t_line "guilty."
        t_para "<PLAY_G>, let's"
        t_line "split the job."
        t_done )
};
const txt_cmd_s RocketBaseLancesSideText[] = {
    text_start("LANCE: Leave this"
        t_line "side to me."
        t_done )
};
const txt_cmd_s RocketBaseLanceElectrodeDoneText[] = {
    text_start("LANCE: That odd"
        t_line "signal has finally"
        t_cont "stopped."
        t_para "The LAKE should be"
        t_line "back to normal."
        t_para "You're the hero!"
        t_line "Let me thank you"
        t_para "on behalf of all"
        t_line "the #MON."
        t_para "Oh, yes. You"
        t_line "should take this."
        t_para "I found it here,"
        t_line "but I don't have"
        t_cont "any need for it."
        t_done )
};
const txt_cmd_s RocketBaseReceivedHM06Text[] = {
    text_start("<PLAYER> received"
        t_line "HM06."
        t_done )
};
const txt_cmd_s RocketBaseLanceWhirlpoolText[] = {
    text_start("That's WHIRLPOOL."
        t_line "Teach it to a"
        t_para "#MON to get"
        t_line "across wild water."
        t_para "But keep this in"
        t_line "mind."
        t_para "You can use that"
        t_line "out of battle only"
        t_para "with the BADGE"
        t_line "from MAHOGANY GYM."
        t_done )
};
const txt_cmd_s RocketBaseLanceMonMasterText[] = {
    text_start("<PLAY_G>…"
        t_para "The journey to be-"
        t_line "coming the #MON"
        t_para "MASTER is long and"
        t_line "difficult."
        t_para "Knowing that, will"
        t_line "you keep going?"
        t_para "…"
        t_para "I see. No, you're"
        t_line "right."
        t_para "If you would give"
        t_line "up that easily,"
        t_para "you would have"
        t_line "never chased that"
        t_para "dream in the first"
        t_line "place."
        t_para "I look forward to"
        t_line "seeing you again!"
        t_done )
};
const txt_cmd_s LanceHealsText1[] = {
    text_start("LANCE: Are you all"
        t_line "right?"
        t_para "Your #MON are"
        t_line "hurt and tired."
        t_para "Here, give them"
        t_line "some of my medi-"
        t_cont "cine."
        t_done )
};
const txt_cmd_s LanceHealsText2[] = {
    text_start("LANCE: <PLAY_G>,"
        t_line "let's give it our"
        t_cont "best for #MON."
        t_done )
};
const txt_cmd_s GruntM17SeenText[] = {
    text_start("The door won't"
        t_line "open?"
        t_para "Well, duh."
        t_line "It has to have a"
        t_para "password that only"
        t_line "TEAM ROCKET knows."
        t_done )
};
const txt_cmd_s GruntM17BeatenText[] = {
    text_start("What? I lost?"
        t_done )
};
const txt_cmd_s GruntM17AfterBattleText[] = {
    text_start("Heh, I'm just a"
        t_line "GRUNT."
        t_para "I don't know the"
        t_line "password. Too bad"
        t_cont "for you."
        t_done )
};
const txt_cmd_s GruntM18SeenText[] = {
    text_start("Oh, a kid? I don't"
        t_line "really like this,"
        t_para "but eliminate you"
        t_line "I must."
        t_done )
};
const txt_cmd_s GruntM18BeatenText[] = {
    text_start("I knew I'd lose…"
        t_done )
};
const txt_cmd_s GruntM18AfterBattleText[] = {
    text_start("I got wiped out on"
        t_line "the last mission"
        t_cont "by a kid too."
        t_para "When we were ab-"
        t_line "ducting #MON,"
        t_para "this kid with long"
        t_line "red hair and mean-"
        t_para "looking eyes just"
        t_line "creamed me…"
        t_done )
};
const txt_cmd_s GruntM19SeenText[] = {
    text_start("You rotten little"
        t_line "pest!"
        t_done )
};
const txt_cmd_s GruntM19BeatenText[] = {
    text_start("Grrrr…"
        t_done )
};
const txt_cmd_s GruntM19AfterBattleText[] = {
    text_start("Heh, only the boss"
        t_line "knows the password"
        t_cont "for that door."
        t_para "Where's the boss?"
        t_line "Who knows? Go look"
        t_cont "for yourself."
        t_done )
};
const txt_cmd_s RocketBaseDoorNoPasswordText[] = {
    text_start("The door's closed…"
        t_para "It needs a pass-"
        t_line "word to open."
        t_done )
};
const txt_cmd_s RocketBaseDoorKnowPasswordText[] = {
    text_start("The door's closed…"
        t_para "<PLAYER> entered"
        t_line "the password."
        t_para "The door opened!"
        t_done )
};
const txt_cmd_s RocketBaseB2FTransmitterText[] = {
    text_start("It's the radio"
        t_line "transmitter that's"
        t_para "sending the"
        t_line "sinister signal."
        t_para "It's working at"
        t_line "full capacity."
        t_done )
};
const txt_cmd_s RocketBaseB2FDeactivateTransmitterText[] = {
    text_start("The radio trans-"
        t_line "mitter has finally"
        t_para "stopped its evil"
        t_line "broadcast."
        t_done )
    //db(0, 0) // filler
};
