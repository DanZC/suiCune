#include "../constants.h"
#include "mobile_22_2.h"
#include "mobile_22.h"
#include "../home/copy.h"
#include "../home/text.h"
#include "../home/sram.h"
#include "../home/audio.h"
#include "../home/menu.h"
#include "../home/scrolling_menu.h"
#include "../home/delay.h"
#include "../data/text/common.h"

void Function8b342(void){
//  Loads the map data pointer, then runs through a
//  dw with three dummy functions. Spends a lot of energy
//  doing pretty much nothing.
    CALL(aGetMapAttributesPointer);
    LD_D_H;
    LD_E_L;

//  Everything between here and "ret" is useless.
    XOR_A_A;

loop:
    PUSH_AF;
    LD_HL(mFunction8b342_dw);
    RST(aJumpTable);
    POP_AF;
    INC_A;
    CP_A(3);
    IF_NZ goto loop;
    RET;


dw:
    //dw ['.zero'];
    //dw ['.one'];
    //dw ['.two'];


zero:
    RET;


one:
    RET;


two:
    RET;

}

void Function8b35d(void){
//  //  unreferenced
    LD_A_H;
    CP_A_D;
    RET_NZ ;
    LD_A_L;
    CP_A_E;
    RET;

}

void Function8b363(void){
//  //  unreferenced
    PUSH_BC;
    FARCALL(aMobile_AlwaysReturnNotCarry);
    POP_BC;
    RET;

}

void Function8b36c(uint8_t* bc){
// [bc + (0:4)] = -1
    // PUSH_BC;
    // LD_H_B;
    // LD_L_C;
    // LD_BC(4);
    // LD_A(-1);
    // CALL(aByteFill);
    ByteFill_Conv2(bc, 4, 0xff);
    // POP_BC;
    // RET;
}

uint8_t Function8b379(uint8_t* bc, uint8_t e){
// d = [bc + e]
    // PUSH_BC;
    // LD_A_C;
    // ADD_A_E;
    // LD_C_A;
    // LD_A(0x0);
    // ADC_A_B;
    // LD_B_A;
    // LD_A_bc;
    // LD_D_A;
    // POP_BC;
    // RET;
    return bc[e];
}

void Function8b385(uint8_t* bc, uint8_t d, uint8_t e){
// [bc + e] = d
    // PUSH_BC;
    // LD_A_C;
    // ADD_A_E;
    // LD_C_A;
    // LD_A(0x0);
    // ADC_A_B;
    // LD_B_A;
    // LD_A_D;
    // LD_bc_A;
    // POP_BC;
    // RET;
    bc[e] = d;
}

// find first e in range(4) such that [bc + e] == -1
// if none exist, return carry
u8_flag_s Function8b391(uint8_t* bc){
    // PUSH_BC;
    // LD_E(0);
    uint8_t e = 0;
    // LD_D(4);
    uint8_t d = 4;

    do {
    // loop:
        // LD_A_bc;
        // INC_BC;
        // CP_A(-1);
        // IF_Z goto done;
        if(*bc == 0xff)
            return u8_flag(e, false);
        // INC_E;
        // DEC_D;
        // IF_NZ goto loop;
    } while(++e, --d != 0);
    // DEC_E;
    // SCF;

// done:
    // POP_BC;
    // RET;
    return u8_flag(--e, true);
}

// Mobile22_StrCmp4
bool Function8b3a4(const uint8_t* hl, const uint8_t* bc){
// strcmp(hl, bc, 4)
    // PUSH_DE;
    // PUSH_BC;
    // LD_D_B;
    // LD_E_C;
    // LD_C(4);
    // CALL(aFunction89185);
    // POP_BC;
    // POP_DE;
    // RET;
    return Function89185(hl, bc, 4);
}

u8_flag_s Function8b3b0(void){
    // LD_BC(s4_a037);
    uint8_t* bc = GBToRAMAddr(s4_a037);
    // LD_A_addr(s4_a60b);
    uint8_t a = gb_read(s4_a60b);
    // AND_A_A;
    // IF_Z goto asm_8b3c2;
    // CP_A(0x3);
    // IF_NC goto asm_8b3c2;
    // CALL(aFunction8b391);
    bool carry = true;
    // IF_C goto asm_8b3c9;
    if(a == 0 || a >= 0x3 || !Function8b391(bc).flag) {
    // asm_8b3c2:
        carry = false;
        // CALL(aFunction8b36c);
        Function8b36c(bc);
        // XOR_A_A;
        // LD_addr_A(s4_a60b);
        gb_write(s4_a60b, 0);
    }

// asm_8b3c9:
    // LD_A_addr(s4_a60b);
    // RET;
    return u8_flag(gb_read(s4_a60b), carry);
}

void Function8b3cd(tile_t* hl, uint8_t* bc){
    // PUSH_DE;
    // PUSH_BC;
    // LD_E(0x4);
    uint8_t e = 0x4;

    do {
    // asm_8b3d1:
        // LD_A_bc;
        // INC_BC;
        uint8_t a = *(bc++);
        // CALL(aFunction8998b);
        Function8998b(hl, a);
        // INC_HL;
        hl++;
        // DEC_E;
        // IF_NZ goto asm_8b3d1;
    } while(--e != 0);
    // POP_BC;
    // POP_DE;
    // RET;

}

u8_flag_s Function8b3dd(uint8_t* bc, uint8_t* e){
    // PUSH_DE;
    // PUSH_BC;
    // CALL(aJoyTextDelay_ForcehJoyDown);  // joypad
    // LD_A_C;
    uint8_t c = JoyTextDelay_ForcehJoyDown_Conv();
    // POP_BC;
    // POP_DE;
    // BIT_A(A_BUTTON_F);
    // IF_NZ goto a_button;
    if(bit_test(c, A_BUTTON_F)) {
    // a_button:
        // LD_A_E;
        // CP_A(0x3);
        // IF_Z goto e_is_zero;
        if(*e == 0x3) {
        // e_is_zero:
            // CALL(aPlayClickSFX);
            PlayClickSFX_Conv();
            // LD_D(0x0);
            // SCF;
            // RET;
            return u8_flag(0x0, true);
        }
        // INC_E;
        // LD_D(0);
        // CALL(aFunction8b385);
        Function8b385(bc, 0, *e);
        // XOR_A_A;
        // LD_addr_A(wd010);
        wram->wd010[0] = 0;
        // RET;
        return u8_flag(0, false);
    }
    // BIT_A(B_BUTTON_F);
    // IF_NZ goto b_button;
    else if(bit_test(c, B_BUTTON_F)) {
    // b_button:
        // LD_A_E;
        // AND_A_A;
        // IF_NZ goto e_is_not_zero;
        if(*e == 0) {
            // CALL(aPlayClickSFX);
            PlayClickSFX_Conv();
            // LD_D(-1);
            // CALL(aFunction8b385);
            Function8b385(bc, -1, *e);
            // LD_D(1);
            // SCF;
            // RET;
            return u8_flag(1, true);
        }
    
    // e_is_not_zero:
        // LD_D(-1);
        // CALL(aFunction8b385);
        Function8b385(bc, -1, *e);
        // DEC_E;
        --(*e);
        // XOR_A_A;
        // LD_addr_A(wd010);
        // RET;
        return u8_flag(-1, false);
    }
    // BIT_A(D_UP_F);
    // IF_NZ goto d_up;
    else if(bit_test(c, D_UP_F)) {
    // d_up:
        // CALL(aFunction8b379);
        uint8_t d = Function8b379(bc, *e);
        // LD_A_D;
        // CP_A(0xa);
        // IF_C goto less_than_10_up_1;
        if(d >= 0xa) {
            // LD_D(0x9);
            d = 0x9;
        }
    
    // less_than_10_up_1:
        // INC_D;
        ++d;
        // LD_A_D;
        // CP_A(0xa);
        // IF_C goto less_than_10_up_2;
        if(d >= 0xa) {
            // LD_D(0x0);
            d = 0;
        }
    
    // less_than_10_up_2:
        // CALL(aFunction8b385);
        Function8b385(bc, d, *e);
        // XOR_A_A;
        // LD_addr_A(wd010);
        wram->wd010[0] = 0;
        // RET;
        return u8_flag(0, false);
    }
    // BIT_A(D_DOWN_F);
    // IF_NZ goto d_down;
    else if(bit_test(c, D_DOWN_F)) {
    // d_down:
        // CALL(aFunction8b379);
        uint8_t d = Function8b379(bc, *e);
        // LD_A_D;
        // CP_A(0xa);
        // IF_C goto less_than_10_down;
        if(d >= 0xa) {
            // LD_D(0x0);
            d = 0;
        }
    
    // less_than_10_down:
        // LD_A_D;
        // DEC_D;
        // AND_A_A;
        // IF_NZ goto nonzero_down;
        if(d == 0) {
            // LD_D(0x9);
            d = 0x9;
        }
        else {
            --d;
        }
    
    // nonzero_down:
        // CALL(aFunction8b385);
        Function8b385(bc, d, *e);
        // XOR_A_A;
        // LD_addr_A(wd010);
        wram->wd010[0] = 0;
        // RET;
        return u8_flag(0, false);
    }
    // AND_A_A;
    // RET;
    return u8_flag(0, false);
}

bool Function8b45c(uint8_t* bc){
    // CALL(aFunction8b36c);
    Function8b36c(bc);
    // XOR_A_A;
    // LD_addr_A(wd010);
    wram->wd010[0] = 0;
    // LD_addr_A(wd012);
    wram->wd012[0] = 0;
    // CALL(aFunction8b391);
    u8_flag_s res = Function8b391(bc);
    // LD_D(0x0);
    // CALL(aFunction8b385);
    Function8b385(bc, 0x0, res.a);

    uint8_t e = res.a;
    u8_flag_s done = {0, false};
    do {
    // asm_8b46e:
        // CALL(aMobile22_SetBGMapMode0);
        Mobile22_SetBGMapMode0();
        // CALL(aFunction8b493);
        Function8b493(bc);
        // CALL(aFunction8b4cc);
        // CALL(aFunction8b518);
        // CALL(aFunction89b78);
        Function89b78(Function8b518(Function8b4cc()), e);
        // PUSH_BC;
        // CALL(aFunction8b4fd);
        uint8_t d, b, c;
        Function8b4fd(&d, &b, &c);
        // CALL(aFunction89c44);
        Function89c44(d, e, b, c);
        // LD_A(0x1);
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = 0x1;
        // POP_BC;
        // CALL(aFunction8b3dd);
        done = Function8b3dd(bc, &e);
        // IF_NC goto asm_8b46e;
    } while(!done.flag);
    // LD_A_D;
    // AND_A_A;
    // RET_Z ;
    if(done.a == 0)
        return false;
    // SCF;
    // RET;
    return true;
}

const Unknown_8b529_s Unknown_8b529[] = {
    //dwcoord ['2', '5'];
    //db ['1', '4', '0x20', '0x49', '0', '1'];
    {coord(2, 5, 0),
        {1, 4, 0x20, 0x49, 0, 1}},
    //dwcoord ['7', '4'];
    //db ['1', '4', '0x48', '0x41', '0', '0'];
    {coord(7, 4, 0),
        {1, 4, 0x48, 0x41, 0, 0}},
};

void Function8b493(uint8_t* bc){
    // PUSH_BC;
    // CALL(aMobile22_SetBGMapMode0);
    Mobile22_SetBGMapMode0();
    // CALL(aFunction8b521);
    uint8_t a = Function8b521();
    // LD_HL(mJumptable_8b4a0);
    Jumptable_8b4a0(bc, a);
    // POP_BC;
    // RST(aJumpTable);
    // RET;
}

void Jumptable_8b4a0(uint8_t* bc, uint8_t a){
    switch(a) {
        case 0: return Function8b4a4(bc);
        case 1: return Function8b4b8(bc);
    }
}

void Function8b4a4(uint8_t* bc){
    // PUSH_BC;
    // PUSH_DE;
    // CALL(aFunction8b4d8);
    uint8_t b, c;
    tile_t* hl = Function8b4d8(&b, &c);
    // CALL(aTextbox);
    Textbox_Conv2(hl, b, c);
    // POP_DE;
    // POP_BC;
    // CALL(aFunction8b4cc);
    // CALL(aFunction8b518);
    // CALL(aFunction8b3cd);
    Function8b3cd(Function8b518(Function8b4cc()), bc);
    // RET;
}

void Function8b4b8(uint8_t* bc){
    // PUSH_BC;
    // PUSH_DE;
    // CALL(aFunction8b4ea);
    uint8_t b, c;
    tile_t* de = Function8b4ea(&b, &c);
    // CALL(aFunction89b3b);
    Function89b3b(de, b, c);
    // POP_DE;
    // POP_BC;
    // CALL(aFunction8b4cc);
    // CALL(aFunction8b518);
    // CALL(aFunction8b3cd);
    Function8b3cd(Function8b518(Function8b4cc()), bc);
    // RET;
}

tile_t* Function8b4cc(void){
    // PUSH_BC;
    // LD_HL(mUnknown_8b529);
    // CALL(aFunction8b50a);
    const Unknown_8b529_s *data = Function8b50a(Unknown_8b529);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // POP_BC;
    // RET;
    return wram->wTilemap + data->offset;
}

tile_t* Function8b4d8(uint8_t* b, uint8_t* c){
    // LD_HL(mUnknown_8b529);
    // CALL(aFunction8b50a);
    // PUSH_HL;
    const Unknown_8b529_s *data = Function8b50a(Unknown_8b529);
    // INC_HL;
    // INC_HL;
    // LD_A_hli;
    // LD_B_A;
    *b = data->bytes[0];
    // LD_A_hl;
    // LD_C_A;
    *c = data->bytes[1];
    // POP_HL;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // RET;
    return wram->wTilemap + data->offset;
}

tile_t* Function8b4ea(uint8_t* b, uint8_t* c){
    // LD_HL(mUnknown_8b529);
    // CALL(aFunction8b50a);
    // PUSH_HL;
    // INC_HL;
    // INC_HL;
    // LD_A_hli;
    // LD_B_A;
    // LD_A_hl;
    // LD_C_A;
    // POP_HL;
    // LD_A_hli;
    // LD_E_A;
    // LD_A_hl;
    // LD_D_A;
    // RET;
    return Function8b4d8(b, c);
}

void Function8b4fd(uint8_t* d, uint8_t* b, uint8_t* c){
    // LD_HL(mUnknown_8b529 + 4);
    // CALL(aFunction8b50a);
    const Unknown_8b529_s *data = Function8b50a(Unknown_8b529);
    // LD_A_hli;
    // LD_C_A;
    *c = data->bytes[2];
    // LD_A_hli;
    // LD_B_A;
    *b = data->bytes[3];
    // LD_A_hli;
    // LD_D_A;
    *d = data->bytes[4];
    // RET;
}

const Unknown_8b529_s* Function8b50a(const Unknown_8b529_s* hl){
    // LD_A_addr(wd02e);
    // AND_A_A;
    // RET_Z ;
    // LD_B(0x0);
    // LD_C(0x8);

// asm_8b513:
    // ADD_HL_BC;
    // DEC_A;
    // IF_NZ goto asm_8b513;
    // RET;
    return hl + wram->wd02e[0];
}

tile_t* Function8b518(tile_t* hl){
    // PUSH_DE;
    // LD_D(0x0);
    // LD_E(0x14);
    // ADD_HL_DE;
    // INC_HL;
    // POP_DE;
    // RET;
    return hl + SCREEN_WIDTH + 1;
}

uint8_t Function8b521(void){
    // LD_HL(mUnknown_8b529 + 7);
    // CALL(aFunction8b50a);
    // LD_A_hl;
    // RET;
    return Function8b50a(Unknown_8b529)->bytes[5];
}

void Function8b539(void){
    LD_BC(wd017);
    CALL(aFunction8b36c);
    XOR_A_A;
    LD_addr_A(wd012);
    LD_addr_A(wd02e);
    CALL(aFunction8b493);
    CALL(aFunction8b4fd);
    LD_E(0x0);
    CALL(aFunction89c44);
    CALL(aCGBOnly_CopyTilemapAtOnce);
    RET;

}

void Function8b555(void){

loop:
    LD_HL(mEnterNewPasscodeText);
    CALL(aPrintText);
    LD_BC(wd017);
    CALL(aFunction8b45c);
    IF_C goto asm_8b5c8;
    CALL(aFunction89448);
    LD_BC(wd017);
    CALL(aFunction8b493);
    LD_BC(wd017);
    CALL(aFunction8b664);
    IF_NZ goto asm_8b57c;
    LD_HL(mFourZerosInvalidText);
    CALL(aPrintText);
    goto loop;


asm_8b57c:
    LD_HL(mConfirmPasscodeText);
    CALL(aPrintText);
    LD_BC(wd013);
    CALL(aFunction8b45c);
    IF_C goto loop;
    LD_BC(wd017);
    LD_HL(wd013);
    CALL(aFunction8b3a4);
    IF_Z goto strings_equal;
    CALL(aFunction89448);
    LD_BC(wd013);
    CALL(aFunction8b493);
    LD_HL(mPasscodesNotSameText);
    CALL(aPrintText);
    goto asm_8b57c;


strings_equal:
    CALL(aOpenSRAMBank4);
    LD_HL(wd013);
    LD_DE(s4_a037);
    LD_BC(0x4);
    CALL(aCopyBytes);
    CALL(aCloseSRAM);
    CALL(aFunction89448);
    LD_BC(wd013);
    CALL(aFunction8b493);
    LD_HL(mPasscodeSetText);
    CALL(aPrintText);
    AND_A_A;

asm_8b5c8:
    PUSH_AF;
    CALL(aFunction89448);
    POP_AF;
    RET;

}

void EnterNewPasscodeText(void){
    //text_far ['_EnterNewPasscodeText']
    //text_end ['?']

    return ConfirmPasscodeText();
}

void ConfirmPasscodeText(void){
    //text_far ['_ConfirmPasscodeText']
    //text_end ['?']

    return PasscodesNotSameText();
}

void PasscodesNotSameText(void){
    //text_far ['_PasscodesNotSameText']
    //text_end ['?']

    return PasscodeSetText();
}

void PasscodeSetText(void){
    //text_far ['_PasscodeSetText']
    //text_end ['?']

    return FourZerosInvalidText();
}

void FourZerosInvalidText(void){
    //text_far ['_FourZerosInvalidText']
    //text_end ['?']
}

// Mobile22_CardFolderPasswordCheck
bool Function8b5e7(void){
    // LD_BC(wd013);
    // CALL(aFunction8b36c);
    Function8b36c(wram->wd013);
    // XOR_A_A;
    // LD_addr_A(wd012);
    wram->wd012[0] = 0;
    // LD_addr_A(wd02e);
    wram->wd02e[0] = 0;
    // CALL(aFunction8b493);
    Function8b493(wram->wd013);
    // CALL(aFunction891ab);
    Function891ab();
    // CALL(aFunction8b4fd);
    uint8_t d, b, c;
    Function8b4fd(&d, &b, &c);
    // LD_E(0x0);
    uint8_t e = 0x0;
    // CALL(aFunction89c44);
    Function89c44(d, e, b, c);

    while(1) {
    // asm_8b602:
        // LD_HL(mEnterPasscodeText);
        // CALL(aPrintText);
        PrintText_Conv2(EnterPasscodeText);
        // LD_BC(wd013);
        // CALL(aFunction8b45c);
        // IF_C goto asm_8b63c;
        if(Function8b45c(wram->wd013)) {
            Function89448();
            return true;
        }
        // CALL(aFunction89448);
        Function89448();
        // LD_BC(wd013);
        // CALL(aFunction8b493);
        Function8b493(wram->wd013);
        // CALL(aOpenSRAMBank4);
        OpenSRAMBank4();
        // LD_HL(s4_a037);
        // CALL(aFunction8b3a4);
        bool eq = Function8b3a4(GBToRAMAddr(s4_a037), wram->wd013);
        // CALL(aCloseSRAM);
        CloseSRAM_Conv();
        // IF_Z goto asm_8b635;
        if(eq)
            break;
        // LD_HL(mIncorrectPasscodeText);
        // CALL(aPrintText);
        PrintText_Conv2(IncorrectPasscodeText);
        // LD_BC(wd013);
        // CALL(aFunction8b36c);
        Function8b36c(wram->wd013);
        // goto asm_8b602;
    }

// asm_8b635:
    // LD_HL(mUnknownText_0x8b64c);
    // CALL(aPrintText);
    PrintText_Conv2(UnknownText_0x8b64c);
    // AND_A_A;

// asm_8b63c:
    // PUSH_AF;
    // CALL(aFunction89448);
    Function89448();
    // POP_AF;
    // RET;
    return false;
}

const txt_cmd_s EnterPasscodeText[] = {
    text_far(v_EnterPasscodeText)
    text_end
};

const txt_cmd_s IncorrectPasscodeText[] = {
    text_far(v_IncorrectPasscodeText)
    text_end
};

static void UnknownText_0x8b64c_Function(struct TextCmdState* state) {
    static const txt_cmd_s string_8b663[] =  { text_end };
    // LD_DE(SFX_TWINKLE);
    // CALL(aPlaySFX);
    PlaySFX_Conv(SFX_TWINKLE);
    // CALL(aWaitSFX);
    WaitSFX_Conv();
    // LD_C(0x8);
    // CALL(aDelayFrames);
    DelayFrames_Conv(0x8);
    // LD_HL(mUnknownText_0x8b64c_string_8b663);
    state->hl = string_8b663;
    // RET;
};
const txt_cmd_s UnknownText_0x8b64c[] = {
// CARD FOLDER open.@ @
    text_far(v_CardFolderOpenText)
    text_asm(UnknownText_0x8b64c_Function)
};

void Function8b664(void){
    PUSH_BC;
    LD_DE(0x4);

asm_8b668:
    LD_A_bc;
    CP_A(0x0);
    IF_NZ goto asm_8b66e;
    INC_D;

asm_8b66e:
    INC_BC;
    DEC_E;
    IF_NZ goto asm_8b668;
    POP_BC;
    LD_A_D;
    CP_A(0x4);
    RET;

}

void Function8b677(void){
    CALL(aClearBGPalettes);
    CALL(aDisableLCD);
    CALL(aFunction8b690);
    CALL(aFunction8b6bb);
    CALL(aFunction8b6ed);
    CALL(aEnableLCD);
    CALL(aFunction891ab);
    CALL(aSetPalettes);
    RET;

}

void Function8b690(void){
    LD_HL(mMobileCardListGFX);
    LD_DE(vTiles2);
    LD_BC(0x16 * LEN_2BPP_TILE);
    LD_A(BANK(aMobileCardListGFX));
    CALL(aFarCopyBytes);
    LD_HL(mMobileCardListGFX + LEN_2BPP_TILE * 0x15);
    LD_DE(vTiles2 + LEN_2BPP_TILE * 0x61);
    LD_BC(1 * LEN_2BPP_TILE);
    LD_A(BANK(aMobileCardListGFX));
    CALL(aFarCopyBytes);
    LD_HL(mMobileCardListGFX + LEN_2BPP_TILE * 0x16);
    LD_DE(vTiles0 + LEN_2BPP_TILE * 0xee);
    LD_BC(1 * LEN_2BPP_TILE);
    LD_A(BANK(aMobileCardListGFX));
    CALL(aFarCopyBytes);
    RET;

}

void Function8b6bb(void){
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x5);
    LDH_addr_A(rSVBK);
    LD_HL(mPalette_8b6d5);
    LD_DE(wBGPals1);
    LD_BC(3 * PALETTE_SIZE);
    CALL(aCopyBytes);
    POP_AF;
    LDH_addr_A(rSVBK);
    CALL(aFunction8949c);
    RET;

}

void Palette_8b6d5(void){
    //rgb ['31', '31', '31']
    //rgb ['31', '21', '00']
    //rgb ['14', '07', '03']
    //rgb ['00', '00', '00']
    //rgb ['31', '31', '31']
    //rgb ['31', '21', '00']
    //rgb ['22', '09', '17']
    //rgb ['00', '00', '00']
    //rgb ['31', '31', '31']
    //rgb ['31', '21', '00']
    //rgb ['06', '24', '08']
    //rgb ['00', '00', '00']

    return Function8b6ed();
}

void Function8b6ed(void){
    hlcoord(0, 0, wAttrmap);
    LD_BC(0x012c);
    XOR_A_A;
    CALL(aByteFill);
    hlcoord(0, 14, wAttrmap);
    LD_BC(0x0050);
    LD_A(0x7);
    CALL(aByteFill);
    RET;

}

void Function8b703(void){
    CALL(aMobile22_SetBGMapMode0);
    PUSH_HL;
    LD_A(0xc);
    LD_hli_A;
    INC_A;
    CALL(aFunction8b73e);
    INC_A;
    LD_hl_A;
    POP_HL;
    PUSH_HL;
    PUSH_BC;
    LD_DE(SCREEN_WIDTH);
    ADD_HL_DE;

asm_8b717:
    PUSH_HL;
    LD_A(0xf);
    LD_hli_A;
    LD_A(0x7f);
    CALL(aFunction8b73e);
    LD_A(0x11);
    LD_hl_A;
    POP_HL;
    LD_DE(SCREEN_WIDTH);
    ADD_HL_DE;
    DEC_B;
    IF_NZ goto asm_8b717;
    CALL(aFunction8b732);
    POP_BC;
    POP_HL;
    JR(mFunction8b744);

}

void Function8b732(void){
    LD_A(0x12);
    LD_hli_A;
    LD_A(0x13);
    CALL(aFunction8b73e);
    LD_A(0x14);
    LD_hl_A;
    RET;

}

void Function8b73e(void){
    LD_D_C;

asm_8b73f:
    LD_hli_A;
    DEC_D;
    IF_NZ goto asm_8b73f;
    RET;

}

void Function8b744(void){
    LD_DE(wAttrmap - wTilemap);
    ADD_HL_DE;
    INC_B;
    INC_B;
    INC_C;
    INC_C;
    XOR_A_A;

asm_8b74d:
    PUSH_BC;
    PUSH_HL;

asm_8b74f:
    LD_hli_A;
    DEC_C;
    IF_NZ goto asm_8b74f;
    POP_HL;
    LD_DE(SCREEN_WIDTH);
    ADD_HL_DE;
    POP_BC;
    DEC_B;
    IF_NZ goto asm_8b74d;
    RET;

}

void Function8b75d(void){
    CALL(aMobile22_SetBGMapMode0);
    hlcoord(0, 0, wTilemap);
    LD_A(0x1);
    LD_BC(SCREEN_WIDTH);
    CALL(aByteFill);
    hlcoord(0, 1, wTilemap);
    LD_A(0x2);
    LD_hl_A;
    hlcoord(9, 1, wTilemap);
    LD_C(0xb);
    CALL(aFunction8b788);
    hlcoord(1, 1, wTilemap);
    LD_A(0x4);
    LD_E(0x8);

asm_8b780:
    LD_hli_A;
    INC_A;
    DEC_E;
    IF_NZ goto asm_8b780;
    JR(mFunction8b79e);

}

void Function8b787(void){
//  //  unreferenced
    RET;

}

void Function8b788(void){

asm_8b788:
    LD_A(0x2);
    LD_hli_A;
    DEC_C;
    RET_Z ;
    LD_A(0x1);
    LD_hli_A;
    DEC_C;
    RET_Z ;
    LD_A(0x3);
    LD_hli_A;
    DEC_C;
    RET_Z ;
    LD_A(0x1);
    LD_hli_A;
    DEC_C;
    IF_NZ goto asm_8b788;
    RET;

}

void Function8b79e(void){
    hlcoord(0, 1, wAttrmap);
    LD_A(0x1);
    LD_hli_A;
    hlcoord(9, 1, wAttrmap);
    LD_E(0xb);

asm_8b7a9:
    LD_A(0x2);
    LD_hli_A;
    DEC_E;
    RET_Z ;
    XOR_A_A;
    LD_hli_A;
    DEC_E;
    RET_Z ;
    LD_A(0x1);
    LD_hli_A;
    DEC_E;
    RET_Z ;
    XOR_A_A;
    LD_hli_A;
    DEC_E;
    IF_NZ goto asm_8b7a9;
    RET;

}

void Function8b7bd(void){
    CALL(aFunction8b855);
    LD_HL(mMenuHeader_0x8b867);
    CALL(aCopyMenuHeader);
    LD_A_addr(wd030);
    LD_addr_A(wMenuCursorPosition);
    LD_A_addr(wd031);
    LD_addr_A(wMenuScrollPosition);
    LD_A_addr(wd032);
    AND_A_A;
    IF_Z goto asm_8b7e0;
    LD_A_addr(wMenuFlags);
    SET_A(3);
    LD_addr_A(wMenuFlags);


asm_8b7e0:
    LD_A_addr(wd0e3);
    AND_A_A;
    IF_Z goto asm_8b7ea;
    DEC_A;
    LD_addr_A(wScrollingMenuCursorPosition);


asm_8b7ea:
    hlcoord(0, 2, wTilemap);
    LD_B(0xb);
    LD_C(0x12);
    CALL(aFunction8b703);
    CALL(aFunction8b75d);
    CALL(aUpdateSprites);
    CALL(aMobile_EnableSpriteUpdates);
    CALL(aScrollingMenu);
    CALL(aMobile_DisableSpriteUpdates);
    LD_A_addr(wMenuJoypad);
    CP_A(0x2);
    IF_Z goto asm_8b823;
    CP_A(0x20);
    IF_NZ goto asm_8b813;
    CALL(aFunction8b832);
    goto asm_8b7ea;


asm_8b813:
    CP_A(0x10);
    IF_NZ goto asm_8b81c;
    CALL(aFunction8b83e);
    goto asm_8b7ea;


asm_8b81c:
    LD_A_addr(wMenuSelection);
    CP_A(0xff);
    IF_NZ goto asm_8b824;


asm_8b823:
    XOR_A_A;


asm_8b824:
    LD_C_A;
    LD_A_addr(wMenuCursorY);
    LD_addr_A(wd030);
    LD_A_addr(wMenuScrollPosition);
    LD_addr_A(wd031);
    RET;

}

void Function8b832(void){
    LD_A_addr(wMenuScrollPosition);
    LD_HL(wMenuDataItems);
    SUB_A_hl;
    JR_NC (mFunction8b84b);
    XOR_A_A;
    JR(mFunction8b84b);

}

void Function8b83e(void){
    LD_A_addr(wMenuScrollPosition);
    LD_HL(wMenuDataItems);
    ADD_A_hl;
    CP_A(0x24);
    JR_C (mFunction8b84b);
    LD_A(0x24);

    return Function8b84b();
}

void Function8b84b(void){
    LD_addr_A(wMenuScrollPosition);
    LD_A_addr(wMenuCursorY);
    LD_addr_A(wMenuCursorPosition);
    RET;

}

void Function8b855(void){
    LD_A(0x28);
    LD_HL(wd002);
    LD_hli_A;
    LD_C(0x28);
    XOR_A_A;

asm_8b85e:
    INC_A;
    LD_hli_A;
    DEC_C;
    IF_NZ goto asm_8b85e;
    LD_A(0xff);
    LD_hl_A;
    RET;

}

void MenuHeader_0x8b867(void){
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['1', '3', '18', '13'];
    //dw ['MenuData_0x8b870'];
    //db ['1'];  // default option

    //db ['0'];

    return MenuData_0x8b870();
}

void MenuData_0x8b870(void){
    //db ['SCROLLINGMENU_ENABLE_FUNCTION3 | SCROLLINGMENU_DISPLAY_ARROWS | SCROLLINGMENU_ENABLE_RIGHT | SCROLLINGMENU_ENABLE_LEFT'];  // flags
    //db ['5', '3'];  // rows, columns
    //db ['SCROLLINGMENU_ITEMS_NORMAL'];  // item format
    //dbw ['0', 'wd002']
    //dba ['Function8b880']
    //dba ['Function8b88c']
    //dba ['Function8b8c8']

    return Function8b880();
}

void Function8b880(void){
    LD_H_D;
    LD_L_E;
    LD_DE(wMenuSelection);
    LD_BC((PRINTNUM_LEADINGZEROS | 1 << 8) | 2);
    CALL(aPrintNum);
    RET;

}

void Function8b88c(void){
    CALL(aOpenSRAMBank4);
    LD_H_D;
    LD_L_E;
    PUSH_HL;
    LD_DE(mString_89116);
    CALL(aFunction8931b);
    CALL(aFunction8932d);
    IF_C goto asm_8b8a3;
    LD_HL(0);
    ADD_HL_BC;
    LD_D_H;
    LD_E_L;


asm_8b8a3:
    POP_HL;
    PUSH_HL;
    CALL(aPlaceString);
    POP_HL;
    LD_D(0x0);
    LD_E(0x6);
    ADD_HL_DE;
    PUSH_HL;
    LD_DE(mString_89116);
    CALL(aFunction8931b);
    CALL(aFunction8934a);
    IF_C goto asm_8b8c0;
    LD_HL(0x0006);
    ADD_HL_BC;
    LD_D_H;
    LD_E_L;


asm_8b8c0:
    POP_HL;
    CALL(aPlaceString);
    CALL(aCloseSRAM);
    RET;

}

void Function8b8c8(void){
    hlcoord(0, 14, wTilemap);
    LD_B(0x2);
    LD_C(0x12);
    CALL(aTextbox);
    LD_A_addr(wd033);
    LD_B(0);
    LD_C_A;
    LD_HL(mUnknown_8b903);
    ADD_HL_BC;
    ADD_HL_BC;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_D_H;
    LD_E_L;
    hlcoord(1, 16, wTilemap);
    CALL(aPlaceString);
    hlcoord(0, 13, wTilemap);
    LD_A(0xf);
    LD_hl_A;
    hlcoord(19, 13, wTilemap);
    LD_A(0x11);
    LD_hl_A;
    LD_A_addr(wMenuScrollPosition);
    CP_A(0x24);
    RET_C ;
    hlcoord(0, 13, wTilemap);
    LD_C(0x12);
    CALL(aFunction8b732);
    RET;

}

void Unknown_8b903(void){
    //dw ['String_8b90b'];
    //dw ['String_8b919'];
    //dw ['String_8b92a'];
    //dw ['String_8b938'];

    return String_8b90b();
}

void String_8b90b(void){
//db "めいしを　えらんでください@"          //  Please select a noun.
    return String_8b919();
}

void String_8b919(void){
//db "どの　めいしと　いれかえますか？@"      //  OK to swap with any noun?
    return String_8b92a();
}

void String_8b92a(void){
//db "あいてを　えらんでください@"          //  Please select an opponent.
    return String_8b938();
}

void String_8b938(void){
//db "いれる　ところを　えらんでください@"   //  Please select a location.

    return Function8b94a();
}

void Function8b94a(void){
    LD_addr_A(wd033);
    XOR_A_A;
    LD_addr_A(wMenuScrollPosition);
    LD_addr_A(wd032);
    LD_addr_A(wd0e3);
    LD_addr_A(wd031);
    LD_A(0x1);
    LD_addr_A(wd030);
    RET;

}

void Function8b960(void){
    LD_HL(mMenuHeader_0x8b9ac);
    CALL(aLoadMenuHeader);
    CALL(aFunction8b9e9);
    IF_C goto asm_8b97a;
    hlcoord(11, 0, wTilemap);
    LD_B(0x6);
    LD_C(0x7);
    CALL(aFunction8b703);
    LD_HL(mMenuHeader_0x8b9b1);
    goto asm_8b987;

asm_8b97a:
    hlcoord(11, 0, wTilemap);
    LD_B(0xa);
    LD_C(0x7);
    CALL(aFunction8b703);
    LD_HL(mMenuHeader_0x8b9ca);

asm_8b987:
    LD_A(0x1);
    CALL(aFunction89d5e);
    LD_HL(mFunction8b9ab);
    CALL(aFunction89d85);
    CALL(aExitMenu);
    IF_C goto asm_8b99c;
    CALL(aFunction8b99f);
    IF_NZ goto asm_8b99d;

asm_8b99c:
    XOR_A_A;

asm_8b99d:
    LD_C_A;
    RET;

}

void Function8b99f(void){
    LD_HL(wd002);
    DEC_A;
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0xff);
    RET;

}

void Function8b9ab(void){
    RET;

}

void MenuHeader_0x8b9ac(void){
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['11', '0', 'SCREEN_WIDTH - 1', 'TEXTBOX_Y - 1'];

    return MenuHeader_0x8b9b1();
}

void MenuHeader_0x8b9b1(void){
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['11', '0', 'SCREEN_WIDTH - 1', '7'];
    //dw ['MenuData_0x8b9b9'];
    //db ['1'];  // default option

    return MenuData_0x8b9b9();
}

void MenuData_0x8b9b9(void){
    //db ['STATICMENU_CURSOR | STATICMENU_WRAP'];  // flags
    //db ['3'];  // items
    //db ['"へんしゅう@"'];  // EDIT
    //db ['"いれかえ@"'];  // REPLACE
    //db ['"やめる@"'];  // QUIT

    return MenuHeader_0x8b9ca();
}

void MenuHeader_0x8b9ca(void){
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['11', '0', 'SCREEN_WIDTH - 1', 'TEXTBOX_Y - 1'];
    //dw ['MenuData_0x8b9d2'];
    //db ['1'];  // default option

    return MenuData_0x8b9d2();
}

void MenuData_0x8b9d2(void){
    //db ['STATICMENU_CURSOR | STATICMENU_WRAP'];  // flags
    //db ['5'];  // items
    //db ['"みる@"'];  // VIEW
    //db ['"へんしゅう@"'];  // EDIT
    //db ['"いれかえ@"'];  // REPLACE
    //db ['"けす@"'];  // ERASE
    //db ['"やめる@"'];  // QUIT

    return Function8b9e9();
}

void Function8b9e9(void){
    CALL(aOpenSRAMBank4);
    CALL(aFunction8931b);
    CALL(aFunction8932d);
    IF_NC goto asm_8b9f6;
    goto asm_8b9ff;

asm_8b9f6:
    LD_HL(0x11);
    ADD_HL_BC;
    CALL(aFunction89b45);
    IF_C goto asm_8ba08;

asm_8b9ff:
    CALL(aFunction892b4);
    AND_A_A;
    LD_DE(mUnknown_8ba1c);
    goto asm_8ba0c;

asm_8ba08:
    LD_DE(mUnknown_8ba1f);
    SCF;

asm_8ba0c:
    PUSH_AF;
    LD_HL(wd002);

asm_8ba10:
    LD_A_de;
    INC_DE;
    LD_hli_A;
    CP_A(0xff);
    IF_NZ goto asm_8ba10;
    CALL(aCloseSRAM);
    POP_AF;
    RET;

}

void Unknown_8ba1c(void){
    //db ['2', '4', '-1'];

    return Unknown_8ba1f();
}

void Unknown_8ba1f(void){
    //db ['1', '2', '4', '3', '-1'];

}
