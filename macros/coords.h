#define hlcoord(x, y, origin) LD_HL(((y) * SCREEN_WIDTH) + (x) + (origin))
#define bccoord(x, y, origin) LD_BC(((y) * SCREEN_WIDTH) + (x) + (origin))
#define decoord(x, y, origin) LD_DE(((y) * SCREEN_WIDTH) + (x) + (origin))

#define hlbgcoord(x, y, origin) LD_HL(((y) * SCREEN_WIDTH) + (x) + (origin))
#define bcbgcoord(x, y, origin) LD_BC(((y) * SCREEN_WIDTH) + (x) + (origin))
#define debgcoord(x, y, origin) LD_DE(((y) * SCREEN_WIDTH) + (x) + (origin))

#define ldcoord_a(x, y, origin) LD_addr_A(((y) * SCREEN_WIDTH) + (x) + (origin))
#define lda_coord(x, y, origin) LD_A_addr(((y) * SCREEN_WIDTH) + (x) + (origin))

#define coord(x, y, origin) (((y) * SCREEN_WIDTH) + (x) + (origin))