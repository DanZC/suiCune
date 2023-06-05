#include "../../constants.h"

struct SpecialCall {
    bool (*condition)(void);
    uint8_t contact;
    const uint8_t* const script;
};

bool SpecialCallOnlyWhenOutside(void);
bool SpecialCallWhereverYouAre(void);
extern const uint8_t ElmPhoneCallerScript[];
extern const uint8_t BikeShopPhoneCallerScript[];
extern const uint8_t MomPhoneLectureScript[];

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

#if defined(__cplusplus) || defined(_MSC_VER)
static_assert(lengthof(SpecialPhoneCallList) == NUM_SPECIALCALLS + 1, "");
#else 
_Static_assert(lengthof(SpecialPhoneCallList) == NUM_SPECIALCALLS + 1, "");
#endif