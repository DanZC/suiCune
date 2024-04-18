#include "../constants.h"
#include "../util/scripting.h"
#include "RuinsOfAlphResearchCenter.h"
//// EVENTS
enum {
    RUINSOFALPHRESEARCHCENTER_SCIENTIST1 = 2,
    RUINSOFALPHRESEARCHCENTER_SCIENTIST2,
    RUINSOFALPHRESEARCHCENTER_SCIENTIST3,
};

const Script_fn_t RuinsOfAlphResearchCenter_SceneScripts[] = {
    RuinsOfAlphResearchCenter_MapScripts_DummyScene0 , //  SCENE_RUINSOFALPHRESEARCHCENTER_NOTHING,
    RuinsOfAlphResearchCenter_MapScripts_GetUnownDex , //  SCENE_RUINSOFALPHRESEARCHCENTER_GET_UNOWN_DEX,
};

const struct MapCallback RuinsOfAlphResearchCenter_MapCallbacks[] = {
    map_callback(MAPCALLBACK_OBJECTS, RuinsOfAlphResearchCenter_MapScripts_ScientistCallback),
};

const struct MapScripts RuinsOfAlphResearchCenter_MapScripts = {
    .scene_script_count = lengthof(RuinsOfAlphResearchCenter_SceneScripts),
    .scene_scripts = RuinsOfAlphResearchCenter_SceneScripts,

    .callback_count = lengthof(RuinsOfAlphResearchCenter_MapCallbacks),
    .callbacks = RuinsOfAlphResearchCenter_MapCallbacks,
};

static const struct CoordEvent RuinsOfAlphResearchCenter_CoordEvents[] = {
    0,
};

static const struct BGEvent RuinsOfAlphResearchCenter_BGEvents[] = {
    bg_event(6, 5, BGEVENT_READ, &RuinsOfAlphResearchCenterBookshelf),
    bg_event(3, 4, BGEVENT_READ, &RuinsOfAlphResearchCenterComputer),
    bg_event(7, 1, BGEVENT_READ, &RuinsOfAlphResearchCenterPrinter),
};

static const struct WarpEventData RuinsOfAlphResearchCenter_WarpEvents[] = {
    warp_event(2, 7, RUINS_OF_ALPH_OUTSIDE, 6),
    warp_event(3, 7, RUINS_OF_ALPH_OUTSIDE, 6),
};

static const struct ObjEvent RuinsOfAlphResearchCenter_ObjectEvents[] = {
    object_event(4, 5, SPRITE_SCIENTIST, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &RuinsOfAlphResearchCenterScientist1Script, -1),
    object_event(5, 2, SPRITE_SCIENTIST, SPRITEMOVEDATA_WANDER, 2, 1, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &RuinsOfAlphResearchCenterScientist2Script, -1),
    object_event(2, 5, SPRITE_SCIENTIST, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &RuinsOfAlphResearchCenterScientist3Script, EVENT_RUINS_OF_ALPH_RESEARCH_CENTER_SCIENTIST),
};

const struct MapEvents RuinsOfAlphResearchCenter_MapEvents = {
    .warp_event_count = lengthof(RuinsOfAlphResearchCenter_WarpEvents),
    .warp_events = RuinsOfAlphResearchCenter_WarpEvents,

    .coord_event_count = 0, // lengthof(RuinsOfAlphResearchCenter_CoordEvents),
    .coord_events = RuinsOfAlphResearchCenter_CoordEvents,

    .bg_event_count = lengthof(RuinsOfAlphResearchCenter_BGEvents),
    .bg_events = RuinsOfAlphResearchCenter_BGEvents,

    .obj_event_count = lengthof(RuinsOfAlphResearchCenter_ObjectEvents),
    .obj_events = RuinsOfAlphResearchCenter_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "RuinsOfAlphResearchCenter.h"

bool RuinsOfAlphResearchCenter_MapScripts_DummyScene0(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool RuinsOfAlphResearchCenter_MapScripts_GetUnownDex(script_s* s) {
    SCRIPT_BEGIN
    sdefer(RuinsOfAlphResearchCenter_MapScripts_GetUnownDexScript);
    s_end
    SCRIPT_END
}
bool RuinsOfAlphResearchCenter_MapScripts_ScientistCallback(script_s* s) {
    SCRIPT_BEGIN
    checkscene
    ifequal_jump(SCENE_RUINSOFALPHRESEARCHCENTER_GET_UNOWN_DEX, RuinsOfAlphResearchCenter_MapScripts_ShowScientist)
    s_endcallback
    SCRIPT_END
}
bool RuinsOfAlphResearchCenter_MapScripts_ShowScientist(script_s* s) {
    SCRIPT_BEGIN
    moveobject(RUINSOFALPHRESEARCHCENTER_SCIENTIST3, 3, 7)
    appear(RUINSOFALPHRESEARCHCENTER_SCIENTIST3)
    s_endcallback
    SCRIPT_END
}
bool RuinsOfAlphResearchCenter_MapScripts_GetUnownDexScript(script_s* s) {
    SCRIPT_BEGIN
    applymovement(RUINSOFALPHRESEARCHCENTER_SCIENTIST3, RuinsOfAlphResearchCenterApproachesComputerMovement)
    playsound(SFX_BOOT_PC)
    pause(60)
    playsound(SFX_SWITCH_POKEMON)
    pause(30)
    playsound(SFX_TALLY)
    pause(30)
    playsound(SFX_TRANSACTION)
    pause(30)
    turnobject(RUINSOFALPHRESEARCHCENTER_SCIENTIST3, DOWN)
    opentext
    writetext(RuinsOfAlphResearchCenterModifiedDexText)
    waitbutton
    closetext
    applymovement(RUINSOFALPHRESEARCHCENTER_SCIENTIST3, RuinsOfAlphResearchCenterApproachesPlayerMovement)
    opentext
    writetext(RuinsOfAlphResearchCenterDexUpgradedText)
    playsound(SFX_ITEM)
    waitsfx
    setflag(ENGINE_UNOWN_DEX)
    writetext(RuinsOfAlphResearchCenterScientist3Text)
    waitbutton
    closetext
    applymovement(RUINSOFALPHRESEARCHCENTER_SCIENTIST3, RuinsOfAlphResearchCenterLeavesPlayerMovement)
    setscene(SCENE_RUINSOFALPHRESEARCHCENTER_NOTHING)
    special(RestartMapMusic)
    s_end
    SCRIPT_END
}
bool RuinsOfAlphResearchCenterScientist3Script(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    readvar(VAR_UNOWNCOUNT)
    ifequal(NUM_UNOWN, PrinterAvailable)
    writetext(RuinsOfAlphResearchCenterScientist3Text)
    waitbutton
    closetext
    s_end
PrinterAvailable:
    writetext(RuinsOfAlphResearchCenterScientist3_PrinterAvailable)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool RuinsOfAlphResearchCenterScientist1Script(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    readvar(VAR_UNOWNCOUNT)
    ifequal(NUM_UNOWN, GotAllUnown)
    checkflag(ENGINE_UNOWN_DEX)
    iftrue(GotUnownDex)
    checkevent(EVENT_MADE_UNOWN_APPEAR_IN_RUINS)
    iftrue(UnownAppeared)
    writetext(RuinsOfAlphResearchCenterScientist1Text)
    waitbutton
    closetext
    s_end
UnownAppeared:
    writetext(RuinsOfAlphResearchCenterScientist1Text_UnownAppeared)
    waitbutton
    closetext
    s_end
GotUnownDex:
    writetext(RuinsOfAlphResearchCenterScientist1Text_GotUnownDex)
    waitbutton
    closetext
    s_end
GotAllUnown:
    writetext(RuinsOfAlphResearchCenterScientist1Text_GotAllUnown)
    waitbutton
    closetext
    clearevent(EVENT_RUINS_OF_ALPH_OUTSIDE_TOURIST_YOUNGSTERS)
    s_end
    SCRIPT_END
}
bool RuinsOfAlphResearchCenterScientist2Script(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    readvar(VAR_UNOWNCOUNT)
    ifequal(NUM_UNOWN, GotAllUnown)
    checkevent(EVENT_MADE_UNOWN_APPEAR_IN_RUINS)
    iftrue(UnownAppeared)
    writetext(RuinsOfAlphResearchCenterScientist2Text)
    waitbutton
    closetext
    s_end
UnownAppeared:
    writetext(RuinsOfAlphResearchCenterScientist2Text_UnownAppeared)
    waitbutton
    closetext
    s_end
GotAllUnown:
    writetext(RuinsOfAlphResearchCenterScientist2Text_GotAllUnown)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool RuinsOfAlphResearchCenterComputer(script_s* s) {
    SCRIPT_BEGIN
    opentext
    checkevent(EVENT_RUINS_OF_ALPH_RESEARCH_CENTER_SCIENTIST)
    iftrue(SkipChecking)
    readvar(VAR_UNOWNCOUNT)
    ifequal(NUM_UNOWN, GotAllUnown)
SkipChecking:
    writetext(RuinsOfAlphResearchCenterComputerText)
    waitbutton
    closetext
    s_end
GotAllUnown:
    writetext(RuinsOfAlphResearchCenterComputerText_GotAllUnown)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool RuinsOfAlphResearchCenterPrinter(script_s* s) {
    SCRIPT_BEGIN
    opentext
    checkevent(EVENT_RUINS_OF_ALPH_RESEARCH_CENTER_SCIENTIST)
    iftrue(SkipChecking)
    readvar(VAR_UNOWNCOUNT)
    ifequal(NUM_UNOWN, PrinterAvailable)
SkipChecking:
    writetext(RuinsOfAlphResearchCenterPrinterText_DoesntWork)
    waitbutton
    closetext
    s_end
PrinterAvailable:
    writetext(RuinsOfAlphResearchCenterUnownPrinterText)
    waitbutton
    special(UnownPrinter)
    closetext
    s_end
    SCRIPT_END
}
bool RuinsOfAlphResearchCenterPhoto(script_s* s) {
    SCRIPT_BEGIN
    jumptext(RuinsOfAlphResearchCenterProfSilktreePhotoText)
    SCRIPT_END
}
bool RuinsOfAlphResearchCenterBookshelf(script_s* s) {
    SCRIPT_BEGIN
    jumptext(RuinsOfAlphResearchCenterAcademicBooksText)
    SCRIPT_END
}
const uint8_t RuinsOfAlphResearchCenterApproachesComputerMovement[] = {
    step(UP),
    step(UP),
    step(LEFT),
    turn_head(UP),
    movement_step_end,
};
const uint8_t RuinsOfAlphResearchCenterApproachesPlayerMovement[] = {
    step(DOWN),
    movement_step_end,
};
const uint8_t RuinsOfAlphResearchCenterLeavesPlayerMovement[] = {
    step(UP),
    movement_step_end,
};
const txt_cmd_s RuinsOfAlphResearchCenterModifiedDexText[] = {
    text_start("Done!"
        t_para "I modified your"
        t_line "#DEX."
        t_para "I added an"
        t_line "optional #DEX"
        t_para "to store UNOWN"
        t_line "data."
        t_para "It records them in"
        t_line "the sequence that"
        t_cont "they were caught."
        t_done )
};
const txt_cmd_s RuinsOfAlphResearchCenterDexUpgradedText[] = {
    text_start("<PLAYER>'s #DEX"
        t_line "was upgraded."
        t_done )
};
const txt_cmd_s RuinsOfAlphResearchCenterScientist3Text[] = {
    text_start("The UNOWN you"
        t_line "catch will all be"
        t_cont "recorded."
        t_para "Check to see how"
        t_line "many kinds exist."
        t_done )
};
const txt_cmd_s RuinsOfAlphResearchCenterScientist3_PrinterAvailable[] = {
    text_start("You caught all the"
        t_line "UNOWN variations?"
        t_para "That's a great"
        t_line "achievement!"
        t_para "I've set up the"
        t_line "printer here for"
        t_cont "handling UNOWN."
        t_para "Feel free to use"
        t_line "it anytime."
        t_done )
};
const txt_cmd_s RuinsOfAlphResearchCenterScientist1Text[] = {
    text_start("The RUINS are"
        t_line "about 1500 years"
        t_cont "old."
        t_para "But it's not known"
        t_line "why they were"
        t_cont "built--or by whom."
        t_done )
};
const txt_cmd_s RuinsOfAlphResearchCenterScientist1Text_GotUnownDex[] = {
    text_start("I wonder how many"
        t_line "kinds of #MON"
        t_cont "are in the RUINS?"
        t_done )
};
const txt_cmd_s RuinsOfAlphResearchCenterScientist1Text_UnownAppeared[] = {
    text_start("#MON appeared"
        t_line "in the RUINS?"
        t_para "That's incredible"
        t_line "news!"
        t_para "We'll need to"
        t_line "investigate this."
        t_done )
};
const txt_cmd_s RuinsOfAlphResearchCenterScientist1Text_GotAllUnown[] = {
    text_start("Our investigation,"
        t_line "with your help, is"
        t_para "giving us insight"
        t_line "into the RUINS."
        t_para "The RUINS appear"
        t_line "to have been built"
        t_para "as a habitat for"
        t_line "#MON."
        t_done )
};
const txt_cmd_s RuinsOfAlphResearchCenterScientist2Text[] = {
    text_start("There are odd pat-"
        t_line "terns drawn on the"
        t_para "walls of the"
        t_line "RUINS."
        t_para "They must be the"
        t_line "keys for unravel-"
        t_cont "ing the mystery"
        t_cont "of the RUINS."
        t_done )
};
const txt_cmd_s RuinsOfAlphResearchCenterScientist2Text_UnownAppeared[] = {
    text_start("The strange #-"
        t_line "MON you saw in the"
        t_cont "RUINS?"
        t_para "They appear to be"
        t_line "very much like the"
        t_para "drawings on the"
        t_line "walls there."
        t_para "Hmm…"
        t_para "That must mean"
        t_line "there are many"
        t_cont "kinds of them…"
        t_done )
};
const txt_cmd_s RuinsOfAlphResearchCenterUnusedText1[] = {
    text_start("We think something"
        t_line "caused the cryptic"
        t_para "patterns to appear"
        t_line "in the RUINS."
        t_para "We've focused our"
        t_line "studies on that."
        t_done )
};
const txt_cmd_s RuinsOfAlphResearchCenterUnusedText2[] = {
    text_start("According to my"
        t_line "research…"
        t_para "Those mysterious"
        t_line "patterns appeared"
        t_para "when the #COM"
        t_line "CENTER was built."
        t_para "It must mean that"
        t_line "radio waves have"
        t_para "some sort of a"
        t_line "link…"
        t_done )
};
const txt_cmd_s RuinsOfAlphResearchCenterScientist2Text_GotAllUnown[] = {
    text_start("Why did those"
        t_line "ancient patterns"
        t_para "appear on the wall"
        t_line "now?"
        t_para "The mystery"
        t_line "deepens…"
        t_done )
};
const txt_cmd_s RuinsOfAlphResearchCenterComputerText[] = {
    text_start("RUINS OF ALPH"
        t_para "Exploration"
        t_line "Year 10"
        t_done )
};
const txt_cmd_s RuinsOfAlphResearchCenterComputerText_GotAllUnown[] = {
    text_start("Mystery #MON"
        t_line "Name: UNOWN"
        t_para "A total of {d:NUM_UNOWN}"
        t_line "kinds found."
        t_done )
};
const txt_cmd_s RuinsOfAlphResearchCenterPrinterText_DoesntWork[] = {
    text_start("This doesn't seem"
        t_line "to work yet."
        t_done )
};
const txt_cmd_s RuinsOfAlphResearchCenterUnownPrinterText[] = {
    text_start("UNOWN may be"
        t_line "printed out."
        t_done )
};
const txt_cmd_s RuinsOfAlphResearchCenterProfSilktreePhotoText[] = {
    text_start("It's a photo of"
        t_line "the RESEARCH"
        t_para "CENTER'S founder,"
        t_line "PROF.SILKTREE."
        t_done )
};
const txt_cmd_s RuinsOfAlphResearchCenterAcademicBooksText[] = {
    text_start("There are many"
        t_line "academic books."
        t_para "Ancient Ruins…"
        t_line "Mysteries of the"
        t_cont "Ancients…"
        t_done )
    //db(0, 0) // filler
};
