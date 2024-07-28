#include "../constants.h"
#include "../util/scripting.h"
#include "FastShipCabins_SE_SSE_CaptainsCabin.h"
//// EVENTS
enum {
    FASTSHIPCABINS_SE_SSE_CAPTAINSCABIN_CAPTAIN = 2,
    FASTSHIPCABINS_SE_SSE_CAPTAINSCABIN_GENTLEMAN,
    FASTSHIPCABINS_SE_SSE_CAPTAINSCABIN_TWIN1,
    FASTSHIPCABINS_SE_SSE_CAPTAINSCABIN_TWIN2,
    FASTSHIPCABINS_SE_SSE_CAPTAINSCABIN_POKEFAN_M1,
    FASTSHIPCABINS_SE_SSE_CAPTAINSCABIN_TWIN3,
    FASTSHIPCABINS_SE_SSE_CAPTAINSCABIN_TWIN4,
    FASTSHIPCABINS_SE_SSE_CAPTAINSCABIN_SUPER_NERD1,
    FASTSHIPCABINS_SE_SSE_CAPTAINSCABIN_POKEFAN_M2,
    FASTSHIPCABINS_SE_SSE_CAPTAINSCABIN_POKEFAN_F,
    FASTSHIPCABINS_SE_SSE_CAPTAINSCABIN_SUPER_NERD2,
};

const Script_fn_t FastShipCabins_SE_SSE_CaptainsCabin_SceneScripts[] = {
    0,
};

const struct MapCallback FastShipCabins_SE_SSE_CaptainsCabin_MapCallbacks[] = {
    0,
};

const struct MapScripts FastShipCabins_SE_SSE_CaptainsCabin_MapScripts = {
    .scene_script_count = 0, // lengthof(FastShipCabins_SE_SSE_CaptainsCabin_SceneScripts),
    .scene_scripts = FastShipCabins_SE_SSE_CaptainsCabin_SceneScripts,

    .callback_count = 0, // lengthof(FastShipCabins_SE_SSE_CaptainsCabin_MapCallbacks),
    .callbacks = FastShipCabins_SE_SSE_CaptainsCabin_MapCallbacks,
};

static const struct CoordEvent FastShipCabins_SE_SSE_CaptainsCabin_CoordEvents[] = {
    0,
};

static const struct BGEvent FastShipCabins_SE_SSE_CaptainsCabin_BGEvents[] = {
    bg_event(4, 25, BGEVENT_READ, &FastShipCaptainsCabinTrashcan),
};

static const struct WarpEventData FastShipCabins_SE_SSE_CaptainsCabin_WarpEvents[] = {
    warp_event(2, 7, FAST_SHIP_1F, 8),
    warp_event(3, 7, FAST_SHIP_1F, 8),
    warp_event(2, 19, FAST_SHIP_1F, 9),
    warp_event(3, 19, FAST_SHIP_1F, 9),
    warp_event(2, 33, FAST_SHIP_1F, 10),
    warp_event(3, 33, FAST_SHIP_1F, 10),
};

static const struct ObjEvent FastShipCabins_SE_SSE_CaptainsCabin_ObjectEvents[] = {
    object_event(3, 25, SPRITE_CAPTAIN, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &SSAquaCaptain, -1),
    object_event(2, 17, SPRITE_GENTLEMAN, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &SSAquaGrandpa, EVENT_FAST_SHIP_CABINS_SE_SSE_GENTLEMAN),
    object_event(3, 17, SPRITE_TWIN, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &SSAquaGranddaughterAfter, EVENT_FAST_SHIP_CABINS_SE_SSE_CAPTAINS_CABIN_TWIN_1),
    object_event(2, 25, SPRITE_TWIN, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &SSAquaGranddaughterBefore, EVENT_FAST_SHIP_CABINS_SE_SSE_CAPTAINS_CABIN_TWIN_2),
    object_event(5, 6, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 5, &TrainerPokefanmColin, EVENT_FAST_SHIP_PASSENGERS_FIRST_TRIP),
    object_event(2, 4, SPRITE_TWIN, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 1, &TrainerTwinsMegandpeg1, EVENT_FAST_SHIP_PASSENGERS_FIRST_TRIP),
    object_event(3, 4, SPRITE_TWIN, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 1, &TrainerTwinsMegandpeg2, EVENT_FAST_SHIP_PASSENGERS_FIRST_TRIP),
    object_event(5, 5, SPRITE_SUPER_NERD, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 5, &TrainerPsychicRodney, EVENT_FAST_SHIP_PASSENGERS_EASTBOUND),
    object_event(2, 3, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 3, &TrainerPokefanmJeremy, EVENT_FAST_SHIP_PASSENGERS_WESTBOUND),
    object_event(5, 5, SPRITE_POKEFAN_F, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 1, &TrainerPokefanfGeorgia, EVENT_FAST_SHIP_PASSENGERS_WESTBOUND),
    object_event(1, 15, SPRITE_SUPER_NERD, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_TRAINER, 2, &TrainerSupernerdShawn, EVENT_FAST_SHIP_PASSENGERS_EASTBOUND),
};

const struct MapEvents FastShipCabins_SE_SSE_CaptainsCabin_MapEvents = {
    .warp_event_count = lengthof(FastShipCabins_SE_SSE_CaptainsCabin_WarpEvents),
    .warp_events = FastShipCabins_SE_SSE_CaptainsCabin_WarpEvents,

    .coord_event_count = 0, // lengthof(FastShipCabins_SE_SSE_CaptainsCabin_CoordEvents),
    .coord_events = FastShipCabins_SE_SSE_CaptainsCabin_CoordEvents,

    .bg_event_count = lengthof(FastShipCabins_SE_SSE_CaptainsCabin_BGEvents),
    .bg_events = FastShipCabins_SE_SSE_CaptainsCabin_BGEvents,

    .obj_event_count = lengthof(FastShipCabins_SE_SSE_CaptainsCabin_ObjectEvents),
    .obj_events = FastShipCabins_SE_SSE_CaptainsCabin_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "FastShipCabins_SE_SSE_CaptainsCabin.h"

bool FastShipCabins_SE_SSE_CaptainsCabin_MapScripts_DummyScene(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool SSAquaCaptain(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_FAST_SHIP_FIRST_TIME)
    iftrue(LaterTrip)
    writetext(SSAquaCaptainExhaustingText)
    waitbutton
    closetext
    s_end
LaterTrip:
    writetext(SSAquaCaptainHowDoYouLikeText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool SSAquaGranddaughterBefore(script_s* s) {
    SCRIPT_BEGIN
    turnobject(FASTSHIPCABINS_SE_SSE_CAPTAINSCABIN_TWIN2, RIGHT)
    opentext
    writetext(SSAquaGranddaughterCaptainPlayWithMeText)
    waitbutton
    closetext
    faceplayer
    opentext
    writetext(SSAquaGranddaughterHasToFindGrandpaText)
    waitbutton
    closetext
    special(FadeBlackQuickly)
    special(ReloadSpritesNoPalettes)
    disappear(FASTSHIPCABINS_SE_SSE_CAPTAINSCABIN_TWIN2)
    applymovement(PLAYER, SSAquaCaptainsCabinWarpsToGrandpasCabinMovement)
    moveobject(FASTSHIPCABINS_SE_SSE_CAPTAINSCABIN_TWIN1, 3, 19)
    appear(FASTSHIPCABINS_SE_SSE_CAPTAINSCABIN_TWIN1)
    turnobject(PLAYER, UP)
    turnobject(FASTSHIPCABINS_SE_SSE_CAPTAINSCABIN_TWIN1, UP)
    special(FadeInQuickly)
    turnobject(FASTSHIPCABINS_SE_SSE_CAPTAINSCABIN_GENTLEMAN, DOWN)
    showemote(EMOTE_SHOCK, FASTSHIPCABINS_SE_SSE_CAPTAINSCABIN_GENTLEMAN, 15)
    applymovement(FASTSHIPCABINS_SE_SSE_CAPTAINSCABIN_TWIN1, SSAquaGranddaughterEntersCabinMovement)
    turnobject(FASTSHIPCABINS_SE_SSE_CAPTAINSCABIN_GENTLEMAN, RIGHT)
    checkflag(ENGINE_PLAYER_IS_FEMALE)
    iftrue(PlayerIsFemale)
    opentext
    writetext(SSAquaGranddaughterWasPlayingMText)
    waitbutton
    closetext
    goto cont;
PlayerIsFemale:
    opentext
    writetext(SSAquaGranddaughterWasPlayingFText)
    waitbutton
    closetext
cont:
    turnobject(FASTSHIPCABINS_SE_SSE_CAPTAINSCABIN_TWIN2, DOWN)
    applymovement(FASTSHIPCABINS_SE_SSE_CAPTAINSCABIN_GENTLEMAN, SSAquaGrandpaApproachesPlayerMovement)
    opentext
    writetext(SSAquaEntertainedGranddaughterText)
    promptbutton
    setevent(EVENT_VERMILION_PORT_SAILOR_AT_GANGWAY)
    setmapscene(FAST_SHIP_1F, SCENE_DEFAULT)
    sjump(SSAquaMetalCoatAndDocking)
    SCRIPT_END
}
bool SSAquaGrandpa(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_METAL_COAT_FROM_GRANDPA_ON_SS_AQUA)
    iftrue_jump(SSAquaGotMetalCoat)
    checkevent(EVENT_FAST_SHIP_CABINS_SE_SSE_CAPTAINS_CABIN_TWIN_2)
    iftrue_jump(SSAquaFoundGranddaughter)
    writetext(SSAquaCantFindGranddaughterText)
    waitbutton
    closetext
    setmapscene(FAST_SHIP_1F, SCENE_DEFAULT)
    s_end
    SCRIPT_END
}
bool SSAquaMetalCoatAndDocking(script_s* s) {
    SCRIPT_BEGIN
    writetext(SSAquaGrandpaHaveThisText)
    promptbutton
    verbosegiveitem(METAL_COAT, 1)
    iffalse(NoRoom)
    setevent(EVENT_GOT_METAL_COAT_FROM_GRANDPA_ON_SS_AQUA)
NoRoom:
    closetext
    waitsfx
    playsound(SFX_ELEVATOR_END)
    pause(30)
    opentext
    writetext(SSAquaHasArrivedVermilionText)
    waitbutton
    setevent(EVENT_FAST_SHIP_HAS_ARRIVED)
    setevent(EVENT_FAST_SHIP_FOUND_GIRL)
    closetext
    s_end
    SCRIPT_END
}
bool SSAquaFoundGranddaughter(script_s* s) {
    SCRIPT_BEGIN
    writetext(SSAquaGrandpaHaveThisText)
    promptbutton
    verbosegiveitem(METAL_COAT, 1)
    iffalse(NoRoom)
    setevent(EVENT_GOT_METAL_COAT_FROM_GRANDPA_ON_SS_AQUA)
NoRoom:
    closetext
    s_end
    SCRIPT_END
}
bool SSAquaGotMetalCoat(script_s* s) {
    SCRIPT_BEGIN
    writetext(SSAquaGrandpaTravellingText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool SSAquaGranddaughterAfter(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(SSAquaGranddaughterHadFunText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerPokefanmColin = {POKEFANM, COLIN, EVENT_BEAT_POKEFANM_COLIN, PokefanmColinSeenText, PokefanmColinBeatenText, 0, TrainerPokefanmColin_Script};
bool TrainerPokefanmColin_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(PokefanmColinAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerTwinsMegandpeg1 = {TWINS, MEGANDPEG1, EVENT_BEAT_TWINS_MEG_AND_PEG, TwinsMegandpeg1SeenText, TwinsMegandpeg1BeatenText, 0, TrainerTwinsMegandpeg1_Script};
bool TrainerTwinsMegandpeg1_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(TwinsMegandpeg1AfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerTwinsMegandpeg2 = {TWINS, MEGANDPEG2, EVENT_BEAT_TWINS_MEG_AND_PEG, TwinsMegandpeg2SeenText, TwinsMegandpeg2BeatenText, 0, TrainerTwinsMegandpeg2_Script};
bool TrainerTwinsMegandpeg2_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(TwinsMegandpeg2AfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerPsychicRodney = {PSYCHIC_T, RODNEY, EVENT_BEAT_PSYCHIC_RODNEY, PsychicRodneySeenText, PsychicRodneyBeatenText, 0, TrainerPsychicRodney_Script};
bool TrainerPsychicRodney_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(PsychicRodneyAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerPokefanmJeremy = {POKEFANM, JEREMY, EVENT_BEAT_POKEFANM_JEREMY, PokefanmJeremySeenText, PokefanmJeremyBeatenText, 0, TrainerPokefanmJeremy_Script};
bool TrainerPokefanmJeremy_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(PokefanmJeremyAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerPokefanfGeorgia = {POKEFANF, GEORGIA, EVENT_BEAT_POKEFANF_GEORGIA, PokefanfGeorgiaSeenText, PokefanfGeorgiaBeatenText, 0, TrainerPokefanfGeorgia_Script};
bool TrainerPokefanfGeorgia_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(PokefanfGeorgiaAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSupernerdShawn = {SUPER_NERD, SHAWN, EVENT_BEAT_SUPER_NERD_SHAWN, SupernerdShawnSeenText, SupernerdShawnBeatenText, 0, TrainerSupernerdShawn_Script};
bool TrainerSupernerdShawn_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SupernerdShawnAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool FastShipCaptainsCabinTrashcan(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(TrashCanScript)
    SCRIPT_END
}
const uint8_t SSAquaCaptainsCabinWarpsToGrandpasCabinMovement[] = {
    big_step(RIGHT),
    big_step(UP),
    big_step(UP),
    big_step(UP),
    big_step(UP),
    big_step(UP),
    big_step(UP),
    movement_step_end,
};
const uint8_t SSAquaGranddaughterEntersCabinMovement[] = {
    step(UP),
    step(UP),
    turn_head(LEFT),
    movement_step_end,
};
const uint8_t SSAquaGrandpaApproachesPlayerMovement[] = {
    step(DOWN),
    movement_step_end,
};
const txt_cmd_s SSAquaCaptainExhaustingText[] = {
    text_start("Whew! Thanks for"
        t_line "coming along."
        t_para "Keeping that lit-"
        t_line "tle girl amused"
        t_cont "was exhausting."
        t_done )
};
const txt_cmd_s SSAquaCaptainHowDoYouLikeText[] = {
    text_start("How do you like"
        t_line "S.S.AQUA's ride?"
        t_para "She practically"
        t_line "skates across the"
        t_cont "waves."
        t_done )
};
const txt_cmd_s SSAquaCantFindGranddaughterText[] = {
    text_start("Oh, hello…"
        t_para "I still can't find"
        t_line "my granddaughter."
        t_para "If she's on the"
        t_line "ship, that's OK."
        t_para "She's an energetic"
        t_line "child, so she may"
        t_para "be bugging some-"
        t_line "one. I'm worried…"
        t_done )
};
const txt_cmd_s SSAquaEntertainedGranddaughterText[] = {
    text_start("<PLAY_G>, was it?"
        t_line "I heard you enter-"
        t_cont "tained my grand-"
        t_cont "daughter."
        t_para "I want to thank"
        t_line "you for that."
        t_done )
};
const txt_cmd_s SSAquaGrandpaHaveThisText[] = {
    text_start("I know! I'd like"
        t_line "you to have this!"
        t_done )
};
const txt_cmd_s SSAquaGrandpaTravellingText[] = {
    text_start("We're traveling"
        t_line "around the world."
        t_done )
};
const txt_cmd_s SSAquaGranddaughterCaptainPlayWithMeText[] = {
    text_start("CAPTAIN, play with"
        t_line "me, please?"
        t_para "I'm bored! I want"
        t_line "to play more!"
        t_done )
};
const txt_cmd_s SSAquaGranddaughterHasToFindGrandpaText[] = {
    text_start("Hi! Will you play"
        t_line "with me?"
        t_para "…Oh!"
        t_para "Grandpa's worried"
        t_line "about me?"
        t_para "I have to go!"
        t_para "I have to go find"
        t_line "Grandpa!"
        t_done )
};
const txt_cmd_s SSAquaGranddaughterWasPlayingMText[] = {
    text_start("Grandpa, here I"
        t_line "am! I was playing"
        t_para "with the CAPTAIN"
        t_line "and this guy!"
        t_done )
};
const txt_cmd_s SSAquaGranddaughterWasPlayingFText[] = {
    text_start("Grandpa, here I"
        t_line "am! I was playing"
        t_para "with the CAPTAIN"
        t_line "and this big girl!"
        t_done )
};
const txt_cmd_s SSAquaGranddaughterHadFunText[] = {
    text_start("I had lots of fun"
        t_line "playing!"
        t_done )
};
const txt_cmd_s PokefanmColinSeenText[] = {
    text_start("Hey, kid! Want to"
        t_line "battle with me?"
        t_done )
};
const txt_cmd_s PokefanmColinBeatenText[] = {
    text_start("You're strong!"
        t_done )
};
const txt_cmd_s PokefanmColinAfterBattleText[] = {
    text_start("You're traveling"
        t_line "all alone?"
        t_para "Isn't your mom"
        t_line "worried?"
        t_done )
};
const txt_cmd_s TwinsMegandpeg1SeenText[] = {
    text_start("You think I'm a"
        t_line "baby?"
        t_cont "That's not fair!"
        t_done )
};
const txt_cmd_s TwinsMegandpeg1BeatenText[] = {
    text_start("Oh! We lost!"
        t_done )
};
const txt_cmd_s TwinsMegandpeg1AfterBattleText[] = {
    text_start("Baby is a rude"
        t_line "name to call us"
        t_cont "girls!"
        t_done )
};
const txt_cmd_s TwinsMegandpeg2SeenText[] = {
    text_start("I'm not a baby!"
        t_para "That's not nice to"
        t_line "say to a lady!"
        t_done )
};
const txt_cmd_s TwinsMegandpeg2BeatenText[] = {
    text_start("Oh! We lost!"
        t_done )
};
const txt_cmd_s TwinsMegandpeg2AfterBattleText[] = {
    text_start("Sometimes, kids"
        t_line "are smarter than"
        t_cont "grown-ups!"
        t_done )
};
const txt_cmd_s PsychicRodneySeenText[] = {
    text_start("Ssh! My brain is"
        t_line "picking up radio"
        t_cont "signals!"
        t_done )
};
const txt_cmd_s PsychicRodneyBeatenText[] = {
    text_start("…I hear some-"
        t_line "thing!"
        t_done )
};
const txt_cmd_s PsychicRodneyAfterBattleText[] = {
    text_start("I get it. You can"
        t_line "hear JOHTO's radio"
        t_cont "on the FAST SHIP."
        t_done )
};
const txt_cmd_s PokefanmJeremySeenText[] = {
    text_start("What do you think?"
        t_line "My #MON are"
        t_cont "beautiful, yes?"
        t_done )
};
const txt_cmd_s PokefanmJeremyBeatenText[] = {
    text_start("Oh, no! My beauti-"
        t_line "ful #MON!"
        t_done )
};
const txt_cmd_s PokefanmJeremyAfterBattleText[] = {
    text_start("I must go to the"
        t_line "#MON SALON and"
        t_cont "fix them up nice!"
        t_done )
};
const txt_cmd_s PokefanfGeorgiaSeenText[] = {
    text_start("I'm going to shop"
        t_line "at the DEPT.STORE"
        t_cont "and then…"
        t_done )
};
const txt_cmd_s PokefanfGeorgiaBeatenText[] = {
    text_start("What was I going"
        t_line "to do?"
        t_done )
};
const txt_cmd_s PokefanfGeorgiaAfterBattleText[] = {
    text_start("Oh, yes! I have to"
        t_line "get my #MON out"
        t_cont "of DAY-CARE!"
        t_done )
};
const txt_cmd_s SupernerdShawnSeenText[] = {
    text_start("What kinds of #"
        t_line "BALLS do you have"
        t_cont "with you?"
        t_done )
};
const txt_cmd_s SupernerdShawnBeatenText[] = {
    text_start("Wait! Stop! Don't!"
        t_line "Please!"
        t_done )
};
const txt_cmd_s SupernerdShawnAfterBattleText[] = {
    text_start("You should use the"
        t_line "right BALLS to fit"
        t_cont "the situation."
        t_done )
};
const txt_cmd_s SSAquaHasArrivedVermilionText[] = {
    text_start("FAST SHIP S.S.AQUA"
        t_line "has arrived in"
        t_cont "VERMILION CITY."
        t_done )
    //db(0, 0) // filler
};
