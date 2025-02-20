#include "../../constants.h"
#include "hidden_power.h"
#include "effect_commands.h"
#include "../../home/battle_vars.h"

uint8_t HiddenPowerDamage(void){
//  Override Hidden Power's type and power based on the user's DVs.

    // LD_HL(wBattleMonDVs);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto got_dvs;
    // LD_HL(wEnemyMonDVs);
    uint16_t dvs = (hBattleTurn == 0)? wram->wBattleMon.dvs: wram->wEnemyMon.dvs;

// got_dvs:

//  Power:

//  Take the top bit from each stat

// Attack
    // LD_A_hl;
    // SWAP_A;
    // AND_A(0b1000);
    uint16_t a = (LOW(dvs) >> 4) & 0b1000;

// Defense
    // LD_B_A;
    // LD_A_hli;
    // AND_A(0b1000);
    // SRL_A;
    // OR_A_B;
    a |= (LOW(dvs) & 0b1000) >> 1;

// Speed
    // LD_B_A;
    // LD_A_hl;
    // SWAP_A;
    // AND_A(0b1000);
    // SRL_A;
    // SRL_A;
    // OR_A_B;
    a |= ((HIGH(dvs) >> 4) & 0b1000) >> 2;

// Special
    // LD_B_A;
    // LD_A_hl;
    // AND_A(0b1000);
    // SRL_A;
    // SRL_A;
    // SRL_A;
    // OR_A_B;
    a |= (HIGH(dvs) & 0b1000) >> 3;

//  Multiply by 5
    // LD_B_A;
    // ADD_A_A;
    // ADD_A_A;
    // ADD_A_B;
    a *= 5;

//  Add Special & 3
    // LD_B_A;
    // LD_A_hld;
    // AND_A(0b0011);
    // ADD_A_B;
    a += HIGH(dvs) & 3;

//  Divide by 2 and add 30 + 1
    // SRL_A;
    // ADD_A(30);
    // INC_A;
    a = (a >> 1) + 31;

    // LD_D_A;
    uint8_t d = (uint8_t)a;

//  Type:

// Def & 3
    // LD_A_hl;
    // AND_A(0b0011);
    // LD_B_A;

// + (Atk & 3) << 2
    // LD_A_hl;
    // AND_A(0b0011 << 4);
    // SWAP_A;
    // ADD_A_A;
    // ADD_A_A;
    // OR_A_B;
    a = (LOW(dvs) & 3) + (((LOW(dvs) >> 4) & 3) << 2);

//  Skip Normal
    // INC_A;
    a++;

//  Skip Bird
    // CP_A(BIRD);
    // IF_C goto done;
    if(a >= BIRD) {
        // INC_A;
        a++;

    //  Skip unused types
        // CP_A(UNUSED_TYPES);
        // IF_C goto done;
        if(a >= UNUSED_TYPES) {
            // ADD_A(UNUSED_TYPES_END - UNUSED_TYPES);
            a += UNUSED_TYPES_END - UNUSED_TYPES;
        }
    }

// done:

//  Overwrite the current move type.
    // PUSH_AF;
    // LD_A(BATTLE_VARS_MOVE_TYPE);
    // CALL(aGetBattleVarAddr);
    // POP_AF;
    // LD_hl_A;
    *GetBattleVarAddr_Conv(BATTLE_VARS_MOVE_TYPE) = a;

//  Get the rest of the damage formula variables
//  based on the new type, but keep base power.
    // LD_A_D;
    // PUSH_AF;
    // FARCALL(aBattleCommand_DamageStats);  // damagestats
    BattleCommand_DamageStats();
    // POP_AF;
    // LD_D_A;
    return d;
    // RET;
}
