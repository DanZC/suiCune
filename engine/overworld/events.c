#include "../../constants.h"
#include "../../util/scripting.h"
#include "../../util/scripting_macros.h"
#include "events.h"
#include "../../home/map.h"
#include "../../home/map_objects.h"
#include "player_movement.h"
#include "npc_movement.h"
#include "tile_events.h"
#include "wildmons.h"
#include "time.h"
#include "map_setup.h"
#include "warp_connection.h"
#include "player_step.h"
#include "player_object.h"
#include "map_objects.h"
#include "select_menu.h"
#include "../../home/joypad.h"
#include "../../home/queue_script.h"
#include "../../home/delay.h"
#include "../../home/trainers.h"
#include "../../home/copy.h"
#include "../../home/audio.h"
#include "../../home/time.h"
#include "../../home/time_palettes.h"
#include "../../home/flag.h"
#include "../../home/gfx.h"
#include "../../home/menu.h"
#include "../../home/random.h"
#include "../../home/math.h"
#include "../phone/phone.h"
#include "../menus/start_menu.h"
#include "../events/forced_movement.h"
#include "../events/whiteout.h"
#include "../events/misc_scripts.h"
#include "../events/repel.h"
#include "../events/map_name_sign.h"
#include "../events/trainer_scripts.h"
#include "../events/std_collision.h"
#include "../events/overworld.h"
#include "../events/hidden_item.h"
#include "../events/poisonstep.h"
#include "../events/happiness_egg.h"
#include "../events/bug_contest/contest.h"
#include "../menus/debug_field_menu.h"
#include "../pokemon/breeding.h"
#include "../../data/wild/bug_contest_mons.h"

// INCLUDE "constants.asm"

Script_fn_t gMapReentryScriptAddress;
#if DEBUG
static bool DebugFieldMenuScript(script_s* s);
#endif

static void EnableWildEncounters(void);
static bool CheckWarpConnxnScriptFlag(void);
static bool CheckCoordEventScriptFlag(void);
static bool CheckStepCountScriptFlag(void);
static bool CheckWildEncountersScriptFlag(void);
static void StartMap(void);
static void EnterMap(void);
static void HandleMap(void);
static void MapEvents(void);
static void ResetOverworldDelay(void);
static void NextOverworldFrame(void);
static void HandleMapTimeAndJoypad(void);
static void HandleMapObjects(void);
static void HandleMapBackground(void);

static void CheckPlayerState(void);
static void v_CheckObjectEnteringVisibleRange(void);
static bool PlayerEvents(void);
static u8_flag_s CheckTrainerBattle_GetPlayerEvent(void);
static u8_flag_s CheckTileEvent(void);
static bool CheckWildEncounterCooldown(void);
static void SetUpFiveStepWildEncounterCooldown(void);
static u8_flag_s RunSceneScript(void);
static u8_flag_s CheckTimeEvents(void);
static u8_flag_s OWPlayerInput(void);
static u8_flag_s CheckAPressOW(void);
static void PlayTalkObject(void);
static u8_flag_s TryObjectEvent(void);
static u8_flag_s TryBGEvent(void);
static u8_flag_s BGEventJumptable(uint8_t a);
static bool CheckBGEventFlag(void);
static u8_flag_s PlayerMovement(void);
static u8_flag_s CheckMenuOW(void);

static bool StartMenuScript(script_s* s);
static bool SelectMenuScript(script_s* s);
static bool StartMenuCallback(script_s* s);
static bool SelectMenuCallback(script_s* s);

static u8_flag_s CountStep(void);
static bool DoRepelStep(void);
static void DoPlayerEvent(void);

static bool InvalidEventScript(script_s* s);
static bool HatchEggScript(script_s* s);
static bool WarpToNewMapScript(script_s* s);
static bool FallIntoMapScript(script_s* s);
static bool LandAfterPitfallScript(script_s* s);
static bool EdgeWarpScript(script_s* s);
static bool ChangeDirectionScript(script_s* s);

static u8_flag_s RunMemScript(void);
static u8_flag_s TryTileCollisionEvent(void);
static u8_flag_s RandomEncounter(void);
static bool WildBattleScript(script_s* s);
static bool v_TryWildEncounter_BugContest(void);
static bool DoBikeStep(void);

// SECTION "Events", ROMX

void OverworldLoop(void){
    // XOR_A_A;  // MAPSTATUS_START
    // LD_addr_A(wMapStatus);
    wram->wMapStatus = MAPSTATUS_START;

    do {
    // loop:
        // LD_A_addr(wMapStatus);
        // LD_HL(mOverworldLoop_Jumptable);
        // RST(aJumpTable);
        switch(wram->wMapStatus) {
            case MAPSTATUS_START:   StartMap();  break;
            case MAPSTATUS_ENTER:   EnterMap();  break;
            case MAPSTATUS_HANDLE:  HandleMap(); break;
        }
        // LD_A_addr(wMapStatus);
        // CP_A(MAPSTATUS_DONE);
        // IF_NZ goto loop;
    } while(wram->wMapStatus != MAPSTATUS_DONE);

// done:
    // RET;
    return;

// Jumptable:
//  entries correspond to MAPSTATUS_* constants
    //dw ['StartMap'];
    //dw ['EnterMap'];
    //dw ['HandleMap'];
    //dw ['.done'];

    // return DisableEvents();
}

void DisableEvents(void){
    // XOR_A_A;
    // LD_addr_A(wScriptFlags2);
    wram->wScriptFlags2 = 0;
    // RET;
}

void EnableEvents(void){
    // LD_A(0xff);
    // LD_addr_A(wScriptFlags2);
    wram->wScriptFlags2 = 0xff;
    // RET;
}

void CheckBit5_ScriptFlags2(void){
    LD_HL(wScriptFlags2);
    BIT_hl(5);
    RET;

}

void DisableWarpsConnxns(void){
//  //  unreferenced
    LD_HL(wScriptFlags2);
    RES_hl(2);
    RET;

}

void DisableCoordEvents(void){
//  //  unreferenced
    LD_HL(wScriptFlags2);
    RES_hl(1);
    RET;

}

void DisableStepCount(void){
//  //  unreferenced
    LD_HL(wScriptFlags2);
    RES_hl(0);
    RET;

}

void DisableWildEncounters(void){
//  //  unreferenced
    LD_HL(wScriptFlags2);
    RES_hl(4);
    RET;

}

void EnableWarpsConnxns(void){
//  //  unreferenced
    LD_HL(wScriptFlags2);
    SET_hl(2);
    RET;

}

void EnableCoordEvents(void){
//  //  unreferenced
    LD_HL(wScriptFlags2);
    SET_hl(1);
    RET;

}

void EnableStepCount(void){
//  //  unreferenced
    LD_HL(wScriptFlags2);
    SET_hl(0);
    RET;

}

static void EnableWildEncounters(void){
    // LD_HL(wScriptFlags2);
    // SET_hl(4);
    bit_set(wram->wScriptFlags2, 4);
    // RET;
}

static bool CheckWarpConnxnScriptFlag(void){
    // LD_HL(wScriptFlags2);
    // BIT_hl(2);
    // RET;
    return bit_test(wram->wScriptFlags2, 2);
}

static bool CheckCoordEventScriptFlag(void){
    // LD_HL(wScriptFlags2);
    // BIT_hl(1);
    // RET;
    return bit_test(wram->wScriptFlags2, 1);
}

static bool CheckStepCountScriptFlag(void){
    // LD_HL(wScriptFlags2);
    // BIT_hl(0);
    // RET;
    return bit_test(wram->wScriptFlags2, 0);
}

static bool CheckWildEncountersScriptFlag(void){
    // LD_HL(wScriptFlags2);
    // BIT_hl(4);
    // RET;
    return bit_test(wram->wScriptFlags2, 4);
}

static void StartMap(void){
    // XOR_A_A;
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = 0;
    // XOR_A_A;
    // LD_addr_A(wScriptRunning);
    wram->wScriptRunning = FALSE;
    // LD_HL(wMapStatus);
    // LD_BC(wMapStatusEnd - wMapStatus);
    // CALL(aByteFill);
    ByteFill(&wram->wMapStatus, wMapStatusEnd - wMapStatus, 0);
    hram.hBGMapMode = BGMAPMODE_NONE;
    // FARCALL(aInitCallReceiveDelay);
    InitCallReceiveDelay();
    // CALL(aClearJoypad);
    ClearJoypad();
    return EnterMap();
}

static void EnterMap(void){
    // XOR_A_A;
    // LD_addr_A(wXYComparePointer);
    // LD_addr_A(wXYComparePointer + 1);
    wram->wXYComparePointer = 0;
    // CALL(aSetUpFiveStepWildEncounterCooldown);
    SetUpFiveStepWildEncounterCooldown();
    // FARCALL(aRunMapSetupScript);
    RunMapSetupScript();
    // CALL(aDisableEvents);
    DisableEvents();

    // LDH_A_addr(hMapEntryMethod);
    // CP_A(MAPSETUP_CONNECTION);
    // IF_NZ goto dont_enable;
    if(hram.hMapEntryMethod == MAPSETUP_CONNECTION) {
        // CALL(aEnableEvents);
        EnableEvents();
    }

// dont_enable:

    // LDH_A_addr(hMapEntryMethod);
    // CP_A(MAPSETUP_RELOADMAP);
    // IF_NZ goto dontresetpoison;
    if(hram.hMapEntryMethod == MAPSETUP_RELOADMAP) {
        // XOR_A_A;
        // LD_addr_A(wPoisonStepCount);
        gPlayer.poisonStepCount = 0;
    }

// dontresetpoison:

    // XOR_A_A;  // end map entry
    // LDH_addr_A(hMapEntryMethod);
    hram.hMapEntryMethod = 0;
    // LD_A(MAPSTATUS_HANDLE);
    // LD_addr_A(wMapStatus);
    wram->wMapStatus = MAPSTATUS_HANDLE;
    // RET;
}

void UnusedWait30Frames(void){
//  //  unreferenced
    LD_C(30);
    CALL(aDelayFrames);
    RET;

}

static void HandleMap(void){
    // CALL(aResetOverworldDelay);
    ResetOverworldDelay();
    // CALL(aHandleMapTimeAndJoypad);
    HandleMapTimeAndJoypad();
    // FARCALL(aHandleCmdQueue);  // no need to farcall
    HandleCmdQueue();
    // CALL(aMapEvents);
    MapEvents();

//  Not immediately entering a connected map will cause problems.
    // LD_A_addr(wMapStatus);
    // CP_A(MAPSTATUS_HANDLE);
    // RET_NZ ;
    if(wram->wMapStatus != MAPSTATUS_HANDLE)
        return;

    // CALL(aHandleMapObjects);
    HandleMapObjects();
    // CALL(aNextOverworldFrame);
    NextOverworldFrame();
    // CALL(aHandleMapBackground);
    HandleMapBackground();
    // CALL(aCheckPlayerState);
    CheckPlayerState();
    // RET;
}

static void MapEvents(void){
    // LD_A_addr(wMapEventStatus);
    // LD_HL(mMapEvents_Jumptable);
    // RST(aJumpTable);
    // RET;

// Jumptable:
//  entries correspond to MAPEVENTS_* constants
    switch(wram->wMapEventStatus) {
    case MAPEVENTS_ON:
    // events:
        // CALL(aPlayerEvents);
        PlayerEvents();
        // CALL(aDisableEvents);
        DisableEvents();
        // FARCALL(aScriptEvents);
        ScriptEvents();
        // RET;
        return;
    case MAPEVENTS_OFF:
    // no_events:
        // RET;
        return;
    }
}

void MaxOverworldDelay(void){
    //db ['2'];

    return ResetOverworldDelay();
}

#define MAX_OVERWORLD_DELAY 2

static void ResetOverworldDelay(void){
    // LD_A_addr(mMaxOverworldDelay);
    // LD_addr_A(wOverworldDelay);
    wram->wOverworldDelay = MAX_OVERWORLD_DELAY;
    // RET;
}

static void NextOverworldFrame(void){
    // LD_A_addr(wOverworldDelay);
    // AND_A_A;
    // RET_Z ;
    if(wram->wOverworldDelay == 0)
        return;
    // LD_C_A;
    // CALL(aDelayFrames);
    DelayFrames(wram->wOverworldDelay);
    // RET;
}

static void HandleMapTimeAndJoypad(void){
    // LD_A_addr(wMapEventStatus);
    // CP_A(MAPEVENTS_OFF);
    // RET_Z ;
    if(wram->wMapEventStatus == MAPEVENTS_OFF)
        return;

    // CALL(aUpdateTime);
    UpdateTime();
    // CALL(aGetJoypad);
    GetJoypad();
    // CALL(aTimeOfDayPals);
    TimeOfDayPals();
    // RET;
}

static void HandleMapObjects(void){
    // FARCALL(aHandleNPCStep);
    HandleNPCStep();
    // FARCALL(av_HandlePlayerStep);
    v_HandlePlayerStep();
    // CALL(av_CheckObjectEnteringVisibleRange);
    v_CheckObjectEnteringVisibleRange();
    // RET;
}

static void HandleMapBackground(void){
    // FARCALL(av_UpdateSprites);
    v_UpdateSprites();
    // FARCALL(aScrollScreen);
    ScrollScreen();
    // FARCALL(aPlaceMapNameSign);
    PlaceMapNameSign();
    // RET;
}

static void CheckPlayerState(void){
    // LD_A_addr(wPlayerStepFlags);
    // BIT_A(PLAYERSTEP_CONTINUE_F);
    // IF_Z goto events;
    if(!bit_test(wram->wPlayerStepFlags, PLAYERSTEP_CONTINUE_F)) {
    // events:
        // LD_A(MAPEVENTS_ON);
        // LD_addr_A(wMapEventStatus);
        wram->wMapEventStatus = MAPEVENTS_ON;
        // RET;
        return;
    }
    // BIT_A(PLAYERSTEP_STOP_F);
    // IF_Z goto noevents;
    // BIT_A(PLAYERSTEP_MIDAIR_F);
    // IF_NZ goto noevents;
    if(!bit_test(wram->wPlayerStepFlags, PLAYERSTEP_STOP_F)
    ||  bit_test(wram->wPlayerStepFlags, PLAYERSTEP_MIDAIR_F)) {
    // noevents:
        // LD_A(MAPEVENTS_OFF);
        // LD_addr_A(wMapEventStatus);
        wram->wMapEventStatus = MAPEVENTS_OFF;
        // RET;
        return;
    }
    // CALL(aEnableEvents);
    EnableEvents();
// events:
    // LD_A(MAPEVENTS_ON);
    // LD_addr_A(wMapEventStatus);
    wram->wMapEventStatus = MAPEVENTS_ON;
    // RET;
    return;
}

static void v_CheckObjectEnteringVisibleRange(void){
    // LD_HL(wPlayerStepFlags);
    // BIT_hl(PLAYERSTEP_STOP_F);
    // RET_Z ;
    if(!bit_test(wram->wPlayerStepFlags, PLAYERSTEP_STOP_F))
        return;
    // FARCALL(aCheckObjectEnteringVisibleRange);
    CheckObjectEnteringVisibleRange();
    // RET;
}

static bool PlayerEvents(void){
    // XOR_A_A;
//  If there's already a player event, don't interrupt it.
    // LD_A_addr(wScriptRunning);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wScriptRunning != 0)
        return false;

    // CALL(aDummy_CheckScriptFlags2Bit5);  // This is a waste of time
    u8_flag_s res;
    do {
        // CALL(aCheckTrainerBattle_GetPlayerEvent);
        res = CheckTrainerBattle_GetPlayerEvent();
        // IF_C goto ok;
        if(res.flag) break;

        // CALL(aCheckTileEvent);
        // IF_C goto ok;
        res = CheckTileEvent();
        if(res.flag) break;

        // CALL(aRunMemScript);
        // IF_C goto ok;
        res = RunMemScript();
        if(res.flag) break;

        // CALL(aRunSceneScript);
        // IF_C goto ok;
        res = RunSceneScript();
        if(res.flag) break;

        // CALL(aCheckTimeEvents);
        // IF_C goto ok;
        res = CheckTimeEvents();
        if(res.flag) break;

        // CALL(aOWPlayerInput);
        // IF_C goto ok;
        res = OWPlayerInput();
        if(res.flag) break;

        // XOR_A_A;
        // RET;
        return false;
    } while(0);


// ok:
    // PUSH_AF;
    // FARCALL(aEnableScriptMode);
    EnableScriptMode();
    // POP_AF;

    // LD_addr_A(wScriptRunning);
    wram->wScriptRunning = res.a;
    // CALL(aDoPlayerEvent);
    DoPlayerEvent();
    // LD_A_addr(wScriptRunning);
    // CP_A(PLAYEREVENT_CONNECTION);
    // IF_Z goto ok2;
    // CP_A(PLAYEREVENT_JOYCHANGEFACING);
    // IF_Z goto ok2;

    if(!(wram->wScriptRunning == PLAYEREVENT_CONNECTION || wram->wScriptRunning == PLAYEREVENT_JOYCHANGEFACING)) {
        // XOR_A_A;
        // LD_addr_A(wLandmarkSignTimer);
        wram->wLandmarkSignTimer = 0;
    }

// ok2:
    // SCF;
    // RET;
    return true;
}

static u8_flag_s CheckTrainerBattle_GetPlayerEvent(void){
    // NOP;
    // NOP;
    // CALL(aCheckTrainerBattle);
    // IF_NC goto nope;
    if(!CheckTrainerBattle())
        return u8_flag(0, false);

    // LD_A(PLAYEREVENT_SEENBYTRAINER);
    // SCF;
    // RET;
    return u8_flag(PLAYEREVENT_SEENBYTRAINER, true);

// nope:
    // XOR_A_A;
    // RET;
}

//  Check for warps, coord events, or wild battles.
static u8_flag_s CheckTileEvent(void){
    // CALL(aCheckWarpConnxnScriptFlag);
    // IF_Z goto connections_disabled;
    if(CheckWarpConnxnScriptFlag()) {
        // FARCALL(aCheckMovingOffEdgeOfMap);
        // IF_C goto map_connection;
        if(CheckMovingOffEdgeOfMap()) {
        // map_connection:
            // LD_A(PLAYEREVENT_CONNECTION);
            // SCF;
            // RET;
            return u8_flag(PLAYEREVENT_CONNECTION, true);
        }

        // CALL(aCheckWarpTile);
        // IF_C goto warp_tile;
        if(CheckWarpTile()) {
        // warp_tile:
            // LD_A_addr(wPlayerStandingTile);
            // CALL(aCheckPitTile);
            // IF_NZ goto not_pit;
            if(CheckPitTile(gPlayer.playerStruct.nextTile)) {
                // LD_A(PLAYEREVENT_FALL);
                // SCF;
                // RET;
                return u8_flag(PLAYEREVENT_FALL, true);
            }
            else {
            // not_pit:
                // LD_A(PLAYEREVENT_WARP);
                // SCF;
                // RET;
                return u8_flag(PLAYEREVENT_WARP, true);
            }
        }
    }

// connections_disabled:
    // CALL(aCheckCoordEventScriptFlag);
    // IF_Z goto coord_events_disabled;
    if(CheckCoordEventScriptFlag()) {
        // CALL(aCheckCurrentMapCoordEvents);
        // IF_C goto coord_event;
        const struct CoordEvent* ev = CheckCurrentMapCoordEvents();
        if(ev != NULL) {
        // coord_event:
            // LD_HL(wCurCoordEventScriptAddr);
            // LD_A_hli;
            // LD_H_hl;
            // LD_L_A;
            // CALL(aGetMapScriptsBank);
            // CALL(aCallScript);
            // RET;
            return u8_flag(CallScript(ev->script), true);
        }
    }

// coord_events_disabled:
    // CALL(aCheckStepCountScriptFlag);
    // IF_Z goto step_count_disabled;
    if(CheckStepCountScriptFlag()) {
        // CALL(aCountStep);
        // RET_C ;
        u8_flag_s res = CountStep();
        if(res.flag)
            return res;
    }

// step_count_disabled:
    // CALL(aCheckWildEncountersScriptFlag);
    // IF_Z goto ok;
    if(CheckWildEncountersScriptFlag()) {
        // CALL(aRandomEncounter);
        // RET_C ;
        u8_flag_s res = RandomEncounter();
        if(res.flag)
            return res;
        // goto ok;  // pointless
    }

// ok:
    // XOR_A_A;
    // RET;
    return u8_flag(0, false);
}

static bool CheckWildEncounterCooldown(void){
    // LD_HL(wWildEncounterCooldown);
    // LD_A_hl;
    // AND_A_A;
    // RET_Z ;
    if(wram->wWildEncounterCooldown == 0)
        return false;
    // DEC_hl;
    // RET_Z ;
    if(--wram->wWildEncounterCooldown == 0)
        return false;
    // SCF;
    // RET;
    return true;
}

static void SetUpFiveStepWildEncounterCooldown(void){
    // LD_A(5);
    // LD_addr_A(wWildEncounterCooldown);
    wram->wWildEncounterCooldown = 5;
    // RET;
}

void SetMinTwoStepWildEncounterCooldown(void){
//  dummied out
    RET;
    LD_A_addr(wWildEncounterCooldown);
    CP_A(2);
    RET_NC ;
    LD_A(2);
    LD_addr_A(wWildEncounterCooldown);
    RET;

}

void Dummy_CheckScriptFlags2Bit5(void){
    CALL(aCheckBit5_ScriptFlags2);
    RET_Z ;
    CALL(aSetXYCompareFlags);
    RET;

}

static u8_flag_s RunSceneScript(void){
    // LD_A_addr(wCurMapSceneScriptCount);
    // AND_A_A;
    // IF_Z goto nope;
    if(gCurMapSceneScriptCount == 0)
        return u8_flag(0, false);

    // LD_C_A;
    // CALL(aCheckScenes);
    // CP_A_C;
    // IF_NC goto nope;
    uint8_t c = CheckScenes();
    if(c == 0xff || c >= gCurMapSceneScriptCount)
        return u8_flag(0, false);

    // LD_E_A;
    // LD_D(0);
    // LD_HL(wCurMapSceneScriptsPointer);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // for(int rept = 0; rept < SCENE_SCRIPT_SIZE; rept++){
    // ADD_HL_DE;
    // }
    Script_fn_t script = gCurMapSceneScriptsPointer[c];

    // CALL(aGetMapScriptsBank);
    // CALL(aGetFarWord);
    // CALL(aGetMapScriptsBank);
    // CALL(aCallScript);
    CallScript(script);

    // LD_HL(wScriptFlags);
    // RES_hl(3);
    bit_reset(wram->wScriptFlags, 3);

    // FARCALL(aEnableScriptMode);
    EnableScriptMode();
    // FARCALL(aScriptEvents);
    ScriptEvents();

    // LD_HL(wScriptFlags);
    // BIT_hl(3);
    // IF_Z goto nope;
    if(!bit_test(wram->wScriptFlags, 3))
        return u8_flag(0, false);

    // LD_HL(wDeferredScriptAddr);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_A_addr(wDeferredScriptBank);
    // CALL(aCallScript);
    uint8_t a = CallScript(gDeferredScriptAddr);
    // SCF;
    // RET;
    return u8_flag(a, true);

// nope:
    // XOR_A_A;
    // RET;
}

static u8_flag_s CheckTimeEvents(void){
    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // IF_NZ goto nothing;
    if(wram->wLinkMode)
        return u8_flag(0, false);

    // LD_HL(wStatusFlags2);
    // BIT_hl(STATUSFLAGS2_BUG_CONTEST_TIMER_F);
    // IF_Z goto do_daily;
    if(!bit_test(gPlayer.statusFlags2, STATUSFLAGS2_BUG_CONTEST_TIMER_F)) {
    // do_daily:
        // FARCALL(aCheckDailyResetTimer);
        CheckDailyResetTimer();
        // FARCALL(aCheckPokerusTick);
        CheckPokerusTick();
        // FARCALL(aCheckPhoneCall);
        // RET_C ;
        u8_flag_s res = CheckPhoneCall();
        if(res.flag)
            return res;
        return u8_flag(0, false);
    }

    // FARCALL(aCheckBugContestTimer);
    // IF_C goto end_bug_contest;
    if(CheckBugContestTimer()) {
    // end_bug_contest:
        // LD_A(BANK(aBugCatchingContestOverScript));
        // LD_HL(mBugCatchingContestOverScript);
        // CALL(aCallScript);
        // SCF;
        // RET;
        return u8_flag(CallScript(BugCatchingContestOverScript), true);
    }
    // XOR_A_A;
    // RET;
    return u8_flag(0, false);

// unused:
//   //  unreferenced
    // LD_A(0x8);  // ???
    // SCF;
    // RET;
}

static u8_flag_s OWPlayerInput(void){
    // CALL(aPlayerMovement);
    // RET_C ;
    u8_flag_s res = PlayerMovement();
    if(res.flag)
        return res;
    // AND_A_A;
    // IF_NZ goto NoAction;
    if(res.a != 0)
        return u8_flag(0, false);

//  Can't perform button actions while sliding on ice.
    // FARCALL(aCheckStandingOnIce);
    // IF_C goto NoAction;
    if(CheckStandingOnIce())
        return u8_flag(0, false);

    do {
        // CALL(aCheckAPressOW);
        // IF_C goto Action;
        res = CheckAPressOW();
        if(res.flag) break;

        // CALL(aCheckMenuOW);
        // IF_C goto Action;
        res = CheckMenuOW();
        if(res.flag) break;

    // NoAction:
        // XOR_A_A;
        // RET;
        return u8_flag(0, false);
    } while(0);

// Action:
    // PUSH_AF;
    // FARCALL(aStopPlayerForEvent);
    StopPlayerForEvent();
    // POP_AF;
    // SCF;
    // RET;
    return res;
}

static u8_flag_s CheckAPressOW(void){
    // LDH_A_addr(hJoyPressed);
    // AND_A(A_BUTTON);
    // RET_Z ;
    if(!(hram.hJoyPressed & (A_BUTTON)))
        return u8_flag(0, false);
    
    u8_flag_s res;
    // CALL(aTryObjectEvent);
    // RET_C ;
    res = TryObjectEvent();
    if(res.flag) return res;
    // CALL(aTryBGEvent);
    // RET_C ;
    res = TryBGEvent();
    if(res.flag) return res;
    // CALL(aTryTileCollisionEvent);
    // RET_C ;
    res = TryTileCollisionEvent();
    if(res.flag) return res;
    // XOR_A_A;
    // RET;
    return u8_flag(0, false);
}

static void PlayTalkObject(void){
    // PUSH_DE;
    // LD_DE(SFX_READ_TEXT_2);
    // CALL(aPlaySFX);
    // POP_DE;
    // RET;
    PlaySFX(SFX_READ_TEXT_2);
}

static u8_flag_s ObjectEventTypeArray_script(struct MapObject* bc) {
    PEEK("");
    printf("script=$%04x\n", bc->objectScript);
    // LD_HL(MAPOBJECT_SCRIPT_POINTER);
    // ADD_HL_BC;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // CALL(aGetMapScriptsBank);
    if(bc->objectScript <= NUM_OBJECTS) {
        Script_fn_t hl = gCurMapObjectEventsPointer[bc->objectScript].script;
        // CALL(aCallScript);
        // RET;
        return u8_flag(CallScript(hl), true);
    }
    else {
        printf("script_gb=$%08x\n", (GetMapScriptsBank() << 14) | (bc->objectScript & 0x3fff));
        if(!redirectFunc[(GetMapScriptsBank() << 14) | (bc->objectScript & 0x3fff)])
            return u8_flag(CallScript(ObjectEvent), true);
        Script_fn_t script = (Script_fn_t)redirectFunc[(GetMapScriptsBank() << 14) | (bc->objectScript & 0x3fff)];
        return u8_flag(CallScript(script), true);
    }
}

static u8_flag_s ObjectEventTypeArray_itemball(struct MapObject* bc) {
    (void)bc;
    // LD_HL(MAPOBJECT_SCRIPT_POINTER);
    // ADD_HL_BC;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // CALL(aGetMapScriptsBank);
    // LD_DE(wItemBallData);
    // LD_BC(wItemBallDataEnd - wItemBallData);
    // CALL(aFarCopyBytes);
    if(bc->objectScript <= NUM_OBJECTS) {
        const struct ItemBall* ball = gCurMapObjectEventsPointer[bc->objectScript].item_ball;
        wram->wItemBallItemID = ball->item;
        wram->wItemBallQuantity = ball->quantity;
    }
    else {
        if(redirectFunc[(GetMapScriptsBank() << 14) | (bc->objectScript & 0x3fff)]) {
            const struct ItemBall* ball = (const struct ItemBall*)redirectFunc[(GetMapScriptsBank() << 14) | (bc->objectScript & 0x3fff)];
            wram->wItemBallItemID = ball->item;
            wram->wItemBallQuantity = ball->quantity;
        }
        else {
            FarCopyBytes(wItemBallData, GetMapScriptsBank(), bc->objectScript, wItemBallDataEnd - wItemBallData);
        }
    }
    // LD_A(PLAYEREVENT_ITEMBALL);
    // SCF;
    // RET;
    return u8_flag(PLAYEREVENT_ITEMBALL, true);
}

static u8_flag_s ObjectEventTypeArray_trainer(struct MapObject* bc) {
    (void)bc;
    // CALL(aTalkToTrainer);
    TalkToTrainer();
    // LD_A(PLAYEREVENT_TALKTOTRAINER);
    // SCF;
    // RET;
    return u8_flag(PLAYEREVENT_TALKTOTRAINER, true);
}

static u8_flag_s ObjectEventTypeArray_dummy(struct MapObject* bc) {
    (void)bc;
    // XOR_A_A;
    // RET;
    return u8_flag(0, false);


// four:
    // XOR_A_A;
    // RET;


// five:
    // XOR_A_A;
    // RET;


// six:
    // XOR_A_A;
    // RET;
}

struct ObjectEventTypeFunc {
    uint8_t type;
    u8_flag_s (*function)(struct MapObject*);
};

const struct ObjectEventTypeFunc ObjectEventTypeArray[] = {
    //table_width ['3', 'ObjectEventTypeArray']
    {OBJECTTYPE_SCRIPT, ObjectEventTypeArray_script},
    {OBJECTTYPE_ITEMBALL, ObjectEventTypeArray_itemball},
    {OBJECTTYPE_TRAINER, ObjectEventTypeArray_trainer},
// the remaining four are dummy events
    {OBJECTTYPE_3, ObjectEventTypeArray_dummy},
    {OBJECTTYPE_4, ObjectEventTypeArray_dummy},
    {OBJECTTYPE_5, ObjectEventTypeArray_dummy},
    {OBJECTTYPE_6, ObjectEventTypeArray_dummy},
    //db ['-1'];  // end
};

static_assert(lengthof(ObjectEventTypeArray) == NUM_OBJECT_TYPES, "");

static u8_flag_s TryObjectEvent(void){
    // FARCALL(aCheckFacingObject);
    struct Object* bc = CheckFacingObject();
    // IF_C goto IsObject;
    if(bc == NULL)
        // XOR_A_A;
        // RET;
        return u8_flag(0, false);

// IsObject:
    // CALL(aPlayTalkObject);
    PlayTalkObject();
    // LDH_A_addr(hObjectStructIndex);
    // CALL(aGetObjectStruct);
    // LD_HL(OBJECT_MAP_OBJECT_INDEX);
    // ADD_HL_BC;
    // LD_A_hl;
    // LDH_addr_A(hLastTalked);
    hram.hLastTalked = bc->mapObjectIndex;

    // LDH_A_addr(hLastTalked);
    // CALL(aGetMapObject);
    struct MapObject* mobj = GetMapObject(hram.hLastTalked);
    // LD_HL(MAPOBJECT_COLOR);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A(0b00001111);
    uint8_t type = (mobj->objectColor & 0b00001111);

//  Bug: If IsInArray returns nc, data at bc will be executed as code.
    // PUSH_BC;
    // LD_DE(3);
    // LD_HL(mObjectEventTypeArray);
    // CALL(aIsInArray);
    uint8_t i = 0;
    for(; i < lengthof(ObjectEventTypeArray); ++i) {
        if(ObjectEventTypeArray[i].type == type) {
            // POP_BC;

            // INC_HL;
            // LD_A_hli;
            // LD_H_hl;
            // LD_L_A;
            // JP_hl;
            return ObjectEventTypeArray[i].function(mobj);
        }
    }
    // IF_NC goto nope;
    // POP_BC;

    // INC_HL;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // JP_hl;

nope:
// pop bc
    // XOR_A_A;
    // RET;
    return u8_flag(0, false);
}

static u8_flag_s TryBGEvent(void){
    // CALL(aCheckFacingBGEvent);
    // IF_C goto is_bg_event;
    if(CheckFacingBGEvent()) {
    // is_bg_event:
        // LD_A_addr(wCurBGEventType);
        // LD_HL(mBGEventJumptable);
        // RST(aJumpTable);
        // RET;
        return BGEventJumptable(gCurBGEvent.function);
    }
    // XOR_A_A;
    // RET;
    return u8_flag(0, false);
}

u8_flag_s BGEventJumptable(uint8_t a){
    //table_width ['2', 'BGEventJumptable']
    //dw ['.read'];
    //dw ['.up'];
    //dw ['.down'];
    //dw ['.right'];
    //dw ['.left'];
    //dw ['.ifset'];
    //dw ['.ifnotset'];
    //dw ['.itemifset'];
    //dw ['.copy'];
    //assert_table_length ['NUM_BGEVENTS']
    uint8_t b;
    switch(a) {
        case BGEVENT_UP: 
        // up:
            // LD_B(OW_UP);
            b = OW_UP;
            goto checkdir;
        case BGEVENT_DOWN:
        // down:
            // LD_B(OW_DOWN);
            b = OW_DOWN;
            goto checkdir;
        case BGEVENT_RIGHT:
        // right:
            // LD_B(OW_RIGHT);
            b = OW_RIGHT;
            goto checkdir;
        case BGEVENT_LEFT:
        // left:
            // LD_B(OW_LEFT);
            b = OW_LEFT;
            // goto checkdir;
        checkdir:
            // LD_A_addr(wPlayerDirection);
            // AND_A(0b1100);
            // CP_A_B;
            // JP_NZ (mBGEventJumptable_dontread);
            if((gPlayer.playerStruct.facing & 0b1100) != b)
                return u8_flag(0, false);
            fallthrough;
        case BGEVENT_READ:
        // read:
            // CALL(aPlayTalkObject);
            PlayTalkObject();
            // LD_HL(wCurBGEventScriptAddr);
            // LD_A_hli;
            // LD_H_hl;
            // LD_L_A;
            // CALL(aGetMapScriptsBank);
            // CALL(aCallScript);
            b = CallScript(gCurBGEvent.script);
            // SCF;
            // RET;
            return u8_flag(b, true);
        case BGEVENT_ITEM:
        // itemifset:
            // CALL(aCheckBGEventFlag);
            // JP_NZ (mBGEventJumptable_dontread);
            if(CheckBGEventFlag())
                return u8_flag(0, false);
            // CALL(aPlayTalkObject);
            PlayTalkObject();
            // CALL(aGetMapScriptsBank);
            // LD_DE(wHiddenItemData);
            // LD_BC(wHiddenItemDataEnd - wHiddenItemData);
            // CALL(aFarCopyBytes);
            wram->wHiddenItemID = gCurBGEvent.hiddenItem->item;
            wram->wHiddenItemEvent = gCurBGEvent.hiddenItem->eventFlag;
            // LD_A(BANK(aHiddenItemScript));
            // LD_HL(mHiddenItemScript);
            // CALL(aCallScript);
            b = CallScript(HiddenItemScript);
            // SCF;
            // RET;
            return u8_flag(b, true);
        case BGEVENT_COPY:
        // copy:
            // CALL(aCheckBGEventFlag);
            // IF_NZ goto dontread;
            if(CheckBGEventFlag())
                return u8_flag(0, false);
            // CALL(aGetMapScriptsBank);
            // LD_DE(wHiddenItemData);
            // LD_BC(wHiddenItemDataEnd - wHiddenItemData);
            // CALL(aFarCopyBytes);
            wram->wHiddenItemID = gCurBGEvent.hiddenItem->item;
            wram->wHiddenItemEvent = gCurBGEvent.hiddenItem->eventFlag;
            // goto dontread;
            return u8_flag(0, false);
        case BGEVENT_IFSET:
        // ifset:
            // CALL(aCheckBGEventFlag);
            // IF_Z goto dontread;
            if(!CheckBGEventFlag())
                return u8_flag(0, false);
            goto thenread;
        case BGEVENT_IFNOTSET:
        // ifnotset:
            // CALL(aCheckBGEventFlag);
            // IF_NZ goto dontread;
            if(!CheckBGEventFlag())
                return u8_flag(0, false);
        thenread:
            // PUSH_HL;
            // CALL(aPlayTalkObject);
            PlayTalkObject();
            // POP_HL;
            // INC_HL;
            // INC_HL;
            // CALL(aGetMapScriptsBank);
            // CALL(aGetFarWord);
            // CALL(aGetMapScriptsBank);
            // CALL(aCallScript);
            b = CallScript(gCurBGEvent.condEvent->script);
            // SCF;
            // RET;
            return u8_flag(b, true);
        default:
            return u8_flag(0, false);
    }
}

static bool CheckBGEventFlag(void){
    // LD_HL(wCurBGEventScriptAddr);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // PUSH_HL;
    // CALL(aGetMapScriptsBank);
    // CALL(aGetFarWord);

    // LD_E_L;
    // LD_D_H;
    // LD_B(CHECK_FLAG);
    // CALL(aEventFlagAction);
    uint8_t a = EventFlagAction(gCurBGEvent.condEvent->eventFlag, CHECK_FLAG);
    // LD_A_C;
    // AND_A_A;
    // POP_HL;
    // RET;
    return a;
}

static u8_flag_s PlayerMovement(void){
    // FARCALL(aDoPlayerMovement);
    // LD_A_C;
    uint8_t a = DoPlayerMovement();
    // LD_HL(mPlayerMovementPointers);
    // RST(aJumpTable);
    switch(a) {
    //  entries correspond to PLAYERMOVEMENT_* constants
        //table_width ['2', 'PlayerMovementPointers']
        //dw ['.normal'];
        //dw ['.warp'];
        //dw ['.turn'];
        //dw ['.force_turn'];
        //dw ['.finish'];
        //dw ['.continue'];
        //dw ['.exit_water'];
        //dw ['.jump'];
        //assert_table_length ['NUM_PLAYER_MOVEMENTS']

    case PLAYERMOVEMENT_NORMAL:
    // normal:
    case PLAYERMOVEMENT_FINISH:
    // finish:
        // XOR_A_A;
        // LD_C_A;
        // RET;
        return u8_flag(0, false);

    case PLAYERMOVEMENT_JUMP:
    // jump:
        // CALL(aSetMinTwoStepWildEncounterCooldown);
        // XOR_A_A;
        // LD_C_A;
        // RET;
        return u8_flag(0, false);

    case PLAYERMOVEMENT_WARP:
    // warp:
        // LD_A(PLAYEREVENT_WARP);
        // LD_C_A;
        // SCF;
        // RET;
        return u8_flag(PLAYEREVENT_WARP, true);

    case PLAYERMOVEMENT_TURN:
    // turn:
        // LD_A(PLAYEREVENT_JOYCHANGEFACING);
        // LD_C_A;
        // SCF;
        // RET;
        return u8_flag(PLAYEREVENT_JOYCHANGEFACING, true);

    case PLAYERMOVEMENT_FORCE_TURN:
    // force_turn:
    //  force the player to move in some direction
        // LD_A(BANK(aScript_ForcedMovement));
        // LD_HL(mScript_ForcedMovement);
        // CALL(aCallScript);
        // LD_C_A;
        // SCF;
        // RET;
        return u8_flag(CallScript(Script_ForcedMovement), true);

    case PLAYERMOVEMENT_CONTINUE:
    // continue_:
    case PLAYERMOVEMENT_EXIT_WATER:
    // exit_water:
        // LD_A(-1);
        // LD_C_A;
        // AND_A_A;
        // RET;
        return u8_flag(0xff, false);
    }
    // LD_A_C;
    // RET;
    return u8_flag(0, false);
}

void PlayerMovementPointers(void){
//  entries correspond to PLAYERMOVEMENT_* constants
    //table_width ['2', 'PlayerMovementPointers']
    //dw ['.normal'];
    //dw ['.warp'];
    //dw ['.turn'];
    //dw ['.force_turn'];
    //dw ['.finish'];
    //dw ['.continue'];
    //dw ['.exit_water'];
    //dw ['.jump'];
    //assert_table_length ['NUM_PLAYER_MOVEMENTS']


normal:

finish:
    XOR_A_A;
    LD_C_A;
    RET;


jump:
    CALL(aSetMinTwoStepWildEncounterCooldown);
    XOR_A_A;
    LD_C_A;
    RET;


warp:
    LD_A(PLAYEREVENT_WARP);
    LD_C_A;
    SCF;
    RET;


turn:
    LD_A(PLAYEREVENT_JOYCHANGEFACING);
    LD_C_A;
    SCF;
    RET;


force_turn:
//  force the player to move in some direction
    LD_A(BANK(aScript_ForcedMovement));
    LD_HL(mScript_ForcedMovement);
    CALL(aCallScript);
    LD_C_A;
    SCF;
    RET;


continue_:

exit_water:
    LD_A(-1);
    LD_C_A;
    AND_A_A;
    RET;

}

static u8_flag_s CheckMenuOW(void){
    // XOR_A_A;
    // LDH_addr_A(hMenuReturn);
    hram.hMenuReturn = 0;
    // LDH_addr_A(hUnusedByte);
    hram.hUnusedByte = 0;
    // LDH_A_addr(hJoyPressed);
    uint8_t a = hram.hJoyPressed;

#if DEBUG
    if(bit_test(a, SELECT_F) && bit_test(hram.hJoyDown, B_BUTTON_F)) {
        return u8_flag(CallScript(DebugFieldMenuScript), true);
    }
#endif
    // BIT_A(SELECT_F);
    // IF_NZ goto Select;
    if(bit_test(a, SELECT_F)) {
    // Select:
        // CALL(aPlayTalkObject);
        PlayTalkObject();
        // LD_A(BANK(aSelectMenuScript));
        // LD_HL(mSelectMenuScript);
        // CALL(aCallScript);
        // SCF;
        // RET;
        return u8_flag(CallScript(SelectMenuScript), true);
    }

    // BIT_A(START_F);
    // IF_Z goto NoMenu;
    if(bit_test(a, START_F)) {
        // LD_A(BANK(aStartMenuScript));
        // LD_HL(mStartMenuScript);
        // CALL(aCallScript);
        // SCF;
        // RET;
        return u8_flag(CallScript(StartMenuScript), true);
    }

// NoMenu:
    // XOR_A_A;
    // RET;
    return u8_flag(0, false);
}

#if DEBUG
static bool DebugFieldMenuScript(script_s* s){
    SCRIPT_BEGIN
    DebugFieldMenu();
    sjump(SelectMenuCallback)
    SCRIPT_END
}
#endif

static bool StartMenuScript(script_s* s){
    SCRIPT_BEGIN
    StartMenu();
    //sjump ['StartMenuCallback']
    sjump(StartMenuCallback)
    SCRIPT_END
}

static bool SelectMenuScript(script_s* s){
    SCRIPT_BEGIN
    SelectMenu();
    sjump(SelectMenuCallback)
    SCRIPT_END
}

static bool StartMenuCallback(script_s* s){
    SCRIPT_BEGIN
    SCRIPT_FALLTHROUGH(SelectMenuCallback)
}

static bool SelectMenuCallback(script_s* s){
    SCRIPT_BEGIN
    readmem(&hram.hMenuReturn)
    ifequal(HMENURETURN_SCRIPT, Script)
    ifequal(HMENURETURN_ASM, Asm)
    s_end

Script:
    sjump(gQueuedScriptAddr)

Asm:
    //memcallasm ['wQueuedScriptBank']
    gQueuedFuncAddr();
    s_end
    SCRIPT_END
}

static u8_flag_s CountStep(void){
// Don't count steps in link communication rooms.
    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // IF_NZ goto done;
    if(wram->wLinkMode != LINK_NULL)
        goto done;

// If there is a special phone call, don't count the step.
    // FARCALL(aCheckSpecialPhoneCall);
    // IF_C goto doscript;
    if(CheckSpecialPhoneCall())
        goto doscript;

// If Repel wore off, don't count the step.
    // CALL(aDoRepelStep);
    // IF_C goto doscript;
    if(DoRepelStep())
        goto doscript;

// Count the step for poison and total steps
    // LD_HL(wPoisonStepCount);
    // INC_hl;
    gPlayer.poisonStepCount++;
    // LD_HL(wStepCount);
    // INC_hl;
    uint8_t step = ++gPlayer.stepCount;
// Every 256 steps, increase the happiness of all your Pokemon.
    // IF_NZ goto skip_happiness;

    if(step == 0) {
        // FARCALL(aStepHappiness);
        StepHappiness();
    }


// skip_happiness:
// Every 256 steps, offset from the happiness incrementor by 128 steps,
// decrease the hatch counter of all your eggs until you reach the first
// one that is ready to hatch.
    // LD_A_addr(wStepCount);
    // CP_A(0x80);
    // IF_NZ goto skip_egg;
    if(gPlayer.stepCount == 0x80) {
        // FARCALL(aDoEggStep);
        // IF_NZ goto hatch;
        if(DoEggStep()) {
        // hatch:
            // LD_A(PLAYEREVENT_HATCH);
            // SCF;
            // RET;
            return u8_flag(PLAYEREVENT_HATCH, true);
        }
    }

// skip_egg:
// Increase the EXP of (both) DayCare Pokemon by 1.
    // FARCALL(aDayCareStep);
    DayCareStep();

// Every 4 steps, deal damage to all poisoned Pokemon.
    // LD_HL(wPoisonStepCount);
    // LD_A_hl;
    // CP_A(4);
    // IF_C goto skip_poison;
    if(gPlayer.poisonStepCount >= 4) {
        // LD_hl(0);
        gPlayer.poisonStepCount = 0;

        // FARCALL(aDoPoisonStep);
        // IF_C goto doscript;
        if(DoPoisonStep())
            goto doscript;
    }

// skip_poison:
    // FARCALL(aDoBikeStep);
    DoBikeStep();


done:
    // XOR_A_A;
    // RET;
    return u8_flag(0, false);


doscript:
    // LD_A(-1);
    // SCF;
    // RET;
    return u8_flag(0xff, true);


whiteout:
//   //  unreferenced
    // LD_A(PLAYEREVENT_WHITEOUT);
    // SCF;
    // RET;
    return u8_flag(PLAYEREVENT_WHITEOUT, true);
}

static bool DoRepelStep(void){
    // LD_A_addr(wRepelEffect);
    // AND_A_A;
    // RET_Z ;
    if(gPlayer.repelEffect == 0)
        return false;

    // DEC_A;
    // LD_addr_A(wRepelEffect);
    // RET_NZ ;
    if(--gPlayer.repelEffect != 0)
        return false;

    // LD_A(BANK(aRepelWoreOffScript));
    // LD_HL(mRepelWoreOffScript);
    // CALL(aCallScript);
    CallScript(RepelWoreOffScript);
    // SCF;
    // RET;
    return true;
}

static void DoPlayerEvent(void){
    // LD_A_addr(wScriptRunning);
    // AND_A_A;
    // RET_Z ;
    if(!wram->wScriptRunning)
        return;

    // CP_A(PLAYEREVENT_MAPSCRIPT);  // run script
    // RET_Z ;
    if(wram->wScriptRunning == (uint8_t)PLAYEREVENT_MAPSCRIPT)
        return;

    // CP_A(NUM_PLAYER_EVENTS);
    // RET_NC ;
    if(wram->wScriptRunning >= NUM_PLAYER_EVENTS)
        return;

    // LD_C_A;
    // LD_B(0);
    // LD_HL(mPlayerEventScriptPointers);
    // ADD_HL_BC;
    // ADD_HL_BC;
    // ADD_HL_BC;
    // LD_A_hli;
    // LD_addr_A(wScriptBank);
    // LD_A_hli;
    // LD_addr_A(wScriptPos);
    // LD_A_hl;
    // LD_addr_A(wScriptPos + 1);
    Script_Goto(&gCurScript, PlayerEventScriptPointers[wram->wScriptRunning]);
    // RET;
}

const Script_fn_t PlayerEventScriptPointers[] = {
//  entries correspond to PLAYEREVENT_* constants
    //table_width ['3', 'PlayerEventScriptPointers']
    [PLAYEREVENT_NONE] = InvalidEventScript,  // PLAYEREVENT_NONE
    [PLAYEREVENT_SEENBYTRAINER] = SeenByTrainerScript,  // PLAYEREVENT_SEENBYTRAINER
    [PLAYEREVENT_TALKTOTRAINER] = TalkToTrainerScript,  // PLAYEREVENT_TALKTOTRAINER
    [PLAYEREVENT_ITEMBALL] = FindItemInBallScript,  // PLAYEREVENT_ITEMBALL
    [PLAYEREVENT_CONNECTION] = EdgeWarpScript,  // PLAYEREVENT_CONNECTION
    [PLAYEREVENT_WARP] = WarpToNewMapScript, // PLAYEREVENT_WARP
    [PLAYEREVENT_FALL] = FallIntoMapScript,  // PLAYEREVENT_FALL
    [PLAYEREVENT_WHITEOUT] = OverworldWhiteoutScript,  // PLAYEREVENT_WHITEOUT
    [PLAYEREVENT_HATCH] = HatchEggScript,  // PLAYEREVENT_HATCH
    [PLAYEREVENT_JOYCHANGEFACING] = ChangeDirectionScript,  // PLAYEREVENT_JOYCHANGEFACING
    [NUM_PLAYER_EVENTS] = InvalidEventScript,  // (NUM_PLAYER_EVENTS)
};
static_assert(lengthof(PlayerEventScriptPointers) == NUM_PLAYER_EVENTS + 1, "");

static bool InvalidEventScript(script_s* s){
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}

void UnusedPlayerEventScript(void){
//  //  unreferenced
    //end ['?']
}

static bool HatchEggScript(script_s* s){
    SCRIPT_BEGIN
    OverworldHatchEgg();
    s_end
    SCRIPT_END
}

static bool WarpToNewMapScript(script_s* s){
    SCRIPT_BEGIN
    warpsound
    newloadmap(MAPSETUP_DOOR)
    s_end
    SCRIPT_END
}

static bool FallIntoMapScript(script_s* s){
    static const uint8_t SkyfallMovement[] = {
        movement_skyfall,
        movement_step_end
    };
    SCRIPT_BEGIN
    newloadmap(MAPSETUP_FALL)
    playsound(SFX_KINESIS)
    applymovement(PLAYER, SkyfallMovement)
    playsound(SFX_STRENGTH)
    scall(LandAfterPitfallScript)
    s_end
    SCRIPT_END
}

static bool LandAfterPitfallScript(script_s* s){
    SCRIPT_BEGIN
    earthquake(16)
    s_end
    SCRIPT_END
}

static bool EdgeWarpScript(script_s* s){
    SCRIPT_BEGIN
    reloadend(MAPSETUP_CONNECTION)
    sjump(ChangeDirectionScript)
    SCRIPT_END
}

static bool ChangeDirectionScript(script_s* s){
    SCRIPT_BEGIN
    deactivatefacing(3)
    EnableWildEncounters();
    s_end
    SCRIPT_END

// INCLUDE "engine/overworld/scripting.asm"
}

void WarpToSpawnPoint(void){
    // LD_HL(wStatusFlags2);
    // RES_hl(STATUSFLAGS2_SAFARI_GAME_F);
    // RES_hl(STATUSFLAGS2_BUG_CONTEST_TIMER_F);
    // RET;
    bit_reset(gPlayer.statusFlags2, STATUSFLAGS2_SAFARI_GAME_F);
    bit_reset(gPlayer.statusFlags2, STATUSFLAGS2_BUG_CONTEST_TIMER_F);
}

static u8_flag_s RunMemScript(void){
//  If there is no script here, we don't need to be here.
    // LD_A_addr(wMapReentryScriptQueueFlag);
    // AND_A_A;
    // RET_Z ;
    if(wram->wMapReentryScriptQueueFlag == 0)
        return u8_flag(0, false);
//  Execute the script at (wMapReentryScriptBank):(wMapReentryScriptAddress).
    // LD_HL(wMapReentryScriptAddress);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_A_addr(wMapReentryScriptBank);
    // CALL(aCallScript);
    uint8_t a = CallScript(gMapReentryScriptAddress);
    // SCF;
//  Clear the buffer for the next script.
    // PUSH_AF;
    // XOR_A_A;
    // LD_HL(wMapReentryScriptQueueFlag);
    // LD_BC(8);
    // CALL(aByteFill);
    wram->wMapReentryScriptQueueFlag = 0;
    gMapReentryScriptAddress = NULL;
    // POP_AF;
    // RET;
    return u8_flag(a, true);
}

bool LoadScriptBDE(Script_fn_t de){
//  If there's already a script here, don't overwrite.
    // LD_HL(wMapReentryScriptQueueFlag);
    // LD_A_hl;
    // AND_A_A;
    // RET_NZ ;
    if(wram->wMapReentryScriptQueueFlag != 0)
        return false;
//  Set the flag
    // LD_hl(1);
    // INC_HL;
    wram->wMapReentryScriptQueueFlag = 1;
//  Load the script pointer b:de into (wMapReentryScriptBank):(wMapReentryScriptAddress)
    // LD_hl_B;
    // INC_HL;
    // LD_hl_E;
    // INC_HL;
    // LD_hl_D;
    gMapReentryScriptAddress = de;
    // SCF;
    // RET;
    return true;
}

static u8_flag_s TryTileCollisionEvent(void){
    // CALL(aGetFacingTileCoord);
    struct CoordsTileId cid = GetFacingTileCoord();
    // LD_addr_A(wFacingTileID);
    wram->wFacingTileID = cid.tileId;
    // LD_C_A;
    // FARCALL(aCheckFacingTileForStdScript);
    // IF_C goto done;
    if(!CheckFacingTileForStdScript(cid.tileId)) {
        // CALL(aCheckCutTreeTile);
        // IF_NZ goto whirlpool;
        if(CheckCutTreeTile(cid.tileId)) {
            // FARCALL(aTryCutOW);
            // goto done;
            TryCutOW();
        }


    // whirlpool:
        // LD_A_addr(wFacingTileID);
        // CALL(aCheckWhirlpoolTile);
        // IF_NZ goto waterfall;
        else if(CheckWhirlpoolTile(cid.tileId)) {
            // FARCALL(aTryWhirlpoolOW);
            TryWhirlpoolOW();
            // goto done;
        }

    // waterfall:
        // LD_A_addr(wFacingTileID);
        // CALL(aCheckWaterfallTile);
        // IF_NZ goto headbutt;
        else if(CheckWaterfallTile(cid.tileId)) {
            // FARCALL(aTryWaterfallOW);
            TryWaterfallOW();
            // goto done;
        }

    // headbutt:
        // LD_A_addr(wFacingTileID);
        // CALL(aCheckHeadbuttTreeTile);
        // IF_NZ goto surf;
        else if(CheckHeadbuttTreeTile(cid.tileId)) {
            // FARCALL(aTryHeadbuttOW);
            // IF_C goto done;
            // goto noevent;
            if(!TryHeadbuttOW())
                return u8_flag(0, false);
        }

    // surf:
        // FARCALL(aTrySurfOW);
        // IF_NC goto noevent;
        // goto done;
        else if(TrySurfOW()) {

        }

        else {
        // noevent:
            // XOR_A_A;
            // RET;
            return u8_flag(0, false);
        }
    }

// done:
    // CALL(aPlayClickSFX);
    PlayClickSFX();
    // LD_A(0xff);
    // SCF;
    // RET;
    return u8_flag(0xff, true);
}

//  Random encounter
static u8_flag_s RandomEncounter(void){
    // CALL(aCheckWildEncounterCooldown);
    // IF_C goto nope;
    if(CheckWildEncounterCooldown())
        return u8_flag(1, false);
    // CALL(aCanUseSweetScent);
    // IF_NC goto nope;
    if(!CanUseSweetScent())
        return u8_flag(1, false);
    // LD_HL(wStatusFlags2);
    // BIT_hl(STATUSFLAGS2_BUG_CONTEST_TIMER_F);
    // IF_NZ goto bug_contest;
    if(bit_test(gPlayer.statusFlags2, STATUSFLAGS2_BUG_CONTEST_TIMER_F)) {
    // bug_contest:
        // CALL(av_TryWildEncounter_BugContest);
        // IF_NC goto nope;
        if(!v_TryWildEncounter_BugContest())
            return u8_flag(1, false);
        // goto ok_bug_contest;
    // ok_bug_contest:
        // LD_A(BANK(aBugCatchingContestBattleScript));
        // LD_HL(mBugCatchingContestBattleScript);
        // goto done;
        return u8_flag(CallScript(BugCatchingContestBattleScript), true);
    }
    // FARCALL(aTryWildEncounter);
    // IF_NZ goto nope;
    if(!TryWildEncounter())
        return u8_flag(1, false);
    // goto ok;


// nope:
    // LD_A(1);
    // AND_A_A;
    // RET;

// ok:
    // LD_A(BANK(aWildBattleScript));
    // LD_HL(mWildBattleScript);
    // goto done;


// done:
    // CALL(aCallScript);
    // SCF;
    // RET;
    return u8_flag(CallScript(WildBattleScript), true);
}

static bool WildBattleScript(script_s* s){
    SCRIPT_BEGIN
    randomwildmon
    startbattle
    reloadmapafterbattle
    s_end
    SCRIPT_END
}

bool CanUseSweetScent(void){
    // LD_HL(wStatusFlags);
    // BIT_hl(STATUSFLAGS_NO_WILD_ENCOUNTERS_F);
    // IF_NZ goto no;
    if(bit_test(gPlayer.statusFlags, STATUSFLAGS_NO_WILD_ENCOUNTERS_F))
        return false;
    // LD_A_addr(wEnvironment);
    uint8_t a = wram->wEnvironment;
    // CP_A(CAVE);
    // IF_Z goto ice_check;
    // CP_A(DUNGEON);
    // IF_Z goto ice_check;
    // FARCALL(aCheckGrassCollision);
    // IF_NC goto no;
    if(a != CAVE && a != DUNGEON && !CheckGrassCollision())
        return false;

// ice_check:
    // LD_A_addr(wPlayerStandingTile);
    // CALL(aCheckIceTile);
    // IF_Z goto no;
    if(CheckIceTile(gPlayer.playerStruct.nextTile))
        return false;
    // SCF;
    // RET;
    return true;

// no:
    // AND_A_A;
    // RET;
}

static bool v_TryWildEncounter_BugContest(void){
    // CALL(aTryWildEncounter_BugContest);
    // RET_NC ;
    if(!TryWildEncounter_BugContest())
        return false;
    // CALL(aChooseWildEncounter_BugContest);
    ChooseWildEncounter_BugContest();
    // FARCALL(aCheckRepelEffect);
    return !CheckRepelEffect();
    // RET;
}

//  Pick a random mon out of ContestMons.
void ChooseWildEncounter_BugContest(void){
    uint8_t a;
    do {
    // loop:
        // CALL(aRandom);
        a = Random();
        // CP_A(100 << 1);
        // IF_NC goto loop;
    } while(a >= 100 << 1);
    // SRL_A;
    a >>= 1;

    // LD_HL(mContestMons);
    const struct ContestMon* hl = ContestMons;
    // LD_DE(4);

    while(a >= hl->pct) {
    // CheckMon:
        // SUB_A_hl;
        // IF_C goto GotMon;
        a -= hl->pct;
        // ADD_HL_DE;
        hl++;
        // goto CheckMon;
    }


// GotMon:
    // INC_HL;

//  Species
    // LD_A_hli;
    // LD_addr_A(wTempWildMonSpecies);
    wram->wTempWildMonSpecies = hl->species;

//  Min level
    // LD_A_hli;
    // LD_D_A;
    uint8_t d = hl->min;

//  Max level
    // LD_A_hl;

    // SUB_A_D;
    a = hl->max - d;
    // IF_NZ goto RandomLevel;

//  If min and max are the same.
    if(a == 0) {
        // LD_A_D;
        a = d;
        // goto GotLevel;
    }
    else {
    // RandomLevel:
    //  Get a random level between the min and max.
        // LD_C_A;
        // INC_C;
        // CALL(aRandom);
        Random();
        // LDH_A_addr(hRandomAdd);
        // CALL(aSimpleDivide);
        // ADD_A_D;
        a = (hram.hRandomAdd % a + 1) + d;
    }

// GotLevel:
    // LD_addr_A(wCurPartyLevel);
    wram->wCurPartyLevel = a;

    // XOR_A_A;
    // RET;
}

bool TryWildEncounter_BugContest(void){
    // LD_A_addr(wPlayerStandingTile);
    // CALL(aCheckSuperTallGrassTile);
    // LD_B(40 percent);
    // IF_Z goto ok;
    // LD_B(20 percent);
    uint8_t b = (CheckSuperTallGrassTile(gPlayer.playerStruct.nextTile))
        ? 40 percent
        : 20 percent;

// ok:
    // FARCALL(aApplyMusicEffectOnEncounterRate);
    b = ApplyMusicEffectOnEncounterRate(b);
    // FARCALL(aApplyCleanseTagEffectOnEncounterRate);
    b = ApplyCleanseTagEffectOnEncounterRate(b);
    // CALL(aRandom);
    Random();
    // LDH_A_addr(hRandomAdd);
    // CP_A_B;
    // RET_C ;
    if(hram.hRandomAdd < b)
        return true;
    // LD_A(1);
    // AND_A_A;
    // RET;
    return false;
// INCLUDE "data/wild/bug_contest_mons.asm"
}

static bool DoBikeStep(void){
    // NOP;
    // NOP;
// If the bike shop owner doesn't have our number, or
// if we've already gotten the call, we don't have to
// be here.
    // LD_HL(wStatusFlags2);
    // BIT_hl(STATUSFLAGS2_BIKE_SHOP_CALL_F);
    // IF_Z goto NoCall;
    if(!bit_test(gPlayer.statusFlags2, STATUSFLAGS2_BIKE_SHOP_CALL_F))
        return false;

// If we're not on the bike, we don't have to be here.
    // LD_A_addr(wPlayerState);
    // CP_A(PLAYER_BIKE);
    // IF_NZ goto NoCall;
    if(gPlayer.playerState != PLAYER_BIKE)
        return false;

// If we're not in an area of phone service, we don't
// have to be here.
    // CALL(aGetMapPhoneService);
    // AND_A_A;
    // IF_NZ goto NoCall;
    if(GetMapPhoneService())
        return false;

// Check the bike step count and check whether we've
// taken 65536 of them yet.
    // LD_HL(wBikeStep);
    // LD_A_hli;
    // LD_D_A;
    // LD_E_hl;
    // CP_A(255);
    // IF_NZ goto increment;
    // LD_A_E;
    // CP_A(255);
    // IF_Z goto dont_increment;

    if(gPlayer.bikeStep != 0xffff) {
    // increment:
        // INC_DE;
        // LD_hl_E;
        // DEC_HL;
        // LD_hl_D;
        gPlayer.bikeStep++;
    }

// dont_increment:
// If we've taken at least 1024 steps, have the bike
//  shop owner try to call us.
    // LD_A_D;
    // CP_A(HIGH(1024));
    // IF_C goto NoCall;
    if(gPlayer.bikeStep >= 1024) {
    // If a call has already been queued, don't overwrite
    // that call.
        // LD_A_addr(wSpecialPhoneCallID);
        // AND_A_A;
        // IF_NZ goto NoCall;
        if(gPlayer.specialPhoneCallID == 0) {

        // Queue the call.
            // LD_A(SPECIALCALL_BIKESHOP);
            // LD_addr_A(wSpecialPhoneCallID);
            // XOR_A_A;
            // LD_addr_A(wSpecialPhoneCallID + 1);
            gPlayer.specialPhoneCallID = SPECIALCALL_BIKESHOP;
            // LD_HL(wStatusFlags2);
            // RES_hl(STATUSFLAGS2_BIKE_SHOP_CALL_F);
            bit_reset(gPlayer.statusFlags2, STATUSFLAGS2_BIKE_SHOP_CALL_F);
            // SCF;
            // RET;
            return true;
        }
    }

// NoCall:
    // XOR_A_A;
    // RET;
    return false;
// INCLUDE "engine/overworld/cmd_queue.asm"

}
