#include "../../../constants.h"
#include "splash.h"
#include "../effect_commands.h"
#include "../../../mobile/mobile_41.h"

void BattleCommand_Splash(void){
    // CALL(aAnimateCurrentMove);
    AnimateCurrentMove();
    // FARCALL(aStubbedTrainerRankings_Splash);
    StubbedTrainerRankings_Splash();
    // JP(mPrintNothingHappened);
    return PrintNothingHappened();
}
