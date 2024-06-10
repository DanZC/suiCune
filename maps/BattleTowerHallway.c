#include "../constants.h"
#include "../util/scripting.h"
#include "BattleTowerHallway.h"
#include "BattleTower1F.h"
//// EVENTS
enum {
    BATTLETOWERHALLWAY_RECEPTIONIST = 2,
};

const Script_fn_t BattleTowerHallway_SceneScripts[] = {
    BattleTowerHallway_MapScripts_Scene0 , //  SCENE_DEFAULT,
    BattleTowerHallway_MapScripts_Scene1 , //  SCENE_FINISHED,
};

const struct MapCallback BattleTowerHallway_MapCallbacks[] = {
    0,
};

const struct MapScripts BattleTowerHallway_MapScripts = {
    .scene_script_count = lengthof(BattleTowerHallway_SceneScripts),
    .scene_scripts = BattleTowerHallway_SceneScripts,

    .callback_count = 0, // lengthof(BattleTowerHallway_MapCallbacks),
    .callbacks = BattleTowerHallway_MapCallbacks,
};

static const struct CoordEvent BattleTowerHallway_CoordEvents[] = {
    0,
};

static const struct BGEvent BattleTowerHallway_BGEvents[] = {
    0,
};

static const struct WarpEventData BattleTowerHallway_WarpEvents[] = {
    warp_event(11, 1, BATTLE_TOWER_ELEVATOR, 1),
    warp_event(5, 0, BATTLE_TOWER_BATTLE_ROOM, 1),
    warp_event(7, 0, BATTLE_TOWER_BATTLE_ROOM, 1),
    warp_event(9, 0, BATTLE_TOWER_BATTLE_ROOM, 1),
    warp_event(13, 0, BATTLE_TOWER_BATTLE_ROOM, 1),
    warp_event(15, 0, BATTLE_TOWER_BATTLE_ROOM, 1),
};

static const struct ObjEvent BattleTowerHallway_ObjectEvents[] = {
    object_event(11, 2, SPRITE_RECEPTIONIST, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &BattleTowerHallway_MapEvents, -1),
};

const struct MapEvents BattleTowerHallway_MapEvents = {
    .warp_event_count = lengthof(BattleTowerHallway_WarpEvents),
    .warp_events = BattleTowerHallway_WarpEvents,

    .coord_event_count = 0, // lengthof(BattleTowerHallway_CoordEvents),
    .coord_events = BattleTowerHallway_CoordEvents,

    .bg_event_count = 0, // lengthof(BattleTowerHallway_BGEvents),
    .bg_events = BattleTowerHallway_BGEvents,

    .obj_event_count = lengthof(BattleTowerHallway_ObjectEvents),
    .obj_events = BattleTowerHallway_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "BattleTowerHallway.h"

bool BattleTowerHallway_MapScripts_Scene0(script_s* s) {
    SCRIPT_BEGIN
    sdefer(BattleTowerHallway_MapScripts_ChooseBattleRoom)
    setscene(SCENE_FINISHED)
    SCRIPT_FALLTHROUGH(BattleTowerHallway_MapScripts_Scene1)
}
bool BattleTowerHallway_MapScripts_Scene1(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}

static void BattleTowerHallway_MapScripts_asm_load_battle_room(void) {
    //ldh(a, [rSVBK])
    //push(af)
    //ld(a, BANK(wBTChoiceOfLvlGroup))
    //ldh([rSVBK], a)
    //ld(a, [wBTChoiceOfLvlGroup])
    //ld([wScriptVar], a)
    wram->wScriptVar = wram->wBTChoiceOfLvlGroup;
    //pop(af)
    //ldh([rSVBK], a)
    //ret
}

bool BattleTowerHallway_MapScripts_ChooseBattleRoom(script_s* s) {
    SCRIPT_BEGIN
    follow(BATTLETOWERHALLWAY_RECEPTIONIST, PLAYER)
    BattleTowerHallway_MapScripts_asm_load_battle_room();
// enter different rooms for different levels to battle against
// at least it should look like that
// because all warps lead to the same room
WalkToChosenBattleRoom:
    ifequal(3, L30L40)
    ifequal(4, L30L40)
    ifequal(5, L50L60)
    ifequal(6, L50L60)
    ifequal(7, L70L80)
    ifequal(8, L70L80)
    ifequal(9, L90L100)
    ifequal(10, L90L100)
    applymovement(BATTLETOWERHALLWAY_RECEPTIONIST, MovementData_BattleTowerHallwayWalkTo1020Room)
    goto EnterBattleRoom;
L30L40:
    applymovement(BATTLETOWERHALLWAY_RECEPTIONIST, MovementData_BattleTowerHallwayWalkTo3040Room)
    goto EnterBattleRoom;
L50L60:
    applymovement(BATTLETOWERHALLWAY_RECEPTIONIST, MovementData_BattleTowerHallwayWalkTo5060Room)
    goto EnterBattleRoom;
L70L80:
    applymovement(BATTLETOWERHALLWAY_RECEPTIONIST, MovementData_BattleTowerHallwayWalkTo7080Room)
    goto EnterBattleRoom;
L90L100:
    applymovement(BATTLETOWERHALLWAY_RECEPTIONIST, MovementData_BattleTowerHallwayWalkTo90100Room)
    goto EnterBattleRoom;
EnterBattleRoom:
    faceobject(PLAYER, BATTLETOWERHALLWAY_RECEPTIONIST)
    opentext
    writetext(Text_PleaseStepThisWay)
    waitbutton
    closetext
    stopfollow
    applymovement(PLAYER, MovementData_BattleTowerHallwayPlayerEntersBattleRoom)
    warpcheck
    s_end
    //db(0, 0) // filler
    SCRIPT_END
}
