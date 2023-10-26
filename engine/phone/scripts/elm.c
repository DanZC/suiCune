#include "../../../constants.h"
#include "../../../util/scripting.h"
#include "../../../data/phone/text/elm.h"
#include "elm.h"

bool ElmPhoneCalleeScript(script_s* s) {
    SCRIPT_BEGIN
    readvar(VAR_SPECIALPHONECALL)
    ifequal(SPECIALCALL_POKERUS, pokerus)
    checkevent(EVENT_SHOWED_TOGEPI_TO_ELM)
    iftrue(discovery)
    checkevent(EVENT_GOT_TOGEPI_EGG_FROM_ELMS_AIDE)
    iffalse(next)
    checkevent(EVENT_TOGEPI_HATCHED)
    iftrue(egghatched)
next:
    checkevent(EVENT_GOT_TOGEPI_EGG_FROM_ELMS_AIDE)
    iftrue(eggunhatched)
    checkevent(EVENT_ELMS_AIDE_IN_LAB)
    iftrue(assistant)
    checkevent(EVENT_GAVE_MYSTERY_EGG_TO_ELM)
    iftrue(checkingegg)
    checkevent(EVENT_ELM_CALLED_ABOUT_STOLEN_POKEMON)
    iftrue(stolen)
    checkevent(EVENT_GOT_MYSTERY_EGG_FROM_MR_POKEMON)
    iftrue(sawmrpokemon)
    writetext(ElmPhoneHealYourMonText)
    s_end
sawmrpokemon:
    writetext(ElmPhoneSawMrPokemonText)
    s_end
stolen:
    writetext(ElmPhonePokemonStolenText)
    s_end
checkingegg:
    writetext(ElmPhoneCheckingTheEggText)
    s_end
assistant:
    writetext(ElmPhoneAssistantText)
    s_end
eggunhatched:
    writetext(ElmPhoneHowIsTheEggText)
    s_end
egghatched:
    writetext(ElmPhoneEggHatchedText)
    setevent(EVENT_TOLD_ELM_ABOUT_TOGEPI_OVER_THE_PHONE)
    s_end
discovery:
    srandom(2)
    ifequal(0, nextdiscovery)
    writetext(ElmPhoneDiscoveredHatchTimeText)
    s_end
nextdiscovery:
    writetext(ElmPhoneInvestigatingEggMovesText)
    s_end
pokerus:
    writetext(ElmPhoneDiscoveredPokerusText)
    specialphonecall(SPECIALCALL_NONE)
    s_end
    SCRIPT_END
}
bool ElmPhoneCallerScript(script_s* s) {
    SCRIPT_BEGIN
    readvar(VAR_SPECIALPHONECALL)
    ifequal(SPECIALCALL_ROBBED, disaster)
    ifequal(SPECIALCALL_ASSISTANT, assistant)
    ifequal(SPECIALCALL_WEIRDBROADCAST, rocket)
    ifequal(SPECIALCALL_SSTICKET, gift)
    ifequal(SPECIALCALL_MASTERBALL, gift)
    writetext(ElmPhoneDiscoveredPokerusText)
    specialphonecall(SPECIALCALL_NONE)
    s_end
disaster:
    writetext(ElmPhoneDisasterText)
    specialphonecall(SPECIALCALL_NONE)
    setevent(EVENT_ELM_CALLED_ABOUT_STOLEN_POKEMON)
    s_end
assistant:
    writetext(ElmPhoneEggAssistantText)
    specialphonecall(SPECIALCALL_NONE)
    clearevent(EVENT_ELMS_AIDE_IN_VIOLET_POKEMON_CENTER)
    setevent(EVENT_ELMS_AIDE_IN_LAB)
    s_end
rocket:
    writetext(ElmPhoneRadioTowerRocketTakeoverText)
    specialphonecall(SPECIALCALL_NONE)
    s_end
gift:
    writetext(ElmPhoneGiftText)
    specialphonecall(SPECIALCALL_NONE)
    s_end
neat: // unreferenced:
    writetext(ElmPhoneGotAholdOfSomethingNeatText)
    specialphonecall(SPECIALCALL_NONE)
    s_end
    SCRIPT_END
}
