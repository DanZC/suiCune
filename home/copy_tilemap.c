#include "../constants.h"
#include "copy_tilemap.h"
#include "copy.h"

//  Load wTilemap into wTempTilemap
void LoadTilemapToTempTilemap(void){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(MBANK(awTempTilemap));
    // LDH_addr_A(rSVBK);
    // uint8_t svbk = gb_read(rSVBK);
    // gb_write(rSVBK, MBANK(awTempTilemap));
    // hlcoord(0, 0, wTilemap);
    // decoord(0, 0, wTempTilemap);
    // LD_BC(wTilemapEnd - wTilemap);
    // CALL(aCopyBytes);
    CopyBytes(coord(0, 0, wram->wTempTilemap), coord(0, 0, wram->wTilemap), sizeof(wram->wTilemap));
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;
    // gb_write(rSVBK, svbk);
}

void SafeLoadTempTilemapToTilemap(void){
    //     XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // CALL(aLoadTempTilemapToTilemap);
    LoadTempTilemapToTilemap();
    // LD_A(1);
    // LDH_addr_A(hBGMapMode);
    // RET;
    hram->hBGMapMode = BGMAPMODE_UPDATE_TILES;
}

//  Load wTempTilemap into wTilemap
void LoadTempTilemapToTilemap(void){
    CopyBytes(coord(0, 0, wram->wTilemap), coord(0, 0, wram->wTempTilemap), sizeof(wram->wTilemap));
}