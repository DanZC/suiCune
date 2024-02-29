#include "../../constants.h"
#include "townmap_convertlinebreakcharacters.h"
#include "../../charmap.h"
#include "../../home/text.h"

void TownMap_ConvertLineBreakCharacters(void){
    // LD_HL(wStringBuffer1);
    uint8_t* hl = wram->wStringBuffer1;

    while(1) {
    // loop:
        // LD_A_hl;
        uint8_t a = *hl;
        // CP_A(CHAR_TERM);
        // IF_Z goto end;
        if(a == CHAR_TERM)
            break;
        // CP_A(CHAR_LM_SLB);
        // IF_Z goto line_feed;
        // CP_A(CHAR_SOFTLB);
        // IF_Z goto line_feed;
        if(a == CHAR_LM_SLB || a == CHAR_SOFTLB) {
        // line_feed:
            // LD_hl(CHAR_LF);
            *hl = CHAR_LF;
            break;
        }
        // INC_HL;
        hl++;
    }


// end:
    // LD_DE(wStringBuffer1);
    // hlcoord(9, 0, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(wram->wStringBuffer1, coord(9, 0, wram->wTilemap));
    // RET;
}
