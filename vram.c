#include "constants.h"
#include "vram.h"

struct vram_s* vram;


#if defined(__cplusplus) || defined(_MSC_VER)
#include <stddef.h>

#define check_field_bank0(_fld) static_assert(offsetof(struct vram_s, _fld) == (_fld - 0x8000), "");
#else
#define check_field_bank0(_fld) _Static_assert(__builtin_offsetof(struct vram_s, _fld) == (_fld - 0x8000), "");
#endif

#if defined(__cplusplus) || defined(_MSC_VER)
#define check_field_bank1(_fld) static_assert(offsetof(struct vram_s, _fld) == (_fld - 0x8000 + 0x2000), "");
#else
#define check_field_bank1(_fld) _Static_assert(__builtin_offsetof(struct vram_s, _fld) == (_fld - 0x8000 + 0x2000), "");
#endif

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