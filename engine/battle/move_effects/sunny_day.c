#include "../../../constants.h"
#include "sunny_day.h"
#include "../effect_commands.h"
#include "../../../home/battle.h"
#include "../../../data/text/battle.h"

void BattleCommand_StartSun(void){
//  startsun
    // LD_A(WEATHER_SUN);
    // LD_addr_A(wBattleWeather);
    wram->wBattleWeather = WEATHER_SUN;
    // LD_A(5);
    // LD_addr_A(wWeatherCount);
    wram->wWeatherCount = 5;
    // CALL(aAnimateCurrentMove);
    AnimateCurrentMove();
    // LD_HL(mSunGotBrightText);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox(SunGotBrightText);

}
