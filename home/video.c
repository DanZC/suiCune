#include "../constants.h"
#include "video.h"
#include "delay.h"
#include "../engine/tilesets/tileset_anims.h"

//  Functions dealing with VRAM.

//  Return true if the transfer is completed.
bool DMATransfer(void) {
    // LDH_A_addr(hDMATransfer);
    // AND_A_A;
    // RET_Z;
    uint8_t value = hram.hDMATransfer;
    if(value == 0) 
        return false;

    //  Start transfer
    // LDH_addr_A(rHDMA5);
    gb_write(rHDMA5, value);

    //  Execution is halted until the transfer is complete.

    // XOR_A_A;
    // LDH_addr_A(hDMATransfer);
    hram.hDMATransfer = 0;
    // SCF;
    // RET;
    return true;
}

//  Copy [hBGMapTileCount] 16x8 tiles from wBGMapBuffer
//  to bg map addresses in wBGMapBufferPointers.
//  [hBGMapTileCount] must be even since this is done in pairs.
//  Return true on success.
bool UpdateBGMapBuffer(void) {

    // LDH_A_addr(hBGMapUpdate);
    // AND_A_A;
    // RET_Z;
    if(hram.hBGMapUpdate == 0)
        return false;

    // LDH_A_addr(rVBK);
    // PUSH_AF;
    uint8_t VBK = gb_read(rVBK);

    //  Relocate the stack pointer to wBGMapBufferPointers
    // LD_addr_SP(hSPBuffer);
    // LD_HL(wBGMapBufferPointers);
    // LD_SP_HL;
    uint8_t* sp = wram->wBGMapBufferPointers;

    //  We can now pop the addresses of affected spots on the BG Map

    // LD_HL(wBGMapPalBuffer);
    // LD_DE(wBGMapBuffer);
    uint8_t* hl = wram->wBGMapPalBuffer;
    uint8_t* de = wram->wBGMapBuffer;
    uint16_t bc = 0;

    do {
        //  Copy a pair of 16x8 blocks (one 16x16 block)

        for (int rept = 0; rept < 2; rept++) {
            //  Get our BG Map address
            // POP_BC;
            bc = sp[0] | (sp[1] << 8);
            sp += 2;

            //  Palettes
            // LD_A(1);
            // LDH_addr_A(rVBK);
            gb_write(rVBK, 1);

            // LD_A_hli;
            // LD_bc_A;
            gb_write(bc, *(hl++));

            // INC_C;
            bc++;

            // LD_A_hli;
            // LD_bc_A;
            gb_write(bc, *(hl++));

            // DEC_C;
            bc--;

            //  Tiles
            // LD_A(0);
            // LDH_addr_A(rVBK);
            gb_write(rVBK, 0);

            // LD_A_de;
            // INC_DE;
            // LD_bc_A;
            gb_write(bc, *(de++));

            // INC_C;
            bc++;

            // LD_A_de;
            // INC_DE;
            // LD_bc_A;
            gb_write(bc, *(de++));
        }

        //  We've done 2 16x8 blocks
        // LDH_A_addr(hBGMapTileCount);
        // DEC_A;
        // DEC_A;
        // LDH_addr_A(hBGMapTileCount);
        hram.hBGMapTileCount -= 2;
    // IF_NZ goto next;
    } while(hram.hBGMapTileCount != 0);

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
    hram.hBGMapUpdate = 0;

    // SCF;
    // RET;
    return true;
}

//  Wait until the top third of the BG Map is being updated.
void WaitTop(void) {

    while(1)
    {
        // LDH_A_addr(hBGMapMode);
        // AND_A_A;
        // RET_Z;
        if(hram.hBGMapMode == BGMAPMODE_NONE)
            return;

        // LDH_A_addr(hBGMapThird);
        // AND_A_A;
        // IF_Z goto done;
        if(hram.hBGMapThird == 0)
            break;

        // CALL(aDelayFrame);
        DelayFrame();
        // JR(mWaitTop);
    }

// done:
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram.hBGMapMode = BGMAPMODE_NONE;
    // RET;
}

static void UpdateBGMap_update(uint8_t* dst, const uint8_t* hl) {
    // LD_addr_SP(hSPBuffer);

    const uint8_t* sp;
    //  Which third?
    // LDH_A_addr(hBGMapThird);
    // AND_A_A;  // 0
    // IF_Z goto top;
    // DEC_A;  // 1
    // IF_Z goto middle;
    // 2
#if ENHANCEMENT_DRAW_BG_IN_ONE_FRAME
    sp = hl;
    hram.hBGMapThird = 0;
#else
    const uint8_t map_third = hram.hBGMapThird;
    switch(map_third) {

#define THIRD_HEIGHT (SCREEN_HEIGHT / 3)
    
    default:
    case 2:
        //  bottom
        // LD_DE(2 * THIRD_HEIGHT * SCREEN_WIDTH);
        // ADD_HL_DE;
        // LD_SP_HL;
        sp = hl + (2 * THIRD_HEIGHT * SCREEN_WIDTH);

        // LDH_A_addr(hBGMapAddress + 1);
        // LD_H_A;
        // LDH_A_addr(hBGMapAddress);
        // LD_L_A;

        // LD_DE(2 * THIRD_HEIGHT * BG_MAP_WIDTH);
        // ADD_HL_DE;
        dst += (2 * THIRD_HEIGHT * BG_MAP_WIDTH);

        //  Next time: top third
        // XOR_A_A;
        hram.hBGMapThird = 0;
        // goto start;
        break;

    case 1:
    // middle:
        // LD_DE(THIRD_HEIGHT * SCREEN_WIDTH);
        // ADD_HL_DE;
        // LD_SP_HL;
        sp = hl + (THIRD_HEIGHT * SCREEN_WIDTH);

        // LDH_A_addr(hBGMapAddress + 1);
        // LD_H_A;
        // LDH_A_addr(hBGMapAddress);
        // LD_L_A;

        // LD_DE(THIRD_HEIGHT * BG_MAP_WIDTH);
        // ADD_HL_DE;
        dst += (THIRD_HEIGHT * BG_MAP_WIDTH);

        //  Next time: bottom third
        // LD_A(2);
        hram.hBGMapThird = 2;
        // goto start;
        break;
    
    case 0:
    // top:
        // LD_SP_HL;
        sp = hl;

        // LDH_A_addr(hBGMapAddress + 1);
        // LD_H_A;
        // LDH_A_addr(hBGMapAddress);
        // LD_L_A;

        //  Next time: middle third
        // LD_A(1);
        hram.hBGMapThird = 1;
        break;
    }
#endif
// start:
    //  Which third to update next time
    // LDH_addr_A(hBGMapThird);

    //  Rows of tiles in a third
    // LD_A(THIRD_HEIGHT);
#if ENHANCEMENT_DRAW_BG_IN_ONE_FRAME
    uint8_t a = SCREEN_HEIGHT;
#else
    uint8_t a = THIRD_HEIGHT;
#endif

    //  Discrepancy between wTilemap and BGMap
    // LD_BC(BG_MAP_WIDTH - (SCREEN_WIDTH - 1));

    do {
    // row:
        //  Copy a row of 20 tiles
        for (int rept = 0; rept < SCREEN_WIDTH / 2 - 1; rept++) {
            // POP_DE;
            // LD_hl_E;
            // INC_L;
            *(dst++) = *(sp++);
            // LD_hl_D;
            // INC_L;
            *(dst++) = *(sp++);
        }
        // POP_DE;
        // LD_hl_E;
        // INC_L;
        *(dst++) = *(sp++);
        // LD_hl_D;
        *dst = *(sp++);

        // ADD_HL_BC;
        dst += (BG_MAP_WIDTH - (SCREEN_WIDTH - 1));
        // DEC_A;
        // IF_NZ goto row;
    } while(--a != 0);

    // LDH_A_addr(hSPBuffer);
    // LD_L_A;
    // LDH_A_addr(hSPBuffer + 1);
    // LD_H_A;
    // LD_SP_HL;
    // RET;
}

static void UpdateBGMap_Tiles(uint8_t* dst) {
    // hlcoord(0, 0, wTilemap);
    return UpdateBGMap_update(dst, coord(0, 0, wram->wTilemap));
}

static void UpdateBGMap_Attr(uint8_t* dst) {
    // LD_A(1);
    // LDH_addr_A(rVBK);

    // hlcoord(0, 0, wAttrmap);
    // CALL(aUpdateBGMap_update);
    return UpdateBGMap_update(dst, coord(0, 0, wram->wAttrmap));

    // LD_A(0);
    // LDH_addr_A(rVBK);
    // RET;
}

//  Update the BG Map, in thirds, from wTilemap and wAttrmap.
void UpdateBGMap(void) {
    // LDH_A_addr(hBGMapMode);
    // AND_A_A;  // 0
    // RET_Z;
    if(hram.hBGMapMode == BGMAPMODE_NONE)
        return;

    //  BG Map 0
    // DEC_A;  // 1
    // IF_Z goto Tiles;
    if(hram.hBGMapMode == BGMAPMODE_UPDATE_TILES)
        return UpdateBGMap_Tiles(GBToRAMAddr(hram.hBGMapAddress));
    // DEC_A;  // 2
    // IF_Z goto Attr;
    if(hram.hBGMapMode == BGMAPMODE_UPDATE_ATTRS)
        return UpdateBGMap_Attr((uint8_t*)GBToRAMAddr(hram.hBGMapAddress) + VRAM_BANK_SIZE);

    //  BG Map 1
    // DEC_A;  // useless

    // LDH_A_addr(hBGMapAddress);
    // LD_L_A;
    // LDH_A_addr(hBGMapAddress + 1);
    // LD_H_A;
    // PUSH_HL;

    // XOR_A_A;  // LOW(vBGMap1)
    // LDH_addr_A(hBGMapAddress);
    // LD_A(HIGH(vBGMap1));
    // LDH_addr_A(hBGMapAddress + 1);

    // LDH_A_addr(hBGMapMode);
    // PUSH_AF;
    uint8_t bgmapmode = hram.hBGMapMode;
    // CP_A(3);
    // CALL_Z(aUpdateBGMap_Tiles);
    if(bgmapmode == BGMAPMODE_UPDATE_VTILES1) {
        UpdateBGMap_Tiles(vram->vBGMap1);
    }
    // POP_AF;
    // CP_A(4);
    // CALL_Z(aUpdateBGMap_Attr);
    if(bgmapmode == BGMAPMODE_UPDATE_VATTRS1) {
        UpdateBGMap_Attr(vram->vBGMap3);
    }

    // POP_HL;
    // LD_A_L;
    // LDH_addr_A(hBGMapAddress);
    // LD_A_H;
    // LDH_addr_A(hBGMapAddress + 1);
    // RET;

// Attr:
    // LD_A(1);
    // LDH_addr_A(rVBK);

    // hlcoord(0, 0, wAttrmap);
    // CALL(aUpdateBGMap_update);

    // LD_A(0);
    // LDH_addr_A(rVBK);
    // RET;

// Tiles:
    // hlcoord(0, 0, wTilemap);
}

void Serve1bppRequest(void) {
    //  Only call during the first fifth of VBlank

    // LD_A_addr(wRequested1bppSize);
    // AND_A_A;
    // RET_Z;
    if(wram->wRequested1bppSize == 0)
        return;

    //  Back out if we're too far into VBlank
    //  lol nope
    // LDH_A_addr(rLY);
    // CP_A(LY_VBLANK);
    // RET_C;
    // CP_A(LY_VBLANK + 2);
    // RET_NC;

    //  Copy [wRequested1bppSize] 1bpp tiles from [wRequested1bppSource] to [wRequested1bppDest]

    // LD_addr_SP(hSPBuffer);

    //  Source
    // LD_HL(wRequested1bppSource);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_SP_HL;
    const uint8_t* sp = GBToRAMAddr(wram->wRequested1bppSource);
    const uint8_t* sp2 = sp;

    //  Destination
    // LD_HL(wRequested1bppDest);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    uint8_t* hl = GBToRAMAddr(wram->wRequested1bppDest);
    uint8_t* hl2 = hl;

    //  # tiles to copy
    // LD_A_addr(wRequested1bppSize);
    // LD_B_A;
    uint8_t b = wram->wRequested1bppSize;

    // XOR_A_A;
    // LD_addr_A(wRequested1bppSize);
    wram->wRequested1bppSize = 0x0;

    do {
    // next:
        for (int rept = 0; rept < 3; rept++) {
            // POP_DE;
            uint8_t e = *(sp++);
            uint8_t d = *(sp++);
            // LD_hl_E;
            // INC_L;
            *(hl++) = e;
            // LD_hl_E;
            // INC_L;
            *(hl++) = e;
            // LD_hl_D;
            // INC_L;
            *(hl++) = d;
            // LD_hl_D;
            // INC_L;
            *(hl++) = d;
        }
        // POP_DE;
        uint8_t e = *(sp++);
        uint8_t d = *(sp++);
        // LD_hl_E;
        // INC_L;
        *(hl++) = e;
        // LD_hl_E;
        // INC_L;
        *(hl++) = e;
        // LD_hl_D;
        // INC_L;
        *(hl++) = d;
        // LD_hl_D;
        *(hl++) = d;

        // INC_HL;
        // DEC_B;
        // IF_NZ goto next;
    } while(--b != 0);

    // LD_A_L;
    // LD_addr_A(wRequested1bppDest);
    // LD_A_H;
    // LD_addr_A(wRequested1bppDest + 1);
    wram->wRequested1bppDest = wram->wRequested1bppDest + (hl - hl2);

    // LD_addr_SP(wRequested1bppSource);
    wram->wRequested1bppSource = wram->wRequested1bppSource + (sp - sp2);

    // LDH_A_addr(hSPBuffer);
    // LD_L_A;
    // LDH_A_addr(hSPBuffer + 1);
    // LD_H_A;
    // LD_SP_HL;
    // RET;
}

void Serve2bppRequest(void) {
    //  Only call during the first fifth of VBlank

    // LD_A_addr(wRequested2bppSize);
    // AND_A_A;
    // RET_Z;

    //  Back out if we're too far into VBlank
    //  lol nope
    // LDH_A_addr(rLY);
    // CP_A(LY_VBLANK);
    // RET_C;
    // CP_A(LY_VBLANK + 2);
    // RET_NC;
    // JR(mv_Serve2bppRequest);
    return Serve2bppRequest_VBlank();
}

void Serve2bppRequest_VBlank(void) {
    // LD_A_addr(wRequested2bppSize);
    // AND_A_A;
    // RET_Z;
    if(wram->wRequested2bppSize == 0)
        return;

    return v_Serve2bppRequest();
}

void v_Serve2bppRequest(void) {
    //  Copy [wRequested2bppSize] 2bpp tiles from [wRequested2bppSource] to [wRequested2bppDest]

    // LD_addr_SP(hSPBuffer);

    //  Source
    // LD_HL(wRequested2bppSource);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_SP_HL;
    const uint8_t* sp = GBToRAMAddr(wram->wRequested2bppSource);
    const uint8_t* sp2 = sp;

    //  Destination
    // LD_HL(wRequested2bppDest);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    uint8_t* hl = GBToRAMAddr(wram->wRequested2bppDest);
    uint8_t* hl2 = hl;

    //  # tiles to copy
    // LD_A_addr(wRequested2bppSize);
    // LD_B_A;
    uint8_t b = wram->wRequested2bppSize;

    // XOR_A_A;
    // LD_addr_A(wRequested2bppSize);
    wram->wRequested2bppSize = 0x0;

    do {
    // next:
        for (int rept = 0; rept < 7; rept++) {
            // POP_DE;
            // LD_hl_E;
            *(hl++) = *(sp++);
            // INC_L;
            // LD_hl_D;
            // INC_L;
            *(hl++) = *(sp++);
        }
        // POP_DE;
        // LD_hl_E;
        *(hl++) = *(sp++);
        // INC_L;
        // LD_hl_D;
        *(hl++) = *(sp++);

        // INC_HL;
        // DEC_B;
        // IF_NZ goto next;
    } while(--b != 0);

    // LD_A_L;
    // LD_addr_A(wRequested2bppDest);
    // LD_A_H;
    // LD_addr_A(wRequested2bppDest + 1);
    wram->wRequested2bppDest = wram->wRequested2bppDest + (hl - hl2);

    // LD_addr_SP(wRequested2bppSource);
    wram->wRequested2bppSource = wram->wRequested2bppSource + (sp - sp2);

    // LDH_A_addr(hSPBuffer);
    // LD_L_A;
    // LDH_A_addr(hSPBuffer + 1);
    // LD_H_A;
    // LD_SP_HL;
    // RET;
}

void AnimateTileset(void) {
    //  Only call during the first fifth of VBlank

    // LDH_A_addr(hMapAnims);
    // AND_A_A;
    // RET_Z;
    if(hram.hMapAnims == 0)
        return;

    //  Back out if we're too far into VBlank
    //  lol nope we have C, bitches!
    // LDH_A_addr(rLY);
    // CP_A(LY_VBLANK);
    // RET_C;
    // CP_A(LY_VBLANK + 7);
    // RET_NC;

    // LDH_A_addr(hROMBank);
    // PUSH_AF;
    // LD_A(BANK(av_AnimateTileset));
    // RST(aBankswitch);

    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(MBANK(awTilesetAnim));
    // LDH_addr_A(rSVBK);

    // LDH_A_addr(rVBK);
    // PUSH_AF;
    uint8_t vbk = gb_read(rVBK);
    // LD_A(0);
    // LDH_addr_A(rVBK);
    gb_write(rVBK, 0);

    // CALL(av_AnimateTileset);  //temporarily commented out to fix crashes
    //                           //Might be okay now?
    v_AnimateTileset();

    // POP_AF;
    // LDH_addr_A(rVBK);
    gb_write(rVBK, vbk);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // POP_AF;
    // RST(aBankswitch);
    // RET;
}
