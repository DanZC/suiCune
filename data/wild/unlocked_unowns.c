#include "../../constants.h"
#include "unlocked_unowns.h"
#include "../../util/variadic_macros.h"
#define unown_value_(_x) UNOWN_##_x
#define unown_set(...) CPPX_INVOKE( CPPX_CONCAT ( unown_value_, PP_NARG(__VA_ARGS__) ) , (__VA_ARGS__) )
#define unown_value_0() ((unown_letter_t)-1)
#define unown_value_1(_0) unown_value_(_0), unown_value_0()
#define unown_value_2(_0, _1) unown_value_(_0), unown_value_1(_1)
#define unown_value_3(_0, _1, _2) unown_value_(_0), unown_value_2(_1, _2)
#define unown_value_4(_0, _1, _2, _3) unown_value_(_0), unown_value_3(_1, _2, _3)
#define unown_value_5(_0, _1, _2, _3, _4) unown_value_(_0), unown_value_4(_1, _2, _3, _4)
#define unown_value_6(_0, _1, _2, _3, _4, _5) unown_value_(_0), unown_value_5(_1, _2, _3, _4, _5)
#define unown_value_7(_0, _1, _2, _3, _4, _5, _6) unown_value_(_0), unown_value_6(_1, _2, _3, _4, _5, _6)
#define unown_value_8(_0, _1, _2, _3, _4, _5, _6, _7) unown_value_(_0), unown_value_7(_1, _2, _3, _4, _5, _6, _7)
#define unown_value_9(_0, _1, _2, _3, _4, _5, _6, _7, _8) unown_value_(_0), unown_value_8(_1, _2, _3, _4, _5, _6, _7, _8)
#define unown_value_10(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9) unown_value_(_0), unown_value_9(_1, _2, _3, _4, _5, _6, _7, _8, _9)
#define unown_value_11(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) unown_value_(_0), unown_value_10(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10)

// unown_set: MACRO
// rept _NARG
// 	db UNOWN_\1
// 	shift
// endr
// 	db -1
// ENDM

static const unown_letter_t Set_A_K[] = {
    unown_set(A, B, C, D, E, F, G, H, I, J, K)
};
static const unown_letter_t Set_L_R[] = {
    unown_set(L, M, N, O, P, Q, R)
};
static const unown_letter_t Set_S_W[] = {
    unown_set(S, T, U, V, W)
};
static const unown_letter_t Set_X_Z[] = {
    unown_set(X, Y, Z)
};

const unown_letter_t* UnlockedUnownLetterSets[] = {
// entries correspond to wUnlockedUnowns bits
    [0] = Set_A_K, // ENGINE_UNLOCKED_UNOWNS_A_TO_K
    [1] = Set_L_R, // ENGINE_UNLOCKED_UNOWNS_L_TO_R
    [2] = Set_S_W, // ENGINE_UNLOCKED_UNOWNS_S_TO_W
    [3] = Set_X_Z, // ENGINE_UNLOCKED_UNOWNS_X_TO_Z
// .End
};
const uint8_t UnlockedUnownLetterSetsCount = lengthof(UnlockedUnownLetterSets);
