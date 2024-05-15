#include "../constants.h"
#include "../util/scripting.h"
#include "SlowpokeWellB1F.h"
//// EVENTS
enum {
    SLOWPOKEWELLB1F_ROCKET1 = 2,
    SLOWPOKEWELLB1F_ROCKET2,
    SLOWPOKEWELLB1F_ROCKET3,
    SLOWPOKEWELLB1F_ROCKET_GIRL,
    SLOWPOKEWELLB1F_SLOWPOKE1,
    SLOWPOKEWELLB1F_SLOWPOKE2,
    SLOWPOKEWELLB1F_KURT,
    SLOWPOKEWELLB1F_BOULDER,
    SLOWPOKEWELLB1F_POKE_BALL,
};

const Script_fn_t SlowpokeWellB1F_SceneScripts[] = {
    0,
};

const struct MapCallback SlowpokeWellB1F_MapCallbacks[] = {
    0,
};

const struct MapScripts SlowpokeWellB1F_MapScripts = {
    .scene_script_count = 0, // lengthof(SlowpokeWellB1F_SceneScripts),
    .scene_scripts = SlowpokeWellB1F_SceneScripts,

    .callback_count = 0, // lengthof(SlowpokeWellB1F_MapCallbacks),
    .callbacks = SlowpokeWellB1F_MapCallbacks,
};

static const struct CoordEvent SlowpokeWellB1F_CoordEvents[] = {
    0,
};

static const struct BGEvent SlowpokeWellB1F_BGEvents[] = {
    0,
};

static const struct WarpEventData SlowpokeWellB1F_WarpEvents[] = {
    warp_event(17, 15, AZALEA_TOWN, 6),
    warp_event(7, 11, SLOWPOKE_WELL_B2F, 1),
};

static const struct ObjEvent SlowpokeWellB1F_ObjectEvents[] = {
    object_event(15, 7, SPRITE_ROCKET, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_TRAINER, 3, &TrainerGruntM29, EVENT_SLOWPOKE_WELL_ROCKETS),
    object_event(5, 2, SPRITE_ROCKET, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_TRAINER, 1, &TrainerGruntM1, EVENT_SLOWPOKE_WELL_ROCKETS),
    object_event(5, 6, SPRITE_ROCKET, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_TRAINER, 2, &TrainerGruntM2, EVENT_SLOWPOKE_WELL_ROCKETS),
    object_event(10, 4, SPRITE_ROCKET_GIRL, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 4, &TrainerGruntF1, EVENT_SLOWPOKE_WELL_ROCKETS),
    object_event(7, 4, SPRITE_SLOWPOKE, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &SlowpokeWellB1FSlowpokeWithMailScript, EVENT_SLOWPOKE_WELL_SLOWPOKES),
    object_event(6, 2, SPRITE_SLOWPOKE, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &SlowpokeWellB1FTaillessSlowpokeScript, EVENT_SLOWPOKE_WELL_SLOWPOKES),
    object_event(16, 14, SPRITE_KURT, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &SlowpokeWellB1FKurtScript, EVENT_SLOWPOKE_WELL_KURT),
    object_event(3, 2, SPRITE_BOULDER, SPRITEMOVEDATA_STRENGTH_BOULDER, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &SlowpokeWellB1FBoulder, -1),
    object_event(10, 3, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &SlowpokeWellB1FSuperPotion, EVENT_SLOWPOKE_WELL_B1F_SUPER_POTION),
};

const struct MapEvents SlowpokeWellB1F_MapEvents = {
    .warp_event_count = lengthof(SlowpokeWellB1F_WarpEvents),
    .warp_events = SlowpokeWellB1F_WarpEvents,

    .coord_event_count = 0, // lengthof(SlowpokeWellB1F_CoordEvents),
    .coord_events = SlowpokeWellB1F_CoordEvents,

    .bg_event_count = 0, // lengthof(SlowpokeWellB1F_BGEvents),
    .bg_events = SlowpokeWellB1F_BGEvents,

    .obj_event_count = lengthof(SlowpokeWellB1F_ObjectEvents),
    .obj_events = SlowpokeWellB1F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "SlowpokeWellB1F.h"

bool SlowpokeWellB1FKurtScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(SlowpokeWellB1FKurtText)
    SCRIPT_END
}
const struct TrainerObj TrainerGruntM29 = {GRUNTM, GRUNTM_29, EVENT_BEAT_ROCKET_GRUNTM_29, GruntM29SeenText, GruntM29BeatenText, 0, TrainerGruntM29_Script};
bool TrainerGruntM29_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(GruntM29AfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerGruntM1 = {GRUNTM, GRUNTM_1, EVENT_BEAT_ROCKET_GRUNTM_1, GruntM1SeenText, GruntM1BeatenText, 0, TrainerGruntM1_Script};
bool TrainerGruntM1_Script(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(TrainerGruntM1WhenTalkText)
    waitbutton
    closetext
    special(FadeBlackQuickly)
    special(ReloadSpritesNoPalettes)
    disappear(SLOWPOKEWELLB1F_ROCKET1)
    disappear(SLOWPOKEWELLB1F_ROCKET2)
    disappear(SLOWPOKEWELLB1F_ROCKET3)
    disappear(SLOWPOKEWELLB1F_ROCKET_GIRL)
    pause(15)
    special(FadeInQuickly)
    disappear(SLOWPOKEWELLB1F_KURT)
    moveobject(SLOWPOKEWELLB1F_KURT, 11, 6)
    appear(SLOWPOKEWELLB1F_KURT)
    applymovement(SLOWPOKEWELLB1F_KURT, KurtSlowpokeWellVictoryMovementData)
    turnobject(PLAYER, RIGHT)
    opentext
    writetext(KurtLeaveSlowpokeWellText)
    waitbutton
    closetext
    setevent(EVENT_CLEARED_SLOWPOKE_WELL)
    variablesprite(SPRITE_AZALEA_ROCKET, SPRITE_SILVER)
    setmapscene(AZALEA_TOWN, SCENE_AZALEATOWN_RIVAL_BATTLE)
    clearevent(EVENT_ILEX_FOREST_APPRENTICE)
    clearevent(EVENT_ILEX_FOREST_FARFETCHD)
    setevent(EVENT_CHARCOAL_KILN_FARFETCH_D)
    setevent(EVENT_CHARCOAL_KILN_APPRENTICE)
    setevent(EVENT_SLOWPOKE_WELL_SLOWPOKES)
    setevent(EVENT_SLOWPOKE_WELL_KURT)
    clearevent(EVENT_AZALEA_TOWN_SLOWPOKES)
    clearevent(EVENT_KURTS_HOUSE_SLOWPOKE)
    clearevent(EVENT_KURTS_HOUSE_KURT_1)
    special(FadeOutPalettes)
    special(HealParty)
    pause(15)
    warp(KURTS_HOUSE, 3, 3)
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerGruntM2 = {GRUNTM, GRUNTM_2, EVENT_BEAT_ROCKET_GRUNTM_2, GruntM2SeenText, GruntM2BeatenText, 0, TrainerGruntM2_Script};
bool TrainerGruntM2_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(GruntM2AfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerGruntF1 = {GRUNTF, GRUNTF_1, EVENT_BEAT_ROCKET_GRUNTF_1, GruntF1SeenText, GruntF1BeatenText, 0, TrainerGruntF1_Script};
bool TrainerGruntF1_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(GruntF1AfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool SlowpokeWellB1FSlowpokeWithMailScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    playcry(SLOWPOKE)
    writetext(SlowpokeWellB1FSlowpokeWithMailText)
    yesorno
    iftrue(ReadMail)
    closetext
    s_end
ReadMail:
    writetext(SlowpokeWellB1FSlowpokeMailText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool SlowpokeWellB1FTaillessSlowpokeScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(SlowpokeWellB1FTaillessSlowpokeText)
    playcry(SLOWPOKE)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool SlowpokeWellB1FBoulder(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(StrengthBoulderScript)
    SCRIPT_END
}
const struct ItemBall SlowpokeWellB1FSuperPotion = {SUPER_POTION, 1};
const uint8_t KurtSlowpokeWellVictoryMovementData[] = {
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(UP),
    step_sleep(8),
    step_sleep(8),
    step_sleep(8),
    step(LEFT),
    step(UP),
    step(UP),
    step_sleep(8),
    step_sleep(8),
    step_sleep(8),
    turn_head(LEFT),
    movement_step_end,
};
const txt_cmd_s SlowpokeWellB1FKurtText[] = {
    text_start("KURT: Hey there,"
        t_line "<PLAYER>!"
        t_para "The guard up top"
        t_line "took off when I"
        t_cont "shouted at him."
        t_para "But then I took a"
        t_line "tumble down the"
        t_cont "WELL."
        t_para "I slammed down"
        t_line "hard on my back,"
        t_cont "so I can't move."
        t_para "Rats! If I were"
        t_line "fit, my #MON"
        t_para "would've punished"
        t_line "them…"
        t_para "Ah, it can't be"
        t_line "helped."
        t_para "<PLAYER>, show them"
        t_line "how gutsy you are"
        t_cont "in my place!"
        t_done )
};
const txt_cmd_s KurtLeaveSlowpokeWellText[] = {
    text_start("KURT: Way to go,"
        t_line "<PLAYER>!"
        t_para "TEAM ROCKET has"
        t_line "taken off."
        t_para "My back's better"
        t_line "too. Let's get out"
        t_cont "of here."
        t_done )
};
const txt_cmd_s GruntM29SeenText[] = {
    text_start("Darn! I was stand-"
        t_line "ing guard up top"
        t_para "when some old coot"
        t_line "yelled at me."
        t_para "He startled me so"
        t_line "much that I fell"
        t_cont "down here."
        t_para "I think I'll vent"
        t_line "my anger by taking"
        t_cont "it out on you!"
        t_done )
};
const txt_cmd_s GruntM29BeatenText[] = {
    text_start("Arrgh! This is NOT"
        t_line "my day!"
        t_done )
};
const txt_cmd_s GruntM29AfterBattleText[] = {
    text_start("Sure, we've been"
        t_line "hacking the tails"
        t_para "off SLOWPOKE and"
        t_line "selling them."
        t_para "Everything we do"
        t_line "is for profit."
        t_para "That's right!"
        t_line "We're TEAM ROCKET,"
        t_para "and we'll do any-"
        t_line "thing for money!"
        t_done )
};
const txt_cmd_s GruntM1SeenText[] = {
    text_start("What do you want?"
        t_para "If you interrupt"
        t_line "our work, don't"
        t_cont "expect any mercy!"
        t_done )
};
const txt_cmd_s GruntM1BeatenText[] = {
    text_start("You did OK today,"
        t_line "but wait till next"
        t_cont "time!"
        t_done )
};
const txt_cmd_s TrainerGruntM1WhenTalkText[] = {
    text_start("Yeah, TEAM ROCKET"
        t_line "was broken up"
        t_cont "three years ago."
        t_para "But we continued"
        t_line "our activities"
        t_cont "underground."
        t_para "Now you can have"
        t_line "fun watching us"
        t_cont "stir up trouble!"
        t_done )
};
const txt_cmd_s GruntM2SeenText[] = {
    text_start("Quit taking SLOW-"
        t_line "POKETAILS?"
        t_para "If we obeyed you,"
        t_line "TEAM ROCKET's rep"
        t_cont "would be ruined!"
        t_done )
};
const txt_cmd_s GruntM2BeatenText[] = {
    text_start("Just…"
        t_line "Too strong…"
        t_done )
};
const txt_cmd_s GruntM2AfterBattleText[] = {
    text_start("We need the money,"
        t_line "but selling SLOW-"
        t_cont "POKETAILS?"
        t_para "It's tough being a"
        t_line "ROCKET GRUNT!"
        t_done )
};
const txt_cmd_s GruntF1SeenText[] = {
    text_start("Stop taking TAILS?"
        t_para "Yeah, just try to"
        t_line "defeat all of us!"
        t_done )
};
const txt_cmd_s GruntF1BeatenText[] = {
    text_start("You rotten brat!"
        t_done )
};
const txt_cmd_s GruntF1AfterBattleText[] = {
    text_start("SLOWPOKETAILS"
        t_line "grow back fast!"
        t_para "What's wrong with"
        t_line "selling them?"
        t_done )
};
const txt_cmd_s SlowpokeWellB1FSlowpokeWithMailText[] = {
    text_start("A SLOWPOKE with"
        t_line "its TAIL cut off…"
        t_para "Huh? It has MAIL."
        t_line "Read it?"
        t_done )
};
const txt_cmd_s SlowpokeWellB1FSlowpokeMailText[] = {
    text_start("<PLAYER> read the"
        t_line "MAIL."
        t_para "Be good and look"
        t_line "after the house"
        t_para "with Grandpa and"
        t_line "SLOWPOKE."
        t_para "Love, Dad"
        t_done )
};
const txt_cmd_s SlowpokeWellB1FTaillessSlowpokeText[] = {
    text_start("A SLOWPOKE with"
        t_line "its TAIL cut off…"
        t_done )
    //db(0, 0) // filler
};
