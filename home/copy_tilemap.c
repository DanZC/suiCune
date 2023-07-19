#include "../constants.h"
#include "copy_tilemap.h"
#include "copy.h"

void LoadTilemapToTempTilemap(void){
    //  Load wTilemap into wTempTilemap
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awTempTilemap));
    LDH_addr_A(rSVBK);
    hlcoord(0, 0, wTilemap);
    decoord(0, 0, wTempTilemap);
    LD_BC(wTilemapEnd - wTilemap);
    CALL(aCopyBytes);
    POP_AF;
    LDH_addr_A(rSVBK);
    RET;

}

//  Load wTilemap into wTempTilemap
void LoadTilemapToTempTilemap_Conv(void){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(MBANK(awTempTilemap));
    // LDH_addr_A(rSVBK);
    uint8_t svbk = gb_read(rSVBK);
    gb_write(rSVBK, MBANK(awTempTilemap));
    // hlcoord(0, 0, wTilemap);
    // decoord(0, 0, wTempTilemap);
    // LD_BC(wTilemapEnd - wTilemap);
    // CALL(aCopyBytes);
    CopyBytes_Conv(coord(0, 0, wTempTilemap), coord(0, 0, wTilemap), wTilemapEnd - wTilemap);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;
    gb_write(rSVBK, svbk);
}

void SafeLoadTempTilemapToTilemap(void){
        XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aLoadTempTilemapToTilemap);
    LD_A(1);
    LDH_addr_A(hBGMapMode);
    RET;

}

void SafeLoadTempTilemapToTilemap_Conv(void){
    //     XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0;
    // CALL(aLoadTempTilemapToTilemap);
    LoadTempTilemapToTilemap_Conv();
    // LD_A(1);
    // LDH_addr_A(hBGMapMode);
    // RET;
    hram->hBGMapMode = 1;
}

void LoadTempTilemapToTilemap(void){
    //  Load wTempTilemap into wTilemap
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awTempTilemap));
    LDH_addr_A(rSVBK);
    hlcoord(0, 0, wTempTilemap);
    decoord(0, 0, wTilemap);
    LD_BC(wTilemapEnd - wTilemap);
    CALL(aCopyBytes);
    POP_AF;
    LDH_addr_A(rSVBK);
    RET;

}

void LoadTempTilemapToTilemap_Conv(void){
    uint8_t svbk = gb_read(rSVBK);
    gb_write(rSVBK, MBANK(awTempTilemap));
    CopyBytes_Conv(coord(0, 0, wTilemap), coord(0, 0, wTempTilemap), wTilemapEnd - wTilemap);
    gb_write(rSVBK, svbk);
}