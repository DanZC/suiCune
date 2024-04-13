#include "../../constants.h"
#include "../../util/variadic_macros.h"
#include <stddef.h>
#define tmhm_id_byte(_x) (_x >> 3)
#define tmhm_value_(_x, _y) ((_x == (_y##_TMNUM >> 3))? (1 << (_y##_TMNUM & 7)): 0) 
#define tm_byte_(_x, ...) [_x] = CPPX_INVOKE( CPPX_CONCAT ( tmhm_value_, PP_NARG(__VA_ARGS__) ) , (_x, __VA_ARGS__) )
#define tmhm_value_1(_x, _0) tmhm_value_(_x, _0)
#define tmhm_value_2(_x, _0, _1)  tmhm_value_1(_x, _0) | tmhm_value_(_x, _1) 
#define tmhm_value_3(_x, _0, _1, _2)  tmhm_value_2(_x, _0, _1) | tmhm_value_(_x, _2) 
#define tmhm_value_4(_x, _0, _1, _2, _3)  tmhm_value_3(_x, _0, _1, _2) | tmhm_value_(_x, _3) 
#define tmhm_value_5(_x, _0, _1, _2, _3, _4)  tmhm_value_4(_x, _0, _1, _2, _3) | tmhm_value_(_x, _4) 
#define tmhm_value_6(_x, _0, _1, _2, _3, _4, _5)  tmhm_value_5(_x, _0, _1, _2, _3, _4) | tmhm_value_(_x, _5) 
#define tmhm_value_7(_x, _0, _1, _2, _3, _4, _5, _6)  tmhm_value_6(_x, _0, _1, _2, _3, _4, _5) | tmhm_value_(_x, _6) 
#define tmhm_value_8(_x, _0, _1, _2, _3, _4, _5, _6, _7)  tmhm_value_7(_x, _0, _1, _2, _3, _4, _5, _6) | tmhm_value_(_x, _7) 
#define tmhm_value_9(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8)  tmhm_value_8(_x, _0, _1, _2, _3, _4, _5, _6, _7) | tmhm_value_(_x, _8) 
#define tmhm_value_10(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9)  tmhm_value_9(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8) | tmhm_value_(_x, _9) 
#define tmhm_value_11(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10)  tmhm_value_10(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9) | tmhm_value_(_x, _10) 
#define tmhm_value_12(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11)  tmhm_value_11(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) | tmhm_value_(_x, _11) 
#define tmhm_value_13(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12)  tmhm_value_12(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) | tmhm_value_(_x, _12) 
#define tmhm_value_14(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13)  tmhm_value_13(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) | tmhm_value_(_x, _13) 
#define tmhm_value_15(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14)  tmhm_value_14(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) | tmhm_value_(_x, _14) 
#define tmhm_value_16(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15)  tmhm_value_15(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) | tmhm_value_(_x, _15) 
#define tmhm_value_17(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16)  tmhm_value_16(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) | tmhm_value_(_x, _16) 
#define tmhm_value_18(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17)  tmhm_value_17(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) | tmhm_value_(_x, _17) 
#define tmhm_value_19(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18)  tmhm_value_18(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) | tmhm_value_(_x, _18) 
#define tmhm_value_20(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19)  tmhm_value_19(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) | tmhm_value_(_x, _19) 
#define tmhm_value_21(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20)  tmhm_value_20(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) | tmhm_value_(_x, _20) 
#define tmhm_value_22(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21)  tmhm_value_21(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20) | tmhm_value_(_x, _21) 
#define tmhm_value_23(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22)  tmhm_value_22(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21) | tmhm_value_(_x, _22) 
#define tmhm_value_24(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23)  tmhm_value_23(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22) | tmhm_value_(_x, _23) 
#define tmhm_value_25(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24)  tmhm_value_24(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23) | tmhm_value_(_x, _24) 
#define tmhm_value_26(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25)  tmhm_value_25(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24) | tmhm_value_(_x, _25) 
#define tmhm_value_27(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26)  tmhm_value_26(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25) | tmhm_value_(_x, _26) 
#define tmhm_value_28(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27)  tmhm_value_27(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26) | tmhm_value_(_x, _27) 
#define tmhm_value_29(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28)  tmhm_value_28(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27) | tmhm_value_(_x, _28) 
#define tmhm_value_30(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29)  tmhm_value_29(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28) | tmhm_value_(_x, _29) 
#define tmhm_value_31(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30)  tmhm_value_30(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29) | tmhm_value_(_x, _30) 
#define tmhm_value_32(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31)  tmhm_value_31(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30) | tmhm_value_(_x, _31) 
#define tmhm_value_33(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32)  tmhm_value_32(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31) | tmhm_value_(_x, _32) 
#define tmhm_value_34(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33)  tmhm_value_33(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32) | tmhm_value_(_x, _33) 
#define tmhm_value_35(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34)  tmhm_value_34(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33) | tmhm_value_(_x, _34) 
#define tmhm_value_36(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35)  tmhm_value_35(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34) | tmhm_value_(_x, _35) 
#define tmhm_value_37(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36)  tmhm_value_36(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35) | tmhm_value_(_x, _36) 
#define tmhm_value_38(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37)  tmhm_value_37(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36) | tmhm_value_(_x, _37) 
#define tmhm_value_39(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38)  tmhm_value_38(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37) | tmhm_value_(_x, _38) 
#define tmhm_value_40(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39)  tmhm_value_39(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38) | tmhm_value_(_x, _39) 
#define tmhm_value_41(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40)  tmhm_value_40(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39) | tmhm_value_(_x, _40) 
#define tmhm_value_42(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41)  tmhm_value_41(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40) | tmhm_value_(_x, _41) 
#define tmhm_value_43(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42)  tmhm_value_42(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41) | tmhm_value_(_x, _42) 
#define tmhm_value_44(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43)  tmhm_value_43(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42) | tmhm_value_(_x, _43) 
#define tmhm_value_45(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44)  tmhm_value_44(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43) | tmhm_value_(_x, _44) 
#define tmhm_value_46(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45)  tmhm_value_45(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44) | tmhm_value_(_x, _45) 
#define tmhm_value_47(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46)  tmhm_value_46(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45) | tmhm_value_(_x, _46) 
#define tmhm_value_48(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47)  tmhm_value_47(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46) | tmhm_value_(_x, _47) 
#define tmhm_value_49(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48)  tmhm_value_48(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47) | tmhm_value_(_x, _48) 
#define tmhm_value_50(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49)  tmhm_value_49(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48) | tmhm_value_(_x, _49) 
#define tmhm_value_51(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50)  tmhm_value_50(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49) | tmhm_value_(_x, _50) 
#define tmhm_value_52(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51)  tmhm_value_51(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50) | tmhm_value_(_x, _51) 
#define tmhm_value_53(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52)  tmhm_value_52(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51) | tmhm_value_(_x, _52) 
#define tmhm_value_54(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53)  tmhm_value_53(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52) | tmhm_value_(_x, _53) 
#define tmhm_value_55(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54)  tmhm_value_54(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53) | tmhm_value_(_x, _54) 
#define tmhm_value_56(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55)  tmhm_value_55(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54) | tmhm_value_(_x, _55) 
#define tmhm_value_57(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56)  tmhm_value_56(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55) | tmhm_value_(_x, _56) 
#define tmhm_value_58(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57)  tmhm_value_57(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56) | tmhm_value_(_x, _57) 
#define tmhm_value_59(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58)  tmhm_value_58(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57) | tmhm_value_(_x, _58) 
#define tmhm_value_60(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59)  tmhm_value_59(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58) | tmhm_value_(_x, _59) 
#define tmhm_value_61(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60)  tmhm_value_60(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59) | tmhm_value_(_x, _60) 
#define tmhm_value_62(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61)  tmhm_value_61(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60) | tmhm_value_(_x, _61) 
#define tmhm_value_63(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62)  tmhm_value_62(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61) | tmhm_value_(_x, _62) 
#define tmhm_value_64(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63)  tmhm_value_63(_x, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62) | tmhm_value_(_x, _63) 

#define tmhm_learnset(...) {tm_byte_(0, __VA_ARGS__), \
    tm_byte_(1, __VA_ARGS__), \
    tm_byte_(2, __VA_ARGS__), \
    tm_byte_(3, __VA_ARGS__), \
    tm_byte_(4, __VA_ARGS__), \
    tm_byte_(5, __VA_ARGS__), \
    tm_byte_(6, __VA_ARGS__), \
    tm_byte_(7, __VA_ARGS__)}

#define dn(_x, _y) ((((_x) & 0xf) << 4) | ((_y) & 0xf))
//  used in data/pokemon/base_stats/*.asm
const struct BaseData BasePokemonData[] = { 
    [BULBASAUR-1] = {
        .dexNo = BULBASAUR , // 001
        .stats = { 45,  49,  49,  45,  65,  65}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {GRASS, POISON }, // type
        .catchRate = 45 , // catch rate
        .exp = 64 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F12_5 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_MONSTER, EGG_PLANT ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, HIDDEN_POWER, SUNNY_DAY, SWEET_SCENT, SNORE, PROTECT, GIGA_DRAIN, ENDURE, FRUSTRATION, SOLARBEAM, RETURN, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, DEFENSE_CURL, REST, ATTRACT, FURY_CUTTER, CUT, FLASH), 
    // end
    },
    [IVYSAUR-1] = {
        .dexNo = IVYSAUR , // 002
        .stats = { 60,  62,  63,  60,  80,  80}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {GRASS, POISON }, // type
        .catchRate = 45 , // catch rate
        .exp = 141 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F12_5 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_MONSTER, EGG_PLANT ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, HIDDEN_POWER, SUNNY_DAY, SWEET_SCENT, SNORE, PROTECT, GIGA_DRAIN, ENDURE, FRUSTRATION, SOLARBEAM, RETURN, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, DEFENSE_CURL, REST, ATTRACT, FURY_CUTTER, CUT, FLASH), 
    // end
    },
    [VENUSAUR-1] = {
        .dexNo = VENUSAUR , // 003
        .stats = { 80,  82,  83,  80, 100, 100}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {GRASS, POISON }, // type
        .catchRate = 45 , // catch rate
        .exp = 208 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F12_5 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_MONSTER, EGG_PLANT ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, ROAR, TOXIC, HIDDEN_POWER, SUNNY_DAY, SWEET_SCENT, SNORE, HYPER_BEAM, PROTECT, GIGA_DRAIN, ENDURE, FRUSTRATION, SOLARBEAM, RETURN, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, DEFENSE_CURL, REST, ATTRACT, FURY_CUTTER, CUT, FLASH), 
    // end
    },
    [CHARMANDER-1] = {
        .dexNo = CHARMANDER , // 004
        .stats = { 39,  52,  43,  65,  60,  50}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {FIRE, FIRE }, // type
        .catchRate = 45 , // catch rate
        .exp = 65 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F12_5 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_MONSTER, EGG_DRAGON ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, ENDURE, FRUSTRATION, IRON_TAIL, DRAGONBREATH, RETURN, DIG, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, FIRE_BLAST, SWIFT, DEFENSE_CURL, REST, ATTRACT, FIRE_PUNCH, FURY_CUTTER, CUT, STRENGTH, FLAMETHROWER), 
    // end
    },
    [CHARMELEON-1] = {
        .dexNo = CHARMELEON , // 005
        .stats = { 58,  64,  58,  80,  80,  65}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {FIRE, FIRE }, // type
        .catchRate = 45 , // catch rate
        .exp = 142 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F12_5 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_MONSTER, EGG_DRAGON ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, ENDURE, FRUSTRATION, IRON_TAIL, DRAGONBREATH, RETURN, DIG, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, FIRE_BLAST, SWIFT, DEFENSE_CURL, REST, ATTRACT, FIRE_PUNCH, FURY_CUTTER, CUT, STRENGTH, FLAMETHROWER), 
    // end
    },
    [CHARIZARD-1] = {
        .dexNo = CHARIZARD , // 006
        .stats = { 78,  84,  78, 100, 109,  85}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {FIRE, FLYING }, // type
        .catchRate = 45 , // catch rate
        .exp = 209 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F12_5 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_MONSTER, EGG_DRAGON ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, ROAR, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, PROTECT, ENDURE, FRUSTRATION, IRON_TAIL, DRAGONBREATH, EARTHQUAKE, RETURN, DIG, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SANDSTORM, FIRE_BLAST, SWIFT, DEFENSE_CURL, REST, ATTRACT, STEEL_WING, FIRE_PUNCH, FURY_CUTTER, CUT, FLY, STRENGTH, FLAMETHROWER), 
    // end
    },
    [SQUIRTLE-1] = {
        .dexNo = SQUIRTLE , // 007
        .stats = { 44,  48,  65,  43,  50,  64}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {WATER, WATER }, // type
        .catchRate = 45 , // catch rate
        .exp = 66 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F12_5 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_MONSTER, EGG_WATER_1 ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, ROLLOUT, TOXIC, ROCK_SMASH, HIDDEN_POWER, SNORE, BLIZZARD, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, IRON_TAIL, RETURN, DIG, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, DEFENSE_CURL, REST, ATTRACT, SURF, STRENGTH, WHIRLPOOL, WATERFALL, ICE_BEAM), 
    // end
    },
    [WARTORTLE-1] = {
        .dexNo = WARTORTLE , // 008
        .stats = { 59,  63,  80,  58,  65,  80}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {WATER, WATER }, // type
        .catchRate = 45 , // catch rate
        .exp = 143 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F12_5 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_MONSTER, EGG_WATER_1 ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, ROLLOUT, TOXIC, ROCK_SMASH, HIDDEN_POWER, SNORE, BLIZZARD, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, IRON_TAIL, RETURN, DIG, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, DEFENSE_CURL, REST, ATTRACT, SURF, STRENGTH, WHIRLPOOL, WATERFALL, ICE_BEAM), 
    // end
    },
    [BLASTOISE-1] = {
        .dexNo = BLASTOISE , // 009
        .stats = { 79,  83, 100,  78,  85, 105}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {WATER, WATER }, // type
        .catchRate = 45 , // catch rate
        .exp = 210 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F12_5 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_MONSTER, EGG_WATER_1 ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, ROLLOUT, ROAR, TOXIC, ROCK_SMASH, HIDDEN_POWER, SNORE, BLIZZARD, HYPER_BEAM, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, IRON_TAIL, EARTHQUAKE, RETURN, DIG, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, DEFENSE_CURL, REST, ATTRACT, SURF, STRENGTH, WHIRLPOOL, WATERFALL, ICE_BEAM), 
    // end
    },
    [CATERPIE-1] = {
        .dexNo = CATERPIE , // 010
        .stats = { 45,  30,  35,  45,  20,  20}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {BUG, BUG }, // type
        .catchRate = 255 , // catch rate
        .exp = 53 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 15 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_BUG, EGG_BUG ), // egg groups
    // tm/hm learnset
        .TMHM = { NULL }, 
    // end
    },
    [METAPOD-1] = {
        .dexNo = METAPOD , // 011
        .stats = { 50,  20,  55,  30,  25,  25}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {BUG, BUG }, // type
        .catchRate = 120 , // catch rate
        .exp = 72 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 15 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_BUG, EGG_BUG ), // egg groups
    // tm/hm learnset
        .TMHM = { NULL },
    // end
    },
    [BUTTERFREE-1] = {
        .dexNo = BUTTERFREE , // 012
        .stats = { 60,  45,  50,  70,  80,  80}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {BUG, FLYING }, // type
        .catchRate = 45 , // catch rate
        .exp = 160 , // base exp
        .items = {NO_ITEM, SILVERPOWDER }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 15 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_BUG, EGG_BUG ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, HIDDEN_POWER, SUNNY_DAY, SWEET_SCENT, SNORE, HYPER_BEAM, PROTECT, GIGA_DRAIN, ENDURE, FRUSTRATION, SOLARBEAM, RETURN, PSYCHIC_M, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, REST, ATTRACT, NIGHTMARE, FLASH), 
    // end
    },
    [WEEDLE-1] = {
        .dexNo = WEEDLE , // 013
        .stats = { 40,  35,  30,  50,  20,  20}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {BUG, POISON }, // type
        .catchRate = 255 , // catch rate
        .exp = 52 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 15 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_BUG, EGG_BUG ), // egg groups
    // tm/hm learnset
        .TMHM = { NULL },
    // end
    },
    [KAKUNA-1] = {
        .dexNo = KAKUNA , // 014
        .stats = { 45,  25,  50,  35,  25,  25}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {BUG, POISON }, // type
        .catchRate = 120 , // catch rate
        .exp = 71 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 15 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_BUG, EGG_BUG ), // egg groups
    // tm/hm learnset
        .TMHM = { NULL },
    // end
    },
    [BEEDRILL-1] = {
        .dexNo = BEEDRILL , // 015
        .stats = { 65,  80,  40,  75,  45,  80}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {BUG, POISON }, // type
        .catchRate = 45 , // catch rate
        .exp = 159 , // base exp
        .items = {NO_ITEM, POISON_BARB }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 15 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_BUG, EGG_BUG ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, HIDDEN_POWER, SUNNY_DAY, SWEET_SCENT, SNORE, HYPER_BEAM, PROTECT, GIGA_DRAIN, ENDURE, FRUSTRATION, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SLUDGE_BOMB, SWIFT, REST, ATTRACT, FURY_CUTTER, CUT), 
    // end
    },
    [PIDGEY-1] = {
        .dexNo = PIDGEY , // 016
        .stats = { 40,  45,  40,  56,  35,  35}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {NORMAL, FLYING }, // type
        .catchRate = 255 , // catch rate
        .exp = 55 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 15 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_FLYING, EGG_FLYING ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, ENDURE, FRUSTRATION, RETURN, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, DETECT, REST, ATTRACT, THIEF, STEEL_WING, FLY), 
    // end
    },
    [PIDGEOTTO-1] = {
        .dexNo = PIDGEOTTO , // 017
        .stats = { 63,  60,  55,  71,  50,  50}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {NORMAL, FLYING }, // type
        .catchRate = 120 , // catch rate
        .exp = 113 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 15 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_FLYING, EGG_FLYING ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, ENDURE, FRUSTRATION, RETURN, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, DETECT, REST, ATTRACT, THIEF, STEEL_WING, FLY), 
    // end
    },
    [PIDGEOT-1] = {
        .dexNo = PIDGEOT , // 018
        .stats = { 83,  80,  75,  91,  70,  70}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {NORMAL, FLYING }, // type
        .catchRate = 45 , // catch rate
        .exp = 172 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 15 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_FLYING, EGG_FLYING ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, PROTECT, ENDURE, FRUSTRATION, RETURN, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, DETECT, REST, ATTRACT, THIEF, STEEL_WING, FLY), 
    // end
    },
    [RATTATA-1] = {
        .dexNo = RATTATA , // 019
        .stats = { 30,  56,  35,  72,  25,  35}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {NORMAL, NORMAL }, // type
        .catchRate = 255 , // catch rate
        .exp = 57 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 15 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_GROUND, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, BLIZZARD, ICY_WIND, PROTECT, ENDURE, FRUSTRATION, IRON_TAIL, THUNDER, RETURN, DIG, SHADOW_BALL, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, DEFENSE_CURL, REST, ATTRACT, THIEF), 
    // end
    },
    [RATICATE-1] = {
        .dexNo = RATICATE , // 020
        .stats = { 55,  81,  60,  97,  50,  70}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {NORMAL, NORMAL }, // type
        .catchRate = 90 , // catch rate
        .exp = 116 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 15 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_GROUND, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, ROAR, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, BLIZZARD, HYPER_BEAM, ICY_WIND, PROTECT, ENDURE, FRUSTRATION, IRON_TAIL, THUNDER, RETURN, DIG, SHADOW_BALL, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, DEFENSE_CURL, REST, ATTRACT, THIEF, CUT, STRENGTH, THUNDERBOLT, ICE_BEAM), 
    // end
    },
    [SPEAROW-1] = {
        .dexNo = SPEAROW , // 021
        .stats = { 40,  60,  30,  70,  31,  31}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {NORMAL, FLYING }, // type
        .catchRate = 255 , // catch rate
        .exp = 58 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 15 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_FLYING, EGG_FLYING ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, ENDURE, FRUSTRATION, RETURN, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, DETECT, REST, ATTRACT, THIEF, STEEL_WING, FLY), 
    // end
    },
    [FEAROW-1] = {
        .dexNo = FEAROW , // 022
        .stats = { 65,  90,  65, 100,  61,  61}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {NORMAL, FLYING }, // type
        .catchRate = 90 , // catch rate
        .exp = 162 , // base exp
        .items = {NO_ITEM, SHARP_BEAK }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 15 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_FLYING, EGG_FLYING ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, PROTECT, ENDURE, FRUSTRATION, RETURN, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, DETECT, REST, ATTRACT, THIEF, STEEL_WING, FLY), 
    // end
    },
    [EKANS-1] = {
        .dexNo = EKANS , // 023
        .stats = { 35,  60,  44,  55,  40,  54}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {POISON, POISON }, // type
        .catchRate = 255 , // catch rate
        .exp = 62 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_GROUND, EGG_DRAGON ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, GIGA_DRAIN, ENDURE, FRUSTRATION, EARTHQUAKE, RETURN, DIG, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SLUDGE_BOMB, REST, ATTRACT, THIEF, STRENGTH), 
    // end
    },
    [ARBOK-1] = {
        .dexNo = ARBOK , // 024
        .stats = { 60,  85,  69,  80,  65,  79}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {POISON, POISON }, // type
        .catchRate = 90 , // catch rate
        .exp = 147 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_GROUND, EGG_DRAGON ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, PROTECT, GIGA_DRAIN, ENDURE, FRUSTRATION, EARTHQUAKE, RETURN, DIG, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SLUDGE_BOMB, REST, ATTRACT, THIEF, STRENGTH), 
    // end
    },
    [PIKACHU-1] = {
        .dexNo = PIKACHU , // 025
        .stats = { 35,  55,  30,  90,  50,  40}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {ELECTRIC, ELECTRIC }, // type
        .catchRate = 190 , // catch rate
        .exp = 82 , // base exp
        .items = {NO_ITEM, BERRY }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 10 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_GROUND, EGG_FAIRY ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, ROLLOUT, TOXIC, ZAP_CANNON, HIDDEN_POWER, SNORE, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, IRON_TAIL, THUNDER, RETURN, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, DEFENSE_CURL, THUNDERPUNCH, DETECT, REST, ATTRACT, STRENGTH, FLASH, THUNDERBOLT), 
    // end
    },
    [RAICHU-1] = {
        .dexNo = RAICHU , // 026
        .stats = { 60,  90,  55, 100,  90,  80}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {ELECTRIC, ELECTRIC }, // type
        .catchRate = 75 , // catch rate
        .exp = 122 , // base exp
        .items = {NO_ITEM, BERRY }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 10 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_GROUND, EGG_FAIRY ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, ROLLOUT, TOXIC, ZAP_CANNON, HIDDEN_POWER, SNORE, HYPER_BEAM, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, IRON_TAIL, THUNDER, RETURN, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, DEFENSE_CURL, THUNDERPUNCH, DETECT, REST, ATTRACT, THIEF, STRENGTH, FLASH, THUNDERBOLT), 
    // end
    },
    [SANDSHREW-1] = {
        .dexNo = SANDSHREW , // 027
        .stats = { 50,  75,  85,  40,  20,  30}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {GROUND, GROUND }, // type
        .catchRate = 255 , // catch rate
        .exp = 93 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_GROUND, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, ROLLOUT, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, ENDURE, FRUSTRATION, IRON_TAIL, EARTHQUAKE, RETURN, DIG, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SANDSTORM, SWIFT, DEFENSE_CURL, DETECT, REST, ATTRACT, THIEF, FURY_CUTTER, CUT, STRENGTH), 
    // end
    },
    [SANDSLASH-1] = {
        .dexNo = SANDSLASH , // 028
        .stats = { 75, 100, 110,  65,  45,  55}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {GROUND, GROUND }, // type
        .catchRate = 90 , // catch rate
        .exp = 163 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_GROUND, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, ROLLOUT, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, PROTECT, ENDURE, FRUSTRATION, IRON_TAIL, EARTHQUAKE, RETURN, DIG, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SANDSTORM, SWIFT, DEFENSE_CURL, DETECT, REST, ATTRACT, THIEF, FURY_CUTTER, CUT, STRENGTH), 
    // end
    },
    [NIDORAN_F-1] = {
        .dexNo = NIDORAN_F , // 029
        .stats = { 55,  47,  52,  41,  40,  40}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {POISON, POISON }, // type
        .catchRate = 235 , // catch rate
        .exp = 59 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F100 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_MONSTER, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, HIDDEN_POWER, SUNNY_DAY, SNORE, BLIZZARD, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, IRON_TAIL, THUNDER, RETURN, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, DEFENSE_CURL, DETECT, REST, ATTRACT, THIEF, THUNDERBOLT), 
    // end
    },
    [NIDORINA-1] = {
        .dexNo = NIDORINA , // 030
        .stats = { 70,  62,  67,  56,  55,  55}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {POISON, POISON }, // type
        .catchRate = 120 , // catch rate
        .exp = 117 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F100 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_NONE, EGG_NONE ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, BLIZZARD, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, IRON_TAIL, THUNDER, RETURN, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, DEFENSE_CURL, DETECT, REST, ATTRACT, THIEF, STRENGTH, THUNDERBOLT, ICE_BEAM), 
    // end
    },
    [NIDOQUEEN-1] = {
        .dexNo = NIDOQUEEN , // 031
        .stats = { 90,  82,  87,  76,  75,  85}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {POISON, GROUND }, // type
        .catchRate = 45 , // catch rate
        .exp = 194 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F100 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_NONE, EGG_NONE ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, ROAR, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, BLIZZARD, HYPER_BEAM, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, IRON_TAIL, THUNDER, EARTHQUAKE, RETURN, SHADOW_BALL, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, SANDSTORM, FIRE_BLAST, DEFENSE_CURL, THUNDERPUNCH, DETECT, REST, ATTRACT, THIEF, FIRE_PUNCH, FURY_CUTTER, SURF, STRENGTH, FLAMETHROWER, THUNDERBOLT, ICE_BEAM), 
    // end
    },
    [NIDORAN_M-1] = {
        .dexNo = NIDORAN_M , // 032
        .stats = { 46,  57,  40,  50,  40,  40}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {POISON, POISON }, // type
        .catchRate = 235 , // catch rate
        .exp = 60 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F0 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_MONSTER, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, HIDDEN_POWER, SUNNY_DAY, SNORE, BLIZZARD, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, IRON_TAIL, THUNDER, RETURN, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, DEFENSE_CURL, DETECT, REST, ATTRACT, THIEF, THUNDERBOLT), 
    // end
    },
    [NIDORINO-1] = {
        .dexNo = NIDORINO , // 033
        .stats = { 61,  72,  57,  65,  55,  55}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {POISON, POISON }, // type
        .catchRate = 120 , // catch rate
        .exp = 118 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F0 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_MONSTER, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, BLIZZARD, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, IRON_TAIL, THUNDER, RETURN, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, DEFENSE_CURL, DETECT, REST, ATTRACT, THIEF, STRENGTH, THUNDERBOLT, ICE_BEAM), 
    // end
    },
    [NIDOKING-1] = {
        .dexNo = NIDOKING , // 034
        .stats = { 81,  92,  77,  85,  85,  75}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {POISON, GROUND }, // type
        .catchRate = 45 , // catch rate
        .exp = 195 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F0 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_MONSTER, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, ROAR, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, BLIZZARD, HYPER_BEAM, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, IRON_TAIL, THUNDER, EARTHQUAKE, RETURN, SHADOW_BALL, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, SANDSTORM, FIRE_BLAST, DEFENSE_CURL, THUNDERPUNCH, DETECT, REST, ATTRACT, THIEF, FIRE_PUNCH, FURY_CUTTER, SURF, STRENGTH, FLAMETHROWER, THUNDERBOLT, ICE_BEAM), 
    // end
    },
    [CLEFAIRY-1] = {
        .dexNo = CLEFAIRY , // 035
        .stats = { 70,  45,  48,  35,  60,  65}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {NORMAL, NORMAL }, // type
        .catchRate = 150 , // catch rate
        .exp = 68 , // base exp
        .items = {MYSTERYBERRY, MOON_STONE }, // items
        .gender = GENDER_F75 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 10 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_FAIRY, EGG_FAIRY ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, ROLLOUT, TOXIC, ZAP_CANNON, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SNORE, BLIZZARD, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, SOLARBEAM, IRON_TAIL, THUNDER, RETURN, PSYCHIC_M, SHADOW_BALL, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, FIRE_BLAST, DEFENSE_CURL, THUNDERPUNCH, DREAM_EATER, DETECT, REST, ATTRACT, FIRE_PUNCH, NIGHTMARE, STRENGTH, FLASH, FLAMETHROWER, THUNDERBOLT, ICE_BEAM), 
    // end
    },
    [CLEFABLE-1] = {
        .dexNo = CLEFABLE , // 036
        .stats = { 95,  70,  73,  60,  85,  90}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {NORMAL, NORMAL }, // type
        .catchRate = 25 , // catch rate
        .exp = 129 , // base exp
        .items = {MYSTERYBERRY, MOON_STONE }, // items
        .gender = GENDER_F75 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 10 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_FAIRY, EGG_FAIRY ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, ROLLOUT, TOXIC, ZAP_CANNON, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SNORE, BLIZZARD, HYPER_BEAM, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, SOLARBEAM, IRON_TAIL, THUNDER, RETURN, PSYCHIC_M, SHADOW_BALL, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, FIRE_BLAST, DEFENSE_CURL, THUNDERPUNCH, DREAM_EATER, DETECT, REST, ATTRACT, FIRE_PUNCH, NIGHTMARE, STRENGTH, FLASH, FLAMETHROWER, THUNDERBOLT, ICE_BEAM), 
    // end
    },
    [VULPIX-1] = {
        .dexNo = VULPIX , // 037
        .stats = { 38,  41,  40,  65,  50,  65}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {FIRE, FIRE }, // type
        .catchRate = 190 , // catch rate
        .exp = 63 , // base exp
        .items = {BURNT_BERRY, BURNT_BERRY }, // items
        .gender = GENDER_F75 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_GROUND, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, ENDURE, FRUSTRATION, IRON_TAIL, RETURN, DIG, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, FIRE_BLAST, SWIFT, REST, ATTRACT, FLAMETHROWER), 
    // end
    },
    [NINETALES-1] = {
        .dexNo = NINETALES , // 038
        .stats = { 73,  76,  75, 100,  81, 100}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {FIRE, FIRE }, // type
        .catchRate = 75 , // catch rate
        .exp = 178 , // base exp
        .items = {BURNT_BERRY, BURNT_BERRY }, // items
        .gender = GENDER_F75 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_GROUND, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, ROAR, TOXIC, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, PROTECT, ENDURE, FRUSTRATION, IRON_TAIL, RETURN, DIG, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, FIRE_BLAST, SWIFT, REST, ATTRACT, FLAMETHROWER), 
    // end
    },
    [JIGGLYPUFF-1] = {
        .dexNo = JIGGLYPUFF , // 039
        .stats = {115,  45,  20,  20,  45,  25}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {NORMAL, NORMAL }, // type
        .catchRate = 170 , // catch rate
        .exp = 76 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F75 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 10 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_FAIRY, EGG_FAIRY ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, ROLLOUT, TOXIC, ZAP_CANNON, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SNORE, BLIZZARD, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, SOLARBEAM, THUNDER, RETURN, PSYCHIC_M, SHADOW_BALL, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, FIRE_BLAST, DEFENSE_CURL, THUNDERPUNCH, DREAM_EATER, DETECT, REST, ATTRACT, FIRE_PUNCH, NIGHTMARE, STRENGTH, FLASH, FLAMETHROWER, THUNDERBOLT, ICE_BEAM), 
    // end
    },
    [WIGGLYTUFF-1] = {
        .dexNo = WIGGLYTUFF , // 040
        .stats = {140,  70,  45,  45,  75,  50}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {NORMAL, NORMAL }, // type
        .catchRate = 50 , // catch rate
        .exp = 109 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F75 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 10 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_FAIRY, EGG_FAIRY ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, ROLLOUT, TOXIC, ZAP_CANNON, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SNORE, BLIZZARD, HYPER_BEAM, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, SOLARBEAM, THUNDER, RETURN, PSYCHIC_M, SHADOW_BALL, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, FIRE_BLAST, DEFENSE_CURL, THUNDERPUNCH, DREAM_EATER, DETECT, REST, ATTRACT, FIRE_PUNCH, NIGHTMARE, STRENGTH, FLASH, FLAMETHROWER, THUNDERBOLT, ICE_BEAM), 
    // end
    },
    [ZUBAT-1] = {
        .dexNo = ZUBAT , // 041
        .stats = { 40,  45,  35,  55,  30,  40}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {POISON, FLYING }, // type
        .catchRate = 255 , // catch rate
        .exp = 54 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 15 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_FLYING, EGG_FLYING ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, GIGA_DRAIN, ENDURE, FRUSTRATION, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, DETECT, REST, ATTRACT, THIEF, STEEL_WING), 
    // end
    },
    [GOLBAT-1] = {
        .dexNo = GOLBAT , // 042
        .stats = { 75,  80,  70,  90,  65,  75}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {POISON, FLYING }, // type
        .catchRate = 90 , // catch rate
        .exp = 171 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 15 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_FLYING, EGG_FLYING ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, PROTECT, GIGA_DRAIN, ENDURE, FRUSTRATION, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, DETECT, REST, ATTRACT, THIEF, STEEL_WING), 
    // end
    },
    [ODDISH-1] = {
        .dexNo = ODDISH , // 043
        .stats = { 45,  50,  55,  30,  75,  65}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {GRASS, POISON }, // type
        .catchRate = 255 , // catch rate
        .exp = 78 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_PLANT, EGG_PLANT ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, HIDDEN_POWER, SUNNY_DAY, SWEET_SCENT, SNORE, PROTECT, GIGA_DRAIN, ENDURE, FRUSTRATION, SOLARBEAM, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SLUDGE_BOMB, REST, ATTRACT, CUT, FLASH), 
    // end
    },
    [GLOOM-1] = {
        .dexNo = GLOOM , // 044
        .stats = { 60,  65,  70,  40,  85,  75}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {GRASS, POISON }, // type
        .catchRate = 120 , // catch rate
        .exp = 132 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_PLANT, EGG_PLANT ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, HIDDEN_POWER, SUNNY_DAY, SWEET_SCENT, SNORE, PROTECT, GIGA_DRAIN, ENDURE, FRUSTRATION, SOLARBEAM, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SLUDGE_BOMB, REST, ATTRACT, CUT, FLASH), 
    // end
    },
    [VILEPLUME-1] = {
        .dexNo = VILEPLUME , // 045
        .stats = { 75,  80,  85,  50, 100,  90}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {GRASS, POISON }, // type
        .catchRate = 45 , // catch rate
        .exp = 184 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_PLANT, EGG_PLANT ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, HIDDEN_POWER, SUNNY_DAY, SWEET_SCENT, SNORE, HYPER_BEAM, PROTECT, GIGA_DRAIN, ENDURE, FRUSTRATION, SOLARBEAM, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SLUDGE_BOMB, REST, ATTRACT, CUT, FLASH), 
    // end
    },
    [PARAS-1] = {
        .dexNo = PARAS , // 046
        .stats = { 35,  70,  55,  25,  45,  55}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {BUG, GRASS }, // type
        .catchRate = 190 , // catch rate
        .exp = 70 , // base exp
        .items = {TINYMUSHROOM, BIG_MUSHROOM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_BUG, EGG_PLANT ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SWEET_SCENT, SNORE, PROTECT, GIGA_DRAIN, ENDURE, FRUSTRATION, SOLARBEAM, RETURN, DIG, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SLUDGE_BOMB, REST, ATTRACT, THIEF, FURY_CUTTER, CUT, FLASH), 
    // end
    },
    [PARASECT-1] = {
        .dexNo = PARASECT , // 047
        .stats = { 60,  95,  80,  30,  60,  80}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {BUG, GRASS }, // type
        .catchRate = 75 , // catch rate
        .exp = 128 , // base exp
        .items = {TINYMUSHROOM, BIG_MUSHROOM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_BUG, EGG_PLANT ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SWEET_SCENT, SNORE, HYPER_BEAM, PROTECT, GIGA_DRAIN, ENDURE, FRUSTRATION, SOLARBEAM, RETURN, DIG, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SLUDGE_BOMB, REST, ATTRACT, THIEF, FURY_CUTTER, CUT, FLASH), 
    // end
    },
    [VENONAT-1] = {
        .dexNo = VENONAT , // 048
        .stats = { 60,  55,  50,  45,  40,  55}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {BUG, POISON }, // type
        .catchRate = 190 , // catch rate
        .exp = 75 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_BUG, EGG_BUG ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, HIDDEN_POWER, SUNNY_DAY, SWEET_SCENT, SNORE, PROTECT, GIGA_DRAIN, ENDURE, FRUSTRATION, SOLARBEAM, RETURN, PSYCHIC_M, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SLUDGE_BOMB, SWIFT, REST, ATTRACT, THIEF), 
    // end
    },
    [VENOMOTH-1] = {
        .dexNo = VENOMOTH , // 049
        .stats = { 70,  65,  60,  90,  90,  75}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {BUG, POISON }, // type
        .catchRate = 75 , // catch rate
        .exp = 138 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_BUG, EGG_BUG ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, HIDDEN_POWER, SUNNY_DAY, SWEET_SCENT, SNORE, HYPER_BEAM, PROTECT, GIGA_DRAIN, ENDURE, FRUSTRATION, SOLARBEAM, RETURN, PSYCHIC_M, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SLUDGE_BOMB, SWIFT, REST, ATTRACT, THIEF, FLASH), 
    // end
    },
    [DIGLETT-1] = {
        .dexNo = DIGLETT , // 050
        .stats = { 10,  55,  25,  95,  35,  45}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {GROUND, GROUND }, // type
        .catchRate = 255 , // catch rate
        .exp = 81 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_GROUND, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, ENDURE, FRUSTRATION, EARTHQUAKE, RETURN, DIG, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SLUDGE_BOMB, REST, ATTRACT, THIEF, CUT), 
    // end
    },
    [DUGTRIO-1] = {
        .dexNo = DUGTRIO , // 051
        .stats = { 35,  80,  50, 120,  50,  70}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {GROUND, GROUND }, // type
        .catchRate = 50 , // catch rate
        .exp = 153 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_GROUND, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, PROTECT, ENDURE, FRUSTRATION, EARTHQUAKE, RETURN, DIG, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SLUDGE_BOMB, REST, ATTRACT, THIEF, CUT), 
    // end
    },
    [MEOWTH-1] = {
        .dexNo = MEOWTH , // 052
        .stats = { 40,  45,  35,  90,  40,  40}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {NORMAL, NORMAL }, // type
        .catchRate = 255 , // catch rate
        .exp = 69 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_GROUND, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, ZAP_CANNON, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SNORE, ICY_WIND, PROTECT, ENDURE, FRUSTRATION, IRON_TAIL, THUNDER, RETURN, SHADOW_BALL, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, DEFENSE_CURL, DREAM_EATER, DETECT, REST, ATTRACT, THIEF, NIGHTMARE, THUNDERBOLT), 
    // end
    },
    [PERSIAN-1] = {
        .dexNo = PERSIAN , // 053
        .stats = { 65,  70,  60, 115,  65,  65}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {NORMAL, NORMAL }, // type
        .catchRate = 90 , // catch rate
        .exp = 148 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_GROUND, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, ROAR, TOXIC, ZAP_CANNON, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, ICY_WIND, PROTECT, ENDURE, FRUSTRATION, IRON_TAIL, THUNDER, RETURN, SHADOW_BALL, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, DEFENSE_CURL, DREAM_EATER, DETECT, REST, ATTRACT, THIEF, NIGHTMARE, THUNDERBOLT), 
    // end
    },
    [PSYDUCK-1] = {
        .dexNo = PSYDUCK , // 054
        .stats = { 50,  52,  48,  55,  65,  50}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {WATER, WATER }, // type
        .catchRate = 190 , // catch rate
        .exp = 80 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_WATER_1, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, TOXIC, ROCK_SMASH, PSYCH_UP, HIDDEN_POWER, SNORE, BLIZZARD, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, IRON_TAIL, RETURN, DIG, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, SWIFT, REST, ATTRACT, SURF, STRENGTH, FLASH, WHIRLPOOL, WATERFALL, ICE_BEAM), 
    // end
    },
    [GOLDUCK-1] = {
        .dexNo = GOLDUCK , // 055
        .stats = { 80,  82,  78,  85,  95,  80}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {WATER, WATER }, // type
        .catchRate = 75 , // catch rate
        .exp = 174 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_WATER_1, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, TOXIC, ROCK_SMASH, PSYCH_UP, HIDDEN_POWER, SNORE, BLIZZARD, HYPER_BEAM, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, IRON_TAIL, RETURN, DIG, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, SWIFT, REST, ATTRACT, FURY_CUTTER, SURF, STRENGTH, FLASH, WHIRLPOOL, WATERFALL, ICE_BEAM), 
    // end
    },
    [MANKEY-1] = {
        .dexNo = MANKEY , // 056
        .stats = { 40,  80,  35,  70,  35,  45}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {FIGHTING, FIGHTING }, // type
        .catchRate = 190 , // catch rate
        .exp = 74 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_GROUND, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, TOXIC, ROCK_SMASH, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, ENDURE, FRUSTRATION, IRON_TAIL, THUNDER, RETURN, DIG, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, SWIFT, DEFENSE_CURL, THUNDERPUNCH, DETECT, REST, ATTRACT, THIEF, FIRE_PUNCH, STRENGTH, THUNDERBOLT), 
    // end
    },
    [PRIMEAPE-1] = {
        .dexNo = PRIMEAPE , // 057
        .stats = { 65, 105,  60,  95,  60,  70}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {FIGHTING, FIGHTING }, // type
        .catchRate = 75 , // catch rate
        .exp = 149 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_GROUND, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, TOXIC, ROCK_SMASH, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, PROTECT, ENDURE, FRUSTRATION, IRON_TAIL, THUNDER, RETURN, DIG, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, SWIFT, DEFENSE_CURL, THUNDERPUNCH, DETECT, REST, ATTRACT, THIEF, FIRE_PUNCH, STRENGTH, THUNDERBOLT), 
    // end
    },
    [GROWLITHE-1] = {
        .dexNo = GROWLITHE , // 058
        .stats = { 55,  70,  45,  60,  70,  50}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {FIRE, FIRE }, // type
        .catchRate = 190 , // catch rate
        .exp = 91 , // base exp
        .items = {BURNT_BERRY, BURNT_BERRY }, // items
        .gender = GENDER_F25 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_GROUND, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, ROAR, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, ENDURE, FRUSTRATION, IRON_TAIL, DRAGONBREATH, RETURN, DIG, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, FIRE_BLAST, SWIFT, REST, ATTRACT, FLAMETHROWER), 
    // end
    },
    [ARCANINE-1] = {
        .dexNo = ARCANINE , // 059
        .stats = { 90, 110,  80,  95, 100,  80}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {FIRE, FIRE }, // type
        .catchRate = 75 , // catch rate
        .exp = 213 , // base exp
        .items = {BURNT_BERRY, BURNT_BERRY }, // items
        .gender = GENDER_F25 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_GROUND, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, ROAR, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, PROTECT, ENDURE, FRUSTRATION, IRON_TAIL, DRAGONBREATH, RETURN, DIG, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, FIRE_BLAST, SWIFT, REST, ATTRACT, FLAMETHROWER), 
    // end
    },
    [POLIWAG-1] = {
        .dexNo = POLIWAG , // 060
        .stats = { 40,  50,  40,  90,  40,  40}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {WATER, WATER }, // type
        .catchRate = 255 , // catch rate
        .exp = 77 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_WATER_1, EGG_WATER_1 ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, HIDDEN_POWER, SNORE, BLIZZARD, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, RETURN, PSYCHIC_M, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, DEFENSE_CURL, REST, ATTRACT, THIEF, SURF, WHIRLPOOL, WATERFALL, ICE_BEAM), 
    // end
    },
    [POLIWHIRL-1] = {
        .dexNo = POLIWHIRL , // 061
        .stats = { 65,  65,  65,  90,  50,  50}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {WATER, WATER }, // type
        .catchRate = 120 , // catch rate
        .exp = 131 , // base exp
        .items = {NO_ITEM, KINGS_ROCK }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_WATER_1, EGG_WATER_1 ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, ROCK_SMASH, HIDDEN_POWER, SNORE, BLIZZARD, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, EARTHQUAKE, RETURN, PSYCHIC_M, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, DEFENSE_CURL, DETECT, REST, ATTRACT, THIEF, SURF, STRENGTH, WHIRLPOOL, WATERFALL, ICE_BEAM), 
    // end
    },
    [POLIWRATH-1] = {
        .dexNo = POLIWRATH , // 062
        .stats = { 90,  85,  95,  70,  70,  90}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {WATER, FIGHTING }, // type
        .catchRate = 45 , // catch rate
        .exp = 185 , // base exp
        .items = {NO_ITEM, KINGS_ROCK }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_WATER_1, EGG_WATER_1 ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, TOXIC, ROCK_SMASH, HIDDEN_POWER, SNORE, BLIZZARD, HYPER_BEAM, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, EARTHQUAKE, RETURN, PSYCHIC_M, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, DEFENSE_CURL, DETECT, REST, ATTRACT, THIEF, SURF, STRENGTH, WHIRLPOOL, WATERFALL, ICE_BEAM), 
    // end
    },
    [ABRA-1] = {
        .dexNo = ABRA , // 063
        .stats = { 25,  20,  15,  90, 105,  55}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {PSYCHIC_TYPE, PSYCHIC_TYPE }, // type
        .catchRate = 200 , // catch rate
        .exp = 73 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F25 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_HUMANSHAPE, EGG_HUMANSHAPE ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, TOXIC, ZAP_CANNON, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, RETURN, PSYCHIC_M, SHADOW_BALL, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, THUNDERPUNCH, DREAM_EATER, REST, ATTRACT, THIEF, FIRE_PUNCH, NIGHTMARE, FLASH), 
    // end
    },
    [KADABRA-1] = {
        .dexNo = KADABRA , // 064
        .stats = { 40,  35,  30, 105, 120,  70}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {PSYCHIC_TYPE, PSYCHIC_TYPE }, // type
        .catchRate = 100 , // catch rate
        .exp = 145 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F25 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_HUMANSHAPE, EGG_HUMANSHAPE ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, TOXIC, ZAP_CANNON, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, RETURN, DIG, PSYCHIC_M, SHADOW_BALL, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, THUNDERPUNCH, DREAM_EATER, REST, ATTRACT, THIEF, FIRE_PUNCH, NIGHTMARE, FLASH), 
    // end
    },
    [ALAKAZAM-1] = {
        .dexNo = ALAKAZAM , // 065
        .stats = { 55,  50,  45, 120, 135,  85}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {PSYCHIC_TYPE, PSYCHIC_TYPE }, // type
        .catchRate = 50 , // catch rate
        .exp = 186 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F25 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_HUMANSHAPE, EGG_HUMANSHAPE ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, TOXIC, ZAP_CANNON, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, RETURN, DIG, PSYCHIC_M, SHADOW_BALL, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, THUNDERPUNCH, DREAM_EATER, REST, ATTRACT, THIEF, FIRE_PUNCH, NIGHTMARE, FLASH), 
    // end
    },
    [MACHOP-1] = {
        .dexNo = MACHOP , // 066
        .stats = { 70,  80,  50,  35,  35,  35}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {FIGHTING, FIGHTING }, // type
        .catchRate = 180 , // catch rate
        .exp = 88 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F25 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_HUMANSHAPE, EGG_HUMANSHAPE ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, ENDURE, FRUSTRATION, EARTHQUAKE, RETURN, DIG, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, FIRE_BLAST, THUNDERPUNCH, DETECT, REST, ATTRACT, THIEF, FIRE_PUNCH, STRENGTH, FLAMETHROWER), 
    // end
    },
    [MACHOKE-1] = {
        .dexNo = MACHOKE , // 067
        .stats = { 80, 100,  70,  45,  50,  60}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {FIGHTING, FIGHTING }, // type
        .catchRate = 90 , // catch rate
        .exp = 146 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F25 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_HUMANSHAPE, EGG_HUMANSHAPE ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, ENDURE, FRUSTRATION, EARTHQUAKE, RETURN, DIG, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, FIRE_BLAST, THUNDERPUNCH, DETECT, REST, ATTRACT, THIEF, FIRE_PUNCH, STRENGTH, FLAMETHROWER), 
    // end
    },
    [MACHAMP-1] = {
        .dexNo = MACHAMP , // 068
        .stats = { 90, 130,  80,  55,  65,  85}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {FIGHTING, FIGHTING }, // type
        .catchRate = 45 , // catch rate
        .exp = 193 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F25 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_HUMANSHAPE, EGG_HUMANSHAPE ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, PROTECT, ENDURE, FRUSTRATION, EARTHQUAKE, RETURN, DIG, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, FIRE_BLAST, THUNDERPUNCH, DETECT, REST, ATTRACT, THIEF, FIRE_PUNCH, STRENGTH, FLAMETHROWER), 
    // end
    },
    [BELLSPROUT-1] = {
        .dexNo = BELLSPROUT , // 069
        .stats = { 50,  75,  35,  40,  70,  30}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {GRASS, POISON }, // type
        .catchRate = 255 , // catch rate
        .exp = 84 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_PLANT, EGG_PLANT ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, HIDDEN_POWER, SUNNY_DAY, SWEET_SCENT, SNORE, PROTECT, GIGA_DRAIN, ENDURE, FRUSTRATION, SOLARBEAM, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SLUDGE_BOMB, REST, ATTRACT, CUT, FLASH), 
    // end
    },
    [WEEPINBELL-1] = {
        .dexNo = WEEPINBELL , // 070
        .stats = { 65,  90,  50,  55,  85,  45}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {GRASS, POISON }, // type
        .catchRate = 120 , // catch rate
        .exp = 151 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_PLANT, EGG_PLANT ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, HIDDEN_POWER, SUNNY_DAY, SWEET_SCENT, SNORE, PROTECT, GIGA_DRAIN, ENDURE, FRUSTRATION, SOLARBEAM, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SLUDGE_BOMB, REST, ATTRACT, CUT, FLASH), 
    // end
    },
    [VICTREEBEL-1] = {
        .dexNo = VICTREEBEL , // 071
        .stats = { 80, 105,  65,  70, 100,  60}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {GRASS, POISON }, // type
        .catchRate = 45 , // catch rate
        .exp = 191 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_PLANT, EGG_PLANT ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, HIDDEN_POWER, SUNNY_DAY, SWEET_SCENT, SNORE, HYPER_BEAM, PROTECT, GIGA_DRAIN, ENDURE, FRUSTRATION, SOLARBEAM, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SLUDGE_BOMB, REST, ATTRACT, CUT, FLASH), 
    // end
    },
    [TENTACOOL-1] = {
        .dexNo = TENTACOOL , // 072
        .stats = { 40,  40,  35,  70,  50, 100}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {WATER, POISON }, // type
        .catchRate = 190 , // catch rate
        .exp = 105 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_WATER_3, EGG_WATER_3 ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, HIDDEN_POWER, SNORE, BLIZZARD, ICY_WIND, PROTECT, RAIN_DANCE, GIGA_DRAIN, ENDURE, FRUSTRATION, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SLUDGE_BOMB, REST, ATTRACT, CUT, SURF, WHIRLPOOL, ICE_BEAM), 
    // end
    },
    [TENTACRUEL-1] = {
        .dexNo = TENTACRUEL , // 073
        .stats = { 80,  70,  65, 100,  80, 120}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {WATER, POISON }, // type
        .catchRate = 60 , // catch rate
        .exp = 205 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_WATER_3, EGG_WATER_3 ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, HIDDEN_POWER, SNORE, BLIZZARD, HYPER_BEAM, ICY_WIND, PROTECT, RAIN_DANCE, GIGA_DRAIN, ENDURE, FRUSTRATION, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SLUDGE_BOMB, REST, ATTRACT, CUT, SURF, WHIRLPOOL, ICE_BEAM), 
    // end
    },
    [GEODUDE-1] = {
        .dexNo = GEODUDE , // 074
        .stats = { 40,  80, 100,  20,  30,  30}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {ROCK, GROUND }, // type
        .catchRate = 255 , // catch rate
        .exp = 86 , // base exp
        .items = {NO_ITEM, EVERSTONE }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 15 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_MINERAL, EGG_MINERAL ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, ROLLOUT, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, ENDURE, FRUSTRATION, EARTHQUAKE, RETURN, DIG, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SANDSTORM, FIRE_BLAST, DEFENSE_CURL, REST, ATTRACT, FIRE_PUNCH, STRENGTH, FLAMETHROWER), 
    // end
    },
    [GRAVELER-1] = {
        .dexNo = GRAVELER , // 075
        .stats = { 55,  95, 115,  35,  45,  45}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {ROCK, GROUND }, // type
        .catchRate = 120 , // catch rate
        .exp = 134 , // base exp
        .items = {NO_ITEM, EVERSTONE }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 15 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_MINERAL, EGG_MINERAL ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, ROLLOUT, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, ENDURE, FRUSTRATION, EARTHQUAKE, RETURN, DIG, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SANDSTORM, FIRE_BLAST, DEFENSE_CURL, REST, ATTRACT, FIRE_PUNCH, STRENGTH, FLAMETHROWER), 
    // end
    },
    [GOLEM-1] = {
        .dexNo = GOLEM , // 076
        .stats = { 80, 110, 130,  45,  55,  65}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {ROCK, GROUND }, // type
        .catchRate = 45 , // catch rate
        .exp = 177 , // base exp
        .items = {NO_ITEM, EVERSTONE }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 15 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_MINERAL, EGG_MINERAL ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, ROLLOUT, ROAR, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, PROTECT, ENDURE, FRUSTRATION, EARTHQUAKE, RETURN, DIG, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SANDSTORM, FIRE_BLAST, DEFENSE_CURL, REST, ATTRACT, FIRE_PUNCH, FURY_CUTTER, STRENGTH, FLAMETHROWER), 
    // end
    },
    [PONYTA-1] = {
        .dexNo = PONYTA , // 077
        .stats = { 50,  85,  55,  90,  65,  65}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {FIRE, FIRE }, // type
        .catchRate = 190 , // catch rate
        .exp = 152 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_GROUND, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, ENDURE, FRUSTRATION, IRON_TAIL, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, FIRE_BLAST, SWIFT, REST, ATTRACT, FLAMETHROWER), 
    // end
    },
    [RAPIDASH-1] = {
        .dexNo = RAPIDASH , // 078
        .stats = { 65, 100,  70, 105,  80,  80}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {FIRE, FIRE }, // type
        .catchRate = 60 , // catch rate
        .exp = 192 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_GROUND, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, PROTECT, ENDURE, FRUSTRATION, IRON_TAIL, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, FIRE_BLAST, SWIFT, REST, ATTRACT, FLAMETHROWER), 
    // end
    },
    [SLOWPOKE-1] = {
        .dexNo = SLOWPOKE , // 079
        .stats = { 90,  65,  65,  15,  40,  40}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {WATER, PSYCHIC_TYPE }, // type
        .catchRate = 190 , // catch rate
        .exp = 99 , // base exp
        .items = {NO_ITEM, KINGS_ROCK }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_MONSTER, EGG_WATER_1 ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, ZAP_CANNON, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SNORE, BLIZZARD, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, IRON_TAIL, EARTHQUAKE, RETURN, DIG, PSYCHIC_M, SHADOW_BALL, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, FIRE_BLAST, SWIFT, DREAM_EATER, REST, ATTRACT, NIGHTMARE, SURF, STRENGTH, FLASH, FLAMETHROWER, ICE_BEAM), 
    // end
    },
    [SLOWBRO-1] = {
        .dexNo = SLOWBRO , // 080
        .stats = { 95,  75, 110,  30, 100,  80}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {WATER, PSYCHIC_TYPE }, // type
        .catchRate = 75 , // catch rate
        .exp = 164 , // base exp
        .items = {NO_ITEM, KINGS_ROCK }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_MONSTER, EGG_WATER_1 ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, TOXIC, ZAP_CANNON, ROCK_SMASH, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SNORE, BLIZZARD, HYPER_BEAM, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, IRON_TAIL, EARTHQUAKE, RETURN, DIG, PSYCHIC_M, SHADOW_BALL, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, FIRE_BLAST, SWIFT, DREAM_EATER, REST, ATTRACT, FURY_CUTTER, NIGHTMARE, SURF, STRENGTH, FLASH, FLAMETHROWER, ICE_BEAM), 
    // end
    },
    [MAGNEMITE-1] = {
        .dexNo = MAGNEMITE , // 081
        .stats = { 25,  35,  70,  45,  95,  55}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {ELECTRIC, STEEL }, // type
        .catchRate = 190 , // catch rate
        .exp = 89 , // base exp
        .items = {NO_ITEM, METAL_COAT }, // items
        .gender = GENDER_UNKNOWN , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_MINERAL, EGG_MINERAL ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, ROLLOUT, TOXIC, ZAP_CANNON, HIDDEN_POWER, SNORE, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, THUNDER, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, REST, FLASH, THUNDERBOLT), 
    // end
    },
    [MAGNETON-1] = {
        .dexNo = MAGNETON , // 082
        .stats = { 50,  60,  95,  70, 120,  70}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {ELECTRIC, STEEL }, // type
        .catchRate = 60 , // catch rate
        .exp = 161 , // base exp
        .items = {NO_ITEM, METAL_COAT }, // items
        .gender = GENDER_UNKNOWN , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_MINERAL, EGG_MINERAL ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, ROLLOUT, TOXIC, ZAP_CANNON, HIDDEN_POWER, SNORE, HYPER_BEAM, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, THUNDER, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, REST, FLASH, THUNDERBOLT), 
    // end
    },
    [FARFETCH_D-1] = {
        .dexNo = FARFETCH_D , // 083
        .stats = { 52,  65,  55,  60,  58,  62}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {NORMAL, FLYING }, // type
        .catchRate = 45 , // catch rate
        .exp = 94 , // base exp
        .items = {NO_ITEM, STICK }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_FLYING, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, ENDURE, FRUSTRATION, IRON_TAIL, RETURN, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, DETECT, REST, ATTRACT, THIEF, STEEL_WING, CUT, FLY), 
    // end
    },
    [DODUO-1] = {
        .dexNo = DODUO , // 084
        .stats = { 35,  85,  45,  75,  35,  35}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {NORMAL, FLYING }, // type
        .catchRate = 190 , // catch rate
        .exp = 96 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_FLYING, EGG_FLYING ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, ENDURE, FRUSTRATION, RETURN, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, REST, ATTRACT, THIEF, STEEL_WING, FLY), 
    // end
    },
    [DODRIO-1] = {
        .dexNo = DODRIO , // 085
        .stats = { 60, 110,  70, 100,  60,  60}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {NORMAL, FLYING }, // type
        .catchRate = 45 , // catch rate
        .exp = 158 , // base exp
        .items = {NO_ITEM, SHARP_BEAK }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_FLYING, EGG_FLYING ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, PROTECT, ENDURE, FRUSTRATION, RETURN, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, REST, ATTRACT, THIEF, STEEL_WING, FLY), 
    // end
    },
    [SEEL-1] = {
        .dexNo = SEEL , // 086
        .stats = { 65,  45,  55,  45,  45,  70}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {WATER, WATER }, // type
        .catchRate = 190 , // catch rate
        .exp = 100 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_WATER_1, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, HIDDEN_POWER, SNORE, BLIZZARD, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, REST, ATTRACT, SURF, WHIRLPOOL, WATERFALL, ICE_BEAM), 
    // end
    },
    [DEWGONG-1] = {
        .dexNo = DEWGONG , // 087
        .stats = { 90,  70,  80,  70,  70,  95}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {WATER, ICE }, // type
        .catchRate = 75 , // catch rate
        .exp = 176 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_WATER_1, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, HIDDEN_POWER, SNORE, BLIZZARD, HYPER_BEAM, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, REST, ATTRACT, SURF, WHIRLPOOL, WATERFALL, ICE_BEAM), 
    // end
    },
    [GRIMER-1] = {
        .dexNo = GRIMER , // 088
        .stats = { 80,  80,  50,  25,  40,  50}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {POISON, POISON }, // type
        .catchRate = 190 , // catch rate
        .exp = 90 , // base exp
        .items = {NO_ITEM, NUGGET }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_INDETERMINATE, EGG_INDETERMINATE ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, CURSE, TOXIC, ZAP_CANNON, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, GIGA_DRAIN, ENDURE, FRUSTRATION, THUNDER, RETURN, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, SLUDGE_BOMB, FIRE_BLAST, THUNDERPUNCH, REST, ATTRACT, THIEF, FIRE_PUNCH, FLAMETHROWER, THUNDERBOLT), 
    // end
    },
    [MUK-1] = {
        .dexNo = MUK , // 089
        .stats = {105, 105,  75,  50,  65, 100}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {POISON, POISON }, // type
        .catchRate = 75 , // catch rate
        .exp = 157 , // base exp
        .items = {NO_ITEM, NUGGET }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_INDETERMINATE, EGG_INDETERMINATE ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, CURSE, TOXIC, ZAP_CANNON, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, PROTECT, GIGA_DRAIN, ENDURE, FRUSTRATION, THUNDER, RETURN, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, SLUDGE_BOMB, FIRE_BLAST, THUNDERPUNCH, REST, ATTRACT, THIEF, FIRE_PUNCH, FLAMETHROWER, THUNDERBOLT), 
    // end
    },
    [SHELLDER-1] = {
        .dexNo = SHELLDER , // 090
        .stats = { 30,  65, 100,  40,  45,  25}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {WATER, WATER }, // type
        .catchRate = 190 , // catch rate
        .exp = 97 , // base exp
        .items = {PEARL, BIG_PEARL }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_WATER_3, EGG_WATER_3 ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, HIDDEN_POWER, SNORE, BLIZZARD, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, REST, ATTRACT, SURF, WHIRLPOOL, ICE_BEAM), 
    // end
    },
    [CLOYSTER-1] = {
        .dexNo = CLOYSTER , // 091
        .stats = { 50,  95, 180,  70,  85,  45}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {WATER, ICE }, // type
        .catchRate = 60 , // catch rate
        .exp = 203 , // base exp
        .items = {PEARL, BIG_PEARL }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_WATER_3, EGG_WATER_3 ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, HIDDEN_POWER, SNORE, BLIZZARD, HYPER_BEAM, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, REST, ATTRACT, SURF, WHIRLPOOL, ICE_BEAM), 
    // end
    },
    [GASTLY-1] = {
        .dexNo = GASTLY , // 092
        .stats = { 30,  35,  30,  80, 100,  35}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {GHOST, POISON }, // type
        .catchRate = 190 , // catch rate
        .exp = 95 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_INDETERMINATE, EGG_INDETERMINATE ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, ZAP_CANNON, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, RAIN_DANCE, GIGA_DRAIN, ENDURE, FRUSTRATION, THUNDER, RETURN, PSYCHIC_M, SHADOW_BALL, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, DREAM_EATER, REST, ATTRACT, THIEF, NIGHTMARE, THUNDERBOLT), 
    // end
    },
    [HAUNTER-1] = {
        .dexNo = HAUNTER , // 093
        .stats = { 45,  50,  45,  95, 115,  55}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {GHOST, POISON }, // type
        .catchRate = 90 , // catch rate
        .exp = 126 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_INDETERMINATE, EGG_INDETERMINATE ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, ZAP_CANNON, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, RAIN_DANCE, GIGA_DRAIN, ENDURE, FRUSTRATION, THUNDER, RETURN, PSYCHIC_M, SHADOW_BALL, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, DREAM_EATER, REST, ATTRACT, THIEF, NIGHTMARE, THUNDERBOLT), 
    // end
    },
    [GENGAR-1] = {
        .dexNo = GENGAR , // 094
        .stats = { 60,  65,  60, 110, 130,  75}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {GHOST, POISON }, // type
        .catchRate = 45 , // catch rate
        .exp = 190 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_INDETERMINATE, EGG_INDETERMINATE ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, TOXIC, ZAP_CANNON, ROCK_SMASH, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, PROTECT, RAIN_DANCE, GIGA_DRAIN, ENDURE, FRUSTRATION, THUNDER, RETURN, PSYCHIC_M, SHADOW_BALL, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, THUNDERPUNCH, DREAM_EATER, REST, ATTRACT, THIEF, FIRE_PUNCH, NIGHTMARE, STRENGTH, THUNDERBOLT), 
    // end
    },
    [ONIX-1] = {
        .dexNo = ONIX , // 095
        .stats = { 35,  45, 160,  70,  30,  45}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {ROCK, GROUND }, // type
        .catchRate = 45 , // catch rate
        .exp = 108 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 25 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_MINERAL, EGG_MINERAL ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, ROAR, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, ENDURE, FRUSTRATION, IRON_TAIL, EARTHQUAKE, RETURN, DIG, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SANDSTORM, REST, ATTRACT, STRENGTH), 
    // end
    },
    [DROWZEE-1] = {
        .dexNo = DROWZEE , // 096
        .stats = { 60,  48,  45,  42,  43,  90}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {PSYCHIC_TYPE, PSYCHIC_TYPE }, // type
        .catchRate = 190 , // catch rate
        .exp = 102 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_HUMANSHAPE, EGG_HUMANSHAPE ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, TOXIC, ZAP_CANNON, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, RETURN, PSYCHIC_M, SHADOW_BALL, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, THUNDERPUNCH, DREAM_EATER, REST, ATTRACT, FIRE_PUNCH, NIGHTMARE, FLASH), 
    // end
    },
    [HYPNO-1] = {
        .dexNo = HYPNO , // 097
        .stats = { 85,  73,  70,  67,  73, 115}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {PSYCHIC_TYPE, PSYCHIC_TYPE }, // type
        .catchRate = 75 , // catch rate
        .exp = 165 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_HUMANSHAPE, EGG_HUMANSHAPE ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, TOXIC, ZAP_CANNON, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, RETURN, PSYCHIC_M, SHADOW_BALL, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, THUNDERPUNCH, DREAM_EATER, REST, ATTRACT, FIRE_PUNCH, NIGHTMARE, FLASH), 
    // end
    },
    [KRABBY-1] = {
        .dexNo = KRABBY , // 098
        .stats = { 30, 105,  90,  50,  25,  25}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {WATER, WATER }, // type
        .catchRate = 225 , // catch rate
        .exp = 115 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_WATER_3, EGG_WATER_3 ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, ROCK_SMASH, HIDDEN_POWER, SNORE, BLIZZARD, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, RETURN, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, REST, ATTRACT, THIEF, FURY_CUTTER, CUT, SURF, STRENGTH, WHIRLPOOL, ICE_BEAM), 
    // end
    },
    [KINGLER-1] = {
        .dexNo = KINGLER , // 099
        .stats = { 55, 130, 115,  75,  50,  50}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {WATER, WATER }, // type
        .catchRate = 60 , // catch rate
        .exp = 206 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_WATER_3, EGG_WATER_3 ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, ROCK_SMASH, HIDDEN_POWER, SNORE, BLIZZARD, HYPER_BEAM, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, RETURN, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, REST, ATTRACT, THIEF, FURY_CUTTER, CUT, SURF, STRENGTH, WHIRLPOOL, ICE_BEAM), 
    // end
    },
    [VOLTORB-1] = {
        .dexNo = VOLTORB , // 100
        .stats = { 40,  30,  50, 100,  55,  55}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {ELECTRIC, ELECTRIC }, // type
        .catchRate = 190 , // catch rate
        .exp = 103 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_UNKNOWN , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_MINERAL, EGG_MINERAL ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, ROLLOUT, TOXIC, ZAP_CANNON, HIDDEN_POWER, SNORE, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, THUNDER, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, REST, FLASH, THUNDERBOLT), 
    // end
    },
    [ELECTRODE-1] = {
        .dexNo = ELECTRODE , // 101
        .stats = { 60,  50,  70, 140,  80,  80}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {ELECTRIC, ELECTRIC }, // type
        .catchRate = 60 , // catch rate
        .exp = 150 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_UNKNOWN , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_MINERAL, EGG_MINERAL ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, ROLLOUT, TOXIC, ZAP_CANNON, HIDDEN_POWER, SNORE, HYPER_BEAM, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, THUNDER, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, REST, FLASH, THUNDERBOLT), 
    // end
    },
    [EXEGGCUTE-1] = {
        .dexNo = EXEGGCUTE , // 102
        .stats = { 60,  40,  80,  40,  60,  45}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {GRASS, PSYCHIC_TYPE }, // type
        .catchRate = 90 , // catch rate
        .exp = 98 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_PLANT, EGG_PLANT ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, ROLLOUT, TOXIC, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, GIGA_DRAIN, ENDURE, FRUSTRATION, SOLARBEAM, RETURN, PSYCHIC_M, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SLUDGE_BOMB, DREAM_EATER, REST, ATTRACT, THIEF, NIGHTMARE, STRENGTH, FLASH), 
    // end
    },
    [EXEGGUTOR-1] = {
        .dexNo = EXEGGUTOR , // 103
        .stats = { 95,  95,  85,  55, 125,  65}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {GRASS, PSYCHIC_TYPE }, // type
        .catchRate = 45 , // catch rate
        .exp = 212 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_PLANT, EGG_PLANT ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, ROLLOUT, TOXIC, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, PROTECT, GIGA_DRAIN, ENDURE, FRUSTRATION, SOLARBEAM, RETURN, PSYCHIC_M, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SLUDGE_BOMB, DREAM_EATER, REST, ATTRACT, THIEF, NIGHTMARE, STRENGTH, FLASH), 
    // end
    },
    [CUBONE-1] = {
        .dexNo = CUBONE , // 104
        .stats = { 50,  50,  95,  35,  40,  50}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {GROUND, GROUND }, // type
        .catchRate = 190 , // catch rate
        .exp = 87 , // base exp
        .items = {NO_ITEM, THICK_CLUB }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_MONSTER, EGG_MONSTER ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, BLIZZARD, ICY_WIND, PROTECT, ENDURE, FRUSTRATION, IRON_TAIL, EARTHQUAKE, RETURN, DIG, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SANDSTORM, FIRE_BLAST, THUNDERPUNCH, DETECT, REST, ATTRACT, THIEF, FIRE_PUNCH, STRENGTH, FLAMETHROWER, ICE_BEAM), 
    // end
    },
    [MAROWAK-1] = {
        .dexNo = MAROWAK , // 105
        .stats = { 60,  80, 110,  45,  50,  80}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {GROUND, GROUND }, // type
        .catchRate = 75 , // catch rate
        .exp = 124 , // base exp
        .items = {NO_ITEM, THICK_CLUB }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_MONSTER, EGG_MONSTER ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, BLIZZARD, HYPER_BEAM, ICY_WIND, PROTECT, ENDURE, FRUSTRATION, IRON_TAIL, EARTHQUAKE, RETURN, DIG, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SANDSTORM, FIRE_BLAST, THUNDERPUNCH, DETECT, REST, ATTRACT, THIEF, FIRE_PUNCH, STRENGTH, FLAMETHROWER, ICE_BEAM), 
    // end
    },
    [HITMONLEE-1] = {
        .dexNo = HITMONLEE , // 106
        .stats = { 50, 120,  53,  87,  35, 110}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {FIGHTING, FIGHTING }, // type
        .catchRate = 45 , // catch rate
        .exp = 139 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F0 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 25 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_HUMANSHAPE, EGG_HUMANSHAPE ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, ENDURE, FRUSTRATION, RETURN, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, DETECT, REST, ATTRACT, THIEF, STRENGTH), 
    // end
    },
    [HITMONCHAN-1] = {
        .dexNo = HITMONCHAN , // 107
        .stats = { 50, 105,  79,  76,  35, 110}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {FIGHTING, FIGHTING }, // type
        .catchRate = 45 , // catch rate
        .exp = 140 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F0 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 25 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_HUMANSHAPE, EGG_HUMANSHAPE ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, ENDURE, FRUSTRATION, RETURN, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, SWIFT, THUNDERPUNCH, DETECT, REST, ATTRACT, THIEF, FIRE_PUNCH, STRENGTH), 
    // end
    },
    [LICKITUNG-1] = {
        .dexNo = LICKITUNG , // 108
        .stats = { 90,  55,  75,  30,  60,  75}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {NORMAL, NORMAL }, // type
        .catchRate = 45 , // catch rate
        .exp = 127 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_MONSTER, EGG_MONSTER ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, ROLLOUT, TOXIC, ROCK_SMASH, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SNORE, BLIZZARD, HYPER_BEAM, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, IRON_TAIL, THUNDER, EARTHQUAKE, RETURN, SHADOW_BALL, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, SANDSTORM, FIRE_BLAST, DEFENSE_CURL, THUNDERPUNCH, DREAM_EATER, REST, ATTRACT, THIEF, FIRE_PUNCH, NIGHTMARE, CUT, SURF, STRENGTH, FLAMETHROWER, THUNDERBOLT, ICE_BEAM), 
    // end
    },
    [KOFFING-1] = {
        .dexNo = KOFFING , // 109
        .stats = { 40,  65,  95,  35,  60,  45}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {POISON, POISON }, // type
        .catchRate = 190 , // catch rate
        .exp = 114 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_INDETERMINATE, EGG_INDETERMINATE ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, ROLLOUT, TOXIC, ZAP_CANNON, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, ENDURE, FRUSTRATION, THUNDER, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SLUDGE_BOMB, FIRE_BLAST, REST, ATTRACT, THIEF, FLAMETHROWER, THUNDERBOLT), 
    // end
    },
    [WEEZING-1] = {
        .dexNo = WEEZING , // 110
        .stats = { 65,  90, 120,  60,  85,  70}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {POISON, POISON }, // type
        .catchRate = 60 , // catch rate
        .exp = 173 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_INDETERMINATE, EGG_INDETERMINATE ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, ROLLOUT, TOXIC, ZAP_CANNON, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, PROTECT, ENDURE, FRUSTRATION, THUNDER, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SLUDGE_BOMB, FIRE_BLAST, REST, ATTRACT, THIEF, FLAMETHROWER, THUNDERBOLT), 
    // end
    },
    [RHYHORN-1] = {
        .dexNo = RHYHORN , // 111
        .stats = { 80,  85,  95,  25,  30,  30}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {GROUND, ROCK }, // type
        .catchRate = 120 , // catch rate
        .exp = 135 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_MONSTER, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, ROLLOUT, ROAR, TOXIC, ZAP_CANNON, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, BLIZZARD, ICY_WIND, PROTECT, ENDURE, FRUSTRATION, IRON_TAIL, THUNDER, EARTHQUAKE, RETURN, DIG, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SANDSTORM, FIRE_BLAST, REST, ATTRACT, STRENGTH, FLAMETHROWER, THUNDERBOLT, ICE_BEAM), 
    // end
    },
    [RHYDON-1] = {
        .dexNo = RHYDON , // 112
        .stats = {105, 130, 120,  40,  45,  45}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {GROUND, ROCK }, // type
        .catchRate = 60 , // catch rate
        .exp = 204 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_MONSTER, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, ROLLOUT, ROAR, TOXIC, ZAP_CANNON, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, BLIZZARD, HYPER_BEAM, ICY_WIND, PROTECT, ENDURE, FRUSTRATION, IRON_TAIL, THUNDER, EARTHQUAKE, RETURN, DIG, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SANDSTORM, FIRE_BLAST, THUNDERPUNCH, REST, ATTRACT, FIRE_PUNCH, FURY_CUTTER, SURF, STRENGTH, FLAMETHROWER, THUNDERBOLT, ICE_BEAM), 
    // end
    },
    [CHANSEY-1] = {
        .dexNo = CHANSEY , // 113
        .stats = {250,  05,  05,  50,  35, 105}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {NORMAL, NORMAL }, // type
        .catchRate = 30 , // catch rate
        .exp = 255 , // base exp
        .items = {NO_ITEM, LUCKY_EGG }, // items
        .gender = GENDER_F100 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 40 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_FAIRY, EGG_FAIRY ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, ROLLOUT, TOXIC, ZAP_CANNON, ROCK_SMASH, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SNORE, BLIZZARD, HYPER_BEAM, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, SOLARBEAM, IRON_TAIL, THUNDER, RETURN, PSYCHIC_M, SHADOW_BALL, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SANDSTORM, FIRE_BLAST, DEFENSE_CURL, DREAM_EATER, REST, ATTRACT, STRENGTH, FLASH, FLAMETHROWER, THUNDERBOLT, ICE_BEAM), 
    // end
    },
    [TANGELA-1] = {
        .dexNo = TANGELA , // 114
        .stats = { 65,  55, 115,  60, 100,  40}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {GRASS, GRASS }, // type
        .catchRate = 45 , // catch rate
        .exp = 166 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_PLANT, EGG_PLANT ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SWEET_SCENT, SNORE, HYPER_BEAM, PROTECT, GIGA_DRAIN, ENDURE, FRUSTRATION, SOLARBEAM, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SLUDGE_BOMB, REST, ATTRACT, THIEF, CUT, FLASH), 
    // end
    },
    [KANGASKHAN-1] = {
        .dexNo = KANGASKHAN , // 115
        .stats = {105,  95,  80,  90,  40,  80}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {NORMAL, NORMAL }, // type
        .catchRate = 45 , // catch rate
        .exp = 175 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F100 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_MONSTER, EGG_MONSTER ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, ROAR, TOXIC, ZAP_CANNON, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, BLIZZARD, HYPER_BEAM, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, IRON_TAIL, THUNDER, EARTHQUAKE, RETURN, SHADOW_BALL, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, SANDSTORM, FIRE_BLAST, THUNDERPUNCH, REST, ATTRACT, FIRE_PUNCH, FURY_CUTTER, SURF, STRENGTH, FLAMETHROWER, THUNDERBOLT, ICE_BEAM), 
    // end
    },
    [HORSEA-1] = {
        .dexNo = HORSEA , // 116
        .stats = { 30,  40,  70,  60,  70,  25}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {WATER, WATER }, // type
        .catchRate = 225 , // catch rate
        .exp = 83 , // base exp
        .items = {NO_ITEM, DRAGON_SCALE }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_WATER_1, EGG_DRAGON ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, HIDDEN_POWER, SNORE, BLIZZARD, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, DRAGONBREATH, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, REST, ATTRACT, SURF, WHIRLPOOL, WATERFALL, ICE_BEAM), 
    // end
    },
    [SEADRA-1] = {
        .dexNo = SEADRA , // 117
        .stats = { 55,  65,  95,  85,  95,  45}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {WATER, WATER }, // type
        .catchRate = 75 , // catch rate
        .exp = 155 , // base exp
        .items = {NO_ITEM, DRAGON_SCALE }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_WATER_1, EGG_DRAGON ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, HIDDEN_POWER, SNORE, BLIZZARD, HYPER_BEAM, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, DRAGONBREATH, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, REST, ATTRACT, SURF, WHIRLPOOL, WATERFALL, ICE_BEAM), 
    // end
    },
    [GOLDEEN-1] = {
        .dexNo = GOLDEEN , // 118
        .stats = { 45,  67,  60,  63,  35,  50}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {WATER, WATER }, // type
        .catchRate = 225 , // catch rate
        .exp = 111 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_WATER_2, EGG_WATER_2 ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, HIDDEN_POWER, SNORE, BLIZZARD, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, REST, ATTRACT, SURF, WATERFALL, ICE_BEAM), 
    // end
    },
    [SEAKING-1] = {
        .dexNo = SEAKING , // 119
        .stats = { 80,  92,  65,  68,  65,  80}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {WATER, WATER }, // type
        .catchRate = 60 , // catch rate
        .exp = 170 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_WATER_2, EGG_WATER_2 ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, HIDDEN_POWER, SNORE, BLIZZARD, HYPER_BEAM, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, REST, ATTRACT, SURF, WATERFALL, ICE_BEAM), 
    // end
    },
    [STARYU-1] = {
        .dexNo = STARYU , // 120
        .stats = { 30,  45,  55,  85,  70,  55}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {WATER, WATER }, // type
        .catchRate = 225 , // catch rate
        .exp = 106 , // base exp
        .items = {STARDUST, STAR_PIECE }, // items
        .gender = GENDER_UNKNOWN , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_WATER_3, EGG_WATER_3 ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, ZAP_CANNON, PSYCH_UP, HIDDEN_POWER, SNORE, BLIZZARD, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, THUNDER, RETURN, PSYCHIC_M, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, REST, ATTRACT, SURF, FLASH, WHIRLPOOL, WATERFALL, THUNDERBOLT, ICE_BEAM), 
    // end
    },
    [STARMIE-1] = {
        .dexNo = STARMIE , // 121
        .stats = { 60,  75,  85, 115, 100,  85}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {WATER, PSYCHIC_TYPE }, // type
        .catchRate = 60 , // catch rate
        .exp = 207 , // base exp
        .items = {STARDUST, STAR_PIECE }, // items
        .gender = GENDER_UNKNOWN , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_WATER_3, EGG_WATER_3 ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, ZAP_CANNON, PSYCH_UP, HIDDEN_POWER, SNORE, BLIZZARD, HYPER_BEAM, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, THUNDER, RETURN, PSYCHIC_M, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, DREAM_EATER, REST, ATTRACT, NIGHTMARE, SURF, FLASH, WHIRLPOOL, WATERFALL, THUNDERBOLT, ICE_BEAM), 
    // end
    },
    [MR__MIME-1] = {
        .dexNo = MR__MIME , // 122
        .stats = { 40,  45,  65,  90, 100, 120}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {PSYCHIC_TYPE, PSYCHIC_TYPE }, // type
        .catchRate = 45 , // catch rate
        .exp = 136 , // base exp
        .items = {NO_ITEM, MYSTERYBERRY }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 25 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_HUMANSHAPE, EGG_HUMANSHAPE ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, TOXIC, ZAP_CANNON, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, PROTECT, ENDURE, FRUSTRATION, SOLARBEAM, THUNDER, RETURN, PSYCHIC_M, SHADOW_BALL, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, THUNDERPUNCH, DREAM_EATER, REST, ATTRACT, THIEF, FIRE_PUNCH, NIGHTMARE, FLASH, THUNDERBOLT), 
    // end
    },
    [SCYTHER-1] = {
        .dexNo = SCYTHER , // 123
        .stats = { 70, 110,  80, 105,  55,  80}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {BUG, FLYING }, // type
        .catchRate = 45 , // catch rate
        .exp = 187 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 25 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_BUG, EGG_BUG ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, PROTECT, ENDURE, FRUSTRATION, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, DETECT, REST, ATTRACT, THIEF, STEEL_WING, FURY_CUTTER, CUT), 
    // end
    },
    [JYNX-1] = {
        .dexNo = JYNX , // 124
        .stats = { 65,  50,  35,  95, 115,  95}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {ICE, PSYCHIC_TYPE }, // type
        .catchRate = 45 , // catch rate
        .exp = 137 , // base exp
        .items = {ICE_BERRY, ICE_BERRY }, // items
        .gender = GENDER_F100 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 25 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_HUMANSHAPE, EGG_HUMANSHAPE ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, TOXIC, PSYCH_UP, HIDDEN_POWER, SWEET_SCENT, SNORE, BLIZZARD, HYPER_BEAM, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, RETURN, PSYCHIC_M, SHADOW_BALL, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, DREAM_EATER, REST, ATTRACT, THIEF, NIGHTMARE, ICE_BEAM), 
    // end
    },
    [ELECTABUZZ-1] = {
        .dexNo = ELECTABUZZ , // 125
        .stats = { 65,  83,  57, 105,  95,  85}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {ELECTRIC, ELECTRIC }, // type
        .catchRate = 45 , // catch rate
        .exp = 156 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F25 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 25 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_HUMANSHAPE, EGG_HUMANSHAPE ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, TOXIC, ZAP_CANNON, ROCK_SMASH, HIDDEN_POWER, SNORE, HYPER_BEAM, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, IRON_TAIL, THUNDER, RETURN, PSYCHIC_M, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, SWIFT, THUNDERPUNCH, DETECT, REST, ATTRACT, THIEF, FIRE_PUNCH, STRENGTH, FLASH, THUNDERBOLT), 
    // end
    },
    [MAGMAR-1] = {
        .dexNo = MAGMAR , // 126
        .stats = { 65,  95,  57,  93, 100,  85}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {FIRE, FIRE }, // type
        .catchRate = 45 , // catch rate
        .exp = 167 , // base exp
        .items = {BURNT_BERRY, BURNT_BERRY }, // items
        .gender = GENDER_F25 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 25 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_HUMANSHAPE, EGG_HUMANSHAPE ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, PROTECT, ENDURE, FRUSTRATION, IRON_TAIL, RETURN, PSYCHIC_M, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, FIRE_BLAST, THUNDERPUNCH, DETECT, REST, ATTRACT, THIEF, FIRE_PUNCH, STRENGTH, FLAMETHROWER), 
    // end
    },
    [PINSIR-1] = {
        .dexNo = PINSIR , // 127
        .stats = { 65, 125, 100,  85,  55,  70}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {BUG, BUG }, // type
        .catchRate = 45 , // catch rate
        .exp = 200 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 25 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_BUG, EGG_BUG ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, PROTECT, ENDURE, FRUSTRATION, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, REST, ATTRACT, THIEF, FURY_CUTTER, CUT, STRENGTH), 
    // end
    },
    [TAUROS-1] = {
        .dexNo = TAUROS , // 128
        .stats = { 75, 100,  95, 110,  40,  70}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {NORMAL, NORMAL }, // type
        .catchRate = 45 , // catch rate
        .exp = 211 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F0 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_GROUND, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, ZAP_CANNON, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, BLIZZARD, HYPER_BEAM, ICY_WIND, PROTECT, ENDURE, FRUSTRATION, IRON_TAIL, THUNDER, EARTHQUAKE, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, FIRE_BLAST, REST, ATTRACT, SURF, STRENGTH, FLAMETHROWER, THUNDERBOLT, ICE_BEAM), 
    // end
    },
    [MAGIKARP-1] = {
        .dexNo = MAGIKARP , // 129
        .stats = { 20,  10,  55,  80,  15,  20}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {WATER, WATER }, // type
        .catchRate = 255 , // catch rate
        .exp = 20 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 5 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_WATER_2, EGG_DRAGON ), // egg groups
    // tm/hm learnset
        .TMHM = { NULL },
    // end
    },
    [GYARADOS-1] = {
        .dexNo = GYARADOS , // 130
        .stats = { 95, 125,  79,  81,  60, 100}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {WATER, FLYING }, // type
        .catchRate = 45 , // catch rate
        .exp = 214 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 5 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_WATER_2, EGG_DRAGON ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, ROAR, TOXIC, ZAP_CANNON, ROCK_SMASH, HIDDEN_POWER, SNORE, BLIZZARD, HYPER_BEAM, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, DRAGONBREATH, THUNDER, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SANDSTORM, FIRE_BLAST, REST, ATTRACT, SURF, STRENGTH, WHIRLPOOL, WATERFALL, FLAMETHROWER, THUNDERBOLT, ICE_BEAM), 
    // end
    },
    [LAPRAS-1] = {
        .dexNo = LAPRAS , // 131
        .stats = {130,  85,  80,  60,  85,  95}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {WATER, ICE }, // type
        .catchRate = 45 , // catch rate
        .exp = 219 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 40 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_MONSTER, EGG_WATER_1 ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, ZAP_CANNON, ROCK_SMASH, HIDDEN_POWER, SNORE, BLIZZARD, HYPER_BEAM, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, IRON_TAIL, DRAGONBREATH, THUNDER, RETURN, PSYCHIC_M, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, DREAM_EATER, REST, ATTRACT, NIGHTMARE, SURF, STRENGTH, WHIRLPOOL, THUNDERBOLT, ICE_BEAM), 
    // end
    },
    [DITTO-1] = {
        .dexNo = DITTO , // 132
        .stats = { 48,  48,  48,  48,  48,  48}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {NORMAL, NORMAL }, // type
        .catchRate = 35 , // catch rate
        .exp = 61 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_UNKNOWN , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_DITTO, EGG_DITTO ), // egg groups
    // tm/hm learnset
        .TMHM = { NULL },
    // end
    },
    [EEVEE-1] = {
        .dexNo = EEVEE , // 133
        .stats = { 55,  55,  50,  55,  45,  65}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {NORMAL, NORMAL }, // type
        .catchRate = 45 , // catch rate
        .exp = 92 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F12_5 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 35 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_GROUND, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, IRON_TAIL, RETURN, SHADOW_BALL, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, DETECT, REST, ATTRACT), 
    // end
    },
    [VAPOREON-1] = {
        .dexNo = VAPOREON , // 134
        .stats = {130,  65,  60,  65, 110,  95}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {WATER, WATER }, // type
        .catchRate = 45 , // catch rate
        .exp = 196 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F12_5 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 35 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_GROUND, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, ROAR, TOXIC, HIDDEN_POWER, SUNNY_DAY, SNORE, BLIZZARD, HYPER_BEAM, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, IRON_TAIL, RETURN, SHADOW_BALL, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, DETECT, REST, ATTRACT, SURF, WHIRLPOOL, WATERFALL, ICE_BEAM), 
    // end
    },
    [JOLTEON-1] = {
        .dexNo = JOLTEON , // 135
        .stats = { 65,  65,  60, 130, 110,  95}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {ELECTRIC, ELECTRIC }, // type
        .catchRate = 45 , // catch rate
        .exp = 197 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F12_5 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 35 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_GROUND, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, ROAR, TOXIC, ZAP_CANNON, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, IRON_TAIL, THUNDER, RETURN, SHADOW_BALL, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, DETECT, REST, ATTRACT, FLASH, THUNDERBOLT), 
    // end
    },
    [FLAREON-1] = {
        .dexNo = FLAREON , // 136
        .stats = { 65, 130,  60,  65,  95, 110}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {FIRE, FIRE }, // type
        .catchRate = 45 , // catch rate
        .exp = 198 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F12_5 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 35 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_GROUND, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, ROAR, TOXIC, ZAP_CANNON, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, IRON_TAIL, RETURN, SHADOW_BALL, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, FIRE_BLAST, SWIFT, DETECT, REST, ATTRACT, FLAMETHROWER), 
    // end
    },
    [PORYGON-1] = {
        .dexNo = PORYGON , // 137
        .stats = { 65,  60,  70,  40,  85,  75}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {NORMAL, NORMAL }, // type
        .catchRate = 45 , // catch rate
        .exp = 130 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_UNKNOWN , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_MINERAL, EGG_MINERAL ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, ZAP_CANNON, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SNORE, BLIZZARD, HYPER_BEAM, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, IRON_TAIL, THUNDER, RETURN, PSYCHIC_M, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, DREAM_EATER, REST, THIEF, NIGHTMARE, FLASH, THUNDERBOLT, ICE_BEAM), 
    // end
    },
    [OMANYTE-1] = {
        .dexNo = OMANYTE , // 138
        .stats = { 35,  40, 100,  35,  90,  55}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {ROCK, WATER }, // type
        .catchRate = 45 , // catch rate
        .exp = 120 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F12_5 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 30 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_WATER_1, EGG_WATER_3 ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, ROLLOUT, TOXIC, ROCK_SMASH, HIDDEN_POWER, SNORE, BLIZZARD, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SANDSTORM, REST, ATTRACT, THIEF, SURF, WHIRLPOOL, ICE_BEAM), 
    // end
    },
    [OMASTAR-1] = {
        .dexNo = OMASTAR , // 139
        .stats = { 70,  60, 125,  55, 115,  70}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {ROCK, WATER }, // type
        .catchRate = 45 , // catch rate
        .exp = 199 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F12_5 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 30 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_WATER_1, EGG_WATER_3 ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, ROLLOUT, TOXIC, ROCK_SMASH, HIDDEN_POWER, SNORE, BLIZZARD, HYPER_BEAM, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SANDSTORM, REST, ATTRACT, THIEF, SURF, WHIRLPOOL, ICE_BEAM), 
    // end
    },
    [KABUTO-1] = {
        .dexNo = KABUTO , // 140
        .stats = { 30,  80,  90,  55,  55,  45}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {ROCK, WATER }, // type
        .catchRate = 45 , // catch rate
        .exp = 119 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F12_5 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 30 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_WATER_1, EGG_WATER_3 ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, ROLLOUT, TOXIC, ROCK_SMASH, HIDDEN_POWER, SNORE, BLIZZARD, ICY_WIND, PROTECT, RAIN_DANCE, GIGA_DRAIN, ENDURE, FRUSTRATION, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SANDSTORM, REST, ATTRACT, THIEF, ICE_BEAM), 
    // end
    },
    [KABUTOPS-1] = {
        .dexNo = KABUTOPS , // 141
        .stats = { 60, 115, 105,  80,  65,  70}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {ROCK, WATER }, // type
        .catchRate = 45 , // catch rate
        .exp = 201 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F12_5 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 30 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_WATER_1, EGG_WATER_3 ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, ROLLOUT, TOXIC, ROCK_SMASH, HIDDEN_POWER, SNORE, BLIZZARD, HYPER_BEAM, ICY_WIND, PROTECT, RAIN_DANCE, GIGA_DRAIN, ENDURE, FRUSTRATION, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SANDSTORM, REST, ATTRACT, THIEF, FURY_CUTTER, CUT, SURF, WHIRLPOOL, ICE_BEAM), 
    // end
    },
    [AERODACTYL-1] = {
        .dexNo = AERODACTYL , // 142
        .stats = { 80, 105,  65, 130,  60,  75}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {ROCK, FLYING }, // type
        .catchRate = 45 , // catch rate
        .exp = 202 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F12_5 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 35 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_FLYING, EGG_FLYING ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, ROAR, TOXIC, ROCK_SMASH, HIDDEN_POWER, SNORE, HYPER_BEAM, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, IRON_TAIL, DRAGONBREATH, EARTHQUAKE, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SANDSTORM, FIRE_BLAST, SWIFT, DETECT, REST, ATTRACT, STEEL_WING, FLY, FLAMETHROWER), 
    // end
    },
    [SNORLAX-1] = {
        .dexNo = SNORLAX , // 143
        .stats = {160, 110,  65,  30,  65, 110}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {NORMAL, NORMAL }, // type
        .catchRate = 25 , // catch rate
        .exp = 154 , // base exp
        .items = {LEFTOVERS, LEFTOVERS }, // items
        .gender = GENDER_F12_5 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 40 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_MONSTER, EGG_MONSTER ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, ROLLOUT, TOXIC, ZAP_CANNON, ROCK_SMASH, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SNORE, BLIZZARD, HYPER_BEAM, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, SOLARBEAM, THUNDER, EARTHQUAKE, RETURN, PSYCHIC_M, SHADOW_BALL, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, SANDSTORM, FIRE_BLAST, DEFENSE_CURL, THUNDERPUNCH, REST, ATTRACT, FIRE_PUNCH, SURF, STRENGTH, FLAMETHROWER, THUNDERBOLT, ICE_BEAM), 
    // end
    },
    [ARTICUNO-1] = {
        .dexNo = ARTICUNO , // 144
        .stats = { 90,  85, 100,  85,  95, 125}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {ICE, FLYING }, // type
        .catchRate = 3 , // catch rate
        .exp = 215 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_UNKNOWN , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 80 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_NONE, EGG_NONE ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, ROAR, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, BLIZZARD, HYPER_BEAM, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, RETURN, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SANDSTORM, SWIFT, DETECT, REST, STEEL_WING, FLY, ICE_BEAM), 
    // end
    },
    [ZAPDOS-1] = {
        .dexNo = ZAPDOS , // 145
        .stats = { 90,  90,  85, 100, 125,  90}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {ELECTRIC, FLYING }, // type
        .catchRate = 3 , // catch rate
        .exp = 216 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_UNKNOWN , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 80 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_NONE, EGG_NONE ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, ROAR, TOXIC, ZAP_CANNON, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, THUNDER, RETURN, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SANDSTORM, SWIFT, DETECT, REST, STEEL_WING, FLY, FLASH, THUNDERBOLT), 
    // end
    },
    [MOLTRES-1] = {
        .dexNo = MOLTRES , // 146
        .stats = { 90, 100,  90,  90, 125,  85}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {FIRE, FLYING }, // type
        .catchRate = 3 , // catch rate
        .exp = 217 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_UNKNOWN , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 80 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_NONE, EGG_NONE ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, ROAR, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, RETURN, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SANDSTORM, FIRE_BLAST, SWIFT, DETECT, REST, STEEL_WING, FLY, FLAMETHROWER), 
    // end
    },
    [DRATINI-1] = {
        .dexNo = DRATINI , // 147
        .stats = { 41,  64,  45,  50,  50,  50}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {DRAGON, DRAGON }, // type
        .catchRate = 45 , // catch rate
        .exp = 67 , // base exp
        .items = {NO_ITEM, DRAGON_SCALE }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 40 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_WATER_1, EGG_DRAGON ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, ZAP_CANNON, HIDDEN_POWER, SNORE, BLIZZARD, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, IRON_TAIL, DRAGONBREATH, THUNDER, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, FIRE_BLAST, SWIFT, DETECT, REST, ATTRACT, SURF, WATERFALL, FLAMETHROWER, THUNDERBOLT, ICE_BEAM), 
    // end
    },
    [DRAGONAIR-1] = {
        .dexNo = DRAGONAIR , // 148
        .stats = { 61,  84,  65,  70,  70,  70}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {DRAGON, DRAGON }, // type
        .catchRate = 45 , // catch rate
        .exp = 144 , // base exp
        .items = {NO_ITEM, DRAGON_SCALE }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 40 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_WATER_1, EGG_DRAGON ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, ZAP_CANNON, HIDDEN_POWER, SNORE, BLIZZARD, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, IRON_TAIL, DRAGONBREATH, THUNDER, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, FIRE_BLAST, SWIFT, DETECT, REST, ATTRACT, SURF, WATERFALL, FLAMETHROWER, THUNDERBOLT, ICE_BEAM), 
    // end
    },
    [DRAGONITE-1] = {
        .dexNo = DRAGONITE , // 149
        .stats = { 91, 134,  95,  80, 100, 100}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {DRAGON, FLYING }, // type
        .catchRate = 45 , // catch rate
        .exp = 218 , // base exp
        .items = {NO_ITEM, DRAGON_SCALE }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 40 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_WATER_1, EGG_DRAGON ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, TOXIC, ZAP_CANNON, ROCK_SMASH, HIDDEN_POWER, SNORE, BLIZZARD, HYPER_BEAM, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, IRON_TAIL, DRAGONBREATH, THUNDER, RETURN, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, SANDSTORM, FIRE_BLAST, SWIFT, THUNDERPUNCH, DETECT, REST, ATTRACT, STEEL_WING, FIRE_PUNCH, FURY_CUTTER, FLY, SURF, STRENGTH, WHIRLPOOL, WATERFALL, FLAMETHROWER, THUNDERBOLT, ICE_BEAM), 
    // end
    },
    [MEWTWO-1] = {
        .dexNo = MEWTWO , // 150
        .stats = {106, 110,  90, 130, 154,  90}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {PSYCHIC_TYPE, PSYCHIC_TYPE }, // type
        .catchRate = 3 , // catch rate
        .exp = 220 , // base exp
        .items = {NO_ITEM, BERSERK_GENE }, // items
        .gender = GENDER_UNKNOWN , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 120 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_NONE, EGG_NONE ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, TOXIC, ZAP_CANNON, ROCK_SMASH, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SNORE, BLIZZARD, HYPER_BEAM, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, SOLARBEAM, IRON_TAIL, THUNDER, RETURN, PSYCHIC_M, SHADOW_BALL, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, FIRE_BLAST, SWIFT, THUNDERPUNCH, DREAM_EATER, DETECT, REST, FIRE_PUNCH, NIGHTMARE, STRENGTH, FLASH, FLAMETHROWER, THUNDERBOLT, ICE_BEAM), 
    // end
    },
    [MEW-1] = {
        .dexNo = MEW , // 151
        .stats = {100, 100, 100, 100, 100, 100}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {PSYCHIC_TYPE, PSYCHIC_TYPE }, // type
        .catchRate = 45 , // catch rate
        .exp = 64 , // base exp
        .items = {NO_ITEM, MIRACLEBERRY }, // items
        .gender = GENDER_UNKNOWN , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 120 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_NONE, EGG_NONE ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, ROLLOUT, ROAR, TOXIC, ZAP_CANNON, ROCK_SMASH, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SWEET_SCENT, SNORE, BLIZZARD, HYPER_BEAM, ICY_WIND, PROTECT, RAIN_DANCE, GIGA_DRAIN, ENDURE, FRUSTRATION, SOLARBEAM, IRON_TAIL, DRAGONBREATH, THUNDER, EARTHQUAKE, RETURN, DIG, PSYCHIC_M, SHADOW_BALL, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, SLUDGE_BOMB, SANDSTORM, FIRE_BLAST, SWIFT, DEFENSE_CURL, THUNDERPUNCH, DREAM_EATER, DETECT, REST, ATTRACT, THIEF, STEEL_WING, FIRE_PUNCH, FURY_CUTTER, NIGHTMARE, CUT, FLY, SURF, STRENGTH, FLASH, WHIRLPOOL, WATERFALL, FLAMETHROWER, THUNDERBOLT, ICE_BEAM), 
    // end
    },
    [CHIKORITA-1] = {
        .dexNo = CHIKORITA , // 152
        .stats = { 45,  49,  65,  45,  49,  65}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {GRASS, GRASS }, // type
        .catchRate = 45 , // catch rate
        .exp = 64 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F12_5 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_MONSTER, EGG_PLANT ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, HIDDEN_POWER, SUNNY_DAY, SWEET_SCENT, SNORE, PROTECT, GIGA_DRAIN, ENDURE, FRUSTRATION, SOLARBEAM, IRON_TAIL, RETURN, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, DETECT, REST, ATTRACT, CUT, FLASH), 
    // end
    },
    [BAYLEEF-1] = {
        .dexNo = BAYLEEF , // 153
        .stats = { 60,  62,  80,  60,  63,  80}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {GRASS, GRASS }, // type
        .catchRate = 45 , // catch rate
        .exp = 141 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F12_5 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_MONSTER, EGG_PLANT ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SWEET_SCENT, SNORE, PROTECT, GIGA_DRAIN, ENDURE, FRUSTRATION, SOLARBEAM, IRON_TAIL, RETURN, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, DETECT, REST, ATTRACT, FURY_CUTTER, CUT, STRENGTH, FLASH), 
    // end
    },
    [MEGANIUM-1] = {
        .dexNo = MEGANIUM , // 154
        .stats = { 80,  82, 100,  80,  83, 100}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {GRASS, GRASS }, // type
        .catchRate = 45 , // catch rate
        .exp = 208 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F12_5 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_MONSTER, EGG_PLANT ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SWEET_SCENT, SNORE, HYPER_BEAM, PROTECT, GIGA_DRAIN, ENDURE, FRUSTRATION, SOLARBEAM, IRON_TAIL, EARTHQUAKE, RETURN, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, DETECT, REST, ATTRACT, FURY_CUTTER, CUT, STRENGTH, FLASH), 
    // end
    },
    [CYNDAQUIL-1] = {
        .dexNo = CYNDAQUIL , // 155
        .stats = { 39,  52,  43,  65,  60,  50}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {FIRE, FIRE }, // type
        .catchRate = 45 , // catch rate
        .exp = 65 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F12_5 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_GROUND, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, ROLLOUT, TOXIC, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, ENDURE, FRUSTRATION, IRON_TAIL, RETURN, DIG, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, FIRE_BLAST, SWIFT, DEFENSE_CURL, DETECT, REST, ATTRACT, CUT, FLAMETHROWER), 
    // end
    },
    [QUILAVA-1] = {
        .dexNo = QUILAVA , // 156
        .stats = { 58,  64,  58,  80,  80,  65}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {FIRE, FIRE }, // type
        .catchRate = 45 , // catch rate
        .exp = 142 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F12_5 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_GROUND, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, ROLLOUT, ROAR, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, ENDURE, FRUSTRATION, IRON_TAIL, RETURN, DIG, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, FIRE_BLAST, SWIFT, DEFENSE_CURL, DETECT, REST, ATTRACT, FURY_CUTTER, CUT, STRENGTH, FLAMETHROWER), 
    // end
    },
    [TYPHLOSION-1] = {
        .dexNo = TYPHLOSION , // 157
        .stats = { 78,  84,  78, 100, 109,  85}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {FIRE, FIRE }, // type
        .catchRate = 45 , // catch rate
        .exp = 209 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F12_5 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_GROUND, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, ROLLOUT, ROAR, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, PROTECT, ENDURE, FRUSTRATION, IRON_TAIL, EARTHQUAKE, RETURN, DIG, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, FIRE_BLAST, SWIFT, DEFENSE_CURL, THUNDERPUNCH, DETECT, REST, ATTRACT, FIRE_PUNCH, FURY_CUTTER, CUT, STRENGTH, FLAMETHROWER), 
    // end
    },
    [TOTODILE-1] = {
        .dexNo = TOTODILE , // 158
        .stats = { 50,  65,  64,  43,  44,  48}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {WATER, WATER }, // type
        .catchRate = 45 , // catch rate
        .exp = 66 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F12_5 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_MONSTER, EGG_WATER_1 ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, TOXIC, HIDDEN_POWER, SNORE, BLIZZARD, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, IRON_TAIL, RETURN, DIG, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, DETECT, REST, ATTRACT, CUT, SURF, WHIRLPOOL, ICE_BEAM), 
    // end
    },
    [CROCONAW-1] = {
        .dexNo = CROCONAW , // 159
        .stats = { 65,  80,  80,  58,  59,  63}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {WATER, WATER }, // type
        .catchRate = 45 , // catch rate
        .exp = 143 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F12_5 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_MONSTER, EGG_WATER_1 ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, ROAR, TOXIC, ROCK_SMASH, HIDDEN_POWER, SNORE, BLIZZARD, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, IRON_TAIL, RETURN, DIG, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, DETECT, REST, ATTRACT, FURY_CUTTER, CUT, SURF, STRENGTH, WHIRLPOOL, ICE_BEAM), 
    // end
    },
    [FERALIGATR-1] = {
        .dexNo = FERALIGATR , // 160
        .stats = { 85, 105, 100,  78,  79,  83}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {WATER, WATER }, // type
        .catchRate = 45 , // catch rate
        .exp = 210 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F12_5 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_MONSTER, EGG_WATER_1 ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, ROAR, TOXIC, ROCK_SMASH, HIDDEN_POWER, SNORE, BLIZZARD, HYPER_BEAM, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, IRON_TAIL, EARTHQUAKE, RETURN, DIG, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, DETECT, REST, ATTRACT, FURY_CUTTER, CUT, SURF, STRENGTH, WHIRLPOOL, ICE_BEAM), 
    // end
    },
    [SENTRET-1] = {
        .dexNo = SENTRET , // 161
        .stats = { 35,  46,  34,  20,  35,  45}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {NORMAL, NORMAL }, // type
        .catchRate = 255 , // catch rate
        .exp = 57 , // base exp
        .items = {NO_ITEM, BERRY }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 15 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_GROUND, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, ROLLOUT, TOXIC, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, ENDURE, FRUSTRATION, IRON_TAIL, RETURN, DIG, SHADOW_BALL, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, SWIFT, DEFENSE_CURL, THUNDERPUNCH, DETECT, REST, ATTRACT, THIEF, FIRE_PUNCH, FURY_CUTTER, CUT, SURF), 
    // end
    },
    [FURRET-1] = {
        .dexNo = FURRET , // 162
        .stats = { 85,  76,  64,  90,  45,  55}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {NORMAL, NORMAL }, // type
        .catchRate = 90 , // catch rate
        .exp = 116 , // base exp
        .items = {BERRY, GOLD_BERRY }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 15 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_GROUND, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, ROLLOUT, TOXIC, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, PROTECT, ENDURE, FRUSTRATION, IRON_TAIL, RETURN, DIG, SHADOW_BALL, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, SWIFT, DEFENSE_CURL, THUNDERPUNCH, DETECT, REST, ATTRACT, THIEF, FIRE_PUNCH, FURY_CUTTER, CUT, SURF, STRENGTH), 
    // end
    },
    [HOOTHOOT-1] = {
        .dexNo = HOOTHOOT , // 163
        .stats = { 60,  30,  30,  50,  36,  56}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {NORMAL, FLYING }, // type
        .catchRate = 255 , // catch rate
        .exp = 58 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 15 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_FLYING, EGG_FLYING ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, ENDURE, FRUSTRATION, RETURN, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, DREAM_EATER, DETECT, REST, ATTRACT, THIEF, STEEL_WING, NIGHTMARE, FLY, FLASH), 
    // end
    },
    [NOCTOWL-1] = {
        .dexNo = NOCTOWL , // 164
        .stats = {100,  50,  50,  70,  76,  96}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {NORMAL, FLYING }, // type
        .catchRate = 90 , // catch rate
        .exp = 162 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 15 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_FLYING, EGG_FLYING ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, PROTECT, ENDURE, FRUSTRATION, RETURN, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, DREAM_EATER, DETECT, REST, ATTRACT, THIEF, STEEL_WING, NIGHTMARE, FLY, FLASH), 
    // end
    },
    [LEDYBA-1] = {
        .dexNo = LEDYBA , // 165
        .stats = { 40,  20,  30,  55,  40,  80}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {BUG, FLYING }, // type
        .catchRate = 255 , // catch rate
        .exp = 54 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 15 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_BUG, EGG_BUG ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, ROLLOUT, TOXIC, HIDDEN_POWER, SUNNY_DAY, SWEET_SCENT, SNORE, PROTECT, GIGA_DRAIN, ENDURE, FRUSTRATION, SOLARBEAM, RETURN, DIG, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, SWIFT, THUNDERPUNCH, REST, ATTRACT, THIEF, FLASH), 
    // end
    },
    [LEDIAN-1] = {
        .dexNo = LEDIAN , // 166
        .stats = { 55,  35,  50,  85,  55, 110}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {BUG, FLYING }, // type
        .catchRate = 90 , // catch rate
        .exp = 134 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 15 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_BUG, EGG_BUG ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, ROLLOUT, TOXIC, HIDDEN_POWER, SUNNY_DAY, SWEET_SCENT, SNORE, HYPER_BEAM, PROTECT, GIGA_DRAIN, ENDURE, FRUSTRATION, SOLARBEAM, RETURN, DIG, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, SWIFT, THUNDERPUNCH, REST, ATTRACT, THIEF, FLASH), 
    // end
    },
    [SPINARAK-1] = {
        .dexNo = SPINARAK , // 167
        .stats = { 40,  60,  40,  30,  40,  40}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {BUG, POISON }, // type
        .catchRate = 255 , // catch rate
        .exp = 54 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 15 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_BUG, EGG_BUG ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, GIGA_DRAIN, ENDURE, FRUSTRATION, SOLARBEAM, RETURN, DIG, PSYCHIC_M, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SLUDGE_BOMB, REST, ATTRACT, THIEF, FLASH), 
    // end
    },
    [ARIADOS-1] = {
        .dexNo = ARIADOS , // 168
        .stats = { 70,  90,  70,  40,  60,  60}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {BUG, POISON }, // type
        .catchRate = 90 , // catch rate
        .exp = 134 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 15 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_BUG, EGG_BUG ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, PROTECT, GIGA_DRAIN, ENDURE, FRUSTRATION, SOLARBEAM, RETURN, DIG, PSYCHIC_M, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SLUDGE_BOMB, REST, ATTRACT, THIEF, FLASH), 
    // end
    },
    [CROBAT-1] = {
        .dexNo = CROBAT , // 169
        .stats = { 85,  90,  80, 130,  70,  80}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {POISON, FLYING }, // type
        .catchRate = 90 , // catch rate
        .exp = 204 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 15 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_FLYING, EGG_FLYING ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, PROTECT, GIGA_DRAIN, ENDURE, FRUSTRATION, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, DETECT, REST, ATTRACT, THIEF, STEEL_WING, FLY), 
    // end
    },
    [CHINCHOU-1] = {
        .dexNo = CHINCHOU , // 170
        .stats = { 75,  38,  38,  67,  56,  56}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {WATER, ELECTRIC }, // type
        .catchRate = 190 , // catch rate
        .exp = 90 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_WATER_2, EGG_WATER_2 ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, ZAP_CANNON, HIDDEN_POWER, SNORE, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, THUNDER, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, REST, ATTRACT, SURF, FLASH, WHIRLPOOL, WATERFALL, THUNDERBOLT, ICE_BEAM), 
    // end
    },
    [LANTURN-1] = {
        .dexNo = LANTURN , // 171
        .stats = {125,  58,  58,  67,  76,  76}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {WATER, ELECTRIC }, // type
        .catchRate = 75 , // catch rate
        .exp = 156 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_WATER_2, EGG_WATER_2 ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, ZAP_CANNON, HIDDEN_POWER, SNORE, HYPER_BEAM, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, THUNDER, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, REST, ATTRACT, SURF, FLASH, WHIRLPOOL, WATERFALL, THUNDERBOLT, ICE_BEAM), 
    // end
    },
    [PICHU-1] = {
        .dexNo = PICHU , // 172
        .stats = { 20,  40,  15,  60,  35,  35}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {ELECTRIC, ELECTRIC }, // type
        .catchRate = 190 , // catch rate
        .exp = 42 , // base exp
        .items = {NO_ITEM, BERRY }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 10 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_NONE, EGG_NONE ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, ROLLOUT, TOXIC, ZAP_CANNON, HIDDEN_POWER, SNORE, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, IRON_TAIL, THUNDER, RETURN, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, DEFENSE_CURL, DETECT, REST, ATTRACT, FLASH, THUNDERBOLT), 
    // end
    },
    [CLEFFA-1] = {
        .dexNo = CLEFFA , // 173
        .stats = { 50,  25,  28,  15,  45,  55}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {NORMAL, NORMAL }, // type
        .catchRate = 150 , // catch rate
        .exp = 37 , // base exp
        .items = {MYSTERYBERRY, MOON_STONE }, // items
        .gender = GENDER_F75 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 10 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_NONE, EGG_NONE ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, ROLLOUT, TOXIC, ZAP_CANNON, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SNORE, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, SOLARBEAM, IRON_TAIL, RETURN, PSYCHIC_M, SHADOW_BALL, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, FIRE_BLAST, DEFENSE_CURL, DREAM_EATER, DETECT, REST, ATTRACT, NIGHTMARE, FLASH, FLAMETHROWER), 
    // end
    },
    [IGGLYBUFF-1] = {
        .dexNo = IGGLYBUFF , // 174
        .stats = { 90,  30,  15,  15,  40,  20}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {NORMAL, NORMAL }, // type
        .catchRate = 170 , // catch rate
        .exp = 39 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F75 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 10 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_NONE, EGG_NONE ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, ROLLOUT, TOXIC, ZAP_CANNON, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SNORE, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, SOLARBEAM, RETURN, PSYCHIC_M, SHADOW_BALL, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, FIRE_BLAST, DEFENSE_CURL, DREAM_EATER, DETECT, REST, ATTRACT, NIGHTMARE, FLASH, FLAMETHROWER), 
    // end
    },
    [TOGEPI-1] = {
        .dexNo = TOGEPI , // 175
        .stats = { 35,  20,  65,  20,  40,  65}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {NORMAL, NORMAL }, // type
        .catchRate = 190 , // catch rate
        .exp = 74 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F12_5 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 10 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_NONE, EGG_NONE ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, ROLLOUT, TOXIC, ZAP_CANNON, ROCK_SMASH, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, SOLARBEAM, RETURN, PSYCHIC_M, SHADOW_BALL, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, FIRE_BLAST, SWIFT, DEFENSE_CURL, DREAM_EATER, DETECT, REST, ATTRACT, FLASH, FLAMETHROWER), 
    // end
    },
    [TOGETIC-1] = {
        .dexNo = TOGETIC , // 176
        .stats = { 55,  40,  85,  40,  80, 105}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {NORMAL, FLYING }, // type
        .catchRate = 75 , // catch rate
        .exp = 114 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F12_5 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 10 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_FLYING, EGG_FAIRY ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, ROLLOUT, TOXIC, ZAP_CANNON, ROCK_SMASH, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, SOLARBEAM, RETURN, PSYCHIC_M, SHADOW_BALL, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, FIRE_BLAST, SWIFT, DEFENSE_CURL, DREAM_EATER, DETECT, REST, ATTRACT, STEEL_WING, FLY, FLASH, FLAMETHROWER), 
    // end
    },
    [NATU-1] = {
        .dexNo = NATU , // 177
        .stats = { 40,  50,  45,  70,  70,  45}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {PSYCHIC_TYPE, FLYING }, // type
        .catchRate = 190 , // catch rate
        .exp = 73 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_FLYING, EGG_FLYING ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, GIGA_DRAIN, ENDURE, FRUSTRATION, SOLARBEAM, RETURN, PSYCHIC_M, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, DREAM_EATER, DETECT, REST, ATTRACT, THIEF, NIGHTMARE, FLASH), 
    // end
    },
    [XATU-1] = {
        .dexNo = XATU , // 178
        .stats = { 65,  75,  70,  95,  95,  70}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {PSYCHIC_TYPE, FLYING }, // type
        .catchRate = 75 , // catch rate
        .exp = 171 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_FLYING, EGG_FLYING ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, PROTECT, GIGA_DRAIN, ENDURE, FRUSTRATION, SOLARBEAM, RETURN, PSYCHIC_M, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, DREAM_EATER, DETECT, REST, ATTRACT, THIEF, NIGHTMARE, FLY, FLASH), 
    // end
    },
    [MAREEP-1] = {
        .dexNo = MAREEP , // 179
        .stats = { 55,  40,  40,  35,  65,  45}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {ELECTRIC, ELECTRIC }, // type
        .catchRate = 235 , // catch rate
        .exp = 59 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_MONSTER, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, ZAP_CANNON, HIDDEN_POWER, SNORE, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, IRON_TAIL, THUNDER, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, DEFENSE_CURL, REST, ATTRACT, FLASH, THUNDERBOLT), 
    // end
    },
    [FLAAFFY-1] = {
        .dexNo = FLAAFFY , // 180
        .stats = { 70,  55,  55,  45,  80,  60}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {ELECTRIC, ELECTRIC }, // type
        .catchRate = 120 , // catch rate
        .exp = 117 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_MONSTER, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, TOXIC, ZAP_CANNON, ROCK_SMASH, HIDDEN_POWER, SNORE, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, IRON_TAIL, THUNDER, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, DEFENSE_CURL, THUNDERPUNCH, REST, ATTRACT, FIRE_PUNCH, STRENGTH, FLASH, THUNDERBOLT), 
    // end
    },
    [AMPHAROS-1] = {
        .dexNo = AMPHAROS , // 181
        .stats = { 90,  75,  75,  55, 115,  90}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {ELECTRIC, ELECTRIC }, // type
        .catchRate = 45 , // catch rate
        .exp = 194 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_MONSTER, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, TOXIC, ZAP_CANNON, ROCK_SMASH, HIDDEN_POWER, SNORE, HYPER_BEAM, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, IRON_TAIL, THUNDER, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, DEFENSE_CURL, THUNDERPUNCH, REST, ATTRACT, FIRE_PUNCH, STRENGTH, FLASH, THUNDERBOLT), 
    // end
    },
    [BELLOSSOM-1] = {
        .dexNo = BELLOSSOM , // 182
        .stats = { 75,  80,  85,  50,  90, 100}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {GRASS, GRASS }, // type
        .catchRate = 45 , // catch rate
        .exp = 184 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_PLANT, EGG_PLANT ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, HIDDEN_POWER, SUNNY_DAY, SWEET_SCENT, SNORE, HYPER_BEAM, PROTECT, GIGA_DRAIN, ENDURE, FRUSTRATION, SOLARBEAM, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, REST, ATTRACT, CUT, FLASH), 
    // end
    },
    [MARILL-1] = {
        .dexNo = MARILL , // 183
        .stats = { 70,  20,  50,  40,  20,  50}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {WATER, WATER }, // type
        .catchRate = 190 , // catch rate
        .exp = 58 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_WATER_1, EGG_FAIRY ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, ROLLOUT, TOXIC, HIDDEN_POWER, SNORE, BLIZZARD, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, IRON_TAIL, RETURN, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, SWIFT, DEFENSE_CURL, REST, ATTRACT, SURF, WHIRLPOOL, WATERFALL, ICE_BEAM), 
    // end
    },
    [AZUMARILL-1] = {
        .dexNo = AZUMARILL , // 184
        .stats = {100,  50,  80,  50,  50,  80}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {WATER, WATER }, // type
        .catchRate = 75 , // catch rate
        .exp = 153 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_WATER_1, EGG_FAIRY ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, ROLLOUT, TOXIC, ROCK_SMASH, HIDDEN_POWER, SNORE, BLIZZARD, HYPER_BEAM, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, IRON_TAIL, RETURN, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, SWIFT, DEFENSE_CURL, REST, ATTRACT, SURF, STRENGTH, WHIRLPOOL, WATERFALL, ICE_BEAM), 
    // end
    },
    [SUDOWOODO-1] = {
        .dexNo = SUDOWOODO , // 185
        .stats = { 70, 100, 115,  30,  30,  65}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {ROCK, ROCK }, // type
        .catchRate = 65 , // catch rate
        .exp = 135 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_MINERAL, EGG_MINERAL ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, ROLLOUT, TOXIC, ROCK_SMASH, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, ENDURE, FRUSTRATION, EARTHQUAKE, RETURN, DIG, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, SANDSTORM, DEFENSE_CURL, THUNDERPUNCH, REST, ATTRACT, THIEF, FIRE_PUNCH, STRENGTH), 
    // end
    },
    [POLITOED-1] = {
        .dexNo = POLITOED , // 186
        .stats = { 90,  75,  75,  70,  90, 100}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {WATER, WATER }, // type
        .catchRate = 45 , // catch rate
        .exp = 185 , // base exp
        .items = {NO_ITEM, KINGS_ROCK }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_WATER_1, EGG_WATER_1 ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, TOXIC, ROCK_SMASH, HIDDEN_POWER, SNORE, BLIZZARD, HYPER_BEAM, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, EARTHQUAKE, RETURN, PSYCHIC_M, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, DEFENSE_CURL, DETECT, REST, ATTRACT, THIEF, SURF, STRENGTH, WHIRLPOOL, WATERFALL, ICE_BEAM), 
    // end
    },
    [HOPPIP-1] = {
        .dexNo = HOPPIP , // 187
        .stats = { 35,  35,  40,  50,  35,  55}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {GRASS, FLYING }, // type
        .catchRate = 255 , // catch rate
        .exp = 74 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_FAIRY, EGG_PLANT ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, HIDDEN_POWER, SUNNY_DAY, SWEET_SCENT, SNORE, PROTECT, GIGA_DRAIN, ENDURE, FRUSTRATION, SOLARBEAM, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, DEFENSE_CURL, REST, ATTRACT, FLASH), 
    // end
    },
    [SKIPLOOM-1] = {
        .dexNo = SKIPLOOM , // 188
        .stats = { 55,  45,  50,  80,  45,  65}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {GRASS, FLYING }, // type
        .catchRate = 120 , // catch rate
        .exp = 136 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_FAIRY, EGG_PLANT ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, HIDDEN_POWER, SUNNY_DAY, SWEET_SCENT, SNORE, PROTECT, GIGA_DRAIN, ENDURE, FRUSTRATION, SOLARBEAM, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, DEFENSE_CURL, REST, ATTRACT, FLASH), 
    // end
    },
    [JUMPLUFF-1] = {
        .dexNo = JUMPLUFF , // 189
        .stats = { 75,  55,  70, 110,  55,  85}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {GRASS, FLYING }, // type
        .catchRate = 45 , // catch rate
        .exp = 176 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_FAIRY, EGG_PLANT ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, HIDDEN_POWER, SUNNY_DAY, SWEET_SCENT, SNORE, HYPER_BEAM, PROTECT, GIGA_DRAIN, ENDURE, FRUSTRATION, SOLARBEAM, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, DEFENSE_CURL, REST, ATTRACT, FLASH), 
    // end
    },
    [AIPOM-1] = {
        .dexNo = AIPOM , // 190
        .stats = { 55,  70,  55,  85,  40,  55}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {NORMAL, NORMAL }, // type
        .catchRate = 45 , // catch rate
        .exp = 94 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_GROUND, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, TOXIC, ZAP_CANNON, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, ENDURE, FRUSTRATION, IRON_TAIL, THUNDER, RETURN, SHADOW_BALL, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, SWIFT, DEFENSE_CURL, THUNDERPUNCH, DREAM_EATER, DETECT, REST, ATTRACT, THIEF, FIRE_PUNCH, FURY_CUTTER, NIGHTMARE, CUT, STRENGTH, THUNDERBOLT), 
    // end
    },
    [SUNKERN-1] = {
        .dexNo = SUNKERN , // 191
        .stats = { 30,  30,  30,  30,  30,  30}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {GRASS, GRASS }, // type
        .catchRate = 235 , // catch rate
        .exp = 52 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_PLANT, EGG_PLANT ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, HIDDEN_POWER, SUNNY_DAY, SWEET_SCENT, SNORE, PROTECT, GIGA_DRAIN, ENDURE, FRUSTRATION, SOLARBEAM, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SLUDGE_BOMB, REST, ATTRACT, CUT, FLASH), 
    // end
    },
    [SUNFLORA-1] = {
        .dexNo = SUNFLORA , // 192
        .stats = { 75,  75,  55,  30, 105,  85}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {GRASS, GRASS }, // type
        .catchRate = 120 , // catch rate
        .exp = 146 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_PLANT, EGG_PLANT ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, HIDDEN_POWER, SUNNY_DAY, SWEET_SCENT, SNORE, HYPER_BEAM, PROTECT, GIGA_DRAIN, ENDURE, FRUSTRATION, SOLARBEAM, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SLUDGE_BOMB, REST, ATTRACT, CUT, FLASH), 
    // end
    },
    [YANMA-1] = {
        .dexNo = YANMA , // 193
        .stats = { 65,  65,  45,  95,  75,  45}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {BUG, FLYING }, // type
        .catchRate = 75 , // catch rate
        .exp = 147 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_BUG, EGG_BUG ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, GIGA_DRAIN, ENDURE, FRUSTRATION, SOLARBEAM, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, DETECT, REST, ATTRACT, THIEF, FLASH), 
    // end
    },
    [WOOPER-1] = {
        .dexNo = WOOPER , // 194
        .stats = { 55,  45,  45,  15,  25,  25}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {WATER, GROUND }, // type
        .catchRate = 255 , // catch rate
        .exp = 52 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_WATER_1, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, ROLLOUT, TOXIC, ROCK_SMASH, HIDDEN_POWER, SNORE, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, IRON_TAIL, EARTHQUAKE, RETURN, DIG, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, SLUDGE_BOMB, SANDSTORM, DEFENSE_CURL, REST, ATTRACT, SURF, FLASH, WHIRLPOOL, ICE_BEAM), 
    // end
    },
    [QUAGSIRE-1] = {
        .dexNo = QUAGSIRE , // 195
        .stats = { 95,  85,  85,  35,  65,  65}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {WATER, GROUND }, // type
        .catchRate = 90 , // catch rate
        .exp = 137 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_WATER_1, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, ROLLOUT, TOXIC, ROCK_SMASH, HIDDEN_POWER, SNORE, HYPER_BEAM, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, IRON_TAIL, EARTHQUAKE, RETURN, DIG, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, SLUDGE_BOMB, SANDSTORM, DEFENSE_CURL, REST, ATTRACT, SURF, STRENGTH, FLASH, WHIRLPOOL, ICE_BEAM), 
    // end
    },
    [ESPEON-1] = {
        .dexNo = ESPEON , // 196
        .stats = { 65,  65,  60, 110, 130,  95}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {PSYCHIC_TYPE, PSYCHIC_TYPE }, // type
        .catchRate = 45 , // catch rate
        .exp = 197 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F12_5 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 35 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_GROUND, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, ZAP_CANNON, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, IRON_TAIL, RETURN, PSYCHIC_M, SHADOW_BALL, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, DREAM_EATER, DETECT, REST, ATTRACT, NIGHTMARE, CUT, FLASH), 
    // end
    },
    [UMBREON-1] = {
        .dexNo = UMBREON , // 197
        .stats = { 95,  65, 110,  65,  60, 130}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {DARK, DARK }, // type
        .catchRate = 45 , // catch rate
        .exp = 197 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F12_5 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 35 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_GROUND, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, ZAP_CANNON, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, IRON_TAIL, RETURN, PSYCHIC_M, SHADOW_BALL, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, DREAM_EATER, DETECT, REST, ATTRACT, NIGHTMARE, CUT, FLASH), 
    // end
    },
    [MURKROW-1] = {
        .dexNo = MURKROW , // 198
        .stats = { 60,  85,  42,  91,  85,  42}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {DARK, FLYING }, // type
        .catchRate = 30 , // catch rate
        .exp = 107 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_FLYING, EGG_FLYING ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SNORE, ICY_WIND, PROTECT, ENDURE, FRUSTRATION, RETURN, SHADOW_BALL, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, DREAM_EATER, DETECT, REST, ATTRACT, THIEF, STEEL_WING, NIGHTMARE, FLY), 
    // end
    },
    [SLOWKING-1] = {
        .dexNo = SLOWKING , // 199
        .stats = { 95,  75,  80,  30, 100, 110}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {WATER, PSYCHIC_TYPE }, // type
        .catchRate = 70 , // catch rate
        .exp = 164 , // base exp
        .items = {NO_ITEM, KINGS_ROCK }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_MONSTER, EGG_WATER_1 ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, TOXIC, ZAP_CANNON, ROCK_SMASH, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SNORE, BLIZZARD, HYPER_BEAM, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, IRON_TAIL, EARTHQUAKE, RETURN, DIG, PSYCHIC_M, SHADOW_BALL, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, FIRE_BLAST, SWIFT, DREAM_EATER, REST, ATTRACT, FURY_CUTTER, NIGHTMARE, SURF, STRENGTH, FLASH, WHIRLPOOL, FLAMETHROWER, ICE_BEAM), 
    // end
    },
    [MISDREAVUS-1] = {
        .dexNo = MISDREAVUS , // 200
        .stats = { 60,  60,  60,  85,  85,  85}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {GHOST, GHOST }, // type
        .catchRate = 45 , // catch rate
        .exp = 147 , // base exp
        .items = {NO_ITEM, SPELL_TAG }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 25 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_INDETERMINATE, EGG_INDETERMINATE ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, ZAP_CANNON, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, THUNDER, RETURN, PSYCHIC_M, SHADOW_BALL, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, DEFENSE_CURL, DREAM_EATER, REST, ATTRACT, THIEF, NIGHTMARE, FLASH, THUNDERBOLT), 
    // end
    },
    [UNOWN-1] = {
        .dexNo = UNOWN , // 201
        .stats = { 48,  72,  48,  48,  72,  48}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {PSYCHIC_TYPE, PSYCHIC_TYPE }, // type
        .catchRate = 225 , // catch rate
        .exp = 61 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_UNKNOWN , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 40 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_NONE, EGG_NONE ), // egg groups
    // tm/hm learnset
        .TMHM = { NULL },
    // end
    },
    [WOBBUFFET-1] = {
        .dexNo = WOBBUFFET , // 202
        .stats = {190,  33,  58,  33,  33,  58}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {PSYCHIC_TYPE, PSYCHIC_TYPE }, // type
        .catchRate = 45 , // catch rate
        .exp = 177 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_INDETERMINATE, EGG_INDETERMINATE ), // egg groups
    // tm/hm learnset
        .TMHM = { NULL },
    // end
    },
    [GIRAFARIG-1] = {
        .dexNo = GIRAFARIG , // 203
        .stats = { 70,  80,  65,  85,  90,  65}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {NORMAL, PSYCHIC_TYPE }, // type
        .catchRate = 60 , // catch rate
        .exp = 149 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_GROUND, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, ZAP_CANNON, ROCK_SMASH, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, ENDURE, FRUSTRATION, IRON_TAIL, THUNDER, EARTHQUAKE, RETURN, PSYCHIC_M, SHADOW_BALL, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, DREAM_EATER, REST, ATTRACT, THIEF, NIGHTMARE, STRENGTH, THUNDERBOLT), 
    // end
    },
    [PINECO-1] = {
        .dexNo = PINECO , // 204
        .stats = { 50,  65,  90,  15,  35,  35}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {BUG, BUG }, // type
        .catchRate = 190 , // catch rate
        .exp = 60 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_BUG, EGG_BUG ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, ROLLOUT, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SWEET_SCENT, SNORE, PROTECT, GIGA_DRAIN, ENDURE, FRUSTRATION, SOLARBEAM, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, DEFENSE_CURL, REST, ATTRACT, STRENGTH), 
    // end
    },
    [FORRETRESS-1] = {
        .dexNo = FORRETRESS , // 205
        .stats = { 75,  90, 140,  40,  60,  60}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {BUG, STEEL }, // type
        .catchRate = 75 , // catch rate
        .exp = 118 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_BUG, EGG_BUG ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, ROLLOUT, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SWEET_SCENT, SNORE, HYPER_BEAM, PROTECT, GIGA_DRAIN, ENDURE, FRUSTRATION, SOLARBEAM, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SANDSTORM, DEFENSE_CURL, REST, ATTRACT, STRENGTH), 
    // end
    },
    [DUNSPARCE-1] = {
        .dexNo = DUNSPARCE , // 206
        .stats = {100,  70,  70,  45,  65,  65}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {NORMAL, NORMAL }, // type
        .catchRate = 190 , // catch rate
        .exp = 75 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_GROUND, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, ROLLOUT, TOXIC, ZAP_CANNON, ROCK_SMASH, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, SOLARBEAM, IRON_TAIL, THUNDER, RETURN, DIG, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, DEFENSE_CURL, DREAM_EATER, REST, ATTRACT, THIEF, NIGHTMARE, STRENGTH, FLAMETHROWER, THUNDERBOLT), 
    // end
    },
    [GLIGAR-1] = {
        .dexNo = GLIGAR , // 207
        .stats = { 65,  75, 105,  85,  35,  65}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {GROUND, FLYING }, // type
        .catchRate = 60 , // catch rate
        .exp = 108 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_BUG, EGG_BUG ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, ENDURE, FRUSTRATION, IRON_TAIL, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SLUDGE_BOMB, SANDSTORM, SWIFT, DETECT, REST, ATTRACT, THIEF, FURY_CUTTER, CUT, STRENGTH), 
    // end
    },
    [STEELIX-1] = {
        .dexNo = STEELIX , // 208
        .stats = { 75,  85, 200,  30,  55,  65}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {STEEL, GROUND }, // type
        .catchRate = 25 , // catch rate
        .exp = 196 , // base exp
        .items = {NO_ITEM, METAL_COAT }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 25 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_MINERAL, EGG_MINERAL ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, ROLLOUT, ROAR, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, PROTECT, ENDURE, FRUSTRATION, IRON_TAIL, DRAGONBREATH, EARTHQUAKE, RETURN, DIG, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SANDSTORM, DEFENSE_CURL, REST, ATTRACT, CUT, STRENGTH), 
    // end
    },
    [SNUBBULL-1] = {
        .dexNo = SNUBBULL , // 209
        .stats = { 60,  80,  50,  30,  40,  40}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {NORMAL, NORMAL }, // type
        .catchRate = 190 , // catch rate
        .exp = 63 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F75 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_GROUND, EGG_FAIRY ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, ROAR, TOXIC, ZAP_CANNON, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, THUNDER, RETURN, SHADOW_BALL, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, SLUDGE_BOMB, DEFENSE_CURL, THUNDERPUNCH, DETECT, REST, ATTRACT, THIEF, FIRE_PUNCH, STRENGTH, THUNDERBOLT), 
    // end
    },
    [GRANBULL-1] = {
        .dexNo = GRANBULL , // 210
        .stats = { 90, 120,  75,  45,  60,  60}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {NORMAL, NORMAL }, // type
        .catchRate = 75 , // catch rate
        .exp = 178 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F75 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_GROUND, EGG_FAIRY ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, ROAR, TOXIC, ZAP_CANNON, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, THUNDER, RETURN, SHADOW_BALL, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, SLUDGE_BOMB, DEFENSE_CURL, THUNDERPUNCH, DETECT, REST, ATTRACT, THIEF, FIRE_PUNCH, STRENGTH, THUNDERBOLT), 
    // end
    },
    [QWILFISH-1] = {
        .dexNo = QWILFISH , // 211
        .stats = { 65,  95,  75,  85,  55,  55}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {WATER, POISON }, // type
        .catchRate = 45 , // catch rate
        .exp = 100 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_WATER_2, EGG_WATER_2 ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, ROLLOUT, TOXIC, HIDDEN_POWER, SNORE, BLIZZARD, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SLUDGE_BOMB, SWIFT, DEFENSE_CURL, REST, ATTRACT, SURF, WHIRLPOOL, WATERFALL, ICE_BEAM), 
    // end
    },
    [SCIZOR-1] = {
        .dexNo = SCIZOR , // 212
        .stats = { 70, 130, 100,  65,  55,  80}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {BUG, STEEL }, // type
        .catchRate = 25 , // catch rate
        .exp = 200 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 25 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_BUG, EGG_BUG ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, PROTECT, ENDURE, FRUSTRATION, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SANDSTORM, SWIFT, DETECT, REST, ATTRACT, THIEF, STEEL_WING, FURY_CUTTER, CUT, STRENGTH), 
    // end
    },
    [SHUCKLE-1] = {
        .dexNo = SHUCKLE , // 213
        .stats = { 20,  10, 230,  05,  10, 230}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {BUG, ROCK }, // type
        .catchRate = 190 , // catch rate
        .exp = 80 , // base exp
        .items = {BERRY, BERRY }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_BUG, EGG_BUG ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, ROLLOUT, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, ENDURE, FRUSTRATION, EARTHQUAKE, RETURN, DIG, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SLUDGE_BOMB, SANDSTORM, DEFENSE_CURL, REST, ATTRACT, STRENGTH, FLASH), 
    // end
    },
    [HERACROSS-1] = {
        .dexNo = HERACROSS , // 214
        .stats = { 80, 125,  75,  85,  40,  95}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {BUG, FIGHTING }, // type
        .catchRate = 45 , // catch rate
        .exp = 200 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 25 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_BUG, EGG_BUG ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, ENDURE, FRUSTRATION, EARTHQUAKE, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, DETECT, REST, ATTRACT, THIEF, FURY_CUTTER, CUT, STRENGTH), 
    // end
    },
    [SNEASEL-1] = {
        .dexNo = SNEASEL , // 215
        .stats = { 55,  95,  55, 115,  35,  75}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {DARK, ICE }, // type
        .catchRate = 60 , // catch rate
        .exp = 132 , // base exp
        .items = {NO_ITEM, QUICK_CLAW }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_GROUND, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, TOXIC, ROCK_SMASH, PSYCH_UP, HIDDEN_POWER, SNORE, BLIZZARD, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, IRON_TAIL, RETURN, DIG, SHADOW_BALL, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, SWIFT, DEFENSE_CURL, DREAM_EATER, DETECT, REST, ATTRACT, THIEF, FURY_CUTTER, NIGHTMARE, CUT, SURF, STRENGTH, ICE_BEAM), 
    // end
    },
    [TEDDIURSA-1] = {
        .dexNo = TEDDIURSA , // 216
        .stats = { 60,  80,  50,  40,  50,  50}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {NORMAL, NORMAL }, // type
        .catchRate = 120 , // catch rate
        .exp = 124 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_GROUND, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, ROLLOUT, ROAR, TOXIC, ZAP_CANNON, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, ENDURE, FRUSTRATION, EARTHQUAKE, RETURN, DIG, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, SWIFT, DEFENSE_CURL, THUNDERPUNCH, REST, ATTRACT, THIEF, FIRE_PUNCH, FURY_CUTTER, CUT, STRENGTH), 
    // end
    },
    [URSARING-1] = {
        .dexNo = URSARING , // 217
        .stats = { 90, 130,  75,  55,  75,  75}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {NORMAL, NORMAL }, // type
        .catchRate = 60 , // catch rate
        .exp = 189 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_GROUND, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, ROLLOUT, ROAR, TOXIC, ZAP_CANNON, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, PROTECT, ENDURE, FRUSTRATION, EARTHQUAKE, RETURN, DIG, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, SWIFT, DEFENSE_CURL, THUNDERPUNCH, REST, ATTRACT, THIEF, FIRE_PUNCH, FURY_CUTTER, CUT, STRENGTH), 
    // end
    },
    [SLUGMA-1] = {
        .dexNo = SLUGMA , // 218
        .stats = { 40,  40,  40,  20,  70,  40}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {FIRE, FIRE }, // type
        .catchRate = 190 , // catch rate
        .exp = 78 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_INDETERMINATE, EGG_INDETERMINATE ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, ROLLOUT, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, ENDURE, FRUSTRATION, RETURN, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, FIRE_BLAST, DEFENSE_CURL, REST, ATTRACT, FLAMETHROWER), 
    // end
    },
    [MAGCARGO-1] = {
        .dexNo = MAGCARGO , // 219
        .stats = { 50,  50, 120,  30,  80,  80}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {FIRE, ROCK }, // type
        .catchRate = 75 , // catch rate
        .exp = 154 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_INDETERMINATE, EGG_INDETERMINATE ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, ROLLOUT, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, PROTECT, ENDURE, FRUSTRATION, EARTHQUAKE, RETURN, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, FIRE_BLAST, DEFENSE_CURL, REST, ATTRACT, STRENGTH, FLAMETHROWER), 
    // end
    },
    [SWINUB-1] = {
        .dexNo = SWINUB , // 220
        .stats = { 50,  50,  40,  50,  30,  30}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {ICE, GROUND }, // type
        .catchRate = 225 , // catch rate
        .exp = 78 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_GROUND, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, ROAR, TOXIC, ROCK_SMASH, HIDDEN_POWER, SNORE, BLIZZARD, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, EARTHQUAKE, RETURN, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, DEFENSE_CURL, DETECT, REST, ATTRACT, STRENGTH, ICE_BEAM), 
    // end
    },
    [PILOSWINE-1] = {
        .dexNo = PILOSWINE , // 221
        .stats = {100, 100,  80,  50,  60,  60}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {ICE, GROUND }, // type
        .catchRate = 75 , // catch rate
        .exp = 160 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_GROUND, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, ROAR, TOXIC, ROCK_SMASH, HIDDEN_POWER, SNORE, BLIZZARD, HYPER_BEAM, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, EARTHQUAKE, RETURN, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, DEFENSE_CURL, DETECT, REST, ATTRACT, STRENGTH, ICE_BEAM), 
    // end
    },
    [CORSOLA-1] = {
        .dexNo = CORSOLA , // 222
        .stats = { 55,  55,  85,  35,  65,  85}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {WATER, ROCK }, // type
        .catchRate = 60 , // catch rate
        .exp = 113 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F75 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_WATER_1, EGG_WATER_3 ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, ROLLOUT, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, EARTHQUAKE, RETURN, PSYCHIC_M, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SANDSTORM, DEFENSE_CURL, REST, ATTRACT, SURF, STRENGTH, WHIRLPOOL, ICE_BEAM), 
    // end
    },
    [REMORAID-1] = {
        .dexNo = REMORAID , // 223
        .stats = { 35,  65,  35,  65,  65,  35}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {WATER, WATER }, // type
        .catchRate = 190 , // catch rate
        .exp = 78 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_WATER_1, EGG_WATER_2 ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, HIDDEN_POWER, SNORE, HYPER_BEAM, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, RETURN, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, DEFENSE_CURL, REST, ATTRACT, THIEF, SURF, WHIRLPOOL, FLAMETHROWER, ICE_BEAM), 
    // end
    },
    [OCTILLERY-1] = {
        .dexNo = OCTILLERY , // 224
        .stats = { 75, 105,  75,  45, 105,  75}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {WATER, WATER }, // type
        .catchRate = 75 , // catch rate
        .exp = 164 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_WATER_1, EGG_WATER_2 ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, HIDDEN_POWER, SNORE, HYPER_BEAM, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, RETURN, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, DEFENSE_CURL, REST, ATTRACT, THIEF, SURF, WHIRLPOOL, FLAMETHROWER, ICE_BEAM), 
    // end
    },
    [DELIBIRD-1] = {
        .dexNo = DELIBIRD , // 225
        .stats = { 45,  55,  45,  75,  65,  45}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {ICE, FLYING }, // type
        .catchRate = 45 , // catch rate
        .exp = 183 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_WATER_1, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, HIDDEN_POWER, SNORE, BLIZZARD, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, RETURN, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, DETECT, REST, ATTRACT, THIEF, FLY, ICE_BEAM), 
    // end
    },
    [MANTINE-1] = {
        .dexNo = MANTINE , // 226
        .stats = { 65,  40,  70,  70,  80, 140}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {WATER, FLYING }, // type
        .catchRate = 25 , // catch rate
        .exp = 168 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 25 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_WATER_1, EGG_WATER_1 ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, HIDDEN_POWER, SNORE, BLIZZARD, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, RETURN, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, REST, ATTRACT, SURF, WHIRLPOOL, WATERFALL, ICE_BEAM), 
    // end
    },
    [SKARMORY-1] = {
        .dexNo = SKARMORY , // 227
        .stats = { 65,  80, 140,  70,  40,  70}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {STEEL, FLYING }, // type
        .catchRate = 25 , // catch rate
        .exp = 168 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 25 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_FLYING, EGG_FLYING ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, ENDURE, FRUSTRATION, RETURN, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SANDSTORM, SWIFT, DETECT, REST, ATTRACT, THIEF, STEEL_WING, CUT, FLY), 
    // end
    },
    [HOUNDOUR-1] = {
        .dexNo = HOUNDOUR , // 228
        .stats = { 45,  60,  30,  65,  80,  50}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {DARK, FIRE }, // type
        .catchRate = 120 , // catch rate
        .exp = 114 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_GROUND, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, ROAR, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, ENDURE, FRUSTRATION, SOLARBEAM, IRON_TAIL, RETURN, SHADOW_BALL, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SLUDGE_BOMB, FIRE_BLAST, SWIFT, DREAM_EATER, DETECT, REST, ATTRACT, THIEF, NIGHTMARE, FLAMETHROWER), 
    // end
    },
    [HOUNDOOM-1] = {
        .dexNo = HOUNDOOM , // 229
        .stats = { 75,  90,  50,  95, 110,  80}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {DARK, FIRE }, // type
        .catchRate = 45 , // catch rate
        .exp = 204 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_GROUND, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, ROAR, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, PROTECT, ENDURE, FRUSTRATION, SOLARBEAM, IRON_TAIL, RETURN, SHADOW_BALL, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SLUDGE_BOMB, FIRE_BLAST, SWIFT, DREAM_EATER, DETECT, REST, ATTRACT, THIEF, NIGHTMARE, STRENGTH, FLAMETHROWER), 
    // end
    },
    [KINGDRA-1] = {
        .dexNo = KINGDRA , // 230
        .stats = { 75,  95,  95,  85,  95,  95}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {WATER, DRAGON }, // type
        .catchRate = 45 , // catch rate
        .exp = 207 , // base exp
        .items = {NO_ITEM, DRAGON_SCALE }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_WATER_1, EGG_DRAGON ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, HIDDEN_POWER, SNORE, BLIZZARD, HYPER_BEAM, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, DRAGONBREATH, RETURN, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, REST, ATTRACT, SURF, WHIRLPOOL, WATERFALL, ICE_BEAM), 
    // end
    },
    [PHANPY-1] = {
        .dexNo = PHANPY , // 231
        .stats = { 90,  60,  60,  40,  40,  40}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {GROUND, GROUND }, // type
        .catchRate = 120 , // catch rate
        .exp = 124 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_GROUND, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, ROLLOUT, ROAR, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, ENDURE, FRUSTRATION, EARTHQUAKE, RETURN, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SANDSTORM, DEFENSE_CURL, REST, ATTRACT, STRENGTH), 
    // end
    },
    [DONPHAN-1] = {
        .dexNo = DONPHAN , // 232
        .stats = { 90, 120, 120,  50,  60,  60}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {GROUND, GROUND }, // type
        .catchRate = 60 , // catch rate
        .exp = 189 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_GROUND, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, ROLLOUT, ROAR, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, PROTECT, ENDURE, FRUSTRATION, EARTHQUAKE, RETURN, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SANDSTORM, DEFENSE_CURL, REST, ATTRACT, STRENGTH), 
    // end
    },
    [PORYGON2-1] = {
        .dexNo = PORYGON2 , // 233
        .stats = { 85,  80,  90,  60, 105,  95}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {NORMAL, NORMAL }, // type
        .catchRate = 45 , // catch rate
        .exp = 180 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_UNKNOWN , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_MINERAL, EGG_MINERAL ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, ZAP_CANNON, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SNORE, BLIZZARD, HYPER_BEAM, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, IRON_TAIL, THUNDER, RETURN, PSYCHIC_M, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, DEFENSE_CURL, DREAM_EATER, REST, THIEF, NIGHTMARE, FLASH, THUNDERBOLT, ICE_BEAM), 
    // end
    },
    [STANTLER-1] = {
        .dexNo = STANTLER , // 234
        .stats = { 73,  95,  62,  85,  85,  65}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {NORMAL, NORMAL }, // type
        .catchRate = 45 , // catch rate
        .exp = 165 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_GROUND, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, ROAR, TOXIC, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, EARTHQUAKE, RETURN, PSYCHIC_M, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, DREAM_EATER, DETECT, REST, ATTRACT, THIEF, NIGHTMARE, FLASH), 
    // end
    },
    [SMEARGLE-1] = {
        .dexNo = SMEARGLE , // 235
        .stats = { 55,  20,  35,  75,  20,  45}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {NORMAL, NORMAL }, // type
        .catchRate = 45 , // catch rate
        .exp = 106 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_GROUND, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = { NULL },
    // end
    },
    [TYROGUE-1] = {
        .dexNo = TYROGUE , // 236
        .stats = { 35,  35,  35,  35,  35,  35}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {FIGHTING, FIGHTING }, // type
        .catchRate = 75 , // catch rate
        .exp = 91 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F0 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 25 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_NONE, EGG_NONE ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, ENDURE, FRUSTRATION, RETURN, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, DETECT, REST, ATTRACT, THIEF, STRENGTH), 
    // end
    },
    [HITMONTOP-1] = {
        .dexNo = HITMONTOP , // 237
        .stats = { 50,  95,  95,  70,  35, 110}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {FIGHTING, FIGHTING }, // type
        .catchRate = 45 , // catch rate
        .exp = 138 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F0 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 25 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_HUMANSHAPE, EGG_HUMANSHAPE ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, ENDURE, FRUSTRATION, RETURN, DIG, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SWIFT, DETECT, REST, ATTRACT, THIEF, STRENGTH), 
    // end
    },
    [SMOOCHUM-1] = {
        .dexNo = SMOOCHUM , // 238
        .stats = { 45,  30,  15,  65,  85,  65}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {ICE, PSYCHIC_TYPE }, // type
        .catchRate = 45 , // catch rate
        .exp = 87 , // base exp
        .items = {ICE_BERRY, ICE_BERRY }, // items
        .gender = GENDER_F100 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 25 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_NONE, EGG_NONE ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, CURSE, TOXIC, PSYCH_UP, HIDDEN_POWER, SWEET_SCENT, SNORE, BLIZZARD, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, RETURN, PSYCHIC_M, SHADOW_BALL, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, DREAM_EATER, REST, ATTRACT, THIEF, NIGHTMARE, ICE_BEAM), 
    // end
    },
    [ELEKID-1] = {
        .dexNo = ELEKID , // 239
        .stats = { 45,  63,  37,  95,  65,  55}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {ELECTRIC, ELECTRIC }, // type
        .catchRate = 45 , // catch rate
        .exp = 106 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F25 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 25 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_NONE, EGG_NONE ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, TOXIC, ZAP_CANNON, HIDDEN_POWER, SNORE, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, THUNDER, RETURN, PSYCHIC_M, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, SWIFT, THUNDERPUNCH, DETECT, REST, ATTRACT, THIEF, FIRE_PUNCH, FLASH, THUNDERBOLT), 
    // end
    },
    [MAGBY-1] = {
        .dexNo = MAGBY , // 240
        .stats = { 45,  75,  37,  83,  70,  55}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {FIRE, FIRE }, // type
        .catchRate = 45 , // catch rate
        .exp = 117 , // base exp
        .items = {BURNT_BERRY, BURNT_BERRY }, // items
        .gender = GENDER_F25 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 25 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_NONE, EGG_NONE ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, TOXIC, HIDDEN_POWER, SUNNY_DAY, SNORE, PROTECT, ENDURE, FRUSTRATION, IRON_TAIL, RETURN, PSYCHIC_M, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, FIRE_BLAST, THUNDERPUNCH, DETECT, REST, ATTRACT, THIEF, FIRE_PUNCH, FLAMETHROWER), 
    // end
    },
    [MILTANK-1] = {
        .dexNo = MILTANK , // 241
        .stats = { 95,  80, 105, 100,  40,  70}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {NORMAL, NORMAL }, // type
        .catchRate = 45 , // catch rate
        .exp = 200 , // base exp
        .items = {MOOMOO_MILK, MOOMOO_MILK }, // items
        .gender = GENDER_F100 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 20 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_GROUND, EGG_GROUND ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, ROLLOUT, TOXIC, ZAP_CANNON, ROCK_SMASH, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SWEET_SCENT, SNORE, BLIZZARD, HYPER_BEAM, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, IRON_TAIL, THUNDER, EARTHQUAKE, RETURN, SHADOW_BALL, MUD_SLAP, DOUBLE_TEAM, ICE_PUNCH, SWAGGER, SLEEP_TALK, SANDSTORM, DEFENSE_CURL, THUNDERPUNCH, REST, ATTRACT, FIRE_PUNCH, SURF, STRENGTH, THUNDERBOLT, ICE_BEAM), 
    // end
    },
    [BLISSEY-1] = {
        .dexNo = BLISSEY , // 242
        .stats = {255,  10,  10,  55,  75, 135}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {NORMAL, NORMAL }, // type
        .catchRate = 30 , // catch rate
        .exp = 255 , // base exp
        .items = {NO_ITEM, LUCKY_EGG }, // items
        .gender = GENDER_F100 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 40 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_FAIRY, EGG_FAIRY ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, ROLLOUT, TOXIC, ZAP_CANNON, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, BLIZZARD, HYPER_BEAM, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, SOLARBEAM, THUNDER, RETURN, PSYCHIC_M, SHADOW_BALL, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SANDSTORM, FIRE_BLAST, DEFENSE_CURL, DREAM_EATER, REST, ATTRACT, STRENGTH, FLASH, FLAMETHROWER, THUNDERBOLT, ICE_BEAM), 
    // end
    },
    [RAIKOU-1] = {
        .dexNo = RAIKOU , // 243
        .stats = { 90,  85,  75, 115, 115, 100}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {ELECTRIC, ELECTRIC }, // type
        .catchRate = 3 , // catch rate
        .exp = 216 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_UNKNOWN , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 80 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_NONE, EGG_NONE ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, ROAR, TOXIC, ZAP_CANNON, ROCK_SMASH, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, IRON_TAIL, THUNDER, RETURN, DIG, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SANDSTORM, SWIFT, DETECT, REST, CUT, STRENGTH, FLASH, THUNDERBOLT), 
    // end
    },
    [ENTEI-1] = {
        .dexNo = ENTEI , // 244
        .stats = {115, 115,  85, 100,  90,  75}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {FIRE, FIRE }, // type
        .catchRate = 3 , // catch rate
        .exp = 217 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_UNKNOWN , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 80 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_NONE, EGG_NONE ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, ROAR, TOXIC, ROCK_SMASH, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, SOLARBEAM, IRON_TAIL, RETURN, DIG, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SANDSTORM, FIRE_BLAST, SWIFT, DETECT, REST, CUT, STRENGTH, FLASH, FLAMETHROWER), 
    // end
    },
    [SUICUNE-1] = {
        .dexNo = SUICUNE , // 245
        .stats = {100,  75, 115,  85,  90, 115}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {WATER, WATER }, // type
        .catchRate = 3 , // catch rate
        .exp = 215 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_UNKNOWN , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 80 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_NONE, EGG_NONE ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, ROAR, TOXIC, ROCK_SMASH, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SNORE, BLIZZARD, HYPER_BEAM, ICY_WIND, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, IRON_TAIL, RETURN, DIG, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SANDSTORM, SWIFT, DETECT, REST, CUT, SURF, WHIRLPOOL, WATERFALL, ICE_BEAM), 
    // end
    },
    [LARVITAR-1] = {
        .dexNo = LARVITAR , // 246
        .stats = { 50,  64,  50,  41,  45,  50}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {ROCK, GROUND }, // type
        .catchRate = 45 , // catch rate
        .exp = 67 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 40 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_MONSTER, EGG_MONSTER ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, EARTHQUAKE, RETURN, DIG, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SANDSTORM, DETECT, REST, ATTRACT), 
    // end
    },
    [PUPITAR-1] = {
        .dexNo = PUPITAR , // 247
        .stats = { 70,  84,  70,  51,  65,  70}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {ROCK, GROUND }, // type
        .catchRate = 45 , // catch rate
        .exp = 144 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 40 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_MONSTER, EGG_MONSTER ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, TOXIC, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, EARTHQUAKE, RETURN, DIG, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SANDSTORM, DETECT, REST, ATTRACT), 
    // end
    },
    [TYRANITAR-1] = {
        .dexNo = TYRANITAR , // 248
        .stats = {100, 134, 110,  61,  95, 100}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {ROCK, DARK }, // type
        .catchRate = 45 , // catch rate
        .exp = 218 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_F50 , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 40 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_MONSTER, EGG_MONSTER ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( DYNAMICPUNCH, HEADBUTT, CURSE, ROAR, TOXIC, ROCK_SMASH, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, PROTECT, RAIN_DANCE, ENDURE, FRUSTRATION, IRON_TAIL, DRAGONBREATH, EARTHQUAKE, RETURN, DIG, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SANDSTORM, FIRE_BLAST, DETECT, REST, ATTRACT, FIRE_PUNCH, FURY_CUTTER, NIGHTMARE, CUT, SURF, STRENGTH, FLAMETHROWER, THUNDERBOLT, ICE_BEAM), 
    // end
    },
    [LUGIA-1] = {
        .dexNo = LUGIA , // 249
        .stats = {106,  90, 130, 110,  90, 154}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {PSYCHIC_TYPE, FLYING }, // type
        .catchRate = 3 , // catch rate
        .exp = 220 , // base exp
        .items = {NO_ITEM, NO_ITEM }, // items
        .gender = GENDER_UNKNOWN , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 120 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_NONE, EGG_NONE ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( HEADBUTT, CURSE, ROAR, TOXIC, ZAP_CANNON, ROCK_SMASH, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SNORE, BLIZZARD, HYPER_BEAM, ICY_WIND, PROTECT, RAIN_DANCE, GIGA_DRAIN, ENDURE, FRUSTRATION, IRON_TAIL, DRAGONBREATH, THUNDER, EARTHQUAKE, RETURN, PSYCHIC_M, SHADOW_BALL, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SANDSTORM, SWIFT, DREAM_EATER, DETECT, REST, STEEL_WING, NIGHTMARE, FLY, SURF, STRENGTH, WHIRLPOOL, WATERFALL, THUNDERBOLT, ICE_BEAM), 
    // end
    },
    [HO_OH-1] = {
        .dexNo = HO_OH , // 250
        .stats = {106, 130,  90,  90, 110, 154}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {FIRE, FLYING }, // type
        .catchRate = 3 , // catch rate
        .exp = 220 , // base exp
        .items = {SACRED_ASH, SACRED_ASH }, // items
        .gender = GENDER_UNKNOWN , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 120 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_NONE, EGG_NONE ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, ROAR, TOXIC, ZAP_CANNON, ROCK_SMASH, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SNORE, HYPER_BEAM, PROTECT, RAIN_DANCE, GIGA_DRAIN, ENDURE, FRUSTRATION, SOLARBEAM, DRAGONBREATH, THUNDER, EARTHQUAKE, RETURN, PSYCHIC_M, SHADOW_BALL, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SANDSTORM, FIRE_BLAST, SWIFT, DREAM_EATER, DETECT, REST, STEEL_WING, NIGHTMARE, FLY, STRENGTH, FLASH, FLAMETHROWER, THUNDERBOLT), 
    // end
    },
    [CELEBI-1] = {
        .dexNo = CELEBI , // 251
        .stats = {100, 100, 100, 100, 100, 100}, 
    //   hp  atk  def  spd  sat  sdf
        .types = {PSYCHIC_TYPE, GRASS }, // type
        .catchRate = 45 , // catch rate
        .exp = 64 , // base exp
        .items = {NO_ITEM, MIRACLEBERRY }, // items
        .gender = GENDER_UNKNOWN , // gender ratio
        .unknown1 = 100 , // unknown 1
        .eggSteps = 120 , // step cycles to hatch
        .unknown2 = 5 , // unknown 2
        .unusedFrontpic = 0, .unusedBackpic = 0, // unused (beta front/back pics)
        .eggGroups = dn(EGG_NONE, EGG_NONE ), // egg groups
    // tm/hm learnset
        .TMHM = tmhm_learnset( CURSE, TOXIC, PSYCH_UP, HIDDEN_POWER, SUNNY_DAY, SWEET_SCENT, SNORE, HYPER_BEAM, PROTECT, RAIN_DANCE, GIGA_DRAIN, ENDURE, FRUSTRATION, SOLARBEAM, RETURN, PSYCHIC_M, SHADOW_BALL, MUD_SLAP, DOUBLE_TEAM, SWAGGER, SLEEP_TALK, SANDSTORM, SWIFT, DEFENSE_CURL, DREAM_EATER, DETECT, REST, NIGHTMARE, FLASH), 
    // end
    },
};

static_assert(lengthof(BasePokemonData) == NUM_POKEMON, "");
