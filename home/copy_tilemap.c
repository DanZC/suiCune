#include "../constants.h"
#include "copy_tilemap.h"

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

void SafeLoadTempTilemapToTilemap(void){
        XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aLoadTempTilemapToTilemap);
    LD_A(1);
    LDH_addr_A(hBGMapMode);
    RET;

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
