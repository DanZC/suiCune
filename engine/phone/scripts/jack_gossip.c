#include "../../../constants.h"
#include "../../../util/scripting.h"
#include "generic_caller.h"
#include "hangups.h"
#include "../../../data/phone/text/jack_caller.h"

bool JackTriviaScript(script_s* s) {
    SCRIPT_BEGIN
    srandom(11)
    ifequal(0, Thunder)
    ifequal(1, Rollout)
    ifequal(2, Solarbeam)
    ifequal(3, Stomp)
    ifequal(4, Gust)
    ifequal(5, Twister)
    ifequal(6, Earthquake)
    ifequal(7, Magnitude)
    ifequal(8, Sandstorm)
    ifequal(9, SunnyDay)
    ifequal(10, RainDance)
Thunder:
    writetext(JackThunderTriviaText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
Rollout:
    writetext(JackRolloutTriviaText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
Solarbeam:
    writetext(JackSolarbeamTriviaText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
Stomp:
    writetext(JackStompTriviaText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
Gust:
    writetext(JackGustTriviaText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
Twister:
    writetext(JackTwisterTriviaText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
Earthquake:
    writetext(JackEarthquakeTriviaText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
Magnitude:
    writetext(JackMagnitudeTriviaText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
Sandstorm:
    writetext(JackSandstormTriviaText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
SunnyDay:
    writetext(JackSunnyDayTriviaText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
RainDance:
    writetext(JackRainDanceTriviaText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
    SCRIPT_END
}
