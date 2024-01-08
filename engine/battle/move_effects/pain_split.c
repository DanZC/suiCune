#include "../../../constants.h"
#include "pain_split.h"
#include "../effect_commands.h"
#include "../update_battle_huds.h"
#include "../../pokemon/health.h"
#include "../../../home/battle.h"
#include "../../../data/text/battle.h"

static void BattleCommand_PainSplit_EnemyShareHP(struct BattleMon* player);

static void BattleCommand_PainSplit_PlayerShareHP(struct BattleMon* player, struct BattleMon* enemy) {
    // LD_A_hld;
    // LD_addr_A(wHPBuffer1);
    // LD_A_hld;
    // LD_addr_A(wHPBuffer1 + 1);
    wram->wHPBuffer1 = ReverseEndian16(player->maxHP);
    // LD_A_hld;
    // LD_B_A;
    // LD_addr_A(wHPBuffer2);
    // LD_A_hl;
    // LD_addr_A(wHPBuffer2 + 1);
    wram->wHPBuffer2 = ReverseEndian16(player->hp);
    // DEC_DE;
    // DEC_DE;
    // LD_A_de;
    // DEC_DE;
    // ADD_A_B;
    // LD_addr_A(wCurDamage + 1);
    // LD_B_hl;
    // LD_A_de;
    // ADC_A_B;
    // SRL_A;
    // LD_addr_A(wCurDamage);
    // LD_A_addr(wCurDamage + 1);
    // RR_A;
    // LD_addr_A(wCurDamage + 1);
    wram->wCurDamage = ReverseEndian16((ReverseEndian16(enemy->hp) + wram->wHPBuffer2) >> 1);
    // INC_HL;
    // INC_HL;
    // INC_HL;
    // INC_DE;
    // INC_DE;
    // INC_DE;
    return BattleCommand_PainSplit_EnemyShareHP(player);
}

static void BattleCommand_PainSplit_EnemyShareHP(struct BattleMon* player) {
// EnemyShareHP:
    // LD_C_hl;
    // DEC_HL;
    // LD_A_addr(wCurDamage + 1);
    // SUB_A_C;
    // LD_B_hl;
    // DEC_HL;
    uint16_t bc = ReverseEndian16(player->maxHP);
    // LD_A_addr(wCurDamage);
    // SBC_A_B;
    // IF_NC goto skip;

    if(ReverseEndian16(wram->wCurDamage) < bc) {
        // LD_A_addr(wCurDamage);
        // LD_B_A;
        // LD_A_addr(wCurDamage + 1);
        // LD_C_A;
        bc = ReverseEndian16(wram->wCurDamage);
    }
// skip:
    // LD_A_C;
    // LD_hld_A;
    // LD_addr_A(wHPBuffer3);
    // LD_A_B;
    // LD_hli_A;
    // LD_addr_A(wHPBuffer3 + 1);
    wram->wHPBuffer3 = bc;
    player->hp = ReverseEndian16(bc);
    // RET;
}

void BattleCommand_PainSplit(void){
//  painsplit

    // LD_A_addr(wAttackMissed);
    // AND_A_A;
    // JP_NZ (mBattleCommand_PainSplit_ButItFailed);
    // CALL(aCheckSubstituteOpp);
    // JP_NZ (mBattleCommand_PainSplit_ButItFailed);
    if(wram->wAttackMissed || CheckSubstituteOpp_Conv()) {
    // ButItFailed:
        // JP(mPrintDidntAffect2);
        return PrintDidntAffect2();
    }
    // CALL(aAnimateCurrentMove);
    AnimateCurrentMove();
    // LD_HL(wBattleMonMaxHP + 1);
    // LD_DE(wEnemyMonMaxHP + 1);
    // CALL(aBattleCommand_PainSplit_PlayerShareHP);
    BattleCommand_PainSplit_PlayerShareHP(&wram->wBattleMon, &wram->wEnemyMon);
    // LD_A(0x1);
    // LD_addr_A(wWhichHPBar);
    // hlcoord(10, 9, wTilemap);
    // PREDEF(pAnimateHPBar);
    AnimateHPBar_Conv(coord(10, 9, wram->wTilemap), 0x1);
    // LD_HL(wEnemyMonHP);
    // LD_A_hli;
    // LD_addr_A(wHPBuffer2 + 1);
    // LD_A_hli;
    // LD_addr_A(wHPBuffer2);
    wram->wHPBuffer2 = ReverseEndian16(wram->wEnemyMon.hp);
    // LD_A_hli;
    // LD_addr_A(wHPBuffer1 + 1);
    // LD_A_hl;
    // LD_addr_A(wHPBuffer1);
    wram->wHPBuffer1 = ReverseEndian16(wram->wEnemyMon.maxHP);
    // CALL(aBattleCommand_PainSplit_EnemyShareHP);
    BattleCommand_PainSplit_EnemyShareHP(&wram->wBattleMon);
    // XOR_A_A;
    // LD_addr_A(wWhichHPBar);
    // CALL(aResetDamage);
    ResetDamage_Conv();
    // hlcoord(2, 2, wTilemap);
    // PREDEF(pAnimateHPBar);
    AnimateHPBar_Conv(coord(2, 2, wram->wTilemap), 0x0);
    // FARCALL(av_UpdateBattleHUDs);
    v_UpdateBattleHUDs();

    // LD_HL(mSharedPainText);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox_Conv2(SharedPainText);

}
