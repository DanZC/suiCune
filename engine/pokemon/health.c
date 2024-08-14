#include "../../constants.h"
#include "health.h"
#include "../items/item_effects.h"
#include "../battle/anim_hp_bar.h"
#include "../../home/tilemap.h"

void HealParty(void){
    return HealParty_Conv();
    XOR_A_A;
    LD_addr_A(wCurPartyMon);
    LD_HL(wPartySpecies);

loop:
    LD_A_hli;
    CP_A(-1);
    IF_Z goto done;
    CP_A(EGG);
    IF_Z goto next;

    PUSH_HL;
    CALL(aHealPartyMon);
    POP_HL;


next:
    LD_A_addr(wCurPartyMon);
    INC_A;
    LD_addr_A(wCurPartyMon);
    goto loop;


done:
    RET;

}

void HealParty_Conv(void){
    // XOR_A_A;
    // LD_addr_A(wCurPartyMon);
    wram->wCurPartyMon = 0;
    // LD_HL(wPartySpecies);

    for(size_t i = 0; i < 6 && wram->wPartySpecies[i] != (species_t)-1; i++) {
    // loop:
        // LD_A_hli;
        // CP_A(-1);
        // IF_Z goto done;
        // CP_A(EGG);
        // IF_Z goto next;
        if(wram->wPartySpecies[i] == EGG)
            continue;

        // PUSH_HL;
        // CALL(aHealPartyMon);
        HealPartyMon_Conv(wram->wPartyMon + i);
        // POP_HL;


    // next:
        // LD_A_addr(wCurPartyMon);
        // INC_A;
        // LD_addr_A(wCurPartyMon);
        // goto loop;
    }

// done:
    // RET;

}

void HealPartyMon(void){
    LD_A(MON_SPECIES);
    CALL(aGetPartyParamLocation);
    LD_D_H;
    LD_E_L;

    LD_HL(MON_STATUS);
    ADD_HL_DE;
    XOR_A_A;
    LD_hli_A;
    LD_hl_A;

    LD_HL(MON_MAXHP);
    ADD_HL_DE;

// bc = MON_HP
    LD_B_H;
    LD_C_L;
    DEC_BC;
    DEC_BC;

    LD_A_hli;
    LD_bc_A;
    INC_BC;
    LD_A_hl;
    LD_bc_A;

    FARCALL(aRestoreAllPP);
    RET;

}

void HealPartyMon_Conv(struct PartyMon* pmon){
    // LD_A(MON_SPECIES);
    // CALL(aGetPartyParamLocation);
    // LD_D_H;
    // LD_E_L;

    // LD_HL(MON_STATUS);
    // ADD_HL_DE;
    // XOR_A_A;
    // LD_hli_A;
    pmon->status = 0;
    // LD_hl_A;
    pmon->unused = 0;

    // LD_HL(MON_MAXHP);
    // ADD_HL_DE;

// bc = MON_HP
    // LD_B_H;
    // LD_C_L;
    // DEC_BC;
    // DEC_BC;

    // LD_A_hli;
    // LD_bc_A;
    // INC_BC;
    // LD_A_hl;
    // LD_bc_A;
    pmon->HP = pmon->maxHP;

    // FARCALL(aRestoreAllPP);
    // RET;
    RestoreAllPP_Conv(pmon);
}

void ComputeHPBarPixels(void){
//  e = bc * (6 * 8) / de
    LD_A_B;
    OR_A_C;
    IF_Z goto zero;
    PUSH_HL;
    XOR_A_A;
    LDH_addr_A(hMultiplicand + 0);
    LD_A_B;
    LDH_addr_A(hMultiplicand + 1);
    LD_A_C;
    LDH_addr_A(hMultiplicand + 2);
    LD_A(6 * 8);
    LDH_addr_A(hMultiplier);
    CALL(aMultiply);
// We need de to be under 256 because hDivisor is only 1 byte.
    LD_A_D;
    AND_A_A;
    IF_Z goto divide;
// divide de and hProduct by 4
    SRL_D;
    RR_E;
    SRL_D;
    RR_E;
    LDH_A_addr(hProduct + 2);
    LD_B_A;
    LDH_A_addr(hProduct + 3);
    SRL_B;
    RR_A;
    SRL_B;
    RR_A;
    LDH_addr_A(hDividend + 3);
    LD_A_B;
    LDH_addr_A(hDividend + 2);

divide:
    LD_A_E;
    LDH_addr_A(hDivisor);
    LD_B(4);
    CALL(aDivide);
    LDH_A_addr(hQuotient + 3);
    LD_E_A;
    POP_HL;
    AND_A_A;
    RET_NZ ;
    LD_E(1);
    RET;


zero:
    LD_E(0);
    RET;

}

//  e = bc * (6 * 8) / de
uint8_t ComputeHPBarPixels_Conv(uint16_t bc, uint16_t de){
    // LD_A_B;
    // OR_A_C;
    // IF_Z goto zero;
    if(bc == 0)
        return 0;
    // PUSH_HL;
    // XOR_A_A;
    // LDH_addr_A(hMultiplicand + 0);
    // LD_A_B;
    // LDH_addr_A(hMultiplicand + 1);
    // LD_A_C;
    // LDH_addr_A(hMultiplicand + 2);
    // LD_A(6 * 8);
    // LDH_addr_A(hMultiplier);
    // CALL(aMultiply);
// We need de to be under 256 because hDivisor is only 1 byte.
    // LD_A_D;
    // AND_A_A;
    // IF_Z goto divide;
// divide de and hProduct by 4
    // SRL_D;
    // RR_E;
    // SRL_D;
    // RR_E;
    // LDH_A_addr(hProduct + 2);
    // LD_B_A;
    // LDH_A_addr(hProduct + 3);
    // SRL_B;
    // RR_A;
    // SRL_B;
    // RR_A;
    // LDH_addr_A(hDividend + 3);
    // LD_A_B;
    // LDH_addr_A(hDividend + 2);

// divide:
    // LD_A_E;
    // LDH_addr_A(hDivisor);
    // LD_B(4);
    // CALL(aDivide);
    // LDH_A_addr(hQuotient + 3);
    // LD_E_A;
    // POP_HL;
    // AND_A_A;
    // RET_NZ ;
    // LD_E(1);
    // RET;
    return (uint8_t)((bc * (6 * 8)) / de);

// zero:
    // LD_E(0);
    // RET;
}

void AnimateHPBar(void){
    CALL(aWaitBGMap);
    CALL(av_AnimateHPBar);
    CALL(aWaitBGMap);
    RET;

}

void AnimateHPBar_Conv(tile_t* hl, uint8_t which){
    wram->wWhichHPBar = which;

    // struct cpu_registers_s regs = gb.cpu_reg;
    // regs.hl = RAMAddrToGB(hl);
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // CALL(av_AnimateHPBar);
    v_AnimateHPBar(hl);
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // RET;
}
