#include "../../../constants.h"
#include "rain_dance.h"
#include "../effect_commands.h"
#include "../../../home/battle.h"
#include "../../../data/text/battle.h"

void BattleCommand_StartRain(void){
//  startrain
    // LD_A(WEATHER_RAIN);
    // LD_addr_A(wBattleWeather);
    wram->wBattleWeather = WEATHER_RAIN;
    // LD_A(5);
    // LD_addr_A(wWeatherCount);
    wram->wWeatherCount = 5;
    // CALL(aAnimateCurrentMove);
    AnimateCurrentMove();
    // LD_HL(mDownpourText);
    // JP(mStdBattleTextbox);
    StdBattleTextbox_Conv2(DownpourText);

}
