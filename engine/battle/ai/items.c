#include "../../../constants.h"
#include "items.h"
#include "scoring.h"
#include "switch.h"
#include "../core.h"
#include "../effect_commands.h"
#include "../../pokemon/health.h"
#include "../../../home/audio.h"
#include "../../../home/battle.h"
#include "../../../home/copy.h"
#include "../../../home/text.h"
#include "../../../home/names.h"
#include "../../../home/random.h"
#include "../../../data/text/common.h"
#include "../../../data/trainers/attributes.h"

bool AI_SwitchOrTryItem(void){
    // AND_A_A;

    // LD_A_addr(wBattleMode);
    // DEC_A;
    // RET_Z ;
    if(wram->wBattleMode == WILD_BATTLE)
        return false;

    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // RET_NZ ;

    // FARCALL(aCheckEnemyLockedIn);
    // RET_NZ ;
    if(wram->wLinkMode != LINK_NULL || CheckEnemyLockedIn_Conv())
        return false;

    // LD_A_addr(wPlayerSubStatus5);
    // BIT_A(SUBSTATUS_CANT_RUN);
    // JR_NZ (mDontSwitch);

    // LD_A_addr(wEnemyWrapCount);
    // AND_A_A;
    // JR_NZ (mDontSwitch);
    if(bit_test(wram->wPlayerSubStatus5, SUBSTATUS_CANT_RUN) || wram->wEnemyWrapCount != 0)
        return DontSwitch();

// always load the first trainer class in wTrainerClass for Battle Tower trainers
    // LD_HL(mTrainerClassAttributes + TRNATTR_AI_ITEM_SWITCH);
    // LD_A_addr(wInBattleTowerBattle);
    // AND_A_A;
    // IF_NZ goto ok;

    // LD_A_addr(wTrainerClass);
    // DEC_A;
    // LD_BC(NUM_TRAINER_ATTRIBUTES);
    // CALL(aAddNTimes);

    uint8_t attr = (wram->wInBattleTowerBattle != 0)
        ? TrainerClassAttributes[FALKNER].aiItemSwitch // always load the first trainer class in wTrainerClass for Battle Tower trainers
        : TrainerClassAttributes[wram->wTrainerClass].aiItemSwitch;

// ok:
    // BIT_hl(SWITCH_OFTEN_F);
    // JP_NZ (mSwitchOften);
    if(bit_test(attr, SWITCH_OFTEN_F))
        return SwitchOften();
    // BIT_hl(SWITCH_RARELY_F);
    // JP_NZ (mSwitchRarely);
    else if(bit_test(attr, SWITCH_RARELY_F))
        return SwitchRarely();
    // BIT_hl(SWITCH_SOMETIMES_F);
    // JP_NZ (mSwitchSometimes);
    else if(bit_test(attr, SWITCH_SOMETIMES_F))
        return SwitchSometimes();
// fallthrough

    return DontSwitch();
}

bool DontSwitch(void){
    // CALL(aAI_TryItem);
    // RET;
    return AI_TryItem();
}

bool SwitchOften(void){
    // CALLFAR(aCheckAbleToSwitch);
    CheckAbleToSwitch_Conv();
    // LD_A_addr(wEnemySwitchMonParam);
    // AND_A(0xf0);
    uint8_t param = (wram->wEnemySwitchMonParam & 0xf0);
    // JP_Z (mDontSwitch);
    if(param == 0x0)
        return DontSwitch();

    // CP_A(0x10);
    // IF_NZ goto not_10;
    if(param == 0x10) {
        // CALL(aRandom);
        // CP_A(50 percent + 1);
        // IF_C goto switch_;
        // JP(mDontSwitch);
        if(Random_Conv() >= 50 percent + 1)
            return DontSwitch();
    }

// not_10:
    // CP_A(0x20);
    // IF_NZ goto not_20;
    else if(param == 0x20) {
        // CALL(aRandom);
        // CP_A(79 percent - 1);
        // IF_C goto switch_;
        // JP(mDontSwitch);
        if(Random_Conv() >= 79 percent - 1)
            return DontSwitch();
    }

// not_20:
// $30
    // CALL(aRandom);
    // CP_A(4 percent);
    // JP_C (mDontSwitch);
    else if(Random_Conv() < 4 percent)
        return DontSwitch();

// switch_:
    // LD_A_addr(wEnemySwitchMonParam);
    // AND_A(0xf);
    // INC_A;
// In register 'a' is the number (1-6) of the mon to switch to
    // LD_addr_A(wEnemySwitchMonIndex);
    wram->wEnemySwitchMonIndex = (wram->wEnemySwitchMonParam & 0xf) + 1;
    // JP(mAI_TrySwitch);
    return AI_TrySwitch();
}

bool SwitchRarely(void){
    // CALLFAR(aCheckAbleToSwitch);
    CheckAbleToSwitch_Conv();
    // LD_A_addr(wEnemySwitchMonParam);
    // AND_A(0xf0);
    uint8_t param = (wram->wEnemySwitchMonParam & 0xf0);
    // JP_Z (mDontSwitch);
    if(param == 0x0)
        return DontSwitch();

    // CP_A(0x10);
    // IF_NZ goto not_10;
    if(param == 0x10) {
        // CALL(aRandom);
        // CP_A(8 percent);
        // IF_C goto switch_;
        // JP(mDontSwitch);
        if(Random_Conv() >= 8 percent)
            return DontSwitch();
    }

// not_10:
    // CP_A(0x20);
    // IF_NZ goto not_20;
    else if(param == 0x20) {
        // CALL(aRandom);
        // CP_A(12 percent);
        // IF_C goto switch_;
        // JP(mDontSwitch);
        if(Random_Conv() >= 12 percent)
            return DontSwitch();
    }

// not_20:
// $30
    // CALL(aRandom);
    // CP_A(79 percent - 1);
    // JP_C (mDontSwitch);
    else if(Random_Conv() < 79 percent - 1)
        return DontSwitch();

// switch_:
    // LD_A_addr(wEnemySwitchMonParam);
    // AND_A(0xf);
    // INC_A;
    // LD_addr_A(wEnemySwitchMonIndex);
    wram->wEnemySwitchMonIndex = (wram->wEnemySwitchMonParam & 0xf) + 1;
    // JP(mAI_TrySwitch);
    return AI_TrySwitch();
}

bool SwitchSometimes(void){
    // CALLFAR(aCheckAbleToSwitch);
    CheckAbleToSwitch_Conv();
    // LD_A_addr(wEnemySwitchMonParam);
    // AND_A(0xf0);
    uint8_t param = (wram->wEnemySwitchMonParam & 0xf0);
    // JP_Z (mDontSwitch);
    if(param == 0x0)
        return DontSwitch();

    // CP_A(0x10);
    // IF_NZ goto not_10;
    if(param == 0x10) {
        // CALL(aRandom);
        // CP_A(20 percent - 1);
        // IF_C goto switch_;
        // JP(mDontSwitch);
        if(Random_Conv() < 20 percent - 1)
            return DontSwitch();
    }

// not_10:
    // CP_A(0x20);
    // IF_NZ goto not_20;
    else if(param == 0x20) {
        // CALL(aRandom);
        // CP_A(50 percent + 1);
        // IF_C goto switch_;
        // JP(mDontSwitch);
        if(Random_Conv() < 50 percent + 1)
            return DontSwitch();
    }

// not_20:
// $30
    // CALL(aRandom);
    // CP_A(20 percent - 1);
    // JP_C (mDontSwitch);
    else if(Random_Conv() < 20 percent - 1)
        return DontSwitch();

// switch_:
    // LD_A_addr(wEnemySwitchMonParam);
    // AND_A(0xf);
    // INC_A;
    // LD_addr_A(wEnemySwitchMonIndex);
    wram->wEnemySwitchMonIndex = (wram->wEnemySwitchMonParam & 0xf) + 1;
    // JP(mAI_TrySwitch);
    return AI_TrySwitch();
}

void CheckSubstatusCantRun(void){
//  //  unreferenced
    LD_A_addr(wEnemySubStatus5);
    BIT_A(SUBSTATUS_CANT_RUN);
    RET;

}

static bool AI_Items_DontUse(void){
    // SCF;
    // RET;
    return false;
}

static bool AI_Items_Use(void){
    // AND_A_A;
    // RET;
    return true;
}

static bool AI_Items_Status(uint8_t bc){
    // LD_A_addr(wEnemyMonStatus);
    // AND_A_A;
    // JP_Z (mAI_Items_DontUse);
    if(wram->wEnemyMon.status[0] == 0)
        return AI_Items_DontUse();

    // LD_A_bc;
    // BIT_A(CONTEXT_USE_F);
    // IF_NZ goto StatusCheckContext;
    if(bit_test(bc, CONTEXT_USE_F)) {
    // StatusCheckContext:
        // LD_A_addr(wEnemySubStatus5);
        // BIT_A(SUBSTATUS_TOXIC);
        // IF_Z goto FailToxicCheck;
        // LD_A_addr(wEnemyToxicCount);
        // CP_A(4);
        // IF_C goto FailToxicCheck;
        if(bit_test(wram->wEnemySubStatus5, SUBSTATUS_TOXIC) && wram->wEnemyToxicCount >= 4) {
            // CALL(aRandom);
            // CP_A(50 percent + 1);
            // JP_C (mAI_Items_Use);
            if(Random_Conv() < 50 percent + 1)
                return AI_Items_Use();
        }

    // FailToxicCheck:
        // LD_A_addr(wEnemyMonStatus);
        // AND_A(1 << FRZ | SLP);
        // JP_Z (mAI_Items_DontUse);
        if((wram->wEnemyMon.status[0] & ((1 << FRZ) | SLP)) == 0)
            return AI_Items_DontUse();
        // JP(mAI_Items_Use);
        return AI_Items_Use();
    }
    // LD_A_bc;
    // BIT_A(ALWAYS_USE_F);
    // JP_NZ (mAI_Items_Use);
    if(bit_test(bc, ALWAYS_USE_F))
        return AI_Items_Use();
    // CALL(aRandom);
    // CP_A(20 percent - 1);
    // JP_C (mAI_Items_Use);
    if(Random_Conv() < 20 percent - 1)
        return AI_Items_Use();
    // JP(mAI_Items_DontUse);
    return AI_Items_DontUse();
}

static bool AI_Items_HealItem(uint8_t bc){
    // LD_A_bc;
    // BIT_A(CONTEXT_USE_F);
    // IF_NZ goto CheckHalfOrQuarterHP;
    if(bit_test(bc, CONTEXT_USE_F)) {
    // CheckHalfOrQuarterHP:
        // CALLFAR(aAICheckEnemyHalfHP);
        // JP_C (mAI_Items_DontUse);
        if(!AICheckEnemyHalfHP_Conv())
            return AI_Items_DontUse();
        // CALLFAR(aAICheckEnemyQuarterHP);
        // JP_NC (mAI_Items_UseHealItem);
        if(AICheckEnemyQuarterHP_Conv())
            return AI_Items_Use();
        // CALL(aRandom);
        // CP_A(20 percent - 1);
        // JP_NC (mAI_Items_DontUse);
        if(Random_Conv() < 20 percent - 1)
            return AI_Items_DontUse();

    // UseHealItem:
        // JP(mAI_Items_Use);
        return AI_Items_Use();
    }
    // CALLFAR(aAICheckEnemyHalfHP);
    // JP_C (mAI_Items_DontUse);
    if(!AICheckEnemyHalfHP_Conv())
        return AI_Items_DontUse();
    // LD_A_bc;
    // BIT_A(UNKNOWN_USE_F);
    // JP_NZ (mAI_Items_CheckQuarterHP);
    if(bit_test(bc, UNKNOWN_USE_F)) {
    // CheckQuarterHP:
        // CALLFAR(aAICheckEnemyQuarterHP);
        // JP_C (mAI_Items_DontUse);
        if(!AICheckEnemyQuarterHP_Conv())
            return AI_Items_DontUse();
        // CALL(aRandom);
        // CP_A(20 percent - 1);
        // JP_C (mAI_Items_DontUse);
        if(Random_Conv() < 20 percent - 1)
            return AI_Items_DontUse();
        // goto UseHealItem;
        return AI_Items_Use();
    }
    // CALLFAR(aAICheckEnemyQuarterHP);
    // JP_NC (mAI_Items_UseHealItem);
    if(!AICheckEnemyQuarterHP_Conv())
        return AI_Items_DontUse();
    // CALL(aRandom);
    // CP_A(50 percent + 1);
    // JP_C (mAI_Items_UseHealItem);
    if(Random_Conv() < 50 percent + 1)
        return AI_Items_Use();
    // JP(mAI_Items_DontUse);
    return AI_Items_DontUse();
}

static bool AI_Items_XItem(uint8_t bc){
    // LD_A_addr(wEnemyTurnsTaken);
    // AND_A_A;
    // IF_NZ goto notfirstturnout;
    if(wram->wEnemyTurnsTaken == 0) {
        // LD_A_bc;
        // BIT_A(ALWAYS_USE_F);
        // JP_NZ (mAI_Items_Use);
        if(bit_test(bc, ALWAYS_USE_F))
            return AI_Items_Use();
        // CALL(aRandom);
        // CP_A(50 percent + 1);
        // JP_C (mAI_Items_DontUse);
        if(Random_Conv() < 50 percent + 1)
            return AI_Items_DontUse();
        // LD_A_bc;
        // BIT_A(CONTEXT_USE_F);
        // JP_NZ (mAI_Items_Use);
        if(bit_test(bc, CONTEXT_USE_F))
            return AI_Items_Use();
        // CALL(aRandom);
        // CP_A(50 percent + 1);
        // JP_C (mAI_Items_DontUse);
        if(Random_Conv() < 50 percent + 1)
            return AI_Items_DontUse();
        // JP(mAI_Items_Use);
        return AI_Items_Use();
    }
    else {
    // notfirstturnout:
        // LD_A_bc;
        // BIT_A(ALWAYS_USE_F);
        // JP_Z (mAI_Items_DontUse);
        if(!bit_test(bc, ALWAYS_USE_F))
            return AI_Items_DontUse();
        // CALL(aRandom);
        // CP_A(20 percent - 1);
        // JP_NC (mAI_Items_DontUse);
        if(Random_Conv() >= 20 percent - 1)
            return AI_Items_DontUse();
        // JP(mAI_Items_Use);
        return AI_Items_Use();
    }

}

static bool AI_Items_FullHeal(uint8_t bc){
    // CALL(aAI_Items_Status);
    // JP_C (mAI_Items_DontUse);
    if(!AI_Items_Status(bc))
        return AI_Items_DontUse();
    // CALL(aEnemyUsedFullHeal);
    // JP(mAI_Items_Use);
    return AI_Items_Use();
}

static bool AI_Items_FullRestore(uint8_t bc){
    // CALL(aAI_Items_HealItem);
    // JP_NC (mAI_Items_UseFullRestore);
    if(!AI_Items_HealItem(bc)) {
        // LD_A_bc;
        // BIT_A(CONTEXT_USE_F);
        // JP_Z (mAI_Items_DontUse);
        if(!bit_test(bc, CONTEXT_USE_F))
            return AI_Items_DontUse();
        // CALL(aAI_Items_Status);
        // JP_C (mAI_Items_DontUse);
        if(!AI_Items_Status(bc))
            return AI_Items_DontUse();
    }

// UseFullRestore:
    // CALL(aEnemyUsedFullRestore);
    EnemyUsedFullRestore();
    // JP(mAI_Items_Use);
    return AI_Items_Use();
}

static bool AI_Items_MaxPotion(uint8_t bc){
    // CALL(aAI_Items_HealItem);
    // JP_C (mAI_Items_DontUse);
    if(!AI_Items_HealItem(bc))
        return AI_Items_DontUse();
    // CALL(aEnemyUsedMaxPotion);
    EnemyUsedMaxPotion();
    // JP(mAI_Items_Use);
    return AI_Items_Use();
}

static bool AI_Items_HyperPotion(uint8_t bc){
    // CALL(aAI_Items_HealItem);
    // JP_C (mAI_Items_DontUse);
    if(!AI_Items_HealItem(bc))
        return AI_Items_DontUse();
    // LD_B(200); // Useless
    // CALL(aEnemyUsedHyperPotion);
    EnemyUsedHyperPotion();
    // JP(mAI_Items_Use);
    return AI_Items_Use();
}

static bool AI_Items_SuperPotion(uint8_t bc){
    // CALL(aAI_Items_HealItem);
    // JP_C (mAI_Items_DontUse);
    if(!AI_Items_HealItem(bc))
        return AI_Items_DontUse();
    // LD_B(50);
    // CALL(aEnemyUsedSuperPotion);
    EnemyUsedSuperPotion();
    // JP(mAI_Items_Use);
    return AI_Items_Use();
}

static bool AI_Items_Potion(uint8_t bc){
    // CALL(aAI_Items_HealItem);
    // JP_C (mAI_Items_DontUse);
    if(!AI_Items_HealItem(bc))
        return AI_Items_DontUse();
    // LD_B(20);
    // CALL(aEnemyUsedPotion);
    EnemyUsedPotion();
    // JP(mAI_Items_Use);
    return AI_Items_Use();
}
//  Everything up to "End unused" is unused


bool AI_Items_UnusedHealItem(uint8_t bc){
//   //  unreferenced
//  This has similar conditions to .HealItem
    (void)bc;
    return true;
    // CALLFAR(aAICheckEnemyMaxHP);
    // IF_C goto dont_use;
    // PUSH_BC;
    // LD_DE(wEnemyMonMaxHP + 1);
    // LD_HL(wEnemyMonHP + 1);
    // LD_A_de;
    // SUB_A_hl;
    // IF_Z goto check_40_percent;
    // DEC_HL;
    // DEC_DE;
    // LD_C_A;
    // SBC_A_hl;
    // AND_A_A;
    // IF_NZ goto check_40_percent;
    // LD_A_C;
    // CP_A_B;
    // JP_C (mAI_Items_check_50_percent);
    // CALLFAR(aAICheckEnemyQuarterHP);
    // IF_C goto check_40_percent;

// check_50_percent:
    // POP_BC;
    // LD_A_bc;
    // BIT_A(UNKNOWN_USE_F);
    // JP_Z (mAI_Items_Use);
    // CALL(aRandom);
    // CP_A(50 percent + 1);
    // JP_C (mAI_Items_Use);

// dont_use:
    // JP(mAI_Items_DontUse);

// check_40_percent:
    // POP_BC;
    // LD_A_bc;
    // BIT_A(UNKNOWN_USE_F);
    // JP_Z (mAI_Items_DontUse);
    // CALL(aRandom);
    // CP_A(39 percent + 1);
    // JP_C (mAI_Items_Use);
    // JP(mAI_Items_DontUse);
}
//  End unused


static bool AI_Items_XAccuracy(uint8_t bc){
    // CALL(aAI_Items_XItem);
    // JP_C (mAI_Items_DontUse);
    if(!AI_Items_XItem(bc))
        return AI_Items_DontUse();
    // CALL(aEnemyUsedXAccuracy);
    EnemyUsedXAccuracy();
    // JP(mAI_Items_Use);
    return AI_Items_Use();
}

static bool AI_Items_GuardSpec(uint8_t bc){
    // CALL(aAI_Items_XItem);
    // JP_C (mAI_Items_DontUse);
    if(!AI_Items_XItem(bc))
        return AI_Items_DontUse();
    // CALL(aEnemyUsedGuardSpec);
    EnemyUsedGuardSpec();
    // JP(mAI_Items_Use);
    return AI_Items_Use();
}

static bool AI_Items_DireHit(uint8_t bc){
    // CALL(aAI_Items_XItem);
    // JP_C (mAI_Items_DontUse);
    if(!AI_Items_XItem(bc))
        return AI_Items_DontUse();
    // CALL(aEnemyUsedDireHit);
    EnemyUsedDireHit();
    // JP(mAI_Items_Use);
    return AI_Items_Use();
}

static bool AI_Items_XAttack(uint8_t bc){
    // CALL(aAI_Items_XItem);
    // JP_C (mAI_Items_DontUse);
    if(!AI_Items_XItem(bc))
        return AI_Items_DontUse();
    // CALL(aEnemyUsedXAttack);
    EnemyUsedXAttack();
    // JP(mAI_Items_Use);
    return AI_Items_Use();
}

static bool AI_Items_XDefend(uint8_t bc){
    // CALL(aAI_Items_XItem);
    // JP_C (mAI_Items_DontUse);
    if(!AI_Items_XItem(bc))
        return AI_Items_DontUse();
    // CALL(aEnemyUsedXDefend);
    EnemyUsedXDefend();
    // JP(mAI_Items_Use);
    return AI_Items_Use();
}

static bool AI_Items_XSpeed(uint8_t bc){
    // CALL(aAI_Items_XItem);
    // JP_C (mAI_Items_DontUse);
    if(!AI_Items_XItem(bc))
        return AI_Items_DontUse();
    // CALL(aEnemyUsedXSpeed);
    EnemyUsedXSpeed();
    // JP(mAI_Items_Use);
    return AI_Items_Use();
}

static bool AI_Items_XSpecial(uint8_t bc){
    // CALL(aAI_Items_XItem);
    // JP_C (mAI_Items_DontUse);
    if(!AI_Items_XItem(bc))
        return AI_Items_DontUse();
    // CALL(aEnemyUsedXSpecial);
    EnemyUsedXSpecial();
    // JP(mAI_Items_Use);
    return AI_Items_Use();
}

struct ItemFunc {
    item_t item;
    bool (*func)(uint8_t);
};

static const struct ItemFunc AI_Items[] = {
    {FULL_RESTORE,  AI_Items_FullRestore},
    {MAX_POTION,    AI_Items_MaxPotion},
    {HYPER_POTION,  AI_Items_HyperPotion},
    {SUPER_POTION,  AI_Items_SuperPotion},
    {POTION,        AI_Items_Potion},
    {X_ACCURACY,    AI_Items_XAccuracy},
    {FULL_HEAL,     AI_Items_FullHeal},
    {GUARD_SPEC,    AI_Items_GuardSpec},
    {DIRE_HIT,      AI_Items_DireHit},
    {X_ATTACK,      AI_Items_XAttack},
    {X_DEFEND,      AI_Items_XDefend},
    {X_SPEED,       AI_Items_XSpeed},
    {X_SPECIAL,     AI_Items_XSpecial},
    //db ['-1'];  // end
    {NO_ITEM, NULL},
};

static bool AI_TryItem_IsHighestLevel(void){
    // LD_A_addr(wOTPartyCount);
    // LD_D_A;
    uint8_t d = wram->wOTPartyCount;
    // LD_E(0);
    uint8_t e = 0;
    // LD_HL(wOTPartyMon1Level);
    const struct PartyMon* hl = wram->wOTPartyMon;
    // LD_BC(PARTYMON_STRUCT_LENGTH);

    do {
    // next:
        // LD_A_hl;
        // CP_A_E;
        // IF_C goto ok;
        // LD_E_A;
        if(hl->mon.level > e)
            e = hl->mon.level;

    // ok:
        // ADD_HL_BC;
        hl++;
        // DEC_D;
        // IF_NZ goto next;
    } while(--d != 0);

    // LD_A_addr(wCurOTMon);
    // LD_HL(wOTPartyMon1Level);
    // CALL(aAddNTimes);
    // LD_A_hl;
    // CP_A_E;
    // IF_NC goto yes;
    if(wram->wOTPartyMon[wram->wCurOTMon].mon.level >= e) {
    // yes:
        // SCF;
        // RET;
        return true;
    }

// no:
//   //  unreferenced
    // AND_A_A;
    // RET;
    return false;
}

bool AI_TryItem(void){
// items are not allowed in the Battle Tower
    // LD_A_addr(wInBattleTowerBattle);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wInBattleTowerBattle)
        return false;

    // LD_A_addr(wEnemyTrainerItem1);
    // LD_B_A;
    // LD_A_addr(wEnemyTrainerItem2);
    // OR_A_B;
    // RET_Z ;
    if(wram->wEnemyTrainerItem1 == NO_ITEM && wram->wEnemyTrainerItem2 == NO_ITEM)
        return false;

    // CALL(aAI_TryItem_IsHighestLevel);
    // RET_NC ;
    if(!AI_TryItem_IsHighestLevel())
        return false;

    // LD_A_addr(wTrainerClass);
    // DEC_A;
    // LD_HL(mTrainerClassAttributes + TRNATTR_AI_ITEM_SWITCH);
    // LD_BC(NUM_TRAINER_ATTRIBUTES);
    // CALL(aAddNTimes);
    // LD_B_H;
    // LD_C_L;
    uint8_t attr = TrainerClassAttributes[wram->wTrainerClass].aiItemSwitch;
    // LD_HL(mAI_Items);
    const struct ItemFunc* hl = AI_Items;
    // LD_DE(wEnemyTrainerItem1);
    item_t* de = &wram->wEnemyTrainerItem1;

    while(hl->item != NO_ITEM) {
    // loop:
        // LD_A_hl;
        // AND_A_A;
        // INC_A;
        // RET_Z ;

        // LD_A_de;
        // CP_A_hl;
        // IF_Z goto has_item;
        // INC_DE;
        // LD_A_de;
        // CP_A_hl;
        // IF_Z goto has_item;
        if(de[0] == hl->item || de[1] == hl->item) {
            if(*de != hl->item && de[1] == hl->item)
                de++;
        // has_item:
            // INC_HL;

            // PUSH_HL;
            // PUSH_DE;
            // LD_DE(mAI_TryItem_callback);
            // PUSH_DE;
            // LD_A_hli;
            // LD_H_hl;
            // LD_L_A;
            // JP_hl;
            // CALL_hl;
            bool doUse = hl->func(attr);

        // callback:
            // POP_DE;
            // POP_HL;

            // INC_HL;
            // INC_HL;
            // IF_C goto loop;
            if(!doUse) {
                hl++;
                continue;
            }

        //  used item
            // XOR_A_A;
            // LD_de_A;
            *de = NO_ITEM;
            // INC_A;
            // LD_addr_A(wEnemyGoesFirst);
            wram->wEnemyGoesFirst = TRUE;

            // LD_HL(wEnemySubStatus3);
            // RES_hl(SUBSTATUS_BIDE);
            bit_reset(wram->wEnemySubStatus3, SUBSTATUS_BIDE);

            // XOR_A_A;
            // LD_addr_A(wEnemyFuryCutterCount);
            wram->wEnemyFuryCutterCount = 0;
            // LD_addr_A(wEnemyProtectCount);
            wram->wEnemyProtectCount = 0;
            // LD_addr_A(wEnemyRageCounter);
            wram->wEnemyRageCounter = 0;

            // LD_HL(wEnemySubStatus4);
            // RES_hl(SUBSTATUS_RAGE);
            bit_reset(wram->wEnemySubStatus4, SUBSTATUS_RAGE);

            // XOR_A_A;
            // LD_addr_A(wLastEnemyCounterMove);
            wram->wLastEnemyCounterMove = NO_MOVE;

            // SCF;
            // RET;
            return true;
        }

        // DEC_DE;
        // INC_HL;
        // INC_HL;
        // INC_HL;
        hl++;
        // goto loop;
    }
    return false;
}

void AIUpdateHUD(void){
    // CALL(aUpdateEnemyMonInParty);
    UpdateEnemyMonInParty_Conv();
    // FARCALL(aUpdateEnemyHUD);
    UpdateEnemyHUD();
    // LD_A(0x1);
    // LDH_addr_A(hBGMapMode);
    hBGMapMode = 0x1;
    // LD_HL(wEnemyItemState);
    // DEC_hl;
    wram->wEnemyItemState--;
    // SCF;
    // RET;
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
    // CALL(aAIUsedItemSound);
    AIUsedItemSound();
    // CALL(aAI_HealStatus);
    AI_HealStatus();
    // LD_A(FULL_HEAL);
    // JP(mPrintText_UsedItemOn_AND_AIUpdateHUD);
    PrintText_UsedItemOn_AND_AIUpdateHUD(FULL_HEAL);
}

void EnemyUsedMaxPotion(void){
    // LD_A(MAX_POTION);
    // LD_addr_A(wCurEnemyItem);
    wram->wCurEnemyItem = MAX_POTION;
    // JR(mFullRestoreContinue);
    return FullRestoreContinue();
}

void EnemyUsedFullRestore(void){
    // CALL(aAI_HealStatus);
    AI_HealStatus();
    // LD_A(FULL_RESTORE);
    // LD_addr_A(wCurEnemyItem);
    wram->wCurEnemyItem = FULL_RESTORE;
    // LD_HL(wEnemySubStatus3);
    // RES_hl(SUBSTATUS_CONFUSED);
    bit_reset(wram->wEnemySubStatus3, SUBSTATUS_CONFUSED);
    // XOR_A_A;
    // LD_addr_A(wEnemyConfuseCount);
    wram->wEnemyConfuseCount = 0;
    return FullRestoreContinue();
}

void FullRestoreContinue(void){
    // LD_DE(wCurHPAnimOldHP);
    // LD_HL(wEnemyMonHP + 1);
    // LD_A_hld;
    // LD_de_A;
    // INC_DE;
    // LD_A_hl;
    // LD_de_A;
    // INC_DE;
    wram->wCurHPAnimOldHP = ReverseEndian16(wram->wEnemyMon.hp);
    // LD_HL(wEnemyMonMaxHP + 1);
    // LD_A_hld;
    // LD_de_A;
    // INC_DE;
    // LD_addr_A(wCurHPAnimMaxHP);
    // LD_addr_A(wEnemyMonHP + 1);
    // LD_A_hl;
    // LD_de_A;
    // LD_addr_A(wCurHPAnimMaxHP + 1);
    // LD_addr_A(wEnemyMonHP);
    wram->wCurHPAnimMaxHP = wram->wCurHPAnimNewHP = ReverseEndian16(wram->wEnemyMon.maxHP);
    wram->wEnemyMon.hp = wram->wEnemyMon.maxHP;
    // JR(mEnemyPotionFinish);
    EnemyPotionFinish();
}

void EnemyUsedPotion(void){
    // LD_A(POTION);
    // LD_B(20);
    // JR(mEnemyPotionContinue);
    return EnemyPotionContinue(POTION, 20);
}

void EnemyUsedSuperPotion(void){
    // LD_A(SUPER_POTION);
    // LD_B(50);
    // JR(mEnemyPotionContinue);
    return EnemyPotionContinue(SUPER_POTION, 50);
}

void EnemyUsedHyperPotion(void){
    // LD_A(HYPER_POTION);
    // LD_B(200);
    return EnemyPotionContinue(HYPER_POTION, 200);
}

void EnemyPotionContinue(item_t a, uint16_t hp){
    // LD_addr_A(wCurEnemyItem);
    wram->wCurEnemyItem = a;
    // LD_HL(wEnemyMonHP + 1);
    // LD_A_hl;
    uint16_t curhp = ReverseEndian16(wram->wEnemyMon.hp);
    // LD_addr_A(wCurHPAnimOldHP);
    wram->wCurHPAnimOldHP = curhp;
    // ADD_A_B;
    curhp += hp;
    // LD_hld_A;
    // LD_addr_A(wCurHPAnimNewHP);
    wram->wCurHPAnimNewHP = curhp;
    // LD_A_hl;
    // LD_addr_A(wCurHPAnimOldHP + 1);
    // LD_addr_A(wCurHPAnimNewHP + 1);
    // IF_NC goto ok;
    // INC_A;
    // LD_hl_A;
    wram->wEnemyMon.hp = ReverseEndian16(curhp);
    // LD_addr_A(wCurHPAnimNewHP + 1);

// ok:
    // INC_HL;
    // LD_A_hld;
    // LD_B_A;
    // LD_DE(wEnemyMonMaxHP + 1);
    // LD_A_de;
    // DEC_DE;
    // LD_addr_A(wCurHPAnimMaxHP);
    // SUB_A_B;
    // LD_A_hli;
    // LD_B_A;
    // LD_A_de;
    // LD_addr_A(wCurHPAnimMaxHP + 1);
    uint16_t maxhp = ReverseEndian16(wram->wEnemyMon.maxHP);
    wram->wCurHPAnimMaxHP = maxhp;
    // SBC_A_B;
    // JR_NC (mEnemyPotionFinish);
    if(maxhp >= curhp)
        return EnemyPotionFinish();
    // INC_DE;
    // LD_A_de;
    // DEC_DE;
    // LD_hld_A;
    // LD_addr_A(wCurHPAnimNewHP);
    // LD_A_de;
    // LD_hl_A;
    // LD_addr_A(wCurHPAnimNewHP + 1);
    wram->wCurHPAnimNewHP = maxhp;
    wram->wEnemyMon.hp = ReverseEndian16(maxhp);

    return EnemyPotionFinish();
}

void EnemyPotionFinish(void){
    // CALL(aPrintText_UsedItemOn);
    PrintText_UsedItemOn();
    // hlcoord(2, 2, wTilemap);
    // XOR_A_A;
    // LD_addr_A(wWhichHPBar);
    wram->wWhichHPBar = 0x0;
    // CALL(aAIUsedItemSound);
    AIUsedItemSound();
    // PREDEF(pAnimateHPBar);
    AnimateHPBar_Conv(coord(2, 2, wram->wTilemap), 0x0);
    // JP(mAIUpdateHUD);
    return AIUpdateHUD();
}

//  Determine whether the AI can switch based on how many Pokemon are still alive.
//  If it can switch, it will.
bool AI_TrySwitch(void){
    // LD_A_addr(wOTPartyCount);
    // LD_C_A;
    uint8_t c = wram->wOTPartyCount;
    // LD_HL(wOTPartyMon1HP);
    const struct PartyMon* hl = wram->wOTPartyMon;
    // LD_D(0);
    uint8_t d = 0;

    do {
    // SwitchLoop:
        // LD_A_hli;
        // LD_B_A;
        // LD_A_hld;
        // OR_A_B;
        // IF_Z goto fainted;
        if(hl->HP != 0) {
            // INC_D;
            d++;
        }

    // fainted:
        // PUSH_BC;
        // LD_BC(PARTYMON_STRUCT_LENGTH);
        // ADD_HL_BC;
        hl++;
        // POP_BC;
        // DEC_C;
        // IF_NZ goto SwitchLoop;
    } while(--c != 0);

    // LD_A_D;
    // CP_A(2);
    // JP_NC (mAI_Switch);
    if(d >= 2)
        return AI_Switch();
    // AND_A_A;
    // RET;
    return false;
}

bool AI_Switch(void){
    // LD_A(0x1);
    // LD_addr_A(wEnemyIsSwitching);
    wram->wEnemyIsSwitching = 0x1;
    // LD_addr_A(wEnemyGoesFirst);
    wram->wEnemyGoesFirst = TRUE;
    // LD_HL(wEnemySubStatus4);
    // RES_hl(SUBSTATUS_RAGE);
    bit_reset(wram->wEnemySubStatus4, SUBSTATUS_RAGE);
    // XOR_A_A;
    // LDH_addr_A(hBattleTurn);
    hBattleTurn = 0x0;
    // CALLFAR(aPursuitSwitch);
    bool fainted = PursuitSwitch();

    // PUSH_AF;
    // LD_A_addr(wCurOTMon);
    // LD_HL(wOTPartyMon1Status);
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // CALL(aAddNTimes);
    // LD_D_H;
    // LD_E_L;
    // LD_HL(wEnemyMonStatus);
    // LD_BC(MON_MAXHP - MON_STATUS);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(&wram->wOTPartyMon[wram->wCurOTMon].status, wram->wEnemyMon.status, MON_MAXHP - MON_STATUS);
    // POP_AF;

    // IF_C goto skiptext;
    if(!fainted) {
        // LD_HL(mEnemyWithdrewText);
        // CALL(aPrintText);
        PrintText_Conv2(EnemyWithdrewText);
    }

// skiptext:
    // LD_A(1);
    // LD_addr_A(wBattleHasJustStarted);
    wram->wBattleHasJustStarted = 1;
    // CALLFAR(aNewEnemyMonStatus);
    NewEnemyMonStatus_Conv();
    // CALLFAR(aResetEnemyStatLevels);
    ResetEnemyStatLevels_Conv();
    // LD_HL(wPlayerSubStatus1);
    // RES_hl(SUBSTATUS_IN_LOVE);
    bit_reset(wram->wPlayerSubStatus1, SUBSTATUS_IN_LOVE);
    // FARCALL(aEnemySwitch);
    EnemySwitch();
    // FARCALL(aResetBattleParticipants);
    ResetBattleParticipants();
    // XOR_A_A;
    // LD_addr_A(wBattleHasJustStarted);
    wram->wBattleHasJustStarted = 0;
    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wLinkMode != LINK_NULL)
        return false;
    // SCF;
    // RET;
    return true;
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
    // LD_A_addr(wCurOTMon);
    // LD_HL(wOTPartyMon1Status);
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // CALL(aAddNTimes);
    // XOR_A_A;
    // LD_hl_A;
    wram->wOTPartyMon[wram->wCurOTMon].status = 0;
    // LD_addr_A(wEnemyMonStatus);
    wram->wEnemyMon.status[0] = 0;
#if BUGFIX_AI_HEAL_STATUS
    // ld hl, wEnemySubStatus1
    // res SUBSTATUS_NIGHTMARE, [hl]
    bit_reset(wram->wEnemySubStatus1, SUBSTATUS_NIGHTMARE);
    // ld hl, wEnemySubStatus3
    // res SUBSTATUS_CONFUSED, [hl]
    bit_reset(wram->wEnemySubStatus3, SUBSTATUS_CONFUSED);
#endif
// Bug: this should reset SUBSTATUS_NIGHTMARE
// Uncomment the 2 lines below to fix
// ld hl, wEnemySubStatus1
// res SUBSTATUS_NIGHTMARE, [hl]
// Bug: this should reset SUBSTATUS_CONFUSED
// Uncomment the 2 lines below to fix
// ld hl, wEnemySubStatus3
// res SUBSTATUS_CONFUSED, [hl]
    // LD_HL(wEnemySubStatus5);
    // RES_hl(SUBSTATUS_TOXIC);
    bit_reset(wram->wEnemySubStatus5, SUBSTATUS_TOXIC);
    // RET;
}

void EnemyUsedXAccuracy(void){
    // CALL(aAIUsedItemSound);
    AIUsedItemSound();
    // LD_HL(wEnemySubStatus4);
    // SET_hl(SUBSTATUS_X_ACCURACY);
    bit_set(wram->wEnemySubStatus4, SUBSTATUS_X_ACCURACY);
    // LD_A(X_ACCURACY);
    // JP(mPrintText_UsedItemOn_AND_AIUpdateHUD);
    PrintText_UsedItemOn_AND_AIUpdateHUD(X_ACCURACY);
}

void EnemyUsedGuardSpec(void){
    // CALL(aAIUsedItemSound);
    AIUsedItemSound();
    // LD_HL(wEnemySubStatus4);
    // SET_hl(SUBSTATUS_MIST);
    bit_set(wram->wEnemySubStatus4, SUBSTATUS_MIST);
    // LD_A(GUARD_SPEC);
    // JP(mPrintText_UsedItemOn_AND_AIUpdateHUD);
    PrintText_UsedItemOn_AND_AIUpdateHUD(GUARD_SPEC);
}

void EnemyUsedDireHit(void){
    // CALL(aAIUsedItemSound);
    AIUsedItemSound();
    // LD_HL(wEnemySubStatus4);
    // SET_hl(SUBSTATUS_FOCUS_ENERGY);
    bit_set(wram->wEnemySubStatus4, SUBSTATUS_FOCUS_ENERGY);
    // LD_A(DIRE_HIT);
    // JP(mPrintText_UsedItemOn_AND_AIUpdateHUD);
    PrintText_UsedItemOn_AND_AIUpdateHUD(DIRE_HIT);
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
    // LD_B(ATTACK);
    // LD_A(X_ATTACK);
    // JR(mEnemyUsedXItem);
    return EnemyUsedXItem(X_ATTACK, ATTACK);
}

void EnemyUsedXDefend(void){
    // LD_B(DEFENSE);
    // LD_A(X_DEFEND);
    // JR(mEnemyUsedXItem);
    return EnemyUsedXItem(X_DEFEND, DEFENSE);
}

void EnemyUsedXSpeed(void){
    // LD_B(SPEED);
    // LD_A(X_SPEED);
    // JR(mEnemyUsedXItem);
    return EnemyUsedXItem(X_SPEED, SPEED);
}

void EnemyUsedXSpecial(void){
    // LD_B(SP_ATTACK);
    // LD_A(X_SPECIAL);
    return EnemyUsedXItem(X_SPECIAL, SP_ATTACK);
}

//  Parameter
//  a = ITEM_CONSTANT
//  b = BATTLE_CONSTANT (ATTACK, DEFENSE, SPEED, SP_ATTACK, SP_DEFENSE, ACCURACY, EVASION)
void EnemyUsedXItem(item_t item, uint8_t b){
    // LD_addr_A(wCurEnemyItem);
    wram->wCurEnemyItem = item;
    // PUSH_BC;
    // CALL(aPrintText_UsedItemOn);
    PrintText_UsedItemOn();
    // POP_BC;
    // FARCALL(aRaiseStat);
    RaiseStat_Conv(b);
    // JP(mAIUpdateHUD);
    AIUpdateHUD();
}

//  Parameter
//  a = ITEM_CONSTANT
void PrintText_UsedItemOn_AND_AIUpdateHUD(item_t item){
    // LD_addr_A(wCurEnemyItem);
    wram->wCurEnemyItem = item;
    // CALL(aPrintText_UsedItemOn);
    PrintText_UsedItemOn();
    // JP(mAIUpdateHUD);
    return AIUpdateHUD();
}

void PrintText_UsedItemOn(void){
    // LD_A_addr(wCurEnemyItem);
    // LD_addr_A(wNamedObjectIndex);
    // CALL(aGetItemName);
    // LD_HL(wStringBuffer1);
    // LD_DE(wMonOrItemNameBuffer);
    // LD_BC(ITEM_NAME_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(wram->wMonOrItemNameBuffer, GetItemName_Conv2(wram->wCurEnemyItem), ITEM_NAME_LENGTH);
    // LD_HL(mEnemyUsedOnText);
    // JP(mPrintText);
    return PrintText_Conv2(EnemyUsedOnText);
}

const txt_cmd_s EnemyUsedOnText[] = {
    text_far(v_EnemyUsedOnText)
    text_end
};
