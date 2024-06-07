#include "../constants.h"
#include "../util/scripting.h"
#include "OlivineGym.h"
//// EVENTS
enum {
    OLIVINEGYM_JASMINE = 2,
    OLIVINEGYM_GYM_GUIDE,
};

const Script_fn_t OlivineGym_SceneScripts[] = {
    0,
};

const struct MapCallback OlivineGym_MapCallbacks[] = {
    0,
};

const struct MapScripts OlivineGym_MapScripts = {
    .scene_script_count = 0, // lengthof(OlivineGym_SceneScripts),
    .scene_scripts = OlivineGym_SceneScripts,

    .callback_count = 0, // lengthof(OlivineGym_MapCallbacks),
    .callbacks = OlivineGym_MapCallbacks,
};

static const struct CoordEvent OlivineGym_CoordEvents[] = {
    0,
};

static const struct BGEvent OlivineGym_BGEvents[] = {
    bg_event(3, 13, BGEVENT_READ, &OlivineGymStatue),
    bg_event(6, 13, BGEVENT_READ, &OlivineGymStatue),
};

static const struct WarpEventData OlivineGym_WarpEvents[] = {
    warp_event(4, 15, OLIVINE_CITY, 2),
    warp_event(5, 15, OLIVINE_CITY, 2),
};

static const struct ObjEvent OlivineGym_ObjectEvents[] = {
    object_event(5, 3, SPRITE_JASMINE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &OlivineGymJasmineScript, EVENT_OLIVINE_GYM_JASMINE),
    object_event(7, 13, SPRITE_GYM_GUIDE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &OlivineGymGuideScript, -1),
};

const struct MapEvents OlivineGym_MapEvents = {
    .warp_event_count = lengthof(OlivineGym_WarpEvents),
    .warp_events = OlivineGym_WarpEvents,

    .coord_event_count = 0, // lengthof(OlivineGym_CoordEvents),
    .coord_events = OlivineGym_CoordEvents,

    .bg_event_count = lengthof(OlivineGym_BGEvents),
    .bg_events = OlivineGym_BGEvents,

    .obj_event_count = lengthof(OlivineGym_ObjectEvents),
    .obj_events = OlivineGym_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "OlivineGym.h"

bool OlivineGymJasmineScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_BEAT_JASMINE)
    iftrue(FightDone)
    writetext(Jasmine_SteelTypeIntro)
    waitbutton
    closetext
    winlosstext(Jasmine_BetterTrainer, 0)
    loadtrainer(JASMINE, JASMINE1)
    startbattle
    reloadmapafterbattle
    setevent(EVENT_BEAT_JASMINE)
    opentext
    writetext(Text_ReceivedMineralBadge)
    playsound(SFX_GET_BADGE)
    waitsfx
    setflag(ENGINE_MINERALBADGE)
    readvar(VAR_BADGES)
    scall(OlivineGymActivateRockets)
FightDone:
    checkevent(EVENT_GOT_TM23_IRON_TAIL)
    iftrue(GotIronTail)
    writetext(Jasmine_BadgeSpeech)
    promptbutton
    verbosegiveitem(TM_IRON_TAIL, 1)
    iffalse(NoRoomForIronTail)
    setevent(EVENT_GOT_TM23_IRON_TAIL)
    writetext(Jasmine_IronTailSpeech)
    waitbutton
    closetext
    s_end
GotIronTail:
    writetext(Jasmine_GoodLuck)
    waitbutton
NoRoomForIronTail:
    closetext
    s_end
    SCRIPT_END
}
bool OlivineGymActivateRockets(script_s* s) {
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
bool OlivineGymGuideScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    checkevent(EVENT_BEAT_JASMINE)
    iftrue(OlivineGymGuideWinScript)
    checkevent(EVENT_JASMINE_RETURNED_TO_GYM)
    iffalse(OlivineGymGuidePreScript)
    opentext
    writetext(OlivineGymGuideText)
    waitbutton
    closetext
    s_end
OlivineGymGuideWinScript:
    opentext
    writetext(OlivineGymGuideWinText)
    waitbutton
    closetext
    s_end
OlivineGymGuidePreScript:
    opentext
    writetext(OlivineGymGuidePreText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool OlivineGymStatue(script_s* s) {
    SCRIPT_BEGIN
    checkflag(ENGINE_MINERALBADGE)
    iftrue(Beaten)
    jumpstd(GymStatue1Script)
Beaten:
    gettrainername(STRING_BUFFER_4, JASMINE, JASMINE1)
    jumpstd(GymStatue2Script)
    SCRIPT_END
}
const txt_cmd_s Jasmine_SteelTypeIntro[] = {
    text_start("…Thank you for"
        t_line "your help at the"
        t_cont "LIGHTHOUSE…"
        t_para "But this is dif-"
        t_line "ferent. Please"
        t_para "allow me to intro-"
        t_line "duce myself."
        t_para "I am JASMINE, a"
        t_line "GYM LEADER. I use"
        t_cont "the steel-type."
        t_para "…Do you know about"
        t_line "the steel-type?"
        t_para "It's a type that"
        t_line "was only recently"
        t_cont "discovered."
        t_para "…Um… May I begin?"
        t_done )
};
const txt_cmd_s Jasmine_BetterTrainer[] = {
    text_start("…You are a better"
        t_line "trainer than me,"
        t_para "in both skill and"
        t_line "kindness."
        t_para "In accordance with"
        t_line "LEAGUE rules, I"
        t_para "confer upon you"
        t_line "this BADGE."
        t_done )
};
const txt_cmd_s Text_ReceivedMineralBadge[] = {
    text_start("<PLAYER> received"
        t_line "MINERALBADGE."
        t_done )
};
const txt_cmd_s Jasmine_BadgeSpeech[] = {
    text_start("MINERALBADGE"
        t_line "raises #MON's"
        t_cont "DEFENSE."
        t_para "…Um… Please take"
        t_line "this too…"
        t_done )
};
const txt_cmd_s Text_ReceivedTM09[] = {
    text_start("<PLAYER> received"
        t_line "TM09."
        t_done )
};
const txt_cmd_s Jasmine_IronTailSpeech[] = {
    text_start("…You could use"
        t_line "that TM to teach"
        t_cont "IRON TAIL."
        t_done )
};
const txt_cmd_s Jasmine_GoodLuck[] = {
    text_start("Um… I don't know"
        t_line "how to say this,"
        t_cont "but good luck…"
        t_done )
};
const txt_cmd_s OlivineGymGuideText[] = {
    text_start("JASMINE uses the"
        t_line "newly discovered"
        t_cont "steel-type."
        t_para "I don't know very"
        t_line "much about it."
        t_done )
};
const txt_cmd_s OlivineGymGuideWinText[] = {
    text_start("That was awesome."
        t_para "The steel-type,"
        t_line "huh?"
        t_para "That was a close"
        t_line "encounter of an"
        t_cont "unknown kind!"
        t_done )
};
const txt_cmd_s OlivineGymGuidePreText[] = {
    text_start("JASMINE, the GYM"
        t_line "LEADER, is at the"
        t_cont "LIGHTHOUSE."
        t_para "She's been tending"
        t_line "to a sick #MON."
        t_para "A strong trainer"
        t_line "has to be compas-"
        t_cont "sionate."
        t_done )
    //db(0, 0) // filler
};
