#include "../../constants.h"
#include "link_result.h"
#include "../../home/battle.h"

static uint8_t DetermineLinkBattleResult_CountMonsRemaining(const struct PartyMon* hl) {
    // LD_C(0);
    uint8_t c = 0;
    // LD_B(3);
    uint8_t b = 3;
    // LD_DE(PARTYMON_STRUCT_LENGTH - 1);

    do {
    // loop:
        // LD_A_hli;
        // OR_A_hl;
        // IF_NZ goto not_fainted;
        if(hl->HP == 0)
            c++;
        // INC_C;

    // not_fainted:
        // ADD_HL_DE;
        hl++;
        // DEC_B;
        // IF_NZ goto loop;
    } while(--b != 0);
    // RET;
    return c;
}

static bool DetermineLinkBattleResult_CheckFaintedOrFullHealth(const struct PartyMon* mon);

static u8_flag_s DetermineLinkBattleResult_BothSides_CheckNumberMonsAtFullHealth(void){
    // LD_HL(wPartyMon1HP);
    // CALL(aDetermineLinkBattleResult_CheckFaintedOrFullHealth);
    // IF_NZ goto finish;  // we have a pokemon that's neither fainted nor at full health
    if(!DetermineLinkBattleResult_CheckFaintedOrFullHealth(wram->wPartyMon)) {
    // finish:
        // LD_HL(wOTPartyMon1HP);
        // CALL(aDetermineLinkBattleResult_CheckFaintedOrFullHealth);
        // LD_E(0x0);  // drawn
        // RET_NZ ;  // we both have pokemon that are neither fainted nor at full health
        if(!DetermineLinkBattleResult_CheckFaintedOrFullHealth(wram->wOTPartyMon))
            return u8_flag(0x0, false);
        // LD_E(0x2);  // defeat
        // LD_A(0x1);  // not drawn
        // AND_A_A;
        // RET;
        return u8_flag(0x2, false);
    }
    // LD_HL(wOTPartyMon1HP);
    // CALL(aDetermineLinkBattleResult_CheckFaintedOrFullHealth);
    bool z = DetermineLinkBattleResult_CheckFaintedOrFullHealth(wram->wOTPartyMon);
    // LD_E(0x1);  // victory
    // RET;
    return u8_flag(0x1, z);
}

static bool DetermineLinkBattleResult_CheckFaintedOrFullHealth(const struct PartyMon* mon) {
    // LD_D(3);
    uint8_t d = 3;

    do {
    // loop3:
        // LD_A_hli;
        // LD_B_A;
        // LD_A_hli;
        // LD_C_A;
        // OR_A_B;
        // IF_Z goto fainted_or_full_health;
        if(mon->HP != 0) {
            // LD_A_hli;
            // CP_A_B;
            // RET_NZ ;
            // LD_A_hld;
            // CP_A_C;
            // RET_NZ ;
            if(mon->HP != mon->maxHP)
                return false;
        }

    // fainted_or_full_health:
        // PUSH_DE;
        // LD_DE(PARTYMON_STRUCT_LENGTH - 2);
        // ADD_HL_DE;
        // POP_DE;
        // DEC_D;
        // IF_NZ goto loop3;
    } while(--d != 0);
    // RET;
    return true;
}

static uint16_t DetermineLinkBattleResult_CalcPercentHPRemaining(const struct PartyMon* mon){
    // LD_DE(0);
    // LD_C(0x3);
    uint8_t c = 0x3;
    uint16_t de = 0;

    do {
    // loop2:
        // LD_A_hli;
        // OR_A_hl;
        // IF_Z goto next;
        if(mon->HP == 0)
            continue;
        // DEC_HL;
        // XOR_A_A;
        // LDH_addr_A(hDividend + 0);
        // LD_A_hli;
        // LDH_addr_A(hDividend + 1);
        // LD_A_hli;
        // LDH_addr_A(hDividend + 2);
        // XOR_A_A;
        // LDH_addr_A(hDividend + 3);
        // LD_A_hli;
        // LD_B_A;
        // LD_A_hld;
        // SRL_B;
        // RR_A;
        // SRL_B;
        // RR_A;
        // LDH_addr_A(hDivisor);
        // LD_B(0x4);
        // CALL(aDivide);
        // LDH_A_addr(hQuotient + 3);
        // ADD_A_E;
        // LD_E_A;
        // LDH_A_addr(hQuotient + 2);
        // ADC_A_D;
        // LD_D_A;
        // DEC_HL;
        de += (uint16_t)(BigEndianToNative16(mon->HP) / (BigEndianToNative16(mon->maxHP) >> 2));

    // next:
        // PUSH_DE;
        // LD_DE(0x2f);
        // ADD_HL_DE;
        // POP_DE;
        // DEC_C;
        // IF_NZ goto loop2;
    } while(mon++, --c != 0);
    // RET;
    return de;
}

void DetermineLinkBattleResult(void){
    // FARCALL(aUpdateEnemyMonInParty);
    UpdateEnemyMonInParty();
    // LD_HL(wPartyMon1HP);
    // CALL(aDetermineLinkBattleResult_CountMonsRemaining);
    uint8_t pmons = DetermineLinkBattleResult_CountMonsRemaining(wram->wPartyMon);
    // PUSH_BC;
    // LD_HL(wOTPartyMon1HP);
    // CALL(aDetermineLinkBattleResult_CountMonsRemaining);
    uint8_t otmons = DetermineLinkBattleResult_CountMonsRemaining(wram->wOTPartyMon);
    // LD_A_C;
    // POP_BC;
    // CP_A_C;
    // IF_Z goto even_number_of_mons_remaining;
    if(pmons == otmons) {
    // even_number_of_mons_remaining:
        // CALL(aDetermineLinkBattleResult_BothSides_CheckNumberMonsAtFullHealth);
        u8_flag_s result = DetermineLinkBattleResult_BothSides_CheckNumberMonsAtFullHealth();
        // IF_Z goto drawn;
        if(result.flag)
            goto drawn;
        // LD_A_E;
        // CP_A(0x1);
        // IF_Z goto victory;
        if(result.a == 0x1)
            goto victory;
        // CP_A(0x2);
        // IF_Z goto defeat;
        if(result.a == 0x2)
            goto defeat;
        // LD_HL(wPartyMon1HP);
        // CALL(aDetermineLinkBattleResult_CalcPercentHPRemaining);
        // PUSH_DE;
        uint16_t pmonHP = DetermineLinkBattleResult_CalcPercentHPRemaining(wram->wPartyMon);
        // LD_HL(wOTPartyMon1HP);
        // CALL(aDetermineLinkBattleResult_CalcPercentHPRemaining);
        uint16_t otmonHP = DetermineLinkBattleResult_CalcPercentHPRemaining(wram->wOTPartyMon);
        // POP_HL;
        // LD_A_D;
        // CP_A_H;
        // IF_C goto victory;
        if(otmonHP < pmonHP)
            goto victory;
        // IF_Z goto compare_lo;
        // goto defeat;

    // compare_lo:
        // LD_A_E;
        // CP_A_L;
        // IF_Z goto drawn;
        if(otmonHP == pmonHP)
            goto drawn;
        // IF_NC goto defeat;
        if(otmonHP > pmonHP)
            goto defeat;
    }
    // IF_C goto defeat;
    if(pmons < otmons) {
        goto defeat;
    }
    // goto victory;
    else {
        goto victory;
    }


victory:
    // LD_A_addr(wBattleResult);
    // AND_A(0xf0);
    // LD_addr_A(wBattleResult);  // WIN
    wram->wBattleResult = (wram->wBattleResult & 0xf0) | WIN;
    // RET;
    return;

defeat:
    // LD_A_addr(wBattleResult);
    // AND_A(0xf0);
    // ADD_A(LOSE);
    // LD_addr_A(wBattleResult);
    wram->wBattleResult = (wram->wBattleResult & 0xf0) | LOSE;
    // RET;
    return;

drawn:
    // LD_A_addr(wBattleResult);
    // AND_A(0xf0);
    // ADD_A(DRAW);
    // LD_addr_A(wBattleResult);
    wram->wBattleResult = (wram->wBattleResult & 0xf0) | DRAW;
    // RET;
    return;
}
