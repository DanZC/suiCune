#include "../constants.h"
#include "video.h"

//  Functions dealing with VRAM.

void DMATransfer(void) {
    //  Return carry if the transfer is completed.

    LDH_A_addr(hDMATransfer);
    AND_A_A;
    RET_Z;

    //  Start transfer
    LDH_addr_A(rHDMA5);

    //  Execution is halted until the transfer is complete.

    XOR_A_A;
    LDH_addr_A(hDMATransfer);
    SCF;
    RET;
}

//  Return true if the transfer is completed.
bool DMATransfer_Conv(void) {
    // LDH_A_addr(hDMATransfer);
    // AND_A_A;
    // RET_Z;
    uint8_t value = gb_read(hDMATransfer);
    if(value == 0) 
        return false;

    //  Start transfer
    // LDH_addr_A(rHDMA5);
    gb_write(rHDMA5, value);

    //  Execution is halted until the transfer is complete.

    // XOR_A_A;
    // LDH_addr_A(hDMATransfer);
    gb_write(hDMATransfer, 0);
    // SCF;
    // RET;
    return true;
}

void UpdateBGMapBuffer(void) {
    //  Copy [hBGMapTileCount] 16x8 tiles from wBGMapBuffer
    //  to bg map addresses in wBGMapBufferPointers.

    //  [hBGMapTileCount] must be even since this is done in pairs.

    //  Return carry on success.

    LDH_A_addr(hBGMapUpdate);
    AND_A_A;
    RET_Z;

    LDH_A_addr(rVBK);
    PUSH_AF;

    //  Relocate the stack pointer to wBGMapBufferPointers
    LD_addr_SP(hSPBuffer);
    LD_HL(wBGMapBufferPointers);
    LD_SP_HL;

    //  We can now pop the addresses of affected spots on the BG Map

    LD_HL(wBGMapPalBuffer);
    LD_DE(wBGMapBuffer);

next:
    //  Copy a pair of 16x8 blocks (one 16x16 block)

    for (int rept = 0; rept < 2; rept++) {
        //  Get our BG Map address
        POP_BC;

        //  Palettes
        LD_A(1);
        LDH_addr_A(rVBK);

        LD_A_hli;
        LD_bc_A;
        INC_C;
        LD_A_hli;
        LD_bc_A;
        DEC_C;

        //  Tiles
        LD_A(0);
        LDH_addr_A(rVBK);

        LD_A_de;
        INC_DE;
        LD_bc_A;
        INC_C;
        LD_A_de;
        INC_DE;
        LD_bc_A;
    }

    //  We've done 2 16x8 blocks
    LDH_A_addr(hBGMapTileCount);
    DEC_A;
    DEC_A;
    LDH_addr_A(hBGMapTileCount);

    IF_NZ goto next;

    //  Restore the stack pointer
    LDH_A_addr(hSPBuffer);
    LD_L_A;
    LDH_A_addr(hSPBuffer + 1);
    LD_H_A;
    LD_SP_HL;

    POP_AF;
    LDH_addr_A(rVBK);

    XOR_A_A;
    LDH_addr_A(hBGMapUpdate);
    SCF;
    RET;
}

//  Copy [hBGMapTileCount] 16x8 tiles from wBGMapBuffer
//  to bg map addresses in wBGMapBufferPointers.
//  [hBGMapTileCount] must be even since this is done in pairs.
//  Return true on success.
bool UpdateBGMapBuffer_Conv(void) {

    // LDH_A_addr(hBGMapUpdate);
    // AND_A_A;
    // RET_Z;
    if(gb_read(hBGMapUpdate) == 0)
        return false;

    // LDH_A_addr(rVBK);
    // PUSH_AF;
    uint8_t VBK = gb_read(rVBK);

    //  Relocate the stack pointer to wBGMapBufferPointers
    // LD_addr_SP(hSPBuffer);
    // LD_HL(wBGMapBufferPointers);
    // LD_SP_HL;
    uint16_t sp = wBGMapBufferPointers;

    //  We can now pop the addresses of affected spots on the BG Map

    // LD_HL(wBGMapPalBuffer);
    // LD_DE(wBGMapBuffer);
    uint16_t hl = wBGMapPalBuffer;
    uint16_t de = wBGMapBuffer;
    union Register bc = {.reg = 0};
    uint8_t tc;

    do {
        //  Copy a pair of 16x8 blocks (one 16x16 block)

        for (int rept = 0; rept < 2; rept++) {
            //  Get our BG Map address
            // POP_BC;
            bc.lo = gb_read(sp++);
            bc.hi = gb_read(sp++);

            //  Palettes
            // LD_A(1);
            // LDH_addr_A(rVBK);
            gb_write(rVBK, 1);

            // LD_A_hli;
            // LD_bc_A;
            gb_write(bc.reg, gb_read(hl++));

            // INC_C;
            bc.lo++;

            // LD_A_hli;
            // LD_bc_A;
            gb_write(bc.reg, gb_read(hl++));

            // DEC_C;
            bc.lo--;

            //  Tiles
            // LD_A(0);
            // LDH_addr_A(rVBK);
            gb_write(rVBK, 0);

            // LD_A_de;
            // INC_DE;
            // LD_bc_A;
            gb_write(bc.reg, gb_read(de++));

            // INC_C;
            bc.lo++;

            // LD_A_de;
            // INC_DE;
            // LD_bc_A;
            gb_write(bc.reg, gb_read(de++));
        }

        //  We've done 2 16x8 blocks
        // LDH_A_addr(hBGMapTileCount);
        // DEC_A;
        // DEC_A;
        // LDH_addr_A(hBGMapTileCount);
        tc = gb_read(hBGMapTileCount) - 2;
        gb_write(hBGMapTileCount, tc);

    // IF_NZ goto next;
    } while(tc != 0);

    //  Restore the stack pointer
    // LDH_A_addr(hSPBuffer);
    // LD_L_A;
    // LDH_A_addr(hSPBuffer + 1);
    // LD_H_A;
    // LD_SP_HL;

    // POP_AF;
    // LDH_addr_A(rVBK);
    gb_write(rVBK, VBK);

    // XOR_A_A;
    // LDH_addr_A(hBGMapUpdate);
    gb_write(hBGMapUpdate, 0);

    // SCF;
    // RET;
    return true;
}

void WaitTop(void) {
    //  Wait until the top third of the BG Map is being updated.

    LDH_A_addr(hBGMapMode);
    AND_A_A;
    RET_Z;

    LDH_A_addr(hBGMapThird);
    AND_A_A;
    IF_Z goto done;

    CALL(aDelayFrame);
    JR(mWaitTop);

done:
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    RET;
}

void UpdateBGMap(void) {
    //  Update the BG Map, in thirds, from wTilemap and wAttrmap.

    LDH_A_addr(hBGMapMode);
    AND_A_A;  // 0
    RET_Z;

    //  BG Map 0
    DEC_A;  // 1
    IF_Z goto Tiles;
    DEC_A;  // 2
    IF_Z goto Attr;

    //  BG Map 1
    DEC_A;  // useless

    LDH_A_addr(hBGMapAddress);
    LD_L_A;
    LDH_A_addr(hBGMapAddress + 1);
    LD_H_A;
    PUSH_HL;

    XOR_A_A;  // LOW(vBGMap1)
    LDH_addr_A(hBGMapAddress);
    LD_A(HIGH(vBGMap1));
    LDH_addr_A(hBGMapAddress + 1);

    LDH_A_addr(hBGMapMode);
    PUSH_AF;
    CP_A(3);
    CALL_Z(aUpdateBGMap_Tiles);
    POP_AF;
    CP_A(4);
    CALL_Z(aUpdateBGMap_Attr);

    POP_HL;
    LD_A_L;
    LDH_addr_A(hBGMapAddress);
    LD_A_H;
    LDH_addr_A(hBGMapAddress + 1);
    RET;

Attr:
    LD_A(1);
    LDH_addr_A(rVBK);

    hlcoord(0, 0, wAttrmap);
    CALL(aUpdateBGMap_update);

    LD_A(0);
    LDH_addr_A(rVBK);
    RET;

Tiles:
    hlcoord(0, 0, wTilemap);

update:
    LD_addr_SP(hSPBuffer);

    //  Which third?
    LDH_A_addr(hBGMapThird);
    AND_A_A;  // 0
    IF_Z goto top;
    DEC_A;  // 1
    IF_Z goto middle;
    // 2

#define THIRD_HEIGHT (SCREEN_HEIGHT / 3)

    //  bottom
    LD_DE(2 * THIRD_HEIGHT * SCREEN_WIDTH);
    ADD_HL_DE;
    LD_SP_HL;

    LDH_A_addr(hBGMapAddress + 1);
    LD_H_A;
    LDH_A_addr(hBGMapAddress);
    LD_L_A;

    LD_DE(2 * THIRD_HEIGHT * BG_MAP_WIDTH);
    ADD_HL_DE;

    //  Next time: top third
    XOR_A_A;
    goto start;

middle:
    LD_DE(THIRD_HEIGHT * SCREEN_WIDTH);
    ADD_HL_DE;
    LD_SP_HL;

    LDH_A_addr(hBGMapAddress + 1);
    LD_H_A;
    LDH_A_addr(hBGMapAddress);
    LD_L_A;

    LD_DE(THIRD_HEIGHT * BG_MAP_WIDTH);
    ADD_HL_DE;

    //  Next time: bottom third
    LD_A(2);
    goto start;

top:
    LD_SP_HL;

    LDH_A_addr(hBGMapAddress + 1);
    LD_H_A;
    LDH_A_addr(hBGMapAddress);
    LD_L_A;

    //  Next time: middle third
    LD_A(1);

start:
    //  Which third to update next time
    LDH_addr_A(hBGMapThird);

    //  Rows of tiles in a third
    LD_A(THIRD_HEIGHT);

    //  Discrepancy between wTilemap and BGMap
    LD_BC(BG_MAP_WIDTH - (SCREEN_WIDTH - 1));

row:
    //  Copy a row of 20 tiles
    for (int rept = 0; rept < SCREEN_WIDTH / 2 - 1; rept++) {
        POP_DE;
        LD_hl_E;
        INC_L;
        LD_hl_D;
        INC_L;
    }
    POP_DE;
    LD_hl_E;
    INC_L;
    LD_hl_D;

    ADD_HL_BC;
    DEC_A;
    IF_NZ goto row;

    LDH_A_addr(hSPBuffer);
    LD_L_A;
    LDH_A_addr(hSPBuffer + 1);
    LD_H_A;
    LD_SP_HL;
    RET;
}

void Serve1bppRequest(void) {
    //  Only call during the first fifth of VBlank

    LD_A_addr(wRequested1bppSize);
    AND_A_A;
    RET_Z;

    //  Back out if we're too far into VBlank
    //  lol nope
    // LDH_A_addr(rLY);
    // CP_A(LY_VBLANK);
    // RET_C;
    // CP_A(LY_VBLANK + 2);
    // RET_NC;

    //  Copy [wRequested1bppSize] 1bpp tiles from [wRequested1bppSource] to [wRequested1bppDest]

    LD_addr_SP(hSPBuffer);

    //  Source
    LD_HL(wRequested1bppSource);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_SP_HL;

    //  Destination
    LD_HL(wRequested1bppDest);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;

    //  # tiles to copy
    LD_A_addr(wRequested1bppSize);
    LD_B_A;

    XOR_A_A;
    LD_addr_A(wRequested1bppSize);

next:

    for (int rept = 0; rept < 3; rept++) {
        POP_DE;
        LD_hl_E;
        INC_L;
        LD_hl_E;
        INC_L;
        LD_hl_D;
        INC_L;
        LD_hl_D;
        INC_L;
    }
    POP_DE;
    LD_hl_E;
    INC_L;
    LD_hl_E;
    INC_L;
    LD_hl_D;
    INC_L;
    LD_hl_D;

    INC_HL;
    DEC_B;
    IF_NZ goto next;

    LD_A_L;
    LD_addr_A(wRequested1bppDest);
    LD_A_H;
    LD_addr_A(wRequested1bppDest + 1);

    LD_addr_SP(wRequested1bppSource);

    LDH_A_addr(hSPBuffer);
    LD_L_A;
    LDH_A_addr(hSPBuffer + 1);
    LD_H_A;
    LD_SP_HL;
    RET;
}

void Serve2bppRequest(void) {
    //  Only call during the first fifth of VBlank

    LD_A_addr(wRequested2bppSize);
    AND_A_A;
    RET_Z;

    //  Back out if we're too far into VBlank
    //  lol nope
    // LDH_A_addr(rLY);
    // CP_A(LY_VBLANK);
    // RET_C;
    // CP_A(LY_VBLANK + 2);
    // RET_NC;
    JR(mv_Serve2bppRequest);
}

void Serve2bppRequest_VBlank(void) {
    LD_A_addr(wRequested2bppSize);
    AND_A_A;
    RET_Z;

    return v_Serve2bppRequest();
}

void v_Serve2bppRequest(void) {
    //  Copy [wRequested2bppSize] 2bpp tiles from [wRequested2bppSource] to [wRequested2bppDest]

    LD_addr_SP(hSPBuffer);

    //  Source
    LD_HL(wRequested2bppSource);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_SP_HL;

    //  Destination
    LD_HL(wRequested2bppDest);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;

    //  # tiles to copy
    LD_A_addr(wRequested2bppSize);
    LD_B_A;

    XOR_A_A;
    LD_addr_A(wRequested2bppSize);

next:

    for (int rept = 0; rept < 7; rept++) {
        POP_DE;
        LD_hl_E;
        INC_L;
        LD_hl_D;
        INC_L;
    }
    POP_DE;
    LD_hl_E;
    INC_L;
    LD_hl_D;

    INC_HL;
    DEC_B;
    IF_NZ goto next;

    LD_A_L;
    LD_addr_A(wRequested2bppDest);
    LD_A_H;
    LD_addr_A(wRequested2bppDest + 1);

    LD_addr_SP(wRequested2bppSource);

    LDH_A_addr(hSPBuffer);
    LD_L_A;
    LDH_A_addr(hSPBuffer + 1);
    LD_H_A;
    LD_SP_HL;
    RET;
}

void AnimateTileset(void) {
    //  Only call during the first fifth of VBlank

    LDH_A_addr(hMapAnims);
    AND_A_A;
    RET_Z;

    //  Back out if we're too far into VBlank
    //  lol nope we have C, bitches!
    // LDH_A_addr(rLY);
    // CP_A(LY_VBLANK);
    // RET_C;
    // CP_A(LY_VBLANK + 7);
    // RET_NC;

    LDH_A_addr(hROMBank);
    PUSH_AF;
    LD_A(BANK(av_AnimateTileset));
    RST(aBankswitch);

    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awTilesetAnim));
    LDH_addr_A(rSVBK);

    LDH_A_addr(rVBK);
    PUSH_AF;
    LD_A(0);
    LDH_addr_A(rVBK);

    CALL(av_AnimateTileset);  //temporarily commented out to fix crashes
                              //Might be okay now?

    POP_AF;
    LDH_addr_A(rVBK);
    POP_AF;
    LDH_addr_A(rSVBK);
    POP_AF;
    RST(aBankswitch);
    RET;
}
