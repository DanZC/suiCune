#include "../../constants.h"
#include "init_hof_credits.h"
#include "../../home/tilemap.h"
#include "../../home/text.h"
#include "../../home/clear_sprites.h"
#include "../../home/lcd.h"
#include "../../home/gfx.h"
#include "../../home/copy.h"
#include "../../data/text/common.h"

void InitDisplayForHallOfFame(void){
    static const txt_cmd_s SavingRecordText[] = {
        text_far(v_SavingRecordText)
        text_end
    };
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // CALL(aClearTilemap);
    ClearTilemap_Conv2();
    // CALL(aClearSprites);
    ClearSprites_Conv();
    // CALL(aDisableLCD);
    DisableLCD_Conv();
    // CALL(aLoadStandardFont);
    LoadStandardFont_Conv();
    // CALL(aLoadFontsBattleExtra);
    LoadFontsBattleExtra_Conv();
    // hlbgcoord(0, 0, vBGMap0);
    // LD_BC(vBGMap1 - vBGMap0);
    // LD_A(0x7f);
    // CALL(aByteFill);
    ByteFill_Conv2(bgcoord(0, 0, vram->vBGMap0), vBGMap1 - vBGMap0, 0x7f);
    // hlcoord(0, 0, wAttrmap);
    // LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill_Conv2(coord(0, 0, wram->wAttrmap), SCREEN_WIDTH * SCREEN_HEIGHT, 0x0);
    // XOR_A_A;
    // LDH_addr_A(hSCY);
    hSCY = 0x0;
    // LDH_addr_A(hSCX);
    hSCX = 0x0;
    // CALL(aEnableLCD);
    EnableLCD_Conv();
    // LD_HL(mInitDisplayForHallOfFame_SavingRecordText);
    // CALL(aPrintText);
    PrintText_Conv2(SavingRecordText);
    // CALL(aWaitBGMap2);
    WaitBGMap2_Conv();
    // CALL(aSetPalettes);
    SetPalettes_Conv();
    // RET;
}

void InitDisplayForRedCredits(void){
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // CALL(aClearTilemap);
    ClearTilemap_Conv2();
    // CALL(aClearSprites);
    ClearSprites_Conv();
    // CALL(aDisableLCD);
    DisableLCD_Conv();
    // CALL(aLoadStandardFont);
    LoadStandardFont_Conv();
    // CALL(aLoadFontsBattleExtra);
    LoadFontsBattleExtra_Conv();
    // hlbgcoord(0, 0, vBGMap0);
    // LD_BC(vBGMap1 - vBGMap0);
    // LD_A(0x7f);
    // CALL(aByteFill);
    ByteFill_Conv2(bgcoord(0, 0, vram->vBGMap0), vBGMap1 - vBGMap0, 0x7f);
    // hlcoord(0, 0, wAttrmap);
    // LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill_Conv2(coord(0, 0, wram->wAttrmap), SCREEN_WIDTH * SCREEN_HEIGHT, 0x0);
    // LD_HL(wBGPals1);
    uint8_t* hl = wram->wBGPals1;
    // LD_C(4 * LEN_2BPP_TILE);
    uint8_t c = 4 * LEN_2BPP_TILE;

    do {
    // load_white_palettes:
        // LD_A(LOW(PALRGB_WHITE));
        // LD_hli_A;
        *(hl++) = LOW(PALRGB_WHITE);
        // LD_A(HIGH(PALRGB_WHITE));
        // LD_hli_A;
        *(hl++) = HIGH(PALRGB_WHITE);
        // DEC_C;
        // IF_NZ goto load_white_palettes;
    } while(--c != 0);
    // XOR_A_A;
    // LDH_addr_A(hSCY);
    hSCY = 0x0;
    // LDH_addr_A(hSCX);
    hSCX = 0x0;
    // CALL(aEnableLCD);
    EnableLCD_Conv();
    // CALL(aWaitBGMap2);
    WaitBGMap2_Conv();
    // CALL(aSetPalettes);
    SetPalettes_Conv();
    // RET;

}

void ResetDisplayBetweenHallOfFameMons(void){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(BANK(wDecompressScratch));
    // LDH_addr_A(rSVBK);
    // LD_HL(wDecompressScratch);
    // LD_BC(wScratchAttrmap - wDecompressScratch);
    // LD_A(0x7f);
    // CALL(aByteFill);
    ByteFill_Conv2(wram->wDecompressScratch, wScratchAttrmap - wDecompressScratch, 0x7f);
    // hlbgcoord(0, 0, vBGMap0);
    // LD_DE(wDecompressScratch);
    // LD_B(0);
    // LD_C(4 * LEN_2BPP_TILE);
    // CALL(aRequest2bpp);
    CopyBytes_Conv2(bgcoord(0, 0, vram->vBGMap0), wram->wDecompressScratch, 4 * LEN_2BPP_TILE);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;
}
