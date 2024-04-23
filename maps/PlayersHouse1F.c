#include "../constants.h"
#include "../util/scripting.h"
#include "PlayersHouse1F.h"
//// EVENTS
enum {
    PLAYERSHOUSE1F_MOM1 = 2,
    PLAYERSHOUSE1F_MOM2,
    PLAYERSHOUSE1F_MOM3,
    PLAYERSHOUSE1F_MOM4,
    PLAYERSHOUSE1F_POKEFAN_F,
};

const Script_fn_t PlayersHouse1F_SceneScripts[] = {
    PlayersHouse1F_MapScripts_DummyScene0 , //  SCENE_DEFAULT,
    PlayersHouse1F_MapScripts_DummyScene1 , //  SCENE_FINISHED,
};

const struct MapCallback PlayersHouse1F_MapCallbacks[] = {
    0,
};

const struct MapScripts PlayersHouse1F_MapScripts = {
    .scene_script_count = lengthof(PlayersHouse1F_SceneScripts),
    .scene_scripts = PlayersHouse1F_SceneScripts,

    .callback_count = 0, // lengthof(PlayersHouse1F_MapCallbacks),
    .callbacks = PlayersHouse1F_MapCallbacks,
};

static const struct CoordEvent PlayersHouse1F_CoordEvents[] = {
    coord_event(8, 4, SCENE_DEFAULT, &MeetMomLeftScript),
    coord_event(9, 4, SCENE_DEFAULT, &MeetMomRightScript),
};

static const struct BGEvent PlayersHouse1F_BGEvents[] = {
    bg_event(0, 1, BGEVENT_READ, &PlayersHouse1FStoveScript),
    bg_event(1, 1, BGEVENT_READ, &PlayersHouse1FSinkScript),
    bg_event(2, 1, BGEVENT_READ, &PlayersHouse1FFridgeScript),
    bg_event(4, 1, BGEVENT_READ, &PlayersHouse1FTVScript),
};

static const struct WarpEventData PlayersHouse1F_WarpEvents[] = {
    warp_event(6, 7, NEW_BARK_TOWN, 2),
    warp_event(7, 7, NEW_BARK_TOWN, 2),
    warp_event(9, 0, PLAYERS_HOUSE_2F, 1),
};

static const struct ObjEvent PlayersHouse1F_ObjectEvents[] = {
    object_event(7, 4, SPRITE_MOM, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &MomScript, EVENT_PLAYERS_HOUSE_MOM_1),
    object_event(2, 2, SPRITE_MOM, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, MORN, 0, OBJECTTYPE_SCRIPT, 0, &MomScript, EVENT_PLAYERS_HOUSE_MOM_2),
    object_event(7, 4, SPRITE_MOM, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, DAY, 0, OBJECTTYPE_SCRIPT, 0, &MomScript, EVENT_PLAYERS_HOUSE_MOM_2),
    object_event(0, 2, SPRITE_MOM, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, NITE, 0, OBJECTTYPE_SCRIPT, 0, &MomScript, EVENT_PLAYERS_HOUSE_MOM_2),
    object_event(4, 4, SPRITE_POKEFAN_F, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &NeighborScript, EVENT_PLAYERS_HOUSE_1F_NEIGHBOR),
};

const struct MapEvents PlayersHouse1F_MapEvents = {
    .warp_event_count = lengthof(PlayersHouse1F_WarpEvents),
    .warp_events = PlayersHouse1F_WarpEvents,

    .coord_event_count = lengthof(PlayersHouse1F_CoordEvents),
    .coord_events = PlayersHouse1F_CoordEvents,

    .bg_event_count = lengthof(PlayersHouse1F_BGEvents),
    .bg_events = PlayersHouse1F_BGEvents,

    .obj_event_count = lengthof(PlayersHouse1F_ObjectEvents),
    .obj_events = PlayersHouse1F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "PlayersHouse1F.h"

bool PlayersHouse1F_MapScripts_DummyScene0(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool PlayersHouse1F_MapScripts_DummyScene1(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool MeetMomLeftScript(script_s* s) {
    SCRIPT_BEGIN
    setevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1)
    SCRIPT_FALLTHROUGH(MeetMomRightScript)
}
bool MeetMomRightScript(script_s* s) {
    SCRIPT_BEGIN
    playmusic(MUSIC_MOM)
    showemote(EMOTE_SHOCK, PLAYERSHOUSE1F_MOM1, 15)
    turnobject(PLAYER, LEFT)
    checkevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1)
    iffalse(OnRight)
    applymovement(PLAYERSHOUSE1F_MOM1, MomTurnsTowardPlayerMovement)
    sjump(MeetMomScript)
OnRight:
    applymovement(PLAYERSHOUSE1F_MOM1, MomWalksToPlayerMovement)
    SCRIPT_FALLTHROUGH(MeetMomScript)
}
bool MeetMomScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(ElmsLookingForYouText)
    promptbutton
    getstring(STRING_BUFFER_4, PokegearName)
    scall(PlayersHouse1FReceiveItemStd)
    setflag(ENGINE_POKEGEAR)
    setflag(ENGINE_PHONE_CARD)
    addcellnum(PHONE_MOM)
    setscene(SCENE_FINISHED)
    setevent(EVENT_PLAYERS_HOUSE_MOM_1)
    clearevent(EVENT_PLAYERS_HOUSE_MOM_2)
    writetext(MomGivesPokegearText)
    promptbutton
    special(SetDayOfWeek)
SetDayOfWeek:
    writetext(IsItDSTText)
    yesorno
    iffalse(WrongDay)
    special(InitialSetDSTFlag)
    yesorno
    iffalse(SetDayOfWeek)
    goto DayOfWeekDone;
WrongDay:
    special(InitialClearDSTFlag)
    yesorno
    iffalse(SetDayOfWeek)
DayOfWeekDone:
    writetext(ComeHomeForDSTText)
    yesorno
    iffalse(ExplainPhone)
    goto KnowPhone;
KnowPhone:
    writetext(KnowTheInstructionsText)
    promptbutton
    goto FinishPhone;
ExplainPhone:
    writetext(DontKnowTheInstructionsText)
    promptbutton
    goto FinishPhone;
FinishPhone:
    writetext(InstructionsNextText)
    waitbutton
    closetext
    checkevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1)
    iftrue(FromRight)
    checkevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2)
    iffalse(FromLeft)
    goto Finish;
FromRight:
    applymovement(PLAYERSHOUSE1F_MOM1, MomTurnsBackMovement)
    goto Finish;
FromLeft:
    applymovement(PLAYERSHOUSE1F_MOM1, MomWalksBackMovement)
    goto Finish;
Finish:
    special(RestartMapMusic)
    turnobject(PLAYERSHOUSE1F_MOM1, LEFT)
    s_end
    SCRIPT_END
}
bool MeetMomTalkedScript(script_s* s) {
    SCRIPT_BEGIN
    playmusic(MUSIC_MOM)
    sjump(MeetMomScript)
    SCRIPT_END
}
const char PokegearName[] = "#GEAR@";
bool PlayersHouse1FReceiveItemStd(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(ReceiveItemScript)
    s_end
    SCRIPT_END
}
bool MomScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    setevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2)
    checkscene
    iffalse_jump(MeetMomTalkedScript) // SCENE_DEFAULT
    opentext
    checkevent(EVENT_FIRST_TIME_BANKING_WITH_MOM)
    iftrue(FirstTimeBanking)
    checkevent(EVENT_TALKED_TO_MOM_AFTER_MYSTERY_EGG_QUEST)
    iftrue(BankOfMom)
    checkevent(EVENT_GAVE_MYSTERY_EGG_TO_ELM)
    iftrue(GaveMysteryEgg)
    checkevent(EVENT_GOT_A_POKEMON_FROM_ELM)
    iftrue(GotAPokemon)
    writetext(HurryUpElmIsWaitingText)
    waitbutton
    closetext
    s_end
GotAPokemon:
    writetext(SoWhatWasProfElmsErrandText)
    waitbutton
    closetext
    s_end
FirstTimeBanking:
    writetext(ImBehindYouText)
    waitbutton
    closetext
    s_end
GaveMysteryEgg:
    setevent(EVENT_FIRST_TIME_BANKING_WITH_MOM)
BankOfMom:
    setevent(EVENT_TALKED_TO_MOM_AFTER_MYSTERY_EGG_QUEST)
    special(BankOfMom)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool NeighborScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checktime(MORN)
    iftrue(MornScript)
    checktime(DAY)
    iftrue(DayScript)
    checktime(NITE)
    iftrue(NiteScript)
MornScript:
    writetext(NeighborMornIntroText)
    promptbutton
    goto Main;
DayScript:
    writetext(NeighborDayIntroText)
    promptbutton
    goto Main;
NiteScript:
    writetext(NeighborNiteIntroText)
    promptbutton
    goto Main;
Main:
    writetext(NeighborText)
    waitbutton
    closetext
    turnobject(PLAYERSHOUSE1F_POKEFAN_F, RIGHT)
    s_end
    SCRIPT_END
}
bool PlayersHouse1FTVScript(script_s* s) {
    SCRIPT_BEGIN
    jumptext(PlayersHouse1FTVText)
    SCRIPT_END
}
bool PlayersHouse1FStoveScript(script_s* s) {
    SCRIPT_BEGIN
    jumptext(PlayersHouse1FStoveText)
    SCRIPT_END
}
bool PlayersHouse1FSinkScript(script_s* s) {
    SCRIPT_BEGIN
    jumptext(PlayersHouse1FSinkText)
    SCRIPT_END
}
bool PlayersHouse1FFridgeScript(script_s* s) {
    SCRIPT_BEGIN
    jumptext(PlayersHouse1FFridgeText)
    SCRIPT_END
}
const uint8_t MomTurnsTowardPlayerMovement[] = {
    turn_head(RIGHT),
    movement_step_end,
};
const uint8_t MomWalksToPlayerMovement[] = {
    slow_step(RIGHT),
    movement_step_end,
};
const uint8_t MomTurnsBackMovement[] = {
    turn_head(LEFT),
    movement_step_end,
};
const uint8_t MomWalksBackMovement[] = {
    slow_step(LEFT),
    movement_step_end,
};
const txt_cmd_s ElmsLookingForYouText[] = {
    text_start("Oh, <PLAYER>…! Our"
        t_line "neighbor, PROF."
        t_para "ELM, was looking"
        t_line "for you."
        t_para "He said he wanted"
        t_line "you to do some-"
        t_cont "thing for him."
        t_para "Oh! I almost for-"
        t_line "got! Your #MON"
        t_para "GEAR is back from"
        t_line "the repair shop."
        t_para "Here you go!"
        t_done )
};
const txt_cmd_s MomGivesPokegearText[] = {
    text_start("#MON GEAR, or"
        t_line "just #GEAR."
        t_para "It's essential if"
        t_line "you want to be a"
        t_cont "good trainer."
        t_para "Oh, the day of the"
        t_line "week isn't set."
        t_para "You mustn't forget"
        t_line "that!"
        t_done )
};
const txt_cmd_s IsItDSTText[] = {
    text_start("Is it Daylight"
        t_line "Saving Time now?"
        t_done )
};
const txt_cmd_s ComeHomeForDSTText[] = {
    text_start("Come home to"
        t_line "adjust your clock"
        t_para "for Daylight"
        t_line "Saving Time."
        t_para "By the way, do you"
        t_line "know how to use"
        t_cont "the PHONE?"
        t_done )
};
const txt_cmd_s KnowTheInstructionsText[] = {
    text_start("Don't you just"
        t_line "turn the #GEAR"
        t_para "on and select the"
        t_line "PHONE icon?"
        t_done )
};
const txt_cmd_s DontKnowTheInstructionsText[] = {
    text_start("I'll read the"
        t_line "instructions."
        t_para "Turn the #GEAR"
        t_line "on and select the"
        t_cont "PHONE icon."
        t_done )
};
const txt_cmd_s InstructionsNextText[] = {
    text_start("Phone numbers are"
        t_line "stored in memory."
        t_para "Just choose a name"
        t_line "you want to call."
        t_para "Gee, isn't that"
        t_line "convenient?"
        t_done )
};
const txt_cmd_s HurryUpElmIsWaitingText[] = {
    text_start("PROF.ELM is wait-"
        t_line "ing for you."
        t_para "Hurry up, baby!"
        t_done )
};
const txt_cmd_s SoWhatWasProfElmsErrandText[] = {
    text_start("So, what was PROF."
        t_line "ELM's errand?"
        t_para "…"
        t_para "That does sound"
        t_line "challenging."
        t_para "But, you should be"
        t_line "proud that people"
        t_cont "rely on you."
        t_done )
};
const txt_cmd_s ImBehindYouText[] = {
    text_start("<PLAYER>, do it!"
        t_para "I'm behind you all"
        t_line "the way!"
        t_done )
};
const txt_cmd_s NeighborMornIntroText[] = {
    text_start("Good morning,"
        t_line "<PLAY_G>!"
        t_para "I'm visiting!"
        t_done )
};
const txt_cmd_s NeighborDayIntroText[] = {
    text_start("Hello, <PLAY_G>!"
        t_line "I'm visiting!"
        t_done )
};
const txt_cmd_s NeighborNiteIntroText[] = {
    text_start("Good evening,"
        t_line "<PLAY_G>!"
        t_para "I'm visiting!"
        t_done )
};
const txt_cmd_s NeighborText[] = {
    text_start("<PLAY_G>, have you"
        t_line "heard?"
        t_para "My daughter is"
        t_line "adamant about"
        t_para "becoming PROF."
        t_line "ELM's assistant."
        t_para "She really loves"
        t_line "#MON!"
        t_done )
};
const txt_cmd_s PlayersHouse1FStoveText[] = {
    text_start("Mom's specialty!"
        t_para "CINNABAR VOLCANO"
        t_line "BURGER!"
        t_done )
};
const txt_cmd_s PlayersHouse1FSinkText[] = {
    text_start("The sink is spot-"
        t_line "less. Mom likes it"
        t_cont "clean."
        t_done )
};
const txt_cmd_s PlayersHouse1FFridgeText[] = {
    text_start("Let's see what's"
        t_line "in the fridge…"
        t_para "FRESH WATER and"
        t_line "tasty LEMONADE!"
        t_done )
};
const txt_cmd_s PlayersHouse1FTVText[] = {
    text_start("There's a movie on"
        t_line "TV: Stars dot the"
        t_para "sky as two boys"
        t_line "ride on a train…"
        t_para "I'd better get"
        t_line "rolling too!"
        t_done )
    //db(0, 0) // filler
};
