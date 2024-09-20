#include "../constants.h"
#include "../util/scripting.h"
#include "BluesHouse.h"
//// EVENTS
enum {
    BLUESHOUSE_DAISY = 2,
};

const Script_fn_t BluesHouse_SceneScripts[] = {
    0,
};

const struct MapCallback BluesHouse_MapCallbacks[] = {
    0,
};

const struct MapScripts BluesHouse_MapScripts = {
    .scene_script_count = 0, // lengthof(BluesHouse_SceneScripts),
    .scene_scripts = BluesHouse_SceneScripts,

    .callback_count = 0, // lengthof(BluesHouse_MapCallbacks),
    .callbacks = BluesHouse_MapCallbacks,
};

static const struct CoordEvent BluesHouse_CoordEvents[] = {
    0,
};

static const struct BGEvent BluesHouse_BGEvents[] = {
    0,
};

static const struct WarpEventData BluesHouse_WarpEvents[] = {
    warp_event(2, 7, PALLET_TOWN, 2),
    warp_event(3, 7, PALLET_TOWN, 2),
};

static const struct ObjEvent BluesHouse_ObjectEvents[] = {
    object_event(2, 3, SPRITE_DAISY, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &DaisyScript, -1),
};

const struct MapEvents BluesHouse_MapEvents = {
    .warp_event_count = lengthof(BluesHouse_WarpEvents),
    .warp_events = BluesHouse_WarpEvents,

    .coord_event_count = 0, // lengthof(BluesHouse_CoordEvents),
    .coord_events = BluesHouse_CoordEvents,

    .bg_event_count = 0, // lengthof(BluesHouse_BGEvents),
    .bg_events = BluesHouse_BGEvents,

    .obj_event_count = lengthof(BluesHouse_ObjectEvents),
    .obj_events = BluesHouse_ObjectEvents,
};

//// CODE

bool DaisyScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    readvar(VAR_HOUR)
    ifequal(15, ThreePM)
    writetext(DaisyHelloText)
    waitbutton
    closetext
    s_end
ThreePM:
    checkflag(ENGINE_DAISYS_GROOMING)
    iftrue(AlreadyGroomedMon)
    writetext(DaisyOfferGroomingText)
    yesorno
    iffalse(Refused)
    writetext(DaisyWhichMonText)
    waitbutton
    special(DaisysGrooming)
    ifequal(0x0, Refused)
    ifequal(0x1, CantGroomEgg)
    setflag(ENGINE_DAISYS_GROOMING)
    writetext(DaisyAlrightText)
    waitbutton
    closetext
    special(FadeOutPalettes)
    playmusic(MUSIC_HEAL)
    pause(60)
    special(FadeInPalettes)
    special(RestartMapMusic)
    opentext
    writetext(GroomedMonLooksContentText)
    special(PlayCurMonCry)
    promptbutton
    writetext(DaisyAllDoneText)
    waitbutton
    closetext
    s_end
AlreadyGroomedMon:
    writetext(DaisyAlreadyGroomedText)
    waitbutton
    closetext
    s_end
Refused:
    writetext(DaisyRefusedText)
    waitbutton
    closetext
    s_end
CantGroomEgg:
    writetext(DaisyCantGroomEggText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const txt_cmd_s DaisyHelloText[] = {
    text_start("DAISY: Hi! My kid"
        t_line "brother is the GYM"
        t_para "LEADER in VIRIDIAN"
        t_line "CITY."
        t_para "But he goes out"
        t_line "of town so often,"
        t_para "it causes problems"
        t_line "for the trainers."
        t_done )
};
const txt_cmd_s DaisyOfferGroomingText[] = {
    text_start("DAISY: Hi! Good"
        t_line "timing. I'm about"
        t_cont "to have some tea."
        t_para "Would you like to"
        t_line "join me?"
        t_para "Oh, your #MON"
        t_line "are a bit dirty."
        t_para "Would you like me"
        t_line "to groom one?"
        t_done )
};
const txt_cmd_s DaisyWhichMonText[] = {
    text_start("DAISY: Which one"
        t_line "should I groom?"
        t_done )
};
const txt_cmd_s DaisyAlrightText[] = {
    text_start("DAISY: OK, I'll"
        t_line "get it looking"
        t_cont "nice in no time."
        t_done )
};
const txt_cmd_s GroomedMonLooksContentText[] = {
    text_ram(wram_ptr(wStringBuffer3))
    text_start(" looks"
        t_line "content."
        t_done )
};
const txt_cmd_s DaisyAllDoneText[] = {
    text_start("DAISY: There you"
        t_line "go! All done."
        t_para "See? Doesn't it"
        t_line "look nice?"
        t_para "It's such a cute"
        t_line "#MON."
        t_done )
};
const txt_cmd_s DaisyAlreadyGroomedText[] = {
    text_start("DAISY: I always"
        t_line "have tea around"
        t_para "this time. Come"
        t_line "join me."
        t_done )
};
const txt_cmd_s DaisyRefusedText[] = {
    text_start("DAISY: You don't"
        t_line "want to have one"
        t_para "groomed? OK, we'll"
        t_line "just have tea."
        t_done )
};
const txt_cmd_s DaisyCantGroomEggText[] = {
    text_start("DAISY: Oh, sorry."
        t_line "I honestly can't"
        t_cont "groom an EGG."
        t_done )
    //db(0, 0) // filler
};
