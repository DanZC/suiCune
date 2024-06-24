#include "../constants.h"
#include "../util/scripting.h"
#include "RadioTower5F.h"
//// EVENTS
enum {
    RADIOTOWER5F_DIRECTOR = 2,
    RADIOTOWER5F_ROCKET,
    RADIOTOWER5F_ROCKET_GIRL,
    RADIOTOWER5F_ROCKER,
    RADIOTOWER5F_POKE_BALL,
};

const Script_fn_t RadioTower5F_SceneScripts[] = {
    RadioTower5F_MapScripts_DummyScene0 , //  SCENE_DEFAULT,
    RadioTower5F_MapScripts_DummyScene1 , //  SCENE_RADIOTOWER5F_ROCKET_BOSS,
    RadioTower5F_MapScripts_DummyScene2 , //  SCENE_RADIOTOWER5F_NOTHING,
};

const struct MapCallback RadioTower5F_MapCallbacks[] = {
    0,
};

const struct MapScripts RadioTower5F_MapScripts = {
    .scene_script_count = lengthof(RadioTower5F_SceneScripts),
    .scene_scripts = RadioTower5F_SceneScripts,

    .callback_count = 0, // lengthof(RadioTower5F_MapCallbacks),
    .callbacks = RadioTower5F_MapCallbacks,
};

static const struct CoordEvent RadioTower5F_CoordEvents[] = {
    coord_event(0, 3, SCENE_DEFAULT, &FakeDirectorScript),
    coord_event(16, 5, SCENE_RADIOTOWER5F_ROCKET_BOSS, &RadioTower5FRocketBossScene),
};

static const struct BGEvent RadioTower5F_BGEvents[] = {
    bg_event(3, 0, BGEVENT_READ, &RadioTower5FDirectorsOfficeSign),
    bg_event(11, 0, BGEVENT_READ, &RadioTower5FStudio1Sign),
    bg_event(15, 0, BGEVENT_READ, &RadioTower5FStudio1Sign),
    bg_event(16, 1, BGEVENT_READ, &RadioTower5FBookshelf),
    bg_event(17, 1, BGEVENT_READ, &RadioTower5FBookshelf),
};

static const struct WarpEventData RadioTower5F_WarpEvents[] = {
    warp_event(0, 0, RADIO_TOWER_4F, 1),
    warp_event(12, 0, RADIO_TOWER_4F, 3),
};

static const struct ObjEvent RadioTower5F_ObjectEvents[] = {
    object_event(3, 6, SPRITE_GENTLEMAN, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Director, -1),
    object_event(13, 5, SPRITE_ROCKET, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, EVENT_RADIO_TOWER_ROCKET_TAKEOVER),
    object_event(17, 2, SPRITE_ROCKET_GIRL, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 1, &TrainerExecutivef1, EVENT_RADIO_TOWER_ROCKET_TAKEOVER),
    object_event(13, 5, SPRITE_ROCKER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &Ben, EVENT_RADIO_TOWER_CIVILIANS_AFTER),
    object_event(8, 5, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &RadioTower5FUltraBall, EVENT_RADIO_TOWER_5F_ULTRA_BALL),
};

const struct MapEvents RadioTower5F_MapEvents = {
    .warp_event_count = lengthof(RadioTower5F_WarpEvents),
    .warp_events = RadioTower5F_WarpEvents,

    .coord_event_count = lengthof(RadioTower5F_CoordEvents),
    .coord_events = RadioTower5F_CoordEvents,

    .bg_event_count = lengthof(RadioTower5F_BGEvents),
    .bg_events = RadioTower5F_BGEvents,

    .obj_event_count = lengthof(RadioTower5F_ObjectEvents),
    .obj_events = RadioTower5F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "RadioTower5F.h"

bool RadioTower5F_MapScripts_DummyScene0(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool RadioTower5F_MapScripts_DummyScene1(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool RadioTower5F_MapScripts_DummyScene2(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool FakeDirectorScript(script_s* s) {
    SCRIPT_BEGIN
    turnobject(RADIOTOWER5F_DIRECTOR, UP)
    showemote(EMOTE_SHOCK, RADIOTOWER5F_DIRECTOR, 15)
    opentext
    writetext(FakeDirectorTextBefore1)
    waitbutton
    closetext
    applymovement(RADIOTOWER5F_DIRECTOR, FakeDirectorMovement)
    playmusic(MUSIC_ROCKET_ENCOUNTER)
    opentext
    writetext(FakeDirectorTextBefore2)
    waitbutton
    closetext
    winlosstext(FakeDirectorWinText, 0)
    setlasttalked(RADIOTOWER5F_DIRECTOR)
    loadtrainer(EXECUTIVEM, EXECUTIVEM_3)
    startbattle
    reloadmapafterbattle
    opentext
    writetext(FakeDirectorTextAfter)
    promptbutton
    verbosegiveitem(BASEMENT_KEY, 1)
    closetext
    setscene(SCENE_RADIOTOWER5F_ROCKET_BOSS)
    setevent(EVENT_BEAT_ROCKET_EXECUTIVEM_3)
    s_end
    SCRIPT_END
}
bool Director(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_CLEARED_RADIO_TOWER)
    iftrue(TrueDirector)
    writetext(FakeDirectorTextAfter)
    waitbutton
    closetext
    s_end
TrueDirector:
    writetext(RadioTower5FDirectorText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerExecutivef1 = {EXECUTIVEF, EXECUTIVEF_1, EVENT_BEAT_ROCKET_EXECUTIVEF_1, Executivef1SeenText, Executivef1BeatenText, 0, TrainerExecutivef1_Script};
bool TrainerExecutivef1_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(Executivef1AfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool RadioTower5FRocketBossScene(script_s* s) {
    SCRIPT_BEGIN
    applymovement(PLAYER, RadioTower5FPlayerTwoStepsLeftMovement)
    playmusic(MUSIC_ROCKET_ENCOUNTER)
    turnobject(RADIOTOWER5F_ROCKET, RIGHT)
    opentext
    writetext(RadioTower5FRocketBossBeforeText)
    waitbutton
    closetext
    winlosstext(RadioTower5FRocketBossWinText, 0)
    setlasttalked(RADIOTOWER5F_ROCKET)
    loadtrainer(EXECUTIVEM, EXECUTIVEM_1)
    startbattle
    reloadmapafterbattle
    opentext
    writetext(RadioTower5FRocketBossAfterText)
    waitbutton
    closetext
    special(FadeBlackQuickly)
    special(ReloadSpritesNoPalettes)
    disappear(RADIOTOWER5F_ROCKET)
    disappear(RADIOTOWER5F_ROCKET_GIRL)
    pause(15)
    special(FadeInQuickly)
    setevent(EVENT_BEAT_ROCKET_EXECUTIVEM_1)
    setevent(EVENT_CLEARED_RADIO_TOWER)
    clearflag(ENGINE_ROCKETS_IN_RADIO_TOWER)
    setevent(EVENT_GOLDENROD_CITY_ROCKET_SCOUT)
    setevent(EVENT_GOLDENROD_CITY_ROCKET_TAKEOVER)
    setevent(EVENT_RADIO_TOWER_ROCKET_TAKEOVER)
    clearevent(EVENT_MAHOGANY_MART_OWNERS)
    clearflag(ENGINE_ROCKETS_IN_MAHOGANY)
    clearevent(EVENT_GOLDENROD_CITY_CIVILIANS)
    clearevent(EVENT_RADIO_TOWER_CIVILIANS_AFTER)
    setevent(EVENT_BLACKTHORN_CITY_SUPER_NERD_BLOCKS_GYM)
    clearevent(EVENT_BLACKTHORN_CITY_SUPER_NERD_DOES_NOT_BLOCK_GYM)
    special(PlayMapMusic)
    disappear(RADIOTOWER5F_DIRECTOR)
    moveobject(RADIOTOWER5F_DIRECTOR, 12, 0)
    appear(RADIOTOWER5F_DIRECTOR)
    applymovement(RADIOTOWER5F_DIRECTOR, RadioTower5FDirectorWalksIn)
    turnobject(PLAYER, RIGHT)
    opentext
    writetext(RadioTower5FDirectorThankYouText)
    promptbutton
    verbosegiveitem(CLEAR_BELL, 1)
    writetext(RadioTower5FDirectorDescribeClearBellText)
    waitbutton
    closetext
    setscene(SCENE_RADIOTOWER5F_NOTHING)
    setmapscene(ECRUTEAK_TIN_TOWER_ENTRANCE, SCENE_DEFAULT)
    setevent(EVENT_GOT_CLEAR_BELL)
    setevent(EVENT_TEAM_ROCKET_DISBANDED)
    goto UselessJump;
UselessJump:
    applymovement(RADIOTOWER5F_DIRECTOR, RadioTower5FDirectorWalksOut)
    playsound(SFX_EXIT_BUILDING)
    disappear(RADIOTOWER5F_DIRECTOR)
    s_end
    SCRIPT_END
}
bool Ben(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(BenText)
    SCRIPT_END
}
const struct ItemBall RadioTower5FUltraBall = {ULTRA_BALL, 1};
bool RadioTower5FDirectorsOfficeSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(RadioTower5FDirectorsOfficeSignText)
    SCRIPT_END
}
bool RadioTower5FStudio1Sign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(RadioTower5FStudio1SignText)
    SCRIPT_END
}
bool RadioTower5FBookshelf(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(MagazineBookshelfScript)
    SCRIPT_END
}
const uint8_t FakeDirectorMovement[] = {
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(UP),
    step(UP),
    movement_step_end,
};
const uint8_t RadioTower5FDirectorWalksIn[] = {
    step(DOWN),
    step(DOWN),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(LEFT),
    movement_step_end,
};
const uint8_t RadioTower5FDirectorWalksOut[] = {
    step(RIGHT),
    step(UP),
    step(UP),
    step(UP),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(UP),
    step(UP),
    movement_step_end,
};
const uint8_t RadioTower5FPlayerTwoStepsLeftMovement[] = {
    step(LEFT),
    step(LEFT),
    movement_step_end,
};
const txt_cmd_s FakeDirectorTextBefore1[] = {
    text_start("Y-you! You came to"
        t_line "rescue me?"
        t_done )
};
const txt_cmd_s FakeDirectorTextBefore2[] = {
    text_start("Is that what you"
        t_line "were expecting?"
        t_para "Wrong!"
        t_line "I'm an imposter!"
        t_para "I pretended to be"
        t_line "the real thing to"
        t_para "prepare for our"
        t_line "takeover."
        t_para "Do you want to"
        t_line "know where we hid"
        t_cont "the real DIRECTOR?"
        t_para "Sure, I'll tell"
        t_line "you. But only if"
        t_cont "you can beat me!"
        t_done )
};
const txt_cmd_s FakeDirectorWinText[] = {
    text_start("OK, OK. I'll tell"
        t_line "you where he is."
        t_done )
};
const txt_cmd_s FakeDirectorTextAfter[] = {
    text_start("We stashed the"
        t_line "real DIRECTOR in"
        t_para "the UNDERGROUND"
        t_line "WAREHOUSE."
        t_para "It's at the far"
        t_line "end of the UNDER-"
        t_cont "GROUND."
        t_para "But I doubt you'll"
        t_line "get that far."
        t_done )
};
const txt_cmd_s Executivef1SeenText[] = {
    text_start("Remember me from"
        t_line "the HIDEOUT in"
        t_cont "MAHOGANY TOWN?"
        t_para "I lost then, but I"
        t_line "won't this time."
        t_done )
};
const txt_cmd_s Executivef1BeatenText[] = {
    text_start("This can't be"
        t_line "happening!"
        t_para "I fought hard, but"
        t_line "I still lost…"
        t_done )
};
const txt_cmd_s Executivef1AfterBattleText[] = {
    text_start("<PLAYER>, isn't it?"
        t_para "A brat like you"
        t_line "won't appreciate"
        t_para "the magnificence"
        t_line "of TEAM ROCKET."
        t_para "That's too bad."
        t_line "I really admire"
        t_cont "your power."
        t_done )
};
const txt_cmd_s RadioTower5FRocketBossBeforeText[] = {
    text_start("Oh? You managed to"
        t_line "get this far?"
        t_para "You must be quite"
        t_line "the trainer."
        t_para "We intend to take"
        t_line "over this RADIO"
        t_para "STATION and an-"
        t_line "nounce our come-"
        t_cont "back."
        t_para "That should bring"
        t_line "our boss GIOVANNI"
        t_para "back from his solo"
        t_line "training."
        t_para "We are going to"
        t_line "regain our former"
        t_cont "glory."
        t_para "I won't allow you"
        t_line "to interfere with"
        t_cont "our plans."
        t_done )
};
const txt_cmd_s RadioTower5FRocketBossWinText[] = {
    text_start("No! Forgive me,"
        t_line "GIOVANNI!"
        t_done )
};
const txt_cmd_s RadioTower5FRocketBossAfterText[] = {
    text_start("How could this be?"
        t_para "Our dreams have"
        t_line "come to naught."
        t_para "I wasn't up to the"
        t_line "task after all."
        t_para "Like GIOVANNI did"
        t_line "before me, I will"
        t_para "disband TEAM"
        t_line "ROCKET here today."
        t_para "Farewell."
        t_done )
};
const txt_cmd_s RadioTower5FDirectorThankYouText[] = {
    text_start("DIRECTOR: <PLAY_G>,"
        t_line "thank you!"
        t_para "Your courageous"
        t_line "actions have saved"
        t_para "#MON nation-"
        t_line "wide."
        t_para "I know it's not"
        t_line "much, but please"
        t_cont "take this."
        t_done )
};
const txt_cmd_s RadioTower5FDirectorDescribeClearBellText[] = {
    text_start("There used to be a"
        t_line "tower right here"
        t_cont "in GOLDENROD CITY."
        t_para "But it was old and"
        t_line "creaky."
        t_para "So we replaced it"
        t_line "with our RADIO"
        t_cont "TOWER."
        t_para "We dug up that"
        t_line "bell during"
        t_cont "construction."
        t_para "I heard that all"
        t_line "sorts of #MON"
        t_para "lived in GOLDENROD"
        t_line "in the past."
        t_para "Perhaps…"
        t_para "That bell has some"
        t_line "connection to the"
        t_para "TIN TOWER in"
        t_line "ECRUTEAK CITY…"
        t_para "Ah!"
        t_para "That reminds me…"
        t_para "I overheard TEAM"
        t_line "ROCKET whispering."
        t_para "Apparently, some-"
        t_line "thing is going on"
        t_cont "at the TIN TOWER."
        t_para "I have no idea"
        t_line "what is happening,"
        t_para "but you might look"
        t_line "into it."
        t_para "OK, I better go to"
        t_line "my OFFICE."
        t_done )
};
const txt_cmd_s RadioTower5FDirectorText[] = {
    text_start("DIRECTOR: Hello,"
        t_line "<PLAY_G>!"
        t_para "You know, I love"
        t_line "#MON."
        t_para "I built this RADIO"
        t_line "TOWER so I could"
        t_para "express my love"
        t_line "of #MON."
        t_para "It would be nice"
        t_line "if people enjoyed"
        t_cont "our programs."
        t_done )
};
const txt_cmd_s BenText[] = {
    text_start("BEN: Do you listen"
        t_line "to our music?"
        t_done )
};
const txt_cmd_s RadioTower5FDirectorsOfficeSignText[] = {
    text_start("5F DIRECTOR'S"
        t_line "   OFFICE"
        t_done )
};
const txt_cmd_s RadioTower5FStudio1SignText[] = {
    text_start("5F STUDIO 1"
        t_done )
    //db(0, 0) // filler
};
