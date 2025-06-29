#include "../../constants.h"
#include "mapgroup_roofs.h"
#include "../../data/maps/roofs.h"

void LoadMapGroupRoof(void){
    // LD_A_addr(wMapGroup);
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mMapGroupRoofs);
    // ADD_HL_DE;
    // LD_A_hl;
    uint8_t a = MapGroupRoofs[gCurMapData.mapGroup];
    // CP_A(-1);
    // RET_Z ;
    if(a == 0xff)
        return;
    // LD_HL(mRoofs);
    // LD_BC(ROOF_LENGTH * LEN_2BPP_TILE);
    // CALL(aAddNTimes);
    // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x0a);
    // LD_BC(ROOF_LENGTH * LEN_2BPP_TILE);
    // CALL(aCopyBytes);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x0a, Roofs[a], 0, ROOF_LENGTH * LEN_2BPP_TILE);
    // RET;
}
