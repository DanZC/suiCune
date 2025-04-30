#include "../../constants.h"
#include "../../engine/phone/scripts/elm.h"
#include "../../engine/phone/scripts/mom.h"
#include "../../engine/phone/scripts/bike_shop.h"
#include "../../engine/phone/phone.h"
#include "special_calls.h"

const struct SpecialCall SpecialPhoneCallList[] = {
    [SPECIALCALL_NONE]           = {SpecialCallOnlyWhenOutside, PHONECONTACT_ELM,      ElmPhoneCallerScript},
    [SPECIALCALL_POKERUS]        = {SpecialCallOnlyWhenOutside, PHONECONTACT_ELM,      ElmPhoneCallerScript},
    [SPECIALCALL_ROBBED]         = {SpecialCallOnlyWhenOutside, PHONECONTACT_ELM,      ElmPhoneCallerScript},
    [SPECIALCALL_ASSISTANT]      = {SpecialCallOnlyWhenOutside, PHONECONTACT_ELM,      ElmPhoneCallerScript},
    [SPECIALCALL_WEIRDBROADCAST] = {SpecialCallWhereverYouAre,  PHONECONTACT_ELM,      ElmPhoneCallerScript},
    [SPECIALCALL_SSTICKET]       = {SpecialCallWhereverYouAre,  PHONECONTACT_ELM,      ElmPhoneCallerScript},
    [SPECIALCALL_BIKESHOP]       = {SpecialCallWhereverYouAre,  PHONECONTACT_BIKESHOP, BikeShopPhoneCallerScript},
    [SPECIALCALL_WORRIED]        = {SpecialCallWhereverYouAre,  PHONECONTACT_MOM,      MomPhoneLectureScript},
    [SPECIALCALL_MASTERBALL]     = {SpecialCallOnlyWhenOutside, PHONECONTACT_ELM,      ElmPhoneCallerScript},
};

static_assert(lengthof(SpecialPhoneCallList) == NUM_SPECIALCALLS + 1, "");
