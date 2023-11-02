#include "../../../constants.h"
#include "../../../util/scripting.h"
#include "../../../data/phone/text/bike_shop.h"

bool BikeShopPhoneCallerScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(BikeShopPhoneCallerText)
    clearflag(ENGINE_BIKE_SHOP_CALL_ENABLED)
    specialphonecall(SPECIALCALL_NONE)
    s_end
    SCRIPT_END
}
