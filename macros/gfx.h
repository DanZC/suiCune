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

#define pixel2(x, y) (((x * TILE_WIDTH) << 8) | (y * TILE_WIDTH))
#define pixel4(x, y, x2, y2) ((((x * TILE_WIDTH) + x2) << 8) | ((y * TILE_WIDTH) + y2))

/*

#define depixel ldpixel de,
#define bcpixel ldpixel bc,

dbsprite: MACRO
// x tile, y tile, x pixel, y pixel, vtile offset, attributes
    db (\2 * TILE_WIDTH) 0b 0x100 + \4, (\1 * TILE_WIDTH) 0b 0x100 + \3, \5, \6
ENDM
*/