#include "../../../constants.h"
#include "../../../util/scripting.h"
#include "../../../data/phone/text/buena.h"
#include "buena.h"

bool BuenaPhoneCalleeScript(script_s* s) {
    SCRIPT_BEGIN
    checkflag(ENGINE_ROCKETS_IN_RADIO_TOWER)
    iftrue_jump(BuenaPhoneScript_Rocket)
    readvar(VAR_HOUR)
    ifgreater_jump(17, BuenaPhoneScript_AfterMidnightCallee)
    scall(BuenaPhoneScript_CheckTimeOfDayCallee)
    sjump(BuenaPhoneScript_RandomCallee)
    SCRIPT_END
}
bool BuenaPhoneCallerScript(script_s* s) {
    SCRIPT_BEGIN
    checkflag(ENGINE_ROCKETS_IN_RADIO_TOWER)
    iftrue_jump(BuenaPhoneScript_Rocket)
    scall(BuenaPhoneScript_CheckTimeOfDayCaller)
    sjump(BuenaPhoneScript_RandomCaller)
    SCRIPT_END
}
bool BuenaPhoneScript_CheckTimeOfDayCallee(script_s* s) {
    SCRIPT_BEGIN
    checktime(MORN)
    iftrue(morn)
    checktime(DAY)
    iftrue(day)
    writetext(BuenaPhoneNiteAnswerText)
    promptbutton
    s_end
morn:
    writetext(BuenaPhoneMorningAnswerText)
    promptbutton
    s_end
day:
    writetext(BuenaPhoneDayAnswerText)
    promptbutton
    s_end
    SCRIPT_END
}
bool BuenaPhoneScript_AfterMidnightCallee(script_s* s) {
    SCRIPT_BEGIN
    writetext(BuenaPhoneMidnightAnswerText)
    s_end
    SCRIPT_END
}
bool BuenaPhoneScript_CheckTimeOfDayCaller(script_s* s) {
    SCRIPT_BEGIN
    readvar(VAR_HOUR)
    ifgreater_jump(17, BuenaPhoneScript_AfterMidnightCaller)
    checktime(MORN)
    iftrue(morn)
    checktime(DAY)
    iftrue(day)
    writetext(BuenaPhoneNiteText)
    promptbutton
    s_end
morn:
    writetext(BuenaPhoneMorningText)
    promptbutton
    s_end
day:
    writetext(BuenaPhoneDayText)
    promptbutton
    s_end
    SCRIPT_END
}
bool BuenaPhoneScript_AfterMidnightCaller(script_s* s) {
    SCRIPT_BEGIN
    writetext(BuenaPhoneMidnightText)
    promptbutton
    s_end
    SCRIPT_END
}
bool BuenaPhoneScript_Rocket(script_s* s) {
    SCRIPT_BEGIN
    writetext(BuenaPhoneRocketText)
    s_end
    SCRIPT_END
}
bool BuenaPhoneScript_RandomCaller(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_BEAT_ELITE_FOUR)
    iftrue(PostE4)
    srandom(11)
    goto Jumptable;
PostE4:
    srandom(14)
Jumptable:
    ifequal(0, zero)
    ifequal(1, one)
    ifequal(2, two)
    ifequal(3, three)
    ifequal(4, four)
    ifequal(5, five)
    ifequal(6, six)
    ifequal(7, seven)
    ifequal(8, eight)
    ifequal(9, nine)
    ifequal(10, ten)
    ifequal(11, eleven)
    ifequal(12, twelve)
    ifequal(13, thirteen)
zero:
    writetext(BuenaPhoneWentOutWithBenText)
    goto finish;
one:
    writetext(BuenaPhoneReceptionistText)
    goto finish;
two:
    writetext(BuenaPhoneLuckyNumberShowText)
    goto finish;
three:
    writetext(BuenaPhoneStressedFromWorkText)
    goto finish;
four:
    writetext(BuenaPhoneProfessorOakText)
    goto finish;
five:
    writetext(BuenaPhoneGotAColdText)
    goto finish;
six:
    writetext(BuenaPhoneRadioCardQuestionsText)
    goto finish;
seven:
    writetext(BuenaPhonePikachuFanClubText)
    goto finish;
eight:
    writetext(BuenaPhoneRadioTowerDirectorText)
    goto finish;
nine:
    writetext(BuenaPhoneWhenDoYouRelaxText)
    goto finish;
ten:
    writetext(BuenaPhoneStarterPokemonText)
    goto finish;
eleven:
    writetext(BuenaPhoneCompanyVacationText)
    goto finish;
twelve:
    writetext(BuenaPhoneBenAndFernText)
    goto finish;
thirteen:
    writetext(BuenaPhoneGoingShoppingText)
finish:
    s_end
    SCRIPT_END
}
bool BuenaPhoneScript_RandomCallee(script_s* s) {
    SCRIPT_BEGIN
    srandom(3)
    ifequal(0, zero)
    ifequal(1, one)
    ifequal(2, two)
zero:
    writetext(BuenaPhoneFavoriteSlotMachineAnswerText)
    s_end
one:
    writetext(BuenaPhonePokegearAnswerText)
    s_end
two:
    writetext(BuenaPhoneCoopedUpInRadioTowerAnswerText)
    s_end
//INCLUDE "data/phone/text/buena.asm"
    SCRIPT_END
}
