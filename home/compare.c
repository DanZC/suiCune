#include "../constants.h"
#include "compare.h"

//  Compare c bytes at de and hl.
//  Return 0 (z) if they all match.
//  Return -1 (c) if de is less than hl.
int CompareBytes(const void* de, const void* hl, uint32_t c){
    const uint8_t* de_ = de;
    const uint8_t* hl_ = hl;
    do {
        if(*(de_) < *(hl_)) 
            return -1;
        if(*(de_) > *(hl_)) 
            return 1;
        de_++, hl_++;
    } while(--c != 0);
    return 0;
}

//  Compare bc bytes at de and hl.
//  Return true if they all match.
//  DEPRECATED: Use CompareBytes instead.
bool CompareBytesLong(const void* de, const void* hl, uint16_t bc){
    const uint8_t* de_ = de;
    const uint8_t* hl_ = hl;
    do {
        if(*(de_) != *(hl_)) 
            return false;
        de_++, hl_++;
    } while(--bc != 0);
    return true;
}
