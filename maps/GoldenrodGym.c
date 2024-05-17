#include "../constants.h"
#include "../util/scripting.h"
#include "GoldenrodGym.h"
//// EVENTS
enum {
    GOLDENRODGYM_WHITNEY = 2,
    GOLDENRODGYM_LASS1,
    GOLDENRODGYM_LASS2,
    GOLDENRODGYM_BEAUTY1,
    GOLDENRODGYM_BEAUTY2,
    GOLDENRODGYM_GYM_GUIDE,
};

const Script_fn_t GoldenrodGym_SceneScripts[] = {
    GoldenrodGym_MapScripts_DummyScene0 , //  SCENE_GOLDENRODGYM_NOTHING,
    GoldenrodGym_MapScripts_DummyScene1 , //  SCENE_GOLDENRODGYM_WHITNEY_STOPS_CRYING,
};

const struct MapCallback GoldenrodGym_MapCallbacks[] = {
    0,
};

const struct MapScripts GoldenrodGym_MapScripts = {
    .scene_script_count = lengthof(GoldenrodGym_SceneScripts),
    .scene_scripts = GoldenrodGym_SceneScripts,

    .callback_count = 0, // lengthof(GoldenrodGym_MapCallbacks),
    .callbacks = GoldenrodGym_MapCallbacks,
};

static const struct CoordEvent GoldenrodGym_CoordEvents[] = {
    coord_event(8, 5, SCENE_GOLDENRODGYM_WHITNEY_STOPS_CRYING, &WhitneyCriesScript),
};

static const struct BGEvent GoldenrodGym_BGEvents[] = {
    bg_event(1, 15, BGEVENT_READ, &GoldenrodGymStatue),
    bg_event(4, 15, BGEVENT_READ, &GoldenrodGymStatue),
};

static const struct WarpEventData GoldenrodGym_WarpEvents[] = {
    warp_event(2, 17, GOLDENROD_CITY, 1),
    warp_event(3, 17, GOLDENROD_CITY, 1),
};

static const struct ObjEvent GoldenrodGym_ObjectEvents[] = {
    object_event(8, 3, SPRITE_WHITNEY, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &GoldenrodGymWhitneyScript, -1),
    object_event(9, 13, SPRITE_LASS, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 4, &TrainerLassCarrie, -1),
    object_event(9, 6, SPRITE_LASS, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 1, &TrainerLassBridget, -1),
    object_event(0, 2, SPRITE_BEAUTY, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerBeautyVictoria, -1),
    object_event(19, 5, SPRITE_BEAUTY, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerBeautySamantha, -1),
    object_event(5, 15, SPRITE_GYM_GUIDE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &GoldenrodGymGuideScript, -1),
};

const struct MapEvents GoldenrodGym_MapEvents = {
    .warp_event_count = lengthof(GoldenrodGym_WarpEvents),
    .warp_events = GoldenrodGym_WarpEvents,

    .coord_event_count = lengthof(GoldenrodGym_CoordEvents),
    .coord_events = GoldenrodGym_CoordEvents,

    .bg_event_count = lengthof(GoldenrodGym_BGEvents),
    .bg_events = GoldenrodGym_BGEvents,

    .obj_event_count = lengthof(GoldenrodGym_ObjectEvents),
    .obj_events = GoldenrodGym_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "GoldenrodGym.h"

bool GoldenrodGym_MapScripts_DummyScene0(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool GoldenrodGym_MapScripts_DummyScene1(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool GoldenrodGymWhitneyScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    checkevent(EVENT_BEAT_WHITNEY)
    iftrue(FightDone)
    opentext
    writetext(WhitneyBeforeText)
    waitbutton
    closetext
    winlosstext(WhitneyShouldntBeSoSeriousText, 0)
    loadtrainer(WHITNEY, WHITNEY1)
    startbattle
    reloadmapafterbattle
    setevent(EVENT_BEAT_WHITNEY)
    setevent(EVENT_MADE_WHITNEY_CRY)
    setscene(SCENE_GOLDENRODGYM_WHITNEY_STOPS_CRYING)
    setevent(EVENT_BEAT_BEAUTY_VICTORIA)
    setevent(EVENT_BEAT_BEAUTY_SAMANTHA)
    setevent(EVENT_BEAT_LASS_CARRIE)
    setevent(EVENT_BEAT_LASS_BRIDGET)
FightDone:
    opentext
    checkevent(EVENT_MADE_WHITNEY_CRY)
    iffalse(StoppedCrying)
    writetext(WhitneyYouMeanieText)
    waitbutton
    closetext
    s_end
StoppedCrying:
    checkevent(EVENT_GOT_TM45_ATTRACT)
    iftrue(GotAttract)
    checkflag(ENGINE_PLAINBADGE)
    iftrue(GotPlainBadge)
    writetext(WhitneyWhatDoYouWantText)
    promptbutton
    waitsfx
    writetext(PlayerReceivedPlainBadgeText)
    playsound(SFX_GET_BADGE)
    waitsfx
    setflag(ENGINE_PLAINBADGE)
    readvar(VAR_BADGES)
    scall(GoldenrodGymActivateRockets)
GotPlainBadge:
    writetext(WhitneyPlainBadgeText)
    promptbutton
    verbosegiveitem(TM_ATTRACT, 1)
    iffalse(NoRoomForAttract)
    setevent(EVENT_GOT_TM45_ATTRACT)
    writetext(WhitneyAttractText)
    waitbutton
    closetext
    s_end
GotAttract:
    writetext(WhitneyGoodCryText)
    waitbutton
NoRoomForAttract:
    closetext
    s_end
    SCRIPT_END
}
bool GoldenrodGymActivateRockets(script_s* s) {
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
const struct TrainerObj TrainerLassCarrie = {LASS, CARRIE, EVENT_BEAT_LASS_CARRIE, LassCarrieSeenText, LassCarrieBeatenText, 0, TrainerLassCarrie_Script};
bool TrainerLassCarrie_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(LassCarrieAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool WhitneyCriesScript(script_s* s) {
    SCRIPT_BEGIN
    showemote(EMOTE_SHOCK, GOLDENRODGYM_LASS2, 15)
    applymovement(GOLDENRODGYM_LASS2, BridgetWalksUpMovement)
    turnobject(PLAYER, DOWN)
    opentext
    writetext(BridgetWhitneyCriesText)
    waitbutton
    closetext
    applymovement(GOLDENRODGYM_LASS2, BridgetWalksAwayMovement)
    setscene(SCENE_GOLDENRODGYM_NOTHING)
    clearevent(EVENT_MADE_WHITNEY_CRY)
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerLassBridget = {LASS, BRIDGET, EVENT_BEAT_LASS_BRIDGET, LassBridgetSeenText, LassBridgetBeatenText, 0, TrainerLassBridget_Script};
bool TrainerLassBridget_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(LassBridgetAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerBeautyVictoria = {BEAUTY, VICTORIA, EVENT_BEAT_BEAUTY_VICTORIA, BeautyVictoriaSeenText, BeautyVictoriaBeatenText, 0, TrainerBeautyVictoria_Script};
bool TrainerBeautyVictoria_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(BeautyVictoriaAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerBeautySamantha = {BEAUTY, SAMANTHA, EVENT_BEAT_BEAUTY_SAMANTHA, BeautySamanthaSeenText, BeautySamanthaBeatenText, 0, TrainerBeautySamantha_Script};
bool TrainerBeautySamantha_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(BeautySamanthaAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool GoldenrodGymGuideScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    checkevent(EVENT_BEAT_WHITNEY)
    iftrue(GoldenrodGymGuideWinScript)
    opentext
    writetext(GoldenrodGymGuideText)
    waitbutton
    closetext
    s_end
GoldenrodGymGuideWinScript:
    opentext
    writetext(GoldenrodGymGuideWinText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool GoldenrodGymStatue(script_s* s) {
    SCRIPT_BEGIN
    checkflag(ENGINE_PLAINBADGE)
    iftrue(Beaten)
    jumpstd(GymStatue1Script)
Beaten:
    gettrainername(STRING_BUFFER_4, WHITNEY, WHITNEY1)
    jumpstd(GymStatue2Script)
    SCRIPT_END
}
const uint8_t BridgetWalksUpMovement[] = {
    step(LEFT),
    turn_head(UP),
    movement_step_end,
};
const uint8_t BridgetWalksAwayMovement[] = {
    step(RIGHT),
    turn_head(LEFT),
    movement_step_end,
};
const txt_cmd_s WhitneyBeforeText[] = {
    text_start("Hi! I'm WHITNEY!"
        t_para "Everyone was into"
        t_line "#MON, so I got"
        t_cont "into it too!"
        t_para "#MON are"
        t_line "super-cute!"
        t_para "You want to bat-"
        t_line "tle? I'm warning"
        t_cont "you--I'm good!"
        t_done )
};
const txt_cmd_s WhitneyShouldntBeSoSeriousText[] = {
    text_start("Sob…"
        t_para "…Waaaaaaah!"
        t_line "You're mean!"
        t_para "You shouldn't be"
        t_line "so serious! You…"
        t_cont "you child, you!"
        t_done )
};
const txt_cmd_s WhitneyYouMeanieText[] = {
    text_start("Waaaaah!"
        t_para "Waaaaah!"
        t_para "…Snivel, hic…"
        t_line "…You meanie!"
        t_done )
};
const txt_cmd_s WhitneyWhatDoYouWantText[] = {
    text_start("…Sniff…"
        t_para "What? What do you"
        t_line "want? A BADGE?"
        t_para "Oh, right."
        t_line "I forgot. Here's"
        t_cont "PLAINBADGE."
        t_done )
};
const txt_cmd_s PlayerReceivedPlainBadgeText[] = {
    text_start("<PLAYER> received"
        t_line "PLAINBADGE."
        t_done )
};
const txt_cmd_s WhitneyPlainBadgeText[] = {
    text_start("PLAINBADGE lets"
        t_line "your #MON use"
        t_para "STRENGTH outside"
        t_line "of battle."
        t_para "It also boosts"
        t_line "your #MON's"
        t_cont "SPEED."
        t_para "Oh, you can have"
        t_line "this too!"
        t_done )
};
const txt_cmd_s WhitneyAttractText[] = {
    text_start("It's ATTRACT!"
        t_line "It makes full use"
        t_para "of a #MON's"
        t_line "charm."
        t_para "Isn't it just per-"
        t_line "fect for a cutie"
        t_cont "like me?"
        t_done )
};
const txt_cmd_s WhitneyGoodCryText[] = {
    text_start("Ah, that was a"
        t_line "good cry!"
        t_para "Come for a visit"
        t_line "again! Bye-bye!"
        t_done )
};
const txt_cmd_s LassCarrieSeenText[] = {
    text_start("Don't let my"
        t_line "#MON's cute"
        t_para "looks fool you."
        t_line "They can whip you!"
        t_done )
};
const txt_cmd_s LassCarrieBeatenText[] = {
    text_start("Darn… I thought"
        t_line "you were weak…"
        t_done )
};
const txt_cmd_s LassCarrieAfterBattleText[] = {
    text_start("Do my #MON"
        t_line "think I'm cute?"
        t_done )
};
const txt_cmd_s LassBridgetSeenText[] = {
    text_start("I like cute #-"
        t_line "MON better than"
        t_cont "strong #MON."
        t_para "But I have strong"
        t_line "and cute #MON!"
        t_done )
};
const txt_cmd_s LassBridgetBeatenText[] = {
    text_start("Oh, no, no, no!"
        t_done )
};
const txt_cmd_s LassBridgetAfterBattleText[] = {
    text_start("I'm trying to beat"
        t_line "WHITNEY, but…"
        t_cont "It's depressing."
        t_para "I'm okay! If I"
        t_line "lose, I'll just"
        t_para "try harder next"
        t_line "time!"
        t_done )
};
const txt_cmd_s BridgetWhitneyCriesText[] = {
    text_start("Oh, no. You made"
        t_line "WHITNEY cry."
        t_para "It's OK. She'll"
        t_line "stop soon. She"
        t_para "always cries when"
        t_line "she loses."
        t_done )
};
const txt_cmd_s BeautyVictoriaSeenText[] = {
    text_start("Oh, you are a cute"
        t_line "little trainer! "
        t_para "I like you, but I"
        t_line "won't hold back!"
        t_done )
};
const txt_cmd_s BeautyVictoriaBeatenText[] = {
    text_start("Let's see… Oops,"
        t_line "it's over?"
        t_done )
};
const txt_cmd_s BeautyVictoriaAfterBattleText[] = {
    text_start("Wow, you must be"
        t_line "good to beat me!"
        t_cont "Keep it up!"
        t_done )
};
const txt_cmd_s BeautySamanthaSeenText[] = {
    text_start("Give it your best"
        t_line "shot, or I'll take"
        t_cont "you down!"
        t_done )
};
const txt_cmd_s BeautySamanthaBeatenText[] = {
    text_start("No! Oh, MEOWTH,"
        t_line "I'm so sorry!"
        t_done )
};
const txt_cmd_s BeautySamanthaAfterBattleText[] = {
    text_start("I taught MEOWTH"
        t_line "moves for taking"
        t_cont "on any type…"
        t_done )
};
const txt_cmd_s GoldenrodGymGuideText[] = {
    text_start("Yo! CHAMP in"
        t_line "making!"
        t_para "This GYM is home"
        t_line "to normal-type"
        t_cont "#MON trainers."
        t_para "I recommend you"
        t_line "use fighting-type"
        t_cont "#MON."
        t_done )
};
const txt_cmd_s GoldenrodGymGuideWinText[] = {
    text_start("You won? Great! I"
        t_line "was busy admiring"
        t_cont "the ladies here."
        t_done )
    //db(0, 0) // filler
};
