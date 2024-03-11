#include "../../constants.h"
#include "unown_walls.h"
#include "../../home/map.h"
#include "../../home/flag.h"
#include "../../data/maps/attributes.h"

void HoOhChamber(void){
    LD_HL(wPartySpecies);
    LD_A_hl;
    CP_A(HO_OH);  // is Ho-oh the first Pokémon in the party?
    IF_NZ goto done;  // if not, we're done
    CALL(aGetMapAttributesPointer);  // pointless?
    LD_DE(EVENT_WALL_OPENED_IN_HO_OH_CHAMBER);
    LD_B(SET_FLAG);
    CALL(aEventFlagAction);

done:
    RET;

}

void OmanyteChamber(void){
    CALL(aGetMapAttributesPointer);  // pointless?
    LD_DE(EVENT_WALL_OPENED_IN_OMANYTE_CHAMBER);
    LD_B(CHECK_FLAG);
    CALL(aEventFlagAction);
    LD_A_C;
    AND_A_A;
    IF_NZ goto nope;

    LD_A(WATER_STONE);
    LD_addr_A(wCurItem);
    LD_HL(wNumItems);
    CALL(aCheckItem);
    IF_C goto open;

    LD_A_addr(wPartyCount);
    LD_B_A;
    INC_B;

loop:
    DEC_B;
    IF_Z goto nope;
    LD_A_B;
    DEC_A;
    LD_addr_A(wCurPartyMon);
    PUSH_BC;
    LD_A(MON_ITEM);
    CALL(aGetPartyParamLocation);
    POP_BC;
    LD_A_hl;
    CP_A(WATER_STONE);
    IF_NZ goto loop;


open:
    CALL(aGetMapAttributesPointer);  // pointless?
    LD_DE(EVENT_WALL_OPENED_IN_OMANYTE_CHAMBER);
    LD_B(SET_FLAG);
    CALL(aEventFlagAction);


nope:
    RET;

}

void SpecialAerodactylChamber(void){
    PUSH_DE;
    PUSH_BC;

    CALL(aGetMapAttributesPointer);
    LD_A_H;
    CP_A(HIGH(aRuinsOfAlphAerodactylChamber_MapAttributes));
    IF_NZ goto nope;
    LD_A_L;
    CP_A(LOW(aRuinsOfAlphAerodactylChamber_MapAttributes));
    IF_NZ goto nope;

    LD_DE(EVENT_WALL_OPENED_IN_AERODACTYL_CHAMBER);
    LD_B(SET_FLAG);
    CALL(aEventFlagAction);

    SCF;
    goto done;


nope:
    AND_A_A;


done:
    POP_BC;
    POP_DE;
    RET;

}

bool SpecialAerodactylChamber_Conv(void){
    // PUSH_DE;
    // PUSH_BC;

    // CALL(aGetMapAttributesPointer);
    const struct MapAttr* attr = GetMapAttributesPointer_Conv2();
    // LD_A_H;
    // CP_A(HIGH(aRuinsOfAlphAerodactylChamber_MapAttributes));
    // IF_NZ goto nope;
    // LD_A_L;
    // CP_A(LOW(aRuinsOfAlphAerodactylChamber_MapAttributes));
    // IF_NZ goto nope;
    if(attr != &RuinsOfAlphAerodactylChamber_MapAttributes)
        return false;

    // LD_DE(EVENT_WALL_OPENED_IN_AERODACTYL_CHAMBER);
    // LD_B(SET_FLAG);
    // CALL(aEventFlagAction);
    EventFlagAction_Conv2(EVENT_WALL_OPENED_IN_AERODACTYL_CHAMBER, SET_FLAG);

    // SCF;
    // goto done;


// nope:
    // AND_A_A;


// done:
    // POP_BC;
    // POP_DE;
    // RET;
    return true;
}

void SpecialKabutoChamber(void){
    PUSH_HL;
    PUSH_DE;

    CALL(aGetMapAttributesPointer);
    LD_A_H;
    CP_A(HIGH(aRuinsOfAlphKabutoChamber_MapAttributes));
    IF_NZ goto done;
    LD_A_L;
    CP_A(LOW(aRuinsOfAlphKabutoChamber_MapAttributes));
    IF_NZ goto done;

    LD_DE(EVENT_WALL_OPENED_IN_KABUTO_CHAMBER);
    LD_B(SET_FLAG);
    CALL(aEventFlagAction);


done:
    POP_DE;
    POP_HL;
    RET;

}

void DisplayUnownWords(void){
    LD_A_addr(wScriptVar);
    LD_HL(mMenuHeaders_UnownWalls);
    AND_A_A;
    IF_Z goto load;

    LD_D(0x0);
    LD_E(0x5);

loop:
    ADD_HL_DE;
    DEC_A;
    IF_NZ goto loop;


load:
    CALL(aLoadMenuHeader);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aMenuBox);
    CALL(aUpdateSprites);
    CALL(aApplyTilemap);
    CALL(aMenuBoxCoord2Tile);
    INC_HL;
    LD_D(0);
    LD_E(SCREEN_WIDTH);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_addr(wScriptVar);
    LD_C_A;
    LD_DE(mUnownWalls);
    AND_A_A;
    IF_Z goto copy;

loop2:
    LD_A_de;
    INC_DE;
    CP_A(-1);
    IF_NZ goto loop2;
    DEC_C;
    IF_NZ goto loop2;

copy:
    CALL(av_DisplayUnownWords_CopyWord);
    LD_BC(wAttrmap - wTilemap);
    ADD_HL_BC;
    CALL(av_DisplayUnownWords_FillAttr);
    CALL(aWaitBGMap2);
    CALL(aJoyWaitAorB);
    CALL(aPlayClickSFX);
    CALL(aCloseWindow);
    RET;

// INCLUDE "data/events/unown_walls.asm"

    return v_DisplayUnownWords_FillAttr();
}

void v_DisplayUnownWords_FillAttr(void){
    LD_A_de;
    CP_A(0xff);
    RET_Z ;
    CP_A(0x60);
    LD_A(VRAM_BANK_1 | PAL_BG_BROWN);
    IF_C goto got_pal;
    LD_A(PAL_BG_BROWN);


got_pal:
    CALL(av_DisplayUnownWords_FillAttr_PlaceSquare);
    INC_HL;
    INC_HL;
    INC_DE;
    JR(mv_DisplayUnownWords_FillAttr);


PlaceSquare:
    PUSH_HL;
    LD_hli_A;
    LD_hld_A;
    LD_B(0);
    LD_C(SCREEN_WIDTH);
    ADD_HL_BC;
    LD_hli_A;
    LD_hl_A;
    POP_HL;
    RET;

}

void v_DisplayUnownWords_CopyWord(void){
    PUSH_HL;
    PUSH_DE;

word_loop:
    LD_A_de;
    CP_A(0xff);
    IF_Z goto word_done;
    LD_C_A;
    CALL(av_DisplayUnownWords_CopyWord_ConvertChar);
    INC_HL;
    INC_HL;
    INC_DE;
    goto word_loop;


word_done:
    POP_DE;
    POP_HL;
    RET;


ConvertChar:
    PUSH_HL;
    LD_A_C;
    CP_A(0x60);
    IF_Z goto Tile60;
    CP_A(0x62);
    IF_Z goto Tile62;
    CP_A(0x64);
    IF_Z goto Tile64;
    LD_hli_A;
    INC_A;
    LD_hld_A;
    DEC_A;
    LD_B(0);
    LD_C(SCREEN_WIDTH);
    ADD_HL_BC;
    LD_C(0x10);
    ADD_A_C;
    LD_hli_A;
    INC_A;
    LD_hl_A;
    POP_HL;
    RET;


Tile60:
    LD_hl(0x5b);
    INC_HL;
    LD_hl(0x5c);
    LD_BC(SCREEN_WIDTH - 1);
    ADD_HL_BC;
    LD_hl(0x4d);
    INC_HL;
    LD_hl(0x5d);
    POP_HL;
    RET;


Tile62:
    LD_hl(0x4e);
    INC_HL;
    LD_hl(0x4f);
    LD_BC(SCREEN_WIDTH - 1);
    ADD_HL_BC;
    LD_hl(0x5e);
    INC_HL;
    LD_hl(0x5f);
    POP_HL;
    RET;


Tile64:
    LD_hl(0x2);
    INC_HL;
    LD_hl(0x3);
    LD_BC(SCREEN_WIDTH - 1);
    ADD_HL_BC;
    LD_hl(0x3);
    INC_HL;
    LD_hl(0x2);
    POP_HL;
    RET;

}
