#include "../constants.h"
#include "../util/scripting.h"
#include "FuchsiaGym.h"
//// EVENTS
enum {
    FUCHSIAGYM_JANINE = 2,
    FUCHSIAGYM_FUCHSIA_GYM_1,
    FUCHSIAGYM_FUCHSIA_GYM_2,
    FUCHSIAGYM_FUCHSIA_GYM_3,
    FUCHSIAGYM_FUCHSIA_GYM_4,
    FUCHSIAGYM_GYM_GUIDE,
};

const Script_fn_t FuchsiaGym_SceneScripts[] = {
    0,
};

const struct MapCallback FuchsiaGym_MapCallbacks[] = {
    0,
};

const struct MapScripts FuchsiaGym_MapScripts = {
    .scene_script_count = 0, // lengthof(FuchsiaGym_SceneScripts),
    .scene_scripts = FuchsiaGym_SceneScripts,

    .callback_count = 0, // lengthof(FuchsiaGym_MapCallbacks),
    .callbacks = FuchsiaGym_MapCallbacks,
};

static const struct CoordEvent FuchsiaGym_CoordEvents[] = {
    0,
};

static const struct BGEvent FuchsiaGym_BGEvents[] = {
    bg_event(3, 15, BGEVENT_READ, &FuchsiaGymStatue),
    bg_event(6, 15, BGEVENT_READ, &FuchsiaGymStatue),
};

static const struct WarpEventData FuchsiaGym_WarpEvents[] = {
    warp_event(4, 17, FUCHSIA_CITY, 3),
    warp_event(5, 17, FUCHSIA_CITY, 3),
};

static const struct ObjEvent FuchsiaGym_ObjectEvents[] = {
    object_event(1, 10, SPRITE_JANINE, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &FuchsiaGymJanineScript, -1),
    object_event(5, 7, SPRITE_FUCHSIA_GYM_1, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &LassAliceScript, -1),
    object_event(5, 11, SPRITE_FUCHSIA_GYM_2, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &LassLindaScript, -1),
    object_event(9, 4, SPRITE_FUCHSIA_GYM_3, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &PicnickerCindyScript, -1),
    object_event(4, 2, SPRITE_FUCHSIA_GYM_4, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &CamperBarryScript, -1),
    object_event(7, 15, SPRITE_GYM_GUIDE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &FuchsiaGymGuideScript, -1),
};

const struct MapEvents FuchsiaGym_MapEvents = {
    .warp_event_count = lengthof(FuchsiaGym_WarpEvents),
    .warp_events = FuchsiaGym_WarpEvents,

    .coord_event_count = 0, // lengthof(FuchsiaGym_CoordEvents),
    .coord_events = FuchsiaGym_CoordEvents,

    .bg_event_count = lengthof(FuchsiaGym_BGEvents),
    .bg_events = FuchsiaGym_BGEvents,

    .obj_event_count = lengthof(FuchsiaGym_ObjectEvents),
    .obj_events = FuchsiaGym_ObjectEvents,
};

//// CODE

bool FuchsiaGymJanineScript(script_s* s) {
    SCRIPT_BEGIN
    checkflag(ENGINE_SOULBADGE)
    iftrue(FightDone)
    applymovement(FUCHSIAGYM_JANINE, Movement_NinjaSpin)
    faceplayer
    opentext
    writetext(JanineText_DisappointYou)
    waitbutton
    closetext
    winlosstext(JanineText_ToughOne, 0)
    loadtrainer(JANINE, JANINE1)
    startbattle
    reloadmapafterbattle
    setevent(EVENT_BEAT_JANINE)
    setevent(EVENT_BEAT_LASS_ALICE)
    setevent(EVENT_BEAT_LASS_LINDA)
    setevent(EVENT_BEAT_PICNICKER_CINDY)
    setevent(EVENT_BEAT_CAMPER_BARRY)
    variablesprite(SPRITE_FUCHSIA_GYM_1, SPRITE_LASS)
    variablesprite(SPRITE_FUCHSIA_GYM_2, SPRITE_LASS)
    variablesprite(SPRITE_FUCHSIA_GYM_3, SPRITE_LASS)
    variablesprite(SPRITE_FUCHSIA_GYM_4, SPRITE_YOUNGSTER)
    special(LoadUsedSpritesGFX)
    opentext
    writetext(Text_ReceivedSoulBadge)
    playsound(SFX_GET_BADGE)
    waitsfx
    setflag(ENGINE_SOULBADGE)
    goto AfterBattle;
FightDone:
    faceplayer
    opentext
AfterBattle:
    checkevent(EVENT_GOT_TM06_TOXIC)
    iftrue(AfterTM)
    writetext(JanineText_ToxicSpeech)
    promptbutton
    verbosegiveitem(TM_TOXIC, 1)
    iffalse(AfterTM)
    setevent(EVENT_GOT_TM06_TOXIC)
AfterTM:
    writetext(JanineText_ApplyMyself)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool LassAliceScript(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_BEAT_LASS_ALICE)
    iftrue(AliceUnmasked)
    applymovement(FUCHSIAGYM_FUCHSIA_GYM_1, Movement_NinjaSpin)
    faceplayer
    variablesprite(SPRITE_FUCHSIA_GYM_1, SPRITE_LASS)
    special(LoadUsedSpritesGFX)
AliceUnmasked:
    faceplayer
    opentext
    checkevent(EVENT_BEAT_LASS_ALICE)
    iftrue(AliceAfterScript)
    writetext(LassAliceBeforeText)
    waitbutton
    closetext
    winlosstext(LassAliceBeatenText, 0)
    loadtrainer(LASS, ALICE)
    startbattle
    iftrue(AliceBecomesJanine)
    reloadmapafterbattle
    setevent(EVENT_BEAT_LASS_ALICE)
    s_end
AliceBecomesJanine:
    variablesprite(SPRITE_FUCHSIA_GYM_1, SPRITE_JANINE)
    reloadmapafterbattle
    s_end
AliceAfterScript:
    writetext(LassAliceAfterText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool LassLindaScript(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_BEAT_LASS_LINDA)
    iftrue(LindaUnmasked)
    applymovement(FUCHSIAGYM_FUCHSIA_GYM_2, Movement_NinjaSpin)
    faceplayer
    variablesprite(SPRITE_FUCHSIA_GYM_2, SPRITE_LASS)
    special(LoadUsedSpritesGFX)
LindaUnmasked:
    faceplayer
    opentext
    checkevent(EVENT_BEAT_LASS_LINDA)
    iftrue(LindaAfterScript)
    writetext(LassLindaBeforeText)
    waitbutton
    closetext
    winlosstext(LassLindaBeatenText, 0)
    loadtrainer(LASS, LINDA)
    startbattle
    iftrue(LindaBecomesJanine)
    reloadmapafterbattle
    setevent(EVENT_BEAT_LASS_LINDA)
    s_end
LindaBecomesJanine:
    variablesprite(SPRITE_FUCHSIA_GYM_2, SPRITE_JANINE)
    reloadmapafterbattle
    s_end
LindaAfterScript:
    writetext(LassLindaAfterText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool PicnickerCindyScript(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_BEAT_PICNICKER_CINDY)
    iftrue(CindyUnmasked)
    applymovement(FUCHSIAGYM_FUCHSIA_GYM_3, Movement_NinjaSpin)
    faceplayer
    variablesprite(SPRITE_FUCHSIA_GYM_3, SPRITE_LASS)
    special(LoadUsedSpritesGFX)
CindyUnmasked:
    faceplayer
    opentext
    checkevent(EVENT_BEAT_PICNICKER_CINDY)
    iftrue(CindyAfterScript)
    writetext(PicnickerCindyBeforeText)
    waitbutton
    closetext
    winlosstext(PicnickerCindyBeatenText, 0)
    loadtrainer(PICNICKER, CINDY)
    startbattle
    iftrue(CindyBecomesJanine)
    reloadmapafterbattle
    setevent(EVENT_BEAT_PICNICKER_CINDY)
    s_end
CindyBecomesJanine:
    variablesprite(SPRITE_FUCHSIA_GYM_3, SPRITE_JANINE)
    reloadmapafterbattle
    s_end
CindyAfterScript:
    writetext(PicnickerCindyAfterText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool CamperBarryScript(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_BEAT_CAMPER_BARRY)
    iftrue(BarryUnmasked)
    applymovement(FUCHSIAGYM_FUCHSIA_GYM_4, Movement_NinjaSpin)
    faceplayer
    variablesprite(SPRITE_FUCHSIA_GYM_4, SPRITE_YOUNGSTER)
    special(LoadUsedSpritesGFX)
BarryUnmasked:
    faceplayer
    opentext
    checkevent(EVENT_BEAT_CAMPER_BARRY)
    iftrue(BarryAfterScript)
    writetext(CamperBarryBeforeText)
    waitbutton
    closetext
    winlosstext(CamperBarryBeatenText, 0)
    loadtrainer(CAMPER, BARRY)
    startbattle
    iftrue(BarryBecomesJanine)
    reloadmapafterbattle
    setevent(EVENT_BEAT_CAMPER_BARRY)
    s_end
BarryBecomesJanine:
    variablesprite(SPRITE_FUCHSIA_GYM_4, SPRITE_JANINE)
    reloadmapafterbattle
    s_end
BarryAfterScript:
    writetext(CamperBarryAfterText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool FuchsiaGymGuideScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_BEAT_JANINE)
    iftrue(FuchsiaGymGuideWinScript)
    writetext(FuchsiaGymGuideText)
    waitbutton
    closetext
    s_end
FuchsiaGymGuideWinScript:
    writetext(FuchsiaGymGuideWinText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool FuchsiaGymStatue(script_s* s) {
    SCRIPT_BEGIN
    checkflag(ENGINE_SOULBADGE)
    iftrue(Beaten)
    jumpstd(GymStatue1Script)
Beaten:
    gettrainername(STRING_BUFFER_4, JANINE, JANINE1)
    jumpstd(GymStatue2Script)
    SCRIPT_END
}
const uint8_t Movement_NinjaSpin[] = {
    turn_head(DOWN),
    turn_head(LEFT),
    turn_head(UP),
    turn_head(RIGHT),
    turn_head(DOWN),
    turn_head(LEFT),
    turn_head(UP),
    turn_head(RIGHT),
    turn_head(DOWN),
    turn_head(LEFT),
    turn_head(UP),
    turn_head(RIGHT),
    turn_head(DOWN),
    movement_step_end,
};
const txt_cmd_s JanineText_DisappointYou[] = {
    text_start("Fufufufu…"
        t_para "I'm sorry to dis-"
        t_line "appoint you…"
        t_para "I'm only joking!"
        t_para "I'm the real deal!"
        t_para "JANINE of FUCHSIA"
        t_line "GYM, that's me!"
        t_done )
};
const txt_cmd_s JanineText_ToughOne[] = {
    text_start("JANINE: You're a"
        t_line "tough one. You"
        t_cont "definitely won…"
        t_para "Here's SOULBADGE."
        t_line "Take it."
        t_done )
};
const txt_cmd_s Text_ReceivedSoulBadge[] = {
    text_start("<PLAYER> received"
        t_line "SOULBADGE."
        t_done )
};
const txt_cmd_s JanineText_ToxicSpeech[] = {
    text_start("JANINE: You're so"
        t_line "tough! I have a"
        t_cont "special gift!"
        t_para "It's TOXIC, a pow-"
        t_line "erful poison that"
        t_para "steadily saps the"
        t_line "victim's HP."
        t_done )
};
const txt_cmd_s JanineText_ApplyMyself[] = {
    text_start("JANINE: I'm going"
        t_line "to really apply"
        t_para "myself and improve"
        t_line "my skills."
        t_para "I want to become"
        t_line "better than both"
        t_cont "Father and you!"
        t_done )
};
const txt_cmd_s LassAliceBeforeText[] = {
    text_start("Fufufu!"
        t_para "I'm JANINE, the"
        t_line "GYM LEADER!"
        t_para "No, I'm not!"
        t_line "Gotcha, sucker!"
        t_done )
};
const txt_cmd_s LassAliceBeatenText[] = {
    text_start("I had you fooled…"
        t_done )
};
const txt_cmd_s LassAliceAfterText[] = {
    text_start("How will you dis-"
        t_line "tinguish our real"
        t_cont "LEADER?"
        t_done )
};
const txt_cmd_s LassLindaBeforeText[] = {
    text_start("Fooled you!"
        t_line "Hahaha!"
        t_done )
};
const txt_cmd_s LassLindaBeatenText[] = {
    text_start("Ooh… I lost…"
        t_line "You're not weak…"
        t_done )
};
const txt_cmd_s LassLindaAfterText[] = {
    text_start("Well? Wasn't my"
        t_line "disguise perfect?"
        t_done )
};
const txt_cmd_s PicnickerCindyBeforeText[] = {
    text_start("I'm JANINE!"
        t_para "How did you know I"
        t_line "was real?"
        t_para "Let's battle!"
        t_done )
};
const txt_cmd_s PicnickerCindyBeatenText[] = {
    text_start("Darn it!"
        t_line "I wanted to win!"
        t_done )
};
const txt_cmd_s PicnickerCindyAfterText[] = {
    text_start("You must be"
        t_line "getting tired."
        t_done )
};
const txt_cmd_s CamperBarryBeforeText[] = {
    text_start("Wahahaha!"
        t_para "You betcha!"
        t_line "I'm JANINE!"
        t_done )
};
const txt_cmd_s CamperBarryBeatenText[] = {
    text_start("My disguise was"
        t_line "right on! Dang!"
        t_done )
};
const txt_cmd_s CamperBarryAfterText[] = {
    text_start("Hey, you. Was my"
        t_line "disguise cute or"
        t_cont "what, huh?"
        t_done )
};
const txt_cmd_s FuchsiaGymGuideText[] = {
    text_start("Yo, CHAMP in"
        t_line "making!"
        t_para "Whoops! Take a"
        t_line "good look around"
        t_para "you. The trainers"
        t_line "all look like the"
        t_cont "LEADER, JANINE."
        t_para "Which of them is"
        t_line "the real JANINE?"
        t_done )
};
const txt_cmd_s FuchsiaGymGuideWinText[] = {
    text_start("That was a great"
        t_line "battle, trainer"
        t_cont "from JOHTO!"
        t_done )
    //db(0, 0) // filler
};
