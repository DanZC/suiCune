#include "../../../constants.h"
#include "thunder.h"
#include "../effect_commands.h"
#include "../../../home/battle.h"
#include "../../../home/battle_vars.h"
#include "../../../data/text/battle.h"

void BattleCommand_ThunderAccuracy(void){
//  thunderaccuracy

    // LD_A(BATTLE_VARS_MOVE_TYPE);
    // CALL(aGetBattleVarAddr);
    // INC_HL;
    uint8_t* hl = GetBattleVarAddr(BATTLE_VARS_MOVE_TYPE) + 1;
    // LD_A_addr(wBattleWeather);
    // CP_A(WEATHER_RAIN);
    // IF_Z goto rain;
    if(wram->wBattleWeather == WEATHER_RAIN) {
    // rain:
    // Redundant with CheckHit guranteeing hit
        // LD_hl(100 percent);
        *hl = 100 percent;
        // RET;
        return;
    }

    // CP_A(WEATHER_SUN);
    // RET_NZ ;
    else if(wram->wBattleWeather == WEATHER_SUN) {
        // LD_hl(50 percent + 1);
        *hl = 50 percent + 1;
        // RET;
        return;
    }
}
