/*
assert_valid_rgb: MACRO
rept _NARG
    assert 0 <= (\1) && (\1) <= 31, "RGB channel must be 0-31"
    shift
endr
ENDM

RGB: MACRO
rept _NARG / 3
    assert_valid_rgb \1, \2, \3
    dw palred (\1) + palgreen (\2) + palblue (\3)
    shift 3
endr
ENDM
*/

#define rgb(_r,_g,_b) ((((_r)&0x1f) << 0) | (((_g)&0x1f) << 5) | (((_b)&0x1f) << 10))

// extracts the middle two colors from a 2bpp binary palette
// example usage:
// INCBIN "foo.gbcpal", middle_colors
#define middle_colors (PAL_COLOR_SIZE, PAL_COLOR_SIZE * 2)
/*
dbpixel: MACRO
if _NARG >= 4
// x tile, y tile, x pixel, y pixel
    db \1 * TILE_WIDTH + \3, \2 * TILE_WIDTH + \4
else
// x tile, y tile
    db \1 * TILE_WIDTH, \2 * TILE_WIDTH
endc
ENDM

*/
#define dbpixel2(_x, _y) _x * TILE_WIDTH, _y * TILE_WIDTH
#define dbpixel4(_x, _y, _px, _py) ((_x) * TILE_WIDTH) + (_px), ((_y) * TILE_WIDTH) + (_py)

/*

ldpixel: MACRO
if _NARG >= 5
// register, x tile, y tile, x pixel, y pixel
    lb \1, \2 * TILE_WIDTH + \4, \3 * TILE_WIDTH + \5
else
// register, x tile, y tile
    lb \1, \2 * TILE_WIDTH, \3 * TILE_WIDTH
endc
ENDM
*/

#define depixel2(x, y) do { LD_DE(((x * TILE_WIDTH) << 8) | (y * TILE_WIDTH)); } while(0)
#define depixel4(x, y, x2, y2) do { LD_DE((((x * TILE_WIDTH) + x2) << 8) | ((y * TILE_WIDTH) + y2)); } while(0)

#define bcpixel2(x, y) do { LD_BC(((x * TILE_WIDTH) << 8) | (y * TILE_WIDTH)); } while(0)
#define bcpixel4(x, y, x2, y2) do { LD_BC((((x * TILE_WIDTH) + x2) << 8) | ((y * TILE_WIDTH) + y2)); } while(0)

#define pixel2(x, y) (((x * TILE_WIDTH) << 8) | (y * TILE_WIDTH))
#define pixel4(x, y, x2, y2) ((((x * TILE_WIDTH) + x2) << 8) | ((y * TILE_WIDTH) + y2))

/*

#define depixel ldpixel de,
#define bcpixel ldpixel bc,

dbsprite: MACRO
// x tile, y tile, x pixel, y pixel, vtile offset, attributes
    db (\2 * TILE_WIDTH) % 0x100 + \4, (\1 * TILE_WIDTH) 0b 0x100 + \3, \5, \6
ENDM
*/
#define dbsprite(_x, _y, _px, _py, _o, _a) (((_y) * TILE_WIDTH) & 0xff) + (_py), (((_x) * TILE_WIDTH) & 0xff) + (_px), _o, _a
#define dbspriteoam(_x, _y, _px, _py, _o, _a) {.yCoord=(((_y) * TILE_WIDTH) & 0xff) + (_py), .xCoord=(((_x) * TILE_WIDTH) & 0xff) + (_px), .tileID=_o, .attributes=_a}
