#include "../constants.h"
#include "../util/scripting.h"
#include "ViridianGym.h"
//// EVENTS
enum {
    VIRIDIANGYM_BLUE = 2,
    VIRIDIANGYM_GYM_GUIDE,
};

const Script_fn_t ViridianGym_SceneScripts[] = {
    0,
};

const struct MapCallback ViridianGym_MapCallbacks[] = {
    0,
};

const struct MapScripts ViridianGym_MapScripts = {
    .scene_script_count = 0, // lengthof(ViridianGym_SceneScripts),
    .scene_scripts = ViridianGym_SceneScripts,

    .callback_count = 0, // lengthof(ViridianGym_MapCallbacks),
    .callbacks = ViridianGym_MapCallbacks,
};

static const struct CoordEvent ViridianGym_CoordEvents[] = {
    0,
};

static const struct BGEvent ViridianGym_BGEvents[] = {
    bg_event(3, 13, BGEVENT_READ, &ViridianGymStatue),
    bg_event(6, 13, BGEVENT_READ, &ViridianGymStatue),
};

static const struct WarpEventData ViridianGym_WarpEvents[] = {
    warp_event(4, 17, VIRIDIAN_CITY, 1),
    warp_event(5, 17, VIRIDIAN_CITY, 1),
};

static const struct ObjEvent ViridianGym_ObjectEvents[] = {
    object_event(5, 3, SPRITE_BLUE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &ViridianGymBlueScript, EVENT_VIRIDIAN_GYM_BLUE),
    object_event(7, 13, SPRITE_GYM_GUIDE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &ViridianGymGuideScript, EVENT_VIRIDIAN_GYM_BLUE),
};

const struct MapEvents ViridianGym_MapEvents = {
    .warp_event_count = lengthof(ViridianGym_WarpEvents),
    .warp_events = ViridianGym_WarpEvents,

    .coord_event_count = 0, // lengthof(ViridianGym_CoordEvents),
    .coord_events = ViridianGym_CoordEvents,

    .bg_event_count = lengthof(ViridianGym_BGEvents),
    .bg_events = ViridianGym_BGEvents,

    .obj_event_count = lengthof(ViridianGym_ObjectEvents),
    .obj_events = ViridianGym_ObjectEvents,
};

//// CODE

bool ViridianGymBlueScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkflag(ENGINE_EARTHBADGE)
    iftrue(FightDone)
    writetext(LeaderBlueBeforeText)
    waitbutton
    closetext
    winlosstext(LeaderBlueWinText, 0)
    loadtrainer(BLUE, BLUE1)
    startbattle
    reloadmapafterbattle
    setevent(EVENT_BEAT_BLUE)
    opentext
    writetext(Text_ReceivedEarthBadge)
    playsound(SFX_GET_BADGE)
    waitsfx
    setflag(ENGINE_EARTHBADGE)
    writetext(LeaderBlueAfterText)
    waitbutton
    closetext
    s_end
FightDone:
    writetext(LeaderBlueEpilogueText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool ViridianGymGuideScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_BEAT_BLUE)
    iftrue(ViridianGymGuideWinScript)
    writetext(ViridianGymGuideText)
    waitbutton
    closetext
    s_end
ViridianGymGuideWinScript:
    writetext(ViridianGymGuideWinText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool ViridianGymStatue(script_s* s) {
    SCRIPT_BEGIN
    checkflag(ENGINE_EARTHBADGE)
    iftrue(Beaten)
    jumpstd(GymStatue1Script)
Beaten:
    gettrainername(STRING_BUFFER_4, BLUE, BLUE1)
    jumpstd(GymStatue2Script)
    SCRIPT_END
}
const txt_cmd_s LeaderBlueBeforeText[] = {
    text_start("BLUE: Yo! Finally"
        t_line "got here, huh?"
        t_para "I wasn't in the"
        t_line "mood at CINNABAR,"
        t_para "but now I'm ready"
        t_line "to battle you."
        t_para "…"
        t_para "You're telling me"
        t_line "you conquered all"
        t_cont "the GYMS in JOHTO?"
        t_para "Heh! JOHTO's GYMS"
        t_line "must be pretty"
        t_cont "pathetic then."
        t_para "Hey, don't worry"
        t_line "about it."
        t_para "I'll know if you"
        t_line "are good or not by"
        t_para "battling you right"
        t_line "now."
        t_para "Ready, JOHTO"
        t_line "CHAMP?"
        t_done )
};
const txt_cmd_s LeaderBlueWinText[] = {
    text_start("BLUE: What?"
        t_para "How the heck did I"
        t_line "lose to you?"
        t_para "…"
        t_para "Tch, all right…"
        t_line "Here, take this--"
        t_cont "it's EARTHBADGE."
        t_done )
};
const txt_cmd_s Text_ReceivedEarthBadge[] = {
    text_start("<PLAYER> received"
        t_line "EARTHBADGE."
        t_done )
};
const txt_cmd_s LeaderBlueAfterText[] = {
    text_start("BLUE: …"
        t_para "All right, I was"
        t_line "wrong. You're the"
        t_para "real deal. You are"
        t_line "a good trainer."
        t_para "But I'm going to"
        t_line "beat you someday."
        t_para "Don't you forget"
        t_line "it!"
        t_done )
};
const txt_cmd_s LeaderBlueEpilogueText[] = {
    text_start("BLUE: Listen, you."
        t_para "You'd better not"
        t_line "lose until I beat"
        t_cont "you. Got it?"
        t_done )
};
const txt_cmd_s ViridianGymGuideText[] = {
    text_start("Yo, CHAMP in"
        t_line "making!"
        t_para "How's it going?"
        t_line "Looks like you're"
        t_cont "on a roll."
        t_para "The GYM LEADER is"
        t_line "a guy who battled"
        t_para "the CHAMPION three"
        t_line "years ago."
        t_para "He's no pushover."
        t_para "Give it everything"
        t_line "you've got!"
        t_done )
};
const txt_cmd_s ViridianGymGuideWinText[] = {
    text_start("Man, you are truly"
        t_line "tough…"
        t_para "That was a heck of"
        t_line "an inspirational"
        t_para "battle. It brought"
        t_line "tears to my eyes."
        t_done )
    //db(0, 0) // filler
};
