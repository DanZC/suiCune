#include "../../../constants.h"
#include "sandstorm.h"
#include "../effect_commands.h"
#include "../../../home/battle.h"
#include "../../../data/text/battle.h"

void BattleCommand_StartSandstorm(void){
//  startsandstorm

    // LD_A_addr(wBattleWeather);
    // CP_A(WEATHER_SANDSTORM);
    // IF_Z goto failed;
    if(wram->wBattleWeather == WEATHER_SANDSTORM) {
    // failed:
        // CALL(aAnimateFailedMove);
        AnimateFailedMove();
        // JP(mPrintButItFailed);
        return PrintButItFailed();
    }

    // LD_A(WEATHER_SANDSTORM);
    // LD_addr_A(wBattleWeather);
    wram->wBattleWeather = WEATHER_SANDSTORM;
    // LD_A(5);
    // LD_addr_A(wWeatherCount);
    wram->wWeatherCount = 5;
    // CALL(aAnimateCurrentMove);
    AnimateCurrentMove();
    // LD_HL(mSandstormBrewedText);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox_Conv2(SandstormBrewedText);
}
