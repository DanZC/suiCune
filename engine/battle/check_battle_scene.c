#include "../../constants.h"
#include "check_battle_scene.h"
#include "../../home/copy.h"
#include "../../home/sram.h"

// Returns false if battle scene is turned off.
bool CheckBattleScene_Conv(void) {
    if(wram->wLinkMode == LINK_MOBILE) {
        if(gb_read(wcd2f) != 0) {
            return bit_test(wram->w5_dc00[0], 0);
        }
        OpenSRAM(MBANK(as4_a60c));  // MBC30 bank used by JP Crystal// inaccessible by MBC3
        uint8_t c = gb_read(s4_a60c);
        CloseSRAM();
        return bit_test(c, 0);
    }
    return !bit_test(wram->wOptions, BATTLE_SCENE);
}

void CheckBattleScene(void){
//  Return carry if battle scene is turned off.
    SET_PC(aCheckBattleScene);
    if(CheckBattleScene_Conv()) {
        AND_A_A;
    } else { 
        SCF;
    }
    RET;

    LD_A(MBANK(awLinkMode));
    LD_HL(wLinkMode);
    CALL(aGetFarWRAMByte);
    CP_A(LINK_MOBILE);
    IF_Z goto mobile;

    LD_A_addr(wOptions);
    BIT_A(BATTLE_SCENE);
    IF_NZ goto off;

    AND_A_A;
    RET;


mobile:
    LD_A_addr(wcd2f);
    AND_A_A;
    IF_NZ goto from_wram;

    LD_A(MBANK(as4_a60c));  // MBC30 bank used by JP Crystal// inaccessible by MBC3
    CALL(aOpenSRAM);
    LD_A_addr(s4_a60c);
    LD_C_A;
    CALL(aCloseSRAM);

    LD_A_C;
    BIT_C(0);
    IF_Z goto off;

    AND_A_A;
    RET;


from_wram:
    LD_A(MBANK(aw5_dc00));
    LD_HL(w5_dc00);
    CALL(aGetFarWRAMByte);
    BIT_A(0);
    IF_Z goto off;

    AND_A_A;
    RET;


off:
    SCF;
    RET;

}
