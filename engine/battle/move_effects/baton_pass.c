#include "../../../constants.h"
#include "baton_pass.h"
#include "../core.h"
#include "../effect_commands.h"
#include "../../../home/battle.h"
#include "../../../home/clear_sprites.h"
#include "../../../home/delay.h"
#include "../../../home/tilemap.h"
#include "../../../home/menu.h"
#include "../../../home/text.h"

static void BatonPass_LinkPlayerSwitch(void);
static void BatonPass_LinkEnemySwitch(void);
static void FailedBatonPass(void);
static void ResetBatonPassStatus(void);
static bool CheckAnyOtherAlivePartyMons(void);
static bool CheckAnyOtherAliveEnemyMons(void);
static bool CheckAnyOtherAliveMons(struct PartyMon* party, uint8_t count, uint8_t curMon);

void BattleCommand_BatonPass(void){
//  batonpass

    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // JP_NZ (mBattleCommand_BatonPass_Enemy);
    if(hram->hBattleTurn == TURN_PLAYER) {

    //  Need something to switch to
        // CALL(aCheckAnyOtherAlivePartyMons);
        // JP_Z (mFailedBatonPass);
        if(!CheckAnyOtherAlivePartyMons())
            return FailedBatonPass();

        // CALL(aUpdateBattleMonInParty);
        UpdateBattleMonInParty();
        // CALL(aAnimateCurrentMove);
        AnimateCurrentMove();

        // LD_C(50);
        // CALL(aDelayFrames);
        DelayFrames(50);

    //  Transition into switchmon menu
        // CALL(aLoadStandardMenuHeader);
        LoadStandardMenuHeader();
        // FARCALL(aSetUpBattlePartyMenu);
        SetUpBattlePartyMenu();

        // FARCALL(aForcePickSwitchMonInBattle);
        ForcePickSwitchMonInBattle();

    //  Return to battle scene
        // CALL(aClearPalettes);
        ClearPalettes();
        // FARCALL(av_LoadBattleFontsHPBar);
        v_LoadBattleFontsHPBar();
        // CALL(aCloseWindow);
        CloseWindow();
        // CALL(aClearSprites);
        ClearSprites();
        // hlcoord(1, 0, wTilemap);
        // LD_BC((4 << 8) | 10);
        // CALL(aClearBox);
        ClearBox(coord(1, 0, wram->wTilemap), 10, 4);
        // LD_B(SCGB_BATTLE_COLORS);
        // CALL(aGetSGBLayout);
        GetSGBLayout(SCGB_BATTLE_COLORS);
        // CALL(aSetPalettes);
        SetPalettes();
        // CALL(aBatonPass_LinkPlayerSwitch);
        BatonPass_LinkPlayerSwitch();

    //  Mobile link battles handle entrances differently
        // FARCALL(aCheckMobileBattleError);
        // JP_C (mEndMoveEffect);
        if(CheckMobileBattleError())
            return EndMoveEffect();

        // LD_HL(mPassedBattleMonEntrance);
        // CALL(aCallBattleCore);
        PassedBattleMonEntrance();

        // CALL(aResetBatonPassStatus);
        ResetBatonPassStatus();
        // RET;
        return;
    }
    else {
    // Enemy:
    //  Wildmons don't have anything to switch to
        // LD_A_addr(wBattleMode);
        // DEC_A;  // WILDMON
        // JP_Z (mFailedBatonPass);
        if(wram->wBattleMode == WILD_BATTLE)
            return FailedBatonPass();

        // CALL(aCheckAnyOtherAliveEnemyMons);
        // JP_Z (mFailedBatonPass);
        if(!CheckAnyOtherAliveEnemyMons())
            return FailedBatonPass();

        // CALL(aUpdateEnemyMonInParty);
        UpdateEnemyMonInParty();
        // CALL(aAnimateCurrentMove);
        AnimateCurrentMove();
        // CALL(aBatonPass_LinkEnemySwitch);
        BatonPass_LinkEnemySwitch();

    //  Mobile link battles handle entrances differently
        // FARCALL(aCheckMobileBattleError);
        // JP_C (mEndMoveEffect);
        if(CheckMobileBattleError())
            return EndMoveEffect();

    //  Passed enemy PartyMon entrance
        // XOR_A_A;
        // LD_addr_A(wEnemySwitchMonIndex);
        wram->wEnemySwitchMonIndex = 0;
        // LD_HL(mEnemySwitch_SetMode);
        // CALL(aCallBattleCore);
        EnemySwitch_SetMode();
        // LD_HL(mResetBattleParticipants);
        // CALL(aCallBattleCore);
        ResetBattleParticipants();
        // LD_A(TRUE);
        // LD_addr_A(wApplyStatLevelMultipliersToEnemy);
        wram->wApplyStatLevelMultipliersToEnemy = TRUE;
        // LD_HL(mApplyStatLevelMultiplierOnAllStats);
        // CALL(aCallBattleCore);
        ApplyStatLevelMultiplierOnAllStats();

        // LD_HL(mSpikesDamage);
        // CALL(aCallBattleCore);
        SpikesDamage();

        // JR(mResetBatonPassStatus);
        return ResetBatonPassStatus();
    }
}

static void BatonPass_LinkPlayerSwitch(void){
    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // RET_Z ;
    if(wram->wLinkMode == 0)
        return;

    // LD_A(BATTLEPLAYERACTION_USEITEM);
    // LD_addr_A(wBattlePlayerAction);
    wram->wBattlePlayerAction = BATTLEPLAYERACTION_USEITEM;

    // CALL(aLoadStandardMenuHeader);
    LoadStandardMenuHeader();
    // LD_HL(mLinkBattleSendReceiveAction);
    // CALL(aCallBattleCore);
    LinkBattleSendReceiveAction();
    // CALL(aCloseWindow);
    CloseWindow();

    // XOR_A_A;  // BATTLEPLAYERACTION_USEMOVE
    // LD_addr_A(wBattlePlayerAction);
    wram->wBattlePlayerAction = BATTLEPLAYERACTION_USEMOVE;
    // RET;
}

static void BatonPass_LinkEnemySwitch(void){
    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // RET_Z ;
    if(wram->wLinkMode == 0)
        return;

    // CALL(aLoadStandardMenuHeader);
    LoadStandardMenuHeader();
    // LD_HL(mLinkBattleSendReceiveAction);
    // CALL(aCallBattleCore);
    LinkBattleSendReceiveAction();

    // LD_A_addr(wOTPartyCount);
    // ADD_A(BATTLEACTION_SWITCH1);
    // LD_B_A;
    uint8_t b = wram->wOTPartyCount + BATTLEACTION_SWITCH1;
    // LD_A_addr(wBattleAction);
    // CP_A(BATTLEACTION_SWITCH1);
    // IF_C goto baton_pass;
    // CP_A_B;
    // IF_C goto switch_;
    if(wram->wBattleAction < BATTLEACTION_SWITCH1 || wram->wBattleAction >= b) {
    // baton_pass:
        // LD_A_addr(wCurOTMon);
        // ADD_A(BATTLEACTION_SWITCH1);
        // LD_addr_A(wBattleAction);
        wram->wBattleAction = wram->wCurOTMon + BATTLEACTION_SWITCH1;
    }

// switch_:
    // JP(mCloseWindow);
    return CloseWindow();
}

static void FailedBatonPass(void){
    // CALL(aAnimateFailedMove);
    // JP(mPrintButItFailed);
    AnimateFailedMove();
    return PrintButItFailed();
}

static void ResetBatonPassStatus(void){
//  Reset status changes that aren't passed by Baton Pass.

// Nightmare isn't passed.
    // LD_A(BATTLE_VARS_STATUS);
    // CALL(aGetBattleVar);
    // AND_A(SLP);
    // IF_NZ goto ok;

    if((GetBattleVar(BATTLE_VARS_STATUS) & SLP) == 0) {
        // LD_A(BATTLE_VARS_SUBSTATUS1);
        // CALL(aGetBattleVarAddr);
        // RES_hl(SUBSTATUS_NIGHTMARE);
        bit_reset(*GetBattleVarAddr(BATTLE_VARS_SUBSTATUS1), SUBSTATUS_NIGHTMARE);
    }
// ok:

// Disable isn't passed.
    // CALL(aResetActorDisable);
    ResetActorDisable();

// Attraction isn't passed.
    // LD_HL(wPlayerSubStatus1);
    // RES_hl(SUBSTATUS_IN_LOVE);
    bit_reset(wram->wPlayerSubStatus1, SUBSTATUS_IN_LOVE);
    // LD_HL(wEnemySubStatus1);
    // RES_hl(SUBSTATUS_IN_LOVE);
    bit_reset(wram->wEnemySubStatus1, SUBSTATUS_IN_LOVE);
    // LD_HL(wPlayerSubStatus5);

    // LD_A(BATTLE_VARS_SUBSTATUS5);
    // CALL(aGetBattleVarAddr);
    uint8_t* ss5 = GetBattleVarAddr(BATTLE_VARS_SUBSTATUS5);
    // RES_hl(SUBSTATUS_TRANSFORMED);
    bit_reset(*ss5, SUBSTATUS_TRANSFORMED);
    // RES_hl(SUBSTATUS_ENCORED);
    bit_reset(*ss5, SUBSTATUS_ENCORED);

// New mon hasn't used a move yet.
    // LD_A(BATTLE_VARS_LAST_MOVE);
    // CALL(aGetBattleVarAddr);
    // LD_hl(0);
    *GetBattleVarAddr(BATTLE_VARS_LAST_MOVE) = NO_MOVE;

    // XOR_A_A;
    // LD_addr_A(wPlayerWrapCount);
    wram->wPlayerWrapCount = 0;
    // LD_addr_A(wEnemyWrapCount);
    wram->wEnemyWrapCount = 0;
    // RET;

}

static bool CheckAnyOtherAlivePartyMons(void){
    // LD_HL(wPartyMon1HP);
    // LD_A_addr(wPartyCount);
    // LD_D_A;
    // LD_A_addr(wCurBattleMon);
    // LD_E_A;
    // JR(mCheckAnyOtherAliveMons);
    return CheckAnyOtherAliveMons(wram->wPartyMon, wram->wPartyCount, wram->wCurBattleMon);
}

static bool CheckAnyOtherAliveEnemyMons(void){
    // LD_HL(wOTPartyMon1HP);
    // LD_A_addr(wOTPartyCount);
    // LD_D_A;
    // LD_A_addr(wCurOTMon);
    // LD_E_A;

// fallthrough

    return CheckAnyOtherAliveMons(wram->wOTPartyMon, wram->wOTPartyCount, wram->wCurOTMon);
}

static bool CheckAnyOtherAliveMons(struct PartyMon* party, uint8_t count, uint8_t curMon){
//  Check for nonzero HP starting from partymon
//  HP at hl for d partymons, besides current mon e.

//  Return nz if any are alive.

    // XOR_A_A;
    // LD_B_A;
    uint8_t b = 0;
    // LD_C_A;
    uint8_t c = 0;

    while(c++ < count) {
    // loop:
        // LD_A_C;
        // CP_A_D;
        // IF_Z goto done;
        // CP_A_E;
        // IF_Z goto next;
        if(c == curMon)
            continue;

        // LD_A_hli;
        // OR_A_B;
        // LD_B_A;
        // LD_A_hld;
        // OR_A_B;
        // LD_B_A;
        if(party[c].HP != 0)
            b++;

    // next:
        // PUSH_BC;
        // LD_BC(PARTYMON_STRUCT_LENGTH);
        // ADD_HL_BC;
        // POP_BC;
        // INC_C;
        // goto loop;
    }


// done:
    // LD_A_B;
    // AND_A_A;
    // RET;
    return b != 0;
}
