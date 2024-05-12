#include "../constants.h"
#include "../util/scripting.h"
#include "VioletGym.h"
//// EVENTS
enum {
    VIOLETGYM_FALKNER = 2,
    VIOLETGYM_YOUNGSTER1,
    VIOLETGYM_YOUNGSTER2,
    VIOLETGYM_GYM_GUIDE,
};

const Script_fn_t VioletGym_SceneScripts[] = {
    0,
};

const struct MapCallback VioletGym_MapCallbacks[] = {
    0,
};

const struct MapScripts VioletGym_MapScripts = {
    .scene_script_count = 0, // lengthof(VioletGym_SceneScripts),
    .scene_scripts = VioletGym_SceneScripts,

    .callback_count = 0, // lengthof(VioletGym_MapCallbacks),
    .callbacks = VioletGym_MapCallbacks,
};

static const struct CoordEvent VioletGym_CoordEvents[] = {
    0,
};

static const struct BGEvent VioletGym_BGEvents[] = {
    bg_event(3, 13, BGEVENT_READ, &VioletGymStatue),
    bg_event(6, 13, BGEVENT_READ, &VioletGymStatue),
};

static const struct WarpEventData VioletGym_WarpEvents[] = {
    warp_event(4, 15, VIOLET_CITY, 2),
    warp_event(5, 15, VIOLET_CITY, 2),
};

static const struct ObjEvent VioletGym_ObjectEvents[] = {
    object_event(5, 1, SPRITE_FALKNER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &VioletGymFalknerScript, -1),
    object_event(7, 6, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_LEFT, 2, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerBirdKeeperRod, -1),
    object_event(2, 10, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_RIGHT, 2, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerBirdKeeperAbe, -1),
    object_event(7, 13, SPRITE_GYM_GUIDE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &VioletGymGuideScript, -1),
};

const struct MapEvents VioletGym_MapEvents = {
    .warp_event_count = lengthof(VioletGym_WarpEvents),
    .warp_events = VioletGym_WarpEvents,

    .coord_event_count = 0, // lengthof(VioletGym_CoordEvents),
    .coord_events = VioletGym_CoordEvents,

    .bg_event_count = lengthof(VioletGym_BGEvents),
    .bg_events = VioletGym_BGEvents,

    .obj_event_count = lengthof(VioletGym_ObjectEvents),
    .obj_events = VioletGym_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "VioletGym.h"

bool VioletGymFalknerScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_BEAT_FALKNER)
    iftrue(FightDone)
    writetext(FalknerIntroText)
    waitbutton
    closetext
    winlosstext(FalknerWinLossText, 0)
    loadtrainer(FALKNER, FALKNER1)
    startbattle
    reloadmapafterbattle
    setevent(EVENT_BEAT_FALKNER)
    opentext
    writetext(ReceivedZephyrBadgeText)
    playsound(SFX_GET_BADGE)
    waitsfx
    setflag(ENGINE_ZEPHYRBADGE)
    readvar(VAR_BADGES)
    scall(VioletGymActivateRockets)
FightDone:
    checkevent(EVENT_GOT_TM31_MUD_SLAP)
    iftrue(SpeechAfterTM)
    setevent(EVENT_BEAT_BIRD_KEEPER_ROD)
    setevent(EVENT_BEAT_BIRD_KEEPER_ABE)
    setmapscene(ELMS_LAB, SCENE_ELMSLAB_NOTHING)
    specialphonecall(SPECIALCALL_ASSISTANT)
    writetext(FalknerZephyrBadgeText)
    promptbutton
    verbosegiveitem(TM_MUD_SLAP, 1)
    iffalse(NoRoomForMudSlap)
    setevent(EVENT_GOT_TM31_MUD_SLAP)
    writetext(FalknerTMMudSlapText)
    waitbutton
    closetext
    s_end
SpeechAfterTM:
    writetext(FalknerFightDoneText)
    waitbutton
NoRoomForMudSlap:
    closetext
    s_end
    SCRIPT_END
}
bool VioletGymActivateRockets(script_s* s) {
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
const struct TrainerObj TrainerBirdKeeperRod = {BIRD_KEEPER, ROD, EVENT_BEAT_BIRD_KEEPER_ROD, BirdKeeperRodSeenText, BirdKeeperRodBeatenText, 0, TrainerBirdKeeperRod_Script};
bool TrainerBirdKeeperRod_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(BirdKeeperRodAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerBirdKeeperAbe = {BIRD_KEEPER, ABE, EVENT_BEAT_BIRD_KEEPER_ABE, BirdKeeperAbeSeenText, BirdKeeperAbeBeatenText, 0, TrainerBirdKeeperAbe_Script};
bool TrainerBirdKeeperAbe_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(BirdKeeperAbeAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool VioletGymGuideScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_BEAT_FALKNER)
    iftrue(VioletGymGuideWinScript)
    writetext(VioletGymGuideText)
    waitbutton
    closetext
    s_end
VioletGymGuideWinScript:
    writetext(VioletGymGuideWinText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool VioletGymStatue(script_s* s) {
    SCRIPT_BEGIN
    checkflag(ENGINE_ZEPHYRBADGE)
    iftrue(Beaten)
    jumpstd(GymStatue1Script)
Beaten:
    gettrainername(STRING_BUFFER_4, FALKNER, FALKNER1)
    jumpstd(GymStatue2Script)
    SCRIPT_END
}
const txt_cmd_s FalknerIntroText[] = {
    text_start("I'm FALKNER, the"
        t_line "VIOLET #MON GYM"
        t_cont "leader!"
        t_para "People say you can"
        t_line "clip flying-type"
        t_para "#MON's wings"
        t_line "with a jolt of"
        t_cont "electricity…"
        t_para "I won't allow such"
        t_line "insults to bird"
        t_cont "#MON!"
        t_para "I'll show you the"
        t_line "real power of the"
        t_para "magnificent bird"
        t_line "#MON!"
        t_done )
};
const txt_cmd_s FalknerWinLossText[] = {
    text_start("…Darn! My dad's"
        t_line "cherished bird"
        t_cont "#MON…"
        t_para "All right."
        t_line "Take this."
        t_para "It's the official"
        t_line "#MON LEAGUE"
        t_cont "ZEPHYRBADGE."
        t_done )
};
const txt_cmd_s ReceivedZephyrBadgeText[] = {
    text_start("<PLAYER> received"
        t_line "ZEPHYRBADGE."
        t_done )
};
const txt_cmd_s FalknerZephyrBadgeText[] = {
    text_start("ZEPHYRBADGE"
        t_line "raises the attack"
        t_cont "power of #MON."
        t_para "It also enables"
        t_line "#MON to use"
        t_para "FLASH, if they"
        t_line "have it, anytime."
        t_para "Here--take this"
        t_line "too."
        t_done )
};
const txt_cmd_s FalknerTMMudSlapText[] = {
    text_start("By using a TM, a"
        t_line "#MON will"
        t_para "instantly learn a"
        t_line "new move."
        t_para "Think before you"
        t_line "act--a TM can be"
        t_cont "used only once."
        t_para "TM31 contains"
        t_line "MUD-SLAP."
        t_para "It reduces the"
        t_line "enemy's accuracy"
        t_para "while it causes"
        t_line "damage."
        t_para "In other words, it"
        t_line "is both defensive"
        t_cont "and offensive."
        t_done )
};
const txt_cmd_s FalknerFightDoneText[] = {
    text_start("There are #MON"
        t_line "GYMS in cities and"
        t_cont "towns ahead."
        t_para "You should test"
        t_line "your skills at"
        t_cont "these GYMS."
        t_para "I'm going to train"
        t_line "harder to become"
        t_para "the greatest bird"
        t_line "master!"
        t_done )
};
const txt_cmd_s BirdKeeperRodSeenText[] = {
    text_start("The keyword is"
        t_line "guts!"
        t_para "Those here are"
        t_line "training night and"
        t_para "day to become bird"
        t_line "#MON masters."
        t_para "Come on!"
        t_done )
};
const txt_cmd_s BirdKeeperRodBeatenText[] = {
    text_start("Gaaah!"
        t_done )
};
const txt_cmd_s BirdKeeperRodAfterBattleText[] = {
    text_start("FALKNER's skills"
        t_line "are for real!"
        t_para "Don't get cocky"
        t_line "just because you"
        t_cont "beat me!"
        t_done )
};
const txt_cmd_s BirdKeeperAbeSeenText[] = {
    text_start("Let me see if you"
        t_line "are good enough to"
        t_cont "face FALKNER!"
        t_done )
};
const txt_cmd_s BirdKeeperAbeBeatenText[] = {
    text_start("This can't be"
        t_line "true!"
        t_done )
};
const txt_cmd_s BirdKeeperAbeAfterBattleText[] = {
    text_start("This is pathetic,"
        t_line "losing to some"
        t_cont "rookie trainer…"
        t_done )
};
const txt_cmd_s VioletGymGuideText[] = {
    text_start("Hey! I'm no train-"
        t_line "er but I can give"
        t_cont "some advice!"
        t_para "Believe me!"
        t_line "If you believe, a"
        t_para "championship dream"
        t_line "can come true."
        t_para "You believe?"
        t_line "Then listen."
        t_para "The grass-type is"
        t_line "weak against the"
        t_para "flying-type. Keep"
        t_line "this in mind."
        t_done )
};
const txt_cmd_s VioletGymGuideWinText[] = {
    text_start("Nice battle! Keep"
        t_line "it up, and you'll"
        t_para "be the CHAMP in no"
        t_line "time at all!"
        t_done )
    //db(0, 0) // filler
};
