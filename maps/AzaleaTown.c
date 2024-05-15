#include "../constants.h"
#include "../util/scripting.h"
#include "AzaleaTown.h"
//// EVENTS
enum {
    AZALEATOWN_AZALEA_ROCKET1 = 2,
    AZALEATOWN_GRAMPS,
    AZALEATOWN_TEACHER,
    AZALEATOWN_YOUNGSTER,
    AZALEATOWN_SLOWPOKE1,
    AZALEATOWN_SLOWPOKE2,
    AZALEATOWN_SLOWPOKE3,
    AZALEATOWN_SLOWPOKE4,
    AZALEATOWN_FRUIT_TREE,
    AZALEATOWN_SILVER,
    AZALEATOWN_AZALEA_ROCKET3,
    AZALEATOWN_KURT_OUTSIDE,
};

const Script_fn_t AzaleaTown_SceneScripts[] = {
    AzaleaTown_MapScripts_DummyScene0 , //  SCENE_AZALEATOWN_NOTHING,
    AzaleaTown_MapScripts_DummyScene1 , //  SCENE_AZALEATOWN_RIVAL_BATTLE,
    AzaleaTown_MapScripts_DummyScene2 , //  SCENE_AZALEATOWN_KURT_RETURNS_GS_BALL,
};

const struct MapCallback AzaleaTown_MapCallbacks[] = {
    map_callback(MAPCALLBACK_NEWMAP, AzaleaTown_MapScripts_Flypoint),
};

const struct MapScripts AzaleaTown_MapScripts = {
    .scene_script_count = lengthof(AzaleaTown_SceneScripts),
    .scene_scripts = AzaleaTown_SceneScripts,

    .callback_count = lengthof(AzaleaTown_MapCallbacks),
    .callbacks = AzaleaTown_MapCallbacks,
};

static const struct CoordEvent AzaleaTown_CoordEvents[] = {
    coord_event(5, 10, SCENE_AZALEATOWN_RIVAL_BATTLE, &AzaleaTownRivalBattleScene1),
    coord_event(5, 11, SCENE_AZALEATOWN_RIVAL_BATTLE, &AzaleaTownRivalBattleScene2),
    coord_event(9, 6, SCENE_AZALEATOWN_KURT_RETURNS_GS_BALL, &AzaleaTownCelebiScene),
};

static const struct BGEvent AzaleaTown_BGEvents[] = {
    bg_event(19, 9, BGEVENT_READ, &AzaleaTownSign),
    bg_event(10, 9, BGEVENT_READ, &KurtsHouseSign),
    bg_event(14, 15, BGEVENT_READ, &AzaleaGymSign),
    bg_event(29, 7, BGEVENT_READ, &SlowpokeWellSign),
    bg_event(19, 13, BGEVENT_READ, &CharcoalKilnSign),
    bg_event(16, 9, BGEVENT_READ, &AzaleaTownPokecenterSign),
    bg_event(22, 5, BGEVENT_READ, &AzaleaTownMartSign),
    bg_event(3, 9, BGEVENT_READ, &AzaleaTownIlextForestSign),
    bg_event(31, 6, BGEVENT_ITEM, &AzaleaTownHiddenFullHeal),
};

static const struct WarpEventData AzaleaTown_WarpEvents[] = {
    warp_event(15, 9, AZALEA_POKECENTER_1F, 1),
    warp_event(21, 13, CHARCOAL_KILN, 1),
    warp_event(21, 5, AZALEA_MART, 2),
    warp_event(9, 5, KURTS_HOUSE, 1),
    warp_event(10, 15, AZALEA_GYM, 1),
    warp_event(31, 7, SLOWPOKE_WELL_B1F, 1),
    warp_event(2, 10, ILEX_FOREST_AZALEA_GATE, 3),
    warp_event(2, 11, ILEX_FOREST_AZALEA_GATE, 4),
};

static const struct ObjEvent AzaleaTown_ObjectEvents[] = {
    object_event(31, 9, SPRITE_AZALEA_ROCKET, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &AzaleaTownRocket1Script, EVENT_AZALEA_TOWN_SLOWPOKETAIL_ROCKET),
    object_event(21, 9, SPRITE_GRAMPS, SPRITEMOVEDATA_WANDER, 1, 2, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &AzaleaTownGrampsScript, -1),
    object_event(15, 13, SPRITE_TEACHER, SPRITEMOVEDATA_WALK_UP_DOWN, 0, 2, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &AzaleaTownTeacherScript, -1),
    object_event(7, 9, SPRITE_YOUNGSTER, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &AzaleaTownYoungsterScript, -1),
    object_event(8, 17, SPRITE_SLOWPOKE, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &AzaleaTownSlowpokeScript, EVENT_AZALEA_TOWN_SLOWPOKES),
    object_event(18, 9, SPRITE_SLOWPOKE, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &AzaleaTownSlowpokeScript, EVENT_AZALEA_TOWN_SLOWPOKES),
    object_event(29, 9, SPRITE_SLOWPOKE, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &AzaleaTownSlowpokeScript, EVENT_AZALEA_TOWN_SLOWPOKES),
    object_event(15, 15, SPRITE_SLOWPOKE, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &AzaleaTownSlowpokeScript, EVENT_AZALEA_TOWN_SLOWPOKES),
    object_event(8, 2, SPRITE_FRUIT_TREE, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &WhiteApricornTree, -1),
    object_event(11, 10, SPRITE_AZALEA_ROCKET, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, EVENT_RIVAL_AZALEA_TOWN),
    object_event(10, 16, SPRITE_AZALEA_ROCKET, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &AzaleaTownRocket2Script, EVENT_SLOWPOKE_WELL_ROCKETS),
    object_event(6, 5, SPRITE_KURT_OUTSIDE, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &AzaleaTownKurtScript, EVENT_AZALEA_TOWN_KURT),
};

const struct MapEvents AzaleaTown_MapEvents = {
    .warp_event_count = lengthof(AzaleaTown_WarpEvents),
    .warp_events = AzaleaTown_WarpEvents,

    .coord_event_count = lengthof(AzaleaTown_CoordEvents),
    .coord_events = AzaleaTown_CoordEvents,

    .bg_event_count = lengthof(AzaleaTown_BGEvents),
    .bg_events = AzaleaTown_BGEvents,

    .obj_event_count = lengthof(AzaleaTown_ObjectEvents),
    .obj_events = AzaleaTown_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "AzaleaTown.h"

bool AzaleaTown_MapScripts_DummyScene0(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool AzaleaTown_MapScripts_DummyScene1(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool AzaleaTown_MapScripts_DummyScene2(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool AzaleaTown_MapScripts_Flypoint(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_FLYPOINT_AZALEA)
    s_endcallback
    SCRIPT_END
}
bool AzaleaTownRivalBattleScene1(script_s* s) {
    SCRIPT_BEGIN
    moveobject(AZALEATOWN_SILVER, 11, 11)
    turnobject(PLAYER, RIGHT)
    showemote(EMOTE_SHOCK, PLAYER, 15)
    special(FadeOutMusic)
    pause(15)
    appear(AZALEATOWN_SILVER)
    applymovement(AZALEATOWN_SILVER, AzaleaTownRivalBattleApproachMovement1)
    turnobject(PLAYER, DOWN)
    sjump(AzaleaTownRivalBattleScript)
    SCRIPT_END
}
bool AzaleaTownRivalBattleScene2(script_s* s) {
    SCRIPT_BEGIN
    turnobject(PLAYER, RIGHT)
    showemote(EMOTE_SHOCK, PLAYER, 15)
    special(FadeOutMusic)
    pause(15)
    appear(AZALEATOWN_SILVER)
    applymovement(AZALEATOWN_SILVER, AzaleaTownRivalBattleApproachMovement2)
    turnobject(PLAYER, UP)
    SCRIPT_FALLTHROUGH(AzaleaTownRivalBattleScript)
}
bool AzaleaTownRivalBattleScript(script_s* s) {
    SCRIPT_BEGIN
    playmusic(MUSIC_RIVAL_ENCOUNTER)
    opentext
    writetext(AzaleaTownRivalBeforeText)
    waitbutton
    closetext
    setevent(EVENT_RIVAL_AZALEA_TOWN)
    checkevent(EVENT_GOT_TOTODILE_FROM_ELM)
    iftrue(Totodile)
    checkevent(EVENT_GOT_CHIKORITA_FROM_ELM)
    iftrue(Chikorita)
    winlosstext(AzaleaTownRivalWinText, AzaleaTownRivalLossText)
    setlasttalked(AZALEATOWN_SILVER)
    loadtrainer(RIVAL1, RIVAL1_2_TOTODILE)
    startbattle
    dontrestartmapmusic
    reloadmapafterbattle
    goto AfterBattle;
Totodile:
    winlosstext(AzaleaTownRivalWinText, AzaleaTownRivalLossText)
    setlasttalked(AZALEATOWN_SILVER)
    loadtrainer(RIVAL1, RIVAL1_2_CHIKORITA)
    startbattle
    dontrestartmapmusic
    reloadmapafterbattle
    goto AfterBattle;
Chikorita:
    winlosstext(AzaleaTownRivalWinText, AzaleaTownRivalLossText)
    setlasttalked(AZALEATOWN_SILVER)
    loadtrainer(RIVAL1, RIVAL1_2_CYNDAQUIL)
    startbattle
    dontrestartmapmusic
    reloadmapafterbattle
    goto AfterBattle;
AfterBattle:
    playmusic(MUSIC_RIVAL_AFTER)
    opentext
    writetext(AzaleaTownRivalAfterText)
    waitbutton
    closetext
    turnobject(PLAYER, LEFT)
    applymovement(AZALEATOWN_SILVER, AzaleaTownRivalBattleExitMovement)
    playsound(SFX_EXIT_BUILDING)
    disappear(AZALEATOWN_SILVER)
    setscene(SCENE_AZALEATOWN_NOTHING)
    waitsfx
    playmapmusic
    s_end
    SCRIPT_END
}
bool AzaleaTownRocket1Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(AzaleaTownRocket1Text)
    SCRIPT_END
}
bool AzaleaTownRocket2Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(AzaleaTownRocket2Text)
    SCRIPT_END
}
bool AzaleaTownGrampsScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_CLEARED_SLOWPOKE_WELL)
    iftrue(ClearedWell)
    writetext(AzaleaTownGrampsTextBefore)
    waitbutton
    closetext
    s_end
ClearedWell:
    writetext(AzaleaTownGrampsTextAfter)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool AzaleaTownTeacherScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(AzaleaTownTeacherText)
    SCRIPT_END
}
bool AzaleaTownYoungsterScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(AzaleaTownYoungsterText)
    SCRIPT_END
}
bool AzaleaTownSlowpokeScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(AzaleaTownSlowpokeText1)
    pause(60)
    writetext(AzaleaTownSlowpokeText2)
    playcry(SLOWPOKE)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool UnusedWoosterScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(WoosterText)
    playcry(QUAGSIRE)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool AzaleaTownCelebiScene(script_s* s) {
    SCRIPT_BEGIN
    applymovement(PLAYER, AzaleaTownPlayerLeavesKurtsHouseMovement)
    opentext
    writetext(AzaleaTownKurtText1)
    promptbutton
    turnobject(AZALEATOWN_KURT_OUTSIDE, RIGHT)
    writetext(AzaleaTownKurtText2)
    promptbutton
    writetext(AzaleaTownKurtText3)
    waitbutton
    verbosegiveitem(GS_BALL, 1)
    turnobject(AZALEATOWN_KURT_OUTSIDE, LEFT)
    setflag(ENGINE_FOREST_IS_RESTLESS)
    clearevent(EVENT_ILEX_FOREST_LASS)
    setevent(EVENT_ROUTE_34_ILEX_FOREST_GATE_LASS)
    setscene(SCENE_AZALEATOWN_NOTHING)
    closetext
    s_end
    SCRIPT_END
}
bool AzaleaTownKurtScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(AzaleaTownKurtText3)
    waitbutton
    turnobject(AZALEATOWN_KURT_OUTSIDE, LEFT)
    closetext
    s_end
    SCRIPT_END
}
bool AzaleaTownSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(AzaleaTownSignText)
    SCRIPT_END
}
bool KurtsHouseSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(KurtsHouseSignText)
    SCRIPT_END
}
bool AzaleaGymSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(AzaleaGymSignText)
    SCRIPT_END
}
bool SlowpokeWellSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(SlowpokeWellSignText)
    SCRIPT_END
}
bool CharcoalKilnSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(CharcoalKilnSignText)
    SCRIPT_END
}
bool AzaleaTownIlextForestSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(AzaleaTownIlexForestSignText)
    SCRIPT_END
}
bool AzaleaTownPokecenterSign(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PokecenterSignScript)
    SCRIPT_END
}
bool AzaleaTownMartSign(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(MartSignScript)
    SCRIPT_END
}
bool WhiteApricornTree(script_s* s) {
    SCRIPT_BEGIN
    fruittree(FRUITTREE_AZALEA_TOWN)
    SCRIPT_END
}
const struct HiddenItem AzaleaTownHiddenFullHeal = {FULL_HEAL, EVENT_AZALEA_TOWN_HIDDEN_FULL_HEAL};
const uint8_t AzaleaTownRivalBattleApproachMovement1[] = {
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    turn_head(UP),
    movement_step_end,
};
const uint8_t AzaleaTownRivalBattleApproachMovement2[] = {
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    turn_head(DOWN),
    movement_step_end,
};
const uint8_t AzaleaTownRivalBattleExitMovement[] = {
    step(LEFT),
    step(LEFT),
    step(LEFT),
    movement_step_end,
};
const uint8_t AzaleaTownPlayerLeavesKurtsHouseMovement[] = {
    step(LEFT),
    step(LEFT),
    step(UP),
    turn_head(LEFT),
    movement_step_end,
};
const txt_cmd_s AzaleaTownRivalBeforeText[] = {
    text_start("…Tell me some-"
        t_line "thing."
        t_para "Is it true that"
        t_line "TEAM ROCKET has"
        t_cont "returned?"
        t_para "What? You beat"
        t_line "them? Hah! Quit"
        t_cont "lying."
        t_para "You're not joking?"
        t_line "Then let's see how"
        t_cont "good you are."
        t_done )
};
const txt_cmd_s AzaleaTownRivalWinText[] = {
    text_start("… Humph! Useless"
        t_line "#MON!"
        t_para "Listen, you. You"
        t_line "only won because"
        t_para "my #MON were"
        t_line "weak."
        t_done )
};
const txt_cmd_s AzaleaTownRivalAfterText[] = {
    text_start("I hate the weak."
        t_para "#MON, trainers."
        t_line "It doesn't matter"
        t_cont "who or what."
        t_para "I'm going to be"
        t_line "strong and wipe"
        t_cont "out the weak."
        t_para "That goes for TEAM"
        t_line "ROCKET too."
        t_para "They act big and"
        t_line "tough in a group."
        t_para "But get them"
        t_line "alone, and they're"
        t_cont "weak."
        t_para "I hate them all."
        t_para "You stay out of my"
        t_line "way. A weakling"
        t_para "like you is only a"
        t_line "distraction."
        t_done )
};
const txt_cmd_s AzaleaTownRivalLossText[] = {
    text_start("…Humph! I knew"
        t_line "you were lying."
        t_done )
};
const txt_cmd_s AzaleaTownRocket1Text[] = {
    text_start("It's unsafe to go"
        t_line "in there, so I'm"
        t_cont "standing guard."
        t_para "Aren't I a good"
        t_line "Samaritan?"
        t_done )
};
const txt_cmd_s AzaleaTownRocket2Text[] = {
    text_start("Do you know about"
        t_line "SLOWPOKETAIL? I"
        t_cont "heard it's tasty!"
        t_para "Aren't you glad I"
        t_line "told you that?"
        t_done )
};
const txt_cmd_s AzaleaTownGrampsTextBefore[] = {
    text_start("The SLOWPOKE have"
        t_line "disappeared from"
        t_cont "town…"
        t_para "I heard their"
        t_line "TAILS are being"
        t_cont "sold somewhere."
        t_done )
};
const txt_cmd_s AzaleaTownGrampsTextAfter[] = {
    text_start("The SLOWPOKE have"
        t_line "returned."
        t_para "Knowing them, they"
        t_line "could've just been"
        t_para "goofing off some-"
        t_line "where."
        t_done )
};
const txt_cmd_s AzaleaTownTeacherText[] = {
    text_start("Did you come to"
        t_line "get KURT to make"
        t_cont "some BALLS?"
        t_para "A lot of people do"
        t_line "just that."
        t_done )
};
const txt_cmd_s AzaleaTownYoungsterText[] = {
    text_start("Cut through AZALEA"
        t_line "and you'll be in"
        t_cont "ILEX FOREST."
        t_para "But these skinny"
        t_line "trees make it"
        t_para "impossible to get"
        t_line "through."
        t_para "The CHARCOAL MAN's"
        t_line "#MON can CUT"
        t_cont "down trees."
        t_done )
};
const txt_cmd_s AzaleaTownSlowpokeText1[] = {
    text_start("SLOWPOKE: …"
        t_para "<……> <……> <……>"
        t_done )
};
const txt_cmd_s AzaleaTownSlowpokeText2[] = {
    text_start("<……> <……>Yawn?"
        t_done )
};
const txt_cmd_s WoosterText[] = {
    text_start("WOOSTER: Gugyoo…"
        t_done )
};
const txt_cmd_s AzaleaTownKurtText1[] = {
    text_start("ILEX FOREST is"
        t_line "restless!"
        t_para "What is going on?"
        t_done )
};
const txt_cmd_s AzaleaTownKurtText2[] = {
    text_start("<PLAYER>, here's"
        t_line "your GS BALL back!"
        t_done )
};
const txt_cmd_s AzaleaTownKurtText3[] = {
    text_start("Could you go see"
        t_line "why ILEX FOREST is"
        t_cont "so restless?"
        t_done )
};
const txt_cmd_s AzaleaTownSignText[] = {
    text_start("AZALEA TOWN"
        t_line "Where People and"
        t_para "#MON Live in"
        t_line "Happy Harmony"
        t_done )
};
const txt_cmd_s KurtsHouseSignText[] = {
    text_start("KURT'S HOUSE"
        t_done )
};
const txt_cmd_s AzaleaGymSignText[] = {
    text_start("AZALEA TOWN"
        t_line "#MON GYM"
        t_cont "LEADER: BUGSY"
        t_para "The Walking"
        t_line "Bug #MON"
        t_cont "Encyclopedia"
        t_done )
};
const txt_cmd_s SlowpokeWellSignText[] = {
    text_start("SLOWPOKE WELL"
        t_para "Also known as the"
        t_line "RAINMAKER WELL."
        t_para "Locals believe"
        t_line "that a SLOWPOKE's"
        t_cont "yawn summons rain."
        t_para "Records show that"
        t_line "a SLOWPOKE's yawn"
        t_para "ended a drought"
        t_line "400 years ago."
        t_done )
};
const txt_cmd_s CharcoalKilnSignText[] = {
    text_start("CHARCOAL KILN"
        t_done )
};
const txt_cmd_s AzaleaTownIlexForestSignText[] = {
    text_start("ILEX FOREST"
        t_para "Enter through the"
        t_line "gate."
        t_done )
    //db(0, 0) // filler
};
