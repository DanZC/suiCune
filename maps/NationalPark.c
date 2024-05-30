#include "../constants.h"
#include "../util/scripting.h"
#include "NationalPark.h"
//// EVENTS
enum {
    NATIONALPARK_LASS1 = 2,
    NATIONALPARK_POKEFAN_F1,
    NATIONALPARK_TEACHER1,
    NATIONALPARK_YOUNGSTER1,
    NATIONALPARK_YOUNGSTER2,
    NATIONALPARK_TEACHER2,
    NATIONALPARK_PERSIAN,
    NATIONALPARK_YOUNGSTER3,
    NATIONALPARK_POKEFAN_F2,
    NATIONALPARK_POKEFAN_M,
    NATIONALPARK_LASS2,
    NATIONALPARK_POKE_BALL1,
    NATIONALPARK_GAMEBOY_KID,
    NATIONALPARK_POKE_BALL2,
};

const Script_fn_t NationalPark_SceneScripts[] = {
    0,
};

const struct MapCallback NationalPark_MapCallbacks[] = {
    0,
};

const struct MapScripts NationalPark_MapScripts = {
    .scene_script_count = 0, // lengthof(NationalPark_SceneScripts),
    .scene_scripts = NationalPark_SceneScripts,

    .callback_count = 0, // lengthof(NationalPark_MapCallbacks),
    .callbacks = NationalPark_MapCallbacks,
};

static const struct CoordEvent NationalPark_CoordEvents[] = {
    0,
};

static const struct BGEvent NationalPark_BGEvents[] = {
    bg_event(14, 44, BGEVENT_READ, &NationalParkRelaxationSquareSign),
    bg_event(27, 31, BGEVENT_READ, &NationalParkBattleNoticeSign),
    bg_event(6, 47, BGEVENT_ITEM, &NationalParkHiddenFullHeal),
    bg_event(12, 4, BGEVENT_READ, &NationalParkTrainerTipsSign),
};

static const struct WarpEventData NationalPark_WarpEvents[] = {
    warp_event(33, 18, ROUTE_36_NATIONAL_PARK_GATE, 1),
    warp_event(33, 19, ROUTE_36_NATIONAL_PARK_GATE, 2),
    warp_event(10, 47, ROUTE_35_NATIONAL_PARK_GATE, 1),
    warp_event(11, 47, ROUTE_35_NATIONAL_PARK_GATE, 2),
};

static const struct ObjEvent NationalPark_ObjectEvents[] = {
    object_event(15, 24, SPRITE_LASS, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &NationalParkLassScript, -1),
    object_event(14, 4, SPRITE_POKEFAN_F, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &NationalParkPokefanFScript, -1),
    object_event(27, 40, SPRITE_TEACHER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &NationalParkTeacher1Script, -1),
    object_event(11, 41, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &NationalParkYoungster1Script, -1),
    object_event(10, 41, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &NationalParkYoungster2Script, -1),
    object_event(17, 41, SPRITE_TEACHER, SPRITEMOVEDATA_WANDER, 1, 2, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &NationalParkTeacher2Script, -1),
    object_event(26, 40, SPRITE_GROWLITHE, SPRITEMOVEDATA_POKEMON, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &NationalParkPersian, -1),
    object_event(27, 23, SPRITE_YOUNGSTER, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerSchoolboyJack1, -1),
    object_event(18, 29, SPRITE_POKEFAN_F, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 2, &TrainerPokefanfBeverly1, -1),
    object_event(16, 9, SPRITE_POKEFAN_M, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 2, &TrainerPokefanmWilliam, -1),
    object_event(8, 14, SPRITE_LASS, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerLassKrise, -1),
    object_event(35, 12, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &NationalParkParlyzHeal, EVENT_NATIONAL_PARK_PARLYZ_HEAL),
    object_event(26, 6, SPRITE_GAMEBOY_KID, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &NationalParkGameboyKidScript, -1),
    object_event(1, 43, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &NationalParkTMDig, EVENT_NATIONAL_PARK_TM_DIG),
};

const struct MapEvents NationalPark_MapEvents = {
    .warp_event_count = lengthof(NationalPark_WarpEvents),
    .warp_events = NationalPark_WarpEvents,

    .coord_event_count = 0, // lengthof(NationalPark_CoordEvents),
    .coord_events = NationalPark_CoordEvents,

    .bg_event_count = lengthof(NationalPark_BGEvents),
    .bg_events = NationalPark_BGEvents,

    .obj_event_count = lengthof(NationalPark_ObjectEvents),
    .obj_events = NationalPark_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "NationalPark.h"

bool NationalParkLassScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(NationalParkLassText)
    SCRIPT_END
}
bool NationalParkPokefanFScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(NationalParkPokefanFText)
    SCRIPT_END
}
bool NationalParkTeacher1Script(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_QUICK_CLAW)
    iftrue(GotQuickClaw)
    writetext(NationalParkTeacher1Text)
    promptbutton
    verbosegiveitem(QUICK_CLAW, 1)
    iffalse(NoRoom)
    setevent(EVENT_GOT_QUICK_CLAW)
GotQuickClaw:
    writetext(NationalParkTeacher1Text_GotQuickClaw)
    waitbutton
NoRoom:
    closetext
    s_end
    SCRIPT_END
}
bool NationalParkYoungster1Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(NationalParkYoungster1Text)
    SCRIPT_END
}
bool NationalParkYoungster2Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(NationalParkYoungster2Text)
    SCRIPT_END
}
bool NationalParkTeacher2Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(NationalParkTeacher2Text)
    SCRIPT_END
}
bool NationalParkPersian(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(NationalParkPersianText)
    playcry(PERSIAN)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool NationalParkGameboyKidScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(NationalParkGameboyKidText)
    waitbutton
    closetext
    turnobject(NATIONALPARK_GAMEBOY_KID, DOWN)
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSchoolboyJack1 = {SCHOOLBOY, JACK1, EVENT_BEAT_SCHOOLBOY_JACK, SchoolboyJack1SeenText, SchoolboyJack1BeatenText, 0, TrainerSchoolboyJack1_Script};
bool TrainerSchoolboyJack1_Script(script_s* s) {
    SCRIPT_BEGIN
    loadvar(VAR_CALLERID, PHONE_SCHOOLBOY_JACK)
    endifjustbattled
    opentext
    checkflag(ENGINE_JACK_READY_FOR_REMATCH)
    iftrue(Rematch)
    checkcellnum(PHONE_SCHOOLBOY_JACK)
    iftrue(NumberAccepted)
    checkevent(EVENT_JACK_ASKED_FOR_PHONE_NUMBER)
    iftrue(AskAgain)
    writetext(SchoolboyJackTradeMonText)
    promptbutton
    setevent(EVENT_JACK_ASKED_FOR_PHONE_NUMBER)
    scall_local(AskNumber1);
    goto RequestNumber;
AskAgain:
    scall_local(AskNumber2);
RequestNumber:
    askforphonenumber(PHONE_SCHOOLBOY_JACK)
    ifequal(PHONE_CONTACTS_FULL, PhoneFull)
    ifequal(PHONE_CONTACT_REFUSED, NumberDeclined)
    gettrainername(STRING_BUFFER_3, SCHOOLBOY, JACK1)
    scall_local(RegisteredNumber);
    goto NumberAccepted;
Rematch:
    scall_local(RematchStd);
    winlosstext(SchoolboyJack1BeatenText, 0)
    readmem(wram_ptr(wJackFightCount))
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
    checkevent(EVENT_CLEARED_RADIO_TOWER)
    iftrue(LoadFight2)
Fight1:
    checkflag(ENGINE_FLYPOINT_OLIVINE)
    iftrue(LoadFight1)
LoadFight0:
    loadtrainer(SCHOOLBOY, JACK1)
    startbattle
    reloadmapafterbattle
    loadmem(wram_ptr(wJackFightCount), 1)
    clearflag(ENGINE_JACK_READY_FOR_REMATCH)
    s_end
LoadFight1:
    loadtrainer(SCHOOLBOY, JACK2)
    startbattle
    reloadmapafterbattle
    loadmem(wram_ptr(wJackFightCount), 2)
    clearflag(ENGINE_JACK_READY_FOR_REMATCH)
    s_end
LoadFight2:
    loadtrainer(SCHOOLBOY, JACK3)
    startbattle
    reloadmapafterbattle
    loadmem(wram_ptr(wJackFightCount), 3)
    clearflag(ENGINE_JACK_READY_FOR_REMATCH)
    s_end
LoadFight3:
    loadtrainer(SCHOOLBOY, JACK4)
    startbattle
    reloadmapafterbattle
    loadmem(wram_ptr(wJackFightCount), 4)
    clearflag(ENGINE_JACK_READY_FOR_REMATCH)
    s_end
LoadFight4:
    loadtrainer(SCHOOLBOY, JACK5)
    startbattle
    reloadmapafterbattle
    clearflag(ENGINE_JACK_READY_FOR_REMATCH)
    s_end
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
RematchStd:
    jumpstd(RematchMScript)
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerPokefanmWilliam = {POKEFANM, WILLIAM, EVENT_BEAT_POKEFANM_WILLIAM, PokefanmWilliamSeenText, PokefanmWilliamBeatenText, 0, TrainerPokefanmWilliam_Script};
bool TrainerPokefanmWilliam_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(PokefanmWilliamAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerPokefanfBeverly1 = {POKEFANF, BEVERLY1, EVENT_BEAT_POKEFANF_BEVERLY, PokefanfBeverly1SeenText, PokefanfBeverly1BeatenText, 0, TrainerPokefanfBeverly1_Script};
bool TrainerPokefanfBeverly1_Script(script_s* s) {
    SCRIPT_BEGIN
    loadvar(VAR_CALLERID, PHONE_POKEFAN_BEVERLY)
    endifjustbattled
    opentext
    checkflag(ENGINE_BEVERLY_HAS_NUGGET)
    iftrue(GiveNugget)
    checkcellnum(PHONE_POKEFAN_BEVERLY)
    iftrue(NumberAccepted)
    //checkpoke(MARILL)
    iffalse(NoMarill)
    checkevent(EVENT_BEVERLY_ASKED_FOR_PHONE_NUMBER)
    iftrue(AskAgain)
    writetext(PokefanBeverlyCuteMonText)
    promptbutton
    setevent(EVENT_BEVERLY_ASKED_FOR_PHONE_NUMBER)
    scall_local(AskNumber1);
    goto RequestNumber;
AskAgain:
    scall_local(AskNumber2);
RequestNumber:
    askforphonenumber(PHONE_POKEFAN_BEVERLY)
    ifequal(PHONE_CONTACTS_FULL, PhoneFull)
    ifequal(PHONE_CONTACT_REFUSED, NumberDeclined)
    gettrainername(STRING_BUFFER_3, POKEFANF, BEVERLY1)
    scall_local(RegisteredNumber);
    goto NumberAccepted;
GiveNugget:
    scall_local(Gift);
    verbosegiveitem(NUGGET, 1)
    iffalse(NoRoom)
    clearflag(ENGINE_BEVERLY_HAS_NUGGET)
    goto NumberAccepted;
NoRoom:
    goto PackFull;
NoMarill:
    writetext(PokefanFBeverlyMarillFriendText)
    waitbutton
    closetext
    s_end
AskNumber1:
    jumpstd(AskNumber1FScript)
    s_end
AskNumber2:
    jumpstd(AskNumber2FScript)
    s_end
RegisteredNumber:
    jumpstd(RegisteredNumberFScript)
    s_end
NumberAccepted:
    jumpstd(NumberAcceptedFScript)
    s_end
NumberDeclined:
    jumpstd(NumberDeclinedFScript)
    s_end
PhoneFull:
    jumpstd(PhoneFullFScript)
    s_end
Gift:
    jumpstd(GiftFScript)
    s_end
PackFull:
    jumpstd(PackFullFScript)
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerLassKrise = {LASS, KRISE, EVENT_BEAT_LASS_KRISE, LassKriseSeenText, LassKriseBeatenText, 0, TrainerLassKrise_Script};
bool TrainerLassKrise_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(LassKriseAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool NationalParkRelaxationSquareSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(NationalParkRelaxationSquareText)
    SCRIPT_END
}
bool NationalParkBattleNoticeSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(NationalParkBattleNoticeText)
    SCRIPT_END
}
bool NationalParkTrainerTipsSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(NationalParkTrainerTipsText)
    SCRIPT_END
}
const struct ItemBall NationalParkParlyzHeal = {PARLYZ_HEAL, 1};
const struct ItemBall NationalParkTMDig = {TM_DIG, 1};
const struct HiddenItem NationalParkHiddenFullHeal = {FULL_HEAL, EVENT_NATIONAL_PARK_HIDDEN_FULL_HEAL};
const txt_cmd_s NationalParkLassText[] = {
    text_start("Look! Check out my"
        t_line "bag!"
        t_para "I printed out my"
        t_line "favorites from my"
        t_para "#DEX and stuck"
        t_line "them on my bag."
        t_done )
};
const txt_cmd_s NationalParkPokefanFText[] = {
    text_start("This is MAIL I got"
        t_line "from my daughter."
        t_cont "It cheers me up."
        t_done )
};
const txt_cmd_s NationalParkTeacher1Text[] = {
    text_start("Pay attention,"
        t_line "please!"
        t_para "…Oops, I have to"
        t_line "quit thinking like"
        t_para "a teacher all the"
        t_line "time."
        t_para "You must be a"
        t_line "#MON trainer."
        t_para "Since you're work-"
        t_line "ing so hard, I"
        t_para "want you to have"
        t_line "this."
        t_done )
};
const txt_cmd_s NationalParkTeacher1Text_GotQuickClaw[] = {
    text_start("Let a #MON hold"
        t_line "that QUICK CLAW."
        t_para "Sometimes it will"
        t_line "strike first"
        t_cont "during battle."
        t_done )
};
const txt_cmd_s NationalParkYoungster1Text[] = {
    text_start("I'm playing with"
        t_line "stickers I printed"
        t_cont "from my #DEX."
        t_done )
};
const txt_cmd_s NationalParkYoungster2Text[] = {
    text_start("I get the other"
        t_line "guy's #DEX"
        t_cont "sticker if I win."
        t_done )
};
const txt_cmd_s NationalParkTeacher2Text[] = {
    text_start("I take walks in"
        t_line "the PARK, but I"
        t_para "never go into the"
        t_line "grass."
        t_para "Trainers always"
        t_line "want to battle…"
        t_done )
};
const txt_cmd_s NationalParkPersianText[] = {
    text_start("PERSIAN: Fufushaa!"
        t_done )
};
const txt_cmd_s NationalParkGameboyKidText[] = {
    text_start("I'm printing out"
        t_line "my #DEX."
        t_para "You can also print"
        t_line "out stuff like"
        t_para "MAIL and your PC"
        t_line "BOXES."
        t_done )
};
const txt_cmd_s SchoolboyJack1SeenText[] = {
    text_start("The world of"
        t_line "#MON is deep."
        t_para "There are still"
        t_line "lots of things we"
        t_cont "don't know."
        t_para "But I know more"
        t_line "than you do!"
        t_done )
};
const txt_cmd_s SchoolboyJack1BeatenText[] = {
    text_start("Wha-wha-what?"
        t_done )
};
const txt_cmd_s SchoolboyJackTradeMonText[] = {
    text_start("There is a lot"
        t_line "to learn."
        t_para "For example…"
        t_para "There are " _s(NUM_TMS) " kinds"
        t_line "of TMs."
        t_para "Traded #MON"
        t_line "level up faster."
        t_done )
};
const txt_cmd_s PokefanfBeverly1SeenText[] = {
    text_start("My #MON are"
        t_line "simply darling."
        t_para "Let me tell you"
        t_line "how proud my"
        t_cont "darlings make me."
        t_done )
};
const txt_cmd_s PokefanfBeverly1BeatenText[] = {
    text_start("I can beat you in"
        t_line "pride, but…"
        t_done )
};
const txt_cmd_s PokefanBeverlyCuteMonText[] = {
    text_start("I must say, your"
        t_line "#MON are quite"
        t_cont "cute, too."
        t_done )
};
const txt_cmd_s PokefanmWilliamSeenText[] = {
    text_start("We adore our #-"
        t_line "MON, even if they"
        t_cont "dislike us."
        t_para "That's what being"
        t_line "a FAN is about."
        t_done )
};
const txt_cmd_s PokefanmWilliamBeatenText[] = {
    text_start("M-my #MON!"
        t_done )
};
const txt_cmd_s PokefanmWilliamAfterBattleText[] = {
    text_start("I lost the battle,"
        t_line "but my #MON win"
        t_para "the prize for"
        t_line "being most lovely."
        t_done )
};
const txt_cmd_s PokefanFBeverlyMarillFriendText[] = {
    text_start("My friend keeps a"
        t_line "MARILL!"
        t_para "I find them very"
        t_line "endearing."
        t_para "Oh, I wish for a"
        t_line "MARILL of my own…"
        t_done )
};
const txt_cmd_s LassKriseSeenText[] = {
    text_start("Hello? Why are you"
        t_line "staring at me?"
        t_para "Oh, a battle?"
        t_done )
};
const txt_cmd_s LassKriseBeatenText[] = {
    text_start("…Hmmm…"
        t_done )
};
const txt_cmd_s LassKriseAfterBattleText[] = {
    text_start("I thought you were"
        t_line "staring at me"
        t_cont "because I'm cute!"
        t_done )
};
const txt_cmd_s NationalParkRelaxationSquareText[] = {
    text_start("RELAXATION SQUARE"
        t_line "NATIONAL PARK"
        t_done )
};
const txt_cmd_s NationalParkBattleNoticeText[] = {
    text_start("What is this"
        t_line "notice?"
        t_para "Please battle only"
        t_line "in the grass."
        t_para "NATIONAL PARK"
        t_line "WARDEN'S OFFICE"
        t_done )
};
const txt_cmd_s NationalParkTrainerTipsText[] = {
    text_start("TRAINER TIPS"
        t_para "Print out MAIL by"
        t_line "opening it then"
        t_cont "pressing START."
        t_done )
    //db(0, 0) // filler
};
