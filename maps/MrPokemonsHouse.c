#include "../constants.h"
#include "../util/scripting.h"
#include "MrPokemonsHouse.h"
//// EVENTS
enum {
    MRPOKEMONSHOUSE_GENTLEMAN = 2,
    MRPOKEMONSHOUSE_OAK,
};

const Script_fn_t MrPokemonsHouse_SceneScripts[] = {
    MrPokemonsHouse_MapScripts_MeetMrPokemon , //  SCENE_DEFAULT,
    MrPokemonsHouse_MapScripts_DummyScene , //  SCENE_FINISHED,
};

const struct MapCallback MrPokemonsHouse_MapCallbacks[] = {
    0
};

const struct MapScripts MrPokemonsHouse_MapScripts = {
    .scene_script_count = lengthof(MrPokemonsHouse_SceneScripts),
    .scene_scripts = MrPokemonsHouse_SceneScripts,

    .callback_count = lengthof(MrPokemonsHouse_MapCallbacks),
    .callbacks = MrPokemonsHouse_MapCallbacks,
};

static const struct CoordEvent MrPokemonsHouse_CoordEvents[] = {
    0
};

static const struct BGEvent MrPokemonsHouse_BGEvents[] = {
    bg_event(0, 1, BGEVENT_READ, &MrPokemonsHouse_ForeignMagazines),
    bg_event(1, 1, BGEVENT_READ, &MrPokemonsHouse_ForeignMagazines),
    bg_event(6, 1, BGEVENT_READ, &MrPokemonsHouse_BrokenComputer),
    bg_event(7, 1, BGEVENT_READ, &MrPokemonsHouse_BrokenComputer),
    bg_event(6, 4, BGEVENT_READ, &MrPokemonsHouse_StrangeCoins),
};

static const struct WarpEventData MrPokemonsHouse_WarpEvents[] = {
    warp_event(2, 7, ROUTE_30, 2),
    warp_event(3, 7, ROUTE_30, 2),
};

static const struct ObjEvent MrPokemonsHouse_ObjectEvents[] = {
    object_event(3, 5, SPRITE_GENTLEMAN, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &MrPokemonsHouse_MrPokemonScript, -1),
    object_event(6, 5, SPRITE_OAK, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, EVENT_MR_POKEMONS_HOUSE_OAK),
};

const struct MapEvents MrPokemonsHouse_MapEvents = {
    .warp_event_count = lengthof(MrPokemonsHouse_WarpEvents),
    .warp_events = MrPokemonsHouse_WarpEvents,

    .coord_event_count = lengthof(MrPokemonsHouse_CoordEvents),
    .coord_events = MrPokemonsHouse_CoordEvents,

    .bg_event_count = lengthof(MrPokemonsHouse_BGEvents),
    .bg_events = MrPokemonsHouse_BGEvents,

    .obj_event_count = lengthof(MrPokemonsHouse_ObjectEvents),
    .obj_events = MrPokemonsHouse_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "MrPokemonsHouse.h"

bool MrPokemonsHouse_MapScripts_MeetMrPokemon(script_s* s) {
    SCRIPT_BEGIN
    sdefer(MrPokemonsHouse_MapScripts_MrPokemonEvent);
    s_end
    SCRIPT_END
}
bool MrPokemonsHouse_MapScripts_DummyScene(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool MrPokemonsHouse_MapScripts_MrPokemonEvent(script_s* s) {
    SCRIPT_BEGIN
    showemote(EMOTE_SHOCK, MRPOKEMONSHOUSE_GENTLEMAN, 15)
    turnobject(MRPOKEMONSHOUSE_GENTLEMAN, DOWN)
    opentext
    writetext(MrPokemonIntroText1)
    waitbutton
    closetext
    applymovement(PLAYER, MrPokemonsHouse_PlayerWalksToMrPokemon)
    opentext
    writetext(MrPokemonIntroText2)
    promptbutton
    waitsfx
    giveitem(MYSTERY_EGG, 1)
    writetext(MrPokemonsHouse_GotEggText)
    playsound(SFX_KEY_ITEM)
    waitsfx
    itemnotify
    setevent(EVENT_GOT_MYSTERY_EGG_FROM_MR_POKEMON)
    blackoutmod(CHERRYGROVE_CITY)
    writetext(MrPokemonIntroText3)
    promptbutton
    turnobject(MRPOKEMONSHOUSE_GENTLEMAN, RIGHT)
    writetext(MrPokemonIntroText4)
    promptbutton
    turnobject(MRPOKEMONSHOUSE_GENTLEMAN, DOWN)
    turnobject(MRPOKEMONSHOUSE_OAK, LEFT)
    writetext(MrPokemonIntroText5)
    waitbutton
    closetext
    sjump(MrPokemonsHouse_OakScript)
    SCRIPT_END
}
bool MrPokemonsHouse_MrPokemonScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkitem(RED_SCALE)
    iftrue(RedScale)
    checkevent(EVENT_GAVE_MYSTERY_EGG_TO_ELM)
    iftrue(AlwaysNewDiscoveries)
    writetext(MrPokemonText_ImDependingOnYou)
    waitbutton
    closetext
    s_end
AlwaysNewDiscoveries:
    writetext(MrPokemonText_AlwaysNewDiscoveries)
    waitbutton
    closetext
    s_end
RedScale:
    writetext(MrPokemonText_GimmeTheScale)
    yesorno
    iffalse(refused)
    verbosegiveitem(EXP_SHARE, 1)
    iffalse(full)
    takeitem(RED_SCALE, 1)
    goto AlwaysNewDiscoveries;
refused:
    writetext(MrPokemonText_Disappointed)
    waitbutton
full:
    closetext
    s_end
    SCRIPT_END
}
bool MrPokemonsHouse_OakScript(script_s* s) {
    SCRIPT_BEGIN
    playmusic(MUSIC_PROF_OAK)
    applymovement(MRPOKEMONSHOUSE_OAK, MrPokemonsHouse_OakWalksToPlayer)
    turnobject(PLAYER, RIGHT)
    opentext
    writetext(MrPokemonsHouse_OakText1)
    promptbutton
    waitsfx
    writetext(MrPokemonsHouse_GetDexText)
    playsound(SFX_ITEM)
    waitsfx
    setflag(ENGINE_POKEDEX)
    writetext(MrPokemonsHouse_OakText2)
    waitbutton
    closetext
    turnobject(PLAYER, DOWN)
    applymovement(MRPOKEMONSHOUSE_OAK, MrPokemonsHouse_OakExits)
    playsound(SFX_EXIT_BUILDING)
    disappear(MRPOKEMONSHOUSE_OAK)
    waitsfx
    special(RestartMapMusic)
    pause(15)
    turnobject(PLAYER, UP)
    opentext
    writetext(MrPokemonsHouse_MrPokemonHealText)
    waitbutton
    closetext
    special(FadeBlackQuickly)
    special(ReloadSpritesNoPalettes)
    playmusic(MUSIC_HEAL)
    special(StubbedTrainerRankings_Healings)
    special(HealParty)
    pause(60)
    special(FadeInQuickly)
    special(RestartMapMusic)
    opentext
    writetext(MrPokemonText_ImDependingOnYou)
    waitbutton
    closetext
    setevent(EVENT_RIVAL_NEW_BARK_TOWN)
    setevent(EVENT_PLAYERS_HOUSE_1F_NEIGHBOR)
    clearevent(EVENT_PLAYERS_NEIGHBORS_HOUSE_NEIGHBOR)
    setscene(SCENE_FINISHED)
    setmapscene(CHERRYGROVE_CITY, SCENE_CHERRYGROVECITY_MEET_RIVAL)
    setmapscene(ELMS_LAB, SCENE_ELMSLAB_MEET_OFFICER)
    specialphonecall(SPECIALCALL_ROBBED)
    clearevent(EVENT_COP_IN_ELMS_LAB)
    checkevent(EVENT_GOT_TOTODILE_FROM_ELM)
    iftrue(RivalTakesChikorita)
    checkevent(EVENT_GOT_CHIKORITA_FROM_ELM)
    iftrue(RivalTakesCyndaquil)
    setevent(EVENT_TOTODILE_POKEBALL_IN_ELMS_LAB)
    s_end
RivalTakesChikorita:
    setevent(EVENT_CHIKORITA_POKEBALL_IN_ELMS_LAB)
    s_end
RivalTakesCyndaquil:
    setevent(EVENT_CYNDAQUIL_POKEBALL_IN_ELMS_LAB)
    s_end
    SCRIPT_END
}
bool MrPokemonsHouse_ForeignMagazines(script_s* s) {
    SCRIPT_BEGIN
    jumptext(MrPokemonsHouse_ForeignMagazinesText)
    SCRIPT_END
}
bool MrPokemonsHouse_BrokenComputer(script_s* s) {
    SCRIPT_BEGIN
    jumptext(MrPokemonsHouse_BrokenComputerText)
    SCRIPT_END
}
bool MrPokemonsHouse_StrangeCoins(script_s* s) {
    SCRIPT_BEGIN
    jumptext(MrPokemonsHouse_StrangeCoinsText)
    SCRIPT_END
}
const uint8_t MrPokemonsHouse_PlayerWalksToMrPokemon[] = {
    step(RIGHT),
    step(UP),
    movement_step_end,
};
const uint8_t MrPokemonsHouse_OakWalksToPlayer[] = {
    step(DOWN),
    step(LEFT),
    step(LEFT),
    movement_step_end,
};
const uint8_t MrPokemonsHouse_OakExits[] = {
    step(DOWN),
    step(LEFT),
    turn_head(DOWN),
    step_sleep(2),
    movement_step_end,
};
const txt_cmd_s MrPokemonIntroText1[] = {
    text_start("Hello, hello! You"
        t_line "must be <PLAY_G>."
        t_para "PROF.ELM said that"
        t_line "you would visit."
        t_done )
};
const txt_cmd_s MrPokemonIntroText2[] = {
    text_start("This is what I"
        t_line "want PROF.ELM to"
        t_cont "examine."
        t_done )
};
const txt_cmd_s MrPokemonsHouse_GotEggText[] = {
    text_start("<PLAYER> received"
        t_line "MYSTERY EGG."
        t_done )
};
const txt_cmd_s MrPokemonIntroText3[] = {
    text_start("I know a couple"
        t_line "who run a #MON"
        t_cont "DAY-CARE service."
        t_para "They gave me that"
        t_line "EGG."
        t_para "I was intrigued,"
        t_line "so I sent mail to"
        t_cont "PROF.ELM."
        t_para "For #MON evolu-"
        t_line "tion, PROF.ELM is"
        t_cont "the authority."
        t_done )
};
const txt_cmd_s MrPokemonIntroText4[] = {
    text_start("Even PROF.OAK here"
        t_line "recognizes that."
        t_done )
};
const txt_cmd_s MrPokemonIntroText5[] = {
    text_start("If my assumption"
        t_line "is correct, PROF."
        t_cont "ELM will know it."
        t_done )
};
const txt_cmd_s MrPokemonsHouse_MrPokemonHealText[] = {
    text_start("You are returning"
        t_line "to PROF.ELM?"
        t_para "Here. Your #MON"
        t_line "should have some"
        t_cont "rest."
        t_done )
};
const txt_cmd_s MrPokemonText_ImDependingOnYou[] = {
    text_start("I'm depending on"
        t_line "you!"
        t_done )
};
const txt_cmd_s MrPokemonText_AlwaysNewDiscoveries[] = {
    text_start("Life is delight-"
        t_line "ful! Always, new"
        t_para "discoveries to be"
        t_line "made!"
        t_done )
};
const txt_cmd_s MrPokemonsHouse_OakText1[] = {
    text_start("OAK: Aha! So"
        t_line "you're <PLAY_G>!"
        t_para "I'm OAK! A #MON"
        t_line "researcher."
        t_para "I was just visit-"
        t_line "ing my old friend"
        t_cont "MR.#MON."
        t_para "I heard you were"
        t_line "running an errand"
        t_para "for PROF.ELM, so I"
        t_line "waited here."
        t_para "Oh! What's this?"
        t_line "A rare #MON!"
        t_para "Let's see…"
        t_para "Hm, I see!"
        t_para "I understand why"
        t_line "PROF.ELM gave you"
        t_para "a #MON for this"
        t_line "errand."
        t_para "To researchers"
        t_line "like PROF.ELM and"
        t_para "I, #MON are our"
        t_line "friends."
        t_para "He saw that you"
        t_line "would treat your"
        t_para "#MON with love"
        t_line "and care."
        t_para "…Ah!"
        t_para "You seem to be"
        t_line "dependable."
        t_para "How would you like"
        t_line "to help me out?"
        t_para "See? This is the"
        t_line "latest version of"
        t_cont "#DEX."
        t_para "It automatically"
        t_line "records data on"
        t_para "#MON you've"
        t_line "seen or caught."
        t_para "It's a hi-tech"
        t_line "encyclopedia!"
        t_done )
};
const txt_cmd_s MrPokemonsHouse_GetDexText[] = {
    text_start("<PLAYER> received"
        t_line "#DEX!"
        t_done )
};
const txt_cmd_s MrPokemonsHouse_OakText2[] = {
    text_start("Go meet many kinds"
        t_line "of #MON and"
        t_para "complete that"
        t_line "#DEX!"
        t_para "But I've stayed"
        t_line "too long."
        t_para "I have to get to"
        t_line "GOLDENROD for my"
        t_cont "usual radio show."
        t_para "<PLAY_G>, I'm"
        t_line "counting on you!"
        t_done )
};
const txt_cmd_s MrPokemonText_GimmeTheScale[] = {
    text_start("Hm? That SCALE!"
        t_line "What's that?"
        t_cont "A red GYARADOS?"
        t_para "That's rare! "
        t_line "I, I want it…"
        t_para "<PLAY_G>, would you"
        t_line "care to trade it?"
        t_para "I can offer this"
        t_line "EXP.SHARE I got"
        t_cont "from PROF.OAK."
        t_done )
};
const txt_cmd_s MrPokemonText_Disappointed[] = {
    text_start("That's disappoint-"
        t_line "ing. That happens"
        t_cont "to be very rare."
        t_done )
};
const txt_cmd_s MrPokemonsHouse_ForeignMagazinesText[] = {
    text_start("It's packed with"
        t_line "foreign magazines."
        t_para "Can't even read"
        t_line "their titles…"
        t_done )
};
const txt_cmd_s MrPokemonsHouse_BrokenComputerText[] = {
    text_start("It's a big com-"
        t_line "puter. Hmm. It's"
        t_cont "broken."
        t_done )
};
const txt_cmd_s MrPokemonsHouse_StrangeCoinsText[] = {
    text_start("A whole pile of"
        t_line "strange coins!"
        t_para "Maybe they're from"
        t_line "another country…"
        t_done )
    //db(0, 0) // filler
};
