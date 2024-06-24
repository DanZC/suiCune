#include "../constants.h"
#include "../util/scripting.h"
#include "Route45.h"
//// EVENTS
enum {
    ROUTE45_POKEFAN_M1 = 2,
    ROUTE45_POKEFAN_M2,
    ROUTE45_POKEFAN_M3,
    ROUTE45_POKEFAN_M4,
    ROUTE45_BLACK_BELT,
    ROUTE45_COOLTRAINER_M,
    ROUTE45_COOLTRAINER_F,
    ROUTE45_FRUIT_TREE,
    ROUTE45_POKE_BALL1,
    ROUTE45_POKE_BALL2,
    ROUTE45_POKE_BALL3,
    ROUTE45_POKE_BALL4,
    ROUTE45_YOUNGSTER,
};

const Script_fn_t Route45_SceneScripts[] = {
    0,
};

const struct MapCallback Route45_MapCallbacks[] = {
    0,
};

const struct MapScripts Route45_MapScripts = {
    .scene_script_count = 0, // lengthof(Route45_SceneScripts),
    .scene_scripts = Route45_SceneScripts,

    .callback_count = 0, // lengthof(Route45_MapCallbacks),
    .callbacks = Route45_MapCallbacks,
};

static const struct CoordEvent Route45_CoordEvents[] = {
    0,
};

static const struct BGEvent Route45_BGEvents[] = {
    bg_event(10, 4, BGEVENT_READ, &Route45Sign),
    bg_event(13, 80, BGEVENT_ITEM, &Route45HiddenPpUp),
};

static const struct WarpEventData Route45_WarpEvents[] = {
    warp_event(2, 5, DARK_CAVE_BLACKTHORN_ENTRANCE, 1),
};

static const struct ObjEvent Route45_ObjectEvents[] = {
    object_event(10, 16, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_TRAINER, 1, &TrainerHikerErik, -1),
    object_event(15, 65, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_TRAINER, 2, &TrainerHikerMichael, -1),
    object_event(5, 28, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_TRAINER, 2, &TrainerHikerParry, -1),
    object_event(9, 65, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_TRAINER, 1, &TrainerHikerTimothy, -1),
    object_event(11, 50, SPRITE_BLACK_BELT, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_TRAINER, 2, &TrainerBlackbeltKenji, -1),
    object_event(17, 18, SPRITE_COOLTRAINER_M, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 1, &TrainerCooltrainermRyan, -1),
    object_event(5, 36, SPRITE_COOLTRAINER_F, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 3, &TrainerCooltrainerfKelly, -1),
    object_event(16, 82, SPRITE_FRUIT_TREE, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Route45FruitTree, -1),
    object_event(6, 51, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &Route45Nugget, EVENT_ROUTE_45_NUGGET),
    object_event(5, 66, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &Route45Revive, EVENT_ROUTE_45_REVIVE),
    object_event(6, 20, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &Route45Elixer, EVENT_ROUTE_45_ELIXER),
    object_event(7, 33, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &Route45MaxPotion, EVENT_ROUTE_45_MAX_POTION),
    object_event(4, 70, SPRITE_YOUNGSTER, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &TrainerCamperQuentin, -1),
};

const struct MapEvents Route45_MapEvents = {
    .warp_event_count = lengthof(Route45_WarpEvents),
    .warp_events = Route45_WarpEvents,

    .coord_event_count = 0, // lengthof(Route45_CoordEvents),
    .coord_events = Route45_CoordEvents,

    .bg_event_count = lengthof(Route45_BGEvents),
    .bg_events = Route45_BGEvents,

    .obj_event_count = lengthof(Route45_ObjectEvents),
    .obj_events = Route45_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "Route45.h"

const struct TrainerObj TrainerBlackbeltKenji = {BLACKBELT_T, KENJI3, EVENT_BEAT_BLACKBELT_KENJI, BlackbeltKenji3SeenText, BlackbeltKenji3BeatenText, 0, TrainerBlackbeltKenji_Script};
bool TrainerBlackbeltKenji_Script(script_s* s) {
    SCRIPT_BEGIN
    loadvar(VAR_CALLERID, PHONE_BLACKBELT_KENJI)
    endifjustbattled
    opentext
    checkcellnum(PHONE_BLACKBELT_KENJI)
    iftrue(Registered)
    checkevent(EVENT_KENJI_ASKED_FOR_PHONE_NUMBER)
    iftrue(AskedAlready)
    special(SampleKenjiBreakCountdown)
    writetext(BlackbeltKenjiAfterBattleText)
    waitbutton
    setevent(EVENT_KENJI_ASKED_FOR_PHONE_NUMBER)
    scall(Route45AskNumber1M)
    goto AskForNumber;
AskedAlready:
    scall(Route45AskNumber2M)
AskForNumber:
    askforphonenumber(PHONE_BLACKBELT_KENJI)
    ifequal_jump(PHONE_CONTACTS_FULL, Route45PhoneFullM)
    ifequal_jump(PHONE_CONTACT_REFUSED, Route45NumberDeclinedM)
    gettrainername(STRING_BUFFER_3, BLACKBELT_T, KENJI3)
    scall(Route45RegisteredNumberM)
    sjump(Route45NumberAcceptedM)
Registered:
    readvar(VAR_KENJI_BREAK)
    ifnotequal_jump(1, Route45NumberAcceptedM)
    checktime(MORN)
    iftrue(Morning)
    checktime(NITE)
    iftrue(Night)
    checkevent(EVENT_KENJI_ON_BREAK)
    iffalse_jump(Route45NumberAcceptedM)
    scall(Route45GiftM)
    verbosegiveitem(PP_UP, 1)
    iffalse(NoRoom)
    clearevent(EVENT_KENJI_ON_BREAK)
    special(SampleKenjiBreakCountdown)
    sjump(Route45NumberAcceptedM)
Morning:
    writetext(BlackbeltKenjiMorningText)
    waitbutton
    closetext
    s_end
Night:
    writetext(BlackbeltKenjiNightText)
    waitbutton
    closetext
    s_end
NoRoom:
    sjump(Route45PackFullM)
    SCRIPT_END
}
bool Route45AskNumber1M(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(AskNumber1MScript)
    s_end
    SCRIPT_END
}
bool Route45AskNumber2M(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(AskNumber2MScript)
    s_end
    SCRIPT_END
}
bool Route45RegisteredNumberM(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(RegisteredNumberMScript)
    s_end
    SCRIPT_END
}
bool Route45NumberAcceptedM(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(NumberAcceptedMScript)
    s_end
    SCRIPT_END
}
bool Route45NumberDeclinedM(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(NumberDeclinedMScript)
    s_end
    SCRIPT_END
}
bool Route45PhoneFullM(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PhoneFullMScript)
    s_end
    SCRIPT_END
}
bool Route45RematchM(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(RematchMScript)
    s_end
    SCRIPT_END
}
bool Route45GiftM(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(GiftMScript)
    s_end
    SCRIPT_END
}
bool Route45PackFullM(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PackFullMScript)
    s_end
    SCRIPT_END
}
bool HikerParryHasIron(script_s* s) {
    SCRIPT_BEGIN
    setevent(EVENT_PARRY_IRON)
    jumpstd(PackFullMScript)
    s_end
    SCRIPT_END
}
bool Route45RematchGiftM(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(RematchGiftMScript)
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerHikerErik = {HIKER, ERIK, EVENT_BEAT_HIKER_ERIK, HikerErikSeenText, HikerErikBeatenText, 0, TrainerHikerErik_Script};
bool TrainerHikerErik_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(HikerErikAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerHikerMichael = {HIKER, MICHAEL, EVENT_BEAT_HIKER_MICHAEL, HikerMichaelSeenText, HikerMichaelBeatenText, 0, TrainerHikerMichael_Script};
bool TrainerHikerMichael_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(HikerMichaelAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerHikerParry = {HIKER, PARRY3, EVENT_BEAT_HIKER_PARRY, HikerParry3SeenText, HikerParry3BeatenText, 0, TrainerHikerParry_Script};
bool TrainerHikerParry_Script(script_s* s) {
    SCRIPT_BEGIN
    loadvar(VAR_CALLERID, PHONE_HIKER_PARRY)
    endifjustbattled
    opentext
    checkflag(ENGINE_PARRY_READY_FOR_REMATCH)
    iftrue(WantsBattle)
    checkcellnum(PHONE_HIKER_PARRY)
    iftrue_jump(Route45NumberAcceptedM)
    checkevent(EVENT_PARRY_ASKED_FOR_PHONE_NUMBER)
    iftrue(AskedAlready)
    writetext(HikerParryAfterBattleText)
    promptbutton
    setevent(EVENT_PARRY_ASKED_FOR_PHONE_NUMBER)
    scall(Route45AskNumber1M)
    goto AskForNumber;
AskedAlready:
    scall(Route45AskNumber2M)
AskForNumber:
    askforphonenumber(PHONE_HIKER_PARRY)
    ifequal_jump(PHONE_CONTACTS_FULL, Route45PhoneFullM)
    ifequal_jump(PHONE_CONTACT_REFUSED, Route45NumberDeclinedM)
    gettrainername(STRING_BUFFER_3, HIKER, PARRY1)
    scall(Route45RegisteredNumberM)
    sjump(Route45NumberAcceptedM)
WantsBattle:
    scall(Route45RematchM)
    winlosstext(HikerParry3BeatenText, 0)
    readmem(wram_ptr(wParryFightCount))
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
    loadtrainer(HIKER, PARRY3)
    startbattle
    reloadmapafterbattle
    loadmem(wram_ptr(wParryFightCount), 1)
    clearflag(ENGINE_PARRY_READY_FOR_REMATCH)
    s_end
LoadFight1:
    loadtrainer(HIKER, PARRY1)
    startbattle
    reloadmapafterbattle
    loadmem(wram_ptr(wParryFightCount), 2)
    clearflag(ENGINE_PARRY_READY_FOR_REMATCH)
    s_end
LoadFight2:
    loadtrainer(HIKER, PARRY2)
    startbattle
    reloadmapafterbattle
    clearflag(ENGINE_PARRY_READY_FOR_REMATCH)
    checkevent(EVENT_PARRY_IRON)
    iftrue(HasIron)
    checkevent(EVENT_GOT_IRON_FROM_PARRY)
    iftrue(GotIron)
    scall(Route45RematchGiftM)
    verbosegiveitem(IRON, 1)
    iffalse_jump(HikerParryHasIron)
    setevent(EVENT_GOT_IRON_FROM_PARRY)
    sjump(Route45NumberAcceptedM)
GotIron:
    s_end
HasIron:
    opentext
    writetext(HikerParryGivesIronText)
    waitbutton
    verbosegiveitem(IRON, 1)
    iffalse_jump(HikerParryHasIron)
    clearevent(EVENT_PARRY_IRON)
    setevent(EVENT_GOT_IRON_FROM_PARRY)
    sjump(Route45NumberAcceptedM)
    SCRIPT_END
}
const struct TrainerObj TrainerHikerTimothy = {HIKER, TIMOTHY, EVENT_BEAT_HIKER_TIMOTHY, HikerTimothySeenText, HikerTimothyBeatenText, 0, TrainerHikerTimothy_Script};
bool TrainerHikerTimothy_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(HikerTimothyAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerCooltrainermRyan = {COOLTRAINERM, RYAN, EVENT_BEAT_COOLTRAINERM_RYAN, CooltrainermRyanSeenText, CooltrainermRyanBeatenText, 0, TrainerCooltrainermRyan_Script};
bool TrainerCooltrainermRyan_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(CooltrainermRyanAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerCooltrainerfKelly = {COOLTRAINERF, KELLY, EVENT_BEAT_COOLTRAINERF_KELLY, CooltrainerfKellySeenText, CooltrainerfKellyBeatenText, 0, TrainerCooltrainerfKelly_Script};
bool TrainerCooltrainerfKelly_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(CooltrainerfKellyAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool TrainerCamperQuentin(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_BEAT_CAMPER_QUENTIN)
    iftrue(Defeated)
    writetext(CamperQuentinSeenText)
    waitbutton
    closetext
    winlosstext(CamperQuentinBeatenText, 0)
    loadtrainer(CAMPER, QUENTIN)
    startbattle
    reloadmapafterbattle
    setevent(EVENT_BEAT_CAMPER_QUENTIN)
    closetext
    s_end
Defeated:
    writetext(CamperQuentinAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Route45DummyScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(Route45DummyText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Route45Sign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route45SignText)
    SCRIPT_END
}
bool Route45FruitTree(script_s* s) {
    SCRIPT_BEGIN
    fruittree(FRUITTREE_ROUTE_45)
    SCRIPT_END
}
const struct ItemBall Route45Nugget = {NUGGET, 1};
const struct ItemBall Route45Revive = {REVIVE, 1};
const struct ItemBall Route45Elixer = {ELIXER, 1};
const struct ItemBall Route45MaxPotion = {MAX_POTION, 1};
const struct HiddenItem Route45HiddenPpUp = {PP_UP, EVENT_ROUTE_45_HIDDEN_PP_UP};
const txt_cmd_s HikerErikSeenText[] = {
    text_start("Be prepared for"
        t_line "anything!"
        t_para "Let me see if your"
        t_line "#MON have been"
        t_cont "raised properly!"
        t_done )
};
const txt_cmd_s HikerErikBeatenText[] = {
    text_start("Oh, I lost that!"
        t_done )
};
const txt_cmd_s HikerErikAfterBattleText[] = {
    text_start("I'll head back to"
        t_line "BLACKTHORN's ICE"
        t_para "PATH and train"
        t_line "some more."
        t_done )
};
const txt_cmd_s HikerMichaelSeenText[] = {
    text_start("Yo! You're spunky!"
        t_line "But you know what?"
        t_para "When it comes to"
        t_line "sheer spunkiness,"
        t_cont "I'm the man!"
        t_done )
};
const txt_cmd_s HikerMichaelBeatenText[] = {
    text_start("My #MON weren't"
        t_line "spunky enough!"
        t_done )
};
const txt_cmd_s HikerMichaelAfterBattleText[] = {
    text_start("Boy, do I love"
        t_line "HP UP! Mmmm, yum!"
        t_para "I keep drinking my"
        t_line "#MON's!"
        t_para "I can't help it!"
        t_done )
};
const txt_cmd_s HikerParry3SeenText[] = {
    text_start("My #MON are"
        t_line "power packed!"
        t_done )
};
const txt_cmd_s HikerParry3BeatenText[] = {
    text_start("Wahahah! I'm the"
        t_line "big loser!"
        t_done )
};
const txt_cmd_s HikerParryAfterBattleText[] = {
    text_start("I'm not much good"
        t_line "at thinking, see?"
        t_para "So, I just plow"
        t_line "ahead with power!"
        t_done )
};
const txt_cmd_s HikerTimothySeenText[] = {
    text_start("Why do I climb"
        t_line "mountains?"
        t_para "Because they're"
        t_line "there."
        t_para "Why do I train"
        t_line "#MON?"
        t_para "Because they're"
        t_line "there!"
        t_done )
};
const txt_cmd_s HikerTimothyBeatenText[] = {
    text_start("Losses…"
        t_line "They're there too!"
        t_done )
};
const txt_cmd_s HikerTimothyAfterBattleText[] = {
    text_start("The best thing to"
        t_line "ever happen to me"
        t_para "was discovering"
        t_line "#MON."
        t_done )
};
const txt_cmd_s HikerParryGivesIronText[] = {
    text_start("I just can't find"
        t_line "a way to win!"
        t_para "Keep it up!"
        t_para "Oh, and take this"
        t_line "--it's the gift"
        t_para "you couldn't take"
        t_line "when we last met."
        t_done )
};
const txt_cmd_s BlackbeltKenji3SeenText[] = {
    text_start("I was training"
        t_line "here alone."
        t_para "Behold the fruits"
        t_line "of my labor!"
        t_done )
};
const txt_cmd_s BlackbeltKenji3BeatenText[] = {
    text_start("Waaaargh!"
        t_done )
};
const txt_cmd_s BlackbeltKenjiAfterBattleText[] = {
    text_start("This calls for"
        t_line "extreme measures."
        t_para "I must take to the"
        t_line "hills and train in"
        t_cont "solitude."
        t_done )
};
const txt_cmd_s BlackbeltKenjiMorningText[] = {
    text_start("I'm going to train"
        t_line "a bit more before"
        t_cont "I break for lunch."
        t_done )
};
const txt_cmd_s BlackbeltKenjiNightText[] = {
    text_start("We had plenty of"
        t_line "rest at lunch, so"
        t_para "now we're all"
        t_line "ready to go again!"
        t_para "We're going to"
        t_line "train again!"
        t_done )
};
const txt_cmd_s CooltrainermRyanSeenText[] = {
    text_start("What are your"
        t_line "thoughts on rais-"
        t_cont "ing #MON?"
        t_done )
};
const txt_cmd_s CooltrainermRyanBeatenText[] = {
    text_start("You've won my"
        t_line "respect."
        t_done )
};
const txt_cmd_s CooltrainermRyanAfterBattleText[] = {
    text_start("I see you're rais-"
        t_line "ing your #MON"
        t_cont "with care."
        t_para "The bond you build"
        t_line "will save you in"
        t_cont "tough situations."
        t_done )
};
const txt_cmd_s CooltrainerfKellySeenText[] = {
    text_start("What is your"
        t_line "battle strategy?"
        t_para "It is foolish to"
        t_line "use strong moves"
        t_cont "indiscriminately."
        t_done )
};
const txt_cmd_s CooltrainerfKellyBeatenText[] = {
    text_start("Fine. I lost."
        t_done )
};
const txt_cmd_s CooltrainerfKellyAfterBattleText[] = {
    text_start("I'm not in favor"
        t_line "of overly power-"
        t_cont "ful moves."
        t_para "I want to win, but"
        t_line "I also don't want"
        t_cont "to harm #MON."
        t_done )
};
const txt_cmd_s Route45DummyText[] = {
    text_start("I'm really, really"
        t_line "tough!"
        t_para "Is there anywhere"
        t_line "I can prove how"
        t_cont "tough I really am?"
        t_done )
};
const txt_cmd_s CamperQuentinSeenText[] = {
    text_start("I'm really, really"
        t_line "tough!"
        t_done )
};
const txt_cmd_s CamperQuentinBeatenText[] = {
    text_start("I was tough at the"
        t_line "BATTLE TOWER…"
        t_done )
};
const txt_cmd_s CamperQuentinAfterBattleText[] = {
    text_start("Have you been to"
        t_line "the BATTLE TOWER?"
        t_para "I never, ever lose"
        t_line "there, but…"
        t_done )
};
const txt_cmd_s Route45SignText[] = {
    text_start("ROUTE 45"
        t_line "MOUNTAIN RD. AHEAD"
        t_done )
    //db(0, 0) // filler
};
