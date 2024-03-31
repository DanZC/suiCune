#include "../constants.h"
#include "../home/map.h"
#include "../util/scripting.h"
#include "../engine/events/std_scripts.h"
#include "CherrygroveCity.h"
//// EVENTS
enum {
    CHERRYGROVECITY_GRAMPS = 2,
    CHERRYGROVECITY_SILVER,
    CHERRYGROVECITY_TEACHER,
    CHERRYGROVECITY_YOUNGSTER,
    CHERRYGROVECITY_FISHER,
};

const Script_fn_t CherrygroveCity_SceneScripts[] = {
    CherrygroveCity_MapScripts_DummyScene0 , //  SCENE_CHERRYGROVECITY_NOTHING,
    CherrygroveCity_MapScripts_DummyScene1 , //  SCENE_CHERRYGROVECITY_MEET_RIVAL,
};

const struct MapCallback CherrygroveCity_MapCallbacks[] = {
    map_callback(MAPCALLBACK_NEWMAP, CherrygroveCity_MapScripts_FlyPoint),
};

const struct MapScripts CherrygroveCity_MapScripts = {
    .scene_script_count = lengthof(CherrygroveCity_SceneScripts),
    .scene_scripts = CherrygroveCity_SceneScripts,

    .callback_count = lengthof(CherrygroveCity_MapCallbacks),
    .callbacks = CherrygroveCity_MapCallbacks,
};

static const struct CoordEvent CherrygroveCity_CoordEvents[] = {
    coord_event(33, 6, SCENE_CHERRYGROVECITY_MEET_RIVAL, CherrygroveSilverSceneNorth),
    coord_event(33, 7, SCENE_CHERRYGROVECITY_MEET_RIVAL, CherrygroveSilverSceneSouth),
};

static const struct BGEvent CherrygroveCity_BGEvents[] = {
    bg_event(30, 8, BGEVENT_READ, CherrygroveCitySign),
    bg_event(23, 9, BGEVENT_READ, GuideGentsHouseSign),
    bg_event(24, 3, BGEVENT_READ, CherrygroveCityMartSign),
    bg_event(30, 3, BGEVENT_READ, CherrygroveCityPokecenterSign),
};

static const struct WarpEventData CherrygroveCity_WarpEvents[] = {
    warp_event(23, 3, CHERRYGROVE_MART, 2),
    warp_event(29, 3, CHERRYGROVE_POKECENTER_1F, 1),
    warp_event(17, 7, CHERRYGROVE_GYM_SPEECH_HOUSE, 1),
    warp_event(25, 9, GUIDE_GENTS_HOUSE, 1),
    warp_event(31, 11, CHERRYGROVE_EVOLUTION_SPEECH_HOUSE, 1),
};

static const struct ObjEvent CherrygroveCity_ObjectEvents[] = {
    object_event(32, 6, SPRITE_GRAMPS, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, CherrygroveCityGuideGent, EVENT_GUIDE_GENT_IN_HIS_HOUSE),
    object_event(39, 6, SPRITE_SILVER, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, ObjectEvent, EVENT_RIVAL_CHERRYGROVE_CITY),
    object_event(27, 12, SPRITE_TEACHER, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, CherrygroveTeacherScript, -1),
    object_event(23, 7, SPRITE_YOUNGSTER, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, CherrygroveYoungsterScript, -1),
    object_event(7, 12, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, MysticWaterGuy, -1),
};

const struct MapEvents CherrygroveCity_MapEvents = {
    .warp_event_count = lengthof(CherrygroveCity_WarpEvents),
    .warp_events = CherrygroveCity_WarpEvents,

    .coord_event_count = lengthof(CherrygroveCity_CoordEvents),
    .coord_events = CherrygroveCity_CoordEvents,

    .bg_event_count = lengthof(CherrygroveCity_BGEvents),
    .bg_events = CherrygroveCity_BGEvents,

    .obj_event_count = lengthof(CherrygroveCity_ObjectEvents),
    .obj_events = CherrygroveCity_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "CherrygroveCity.h"

bool CherrygroveCity_MapScripts_DummyScene0(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool CherrygroveCity_MapScripts_DummyScene1(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool CherrygroveCity_MapScripts_FlyPoint(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_FLYPOINT_CHERRYGROVE)
    s_endcallback
    SCRIPT_END
}
const char mapcardname[] = "MAP CARD@";
bool CherrygroveCityGuideGent(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(GuideGentIntroText)
    yesorno
    iffalse(No)
    goto Yes;
Yes:
    writetext(GuideGentTourText1)
    waitbutton
    closetext
    playmusic(MUSIC_SHOW_ME_AROUND)
    follow(CHERRYGROVECITY_GRAMPS, PLAYER)
    applymovement(CHERRYGROVECITY_GRAMPS, GuideGentMovement1)
    opentext
    writetext(GuideGentPokecenterText)
    waitbutton
    closetext
    applymovement(CHERRYGROVECITY_GRAMPS, GuideGentMovement2)
    turnobject(PLAYER, UP)
    opentext
    writetext(GuideGentMartText)
    waitbutton
    closetext
    applymovement(CHERRYGROVECITY_GRAMPS, GuideGentMovement3)
    turnobject(PLAYER, UP)
    opentext
    writetext(GuideGentRoute30Text)
    waitbutton
    closetext
    applymovement(CHERRYGROVECITY_GRAMPS, GuideGentMovement4)
    turnobject(PLAYER, LEFT)
    opentext
    writetext(GuideGentSeaText)
    waitbutton
    closetext
    applymovement(CHERRYGROVECITY_GRAMPS, GuideGentMovement5)
    turnobject(PLAYER, UP)
    pause(60)
    turnobject(CHERRYGROVECITY_GRAMPS, LEFT)
    turnobject(PLAYER, RIGHT)
    opentext
    writetext(GuideGentGiftText)
    promptbutton
    getstring(STRING_BUFFER_4, mapcardname)
    scall_local(JumpstdReceiveItem);
    setflag(ENGINE_MAP_CARD)
    writetext(GotMapCardText)
    promptbutton
    writetext(GuideGentPokegearText)
    waitbutton
    closetext
    stopfollow
    special(RestartMapMusic)
    turnobject(PLAYER, UP)
    applymovement(CHERRYGROVECITY_GRAMPS, GuideGentMovement6)
    playsound(SFX_ENTER_DOOR)
    disappear(CHERRYGROVECITY_GRAMPS)
    clearevent(EVENT_GUIDE_GENT_VISIBLE_IN_CHERRYGROVE)
    waitsfx
    s_end
JumpstdReceiveItem:
    jumpstd(ReceiveItemScript)
    s_end
No:
    writetext(GuideGentNoText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool CherrygroveSilverSceneSouth(script_s* s) {
    SCRIPT_BEGIN
    moveobject(CHERRYGROVECITY_SILVER, 39, 7)
    SCRIPT_FALLTHROUGH(CherrygroveSilverSceneNorth)
}
bool CherrygroveSilverSceneNorth(script_s* s) {
    SCRIPT_BEGIN
    turnobject(PLAYER, RIGHT)
    showemote(EMOTE_SHOCK, PLAYER, 15)
    special(FadeOutMusic)
    pause(15)
    appear(CHERRYGROVECITY_SILVER)
    applymovement(CHERRYGROVECITY_SILVER, CherrygroveCity_RivalWalksToYou)
    turnobject(PLAYER, RIGHT)
    playmusic(MUSIC_RIVAL_ENCOUNTER)
    opentext
    writetext(CherrygroveRivalText_Seen)
    waitbutton
    closetext
    checkevent(EVENT_GOT_TOTODILE_FROM_ELM)
    iftrue(Totodile)
    checkevent(EVENT_GOT_CHIKORITA_FROM_ELM)
    iftrue(Chikorita)
    printf("Cyndaquil.");
    winlosstext(SilverCherrygroveWinText, SilverCherrygroveLossText)
    setlasttalked(CHERRYGROVECITY_SILVER)
    loadtrainer(RIVAL1, RIVAL1_1_TOTODILE)
    loadvar(VAR_BATTLETYPE, BATTLETYPE_CANLOSE)
    startbattle
    dontrestartmapmusic
    reloadmap
    iftrue(AfterVictorious)
    goto AfterYourDefeat;
Totodile:
    printf("Totodile.");
    winlosstext(SilverCherrygroveWinText, SilverCherrygroveLossText)
    setlasttalked(CHERRYGROVECITY_SILVER)
    loadtrainer(RIVAL1, RIVAL1_1_CHIKORITA)
    loadvar(VAR_BATTLETYPE, BATTLETYPE_CANLOSE)
    startbattle
    dontrestartmapmusic
    reloadmap
    iftrue(AfterVictorious)
    goto AfterYourDefeat;
Chikorita:
    printf("Chikorita.");
    winlosstext(SilverCherrygroveWinText, SilverCherrygroveLossText)
    setlasttalked(CHERRYGROVECITY_SILVER)
    loadtrainer(RIVAL1, RIVAL1_1_CYNDAQUIL)
    loadvar(VAR_BATTLETYPE, BATTLETYPE_CANLOSE)
    startbattle
    dontrestartmapmusic
    reloadmap
    iftrue(AfterVictorious)
    goto AfterYourDefeat;
AfterVictorious:
    playmusic(MUSIC_RIVAL_AFTER)
    opentext
    writetext(CherrygroveRivalText_YouWon)
    waitbutton
    closetext
    goto FinishRival;
AfterYourDefeat:
    playmusic(MUSIC_RIVAL_AFTER)
    opentext
    writetext(CherrygroveRivalText_YouLost)
    waitbutton
    closetext
FinishRival:
    playsound(SFX_TACKLE)
    applymovement(PLAYER, CherrygroveCity_RivalPushesYouOutOfTheWay)
    turnobject(PLAYER, LEFT)
    applymovement(CHERRYGROVECITY_SILVER, CherrygroveCity_RivalExitsStageLeft)
    disappear(CHERRYGROVECITY_SILVER)
    setscene(SCENE_CHERRYGROVECITY_NOTHING)
    special(HealParty)
    playmapmusic
    s_end
    SCRIPT_END
}
bool CherrygroveTeacherScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkflag(ENGINE_MAP_CARD)
    iftrue(HaveMapCard)
    writetext(CherrygroveTeacherText_NoMapCard)
    waitbutton
    closetext
    s_end
HaveMapCard:
    writetext(CherrygroveTeacherText_HaveMapCard)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool CherrygroveYoungsterScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkflag(ENGINE_POKEDEX)
    iftrue(HavePokedex)
    writetext(CherrygroveYoungsterText_NoPokedex)
    waitbutton
    closetext
    s_end
HavePokedex:
    writetext(CherrygroveYoungsterText_HavePokedex)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool MysticWaterGuy(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_MYSTIC_WATER_IN_CHERRYGROVE)
    iftrue(After)
    writetext(MysticWaterGuyTextBefore)
    promptbutton
    verbosegiveitem(MYSTIC_WATER, 1)
    iffalse(Exit)
    setevent(EVENT_GOT_MYSTIC_WATER_IN_CHERRYGROVE)
After:
    writetext(MysticWaterGuyTextAfter)
    waitbutton
Exit:
    closetext
    s_end
    SCRIPT_END
}
bool CherrygroveCitySign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(CherrygroveCitySignText)
    SCRIPT_END
}
bool GuideGentsHouseSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(GuideGentsHouseSignText)
    SCRIPT_END
}
bool CherrygroveCityPokecenterSign(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PokecenterSignScript)
    SCRIPT_END
}
bool CherrygroveCityMartSign(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(MartSignScript)
    SCRIPT_END
}
const uint8_t GuideGentMovement1[] = {
    step(LEFT),
    step(LEFT),
    step(UP),
    step(LEFT),
    turn_head(UP),
    movement_step_end,
};
const uint8_t GuideGentMovement2[] = {
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    turn_head(UP),
    movement_step_end,
};
const uint8_t GuideGentMovement3[] = {
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    turn_head(UP),
    movement_step_end,
};
const uint8_t GuideGentMovement4[] = {
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(DOWN),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(DOWN),
    turn_head(LEFT),
    movement_step_end,
};
const uint8_t GuideGentMovement5[] = {
    step(DOWN),
    step(DOWN),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    step(DOWN),
    step(DOWN),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    turn_head(UP),
    movement_step_end,
};
const uint8_t GuideGentMovement6[] = {
    step(UP),
    step(UP),
    movement_step_end,
};
const uint8_t CherrygroveCity_RivalWalksToYou[] = {
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    movement_step_end,
};
const uint8_t CherrygroveCity_RivalPushesYouOutOfTheWay[] = {
    big_step(DOWN),
    turn_head(UP),
    movement_step_end,
};
const uint8_t CherrygroveCity_UnusedMovementData[] = {
    step(LEFT),
    turn_head(DOWN),
    movement_step_end,
};
const uint8_t CherrygroveCity_RivalExitsStageLeft[] = {
    big_step(LEFT),
    big_step(LEFT),
    big_step(LEFT),
    big_step(LEFT),
    big_step(UP),
    big_step(UP),
    big_step(LEFT),
    big_step(LEFT),
    movement_step_end,
};
const txt_cmd_s GuideGentIntroText[] = {
    text_start("You're a rookie"
        t_line "trainer, aren't"
        t_cont "you? I can tell!"
        t_para "That's OK! Every-"
        t_line "one is a rookie"
        t_cont "at some point!"
        t_para "If you'd like, I"
        t_line "can teach you a"
        t_cont "few things."
        t_done )
};
const txt_cmd_s GuideGentTourText1[] = {
    text_start("OK, then!"
        t_line "Follow me!"
        t_done )
};
const txt_cmd_s GuideGentPokecenterText[] = {
    text_start("This is a #MON"
        t_line "CENTER. They heal"
        t_para "your #MON in no"
        t_line "time at all."
        t_para "You'll be relying"
        t_line "on them a lot, so"
        t_para "you better learn"
        t_line "about them."
        t_done )
};
const txt_cmd_s GuideGentMartText[] = {
    text_start("This is a #MON"
        t_line "MART."
        t_para "They sell BALLS"
        t_line "for catching wild"
        t_para "#MON and other"
        t_line "useful items."
        t_done )
};
const txt_cmd_s GuideGentRoute30Text[] = {
    text_start("ROUTE 30 is out"
        t_line "this way."
        t_para "Trainers will be"
        t_line "battling their"
        t_para "prized #MON"
        t_line "there."
        t_done )
};
const txt_cmd_s GuideGentSeaText[] = {
    text_start("This is the sea,"
        t_line "as you can see."
        t_para "Some #MON are"
        t_line "found only in"
        t_cont "water."
        t_done )
};
const txt_cmd_s GuideGentGiftText[] = {
    text_start("Here…"
        t_para "It's my house!"
        t_line "Thanks for your"
        t_cont "company."
        t_para "Let me give you a"
        t_line "small gift."
        t_done )
};
const txt_cmd_s GotMapCardText[] = {
    text_start("<PLAYER>'s #GEAR"
        t_line "now has a MAP!"
        t_done )
};
const txt_cmd_s GuideGentPokegearText[] = {
    text_start("#GEAR becomes"
        t_line "more useful as you"
        t_cont "add CARDS."
        t_para "I wish you luck on"
        t_line "your journey!"
        t_done )
};
const txt_cmd_s GuideGentNoText[] = {
    text_start("Oh… It's something"
        t_line "I enjoy doing…"
        t_para "Fine. Come see me"
        t_line "when you like."
        t_done )
};
const txt_cmd_s CherrygroveRivalText_Seen[] = {
    text_start("<……> <……> <……>"
        t_para "You got a #MON"
        t_line "at the LAB."
        t_para "What a waste."
        t_line "A wimp like you."
        t_para "<……> <……> <……>"
        t_para "Don't you get what"
        t_line "I'm saying?"
        t_para "Well, I too, have"
        t_line "a good #MON."
        t_para "I'll show you"
        t_line "what I mean!"
        t_done )
};
const txt_cmd_s SilverCherrygroveWinText[] = {
    text_start("Humph. Are you"
        t_line "happy you won?"
        t_done )
};
const txt_cmd_s CherrygroveRivalText_YouLost[] = {
    text_start("<……> <……> <……>"
        t_para "My name's ???."
        t_para "I'm going to be"
        t_line "the world's great-"
        t_cont "est #MON"
        t_cont "trainer."
        t_done )
};
const txt_cmd_s SilverCherrygroveLossText[] = {
    text_start("Humph. That was a"
        t_line "waste of time."
        t_done )
};
const txt_cmd_s CherrygroveRivalText_YouWon[] = {
    text_start("<……> <……> <……>"
        t_para "My name's ???."
        t_para "I'm going to be"
        t_line "the world's great-"
        t_cont "est #MON"
        t_cont "trainer."
        t_done )
};
const txt_cmd_s CherrygroveTeacherText_NoMapCard[] = {
    text_start("Did you talk to"
        t_line "the old man by the"
        t_cont "#MON CENTER?"
        t_para "He'll put a MAP of"
        t_line "JOHTO on your"
        t_cont "#GEAR."
        t_done )
};
const txt_cmd_s CherrygroveTeacherText_HaveMapCard[] = {
    text_start("When you're with"
        t_line "#MON, going"
        t_cont "anywhere is fun."
        t_done )
};
const txt_cmd_s CherrygroveYoungsterText_NoPokedex[] = {
    text_start("MR.#MON's house"
        t_line "is still farther"
        t_cont "up ahead."
        t_done )
};
const txt_cmd_s CherrygroveYoungsterText_HavePokedex[] = {
    text_start("I battled the"
        t_line "trainers on the"
        t_cont "road."
        t_para "My #MON lost."
        t_line "They're a mess! I"
        t_para "must take them to"
        t_line "a #MON CENTER."
        t_done )
};
const txt_cmd_s MysticWaterGuyTextBefore[] = {
    text_start("A #MON I caught"
        t_line "had an item."
        t_para "I think it's"
        t_line "MYSTIC WATER."
        t_para "I don't need it,"
        t_line "so do you want it?"
        t_done )
};
const txt_cmd_s MysticWaterGuyTextAfter[] = {
    text_start("Back to fishing"
        t_line "for me, then."
        t_done )
};
const txt_cmd_s CherrygroveCitySignText[] = {
    text_start("CHERRYGROVE CITY"
        t_para "The City of Cute,"
        t_line "Fragrant Flowers"
        t_done )
};
const txt_cmd_s GuideGentsHouseSignText[] = {
    text_start("GUIDE GENT'S HOUSE"
        t_done )
    //db(0, 0) // filler
};
