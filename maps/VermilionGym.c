#include "../constants.h"
#include "../util/scripting.h"
#include "VermilionGym.h"
//// EVENTS
enum {
    VERMILIONGYM_SURGE = 2,
    VERMILIONGYM_GENTLEMAN,
    VERMILIONGYM_ROCKER,
    VERMILIONGYM_SUPER_NERD,
    VERMILIONGYM_GYM_GUIDE,
};

const Script_fn_t VermilionGym_SceneScripts[] = {
    0,
};

const struct MapCallback VermilionGym_MapCallbacks[] = {
    0,
};

const struct MapScripts VermilionGym_MapScripts = {
    .scene_script_count = 0, // lengthof(VermilionGym_SceneScripts),
    .scene_scripts = VermilionGym_SceneScripts,

    .callback_count = 0, // lengthof(VermilionGym_MapCallbacks),
    .callbacks = VermilionGym_MapCallbacks,
};

static const struct CoordEvent VermilionGym_CoordEvents[] = {
    0,
};

static const struct BGEvent VermilionGym_BGEvents[] = {
    bg_event(1, 7, BGEVENT_READ, &VermilionGymTrashCan),
    bg_event(3, 7, BGEVENT_READ, &VermilionGymTrashCan),
    bg_event(5, 7, BGEVENT_READ, &VermilionGymTrashCan),
    bg_event(7, 7, BGEVENT_READ, &VermilionGymTrashCan),
    bg_event(9, 7, BGEVENT_READ, &VermilionGymTrashCan),
    bg_event(1, 9, BGEVENT_READ, &VermilionGymTrashCan),
    bg_event(3, 9, BGEVENT_READ, &VermilionGymTrashCan),
    bg_event(5, 9, BGEVENT_READ, &VermilionGymTrashCan),
    bg_event(7, 9, BGEVENT_READ, &VermilionGymTrashCan),
    bg_event(9, 9, BGEVENT_READ, &VermilionGymTrashCan),
    bg_event(1, 11, BGEVENT_READ, &VermilionGymTrashCan),
    bg_event(3, 11, BGEVENT_READ, &VermilionGymTrashCan),
    bg_event(5, 11, BGEVENT_READ, &VermilionGymTrashCan),
    bg_event(7, 11, BGEVENT_READ, &VermilionGymTrashCan),
    bg_event(9, 11, BGEVENT_READ, &VermilionGymTrashCan),
    bg_event(3, 15, BGEVENT_READ, &VermilionGymStatue),
    bg_event(6, 15, BGEVENT_READ, &VermilionGymStatue),
};

static const struct WarpEventData VermilionGym_WarpEvents[] = {
    warp_event(4, 17, VERMILION_CITY, 7),
    warp_event(5, 17, VERMILION_CITY, 7),
};

static const struct ObjEvent VermilionGym_ObjectEvents[] = {
    object_event(5, 2, SPRITE_SURGE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, &VermilionGymSurgeScript, -1),
    object_event(8, 8, SPRITE_GENTLEMAN, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 4, &TrainerGentlemanGregory, -1),
    object_event(4, 7, SPRITE_ROCKER, SPRITEMOVEDATA_STANDING_DOWN, 3, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 3, &TrainerGuitaristVincent, -1),
    object_event(0, 10, SPRITE_SUPER_NERD, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 4, &TrainerJugglerHorton, -1),
    object_event(7, 15, SPRITE_GYM_GUIDE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 1, &VermilionGymGuideScript, -1),
};

const struct MapEvents VermilionGym_MapEvents = {
    .warp_event_count = lengthof(VermilionGym_WarpEvents),
    .warp_events = VermilionGym_WarpEvents,

    .coord_event_count = 0, // lengthof(VermilionGym_CoordEvents),
    .coord_events = VermilionGym_CoordEvents,

    .bg_event_count = lengthof(VermilionGym_BGEvents),
    .bg_events = VermilionGym_BGEvents,

    .obj_event_count = lengthof(VermilionGym_ObjectEvents),
    .obj_events = VermilionGym_ObjectEvents,
};

//// CODE

bool VermilionGymSurgeScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkflag(ENGINE_THUNDERBADGE)
    iftrue(FightDone)
    writetext(LtSurgeIntroText)
    waitbutton
    closetext
    winlosstext(LtSurgeWinLossText, 0)
    loadtrainer(LT_SURGE, LT_SURGE1)
    startbattle
    reloadmapafterbattle
    setevent(EVENT_BEAT_LTSURGE)
    setevent(EVENT_BEAT_GENTLEMAN_GREGORY)
    setevent(EVENT_BEAT_GUITARIST_VINCENT)
    setevent(EVENT_BEAT_JUGGLER_HORTON)
    opentext
    writetext(ReceivedThunderBadgeText)
    playsound(SFX_GET_BADGE)
    waitsfx
    setflag(ENGINE_THUNDERBADGE)
    writetext(LtSurgeThunderBadgeText)
    waitbutton
    closetext
    s_end
FightDone:
    writetext(LtSurgeFightDoneText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerGentlemanGregory = {GENTLEMAN, GREGORY, EVENT_BEAT_GENTLEMAN_GREGORY, GentlemanGregorySeenText, GentlemanGregoryBeatenText, 0, TrainerGentlemanGregory_Script};
bool TrainerGentlemanGregory_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(GentlemanGregoryAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerGuitaristVincent = {GUITARIST, VINCENT, EVENT_BEAT_GUITARIST_VINCENT, GuitaristVincentSeenText, GuitaristVincentBeatenText, 0, TrainerGuitaristVincent_Script};
bool TrainerGuitaristVincent_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(GuitaristVincentAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerJugglerHorton = {JUGGLER, HORTON, EVENT_BEAT_JUGGLER_HORTON, JugglerHortonSeenText, JugglerHortonBeatenText, 0, TrainerJugglerHorton_Script};
bool TrainerJugglerHorton_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(JugglerHortonAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool VermilionGymGuideScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_BEAT_LTSURGE)
    iftrue(VermilionGymGuideWinScript)
    writetext(VermilionGymGuideText)
    waitbutton
    closetext
    s_end
VermilionGymGuideWinScript:
    writetext(VermilionGymGuideWinText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool VermilionGymTrashCan(script_s* s) {
    SCRIPT_BEGIN
    jumptext(VermilionGymTrashCanText)
    SCRIPT_END
}
bool VermilionGymStatue(script_s* s) {
    SCRIPT_BEGIN
    checkflag(ENGINE_THUNDERBADGE)
    iftrue(Beaten)
    jumpstd(GymStatue1Script)
Beaten:
    gettrainername(STRING_BUFFER_4, LT_SURGE, LT_SURGE1)
    jumpstd(GymStatue2Script)
    SCRIPT_END
}
const txt_cmd_s LtSurgeIntroText[] = {
    text_start("SURGE: Hey, you"
        t_line "little tyke!"
        t_para "I have to hand it"
        t_line "to you. It may not"
        t_para "be very smart to"
        t_line "challenge me, but"
        t_cont "it takes guts!"
        t_para "When it comes to"
        t_line "electric #MON,"
        t_cont "I'm number one!"
        t_para "I've never lost on"
        t_line "the battlefield."
        t_para "I'll zap you just"
        t_line "like I did my"
        t_cont "enemies in war!"
        t_done )
};
const txt_cmd_s LtSurgeWinLossText[] = {
    text_start("SURGE: Arrrgh!"
        t_line "You are strong!"
        t_para "OK, kid. You get"
        t_line "THUNDERBADGE!"
        t_done )
};
const txt_cmd_s ReceivedThunderBadgeText[] = {
    text_start("<PLAYER> received"
        t_line "THUNDERBADGE."
        t_done )
};
const txt_cmd_s LtSurgeThunderBadgeText[] = {
    text_start("SURGE: THUNDER-"
        t_line "BADGE increases"
        t_cont "#MON's speed. "
        t_para "Consider it proof"
        t_line "that you defeated"
        t_para "me. You wear it"
        t_line "proudly, hear?"
        t_done )
};
const txt_cmd_s LtSurgeFightDoneText[] = {
    text_start("SURGE: Hey, kid!"
        t_line "Still slugging and"
        t_cont "chugging away?"
        t_para "My #MON and I"
        t_line "are still at it!"
        t_done )
};
const txt_cmd_s GentlemanGregorySeenText[] = {
    text_start("You're here to"
        t_line "defeat LT.SURGE?"
        t_para "Not if I can help"
        t_line "it!"
        t_done )
};
const txt_cmd_s GentlemanGregoryBeatenText[] = {
    text_start("Sorry I failed"
        t_line "you, LT.SURGE,"
        t_cont "sir!"
        t_done )
};
const txt_cmd_s GentlemanGregoryAfterBattleText[] = {
    text_start("When I was still"
        t_line "in the army, LT."
        t_para "SURGE saved my"
        t_line "life."
        t_done )
};
const txt_cmd_s GuitaristVincentSeenText[] = {
    text_start("LT.SURGE recog-"
        t_line "nized my potential"
        t_para "with electric"
        t_line "#MON."
        t_para "Think you can beat"
        t_line "me?"
        t_done )
};
const txt_cmd_s GuitaristVincentBeatenText[] = {
    text_start("Ooh, how shocking!"
        t_done )
};
const txt_cmd_s GuitaristVincentAfterBattleText[] = {
    text_start("If the GYM's traps"
        t_line "were working, you"
        t_para "would have been"
        t_line "toast…"
        t_done )
};
const txt_cmd_s JugglerHortonSeenText[] = {
    text_start("I'm going to take"
        t_line "you down! Prepare"
        t_cont "to be shocked!"
        t_done )
};
const txt_cmd_s JugglerHortonBeatenText[] = {
    text_start("Gwaaah!"
        t_line "I was overpowered…"
        t_done )
};
const txt_cmd_s JugglerHortonAfterBattleText[] = {
    text_start("Don't get too com-"
        t_line "fortable about"
        t_para "beating me…"
        t_line "LT.SURGE is tough."
        t_done )
};
const txt_cmd_s VermilionGymGuideText[] = {
    text_start("Yo! CHAMP in"
        t_line "making!"
        t_para "You lucked out"
        t_line "this time."
        t_para "LT.SURGE is very"
        t_line "cautious. He has"
        t_para "traps set all over"
        t_line "the GYM."
        t_para "But--he-heh--the"
        t_line "traps aren't"
        t_cont "active right now."
        t_para "You'll have no"
        t_line "problem getting to"
        t_cont "LT.SURGE."
        t_done )
};
const txt_cmd_s VermilionGymGuideWinText[] = {
    text_start("Whew! That was an"
        t_line "electrifying bout!"
        t_para "It sure made me"
        t_line "nervous."
        t_done )
};
const txt_cmd_s VermilionGymTrashCanText[] = {
    text_start("Nope! Nothing here"
        t_line "but trash."
        t_done )
    //db(0, 0) // filler
};
