#include "../constants.h"
#include "mobile.h"

void MobileAPI(void){
    //  Mobile
    CP_A(0x2);
    LD_addr_A(wMobileAPIIndex);
    LD_A_L;
    LD_addr_A(wc986);
    LD_A_H;
    LD_addr_A(wc987);
    IF_NZ goto okay;

    LD_addr_A(wc982);
    LD_A_L;
    LD_addr_A(wc981);
    LD_HL(wc983);
    LD_A_C;
    LD_hli_A;
    LD_A_B;
    LD_hl_A;


okay:
        LD_HL(wc822);
    SET_hl(6);
    LDH_A_addr(hROMBank);
    PUSH_AF;
    LD_A(BANK(av_MobileAPI));
    LD_addr_A(wc981);
    RST(aBankswitch);

    JP(mv_MobileAPI);

}

void ReturnMobileAPI(void){
    //  Return from _MobileAPI
    LD_addr_A(wc986);
    LD_A_L;
    LD_addr_A(wc987);
    LD_A_H;
    LD_addr_A(wMobileAPIIndex);

    POP_BC;
    LD_A_B;
    LD_addr_A(wc981);
    RST(aBankswitch);

    LD_HL(wc822);
    RES_hl(6);
    LD_HL(wc987);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_A_addr(wc986);
    RET;

}

void MobileReceive(void){
    LDH_A_addr(hROMBank);
    PUSH_AF;
    LD_A(BANK(av_MobileReceive));
    LD_addr_A(wc981);
    RST(aBankswitch);

    CALL(av_MobileReceive);
    POP_BC;
    LD_A_B;
    LD_addr_A(wc981);
    RST(aBankswitch);

    RET;

}

void MobileTimer(void){
        PUSH_AF;
    PUSH_BC;
    PUSH_DE;
    PUSH_HL;

    LDH_A_addr(hMobile);
    AND_A_A;
    IF_Z goto pop_ret;

    XOR_A_A;
    LDH_addr_A(rTAC);

//  Turn off timer interrupt
    LDH_A_addr(rIF);
    AND_A(1 << VBLANK | 1 << LCD_STAT | 1 << SERIAL | 1 << JOYPAD);
    LDH_addr_A(rIF);

    LD_A_addr(wc86a);
    OR_A_A;
    IF_Z goto pop_ret;

    LD_A_addr(wc822);
    BIT_A(1);
    IF_NZ goto skip_timer;

    LDH_A_addr(rSC);
    AND_A(1 << rSC_ON);
    IF_NZ goto skip_timer;

    LDH_A_addr(hROMBank);
    PUSH_AF;
    LD_A(BANK(av_Timer));
    LD_addr_A(wc981);
    RST(aBankswitch);

    CALL(av_Timer);

    POP_BC;
    LD_A_B;
    LD_addr_A(wc981);
    RST(aBankswitch);


skip_timer:
        LDH_A_addr(rTMA);
    LDH_addr_A(rTIMA);

    LD_A(1 << rTAC_ON | rTAC_65536_HZ);
    LDH_addr_A(rTAC);


pop_ret:
        POP_HL;
    POP_DE;
    POP_BC;
    POP_AF;
    RET;

}

void Function3ed7(void){
    //  //  unreferenced
    LD_addr_A(0xdc02);
    LDH_A_addr(hROMBank);
    PUSH_AF;
    LD_A(BANK(aFunction114243));
    RST(aBankswitch);

    CALL(aFunction114243);
    POP_BC;
    LD_A_B;
    RST(aBankswitch);

    LD_A_addr(0xdc02);
    RET;

}

void Function3eea(void){
        PUSH_HL;
    PUSH_BC;
    LD_DE(wAttrmap - wTilemap);
    ADD_HL_DE;
    INC_B;
    INC_B;
    INC_C;
    INC_C;
    CALL(aFunction3f35);
    POP_BC;
    POP_HL;
    CALL(aMobileHome_PlaceBox);
    RET;

}

void Function3efd(void){
    //  //  unreferenced
    PUSH_HL;
    hlcoord(0, 12, wTilemap);
    LD_B(4);
    LD_C(18);
    CALL(aFunction3efd_fill_attr);
    POP_HL;
    CALL(aPrintTextboxText);
    RET;


fill_attr:
        PUSH_HL;
    PUSH_BC;
    LD_DE(wAttrmap - wTilemap);
    ADD_HL_DE;
    INC_B;
    INC_B;
    INC_C;
    INC_C;
    CALL(aFunction3f35);
    POP_BC;
    POP_HL;
    CALL(aTextboxBorder);
    RET;

}

void Function3f20(void){
        hlcoord(0, 0, wAttrmap);
    LD_B(6);
    LD_C(20);
    CALL(aFunction3f35);
    hlcoord(0, 0, wTilemap);
    LD_B(4);
    LD_C(18);
    CALL(aMobileHome_PlaceBox);
    RET;

}

void Function3f35(void){
        LD_A(6);
    LD_DE(SCREEN_WIDTH);

row:
        PUSH_BC;
    PUSH_HL;

col:
        LD_hli_A;
    DEC_C;
    IF_NZ goto col;
    POP_HL;
    ADD_HL_DE;
    POP_BC;
    DEC_B;
    IF_NZ goto row;
    RET;

}

void MobileHome_PlaceBox(void){
        PUSH_BC;
    CALL(aMobileHome_PlaceBox_FillTop);
    POP_BC;

RowLoop:
        PUSH_BC;
    CALL(aMobileHome_PlaceBox_FillMiddle);
    POP_BC;
    DEC_B;
    IF_NZ goto RowLoop;
    CALL(aMobileHome_PlaceBox_FillBottom);
    RET;


FillTop:
        LD_A(0x63);
    LD_D(0x62);
    LD_E(0x64);
    goto FillRow;


FillBottom:
        LD_A(0x68);
    LD_D(0x67);
    LD_E(0x69);
    goto FillRow;


FillMiddle:
        LD_A(0x7f);
    LD_D(0x65);
    LD_E(0x66);


FillRow:
        PUSH_HL;
    LD_hl_D;
    INC_HL;

FillLoop:
        LD_hli_A;
    DEC_C;
    IF_NZ goto FillLoop;
    LD_hl_E;
    POP_HL;
    LD_DE(SCREEN_WIDTH);
    ADD_HL_DE;
    RET;

}

void Function3f7c(void){
        CALL(aMenuBoxCoord2Tile);
    CALL(aGetMenuBoxDims);
    DEC_B;
    DEC_C;
    CALL(aFunction3eea);
    RET;

}

void Function3f88(void){
        LD_HL(wDecompressScratch);
    LD_B(0);

row:
        PUSH_BC;
    LD_C(1 * LEN_2BPP_TILE / 2);

col:
        LD_A_de;
    INC_DE;
    CPL;
    LD_hl(0);
    INC_HL;
    LD_hli_A;
    DEC_C;
    IF_NZ goto col;
    POP_BC;
    DEC_C;
    IF_NZ goto row;
    RET;

}

void Function3f9f(void){
        LD_HL(wDecompressScratch);

row:
        PUSH_BC;
    LD_C(1 * LEN_2BPP_TILE / 2);

col:
        LD_A_de;
    INC_DE;
    INC_DE;
    CPL;
    LD_hl(0x0);
    INC_HL;
    LD_hli_A;
    DEC_C;
    IF_NZ goto col;
    POP_BC;
    DEC_C;
    IF_NZ goto row;
    RET;

}
