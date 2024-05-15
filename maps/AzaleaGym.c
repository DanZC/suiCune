#include "../constants.h"
#include "../util/scripting.h"
#include "AzaleaGym.h"
//// EVENTS
enum {
    AZALEAGYM_BUGSY = 2,
    AZALEAGYM_BUG_CATCHER1,
    AZALEAGYM_BUG_CATCHER2,
    AZALEAGYM_BUG_CATCHER3,
    AZALEAGYM_TWIN1,
    AZALEAGYM_TWIN2,
    AZALEAGYM_GYM_GUIDE,
};

const Script_fn_t AzaleaGym_SceneScripts[] = {
    0,
};

const struct MapCallback AzaleaGym_MapCallbacks[] = {
    0,
};

const struct MapScripts AzaleaGym_MapScripts = {
    .scene_script_count = 0, // lengthof(AzaleaGym_SceneScripts),
    .scene_scripts = AzaleaGym_SceneScripts,

    .callback_count = 0, // lengthof(AzaleaGym_MapCallbacks),
    .callbacks = AzaleaGym_MapCallbacks,
};

static const struct CoordEvent AzaleaGym_CoordEvents[] = {
    0,
};

static const struct BGEvent AzaleaGym_BGEvents[] = {
    bg_event(3, 13, BGEVENT_READ, &AzaleaGymStatue),
    bg_event(6, 13, BGEVENT_READ, &AzaleaGymStatue),
};

static const struct WarpEventData AzaleaGym_WarpEvents[] = {
    warp_event(4, 15, AZALEA_TOWN, 5),
    warp_event(5, 15, AZALEA_TOWN, 5),
};

static const struct ObjEvent AzaleaGym_ObjectEvents[] = {
    object_event(5, 7, SPRITE_BUGSY, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &AzaleaGymBugsyScript, -1),
    object_event(5, 3, SPRITE_BUG_CATCHER, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_TRAINER, 2, &TrainerBugCatcherBenny, -1),
    object_event(8, 8, SPRITE_BUG_CATCHER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_TRAINER, 3, &TrainerBugCatcherAl, -1),
    object_event(0, 2, SPRITE_BUG_CATCHER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_TRAINER, 3, &TrainerBugCatcherJosh, -1),
    object_event(4, 10, SPRITE_TWIN, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 1, &TrainerTwinsAmyandmay1, -1),
    object_event(5, 10, SPRITE_TWIN, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 1, &TrainerTwinsAmyandmay2, -1),
    object_event(7, 13, SPRITE_GYM_GUIDE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &AzaleaGymGuideScript, -1),
};

const struct MapEvents AzaleaGym_MapEvents = {
    .warp_event_count = lengthof(AzaleaGym_WarpEvents),
    .warp_events = AzaleaGym_WarpEvents,

    .coord_event_count = 0, // lengthof(AzaleaGym_CoordEvents),
    .coord_events = AzaleaGym_CoordEvents,

    .bg_event_count = lengthof(AzaleaGym_BGEvents),
    .bg_events = AzaleaGym_BGEvents,

    .obj_event_count = lengthof(AzaleaGym_ObjectEvents),
    .obj_events = AzaleaGym_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "AzaleaGym.h"

bool AzaleaGymBugsyScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_BEAT_BUGSY)
    iftrue(FightDone)
    writetext(BugsyText_INeverLose)
    waitbutton
    closetext
    winlosstext(BugsyText_ResearchIncomplete, 0)
    loadtrainer(BUGSY, BUGSY1)
    startbattle
    reloadmapafterbattle
    setevent(EVENT_BEAT_BUGSY)
    opentext
    writetext(Text_ReceivedHiveBadge)
    playsound(SFX_GET_BADGE)
    waitsfx
    setflag(ENGINE_HIVEBADGE)
    readvar(VAR_BADGES)
    scall(AzaleaGymActivateRockets)
FightDone:
    checkevent(EVENT_GOT_TM49_FURY_CUTTER)
    iftrue(GotFuryCutter)
    setevent(EVENT_BEAT_TWINS_AMY_AND_MAY)
    setevent(EVENT_BEAT_BUG_CATCHER_BENNY)
    setevent(EVENT_BEAT_BUG_CATCHER_AL)
    setevent(EVENT_BEAT_BUG_CATCHER_JOSH)
    writetext(BugsyText_HiveBadgeSpeech)
    promptbutton
    verbosegiveitem(TM_FURY_CUTTER, 1)
    iffalse(NoRoomForFuryCutter)
    setevent(EVENT_GOT_TM49_FURY_CUTTER)
    writetext(BugsyText_FuryCutterSpeech)
    waitbutton
    closetext
    s_end
GotFuryCutter:
    writetext(BugsyText_BugMonsAreDeep)
    waitbutton
NoRoomForFuryCutter:
    closetext
    s_end
    SCRIPT_END
}
bool AzaleaGymActivateRockets(script_s* s) {
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
const struct TrainerObj TrainerTwinsAmyandmay1 = {TWINS, AMYANDMAY1, EVENT_BEAT_TWINS_AMY_AND_MAY, TwinsAmyandmay1SeenText, TwinsAmyandmay1BeatenText, 0, TrainerTwinsAmyandmay1_Script};
bool TrainerTwinsAmyandmay1_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(TwinsAmyandmay1AfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerTwinsAmyandmay2 = {TWINS, AMYANDMAY2, EVENT_BEAT_TWINS_AMY_AND_MAY, TwinsAmyandmay2SeenText, TwinsAmyandmay2BeatenText, 0, TrainerTwinsAmyandmay2_Script};
bool TrainerTwinsAmyandmay2_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(TwinsAmyandmay2AfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerBugCatcherBenny = {BUG_CATCHER, BUG_CATCHER_BENNY, EVENT_BEAT_BUG_CATCHER_BENNY, BugCatcherBennySeenText, BugCatcherBennyBeatenText, 0, TrainerBugCatcherBenny_Script};
bool TrainerBugCatcherBenny_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(BugCatcherBennyAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerBugCatcherAl = {BUG_CATCHER, AL, EVENT_BEAT_BUG_CATCHER_AL, BugCatcherAlSeenText, BugCatcherAlBeatenText, 0, TrainerBugCatcherAl_Script};
bool TrainerBugCatcherAl_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(BugCatcherAlAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerBugCatcherJosh = {BUG_CATCHER, JOSH, EVENT_BEAT_BUG_CATCHER_JOSH, BugCatcherJoshSeenText, BugCatcherJoshBeatenText, 0, TrainerBugCatcherJosh_Script};
bool TrainerBugCatcherJosh_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(BugCatcherJoshAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool AzaleaGymGuideScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    checkevent(EVENT_BEAT_BUGSY)
    iftrue(AzaleaGymGuideWinScript)
    opentext
    writetext(AzaleaGymGuideText)
    waitbutton
    closetext
    s_end
AzaleaGymGuideWinScript:
    opentext
    writetext(AzaleaGymGuideWinText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool AzaleaGymStatue(script_s* s) {
    SCRIPT_BEGIN
    checkflag(ENGINE_HIVEBADGE)
    iftrue(Beaten)
    jumpstd(GymStatue1Script)
Beaten:
    gettrainername(STRING_BUFFER_4, BUGSY, BUGSY1)
    jumpstd(GymStatue2Script)
    SCRIPT_END
}
const txt_cmd_s BugsyText_INeverLose[] = {
    text_start("I'm BUGSY!"
        t_line "I never lose when"
        t_para "it comes to bug"
        t_line "#MON."
        t_para "My research is"
        t_line "going to make me"
        t_para "the authority on"
        t_line "bug #MON!"
        t_para "Let me demonstrate"
        t_line "what I've learned"
        t_cont "from my studies."
        t_done )
};
const txt_cmd_s BugsyText_ResearchIncomplete[] = {
    text_start("Whoa, amazing!"
        t_line "You're an expert"
        t_cont "on #MON!"
        t_para "My research isn't"
        t_line "complete yet."
        t_para "OK, you win. Take"
        t_line "this BADGE."
        t_done )
};
const txt_cmd_s Text_ReceivedHiveBadge[] = {
    text_start("<PLAYER> received"
        t_line "HIVEBADGE."
        t_done )
};
const txt_cmd_s BugsyText_HiveBadgeSpeech[] = {
    text_start("Do you know the"
        t_line "benefits of HIVE-"
        t_cont "BADGE?"
        t_para "If you have it,"
        t_line "#MON up to L30"
        t_para "will obey you,"
        t_line "even traded ones."
        t_para "#MON that know"
        t_line "CUT will be able"
        t_para "to use it outside"
        t_line "of battle too."
        t_para "Here, I also want"
        t_line "you to have this."
        t_done )
};
const txt_cmd_s BugsyText_FuryCutterSpeech[] = {
    text_start("TM49 contains"
        t_line "FURY CUTTER."
        t_para "If you don't miss,"
        t_line "it gets stronger"
        t_cont "every turn."
        t_para "The longer your"
        t_line "battle goes, the"
        t_cont "better it gets."
        t_para "Isn't that great?"
        t_line "I discovered it!"
        t_done )
};
const txt_cmd_s BugsyText_BugMonsAreDeep[] = {
    text_start("Bug #MON are"
        t_line "deep. There are"
        t_para "many mysteries to"
        t_line "be explored."
        t_para "Study your favor-"
        t_line "ites thoroughly."
        t_done )
};
const txt_cmd_s BugCatcherBennySeenText[] = {
    text_start("Bug #MON evolve"
        t_line "young. So they get"
        t_para "stronger that much"
        t_line "faster."
        t_done )
};
const txt_cmd_s BugCatcherBennyBeatenText[] = {
    text_start("Just evolving"
        t_line "isn't enough!"
        t_done )
};
const txt_cmd_s BugCatcherBennyAfterBattleText[] = {
    text_start("#MON become"
        t_line "stronger if they"
        t_cont "evolve. Really!"
        t_done )
};
const txt_cmd_s BugCatcherAlSeenText[] = {
    text_start("Bug #MON are"
        t_line "cool and tough!"
        t_para "I'll prove it to"
        t_line "you!"
        t_done )
};
const txt_cmd_s BugCatcherAlBeatenText[] = {
    text_start("You proved how"
        t_line "tough you are…"
        t_done )
};
const txt_cmd_s BugCatcherAlAfterBattleText[] = {
    text_start("They're so cool,"
        t_line "but most girls"
        t_para "don't like bug"
        t_line "#MON."
        t_para "I don't know why…"
        t_done )
};
const txt_cmd_s BugCatcherJoshSeenText[] = {
    text_start("You saved all the"
        t_line "SLOWPOKE? Whew,"
        t_cont "you're mighty!"
        t_para "But my grown-up"
        t_line "#MON are pretty"
        t_cont "tough too!"
        t_done )
};
const txt_cmd_s BugCatcherJoshBeatenText[] = {
    text_start("Urrgggh!"
        t_done )
};
const txt_cmd_s BugCatcherJoshAfterBattleText[] = {
    text_start("I guess I should"
        t_line "teach them better"
        t_cont "moves…"
        t_done )
};
const txt_cmd_s TwinsAmyandmay1SeenText[] = {
    text_start("AMY: Hi! Are you"
        t_line "challenging the"
        t_cont "LEADER? No way!"
        t_done )
};
const txt_cmd_s TwinsAmyandmay1BeatenText[] = {
    text_start("AMY & MAY: Oh,"
        t_line "double goodness!"
        t_done )
};
const txt_cmd_s TwinsAmyandmay1AfterBattleText[] = {
    text_start("AMY: You're"
        t_line "really strong!"
        t_done )
};
const txt_cmd_s TwinsAmyandmay2SeenText[] = {
    text_start("MAY: You want to"
        t_line "see the LEADER?"
        t_cont "We come first!"
        t_done )
};
const txt_cmd_s TwinsAmyandmay2BeatenText[] = {
    text_start("AMY & MAY: Oh,"
        t_line "double goodness!"
        t_done )
};
const txt_cmd_s TwinsAmyandmay2AfterBattleText[] = {
    text_start("MAY: Our bug #-"
        t_line "MON lost! Oh, what"
        t_cont "a shame."
        t_done )
};
const txt_cmd_s AzaleaGymGuideText[] = {
    text_start("Yo, challenger!"
        t_para "BUGSY's young, but"
        t_line "his knowledge of"
        t_para "bug #MON is for"
        t_line "real."
        t_para "It's going to be"
        t_line "tough without my"
        t_cont "advice."
        t_para "Let's see… Bug"
        t_line "#MON don't like"
        t_cont "fire."
        t_para "Flying-type moves"
        t_line "are super-effec-"
        t_cont "tive too."
        t_done )
};
const txt_cmd_s AzaleaGymGuideWinText[] = {
    text_start("Well done! That"
        t_line "was a great clash"
        t_para "of talented young"
        t_line "trainers."
        t_para "With people like"
        t_line "you, the future of"
        t_cont "#MON is bright!"
        t_done )
    //db(0, 0) // filler
};
