#include "../../../constants.h"
#include "../../../util/scripting.h"
#include "generic_caller.h"
#include "hangups.h"
#include "../../../data/phone/text/chad_caller.h"

bool ChadOakGossipScript(script_s* s) {
    SCRIPT_BEGIN
    srandom(10)
    ifequal(0, Blue)
    ifequal(1, Daisy)
    ifequal(2, ProfElm)
    ifequal(3, Dream)
    ifequal(4, Kurt)
    ifequal(5, League)
    ifequal(6, RadioShow)
    ifequal(7, Battling)
    ifequal(8, DaisyTea)
    ifequal(9, Traveled)
Blue:
    writetext(ChadBlueGossipText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
Daisy:
    writetext(ChadDaisyGossipText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
ProfElm:
    writetext(ChadProfElmGossipText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
Dream:
    writetext(ChadProfOaksDreamGossipText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
Kurt:
    writetext(ChadKurtGossipText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
League:
    writetext(ChadLeagueGossipText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
RadioShow:
    writetext(ChadPokemonTalkGossipText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
Battling:
    writetext(ChadProfOakTrainerGossipText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
DaisyTea:
    writetext(ChadDaisyTeaGossipText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
Traveled:
    writetext(ChadProfOakTravelingGossipText)
    promptbutton
    sjump(PhoneScript_HangUpText_Male)
    SCRIPT_END
}
