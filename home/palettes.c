#include "../constants.h"
#include "palettes.h"
#include "copy.h"
#include "delay.h"
#include "../engine/tilesets/map_palettes.h"

//  Functions dealing with palettes.

//  update bgp data from wBGPals2
//  update obp data from wOBPals2
//  return true if successful
bool UpdatePalsIfCGB(void){
//  check cgb
    // LDH_A_addr(hCGB);
    // AND_A_A;
    // RET_Z ;
    if(hram->hCGB == 0)
        return false;

    return UpdateCGBPals();
}

//  return true if successful
bool UpdateCGBPals(void){
//  any pals to update?
    // LDH_A_addr(hCGBPalUpdate);
    // AND_A_A;
    // RET_Z ;
    if(hram->hCGBPalUpdate == 0)
        return false;
// fallthrough

    return ForceUpdateCGBPals();
}

bool ForceUpdateCGBPals(void){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    uint8_t svbk = gb_read(rSVBK);

    // LD_A(MBANK(awBGPals2));
    // LDH_addr_A(rSVBK);
    gb_write(rSVBK, MBANK(awBGPals2));

    // LD_HL(wBGPals2);
    uint8_t* hl = wram->wBGPals2;

//  copy 8 pals to bgpd
    // LD_A(1 << rBGPI_AUTO_INCREMENT);
    // LDH_addr_A(rBGPI);
    gb_write(rBGPI, (1 << rBGPI_AUTO_INCREMENT));

    // LD_C(LOW(rBGPD));
    // LD_B(8 / 2);
    uint8_t b = 8 / 2;

    do {
        for(int rept = 0; rept < (1 * PALETTE_SIZE) * 2; rept++){
            // LD_A_hli;
            // LDH_c_A;
            gb_write(rBGPD, *(hl++));
        }

        // DEC_B;
        // IF_NZ goto bgp;
    } while(--b != 0);

//  hl is now wOBPals2
    hl = wram->wOBPals2;

//  copy 8 pals to obpd
    // LD_A(1 << rOBPI_AUTO_INCREMENT);
    // LDH_addr_A(rOBPI);
    gb_write(rOBPI, (1 << rOBPI_AUTO_INCREMENT));

    // LD_C(LOW(rOBPD));
    b = 8 / 2;

    do {
        for(int rept = 0; rept < (1 * PALETTE_SIZE) * 2; rept++){
            // LD_A_hli;
            // LDH_c_A;
            gb_write(rOBPD, *(hl++));
        }

    // DEC_B;
    // IF_NZ goto obp;
    } while(--b != 0);

    // POP_AF;
    // LDH_addr_A(rSVBK);
    gb_write(rSVBK, svbk);

//  clear pal update queue
    // XOR_A_A;
    // LDH_addr_A(hCGBPalUpdate);
    hram->hCGBPalUpdate = FALSE;
    return true;
}

//  exists to forego reinserting cgb-converted image data
//  input: a -> bgp
void DmgToCgbBGPals(uint8_t a){
    // LDH_addr_A(rBGP);
    gb_write(rBGP, a);

    // PUSH_AF;
//  Don't need to be here if DMG
    // LDH_A_addr(hCGB);
    // AND_A_A;
    // IF_Z goto end;
    if(hram->hCGB == 0)
        return;

    // LDH_A_addr(rSVBK);
    // PUSH_AF;

    // LD_A(MBANK(awBGPals2));
    // LDH_addr_A(rSVBK);

//  copy & reorder bg pal buffer
    // LD_HL(wBGPals2);  // to
    // LD_DE(wBGPals1);  // from
//  order
    // LDH_A_addr(rBGP);
    // LD_B_A;
//  all pals
    // LD_C(8);
    // CALL(aCopyPals);
    CopyPals(wram->wBGPals2, wram->wBGPals1, gb_read(rBGP), 8);
//  request pal update
    // LD_A(TRUE);
    // LDH_addr_A(hCGBPalUpdate);
    hram->hCGBPalUpdate = TRUE;

    // POP_AF;
    // LDH_addr_A(rSVBK);

    return;
}

//  exists to forego reinserting cgb-converted image data
//  input: d -> obp1
//         e -> obp2
void DmgToCgbObjPals(uint8_t d, uint8_t e){
    // LD_A_E;
    // LDH_addr_A(rOBP0);
    gb_write(rOBP0, e);

    // LD_A_D;
    // LDH_addr_A(rOBP1);
    gb_write(rOBP1, d);

    // LDH_A_addr(hCGB);
    // AND_A_A;
    // RET_Z ;
    if(hram->hCGB == 0)
        return;
    
    // LDH_A_addr(rSVBK);
    // PUSH_AF;

    // LD_A(MBANK(awOBPals2));
    // LDH_addr_A(rSVBK);

//  copy & reorder obj pal buffer
    // LD_HL(wOBPals2);  // to
    // LD_DE(wOBPals1);  // from
//  order
    // LDH_A_addr(rOBP0);
    // LD_B_A;
//  all pals
    // LD_C(8);
    // CALL(aCopyPals);
    CopyPals(wram->wOBPals2, wram->wOBPals1, gb_read(rOBP0), 8);
//  request pal update
    // LD_A(TRUE);
    // LDH_addr_A(hCGBPalUpdate);
    hram->hCGBPalUpdate = TRUE;

    // POP_AF;
    // LDH_addr_A(rSVBK);
}

void DmgToCgbObjPal0(uint8_t a){
    // LDH_addr_A(rOBP0);
    gb_write(rOBP0, a);
    // PUSH_AF;

//  Don't need to be here if not CGB
    // LDH_A_addr(hCGB);
    // AND_A_A;
    // IF_Z goto dmg;
    if(hram->hCGB == 0) {
    // dmg:
        // POP_AF;
        // RET;
        return;
    }

    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;

    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(MBANK(awOBPals2));
    // LDH_addr_A(rSVBK);

    // LD_HL(wOBPals2 + PALETTE_SIZE * 0);
    // LD_DE(wOBPals1 + PALETTE_SIZE * 0);
    // LDH_A_addr(rOBP0);
    // LD_B_A;
    // LD_C(1);
    // CALL(aCopyPals);
    CopyPals(wram->wOBPals2 + PALETTE_SIZE * 0, wram->wOBPals1 + PALETTE_SIZE * 0, gb_read(rOBP0), 1);
    // LD_A(TRUE);
    // LDH_addr_A(hCGBPalUpdate);
    hram->hCGBPalUpdate = TRUE;

    // POP_AF;
    // LDH_addr_A(rSVBK);

    // POP_BC;
    // POP_DE;
    // POP_HL;
}

void DmgToCgbObjPal1(uint8_t a){
    // LDH_addr_A(rOBP1);
    // PUSH_AF;
    gb_write(rOBP1, a);

    // LDH_A_addr(hCGB);
    // AND_A_A;
    // IF_Z goto dmg;
    if(hram->hCGB == 0) {
    // dmg:
        // POP_AF;
        // RET;
        return;
    }

    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;

    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(MBANK(awOBPals2));
    // LDH_addr_A(rSVBK);

    // LD_HL(wOBPals2 + PALETTE_SIZE * 1);
    // LD_DE(wOBPals1 + PALETTE_SIZE * 1);
    // LDH_A_addr(rOBP1);
    // LD_B_A;
    // LD_C(1);
    // CALL(aCopyPals);
    CopyPals(wram->wOBPals2 + PALETTE_SIZE * 1, wram->wOBPals1 + PALETTE_SIZE * 1, gb_read(rOBP1), 1);
    // LD_A(TRUE);
    // LDH_addr_A(hCGBPalUpdate);
    hram->hCGBPalUpdate = TRUE;

    // POP_AF;
    // LDH_addr_A(rSVBK);

    // POP_BC;
    // POP_DE;
    // POP_HL;


// dmg:
    // POP_AF;
    // RET;
}

void CopyPals(void* hl_, const void* de_, uint8_t b, uint8_t c){
    uint16_t* hl = hl_;
    const uint16_t* de = de_;
    do {
        // PUSH_BC;
        uint8_t bsaved = b;
        // LD_C(NUM_PAL_COLORS);
        uint8_t n = NUM_PAL_COLORS;

        do {
            // PUSH_DE;
            // PUSH_HL;

        //  get pal color
            // LD_A_B;
            // maskbits(1 << PAL_COLOR_SIZE, 0);
            uint8_t palc = b & (0b11);
        //  2 bytes per color
            // ADD_A_A;
            // LD_L_A;
            // LD_H(0);
            // ADD_HL_DE;

            // LD_E_hl;
            // INC_HL;
            // LD_D_hl;
            uint16_t pal = de[palc];

        //  dest
            // POP_HL;
        //  write color
            // LD_hl_E;
            // INC_HL;
            // LD_hl_D;
            // INC_HL;
            *hl = pal;
            hl++;

        //  next pal color
            // for(int rept = 0; rept < PAL_COLOR_SIZE; rept++){
            // SRL_B;
            // }
            b >>= PAL_COLOR_SIZE;
        //  source
            // POP_DE;
        //  done pal?
            // DEC_C;
            // IF_NZ goto loop;
        } while(--n != 0);

    //  de += 8 (next pal)
        // LD_A(PALETTE_SIZE);
        // ADD_A_E;
        // IF_NC goto ok;
        // INC_D;
    // ok:
        // LD_E_A;
        de += NUM_PAL_COLORS;

    //  how many more pals?
        // POP_BC;
        b = bsaved;
        // DEC_C;
        // JR_NZ (mCopyPals);
    } while(--c != 0);
}

//  copy c palettes in order b from de to hl
void CopyPals_GB(uint16_t hl, uint16_t de, uint8_t b, uint8_t c){
    do {
        // PUSH_BC;
        uint8_t bsaved = b;
        // LD_C(NUM_PAL_COLORS);
        uint8_t n = NUM_PAL_COLORS;

        do {
            // PUSH_DE;
            // PUSH_HL;
            uint16_t desaved = de;
            uint16_t hlsaved = hl;

        //  get pal color
            // LD_A_B;
            // maskbits(1 << PAL_COLOR_SIZE, 0);
            uint8_t palc = b & (0b11);
        //  2 bytes per color
            // ADD_A_A;
            // LD_L_A;
            // LD_H(0);
            // ADD_HL_DE;
            hl = de + (2 * palc);

            // LD_E_hl;
            // INC_HL;
            // LD_D_hl;
            de = gb_read16(hl);

        //  dest
            // POP_HL;
            hl = hlsaved;
        //  write color
            // LD_hl_E;
            // INC_HL;
            // LD_hl_D;
            // INC_HL;
            gb_write16(hl, de);
            hl += 2;

        //  next pal color
            // for(int rept = 0; rept < PAL_COLOR_SIZE; rept++){
            // SRL_B;
            // }
            b >>= PAL_COLOR_SIZE;
        //  source
            // POP_DE;
            de = desaved;
        //  done pal?
            // DEC_C;
            // IF_NZ goto loop;
        } while(--n != 0);

    //  de += 8 (next pal)
        // LD_A(PALETTE_SIZE);
        // ADD_A_E;
        // IF_NC goto ok;
        // INC_D;
    // ok:
        // LD_E_A;
        de += PALETTE_SIZE;

    //  how many more pals?
        // POP_BC;
        b = bsaved;
        // DEC_C;
        // JR_NZ (mCopyPals);
    } while(--c != 0);
}

void ClearVBank1(void){
    if(hram->hCGB == 0) 
        return;

    ByteFill(vram->vTiles3, (VRAM_End - VRAM_Begin), 0);
}

void GSReloadPalettes(void){
    //  //  dummied out
    // RET;
}

void ReloadSpritesNoPalettes(void){
    // LDH_A_addr(hCGB);
    // AND_A_A;
    // RET_Z ;
    if(hram->hCGB == 0)
        return;
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(MBANK(awBGPals2));
    // LDH_addr_A(rSVBK);
    // LD_HL(wBGPals2);
    // LD_BC((8 * PALETTE_SIZE) + (2 * PALETTE_SIZE));
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill(wram->wBGPals2, (8 * PALETTE_SIZE) + (2 * PALETTE_SIZE), 0);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // LD_A(TRUE);
    // LDH_addr_A(hCGBPalUpdate);
    hram->hCGBPalUpdate = TRUE;
    // CALL(aDelayFrame);
    DelayFrame();
    // RET;
}

void SwapTextboxPalettes(void){
    // HOMECALL(av_SwapTextboxPalettes);
    // RET;
    return v_SwapTextboxPalettes_Conv();
}

void ScrollBGMapPalettes(uint8_t c){
    // HOMECALL(av_ScrollBGMapPalettes);
    // RET;
    return v_ScrollBGMapPalettes_Conv(c);
}
