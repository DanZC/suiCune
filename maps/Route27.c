#include "../constants.h"
#include "../util/scripting.h"
#include "Route27.h"
//// EVENTS
enum {
    ROUTE27_COOLTRAINER_M1 = 2,
    ROUTE27_COOLTRAINER_M2,
    ROUTE27_COOLTRAINER_F1,
    ROUTE27_COOLTRAINER_F2,
    ROUTE27_YOUNGSTER1,
    ROUTE27_YOUNGSTER2,
    ROUTE27_POKE_BALL1,
    ROUTE27_POKE_BALL2,
    ROUTE27_FISHER,
};

const Script_fn_t Route27_SceneScripts[] = {
    Route27_MapScripts_DummyScene0 , //  SCENE_DEFAULT,
    Route27_MapScripts_DummyScene1 , //  SCENE_FINISHED,
};

const struct MapCallback Route27_MapCallbacks[] = {
};

const struct MapScripts Route27_MapScripts = {
    .scene_script_count = lengthof(Route27_SceneScripts),
    .scene_scripts = Route27_SceneScripts,

    .callback_count = lengthof(Route27_MapCallbacks),
    .callbacks = Route27_MapCallbacks,
};

static const struct CoordEvent Route27_CoordEvents[] = {
    coord_event(18, 10, SCENE_DEFAULT, &FirstStepIntoKantoLeftScene),
    coord_event(19, 10, SCENE_DEFAULT, &FirstStepIntoKantoRightScene),
};

static const struct BGEvent Route27_BGEvents[] = {
    bg_event(25, 7, BGEVENT_READ, &TohjoFallsSign),
};

static const struct WarpEventData Route27_WarpEvents[] = {
    warp_event(33, 7, ROUTE_27_SANDSTORM_HOUSE, 1),
    warp_event(26, 5, TOHJO_FALLS, 1),
    warp_event(36, 5, TOHJO_FALLS, 2),
};

static const struct ObjEvent Route27_ObjectEvents[] = {
    object_event(48, 7, SPRITE_COOLTRAINER_M, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 3, &TrainerCooltrainermBlake, -1),
    object_event(58, 6, SPRITE_COOLTRAINER_M, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 4, &TrainerCooltrainermBrian, -1),
    object_event(72, 10, SPRITE_COOLTRAINER_F, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 4, &TrainerCooltrainerfReena, -1),
    object_event(37, 6, SPRITE_COOLTRAINER_F, SPRITEMOVEDATA_SPINCLOCKWISE, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 2, &TrainerCooltrainerfMegan, -1),
    object_event(65, 7, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerPsychicGilbert, -1),
    object_event(58, 13, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerBirdKeeperJose2, -1),
    object_event(60, 12, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &Route27TMSolarbeam, EVENT_ROUTE_27_TM_SOLARBEAM),
    object_event(53, 12, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &Route27RareCandy, EVENT_ROUTE_27_RARE_CANDY),
    object_event(21, 10, SPRITE_FISHER, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 3, &Route27FisherScript, -1),
};

const struct MapEvents Route27_MapEvents = {
    .warp_event_count = lengthof(Route27_WarpEvents),
    .warp_events = Route27_WarpEvents,

    .coord_event_count = lengthof(Route27_CoordEvents),
    .coord_events = Route27_CoordEvents,

    .bg_event_count = lengthof(Route27_BGEvents),
    .bg_events = Route27_BGEvents,

    .obj_event_count = lengthof(Route27_ObjectEvents),
    .obj_events = Route27_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "Route27.h"

bool Route27_MapScripts_DummyScene0(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool Route27_MapScripts_DummyScene1(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool FirstStepIntoKantoLeftScene(script_s* s) {
    SCRIPT_BEGIN
    turnobject(ROUTE27_FISHER, LEFT)
    showemote(EMOTE_SHOCK, ROUTE27_FISHER, 15)
    applymovement(ROUTE27_FISHER, Route27FisherStepLeftTwiceMovement)
    sjump(FirstStepIntoKantoScene_Continue)
    SCRIPT_END
}
bool FirstStepIntoKantoRightScene(script_s* s) {
    SCRIPT_BEGIN
    turnobject(ROUTE27_FISHER, LEFT)
    showemote(EMOTE_SHOCK, ROUTE27_FISHER, 15)
    applymovement(ROUTE27_FISHER, Route27FisherStepLeftOnceMovement)
    SCRIPT_FALLTHROUGH(FirstStepIntoKantoScene_Continue)
}
bool FirstStepIntoKantoScene_Continue(script_s* s) {
    SCRIPT_BEGIN
    turnobject(PLAYER, RIGHT)
    opentext
    writetext(Route27FisherHeyText)
    promptbutton
    writetext(Route27FisherText)
    waitbutton
    closetext
    setscene(SCENE_FINISHED)
    s_end
    SCRIPT_END
}
bool Route27FisherScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(Route27FisherText)
    SCRIPT_END
}
const struct TrainerObj TrainerPsychicGilbert = {PSYCHIC_T, GILBERT, EVENT_BEAT_PSYCHIC_GILBERT, PsychicGilbertSeenText, PsychicGilbertBeatenText, 0, TrainerPsychicGilbert_Script};
bool TrainerPsychicGilbert_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(PsychicGilbertAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerBirdKeeperJose2 = {BIRD_KEEPER, JOSE2, EVENT_BEAT_BIRD_KEEPER_JOSE2, BirdKeeperJose2SeenText, BirdKeeperJose2BeatenText, 0, TrainerBirdKeeperJose2_Script};
bool TrainerBirdKeeperJose2_Script(script_s* s) {
    SCRIPT_BEGIN
    loadvar(VAR_CALLERID, PHONE_BIRDKEEPER_JOSE)
    endifjustbattled
    opentext
    checkflag(ENGINE_JOSE_READY_FOR_REMATCH)
    iftrue(WantsBattle)
    checkflag(ENGINE_JOSE_HAS_STAR_PIECE)
    iftrue(HasStarPiece)
    checkcellnum(PHONE_BIRDKEEPER_JOSE)
    iftrue(NumberAccepted)
    checkflag(EVENT_JOSE_ASKED_FOR_PHONE_NUMBER)
    iftrue(AskedAlready)
    writetext(BirdKeeperJose2AfterBattleText)
    promptbutton
    setflag(EVENT_JOSE_ASKED_FOR_PHONE_NUMBER)
    scall_local(AskNumber1);
    goto AskForNumber;
AskedAlready:
    scall_local(AskNumber2);
AskForNumber:
    askforphonenumber(PHONE_BIRDKEEPER_JOSE)
    ifequal(PHONE_CONTACTS_FULL, PhoneFull)
    ifequal(PHONE_CONTACT_REFUSED, NumberDeclined)
    gettrainername(STRING_BUFFER_3, BIRD_KEEPER, JOSE2)
    scall_local(RegisteredNumber);
    goto NumberAccepted;
WantsBattle:
    scall_local(Rematch);
    winlosstext(BirdKeeperJose2BeatenText, 0)
    readmem(wram_ptr(wJoseFightCount))
    ifequal(2, Fight2)
    ifequal(1, Fight1)
    ifequal(0, LoadFight0)
Fight2:
    checkflag(EVENT_RESTORED_POWER_TO_KANTO)
    iftrue(LoadFight2)
Fight1:
    checkflag(EVENT_BEAT_ELITE_FOUR)
    iftrue(LoadFight1)
LoadFight0:
    loadtrainer(BIRD_KEEPER, JOSE2)
    startbattle
    reloadmapafterbattle
    loadmem(wram_ptr(wJoseFightCount), 1)
    clearflag(ENGINE_JOSE_READY_FOR_REMATCH)
    s_end
LoadFight1:
    loadtrainer(BIRD_KEEPER, JOSE1)
    startbattle
    reloadmapafterbattle
    loadmem(wram_ptr(wJoseFightCount), 2)
    clearflag(ENGINE_JOSE_READY_FOR_REMATCH)
    s_end
LoadFight2:
    loadtrainer(BIRD_KEEPER, JOSE3)
    startbattle
    reloadmapafterbattle
    clearflag(ENGINE_JOSE_READY_FOR_REMATCH)
    s_end
HasStarPiece:
    scall_local(Gift);
    verbosegiveitem(STAR_PIECE, 1)
    iffalse(NoRoom)
    clearflag(ENGINE_JOSE_HAS_STAR_PIECE)
    goto NumberAccepted;
NoRoom:
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
const struct TrainerObj TrainerCooltrainermBlake = {COOLTRAINERM, BLAKE, EVENT_BEAT_COOLTRAINERM_BLAKE, CooltrainermBlakeSeenText, CooltrainermBlakeBeatenText, 0, TrainerCooltrainermBlake_Script};
bool TrainerCooltrainermBlake_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(CooltrainermBlakeAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerCooltrainermBrian = {COOLTRAINERM, BRIAN, EVENT_BEAT_COOLTRAINERM_BRIAN, CooltrainermBrianSeenText, CooltrainermBrianBeatenText, 0, TrainerCooltrainermBrian_Script};
bool TrainerCooltrainermBrian_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(CooltrainermBrianAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerCooltrainerfReena = {COOLTRAINERF, REENA1, EVENT_BEAT_COOLTRAINERF_REENA, CooltrainerfReenaSeenText, CooltrainerfReenaBeatenText, 0, TrainerCooltrainerfReena_Script};
bool TrainerCooltrainerfReena_Script(script_s* s) {
    SCRIPT_BEGIN
    loadvar(VAR_CALLERID, PHONE_COOLTRAINERF_REENA)
    endifjustbattled
    opentext
    checkflag(ENGINE_REENA_READY_FOR_REMATCH)
    iftrue(WantsBattle)
    checkcellnum(PHONE_COOLTRAINERF_REENA)
    iftrue(NumberAccepted)
    checkflag(EVENT_REENA_ASKED_FOR_PHONE_NUMBER)
    iftrue(AskedAlready)
    writetext(CooltrainerfReenaAfterBattleText)
    promptbutton
    setflag(EVENT_REENA_ASKED_FOR_PHONE_NUMBER)
    scall_local(AskNumber1);
    goto AskForNumber;
AskedAlready:
    scall_local(AskNumber2);
AskForNumber:
    askforphonenumber(PHONE_COOLTRAINERF_REENA)
    ifequal(PHONE_CONTACTS_FULL, PhoneFull)
    ifequal(PHONE_CONTACT_REFUSED, NumberDeclined)
    gettrainername(STRING_BUFFER_3, COOLTRAINERF, REENA1)
    scall_local(RegisteredNumber);
    goto NumberAccepted;
WantsBattle:
    scall_local(Rematch);
    winlosstext(CooltrainerfReenaBeatenText, 0)
    readmem(wram_ptr(wReenaFightCount))
    ifequal(2, Fight2)
    ifequal(1, Fight1)
    ifequal(0, LoadFight0)
Fight2:
    checkflag(EVENT_RESTORED_POWER_TO_KANTO)
    iftrue(LoadFight2)
Fight1:
    checkflag(EVENT_BEAT_ELITE_FOUR)
    iftrue(LoadFight1)
LoadFight0:
    loadtrainer(COOLTRAINERF, REENA1)
    startbattle
    reloadmapafterbattle
    loadmem(wram_ptr(wReenaFightCount), 1)
    clearflag(ENGINE_REENA_READY_FOR_REMATCH)
    s_end
LoadFight1:
    loadtrainer(COOLTRAINERF, REENA2)
    startbattle
    reloadmapafterbattle
    loadmem(wram_ptr(wReenaFightCount), 2)
    clearflag(ENGINE_REENA_READY_FOR_REMATCH)
    s_end
LoadFight2:
    loadtrainer(COOLTRAINERF, REENA3)
    startbattle
    reloadmapafterbattle
    clearflag(ENGINE_REENA_READY_FOR_REMATCH)
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
const struct TrainerObj TrainerCooltrainerfMegan = {COOLTRAINERF, MEGAN, EVENT_BEAT_COOLTRAINERF_MEGAN, CooltrainerfMeganSeenText, CooltrainerfMeganBeatenText, 0, TrainerCooltrainerfMegan_Script};
bool TrainerCooltrainerfMegan_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(CooltrainerfMeganAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool TohjoFallsSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(TohjoFallsSignText)
    SCRIPT_END
}
const struct ItemBall Route27TMSolarbeam = {TM_SOLARBEAM, 1};
const struct ItemBall Route27RareCandy = {RARE_CANDY, 1};
const uint8_t Route27FisherStepLeftTwiceMovement[] = {
    step(LEFT),
    step(LEFT),
    movement_step_end,
};
const uint8_t Route27FisherStepLeftOnceMovement[] = {
    step(LEFT),
    movement_step_end,
};
const txt_cmd_s Route27FisherHeyText[] = {
    text_start("Hey!"
        t_done )
};
const txt_cmd_s Route27FisherText[] = {
    text_start("Do you know what"
        t_line "you just did?"
        t_para "You've taken your"
        t_line "first step into"
        t_cont "KANTO."
        t_para "Check your #-"
        t_line "GEAR MAP and see."
        t_done )
};
const txt_cmd_s CooltrainermBlakeSeenText[] = {
    text_start("You look pretty"
        t_line "strong."
        t_cont "Let me battle you!"
        t_done )
};
const txt_cmd_s CooltrainermBlakeBeatenText[] = {
    text_start("Yow!"
        t_done )
};
const txt_cmd_s CooltrainermBlakeAfterBattleText[] = {
    text_start("If you prevail on"
        t_line "this harsh trek,"
        t_para "the truth will be"
        t_line "revealed!"
        t_para "Heh, sorry, I just"
        t_line "wanted to say"
        t_cont "something cool."
        t_done )
};
const txt_cmd_s CooltrainermBrianSeenText[] = {
    text_start("Hm? You're good,"
        t_line "aren't you?"
        t_done )
};
const txt_cmd_s CooltrainermBrianBeatenText[] = {
    text_start("Just as I thought!"
        t_done )
};
const txt_cmd_s CooltrainermBrianAfterBattleText[] = {
    text_start("A good trainer can"
        t_line "recognize other"
        t_cont "good trainers."
        t_done )
};
const txt_cmd_s CooltrainerfReenaSeenText[] = {
    text_start("You shouldn't"
        t_line "underestimate the"
        t_para "wild #MON in"
        t_line "these parts."
        t_done )
};
const txt_cmd_s CooltrainerfReenaBeatenText[] = {
    text_start("Oh! You're much"
        t_line "too strong!"
        t_done )
};
const txt_cmd_s CooltrainerfReenaAfterBattleText[] = {
    text_start("You're just a kid,"
        t_line "but you're not to"
        t_para "be underestimated"
        t_line "either."
        t_done )
};
const txt_cmd_s CooltrainerfMeganSeenText[] = {
    text_start("It's rare to see"
        t_line "anyone come here."
        t_para "Are you training"
        t_line "on your own?"
        t_done )
};
const txt_cmd_s CooltrainerfMeganBeatenText[] = {
    text_start("Oh! You're really"
        t_line "strong!"
        t_done )
};
const txt_cmd_s CooltrainerfMeganAfterBattleText[] = {
    text_start("I'm checking out"
        t_line "pre- and post-"
        t_cont "evolution #MON."
        t_para "Evolution really"
        t_line "does make #MON"
        t_cont "stronger."
        t_para "But evolved forms"
        t_line "also learn moves"
        t_cont "later on."
        t_done )
};
const txt_cmd_s PsychicGilbertSeenText[] = {
    text_start("Don't say a thing!"
        t_para "Let me guess what"
        t_line "you're thinking."
        t_para "Mmmmmmm…"
        t_para "I got it! You're"
        t_line "on the #MON"
        t_cont "LEAGUE challenge!"
        t_done )
};
const txt_cmd_s PsychicGilbertBeatenText[] = {
    text_start("You're too much!"
        t_done )
};
const txt_cmd_s PsychicGilbertAfterBattleText[] = {
    text_start("With your skills,"
        t_line "you'll do well at"
        t_cont "the LEAGUE."
        t_para "That's what my"
        t_line "premonition says."
        t_done )
};
const txt_cmd_s BirdKeeperJose2SeenText[] = {
    text_start("Tweet! Tweet!"
        t_line "Tetweet!"
        t_done )
};
const txt_cmd_s BirdKeeperJose2BeatenText[] = {
    text_start("Tweet!"
        t_done )
};
const txt_cmd_s BirdKeeperJose2AfterBattleText[] = {
    text_start("BIRD KEEPERS like"
        t_line "me mimic bird"
        t_para "whistles to com-"
        t_line "mand #MON."
        t_done )
};
const txt_cmd_s TohjoFallsSignText[] = {
    text_start("TOHJO FALLS"
        t_para "THE LINK BETWEEN"
        t_line "KANTO AND JOHTO"
        t_done )
    //db(0, 0) // filler
};
