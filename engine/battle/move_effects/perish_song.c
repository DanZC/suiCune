#include "../../../constants.h"
#include "perish_song.h"
#include "../effect_commands.h"
#include "../../../home/battle.h"
#include "../../../home/battle_vars.h"
#include "../../../data/text/battle.h"

void BattleCommand_PerishSong(void){
//  perishsong

    // LD_HL(wPlayerSubStatus1);
    uint8_t* hl = &wram->wPlayerSubStatus1;
    uint8_t* de = &wram->wEnemySubStatus1;
    // LD_DE(wEnemySubStatus1);
    // BIT_hl(SUBSTATUS_PERISH);
    // IF_Z goto ok;

    // LD_A_de;
    // BIT_A(SUBSTATUS_PERISH);
    // IF_NZ goto failed;
    if(bit_test(*hl, SUBSTATUS_PERISH) && bit_test(*de, SUBSTATUS_PERISH)) {
    // failed:
        // CALL(aAnimateFailedMove);
        AnimateFailedMove();
        // JP(mPrintButItFailed);
        return PrintButItFailed();
    }


// ok:
    // BIT_hl(SUBSTATUS_PERISH);
    // IF_NZ goto enemy;

    if(!bit_test(*hl, SUBSTATUS_PERISH)) {
        // SET_hl(SUBSTATUS_PERISH);
        bit_set(*hl, SUBSTATUS_PERISH);
        // LD_A(4);
        // LD_addr_A(wPlayerPerishCount);
        wram->wPlayerPerishCount = 4;
    }

// enemy:
    // LD_A_de;
    // BIT_A(SUBSTATUS_PERISH);
    // IF_NZ goto done;

    if(!bit_test(*de, SUBSTATUS_PERISH)) {
        // SET_A(SUBSTATUS_PERISH);
        // LD_de_A;
        bit_set(*de, SUBSTATUS_PERISH);
        // LD_A(4);
        // LD_addr_A(wEnemyPerishCount);
        wram->wEnemyPerishCount = 4;
    }

// done:
    // CALL(aAnimateCurrentMove);
    AnimateCurrentMove();
    // LD_HL(mStartPerishText);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox_Conv2(StartPerishText);

}
