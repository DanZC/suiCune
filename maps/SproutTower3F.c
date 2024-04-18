#include "../constants.h"
#include "../util/scripting.h"
#include "SproutTower3F.h"
//// EVENTS
enum {
    SPROUTTOWER3F_SAGE1 = 2,
    SPROUTTOWER3F_SAGE2,
    SPROUTTOWER3F_SAGE3,
    SPROUTTOWER3F_SAGE4,
    SPROUTTOWER3F_POKE_BALL1,
    SPROUTTOWER3F_POKE_BALL2,
    SPROUTTOWER3F_SILVER,
};

const Script_fn_t SproutTower3F_SceneScripts[] = {
    SproutTower3F_MapScripts_DummyScene0 , //  SCENE_DEFAULT,
    SproutTower3F_MapScripts_DummyScene1 , //  SCENE_FINISHED,
};

const struct MapCallback SproutTower3F_MapCallbacks[] = {
    0,
};

const struct MapScripts SproutTower3F_MapScripts = {
    .scene_script_count = lengthof(SproutTower3F_SceneScripts),
    .scene_scripts = SproutTower3F_SceneScripts,

    .callback_count = 0, // lengthof(SproutTower3F_MapCallbacks),
    .callbacks = SproutTower3F_MapCallbacks,
};

static const struct CoordEvent SproutTower3F_CoordEvents[] = {
    coord_event(11, 9, SCENE_DEFAULT, &SproutTower3FRivalScene),
};

static const struct BGEvent SproutTower3F_BGEvents[] = {
    bg_event(8, 1, BGEVENT_READ, &SproutTower3FStatue),
    bg_event(11, 1, BGEVENT_READ, &SproutTower3FStatue),
    bg_event(9, 0, BGEVENT_READ, &SproutTower3FPainting),
    bg_event(10, 0, BGEVENT_READ, &SproutTower3FPainting),
    bg_event(5, 15, BGEVENT_READ, &SproutTower3FStatue),
    bg_event(14, 15, BGEVENT_READ, &SproutTower3FStatue),
};

static const struct WarpEventData SproutTower3F_WarpEvents[] = {
    warp_event(10, 14, SPROUT_TOWER_2F, 4),
};

static const struct ObjEvent SproutTower3F_ObjectEvents[] = {
    object_event(8, 13, SPRITE_SAGE, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerSageJin, -1),
    object_event(8, 8, SPRITE_SAGE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 2, &TrainerSageTroy, -1),
    object_event(10, 2, SPRITE_SAGE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &SageLiScript, -1),
    object_event(11, 11, SPRITE_SAGE, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerSageNeal, -1),
    object_event(6, 14, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &SproutTower3FPotion, EVENT_SPROUT_TOWER_3F_POTION),
    object_event(14, 1, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &SproutTower3FEscapeRope, EVENT_SPROUT_TOWER_3F_ESCAPE_ROPE),
    object_event(10, 4, SPRITE_SILVER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, EVENT_RIVAL_SPROUT_TOWER),
};

const struct MapEvents SproutTower3F_MapEvents = {
    .warp_event_count = lengthof(SproutTower3F_WarpEvents),
    .warp_events = SproutTower3F_WarpEvents,

    .coord_event_count = lengthof(SproutTower3F_CoordEvents),
    .coord_events = SproutTower3F_CoordEvents,

    .bg_event_count = lengthof(SproutTower3F_BGEvents),
    .bg_events = SproutTower3F_BGEvents,

    .obj_event_count = lengthof(SproutTower3F_ObjectEvents),
    .obj_events = SproutTower3F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "SproutTower3F.h"

bool SproutTower3F_MapScripts_DummyScene0(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool SproutTower3F_MapScripts_DummyScene1(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool SproutTower3FRivalScene(script_s* s) {
    SCRIPT_BEGIN
    turnobject(PLAYER, UP)
    showemote(EMOTE_SHOCK, PLAYER, 15)
    special(FadeOutMusic)
    playsound(SFX_TACKLE)
    playsound(SFX_ELEVATOR)
    earthquake(79)
    pause(15)
    playsound(SFX_TACKLE)
    playsound(SFX_ELEVATOR)
    earthquake(79)
    applymovement(PLAYER, SproutTower3FPlayerApproachesRivalMovement)
    applymovement(SPROUTTOWER3F_SILVER, SproutTower3FRivalApproachesElderMovement)
    opentext
    writetext(SproutTowerElderLecturesRivalText)
    waitbutton
    closetext
    showemote(EMOTE_SHOCK, SPROUTTOWER3F_SILVER, 15)
    turnobject(SPROUTTOWER3F_SILVER, DOWN)
    pause(15)
    applymovement(SPROUTTOWER3F_SILVER, SproutTower3FRivalLeavesElderMovement)
    playmusic(MUSIC_RIVAL_ENCOUNTER)
    opentext
    writetext(SproutTowerRivalOnlyCareAboutStrongText)
    waitbutton
    closetext
    turnobject(SPROUTTOWER3F_SILVER, UP)
    opentext
    writetext(SproutTowerRivalUsedEscapeRopeText)
    pause(15)
    closetext
    playsound(SFX_WARP_TO)
    special(FadeBlackQuickly)
    special(ReloadSpritesNoPalettes)
    disappear(SPROUTTOWER3F_SILVER)
    waitsfx
    special(FadeInQuickly)
    setscene(SCENE_FINISHED)
    special(RestartMapMusic)
    s_end
    SCRIPT_END
}
bool SageLiScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_HM05_FLASH)
    iftrue(GotFlash)
    writetext(SageLiSeenText)
    waitbutton
    closetext
    winlosstext(SageLiBeatenText, 0)
    loadtrainer(SAGE, LI)
    startbattle
    reloadmapafterbattle
    opentext
    writetext(SageLiTakeThisFlashText)
    promptbutton
    verbosegiveitem(HM_FLASH, 1)
    setevent(EVENT_GOT_HM05_FLASH)
    setevent(EVENT_BEAT_SAGE_LI)
    writetext(SageLiFlashExplanationText)
    waitbutton
    closetext
    s_end
GotFlash:
    writetext(SageLiAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSageJin = {SAGE, JIN, EVENT_BEAT_SAGE_JIN, SageJinSeenText, SageJinBeatenText, 0, TrainerSageJin_Script};
bool TrainerSageJin_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SageJinAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSageTroy = {SAGE, TROY, EVENT_BEAT_SAGE_TROY, SageTroySeenText, SageTroyBeatenText, 0, TrainerSageTroy_Script};
bool TrainerSageTroy_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SageTroyAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSageNeal = {SAGE, NEAL, EVENT_BEAT_SAGE_NEAL, SageNealSeenText, SageNealBeatenText, 0, TrainerSageNeal_Script};
bool TrainerSageNeal_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SageNealAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool SproutTower3FPainting(script_s* s) {
    SCRIPT_BEGIN
    jumptext(SproutTower3FPaintingText)
    SCRIPT_END
}
bool SproutTower3FStatue(script_s* s) {
    SCRIPT_BEGIN
    jumptext(SproutTower3FStatueText)
    SCRIPT_END
}
const struct ItemBall SproutTower3FPotion = {POTION, 1};
const struct ItemBall SproutTower3FEscapeRope = {ESCAPE_ROPE, 1};
const uint8_t SproutTower3FPlayerApproachesRivalMovement[] = {
    step(UP),
    step(UP),
    step(UP),
    step(UP),
    movement_step_end,
};
const uint8_t SproutTower3FRivalApproachesElderMovement[] = {
    step(UP),
    movement_step_end,
};
const uint8_t SproutTower3FRivalLeavesElderMovement[] = {
    step(RIGHT),
    step(DOWN),
    movement_step_end,
};
const txt_cmd_s SproutTowerElderLecturesRivalText[] = {
    text_start("ELDER: You are in-"
        t_line "deed skilled as a"
        t_cont "trainer."
        t_para "As promised, here"
        t_line "is your HM."
        t_para "But let me say"
        t_line "this: You should"
        t_para "treat your"
        t_line "#MON better."
        t_para "The way you battle"
        t_line "is far too harsh."
        t_para "#MON are not"
        t_line "tools of war…"
        t_done )
};
const txt_cmd_s SproutTowerRivalOnlyCareAboutStrongText[] = {
    text_start("…"
        t_line "…Humph!"
        t_para "He claims to be"
        t_line "the ELDER but"
        t_cont "he's weak."
        t_para "It stands to"
        t_line "reason."
        t_para "I'd never lose to"
        t_line "fools who babble"
        t_para "about being nice"
        t_line "to #MON."
        t_para "I only care about"
        t_line "strong #MON"
        t_cont "that can win."
        t_para "I really couldn't"
        t_line "care less about"
        t_cont "weak #MON."
        t_done )
};
const txt_cmd_s SproutTowerRivalUsedEscapeRopeText[] = {
    text_start("<RIVAL> used an"
        t_line "ESCAPE ROPE!"
        t_done )
};
const txt_cmd_s SageLiSeenText[] = {
    text_start("So good of you to"
        t_line "come here!"
        t_para "SPROUT TOWER is a"
        t_line "place of training."
        t_para "People and #MON"
        t_line "test their bonds"
        t_para "to build a bright"
        t_line "future together."
        t_para "I am the final"
        t_line "test."
        t_para "Allow me to check"
        t_line "the ties between"
        t_para "your #MON and"
        t_line "you!"
        t_done )
};
const txt_cmd_s SageLiBeatenText[] = {
    text_start("Ah, excellent!"
        t_done )
};
const txt_cmd_s SageLiTakeThisFlashText[] = {
    text_start("You and your #-"
        t_line "MON should have"
        t_para "no problem using"
        t_line "this move."
        t_para "Take this FLASH"
        t_line "HM."
        t_done )
};
const txt_cmd_s SageLiFlashExplanationText[] = {
    text_start("FLASH illuminates"
        t_line "even the darkest"
        t_cont "of all places."
        t_para "But to use it out"
        t_line "of battle, you"
        t_para "need the BADGE"
        t_line "from VIOLET's GYM."
        t_done )
};
const txt_cmd_s SageLiAfterBattleText[] = {
    text_start("I hope you learn"
        t_line "and grow from your"
        t_cont "journey."
        t_done )
};
const txt_cmd_s SageJinSeenText[] = {
    text_start("I train to find"
        t_line "enlightenment in"
        t_cont "#MON!"
        t_done )
};
const txt_cmd_s SageJinBeatenText[] = {
    text_start("My training is"
        t_line "incomplete…"
        t_done )
};
const txt_cmd_s SageJinAfterBattleText[] = {
    text_start("As #MON grow"
        t_line "stronger, so does"
        t_cont "the trainer."
        t_para "No, wait. As the"
        t_line "trainer grows"
        t_para "stronger, so do"
        t_line "the #MON."
        t_done )
};
const txt_cmd_s SageTroySeenText[] = {
    text_start("Let me see how"
        t_line "much you trust"
        t_cont "your #MON."
        t_done )
};
const txt_cmd_s SageTroyBeatenText[] = {
    text_start("Yes, your trust is"
        t_line "real!"
        t_done )
};
const txt_cmd_s SageTroyAfterBattleText[] = {
    text_start("It is not far to"
        t_line "the ELDER."
        t_done )
};
const txt_cmd_s SageNealSeenText[] = {
    text_start("The ELDER's HM"
        t_line "lights even pitch-"
        t_cont "black darkness."
        t_done )
};
const txt_cmd_s SageNealBeatenText[] = {
    text_start("It is my head that"
        t_line "is bright!"
        t_done )
};
const txt_cmd_s SageNealAfterBattleText[] = {
    text_start("Let there be light"
        t_line "on your journey."
        t_done )
};
const txt_cmd_s SproutTower3FPaintingText[] = {
    text_start("It's a powerful"
        t_line "painting of a"
        t_cont "BELLSPROUT."
        t_done )
};
const txt_cmd_s SproutTower3FStatueText[] = {
    text_start("A #MON statue…"
        t_para "It looks very"
        t_line "distinguished."
        t_done )
    //db(0, 0) // filler
};
