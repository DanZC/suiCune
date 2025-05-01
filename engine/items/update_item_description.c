#include "../../constants.h"
#include "update_item_description.h"
#include "print_item_description.h"
#include "../../home/text.h"

void UpdateItemDescription(void){
    // LD_A_addr(wMenuSelection);
    // LD_addr_A(wCurSpecies);
    wram->wCurSpecies = wram->wMenuSelection;
    // hlcoord(0, 12, wTilemap);
    // LD_B(4);
    // LD_C(SCREEN_WIDTH - 2);
    // CALL(aTextbox);
    Textbox(coord(0, 12, wram->wTilemap), 4, SCREEN_WIDTH - 2);
    // LD_A_addr(wMenuSelection);
    // CP_A(-1);
    // RET_Z ;
    if(wram->wMenuSelection == 0xff)
        return;
    // decoord(1, 14, wTilemap);
    // FARCALL(aPrintItemDescription);
    PrintItemDescription(coord(1, 14, wram->wTilemap), wram->wCurSpecies);
    // RET;
}
