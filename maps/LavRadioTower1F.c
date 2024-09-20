#include "../constants.h"
#include "../util/scripting.h"
#include "LavRadioTower1F.h"
//// EVENTS
enum {
    LAVRADIOTOWER1F_RECEPTIONIST = 2,
    LAVRADIOTOWER1F_OFFICER,
    LAVRADIOTOWER1F_SUPER_NERD1,
    LAVRADIOTOWER1F_GENTLEMAN,
    LAVRADIOTOWER1F_SUPER_NERD2,
};

const Script_fn_t LavRadioTower1F_SceneScripts[] = {
    0,
};

const struct MapCallback LavRadioTower1F_MapCallbacks[] = {
    0,
};

const struct MapScripts LavRadioTower1F_MapScripts = {
    .scene_script_count = 0, // lengthof(LavRadioTower1F_SceneScripts),
    .scene_scripts = LavRadioTower1F_SceneScripts,

    .callback_count = 0, // lengthof(LavRadioTower1F_MapCallbacks),
    .callbacks = LavRadioTower1F_MapCallbacks,
};

static const struct CoordEvent LavRadioTower1F_CoordEvents[] = {
    0,
};

static const struct BGEvent LavRadioTower1F_BGEvents[] = {
    bg_event(11, 0, BGEVENT_READ, &LavRadioTower1FDirectory),
    bg_event(5, 0, BGEVENT_READ, &LavRadioTower1FPokeFluteSign),
};

static const struct WarpEventData LavRadioTower1F_WarpEvents[] = {
    warp_event(2, 7, LAVENDER_TOWN, 7),
    warp_event(3, 7, LAVENDER_TOWN, 7),
};

static const struct ObjEvent LavRadioTower1F_ObjectEvents[] = {
    object_event(6, 6, SPRITE_RECEPTIONIST, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &LavRadioTower1FReceptionistScript, -1),
    object_event(15, 1, SPRITE_OFFICER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &LavRadioTower1FOfficerScript, -1),
    object_event(1, 3, SPRITE_SUPER_NERD, SPRITEMOVEDATA_WANDER, 1, 1, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &LavRadioTower1FSuperNerd1Script, -1),
    object_event(9, 1, SPRITE_GENTLEMAN, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &LavRadioTower1FGentlemanScript, -1),
    object_event(14, 6, SPRITE_SUPER_NERD, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &LavRadioTower1FSuperNerd2Script, -1),
};

const struct MapEvents LavRadioTower1F_MapEvents = {
    .warp_event_count = lengthof(LavRadioTower1F_WarpEvents),
    .warp_events = LavRadioTower1F_WarpEvents,

    .coord_event_count = 0, // lengthof(LavRadioTower1F_CoordEvents),
    .coord_events = LavRadioTower1F_CoordEvents,

    .bg_event_count = lengthof(LavRadioTower1F_BGEvents),
    .bg_events = LavRadioTower1F_BGEvents,

    .obj_event_count = lengthof(LavRadioTower1F_ObjectEvents),
    .obj_events = LavRadioTower1F_ObjectEvents,
};

//// CODE

bool LavRadioTower1FReceptionistScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(LavRadioTower1FReceptionistText)
    SCRIPT_END
}
bool LavRadioTower1FOfficerScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(LavRadioTower1FOfficerText)
    SCRIPT_END
}
bool LavRadioTower1FSuperNerd1Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(LavRadioTower1FSuperNerd1Text)
    SCRIPT_END
}
bool LavRadioTower1FGentlemanScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkflag(ENGINE_EXPN_CARD)
    iftrue(GotExpnCard)
    checkevent(EVENT_RETURNED_MACHINE_PART)
    iftrue(ReturnedMachinePart)
    writetext(LavRadioTower1FGentlemanText)
    waitbutton
    closetext
    s_end
ReturnedMachinePart:
    writetext(LavRadioTower1FGentlemanText_ReturnedMachinePart)
    promptbutton
    getstring(STRING_BUFFER_4, expncardname)
    scall_local(receiveitem);
    setflag(ENGINE_EXPN_CARD)
GotExpnCard:
    writetext(LavRadioTower1FGentlemanText_GotExpnCard)
    waitbutton
    closetext
    s_end
receiveitem:
    jumpstd(ReceiveItemScript)
    s_end
    SCRIPT_END
}
const char expncardname[] = "EXPN CARD@";
bool LavRadioTower1FSuperNerd2Script(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkflag(ENGINE_EXPN_CARD)
    iftrue(GotExpnCard)
    writetext(LavRadioTower1FSuperNerd2Text)
    waitbutton
    closetext
    s_end
GotExpnCard:
    writetext(LavRadioTower1FSuperNerd2Text_GotExpnCard)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool LavRadioTower1FDirectory(script_s* s) {
    SCRIPT_BEGIN
    jumptext(LavRadioTower1FDirectoryText)
    SCRIPT_END
}
bool LavRadioTower1FPokeFluteSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(LavRadioTower1FPokeFluteSignText)
    SCRIPT_END
}
bool LavRadioTower1FReferenceLibrary(script_s* s) {
    SCRIPT_BEGIN
    jumptext(LavRadioTower1FReferenceLibraryText)
    SCRIPT_END
}
const txt_cmd_s LavRadioTower1FReceptionistText[] = {
    text_start("Welcome!"
        t_line "Feel free to look"
        t_para "around anywhere on"
        t_line "this floor."
        t_done )
};
const txt_cmd_s LavRadioTower1FOfficerText[] = {
    text_start("Sorry, but you can"
        t_line "only tour the"
        t_cont "ground floor."
        t_para "Ever since JOHTO's"
        t_line "RADIO TOWER was"
        t_para "taken over by a"
        t_line "criminal gang, we"
        t_para "have had to step"
        t_line "up our security."
        t_done )
};
const txt_cmd_s LavRadioTower1FSuperNerd1Text[] = {
    text_start("Many people are"
        t_line "hard at work here"
        t_para "in the RADIO"
        t_line "TOWER."
        t_para "They must be doing"
        t_line "their best to put"
        t_cont "on good shows."
        t_done )
};
const txt_cmd_s LavRadioTower1FGentlemanText[] = {
    text_start("Oh, no, no, no!"
        t_para "We've been off the"
        t_line "air ever since the"
        t_para "POWER PLANT shut"
        t_line "down."
        t_para "All my efforts to"
        t_line "start this station"
        t_para "would be wasted if"
        t_line "I can't broadcast."
        t_para "I'll be ruined!"
        t_done )
};
const txt_cmd_s LavRadioTower1FGentlemanText_ReturnedMachinePart[] = {
    text_start("Ah! So you're the"
        t_line "<PLAY_G> who solved"
        t_para "the POWER PLANT's"
        t_line "problem?"
        t_para "Thanks to you, I"
        t_line "never lost my job."
        t_para "I tell you, you're"
        t_line "a real lifesaver!"
        t_para "Please take this"
        t_line "as my thanks."
        t_done )
};
const txt_cmd_s LavRadioTower1FGentlemanText_GotExpnCard[] = {
    text_start("With that thing,"
        t_line "you can tune into"
        t_para "the radio programs"
        t_line "here in KANTO."
        t_para "Gahahahaha!"
        t_done )
};
const txt_cmd_s LavRadioTower1FSuperNerd2Text[] = {
    text_start("Hey there!"
        t_para "I am the super"
        t_line "MUSIC DIRECTOR!"
        t_para "Huh? Your #GEAR"
        t_line "can't tune into my"
        t_para "music programs."
        t_line "How unfortunate!"
        t_para "If you get an EXPN"
        t_line "CARD upgrade, you"
        t_para "can tune in. You'd"
        t_line "better get one!"
        t_done )
};
const txt_cmd_s LavRadioTower1FSuperNerd2Text_GotExpnCard[] = {
    text_start("Hey there!"
        t_para "I am the super"
        t_line "MUSIC DIRECTOR!"
        t_para "I'm responsible"
        t_line "for the gorgeous"
        t_para "melodies that go"
        t_line "out over the air."
        t_para "Don't be square."
        t_line "Grab your music"
        t_cont "off the air!"
        t_done )
};
const txt_cmd_s LavRadioTower1FDirectoryText[] = {
    text_start("1F RECEPTION"
        t_line "2F SALES"
        t_para "3F PERSONNEL"
        t_line "4F PRODUCTION"
        t_para "5F DIRECTOR'S"
        t_line "   OFFICE"
        t_done )
};
const txt_cmd_s LavRadioTower1FPokeFluteSignText[] = {
    text_start("Perk Up #MON"
        t_line "with Mellow Sounds"
        t_para "of the # FLUTE"
        t_line "on CHANNEL 20"
        t_done )
};
const txt_cmd_s LavRadioTower1FReferenceLibraryText[] = {
    text_start("Wow! A full rack"
        t_line "of #MON CDs and"
        t_cont "videos."
        t_para "This must be the"
        t_line "reference library."
        t_done )
    //db(0, 0) // filler
};
