#include "../constants.h"
#include "hm_moves.h"
#include "array.h"

//  HM moves can't be forgotten

void IsHM(void){
        CP_A(HM01);
    IF_C goto NotHM;
    SCF;
    RET;

NotHM:
        AND_A_A;
    RET;

}

bool IsHM_Conv(uint8_t a){
    return (a >= HM01);
}

void IsHMMove(void){
        LD_HL(mIsHMMove_HMMoves);
    LD_DE(1);
    JP(mIsInArray);

/* Currently not used?
HMMoves:
        //db ['CUT'];
    //db ['FLY'];
    //db ['SURF'];
    //db ['STRENGTH'];
    //db ['FLASH'];
    //db ['WATERFALL'];
    //db ['WHIRLPOOL'];
    //db ['-1'];  // end
*/
}

bool IsHMMove_Conv(uint8_t a){
    return IsInArray_Conv(mIsHMMove_HMMoves, 1, a) != 0xFFFF;
}
