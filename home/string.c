#include "../constants.h"
#include "string.h"
#include "copy.h"

void InitString(void){
    //  Init a string of length c.
    PUSH_HL;
    JR(mv_InitString);

}

void InitName(void){
    //  Intended for names, so this function is limited to ten characters.
    PUSH_HL;
    LD_C(NAME_LENGTH - 1);
    return v_InitString();
}

void v_InitString(void){
    //  if the string pointed to by hl is empty (defined as "zero or more spaces
//  followed by a null"), then initialize it to the string pointed to by de.
    PUSH_BC;

loop:
        LD_A_hli;
    CP_A(0x50);
    IF_Z goto blank;
    CP_A(0x7f);
    IF_NZ goto notblank;
    DEC_C;
    IF_NZ goto loop;

blank:
        POP_BC;
    LD_L_E;
    LD_H_D;
    POP_DE;
    LD_B(0);
    INC_C;
    CALL(aCopyBytes);
    RET;


notblank:
        POP_BC;
    POP_HL;
    RET;

}

void InitString_Conv(uint16_t hl, uint16_t de, uint8_t c){
    //  Init a string of length c.
    // PUSH_HL;
    // JR(mv_InitString);
    return v_InitString_Conv(hl, de, c);
}

//  Intended for names, so this function is limited to ten characters.
void InitName_Conv(uint16_t hl, uint16_t de){
    // PUSH_HL;
    // LD_C(NAME_LENGTH - 1);
    return v_InitString_Conv(hl, de, NAME_LENGTH - 1);
}

//  if the string pointed to by hl is empty (defined as "zero or more spaces
//  followed by a null"), then initialize it to the string pointed to by de.
void v_InitString_Conv(uint16_t hl, uint16_t de, uint8_t len){
    // PUSH_BC;
    uint8_t c = len;
    uint8_t a;

    do
    {
        // LD_A_hli;
        a = gb_read(hl++);

        // CP_A(0x50);
        // IF_Z goto blank;
        if(a == 0x50)
            break;
        
        // CP_A(0x7f);
        // IF_NZ goto notblank;
        if(a != 0x7f) 
        {
            // notblank:
            //     POP_BC;
            //     POP_HL;
            //     RET;
            return;
        }

    } while(--c != 0);

    // POP_BC;
    // LD_L_E;
    // LD_H_D;
    uint16_t dest = de;

    // POP_DE;
    // LD_B(0);
    // INC_C;
    // CALL(aCopyBytes);
    // RET;
    CopyBytes_Conv(dest, hl, c + 1);
}
