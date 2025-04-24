#include "../../constants.h"
#include "place_waiting_text.h"
#include "link.h"
#include "../../home/text.h"
#include "../../home/delay.h"

void PlaceWaitingText(void){
    // hlcoord(3, 10, wTilemap);
    // LD_B(1);
    // LD_C(11);

    // LD_A_addr(wBattleMode);
    // AND_A_A;
    // IF_Z goto notinbattle;
    if(wram->wBattleMode != 0) {
        // CALL(aTextbox);
        Textbox(coord(3, 10, wram->wTilemap), 1, 11);
        // goto proceed;
    } else {
    // notinbattle:
        // PREDEF(pLinkTextboxAtHL);
        LinkTextboxAtHL_Conv(coord(3, 10, wram->wTilemap), 1, 11);
    }

// proceed:
    // hlcoord(4, 11, wTilemap);
    // LD_DE(mPlaceWaitingText_Waiting);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C("Waiting...!"), coord(4, 11, wram->wTilemap));
    // LD_C(50);
    // JP(mDelayFrames);
    return DelayFrames(50);
}
