#include "../../constants.h"
#include "phonering_copytilemapatonce.h"
#include "../../home/tilemap.h"

static void PhoneRing_CopyTilemapAtOnce_CopyBGMapViaStack(tile_t* hl, const tile_t* sp) {
//  Copy all tiles to vBGMap
    // LD_addr_SP(hSPBuffer);
    // LD_SP_HL;
    // LDH_A_addr(hBGMapAddress + 1);
    // LD_H_A;
    // LD_L(0);
    // LD_A(SCREEN_HEIGHT);
    // LDH_addr_A(hTilesPerCycle);
    hram->hTilesPerCycle = SCREEN_HEIGHT;
    // LD_B(1 << 1);  // not in v/hblank
    // LD_C(LOW(rSTAT));

    // uint16_t de;


    do {
        for(int rept = 0; rept < SCREEN_WIDTH / 2; rept++){
            // POP_DE;
        //  if in v/hblank, wait until not in v/hblank
            *(hl++) = *(sp++);
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
            *(hl++) = *(sp++);
        }

        // LD_DE(BG_MAP_WIDTH - SCREEN_WIDTH);
        // ADD_HL_DE;
        hl += BG_MAP_WIDTH - SCREEN_WIDTH;
        // LDH_A_addr(hTilesPerCycle);
        // DEC_A;
        // LDH_addr_A(hTilesPerCycle);
        // IF_NZ goto loop;
    } while(--hram->hTilesPerCycle != 0);

    // LDH_A_addr(hSPBuffer);
    // LD_L_A;
    // LDH_A_addr(hSPBuffer + 1);
    // LD_H_A;
    // LD_SP_HL;
    // RET;
}

void PhoneRing_CopyTilemapAtOnce_Conv(void){
    // LDH_A_addr(hCGB);
    // AND_A_A;
    // JP_Z (mWaitBGMap);
    if(hram->hCGB == 0)
        return WaitBGMap_Conv();
    
    // LD_A_addr(wSpriteUpdatesEnabled);
    // CP_A(0x0);
    // JP_Z (mWaitBGMap);
    if(wram->wSpriteUpdatesEnabled == 0x0)
        return WaitBGMap_Conv();

//  The following is a modified version of _CopyTilemapAtOnce
//  that waits for [rLY] to be LY_VBLANK - 1 instead of $80 - 1.
    // LDH_A_addr(hBGMapMode);
    // PUSH_AF;
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    uint8_t mode_temp = hram->hBGMapMode;
    hram->hBGMapMode = BGMAPMODE_NONE;

    // LDH_A_addr(hMapAnims);
    // PUSH_AF;
    // XOR_A_A;
    // LDH_addr_A(hMapAnims);
    uint8_t anims_temp = hram->hMapAnims;
    hram->hMapAnims = 0;


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
    //  Uncommenting the line below causes weird color issues.
    PhoneRing_CopyTilemapAtOnce_CopyBGMapViaStack(GBToRAMAddr(hram->hBGMapAddress & 0xff00), coord(0, 0, wram->wAttrmap));
    // LD_A(MBANK(avBGMap0));
    // LDH_addr_A(rVBK);
    gb_write(rVBK, MBANK(avBGMap0));
    // hlcoord(0, 0, wTilemap);
    // CALL(aPhoneRing_CopyTilemapAtOnce_CopyBGMapViaStack);
    PhoneRing_CopyTilemapAtOnce_CopyBGMapViaStack(GBToRAMAddr(hram->hBGMapAddress & 0xff00), coord(0, 0, wram->wTilemap));


// wait2:
//     LDH_A_addr(rLY);
//     CP_A(LY_VBLANK - 1);
//     // IF_C goto wait2;
//     NOP; NOP;
//     NOP;

    // POP_AF;
    // LDH_addr_A(hMapAnims);
    hram->hMapAnims = anims_temp;
    // POP_AF;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = mode_temp;
    // RET;


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

void PhoneRing_CopyTilemapAtOnce(void) {
    PEEK("");
    PhoneRing_CopyTilemapAtOnce_Conv();
    RET;
}
