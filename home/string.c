#include "../constants.h"
#include "string.h"
#include "copy.h"
#include "../charmap.h"

void InitString(uint8_t* hl, const uint8_t* de, uint8_t c){
    //  Init a string of length c.
    // PUSH_HL;
    // JR(mv_InitString);
    return v_InitString(hl, de, c);
}

//  Intended for names, so this function is limited to ten characters.
void InitName(uint8_t* hl, const uint8_t* de){
    // PUSH_HL;
    // LD_C(NAME_LENGTH - 1);
    return v_InitString(hl, de, NAME_LENGTH - 1);
}

//  if the string pointed to by hl is empty (defined as "zero or more spaces
//  followed by a null"), then initialize it to the string pointed to by de.
void v_InitString(uint8_t* hl, const uint8_t* de, uint8_t len){
    // PUSH_BC;
    uint8_t c = 0;
    uint8_t a;

    do
    {
        // LD_A_hli;
        a = hl[c++];

        // CP_A(0x50);
        // IF_Z goto blank;
        if(a == CHAR_TERM)
            break;
        
        // CP_A(0x7f);
        // IF_NZ goto notblank;
        if(a != CHAR_SPACE) 
        {
            // notblank:
            //     POP_BC;
            //     POP_HL;
            //     RET;
            return;
        }

    } while(c < len);

    // POP_BC;
    // LD_L_E;
    // LD_H_D;

    // POP_DE;
    // LD_B(0);
    // INC_C;
    // CALL(aCopyBytes);
    // RET;
    CopyBytes(hl, de, c + 1);
}
