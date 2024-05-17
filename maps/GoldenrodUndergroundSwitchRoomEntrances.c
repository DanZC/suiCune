#include "../constants.h"
#include "../util/scripting.h"
#include "GoldenrodUndergroundSwitchRoomEntrances.h"
//// EVENTS
enum {
    GOLDENRODUNDERGROUNDSWITCHROOMENTRANCES_PHARMACIST1 = 2,
    GOLDENRODUNDERGROUNDSWITCHROOMENTRANCES_PHARMACIST2,
    GOLDENRODUNDERGROUNDSWITCHROOMENTRANCES_ROCKET1,
    GOLDENRODUNDERGROUNDSWITCHROOMENTRANCES_ROCKET2,
    GOLDENRODUNDERGROUNDSWITCHROOMENTRANCES_ROCKET3,
    GOLDENRODUNDERGROUNDSWITCHROOMENTRANCES_ROCKET_GIRL,
    GOLDENRODUNDERGROUNDSWITCHROOMENTRANCES_TEACHER,
    GOLDENRODUNDERGROUNDSWITCHROOMENTRANCES_SUPER_NERD,
    GOLDENRODUNDERGROUNDSWITCHROOMENTRANCES_POKE_BALL1,
    GOLDENRODUNDERGROUNDSWITCHROOMENTRANCES_POKE_BALL2,
    GOLDENRODUNDERGROUNDSWITCHROOMENTRANCES_SILVER,
};

const Script_fn_t GoldenrodUndergroundSwitchRoomEntrances_SceneScripts[] = {
    GoldenrodUndergroundSwitchRoomEntrances_MapScripts_DummyScene0 , //  SCENE_DEFAULT,
    GoldenrodUndergroundSwitchRoomEntrances_MapScripts_DummyScene1 , //  SCENE_FINISHED,
};

const struct MapCallback GoldenrodUndergroundSwitchRoomEntrances_MapCallbacks[] = {
    map_callback(MAPCALLBACK_TILES, GoldenrodUndergroundSwitchRoomEntrances_MapScripts_UpdateDoorPositions),
};

const struct MapScripts GoldenrodUndergroundSwitchRoomEntrances_MapScripts = {
    .scene_script_count = lengthof(GoldenrodUndergroundSwitchRoomEntrances_SceneScripts),
    .scene_scripts = GoldenrodUndergroundSwitchRoomEntrances_SceneScripts,

    .callback_count = lengthof(GoldenrodUndergroundSwitchRoomEntrances_MapCallbacks),
    .callbacks = GoldenrodUndergroundSwitchRoomEntrances_MapCallbacks,
};

static const struct CoordEvent GoldenrodUndergroundSwitchRoomEntrances_CoordEvents[] = {
    coord_event(19, 4, SCENE_DEFAULT, &UndergroundSilverScene1),
    coord_event(19, 5, SCENE_DEFAULT, &UndergroundSilverScene2),
};

static const struct BGEvent GoldenrodUndergroundSwitchRoomEntrances_BGEvents[] = {
    bg_event(16, 1, BGEVENT_READ, &Switch1Script),
    bg_event(10, 1, BGEVENT_READ, &Switch2Script),
    bg_event(2, 1, BGEVENT_READ, &Switch3Script),
    bg_event(20, 11, BGEVENT_READ, &EmergencySwitchScript),
    bg_event(8, 9, BGEVENT_ITEM, &GoldenrodUndergroundSwitchRoomEntrancesHiddenMaxPotion),
    bg_event(1, 8, BGEVENT_ITEM, &GoldenrodUndergroundSwitchRoomEntrancesHiddenRevive),
};

static const struct WarpEventData GoldenrodUndergroundSwitchRoomEntrances_WarpEvents[] = {
    warp_event(23, 3, GOLDENROD_UNDERGROUND, 6),
    warp_event(22, 10, GOLDENROD_UNDERGROUND_WAREHOUSE, 1),
    warp_event(23, 10, GOLDENROD_UNDERGROUND_WAREHOUSE, 2),
    warp_event(5, 25, GOLDENROD_UNDERGROUND, 2),
    warp_event(4, 29, GOLDENROD_CITY, 14),
    warp_event(5, 29, GOLDENROD_CITY, 14),
    warp_event(21, 25, GOLDENROD_UNDERGROUND, 1),
    warp_event(20, 29, GOLDENROD_CITY, 13),
    warp_event(21, 29, GOLDENROD_CITY, 13),
};

static const struct ObjEvent GoldenrodUndergroundSwitchRoomEntrances_ObjectEvents[] = {
    object_event(9, 12, SPRITE_PHARMACIST, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 2, &TrainerBurglarDuncan, EVENT_RADIO_TOWER_ROCKET_TAKEOVER),
    object_event(4, 8, SPRITE_PHARMACIST, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 2, &TrainerBurglarEddie, EVENT_RADIO_TOWER_ROCKET_TAKEOVER),
    object_event(17, 2, SPRITE_ROCKET, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_TRAINER, 3, &TrainerGruntM13, EVENT_RADIO_TOWER_ROCKET_TAKEOVER),
    object_event(11, 2, SPRITE_ROCKET, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_TRAINER, 3, &TrainerGruntM11, EVENT_RADIO_TOWER_ROCKET_TAKEOVER),
    object_event(3, 2, SPRITE_ROCKET, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_TRAINER, 3, &TrainerGruntM25, EVENT_RADIO_TOWER_ROCKET_TAKEOVER),
    object_event(19, 12, SPRITE_ROCKET_GIRL, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 1, &TrainerGruntF3, EVENT_RADIO_TOWER_ROCKET_TAKEOVER),
    object_event(3, 27, SPRITE_TEACHER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &GoldenrodUndergroundSwitchRoomEntrancesTeacherScript, -1),
    object_event(19, 27, SPRITE_SUPER_NERD, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &GoldenrodUndergroundSwitchRoomEntrancesSuperNerdScript, -1),
    object_event(1, 12, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &GoldenrodUndergroundSwitchRoomEntrancesSmokeBall, EVENT_GOLDENROD_UNDERGROUND_SWITCH_ROOM_ENTRANCES_SMOKE_BALL),
    object_event(14, 9, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &GoldenrodUndergroundSwitchRoomEntrancesFullHeal, EVENT_GOLDENROD_UNDERGROUND_SWITCH_ROOM_ENTRANCES_FULL_HEAL),
    object_event(23, 3, SPRITE_SILVER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, EVENT_RIVAL_GOLDENROD_UNDERGROUND),
};

const struct MapEvents GoldenrodUndergroundSwitchRoomEntrances_MapEvents = {
    .warp_event_count = lengthof(GoldenrodUndergroundSwitchRoomEntrances_WarpEvents),
    .warp_events = GoldenrodUndergroundSwitchRoomEntrances_WarpEvents,

    .coord_event_count = lengthof(GoldenrodUndergroundSwitchRoomEntrances_CoordEvents),
    .coord_events = GoldenrodUndergroundSwitchRoomEntrances_CoordEvents,

    .bg_event_count = lengthof(GoldenrodUndergroundSwitchRoomEntrances_BGEvents),
    .bg_events = GoldenrodUndergroundSwitchRoomEntrances_BGEvents,

    .obj_event_count = lengthof(GoldenrodUndergroundSwitchRoomEntrances_ObjectEvents),
    .obj_events = GoldenrodUndergroundSwitchRoomEntrances_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "GoldenrodUndergroundSwitchRoomEntrances.h"

// block ids
#define UNDERGROUND_DOOR_CLOSED1 0x2a
#define UNDERGROUND_DOOR_CLOSED2 0x3e
#define UNDERGROUND_DOOR_CLOSED3 0x3f
#define UNDERGROUND_DOOR_OPEN1 0x2d
#define UNDERGROUND_DOOR_OPEN2 0x3d

#define ugdoor(_id, _x, _y) enum { UGDOOR_##_id##_XCOORD = _x, UGDOOR_##_id##_YCOORD = _y }
//      id,  x,  y
ugdoor(1, 6, 16);
ugdoor(2, 6, 10);
ugdoor(3, 6, 2);
ugdoor(4, 10, 2);
ugdoor(5, 10, 10);
ugdoor(6, 10, 16);
ugdoor(7, 6, 12);
ugdoor(8, 8, 12);
ugdoor(9, 6, 6);
ugdoor(10, 8, 6);
ugdoor(11, 10, 12);
ugdoor(12, 12, 12);
ugdoor(13, 10, 6);
ugdoor(14, 12, 6);
ugdoor(15, 10, 18);
ugdoor(16, 12, 18);

#define doorstate(_x, _y) changeblock(UGDOOR_##_x##_XCOORD, UGDOOR_##_x##_YCOORD, UNDERGROUND_DOOR_##_y)

bool GoldenrodUndergroundSwitchRoomEntrances_MapScripts_DummyScene0(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool GoldenrodUndergroundSwitchRoomEntrances_MapScripts_DummyScene1(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool GoldenrodUndergroundSwitchRoomEntrances_MapScripts_UpdateDoorPositions(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_SWITCH_4)
    iffalse(false4)
    doorstate(1, OPEN1)
false4:
    checkevent(EVENT_SWITCH_5)
    iffalse(false5)
    doorstate(2, OPEN1)
false5:
    checkevent(EVENT_SWITCH_6)
    iffalse(false6)
    doorstate(3, OPEN1)
false6:
    checkevent(EVENT_SWITCH_7)
    iffalse(false7)
    doorstate(4, OPEN1)
false7:
    checkevent(EVENT_SWITCH_8)
    iffalse(false8)
    doorstate(5, OPEN1)
false8:
    checkevent(EVENT_SWITCH_9)
    iffalse(false9)
    doorstate(6, OPEN1)
false9:
    checkevent(EVENT_SWITCH_10)
    iffalse(false10)
    doorstate(7, CLOSED1)
    doorstate(8, OPEN1)
false10:
    checkevent(EVENT_SWITCH_11)
    iffalse(false11)
    doorstate(9, CLOSED1)
    doorstate(10, OPEN1)
false11:
    checkevent(EVENT_SWITCH_12)
    iffalse(false12)
    doorstate(11, CLOSED1)
    doorstate(12, OPEN1)
false12:
    checkevent(EVENT_SWITCH_13)
    iffalse(false13)
    doorstate(13, CLOSED1)
    doorstate(14, OPEN1)
false13:
    checkevent(EVENT_SWITCH_14)
    iffalse(false14)
    doorstate(15, CLOSED1)
    doorstate(16, OPEN1)
false14:
    s_endcallback
    SCRIPT_END
}
bool GoldenrodUndergroundSwitchRoomEntrancesSuperNerdScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(GoldenrodUndergroundSwitchRoomEntrances_SuperNerdText)
    SCRIPT_END
}
bool GoldenrodUndergroundSwitchRoomEntrancesTeacherScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(GoldenrodUndergroundSwitchRoomEntrances_TeacherText)
    SCRIPT_END
}
bool UndergroundSilverScene1(script_s* s) {
    SCRIPT_BEGIN
    turnobject(PLAYER, RIGHT)
    showemote(EMOTE_SHOCK, PLAYER, 15)
    special(FadeOutMusic)
    pause(15)
    playsound(SFX_EXIT_BUILDING)
    appear(GOLDENRODUNDERGROUNDSWITCHROOMENTRANCES_SILVER)
    waitsfx
    applymovement(GOLDENRODUNDERGROUNDSWITCHROOMENTRANCES_SILVER, UndergroundSilverApproachMovement1)
    turnobject(PLAYER, RIGHT)
    scall(UndergroundSilverBattleScript)
    applymovement(GOLDENRODUNDERGROUNDSWITCHROOMENTRANCES_SILVER, UndergroundSilverRetreatMovement1)
    playsound(SFX_EXIT_BUILDING)
    disappear(GOLDENRODUNDERGROUNDSWITCHROOMENTRANCES_SILVER)
    setscene(SCENE_FINISHED)
    waitsfx
    playmapmusic
    s_end
    SCRIPT_END
}
bool UndergroundSilverScene2(script_s* s) {
    SCRIPT_BEGIN
    turnobject(PLAYER, RIGHT)
    showemote(EMOTE_SHOCK, PLAYER, 15)
    special(FadeOutMusic)
    pause(15)
    playsound(SFX_EXIT_BUILDING)
    appear(GOLDENRODUNDERGROUNDSWITCHROOMENTRANCES_SILVER)
    waitsfx
    applymovement(GOLDENRODUNDERGROUNDSWITCHROOMENTRANCES_SILVER, UndergroundSilverApproachMovement2)
    turnobject(PLAYER, RIGHT)
    scall(UndergroundSilverBattleScript)
    applymovement(GOLDENRODUNDERGROUNDSWITCHROOMENTRANCES_SILVER, UndergroundSilverRetreatMovement2)
    playsound(SFX_EXIT_BUILDING)
    disappear(GOLDENRODUNDERGROUNDSWITCHROOMENTRANCES_SILVER)
    setscene(SCENE_FINISHED)
    waitsfx
    playmapmusic
    s_end
    SCRIPT_END
}
bool UndergroundSilverBattleScript(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_RIVAL_BURNED_TOWER)
    iftrue(Continue)
    setevent(EVENT_RIVAL_BURNED_TOWER)
    setmapscene(BURNED_TOWER_1F, SCENE_BURNEDTOWER1F_RIVAL_BATTLE)
Continue:
    playmusic(MUSIC_RIVAL_ENCOUNTER)
    opentext
    writetext(UndergroundSilverBeforeText)
    waitbutton
    closetext
    setevent(EVENT_RIVAL_GOLDENROD_UNDERGROUND)
    checkevent(EVENT_GOT_TOTODILE_FROM_ELM)
    iftrue(Totodile)
    checkevent(EVENT_GOT_CHIKORITA_FROM_ELM)
    iftrue(Chikorita)
    winlosstext(UndergroundSilverWinText, UndergroundSilverLossText)
    setlasttalked(GOLDENRODUNDERGROUNDSWITCHROOMENTRANCES_SILVER)
    loadtrainer(RIVAL1, RIVAL1_4_TOTODILE)
    startbattle
    dontrestartmapmusic
    reloadmapafterbattle
    goto FinishRivalBattle;
Totodile:
    winlosstext(UndergroundSilverWinText, UndergroundSilverLossText)
    setlasttalked(GOLDENRODUNDERGROUNDSWITCHROOMENTRANCES_SILVER)
    loadtrainer(RIVAL1, RIVAL1_4_CHIKORITA)
    startbattle
    dontrestartmapmusic
    reloadmapafterbattle
    goto FinishRivalBattle;
Chikorita:
    winlosstext(UndergroundSilverWinText, UndergroundSilverLossText)
    setlasttalked(GOLDENRODUNDERGROUNDSWITCHROOMENTRANCES_SILVER)
    loadtrainer(RIVAL1, RIVAL1_4_CYNDAQUIL)
    startbattle
    dontrestartmapmusic
    reloadmapafterbattle
    goto FinishRivalBattle;
FinishRivalBattle:
    playmusic(MUSIC_RIVAL_AFTER)
    opentext
    writetext(UndergroundSilverAfterText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerGruntM11 = {GRUNTM, GRUNTM_11, EVENT_BEAT_ROCKET_GRUNTM_11, GruntM11SeenText, GruntM11BeatenText, 0, TrainerGruntM11_Script};
bool TrainerGruntM11_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(GruntM11AfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerGruntM25 = {GRUNTM, GRUNTM_25, EVENT_BEAT_ROCKET_GRUNTM_25, GruntM25SeenText, GruntM25BeatenText, 0, TrainerGruntM25_Script};
bool TrainerGruntM25_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(GruntM25AfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerBurglarDuncan = {BURGLAR, DUNCAN, EVENT_BEAT_BURGLAR_DUNCAN, BurglarDuncanSeenText, BurglarDuncanBeatenText, 0, TrainerBurglarDuncan_Script};
bool TrainerBurglarDuncan_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(BurglarDuncanAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerBurglarEddie = {BURGLAR, EDDIE, EVENT_BEAT_BURGLAR_EDDIE, BurglarEddieSeenText, BurglarEddieBeatenText, 0, TrainerBurglarEddie_Script};
bool TrainerBurglarEddie_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(BurglarEddieAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerGruntM13 = {GRUNTM, GRUNTM_13, EVENT_BEAT_ROCKET_GRUNTM_13, GruntM13SeenText, GruntM13BeatenText, 0, TrainerGruntM13_Script};
bool TrainerGruntM13_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(GruntM13AfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerGruntF3 = {GRUNTF, GRUNTF_3, EVENT_BEAT_ROCKET_GRUNTF_3, GruntF3SeenText, GruntF3BeatenText, 0, TrainerGruntF3_Script};
bool TrainerGruntF3_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(GruntF3AfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Switch1Script(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(SwitchRoomText_Switch1)
    promptbutton
    checkevent(EVENT_SWITCH_1)
    iftrue(On)
    writetext(SwitchRoomText_OffTurnOn)
    yesorno
    iffalse_jump(GoldenrodUndergroundSwitchRoomEntrances_DontToggle)
    readmem(wram_ptr(wUndergroundSwitchPositions))
    addval(1)
    writemem(wram_ptr(wUndergroundSwitchPositions))
    setevent(EVENT_SWITCH_1)
    sjump(GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors)
On:
    writetext(SwitchRoomText_OnTurnOff)
    yesorno
    iffalse_jump(GoldenrodUndergroundSwitchRoomEntrances_DontToggle)
    readmem(wram_ptr(wUndergroundSwitchPositions))
    addval(-1)
    writemem(wram_ptr(wUndergroundSwitchPositions))
    clearevent(EVENT_SWITCH_1)
    sjump(GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors)
    SCRIPT_END
}
bool Switch2Script(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(SwitchRoomText_Switch2)
    promptbutton
    checkevent(EVENT_SWITCH_2)
    iftrue(On)
    writetext(SwitchRoomText_OffTurnOn)
    yesorno
    iffalse_jump(GoldenrodUndergroundSwitchRoomEntrances_DontToggle)
    readmem(wram_ptr(wUndergroundSwitchPositions))
    addval(2)
    writemem(wram_ptr(wUndergroundSwitchPositions))
    setevent(EVENT_SWITCH_2)
    sjump(GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors)
On:
    writetext(SwitchRoomText_OnTurnOff)
    yesorno
    iffalse_jump(GoldenrodUndergroundSwitchRoomEntrances_DontToggle)
    readmem(wram_ptr(wUndergroundSwitchPositions))
    addval(-2)
    writemem(wram_ptr(wUndergroundSwitchPositions))
    clearevent(EVENT_SWITCH_2)
    sjump(GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors)
    SCRIPT_END
}
bool Switch3Script(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(SwitchRoomText_Switch3)
    promptbutton
    checkevent(EVENT_SWITCH_3)
    iftrue(On)
    writetext(SwitchRoomText_OffTurnOn)
    yesorno
    iffalse_jump(GoldenrodUndergroundSwitchRoomEntrances_DontToggle)
    readmem(wram_ptr(wUndergroundSwitchPositions))
    addval(3)
    writemem(wram_ptr(wUndergroundSwitchPositions))
    setevent(EVENT_SWITCH_3)
    sjump(GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors)
On:
    writetext(SwitchRoomText_OnTurnOff)
    yesorno
    iffalse_jump(GoldenrodUndergroundSwitchRoomEntrances_DontToggle)
    readmem(wram_ptr(wUndergroundSwitchPositions))
    addval(-3)
    writemem(wram_ptr(wUndergroundSwitchPositions))
    clearevent(EVENT_SWITCH_3)
    sjump(GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors)
    SCRIPT_END
}
bool EmergencySwitchScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(SwitchRoomText_Emergency)
    promptbutton
    checkevent(EVENT_EMERGENCY_SWITCH)
    iftrue(On)
    writetext(SwitchRoomText_OffTurnOn)
    yesorno
    iffalse_jump(GoldenrodUndergroundSwitchRoomEntrances_DontToggle)
    setval(7)
    writemem(wram_ptr(wUndergroundSwitchPositions))
    setevent(EVENT_EMERGENCY_SWITCH)
    setevent(EVENT_SWITCH_1)
    setevent(EVENT_SWITCH_2)
    setevent(EVENT_SWITCH_3)
    sjump(GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors)
On:
    writetext(SwitchRoomText_OnTurnOff)
    yesorno
    iffalse_jump(GoldenrodUndergroundSwitchRoomEntrances_DontToggle)
    setval(0)
    writemem(wram_ptr(wUndergroundSwitchPositions))
    clearevent(EVENT_EMERGENCY_SWITCH)
    clearevent(EVENT_SWITCH_1)
    clearevent(EVENT_SWITCH_2)
    clearevent(EVENT_SWITCH_3)
    sjump(GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors)
    SCRIPT_END
}
bool GoldenrodUndergroundSwitchRoomEntrances_DontToggle(script_s* s) {
    SCRIPT_BEGIN
    closetext
    s_end
    SCRIPT_END
}
bool GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors(script_s* s) {
    SCRIPT_BEGIN
    readmem(wram_ptr(wUndergroundSwitchPositions))
    ifequal(0, Position0)
    ifequal(1, Position1)
    ifequal(2, Position2)
    ifequal(3, Position3)
    ifequal(4, Position4)
    ifequal(5, Position5)
    ifequal(6, Position6)
    ifequal(7, EmergencyPosition)
Position0:
    playsound(SFX_ENTER_DOOR)
    scall_local(Clear4);
    scall_local(Clear5);
    scall_local(Clear6);
    scall_local(Clear7);
    scall_local(Clear8);
    scall_local(Clear9);
    scall_local(Clear10);
    scall_local(Clear11);
    scall_local(Clear12);
    scall_local(Clear13);
    scall_local(Clear14);
    reloadmappart
    closetext
    s_end
Position1:
    playsound(SFX_ENTER_DOOR)
    scall_local(Set4);
    scall_local(Set10);
    scall_local(Set13);
    scall_local(Clear9);
    scall_local(Clear11);
    scall_local(Clear12);
    scall_local(Clear14);
    reloadmappart
    closetext
    s_end
Position2:
    playsound(SFX_ENTER_DOOR)
    scall_local(Set5);
    scall_local(Set11);
    scall_local(Set12);
    scall_local(Clear8);
    scall_local(Clear10);
    scall_local(Clear13);
    scall_local(Clear14);
    reloadmappart
    closetext
    s_end
Position3:
    playsound(SFX_ENTER_DOOR)
    scall_local(Set6);
    scall_local(Set10);
    scall_local(Set13);
    scall_local(Clear7);
    scall_local(Clear11);
    scall_local(Clear12);
    scall_local(Clear14);
    reloadmappart
    closetext
    s_end
Position4:
    playsound(SFX_ENTER_DOOR)
    scall_local(Set7);
    scall_local(Set11);
    scall_local(Set12);
    scall_local(Clear6);
    scall_local(Clear10);
    scall_local(Clear13);
    scall_local(Clear14);
    reloadmappart
    closetext
    s_end
Position5:
    playsound(SFX_ENTER_DOOR)
    scall_local(Set8);
    scall_local(Set10);
    scall_local(Set13);
    scall_local(Clear5);
    scall_local(Clear11);
    scall_local(Clear12);
    scall_local(Clear14);
    reloadmappart
    closetext
    s_end
Position6:
    playsound(SFX_ENTER_DOOR)
    scall_local(Set9);
    scall_local(Set11);
    scall_local(Set12);
    scall_local(Set14);
    scall_local(Clear4);
    scall_local(Clear10);
    scall_local(Clear13);
    reloadmappart
    closetext
    s_end
EmergencyPosition:
    playsound(SFX_ENTER_DOOR)
    scall_local(Clear4);
    scall_local(Clear5);
    scall_local(Set6);
    scall_local(Clear7);
    scall_local(Set8);
    scall_local(Set9);
    scall_local(Clear10);
    scall_local(Set11);
    scall_local(Set12);
    scall_local(Clear13);
    scall_local(Set14);
    reloadmappart
    closetext
    setval(6)
    writemem(wram_ptr(wUndergroundSwitchPositions))
    s_end
Set4:
    doorstate(1, OPEN1)
    setevent(EVENT_SWITCH_4)
    s_end
Set5:
    doorstate(2, OPEN1)
    setevent(EVENT_SWITCH_5)
    s_end
Set6:
    doorstate(3, OPEN1)
    setevent(EVENT_SWITCH_6)
    s_end
Set7:
    doorstate(4, OPEN1)
    setevent(EVENT_SWITCH_7)
    s_end
Set8:
    doorstate(5, OPEN1)
    setevent(EVENT_SWITCH_8)
    s_end
Set9:
    doorstate(6, OPEN1)
    setevent(EVENT_SWITCH_9)
    s_end
Set10:
    doorstate(7, CLOSED1)
    doorstate(8, OPEN1)
    setevent(EVENT_SWITCH_10)
    s_end
Set11:
    doorstate(9, CLOSED1)
    doorstate(10, OPEN1)
    setevent(EVENT_SWITCH_11)
    s_end
Set12:
    doorstate(11, CLOSED1)
    doorstate(12, OPEN1)
    setevent(EVENT_SWITCH_12)
    s_end
Set13:
    doorstate(13, CLOSED1)
    doorstate(14, OPEN1)
    setevent(EVENT_SWITCH_13)
    s_end
Set14:
    doorstate(15, CLOSED1)
    doorstate(16, OPEN1)
    setevent(EVENT_SWITCH_14)
    s_end
Clear4:
    doorstate(1, CLOSED2)
    clearevent(EVENT_SWITCH_4)
    s_end
Clear5:
    doorstate(2, CLOSED2)
    clearevent(EVENT_SWITCH_5)
    s_end
Clear6:
    doorstate(3, CLOSED2)
    clearevent(EVENT_SWITCH_6)
    s_end
Clear7:
    doorstate(4, CLOSED2)
    clearevent(EVENT_SWITCH_7)
    s_end
Clear8:
    doorstate(5, CLOSED2)
    clearevent(EVENT_SWITCH_8)
    s_end
Clear9:
    doorstate(6, CLOSED2)
    clearevent(EVENT_SWITCH_9)
    s_end
Clear10:
    doorstate(7, CLOSED3)
    doorstate(8, OPEN2)
    clearevent(EVENT_SWITCH_10)
    s_end
Clear11:
    doorstate(9, CLOSED3)
    doorstate(10, OPEN2)
    clearevent(EVENT_SWITCH_11)
    s_end
Clear12:
    doorstate(11, CLOSED3)
    doorstate(12, OPEN2)
    clearevent(EVENT_SWITCH_12)
    s_end
Clear13:
    doorstate(13, CLOSED3)
    doorstate(14, OPEN2)
    clearevent(EVENT_SWITCH_13)
    s_end
Clear14:
    doorstate(15, CLOSED3)
    doorstate(16, OPEN2)
    clearevent(EVENT_SWITCH_14)
    s_end
    SCRIPT_END
}
const struct ItemBall GoldenrodUndergroundSwitchRoomEntrancesSmokeBall = {SMOKE_BALL, 1};
const struct ItemBall GoldenrodUndergroundSwitchRoomEntrancesFullHeal = {FULL_HEAL, 1};
const struct HiddenItem GoldenrodUndergroundSwitchRoomEntrancesHiddenMaxPotion = {MAX_POTION, EVENT_GOLDENROD_UNDERGROUND_SWITCH_ROOM_ENTRANCES_HIDDEN_MAX_POTION};
const struct HiddenItem GoldenrodUndergroundSwitchRoomEntrancesHiddenRevive = {REVIVE, EVENT_GOLDENROD_UNDERGROUND_SWITCH_ROOM_ENTRANCES_HIDDEN_REVIVE};
const uint8_t UndergroundSilverApproachMovement1[] = {
    step(DOWN),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    movement_step_end,
};
const uint8_t UndergroundSilverApproachMovement2[] = {
    step(DOWN),
    step(DOWN),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    movement_step_end,
};
const uint8_t UndergroundSilverRetreatMovement1[] = {
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    step(UP),
    movement_step_end,
};
const uint8_t UndergroundSilverRetreatMovement2[] = {
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    step(UP),
    step(UP),
    movement_step_end,
};
const txt_cmd_s UndergroundSilverBeforeText[] = {
    text_start("Hold it!"
        t_para "I saw you, so I"
        t_line "tailed you."
        t_para "I don't need you"
        t_line "underfoot while I"
        t_para "take care of TEAM"
        t_line "ROCKET."
        t_para "…Wait a second."
        t_line "You beat me be-"
        t_cont "fore, didn't you?"
        t_para "That was just a"
        t_line "fluke."
        t_para "But I repay my"
        t_line "debts!"
        t_done )
};
const txt_cmd_s UndergroundSilverWinText[] = {
    text_start("…Why…"
        t_line "Why do I lose?"
        t_para "I've assembled the"
        t_line "toughest #MON."
        t_para "I didn't ease up"
        t_line "on the gas."
        t_para "So why do I lose?"
        t_done )
};
const txt_cmd_s UndergroundSilverAfterText[] = {
    text_start("…I don't under-"
        t_line "stand…"
        t_para "Is what that LANCE"
        t_line "guy said true?"
        t_para "That I don't treat"
        t_line "#MON properly?"
        t_para "Love…"
        t_para "Trust…"
        t_para "Are they really"
        t_line "what I lack?"
        t_para "Are they keeping"
        t_line "me from winning?"
        t_para "I… I just don't"
        t_line "understand."
        t_para "But it's not going"
        t_line "to end here."
        t_para "Not now. Not"
        t_line "because of this."
        t_para "I won't give up my"
        t_line "dream of becoming"
        t_para "the world's best"
        t_line "#MON trainer!"
        t_done )
};
const txt_cmd_s UndergroundSilverLossText[] = {
    text_start("Humph. This is my"
        t_line "real power, wimp."
        t_para "I'll make TEAM"
        t_line "ROCKET history."
        t_para "And I'm going to"
        t_line "grind that LANCE"
        t_cont "under my heels."
        t_done )
};
const txt_cmd_s GoldenrodUndergroundSwitchRoomEntrances_SuperNerdText[] = {
    text_start("I was challenged"
        t_line "to a battle down-"
        t_cont "stairs."
        t_para "It's rough down"
        t_line "there. You'd"
        t_cont "better be careful."
        t_done )
};
const txt_cmd_s GoldenrodUndergroundSwitchRoomEntrances_TeacherText[] = {
    text_start("There are some"
        t_line "shops downstairs…"
        t_para "But there are"
        t_line "also trainers."
        t_para "I'm scared to go"
        t_line "down there."
        t_done )
};
const txt_cmd_s GruntM11SeenText[] = {
    text_start("Open one shutter,"
        t_line "another closes."
        t_para "Bet you can't get"
        t_line "where you want!"
        t_done )
};
const txt_cmd_s GruntM11BeatenText[] = {
    text_start("Drat! I was sunk"
        t_line "by indecision!"
        t_done )
};
const txt_cmd_s GruntM11AfterBattleText[] = {
    text_start("I'm confused too…"
        t_line "The switch on the"
        t_para "end is the one to"
        t_line "press first, but…"
        t_done )
};
const txt_cmd_s GruntM25SeenText[] = {
    text_start("Kwahaha!"
        t_para "Confounded by the"
        t_line "shutters, are we?"
        t_para "I'll let you in on"
        t_line "a secret if you"
        t_cont "can beat me!"
        t_done )
};
const txt_cmd_s GruntM25BeatenText[] = {
    text_start("Uwww…"
        t_line "I blew it."
        t_done )
};
const txt_cmd_s GruntM25AfterBattleText[] = {
    text_start("All right. A hint!"
        t_para "Change the order"
        t_line "of switching."
        t_para "That'll change the"
        t_line "ways the shutters"
        t_cont "open and close."
        t_done )
};
const txt_cmd_s BurglarDuncanSeenText[] = {
    text_start("Fork over your"
        t_line "goodies!"
        t_done )
};
const txt_cmd_s BurglarDuncanBeatenText[] = {
    text_start("Mercy!"
        t_done )
};
const txt_cmd_s BurglarDuncanAfterBattleText[] = {
    text_start("Steal and sell!"
        t_line "That's basic in"
        t_cont "crime, kid!"
        t_done )
};
const txt_cmd_s BurglarEddieSeenText[] = {
    text_start("They ditched this"
        t_line "project before"
        t_cont "they finished."
        t_para "I'm searching for"
        t_line "leftover loot."
        t_done )
};
const txt_cmd_s BurglarEddieBeatenText[] = {
    text_start("Over the top!"
        t_done )
};
const txt_cmd_s BurglarEddieAfterBattleText[] = {
    text_start("UNDERGROUND WARE-"
        t_line "HOUSE?"
        t_para "What do you want"
        t_line "to go there for?"
        t_para "There's nothing"
        t_line "down there."
        t_done )
};
const txt_cmd_s GruntM13SeenText[] = {
    text_start("I don't care if"
        t_line "you're lost."
        t_para "You show up here,"
        t_line "you're nothing but"
        t_cont "a victim!"
        t_done )
};
const txt_cmd_s GruntM13BeatenText[] = {
    text_start("Urk! Yeah, think"
        t_line "you're cool, huh?"
        t_done )
};
const txt_cmd_s GruntM13AfterBattleText[] = {
    text_start("You must have ice"
        t_line "in your veins to"
        t_cont "dis TEAM ROCKET."
        t_done )
};
const txt_cmd_s SwitchRoomText_Switch1[] = {
    text_start("It's labeled"
        t_line "SWITCH 1."
        t_done )
};
const txt_cmd_s GruntF3SeenText[] = {
    text_start("Are you lost? No,"
        t_line "you can't be."
        t_para "You don't have"
        t_line "that scared look."
        t_para "I'll give you"
        t_line "something to be"
        t_cont "scared about!"
        t_done )
};
const txt_cmd_s GruntF3BeatenText[] = {
    text_start("How could you?"
        t_done )
};
const txt_cmd_s GruntF3AfterBattleText[] = {
    text_start("Go wherever you'd"
        t_line "like! Get lost!"
        t_cont "See if I care!"
        t_done )
};
const txt_cmd_s SwitchRoomText_OffTurnOn[] = {
    text_start("It's OFF."
        t_line "Turn it ON?"
        t_done )
};
const txt_cmd_s SwitchRoomText_OnTurnOff[] = {
    text_start("It's ON."
        t_line "Turn it OFF?"
        t_done )
};
const txt_cmd_s SwitchRoomText_Switch2[] = {
    text_start("It's labeled"
        t_line "SWITCH 2."
        t_done )
};
const txt_cmd_s SwitchRoomText_Switch3[] = {
    text_start("It's labeled"
        t_line "SWITCH 3."
        t_done )
};
const txt_cmd_s SwitchRoomText_Emergency[] = {
    text_start("It's labeled"
        t_line "EMERGENCY."
        t_done )
    //db(0, 0) // filler
};
