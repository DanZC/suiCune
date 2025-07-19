#include "../constants.h"
#include "../util/scripting.h"
#include "GoldenrodUnderground.h"
//// EVENTS
enum {
    GOLDENRODUNDERGROUND_SUPER_NERD1 = 2,
    GOLDENRODUNDERGROUND_SUPER_NERD2,
    GOLDENRODUNDERGROUND_SUPER_NERD3,
    GOLDENRODUNDERGROUND_SUPER_NERD4,
    GOLDENRODUNDERGROUND_POKE_BALL,
    GOLDENRODUNDERGROUND_GRAMPS,
    GOLDENRODUNDERGROUND_OLDER_HAIRCUT_BROTHER,
    GOLDENRODUNDERGROUND_YOUNGER_HAIRCUT_BROTHER,
    GOLDENRODUNDERGROUND_GRANNY,
};

const Script_fn_t GoldenrodUnderground_SceneScripts[] = {
    0,
};

const struct MapCallback GoldenrodUnderground_MapCallbacks[] = {
    map_callback(MAPCALLBACK_NEWMAP, GoldenrodUnderground_MapScripts_ResetSwitches),
    map_callback(MAPCALLBACK_TILES, GoldenrodUnderground_MapScripts_CheckBasementKey),
    map_callback(MAPCALLBACK_OBJECTS, GoldenrodUnderground_MapScripts_CheckDayOfWeek),
};

const struct MapScripts GoldenrodUnderground_MapScripts = {
    .scene_script_count = 0, // lengthof(GoldenrodUnderground_SceneScripts),
    .scene_scripts = GoldenrodUnderground_SceneScripts,

    .callback_count = lengthof(GoldenrodUnderground_MapCallbacks),
    .callbacks = GoldenrodUnderground_MapCallbacks,
};

static const struct CoordEvent GoldenrodUnderground_CoordEvents[] = {
    0,
};

static const struct BGEvent GoldenrodUnderground_BGEvents[] = {
    bg_event(18, 6, BGEVENT_READ, &BasementDoorScript),
    bg_event(19, 6, BGEVENT_READ, &GoldenrodUndergroundNoEntrySign),
    bg_event(6, 13, BGEVENT_ITEM, &GoldenrodUndergroundHiddenParlyzHeal),
    bg_event(4, 18, BGEVENT_ITEM, &GoldenrodUndergroundHiddenSuperPotion),
    bg_event(17, 8, BGEVENT_ITEM, &GoldenrodUndergroundHiddenAntidote),
};

static const struct WarpEventData GoldenrodUnderground_WarpEvents[] = {
    warp_event(3, 2, GOLDENROD_UNDERGROUND_SWITCH_ROOM_ENTRANCES, 7),
    warp_event(3, 34, GOLDENROD_UNDERGROUND_SWITCH_ROOM_ENTRANCES, 4),
    warp_event(18, 6, GOLDENROD_UNDERGROUND, 4),
    warp_event(21, 31, GOLDENROD_UNDERGROUND, 3),
    warp_event(22, 31, GOLDENROD_UNDERGROUND, 3),
    warp_event(22, 27, GOLDENROD_UNDERGROUND_SWITCH_ROOM_ENTRANCES, 1),
};

static const struct ObjEvent GoldenrodUnderground_ObjectEvents[] = {
    object_event(5, 31, SPRITE_SUPER_NERD, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_TRAINER, 3, &TrainerSupernerdEric, -1),
    object_event(6, 9, SPRITE_SUPER_NERD, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_TRAINER, 2, &TrainerSupernerdTeru, -1),
    object_event(3, 27, SPRITE_SUPER_NERD, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 2, &TrainerPokemaniacIssac, -1),
    object_event(2, 6, SPRITE_SUPER_NERD, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerPokemaniacDonald, -1),
    object_event(7, 25, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &GoldenrodUndergroundCoinCase, EVENT_GOLDENROD_UNDERGROUND_COIN_CASE),
    object_event(7, 11, SPRITE_GRAMPS, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, &BargainMerchantScript, EVENT_GOLDENROD_UNDERGROUND_GRAMPS),
    object_event(7, 14, SPRITE_SUPER_NERD, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &OlderHaircutBrotherScript, EVENT_GOLDENROD_UNDERGROUND_OLDER_HAIRCUT_BROTHER),
    object_event(7, 15, SPRITE_SUPER_NERD, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &YoungerHaircutBrotherScript, EVENT_GOLDENROD_UNDERGROUND_YOUNGER_HAIRCUT_BROTHER),
    object_event(7, 21, SPRITE_GRANNY, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, &BitterMerchantScript, EVENT_GOLDENROD_UNDERGROUND_GRANNY),
};

const struct MapEvents GoldenrodUnderground_MapEvents = {
    .warp_event_count = lengthof(GoldenrodUnderground_WarpEvents),
    .warp_events = GoldenrodUnderground_WarpEvents,

    .coord_event_count = 0, // lengthof(GoldenrodUnderground_CoordEvents),
    .coord_events = GoldenrodUnderground_CoordEvents,

    .bg_event_count = lengthof(GoldenrodUnderground_BGEvents),
    .bg_events = GoldenrodUnderground_BGEvents,

    .obj_event_count = lengthof(GoldenrodUnderground_ObjectEvents),
    .obj_events = GoldenrodUnderground_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "GoldenrodUnderground.h"

#define GOLDENRODUNDERGROUND_OLDER_HAIRCUT_PRICE 500
#define GOLDENRODUNDERGROUND_YOUNGER_HAIRCUT_PRICE 300
bool GoldenrodUnderground_MapScripts_ResetSwitches(script_s* s) {
    SCRIPT_BEGIN
    clearevent(EVENT_SWITCH_1)
    clearevent(EVENT_SWITCH_2)
    clearevent(EVENT_SWITCH_3)
    clearevent(EVENT_EMERGENCY_SWITCH)
    clearevent(EVENT_SWITCH_4)
    clearevent(EVENT_SWITCH_5)
    clearevent(EVENT_SWITCH_6)
    clearevent(EVENT_SWITCH_7)
    clearevent(EVENT_SWITCH_8)
    clearevent(EVENT_SWITCH_9)
    clearevent(EVENT_SWITCH_10)
    clearevent(EVENT_SWITCH_11)
    clearevent(EVENT_SWITCH_12)
    clearevent(EVENT_SWITCH_13)
    clearevent(EVENT_SWITCH_14)
    setval(0)
    writemem(&gPlayer.undergroundSwitchPositions)
    s_endcallback
    SCRIPT_END
}
bool GoldenrodUnderground_MapScripts_CheckBasementKey(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_USED_BASEMENT_KEY)
    iffalse_jump(GoldenrodUnderground_MapScripts_LockBasementDoor)
    s_endcallback
    SCRIPT_END
}
bool GoldenrodUnderground_MapScripts_LockBasementDoor(script_s* s) {
    SCRIPT_BEGIN
    changeblock(18, 6, 0x3d) // locked door
    s_endcallback
    SCRIPT_END
}
bool GoldenrodUnderground_MapScripts_CheckDayOfWeek(script_s* s) {
    SCRIPT_BEGIN
    readvar(VAR_WEEKDAY)
    ifequal(MONDAY, Monday)
    ifequal(TUESDAY, Tuesday)
    ifequal(WEDNESDAY, Wednesday)
    ifequal(THURSDAY, Thursday)
    ifequal(FRIDAY, Friday)
    ifequal(SATURDAY, Saturday)
// Sunday
    disappear(GOLDENRODUNDERGROUND_GRAMPS)
    disappear(GOLDENRODUNDERGROUND_OLDER_HAIRCUT_BROTHER)
    appear(GOLDENRODUNDERGROUND_YOUNGER_HAIRCUT_BROTHER)
    appear(GOLDENRODUNDERGROUND_GRANNY)
    s_endcallback
Monday:
    disappear(GOLDENRODUNDERGROUND_GRAMPS)
    checktime(MORN)
    iffalse(NotMondayMorning)
    appear(GOLDENRODUNDERGROUND_GRAMPS)
NotMondayMorning:
    disappear(GOLDENRODUNDERGROUND_OLDER_HAIRCUT_BROTHER)
    disappear(GOLDENRODUNDERGROUND_YOUNGER_HAIRCUT_BROTHER)
    disappear(GOLDENRODUNDERGROUND_GRANNY)
    s_endcallback
Tuesday:
    disappear(GOLDENRODUNDERGROUND_GRAMPS)
    appear(GOLDENRODUNDERGROUND_OLDER_HAIRCUT_BROTHER)
    disappear(GOLDENRODUNDERGROUND_YOUNGER_HAIRCUT_BROTHER)
    disappear(GOLDENRODUNDERGROUND_GRANNY)
    s_endcallback
Wednesday:
    disappear(GOLDENRODUNDERGROUND_GRAMPS)
    disappear(GOLDENRODUNDERGROUND_OLDER_HAIRCUT_BROTHER)
    appear(GOLDENRODUNDERGROUND_YOUNGER_HAIRCUT_BROTHER)
    disappear(GOLDENRODUNDERGROUND_GRANNY)
    s_endcallback
Thursday:
    disappear(GOLDENRODUNDERGROUND_GRAMPS)
    appear(GOLDENRODUNDERGROUND_OLDER_HAIRCUT_BROTHER)
    disappear(GOLDENRODUNDERGROUND_YOUNGER_HAIRCUT_BROTHER)
    disappear(GOLDENRODUNDERGROUND_GRANNY)
    s_endcallback
Friday:
    disappear(GOLDENRODUNDERGROUND_GRAMPS)
    disappear(GOLDENRODUNDERGROUND_OLDER_HAIRCUT_BROTHER)
    appear(GOLDENRODUNDERGROUND_YOUNGER_HAIRCUT_BROTHER)
    disappear(GOLDENRODUNDERGROUND_GRANNY)
    s_endcallback
Saturday:
    disappear(GOLDENRODUNDERGROUND_GRAMPS)
    appear(GOLDENRODUNDERGROUND_OLDER_HAIRCUT_BROTHER)
    disappear(GOLDENRODUNDERGROUND_YOUNGER_HAIRCUT_BROTHER)
    appear(GOLDENRODUNDERGROUND_GRANNY)
    s_endcallback
    SCRIPT_END
}
const struct TrainerObj TrainerSupernerdEric = {SUPER_NERD, ERIC, EVENT_BEAT_SUPER_NERD_ERIC, SupernerdEricSeenText, SupernerdEricBeatenText, 0, TrainerSupernerdEric_Script};
bool TrainerSupernerdEric_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SupernerdEricAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSupernerdTeru = {SUPER_NERD, TERU, EVENT_BEAT_SUPER_NERD_TERU, SupernerdTeruSeenText, SupernerdTeruBeatenText, 0, TrainerSupernerdTeru_Script};
bool TrainerSupernerdTeru_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SupernerdTeruAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerPokemaniacIssac = {POKEMANIAC, ISSAC, EVENT_BEAT_POKEMANIAC_ISSAC, PokemaniacIssacSeenText, PokemaniacIssacBeatenText, 0, TrainerPokemaniacIssac_Script};
bool TrainerPokemaniacIssac_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(PokemaniacIssacAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerPokemaniacDonald = {POKEMANIAC, DONALD, EVENT_BEAT_POKEMANIAC_DONALD, PokemaniacDonaldSeenText, PokemaniacDonaldBeatenText, 0, TrainerPokemaniacDonald_Script};
bool TrainerPokemaniacDonald_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(PokemaniacDonaldAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool BitterMerchantScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    readvar(VAR_WEEKDAY)
    ifequal(SUNDAY, Open)
    ifequal(SATURDAY, Open)
    sjump(GoldenrodUndergroundScript_ShopClosed)
Open:
    pokemart(MARTTYPE_BITTER, MART_UNDERGROUND)
    closetext
    s_end
    SCRIPT_END
}
bool BargainMerchantScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    checkflag(ENGINE_GOLDENROD_UNDERGROUND_MERCHANT_CLOSED)
    iftrue_jump(GoldenrodUndergroundScript_ShopClosed)
    readvar(VAR_WEEKDAY)
    ifequal(MONDAY, CheckMorn)
    sjump(GoldenrodUndergroundScript_ShopClosed)
CheckMorn:
    checktime(MORN)
    iffalse_jump(GoldenrodUndergroundScript_ShopClosed)
    pokemart(MARTTYPE_BARGAIN, 0)
    closetext
    s_end
    SCRIPT_END
}
bool OlderHaircutBrotherScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    readvar(VAR_WEEKDAY)
    ifequal(TUESDAY, DoHaircut)
    ifequal(THURSDAY, DoHaircut)
    ifequal(SATURDAY, DoHaircut)
    sjump(GoldenrodUndergroundScript_ShopClosed)
DoHaircut:
    checkflag(ENGINE_GOLDENROD_UNDERGROUND_GOT_HAIRCUT)
    iftrue(AlreadyGotHaircut)
    special(PlaceMoneyTopRight)
    writetext(GoldenrodUndergroundOlderHaircutBrotherOfferHaircutText)
    yesorno
    iffalse(Refused)
    checkmoney(YOUR_MONEY, GOLDENRODUNDERGROUND_OLDER_HAIRCUT_PRICE)
    ifequal(HAVE_LESS, NotEnoughMoney)
    writetext(GoldenrodUndergroundOlderHaircutBrotherAskWhichMonText)
    promptbutton
    special(OlderHaircutBrother)
    ifequal(0x0, Refused)
    ifequal(0x1, Refused)
    setflag(ENGINE_GOLDENROD_UNDERGROUND_GOT_HAIRCUT)
    ifequal(0x2, two)
    ifequal(0x3, three)
    goto else_;
two:
    setevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1)
    clearevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2)
    clearevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_3)
    goto then;
three:
    clearevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1)
    setevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2)
    clearevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_3)
    goto then;
else_:
    clearevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1)
    clearevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2)
    setevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_3)
    goto then;
then:
    takemoney(YOUR_MONEY, GOLDENRODUNDERGROUND_OLDER_HAIRCUT_PRICE)
    special(PlaceMoneyTopRight)
    writetext(GoldenrodUndergroundOlderHaircutBrotherWatchItBecomeBeautifulText)
    waitbutton
    closetext
    special(FadeOutPalettes)
    playmusic(MUSIC_HEAL)
    pause(60)
    special(FadeInPalettes)
    special(RestartMapMusic)
    opentext
    writetext(GoldenrodUndergroundOlderHaircutBrotherAllDoneText)
    waitbutton
    checkevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1)
    iftrue_jump(EitherHaircutBrotherScript_SlightlyHappier)
    checkevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2)
    iftrue_jump(EitherHaircutBrotherScript_Happier)
    sjump(EitherHaircutBrotherScript_MuchHappier)
Refused:
    writetext(GoldenrodUndergroundOlderHaircutBrotherThatsAShameText)
    waitbutton
    closetext
    s_end
NotEnoughMoney:
    writetext(GoldenrodUndergroundOlderHaircutBrotherYoullNeedMoreMoneyText)
    waitbutton
    closetext
    s_end
AlreadyGotHaircut:
    writetext(GoldenrodUndergroundOlderHaircutBrotherOneHaircutADayText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool YoungerHaircutBrotherScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    readvar(VAR_WEEKDAY)
    ifequal(SUNDAY, DoHaircut)
    ifequal(WEDNESDAY, DoHaircut)
    ifequal(FRIDAY, DoHaircut)
    sjump(GoldenrodUndergroundScript_ShopClosed)
DoHaircut:
    checkflag(ENGINE_GOLDENROD_UNDERGROUND_GOT_HAIRCUT)
    iftrue(AlreadyGotHaircut)
    special(PlaceMoneyTopRight)
    writetext(GoldenrodUndergroundYoungerHaircutBrotherOfferHaircutText)
    yesorno
    iffalse(Refused)
    checkmoney(YOUR_MONEY, GOLDENRODUNDERGROUND_YOUNGER_HAIRCUT_PRICE)
    ifequal(HAVE_LESS, NotEnoughMoney)
    writetext(GoldenrodUndergroundYoungerHaircutBrotherAskWhichMonText)
    promptbutton
    special(YoungerHaircutBrother)
    ifequal(0x0, Refused)
    ifequal(0x1, Refused)
    setflag(ENGINE_GOLDENROD_UNDERGROUND_GOT_HAIRCUT)
    ifequal(0x2, two)
    ifequal(0x3, three)
    goto else_;
two:
    setevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1)
    clearevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2)
    clearevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_3)
    goto then;
three:
    clearevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1)
    setevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2)
    clearevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_3)
    goto then;
else_:
    clearevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1)
    clearevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2)
    setevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_3)
    goto then;
then:
    takemoney(YOUR_MONEY, GOLDENRODUNDERGROUND_YOUNGER_HAIRCUT_PRICE)
    special(PlaceMoneyTopRight)
    writetext(GoldenrodUndergroundYoungerHaircutBrotherIllMakeItLookCoolText)
    waitbutton
    closetext
    special(FadeOutPalettes)
    playmusic(MUSIC_HEAL)
    pause(60)
    special(FadeInPalettes)
    special(RestartMapMusic)
    opentext
    writetext(GoldenrodUndergroundYoungerHaircutBrotherAllDoneText)
    waitbutton
    checkevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1)
    iftrue_jump(EitherHaircutBrotherScript_SlightlyHappier)
    checkevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2)
    iftrue_jump(EitherHaircutBrotherScript_Happier)
    sjump(EitherHaircutBrotherScript_MuchHappier)
Refused:
    writetext(GoldenrodUndergroundYoungerHaircutBrotherHowDisappointingText)
    waitbutton
    closetext
    s_end
NotEnoughMoney:
    writetext(GoldenrodUndergroundYoungerHaircutBrotherShortOnFundsText)
    waitbutton
    closetext
    s_end
AlreadyGotHaircut:
    writetext(GoldenrodUndergroundYoungerHaircutBrotherOneHaircutADayText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool EitherHaircutBrotherScript_SlightlyHappier(script_s* s) {
    SCRIPT_BEGIN
    writetext(HaircutBrosText_SlightlyHappier)
    special(PlayCurMonCry)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool EitherHaircutBrotherScript_Happier(script_s* s) {
    SCRIPT_BEGIN
    writetext(HaircutBrosText_Happier)
    special(PlayCurMonCry)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool EitherHaircutBrotherScript_MuchHappier(script_s* s) {
    SCRIPT_BEGIN
    writetext(HaircutBrosText_MuchHappier)
    special(PlayCurMonCry)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool BasementDoorScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    checkevent(EVENT_USED_BASEMENT_KEY)
    iftrue(Open)
    checkitem(BASEMENT_KEY)
    iftrue(Unlock)
    writetext(GoldenrodUndergroundTheDoorsLockedText)
    waitbutton
    closetext
    s_end
Unlock:
    playsound(SFX_TRANSACTION)
    writetext(GoldenrodUndergroundBasementKeyOpenedDoorText)
    waitbutton
    closetext
    changeblock(18, 6, 0x2e) // unlocked door
    reloadmappart
    closetext
    setevent(EVENT_USED_BASEMENT_KEY)
    s_end
Open:
    writetext(GoldenrodUndergroundTheDoorIsOpenText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool GoldenrodUndergroundScript_ShopClosed(script_s* s) {
    SCRIPT_BEGIN
    writetext(GoldenrodUndergroundWeAreNotOpenTodayText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct ItemBall GoldenrodUndergroundCoinCase = {COIN_CASE, 1};
bool GoldenrodUndergroundNoEntrySign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(GoldenrodUndergroundNoEntryText)
    SCRIPT_END
}
const struct HiddenItem GoldenrodUndergroundHiddenParlyzHeal = {PARLYZ_HEAL, EVENT_GOLDENROD_UNDERGROUND_HIDDEN_PARLYZ_HEAL};
const struct HiddenItem GoldenrodUndergroundHiddenSuperPotion = {SUPER_POTION, EVENT_GOLDENROD_UNDERGROUND_HIDDEN_SUPER_POTION};
const struct HiddenItem GoldenrodUndergroundHiddenAntidote = {ANTIDOTE, EVENT_GOLDENROD_UNDERGROUND_HIDDEN_ANTIDOTE};
const txt_cmd_s SupernerdEricSeenText[] = {
    text_start("I got booted out"
        t_line "of the GAME COR-"
        t_cont "NER."
        t_para "I was trying to"
        t_line "cheat using my"
        t_cont "#MON…"
        t_done )
};
const txt_cmd_s SupernerdEricBeatenText[] = {
    text_start("…Grumble…"
        t_done )
};
const txt_cmd_s SupernerdEricAfterBattleText[] = {
    text_start("I guess I have to"
        t_line "do things fair and"
        t_cont "square…"
        t_done )
};
const txt_cmd_s SupernerdTeruSeenText[] = {
    text_start("Do you consider"
        t_line "type alignments in"
        t_cont "battle?"
        t_para "If you know your"
        t_line "type advantages,"
        t_para "you'll do better"
        t_line "in battle."
        t_done )
};
const txt_cmd_s SupernerdTeruBeatenText[] = {
    text_start("Ow, ow, ow!"
        t_done )
};
const txt_cmd_s SupernerdTeruAfterBattleText[] = {
    text_start("I know my #MON"
        t_line "type alignments."
        t_para "But I only use one"
        t_line "type of #MON."
        t_done )
};
const txt_cmd_s PokemaniacIssacSeenText[] = {
    text_start("My #MON just"
        t_line "got a haircut!"
        t_para "I'll show you how"
        t_line "strong it is!"
        t_done )
};
const txt_cmd_s PokemaniacIssacBeatenText[] = {
    text_start("Aiyeeee!"
        t_done )
};
const txt_cmd_s PokemaniacIssacAfterBattleText[] = {
    text_start("Your #MON will"
        t_line "like you more if"
        t_para "you give them"
        t_line "haircuts."
        t_done )
};
const txt_cmd_s PokemaniacDonaldSeenText[] = {
    text_start("I think you have"
        t_line "some rare #MON"
        t_cont "with you."
        t_para "Let me see them!"
        t_done )
};
const txt_cmd_s PokemaniacDonaldBeatenText[] = {
    text_start("Gaah! I lost!"
        t_line "That makes me mad!"
        t_done )
};
const txt_cmd_s PokemaniacDonaldAfterBattleText[] = {
    text_start("Are you making a"
        t_line "#DEX? Here's a"
        t_cont "hot tip."
        t_para "The HIKER on ROUTE"
        t_line "33, ANTHONY, is a"
        t_cont "good guy."
        t_para "He'll phone you if"
        t_line "he sees any rare"
        t_cont "#MON."
        t_done )
};
const txt_cmd_s GoldenrodUndergroundTheDoorsLockedText[] = {
    text_start("The door's locked…"
        t_done )
};
const txt_cmd_s GoldenrodUndergroundTheDoorIsOpenText[] = {
    text_start("The door is open."
        t_done )
};
const txt_cmd_s GoldenrodUndergroundBasementKeyOpenedDoorText[] = {
    text_start("The BASEMENT KEY"
        t_line "opened the door."
        t_done )
};
const txt_cmd_s GoldenrodUndergroundOlderHaircutBrotherOfferHaircutText[] = {
    text_start("Welcome!"
        t_para "I run the #MON"
        t_line "SALON!"
        t_para "I'm the older and"
        t_line "better of the two"
        t_cont "HAIRCUT BROTHERS."
        t_para "I can make your"
        t_line "#MON beautiful"
        t_cont "for just ¥500."
        t_para "Would you like me"
        t_line "to do that?"
        t_done )
};
const txt_cmd_s GoldenrodUndergroundOlderHaircutBrotherAskWhichMonText[] = {
    text_start("Which #MON"
        t_line "should I work on?"
        t_done )
};
const txt_cmd_s GoldenrodUndergroundOlderHaircutBrotherWatchItBecomeBeautifulText[] = {
    text_start("OK! Watch it"
        t_line "become beautiful!"
        t_done )
};
const txt_cmd_s GoldenrodUndergroundOlderHaircutBrotherAllDoneText[] = {
    text_start("There! All done!"
        t_done )
};
const txt_cmd_s GoldenrodUndergroundOlderHaircutBrotherThatsAShameText[] = {
    text_start("Is that right?"
        t_line "That's a shame!"
        t_done )
};
const txt_cmd_s GoldenrodUndergroundOlderHaircutBrotherYoullNeedMoreMoneyText[] = {
    text_start("You'll need more"
        t_line "money than that."
        t_done )
};
const txt_cmd_s GoldenrodUndergroundOlderHaircutBrotherOneHaircutADayText[] = {
    text_start("I do only one"
        t_line "haircut a day. I'm"
        t_cont "done for today."
        t_done )
};
const txt_cmd_s GoldenrodUndergroundYoungerHaircutBrotherOfferHaircutText[] = {
    text_start("Welcome to the"
        t_line "#MON SALON!"
        t_para "I'm the younger"
        t_line "and less expen-"
        t_cont "sive of the two"
        t_cont "HAIRCUT BROTHERS."
        t_para "I'll spiff up your"
        t_line "#MON for just"
        t_cont "¥300."
        t_para "So? How about it?"
        t_done )
};
const txt_cmd_s GoldenrodUndergroundYoungerHaircutBrotherAskWhichMonText[] = {
    text_start("OK, which #MON"
        t_line "should I do?"
        t_done )
};
const txt_cmd_s GoldenrodUndergroundYoungerHaircutBrotherIllMakeItLookCoolText[] = {
    text_start("OK! I'll make it"
        t_line "look cool!"
        t_done )
};
const txt_cmd_s GoldenrodUndergroundYoungerHaircutBrotherAllDoneText[] = {
    text_start("There we go!"
        t_line "All done!"
        t_done )
};
const txt_cmd_s GoldenrodUndergroundYoungerHaircutBrotherHowDisappointingText[] = {
    text_start("No? "
        t_line "How disappointing!"
        t_done )
};
const txt_cmd_s GoldenrodUndergroundYoungerHaircutBrotherShortOnFundsText[] = {
    text_start("You're a little"
        t_line "short on funds."
        t_done )
};
const txt_cmd_s GoldenrodUndergroundYoungerHaircutBrotherOneHaircutADayText[] = {
    text_start("I can do only one"
        t_line "haircut a day."
        t_para "Sorry, but I'm all"
        t_line "done for today."
        t_done )
};
const txt_cmd_s HaircutBrosText_SlightlyHappier[] = {
    text_ram(wram_ptr(wStringBuffer3))
    text_start(" looks a"
        t_line "little happier."
        t_done )
};
const txt_cmd_s HaircutBrosText_Happier[] = {
    text_ram(wram_ptr(wStringBuffer3))
    text_start(" looks"
        t_line "happy."
        t_done )
};
const txt_cmd_s HaircutBrosText_MuchHappier[] = {
    text_ram(wram_ptr(wStringBuffer3))
    text_start(" looks"
        t_line "delighted!"
        t_done )
};
const txt_cmd_s GoldenrodUndergroundWeAreNotOpenTodayText[] = {
    text_start("We're not open"
        t_line "today."
        t_done )
};
const txt_cmd_s GoldenrodUndergroundNoEntryText[] = {
    text_start("NO ENTRY BEYOND"
        t_line "THIS POINT"
        t_done )
    //db(0, 0) // filler
};
