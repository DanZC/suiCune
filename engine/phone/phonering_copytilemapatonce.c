#include "../../constants.h"
#include "phonering_copytilemapatonce.h"
#include "../../home/tilemap.h"

static void PhoneRing_CopyTilemapAtOnce_CopyBGMapViaStack(uint16_t sp) {
//  Copy all tiles to vBGMap
    // LD_addr_SP(hSPBuffer);
    // LD_SP_HL;
    // LDH_A_addr(hBGMapAddress + 1);
    // LD_H_A;
    // LD_L(0);
    uint16_t hl = gb_read(hBGMapAddress + 1) << 8;
    // LD_A(SCREEN_HEIGHT);
    // LDH_addr_A(hTilesPerCycle);
    uint8_t a = SCREEN_HEIGHT;
    gb_write(hTilesPerCycle, a);
    // LD_B(1 << 1);  // not in v/hblank
    // LD_C(LOW(rSTAT));

    uint16_t de;


    do {
        for(int rept = 0; rept < SCREEN_WIDTH / 2; rept++){
            // POP_DE;
        //  if in v/hblank, wait until not in v/hblank
            de = gb_read16(sp);
            sp += 2;
            // loop2:
            //     LDH_A_c;
            //     AND_A_B;
            //     // IF_NZ goto loop2;
            //     NOP; NOP;
        //  load vBGMap
            // LD_hl_E;
            // INC_L;
            // LD_hl_D;
            // INC_L;
            gb_write16(hl, de);
            hl += 2;
        }

        // LD_DE(BG_MAP_WIDTH - SCREEN_WIDTH);
        // ADD_HL_DE;
        hl += BG_MAP_WIDTH - SCREEN_WIDTH;
        // LDH_A_addr(hTilesPerCycle);
        // DEC_A;
        // LDH_addr_A(hTilesPerCycle);
        a = gb_read(hTilesPerCycle) - 1;
        gb_write(hTilesPerCycle, a);
        // IF_NZ goto loop;
    } while(a != 0);

    // LDH_A_addr(hSPBuffer);
    // LD_L_A;
    // LDH_A_addr(hSPBuffer + 1);
    // LD_H_A;
    // LD_SP_HL;
    // RET;
}

void PhoneRing_CopyTilemapAtOnce(void){
    PEEK("");
    // LDH_A_addr(hCGB);
    // AND_A_A;
    // JP_Z (mWaitBGMap);
    if(gb_read(hCGB) == 0)
        return WaitBGMap_Conv();
    
    // LD_A_addr(wSpriteUpdatesEnabled);
    // CP_A(0x0);
    // JP_Z (mWaitBGMap);

//  The following is a modified version of _CopyTilemapAtOnce
//  that waits for [rLY] to be LY_VBLANK - 1 instead of $80 - 1.
    // LDH_A_addr(hBGMapMode);
    // PUSH_AF;
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    uint8_t mode_temp = gb_read(hBGMapMode);
    gb_write(hBGMapMode, 0);

    // LDH_A_addr(hMapAnims);
    // PUSH_AF;
    // XOR_A_A;
    // LDH_addr_A(hMapAnims);
    uint8_t anims_temp = gb_read(hMapAnims);
    gb_write(hMapAnims, 0);


// wait:
//     LDH_A_addr(rLY);
//     CP_A(LY_VBLANK - 1);
//     // IF_C goto wait;
//     NOP; NOP;

//     NOP;
    // LD_A(MBANK(avBGMap2));
    // LDH_addr_A(rVBK);
    gb_write(rVBK, MBANK(avBGMap2));

    // hlcoord(0, 0, wAttrmap);
    // CALL(aPhoneRing_CopyTilemapAtOnce_CopyBGMapViaStack);
    PhoneRing_CopyTilemapAtOnce_CopyBGMapViaStack(coord(0, 0, wAttrmap));
    // LD_A(MBANK(avBGMap0));
    // LDH_addr_A(rVBK);
    gb_write(rVBK, MBANK(avBGMap0));
    // hlcoord(0, 0, wTilemap);
    // CALL(aPhoneRing_CopyTilemapAtOnce_CopyBGMapViaStack);
    PhoneRing_CopyTilemapAtOnce_CopyBGMapViaStack(coord(0, 0, wTilemap));


// wait2:
//     LDH_A_addr(rLY);
//     CP_A(LY_VBLANK - 1);
//     // IF_C goto wait2;
//     NOP; NOP;
//     NOP;

    // POP_AF;
    // LDH_addr_A(hMapAnims);
    gb_write(hMapAnims, anims_temp);
    // POP_AF;
    // LDH_addr_A(hBGMapMode);
    gb_write(hBGMapMode, mode_temp);
    RET;


// CopyBGMapViaStack:
// //  Copy all tiles to vBGMap
//     LD_addr_SP(hSPBuffer);
//     LD_SP_HL;
//     LDH_A_addr(hBGMapAddress + 1);
//     LD_H_A;
//     LD_L(0);
//     LD_A(SCREEN_HEIGHT);
//     LDH_addr_A(hTilesPerCycle);
//     LD_B(1 << 1);  // not in v/hblank
//     LD_C(LOW(rSTAT));


// loop:
//     for(int rept = 0; rept < SCREEN_WIDTH / 2; rept++){
//     POP_DE;
// //  if in v/hblank, wait until not in v/hblank

//     loop2:
//         LDH_A_c;
//         AND_A_B;
//         // IF_NZ goto loop2;
//         NOP; NOP;
// //  load vBGMap
//     LD_hl_E;
//     INC_L;
//     LD_hl_D;
//     INC_L;
//     }

//     LD_DE(BG_MAP_WIDTH - SCREEN_WIDTH);
//     ADD_HL_DE;
//     LDH_A_addr(hTilesPerCycle);
//     DEC_A;
//     LDH_addr_A(hTilesPerCycle);
//     IF_NZ goto loop;

//     LDH_A_addr(hSPBuffer);
//     LD_L_A;
//     LDH_A_addr(hSPBuffer + 1);
//     LD_H_A;
//     LD_SP_HL;
//     RET;

}
