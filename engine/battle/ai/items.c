#include "../../../constants.h"
#include "items.h"
#include "../../../home/audio.h"
#include "../../../data/text/common.h"

void AI_SwitchOrTryItem(void){
    AND_A_A;

    LD_A_addr(wBattleMode);
    DEC_A;
    RET_Z ;

    LD_A_addr(wLinkMode);
    AND_A_A;
    RET_NZ ;

    FARCALL(aCheckEnemyLockedIn);
    RET_NZ ;

    LD_A_addr(wPlayerSubStatus5);
    BIT_A(SUBSTATUS_CANT_RUN);
    JR_NZ (mDontSwitch);

    LD_A_addr(wEnemyWrapCount);
    AND_A_A;
    JR_NZ (mDontSwitch);

// always load the first trainer class in wTrainerClass for Battle Tower trainers
    LD_HL(mTrainerClassAttributes + TRNATTR_AI_ITEM_SWITCH);
    LD_A_addr(wInBattleTowerBattle);
    AND_A_A;
    IF_NZ goto ok;

    LD_A_addr(wTrainerClass);
    DEC_A;
    LD_BC(NUM_TRAINER_ATTRIBUTES);
    CALL(aAddNTimes);


ok:
    BIT_hl(SWITCH_OFTEN_F);
    JP_NZ (mSwitchOften);
    BIT_hl(SWITCH_RARELY_F);
    JP_NZ (mSwitchRarely);
    BIT_hl(SWITCH_SOMETIMES_F);
    JP_NZ (mSwitchSometimes);
// fallthrough

    return DontSwitch();
}

void DontSwitch(void){
    CALL(aAI_TryItem);
    RET;

}

void SwitchOften(void){
    CALLFAR(aCheckAbleToSwitch);
    LD_A_addr(wEnemySwitchMonParam);
    AND_A(0xf0);
    JP_Z (mDontSwitch);

    CP_A(0x10);
    IF_NZ goto not_10;
    CALL(aRandom);
    CP_A(50 percent + 1);
    IF_C goto switch_;
    JP(mDontSwitch);

not_10:

    CP_A(0x20);
    IF_NZ goto not_20;
    CALL(aRandom);
    CP_A(79 percent - 1);
    IF_C goto switch_;
    JP(mDontSwitch);

not_20:

// $30
    CALL(aRandom);
    CP_A(4 percent);
    JP_C (mDontSwitch);


switch_:
    LD_A_addr(wEnemySwitchMonParam);
    AND_A(0xf);
    INC_A;
// In register 'a' is the number (1-6) of the mon to switch to
    LD_addr_A(wEnemySwitchMonIndex);
    JP(mAI_TrySwitch);

}

void SwitchRarely(void){
    CALLFAR(aCheckAbleToSwitch);
    LD_A_addr(wEnemySwitchMonParam);
    AND_A(0xf0);
    JP_Z (mDontSwitch);

    CP_A(0x10);
    IF_NZ goto not_10;
    CALL(aRandom);
    CP_A(8 percent);
    IF_C goto switch_;
    JP(mDontSwitch);

not_10:

    CP_A(0x20);
    IF_NZ goto not_20;
    CALL(aRandom);
    CP_A(12 percent);
    IF_C goto switch_;
    JP(mDontSwitch);

not_20:

// $30
    CALL(aRandom);
    CP_A(79 percent - 1);
    JP_C (mDontSwitch);


switch_:
    LD_A_addr(wEnemySwitchMonParam);
    AND_A(0xf);
    INC_A;
    LD_addr_A(wEnemySwitchMonIndex);
    JP(mAI_TrySwitch);

}

void SwitchSometimes(void){
    CALLFAR(aCheckAbleToSwitch);
    LD_A_addr(wEnemySwitchMonParam);
    AND_A(0xf0);
    JP_Z (mDontSwitch);

    CP_A(0x10);
    IF_NZ goto not_10;
    CALL(aRandom);
    CP_A(20 percent - 1);
    IF_C goto switch_;
    JP(mDontSwitch);

not_10:

    CP_A(0x20);
    IF_NZ goto not_20;
    CALL(aRandom);
    CP_A(50 percent + 1);
    IF_C goto switch_;
    JP(mDontSwitch);

not_20:

// $30
    CALL(aRandom);
    CP_A(20 percent - 1);
    JP_C (mDontSwitch);


switch_:
    LD_A_addr(wEnemySwitchMonParam);
    AND_A(0xf);
    INC_A;
    LD_addr_A(wEnemySwitchMonIndex);
    JP(mAI_TrySwitch);

}

void CheckSubstatusCantRun(void){
//  //  unreferenced
    LD_A_addr(wEnemySubStatus5);
    BIT_A(SUBSTATUS_CANT_RUN);
    RET;

}

void AI_TryItem(void){
// items are not allowed in the Battle Tower
    LD_A_addr(wInBattleTowerBattle);
    AND_A_A;
    RET_NZ ;

    LD_A_addr(wEnemyTrainerItem1);
    LD_B_A;
    LD_A_addr(wEnemyTrainerItem2);
    OR_A_B;
    RET_Z ;

    CALL(aAI_TryItem_IsHighestLevel);
    RET_NC ;

    LD_A_addr(wTrainerClass);
    DEC_A;
    LD_HL(mTrainerClassAttributes + TRNATTR_AI_ITEM_SWITCH);
    LD_BC(NUM_TRAINER_ATTRIBUTES);
    CALL(aAddNTimes);
    LD_B_H;
    LD_C_L;
    LD_HL(mAI_Items);
    LD_DE(wEnemyTrainerItem1);

loop:
    LD_A_hl;
    AND_A_A;
    INC_A;
    RET_Z ;

    LD_A_de;
    CP_A_hl;
    IF_Z goto has_item;
    INC_DE;
    LD_A_de;
    CP_A_hl;
    IF_Z goto has_item;

    DEC_DE;
    INC_HL;
    INC_HL;
    INC_HL;
    goto loop;


has_item:
    INC_HL;

    PUSH_HL;
    PUSH_DE;
    // LD_DE(mAI_TryItem_callback);
    // PUSH_DE;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    // JP_hl;
    CALL_hl;

callback:
    POP_DE;
    POP_HL;

    INC_HL;
    INC_HL;
    IF_C goto loop;

//  used item
    XOR_A_A;
    LD_de_A;
    INC_A;
    LD_addr_A(wEnemyGoesFirst);

    LD_HL(wEnemySubStatus3);
    RES_hl(SUBSTATUS_BIDE);

    XOR_A_A;
    LD_addr_A(wEnemyFuryCutterCount);
    LD_addr_A(wEnemyProtectCount);
    LD_addr_A(wEnemyRageCounter);

    LD_HL(wEnemySubStatus4);
    RES_hl(SUBSTATUS_RAGE);

    XOR_A_A;
    LD_addr_A(wLastEnemyCounterMove);

    SCF;
    RET;


IsHighestLevel:
    LD_A_addr(wOTPartyCount);
    LD_D_A;
    LD_E(0);
    LD_HL(wOTPartyMon1Level);
    LD_BC(PARTYMON_STRUCT_LENGTH);

next:
    LD_A_hl;
    CP_A_E;
    IF_C goto ok;
    LD_E_A;

ok:
    ADD_HL_BC;
    DEC_D;
    IF_NZ goto next;

    LD_A_addr(wCurOTMon);
    LD_HL(wOTPartyMon1Level);
    CALL(aAddNTimes);
    LD_A_hl;
    CP_A_E;
    IF_NC goto yes;


no:
//   //  unreferenced
    AND_A_A;
    RET;


yes:
    SCF;
    RET;

}

void AI_Items(void){
    //dbw ['FULL_RESTORE', '.FullRestore']
    //dbw ['MAX_POTION', '.MaxPotion']
    //dbw ['HYPER_POTION', '.HyperPotion']
    //dbw ['SUPER_POTION', '.SuperPotion']
    //dbw ['POTION', '.Potion']
    //dbw ['X_ACCURACY', '.XAccuracy']
    //dbw ['FULL_HEAL', '.FullHeal']
    //dbw ['GUARD_SPEC', '.GuardSpec']
    //dbw ['DIRE_HIT', '.DireHit']
    //dbw ['X_ATTACK', '.XAttack']
    //dbw ['X_DEFEND', '.XDefend']
    //dbw ['X_SPEED', '.XSpeed']
    //dbw ['X_SPECIAL', '.XSpecial']
    //db ['-1'];  // end

FullHeal:
    CALL(aAI_Items_Status);
    JP_C (mAI_Items_DontUse);
    CALL(aEnemyUsedFullHeal);
    JP(mAI_Items_Use);


Status:
    LD_A_addr(wEnemyMonStatus);
    AND_A_A;
    JP_Z (mAI_Items_DontUse);

    LD_A_bc;
    BIT_A(CONTEXT_USE_F);
    IF_NZ goto StatusCheckContext;
    LD_A_bc;
    BIT_A(ALWAYS_USE_F);
    JP_NZ (mAI_Items_Use);
    CALL(aRandom);
    CP_A(20 percent - 1);
    JP_C (mAI_Items_Use);
    JP(mAI_Items_DontUse);


StatusCheckContext:
    LD_A_addr(wEnemySubStatus5);
    BIT_A(SUBSTATUS_TOXIC);
    IF_Z goto FailToxicCheck;
    LD_A_addr(wEnemyToxicCount);
    CP_A(4);
    IF_C goto FailToxicCheck;
    CALL(aRandom);
    CP_A(50 percent + 1);
    JP_C (mAI_Items_Use);

FailToxicCheck:
    LD_A_addr(wEnemyMonStatus);
    AND_A(1 << FRZ | SLP);
    JP_Z (mAI_Items_DontUse);
    JP(mAI_Items_Use);


FullRestore:
    CALL(aAI_Items_HealItem);
    JP_NC (mAI_Items_UseFullRestore);
    LD_A_bc;
    BIT_A(CONTEXT_USE_F);
    JP_Z (mAI_Items_DontUse);
    CALL(aAI_Items_Status);
    JP_C (mAI_Items_DontUse);


UseFullRestore:
    CALL(aEnemyUsedFullRestore);
    JP(mAI_Items_Use);


MaxPotion:
    CALL(aAI_Items_HealItem);
    JP_C (mAI_Items_DontUse);
    CALL(aEnemyUsedMaxPotion);
    JP(mAI_Items_Use);


HealItem:
    LD_A_bc;
    BIT_A(CONTEXT_USE_F);
    IF_NZ goto CheckHalfOrQuarterHP;
    CALLFAR(aAICheckEnemyHalfHP);
    JP_C (mAI_Items_DontUse);
    LD_A_bc;
    BIT_A(UNKNOWN_USE_F);
    JP_NZ (mAI_Items_CheckQuarterHP);
    CALLFAR(aAICheckEnemyQuarterHP);
    JP_NC (mAI_Items_UseHealItem);
    CALL(aRandom);
    CP_A(50 percent + 1);
    JP_C (mAI_Items_UseHealItem);
    JP(mAI_Items_DontUse);


CheckQuarterHP:
    CALLFAR(aAICheckEnemyQuarterHP);
    JP_C (mAI_Items_DontUse);
    CALL(aRandom);
    CP_A(20 percent - 1);
    JP_C (mAI_Items_DontUse);
    goto UseHealItem;


CheckHalfOrQuarterHP:
    CALLFAR(aAICheckEnemyHalfHP);
    JP_C (mAI_Items_DontUse);
    CALLFAR(aAICheckEnemyQuarterHP);
    JP_NC (mAI_Items_UseHealItem);
    CALL(aRandom);
    CP_A(20 percent - 1);
    JP_NC (mAI_Items_DontUse);


UseHealItem:
    JP(mAI_Items_Use);


HyperPotion:
    CALL(aAI_Items_HealItem);
    JP_C (mAI_Items_DontUse);
    LD_B(200);
    CALL(aEnemyUsedHyperPotion);
    JP(mAI_Items_Use);


SuperPotion:
    CALL(aAI_Items_HealItem);
    JP_C (mAI_Items_DontUse);
    LD_B(50);
    CALL(aEnemyUsedSuperPotion);
    JP(mAI_Items_Use);


Potion:
    CALL(aAI_Items_HealItem);
    JP_C (mAI_Items_DontUse);
    LD_B(20);
    CALL(aEnemyUsedPotion);
    JP(mAI_Items_Use);

//  Everything up to "End unused" is unused


UnusedHealItem:
//   //  unreferenced
//  This has similar conditions to .HealItem
    CALLFAR(aAICheckEnemyMaxHP);
    IF_C goto dont_use;
    PUSH_BC;
    LD_DE(wEnemyMonMaxHP + 1);
    LD_HL(wEnemyMonHP + 1);
    LD_A_de;
    SUB_A_hl;
    IF_Z goto check_40_percent;
    DEC_HL;
    DEC_DE;
    LD_C_A;
    SBC_A_hl;
    AND_A_A;
    IF_NZ goto check_40_percent;
    LD_A_C;
    CP_A_B;
    JP_C (mAI_Items_check_50_percent);
    CALLFAR(aAICheckEnemyQuarterHP);
    IF_C goto check_40_percent;


check_50_percent:
    POP_BC;
    LD_A_bc;
    BIT_A(UNKNOWN_USE_F);
    JP_Z (mAI_Items_Use);
    CALL(aRandom);
    CP_A(50 percent + 1);
    JP_C (mAI_Items_Use);


dont_use:
    JP(mAI_Items_DontUse);


check_40_percent:
    POP_BC;
    LD_A_bc;
    BIT_A(UNKNOWN_USE_F);
    JP_Z (mAI_Items_DontUse);
    CALL(aRandom);
    CP_A(39 percent + 1);
    JP_C (mAI_Items_Use);
    JP(mAI_Items_DontUse);

//  End unused


XAccuracy:
    CALL(aAI_Items_XItem);
    JP_C (mAI_Items_DontUse);
    CALL(aEnemyUsedXAccuracy);
    JP(mAI_Items_Use);


GuardSpec:
    CALL(aAI_Items_XItem);
    JP_C (mAI_Items_DontUse);
    CALL(aEnemyUsedGuardSpec);
    JP(mAI_Items_Use);


DireHit:
    CALL(aAI_Items_XItem);
    JP_C (mAI_Items_DontUse);
    CALL(aEnemyUsedDireHit);
    JP(mAI_Items_Use);


XAttack:
    CALL(aAI_Items_XItem);
    JP_C (mAI_Items_DontUse);
    CALL(aEnemyUsedXAttack);
    JP(mAI_Items_Use);


XDefend:
    CALL(aAI_Items_XItem);
    JP_C (mAI_Items_DontUse);
    CALL(aEnemyUsedXDefend);
    JP(mAI_Items_Use);


XSpeed:
    CALL(aAI_Items_XItem);
    JP_C (mAI_Items_DontUse);
    CALL(aEnemyUsedXSpeed);
    JP(mAI_Items_Use);


XSpecial:
    CALL(aAI_Items_XItem);
    JP_C (mAI_Items_DontUse);
    CALL(aEnemyUsedXSpecial);
    JP(mAI_Items_Use);


XItem:
    LD_A_addr(wEnemyTurnsTaken);
    AND_A_A;
    IF_NZ goto notfirstturnout;
    LD_A_bc;
    BIT_A(ALWAYS_USE_F);
    JP_NZ (mAI_Items_Use);
    CALL(aRandom);
    CP_A(50 percent + 1);
    JP_C (mAI_Items_DontUse);
    LD_A_bc;
    BIT_A(CONTEXT_USE_F);
    JP_NZ (mAI_Items_Use);
    CALL(aRandom);
    CP_A(50 percent + 1);
    JP_C (mAI_Items_DontUse);
    JP(mAI_Items_Use);

notfirstturnout:
    LD_A_bc;
    BIT_A(ALWAYS_USE_F);
    JP_Z (mAI_Items_DontUse);
    CALL(aRandom);
    CP_A(20 percent - 1);
    JP_NC (mAI_Items_DontUse);
    JP(mAI_Items_Use);


DontUse:
    SCF;
    RET;


Use:
    AND_A_A;
    RET;

}

void AIUpdateHUD(void){
    CALL(aUpdateEnemyMonInParty);
    FARCALL(aUpdateEnemyHUD);
    LD_A(0x1);
    LDH_addr_A(hBGMapMode);
    LD_HL(wEnemyItemState);
    DEC_hl;
    SCF;
    RET;

}

void AIUsedItemSound(void){
    // PUSH_DE;
    // LD_DE(SFX_FULL_HEAL);
    // CALL(aPlaySFX);
    // POP_DE;
    // RET;
    PlaySFX_Conv(SFX_FULL_HEAL);
}

void EnemyUsedFullHeal(void){
    CALL(aAIUsedItemSound);
    CALL(aAI_HealStatus);
    LD_A(FULL_HEAL);
    JP(mPrintText_UsedItemOn_AND_AIUpdateHUD);

}

void EnemyUsedMaxPotion(void){
    LD_A(MAX_POTION);
    LD_addr_A(wCurEnemyItem);
    JR(mFullRestoreContinue);

}

void EnemyUsedFullRestore(void){
    CALL(aAI_HealStatus);
    LD_A(FULL_RESTORE);
    LD_addr_A(wCurEnemyItem);
    LD_HL(wEnemySubStatus3);
    RES_hl(SUBSTATUS_CONFUSED);
    XOR_A_A;
    LD_addr_A(wEnemyConfuseCount);

    return FullRestoreContinue();
}

void FullRestoreContinue(void){
    LD_DE(wCurHPAnimOldHP);
    LD_HL(wEnemyMonHP + 1);
    LD_A_hld;
    LD_de_A;
    INC_DE;
    LD_A_hl;
    LD_de_A;
    INC_DE;
    LD_HL(wEnemyMonMaxHP + 1);
    LD_A_hld;
    LD_de_A;
    INC_DE;
    LD_addr_A(wCurHPAnimMaxHP);
    LD_addr_A(wEnemyMonHP + 1);
    LD_A_hl;
    LD_de_A;
    LD_addr_A(wCurHPAnimMaxHP + 1);
    LD_addr_A(wEnemyMonHP);
    JR(mEnemyPotionFinish);

}

void EnemyUsedPotion(void){
    LD_A(POTION);
    LD_B(20);
    JR(mEnemyPotionContinue);

}

void EnemyUsedSuperPotion(void){
    LD_A(SUPER_POTION);
    LD_B(50);
    JR(mEnemyPotionContinue);

}

void EnemyUsedHyperPotion(void){
    LD_A(HYPER_POTION);
    LD_B(200);

    return EnemyPotionContinue();
}

void EnemyPotionContinue(void){
    LD_addr_A(wCurEnemyItem);
    LD_HL(wEnemyMonHP + 1);
    LD_A_hl;
    LD_addr_A(wCurHPAnimOldHP);
    ADD_A_B;
    LD_hld_A;
    LD_addr_A(wCurHPAnimNewHP);
    LD_A_hl;
    LD_addr_A(wCurHPAnimOldHP + 1);
    LD_addr_A(wCurHPAnimNewHP + 1);
    IF_NC goto ok;
    INC_A;
    LD_hl_A;
    LD_addr_A(wCurHPAnimNewHP + 1);

ok:
    INC_HL;
    LD_A_hld;
    LD_B_A;
    LD_DE(wEnemyMonMaxHP + 1);
    LD_A_de;
    DEC_DE;
    LD_addr_A(wCurHPAnimMaxHP);
    SUB_A_B;
    LD_A_hli;
    LD_B_A;
    LD_A_de;
    LD_addr_A(wCurHPAnimMaxHP + 1);
    SBC_A_B;
    JR_NC (mEnemyPotionFinish);
    INC_DE;
    LD_A_de;
    DEC_DE;
    LD_hld_A;
    LD_addr_A(wCurHPAnimNewHP);
    LD_A_de;
    LD_hl_A;
    LD_addr_A(wCurHPAnimNewHP + 1);

    return EnemyPotionFinish();
}

void EnemyPotionFinish(void){
    CALL(aPrintText_UsedItemOn);
    hlcoord(2, 2, wTilemap);
    XOR_A_A;
    LD_addr_A(wWhichHPBar);
    CALL(aAIUsedItemSound);
    PREDEF(pAnimateHPBar);
    JP(mAIUpdateHUD);

}

void AI_TrySwitch(void){
//  Determine whether the AI can switch based on how many Pokemon are still alive.
//  If it can switch, it will.
    LD_A_addr(wOTPartyCount);
    LD_C_A;
    LD_HL(wOTPartyMon1HP);
    LD_D(0);

SwitchLoop:
    LD_A_hli;
    LD_B_A;
    LD_A_hld;
    OR_A_B;
    IF_Z goto fainted;
    INC_D;

fainted:
    PUSH_BC;
    LD_BC(PARTYMON_STRUCT_LENGTH);
    ADD_HL_BC;
    POP_BC;
    DEC_C;
    IF_NZ goto SwitchLoop;

    LD_A_D;
    CP_A(2);
    JP_NC (mAI_Switch);
    AND_A_A;
    RET;

}

void AI_Switch(void){
    LD_A(0x1);
    LD_addr_A(wEnemyIsSwitching);
    LD_addr_A(wEnemyGoesFirst);
    LD_HL(wEnemySubStatus4);
    RES_hl(SUBSTATUS_RAGE);
    XOR_A_A;
    LDH_addr_A(hBattleTurn);
    CALLFAR(aPursuitSwitch);

    PUSH_AF;
    LD_A_addr(wCurOTMon);
    LD_HL(wOTPartyMon1Status);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aAddNTimes);
    LD_D_H;
    LD_E_L;
    LD_HL(wEnemyMonStatus);
    LD_BC(MON_MAXHP - MON_STATUS);
    CALL(aCopyBytes);
    POP_AF;

    IF_C goto skiptext;
    LD_HL(mEnemyWithdrewText);
    CALL(aPrintText);


skiptext:
    LD_A(1);
    LD_addr_A(wBattleHasJustStarted);
    CALLFAR(aNewEnemyMonStatus);
    CALLFAR(aResetEnemyStatLevels);
    LD_HL(wPlayerSubStatus1);
    RES_hl(SUBSTATUS_IN_LOVE);
    FARCALL(aEnemySwitch);
    FARCALL(aResetBattleParticipants);
    XOR_A_A;
    LD_addr_A(wBattleHasJustStarted);
    LD_A_addr(wLinkMode);
    AND_A_A;
    RET_NZ ;
    SCF;
    RET;

}

const txt_cmd_s EnemyWithdrewText[] = {
    text_far(v_EnemyWithdrewText)
    text_end
};

void EnemyUsedFullHealRed(void){
//  //  unreferenced
    CALL(aAIUsedItemSound);
    CALL(aAI_HealStatus);
    LD_A(FULL_HEAL_RED);  // X_SPEED
    JP(mPrintText_UsedItemOn_AND_AIUpdateHUD);

}

void AI_HealStatus(void){
    LD_A_addr(wCurOTMon);
    LD_HL(wOTPartyMon1Status);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aAddNTimes);
    XOR_A_A;
    LD_hl_A;
    LD_addr_A(wEnemyMonStatus);
// Bug: this should reset SUBSTATUS_NIGHTMARE
// Uncomment the 2 lines below to fix
// ld hl, wEnemySubStatus1
// res SUBSTATUS_NIGHTMARE, [hl]
// Bug: this should reset SUBSTATUS_CONFUSED
// Uncomment the 2 lines below to fix
// ld hl, wEnemySubStatus3
// res SUBSTATUS_CONFUSED, [hl]
    LD_HL(wEnemySubStatus5);
    RES_hl(SUBSTATUS_TOXIC);
    RET;

}

void EnemyUsedXAccuracy(void){
    CALL(aAIUsedItemSound);
    LD_HL(wEnemySubStatus4);
    SET_hl(SUBSTATUS_X_ACCURACY);
    LD_A(X_ACCURACY);
    JP(mPrintText_UsedItemOn_AND_AIUpdateHUD);

}

void EnemyUsedGuardSpec(void){
    CALL(aAIUsedItemSound);
    LD_HL(wEnemySubStatus4);
    SET_hl(SUBSTATUS_MIST);
    LD_A(GUARD_SPEC);
    JP(mPrintText_UsedItemOn_AND_AIUpdateHUD);

}

void EnemyUsedDireHit(void){
    CALL(aAIUsedItemSound);
    LD_HL(wEnemySubStatus4);
    SET_hl(SUBSTATUS_FOCUS_ENERGY);
    LD_A(DIRE_HIT);
    JP(mPrintText_UsedItemOn_AND_AIUpdateHUD);

}

void AICheckEnemyFractionMaxHP(void){
//  //  unreferenced
//  Input: a = divisor
//  Work: bc = [wEnemyMonMaxHP] / a
//  Work: de = [wEnemyMonHP]
//  Output:
//  -  c, nz if [wEnemyMonHP] > [wEnemyMonMaxHP] / a
//  - nc,  z if [wEnemyMonHP] = [wEnemyMonMaxHP] / a
//  - nc, nz if [wEnemyMonHP] < [wEnemyMonMaxHP] / a
    LDH_addr_A(hDivisor);
    LD_HL(wEnemyMonMaxHP);
    LD_A_hli;
    LDH_addr_A(hDividend);
    LD_A_hl;
    LDH_addr_A(hDividend + 1);
    LD_B(2);
    CALL(aDivide);
    LDH_A_addr(hQuotient + 3);
    LD_C_A;
    LDH_A_addr(hQuotient + 2);
    LD_B_A;
    LD_HL(wEnemyMonHP + 1);
    LD_A_hld;
    LD_E_A;
    LD_A_hl;
    LD_D_A;
    LD_A_D;
    SUB_A_B;
    RET_NZ ;
    LD_A_E;
    SUB_A_C;
    RET;

}

void EnemyUsedXAttack(void){
    LD_B(ATTACK);
    LD_A(X_ATTACK);
    JR(mEnemyUsedXItem);

}

void EnemyUsedXDefend(void){
    LD_B(DEFENSE);
    LD_A(X_DEFEND);
    JR(mEnemyUsedXItem);

}

void EnemyUsedXSpeed(void){
    LD_B(SPEED);
    LD_A(X_SPEED);
    JR(mEnemyUsedXItem);

}

void EnemyUsedXSpecial(void){
    LD_B(SP_ATTACK);
    LD_A(X_SPECIAL);

//  Parameter
//  a = ITEM_CONSTANT
//  b = BATTLE_CONSTANT (ATTACK, DEFENSE, SPEED, SP_ATTACK, SP_DEFENSE, ACCURACY, EVASION)
    return EnemyUsedXItem();
}

void EnemyUsedXItem(void){
    LD_addr_A(wCurEnemyItem);
    PUSH_BC;
    CALL(aPrintText_UsedItemOn);
    POP_BC;
    FARCALL(aRaiseStat);
    JP(mAIUpdateHUD);

//  Parameter
//  a = ITEM_CONSTANT
    return PrintText_UsedItemOn_AND_AIUpdateHUD();
}

void PrintText_UsedItemOn_AND_AIUpdateHUD(void){
    LD_addr_A(wCurEnemyItem);
    CALL(aPrintText_UsedItemOn);
    JP(mAIUpdateHUD);

}

void PrintText_UsedItemOn(void){
    LD_A_addr(wCurEnemyItem);
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetItemName);
    LD_HL(wStringBuffer1);
    LD_DE(wMonOrItemNameBuffer);
    LD_BC(ITEM_NAME_LENGTH);
    CALL(aCopyBytes);
    LD_HL(mEnemyUsedOnText);
    JP(mPrintText);

}

const txt_cmd_s EnemyUsedOnText[] = {
    text_far(v_EnemyUsedOnText)
    text_end
};
