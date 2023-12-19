#include "../../../constants.h"
#include "splash.h"
#include "../effect_commands.h"

void BattleCommand_Splash(void){
    // CALL(aAnimateCurrentMove);
    AnimateCurrentMove();
    // FARCALL(aStubbedTrainerRankings_Splash);
    // JP(mPrintNothingHappened);
    return PrintNothingHappened();
}
