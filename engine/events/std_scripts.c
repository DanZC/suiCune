#include "../../constants.h"
#include "../../util/scripting_macros.h"
#include "../../util/scripting.h"
#include "../../engine/overworld/scripting.h"
#include "../../data/text/std_text.h"
#include "../../data/phone/text.h"
#include "overworld.h"

bool CoinVendor_IntroScript(script_s* s);
bool PokecenterNurseScript(script_s* s);
bool DifficultBookshelfScript(script_s* s);
bool PictureBookshelfScript(script_s* s);
bool MagazineBookshelfScript(script_s* s);
bool TeamRocketOathScript(script_s* s);
bool IncenseBurnerScript(script_s* s);
bool MerchandiseShelfScript(script_s* s);
bool TownMapScript(script_s* s);
bool WindowScript(script_s* s);
bool TVScript(script_s* s);
bool HomepageScript(script_s* s);
bool Radio1Script(script_s* s);
bool Radio2Script(script_s* s);
bool TrashCanScript(script_s* s);
bool StrengthBoulderScript(script_s* s);
bool SmashRockScript(script_s* s);
bool PokecenterSignScript(script_s* s);
bool MartSignScript(script_s* s);
bool GoldenrodRocketsScript(script_s* s);
bool RadioTowerRocketsScript(script_s* s);
bool ElevatorButtonScript(script_s* s);
bool DayToTextScript(script_s* s);
bool BugContestResultsWarpScript(script_s* s);
bool BugContestResultsScript(script_s* s);
bool InitializeEventsScript(script_s* s);
bool AskNumber1MScript(script_s* s);
bool AskNumber2MScript(script_s* s);
bool RegisteredNumberMScript(script_s* s);
bool NumberAcceptedMScript(script_s* s);
bool NumberDeclinedMScript(script_s* s);
bool PhoneFullMScript(script_s* s);
bool RematchMScript(script_s* s);
bool GiftMScript(script_s* s);
bool PackFullMScript(script_s* s);
bool RematchGiftMScript(script_s* s);
bool AskNumber1FScript(script_s* s);
bool AskNumber2FScript(script_s* s);
bool RegisteredNumberFScript(script_s* s);
bool NumberAcceptedFScript(script_s* s);
bool NumberDeclinedFScript(script_s* s);
bool PhoneFullFScript(script_s* s);
bool RematchFScript(script_s* s);
bool GiftFScript(script_s* s);
bool PackFullFScript(script_s* s);
bool RematchGiftFScript(script_s* s);
bool GymStatue1Script(script_s* s);
bool GymStatue2Script(script_s* s);
bool ReceiveItemScript(script_s* s);
bool ReceiveTogepiEggScript(script_s* s);
bool PCScript(script_s* s);
bool GameCornerCoinVendorScript(script_s* s);
bool HappinessCheckScript(script_s* s);

const Script_fn_t StdScripts[] = {
    PokecenterNurseScript,
    DifficultBookshelfScript,
    PictureBookshelfScript,
    MagazineBookshelfScript,
    TeamRocketOathScript,
    IncenseBurnerScript,
    MerchandiseShelfScript,
    TownMapScript,
    WindowScript,
    TVScript,
    HomepageScript, // unused
    Radio1Script,
    Radio2Script,
    TrashCanScript,
    StrengthBoulderScript,
    SmashRockScript,
    PokecenterSignScript,
    MartSignScript,
    GoldenrodRocketsScript,
    RadioTowerRocketsScript,
    ElevatorButtonScript,
    DayToTextScript,
    BugContestResultsWarpScript,
    BugContestResultsScript,
    InitializeEventsScript,
    AskNumber1MScript,
    AskNumber2MScript,
    RegisteredNumberMScript,
    NumberAcceptedMScript,
    NumberDeclinedMScript,
    PhoneFullMScript,
    RematchMScript,
    GiftMScript,
    PackFullMScript,
    RematchGiftMScript,
    AskNumber1FScript,
    AskNumber2FScript,
    RegisteredNumberFScript,
    NumberAcceptedFScript,
    NumberDeclinedFScript,
    PhoneFullFScript,
    RematchFScript,
    GiftFScript,
    PackFullFScript,
    RematchGiftFScript,
    GymStatue1Script,
    GymStatue2Script,
    ReceiveItemScript,
    ReceiveTogepiEggScript,
    PCScript,
    GameCornerCoinVendorScript,
    HappinessCheckScript,
};
bool PokecenterNurseScript(script_s* s) {
    SCRIPT_BEGIN
// EVENT_WELCOMED_TO_POKECOM_CENTER is never set
    opentext
    checktime(MORN)
    iftrue(morn)
    checktime(DAY)
    iftrue(day)
    checktime(NITE)
    iftrue(nite)
    goto ok;
morn:
    checkevent(EVENT_WELCOMED_TO_POKECOM_CENTER)
    iftrue(morn_comcenter)
    writetext(NurseMornText)
    promptbutton
    goto ok;
morn_comcenter:
    writetext(PokeComNurseMornText)
    promptbutton
    goto ok;
day:
    checkevent(EVENT_WELCOMED_TO_POKECOM_CENTER)
    iftrue(day_comcenter)
    writetext(NurseDayText)
    promptbutton
    goto ok;
day_comcenter:
    writetext(PokeComNurseDayText)
    promptbutton
    goto ok;
nite:
    checkevent(EVENT_WELCOMED_TO_POKECOM_CENTER)
    iftrue(nite_comcenter)
    writetext(NurseNiteText)
    promptbutton
    goto ok;
nite_comcenter:
    writetext(PokeComNurseNiteText)
    promptbutton
    goto ok;
ok:
    // only do this once
    clearevent(EVENT_WELCOMED_TO_POKECOM_CENTER)
    writetext(NurseAskHealText)
    yesorno
    iffalse(done)
    writetext(NurseTakePokemonText)
    pause(20)
    special(StubbedTrainerRankings_Healings)
    turnobject(LAST_TALKED, LEFT)
    pause(10)
    special(HealParty)
    playmusic(MUSIC_NONE)
    setval(HEALMACHINE_POKECENTER)
    special(HealMachineAnim)
    pause(30)
    special(RestartMapMusic)
    turnobject(LAST_TALKED, DOWN)
    pause(10)
    checkphonecall // elm already called about pokerus
    iftrue(no)
    checkflag(ENGINE_CAUGHT_POKERUS)
    iftrue(no)
    special(CheckPokerus)
    iftrue(pokerus)
no:
    writetext(NurseReturnPokemonText)
    pause(20)
done:
    writetext(NurseGoodbyeText)
    turnobject(LAST_TALKED, UP)
    pause(10)
    turnobject(LAST_TALKED, DOWN)
    pause(10)
    waitbutton
    closetext
    s_end
pokerus:
    // already cleared earlier in the script
    checkevent(EVENT_WELCOMED_TO_POKECOM_CENTER)
    iftrue(pokerus_comcenter)
    writetext(NursePokerusText)
    waitbutton
    closetext
    goto pokerus_done;
pokerus_comcenter:
    writetext(PokeComNursePokerusText)
    waitbutton
    closetext
pokerus_done:
    setflag(ENGINE_CAUGHT_POKERUS)
    specialphonecall(SPECIALCALL_POKERUS)
    s_end
    SCRIPT_END
}
bool DifficultBookshelfScript(script_s* s) {
    SCRIPT_BEGIN
    jumptext(DifficultBookshelfText)
    SCRIPT_END
}
bool PictureBookshelfScript(script_s* s) {
    SCRIPT_BEGIN
    jumptext(PictureBookshelfText)
    SCRIPT_END
}
bool MagazineBookshelfScript(script_s* s) {
    SCRIPT_BEGIN
    jumptext(MagazineBookshelfText)
    SCRIPT_END
}
bool TeamRocketOathScript(script_s* s) {
    SCRIPT_BEGIN
    jumptext(TeamRocketOathText)
    SCRIPT_END
}
bool IncenseBurnerScript(script_s* s) {
    SCRIPT_BEGIN
    jumptext(IncenseBurnerText)
    SCRIPT_END
}
bool MerchandiseShelfScript(script_s* s) {
    SCRIPT_BEGIN
    jumptext(MerchandiseShelfText)
    SCRIPT_END
}
bool TownMapScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(LookTownMapText)
    waitbutton
    special(OverworldTownMap)
    closetext
    s_end
    SCRIPT_END
}
bool WindowScript(script_s* s) {
    SCRIPT_BEGIN
    jumptext(WindowText)
    SCRIPT_END
}
bool TVScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(TVText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool HomepageScript(script_s* s) {
    SCRIPT_BEGIN
    jumptext(HomepageText)
    SCRIPT_END
}
bool Radio1Script(script_s* s) {
    SCRIPT_BEGIN
    opentext
    setval(MAPRADIO_POKEMON_CHANNEL)
    special(MapRadio)
    closetext
    s_end
    SCRIPT_END
}
// Lucky Channel
bool Radio2Script(script_s* s) {
    SCRIPT_BEGIN
    opentext
    setval(MAPRADIO_LUCKY_CHANNEL)
    special(MapRadio)
    closetext
    s_end
    SCRIPT_END
}
bool TrashCanScript(script_s* s) {
    SCRIPT_BEGIN
    jumptext(TrashCanText)
    SCRIPT_END
}
bool PCScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    special(PokemonCenterPC)
    closetext
    s_end
    SCRIPT_END
}
bool ElevatorButtonScript(script_s* s) {
    SCRIPT_BEGIN
    playsound(SFX_READ_TEXT_2)
    pause(15)
    playsound(SFX_ELEVATOR_END)
    s_end
    SCRIPT_END
}
bool StrengthBoulderScript(script_s* s) {
    SCRIPT_BEGIN
    sjump(AskStrengthScript)
    SCRIPT_END
}
bool SmashRockScript(script_s* s) {
    SCRIPT_BEGIN
    sjump(AskRockSmashScript)
    SCRIPT_END
}
bool PokecenterSignScript(script_s* s) {
    SCRIPT_BEGIN
    jumptext(PokecenterSignText)
    SCRIPT_END
}
bool MartSignScript(script_s* s) {
    SCRIPT_BEGIN
    jumptext(MartSignText)
    SCRIPT_END
}
bool DayToTextScript(script_s* s) {
    SCRIPT_BEGIN
    readvar(VAR_WEEKDAY)
    ifequal(MONDAY, Monday)
    ifequal(TUESDAY, Tuesday)
    ifequal(WEDNESDAY, Wednesday)
    ifequal(THURSDAY, Thursday)
    ifequal(FRIDAY, Friday)
    ifequal(SATURDAY, Saturday)
    getstring(STRING_BUFFER_3, "SUNDAY@")
    s_end
Monday:
    getstring(STRING_BUFFER_3, "MONDAY@")
    s_end
Tuesday:
    getstring(STRING_BUFFER_3, "TUESDAY@")
    s_end
Wednesday:
    getstring(STRING_BUFFER_3, "WEDNESDAY@")
    s_end
Thursday:
    getstring(STRING_BUFFER_3, "THURSDAY@")
    s_end
Friday:
    getstring(STRING_BUFFER_3, "FRIDAY@")
    s_end
Saturday:
    getstring(STRING_BUFFER_3, "SATURDAY@")
    s_end
    SCRIPT_END
}
bool GoldenrodRocketsScript(script_s* s) {
    SCRIPT_BEGIN
    clearevent(EVENT_GOLDENROD_CITY_ROCKET_TAKEOVER)
    s_end
    SCRIPT_END
}
bool RadioTowerRocketsScript(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_ROCKETS_IN_RADIO_TOWER)
    setevent(EVENT_GOLDENROD_CITY_CIVILIANS)
    setevent(EVENT_RADIO_TOWER_BLACKBELT_BLOCKS_STAIRS)
    clearevent(EVENT_RADIO_TOWER_ROCKET_TAKEOVER)
    clearevent(EVENT_USED_THE_CARD_KEY_IN_THE_RADIO_TOWER)
    setevent(EVENT_MAHOGANY_TOWN_POKEFAN_M_BLOCKS_EAST)
    specialphonecall(SPECIALCALL_WEIRDBROADCAST)
    setmapscene(MAHOGANY_TOWN, SCENE_FINISHED)
    s_end
    SCRIPT_END
}

bool BugContestResults_CopyContestantsToResults(script_s* s);
bool BugContestResults_FirstPlace(script_s* s);
bool BugContestResults_SecondPlace(script_s* s);
bool BugContestResults_ThirdPlace(script_s* s);
bool BugContestResults_NoRoomForBerry(script_s* s);
bool BugContestResults_ReturnAfterWinnersPrize(script_s* s);
bool BugContestResults_FinishUp(script_s* s);
bool BugContestResults_DidNotWin(script_s* s);
bool BugContestResults_DidNotLeaveMons(script_s* s);
bool BugContestResults_NoRoomForSunStone(script_s* s);
bool BugContestResults_NoRoomForEverstone(script_s* s);
bool BugContestResults_NoRoomForGoldBerry(script_s* s);
bool BugContestResults_NoRoomForBerry(script_s* s);
bool BugContestResults_NoRoomForGoldBerry(script_s* s);
bool BugContestResults_CleanUp(script_s* s);
extern const uint8_t Movement_ContestResults_WalkAfterWarp[];

bool BugContestResultsWarpScript(script_s* s) {
    SCRIPT_BEGIN
    special(ClearBGPalettes)
    scall(BugContestResults_CopyContestantsToResults)
    setevent(EVENT_ROUTE_36_NATIONAL_PARK_GATE_OFFICER_CONTEST_DAY)
    clearevent(EVENT_ROUTE_36_NATIONAL_PARK_GATE_OFFICER_NOT_CONTEST_DAY)
    setevent(EVENT_WARPED_FROM_ROUTE_35_NATIONAL_PARK_GATE)
    warp(ROUTE_36_NATIONAL_PARK_GATE, 0, 4)
    applymovement(PLAYER, Movement_ContestResults_WalkAfterWarp)
    SCRIPT_FALLTHROUGH(BugContestResultsScript)
}
bool BugContestResultsScript(script_s* s) {
    SCRIPT_BEGIN
    clearflag(ENGINE_BUG_CONTEST_TIMER)
    clearevent(EVENT_WARPED_FROM_ROUTE_35_NATIONAL_PARK_GATE)
    clearevent(EVENT_CONTEST_OFFICER_HAS_SUN_STONE)
    clearevent(EVENT_CONTEST_OFFICER_HAS_EVERSTONE)
    clearevent(EVENT_CONTEST_OFFICER_HAS_GOLD_BERRY)
    clearevent(EVENT_CONTEST_OFFICER_HAS_BERRY)
    opentext
    writetext(ContestResults_ReadyToJudgeText)
    waitbutton
    special(BugContestJudging)
    getnum(STRING_BUFFER_3)
    ifequal_jump(1, BugContestResults_FirstPlace)
    ifequal_jump(2, BugContestResults_SecondPlace)
    ifequal_jump(3, BugContestResults_ThirdPlace)
    writetext(ContestResults_ConsolationPrizeText)
    promptbutton
    waitsfx
    verbosegiveitem(BERRY, 1)
    iffalse_jump(BugContestResults_NoRoomForBerry)
    SCRIPT_FALLTHROUGH(BugContestResults_DidNotWin)
}
bool BugContestResults_DidNotWin(script_s* s) {
    SCRIPT_BEGIN
    writetext(ContestResults_DidNotWinText)
    promptbutton
    sjump(BugContestResults_FinishUp)
    SCRIPT_END
}
bool BugContestResults_ReturnAfterWinnersPrize(script_s* s) {
    SCRIPT_BEGIN
    writetext(ContestResults_JoinUsNextTimeText)
    promptbutton
    SCRIPT_FALLTHROUGH(BugContestResults_FinishUp)
}
bool BugContestResults_FinishUp(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_LEFT_MONS_WITH_CONTEST_OFFICER)
    iffalse_jump(BugContestResults_DidNotLeaveMons)
    writetext(ContestResults_ReturnPartyText)
    waitbutton
    special(ContestReturnMons)
    SCRIPT_FALLTHROUGH(BugContestResults_DidNotLeaveMons)
}
bool BugContestResults_DidNotLeaveMons(script_s* s) {
    SCRIPT_BEGIN
    special(CheckPartyFullAfterContest)
    ifequal_jump(BUGCONTEST_CAUGHT_MON, BugContestResults_CleanUp)
    ifequal_jump(BUGCONTEST_NO_CATCH, BugContestResults_CleanUp)
    // BUGCONTEST_BOXED_MON
    writetext(ContestResults_PartyFullText)
    waitbutton
    SCRIPT_FALLTHROUGH(BugContestResults_CleanUp)
}
bool BugContestResults_CleanUp(script_s* s) {
    SCRIPT_BEGIN
    closetext
    setscene(SCENE_ROUTE36NATIONALPARKGATE_NOTHING)
    setmapscene(ROUTE_35_NATIONAL_PARK_GATE, SCENE_ROUTE35NATIONALPARKGATE_NOTHING)
    setevent(EVENT_BUG_CATCHING_CONTESTANT_1A)
    setevent(EVENT_BUG_CATCHING_CONTESTANT_2A)
    setevent(EVENT_BUG_CATCHING_CONTESTANT_3A)
    setevent(EVENT_BUG_CATCHING_CONTESTANT_4A)
    setevent(EVENT_BUG_CATCHING_CONTESTANT_5A)
    setevent(EVENT_BUG_CATCHING_CONTESTANT_6A)
    setevent(EVENT_BUG_CATCHING_CONTESTANT_7A)
    setevent(EVENT_BUG_CATCHING_CONTESTANT_8A)
    setevent(EVENT_BUG_CATCHING_CONTESTANT_9A)
    setevent(EVENT_BUG_CATCHING_CONTESTANT_10A)
    setevent(EVENT_BUG_CATCHING_CONTESTANT_1B)
    setevent(EVENT_BUG_CATCHING_CONTESTANT_2B)
    setevent(EVENT_BUG_CATCHING_CONTESTANT_3B)
    setevent(EVENT_BUG_CATCHING_CONTESTANT_4B)
    setevent(EVENT_BUG_CATCHING_CONTESTANT_5B)
    setevent(EVENT_BUG_CATCHING_CONTESTANT_6B)
    setevent(EVENT_BUG_CATCHING_CONTESTANT_7B)
    setevent(EVENT_BUG_CATCHING_CONTESTANT_8B)
    setevent(EVENT_BUG_CATCHING_CONTESTANT_9B)
    setevent(EVENT_BUG_CATCHING_CONTESTANT_10B)
    setflag(ENGINE_DAILY_BUG_CONTEST)
    special(PlayMapMusic)
    s_end
    SCRIPT_END
}
bool BugContestResults_FirstPlace(script_s* s) {
    SCRIPT_BEGIN
    setevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1)
    getitemname(STRING_BUFFER_4, SUN_STONE)
    writetext(ContestResults_PlayerWonAPrizeText)
    waitbutton
    verbosegiveitem(SUN_STONE, 1)
    iffalse_jump(BugContestResults_NoRoomForSunStone)
    sjump(BugContestResults_ReturnAfterWinnersPrize)
    SCRIPT_END
}
bool BugContestResults_SecondPlace(script_s* s) {
    SCRIPT_BEGIN
    getitemname(STRING_BUFFER_4, EVERSTONE)
    writetext(ContestResults_PlayerWonAPrizeText)
    waitbutton
    verbosegiveitem(EVERSTONE, 1)
    iffalse_jump(BugContestResults_NoRoomForEverstone)
    sjump(BugContestResults_ReturnAfterWinnersPrize)
    SCRIPT_END
}
bool BugContestResults_ThirdPlace(script_s* s) {
    SCRIPT_BEGIN
    getitemname(STRING_BUFFER_4, GOLD_BERRY)
    writetext(ContestResults_PlayerWonAPrizeText)
    waitbutton
    verbosegiveitem(GOLD_BERRY, 1)
    iffalse_jump(BugContestResults_NoRoomForGoldBerry)
    sjump(BugContestResults_ReturnAfterWinnersPrize)
    SCRIPT_END
}
bool BugContestResults_NoRoomForSunStone(script_s* s) {
    SCRIPT_BEGIN
    writetext(BugContestPrizeNoRoomText)
    promptbutton
    setevent(EVENT_CONTEST_OFFICER_HAS_SUN_STONE)
    sjump(BugContestResults_ReturnAfterWinnersPrize)
    SCRIPT_END
}
bool BugContestResults_NoRoomForEverstone(script_s* s) {
    SCRIPT_BEGIN
    writetext(BugContestPrizeNoRoomText)
    promptbutton
    setevent(EVENT_CONTEST_OFFICER_HAS_EVERSTONE)
    sjump(BugContestResults_ReturnAfterWinnersPrize)
    SCRIPT_END
}
bool BugContestResults_NoRoomForGoldBerry(script_s* s) {
    SCRIPT_BEGIN
    writetext(BugContestPrizeNoRoomText)
    promptbutton
    setevent(EVENT_CONTEST_OFFICER_HAS_GOLD_BERRY)
    sjump(BugContestResults_ReturnAfterWinnersPrize)
    SCRIPT_END
}
bool BugContestResults_NoRoomForBerry(script_s* s) {
    SCRIPT_BEGIN
    writetext(BugContestPrizeNoRoomText)
    promptbutton
    setevent(EVENT_CONTEST_OFFICER_HAS_BERRY)
    sjump(BugContestResults_DidNotWin)
    SCRIPT_END
}
bool BugContestResults_CopyContestantsToResults(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_BUG_CATCHING_CONTESTANT_1A)
    iftrue(skip1)
    clearevent(EVENT_BUG_CATCHING_CONTESTANT_1B)
skip1:
    checkevent(EVENT_BUG_CATCHING_CONTESTANT_2A)
    iftrue(skip2)
    clearevent(EVENT_BUG_CATCHING_CONTESTANT_2B)
skip2:
    checkevent(EVENT_BUG_CATCHING_CONTESTANT_3A)
    iftrue(skip3)
    clearevent(EVENT_BUG_CATCHING_CONTESTANT_3B)
skip3:
    checkevent(EVENT_BUG_CATCHING_CONTESTANT_4A)
    iftrue(skip4)
    clearevent(EVENT_BUG_CATCHING_CONTESTANT_4B)
skip4:
    checkevent(EVENT_BUG_CATCHING_CONTESTANT_5A)
    iftrue(skip5)
    clearevent(EVENT_BUG_CATCHING_CONTESTANT_5B)
skip5:
    checkevent(EVENT_BUG_CATCHING_CONTESTANT_6A)
    iftrue(skip6)
    clearevent(EVENT_BUG_CATCHING_CONTESTANT_6B)
skip6:
    checkevent(EVENT_BUG_CATCHING_CONTESTANT_7A)
    iftrue(skip7)
    clearevent(EVENT_BUG_CATCHING_CONTESTANT_7B)
skip7:
    checkevent(EVENT_BUG_CATCHING_CONTESTANT_8A)
    iftrue(skip8)
    clearevent(EVENT_BUG_CATCHING_CONTESTANT_8B)
skip8:
    checkevent(EVENT_BUG_CATCHING_CONTESTANT_9A)
    iftrue(skip9)
    clearevent(EVENT_BUG_CATCHING_CONTESTANT_9B)
skip9:
    checkevent(EVENT_BUG_CATCHING_CONTESTANT_10A)
    iftrue(skip10)
    clearevent(EVENT_BUG_CATCHING_CONTESTANT_10B)
skip10:
    s_end
    SCRIPT_END
}
bool InitializeEventsScript(script_s* s) {
    SCRIPT_BEGIN
    setevent(EVENT_EARLS_ACADEMY_EARL)
    setevent(EVENT_RADIO_TOWER_ROCKET_TAKEOVER)
    setevent(EVENT_GOLDENROD_CITY_ROCKET_TAKEOVER)
    setevent(EVENT_RADIO_TOWER_CIVILIANS_AFTER)
    setevent(EVENT_ILEX_FOREST_APPRENTICE)
    setevent(EVENT_ILEX_FOREST_FARFETCHD)
    setevent(EVENT_ILEX_FOREST_CHARCOAL_MASTER)
    setevent(EVENT_MAHOGANY_MART_LANCE_AND_DRAGONITE)
    setevent(EVENT_TEAM_ROCKET_BASE_B2F_GRUNT_WITH_EXECUTIVE)
    setevent(EVENT_TEAM_ROCKET_BASE_B2F_EXECUTIVE)
    setevent(EVENT_TEAM_ROCKET_BASE_B2F_DRAGONITE)
    setevent(EVENT_RIVAL_TEAM_ROCKET_BASE)
    setevent(EVENT_BLACKTHORN_CITY_SUPER_NERD_DOES_NOT_BLOCK_GYM)
    setevent(EVENT_USED_THE_CARD_KEY_IN_THE_RADIO_TOWER)
    setevent(EVENT_RIVAL_CHERRYGROVE_CITY)
    setevent(EVENT_RIVAL_AZALEA_TOWN)
    setevent(EVENT_RIVAL_GOLDENROD_UNDERGROUND)
    setevent(EVENT_AZALEA_TOWN_SLOWPOKES)
    setevent(EVENT_KURTS_HOUSE_SLOWPOKE)
    setevent(EVENT_GUIDE_GENT_VISIBLE_IN_CHERRYGROVE)
    setevent(EVENT_ELMS_AIDE_IN_VIOLET_POKEMON_CENTER)
    setevent(EVENT_COP_IN_ELMS_LAB)
    setevent(EVENT_RUINS_OF_ALPH_OUTSIDE_SCIENTIST)
    setevent(EVENT_RUINS_OF_ALPH_RESEARCH_CENTER_SCIENTIST)
    setevent(EVENT_BOULDER_IN_ICE_PATH_1A)
    setevent(EVENT_BOULDER_IN_ICE_PATH_2A)
    setevent(EVENT_BOULDER_IN_ICE_PATH_3A)
    setevent(EVENT_BOULDER_IN_ICE_PATH_4A)
    setevent(EVENT_ROUTE_30_YOUNGSTER_JOEY)
    setevent(EVENT_BUG_CATCHING_CONTESTANT_1A)
    setevent(EVENT_BUG_CATCHING_CONTESTANT_2A)
    setevent(EVENT_BUG_CATCHING_CONTESTANT_3A)
    setevent(EVENT_BUG_CATCHING_CONTESTANT_4A)
    setevent(EVENT_BUG_CATCHING_CONTESTANT_5A)
    setevent(EVENT_BUG_CATCHING_CONTESTANT_6A)
    setevent(EVENT_BUG_CATCHING_CONTESTANT_7A)
    setevent(EVENT_BUG_CATCHING_CONTESTANT_8A)
    setevent(EVENT_BUG_CATCHING_CONTESTANT_9A)
    setevent(EVENT_BUG_CATCHING_CONTESTANT_10A)
    setevent(EVENT_BUG_CATCHING_CONTESTANT_1B)
    setevent(EVENT_BUG_CATCHING_CONTESTANT_2B)
    setevent(EVENT_BUG_CATCHING_CONTESTANT_3B)
    setevent(EVENT_BUG_CATCHING_CONTESTANT_4B)
    setevent(EVENT_BUG_CATCHING_CONTESTANT_5B)
    setevent(EVENT_BUG_CATCHING_CONTESTANT_6B)
    setevent(EVENT_BUG_CATCHING_CONTESTANT_7B)
    setevent(EVENT_BUG_CATCHING_CONTESTANT_8B)
    setevent(EVENT_BUG_CATCHING_CONTESTANT_9B)
    setevent(EVENT_BUG_CATCHING_CONTESTANT_10B)
    setevent(EVENT_FAST_SHIP_1F_GENTLEMAN)
    setevent(EVENT_FAST_SHIP_B1F_SAILOR_RIGHT)
    setevent(EVENT_FAST_SHIP_CABINS_NNW_NNE_NE_SAILOR)
    setevent(EVENT_LAKE_OF_RAGE_CIVILIANS)
    setevent(EVENT_MAHOGANY_MART_OWNERS)
    setevent(EVENT_TIN_TOWER_ROOF_HO_OH)
    setevent(EVENT_WHIRL_ISLAND_LUGIA_CHAMBER_LUGIA)
    setevent(EVENT_PLAYERS_HOUSE_2F_CONSOLE)
    setevent(EVENT_PLAYERS_HOUSE_2F_DOLL_1)
    setevent(EVENT_PLAYERS_HOUSE_2F_DOLL_2)
    setevent(EVENT_PLAYERS_HOUSE_2F_BIG_DOLL)
    setevent(EVENT_DECO_BED_1)
    setevent(EVENT_DECO_POSTER_1)
    setevent(EVENT_GOLDENROD_TRAIN_STATION_GENTLEMAN)
    setevent(EVENT_OLIVINE_GYM_JASMINE)
    setevent(EVENT_BLACKTHORN_CITY_GRAMPS_NOT_BLOCKING_DRAGONS_DEN)
    setevent(EVENT_MET_BILL)
    setevent(EVENT_ECRUTEAK_POKE_CENTER_BILL)
    setevent(EVENT_MYSTERY_GIFT_DELIVERY_GUY)
    setevent(EVENT_LAKE_OF_RAGE_LANCE)
    setevent(EVENT_GOLDENROD_DEPT_STORE_B1F_LAYOUT_1)
    setevent(EVENT_GOLDENROD_UNDERGROUND_WAREHOUSE_BLOCKED_OFF)
    setevent(EVENT_DRAGONS_DEN_CLAIR)
    setevent(EVENT_RIVAL_OLIVINE_CITY)
    setevent(EVENT_RIVAL_VICTORY_ROAD)
    setevent(EVENT_RIVAL_DRAGONS_DEN)
    setevent(EVENT_LANCES_ROOM_OAK_AND_MARY)
    setevent(EVENT_FAST_SHIP_CABINS_SE_SSE_CAPTAINS_CABIN_TWIN_1)
    setevent(EVENT_BURNED_TOWER_B1F_BEASTS_1)
    setevent(EVENT_RED_IN_MT_SILVER)
    setevent(EVENT_OLIVINE_PORT_SPRITES_AFTER_HALL_OF_FAME)
    setevent(EVENT_FAST_SHIP_PASSENGERS_EASTBOUND)
    setevent(EVENT_FAST_SHIP_PASSENGERS_WESTBOUND)
    setevent(EVENT_OLIVINE_PORT_PASSAGE_POKEFAN_M)
    setevent(EVENT_KURTS_HOUSE_KURT_2)
    setevent(EVENT_KURTS_HOUSE_GRANDDAUGHTER_2)
    setevent(EVENT_RANG_CLEAR_BELL_1)
    setevent(EVENT_FLORIA_AT_FLOWER_SHOP)
    setevent(EVENT_FLORIA_AT_SUDOWOODO)
    setevent(EVENT_GOLDENROD_CITY_MOVE_TUTOR)
    setevent(EVENT_RUINS_OF_ALPH_OUTSIDE_TOURIST_FISHER)
    setevent(EVENT_RUINS_OF_ALPH_OUTSIDE_TOURIST_YOUNGSTERS)
    setevent(EVENT_DRAGON_SHRINE_CLAIR)
    setevent(EVENT_BATTLE_TOWER_BATTLE_ROOM_YOUNGSTER)
    setevent(EVENT_PLAYERS_NEIGHBORS_HOUSE_NEIGHBOR)
    setevent(EVENT_AZALEA_TOWN_KURT)
    setevent(EVENT_AZALEA_TOWN_KURT)
    setevent(EVENT_ILEX_FOREST_KURT)
    setevent(EVENT_ROUTE_34_ILEX_FOREST_GATE_TEACHER_IN_WALKWAY)
    setevent(EVENT_ILEX_FOREST_LASS)
    setevent(EVENT_GOLDENROD_SALE_OFF)
    setevent(EVENT_ECRUTEAK_CITY_GRAMPS)
    setevent(EVENT_EUSINE_IN_BURNED_TOWER)
    setevent(EVENT_PLAYERS_HOUSE_MOM_2)
    setevent(EVENT_WISE_TRIOS_ROOM_WISE_TRIO_2)
    setevent(EVENT_CIANWOOD_CITY_EUSINE)
    setevent(EVENT_TIN_TOWER_1F_EUSINE)
    setevent(EVENT_TIN_TOWER_1F_WISE_TRIO_1)
    setevent(EVENT_TIN_TOWER_1F_WISE_TRIO_2)
    setevent(EVENT_SET_WHEN_FOUGHT_HO_OH)
    setevent(EVENT_SAW_SUICUNE_ON_ROUTE_36)
    setevent(EVENT_SAW_SUICUNE_ON_ROUTE_42)
    setevent(EVENT_SAW_SUICUNE_AT_CIANWOOD_CITY)
    setevent(EVENT_BATTLE_TOWER_OUTSIDE_SAILOR)
    setflag(ENGINE_ROCKET_SIGNAL_ON_CH20)
    setflag(ENGINE_ROCKETS_IN_MAHOGANY)

    variablesprite(SPRITE_WEIRD_TREE, SPRITE_SUDOWOODO)
    variablesprite(SPRITE_OLIVINE_RIVAL, SPRITE_SILVER)
    variablesprite(SPRITE_AZALEA_ROCKET, SPRITE_ROCKET)
    variablesprite(SPRITE_FUCHSIA_GYM_1, SPRITE_JANINE)
    variablesprite(SPRITE_FUCHSIA_GYM_2, SPRITE_JANINE)
    variablesprite(SPRITE_FUCHSIA_GYM_3, SPRITE_JANINE)
    variablesprite(SPRITE_FUCHSIA_GYM_4, SPRITE_JANINE)
    variablesprite(SPRITE_COPYCAT, SPRITE_LASS)
    variablesprite(SPRITE_JANINE_IMPERSONATOR, SPRITE_LASS)

    setevent(EVENT_FOUND_MACHINE_PART_IN_CERULEAN_GYM)
    setevent(EVENT_CERULEAN_GYM_ROCKET)
    setevent(EVENT_ROUTE_24_ROCKET)
    setevent(EVENT_ROUTE_25_MISTY_BOYFRIEND)
    setevent(EVENT_TRAINERS_IN_CERULEAN_GYM)
    setevent(EVENT_COPYCATS_HOUSE_2F_DOLL)
    setevent(EVENT_VIRIDIAN_GYM_BLUE)
    setevent(EVENT_SEAFOAM_GYM_GYM_GUIDE)
    setevent(EVENT_MT_MOON_SQUARE_CLEFAIRY)
    setevent(EVENT_SAFFRON_TRAIN_STATION_POPULATION)
    setevent(EVENT_INDIGO_PLATEAU_POKECENTER_RIVAL)
    setevent(EVENT_INITIALIZED_EVENTS)
    s_endcallback
    SCRIPT_END
}
bool AskNumber1MScript(script_s* s) {
    SCRIPT_BEGIN
    special(RandomPhoneMon)
    readvar(VAR_CALLERID)
    ifequal(PHONE_SCHOOLBOY_JACK, Jack)
    ifequal(PHONE_SAILOR_HUEY, Huey)
    ifequal(PHONE_COOLTRAINERM_GAVEN, Gaven)
    ifequal(PHONE_BIRDKEEPER_JOSE, Jose)
    ifequal(PHONE_YOUNGSTER_JOEY, Joey)
    ifequal(PHONE_BUG_CATCHER_WADE, Wade)
    ifequal(PHONE_FISHER_RALPH, Ralph)
    ifequal(PHONE_HIKER_ANTHONY, Anthony)
    ifequal(PHONE_CAMPER_TODD, Todd)
    ifequal(PHONE_JUGGLER_IRWIN, Irwin)
    ifequal(PHONE_BUG_CATCHER_ARNIE, Arnie)
    ifequal(PHONE_SCHOOLBOY_ALAN, Alan)
    ifequal(PHONE_SCHOOLBOY_CHAD, Chad)
    ifequal(PHONE_POKEFANM_DEREK, Derek)
    ifequal(PHONE_FISHER_TULLY, Tully)
    ifequal(PHONE_POKEMANIAC_BRENT, Brent)
    ifequal(PHONE_BIRDKEEPER_VANCE, Vance)
    ifequal(PHONE_FISHER_WILTON, Wilton)
    ifequal(PHONE_BLACKBELT_KENJI, Kenji)
    ifequal(PHONE_HIKER_PARRY, Parry)
Jack:
    writetext(JackAskNumber1Text)
    s_end
Huey:
    writetext(HueyAskNumber1Text)
    s_end
Gaven:
    writetext(GavenAskNumber1Text)
    s_end
Jose:
    writetext(JoseAskNumber1Text)
    s_end
Joey:
    writetext(JoeyAskNumber1Text)
    s_end
Wade:
    writetext(WadeAskNumber1Text)
    s_end
Ralph:
    writetext(RalphAskNumber1Text)
    s_end
Anthony:
    writetext(AnthonyAskNumber1Text)
    s_end
Todd:
    writetext(ToddAskNumber1Text)
    s_end
Irwin:
    writetext(IrwinAskNumber1Text)
    s_end
Arnie:
    writetext(ArnieAskNumber1Text)
    s_end
Alan:
    writetext(AlanAskNumber1Text)
    s_end
Chad:
    writetext(ChadAskNumber1Text)
    s_end
Derek:
    writetext(DerekAskNumber1Text)
    s_end
Tully:
    writetext(TullyAskNumber1Text)
    s_end
Brent:
    writetext(BrentAskNumber1Text)
    s_end
Vance:
    writetext(VanceAskNumber1Text)
    s_end
Wilton:
    writetext(WiltonAskNumber1Text)
    s_end
Kenji:
    writetext(KenjiAskNumber1Text)
    s_end
Parry:
    writetext(ParryAskNumber1Text)
    s_end
    SCRIPT_END
}
bool AskNumber2MScript(script_s* s) {
    SCRIPT_BEGIN
    special(RandomPhoneMon)
    readvar(VAR_CALLERID)
    ifequal(PHONE_SCHOOLBOY_JACK, Jack)
    ifequal(PHONE_SAILOR_HUEY, Huey)
    ifequal(PHONE_COOLTRAINERM_GAVEN, Gaven)
    ifequal(PHONE_BIRDKEEPER_JOSE, Jose)
    ifequal(PHONE_YOUNGSTER_JOEY, Joey)
    ifequal(PHONE_BUG_CATCHER_WADE, Wade)
    ifequal(PHONE_FISHER_RALPH, Ralph)
    ifequal(PHONE_HIKER_ANTHONY, Anthony)
    ifequal(PHONE_CAMPER_TODD, Todd)
    ifequal(PHONE_JUGGLER_IRWIN, Irwin)
    ifequal(PHONE_BUG_CATCHER_ARNIE, Arnie)
    ifequal(PHONE_SCHOOLBOY_ALAN, Alan)
    ifequal(PHONE_SCHOOLBOY_CHAD, Chad)
    ifequal(PHONE_POKEFANM_DEREK, Derek)
    ifequal(PHONE_FISHER_TULLY, Tully)
    ifequal(PHONE_POKEMANIAC_BRENT, Brent)
    ifequal(PHONE_BIRDKEEPER_VANCE, Vance)
    ifequal(PHONE_FISHER_WILTON, Wilton)
    ifequal(PHONE_BLACKBELT_KENJI, Kenji)
    ifequal(PHONE_HIKER_PARRY, Parry)
Jack:
    writetext(JackAskNumber2Text)
    s_end
Huey:
    writetext(HueyAskNumber2Text)
    s_end
Gaven:
    writetext(GavenAskNumber2Text)
    s_end
Jose:
    writetext(JoseAskNumber2Text)
    s_end
Joey:
    writetext(JoeyAskNumber2Text)
    s_end
Wade:
    writetext(WadeAskNumber2Text)
    s_end
Ralph:
    writetext(RalphAskNumber2Text)
    s_end
Anthony:
    writetext(AnthonyAskNumber2Text)
    s_end
Todd:
    writetext(ToddAskNumber2Text)
    s_end
Irwin:
    writetext(IrwinAskNumber2Text)
    s_end
Arnie:
    writetext(ArnieAskNumber2Text)
    s_end
Alan:
    writetext(AlanAskNumber2Text)
    s_end
Chad:
    writetext(ChadAskNumber2Text)
    s_end
Derek:
    writetext(DerekAskNumber2Text)
    s_end
Tully:
    writetext(TullyAskNumber2Text)
    s_end
Brent:
    writetext(BrentAskNumber2Text)
    s_end
Vance:
    writetext(VanceAskNumber2Text)
    s_end
Wilton:
    writetext(WiltonAskNumber2Text)
    s_end
Kenji:
    writetext(KenjiAskNumber2Text)
    s_end
Parry:
    writetext(ParryAskNumber2Text)
    s_end
    SCRIPT_END
}
bool RegisteredNumberMScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(RegisteredNumber1Text)
    playsound(SFX_REGISTER_PHONE_NUMBER)
    waitsfx
    promptbutton
    s_end
    SCRIPT_END
}
bool NumberAcceptedMScript(script_s* s) {
    SCRIPT_BEGIN
    readvar(VAR_CALLERID)
    ifequal(PHONE_SCHOOLBOY_JACK, Jack)
    ifequal(PHONE_SAILOR_HUEY, Huey)
    ifequal(PHONE_COOLTRAINERM_GAVEN, Gaven)
    ifequal(PHONE_BIRDKEEPER_JOSE, Jose)
    ifequal(PHONE_YOUNGSTER_JOEY, Joey)
    ifequal(PHONE_BUG_CATCHER_WADE, Wade)
    ifequal(PHONE_FISHER_RALPH, Ralph)
    ifequal(PHONE_HIKER_ANTHONY, Anthony)
    ifequal(PHONE_CAMPER_TODD, Todd)
    ifequal(PHONE_JUGGLER_IRWIN, Irwin)
    ifequal(PHONE_BUG_CATCHER_ARNIE, Arnie)
    ifequal(PHONE_SCHOOLBOY_ALAN, Alan)
    ifequal(PHONE_SCHOOLBOY_CHAD, Chad)
    ifequal(PHONE_POKEFANM_DEREK, Derek)
    ifequal(PHONE_FISHER_TULLY, Tully)
    ifequal(PHONE_POKEMANIAC_BRENT, Brent)
    ifequal(PHONE_BIRDKEEPER_VANCE, Vance)
    ifequal(PHONE_FISHER_WILTON, Wilton)
    ifequal(PHONE_BLACKBELT_KENJI, Kenji)
    ifequal(PHONE_HIKER_PARRY, Parry)
Jack:
    writetext(JackNumberAcceptedText)
    waitbutton
    closetext
    s_end
Huey:
    writetext(HueyNumberAcceptedText)
    waitbutton
    closetext
    s_end
Gaven:
    writetext(GavenNumberAcceptedText)
    waitbutton
    closetext
    s_end
Jose:
    writetext(JoseNumberAcceptedText)
    waitbutton
    closetext
    s_end
Joey:
    writetext(JoeyNumberAcceptedText)
    waitbutton
    closetext
    s_end
Wade:
    writetext(WadeNumberAcceptedText)
    waitbutton
    closetext
    s_end
Ralph:
    writetext(RalphNumberAcceptedText)
    waitbutton
    closetext
    s_end
Anthony:
    writetext(AnthonyNumberAcceptedText)
    waitbutton
    closetext
    s_end
Todd:
    writetext(ToddNumberAcceptedText)
    waitbutton
    closetext
    s_end
Irwin:
    writetext(IrwinNumberAcceptedText)
    waitbutton
    closetext
    s_end
Arnie:
    writetext(ArnieNumberAcceptedText)
    waitbutton
    closetext
    s_end
Alan:
    writetext(AlanNumberAcceptedText)
    waitbutton
    closetext
    s_end
Chad:
    writetext(ChadNumberAcceptedText)
    waitbutton
    closetext
    s_end
Derek:
    writetext(DerekNumberAcceptedText)
    waitbutton
    closetext
    s_end
Tully:
    writetext(TullyNumberAcceptedText)
    waitbutton
    closetext
    s_end
Brent:
    writetext(BrentNumberAcceptedText)
    waitbutton
    closetext
    s_end
Vance:
    writetext(VanceNumberAcceptedText)
    waitbutton
    closetext
    s_end
Wilton:
    writetext(WiltonNumberAcceptedText)
    waitbutton
    closetext
    s_end
Kenji:
    writetext(KenjiNumberAcceptedText)
    waitbutton
    closetext
    s_end
Parry:
    writetext(ParryNumberAcceptedText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool NumberDeclinedMScript(script_s* s) {
    SCRIPT_BEGIN
    readvar(VAR_CALLERID)
    ifequal(PHONE_SCHOOLBOY_JACK, Jack)
    ifequal(PHONE_SAILOR_HUEY, Huey)
    ifequal(PHONE_COOLTRAINERM_GAVEN, Gaven)
    ifequal(PHONE_BIRDKEEPER_JOSE, Jose)
    ifequal(PHONE_YOUNGSTER_JOEY, Joey)
    ifequal(PHONE_BUG_CATCHER_WADE, Wade)
    ifequal(PHONE_FISHER_RALPH, Ralph)
    ifequal(PHONE_HIKER_ANTHONY, Anthony)
    ifequal(PHONE_CAMPER_TODD, Todd)
    ifequal(PHONE_JUGGLER_IRWIN, Irwin)
    ifequal(PHONE_BUG_CATCHER_ARNIE, Arnie)
    ifequal(PHONE_SCHOOLBOY_ALAN, Alan)
    ifequal(PHONE_SCHOOLBOY_CHAD, Chad)
    ifequal(PHONE_POKEFANM_DEREK, Derek)
    ifequal(PHONE_FISHER_TULLY, Tully)
    ifequal(PHONE_POKEMANIAC_BRENT, Brent)
    ifequal(PHONE_BIRDKEEPER_VANCE, Vance)
    ifequal(PHONE_FISHER_WILTON, Wilton)
    ifequal(PHONE_BLACKBELT_KENJI, Kenji)
    ifequal(PHONE_HIKER_PARRY, Parry)
Jack:
    writetext(JackNumberDeclinedText)
    waitbutton
    closetext
    s_end
Huey:
    writetext(HueyNumberDeclinedText)
    waitbutton
    closetext
    s_end
Gaven:
    writetext(GavenNumberDeclinedText)
    waitbutton
    closetext
    s_end
Jose:
    writetext(JoseNumberDeclinedText)
    waitbutton
    closetext
    s_end
Joey:
    writetext(JoeyNumberDeclinedText)
    waitbutton
    closetext
    s_end
Wade:
    writetext(WadeNumberDeclinedText)
    waitbutton
    closetext
    s_end
Ralph:
    writetext(RalphNumberDeclinedText)
    waitbutton
    closetext
    s_end
Anthony:
    writetext(AnthonyNumberDeclinedText)
    waitbutton
    closetext
    s_end
Todd:
    writetext(ToddNumberDeclinedText)
    waitbutton
    closetext
    s_end
Irwin:
    writetext(IrwinNumberDeclinedText)
    waitbutton
    closetext
    s_end
Arnie:
    writetext(ArnieNumberDeclinedText)
    waitbutton
    closetext
    s_end
Alan:
    writetext(AlanNumberDeclinedText)
    waitbutton
    closetext
    s_end
Chad:
    writetext(ChadNumberDeclinedText)
    waitbutton
    closetext
    s_end
Derek:
    writetext(DerekNumberDeclinedText)
    waitbutton
    closetext
    s_end
Tully:
    writetext(TullyNumberDeclinedText)
    waitbutton
    closetext
    s_end
Brent:
    writetext(BrentNumberDeclinedText)
    waitbutton
    closetext
    s_end
Vance:
    writetext(VanceNumberDeclinedText)
    waitbutton
    closetext
    s_end
Wilton:
    writetext(WiltonNumberDeclinedText)
    waitbutton
    closetext
    s_end
Kenji:
    writetext(KenjiNumberDeclinedText)
    waitbutton
    closetext
    s_end
Parry:
    writetext(ParryNumberDeclinedText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool PhoneFullMScript(script_s* s) {
    SCRIPT_BEGIN
    readvar(VAR_CALLERID)
    ifequal(PHONE_SCHOOLBOY_JACK, Jack)
    ifequal(PHONE_SAILOR_HUEY, Huey)
    ifequal(PHONE_COOLTRAINERM_GAVEN, Gaven)
    ifequal(PHONE_BIRDKEEPER_JOSE, Jose)
    ifequal(PHONE_YOUNGSTER_JOEY, Joey)
    ifequal(PHONE_BUG_CATCHER_WADE, Wade)
    ifequal(PHONE_FISHER_RALPH, Ralph)
    ifequal(PHONE_HIKER_ANTHONY, Anthony)
    ifequal(PHONE_CAMPER_TODD, Todd)
    ifequal(PHONE_JUGGLER_IRWIN, Irwin)
    ifequal(PHONE_BUG_CATCHER_ARNIE, Arnie)
    ifequal(PHONE_SCHOOLBOY_ALAN, Alan)
    ifequal(PHONE_SCHOOLBOY_CHAD, Chad)
    ifequal(PHONE_POKEFANM_DEREK, Derek)
    ifequal(PHONE_FISHER_TULLY, Tully)
    ifequal(PHONE_POKEMANIAC_BRENT, Brent)
    ifequal(PHONE_BIRDKEEPER_VANCE, Vance)
    ifequal(PHONE_FISHER_WILTON, Wilton)
    ifequal(PHONE_BLACKBELT_KENJI, Kenji)
    ifequal(PHONE_HIKER_PARRY, Parry)
Jack:
    writetext(JackPhoneFullText)
    waitbutton
    closetext
    s_end
Huey:
    writetext(HueyPhoneFullText)
    waitbutton
    closetext
    s_end
Gaven:
    writetext(GavenPhoneFullText)
    waitbutton
    closetext
    s_end
Jose:
    writetext(JosePhoneFullText)
    waitbutton
    closetext
    s_end
Joey:
    writetext(JoeyPhoneFullText)
    waitbutton
    closetext
    s_end
Wade:
    writetext(WadePhoneFullText)
    waitbutton
    closetext
    s_end
Ralph:
    writetext(RalphPhoneFullText)
    waitbutton
    closetext
    s_end
Anthony:
    writetext(AnthonyPhoneFullText)
    waitbutton
    closetext
    s_end
Todd:
    writetext(ToddPhoneFullText)
    waitbutton
    closetext
    s_end
Irwin:
    writetext(IrwinPhoneFullText)
    waitbutton
    closetext
    s_end
Arnie:
    writetext(ArniePhoneFullText)
    waitbutton
    closetext
    s_end
Alan:
    writetext(AlanPhoneFullText)
    waitbutton
    closetext
    s_end
Chad:
    writetext(ChadPhoneFullText)
    waitbutton
    closetext
    s_end
Derek:
    writetext(DerekPhoneFullText)
    waitbutton
    closetext
    s_end
Tully:
    writetext(TullyPhoneFullText)
    waitbutton
    closetext
    s_end
Brent:
    writetext(BrentPhoneFullText)
    waitbutton
    closetext
    s_end
Vance:
    writetext(VancePhoneFullText)
    waitbutton
    closetext
    s_end
Wilton:
    writetext(WiltonPhoneFullText)
    waitbutton
    closetext
    s_end
Kenji:
    writetext(KenjiPhoneFullText)
    waitbutton
    closetext
    s_end
Parry:
    writetext(ParryPhoneFullText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool RematchMScript(script_s* s) {
    SCRIPT_BEGIN
    readvar(VAR_CALLERID)
    ifequal(PHONE_SCHOOLBOY_JACK, Jack)
    ifequal(PHONE_SAILOR_HUEY, Huey)
    ifequal(PHONE_COOLTRAINERM_GAVEN, Gaven)
    ifequal(PHONE_BIRDKEEPER_JOSE, Jose)
    ifequal(PHONE_YOUNGSTER_JOEY, Joey)
    ifequal(PHONE_BUG_CATCHER_WADE, Wade)
    ifequal(PHONE_FISHER_RALPH, Ralph)
    ifequal(PHONE_HIKER_ANTHONY, Anthony)
    ifequal(PHONE_CAMPER_TODD, Todd)
    ifequal(PHONE_BUG_CATCHER_ARNIE, Arnie)
    ifequal(PHONE_SCHOOLBOY_ALAN, Alan)
    ifequal(PHONE_SCHOOLBOY_CHAD, Chad)
    ifequal(PHONE_FISHER_TULLY, Tully)
    ifequal(PHONE_POKEMANIAC_BRENT, Brent)
    ifequal(PHONE_BIRDKEEPER_VANCE, Vance)
    ifequal(PHONE_FISHER_WILTON, Wilton)
    ifequal(PHONE_HIKER_PARRY, Parry)
Jack:
    writetext(JackRematchText)
    waitbutton
    closetext
    s_end
Huey:
    writetext(HueyRematchText)
    waitbutton
    closetext
    s_end
Gaven:
    writetext(GavenRematchText)
    waitbutton
    closetext
    s_end
Jose:
    writetext(JoseRematchText)
    waitbutton
    closetext
    s_end
Joey:
    writetext(JoeyRematchText)
    waitbutton
    closetext
    s_end
Wade:
    writetext(WadeRematchText)
    waitbutton
    closetext
    s_end
Ralph:
    writetext(RalphRematchText)
    waitbutton
    closetext
    s_end
Anthony:
    writetext(AnthonyRematchText)
    waitbutton
    closetext
    s_end
Todd:
    writetext(ToddRematchText)
    waitbutton
    closetext
    s_end
Arnie:
    writetext(ArnieRematchText)
    waitbutton
    closetext
    s_end
Alan:
    writetext(AlanRematchText)
    waitbutton
    closetext
    s_end
Chad:
    writetext(ChadRematchText)
    waitbutton
    closetext
    s_end
Tully:
    writetext(TullyRematchText)
    waitbutton
    closetext
    s_end
Brent:
    writetext(BrentRematchText)
    waitbutton
    closetext
    s_end
Vance:
    writetext(VanceRematchText)
    waitbutton
    closetext
    s_end
Wilton:
    writetext(WiltonRematchText)
    waitbutton
    closetext
    s_end
Parry:
    writetext(ParryRematchText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool GiftMScript(script_s* s) {
    SCRIPT_BEGIN
    readvar(VAR_CALLERID)
    ifequal(PHONE_BIRDKEEPER_JOSE, Jose)
    ifequal(PHONE_BUG_CATCHER_WADE, Wade)
    ifequal(PHONE_SCHOOLBOY_ALAN, Alan)
    ifequal(PHONE_POKEFANM_DEREK, Derek)
    ifequal(PHONE_FISHER_TULLY, Tully)
    ifequal(PHONE_FISHER_WILTON, Wilton)
    ifequal(PHONE_BLACKBELT_KENJI, Kenji)
Jose:
    writetext(JoseGiftText)
    promptbutton
    s_end
Wade:
    writetext(WadeGiftText)
    promptbutton
    s_end
Alan:
    writetext(AlanGiftText)
    promptbutton
    s_end
Derek:
    writetext(DerekGiftText)
    promptbutton
    s_end
Tully:
    writetext(TullyGiftText)
    promptbutton
    s_end
Wilton:
    writetext(WiltonGiftText)
    promptbutton
    s_end
Kenji:
    writetext(KenjiGiftText)
    promptbutton
    s_end
    SCRIPT_END
}
bool PackFullMScript(script_s* s) {
    SCRIPT_BEGIN
    readvar(VAR_CALLERID)
    ifequal(PHONE_SAILOR_HUEY, Huey)
    ifequal(PHONE_BIRDKEEPER_JOSE, Jose)
    ifequal(PHONE_YOUNGSTER_JOEY, Joey)
    ifequal(PHONE_BUG_CATCHER_WADE, Wade)
    ifequal(PHONE_SCHOOLBOY_ALAN, Alan)
    ifequal(PHONE_POKEFANM_DEREK, Derek)
    ifequal(PHONE_FISHER_TULLY, Tully)
    ifequal(PHONE_BIRDKEEPER_VANCE, Vance)
    ifequal(PHONE_FISHER_WILTON, Wilton)
    ifequal(PHONE_BLACKBELT_KENJI, Kenji)
    ifequal(PHONE_HIKER_PARRY, Parry)
Huey:
    writetext(HueyPackFullText)
    waitbutton
    closetext
    s_end
Jose:
    writetext(JosePackFullText)
    waitbutton
    closetext
    s_end
Joey:
    writetext(JoeyPackFullText)
    waitbutton
    closetext
    s_end
Wade:
    writetext(WadePackFullText)
    waitbutton
    closetext
    s_end
Alan:
    writetext(AlanPackFullText)
    waitbutton
    closetext
    s_end
Derek:
    writetext(DerekPackFullText)
    waitbutton
    closetext
    s_end
Tully:
    writetext(TullyPackFullText)
    waitbutton
    closetext
    s_end
Vance:
    writetext(VancePackFullText)
    waitbutton
    closetext
    s_end
Wilton:
    writetext(WiltonPackFullText)
    waitbutton
    closetext
    s_end
Kenji:
    writetext(KenjiPackFullText)
    waitbutton
    closetext
    s_end
Parry:
    writetext(ParryPackFullText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool RematchGiftMScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    readvar(VAR_CALLERID)
    ifequal(PHONE_SAILOR_HUEY, Huey)
    ifequal(PHONE_YOUNGSTER_JOEY, Joey)
    ifequal(PHONE_BIRDKEEPER_VANCE, Vance)
    ifequal(PHONE_HIKER_PARRY, Parry)
Huey:
    writetext(HueyRematchGiftText)
    promptbutton
    s_end
Joey:
    writetext(JoeyRematchGiftText)
    promptbutton
    s_end
Vance:
    writetext(VanceRematchGiftText)
    promptbutton
    s_end
Parry:
    writetext(ParryRematchGiftText)
    promptbutton
    s_end
    SCRIPT_END
}
bool AskNumber1FScript(script_s* s) {
    SCRIPT_BEGIN
    readvar(VAR_CALLERID)
    ifequal(PHONE_POKEFAN_BEVERLY, Beverly)
    ifequal(PHONE_COOLTRAINERF_BETH, Beth)
    ifequal(PHONE_COOLTRAINERF_REENA, Reena)
    ifequal(PHONE_PICNICKER_LIZ, Liz)
    ifequal(PHONE_PICNICKER_GINA, Gina)
    ifequal(PHONE_LASS_DANA, Dana)
    ifequal(PHONE_PICNICKER_TIFFANY, Tiffany)
    ifequal(PHONE_PICNICKER_ERIN, Erin)
Beverly:
    writetext(BeverlyAskNumber1Text)
    s_end
Beth:
    writetext(BethAskNumber1Text)
    s_end
Reena:
    writetext(ReenaAskNumber1Text)
    s_end
Liz:
    writetext(LizAskNumber1Text)
    s_end
Gina:
    writetext(GinaAskNumber1Text)
    s_end
Dana:
    writetext(DanaAskNumber1Text)
    s_end
Tiffany:
    writetext(TiffanyAskNumber1Text)
    s_end
Erin:
    writetext(ErinAskNumber1Text)
    s_end
    SCRIPT_END
}
bool AskNumber2FScript(script_s* s) {
    SCRIPT_BEGIN
    readvar(VAR_CALLERID)
    ifequal(PHONE_POKEFAN_BEVERLY, Beverly)
    ifequal(PHONE_COOLTRAINERF_BETH, Beth)
    ifequal(PHONE_COOLTRAINERF_REENA, Reena)
    ifequal(PHONE_PICNICKER_LIZ, Liz)
    ifequal(PHONE_PICNICKER_GINA, Gina)
    ifequal(PHONE_LASS_DANA, Dana)
    ifequal(PHONE_PICNICKER_TIFFANY, Tiffany)
    ifequal(PHONE_PICNICKER_ERIN, Erin)
Beverly:
    writetext(BeverlyAskNumber2Text)
    s_end
Beth:
    writetext(BethAskNumber2Text)
    s_end
Reena:
    writetext(ReenaAskNumber2Text)
    s_end
Liz:
    writetext(LizAskNumber2Text)
    s_end
Gina:
    writetext(GinaAskNumber2Text)
    s_end
Dana:
    writetext(DanaAskNumber2Text)
    s_end
Tiffany:
    writetext(TiffanyAskNumber2Text)
    s_end
Erin:
    writetext(ErinAskNumber2Text)
    s_end
    SCRIPT_END
}
bool RegisteredNumberFScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(RegisteredNumber2Text)
    playsound(SFX_REGISTER_PHONE_NUMBER)
    waitsfx
    promptbutton
    s_end
    SCRIPT_END
}
bool NumberAcceptedFScript(script_s* s) {
    SCRIPT_BEGIN
    readvar(VAR_CALLERID)
    ifequal(PHONE_POKEFAN_BEVERLY, Beverly)
    ifequal(PHONE_COOLTRAINERF_BETH, Beth)
    ifequal(PHONE_COOLTRAINERF_REENA, Reena)
    ifequal(PHONE_PICNICKER_LIZ, Liz)
    ifequal(PHONE_PICNICKER_GINA, Gina)
    ifequal(PHONE_LASS_DANA, Dana)
    ifequal(PHONE_PICNICKER_TIFFANY, Tiffany)
    ifequal(PHONE_PICNICKER_ERIN, Erin)
Beverly:
    writetext(BeverlyNumberAcceptedText)
    waitbutton
    closetext
    s_end
Beth:
    writetext(BethNumberAcceptedText)
    waitbutton
    closetext
    s_end
Reena:
    writetext(ReenaNumberAcceptedText)
    waitbutton
    closetext
    s_end
Liz:
    writetext(LizNumberAcceptedText)
    waitbutton
    closetext
    s_end
Gina:
    writetext(GinaNumberAcceptedText)
    waitbutton
    closetext
    s_end
Dana:
    writetext(DanaNumberAcceptedText)
    waitbutton
    closetext
    s_end
Tiffany:
    writetext(TiffanyNumberAcceptedText)
    waitbutton
    closetext
    s_end
Erin:
    writetext(ErinNumberAcceptedText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool NumberDeclinedFScript(script_s* s) {
    SCRIPT_BEGIN
    readvar(VAR_CALLERID)
    ifequal(PHONE_POKEFAN_BEVERLY, Beverly)
    ifequal(PHONE_COOLTRAINERF_BETH, Beth)
    ifequal(PHONE_COOLTRAINERF_REENA, Reena)
    ifequal(PHONE_PICNICKER_LIZ, Liz)
    ifequal(PHONE_PICNICKER_GINA, Gina)
    ifequal(PHONE_LASS_DANA, Dana)
    ifequal(PHONE_PICNICKER_TIFFANY, Tiffany)
    ifequal(PHONE_PICNICKER_ERIN, Erin)
Beverly:
    writetext(BeverlyNumberDeclinedText)
    waitbutton
    closetext
    s_end
Beth:
    writetext(BethNumberDeclinedText)
    waitbutton
    closetext
    s_end
Reena:
    writetext(ReenaNumberDeclinedText)
    waitbutton
    closetext
    s_end
Liz:
    writetext(LizNumberDeclinedText)
    waitbutton
    closetext
    s_end
Gina:
    writetext(GinaNumberDeclinedText)
    waitbutton
    closetext
    s_end
Dana:
    writetext(DanaNumberDeclinedText)
    waitbutton
    closetext
    s_end
Tiffany:
    writetext(TiffanyNumberDeclinedText)
    waitbutton
    closetext
    s_end
Erin:
    writetext(ErinNumberDeclinedText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool PhoneFullFScript(script_s* s) {
    SCRIPT_BEGIN
    readvar(VAR_CALLERID)
    ifequal(PHONE_POKEFAN_BEVERLY, Beverly)
    ifequal(PHONE_COOLTRAINERF_BETH, Beth)
    ifequal(PHONE_COOLTRAINERF_REENA, Reena)
    ifequal(PHONE_PICNICKER_LIZ, Liz)
    ifequal(PHONE_PICNICKER_GINA, Gina)
    ifequal(PHONE_LASS_DANA, Dana)
    ifequal(PHONE_PICNICKER_TIFFANY, Tiffany)
    ifequal(PHONE_PICNICKER_ERIN, Erin)
Beverly:
    writetext(BeverlyPhoneFullText)
    waitbutton
    closetext
    s_end
Beth:
    writetext(BethPhoneFullText)
    waitbutton
    closetext
    s_end
Reena:
    writetext(ReenaPhoneFullText)
    waitbutton
    closetext
    s_end
Liz:
    writetext(LizPhoneFullText)
    waitbutton
    closetext
    s_end
Gina:
    writetext(GinaPhoneFullText)
    waitbutton
    closetext
    s_end
Dana:
    writetext(DanaPhoneFullText)
    waitbutton
    closetext
    s_end
Tiffany:
    writetext(TiffanyPhoneFullText)
    waitbutton
    closetext
    s_end
Erin:
    writetext(ErinPhoneFullText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool RematchFScript(script_s* s) {
    SCRIPT_BEGIN
    readvar(VAR_CALLERID)
    ifequal(PHONE_COOLTRAINERF_BETH, Beth)
    ifequal(PHONE_COOLTRAINERF_REENA, Reena)
    ifequal(PHONE_PICNICKER_LIZ, Liz)
    ifequal(PHONE_PICNICKER_GINA, Gina)
    ifequal(PHONE_LASS_DANA, Dana)
    ifequal(PHONE_PICNICKER_TIFFANY, Tiffany)
    ifequal(PHONE_PICNICKER_ERIN, Erin)
Beth:
    writetext(BethRematchText)
    waitbutton
    closetext
    s_end
Reena:
    writetext(ReenaRematchText)
    waitbutton
    closetext
    s_end
Liz:
    writetext(LizRematchText)
    waitbutton
    closetext
    s_end
Gina:
    writetext(GinaRematchText)
    waitbutton
    closetext
    s_end
Dana:
    writetext(DanaRematchText)
    waitbutton
    closetext
    s_end
Tiffany:
    writetext(TiffanyRematchText)
    waitbutton
    closetext
    s_end
Erin:
    writetext(ErinRematchText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool GiftFScript(script_s* s) {
    SCRIPT_BEGIN
    readvar(VAR_CALLERID)
    ifequal(PHONE_POKEFAN_BEVERLY, Beverly)
    ifequal(PHONE_PICNICKER_GINA, Gina)
    ifequal(PHONE_LASS_DANA, Dana)
    ifequal(PHONE_PICNICKER_TIFFANY, Tiffany)
Beverly:
    writetext(BeverlyGiftText)
    promptbutton
    s_end
Gina:
    writetext(GinaGiftText)
    promptbutton
    s_end
Dana:
    writetext(DanaGiftText)
    promptbutton
    s_end
Tiffany:
    writetext(TiffanyGiftText)
    promptbutton
    s_end
    SCRIPT_END
}
bool PackFullFScript(script_s* s) {
    SCRIPT_BEGIN
    readvar(VAR_CALLERID)
    ifequal(PHONE_POKEFAN_BEVERLY, Beverly)
    ifequal(PHONE_PICNICKER_GINA, Gina)
    ifequal(PHONE_LASS_DANA, Dana)
    ifequal(PHONE_PICNICKER_TIFFANY, Tiffany)
    ifequal(PHONE_PICNICKER_ERIN, Erin)
Beverly:
    writetext(BeverlyPackFullText)
    waitbutton
    closetext
    s_end
Gina:
    writetext(GinaPackFullText)
    waitbutton
    closetext
    s_end
Dana:
    writetext(DanaPackFullText)
    waitbutton
    closetext
    s_end
Tiffany:
    writetext(TiffanyPackFullText)
    waitbutton
    closetext
    s_end
Erin:
    writetext(ErinPackFullText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool RematchGiftFScript(script_s* s) {
    SCRIPT_BEGIN
    readvar(VAR_CALLERID)
    ifequal(PHONE_PICNICKER_ERIN, Erin)
Erin:
    opentext
    writetext(ErinRematchGiftText)
    promptbutton
    s_end
    SCRIPT_END
}
bool GymStatue1Script(script_s* s) {
    SCRIPT_BEGIN
    getcurlandmarkname(STRING_BUFFER_3)
    opentext
    writetext(GymStatue_CityGymText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool GymStatue2Script(script_s* s) {
    SCRIPT_BEGIN
    getcurlandmarkname(STRING_BUFFER_3)
    opentext
    writetext(GymStatue_CityGymText)
    promptbutton
    writetext(GymStatue_WinningTrainersText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool ReceiveItemScript(script_s* s) {
    SCRIPT_BEGIN
    waitsfx
    writetext(ReceivedItemText)
    playsound(SFX_ITEM)
    waitsfx
    s_end
    SCRIPT_END
}
bool ReceiveTogepiEggScript(script_s* s) {
    SCRIPT_BEGIN
    waitsfx
    writetext(ReceivedItemText)
    playsound(SFX_GET_EGG)
    waitsfx
    s_end
    SCRIPT_END
}
bool GameCornerCoinVendorScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(CoinVendor_WelcomeText)
    promptbutton
    checkitem(COIN_CASE)
    iftrue_jump(CoinVendor_IntroScript)
    writetext(CoinVendor_NoCoinCaseText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}

static const struct MenuData CoinVendor_MenuData = {
    .flags = STATICMENU_CURSOR, // flags
    .verticalMenu = {
        .count = 3, // items
        .options = (const char*[]){
            " 50 :  ¥1000@",
            "500 : ¥10000@",
            "CANCEL@",
        },
    }
};

static const struct MenuHeader CoinVendor_MenuHeader = {
    .flags = MENU_BACKUP_TILES, // flags
    .coord = menu_coords(0, 4, 15, TEXTBOX_Y - 1),
    .data = &CoinVendor_MenuData,
    .defaultOption = 1, // default option
};

bool CoinVendor_IntroScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(CoinVendor_IntroText)
loop:
    special(DisplayMoneyAndCoinBalance)
    loadmenu(&CoinVendor_MenuHeader)
    verticalmenu
    closewindow
    ifequal(1, Buy50)
    ifequal(2, Buy500)
    goto Cancel;
Buy50:
    checkcoins(MAX_COINS - 50)
    ifequal(HAVE_MORE, CoinCaseFull)
    checkmoney(YOUR_MONEY, 1000)
    ifequal(HAVE_LESS, NotEnoughMoney)
    givecoins(50)
    takemoney(YOUR_MONEY, 1000)
    waitsfx
    playsound(SFX_TRANSACTION)
    writetext(CoinVendor_Buy50CoinsText)
    waitbutton
    goto loop;
Buy500:
    checkcoins(MAX_COINS - 500)
    ifequal(HAVE_MORE, CoinCaseFull)
    checkmoney(YOUR_MONEY, 10000)
    ifequal(HAVE_LESS, NotEnoughMoney)
    givecoins(500)
    takemoney(YOUR_MONEY, 10000)
    waitsfx
    playsound(SFX_TRANSACTION)
    writetext(CoinVendor_Buy500CoinsText)
    waitbutton
    goto loop;
NotEnoughMoney:
    writetext(CoinVendor_NotEnoughMoneyText)
    waitbutton
    closetext
    s_end
CoinCaseFull:
    writetext(CoinVendor_CoinCaseFullText)
    waitbutton
    closetext
    s_end
Cancel:
    writetext(CoinVendor_CancelText)
    waitbutton
    closetext
    s_end
    SCRIPT_FALLTHROUGH(HappinessCheckScript)
}
bool HappinessCheckScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    special(GetFirstPokemonHappiness)
    ifless(50, Unhappy)
    ifless(150, KindaHappy)
    writetext(HappinessText3)
    waitbutton
    closetext
    s_end
KindaHappy:
    writetext(HappinessText2)
    waitbutton
    closetext
    s_end
Unhappy:
    writetext(HappinessText1)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const uint8_t Movement_ContestResults_WalkAfterWarp[] = {
    step(RIGHT),
    step(DOWN),
    turn_head(UP),
    movement_step_end,
};
