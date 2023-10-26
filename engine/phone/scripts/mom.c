#include "../../../constants.h"
#include "../../../util/scripting.h"
#include "../../../data/phone/text/mom.h"
#include "mom.h"

bool MomPhoneCalleeScript(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_TALKED_TO_MOM_AFTER_MYSTERY_EGG_QUEST)
    iftrue(started_quest)
    checkevent(EVENT_DUDE_TALKED_TO_YOU)
    iftrue_jump(MomPhoneLectureScript)
    checkevent(EVENT_GAVE_MYSTERY_EGG_TO_ELM)
    iftrue_jump(MomPhoneNoGymQuestScript)
    checkevent(EVENT_GOT_A_POKEMON_FROM_ELM)
    iftrue_jump(MomPhoneNoPokedexScript)
    sjump(MomPhoneNoPokemonScript)
started_quest:
    checkevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_8)
    iftrue_jump(MomPhoneHangUpScript)
    writetext(MomPhoneGreetingText)
    promptbutton
    getcurlandmarkname(STRING_BUFFER_3)
    readvar(VAR_ENVIRONMENT)
    ifequal_jump(TOWN, MomPhoneInTown)
    ifequal_jump(ROUTE, MomPhoneOnRoute)
    sjump(MomPhoneOther)
    SCRIPT_END
}
bool MomPhoneLandmark(script_s* s) {
    SCRIPT_BEGIN
    writetext(MomPhoneLandmarkText)
    promptbutton
    sjump(MomSavingMoney)
    SCRIPT_END
}
bool MomPhoneInTown(script_s* s) {
    SCRIPT_BEGIN
    readvar(VAR_MAPGROUP)
    ifequal(GROUP_NEW_BARK_TOWN, newbark)
    ifequal(GROUP_CHERRYGROVE_CITY, cherrygrove)
    ifequal(GROUP_VIOLET_CITY, violet)
    ifequal(GROUP_AZALEA_TOWN, azalea)
    ifequal(GROUP_GOLDENROD_CITY, goldenrod)
    writetext(MomPhoneGenericAreaText)
    promptbutton
    sjump(MomSavingMoney)
newbark:
    writetext(MomPhoneNewBarkText)
    promptbutton
    sjump(MomSavingMoney)
cherrygrove:
    writetext(MomPhoneCherrygroveText)
    promptbutton
    sjump(MomSavingMoney)
violet:
    getlandmarkname(STRING_BUFFER_4, LANDMARK_SPROUT_TOWER)
    sjump(MomPhoneLandmark)
azalea:
    getlandmarkname(STRING_BUFFER_4, LANDMARK_SLOWPOKE_WELL)
    sjump(MomPhoneLandmark)
goldenrod:
    getlandmarkname(STRING_BUFFER_4, LANDMARK_RADIO_TOWER)
    sjump(MomPhoneLandmark)
    SCRIPT_END
}
bool MomPhoneOnRoute(script_s* s) {
    SCRIPT_BEGIN
    writetext(MomOtherAreaText)
    promptbutton
    sjump(MomSavingMoney)
    SCRIPT_END
}
bool MomPhoneOther(script_s* s) {
    SCRIPT_BEGIN
    writetext(MomDeterminedText)
    promptbutton
    sjump(MomSavingMoney)
    SCRIPT_END
}
bool MomSavingMoney(script_s* s) {
    SCRIPT_BEGIN
    checkflag(ENGINE_MOM_SAVING_MONEY)
    iffalse(NotSaving)
    checkmoney(MOMS_MONEY, 0)
    ifequal(HAVE_MORE, SavingHasMoney)
    goto SavingNoMoney;
NotSaving:
    checkmoney(MOMS_MONEY, 0)
    ifequal(HAVE_MORE, HasMoney)
    goto NoMoney;
SavingHasMoney:
    // getmoney
    writetext(MomCheckBalanceText)
    // yesorno
    iftrue_jump(MomPhoneSaveMoneyScript)
    sjump(MomPhoneWontSaveMoneyScript)
SavingNoMoney:
    writetext(MomImportantToSaveText)
    // yesorno
    iftrue_jump(MomPhoneSaveMoneyScript)
    sjump(MomPhoneWontSaveMoneyScript)
NoMoney:
    writetext(MomYoureNotSavingText)
    // yesorno
    iftrue_jump(MomPhoneSaveMoneyScript)
    sjump(MomPhoneWontSaveMoneyScript)
HasMoney:
    // getmoney
    writetext(MomYouveSavedText)
    // yesorno
    iftrue_jump(MomPhoneSaveMoneyScript)
    sjump(MomPhoneWontSaveMoneyScript)
    SCRIPT_END
}
bool MomPhoneSaveMoneyScript(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_MOM_SAVING_MONEY)
    writetext(MomOKIllSaveText)
    promptbutton
    sjump(MomPhoneHangUpScript)
    SCRIPT_END
}
bool MomPhoneWontSaveMoneyScript(script_s* s) {
    SCRIPT_BEGIN
    clearflag(ENGINE_MOM_SAVING_MONEY)
    writetext(MomPhoneWontSaveMoneyText)
    promptbutton
    sjump(MomPhoneHangUpScript)
    SCRIPT_END
}
bool MomPhoneHangUpScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(MomPhoneHangUpText)
    s_end
    SCRIPT_END
}
bool MomPhoneNoPokemonScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(MomPhoneNoPokemonText)
    s_end
    SCRIPT_END
}
bool MomPhoneNoPokedexScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(MomPhoneNoPokedexText)
    s_end
    SCRIPT_END
}
bool MomPhoneNoGymQuestScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(MomPhoneNoGymQuestText)
    s_end
    SCRIPT_END
}
bool MomPhoneLectureScript(script_s* s) {
    SCRIPT_BEGIN
    setevent(EVENT_TALKED_TO_MOM_AFTER_MYSTERY_EGG_QUEST)
    setflag(ENGINE_MOM_ACTIVE)
    specialphonecall(SPECIALCALL_NONE)
    writetext(MomPhoneLectureText)
    // yesorno
    iftrue_jump(MomPhoneSaveMoneyScript)
    sjump(MomPhoneWontSaveMoneyScript)
    SCRIPT_END
}
