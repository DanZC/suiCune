#include "../constants.h"
#include "../util/scripting.h"
#include "EarlsPokemonAcademy.h"
//// EVENTS
enum {
    EARLSPOKEMONACADEMY_EARL = 2,
    EARLSPOKEMONACADEMY_YOUNGSTER1,
    EARLSPOKEMONACADEMY_GAMEBOY_KID1,
    EARLSPOKEMONACADEMY_GAMEBOY_KID2,
    EARLSPOKEMONACADEMY_YOUNGSTER2,
    EARLSPOKEMONACADEMY_POKEDEX,
};

const Script_fn_t EarlsPokemonAcademy_SceneScripts[] = {
    0,
};

const struct MapCallback EarlsPokemonAcademy_MapCallbacks[] = {
    0,
};

const struct MapScripts EarlsPokemonAcademy_MapScripts = {
    .scene_script_count = 0, // lengthof(EarlsPokemonAcademy_SceneScripts),
    .scene_scripts = EarlsPokemonAcademy_SceneScripts,

    .callback_count = 0, // lengthof(EarlsPokemonAcademy_MapCallbacks),
    .callbacks = EarlsPokemonAcademy_MapCallbacks,
};

static const struct CoordEvent EarlsPokemonAcademy_CoordEvents[] = {
    0,
};

static const struct BGEvent EarlsPokemonAcademy_BGEvents[] = {
    bg_event(0, 1, BGEVENT_READ, &AcademyBookshelf),
    bg_event(1, 1, BGEVENT_READ, &AcademyBookshelf),
    bg_event(3, 0, BGEVENT_READ, &AcademyBlackboard),
    bg_event(4, 0, BGEVENT_READ, &AcademyBlackboard),
};

static const struct WarpEventData EarlsPokemonAcademy_WarpEvents[] = {
    warp_event(3, 15, VIOLET_CITY, 3),
    warp_event(4, 15, VIOLET_CITY, 3),
};

static const struct ObjEvent EarlsPokemonAcademy_ObjectEvents[] = {
    object_event(4, 2, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &AcademyEarl, EVENT_EARLS_ACADEMY_EARL),
    object_event(2, 5, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &EarlsPokemonAcademyYoungster1Script, -1),
    object_event(3, 11, SPRITE_GAMEBOY_KID, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &EarlsPokemonAcademyGameboyKid1Script, -1),
    object_event(4, 11, SPRITE_GAMEBOY_KID, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &EarlsPokemonAcademyGameboyKid2Script, -1),
    object_event(4, 7, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &EarlsPokemonAcademyYoungster2Script, -1),
    object_event(2, 4, SPRITE_POKEDEX, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &AcademyNotebook, -1),
};

const struct MapEvents EarlsPokemonAcademy_MapEvents = {
    .warp_event_count = lengthof(EarlsPokemonAcademy_WarpEvents),
    .warp_events = EarlsPokemonAcademy_WarpEvents,

    .coord_event_count = 0, // lengthof(EarlsPokemonAcademy_CoordEvents),
    .coord_events = EarlsPokemonAcademy_CoordEvents,

    .bg_event_count = lengthof(EarlsPokemonAcademy_BGEvents),
    .bg_events = EarlsPokemonAcademy_BGEvents,

    .obj_event_count = lengthof(EarlsPokemonAcademy_ObjectEvents),
    .obj_events = EarlsPokemonAcademy_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "EarlsPokemonAcademy.h"

bool AcademyEarl(script_s* s) {
    SCRIPT_BEGIN
    applymovement(EARLSPOKEMONACADEMY_EARL, AcademyEarlSpinMovement)
    faceplayer
    opentext
    writetext(AcademyEarlIntroText)
    yesorno
    iffalse(Part1)
    writetext(AcademyEarlTeachHowToWinText)
    yesorno
    iffalse(Done)
Part1:
    writetext(AcademyEarlTeachMoreText)
    yesorno
    iffalse(Done)
    writetext(AcademyEarlTeachHowToRaiseWellText)
    waitbutton
    closetext
    s_end
Done:
    writetext(AcademyEarlNoMoreToTeachText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool EarlsPokemonAcademyYoungster1Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(EarlsPokemonAcademyYoungster1Text)
    SCRIPT_END
}
bool EarlsPokemonAcademyGameboyKid1Script(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(EarlsPokemonAcademyGameboyKid1Text)
    waitbutton
    closetext
    turnobject(EARLSPOKEMONACADEMY_GAMEBOY_KID1, DOWN)
    s_end
    SCRIPT_END
}
bool EarlsPokemonAcademyGameboyKid2Script(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(EarlsPokemonAcademyGameboyKid2Text)
    waitbutton
    closetext
    turnobject(EARLSPOKEMONACADEMY_GAMEBOY_KID2, DOWN)
    s_end
    SCRIPT_END
}
bool EarlsPokemonAcademyYoungster2Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(EarlsPokemonAcademyYoungster2Text)
    SCRIPT_END
}

static const struct MenuHeader BlackboardMenuHeader = {
    .flags = MENU_BACKUP_TILES, // flags
    .coord = menu_coords(0, 0, 11, 8),
    //dw(.MenuData)
    .data = &(struct MenuData) {
    // MenuData:
        .flags = STATICMENU_CURSOR, // flags
        ._2dMenu = {
            .rows=3, .cols=2, // rows, columns
            .spacing = 5, // spacing
            .options = (const char*[]) {
                "PSN@",
                "PAR@",
                "SLP@",
                "BRN@",
                "FRZ@",
                "QUIT@",
            },
            //dbw(BANK(@), NULL)
        },
    },
    .defaultOption = 1, // default option
};

bool AcademyBlackboard(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(AcademyBlackboardText)
Loop:
    loadmenu(&BlackboardMenuHeader)
    _2dmenu
    closewindow
    ifequal(1, Poison)
    ifequal(2, Paralysis)
    ifequal(3, Sleep)
    ifequal(4, Burn)
    ifequal(5, Freeze)
    closetext
    s_end
Poison:
    writetext(AcademyPoisonText)
    waitbutton
    goto Loop;
Paralysis:
    writetext(AcademyParalysisText)
    waitbutton
    goto Loop;
Sleep:
    writetext(AcademySleepText)
    waitbutton
    goto Loop;
Burn:
    writetext(AcademyBurnText)
    waitbutton
    goto Loop;
Freeze:
    writetext(AcademyFreezeText)
    waitbutton
    goto Loop;
    SCRIPT_END
}
bool AcademyNotebook(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(AcademyNotebookText)
    yesorno
    iffalse(Done)
    writetext(AcademyNotebookText1)
    yesorno
    iffalse(Done)
    writetext(AcademyNotebookText2)
    yesorno
    iffalse(Done)
    writetext(AcademyNotebookText3)
    waitbutton
Done:
    closetext
    s_end
    SCRIPT_END
}
bool AcademyStickerMachine(script_s* s) {
    SCRIPT_BEGIN
    jumptext(AcademyStickerMachineText)
    SCRIPT_END
}
bool AcademyBookshelf(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(DifficultBookshelfScript)
    SCRIPT_END
}
const uint8_t AcademyEarlSpinMovement[] = {
    turn_head(DOWN),
    turn_head(LEFT),
    turn_head(UP),
    turn_head(RIGHT),
    turn_head(DOWN),
    turn_head(LEFT),
    turn_head(UP),
    turn_head(RIGHT),
    turn_head(DOWN),
    turn_head(LEFT),
    turn_head(UP),
    turn_head(RIGHT),
    turn_head(DOWN),
    movement_step_end,
};
const txt_cmd_s AcademyEarlIntroText[] = {
    text_start("EARL, I am!"
        t_para "Wonderful are"
        t_line "#MON, yes!"
        t_para "Teach you I will"
        t_line "to be a better"
        t_cont "trainer!"
        t_para "What you want to"
        t_line "know? Want to be"
        t_cont "a winner is you?"
        t_done )
};
const txt_cmd_s AcademyEarlTeachHowToWinText[] = {
    text_start("Good! Teach you,"
        t_line "I will!"
        t_para "In battle, #MON"
        t_line "top on list jump"
        t_cont "out first!"
        t_para "Change order in"
        t_line "list, make battle"
        t_cont "easy, maybe!"
        t_para "More from me you"
        t_line "want to hear?"
        t_done )
};
const txt_cmd_s AcademyEarlTeachMoreText[] = {
    text_start("So, want to know"
        t_line "how to raise"
        t_cont "#MON well?"
        t_done )
};
const txt_cmd_s AcademyEarlTeachHowToRaiseWellText[] = {
    text_start("Fine! Teach you,"
        t_line "I will!"
        t_para "If #MON come"
        t_line "out in battle even"
        t_para "briefly, some EXP."
        t_line "Points it gets."
        t_para "At top of list put"
        t_line "weak #MON."
        t_para "Switch in battle"
        t_line "quick!"
        t_para "This way, weak"
        t_line "#MON strong"
        t_cont "become!"
        t_done )
};
const txt_cmd_s AcademyEarlNoMoreToTeachText[] = {
    text_start("Oh! Smart student"
        t_line "you are! Nothing"
        t_cont "more do I teach!"
        t_para "Good to #MON"
        t_line "you must be!"
        t_done )
};
const txt_cmd_s EarlsPokemonAcademyYoungster1Text[] = {
    text_start("I'm taking notes"
        t_line "of the teacher's"
        t_cont "lecture."
        t_para "I'd better copy"
        t_line "the stuff on the"
        t_cont "blackboard too."
        t_done )
};
const txt_cmd_s EarlsPokemonAcademyGameboyKid1Text[] = {
    text_start("I traded my best"
        t_line "#MON to the"
        t_cont "guy beside me."
        t_done )
};
const txt_cmd_s EarlsPokemonAcademyGameboyKid2Text[] = {
    text_start("Huh? The #MON I"
        t_line "just got is hold-"
        t_cont "ing something!"
        t_done )
};
const txt_cmd_s EarlsPokemonAcademyYoungster2Text[] = {
    text_start("A #MON holding"
        t_line "a BERRY will heal"
        t_cont "itself in battle."
        t_para "Many other items"
        t_line "can be held by"
        t_cont "#MON…"
        t_para "It sure is tough"
        t_line "taking notes…"
        t_done )
};
const txt_cmd_s AcademyBlackboardText[] = {
    text_start("The blackboard"
        t_line "describes #MON"
        t_para "status changes in"
        t_line "battle."
        t_done )
};
const txt_cmd_s AcademyBlackboardText2[] = {
    text_start("Read which topic?"
        t_done )
};
const txt_cmd_s AcademyPoisonText[] = {
    text_start("If poisoned, a"
        t_line "#MON steadily"
        t_cont "loses HP."
        t_para "Poison lingers"
        t_line "after the battle,"
        t_para "and HP is lost as"
        t_line "you walk."
        t_para "To cure it, use an"
        t_line "ANTIDOTE."
        t_done )
};
const txt_cmd_s AcademyParalysisText[] = {
    text_start("Paralysis reduces"
        t_line "speed and may"
        t_cont "prevent movement."
        t_para "It remains after"
        t_line "battle, so use"
        t_cont "a PARLYZ HEAL."
        t_done )
};
const txt_cmd_s AcademySleepText[] = {
    text_start("If asleep, your"
        t_line "#MON can't make"
        t_cont "a move."
        t_para "A sleeping #MON"
        t_line "doesn't wake up"
        t_cont "after battle."
        t_para "Wake it up with"
        t_line "an AWAKENING."
        t_done )
};
const txt_cmd_s AcademyBurnText[] = {
    text_start("A burn steadily"
        t_line "consumes HP."
        t_para "It also reduces"
        t_line "attack power."
        t_para "A burn lingers"
        t_line "after battle."
        t_para "Use a BURN HEAL as"
        t_line "the cure."
        t_done )
};
const txt_cmd_s AcademyFreezeText[] = {
    text_start("If your #MON is"
        t_line "frozen, it can't"
        t_cont "do a thing."
        t_para "It remains frozen"
        t_line "after battle."
        t_para "Thaw it out with"
        t_line "an ICE HEAL."
        t_done )
};
const txt_cmd_s AcademyNotebookText[] = {
    text_start("It's this kid's"
        t_line "notebook…"
        t_para "Catch #MON"
        t_line "using # BALLS."
        t_para "Up to six can be"
        t_line "in your party."
        t_para "Keep reading?"
        t_done )
};
const txt_cmd_s AcademyNotebookText1[] = {
    text_start("Before throwing a"
        t_line "# BALL, weaken"
        t_cont "the target first."
        t_para "A poisoned or"
        t_line "burned #MON is"
        t_cont "easier to catch."
        t_para "Keep reading?"
        t_done )
};
const txt_cmd_s AcademyNotebookText2[] = {
    text_start("Some moves may"
        t_line "cause confusion."
        t_para "Confusion may make"
        t_line "a #MON attack"
        t_cont "itself."
        t_para "Leaving battle"
        t_line "clears up any"
        t_cont "confusion."
        t_para "Keep reading?"
        t_done )
};
const txt_cmd_s AcademyNotebookText3[] = {
    text_start("People who catch"
        t_line "and use #MON"
        t_para "in battle are"
        t_line "#MON trainers."
        t_para "They are expected"
        t_line "to visit #MON"
        t_para "GYMS and defeat"
        t_line "other trainers."
        t_para "The next page"
        t_line "is… Blank!"
        t_para "Boy: E-he-he…"
        t_para "I haven't written"
        t_line "anymore…"
        t_done )
};
const txt_cmd_s AcademyStickerMachineText[] = {
    text_start("This super machine"
        t_line "prints data out as"
        t_para "stickers!"
        t_done )
    //db(0, 0) // filler
};
