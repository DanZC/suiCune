#include "../constants.h"
#include "../util/scripting.h"
#include "OlivineLighthouse6F.h"
//// EVENTS
enum {
    OLIVINELIGHTHOUSE6F_JASMINE = 2,
    OLIVINELIGHTHOUSE6F_MONSTER,
    OLIVINELIGHTHOUSE6F_POKE_BALL,
};

const Script_fn_t OlivineLighthouse6F_SceneScripts[] = {
    0,
};

const struct MapCallback OlivineLighthouse6F_MapCallbacks[] = {
    0,
};

const struct MapScripts OlivineLighthouse6F_MapScripts = {
    .scene_script_count = 0, // lengthof(OlivineLighthouse6F_SceneScripts),
    .scene_scripts = OlivineLighthouse6F_SceneScripts,

    .callback_count = 0, // lengthof(OlivineLighthouse6F_MapCallbacks),
    .callbacks = OlivineLighthouse6F_MapCallbacks,
};

static const struct CoordEvent OlivineLighthouse6F_CoordEvents[] = {
    0,
};

static const struct BGEvent OlivineLighthouse6F_BGEvents[] = {
    0,
};

static const struct WarpEventData OlivineLighthouse6F_WarpEvents[] = {
    warp_event(9, 15, OLIVINE_LIGHTHOUSE_5F, 1),
    warp_event(16, 5, OLIVINE_LIGHTHOUSE_5F, 6),
    warp_event(17, 5, OLIVINE_LIGHTHOUSE_5F, 7),
};

static const struct ObjEvent OlivineLighthouse6F_ObjectEvents[] = {
    object_event(8, 8, SPRITE_JASMINE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &OlivineLighthouseJasmine, EVENT_OLIVINE_LIGHTHOUSE_JASMINE),
    object_event(9, 8, SPRITE_MONSTER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, &OlivineLighthouseAmphy, -1),
    object_event(3, 4, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &OlivineLighthouse6FSuperPotion, EVENT_OLIVINE_LIGHTHOUSE_6F_SUPER_POTION),
};

const struct MapEvents OlivineLighthouse6F_MapEvents = {
    .warp_event_count = lengthof(OlivineLighthouse6F_WarpEvents),
    .warp_events = OlivineLighthouse6F_WarpEvents,

    .coord_event_count = 0, // lengthof(OlivineLighthouse6F_CoordEvents),
    .coord_events = OlivineLighthouse6F_CoordEvents,

    .bg_event_count = 0, // lengthof(OlivineLighthouse6F_BGEvents),
    .bg_events = OlivineLighthouse6F_BGEvents,

    .obj_event_count = lengthof(OlivineLighthouse6F_ObjectEvents),
    .obj_events = OlivineLighthouse6F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "OlivineLighthouse6F.h"

bool OlivineLighthouseJasmine(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkitem(SECRETPOTION)
    iftrue(BroughtSecretpotion)
    checkevent(EVENT_JASMINE_EXPLAINED_AMPHYS_SICKNESS)
    iftrue(ExplainedSickness)
    writetext(JasmineCianwoodPharmacyText)
    promptbutton
    setevent(EVENT_JASMINE_EXPLAINED_AMPHYS_SICKNESS)
ExplainedSickness:
    writetext(JasmineGetSomeMedicineText)
    waitbutton
    closetext
    s_end
BroughtSecretpotion:
    writetext(JasmineCureAmphyText)
    yesorno
    iffalse(Refused)
    writetext(PlayerHandedSecretpotionText)
    promptbutton
    takeitem(SECRETPOTION, 1)
    writetext(JasmineDontBeOffendedText)
    waitbutton
    closetext
    turnobject(OLIVINELIGHTHOUSE6F_JASMINE, RIGHT)
    pause(15)
    turnobject(OLIVINELIGHTHOUSE6F_MONSTER, LEFT)
    opentext
    playmusic(MUSIC_HEAL)
    writetext(JasmineAmphyHowAreYouFeelingText)
    pause(60)
    promptbutton
    closetext
    special(RestartMapMusic)
    playcry(AMPHAROS)
    special(FadeOutPalettes)
    pause(10)
    special(FadeInPalettes)
    opentext
    writetext(AmphyPaluPaluluText)
    waitbutton
    closetext
    turnobject(OLIVINELIGHTHOUSE6F_MONSTER, RIGHT)
    pause(10)
    turnobject(OLIVINELIGHTHOUSE6F_MONSTER, LEFT)
    pause(10)
    turnobject(OLIVINELIGHTHOUSE6F_MONSTER, RIGHT)
    pause(10)
    turnobject(OLIVINELIGHTHOUSE6F_MONSTER, LEFT)
    pause(10)
    faceplayer
    opentext
    writetext(JasmineThankYouText)
    waitbutton
    closetext
    setevent(EVENT_JASMINE_RETURNED_TO_GYM)
    clearevent(EVENT_OLIVINE_GYM_JASMINE)
    readvar(VAR_FACING)
    ifequal(DOWN, FacingDown)
    ifequal(RIGHT, FacingRight)
    applymovement(OLIVINELIGHTHOUSE6F_JASMINE, OlivineLighthouseJasmineLeavesUpMovement)
    disappear(OLIVINELIGHTHOUSE6F_JASMINE)
    s_end
FacingDown:
    applymovement(OLIVINELIGHTHOUSE6F_JASMINE, OlivineLighthouseJasmineLeavesDownMovement)
    disappear(OLIVINELIGHTHOUSE6F_JASMINE)
    s_end
FacingRight:
    applymovement(OLIVINELIGHTHOUSE6F_JASMINE, OlivineLighthouseJasmineLeavesRightMovement)
    disappear(OLIVINELIGHTHOUSE6F_JASMINE)
    s_end
Refused:
    writetext(JasmineISeeText)
    waitbutton
    closetext
    turnobject(OLIVINELIGHTHOUSE6F_JASMINE, RIGHT)
    pause(15)
    turnobject(OLIVINELIGHTHOUSE6F_MONSTER, LEFT)
    opentext
    writetext(JasmineAmphyHangOnText)
    waitbutton
    closetext
    s_end
Unused:
    s_end
    SCRIPT_END
}
bool OlivineLighthouseAmphy(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_JASMINE_RETURNED_TO_GYM)
    iftrue(HealthyNow)
    writetext(AmphyPalPalooText)
    setval(AMPHAROS)
    special(PlaySlowCry)
    promptbutton
    writetext(AmphyBreathingLaboredText)
    waitbutton
    closetext
    s_end
HealthyNow:
    writetext(AmphyPaluPaluluText)
    playcry(AMPHAROS)
    waitbutton
    closetext
    special(FadeOutPalettes)
    special(FadeInPalettes)
    special(FadeOutPalettes)
    special(FadeInPalettes)
    s_end
    SCRIPT_END
}
const struct ItemBall OlivineLighthouse6FSuperPotion = {SUPER_POTION, 1};
const uint8_t OlivineLighthouseJasmineLeavesUpMovement[] = {
    slow_step(UP),
    slow_step(UP),
    slow_step(RIGHT),
    slow_step(UP),
    slow_step(UP),
    step_sleep(8),
    step_sleep(8),
    movement_step_end,
};
const uint8_t OlivineLighthouseJasmineLeavesDownMovement[] = {
    slow_step(DOWN),
    slow_step(RIGHT),
    slow_step(RIGHT),
    slow_step(RIGHT),
    slow_step(UP),
    slow_step(RIGHT),
    slow_step(RIGHT),
    slow_step(RIGHT),
    movement_step_end,
};
const uint8_t OlivineLighthouseJasmineLeavesRightMovement[] = {
    slow_step(UP),
    slow_step(UP),
    slow_step(RIGHT),
    slow_step(UP),
    slow_step(UP),
    slow_step(UP),
    step_sleep(8),
    movement_step_end,
};
const txt_cmd_s JasmineCianwoodPharmacyText[] = {
    text_start("JASMINE: … This"
        t_line "#MON always"
        t_para "kept the sea lit"
        t_line "at night."
        t_para "…But it suddenly"
        t_line "got sick… It's"
        t_cont "gasping for air…"
        t_para "…I understand"
        t_line "that there is a"
        t_para "wonderful PHARMACY"
        t_line "in CIANWOOD…"
        t_para "But that's across"
        t_line "the sea…"
        t_para "And I can't leave"
        t_line "AMPHY unattended…"
        t_done )
};
const txt_cmd_s JasmineGetSomeMedicineText[] = {
    text_start("…May I ask you to"
        t_line "get some medicine"
        t_cont "for me? Please?"
        t_done )
};
const txt_cmd_s JasmineCureAmphyText[] = {
    text_start("JASMINE: …Will"
        t_line "that medicine cure"
        t_cont "AMPHY?"
        t_done )
};
const txt_cmd_s PlayerHandedSecretpotionText[] = {
    text_start("<PLAYER> handed the"
        t_line "SECRETPOTION to"
        t_cont "JASMINE."
        t_done )
};
const txt_cmd_s JasmineDontBeOffendedText[] = {
    text_start("JASMINE: …Um,"
        t_line "please don't be"
        t_cont "offended…"
        t_para "…AMPHY will not"
        t_line "take anything from"
        t_cont "anyone but me…"
        t_done )
};
const txt_cmd_s JasmineAmphyHowAreYouFeelingText[] = {
    text_start("JASMINE: …"
        t_para "AMPHY, how are you"
        t_line "feeling?"
        t_done )
};
const txt_cmd_s JasmineThankYouText[] = {
    text_start("JASMINE: …Oh, I'm"
        t_line "so relieved…"
        t_para "This is just so"
        t_line "wonderful…"
        t_para "Thank you so very,"
        t_line "very much."
        t_para "…I will return to"
        t_line "the GYM…"
        t_done )
};
const txt_cmd_s JasmineISeeText[] = {
    text_start("JASMINE: …I see…"
        t_done )
};
const txt_cmd_s JasmineAmphyHangOnText[] = {
    text_start("…AMPHY, hang on!"
        t_done )
};
const txt_cmd_s AmphyPalPalooText[] = {
    text_start("AMPHY: …"
        t_line "…Pa… paloo…"
        t_done )
};
const txt_cmd_s AmphyBreathingLaboredText[] = {
    text_start("Its breathing is"
        t_line "terribly labored…"
        t_done )
};
const txt_cmd_s AmphyPaluPaluluText[] = {
    text_start("AMPHY: Palu!"
        t_line "Palulu!"
        t_done )
    //db(0, 0) // filler
};
