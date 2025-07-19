#include "../constants.h"
#include "../util/scripting.h"
#include "Route36.h"
//// EVENTS
enum {
    ROUTE36_YOUNGSTER1 = 2,
    ROUTE36_YOUNGSTER2,
    ROUTE36_WEIRD_TREE,
    ROUTE36_LASS1,
    ROUTE36_FISHER,
    ROUTE36_FRUIT_TREE,
    ROUTE36_ARTHUR,
    ROUTE36_FLORIA,
    ROUTE36_SUICUNE,
};

const Script_fn_t Route36_SceneScripts[] = {
    Route36_MapScripts_DummyScene0 , //  SCENE_ROUTE36_NOTHING,
    Route36_MapScripts_DummyScene1 , //  SCENE_ROUTE36_SUICUNE,
};

const struct MapCallback Route36_MapCallbacks[] = {
    map_callback(MAPCALLBACK_OBJECTS, Route36_MapScripts_ArthurCallback),
};

const struct MapScripts Route36_MapScripts = {
    .scene_script_count = lengthof(Route36_SceneScripts),
    .scene_scripts = Route36_SceneScripts,

    .callback_count = lengthof(Route36_MapCallbacks),
    .callbacks = Route36_MapCallbacks,
};

static const struct CoordEvent Route36_CoordEvents[] = {
    coord_event(20, 7, SCENE_ROUTE36_SUICUNE, &Route36SuicuneScript),
    coord_event(22, 7, SCENE_ROUTE36_SUICUNE, &Route36SuicuneScript),
};

static const struct BGEvent Route36_BGEvents[] = {
    bg_event(29, 1, BGEVENT_READ, &Route36TrainerTips2),
    bg_event(45, 11, BGEVENT_READ, &RuinsOfAlphNorthSign),
    bg_event(55, 7, BGEVENT_READ, &Route36Sign),
    bg_event(21, 7, BGEVENT_READ, &Route36TrainerTips1),
};

static const struct WarpEventData Route36_WarpEvents[] = {
    warp_event(18, 8, ROUTE_36_NATIONAL_PARK_GATE, 3),
    warp_event(18, 9, ROUTE_36_NATIONAL_PARK_GATE, 4),
    warp_event(47, 13, ROUTE_36_RUINS_OF_ALPH_GATE, 1),
    warp_event(48, 13, ROUTE_36_RUINS_OF_ALPH_GATE, 2),
};

static const struct ObjEvent Route36_ObjectEvents[] = {
    object_event(20, 13, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerPsychicMark, -1),
    object_event(31, 14, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 5, &TrainerSchoolboyAlan1, -1),
    object_event(35, 9, SPRITE_WEIRD_TREE, SPRITEMOVEDATA_SUDOWOODO, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &SudowoodoScript, EVENT_ROUTE_36_SUDOWOODO),
    object_event(51, 8, SPRITE_LASS, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 2, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Route36LassScript, -1),
    object_event(44, 9, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Route36RockSmashGuyScript, -1),
    object_event(21, 4, SPRITE_FRUIT_TREE, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Route36FruitTree, -1),
    object_event(46, 6, SPRITE_YOUNGSTER, SPRITEMOVEDATA_WANDER, 1, 1, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &ArthurScript, EVENT_ROUTE_36_ARTHUR_OF_THURSDAY),
    object_event(33, 12, SPRITE_LASS, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &Route36FloriaScript, EVENT_FLORIA_AT_SUDOWOODO),
    object_event(21, 6, SPRITE_SUICUNE, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, EVENT_SAW_SUICUNE_ON_ROUTE_36),
};

const struct MapEvents Route36_MapEvents = {
    .warp_event_count = lengthof(Route36_WarpEvents),
    .warp_events = Route36_WarpEvents,

    .coord_event_count = lengthof(Route36_CoordEvents),
    .coord_events = Route36_CoordEvents,

    .bg_event_count = lengthof(Route36_BGEvents),
    .bg_events = Route36_BGEvents,

    .obj_event_count = lengthof(Route36_ObjectEvents),
    .obj_events = Route36_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "Route36.h"

bool Route36_MapScripts_DummyScene0(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool Route36_MapScripts_DummyScene1(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool Route36_MapScripts_ArthurCallback(script_s* s) {
    SCRIPT_BEGIN
    readvar(VAR_WEEKDAY)
    ifequal_jump(THURSDAY, Route36_MapScripts_ArthurAppears)
    disappear(ROUTE36_ARTHUR)
    s_endcallback
    SCRIPT_END
}
bool Route36_MapScripts_ArthurAppears(script_s* s) {
    SCRIPT_BEGIN
    appear(ROUTE36_ARTHUR)
    s_endcallback
    SCRIPT_END
}
bool Route36SuicuneScript(script_s* s) {
    SCRIPT_BEGIN
    showemote(EMOTE_SHOCK, PLAYER, 15)
    pause(15)
    playsound(SFX_WARP_FROM)
    turnobject(PLAYER, UP)
    applymovement(ROUTE36_SUICUNE, Route36SuicuneMovement)
    disappear(ROUTE36_SUICUNE)
    turnobject(PLAYER, DOWN)
    pause(10)
    setscene(SCENE_ROUTE36_NOTHING)
    clearevent(EVENT_SAW_SUICUNE_AT_CIANWOOD_CITY)
    setmapscene(CIANWOOD_CITY, SCENE_CIANWOODCITY_SUICUNE_AND_EUSINE)
    s_end
    SCRIPT_END
}
bool SudowoodoScript(script_s* s) {
    SCRIPT_BEGIN
    checkitem(SQUIRTBOTTLE)
    iftrue(Fight)
    waitsfx
    playsound(SFX_SANDSTORM)
    applymovement(ROUTE36_WEIRD_TREE, SudowoodoShakeMovement)
    s_end
Fight:
    opentext
    writetext(UseSquirtbottleText)
    yesorno
    iffalse_jump(DidntUseSquirtbottleScript)
    closetext
    SCRIPT_FALLTHROUGH(WateredWeirdTreeScript)
}
bool WateredWeirdTreeScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(UsedSquirtbottleText)
    waitbutton
    closetext
    waitsfx
    playsound(SFX_SANDSTORM)
    applymovement(ROUTE36_WEIRD_TREE, SudowoodoShakeMovement)
    opentext
    writetext(SudowoodoAttackedText)
    waitbutton
    closetext
    loadwildmon(SUDOWOODO, 20)
    startbattle
    setevent(EVENT_FOUGHT_SUDOWOODO)
    ifequal_jump(DRAW, DidntCatchSudowoodo)
    disappear(ROUTE36_WEIRD_TREE)
    variablesprite(SPRITE_WEIRD_TREE, SPRITE_TWIN)
    reloadmapafterbattle
    s_end
    SCRIPT_END
}
bool DidntUseSquirtbottleScript(script_s* s) {
    SCRIPT_BEGIN
    closetext
    s_end
    SCRIPT_END
}
bool DidntCatchSudowoodo(script_s* s) {
    SCRIPT_BEGIN
    reloadmapafterbattle
    applymovement(ROUTE36_WEIRD_TREE, WeirdTreeMovement_Flee)
    disappear(ROUTE36_WEIRD_TREE)
    variablesprite(SPRITE_WEIRD_TREE, SPRITE_TWIN)
    special(LoadUsedSpritesGFX)
    special(RefreshSprites)
    s_end
    SCRIPT_END
}
bool Route36FloriaScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_TALKED_TO_FLORIA_AT_FLOWER_SHOP)
    iftrue(SecondTimeTalking)
    setevent(EVENT_MET_FLORIA)
    writetext(FloriaText1)
    waitbutton
    closetext
    clearevent(EVENT_FLORIA_AT_FLOWER_SHOP)
    readvar(VAR_FACING)
    ifequal(UP, Up)
    applymovement(ROUTE36_FLORIA, FloriaMovement1)
    disappear(ROUTE36_FLORIA)
    s_end
Up:
    applymovement(ROUTE36_FLORIA, FloriaMovement2)
    disappear(ROUTE36_FLORIA)
    s_end
SecondTimeTalking:
    writetext(FloriaText2)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Route36RockSmashGuyScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_TM08_ROCK_SMASH)
    iftrue(AlreadyGotRockSmash)
    checkevent(EVENT_FOUGHT_SUDOWOODO)
    iftrue(ClearedSudowoodo)
    writetext(RockSmashGuyText1)
    waitbutton
    closetext
    s_end
ClearedSudowoodo:
    writetext(RockSmashGuyText2)
    promptbutton
    verbosegiveitem(TM_ROCK_SMASH, 1)
    iffalse(NoRoomForTM)
    setevent(EVENT_GOT_TM08_ROCK_SMASH)
AlreadyGotRockSmash:
    writetext(RockSmashGuyText3)
    waitbutton
NoRoomForTM:
    closetext
    s_end
    SCRIPT_END
}
bool Route36LassScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_FOUGHT_SUDOWOODO)
    iftrue(ClearedSudowoodo)
    writetext(Route36LassText)
    waitbutton
    closetext
    s_end
ClearedSudowoodo:
    writetext(Route36LassText_ClearedSudowoodo)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSchoolboyAlan1 = {SCHOOLBOY, ALAN1, EVENT_BEAT_SCHOOLBOY_ALAN, SchoolboyAlan1SeenText, SchoolboyAlan1BeatenText, 0, TrainerSchoolboyAlan1_Script};
bool TrainerSchoolboyAlan1_Script(script_s* s) {
    SCRIPT_BEGIN
    loadvar(VAR_CALLERID, PHONE_SCHOOLBOY_ALAN)
    endifjustbattled
    opentext
    checkflag(ENGINE_ALAN_READY_FOR_REMATCH)
    iftrue(ChooseRematch)
    checkflag(ENGINE_ALAN_HAS_FIRE_STONE)
    iftrue(GiveFireStone)
    checkcellnum(PHONE_SCHOOLBOY_ALAN)
    iftrue(NumberAccepted)
    checkevent(EVENT_ALAN_ASKED_FOR_PHONE_NUMBER)
    iftrue(AskAgainForPhoneNumber)
    writetext(SchoolboyAlanBooksText)
    promptbutton
    setevent(EVENT_ALAN_ASKED_FOR_PHONE_NUMBER)
    scall_local(AskNumber1);
    goto ContinueAskForPhoneNumber;
AskAgainForPhoneNumber:
    scall_local(AskNumber2);
ContinueAskForPhoneNumber:
    askforphonenumber(PHONE_SCHOOLBOY_ALAN)
    ifequal(PHONE_CONTACTS_FULL, PhoneFull)
    ifequal(PHONE_CONTACT_REFUSED, NumberDeclined)
    gettrainername(STRING_BUFFER_3, SCHOOLBOY, ALAN1)
    scall_local(RegisteredNumber);
    goto NumberAccepted;
ChooseRematch:
    scall_local(Rematch);
    winlosstext(SchoolboyAlan1BeatenText, 0)
    readmem(&gPlayer.AlanFightCount)
    ifequal(4, Fight4)
    ifequal(3, Fight3)
    ifequal(2, Fight2)
    ifequal(1, Fight1)
    ifequal(0, LoadFight0)
Fight4:
    checkevent(EVENT_RESTORED_POWER_TO_KANTO)
    iftrue(LoadFight4)
Fight3:
    checkevent(EVENT_BEAT_ELITE_FOUR)
    iftrue(LoadFight3)
Fight2:
    checkflag(ENGINE_FLYPOINT_BLACKTHORN)
    iftrue(LoadFight2)
Fight1:
    checkflag(ENGINE_FLYPOINT_OLIVINE)
    iftrue(LoadFight1)
LoadFight0:
    loadtrainer(SCHOOLBOY, ALAN1)
    startbattle
    reloadmapafterbattle
    loadmem(&gPlayer.AlanFightCount, 1)
    clearflag(ENGINE_ALAN_READY_FOR_REMATCH)
    s_end
LoadFight1:
    loadtrainer(SCHOOLBOY, ALAN2)
    startbattle
    reloadmapafterbattle
    loadmem(&gPlayer.AlanFightCount, 2)
    clearflag(ENGINE_ALAN_READY_FOR_REMATCH)
    s_end
LoadFight2:
    loadtrainer(SCHOOLBOY, ALAN3)
    startbattle
    reloadmapafterbattle
    loadmem(&gPlayer.AlanFightCount, 3)
    clearflag(ENGINE_ALAN_READY_FOR_REMATCH)
    s_end
LoadFight3:
    loadtrainer(SCHOOLBOY, ALAN4)
    startbattle
    reloadmapafterbattle
    loadmem(&gPlayer.AlanFightCount, 4)
    clearflag(ENGINE_ALAN_READY_FOR_REMATCH)
    s_end
LoadFight4:
    loadtrainer(SCHOOLBOY, ALAN5)
    startbattle
    reloadmapafterbattle
    clearflag(ENGINE_ALAN_READY_FOR_REMATCH)
    s_end
GiveFireStone:
    scall_local(Gift);
    verbosegiveitem(FIRE_STONE, 1)
    iffalse(BagFull)
    clearflag(ENGINE_ALAN_HAS_FIRE_STONE)
    setevent(EVENT_ALAN_GAVE_FIRE_STONE)
    goto NumberAccepted;
BagFull:
    goto PackFull;
AskNumber1:
    jumpstd(AskNumber1MScript)
    s_end
AskNumber2:
    jumpstd(AskNumber2MScript)
    s_end
RegisteredNumber:
    jumpstd(RegisteredNumberMScript)
    s_end
NumberAccepted:
    jumpstd(NumberAcceptedMScript)
    s_end
NumberDeclined:
    jumpstd(NumberDeclinedMScript)
    s_end
PhoneFull:
    jumpstd(PhoneFullMScript)
    s_end
Rematch:
    jumpstd(RematchMScript)
    s_end
Gift:
    jumpstd(GiftMScript)
    s_end
PackFull:
    jumpstd(PackFullMScript)
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerPsychicMark = {PSYCHIC_T, MARK, EVENT_BEAT_PSYCHIC_MARK, PsychicMarkSeenText, PsychicMarkBeatenText, 0, TrainerPsychicMark_Script};
bool TrainerPsychicMark_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(PsychicMarkAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool ArthurScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_HARD_STONE_FROM_ARTHUR)
    iftrue(AlreadyGotStone)
    readvar(VAR_WEEKDAY)
    ifnotequal_jump(THURSDAY, ArthurNotThursdayScript)
    checkevent(EVENT_MET_ARTHUR_OF_THURSDAY)
    iftrue(MetArthur)
    writetext(MeetArthurText)
    promptbutton
    setevent(EVENT_MET_ARTHUR_OF_THURSDAY)
MetArthur:
    writetext(ArthurGivesGiftText)
    promptbutton
    verbosegiveitem(HARD_STONE, 1)
    iffalse(BagFull)
    setevent(EVENT_GOT_HARD_STONE_FROM_ARTHUR)
    writetext(ArthurGaveGiftText)
    waitbutton
    closetext
    s_end
AlreadyGotStone:
    writetext(ArthurThursdayText)
    waitbutton
BagFull:
    closetext
    s_end
    SCRIPT_END
}
bool ArthurNotThursdayScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(ArthurNotThursdayText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Route36Sign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route36SignText)
    SCRIPT_END
}
bool RuinsOfAlphNorthSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(RuinsOfAlphNorthSignText)
    SCRIPT_END
}
bool Route36TrainerTips1(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route36TrainerTips1Text)
    SCRIPT_END
}
bool Route36TrainerTips2(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route36TrainerTips2Text)
    SCRIPT_END
}
bool Route36FruitTree(script_s* s) {
    SCRIPT_BEGIN
    fruittree(FRUITTREE_ROUTE_36)
    SCRIPT_END
}
const uint8_t SudowoodoShakeMovement[] = {
    movement_tree_shake,
    movement_step_end,
};
const uint8_t WeirdTreeMovement_Flee[] = {
    fast_jump_step(UP),
    fast_jump_step(UP),
    movement_step_end
};
const uint8_t FloriaMovement1[] = {
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    movement_step_end,
};
const uint8_t FloriaMovement2[] = {
    step(LEFT),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    movement_step_end,
};
const uint8_t Route36SuicuneMovement[] = {
    movement_set_sliding,
    fast_jump_step(DOWN),
    fast_jump_step(DOWN),
    fast_jump_step(DOWN),
    fast_jump_step(RIGHT),
    fast_jump_step(RIGHT),
    fast_jump_step(RIGHT),
    movement_remove_sliding,
    movement_step_end,
};
const txt_cmd_s UseSquirtbottleText[] = {
    text_start("It's a weird tree."
        t_line "Use SQUIRTBOTTLE?"
        t_done )
};
const txt_cmd_s UsedSquirtbottleText[] = {
    text_start("<PLAYER> used the"
        t_line "SQUIRTBOTTLE."
        t_done )
};
const txt_cmd_s SudowoodoAttackedText[] = {
    text_start("The weird tree"
        t_line "doesn't like the"
        t_cont "SQUIRTBOTTLE!"
        t_para "The weird tree"
        t_line "attacked!"
        t_done )
};
const txt_cmd_s FloriaText1[] = {
    text_start("I'm the FLOWER"
        t_line "SHOP's FLORIA!"
        t_para "Listen, listen!"
        t_para "When I sprinkled"
        t_line "water on that"
        t_para "wiggly tree, it"
        t_line "jumped right up!"
        t_para "It just has to be"
        t_line "a #MON."
        t_para "I bet it would be"
        t_line "shocked out of its"
        t_para "disguise if you"
        t_line "soaked it!"
        t_para "I know! I'll tell"
        t_line "my sis and borrow"
        t_cont "her water bottle!"
        t_done )
};
const txt_cmd_s FloriaText2[] = {
    text_start("When I told my sis"
        t_line "about the jiggly"
        t_para "tree, she said"
        t_line "it's dangerous."
        t_para "If I beat WHITNEY,"
        t_line "I wonder if she'll"
        t_para "lend me her water"
        t_line "bottle…"
        t_done )
};
const txt_cmd_s RockSmashGuyText1[] = {
    text_start("Wa-hey!"
        t_para "I was going to"
        t_line "snap that tree"
        t_para "with my straight-"
        t_line "arm punch."
        t_para "But I couldn't!"
        t_line "I'm a failure!"
        t_done )
};
const txt_cmd_s RockSmashGuyText2[] = {
    text_start("Did you clear that"
        t_line "wretched tree?"
        t_para "I'm impressed!"
        t_line "I want you to"
        t_cont "have this."
        t_done )
};
const txt_cmd_s Text_ReceivedTM08[] = {
    text_start("<PLAYER> received"
        t_line "TM08."
        t_done )
};
const txt_cmd_s RockSmashGuyText3[] = {
    text_start("That happens to be"
        t_line "ROCK SMASH."
        t_para "You can shatter"
        t_line "rocks with just a"
        t_para "single well-aimed"
        t_line "smack."
        t_para "If any rocks are"
        t_line "in your way, just"
        t_cont "smash 'em up!"
        t_done )
};
const txt_cmd_s UnusedOddTreeText[] = {
    text_start("An odd tree is"
        t_line "blocking the way"
        t_cont "to GOLDENROD CITY."
        t_para "I wanted to go see"
        t_line "the huge #MON"
        t_para "CENTER they just"
        t_line "opened…"
        t_done )
};
const txt_cmd_s Route36LassText[] = {
    text_start("An odd tree is"
        t_line "blocking the way"
        t_cont "to GOLDENROD CITY."
        t_para "It's preventing"
        t_line "me from shopping."
        t_para "Something should"
        t_line "be done about it."
        t_done )
};
const txt_cmd_s Route36LassText_ClearedSudowoodo[] = {
    text_start("That odd tree dis-"
        t_line "appeared without a"
        t_cont "trace."
        t_para "Oh! That tree was"
        t_line "really a #MON?"
        t_done )
};
const txt_cmd_s PsychicMarkSeenText[] = {
    text_start("I'm going to read"
        t_line "your thoughts!"
        t_done )
};
const txt_cmd_s PsychicMarkBeatenText[] = {
    text_start("I misread you!"
        t_done )
};
const txt_cmd_s PsychicMarkAfterBattleText[] = {
    text_start("I'd be strong if"
        t_line "only I could tell"
        t_para "what my opponent"
        t_line "was thinking."
        t_done )
};
const txt_cmd_s SchoolboyAlan1SeenText[] = {
    text_start("Thanks to my stud-"
        t_line "ies, I'm ready for"
        t_cont "any #MON!"
        t_done )
};
const txt_cmd_s SchoolboyAlan1BeatenText[] = {
    text_start("Oops! Computation"
        t_line "error?"
        t_done )
};
const txt_cmd_s SchoolboyAlanBooksText[] = {
    text_start("Darn. I study five"
        t_line "hours a day too."
        t_para "There's more to"
        t_line "learning than just"
        t_cont "reading books."
        t_done )
};
const txt_cmd_s MeetArthurText[] = {
    text_start("ARTHUR: Who are"
        t_line "you?"
        t_para "I'm ARTHUR of"
        t_line "Thursday."
        t_done )
};
const txt_cmd_s ArthurGivesGiftText[] = {
    text_start("Here. You can have"
        t_line "this."
        t_done )
};
const txt_cmd_s ArthurGaveGiftText[] = {
    text_start("ARTHUR: A #MON"
        t_line "that uses rock-"
        t_para "type moves should"
        t_line "hold on to that."
        t_para "It pumps up rock-"
        t_line "type attacks."
        t_done )
};
const txt_cmd_s ArthurThursdayText[] = {
    text_start("ARTHUR: I'm ARTHUR"
        t_line "of Thursday. I'm"
        t_para "the second son out"
        t_line "of seven children."
        t_done )
};
const txt_cmd_s ArthurNotThursdayText[] = {
    text_start("ARTHUR: Today's"
        t_line "not Thursday. How"
        t_cont "disappointing."
        t_done )
};
const txt_cmd_s Route36SignText[] = {
    text_start("ROUTE 36"
        t_done )
};
const txt_cmd_s RuinsOfAlphNorthSignText[] = {
    text_start("RUINS OF ALPH"
        t_line "NORTH ENTRANCE"
        t_done )
};
const txt_cmd_s Route36TrainerTips1Text[] = {
    text_start("TRAINER TIPS"
        t_para "#MON stats"
        t_line "vary--even within"
        t_cont "the same species."
        t_para "Their stats may be"
        t_line "similar at first."
        t_para "However, differ-"
        t_line "ences will become"
        t_para "pronounced as the"
        t_line "#MON grow."
        t_done )
};
const txt_cmd_s Route36TrainerTips2Text[] = {
    text_start("TRAINER TIPS"
        t_para "Use DIG to return"
        t_line "to the entrance of"
        t_cont "any place."
        t_para "It is convenient"
        t_line "for exploring"
        t_para "caves and other"
        t_line "landmarks."
        t_done )
    //db(0, 0) // filler
};
