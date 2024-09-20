#include "../constants.h"
#include "../util/scripting.h"
#include "PewterGym.h"
//// EVENTS
enum {
    PEWTERGYM_BROCK = 2,
    PEWTERGYM_YOUNGSTER,
    PEWTERGYM_GYM_GUIDE,
};

const Script_fn_t PewterGym_SceneScripts[] = {
    0,
};

const struct MapCallback PewterGym_MapCallbacks[] = {
    0,
};

const struct MapScripts PewterGym_MapScripts = {
    .scene_script_count = 0, // lengthof(PewterGym_SceneScripts),
    .scene_scripts = PewterGym_SceneScripts,

    .callback_count = 0, // lengthof(PewterGym_MapCallbacks),
    .callbacks = PewterGym_MapCallbacks,
};

static const struct CoordEvent PewterGym_CoordEvents[] = {
    0,
};

static const struct BGEvent PewterGym_BGEvents[] = {
    bg_event(2, 11, BGEVENT_READ, &PewterGymStatue),
    bg_event(7, 11, BGEVENT_READ, &PewterGymStatue),
};

static const struct WarpEventData PewterGym_WarpEvents[] = {
    warp_event(4, 13, PEWTER_CITY, 2),
    warp_event(5, 13, PEWTER_CITY, 2),
};

static const struct ObjEvent PewterGym_ObjectEvents[] = {
    object_event(5, 1, SPRITE_BROCK, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, &PewterGymBrockScript, -1),
    object_event(2, 5, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 3, &TrainerCamperJerry, -1),
    object_event(6, 11, SPRITE_GYM_GUIDE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 1, &PewterGymGuideScript, -1),
};

const struct MapEvents PewterGym_MapEvents = {
    .warp_event_count = lengthof(PewterGym_WarpEvents),
    .warp_events = PewterGym_WarpEvents,

    .coord_event_count = 0, // lengthof(PewterGym_CoordEvents),
    .coord_events = PewterGym_CoordEvents,

    .bg_event_count = lengthof(PewterGym_BGEvents),
    .bg_events = PewterGym_BGEvents,

    .obj_event_count = lengthof(PewterGym_ObjectEvents),
    .obj_events = PewterGym_ObjectEvents,
};

//// CODE

bool PewterGymBrockScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkflag(ENGINE_BOULDERBADGE)
    iftrue(FightDone)
    writetext(BrockIntroText)
    waitbutton
    closetext
    winlosstext(BrockWinLossText, 0)
    loadtrainer(BROCK, BROCK1)
    startbattle
    reloadmapafterbattle
    setevent(EVENT_BEAT_BROCK)
    setevent(EVENT_BEAT_CAMPER_JERRY)
    opentext
    writetext(ReceivedBoulderBadgeText)
    playsound(SFX_GET_BADGE)
    waitsfx
    setflag(ENGINE_BOULDERBADGE)
    writetext(BrockBoulderBadgeText)
    waitbutton
    closetext
    s_end
FightDone:
    writetext(BrockFightDoneText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerCamperJerry = {CAMPER, JERRY, EVENT_BEAT_CAMPER_JERRY, CamperJerrySeenText, CamperJerryBeatenText, 0, TrainerCamperJerry_Script};
bool TrainerCamperJerry_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(CamperJerryAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool PewterGymGuideScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_BEAT_BROCK)
    iftrue(PewterGymGuideWinScript)
    writetext(PewterGymGuideText)
    waitbutton
    closetext
    s_end
PewterGymGuideWinScript:
    writetext(PewterGymGuideWinText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool PewterGymStatue(script_s* s) {
    SCRIPT_BEGIN
    checkflag(ENGINE_BOULDERBADGE)
    iftrue(Beaten)
    jumpstd(GymStatue1Script)
Beaten:
    gettrainername(STRING_BUFFER_4, BROCK, BROCK1)
    jumpstd(GymStatue2Script)
    SCRIPT_END
}
const txt_cmd_s BrockIntroText[] = {
    text_start("BROCK: Wow, it's"
        t_line "not often that we"
        t_para "get a challenger"
        t_line "from JOHTO."
        t_para "I'm BROCK, the"
        t_line "PEWTER GYM LEADER."
        t_para "I'm an expert on"
        t_line "rock-type #MON."
        t_para "My #MON are im-"
        t_line "pervious to most"
        t_para "physical attacks."
        t_line "You'll have a hard"
        t_para "time inflicting"
        t_line "any damage."
        t_para "Come on!"
        t_done )
};
const txt_cmd_s BrockWinLossText[] = {
    text_start("BROCK: Your #-"
        t_line "MON's powerful at-"
        t_cont "tacks overcame my"
        t_cont "rock-hard defense…"
        t_para "You're stronger"
        t_line "than I expected…"
        t_para "Go ahead--take"
        t_line "this BADGE."
        t_done )
};
const txt_cmd_s ReceivedBoulderBadgeText[] = {
    text_start("<PLAYER> received"
        t_line "BOULDERBADGE."
        t_done )
};
const txt_cmd_s BrockBoulderBadgeText[] = {
    text_start("BROCK: <PLAY_G>,"
        t_line "thanks. I enjoyed"
        t_para "battling you, even"
        t_line "though I am a bit"
        t_cont "upset."
        t_para "That BOULDERBADGE"
        t_line "will make your"
        t_para "#MON even more"
        t_line "powerful."
        t_done )
};
const txt_cmd_s BrockFightDoneText[] = {
    text_start("BROCK: The world"
        t_line "is huge. There are"
        t_para "still many strong"
        t_line "trainers like you."
        t_para "Just wait and see."
        t_line "I'm going to be-"
        t_cont "come a lot strong-"
        t_cont "er too."
        t_done )
};
const txt_cmd_s CamperJerrySeenText[] = {
    text_start("The trainers of"
        t_line "this GYM use rock-"
        t_cont "type #MON."
        t_para "The rock-type has"
        t_line "high DEFENSE."
        t_para "Battles could end"
        t_line "up going a long"
        t_para "time. Are you"
        t_line "ready for this?"
        t_done )
};
const txt_cmd_s CamperJerryBeatenText[] = {
    text_start("I have to win"
        t_line "these battles…"
        t_done )
};
const txt_cmd_s CamperJerryAfterBattleText[] = {
    text_start("Hey, you! Trainer"
        t_line "from JOHTO! BROCK"
        t_para "is tough. He'll"
        t_line "punish you if you"
        t_para "don't take him"
        t_line "seriously."
        t_done )
};
const txt_cmd_s PewterGymGuideText[] = {
    text_start("Yo! CHAMP in"
        t_line "making! You're"
        t_para "really rocking."
        t_line "Are you battling"
        t_para "the GYM LEADERS of"
        t_line "KANTO?"
        t_para "They're strong and"
        t_line "dedicated people,"
        t_para "just like JOHTO's"
        t_line "GYM LEADERS."
        t_done )
};
const txt_cmd_s PewterGymGuideWinText[] = {
    text_start("Yo! CHAMP in"
        t_line "making! That GYM"
        t_para "didn't give you"
        t_line "much trouble."
        t_para "The way you took"
        t_line "charge was really"
        t_para "inspiring. I mean"
        t_line "that seriously."
        t_done )
    //db(0, 0) // filler
};
