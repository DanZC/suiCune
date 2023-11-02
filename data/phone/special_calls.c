#include "../../constants.h"
#include "../../engine/phone/scripts/elm.h"
#include "../../engine/phone/scripts/mom.h"
#include "../../engine/phone/scripts/bike_shop.h"
#include "../../engine/phone/phone.h"
#include "special_calls.h"

const struct SpecialCall SpecialPhoneCallList[] = {
    [SPECIALCALL_NONE]           = {SpecialCallOnlyWhenOutside_Conv, PHONECONTACT_ELM,      ElmPhoneCallerScript},
    [SPECIALCALL_POKERUS]        = {SpecialCallOnlyWhenOutside_Conv, PHONECONTACT_ELM,      ElmPhoneCallerScript},
    [SPECIALCALL_ROBBED]         = {SpecialCallOnlyWhenOutside_Conv, PHONECONTACT_ELM,      ElmPhoneCallerScript},
    [SPECIALCALL_ASSISTANT]      = {SpecialCallOnlyWhenOutside_Conv, PHONECONTACT_ELM,      ElmPhoneCallerScript},
    [SPECIALCALL_WEIRDBROADCAST] = {SpecialCallWhereverYouAre_Conv,  PHONECONTACT_ELM,      ElmPhoneCallerScript},
    [SPECIALCALL_SSTICKET]       = {SpecialCallWhereverYouAre_Conv,  PHONECONTACT_ELM,      ElmPhoneCallerScript},
    [SPECIALCALL_BIKESHOP]       = {SpecialCallWhereverYouAre_Conv,  PHONECONTACT_BIKESHOP, BikeShopPhoneCallerScript},
    [SPECIALCALL_WORRIED]        = {SpecialCallWhereverYouAre_Conv,  PHONECONTACT_MOM,      MomPhoneLectureScript},
    [SPECIALCALL_MASTERBALL]     = {SpecialCallOnlyWhenOutside_Conv, PHONECONTACT_ELM,      ElmPhoneCallerScript},
};

static_assert(lengthof(SpecialPhoneCallList) == NUM_SPECIALCALLS + 1, "");
