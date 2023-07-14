#include "../constants.h"
#include "copy_name.h"
#include "../charmap.h"

void CopyName1(void){
    //  Copies the name from de to wStringBuffer2
    LD_HL(wStringBuffer2);

    return CopyName2();
}

void CopyName2(void){
    //  Copies the name from de to hl

loop:
        LD_A_de;
    INC_DE;
    LD_hli_A;
    CP_A(0x50);
    IF_NZ goto loop;
    RET;

}

//  Copies the name from de to wStringBuffer2
void CopyName1_Conv(uint16_t de) {
    return CopyName2_Conv(wStringBuffer2, de);
}

//  Copies the name from de to wStringBuffer2
void CopyName1_Conv2(const uint8_t* de) {
    return CopyName2_Conv2(wram->wStringBuffer2, de);
}

//  Copies the name from de to hl
void CopyName2_Conv(uint16_t hl, uint16_t de){
    uint8_t a;
    do {
        a = gb_read(de++);
        gb_write(hl++, a);
    } while(a != CHAR_TERM);
}

//  Copies the name from de to hl
void CopyName2_Conv2(uint8_t* hl, const uint8_t* de){
    uint8_t a;
    do {
        a = *(de++);
        *(hl++) = a;
    } while(a != CHAR_TERM);
}
