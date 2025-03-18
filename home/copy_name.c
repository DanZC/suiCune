#include "../constants.h"
#include "copy_name.h"
#include "../charmap.h"

//  Copies the name from de to wStringBuffer2
uint8_t* CopyName1(const uint8_t* de) {
    return CopyName2(wram->wStringBuffer2, de);
}

//  Copies the name from de to hl
uint8_t* CopyName2(uint8_t* hl, const uint8_t* de){
    uint8_t a;
    do {
        a = *(de++);
        *(hl++) = a;
    } while(a != CHAR_TERM);
    return hl;
}

//  Copies the name from de to wStringBuffer2
//  Unused
void CopyName1_GB(uint16_t de) {
    return CopyName2_GB(wStringBuffer2, de);
}

//  Copies the name from de to hl
//  Unused
void CopyName2_GB(uint16_t hl, uint16_t de){
    uint8_t a;
    do {
        a = gb_read(de++);
        gb_write(hl++, a);
    } while(a != CHAR_TERM);
}
