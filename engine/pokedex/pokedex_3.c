#include "../../constants.h"
#include "pokedex_3.h"
#include "../../home/tilemap.h"
#include "../../home/copy.h"
#include "../../home/text.h"

void LoadSGBPokedexGFX(void){
    // LD_HL(mSGBPokedexGFX_LZ);
    // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x31);
    // CALL(aDecompress);
    LoadPNG2bppAssetToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x31, SGBPokedexGFX_LZ);
    // RET;
}

void LoadSGBPokedexGFX2(void){
    // LD_HL(mSGBPokedexGFX_LZ);
    // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x31);
    // LD_BC((BANK(aSGBPokedexGFX_LZ) << 8) | 58);
    // CALL(aDecompressRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x31, SGBPokedexGFX_LZ, 0, 58);
    // RET;
}

const char SGBPokedexGFX_LZ[] = "gfx/pokedex/pokedex_sgb.png";

void LoadQuestionMarkPic(void){
    static const char QuestionMarkLZ[] = "gfx/pokedex/question_mark.png";
    // LD_HL(mLoadQuestionMarkPic_QuestionMarkLZ);
    // LD_DE(sScratch);
    // CALL(aDecompress);
    LoadPNG2bppAssetToVRAM(GBToRAMAddr(sScratch), QuestionMarkLZ);
    // RET;
}

void DrawPokedexListWindow(void){
    // LD_A(0x32);
    // hlcoord(0, 17, wTilemap);
    // LD_BC(12);
    // CALL(aByteFill);
    ByteFill(coord(0, 17, wram->wTilemap), 12, 0x32);
    // hlcoord(0, 1, wTilemap);
    // LD_BC((15 << 8) | 11);
    // CALL(aClearBox);
    ClearBox(coord(0, 1, wram->wTilemap), 11, 15);
    // LD_A(0x34);
    // hlcoord(0, 0, wTilemap);
    // LD_BC(11);
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wTilemap), 11, 0x34);
    // LD_A(0x39);
    // hlcoord(0, 16, wTilemap);
    // LD_BC(11);
    // CALL(aByteFill);
    ByteFill(coord(0, 16, wram->wTilemap), 11, 0x39);
    // hlcoord(5, 0, wTilemap);
    // LD_hl(0x3f);
    *coord(5, 0, wram->wTilemap) = 0x3f;
    // hlcoord(5, 16, wTilemap);
    // LD_hl(0x40);
    *coord(5, 16, wram->wTilemap) = 0x40;
    // LD_A_addr(wCurDexMode);
    // CP_A(DEXMODE_OLD);
    // IF_Z goto OldMode;
    if(wram->wCurDexMode == DEXMODE_OLD) {
    // OldMode:
    //  no scroll bar
        // hlcoord(11, 0, wTilemap);
        // LD_hl(0x66);
        *coord(11, 0, wram->wTilemap) = 0x66;
        // LD_A(0x67);
        // hlcoord(11, 1, wTilemap);
        // LD_B(SCREEN_HEIGHT - 3);
        // CALL(aPokedex_FillColumn2);
        tile_t* hl = Pokedex_FillColumn2(coord(11, 1, wram->wTilemap), 0x67, SCREEN_HEIGHT - 3);
        // LD_hl(0x68);
        *hl = 0x68;
    }
    else {
    //  scroll bar
        // hlcoord(11, 0, wTilemap);
        // LD_hl(0x50);
        *coord(11, 0, wram->wTilemap) = 0x50;
        // LD_A(0x51);
        // hlcoord(11, 1, wTilemap);
        // LD_B(SCREEN_HEIGHT - 3);
        // CALL(aPokedex_FillColumn2);
        tile_t* hl = Pokedex_FillColumn2(coord(11, 1, wram->wTilemap), 0x51, SCREEN_HEIGHT - 3);
        // LD_hl(0x52);
        *hl = 0x52;
        // goto Done;
    }

// Done:
    // RET;
}

void DrawPokedexSearchResultsWindow(void){
    static const char esults_D[] = 
    //  (SEARCH R)
        "ESULTS"
        t_next ""
    //  (### FOUN)
        t_next "D!";
    // LD_A(0x34);
    // hlcoord(0, 0, wTilemap);
    // LD_BC(11);
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wTilemap), 11, 0x34);
    // LD_A(0x39);
    // hlcoord(0, 10, wTilemap);
    // LD_BC(11);
    // CALL(aByteFill);
    ByteFill(coord(0, 10, wram->wTilemap), 11, 0x39);
    // hlcoord(5, 0, wTilemap);
    // LD_hl(0x3f);
    *coord(5, 0, wram->wTilemap) = 0x3f;
    // hlcoord(5, 10, wTilemap);
    // LD_hl(0x40);
    *coord(5, 10, wram->wTilemap) = 0x40;
    // hlcoord(11, 0, wTilemap);
    // LD_hl(0x66);
    *coord(11, 0, wram->wTilemap) = 0x66;
    // LD_A(0x67);
    // hlcoord(11, 1, wTilemap);
    // LD_B(SCREEN_HEIGHT / 2);
    // CALL(aPokedex_FillColumn2);
    tile_t* hl = Pokedex_FillColumn2(coord(11, 1, wram->wTilemap), 0x67, SCREEN_HEIGHT / 2);
    // LD_hl(0x68);
    *hl = 0x68;
    // LD_A(0x34);
    // hlcoord(0, 11, wTilemap);
    // LD_BC(11);
    // CALL(aByteFill);
    ByteFill(coord(0, 11, wram->wTilemap), 11, 0x34);
    // LD_A(0x39);
    // hlcoord(0, 17, wTilemap);
    // LD_BC(11);
    // CALL(aByteFill);
    ByteFill(coord(0, 17, wram->wTilemap), 11, 0x39);
    // hlcoord(11, 11, wTilemap);
    // LD_hl(0x66);
    *coord(11, 11, wram->wTilemap) = 0x66;
    // LD_A(0x67);
    // hlcoord(11, 12, wTilemap);
    // LD_B(5);
    // CALL(aPokedex_FillColumn2);
    hl = Pokedex_FillColumn2(coord(11, 12, wram->wTilemap), 0x67, 5);
    // LD_hl(0x68);
    *hl = 0x68;
    // hlcoord(0, 12, wTilemap);
    // LD_BC((5 << 8) | 11);
    // CALL(aClearBox);
    ClearBox(coord(0, 12, wram->wTilemap), 11, 5);
    // LD_DE(mDrawPokedexSearchResultsWindow_esults_D);
    // hlcoord(0, 12, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(esults_D), coord(0, 12, wram->wTilemap));
    // RET;
}

void DrawDexEntryScreenRightEdge(void){
    // LDH_A_addr(hBGMapAddress);
    // LD_L_A;
    // LDH_A_addr(hBGMapAddress + 1);
    // LD_H_A;
    // PUSH_HL;
    uint16_t bgMapAddress = hram.hBGMapAddress;
    // INC_HL;
    // LD_A_L;
    // LDH_addr_A(hBGMapAddress);
    // LD_A_H;
    // LDH_addr_A(hBGMapAddress + 1);
    hram.hBGMapAddress++;
    // hlcoord(19, 0, wTilemap);
    // LD_hl(0x66);
    *coord(19, 0, wram->wTilemap) = 0x66;
    // hlcoord(19, 1, wTilemap);
    // LD_A(0x67);
    // LD_B(15);
    // CALL(aPokedex_FillColumn2);
    tile_t* hl = Pokedex_FillColumn2(coord(19, 1, wram->wTilemap), 0x67, 15);
    // LD_hl(0x68);
    *hl = 0x68;
    // hlcoord(19, 17, wTilemap);
    // LD_hl(0x3c);
    *coord(19, 17, wram->wTilemap) = 0x3c;
    // XOR_A_A;
    // LD_B(SCREEN_HEIGHT);
    // hlcoord(19, 0, wAttrmap);
    // CALL(aPokedex_FillColumn2);
    Pokedex_FillColumn2(coord(19, 0, wram->wAttrmap), 0x0, SCREEN_HEIGHT);
    // CALL(aWaitBGMap2);
    WaitBGMap2();
    // POP_HL;
    // LD_A_L;
    // LDH_addr_A(hBGMapAddress);
    // LD_A_H;
    // LDH_addr_A(hBGMapAddress + 1);
    hram.hBGMapAddress = bgMapAddress;
    // RET;
}

//  A local duplicate of Pokedex_FillColumn.
tile_t* Pokedex_FillColumn2(tile_t* hl, uint8_t a, uint8_t b){
    // PUSH_DE;
    // LD_DE(SCREEN_WIDTH);

    do {
    // loop:
        // LD_hl_A;
        *hl = a;
        // ADD_HL_DE;
        hl += SCREEN_WIDTH;
        // DEC_B;
        // IF_NZ goto loop;
    } while(--b != 0);
    // POP_DE;
    // RET;
    return hl;
}
