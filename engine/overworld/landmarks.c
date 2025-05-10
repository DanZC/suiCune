#include "../../constants.h"
#include "landmarks.h"
#include "../../data/maps/landmarks.h"
#include "../../home/map.h"

//  Return coordinates (d, e) of landmark e.
struct Coords GetLandmarkCoords(uint8_t e){
    // PUSH_HL;
    // LD_L_E;
    // LD_H(0);
    // ADD_HL_HL;
    // ADD_HL_HL;
    // LD_DE(mLandmarks);
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_E_A;
    // LD_D_hl;
    // POP_HL;
    // RET;
    return (struct Coords){.x = Landmarks[e].x + 8, .y = Landmarks[e].y + 16};
}

//  Copy the name of landmark e to wStringBuffer1.
uint8_t* GetLandmarkName(uint8_t e){
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;

    // LD_L_E;
    // LD_H(0);
    // ADD_HL_HL;
    // ADD_HL_HL;
    // LD_DE(mLandmarks + 2);
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    const char* name = Landmarks[e].name;

    // LD_DE(wStringBuffer1);
    // LD_C(18);
    U82CA(wram->wStringBuffer1, name);


// copy:
    // LD_A_hli;
    // LD_de_A;
    // INC_DE;
    // DEC_C;
    // IF_NZ goto copy;

    // POP_BC;
    // POP_DE;
    // POP_HL;
    // RET;

// INCLUDE "data/maps/landmarks.asm"

    // return RegionCheck();
    return wram->wStringBuffer1;
}

//  Checks if the player is in Kanto or Johto.
//  If in Johto, returns 0 (JOHTO_REGION).
//  If in Kanto, returns 1 (KANTO_REGION).
int RegionCheck(void){
    // LD_A_addr(wMapGroup);
    // LD_B_A;
    // LD_A_addr(wMapNumber);
    // LD_C_A;
    // CALL(aGetWorldMapLocation);
    uint8_t loc = GetWorldMapLocation(wram->wMapGroup, wram->wMapNumber);
    // CP_A(LANDMARK_FAST_SHIP);  // S.S. Aqua
    // IF_Z goto johto;
    if(loc == LANDMARK_FAST_SHIP)
        return JOHTO_REGION;
    // CP_A(LANDMARK_SPECIAL);
    // IF_NZ goto checkagain;
//  In a special map, get the backup map group / map id
    if(loc == LANDMARK_SPECIAL) {
        // LD_A_addr(wBackupMapGroup);
        // LD_B_A;
        // LD_A_addr(wBackupMapNumber);
        // LD_C_A;
        // CALL(aGetWorldMapLocation);
        loc = GetWorldMapLocation(wram->wBackupMapGroup, wram->wBackupMapNumber);
    }


// checkagain:
    // CP_A(KANTO_LANDMARK);
    // IF_C goto johto;
    if(loc < KANTO_LANDMARK)
        return JOHTO_REGION;

//  Victory Road area is considered to be Johto.
    // CP_A(LANDMARK_VICTORY_ROAD);
    // IF_C goto kanto;
    if(loc < LANDMARK_VICTORY_ROAD)
        return KANTO_REGION;


// johto:
    // LD_E(JOHTO_REGION);
    // RET;
    return JOHTO_REGION;

// kanto:
    // LD_E(KANTO_REGION);
    // RET;
}