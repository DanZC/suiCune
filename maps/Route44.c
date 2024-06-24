#include "../constants.h"
#include "../util/scripting.h"
#include "Route44.h"
//// EVENTS
enum {
    ROUTE44_FISHER1 = 2,
    ROUTE44_FISHER2,
    ROUTE44_YOUNGSTER1,
    ROUTE44_SUPER_NERD,
    ROUTE44_YOUNGSTER2,
    ROUTE44_COOLTRAINER_M,
    ROUTE44_COOLTRAINER_F,
    ROUTE44_FRUIT_TREE,
    ROUTE44_POKE_BALL1,
    ROUTE44_POKE_BALL2,
    ROUTE44_POKE_BALL3,
};

const Script_fn_t Route44_SceneScripts[] = {
    0,
};

const struct MapCallback Route44_MapCallbacks[] = {
    0,
};

const struct MapScripts Route44_MapScripts = {
    .scene_script_count = 0, // lengthof(Route44_SceneScripts),
    .scene_scripts = Route44_SceneScripts,

    .callback_count = 0, // lengthof(Route44_MapCallbacks),
    .callbacks = Route44_MapCallbacks,
};

static const struct CoordEvent Route44_CoordEvents[] = {
    0,
};

static const struct BGEvent Route44_BGEvents[] = {
    bg_event(53, 7, BGEVENT_READ, &Route44Sign1),
    bg_event(6, 10, BGEVENT_READ, &Route44Sign2),
    bg_event(32, 9, BGEVENT_ITEM, &Route44HiddenElixer),
};

static const struct WarpEventData Route44_WarpEvents[] = {
    warp_event(56, 7, ICE_PATH_1F, 1),
};

static const struct ObjEvent Route44_ObjectEvents[] = {
    object_event(35, 3, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 1, &TrainerFisherWilton1, -1),
    object_event(19, 13, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 1, &TrainerFisherEdgar, -1),
    object_event(10, 9, SPRITE_YOUNGSTER, SPRITEMOVEDATA_SPINCLOCKWISE, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerPsychicPhil, -1),
    object_event(43, 2, SPRITE_SUPER_NERD, SPRITEMOVEDATA_SPINCLOCKWISE, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 3, &TrainerPokemaniacZach, -1),
    object_event(51, 5, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 2, &TrainerBirdKeeperVance1, -1),
    object_event(41, 15, SPRITE_COOLTRAINER_M, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 5, &TrainerCooltrainermAllen, -1),
    object_event(31, 14, SPRITE_COOLTRAINER_F, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 5, &TrainerCooltrainerfCybil, -1),
    object_event(9, 5, SPRITE_FRUIT_TREE, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Route44FruitTree, -1),
    object_event(30, 8, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &Route44MaxRevive, EVENT_ROUTE_44_MAX_REVIVE),
    object_event(45, 4, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &Route44UltraBall, EVENT_ROUTE_44_ULTRA_BALL),
    object_event(14, 9, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &Route44MaxRepel, EVENT_ROUTE_44_MAX_REPEL),
};

const struct MapEvents Route44_MapEvents = {
    .warp_event_count = lengthof(Route44_WarpEvents),
    .warp_events = Route44_WarpEvents,

    .coord_event_count = 0, // lengthof(Route44_CoordEvents),
    .coord_events = Route44_CoordEvents,

    .bg_event_count = lengthof(Route44_BGEvents),
    .bg_events = Route44_BGEvents,

    .obj_event_count = lengthof(Route44_ObjectEvents),
    .obj_events = Route44_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "Route44.h"

const struct TrainerObj TrainerBirdKeeperVance1 = {BIRD_KEEPER, VANCE1, EVENT_BEAT_BIRD_KEEPER_VANCE, BirdKeeperVance1SeenText, BirdKeeperVance1BeatenText, 0, TrainerBirdKeeperVance1_Script};
bool TrainerBirdKeeperVance1_Script(script_s* s) {
    SCRIPT_BEGIN
    loadvar(VAR_CALLERID, PHONE_BIRDKEEPER_VANCE)
    endifjustbattled
    opentext
    checkflag(ENGINE_VANCE_READY_FOR_REMATCH)
    iftrue(WantsBattle)
    checkcellnum(PHONE_BIRDKEEPER_VANCE)
    iftrue_jump(Route44NumberAcceptedM)
    checkevent(EVENT_VANCE_ASKED_FOR_PHONE_NUMBER)
    iftrue(AskedAlready)
    writetext(BirdKeeperVanceLegendaryBirdsText)
    promptbutton
    setevent(EVENT_VANCE_ASKED_FOR_PHONE_NUMBER)
    scall(Route44AskNumber1M)
    goto AskForNumber;
AskedAlready:
    scall(Route44AskNumber2M)
AskForNumber:
    askforphonenumber(PHONE_BIRDKEEPER_VANCE)
    ifequal_jump(PHONE_CONTACTS_FULL, Route44PhoneFullM)
    ifequal_jump(PHONE_CONTACT_REFUSED, Route44NumberDeclinedM)
    gettrainername(STRING_BUFFER_3, BIRD_KEEPER, VANCE1)
    scall(Route44RegisteredNumberM)
    sjump(Route44NumberAcceptedM)
WantsBattle:
    scall(Route44RematchM)
    winlosstext(BirdKeeperVance1BeatenText, 0)
    readmem(wram_ptr(wVanceFightCount))
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
    loadtrainer(BIRD_KEEPER, VANCE1)
    startbattle
    reloadmapafterbattle
    loadmem(wram_ptr(wVanceFightCount), 1)
    clearflag(ENGINE_VANCE_READY_FOR_REMATCH)
    s_end
LoadFight1:
    loadtrainer(BIRD_KEEPER, VANCE2)
    startbattle
    reloadmapafterbattle
    loadmem(wram_ptr(wVanceFightCount), 2)
    clearflag(ENGINE_VANCE_READY_FOR_REMATCH)
    s_end
LoadFight2:
    loadtrainer(BIRD_KEEPER, VANCE3)
    startbattle
    reloadmapafterbattle
    clearflag(ENGINE_VANCE_READY_FOR_REMATCH)
    checkevent(EVENT_VANCE_CARBOS)
    iftrue(Carbos)
    checkevent(EVENT_GOT_CARBOS_FROM_VANCE)
    iftrue(ReceivedCarbosBefore)
    scall(Route44RematchGiftM)
    verbosegiveitem(CARBOS, 1)
    iffalse_jump(VancePackFull)
    setevent(EVENT_GOT_CARBOS_FROM_VANCE)
    sjump(Route44NumberAcceptedM)
ReceivedCarbosBefore:
    s_end
Carbos:
    opentext
    writetext(BirdKeeperVance2BeatenText)
    waitbutton
    verbosegiveitem(CARBOS, 1)
    iffalse_jump(VancePackFull)
    clearevent(EVENT_VANCE_CARBOS)
    setevent(EVENT_GOT_CARBOS_FROM_VANCE)
    sjump(Route44NumberAcceptedM)
    SCRIPT_END
}
bool Route44AskNumber1M(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(AskNumber1MScript)
    s_end
    SCRIPT_END
}
bool Route44AskNumber2M(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(AskNumber2MScript)
    s_end
    SCRIPT_END
}
bool Route44RegisteredNumberM(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(RegisteredNumberMScript)
    s_end
    SCRIPT_END
}
bool Route44NumberAcceptedM(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(NumberAcceptedMScript)
    s_end
    SCRIPT_END
}
bool Route44NumberDeclinedM(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(NumberDeclinedMScript)
    s_end
    SCRIPT_END
}
bool Route44PhoneFullM(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PhoneFullMScript)
    s_end
    SCRIPT_END
}
bool Route44RematchM(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(RematchMScript)
    s_end
    SCRIPT_END
}
bool Route44GiftM(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(GiftMScript)
    s_end
    SCRIPT_END
}
bool Route44PackFullM(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PackFullMScript)
    s_end
    SCRIPT_END
}
bool VancePackFull(script_s* s) {
    SCRIPT_BEGIN
    setevent(EVENT_VANCE_CARBOS)
    jumpstd(PackFullMScript)
    s_end
    SCRIPT_END
}
bool Route44RematchGiftM(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(RematchGiftMScript)
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerPsychicPhil = {PSYCHIC_T, PHIL, EVENT_BEAT_PSYCHIC_PHIL, PsychicPhilSeenText, PsychicPhilBeatenText, 0, TrainerPsychicPhil_Script};
bool TrainerPsychicPhil_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(PsychicPhilAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerFisherWilton1 = {FISHER, WILTON1, EVENT_BEAT_FISHER_WILTON, FisherWilton1SeenText, FisherWilton1BeatenText, 0, TrainerFisherWilton1_Script};
bool TrainerFisherWilton1_Script(script_s* s) {
    SCRIPT_BEGIN
    loadvar(VAR_CALLERID, PHONE_FISHER_WILTON)
    endifjustbattled
    opentext
    checkflag(ENGINE_WILTON_READY_FOR_REMATCH)
    iftrue(WantsBattle)
    checkflag(ENGINE_WILTON_HAS_ITEM)
    iftrue(HasItem)
    checkcellnum(PHONE_FISHER_WILTON)
    iftrue_jump(Route44NumberAcceptedM)
    checkevent(EVENT_WILTON_ASKED_FOR_PHONE_NUMBER)
    iftrue(AskedAlready)
    writetext(FisherWiltonHugePoliwagText)
    promptbutton
    setevent(EVENT_WILTON_ASKED_FOR_PHONE_NUMBER)
    scall(Route44AskNumber1M)
    goto AskForNumber;
AskedAlready:
    scall(Route44AskNumber2M)
AskForNumber:
    askforphonenumber(PHONE_FISHER_WILTON)
    ifequal_jump(PHONE_CONTACTS_FULL, Route44PhoneFullM)
    ifequal_jump(PHONE_CONTACT_REFUSED, Route44NumberDeclinedM)
    gettrainername(STRING_BUFFER_3, FISHER, WILTON1)
    scall(Route44RegisteredNumberM)
    sjump(Route44NumberAcceptedM)
WantsBattle:
    scall(Route44RematchM)
    winlosstext(FisherWilton1BeatenText, 0)
    readmem(wram_ptr(wWiltonFightCount))
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
    loadtrainer(FISHER, WILTON1)
    startbattle
    reloadmapafterbattle
    loadmem(wram_ptr(wWiltonFightCount), 1)
    clearflag(ENGINE_WILTON_READY_FOR_REMATCH)
    s_end
LoadFight1:
    loadtrainer(FISHER, WILTON2)
    startbattle
    reloadmapafterbattle
    loadmem(wram_ptr(wWiltonFightCount), 2)
    clearflag(ENGINE_WILTON_READY_FOR_REMATCH)
    s_end
LoadFight2:
    loadtrainer(FISHER, WILTON3)
    startbattle
    reloadmapafterbattle
    clearflag(ENGINE_WILTON_READY_FOR_REMATCH)
    s_end
HasItem:
    scall(Route44GiftM)
    checkevent(EVENT_WILTON_HAS_ULTRA_BALL)
    iftrue(UltraBall)
    checkevent(EVENT_WILTON_HAS_GREAT_BALL)
    iftrue(GreatBall)
    checkevent(EVENT_WILTON_HAS_POKE_BALL)
    iftrue(PokeBall)
UltraBall:
    verbosegiveitem(ULTRA_BALL, 1)
    iffalse(Route44PackFullM)
    goto ItemReceived;
GreatBall:
    verbosegiveitem(GREAT_BALL, 1)
    iffalse(Route44PackFullM)
    goto ItemReceived;
PokeBall:
    verbosegiveitem(POKE_BALL, 1)
    iffalse(Route44PackFullM)
ItemReceived:
    clearflag(ENGINE_WILTON_HAS_ITEM)
    sjump(Route44NumberAcceptedM)
Route44PackFullM:
    sjump(Route44PackFullM)
    SCRIPT_END
}
const struct TrainerObj TrainerFisherEdgar = {FISHER, EDGAR, EVENT_BEAT_FISHER_EDGAR, FisherEdgarSeenText, FisherEdgarBeatenText, 0, TrainerFisherEdgar_Script};
bool TrainerFisherEdgar_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(FisherEdgarAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerCooltrainerfCybil = {COOLTRAINERF, CYBIL, EVENT_BEAT_COOLTRAINERF_CYBIL, CooltrainerfCybilSeenText, CooltrainerfCybilBeatenText, 0, TrainerCooltrainerfCybil_Script};
bool TrainerCooltrainerfCybil_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(CooltrainerfCybilAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerPokemaniacZach = {POKEMANIAC, ZACH, EVENT_BEAT_POKEMANIAC_ZACH, PokemaniacZachSeenText, PokemaniacZachBeatenText, 0, TrainerPokemaniacZach_Script};
bool TrainerPokemaniacZach_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(PokemaniacZachAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerCooltrainermAllen = {COOLTRAINERM, ALLEN, EVENT_BEAT_COOLTRAINERM_ALLEN, CooltrainermAllenSeenText, CooltrainermAllenBeatenText, 0, TrainerCooltrainermAllen_Script};
bool TrainerCooltrainermAllen_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(CooltrainermAllenAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Route44Sign1(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route44Sign1Text)
    SCRIPT_END
}
bool Route44Sign2(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route44Sign2Text)
    SCRIPT_END
}
bool Route44FruitTree(script_s* s) {
    SCRIPT_BEGIN
    fruittree(FRUITTREE_ROUTE_44)
    SCRIPT_END
}
const struct ItemBall Route44MaxRevive = {MAX_REVIVE, 1};
const struct ItemBall Route44UltraBall = {ULTRA_BALL, 1};
const struct ItemBall Route44MaxRepel = {MAX_REPEL, 1};
const struct HiddenItem Route44HiddenElixer = {ELIXER, EVENT_ROUTE_44_HIDDEN_ELIXER};
const txt_cmd_s FisherWilton1SeenText[] = {
    text_start("Aack! You made me"
        t_line "lose a POLIWAG!"
        t_para "What are you going"
        t_line "to do about it?"
        t_done )
};
const txt_cmd_s FisherWilton1BeatenText[] = {
    text_start("Just forget about"
        t_line "it."
        t_done )
};
const txt_cmd_s FisherWiltonHugePoliwagText[] = {
    text_start("That POLIWAG that"
        t_line "got away…"
        t_cont "It was huge."
        t_para "I swear it must've"
        t_line "been 16 feet long!"
        t_done )
};
const txt_cmd_s FisherEdgarSeenText[] = {
    text_start("I fish until I"
        t_line "can't anymore."
        t_para "I also battle"
        t_line "until I drop."
        t_para "That's my"
        t_line "relationship"
        t_cont "with my #MON."
        t_done )
};
const txt_cmd_s FisherEdgarBeatenText[] = {
    text_start("Hmmmm… "
        t_line "This isn't right."
        t_done )
};
const txt_cmd_s FisherEdgarAfterBattleText[] = {
    text_start("That's 100 wins"
        t_line "to 101 losses."
        t_para "I won't battle"
        t_line "again for a while."
        t_done )
};
const txt_cmd_s BirdKeeperVance1SeenText[] = {
    text_start("Do you know about"
        t_line "the legendary bird"
        t_cont "#MON?"
        t_done )
};
const txt_cmd_s BirdKeeperVance1BeatenText[] = {
    text_start("Whew! You're hot"
        t_line "stuff."
        t_done )
};
const txt_cmd_s BirdKeeperVanceLegendaryBirdsText[] = {
    text_start("ARTICUNO, ZAPDOS"
        t_line "and MOLTRES are"
        t_para "the three legend-"
        t_line "ary bird #MON."
        t_para "I heard there are"
        t_line "other legendary"
        t_cont "birds, though."
        t_done )
};
const txt_cmd_s BirdKeeperVance2BeatenText[] = {
    text_start("Why can't I ever"
        t_line "beat you?"
        t_para "Oh yeah, here you"
        t_line "go. It's that gift"
        t_para "I couldn't give"
        t_line "you last time."
        t_done )
};
const txt_cmd_s PsychicPhilSeenText[] = {
    text_start("I'm gonna win,"
        t_line "for sure!"
        t_done )
};
const txt_cmd_s PsychicPhilBeatenText[] = {
    text_start("Arrgh… That's a"
        t_line "shocking loss…"
        t_done )
};
const txt_cmd_s PsychicPhilAfterBattleText[] = {
    text_start("It's important to"
        t_line "have conviction"
        t_cont "on your side."
        t_done )
};
const txt_cmd_s PokemaniacZachSeenText[] = {
    text_start("I'll do anything"
        t_line "to get my hands on"
        t_cont "rare #MON!"
        t_done )
};
const txt_cmd_s PokemaniacZachBeatenText[] = {
    text_start("Oooh, your #MON"
        t_line "are so appealing."
        t_done )
};
const txt_cmd_s PokemaniacZachAfterBattleText[] = {
    text_start("If a #MON has"
        t_line "different colors"
        t_para "from usual, it's"
        t_line "more valuable."
        t_para "What? You mean"
        t_line "that's not true?"
        t_done )
};
const txt_cmd_s CooltrainermAllenSeenText[] = {
    text_start("I can tell you're"
        t_line "a good trainer by"
        t_cont "looking at you."
        t_para "I'm good at #-"
        t_line "MON, and I can see"
        t_cont "that you are too."
        t_done )
};
const txt_cmd_s CooltrainermAllenBeatenText[] = {
    text_start("Tch! It's a total"
        t_line "loss on my part."
        t_done )
};
const txt_cmd_s CooltrainermAllenAfterBattleText[] = {
    text_start("Wow. You have a"
        t_line "lot of BADGES."
        t_para "No wonder you're"
        t_line "so tough."
        t_para "I wonder if"
        t_line "ECRUTEAK GYM's"
        t_para "MORTY is still in"
        t_line "training?"
        t_para "He really hammered"
        t_line "me."
        t_done )
};
const txt_cmd_s CooltrainerfCybilSeenText[] = {
    text_start("You look strong."
        t_para "Good trainers seek"
        t_line "tough opponents"
        t_cont "instinctively."
        t_done )
};
const txt_cmd_s CooltrainerfCybilBeatenText[] = {
    text_start("Nope! This won't"
        t_line "do at all."
        t_done )
};
const txt_cmd_s CooltrainerfCybilAfterBattleText[] = {
    text_start("We all get better"
        t_line "by experiencing"
        t_cont "many battles."
        t_para "I battled a lot to"
        t_line "become what I am"
        t_cont "today--an elite."
        t_done )
};
const txt_cmd_s Route44Sign1Text[] = {
    text_start("ROUTE 44"
        t_line "ICE PATH AHEAD"
        t_done )
};
const txt_cmd_s Route44Sign2Text[] = {
    text_start("ROUTE 44"
        t_para "MAHOGANY TOWN -"
        t_line "BLACKTHORN CITY"
        t_done )
    //db(0, 0) // filler
};
