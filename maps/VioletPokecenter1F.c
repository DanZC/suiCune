#include "../constants.h"
#include "../util/scripting.h"
#include "VioletPokecenter1F.h"
//// EVENTS
enum {
    VIOLETPOKECENTER1F_NURSE = 2,
    VIOLETPOKECENTER1F_GAMEBOY_KID,
    VIOLETPOKECENTER1F_GENTLEMAN,
    VIOLETPOKECENTER1F_YOUNGSTER,
    VIOLETPOKECENTER1F_ELMS_AIDE,
};

const Script_fn_t VioletPokecenter1F_SceneScripts[] = {
    0,
};

const struct MapCallback VioletPokecenter1F_MapCallbacks[] = {
    0,
};

const struct MapScripts VioletPokecenter1F_MapScripts = {
    .scene_script_count = 0, // lengthof(VioletPokecenter1F_SceneScripts),
    .scene_scripts = VioletPokecenter1F_SceneScripts,

    .callback_count = 0, // lengthof(VioletPokecenter1F_MapCallbacks),
    .callbacks = VioletPokecenter1F_MapCallbacks,
};

static const struct CoordEvent VioletPokecenter1F_CoordEvents[] = {
    0,
};

static const struct BGEvent VioletPokecenter1F_BGEvents[] = {
    0,
};

static const struct WarpEventData VioletPokecenter1F_WarpEvents[] = {
    warp_event(3, 7, VIOLET_CITY, 5),
    warp_event(4, 7, VIOLET_CITY, 5),
    warp_event(0, 7, POKECENTER_2F, 1),
};

static const struct ObjEvent VioletPokecenter1F_ObjectEvents[] = {
    object_event(3, 1, SPRITE_NURSE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &VioletPokecenterNurse, -1),
    object_event(7, 6, SPRITE_GAMEBOY_KID, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &VioletPokecenter1FGameboyKidScript, -1),
    object_event(1, 4, SPRITE_GENTLEMAN, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &VioletPokecenter1FGentlemanScript, -1),
    object_event(8, 1, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &VioletPokecenter1FYoungsterScript, -1),
    object_event(4, 3, SPRITE_SCIENTIST, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &VioletPokecenter1F_ElmsAideScript, EVENT_ELMS_AIDE_IN_VIOLET_POKEMON_CENTER),
};

const struct MapEvents VioletPokecenter1F_MapEvents = {
    .warp_event_count = lengthof(VioletPokecenter1F_WarpEvents),
    .warp_events = VioletPokecenter1F_WarpEvents,

    .coord_event_count = 0, // lengthof(VioletPokecenter1F_CoordEvents),
    .coord_events = VioletPokecenter1F_CoordEvents,

    .bg_event_count = 0, // lengthof(VioletPokecenter1F_BGEvents),
    .bg_events = VioletPokecenter1F_BGEvents,

    .obj_event_count = lengthof(VioletPokecenter1F_ObjectEvents),
    .obj_events = VioletPokecenter1F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "VioletPokecenter1F.h"

static bool VioletPokecenter1F_AskTakeEgg(script_s* s);
static bool VioletPokecenter1F_AideGivesEgg(script_s* s);
static bool VioletPokecenter1F_PartyFull(script_s* s);
static bool VioletPokecenter1F_RefusedEgg(script_s* s);
static bool VioletPokecenter1F_SecondTimeAsking(script_s* s);

bool VioletPokecenterNurse(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PokecenterNurseScript)
    SCRIPT_END
}
bool VioletPokecenter1F_ElmsAideScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_REFUSED_TO_TAKE_EGG_FROM_ELMS_AIDE)
    iftrue_jump(VioletPokecenter1F_SecondTimeAsking)
    writetext(VioletPokecenterElmsAideFavorText)
    SCRIPT_FALLTHROUGH(VioletPokecenter1F_AskTakeEgg)
}
static bool VioletPokecenter1F_AskTakeEgg(script_s* s) {
    static const char eggname[] = "EGG@";
    SCRIPT_BEGIN
    yesorno
    iffalse_jump(VioletPokecenter1F_RefusedEgg)
    readvar(VAR_PARTYCOUNT)
    ifequal_jump(PARTY_LENGTH, VioletPokecenter1F_PartyFull)
    giveegg(TOGEPI, EGG_LEVEL)
    getstring(STRING_BUFFER_4, eggname)
    scall(VioletPokecenter1F_AideGivesEgg);
    setevent(EVENT_GOT_TOGEPI_EGG_FROM_ELMS_AIDE)
    clearevent(EVENT_ELMS_AIDE_IN_LAB)
    clearevent(EVENT_TOGEPI_HATCHED)
    setmapscene(ROUTE_32, SCENE_ROUTE32_OFFER_SLOWPOKETAIL)
    writetext(VioletPokecenterElmsAideGiveEggText)
    waitbutton
    closetext
    readvar(VAR_FACING)
    ifequal(UP, AideWalksAroundPlayer)
    turnobject(PLAYER, DOWN)
    applymovement(VIOLETPOKECENTER1F_ELMS_AIDE, MovementData_AideWalksStraightOutOfPokecenter)
    playsound(SFX_EXIT_BUILDING)
    disappear(VIOLETPOKECENTER1F_ELMS_AIDE)
    waitsfx
    s_end
AideWalksAroundPlayer:
    applymovement(VIOLETPOKECENTER1F_ELMS_AIDE, MovementData_AideWalksLeftToExitPokecenter)
    turnobject(PLAYER, DOWN)
    applymovement(VIOLETPOKECENTER1F_ELMS_AIDE, MovementData_AideFinishesLeavingPokecenter)
    playsound(SFX_EXIT_BUILDING)
    disappear(VIOLETPOKECENTER1F_ELMS_AIDE)
    waitsfx
    s_end
    SCRIPT_END
}
static bool VioletPokecenter1F_AideGivesEgg(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(ReceiveTogepiEggScript)
    s_end
    SCRIPT_END
}
static bool VioletPokecenter1F_PartyFull(script_s* s) {
    SCRIPT_BEGIN
    writetext(VioletCityElmsAideFullPartyText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
static bool VioletPokecenter1F_RefusedEgg(script_s* s) {
    SCRIPT_BEGIN
    writetext(VioletPokecenterElmsAideRefuseText)
    waitbutton
    closetext
    setevent(EVENT_REFUSED_TO_TAKE_EGG_FROM_ELMS_AIDE)
    s_end
    SCRIPT_END
}
static bool VioletPokecenter1F_SecondTimeAsking(script_s* s) {
    SCRIPT_BEGIN
    writetext(VioletPokecenterElmsAideAskEggText)
    // goto AskTakeEgg;
    sjump(VioletPokecenter1F_AskTakeEgg);
    SCRIPT_END
}
bool VioletPokecenter1FGameboyKidScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(VioletPokecenter1FGameboyKidText)
    SCRIPT_END
}
bool VioletPokecenter1FGentlemanScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(VioletPokecenter1FGentlemanText)
    SCRIPT_END
}
bool VioletPokecenter1FYoungsterScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(VioletPokecenter1FYoungsterText)
    SCRIPT_END
}
const uint8_t MovementData_AideWalksStraightOutOfPokecenter[] = {
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    movement_step_end,
};
const uint8_t MovementData_AideWalksLeftToExitPokecenter[] = {
    step(LEFT),
    step(DOWN),
    movement_step_end,
};
const uint8_t MovementData_AideFinishesLeavingPokecenter[] = {
    step(DOWN),
    step(DOWN),
    step(DOWN),
    movement_step_end,
};
const txt_cmd_s VioletPokecenterElmsAideFavorText[] = {
    text_start("<PLAY_G>, long"
        t_line "time, no see."
        t_para "PROF.ELM asked me"
        t_line "to find you."
        t_para "He has another"
        t_line "favor to ask."
        t_para "Would you take the"
        t_line "#MON EGG?"
        t_done )
};
const txt_cmd_s VioletPokecenterElmsAideGiveEggText[] = {
    text_start("We discovered that"
        t_line "a #MON will not"
        t_para "hatch until it"
        t_line "grows in the EGG."
        t_para "It also has to be"
        t_line "with other active"
        t_cont "#MON to hatch."
        t_para "<PLAY_G>, you're"
        t_line "the only person"
        t_cont "we can rely on."
        t_para "Please call PROF."
        t_line "ELM when that EGG"
        t_cont "hatches!"
        t_done )
};
const txt_cmd_s VioletCityElmsAideFullPartyText[] = {
    text_start("Oh, no. You can't"
        t_line "carry any more"
        t_cont "#MON with you."
        t_para "I'll wait here"
        t_line "while you make"
        t_cont "room for the EGG."
        t_done )
};
const txt_cmd_s VioletPokecenterElmsAideRefuseText[] = {
    text_start("B-but… PROF.ELM"
        t_line "asked for you…"
        t_done )
};
const txt_cmd_s VioletPokecenterElmsAideAskEggText[] = {
    text_start("<PLAY_G>, will you"
        t_line "take the EGG?"
        t_done )
};
const txt_cmd_s VioletPokecenterFarawayLinkText[] = {
    text_start("I've been thinking"
        t_line "it'd be great to"
        t_para "be able to link up"
        t_line "and battle with my"
        t_para "friends who live"
        t_line "far away."
        t_done )
};
const txt_cmd_s VioletPokecenterMobileAdapterText[] = {
    text_start("I just battled a"
        t_line "friend in CIANWOOD"
        t_cont "over a link."
        t_para "If you connect a"
        t_line "MOBILE ADAPTER,"
        t_para "you can link with"
        t_line "a friend far away."
        t_done )
};
const txt_cmd_s VioletPokecenter1FGameboyKidText[] = {
    text_start("A guy named BILL"
        t_line "made the #MON"
        t_cont "PC storage system."
        t_done )
};
const txt_cmd_s VioletPokecenter1FGentlemanText[] = {
    text_start("It was around"
        t_line "three years ago."
        t_para "TEAM ROCKET was up"
        t_line "to no good with"
        t_cont "#MON."
        t_para "But justice pre-"
        t_line "vailed--a young"
        t_cont "kid broke 'em up."
        t_done )
};
const txt_cmd_s VioletPokecenter1FYoungsterText[] = {
    text_start("#MON are smart."
        t_line "They won't obey a"
        t_para "trainer they don't"
        t_line "respect."
        t_para "Without the right"
        t_line "GYM BADGES, they"
        t_para "will just do as"
        t_line "they please."
        t_done )
    //db(0, 0) // filler
};
