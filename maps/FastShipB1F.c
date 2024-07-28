#include "../constants.h"
#include "../util/scripting.h"
#include "FastShipB1F.h"
//// EVENTS
enum {
    FASTSHIPB1F_SAILOR1 = 2,
    FASTSHIPB1F_SAILOR2,
    FASTSHIPB1F_SAILOR3,
    FASTSHIPB1F_LASS,
    FASTSHIPB1F_SUPER_NERD,
    FASTSHIPB1F_SAILOR4,
    FASTSHIPB1F_FISHER,
    FASTSHIPB1F_BLACK_BELT,
    FASTSHIPB1F_SAILOR5,
    FASTSHIPB1F_TEACHER,
    FASTSHIPB1F_YOUNGSTER1,
    FASTSHIPB1F_YOUNGSTER2,
};

const Script_fn_t FastShipB1F_SceneScripts[] = {
    FastShipB1F_MapScripts_DummyScene0 , //  SCENE_DEFAULT,
    FastShipB1F_MapScripts_DummyScene1 , //  SCENE_FINISHED,
};

const struct MapCallback FastShipB1F_MapCallbacks[] = {
    0,
};

const struct MapScripts FastShipB1F_MapScripts = {
    .scene_script_count = lengthof(FastShipB1F_SceneScripts),
    .scene_scripts = FastShipB1F_SceneScripts,

    .callback_count = 0, // lengthof(FastShipB1F_MapCallbacks),
    .callbacks = FastShipB1F_MapCallbacks,
};

static const struct CoordEvent FastShipB1F_CoordEvents[] = {
    coord_event(30, 7, SCENE_DEFAULT, &FastShipB1FSailorBlocksLeft),
    coord_event(31, 7, SCENE_DEFAULT, &FastShipB1FSailorBlocksRight),
};

static const struct BGEvent FastShipB1F_BGEvents[] = {
    bg_event(27, 9, BGEVENT_READ, &FastShipB1FTrashcan),
};

static const struct WarpEventData FastShipB1F_WarpEvents[] = {
    warp_event(5, 11, FAST_SHIP_1F, 11),
    warp_event(31, 13, FAST_SHIP_1F, 12),
};

static const struct ObjEvent FastShipB1F_ObjectEvents[] = {
    object_event(30, 6, SPRITE_SAILOR, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &FastShipB1FSailorScript, EVENT_FAST_SHIP_B1F_SAILOR_LEFT),
    object_event(31, 6, SPRITE_SAILOR, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &FastShipB1FSailorScript, EVENT_FAST_SHIP_B1F_SAILOR_RIGHT),
    object_event(9, 11, SPRITE_SAILOR, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerSailorJeff, EVENT_FAST_SHIP_PASSENGERS_FIRST_TRIP),
    object_event(6, 4, SPRITE_LASS, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 1, &TrainerPicnickerDebra, EVENT_FAST_SHIP_PASSENGERS_FIRST_TRIP),
    object_event(26, 9, SPRITE_SUPER_NERD, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 1, &TrainerJugglerFritz, EVENT_FAST_SHIP_PASSENGERS_FIRST_TRIP),
    object_event(17, 4, SPRITE_SAILOR, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 4, &TrainerSailorGarrett, EVENT_FAST_SHIP_PASSENGERS_EASTBOUND),
    object_event(25, 8, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 3, &TrainerFisherJonah, EVENT_FAST_SHIP_PASSENGERS_EASTBOUND),
    object_event(15, 11, SPRITE_BLACK_BELT, SPRITEMOVEDATA_SPINCLOCKWISE, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_TRAINER, 3, &TrainerBlackbeltWai, EVENT_FAST_SHIP_PASSENGERS_EASTBOUND),
    object_event(23, 4, SPRITE_SAILOR, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 4, &TrainerSailorKenneth, EVENT_FAST_SHIP_PASSENGERS_WESTBOUND),
    object_event(9, 11, SPRITE_TEACHER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 3, &TrainerTeacherShirley, EVENT_FAST_SHIP_PASSENGERS_WESTBOUND),
    object_event(14, 9, SPRITE_YOUNGSTER, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 1, &TrainerSchoolboyNate, EVENT_FAST_SHIP_PASSENGERS_WESTBOUND),
    object_event(14, 11, SPRITE_YOUNGSTER, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 1, &TrainerSchoolboyRicky, EVENT_FAST_SHIP_PASSENGERS_WESTBOUND),
};

const struct MapEvents FastShipB1F_MapEvents = {
    .warp_event_count = lengthof(FastShipB1F_WarpEvents),
    .warp_events = FastShipB1F_WarpEvents,

    .coord_event_count = lengthof(FastShipB1F_CoordEvents),
    .coord_events = FastShipB1F_CoordEvents,

    .bg_event_count = lengthof(FastShipB1F_BGEvents),
    .bg_events = FastShipB1F_BGEvents,

    .obj_event_count = lengthof(FastShipB1F_ObjectEvents),
    .obj_events = FastShipB1F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "FastShipB1F.h"

bool FastShipB1F_MapScripts_DummyScene0(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool FastShipB1F_MapScripts_DummyScene1(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool FastShipB1FSailorBlocksLeft(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_FAST_SHIP_B1F_SAILOR_RIGHT)
    iftrue_jump(FastShipB1FAlreadyBlocked)
    applymovement(FASTSHIPB1F_SAILOR2, FastShipB1FSailorBlocksLeftMovement)
    moveobject(FASTSHIPB1F_SAILOR1, 30, 6)
    appear(FASTSHIPB1F_SAILOR1)
    pause(5)
    disappear(FASTSHIPB1F_SAILOR2)
    s_end
    SCRIPT_END
}
bool FastShipB1FSailorBlocksRight(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_FAST_SHIP_B1F_SAILOR_LEFT)
    iftrue_jump(FastShipB1FAlreadyBlocked)
    applymovement(FASTSHIPB1F_SAILOR1, FastShipB1FSailorBlocksRightMovement)
    moveobject(FASTSHIPB1F_SAILOR2, 31, 6)
    appear(FASTSHIPB1F_SAILOR2)
    pause(5)
    disappear(FASTSHIPB1F_SAILOR1)
    s_end
    SCRIPT_END
}
bool FastShipB1FAlreadyBlocked(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool FastShipB1FSailorScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_FAST_SHIP_FIRST_TIME)
    iftrue(FirstTime)
    checkevent(EVENT_FAST_SHIP_LAZY_SAILOR)
    iftrue(LazySailor)
    checkevent(EVENT_FAST_SHIP_INFORMED_ABOUT_LAZY_SAILOR)
    iftrue(AlreadyInformed)
    writetext(FastShipB1FOnDutySailorText)
    waitbutton
    closetext
    setevent(EVENT_FAST_SHIP_INFORMED_ABOUT_LAZY_SAILOR)
    clearevent(EVENT_FAST_SHIP_CABINS_NNW_NNE_NE_SAILOR)
    s_end
AlreadyInformed:
    writetext(FastShipB1FOnDutySailorRefusedText)
    waitbutton
    closetext
    s_end
LazySailor:
    writetext(FastShipB1FOnDutySailorThanksText)
    checkevent(EVENT_FAST_SHIP_FOUND_GIRL)
    iffalse(NotFoundGirl)
    waitbutton
    closetext
    s_end
NotFoundGirl:
    promptbutton
    writetext(FastShipB1FOnDutySailorSawLittleGirlText)
    waitbutton
    closetext
    s_end
FirstTime:
    writetext(FastShipB1FOnDutySailorDirectionsText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSailorJeff = {SAILOR, JEFF, EVENT_BEAT_SAILOR_JEFF, SailorJeffSeenText, SailorJeffBeatenText, 0, TrainerSailorJeff_Script};
bool TrainerSailorJeff_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SailorJeffAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerPicnickerDebra = {PICNICKER, DEBRA, EVENT_BEAT_PICNICKER_DEBRA, PicnickerDebraSeenText, PicnickerDebraBeatenText, 0, TrainerPicnickerDebra_Script};
bool TrainerPicnickerDebra_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(PicnickerDebraAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerJugglerFritz = {JUGGLER, FRITZ, EVENT_BEAT_JUGGLER_FRITZ, JugglerFritzSeenText, JugglerFritzBeatenText, 0, TrainerJugglerFritz_Script};
bool TrainerJugglerFritz_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(JugglerFritzAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSailorGarrett = {SAILOR, GARRETT, EVENT_BEAT_SAILOR_GARRETT, SailorGarrettSeenText, SailorGarrettBeatenText, 0, TrainerSailorGarrett_Script};
bool TrainerSailorGarrett_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SailorGarrettAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerFisherJonah = {FISHER, JONAH, EVENT_BEAT_FISHER_JONAH, FisherJonahSeenText, FisherJonahBeatenText, 0, TrainerFisherJonah_Script};
bool TrainerFisherJonah_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(FisherJonahAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerBlackbeltWai = {BLACKBELT_T, WAI, EVENT_BEAT_BLACKBELT_WAI, BlackbeltWaiSeenText, BlackbeltWaiBeatenText, 0, TrainerBlackbeltWai_Script};
bool TrainerBlackbeltWai_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(BlackbeltWaiAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSailorKenneth = {SAILOR, KENNETH, EVENT_BEAT_SAILOR_KENNETH, SailorKennethSeenText, SailorKennethBeatenText, 0, TrainerSailorKenneth_Script};
bool TrainerSailorKenneth_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SailorKennethAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerTeacherShirley = {TEACHER, SHIRLEY, EVENT_BEAT_TEACHER_SHIRLEY, TeacherShirleySeenText, TeacherShirleyBeatenText, 0, TrainerTeacherShirley_Script};
bool TrainerTeacherShirley_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(TeacherShirleyAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSchoolboyNate = {SCHOOLBOY, NATE, EVENT_BEAT_SCHOOLBOY_NATE, SchoolboyNateSeenText, SchoolboyNateBeatenText, 0, TrainerSchoolboyNate_Script};
bool TrainerSchoolboyNate_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SchoolboyNateAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSchoolboyRicky = {SCHOOLBOY, RICKY, EVENT_BEAT_SCHOOLBOY_RICKY, SchoolboyRickySeenText, SchoolboyRickyBeatenText, 0, TrainerSchoolboyRicky_Script};
bool TrainerSchoolboyRicky_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SchoolboyRickyAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool FastShipB1FTrashcan(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(TrashCanScript)
    SCRIPT_END
}
const uint8_t FastShipB1FSailorBlocksRightMovement[] = {
    movement_fix_facing,
    big_step(RIGHT),
    movement_remove_fixed_facing,
    turn_head(DOWN),
    movement_step_end,
};
const uint8_t FastShipB1FSailorBlocksLeftMovement[] = {
    movement_fix_facing,
    big_step(LEFT),
    movement_remove_fixed_facing,
    turn_head(DOWN),
    movement_step_end,
};
const txt_cmd_s FastShipB1FOnDutySailorText[] = {
    text_start("Hey, kid. Could I"
        t_line "get you to look"
        t_cont "for my buddy?"
        t_para "He's goofing off"
        t_line "somewhere, that"
        t_cont "lazy bum!"
        t_para "I want to go find"
        t_line "him, but I'm on"
        t_cont "duty right now."
        t_done )
};
const txt_cmd_s FastShipB1FOnDutySailorRefusedText[] = {
    text_start("Oh, gee…"
        t_para "The CAPTAIN will"
        t_line "be furious…"
        t_done )
};
const txt_cmd_s FastShipB1FOnDutySailorThanksText[] = {
    text_start("Thanks, kid!"
        t_line "I chewed him out"
        t_para "good so he'll quit"
        t_line "slacking off!"
        t_done )
};
const txt_cmd_s FastShipB1FOnDutySailorSawLittleGirlText[] = {
    text_start("A little girl?"
        t_para "I may have seen"
        t_line "her go by here."
        t_done )
};
const txt_cmd_s FastShipB1FOnDutySailorDirectionsText[] = {
    text_start("The dining room is"
        t_line "up ahead."
        t_para "The stairs at the"
        t_line "end lead to the"
        t_cont "CAPTAIN's cabin."
        t_done )
};
const txt_cmd_s SailorJeffSeenText[] = {
    text_start("Nothing beats a"
        t_line "battle when I'm"
        t_cont "on my break."
        t_done )
};
const txt_cmd_s SailorJeffBeatenText[] = {
    text_start("Win or lose, my"
        t_line "break's over!"
        t_done )
};
const txt_cmd_s SailorJeffAfterBattleText[] = {
    text_start("I guess I can't"
        t_line "win if I don't get"
        t_cont "serious."
        t_done )
};
const txt_cmd_s PicnickerDebraSeenText[] = {
    text_start("I'm so bored."
        t_line "Want to battle?"
        t_done )
};
const txt_cmd_s PicnickerDebraBeatenText[] = {
    text_start("Yow! You're too"
        t_line "strong!"
        t_done )
};
const txt_cmd_s PicnickerDebraAfterBattleText[] = {
    text_start("SAFFRON, CELADON…"
        t_line "I hear there are"
        t_para "many big cities"
        t_line "in KANTO."
        t_done )
};
const txt_cmd_s JugglerFritzSeenText[] = {
    text_start("Urrf…"
        t_line "I'm seasick!"
        t_done )
};
const txt_cmd_s JugglerFritzBeatenText[] = {
    text_start("I can't move any-"
        t_line "more…"
        t_done )
};
const txt_cmd_s JugglerFritzAfterBattleText[] = {
    text_start("No more ships for"
        t_line "me. Next time,"
        t_para "I'm taking the"
        t_line "MAGNET TRAIN."
        t_done )
};
const txt_cmd_s SailorGarrettSeenText[] = {
    text_start("This is where we"
        t_line "sailors work!"
        t_done )
};
const txt_cmd_s SailorGarrettBeatenText[] = {
    text_start("I lost on my home"
        t_line "field…"
        t_done )
};
const txt_cmd_s SailorGarrettAfterBattleText[] = {
    text_start("We get different"
        t_line "passengers from"
        t_para "VERMILION CITY to"
        t_line "OLIVINE CITY."
        t_done )
};
const txt_cmd_s FisherJonahSeenText[] = {
    text_start("Even though we're"
        t_line "out on the sea, I"
        t_cont "can't fish!"
        t_para "This is boring!"
        t_line "Let's battle!"
        t_done )
};
const txt_cmd_s FisherJonahBeatenText[] = {
    text_start("I… I'm not bored"
        t_line "anymore…"
        t_done )
};
const txt_cmd_s FisherJonahAfterBattleText[] = {
    text_start("I plan to fish off"
        t_line "VERMILION's pier."
        t_done )
};
const txt_cmd_s BlackbeltWaiSeenText[] = {
    text_start("I'm building up my"
        t_line "legs by bracing"
        t_para "against the ship's"
        t_line "rocking!"
        t_done )
};
const txt_cmd_s BlackbeltWaiBeatenText[] = {
    text_start("Rocked and rolled"
        t_line "over!"
        t_done )
};
const txt_cmd_s BlackbeltWaiAfterBattleText[] = {
    text_start("I couldn't find"
        t_line "the KARATE KING in"
        t_cont "JOHTO."
        t_para "He's supposed to"
        t_line "be training in a"
        t_cont "cave somewhere."
        t_done )
};
const txt_cmd_s SailorKennethSeenText[] = {
    text_start("I'm a sailor man!"
        t_para "But I'm training"
        t_line "#MON, so I can"
        t_cont "become the CHAMP!"
        t_done )
};
const txt_cmd_s SailorKennethBeatenText[] = {
    text_start("My lack of train-"
        t_line "ing is obvious…"
        t_done )
};
const txt_cmd_s SailorKennethAfterBattleText[] = {
    text_start("Eight BADGES!"
        t_line "They must prove"
        t_para "that you've beaten"
        t_line "GYM LEADERS."
        t_para "No wonder you're"
        t_line "so good!"
        t_done )
};
const txt_cmd_s TeacherShirleySeenText[] = {
    text_start("Don't lay a finger"
        t_line "on my students!"
        t_done )
};
const txt_cmd_s TeacherShirleyBeatenText[] = {
    text_start("Aaack!"
        t_done )
};
const txt_cmd_s TeacherShirleyAfterBattleText[] = {
    text_start("We're on a field"
        t_line "trip to the RUINS"
        t_cont "outside VIOLET."
        t_done )
};
const txt_cmd_s SchoolboyNateSeenText[] = {
    text_start("Do you know the"
        t_line "RUINS OF ALPH?"
        t_done )
};
const txt_cmd_s SchoolboyNateBeatenText[] = {
    text_start("Yaargh!"
        t_done )
};
const txt_cmd_s SchoolboyNateAfterBattleText[] = {
    text_start("Radios pick up"
        t_line "strange signals"
        t_cont "inside the RUINS."
        t_done )
};
const txt_cmd_s SchoolboyRickySeenText[] = {
    text_start("There are some odd"
        t_line "stone panels in"
        t_cont "the RUINS OF ALPH."
        t_done )
};
const txt_cmd_s SchoolboyRickyBeatenText[] = {
    text_start("I was done in!"
        t_done )
};
const txt_cmd_s SchoolboyRickyAfterBattleText[] = {
    text_start("I read that there"
        t_line "are four of those"
        t_cont "stone panels."
        t_done )
    //db(0, 0) // filler
};
