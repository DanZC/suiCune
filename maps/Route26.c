#include "../constants.h"
#include "../util/scripting.h"
#include "Route26.h"
//// EVENTS
enum {
    ROUTE26_COOLTRAINER_M1 = 2,
    ROUTE26_COOLTRAINER_M2,
    ROUTE26_COOLTRAINER_F1,
    ROUTE26_COOLTRAINER_F2,
    ROUTE26_YOUNGSTER,
    ROUTE26_FISHER,
    ROUTE26_FRUIT_TREE,
    ROUTE26_POKE_BALL,
};

const Script_fn_t Route26_SceneScripts[] = {
    0,
};

const struct MapCallback Route26_MapCallbacks[] = {
    0,
};

const struct MapScripts Route26_MapScripts = {
    .scene_script_count = 0, // lengthof(Route26_SceneScripts),
    .scene_scripts = Route26_SceneScripts,

    .callback_count = 0, // lengthof(Route26_MapCallbacks),
    .callbacks = Route26_MapCallbacks,
};

static const struct CoordEvent Route26_CoordEvents[] = {
    0,
};

static const struct BGEvent Route26_BGEvents[] = {
    bg_event(8, 6, BGEVENT_READ, &Route26Sign),
};

static const struct WarpEventData Route26_WarpEvents[] = {
    warp_event(7, 5, VICTORY_ROAD_GATE, 3),
    warp_event(15, 57, ROUTE_26_HEAL_HOUSE, 1),
    warp_event(5, 71, DAY_OF_WEEK_SIBLINGS_HOUSE, 1),
};

static const struct ObjEvent Route26_ObjectEvents[] = {
    object_event(14, 24, SPRITE_COOLTRAINER_M, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 2, &TrainerCooltrainermJake, -1),
    object_event(9, 38, SPRITE_COOLTRAINER_M, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 3, &TrainerCooltrainermGaven3, -1),
    object_event(10, 56, SPRITE_COOLTRAINER_F, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 3, &TrainerCooltrainerfJoyce, -1),
    object_event(5, 8, SPRITE_COOLTRAINER_F, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 4, &TrainerCooltrainerfBeth1, -1),
    object_event(13, 79, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 2, &TrainerPsychicRichard, -1),
    object_event(10, 92, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 3, &TrainerFisherScott, -1),
    object_event(14, 54, SPRITE_FRUIT_TREE, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Route26FruitTree, -1),
    object_event(9, 15, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &Route26MaxElixer, EVENT_ROUTE_26_MAX_ELIXER),
};

const struct MapEvents Route26_MapEvents = {
    .warp_event_count = lengthof(Route26_WarpEvents),
    .warp_events = Route26_WarpEvents,

    .coord_event_count = 0, // lengthof(Route26_CoordEvents),
    .coord_events = Route26_CoordEvents,

    .bg_event_count = lengthof(Route26_BGEvents),
    .bg_events = Route26_BGEvents,

    .obj_event_count = lengthof(Route26_ObjectEvents),
    .obj_events = Route26_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "Route26.h"

const struct TrainerObj TrainerCooltrainermJake = {COOLTRAINERM, JAKE, EVENT_BEAT_COOLTRAINERM_JAKE, CooltrainermJakeSeenText, CooltrainermJakeBeatenText, 0, TrainerCooltrainermJake_Script};
bool TrainerCooltrainermJake_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(CooltrainermJakeAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerCooltrainermGaven3 = {COOLTRAINERM, GAVEN3, EVENT_BEAT_COOLTRAINERM_GAVEN, CooltrainermGaven3SeenText, CooltrainermGaven3BeatenText, 0, TrainerCooltrainermGaven3_Script};
bool TrainerCooltrainermGaven3_Script(script_s* s) {
    SCRIPT_BEGIN
    loadvar(VAR_CALLERID, PHONE_COOLTRAINERM_GAVEN)
    endifjustbattled
    opentext
    checkflag(ENGINE_GAVEN_READY_FOR_REMATCH)
    iftrue(WantsBattle)
    checkcellnum(PHONE_COOLTRAINERM_GAVEN)
    iftrue(NumberAccepted)
    checkevent(EVENT_GAVEN_ASKED_FOR_PHONE_NUMBER)
    iftrue(AskedAlready)
    writetext(CooltrainermGavenAfterText)
    promptbutton
    setevent(EVENT_GAVEN_ASKED_FOR_PHONE_NUMBER)
    scall_local(AskNumber1);
    goto AskForNumber;
AskedAlready:
    scall_local(AskNumber2);
AskForNumber:
    askforphonenumber(PHONE_COOLTRAINERM_GAVEN)
    ifequal(PHONE_CONTACTS_FULL, PhoneFull)
    ifequal(PHONE_CONTACT_REFUSED, NumberDeclined)
    gettrainername(STRING_BUFFER_3, COOLTRAINERM, GAVEN3)
    scall_local(RegisteredNumber);
    goto NumberAccepted;
WantsBattle:
    scall_local(Rematch);
    winlosstext(CooltrainermGaven3BeatenText, 0)
    readmem(wram_ptr(wGavenFightCount))
    ifequal(2, Fight2)
    ifequal(1, Fight1)
    ifequal(0, LoadFight0)
Fight2:
    checkevent(EVENT_RESTORED_POWER_TO_KANTO)
    iftrue(LoadFight2)
Fight1:
    checkevent(EVENT_BEAT_ELITE_FOUR)
    iftrue(LoadFight1)
LoadFight0:
    loadtrainer(COOLTRAINERM, GAVEN3)
    startbattle
    reloadmapafterbattle
    loadmem(wram_ptr(wGavenFightCount), 1)
    clearflag(ENGINE_GAVEN_READY_FOR_REMATCH)
    s_end
LoadFight1:
    loadtrainer(COOLTRAINERM, GAVEN1)
    startbattle
    reloadmapafterbattle
    loadmem(wram_ptr(wGavenFightCount), 2)
    clearflag(ENGINE_GAVEN_READY_FOR_REMATCH)
    s_end
LoadFight2:
    loadtrainer(COOLTRAINERM, GAVEN2)
    startbattle
    reloadmapafterbattle
    clearflag(ENGINE_GAVEN_READY_FOR_REMATCH)
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
Rematch:
    jumpstd(RematchMScript)
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerCooltrainerfJoyce = {COOLTRAINERF, JOYCE, EVENT_BEAT_COOLTRAINERF_JOYCE, CooltrainerfJoyceSeenText, CooltrainerfJoyceBeatenText, 0, TrainerCooltrainerfJoyce_Script};
bool TrainerCooltrainerfJoyce_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(CooltrainerfJoyceAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerCooltrainerfBeth1 = {COOLTRAINERF, BETH1, EVENT_BEAT_COOLTRAINERF_BETH, CooltrainerfBeth1SeenText, CooltrainerfBeth1BeatenText, 0, TrainerCooltrainerfBeth1_Script};
bool TrainerCooltrainerfBeth1_Script(script_s* s) {
    SCRIPT_BEGIN
    loadvar(VAR_CALLERID, PHONE_COOLTRAINERF_BETH)
    endifjustbattled
    opentext
    checkflag(ENGINE_BETH_READY_FOR_REMATCH)
    iftrue(WantsBattle)
    checkcellnum(PHONE_COOLTRAINERF_BETH)
    iftrue(NumberAccepted)
    checkevent(EVENT_BETH_ASKED_FOR_PHONE_NUMBER)
    iftrue(AskedAlready)
    writetext(CooltrainerfBethAfterText)
    promptbutton
    setevent(EVENT_BETH_ASKED_FOR_PHONE_NUMBER)
    scall_local(AskNumber1);
    goto AskForNumber;
AskedAlready:
    scall_local(AskNumber2);
AskForNumber:
    askforphonenumber(PHONE_COOLTRAINERF_BETH)
    ifequal(PHONE_CONTACTS_FULL, PhoneFull)
    ifequal(PHONE_CONTACT_REFUSED, NumberDeclined)
    gettrainername(STRING_BUFFER_3, COOLTRAINERF, BETH1)
    scall_local(RegisteredNumber);
    goto NumberAccepted;
WantsBattle:
    scall_local(Rematch);
    winlosstext(CooltrainerfBeth1BeatenText, 0)
    readmem(wram_ptr(wBethFightCount))
    ifequal(2, Fight2)
    ifequal(1, Fight1)
    ifequal(0, LoadFight0)
Fight2:
    checkevent(EVENT_RESTORED_POWER_TO_KANTO)
    iftrue(LoadFight2)
Fight1:
    checkevent(EVENT_BEAT_ELITE_FOUR)
    iftrue(LoadFight1)
LoadFight0:
    loadtrainer(COOLTRAINERF, BETH1)
    startbattle
    reloadmapafterbattle
    loadmem(wram_ptr(wBethFightCount), 1)
    clearflag(ENGINE_BETH_READY_FOR_REMATCH)
    s_end
LoadFight1:
    loadtrainer(COOLTRAINERF, BETH2)
    startbattle
    reloadmapafterbattle
    loadmem(wram_ptr(wBethFightCount), 2)
    clearflag(ENGINE_BETH_READY_FOR_REMATCH)
    s_end
LoadFight2:
    loadtrainer(COOLTRAINERF, BETH3)
    startbattle
    reloadmapafterbattle
    clearflag(ENGINE_BETH_READY_FOR_REMATCH)
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
Rematch:
    jumpstd(RematchFScript)
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerPsychicRichard = {PSYCHIC_T, RICHARD, EVENT_BEAT_PSYCHIC_RICHARD, PsychicRichardSeenText, PsychicRichardBeatenText, 0, TrainerPsychicRichard_Script};
bool TrainerPsychicRichard_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(PsychicRichardAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerFisherScott = {FISHER, SCOTT, EVENT_BEAT_FISHER_SCOTT, FisherScottSeenText, FisherScottBeatenText, 0, TrainerFisherScott_Script};
bool TrainerFisherScott_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(FisherScottAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Route26Sign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route26SignText)
    SCRIPT_END
}
bool Route26FruitTree(script_s* s) {
    SCRIPT_BEGIN
    fruittree(FRUITTREE_ROUTE_26)
    SCRIPT_END
}
const struct ItemBall Route26MaxElixer = {MAX_ELIXER, 1};
const txt_cmd_s CooltrainermJakeSeenText[] = {
    text_start("I'm making my"
        t_line "final preparations"
        t_para "for the #MON"
        t_line "LEAGUE."
        t_done )
};
const txt_cmd_s CooltrainermJakeBeatenText[] = {
    text_start("I blew it!"
        t_done )
};
const txt_cmd_s CooltrainermJakeAfterBattleText[] = {
    text_start("It's going to be"
        t_line "tough to win at"
        t_cont "the LEAGUE."
        t_para "I need to do some"
        t_line "more training."
        t_para "I hear that the"
        t_line "LEAGUE's ELITE"
        t_para "FOUR are tougher"
        t_line "than GYM LEADERS."
        t_done )
};
const txt_cmd_s CooltrainermGaven3SeenText[] = {
    text_start("By experiencing"
        t_line "tough battles, you"
        t_cont "gain power."
        t_done )
};
const txt_cmd_s CooltrainermGaven3BeatenText[] = {
    text_start("Gaah! Life is even"
        t_line "tougher!"
        t_done )
};
const txt_cmd_s CooltrainermGavenAfterText[] = {
    text_start("To get to #MON"
        t_line "LEAGUE, you have"
        t_para "to get through"
        t_line "VICTORY ROAD."
        t_para "But VICTORY ROAD"
        t_line "is tough."
        t_para "Practically nobody"
        t_line "goes there!"
        t_done )
};
const txt_cmd_s CooltrainerfJoyceSeenText[] = {
    text_start("Since you've come"
        t_line "this far, you must"
        t_cont "be good."
        t_para "I'm going to give"
        t_line "this battle every-"
        t_cont "thing I've got!"
        t_done )
};
const txt_cmd_s CooltrainerfJoyceBeatenText[] = {
    text_start("No! I don't"
        t_line "believe this!"
        t_done )
};
const txt_cmd_s CooltrainerfJoyceAfterBattleText[] = {
    text_start("I've defeated"
        t_line "eight GYM LEADERS,"
        t_para "so I was feeling"
        t_line "confident."
        t_para "I'll have to try"
        t_line "harder next time."
        t_done )
};
const txt_cmd_s CooltrainerfBeth1SeenText[] = {
    text_start("I lost to a train-"
        t_line "er named <RIVAL>."
        t_para "He was really"
        t_line "strong, but…"
        t_para "It was as if he"
        t_line "absolutely had to"
        t_cont "win at any cost."
        t_para "I felt sorry for"
        t_line "his #MON."
        t_done )
};
const txt_cmd_s CooltrainerfBeth1BeatenText[] = {
    text_start("#MON aren't"
        t_line "tools of war."
        t_done )
};
const txt_cmd_s CooltrainerfBethAfterText[] = {
    text_start("#MON are in-"
        t_line "valuable, lifelong"
        t_cont "partners."
        t_done )
};
const txt_cmd_s PsychicRichardSeenText[] = {
    text_start("Wow, look at all"
        t_line "those BADGES!"
        t_cont "I'm impressed."
        t_para "But you're not"
        t_line "satisfied by just"
        t_para "collecting them,"
        t_line "right?"
        t_done )
};
const txt_cmd_s PsychicRichardBeatenText[] = {
    text_start("Good battle!"
        t_done )
};
const txt_cmd_s PsychicRichardAfterBattleText[] = {
    text_start("People and #MON"
        t_line "grow from their"
        t_cont "experiences."
        t_para "Don't get lazy and"
        t_line "complacent."
        t_done )
};
const txt_cmd_s FisherScottSeenText[] = {
    text_start("I'm feeling great"
        t_line "today!"
        t_para "I feel like I"
        t_line "could boot even"
        t_cont "the LEAGUE CHAMP!"
        t_done )
};
const txt_cmd_s FisherScottBeatenText[] = {
    text_start("No! Not in this"
        t_line "battle!"
        t_done )
};
const txt_cmd_s FisherScottAfterBattleText[] = {
    text_start("Just like in fish-"
        t_line "ing, it's all over"
        t_para "in #MON if you"
        t_line "give up."
        t_done )
};
const txt_cmd_s Route26SignText[] = {
    text_start("ROUTE 26"
        t_para "#MON LEAGUE"
        t_line "RECEPTION GATE"
        t_done )
    //db(0, 0) // filler
};
