#include "../constants.h"
#include "../util/scripting.h"
#include "ManiasHouse.h"
//// EVENTS
enum {
    MANIASHOUSE_ROCKER = 2,
};

const Script_fn_t ManiasHouse_SceneScripts[] = {
    0,
};

const struct MapCallback ManiasHouse_MapCallbacks[] = {
    0,
};

const struct MapScripts ManiasHouse_MapScripts = {
    .scene_script_count = 0, // lengthof(ManiasHouse_SceneScripts),
    .scene_scripts = ManiasHouse_SceneScripts,

    .callback_count = 0, // lengthof(ManiasHouse_MapCallbacks),
    .callbacks = ManiasHouse_MapCallbacks,
};

static const struct CoordEvent ManiasHouse_CoordEvents[] = {
    0,
};

static const struct BGEvent ManiasHouse_BGEvents[] = {
    0,
};

static const struct WarpEventData ManiasHouse_WarpEvents[] = {
    warp_event(2, 7, CIANWOOD_CITY, 1),
    warp_event(3, 7, CIANWOOD_CITY, 1),
};

static const struct ObjEvent ManiasHouse_ObjectEvents[] = {
    object_event(2, 4, SPRITE_ROCKER, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &ManiaScript, -1),
};

const struct MapEvents ManiasHouse_MapEvents = {
    .warp_event_count = lengthof(ManiasHouse_WarpEvents),
    .warp_events = ManiasHouse_WarpEvents,

    .coord_event_count = 0, // lengthof(ManiasHouse_CoordEvents),
    .coord_events = ManiasHouse_CoordEvents,

    .bg_event_count = 0, // lengthof(ManiasHouse_BGEvents),
    .bg_events = ManiasHouse_BGEvents,

    .obj_event_count = lengthof(ManiasHouse_ObjectEvents),
    .obj_events = ManiasHouse_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "ManiasHouse.h"

bool ManiaScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_MANIA_TOOK_SHUCKIE_OR_LET_YOU_KEEP_HIM)
    iftrue(default_postevent)
    checkevent(EVENT_GOT_SHUCKIE)
    iftrue(alreadyhaveshuckie)
    writetext(ManiaText_AskLookAfterShuckle)
    yesorno
    iffalse(refusetotakeshuckie)
    special(GiveShuckle)
    iffalse(partyfull)
    writetext(ManiaText_TakeCareOfShuckle)
    promptbutton
    waitsfx
    writetext(ManiaText_GotShuckle)
    playsound(SFX_KEY_ITEM)
    waitsfx
    closetext
    setevent(EVENT_GOT_SHUCKIE)
    s_end
alreadyhaveshuckie:
    checkflag(ENGINE_GOT_SHUCKIE_TODAY)
    iffalse(returnshuckie)
    writetext(ManiaText_TakeCareOfShuckle)
    waitbutton
    closetext
    s_end
partyfull:
    writetext(ManiaText_PartyFull)
    waitbutton
    closetext
    s_end
refusetotakeshuckie:
    writetext(ManiaText_IfHeComesBack)
    waitbutton
    closetext
    s_end
returnshuckie:
    writetext(ManiaText_CanIHaveMyMonBack)
    yesorno
    iffalse(refused)
    special(ReturnShuckie)
    ifequal(SHUCKIE_WRONG_MON, wrong)
    ifequal(SHUCKIE_REFUSED, refused)
    ifequal(SHUCKIE_HAPPY, superhappy)
    ifequal(SHUCKIE_FAINTED, default_postevent)
    // SHUCKIE_RETURNED
    writetext(ManiaText_ThankYou)
    waitbutton
    closetext
    setevent(EVENT_MANIA_TOOK_SHUCKIE_OR_LET_YOU_KEEP_HIM)
    s_end
wrong:
    writetext(ManiaText_ShuckleNotThere)
    waitbutton
    closetext
    s_end
superhappy:
    writetext(ManiaText_ShuckleLikesYou)
    waitbutton
    closetext
    setevent(EVENT_MANIA_TOOK_SHUCKIE_OR_LET_YOU_KEEP_HIM)
    s_end
refused:
    writetext(ManiaText_SameAsBeingRobbed)
    waitbutton
    closetext
    s_end
nothingleft: // unreferenced:
    writetext(ManiaText_ShuckleIsYourLastMon)
    waitbutton
    closetext
    s_end
default_postevent:
    writetext(ManiaText_HappinessSpeech)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool ManiasHouseUnusedBookshelf(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PictureBookshelfScript)
    SCRIPT_END
}
const txt_cmd_s ManiaText_AskLookAfterShuckle[] = {
    text_start("I, I'm in shock!"
        t_para "A guy about your"
        t_line "age with piercing"
        t_para "eyes and long hair"
        t_line "came in."
        t_para "He scared me into"
        t_line "giving him my"
        t_cont "prized #MON!"
        t_para "I still have one"
        t_line "left, but what if"
        t_cont "he comes back?"
        t_para "You look strong."
        t_line "Could you look"
        t_para "after my #MON"
        t_line "for a while?"
        t_done )
};
const txt_cmd_s ManiaText_TakeCareOfShuckle[] = {
    text_start("Oh, thank you!"
        t_para "Take good care of"
        t_line "it, please!"
        t_done )
};
const txt_cmd_s ManiaText_GotShuckle[] = {
    text_start("<PLAYER> received a"
        t_line "#MON."
        t_done )
};
const txt_cmd_s ManiaText_PartyFull[] = {
    text_start("Your #MON party"
        t_line "is full."
        t_done )
};
const txt_cmd_s ManiaText_IfHeComesBack[] = {
    text_start("Oh, no… What'll"
        t_line "I do if he comes"
        t_cont "back?"
        t_done )
};
const txt_cmd_s ManiaText_CanIHaveMyMonBack[] = {
    text_start("Hi! How's my #-"
        t_line "MON?"
        t_para "I think I'm safe"
        t_line "now, so may I have"
        t_cont "it back?"
        t_done )
};
const txt_cmd_s ManiaText_ThankYou[] = {
    text_start("Thank you!"
        t_done )
};
const txt_cmd_s ManiaText_ShuckleNotThere[] = {
    text_start("Hey, you don't"
        t_line "have my #MON"
        t_cont "with you."
        t_done )
};
const txt_cmd_s ManiaText_ShuckleLikesYou[] = {
    text_start("My #MON has"
        t_line "come to like you."
        t_para "All right, you"
        t_line "should keep it."
        t_para "But promise to"
        t_line "be good to it!"
        t_done )
};
const txt_cmd_s ManiaText_SameAsBeingRobbed[] = {
    text_start("Oh, no, no… That's"
        t_line "the same as being"
        t_cont "robbed."
        t_done )
};
const txt_cmd_s ManiaText_HappinessSpeech[] = {
    text_start("For #MON, hap-"
        t_line "piness is being"
        t_para "with a person who"
        t_line "treats them well."
        t_done )
};
const txt_cmd_s ManiaText_ShuckleIsYourLastMon[] = {
    text_start("If I take my #-"
        t_line "MON back, what are"
        t_para "you going to use"
        t_line "in battle?"
        t_done )
    //db(0, 0) // filler
};
