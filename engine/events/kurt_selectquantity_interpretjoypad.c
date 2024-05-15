#include "../../constants.h"
#include "kurt_selectquantity_interpretjoypad.h"
#include "../items/buy_sell_toss.h"

u8_flag_s Kurt_SelectQuantity_InterpretJoypad(void){
    // CALL(aBuySellToss_InterpretJoypad);
    u8_flag_s res = BuySellToss_InterpretJoypad();
    // LD_B_A;
    // RET;
    return res;
}
