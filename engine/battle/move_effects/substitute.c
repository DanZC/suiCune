#include "../../../constants.h"
#include "substitute.h"
#include "../effect_commands.h"
#include "../../../home/battle_vars.h"
#include "../../../home/battle.h"
#include "../check_battle_scene.h"
#include "../../../data/text/battle.h"

void BattleCommand_Substitute(void){
//  substitute

    // CALL(aBattleCommand_MoveDelay);
    BattleCommand_MoveDelay();
    // LD_HL(wBattleMonMaxHP);
    // LD_DE(wPlayerSubstituteHP);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto got_hp;
    // LD_HL(wEnemyMonMaxHP);
    // LD_DE(wEnemySubstituteHP);
    struct BattleMon* mon = (hram->hBattleTurn == TURN_PLAYER)? &wram->wBattleMon: &wram->wEnemyMon;
    uint8_t* subHP = (hram->hBattleTurn == TURN_PLAYER)? &wram->wPlayerSubstituteHP: &wram->wEnemySubstituteHP;

// got_hp:

    // LD_A(BATTLE_VARS_SUBSTATUS4);
    // CALL(aGetBattleVar);
    // BIT_A(SUBSTATUS_SUBSTITUTE);
    // IF_NZ goto already_has_sub;
    if(bit_test(GetBattleVar(BATTLE_VARS_SUBSTATUS4), SUBSTATUS_SUBSTITUTE)) {
    // already_has_sub:
        // CALL(aCheckUserIsCharging);
        // CALL_NZ (aBattleCommand_RaiseSub);
        if(CheckUserIsCharging_Conv())
            BattleCommand_RaiseSub();
        // LD_HL(mHasSubstituteText);
        // goto jp_stdbattletextbox;
        return StdBattleTextbox(HasSubstituteText);
    }

    // LD_A_hli;
    // LD_B_hl;
    // SRL_A;
    // RR_B;
    // SRL_A;
    // RR_B;
    uint8_t b = BigEndianToNative16(mon->maxHP) >> 2;
    // DEC_HL;
    // DEC_HL;
    // LD_A_B;
    // LD_de_A;
    *subHP = b;
    // LD_A_hld;
    // SUB_A_B;
    // LD_E_A;
    // LD_A_hl;
    // SBC_A(0);
    // LD_D_A;
    // IF_C goto too_weak_to_sub;
    // LD_A_D;
    // OR_A_E;
    // IF_Z goto too_weak_to_sub;
    if(BigEndianToNative16(mon->hp) <= b) {
    // too_weak_to_sub:
        // CALL(aCheckUserIsCharging);
        // CALL_NZ (aBattleCommand_RaiseSub);
        if(CheckUserIsCharging_Conv())
            BattleCommand_RaiseSub();
        // LD_HL(mTooWeakSubText);

    // jp_stdbattletextbox:
        // JP(mStdBattleTextbox);
        return StdBattleTextbox(TooWeakSubText);
    }

    // LD_hl_D;
    // INC_HL;
    // LD_hl_E;
    mon->hp = NativeToBigEndian16(BigEndianToNative16(mon->hp) - b);

    // LD_A(BATTLE_VARS_SUBSTATUS4);
    // CALL(aGetBattleVarAddr);
    // SET_hl(SUBSTATUS_SUBSTITUTE);
    bit_set(*GetBattleVarAddr(BATTLE_VARS_SUBSTATUS4), SUBSTATUS_SUBSTITUTE);

    // LD_HL(wPlayerWrapCount);
    // LD_DE(wPlayerTrappingMove);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto player;
    // LD_HL(wEnemyWrapCount);
    // LD_DE(wEnemyTrappingMove);
    uint8_t* wrapCount = (hram->hBattleTurn == TURN_PLAYER)? &wram->wPlayerWrapCount: &wram->wEnemyWrapCount;
    move_t* trappingMove = (hram->hBattleTurn == TURN_PLAYER)? &wram->wPlayerTrappingMove: &wram->wEnemyTrappingMove;

// player:

    // XOR_A_A;
    // LD_hl_A;
    *wrapCount = 0;
    // LD_de_A;
    *trappingMove = NO_MOVE;
    // CALL(av_CheckBattleScene);
    // IF_C goto no_anim;

    if(CheckBattleScene_Conv()) {
        // XOR_A_A;
        // LD_addr_A(wNumHits);
        wram->wNumHits = 0;
        // LD_addr_A(wFXAnimID + 1);
        wram->wFXAnimID &= 0xff;
        // LD_addr_A(wBattleAnimParam);
        wram->wBattleAnimParam = 0;
        // LD_A(SUBSTITUTE);
        // CALL(aLoadAnim);
        LoadAnim_Conv(SUBSTITUTE);
        // goto finish;
    }
    else {
    // no_anim:
        // CALL(aBattleCommand_RaiseSubNoAnim);
        BattleCommand_RaiseSubNoAnim();
    }

// finish:
    // LD_HL(mMadeSubstituteText);
    // CALL(aStdBattleTextbox);
    StdBattleTextbox(MadeSubstituteText);
    // JP(mRefreshBattleHuds);
    RefreshBattleHuds();
}
