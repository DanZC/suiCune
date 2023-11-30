#include "constants.h"
#include "vram.h"
#include <stddef.h>

struct vram_s* vram;


#define check_field_bank0(_fld) static_assert(offsetof(struct vram_s, _fld) == (_fld - 0x8000), "");
#define check_field_bank1(_fld) static_assert(offsetof(struct vram_s, _fld) == (_fld - 0x8000 + 0x2000), "");

check_field_bank0(vTiles0);
check_field_bank0(vTiles1);
check_field_bank0(vTiles2);
check_field_bank0(vBGMap0);
check_field_bank0(vBGMap1);

check_field_bank1(vTiles3);
check_field_bank1(vTiles4);
check_field_bank1(vTiles5);
check_field_bank1(vBGMap2);
check_field_bank1(vBGMap3);