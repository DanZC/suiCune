#include "../constants.h"
#include "../util/scripting.h"
#include "RadioTower2F.h"
//// EVENTS
enum {
    RADIOTOWER2F_SUPER_NERD = 2,
    RADIOTOWER2F_TEACHER,
    RADIOTOWER2F_ROCKET1,
    RADIOTOWER2F_ROCKET2,
    RADIOTOWER2F_ROCKET3,
    RADIOTOWER2F_ROCKET_GIRL,
    RADIOTOWER2F_BLACK_BELT1,
    RADIOTOWER2F_BLACK_BELT2,
    RADIOTOWER2F_JIGGLYPUFF,
    RADIOTOWER2F_BUENA,
    RADIOTOWER2F_RECEPTIONIST,
};

const Script_fn_t RadioTower2F_SceneScripts[] = {
    0,
};

const struct MapCallback RadioTower2F_MapCallbacks[] = {
    0,
};

const struct MapScripts RadioTower2F_MapScripts = {
    .scene_script_count = 0, // lengthof(RadioTower2F_SceneScripts),
    .scene_scripts = RadioTower2F_SceneScripts,

    .callback_count = 0, // lengthof(RadioTower2F_MapCallbacks),
    .callbacks = RadioTower2F_MapCallbacks,
};

static const struct CoordEvent RadioTower2F_CoordEvents[] = {
    0,
};

static const struct BGEvent RadioTower2F_BGEvents[] = {
    bg_event(3, 0, BGEVENT_READ, &RadioTower2FSalesSign),
    bg_event(5, 0, BGEVENT_READ, &RadioTower2FOaksPKMNTalkSign),
    bg_event(9, 1, BGEVENT_READ, &RadioTower2FBookshelf),
    bg_event(10, 1, BGEVENT_READ, &RadioTower2FBookshelf),
    bg_event(11, 1, BGEVENT_READ, &RadioTower2FBookshelf),
    bg_event(13, 0, BGEVENT_READ, &RadioTower2FPokemonRadioSign),
};

static const struct WarpEventData RadioTower2F_WarpEvents[] = {
    warp_event(0, 0, RADIO_TOWER_3F, 1),
    warp_event(15, 0, RADIO_TOWER_1F, 3),
};

static const struct ObjEvent RadioTower2F_ObjectEvents[] = {
    object_event(6, 6, SPRITE_SUPER_NERD, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &RadioTower2FSuperNerdScript, EVENT_GOLDENROD_CITY_CIVILIANS),
    object_event(17, 2, SPRITE_TEACHER, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &RadioTower2FTeacherScript, -1),
    object_event(1, 4, SPRITE_ROCKET, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, 0, OBJECTTYPE_TRAINER, 3, &TrainerGruntM4, EVENT_RADIO_TOWER_ROCKET_TAKEOVER),
    object_event(8, 4, SPRITE_ROCKET, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_TRAINER, 3, &TrainerGruntM5, EVENT_RADIO_TOWER_ROCKET_TAKEOVER),
    object_event(4, 1, SPRITE_ROCKET, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_TRAINER, 2, &TrainerGruntM6, EVENT_RADIO_TOWER_ROCKET_TAKEOVER),
    object_event(10, 5, SPRITE_ROCKET_GIRL, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 3, &TrainerGruntF2, EVENT_RADIO_TOWER_ROCKET_TAKEOVER),
    object_event(0, 1, SPRITE_BLACK_BELT, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &RadioTower2FBlackBelt1Script, EVENT_RADIO_TOWER_BLACKBELT_BLOCKS_STAIRS),
    object_event(1, 1, SPRITE_BLACK_BELT, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &RadioTower2FBlackBelt2Script, EVENT_RADIO_TOWER_CIVILIANS_AFTER),
    object_event(12, 1, SPRITE_JIGGLYPUFF, SPRITEMOVEDATA_POKEMON, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &RadioTowerJigglypuff, -1),
    object_event(14, 5, SPRITE_BEAUTY, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &Buena, -1),
    object_event(12, 7, SPRITE_RECEPTIONIST, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &RadioTowerBuenaPrizeReceptionist, EVENT_GOLDENROD_CITY_CIVILIANS),
};

const struct MapEvents RadioTower2F_MapEvents = {
    .warp_event_count = lengthof(RadioTower2F_WarpEvents),
    .warp_events = RadioTower2F_WarpEvents,

    .coord_event_count = 0, // lengthof(RadioTower2F_CoordEvents),
    .coord_events = RadioTower2F_CoordEvents,

    .bg_event_count = lengthof(RadioTower2F_BGEvents),
    .bg_events = RadioTower2F_BGEvents,

    .obj_event_count = lengthof(RadioTower2F_ObjectEvents),
    .obj_events = RadioTower2F_ObjectEvents,
};

//// CODE

#define BLUE_CARD_POINT_CAP 30
bool RadioTower2FUnusedDummyScene(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool RadioTower2FSuperNerdScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(RadioTower2FSuperNerdText)
    SCRIPT_END
}
bool RadioTower2FTeacherScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkflag(ENGINE_ROCKETS_IN_RADIO_TOWER)
    iftrue(Rockets)
    writetext(RadioTower2FTeacherText)
    waitbutton
    closetext
    s_end
Rockets:
    writetext(RadioTower2FTeacherText_Rockets)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool RadioTowerJigglypuff(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(RadioTowerJigglypuffText)
    playcry(JIGGLYPUFF)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool RadioTower2FBlackBelt1Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(RadioTower2FBlackBelt1Text)
    SCRIPT_END
}
bool RadioTower2FBlackBelt2Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(RadioTower2FBlackBelt2Text)
    SCRIPT_END
}
const struct TrainerObj TrainerGruntM4 = {GRUNTM, GRUNTM_4, EVENT_BEAT_ROCKET_GRUNTM_4, GruntM4SeenText, GruntM4BeatenText, 0, TrainerGruntM4_Script};
bool TrainerGruntM4_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(GruntM4AfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerGruntM5 = {GRUNTM, GRUNTM_5, EVENT_BEAT_ROCKET_GRUNTM_5, GruntM5SeenText, GruntM5BeatenText, 0, TrainerGruntM5_Script};
bool TrainerGruntM5_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(GruntM5AfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerGruntM6 = {GRUNTM, GRUNTM_6, EVENT_BEAT_ROCKET_GRUNTM_6, GruntM6SeenText, GruntM6BeatenText, 0, TrainerGruntM6_Script};
bool TrainerGruntM6_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(GruntM6AfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerGruntF2 = {GRUNTF, GRUNTF_2, EVENT_BEAT_ROCKET_GRUNTF_2, GruntF2SeenText, GruntF2BeatenText, 0, TrainerGruntF2_Script};
bool TrainerGruntF2_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(GruntF2AfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Buena(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkflag(ENGINE_ROCKETS_IN_RADIO_TOWER)
    iftrue(MidRocketTakeover)
    checkevent(EVENT_MET_BUENA)
    iffalse(Introduction)
    checkflag(ENGINE_BUENAS_PASSWORD_2)
    iftrue(PlayedAlready)
    readvar(VAR_HOUR)
    ifless(NITE_HOUR, TooEarly)
    checkflag(ENGINE_BUENAS_PASSWORD)
    iffalse(TuneIn)
    checkitem(BLUE_CARD)
    iffalse(NoBlueCard)
    readvar(VAR_BLUECARDBALANCE)
    ifequal(BLUE_CARD_POINT_CAP, BlueCardCapped0)
    playmusic(MUSIC_BUENAS_PASSWORD)
    writetext(RadioTower2FBuenaDoYouKnowPasswordText)
    special(AskRememberPassword)
    iffalse(ForgotPassword)
    writetext(RadioTower2FBuenaJoinTheShowText)
    waitbutton
    closetext
    turnobject(RADIOTOWER2F_BUENA, RIGHT)
    readvar(VAR_FACING)
    ifnotequal(RIGHT, DontNeedToMove)
    applymovement(PLAYER, RadioTower2FPlayerWalksToMicrophoneMovement)
DontNeedToMove:
    turnobject(PLAYER, RIGHT)
    opentext
    writetext(RadioTower2FBuenaEveryoneSayPasswordText)
    waitbutton
    closetext
    turnobject(RADIOTOWER2F_BUENA, DOWN)
    refreshscreen
    special(BuenasPassword)
    closetext
    iffalse(WrongAnswer)
    opentext
    writetext(RadioTower2FBuenaCorrectAnswerText)
    waitbutton
    closetext
    readvar(VAR_BLUECARDBALANCE)
    addval(1)
    writevar(VAR_BLUECARDBALANCE)
    waitsfx
    playsound(SFX_TRANSACTION)
    setflag(ENGINE_BUENAS_PASSWORD_2)
    pause(20)
    turnobject(RADIOTOWER2F_BUENA, RIGHT)
    opentext
    writetext(RadioTower2FBuenaThanksForComingText)
    waitbutton
    closetext
    special(FadeOutMusic)
    pause(20)
    special(RestartMapMusic)
    readvar(VAR_BLUECARDBALANCE)
    ifequal(BLUE_CARD_POINT_CAP, BlueCardCapped1)
    s_end
Introduction:
    writetext(RadioTower2FBuenaShowIntroductionText)
    promptbutton
    setevent(EVENT_MET_BUENA)
    verbosegiveitem(BLUE_CARD, 1)
TuneIn:
    writetext(RadioTower2FBuenaTuneInToMyShowText)
    waitbutton
    closetext
    checkcellnum(PHONE_BUENA)
    iftrue(Registered0)
    checkevent(EVENT_BUENA_OFFERED_HER_PHONE_NUMBER)
    iftrue(OfferedNumberBefore)
Registered0:
    turnobject(RADIOTOWER2F_BUENA, RIGHT)
    s_end
ForgotPassword:
    writetext(RadioTower2FBuenaComeBackAfterListeningText)
    waitbutton
    closetext
    turnobject(RADIOTOWER2F_BUENA, RIGHT)
    special(FadeOutMusic)
    pause(20)
    special(RestartMapMusic)
    s_end
PlayedAlready:
    writetext(RadioTower2FBuenaAlreadyPlayedText)
    waitbutton
    closetext
    checkcellnum(PHONE_BUENA)
    iftrue(Registered1)
    checkevent(EVENT_BUENA_OFFERED_HER_PHONE_NUMBER)
    iftrue(OfferedNumberBefore)
Registered1:
    turnobject(RADIOTOWER2F_BUENA, RIGHT)
    pause(10)
    s_end
WrongAnswer:
    setflag(ENGINE_BUENAS_PASSWORD_2)
    opentext
    writetext(RadioTower2FBuenaDidYouForgetText)
    waitbutton
    closetext
    turnobject(RADIOTOWER2F_BUENA, RIGHT)
    pause(20)
    opentext
    writetext(RadioTower2FBuenaThanksForComingText)
    waitbutton
    closetext
    turnobject(RADIOTOWER2F_BUENA, RIGHT)
    special(FadeOutMusic)
    pause(20)
    special(RestartMapMusic)
    s_end
MidRocketTakeover:
    writetext(RadioTower2FBuenaPasswordIsHelpText)
    waitbutton
    closetext
    s_end
NoBlueCard:
    writetext(RadioTower2FBuenaNoBlueCardText)
    waitbutton
    closetext
    checkcellnum(PHONE_BUENA)
    iftrue(Registered2)
    checkevent(EVENT_BUENA_OFFERED_HER_PHONE_NUMBER_NO_BLUE_CARD)
    iftrue(OfferedNumberBefore)
Registered2:
    turnobject(RADIOTOWER2F_BUENA, RIGHT)
    s_end
BlueCardCapped0:
    writetext(RadioTower2FBuenaCardIsFullText)
    waitbutton
    closetext
    checkcellnum(PHONE_BUENA)
    iftrue(Registered3)
    checkevent(EVENT_BUENA_OFFERED_HER_PHONE_NUMBER_NO_BLUE_CARD)
    iftrue(OfferedNumberBefore)
Registered3:
    turnobject(RADIOTOWER2F_BUENA, RIGHT)
    s_end
TooEarly:
    writetext(RadioTower2FBuenaTuneInAfterSixText)
    waitbutton
    closetext
    checkcellnum(PHONE_BUENA)
    iftrue(Registered4)
    checkevent(EVENT_BUENA_OFFERED_HER_PHONE_NUMBER)
    iftrue(OfferedNumberBefore)
Registered4:
    s_end
BlueCardCapped1:
    checkcellnum(PHONE_BUENA)
    iftrue(HasNumber)
    pause(20)
    turnobject(RADIOTOWER2F_BUENA, DOWN)
    pause(15)
    turnobject(PLAYER, UP)
    pause(15)
    checkevent(EVENT_BUENA_OFFERED_HER_PHONE_NUMBER_NO_BLUE_CARD)
    iftrue(OfferedNumberBefore)
    showemote(EMOTE_SHOCK, RADIOTOWER2F_BUENA, 15)
    setevent(EVENT_BUENA_OFFERED_HER_PHONE_NUMBER_NO_BLUE_CARD)
    setevent(EVENT_BUENA_OFFERED_HER_PHONE_NUMBER)
    opentext
    writetext(RadioTower2FBuenaOfferPhoneNumberText)
    goto AskForNumber;
OfferedNumberBefore:
    opentext
    writetext(RadioTower2FBuenaOfferNumberAgainText)
AskForNumber:
    askforphonenumber(PHONE_BUENA)
    ifequal(PHONE_CONTACTS_FULL, PhoneFull)
    ifequal(PHONE_CONTACT_REFUSED, NumberDeclined)
    writetext(RadioTower2FRegisteredBuenasNumberText)
    playsound(SFX_REGISTER_PHONE_NUMBER)
    waitsfx
    promptbutton
    writetext(RadioTower2FBuenaCallMeText)
    waitbutton
    closetext
    turnobject(RADIOTOWER2F_BUENA, RIGHT)
    addcellnum(PHONE_BUENA)
    s_end
NumberDeclined:
    writetext(RadioTower2FBuenaSadRejectedText)
    waitbutton
    closetext
    turnobject(RADIOTOWER2F_BUENA, RIGHT)
    s_end
PhoneFull:
    writetext(RadioTower2FBuenaYourPhoneIsFullText)
    waitbutton
    closetext
    turnobject(RADIOTOWER2F_BUENA, RIGHT)
HasNumber:
    s_end
    SCRIPT_END
}
bool RadioTowerBuenaPrizeReceptionist(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkitem(BLUE_CARD)
    iffalse(NoCard)
    writetext(RadioTower2FBuenaReceptionistPointsForPrizesText)
    promptbutton
    special(BuenaPrize)
    closetext
    s_end
NoCard:
    writetext(RadioTower2FBuenaReceptionistNoCardText)
    promptbutton
    closetext
    s_end
    SCRIPT_END
}
bool RadioTower2FSalesSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(RadioTower2FSalesSignText)
    SCRIPT_END
}
bool RadioTower2FOaksPKMNTalkSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(RadioTower2FOaksPKMNTalkSignText)
    SCRIPT_END
}
bool RadioTower2FPokemonRadioSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(RadioTower2FPokemonRadioSignText)
    SCRIPT_END
}
bool RadioTower2FBookshelf(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(MagazineBookshelfScript)
    SCRIPT_END
}
const uint8_t RadioTower2FPlayerWalksToMicrophoneMovement[] = {
    slow_step(DOWN),
    slow_step(RIGHT),
    movement_step_end,
};
const txt_cmd_s RadioTower2FSuperNerdText[] = {
    text_start("You can listen to"
        t_line "the radio any-"
        t_cont "where. Tune in!"
        t_done )
};
const txt_cmd_s RadioTower2FTeacherText[] = {
    text_start("Lullabies on the"
        t_line "radio may make"
        t_cont "#MON sleep."
        t_done )
};
const txt_cmd_s RadioTower2FTeacherText_Rockets[] = {
    text_start("Why would they"
        t_line "want to take over"
        t_cont "the RADIO TOWER?"
        t_done )
};
const txt_cmd_s RadioTowerJigglypuffText[] = {
    text_start("JIGGLYPUFF:"
        t_line "Jiggly…"
        t_done )
};
const txt_cmd_s RadioTower2FBlackBelt1Text[] = {
    text_start("Sorry. Authorized"
        t_line "personnel only"
        t_cont "beyond this point."
        t_para "It wasn't that way"
        t_line "before."
        t_para "There's something"
        t_line "wrong with the"
        t_cont "DIRECTOR…"
        t_done )
};
const txt_cmd_s RadioTower2FBlackBelt2Text[] = {
    text_start("Feel free to look"
        t_line "around anywhere."
        t_para "The DIRECTOR is"
        t_line "nice again, just"
        t_cont "as he was before."
        t_done )
};
const txt_cmd_s GruntM4SeenText[] = {
    text_start("Three years ago,"
        t_line "TEAM ROCKET was"
        t_cont "forced to disband."
        t_para "But we're making a"
        t_line "comeback here!"
        t_done )
};
const txt_cmd_s GruntM4BeatenText[] = {
    text_start("Gwah! Don't get"
        t_line "cute!"
        t_done )
};
const txt_cmd_s GruntM4AfterBattleText[] = {
    text_start("We won't let you"
        t_line "ruin our plans"
        t_cont "for our comeback!"
        t_done )
};
const txt_cmd_s GruntM5SeenText[] = {
    text_start("We're TEAM ROCKET,"
        t_line "the exploiters of"
        t_cont "#MON!"
        t_para "We love being"
        t_line "evil! Scared?"
        t_done )
};
const txt_cmd_s GruntM5BeatenText[] = {
    text_start("You think you're a"
        t_line "hero?"
        t_done )
};
const txt_cmd_s GruntM5AfterBattleText[] = {
    text_start("We're not always"
        t_line "evil. We just do"
        t_cont "whatever we like."
        t_done )
};
const txt_cmd_s GruntM6SeenText[] = {
    text_start("Hey, hey! Keep out"
        t_line "of our way!"
        t_done )
};
const txt_cmd_s GruntM6BeatenText[] = {
    text_start("Arggh. I give up."
        t_done )
};
const txt_cmd_s GruntM6AfterBattleText[] = {
    text_start("Our EXECUTIVES are"
        t_line "trying to take"
        t_cont "this place over."
        t_para "They have some big"
        t_line "plan. I wonder"
        t_cont "what that is?"
        t_done )
};
const txt_cmd_s GruntF2SeenText[] = {
    text_start("Hahaha!"
        t_para "How boring."
        t_line "It was far too"
        t_para "easy to take over"
        t_line "this place!"
        t_para "Come on, keep me"
        t_line "amused!"
        t_done )
};
const txt_cmd_s GruntF2BeatenText[] = {
    text_start("Wh-who are you?"
        t_done )
};
const txt_cmd_s GruntF2AfterBattleText[] = {
    text_start("You beat me, and"
        t_line "I won't forget it!"
        t_done )
};
const txt_cmd_s RadioTower2FBuenaShowIntroductionText[] = {
    text_start("BUENA: Hi! I'm"
        t_line "BUENA!"
        t_para "Do you know about"
        t_line "a radio program"
        t_cont "called PASSWORD?"
        t_para "If you can tell me"
        t_line "the password from"
        t_para "the program, you"
        t_line "will earn points."
        t_para "Save up those"
        t_line "points and trade"
        t_para "them to that sweet"
        t_line "young lady over"
        t_para "there for some"
        t_line "choice prizes!"
        t_para "Here you go!"
        t_para "It's your very own"
        t_line "point card!"
        t_done )
};
const txt_cmd_s RadioTower2FBuenaTuneInToMyShowText[] = {
    text_start("BUENA: Tune in to"
        t_line "my PASSWORD SHOW!"
        t_done )
};
const txt_cmd_s RadioTower2FBuenaDoYouKnowPasswordText[] = {
    text_start("BUENA: Hi!"
        t_line "Did you tune in to"
        t_cont "my radio show?"
        t_para "Do you remember"
        t_line "today's password?"
        t_done )
};
const txt_cmd_s RadioTower2FBuenaJoinTheShowText[] = {
    text_start("BUENA: Oh, wow!"
        t_line "Thank you!"
        t_para "What was your name"
        t_line "again?"
        t_para "…<PLAY_G>, OK!"
        t_para "Come on, <PLAY_G>."
        t_line "Join the show."
        t_done )
};
const txt_cmd_s RadioTower2FBuenaEveryoneSayPasswordText[] = {
    text_start("BUENA: Everyone"
        t_line "ready?"
        t_para "I want to hear you"
        t_line "shout out today's"
        t_para "password for"
        t_line "<PLAY_G>!"
        t_done )
};
const txt_cmd_s RadioTower2FBuenaComeBackAfterListeningText[] = {
    text_start("BUENA: Come back"
        t_line "after you listen"
        t_para "to my show, OK?"
        t_line "Catch ya later!"
        t_done )
};
const txt_cmd_s RadioTower2FBuenaAlreadyPlayedText[] = {
    text_start("BUENA: Sorry…"
        t_para "You get just one"
        t_line "chance each day."
        t_para "Come back tomorrow"
        t_line "for another try!"
        t_done )
};
const txt_cmd_s RadioTower2FBuenaCorrectAnswerText[] = {
    text_start("BUENA: YIPPEE!"
        t_line "That's right!"
        t_para "You did tune in!"
        t_line "I'm so happy!"
        t_para "You earned one"
        t_line "point! Congrats!"
        t_done )
};
const txt_cmd_s RadioTower2FBuenaDidYouForgetText[] = {
    text_start("BUENA: Aww…"
        t_line "That's not it…"
        t_para "Did you forget the"
        t_line "password?"
        t_done )
};
const txt_cmd_s RadioTower2FBuenaThanksForComingText[] = {
    text_start("BUENA: Yup! Our"
        t_line "contestant was"
        t_para "<PLAY_G>."
        t_line "Thanks for coming!"
        t_para "I hope all you"
        t_line "listeners will"
        t_para "come too!"
        t_line "I'll be waiting!"
        t_done )
};
const txt_cmd_s RadioTower2FBuenaPasswordIsHelpText[] = {
    text_start("BUENA: Huh?"
        t_line "Today's password?"
        t_para "HELP, of course!"
        t_done )
};
const txt_cmd_s RadioTower2FBuenaCardIsFullText[] = {
    text_start("BUENA: Your BLUE"
        t_line "CARD's full."
        t_para "Trade it in for a"
        t_line "fabulous prize!"
        t_done )
};
const txt_cmd_s RadioTower2FBuenaTuneInAfterSixText[] = {
    text_start("BUENA: Tune in to"
        t_line "PASSWORD every"
        t_para "night from six to"
        t_line "midnight!"
        t_para "Tune in, then drop"
        t_line "in for a visit!"
        t_done )
};
const txt_cmd_s RadioTower2FBuenaNoBlueCardText[] = {
    text_start("BUENA: Oh? You"
        t_line "forgot to bring"
        t_cont "your BLUE CARD?"
        t_para "I can't give you"
        t_line "points if you"
        t_cont "don't have it."
        t_done )
};
const txt_cmd_s RadioTower2FBuenaOfferPhoneNumberText[] = {
    text_start("BUENA: Oh! Your"
        t_line "BLUE CARD reached"
        t_para _s(BLUE_CARD_POINT_CAP) " points today!"
        t_line "That's so wild!"
        t_para "Hmm… There isn't a"
        t_line "prize for hitting"
        t_cont _s(BLUE_CARD_POINT_CAP) " points, but…"
        t_para "You came by so"
        t_line "often, <PLAY_G>."
        t_para "I'll make you a"
        t_line "special deal!"
        t_para "How would you like"
        t_line "my phone number?"
        t_done )
};
const txt_cmd_s RadioTower2FBuenaOfferNumberAgainText[] = {
    text_start("BUENA: <PLAY_G>,"
        t_line "do you want to"
        t_para "register my phone"
        t_line "number?"
        t_done )
};
const txt_cmd_s RadioTower2FRegisteredBuenasNumberText[] = {
    text_start("<PLAYER> registered"
        t_line "BUENA's number."
        t_done )
};
const txt_cmd_s RadioTower2FBuenaCallMeText[] = {
    text_start("BUENA: I look"
        t_line "forward to hearing"
        t_cont "from you!"
        t_done )
};
const txt_cmd_s RadioTower2FBuenaSadRejectedText[] = {
    text_start("BUENA: Aww… It's a"
        t_line "special prize…"
        t_done )
};
const txt_cmd_s RadioTower2FBuenaYourPhoneIsFullText[] = {
    text_start("BUENA: <PLAY_G>,"
        t_line "your phone list"
        t_para "has no room left"
        t_line "for me…"
        t_done )
};
const txt_cmd_s RadioTower2FBuenaReceptionistPointsForPrizesText[] = {
    text_start("You can cash in"
        t_line "your saved points"
        t_para "for a lovely prize"
        t_line "of your choice!"
        t_done )
};
const txt_cmd_s RadioTower2FBuenaReceptionistNoCardText[] = {
    text_start("You can't trade in"
        t_line "points without"
        t_cont "your BLUE CARD."
        t_para "Don't forget your"
        t_line "BLUE CARD!"
        t_done )
};
const txt_cmd_s RadioTower2FSalesSignText[] = {
    text_start("2F SALES"
        t_done )
};
const txt_cmd_s RadioTower2FOaksPKMNTalkSignText[] = {
    text_start("PROF.OAK'S #MON"
        t_line "TALK"
        t_para "The Hottest Show"
        t_line "on the Air!"
        t_done )
};
const txt_cmd_s RadioTower2FPokemonRadioSignText[] = {
    text_start("Anywhere, Anytime"
        t_line "#MON Radio"
        t_done )
    //db(0, 0) // filler
};
