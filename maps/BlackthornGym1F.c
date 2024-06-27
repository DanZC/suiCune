#include "../constants.h"
#include "../util/scripting.h"
#include "BlackthornGym1F.h"
//// EVENTS
enum {
    BLACKTHORNGYM1F_CLAIR = 2,
    BLACKTHORNGYM1F_COOLTRAINER_M1,
    BLACKTHORNGYM1F_COOLTRAINER_M2,
    BLACKTHORNGYM1F_COOLTRAINER_F,
    BLACKTHORNGYM1F_GYM_GUIDE,
};

const Script_fn_t BlackthornGym1F_SceneScripts[] = {
    0,
};

const struct MapCallback BlackthornGym1F_MapCallbacks[] = {
    map_callback(MAPCALLBACK_TILES, BlackthornGym1F_MapScripts_Boulders),
};

const struct MapScripts BlackthornGym1F_MapScripts = {
    .scene_script_count = 0, // lengthof(BlackthornGym1F_SceneScripts),
    .scene_scripts = BlackthornGym1F_SceneScripts,

    .callback_count = lengthof(BlackthornGym1F_MapCallbacks),
    .callbacks = BlackthornGym1F_MapCallbacks,
};

static const struct CoordEvent BlackthornGym1F_CoordEvents[] = {
    0,
};

static const struct BGEvent BlackthornGym1F_BGEvents[] = {
    bg_event(3, 15, BGEVENT_READ, &BlackthornGymStatue),
    bg_event(6, 15, BGEVENT_READ, &BlackthornGymStatue),
};

static const struct WarpEventData BlackthornGym1F_WarpEvents[] = {
    warp_event(4, 17, BLACKTHORN_CITY, 1),
    warp_event(5, 17, BLACKTHORN_CITY, 1),
    warp_event(1, 7, BLACKTHORN_GYM_2F, 1),
    warp_event(7, 9, BLACKTHORN_GYM_2F, 2),
    warp_event(2, 6, BLACKTHORN_GYM_2F, 3),
    warp_event(7, 7, BLACKTHORN_GYM_2F, 4),
    warp_event(7, 6, BLACKTHORN_GYM_2F, 5),
};

static const struct ObjEvent BlackthornGym1F_ObjectEvents[] = {
    object_event(5, 3, SPRITE_CLAIR, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &BlackthornGymClairScript, -1),
    object_event(6, 6, SPRITE_COOLTRAINER_M, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 3, &TrainerCooltrainermMike, -1),
    object_event(1, 14, SPRITE_COOLTRAINER_M, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 3, &TrainerCooltrainermPaul, -1),
    object_event(9, 2, SPRITE_COOLTRAINER_F, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 1, &TrainerCooltrainerfLola, -1),
    object_event(7, 15, SPRITE_GYM_GUIDE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &BlackthornGymGuideScript, -1),
};

const struct MapEvents BlackthornGym1F_MapEvents = {
    .warp_event_count = lengthof(BlackthornGym1F_WarpEvents),
    .warp_events = BlackthornGym1F_WarpEvents,

    .coord_event_count = 0, // lengthof(BlackthornGym1F_CoordEvents),
    .coord_events = BlackthornGym1F_CoordEvents,

    .bg_event_count = lengthof(BlackthornGym1F_BGEvents),
    .bg_events = BlackthornGym1F_BGEvents,

    .obj_event_count = lengthof(BlackthornGym1F_ObjectEvents),
    .obj_events = BlackthornGym1F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "BlackthornGym1F.h"

bool BlackthornGym1F_MapScripts_Boulders(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_BOULDER_IN_BLACKTHORN_GYM_1)
    iffalse(skip1)
    changeblock(8, 2, 0x3b) // fallen boulder 2
skip1:
    checkevent(EVENT_BOULDER_IN_BLACKTHORN_GYM_2)
    iffalse(skip2)
    changeblock(2, 4, 0x3a) // fallen boulder 1
skip2:
    checkevent(EVENT_BOULDER_IN_BLACKTHORN_GYM_3)
    iffalse(skip3)
    changeblock(8, 6, 0x3b) // fallen boulder 2
skip3:
    s_endcallback
    SCRIPT_END
}
bool BlackthornGymClairScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkflag(ENGINE_RISINGBADGE)
    iftrue(AlreadyGotBadge)
    checkevent(EVENT_BEAT_CLAIR)
    iftrue(FightDone)
    writetext(ClairIntroText)
    waitbutton
    closetext
    winlosstext(ClairWinText, 0)
    loadtrainer(CLAIR, CLAIR1)
    startbattle
    reloadmapafterbattle
    setevent(EVENT_BEAT_CLAIR)
    opentext
    writetext(ClairText_GoToDragonsDen)
    waitbutton
    closetext
    setevent(EVENT_BEAT_COOLTRAINERM_PAUL)
    setevent(EVENT_BEAT_COOLTRAINERM_CODY)
    setevent(EVENT_BEAT_COOLTRAINERM_MIKE)
    setevent(EVENT_BEAT_COOLTRAINERF_FRAN)
    setevent(EVENT_BEAT_COOLTRAINERF_LOLA)
    clearevent(EVENT_MAHOGANY_MART_OWNERS)
    setevent(EVENT_BLACKTHORN_CITY_GRAMPS_BLOCKS_DRAGONS_DEN)
    clearevent(EVENT_BLACKTHORN_CITY_GRAMPS_NOT_BLOCKING_DRAGONS_DEN)
    s_end
FightDone:
    writetext(ClairText_TooMuchToExpect)
    waitbutton
    closetext
    s_end
AlreadyGotBadge:
    checkevent(EVENT_GOT_TM24_DRAGONBREATH)
    iftrue(GotTM24)
    writetext(BlackthornGymClairText_YouKeptMeWaiting)
    promptbutton
    giveitem(TM_DRAGONBREATH, 1)
    iffalse(BagFull)
    getitemname(STRING_BUFFER_3, TM_DRAGONBREATH)
    writetext(BlackthornGymText_ReceivedTM24)
    playsound(SFX_ITEM)
    waitsfx
    itemnotify
    setevent(EVENT_GOT_TM24_DRAGONBREATH)
    writetext(BlackthornGymClairText_DescribeTM24)
    promptbutton
    goto GotTM24;
BagFull:
    writetext(BlackthornGymClairText_BagFull)
    waitbutton
    closetext
    s_end
GotTM24:
    writetext(BlackthornGymClairText_League)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerCooltrainermPaul = {COOLTRAINERM, PAUL, EVENT_BEAT_COOLTRAINERM_PAUL, CooltrainermPaulSeenText, CooltrainermPaulBeatenText, 0, TrainerCooltrainermPaul_Script};
bool TrainerCooltrainermPaul_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(CooltrainermPaulAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerCooltrainermMike = {COOLTRAINERM, MIKE, EVENT_BEAT_COOLTRAINERM_MIKE, CooltrainermMikeSeenText, CooltrainermMikeBeatenText, 0, TrainerCooltrainermMike_Script};
bool TrainerCooltrainermMike_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(CooltrainermMikeAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerCooltrainerfLola = {COOLTRAINERF, LOLA, EVENT_BEAT_COOLTRAINERF_LOLA, CooltrainerfLolaSeenText, CooltrainerfLolaBeatenText, 0, TrainerCooltrainerfLola_Script};
bool TrainerCooltrainerfLola_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(CooltrainerfLolaAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool BlackthornGymGuideScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_BEAT_CLAIR)
    iftrue(BlackthornGymGuideWinScript)
    writetext(BlackthornGymGuideText)
    waitbutton
    closetext
    s_end
BlackthornGymGuideWinScript:
    writetext(BlackthornGymGuideWinText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool BlackthornGymStatue(script_s* s) {
    SCRIPT_BEGIN
    checkflag(ENGINE_RISINGBADGE)
    iftrue(Beaten)
    jumpstd(GymStatue1Script)
Beaten:
    gettrainername(STRING_BUFFER_4, CLAIR, CLAIR1)
    jumpstd(GymStatue2Script)
    SCRIPT_END
}
const txt_cmd_s ClairIntroText[] = {
    text_start("I am CLAIR."
        t_para "The world's best"
        t_line "dragon master."
        t_para "I can hold my own"
        t_line "against even the"
        t_para "#MON LEAGUE's"
        t_line "ELITE FOUR."
        t_para "Do you still want"
        t_line "to take me on?"
        t_para "…Fine."
        t_line "Let's do it!"
        t_para "As a GYM LEADER,"
        t_line "I will use my full"
        t_para "power against any"
        t_line "opponent!"
        t_done )
};
const txt_cmd_s ClairWinText[] = {
    text_start("I lost?"
        t_para "I don't believe"
        t_line "it. There must be"
        t_cont "some mistake…"
        t_done )
};
const txt_cmd_s ClairText_GoToDragonsDen[] = {
    text_start("I won't admit"
        t_line "this."
        t_para "I may have lost,"
        t_line "but you're still"
        t_para "not ready for the"
        t_line "#MON LEAGUE."
        t_para "I know. You should"
        t_line "take the dragon"
        t_cont "user challenge."
        t_para "Behind this GYM is"
        t_line "a place called"
        t_cont "DRAGON'S DEN."
        t_para "There is a small"
        t_line "shrine at its"
        t_para "center."
        t_line "Go there."
        t_para "If you can prove"
        t_line "that you've lost"
        t_para "your lazy ideals,"
        t_line "I will recognize"
        t_para "you as a trainer"
        t_line "worthy of a GYM"
        t_cont "BADGE!"
        t_done )
};
const txt_cmd_s ClairText_TooMuchToExpect[] = {
    text_start("What's the matter?"
        t_para "Is it too much to"
        t_line "expect of you?"
        t_done )
};
const txt_cmd_s BlackthornGymClairText_YouKeptMeWaiting[] = {
    text_start("You've kept me"
        t_line "waiting!"
        t_para "Here! Take this!"
        t_done )
};
const txt_cmd_s BlackthornGymText_ReceivedTM24[] = {
    text_start("<PLAYER> received"
        t_line "TM24."
        t_done )
};
const txt_cmd_s BlackthornGymClairText_DescribeTM24[] = {
    text_start("That contains"
        t_line "DRAGONBREATH."
        t_para "No, it doesn't"
        t_line "have anything to"
        t_cont "do with my breath."
        t_para "If you don't want"
        t_line "it, you don't have"
        t_cont "to take it."
        t_done )
};
const txt_cmd_s BlackthornGymClairText_BagFull[] = {
    text_start("What is this? You"
        t_line "don't have room?"
        t_done )
};
const txt_cmd_s BlackthornGymClairText_League[] = {
    text_start("What's the matter?"
        t_para "Aren't you headed"
        t_line "to the #MON"
        t_cont "LEAGUE?"
        t_para "Don't you know"
        t_line "where it is?"
        t_para "From here, go to"
        t_line "NEW BARK TOWN."
        t_para "Then SURF east."
        t_line "The route there is"
        t_cont "very tough."
        t_para "Don't you dare"
        t_line "lose at the #-"
        t_cont "MON LEAGUE!"
        t_para "If you do, I'll"
        t_line "feel even worse"
        t_para "about having lost"
        t_line "to you!"
        t_para "Give it every-"
        t_line "thing you've got."
        t_done )
};
const txt_cmd_s CooltrainermPaulSeenText[] = {
    text_start("Your first battle"
        t_line "against dragons?"
        t_para "I'll show you how"
        t_line "tough they are!"
        t_done )
};
const txt_cmd_s CooltrainermPaulBeatenText[] = {
    text_start("My dragon #MON"
        t_line "lost?"
        t_done )
};
const txt_cmd_s CooltrainermPaulAfterBattleText[] = {
    text_start("LANCE told you"
        t_line "that he'd like to"
        t_para "see you again?"
        t_line "Not a chance!"
        t_done )
};
const txt_cmd_s CooltrainermMikeSeenText[] = {
    text_start("My chance of"
        t_line "losing? Not even"
        t_cont "one percent!"
        t_done )
};
const txt_cmd_s CooltrainermMikeBeatenText[] = {
    text_start("That's odd."
        t_done )
};
const txt_cmd_s CooltrainermMikeAfterBattleText[] = {
    text_start("I know my short-"
        t_line "comings now."
        t_para "Thanks for showing"
        t_line "me!"
        t_done )
};
const txt_cmd_s CooltrainerfLolaSeenText[] = {
    text_start("Dragons are sacred"
        t_line "#MON."
        t_para "They are full of"
        t_line "life energy."
        t_para "If you're not"
        t_line "serious, you won't"
        t_para "be able to beat"
        t_line "them."
        t_done )
};
const txt_cmd_s CooltrainerfLolaBeatenText[] = {
    text_start("Way to go!"
        t_done )
};
const txt_cmd_s CooltrainerfLolaAfterBattleText[] = {
    text_start("Dragons are weak"
        t_line "against dragon-"
        t_cont "type moves."
        t_done )
};
const txt_cmd_s BlackthornGymGuideText[] = {
    text_start("Yo! CHAMP in"
        t_line "making!"
        t_para "It's been a long"
        t_line "journey, but we"
        t_para "are almost done!"
        t_line "Count on me!"
        t_para "CLAIR uses the"
        t_line "mythical and sac-"
        t_cont "red dragon-type"
        t_cont "#MON."
        t_para "You can't damage"
        t_line "them very easily."
        t_para "But you know,"
        t_line "they're supposed"
        t_para "to be weak against"
        t_line "ice-type moves."
        t_done )
};
const txt_cmd_s BlackthornGymGuideWinText[] = {
    text_start("You were great to"
        t_line "beat CLAIR!"
        t_para "All that's left is"
        t_line "the #MON LEAGUE"
        t_cont "challenge."
        t_para "You're on the way"
        t_line "to becoming the"
        t_cont "#MON CHAMPION!"
        t_done )
    //db(0, 0) // filler
};
