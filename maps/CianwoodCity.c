#include "../constants.h"
#include "../util/scripting.h"
#include "CianwoodCity.h"
//// EVENTS
enum {
    CIANWOODCITY_STANDING_YOUNGSTER = 2,
    CIANWOODCITY_POKEFAN_M,
    CIANWOODCITY_LASS,
    CIANWOODCITY_ROCK1,
    CIANWOODCITY_ROCK2,
    CIANWOODCITY_ROCK3,
    CIANWOODCITY_ROCK4,
    CIANWOODCITY_ROCK5,
    CIANWOODCITY_ROCK6,
    CIANWOODCITY_POKEFAN_F,
    CIANWOODCITY_EUSINE,
    CIANWOODCITY_SUICUNE,
};

const Script_fn_t CianwoodCity_SceneScripts[] = {
    CianwoodCity_MapScripts_DummyScene0 , //  SCENE_CIANWOODCITY_NOTHING,
    CianwoodCity_MapScripts_DummyScene1 , //  SCENE_CIANWOODCITY_SUICUNE_AND_EUSINE,
};

const struct MapCallback CianwoodCity_MapCallbacks[] = {
    map_callback(MAPCALLBACK_NEWMAP, CianwoodCity_MapScripts_FlyPointAndSuicune),
};

const struct MapScripts CianwoodCity_MapScripts = {
    .scene_script_count = lengthof(CianwoodCity_SceneScripts),
    .scene_scripts = CianwoodCity_SceneScripts,

    .callback_count = lengthof(CianwoodCity_MapCallbacks),
    .callbacks = CianwoodCity_MapCallbacks,
};

static const struct CoordEvent CianwoodCity_CoordEvents[] = {
    coord_event(11, 16, SCENE_CIANWOODCITY_SUICUNE_AND_EUSINE, &CianwoodCitySuicuneAndEusine),
};

static const struct BGEvent CianwoodCity_BGEvents[] = {
    bg_event(20, 34, BGEVENT_READ, &CianwoodCitySign),
    bg_event(7, 45, BGEVENT_READ, &CianwoodGymSign),
    bg_event(24, 43, BGEVENT_READ, &CianwoodPokecenterSign),
    bg_event(19, 47, BGEVENT_READ, &CianwoodPharmacySign),
    bg_event(8, 32, BGEVENT_READ, &CianwoodPhotoStudioSign),
    bg_event(8, 24, BGEVENT_READ, &CianwoodPokeSeerSign),
    bg_event(4, 19, BGEVENT_ITEM, &CianwoodCityHiddenRevive),
    bg_event(5, 29, BGEVENT_ITEM, &CianwoodCityHiddenMaxEther),
};

static const struct WarpEventData CianwoodCity_WarpEvents[] = {
    warp_event(17, 41, MANIAS_HOUSE, 1),
    warp_event(8, 43, CIANWOOD_GYM, 1),
    warp_event(23, 43, CIANWOOD_POKECENTER_1F, 1),
    warp_event(15, 47, CIANWOOD_PHARMACY, 1),
    warp_event(9, 31, CIANWOOD_PHOTO_STUDIO, 1),
    warp_event(15, 37, CIANWOOD_LUGIA_SPEECH_HOUSE, 1),
    warp_event(5, 17, POKE_SEERS_HOUSE, 1),
};

static const struct ObjEvent CianwoodCity_ObjectEvents[] = {
    object_event(21, 37, SPRITE_STANDING_YOUNGSTER, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &CianwoodCityYoungster, -1),
    object_event(17, 33, SPRITE_POKEFAN_M, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &CianwoodCityPokefanM, -1),
    object_event(14, 42, SPRITE_LASS, SPRITEMOVEDATA_WALK_UP_DOWN, 0, 2, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &CianwoodCityLass, -1),
    object_event(8, 16, SPRITE_ROCK, SPRITEMOVEDATA_SMASHABLE_ROCK, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &CianwoodCityRock, -1),
    object_event(9, 17, SPRITE_ROCK, SPRITEMOVEDATA_SMASHABLE_ROCK, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &CianwoodCityRock, -1),
    object_event(4, 25, SPRITE_ROCK, SPRITEMOVEDATA_SMASHABLE_ROCK, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &CianwoodCityRock, -1),
    object_event(5, 29, SPRITE_ROCK, SPRITEMOVEDATA_SMASHABLE_ROCK, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &CianwoodCityRock, -1),
    object_event(10, 27, SPRITE_ROCK, SPRITEMOVEDATA_SMASHABLE_ROCK, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &CianwoodCityRock, -1),
    object_event(4, 19, SPRITE_ROCK, SPRITEMOVEDATA_SMASHABLE_ROCK, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &CianwoodCityRock, -1),
    object_event(10, 46, SPRITE_POKEFAN_F, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &CianwoodCityChucksWife, -1),
    object_event(11, 21, SPRITE_SUPER_NERD, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, EVENT_CIANWOOD_CITY_EUSINE),
    object_event(10, 14, SPRITE_SUICUNE, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, EVENT_SAW_SUICUNE_AT_CIANWOOD_CITY),
};

const struct MapEvents CianwoodCity_MapEvents = {
    .warp_event_count = lengthof(CianwoodCity_WarpEvents),
    .warp_events = CianwoodCity_WarpEvents,

    .coord_event_count = lengthof(CianwoodCity_CoordEvents),
    .coord_events = CianwoodCity_CoordEvents,

    .bg_event_count = lengthof(CianwoodCity_BGEvents),
    .bg_events = CianwoodCity_BGEvents,

    .obj_event_count = lengthof(CianwoodCity_ObjectEvents),
    .obj_events = CianwoodCity_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "CianwoodCity.h"

bool CianwoodCity_MapScripts_DummyScene0(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool CianwoodCity_MapScripts_DummyScene1(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool CianwoodCity_MapScripts_FlyPointAndSuicune(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_FLYPOINT_CIANWOOD)
    setevent(EVENT_EUSINE_IN_BURNED_TOWER)
    checkevent(EVENT_FOUGHT_EUSINE)
    iffalse(Done)
    disappear(CIANWOODCITY_EUSINE)
Done:
    s_endcallback
    SCRIPT_END
}
bool CianwoodCitySuicuneAndEusine(script_s* s) {
    SCRIPT_BEGIN
    turnobject(PLAYER, UP)
    showemote(EMOTE_SHOCK, PLAYER, 15)
    pause(15)
    playsound(SFX_WARP_FROM)
    applymovement(CIANWOODCITY_SUICUNE, CianwoodCitySuicuneApproachMovement)
    turnobject(PLAYER, DOWN)
    pause(15)
    playsound(SFX_WARP_FROM)
    applymovement(CIANWOODCITY_SUICUNE, CianwoodCitySuicuneDepartMovement)
    disappear(CIANWOODCITY_SUICUNE)
    pause(10)
    setscene(SCENE_CIANWOODCITY_NOTHING)
    clearevent(EVENT_SAW_SUICUNE_ON_ROUTE_42)
    setmapscene(ROUTE_42, SCENE_ROUTE42_SUICUNE)
    checkevent(EVENT_FOUGHT_EUSINE)
    iftrue(Done)
    setevent(EVENT_FOUGHT_EUSINE)
    playmusic(MUSIC_MYSTICALMAN_ENCOUNTER)
    appear(CIANWOODCITY_EUSINE)
    applymovement(CIANWOODCITY_EUSINE, CianwoodCityEusineApproachMovement)
    opentext
    writetext(EusineSuicuneText)
    waitbutton
    closetext
    winlosstext(EusineBeatenText, 0)
    setlasttalked(CIANWOODCITY_EUSINE)
    loadtrainer(MYSTICALMAN, EUSINE)
    startbattle
    dontrestartmapmusic
    reloadmapafterbattle
    playmusic(MUSIC_MYSTICALMAN_ENCOUNTER)
    opentext
    writetext(EusineAfterText)
    waitbutton
    closetext
    applymovement(CIANWOODCITY_EUSINE, CianwoodCityEusineDepartMovement)
    disappear(CIANWOODCITY_EUSINE)
    pause(20)
    special(FadeOutMusic)
    playmapmusic
    pause(10)
Done:
    s_end
    SCRIPT_END
}
bool CianwoodCityChucksWife(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_HM02_FLY)
    iftrue(GotFly)
    writetext(ChucksWifeEasierToFlyText)
    promptbutton
    checkevent(EVENT_BEAT_CHUCK)
    iftrue(BeatChuck)
    writetext(ChucksWifeBeatChuckText)
    waitbutton
    closetext
    s_end
BeatChuck:
    writetext(ChucksWifeGiveHMText)
    promptbutton
    verbosegiveitem(HM_FLY, 1)
    iffalse(Done)
    setevent(EVENT_GOT_HM02_FLY)
    writetext(ChucksWifeFlySpeechText)
    promptbutton
GotFly:
    writetext(ChucksWifeChubbyText)
    waitbutton
Done:
    closetext
    s_end
    SCRIPT_END
}
bool CianwoodCityYoungster(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CianwoodCityYoungsterText)
    SCRIPT_END
}
bool CianwoodCityPokefanM(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CianwoodCityPokefanMText)
    SCRIPT_END
}
bool CianwoodCityLass(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CianwoodCityLassText)
    SCRIPT_END
}
bool CianwoodCityUnusedScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CianwoodCityUnusedText)
    SCRIPT_END
}
bool CianwoodCitySign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(CianwoodCitySignText)
    SCRIPT_END
}
bool CianwoodGymSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(CianwoodGymSignText)
    SCRIPT_END
}
bool CianwoodPharmacySign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(CianwoodPharmacySignText)
    SCRIPT_END
}
bool CianwoodPhotoStudioSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(CianwoodPhotoStudioSignText)
    SCRIPT_END
}
bool CianwoodPokeSeerSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(CianwoodPokeSeerSignText)
    SCRIPT_END
}
bool CianwoodPokecenterSign(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PokecenterSignScript)
    SCRIPT_END
}
bool CianwoodCityRock(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(SmashRockScript)
    SCRIPT_END
}
const struct HiddenItem CianwoodCityHiddenRevive = {REVIVE, EVENT_CIANWOOD_CITY_HIDDEN_REVIVE};
const struct HiddenItem CianwoodCityHiddenMaxEther = {MAX_ETHER, EVENT_CIANWOOD_CITY_HIDDEN_MAX_ETHER};
const uint8_t CianwoodCitySuicuneApproachMovement[] = {
    movement_set_sliding,
    fast_jump_step(DOWN),
    fast_jump_step(DOWN),
    fast_jump_step(RIGHT),
    movement_remove_sliding,
    movement_step_end,
};
const uint8_t CianwoodCitySuicuneDepartMovement[] = {
    movement_set_sliding,
    fast_jump_step(RIGHT),
    fast_jump_step(UP),
    fast_jump_step(RIGHT),
    fast_jump_step(RIGHT),
    movement_remove_sliding,
    movement_step_end,
};
const uint8_t CianwoodCityEusineApproachMovement[] = {
    step(UP),
    step(UP),
    step(UP),
    step(UP),
    movement_step_end,
};
const uint8_t CianwoodCityEusineDepartMovement[] = {
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    movement_step_end,
};
const txt_cmd_s ChucksWifeEasierToFlyText[] = {
    text_start("You crossed the"
        t_line "sea to get here?"
        t_para "That must have"
        t_line "been hard."
        t_para "It would be much"
        t_line "easier if your"
        t_para "#MON knew how"
        t_line "to FLY…"
        t_done )
};
const txt_cmd_s ChucksWifeBeatChuckText[] = {
    text_start("But you can't use"
        t_line "FLY without this"
        t_cont "city's GYM BADGE."
        t_para "If you beat the"
        t_line "GYM LEADER here,"
        t_cont "come see me."
        t_para "I'll have a nice"
        t_line "gift for you."
        t_done )
};
const txt_cmd_s ChucksWifeGiveHMText[] = {
    text_start("That's CIANWOOD's"
        t_line "GYM BADGE!"
        t_para "Then you should"
        t_line "take this HM."
        t_done )
};
const txt_cmd_s ChucksWifeFlySpeechText[] = {
    text_start("Teach FLY to your"
        t_line "#MON."
        t_para "You will be able"
        t_line "to FLY instantly"
        t_para "to anywhere you "
        t_line "have visited."
        t_done )
};
const txt_cmd_s ChucksWifeChubbyText[] = {
    text_start("My husband lost to"
        t_line "you, so he needs"
        t_cont "to train harder."
        t_para "That's good, since"
        t_line "he was getting a"
        t_cont "little chubby."
        t_done )
};
const txt_cmd_s CianwoodCityYoungsterText[] = {
    text_start("If you use FLY,"
        t_line "you can get back"
        t_para "to OLIVINE in-"
        t_line "stantly."
        t_done )
};
const txt_cmd_s CianwoodCityPokefanMText[] = {
    text_start("Boulders to the"
        t_line "north of town can"
        t_cont "be crushed."
        t_para "They may be hiding"
        t_line "something."
        t_para "Your #MON could"
        t_line "use ROCK SMASH to"
        t_cont "break them."
        t_done )
};
const txt_cmd_s CianwoodCityLassText[] = {
    text_start("CHUCK, the GYM"
        t_line "LEADER, spars with"
        t_para "his fighting #-"
        t_line "MON."
        t_done )
};
const txt_cmd_s CianwoodCityUnusedText[] = {
    text_start("There are several"
        t_line "islands between"
        t_cont "here and OLIVINE."
        t_para "A mythical sea"
        t_line "creature supposed-"
        t_cont "ly lives there."
        t_done )
};
const txt_cmd_s EusineSuicuneText[] = {
    text_start("EUSINE: Yo,"
        t_line "<PLAYER>."
        t_para "Wasn't that"
        t_line "SUICUNE just now?"
        t_para "I only caught a"
        t_line "quick glimpse, but"
        t_para "I thought I saw"
        t_line "SUICUNE running on"
        t_cont "the waves."
        t_para "SUICUNE is beau-"
        t_line "tiful and grand."
        t_para "And it races"
        t_line "through towns and"
        t_para "roads at simply"
        t_line "awesome speeds."
        t_para "It's wonderful…"
        t_para "I want to see"
        t_line "SUICUNE up close…"
        t_para "I've decided."
        t_para "I'll battle you as"
        t_line "a trainer to earn"
        t_cont "SUICUNE's respect!"
        t_para "Come on, <PLAYER>."
        t_line "Let's battle now!"
        t_done )
};
const txt_cmd_s EusineBeatenText[] = {
    text_start("I hate to admit"
        t_line "it, but you win."
        t_done )
};
const txt_cmd_s EusineAfterText[] = {
    text_start("You're amazing,"
        t_line "<PLAYER>!"
        t_para "No wonder #MON"
        t_line "gravitate to you."
        t_para "I get it now."
        t_para "I'm going to keep"
        t_line "searching for"
        t_cont "SUICUNE."
        t_para "I'm sure we'll see"
        t_line "each other again."
        t_para "See you around!"
        t_done )
};
const txt_cmd_s CianwoodCitySignText[] = {
    text_start("CIANWOOD CITY"
        t_para "A Port Surrounded"
        t_line "by Rough Seas"
        t_done )
};
const txt_cmd_s CianwoodGymSignText[] = {
    text_start("CIANWOOD CITY"
        t_line "#MON GYM"
        t_para "LEADER: CHUCK"
        t_para "His Roaring Fists"
        t_line "Do the Talking"
        t_done )
};
const txt_cmd_s CianwoodPharmacySignText[] = {
    text_start("500 Years of"
        t_line "Tradition"
        t_para "CIANWOOD CITY"
        t_line "PHARMACY"
        t_para "We Await Your"
        t_line "Medicinal Queries"
        t_done )
};
const txt_cmd_s CianwoodPhotoStudioSignText[] = {
    text_start("CIANWOOD CITY"
        t_line "PHOTO STUDIO"
        t_para "Take a Snapshot as"
        t_line "a Keepsake!"
        t_done )
};
const txt_cmd_s CianwoodPokeSeerSignText[] = {
    text_start("THE # SEER"
        t_line "AHEAD"
        t_done )
    //db(0, 0) // filler
};
