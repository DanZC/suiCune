#include "../constants.h"
#include "../util/scripting.h"
#include "MahoganyGym.h"
//// EVENTS
enum {
    MAHOGANYGYM_PRYCE = 2,
    MAHOGANYGYM_BEAUTY1,
    MAHOGANYGYM_ROCKER1,
    MAHOGANYGYM_BEAUTY2,
    MAHOGANYGYM_ROCKER2,
    MAHOGANYGYM_ROCKER3,
    MAHOGANYGYM_GYM_GUIDE,
};

const Script_fn_t MahoganyGym_SceneScripts[] = {
    0,
};

const struct MapCallback MahoganyGym_MapCallbacks[] = {
    0,
};

const struct MapScripts MahoganyGym_MapScripts = {
    .scene_script_count = 0, // lengthof(MahoganyGym_SceneScripts),
    .scene_scripts = MahoganyGym_SceneScripts,

    .callback_count = 0, // lengthof(MahoganyGym_MapCallbacks),
    .callbacks = MahoganyGym_MapCallbacks,
};

static const struct CoordEvent MahoganyGym_CoordEvents[] = {
    0,
};

static const struct BGEvent MahoganyGym_BGEvents[] = {
    bg_event(3, 15, BGEVENT_READ, &MahoganyGymStatue),
    bg_event(6, 15, BGEVENT_READ, &MahoganyGymStatue),
};

static const struct WarpEventData MahoganyGym_WarpEvents[] = {
    warp_event(4, 17, MAHOGANY_TOWN, 3),
    warp_event(5, 17, MAHOGANY_TOWN, 3),
};

static const struct ObjEvent MahoganyGym_ObjectEvents[] = {
    object_event(5, 3, SPRITE_PRYCE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, &MahoganyGymPryceScript, -1),
    object_event(4, 6, SPRITE_BEAUTY, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 1, &TrainerSkierRoxanne, -1),
    object_event(0, 17, SPRITE_ROCKER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 1, &TrainerBoarderRonald, -1),
    object_event(9, 17, SPRITE_BEAUTY, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 1, &TrainerSkierClarissa, -1),
    object_event(5, 9, SPRITE_ROCKER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 1, &TrainerBoarderBrad, -1),
    object_event(2, 4, SPRITE_ROCKER, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 1, &TrainerBoarderDouglas, -1),
    object_event(7, 15, SPRITE_GYM_GUIDE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &MahoganyGymGuideScript, -1),
};

const struct MapEvents MahoganyGym_MapEvents = {
    .warp_event_count = lengthof(MahoganyGym_WarpEvents),
    .warp_events = MahoganyGym_WarpEvents,

    .coord_event_count = 0, // lengthof(MahoganyGym_CoordEvents),
    .coord_events = MahoganyGym_CoordEvents,

    .bg_event_count = lengthof(MahoganyGym_BGEvents),
    .bg_events = MahoganyGym_BGEvents,

    .obj_event_count = lengthof(MahoganyGym_ObjectEvents),
    .obj_events = MahoganyGym_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "MahoganyGym.h"

bool MahoganyGymPryceScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_BEAT_PRYCE)
    iftrue(FightDone)
    writetext(PryceText_Intro)
    waitbutton
    closetext
    winlosstext(PryceText_Impressed, 0)
    loadtrainer(PRYCE, PRYCE1)
    startbattle
    reloadmapafterbattle
    setevent(EVENT_BEAT_PRYCE)
    opentext
    writetext(Text_ReceivedGlacierBadge)
    playsound(SFX_GET_BADGE)
    waitsfx
    setflag(ENGINE_GLACIERBADGE)
    readvar(VAR_BADGES)
    scall(MahoganyGymActivateRockets)
FightDone:
    checkevent(EVENT_GOT_TM16_ICY_WIND)
    iftrue_jump(PryceScript_Defeat)
    setevent(EVENT_BEAT_SKIER_ROXANNE)
    setevent(EVENT_BEAT_SKIER_CLARISSA)
    setevent(EVENT_BEAT_BOARDER_RONALD)
    setevent(EVENT_BEAT_BOARDER_BRAD)
    setevent(EVENT_BEAT_BOARDER_DOUGLAS)
    writetext(PryceText_GlacierBadgeSpeech)
    promptbutton
    verbosegiveitem(TM_ICY_WIND, 1)
    iffalse_jump(MahoganyGym_NoRoomForIcyWind)
    setevent(EVENT_GOT_TM16_ICY_WIND)
    writetext(PryceText_IcyWindSpeech)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool PryceScript_Defeat(script_s* s) {
    SCRIPT_BEGIN
    writetext(PryceText_CherishYourPokemon)
    waitbutton
    SCRIPT_FALLTHROUGH(MahoganyGym_NoRoomForIcyWind)
}
bool MahoganyGym_NoRoomForIcyWind(script_s* s) {
    SCRIPT_BEGIN
    closetext
    s_end
    SCRIPT_END
}
bool MahoganyGymActivateRockets(script_s* s) {
    SCRIPT_BEGIN
    ifequal(7, RadioTowerRockets)
    ifequal(6, GoldenrodRockets)
    s_end
GoldenrodRockets:
    jumpstd(GoldenrodRocketsScript)
RadioTowerRockets:
    jumpstd(RadioTowerRocketsScript)
    SCRIPT_END
}
const struct TrainerObj TrainerSkierRoxanne = {SKIER, ROXANNE, EVENT_BEAT_SKIER_ROXANNE, SkierRoxanneSeenText, SkierRoxanneBeatenText, 0, TrainerSkierRoxanne_Script};
bool TrainerSkierRoxanne_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SkierRoxanneAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSkierClarissa = {SKIER, CLARISSA, EVENT_BEAT_SKIER_CLARISSA, SkierClarissaSeenText, SkierClarissaBeatenText, 0, TrainerSkierClarissa_Script};
bool TrainerSkierClarissa_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SkierClarissaAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerBoarderRonald = {BOARDER, RONALD, EVENT_BEAT_BOARDER_RONALD, BoarderRonaldSeenText, BoarderRonaldBeatenText, 0, TrainerBoarderRonald_Script};
bool TrainerBoarderRonald_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(BoarderRonaldAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerBoarderBrad = {BOARDER, BRAD, EVENT_BEAT_BOARDER_BRAD, BoarderBradSeenText, BoarderBradBeatenText, 0, TrainerBoarderBrad_Script};
bool TrainerBoarderBrad_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(BoarderBradAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerBoarderDouglas = {BOARDER, DOUGLAS, EVENT_BEAT_BOARDER_DOUGLAS, BoarderDouglasSeenText, BoarderDouglasBeatenText, 0, TrainerBoarderDouglas_Script};
bool TrainerBoarderDouglas_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(BoarderDouglasAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool MahoganyGymGuideScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_BEAT_PRYCE)
    iftrue(MahoganyGymGuideWinScript)
    writetext(MahoganyGymGuideText)
    waitbutton
    closetext
    s_end
MahoganyGymGuideWinScript:
    writetext(MahoganyGymGuideWinText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool MahoganyGymStatue(script_s* s) {
    SCRIPT_BEGIN
    checkflag(ENGINE_GLACIERBADGE)
    iftrue(Beaten)
    jumpstd(GymStatue1Script)
Beaten:
    gettrainername(STRING_BUFFER_4, PRYCE, PRYCE1)
    jumpstd(GymStatue2Script)
    SCRIPT_END
}
const txt_cmd_s PryceText_Intro[] = {
    text_start("#MON have many"
        t_line "experiences in"
        t_para "their lives, just "
        t_line "like we do. "
        t_para "I, too, have seen"
        t_line "and suffered much"
        t_cont "in my life."
        t_para "Since I am your"
        t_line "elder, let me show"
        t_cont "you what I mean."
        t_para "I have been with"
        t_line "#MON since"
        t_para "before you were"
        t_line "born."
        t_para "I do not lose"
        t_line "easily."
        t_para "I, PRYCE--the"
        t_line "winter trainer--"
        t_para "shall demonstrate"
        t_line "my power!"
        t_done )
};
const txt_cmd_s PryceText_Impressed[] = {
    text_start("Ah, I am impressed"
        t_line "by your prowess."
        t_para "With your strong"
        t_line "will, I know you"
        t_para "will overcome all"
        t_line "life's obstacles."
        t_para "You are worthy of"
        t_line "this BADGE!"
        t_done )
};
const txt_cmd_s Text_ReceivedGlacierBadge[] = {
    text_start("<PLAYER> received"
        t_line "GLACIERBADGE."
        t_done )
};
const txt_cmd_s PryceText_GlacierBadgeSpeech[] = {
    text_start("That BADGE will"
        t_line "raise the SPECIAL"
        t_cont "stats of #MON."
        t_para "It also lets your"
        t_line "#MON use WHIRL-"
        t_cont "POOL to get across"
        t_cont "real whirlpools."
        t_para "And this… This is"
        t_line "a gift from me!"
        t_done )
};
const txt_cmd_s PryceText_IcyWindSpeech[] = {
    text_start("That TM contains"
        t_line "ICY WIND."
        t_para "It inflicts damage"
        t_line "and lowers speed."
        t_para "It demonstrates"
        t_line "the harshness of"
        t_cont "winter."
        t_done )
};
const txt_cmd_s PryceText_CherishYourPokemon[] = {
    text_start("When the ice and"
        t_line "snow melt, spring"
        t_cont "arrives."
        t_para "You and your #-"
        t_line "MON will be to-"
        t_para "gether for many"
        t_line "years to come."
        t_para "Cherish your time"
        t_line "together!"
        t_done )
};
const txt_cmd_s BoarderRonaldSeenText[] = {
    text_start("I'll freeze your"
        t_line "#MON, so you"
        t_cont "can't do a thing!"
        t_done )
};
const txt_cmd_s BoarderRonaldBeatenText[] = {
    text_start("Darn. I couldn't"
        t_line "do a thing."
        t_done )
};
const txt_cmd_s BoarderRonaldAfterBattleText[] = {
    text_start("I think there's a"
        t_line "move a #MON"
        t_para "can use while it's"
        t_line "frozen."
        t_done )
};
const txt_cmd_s BoarderBradSeenText[] = {
    text_start("This GYM has a"
        t_line "slippery floor."
        t_para "It's fun, isn't"
        t_line "it?"
        t_para "But hey--we're"
        t_line "not playing games"
        t_cont "here!"
        t_done )
};
const txt_cmd_s BoarderBradBeatenText[] = {
    text_start("Do you see how"
        t_line "serious we are?"
        t_done )
};
const txt_cmd_s BoarderBradAfterBattleText[] = {
    text_start("This GYM is great."
        t_line "I love boarding"
        t_cont "with my #MON!"
        t_done )
};
const txt_cmd_s BoarderDouglasSeenText[] = {
    text_start("I know PRYCE's"
        t_line "secret."
        t_done )
};
const txt_cmd_s BoarderDouglasBeatenText[] = {
    text_start("OK. I'll tell you"
        t_line "PRYCE's secret."
        t_done )
};
const txt_cmd_s BoarderDouglasAfterBattleText[] = {
    text_start("The secret behind"
        t_line "PRYCE's power…"
        t_para "He meditates under"
        t_line "a waterfall daily"
        t_para "to strengthen his"
        t_line "mind and body."
        t_done )
};
const txt_cmd_s SkierRoxanneSeenText[] = {
    text_start("To get to PRYCE,"
        t_line "our GYM LEADER,"
        t_para "you need to think"
        t_line "before you skate."
        t_done )
};
const txt_cmd_s SkierRoxanneBeatenText[] = {
    text_start("I wouldn't lose to"
        t_line "you in skiing!"
        t_done )
};
const txt_cmd_s SkierRoxanneAfterBattleText[] = {
    text_start("If you don't skate"
        t_line "with precision,"
        t_para "you won't get far"
        t_line "in this GYM."
        t_done )
};
const txt_cmd_s SkierClarissaSeenText[] = {
    text_start("Check out my"
        t_line "parallel turn!"
        t_done )
};
const txt_cmd_s SkierClarissaBeatenText[] = {
    text_start("No! You made me"
        t_line "wipe out!"
        t_done )
};
const txt_cmd_s SkierClarissaAfterBattleText[] = {
    text_start("I shouldn't have"
        t_line "been bragging"
        t_cont "about my skiing…"
        t_done )
};
const txt_cmd_s MahoganyGymGuideText[] = {
    text_start("PRYCE is a veteran"
        t_line "who has trained"
        t_para "#MON for some"
        t_line "50 years."
        t_para "He's said to be"
        t_line "good at freezing"
        t_para "opponents with"
        t_line "ice-type moves."
        t_para "That means you"
        t_line "should melt him"
        t_para "with your burning"
        t_line "ambition!"
        t_done )
};
const txt_cmd_s MahoganyGymGuideWinText[] = {
    text_start("PRYCE is some-"
        t_line "thing, but you're"
        t_cont "something else!"
        t_para "That was a hot"
        t_line "battle that"
        t_para "bridged the gen-"
        t_line "eration gap!"
        t_done )
    //db(0, 0) // filler
};
