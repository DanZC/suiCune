#include "../constants.h"
#include "region.h"
#include "map.h"

void IsInJohto(void){
    //  Return 0 if the player is in Johto, and 1 in Kanto.

    LD_A_addr(wMapGroup);
    LD_B_A;
    LD_A_addr(wMapNumber);
    LD_C_A;
    CALL(aGetWorldMapLocation);

    CP_A(LANDMARK_FAST_SHIP);
    IF_Z goto Johto;

    CP_A(LANDMARK_SPECIAL);
    IF_NZ goto CheckRegion;

    LD_A_addr(wBackupMapGroup);
    LD_B_A;
    LD_A_addr(wBackupMapNumber);
    LD_C_A;
    CALL(aGetWorldMapLocation);


CheckRegion:
        CP_A(KANTO_LANDMARK);
    IF_NC goto Kanto;


Johto:
        XOR_A_A;  // JOHTO_REGION
    RET;


Kanto:
        LD_A(KANTO_REGION);
    RET;

}

//  Return 0 if the player is in Johto, and 1 in Kanto.
uint8_t IsInJohto_Conv(void){
    //REG_B = gb_read(wMapGroup);
    //REG_C = gb_read(wMapNumber);
    //CALL(aGetWorldMapLocation);
    uint8_t landmark = GetWorldMapLocation_Conv(gb_read(wMapGroup), gb_read(wMapNumber));

    if(landmark == LANDMARK_FAST_SHIP)
        return JOHTO_REGION;

    if(landmark == LANDMARK_SPECIAL)
    {
        //REG_B = gb_read(wBackupMapGroup);
        //REG_C = gb_read(wBackupMapNumber);
        //CALL(aGetWorldMapLocation);
        landmark = GetWorldMapLocation_Conv(gb_read(wBackupMapGroup), gb_read(wBackupMapNumber));
    }

    if(landmark >= KANTO_LANDMARK)
        return KANTO_REGION;
    else 
        return JOHTO_REGION;
}

void SetXYCompareFlags(void){
    //  //  dummied out
    RET;

}
