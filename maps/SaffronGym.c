#include "../constants.h"
#include "../util/scripting.h"
#include "SaffronGym.h"
//// EVENTS
enum {
    SAFFRONGYM_SABRINA = 2,
    SAFFRONGYM_GRANNY1,
    SAFFRONGYM_YOUNGSTER1,
    SAFFRONGYM_GRANNY2,
    SAFFRONGYM_YOUNGSTER2,
    SAFFRONGYM_GYM_GUIDE,
};

const Script_fn_t SaffronGym_SceneScripts[] = {
    0,
};

const struct MapCallback SaffronGym_MapCallbacks[] = {
    0,
};

const struct MapScripts SaffronGym_MapScripts = {
    .scene_script_count = 0, // lengthof(SaffronGym_SceneScripts),
    .scene_scripts = SaffronGym_SceneScripts,

    .callback_count = 0, // lengthof(SaffronGym_MapCallbacks),
    .callbacks = SaffronGym_MapCallbacks,
};

static const struct CoordEvent SaffronGym_CoordEvents[] = {
    0,
};

static const struct BGEvent SaffronGym_BGEvents[] = {
    bg_event(8, 15, BGEVENT_READ, &SaffronGymStatue),
};

static const struct WarpEventData SaffronGym_WarpEvents[] = {
    warp_event(8, 17, SAFFRON_CITY, 2),
    warp_event(9, 17, SAFFRON_CITY, 2),
    warp_event(11, 15, SAFFRON_GYM, 18),
    warp_event(19, 15, SAFFRON_GYM, 19),
    warp_event(19, 11, SAFFRON_GYM, 20),
    warp_event(1, 11, SAFFRON_GYM, 21),
    warp_event(5, 3, SAFFRON_GYM, 22),
    warp_event(11, 5, SAFFRON_GYM, 23),
    warp_event(1, 15, SAFFRON_GYM, 24),
    warp_event(19, 3, SAFFRON_GYM, 25),
    warp_event(15, 17, SAFFRON_GYM, 26),
    warp_event(5, 17, SAFFRON_GYM, 27),
    warp_event(5, 9, SAFFRON_GYM, 28),
    warp_event(9, 3, SAFFRON_GYM, 29),
    warp_event(15, 9, SAFFRON_GYM, 30),
    warp_event(15, 5, SAFFRON_GYM, 31),
    warp_event(1, 5, SAFFRON_GYM, 32),
    warp_event(19, 17, SAFFRON_GYM, 3),
    warp_event(19, 9, SAFFRON_GYM, 4),
    warp_event(1, 9, SAFFRON_GYM, 5),
    warp_event(5, 5, SAFFRON_GYM, 6),
    warp_event(11, 3, SAFFRON_GYM, 7),
    warp_event(1, 17, SAFFRON_GYM, 8),
    warp_event(19, 5, SAFFRON_GYM, 9),
    warp_event(15, 15, SAFFRON_GYM, 10),
    warp_event(5, 15, SAFFRON_GYM, 11),
    warp_event(5, 11, SAFFRON_GYM, 12),
    warp_event(9, 5, SAFFRON_GYM, 13),
    warp_event(15, 11, SAFFRON_GYM, 14),
    warp_event(15, 3, SAFFRON_GYM, 15),
    warp_event(1, 3, SAFFRON_GYM, 16),
    warp_event(11, 9, SAFFRON_GYM, 17),
};

static const struct ObjEvent SaffronGym_ObjectEvents[] = {
    object_event(9, 8, SPRITE_SABRINA, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &SaffronGymSabrinaScript, -1),
    object_event(17, 16, SPRITE_GRANNY, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_TRAINER, 3, &TrainerMediumRebecca, -1),
    object_event(3, 16, SPRITE_YOUNGSTER, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerPsychicFranklin, -1),
    object_event(3, 4, SPRITE_GRANNY, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_TRAINER, 2, &TrainerMediumDoris, -1),
    object_event(17, 4, SPRITE_YOUNGSTER, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 2, &TrainerPsychicJared, -1),
    object_event(9, 14, SPRITE_GYM_GUIDE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &SaffronGymGuideScript, -1),
};

const struct MapEvents SaffronGym_MapEvents = {
    .warp_event_count = lengthof(SaffronGym_WarpEvents),
    .warp_events = SaffronGym_WarpEvents,

    .coord_event_count = 0, // lengthof(SaffronGym_CoordEvents),
    .coord_events = SaffronGym_CoordEvents,

    .bg_event_count = lengthof(SaffronGym_BGEvents),
    .bg_events = SaffronGym_BGEvents,

    .obj_event_count = lengthof(SaffronGym_ObjectEvents),
    .obj_events = SaffronGym_ObjectEvents,
};

//// CODE

bool SaffronGymSabrinaScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkflag(ENGINE_MARSHBADGE)
    iftrue(FightDone)
    writetext(SabrinaIntroText)
    waitbutton
    closetext
    winlosstext(SabrinaWinLossText, 0)
    loadtrainer(SABRINA, SABRINA1)
    startbattle
    reloadmapafterbattle
    setevent(EVENT_BEAT_SABRINA)
    setevent(EVENT_BEAT_MEDIUM_REBECCA)
    setevent(EVENT_BEAT_MEDIUM_DORIS)
    setevent(EVENT_BEAT_PSYCHIC_FRANKLIN)
    setevent(EVENT_BEAT_PSYCHIC_JARED)
    opentext
    writetext(ReceivedMarshBadgeText)
    playsound(SFX_GET_BADGE)
    waitsfx
    setflag(ENGINE_MARSHBADGE)
    writetext(SabrinaMarshBadgeText)
    waitbutton
    closetext
    s_end
FightDone:
    writetext(SabrinaFightDoneText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerMediumRebecca = {MEDIUM, REBECCA, EVENT_BEAT_MEDIUM_REBECCA, MediumRebeccaSeenText, MediumRebeccaBeatenText, 0, TrainerMediumRebecca_Script};
bool TrainerMediumRebecca_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(MediumRebeccaAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerPsychicFranklin = {PSYCHIC_T, FRANKLIN, EVENT_BEAT_PSYCHIC_FRANKLIN, PsychicFranklinSeenText, PsychicFranklinBeatenText, 0, TrainerPsychicFranklin_Script};
bool TrainerPsychicFranklin_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(PsychicFranklinAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerMediumDoris = {MEDIUM, DORIS, EVENT_BEAT_MEDIUM_DORIS, MediumDorisSeenText, MediumDorisBeatenText, 0, TrainerMediumDoris_Script};
bool TrainerMediumDoris_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(MediumDorisAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerPsychicJared = {PSYCHIC_T, JARED, EVENT_BEAT_PSYCHIC_JARED, PsychicJaredSeenText, PsychicJaredBeatenText, 0, TrainerPsychicJared_Script};
bool TrainerPsychicJared_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(PsychicJaredAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool SaffronGymGuideScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_BEAT_SABRINA)
    iftrue(SaffronGymGuideWinScript)
    writetext(SaffronGymGuideText)
    waitbutton
    closetext
    s_end
SaffronGymGuideWinScript:
    writetext(SaffronGymGuideWinText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool SaffronGymStatue(script_s* s) {
    SCRIPT_BEGIN
    checkflag(ENGINE_MARSHBADGE)
    iftrue(Beaten)
    jumpstd(GymStatue1Script)
Beaten:
    gettrainername(STRING_BUFFER_4, SABRINA, SABRINA1)
    jumpstd(GymStatue2Script)
    SCRIPT_END
}
const txt_cmd_s SabrinaIntroText[] = {
    text_start("SABRINA: I knew"
        t_line "you were coming…"
        t_para "Three years ago I"
        t_line "had a vision of"
        t_cont "your arrival."
        t_para "You're after my"
        t_line "BADGE."
        t_para "I don't enjoy bat-"
        t_line "tling, but it's my"
        t_para "duty as a LEADER"
        t_line "to confer BADGES"
        t_para "on anyone who has"
        t_line "proven him- or"
        t_cont "herself worthy."
        t_para "Since you wish it,"
        t_line "I will show you my"
        t_cont "psychic powers!"
        t_done )
};
const txt_cmd_s SabrinaWinLossText[] = {
    text_start("SABRINA: Your"
        t_line "power…"
        t_para "It far exceeds"
        t_line "what I foresaw…"
        t_para "Maybe it isn't"
        t_line "possible to fully"
        t_para "predict what the"
        t_line "future holds…"
        t_para "OK, you win. You"
        t_line "earned yourself"
        t_cont "MARSHBADGE."
        t_done )
};
const txt_cmd_s ReceivedMarshBadgeText[] = {
    text_start("<PLAYER> received"
        t_line "MARSHBADGE."
        t_done )
};
const txt_cmd_s SabrinaMarshBadgeText[] = {
    text_start("SABRINA: MARSH-"
        t_line "BADGE draws out"
        t_para "your subliminal"
        t_line "powers…"
        t_para "Although I failed"
        t_line "to accurately pre-"
        t_cont "dict your power,"
        t_cont "this much I know"
        t_cont "to be true."
        t_para "You will become a"
        t_line "celebrated and"
        t_cont "beloved CHAMPION!"
        t_done )
};
const txt_cmd_s SabrinaFightDoneText[] = {
    text_start("SABRINA: Your love"
        t_line "for your #MON"
        t_para "overwhelmed my"
        t_line "psychic power…"
        t_para "The power of love,"
        t_line "I think, is also a"
        t_para "kind of psychic"
        t_line "power…"
        t_done )
};
const txt_cmd_s MediumRebeccaSeenText[] = {
    text_start("The power of all"
        t_line "those you defeated"
        t_cont "comes to me!"
        t_done )
};
const txt_cmd_s MediumRebeccaBeatenText[] = {
    text_start("Strong…"
        t_line "Far too strong…"
        t_done )
};
const txt_cmd_s MediumRebeccaAfterBattleText[] = {
    text_start("What is the source"
        t_line "of your power?"
        t_done )
};
const txt_cmd_s PsychicFranklinSeenText[] = {
    text_start("Psychic power is"
        t_line "the power of your"
        t_cont "soul."
        t_done )
};
const txt_cmd_s PsychicFranklinBeatenText[] = {
    text_start("Your soul has more"
        t_line "power than mine!"
        t_done )
};
const txt_cmd_s PsychicFranklinAfterBattleText[] = {
    text_start("You made your soul"
        t_line "stronger, not just"
        t_cont "your abilities."
        t_done )
};
const txt_cmd_s MediumDorisSeenText[] = {
    text_start("Fufufufu…"
        t_line "I see it clearly."
        t_para "I can see into"
        t_line "your soul!"
        t_done )
};
const txt_cmd_s MediumDorisBeatenText[] = {
    text_start("Though I read you,"
        t_line "I still lost…"
        t_done )
};
const txt_cmd_s MediumDorisAfterBattleText[] = {
    text_start("Darn! I forgot"
        t_line "that I predicted I"
        t_cont "would lose to you."
        t_done )
};
const txt_cmd_s PsychicJaredSeenText[] = {
    text_start("The FIGHTING DOJO"
        t_line "next door was once"
        t_cont "this city's GYM."
        t_done )
};
const txt_cmd_s PsychicJaredBeatenText[] = {
    text_start("I was no match…"
        t_done )
};
const txt_cmd_s PsychicJaredAfterBattleText[] = {
    text_start("KARATE KING, the"
        t_line "master of the"
        t_para "FIGHTING DOJO, was"
        t_line "just destroyed by"
        t_cont "SABRINA."
        t_done )
};
const txt_cmd_s SaffronGymGuideText[] = {
    text_start("Yo, CHAMP in"
        t_line "making!"
        t_para "A trainer as"
        t_line "skilled as you"
        t_para "doesn't need to be"
        t_line "told how to deal"
        t_para "with psychic-type"
        t_line "#MON, right?"
        t_para "I expect great"
        t_line "things from you!"
        t_para "Good luck!"
        t_done )
};
const txt_cmd_s SaffronGymGuideWinText[] = {
    text_start("That was another"
        t_line "fantastic battle!"
        t_done )
    //db(0, 0) // filler
};
