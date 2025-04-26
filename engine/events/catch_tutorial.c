#include "../../constants.h"
#include "catch_tutorial.h"
#include "../../home/copy.h"
#include "../../home/joypad.h"
#include "../battle/core.h"

void CatchTutorial(void){
    // LD_A_addr(wBattleType);
    // DEC_A;
    // LD_C_A;
    // LD_HL(mCatchTutorial_dw);
    // LD_B(0);
    // ADD_HL_BC;
    // ADD_HL_BC;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // JP_hl;
    

    // AutoInput:
        //db ['NO_INPUT', '0xff'];  // end
    static const uint8_t AutoInput[] = {
        NO_INPUT, 0xff
    };

// dw:
    //dw ['.DudeTutorial'];
    //dw ['.DudeTutorial'];
    //dw ['.DudeTutorial'];
    switch(wram->wBattleType) {
        default:
        case 0:
        case 1:
        case 2:
        // DudeTutorial:
        //  Back up your name to your Mom's name.
            // LD_HL(wPlayerName);
            // LD_DE(wMomsName);
            // LD_BC(NAME_LENGTH);
            // CALL(aCopyBytes);
            CopyBytes(wram->wMomsName, wram->wPlayerName, NAME_LENGTH);
        //  Copy Dude's name to your name
            // LD_HL(mCatchTutorial_Dude);
            // LD_DE(wPlayerName);
            // LD_BC(NAME_LENGTH);
            // CALL(aCopyBytes);
            U82CA(wram->wPlayerName, "DUDE@");

            // CALL(aCatchTutorial_LoadDudeData);
            // LoadDudeData:
            // LD_HL(wDudeNumItems);
            // LD_hl(1);
            wram->wDudeNumItems = 1;
            // INC_HL;
            // LD_hl(POTION);
            wram->wDudeItems[0] = POTION;
            // INC_HL;
            // LD_hl(1);
            wram->wDudeItems[1] = 1;
            // INC_HL;
            // LD_hl(-1);
            wram->wDudeItems[2] = 0xff;
            // LD_HL(wDudeNumKeyItems);
            // LD_hl(0);
            wram->wDudeNumKeyItems = 0;
            // INC_HL;
            // LD_hl(-1);
            wram->wDudeKeyItems[0] = 0xff;
            // LD_HL(wDudeNumBalls);
            // LD_A(1);
            // LD_hli_A;
            wram->wDudeNumBalls = 1;
            // LD_A(POKE_BALL);
            // LD_hli_A;
            wram->wDudeBalls[0] = POKE_BALL;
            // LD_hli_A;
            wram->wDudeBalls[1] = 5;
            // LD_hl(-1);
            wram->wDudeBalls[2] = 0xff;
            // RET;

            // XOR_A_A;
            // LDH_addr_A(hJoyDown);
            // LDH_addr_A(hJoyPressed);
            hram->hJoyDown = 0;
            hram->hJoyPressed = 0;
            // LD_A_addr(wOptions);
            // PUSH_AF;
            uint8_t options = wram->wOptions;
            // AND_A(~TEXT_DELAY_MASK);
            // ADD_A(TEXT_DELAY_MED);
            // LD_addr_A(wOptions);
            wram->wOptions = (options & ~TEXT_DELAY_MASK) | TEXT_DELAY_MED;
            // LD_HL(mCatchTutorial_AutoInput);
            // LD_A(BANK(aCatchTutorial_AutoInput));
            // CALL(aStartAutoInput);
            StartAutoInput(AutoInput);
            // CALLFAR(aStartBattle);
            StartBattle_Conv();
            // CALL(aStopAutoInput);
            StopAutoInput();
            // POP_AF;

            // LD_addr_A(wOptions);
            wram->wOptions = options;
            // LD_HL(wMomsName);
            // LD_DE(wPlayerName);
            // LD_BC(NAME_LENGTH);
            // CALL(aCopyBytes);
            CopyBytes(wram->wPlayerName, wram->wMomsName, NAME_LENGTH);
            // RET;
            return;


        // Dude:
            //db ['"DUDE@"'];

    }
}
