#include "../constants.h"
#include "../util/scripting.h"
#include "CianwoodGym.h"
//// EVENTS
enum {
    CIANWOODGYM_CHUCK = 2,
    CIANWOODGYM_BLACK_BELT1,
    CIANWOODGYM_BLACK_BELT2,
    CIANWOODGYM_BLACK_BELT3,
    CIANWOODGYM_BLACK_BELT4,
    CIANWOODGYM_BOULDER1,
    CIANWOODGYM_BOULDER2,
    CIANWOODGYM_BOULDER3,
    CIANWOODGYM_BOULDER4,
};

const Script_fn_t CianwoodGym_SceneScripts[] = {
    0,
};

const struct MapCallback CianwoodGym_MapCallbacks[] = {
    0,
};

const struct MapScripts CianwoodGym_MapScripts = {
    .scene_script_count = 0, // lengthof(CianwoodGym_SceneScripts),
    .scene_scripts = CianwoodGym_SceneScripts,

    .callback_count = 0, // lengthof(CianwoodGym_MapCallbacks),
    .callbacks = CianwoodGym_MapCallbacks,
};

static const struct CoordEvent CianwoodGym_CoordEvents[] = {
    0,
};

static const struct BGEvent CianwoodGym_BGEvents[] = {
    bg_event(3, 15, BGEVENT_READ, &CianwoodGymStatue),
    bg_event(6, 15, BGEVENT_READ, &CianwoodGymStatue),
};

static const struct WarpEventData CianwoodGym_WarpEvents[] = {
    warp_event(4, 17, CIANWOOD_CITY, 2),
    warp_event(5, 17, CIANWOOD_CITY, 2),
};

static const struct ObjEvent CianwoodGym_ObjectEvents[] = {
    object_event(4, 1, SPRITE_CHUCK, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, &CianwoodGymChuckScript, -1),
    object_event(2, 12, SPRITE_BLACK_BELT, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_TRAINER, 3, &TrainerBlackbeltYoshi, -1),
    object_event(7, 12, SPRITE_BLACK_BELT, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_TRAINER, 3, &TrainerBlackbeltLao, -1),
    object_event(3, 9, SPRITE_BLACK_BELT, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_TRAINER, 2, &TrainerBlackbeltNob, -1),
    object_event(5, 5, SPRITE_BLACK_BELT, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_TRAINER, 1, &TrainerBlackbeltLung, -1),
    object_event(5, 1, SPRITE_BOULDER, SPRITEMOVEDATA_STRENGTH_BOULDER, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &CianwoodGymBoulder, -1),
    object_event(3, 7, SPRITE_BOULDER, SPRITEMOVEDATA_STRENGTH_BOULDER, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &CianwoodGymBoulder, -1),
    object_event(4, 7, SPRITE_BOULDER, SPRITEMOVEDATA_STRENGTH_BOULDER, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &CianwoodGymBoulder, -1),
    object_event(5, 7, SPRITE_BOULDER, SPRITEMOVEDATA_STRENGTH_BOULDER, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &CianwoodGymBoulder, -1),
};

const struct MapEvents CianwoodGym_MapEvents = {
    .warp_event_count = lengthof(CianwoodGym_WarpEvents),
    .warp_events = CianwoodGym_WarpEvents,

    .coord_event_count = 0, // lengthof(CianwoodGym_CoordEvents),
    .coord_events = CianwoodGym_CoordEvents,

    .bg_event_count = lengthof(CianwoodGym_BGEvents),
    .bg_events = CianwoodGym_BGEvents,

    .obj_event_count = lengthof(CianwoodGym_ObjectEvents),
    .obj_events = CianwoodGym_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "CianwoodGym.h"

bool CianwoodGymChuckScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_BEAT_CHUCK)
    iftrue(FightDone)
    writetext(ChuckIntroText1)
    waitbutton
    closetext
    turnobject(CIANWOODGYM_CHUCK, RIGHT)
    opentext
    writetext(ChuckIntroText2)
    waitbutton
    closetext
    applymovement(CIANWOODGYM_BOULDER1, CianwoodGymMovement_ChuckChucksBoulder)
    playsound(SFX_STRENGTH)
    earthquake(80)
    disappear(CIANWOODGYM_BOULDER1)
    pause(30)
    faceplayer
    opentext
    writetext(ChuckIntroText3)
    waitbutton
    closetext
    winlosstext(ChuckLossText, 0)
    loadtrainer(CHUCK, CHUCK1)
    startbattle
    reloadmapafterbattle
    setevent(EVENT_BEAT_CHUCK)
    opentext
    writetext(GetStormBadgeText)
    playsound(SFX_GET_BADGE)
    waitsfx
    setflag(ENGINE_STORMBADGE)
    readvar(VAR_BADGES)
    scall(CianwoodGymActivateRockets)
FightDone:
    checkevent(EVENT_GOT_TM01_DYNAMICPUNCH)
    iftrue(AlreadyGotTM)
    setevent(EVENT_BEAT_BLACKBELT_YOSHI)
    setevent(EVENT_BEAT_BLACKBELT_LAO)
    setevent(EVENT_BEAT_BLACKBELT_NOB)
    setevent(EVENT_BEAT_BLACKBELT_LUNG)
    writetext(ChuckExplainBadgeText)
    promptbutton
    verbosegiveitem(TM_DYNAMICPUNCH, 1)
    iffalse(BagFull)
    setevent(EVENT_GOT_TM01_DYNAMICPUNCH)
    writetext(ChuckExplainTMText)
    waitbutton
    closetext
    s_end
AlreadyGotTM:
    writetext(ChuckAfterText)
    waitbutton
BagFull:
    closetext
    s_end
    SCRIPT_END
}
bool CianwoodGymActivateRockets(script_s* s) {
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
const struct TrainerObj TrainerBlackbeltYoshi = {BLACKBELT_T, YOSHI, EVENT_BEAT_BLACKBELT_YOSHI, BlackbeltYoshiSeenText, BlackbeltYoshiBeatenText, 0, TrainerBlackbeltYoshi_Script};
bool TrainerBlackbeltYoshi_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(BlackbeltYoshiAfterText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerBlackbeltLao = {BLACKBELT_T, LAO, EVENT_BEAT_BLACKBELT_LAO, BlackbeltLaoSeenText, BlackbeltLaoBeatenText, 0, TrainerBlackbeltLao_Script};
bool TrainerBlackbeltLao_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(BlackbeltLaoAfterText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerBlackbeltNob = {BLACKBELT_T, NOB, EVENT_BEAT_BLACKBELT_NOB, BlackbeltNobSeenText, BlackbeltNobBeatenText, 0, TrainerBlackbeltNob_Script};
bool TrainerBlackbeltNob_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(BlackbeltNobAfterText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerBlackbeltLung = {BLACKBELT_T, LUNG, EVENT_BEAT_BLACKBELT_LUNG, BlackbeltLungSeenText, BlackbeltLungBeatenText, 0, TrainerBlackbeltLung_Script};
bool TrainerBlackbeltLung_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(BlackbeltLungAfterText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool CianwoodGymBoulder(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(StrengthBoulderScript)
    SCRIPT_END
}
bool CianwoodGymStatue(script_s* s) {
    SCRIPT_BEGIN
    checkflag(ENGINE_STORMBADGE)
    iftrue(Beaten)
    jumpstd(GymStatue1Script)
Beaten:
    gettrainername(STRING_BUFFER_4, CHUCK, CHUCK1)
    jumpstd(GymStatue2Script)
    SCRIPT_END
}
const uint8_t CianwoodGymMovement_ChuckChucksBoulder[] = {
    movement_set_sliding,
    big_step(LEFT),
    big_step(UP),
    fast_jump_step(RIGHT),
    movement_remove_sliding,
    movement_step_end,
};
const txt_cmd_s ChuckIntroText1[] = {
    text_start("WAHAHAH!"
        t_para "So you've come"
        t_line "this far!"
        t_para "Let me tell you,"
        t_line "I'm tough!"
        t_para "My #MON will"
        t_line "crush stones and"
        t_cont "shatter bones!"
        t_para "Watch this!"
        t_done )
};
const txt_cmd_s ChuckIntroText2[] = {
    text_start("CHUCK: Urggh!"
        t_line "…"
        t_para "Oooarrgh!"
        t_done )
};
const txt_cmd_s ChuckIntroText3[] = {
    text_start("There! Scared now,"
        t_line "are you?"
        t_para "What?"
        t_line "It has nothing to"
        t_para "do with #MON?"
        t_line "That's true!"
        t_para "Come on. We shall"
        t_line "do battle!"
        t_done )
};
const txt_cmd_s ChuckLossText[] = {
    text_start("Wha? Huh?"
        t_line "I lost?"
        t_para "How about that!"
        t_line "You're worthy of"
        t_cont "STORMBADGE!"
        t_done )
};
const txt_cmd_s GetStormBadgeText[] = {
    text_start("<PLAYER> received"
        t_line "STORMBADGE."
        t_done )
};
const txt_cmd_s ChuckExplainBadgeText[] = {
    text_start("STORMBADGE makes"
        t_line "all #MON up to"
        t_para "L70 obey, even"
        t_line "traded ones."
        t_para "It also lets your"
        t_line "#MON use FLY"
        t_para "when you're not in"
        t_line "a battle."
        t_para "Here, take this"
        t_line "too!"
        t_done )
};
const txt_cmd_s ChuckExplainTMText[] = {
    text_start("That is DYNAMIC-"
        t_line "PUNCH."
        t_para "It doesn't always"
        t_line "hit, but when it"
        t_para "does, it causes"
        t_line "confusion!"
        t_done )
};
const txt_cmd_s ChuckAfterText[] = {
    text_start("WAHAHAH! I enjoyed"
        t_line "battling you!"
        t_para "But a loss is a"
        t_line "loss!"
        t_para "From now on, I'm"
        t_line "going to train 24"
        t_cont "hours a day!"
        t_done )
};
const txt_cmd_s BlackbeltYoshiSeenText[] = {
    text_start("My #MON and I"
        t_line "are bound togeth-"
        t_cont "er by friendship."
        t_para "Our bond will"
        t_line "never be broken!"
        t_done )
};
const txt_cmd_s BlackbeltYoshiBeatenText[] = {
    text_start("This isn't real!"
        t_done )
};
const txt_cmd_s BlackbeltYoshiAfterText[] = {
    text_start("You seem to have a"
        t_line "strong bond with"
        t_cont "your #MON too!"
        t_done )
};
const txt_cmd_s BlackbeltLaoSeenText[] = {
    text_start("We martial artists"
        t_line "fear nothing!"
        t_done )
};
const txt_cmd_s BlackbeltLaoBeatenText[] = {
    text_start("That's shocking!"
        t_done )
};
const txt_cmd_s BlackbeltLaoAfterText[] = {
    text_start("Fighting #MON"
        t_line "are afraid of psy-"
        t_cont "chics…"
        t_done )
};
const txt_cmd_s BlackbeltNobSeenText[] = {
    text_start("Words are useless."
        t_line "Let your fists do"
        t_cont "the talking!"
        t_done )
};
const txt_cmd_s BlackbeltNobBeatenText[] = {
    text_start("…"
        t_done )
};
const txt_cmd_s BlackbeltNobAfterText[] = {
    text_start("I lost! "
        t_line "I'm speechless!"
        t_done )
};
const txt_cmd_s BlackbeltLungSeenText[] = {
    text_start("My raging fists"
        t_line "will shatter your"
        t_cont "#MON!"
        t_done )
};
const txt_cmd_s BlackbeltLungBeatenText[] = {
    text_start("I got shattered!"
        t_done )
};
const txt_cmd_s BlackbeltLungAfterText[] = {
    text_start("My #MON lost…"
        t_line "My… my pride is"
        t_cont "shattered…"
        t_done )
    //db(0, 0) // filler
};
