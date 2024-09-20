#include "../constants.h"
#include "../util/scripting.h"
#include "OaksLab.h"
//// EVENTS
enum {
    OAKSLAB_OAK = 2,
    OAKSLAB_SCIENTIST1,
    OAKSLAB_SCIENTIST2,
    OAKSLAB_SCIENTIST3,
};

const Script_fn_t OaksLab_SceneScripts[] = {
    0,
};

const struct MapCallback OaksLab_MapCallbacks[] = {
    0,
};

const struct MapScripts OaksLab_MapScripts = {
    .scene_script_count = 0, // lengthof(OaksLab_SceneScripts),
    .scene_scripts = OaksLab_SceneScripts,

    .callback_count = 0, // lengthof(OaksLab_MapCallbacks),
    .callbacks = OaksLab_MapCallbacks,
};

static const struct CoordEvent OaksLab_CoordEvents[] = {
    0,
};

static const struct BGEvent OaksLab_BGEvents[] = {
    bg_event(6, 1, BGEVENT_READ, &OaksLabBookshelf),
    bg_event(7, 1, BGEVENT_READ, &OaksLabBookshelf),
    bg_event(8, 1, BGEVENT_READ, &OaksLabBookshelf),
    bg_event(9, 1, BGEVENT_READ, &OaksLabBookshelf),
    bg_event(0, 7, BGEVENT_READ, &OaksLabBookshelf),
    bg_event(1, 7, BGEVENT_READ, &OaksLabBookshelf),
    bg_event(2, 7, BGEVENT_READ, &OaksLabBookshelf),
    bg_event(3, 7, BGEVENT_READ, &OaksLabBookshelf),
    bg_event(6, 7, BGEVENT_READ, &OaksLabBookshelf),
    bg_event(7, 7, BGEVENT_READ, &OaksLabBookshelf),
    bg_event(8, 7, BGEVENT_READ, &OaksLabBookshelf),
    bg_event(9, 7, BGEVENT_READ, &OaksLabBookshelf),
    bg_event(4, 0, BGEVENT_READ, &OaksLabPoster1),
    bg_event(5, 0, BGEVENT_READ, &OaksLabPoster2),
    bg_event(9, 3, BGEVENT_READ, &OaksLabTrashcan),
    bg_event(0, 1, BGEVENT_READ, &OaksLabPC),
};

static const struct WarpEventData OaksLab_WarpEvents[] = {
    warp_event(4, 11, PALLET_TOWN, 3),
    warp_event(5, 11, PALLET_TOWN, 3),
};

static const struct ObjEvent OaksLab_ObjectEvents[] = {
    object_event(4, 2, SPRITE_OAK, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Oak, -1),
    object_event(1, 8, SPRITE_SCIENTIST, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &OaksAssistant1Script, -1),
    object_event(8, 9, SPRITE_SCIENTIST, SPRITEMOVEDATA_WALK_UP_DOWN, 0, 1, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &OaksAssistant2Script, -1),
    object_event(1, 4, SPRITE_SCIENTIST, SPRITEMOVEDATA_WANDER, 1, 1, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &OaksAssistant3Script, -1),
};

const struct MapEvents OaksLab_MapEvents = {
    .warp_event_count = lengthof(OaksLab_WarpEvents),
    .warp_events = OaksLab_WarpEvents,

    .coord_event_count = 0, // lengthof(OaksLab_CoordEvents),
    .coord_events = OaksLab_CoordEvents,

    .bg_event_count = lengthof(OaksLab_BGEvents),
    .bg_events = OaksLab_BGEvents,

    .obj_event_count = lengthof(OaksLab_ObjectEvents),
    .obj_events = OaksLab_ObjectEvents,
};

//// CODE

bool OaksLab_MapScripts_DummyScene(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool Oak(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_OPENED_MT_SILVER)
    iftrue(CheckPokedex)
    checkevent(EVENT_TALKED_TO_OAK_IN_KANTO)
    iftrue(CheckBadges)
    writetext(OakWelcomeKantoText)
    promptbutton
    setevent(EVENT_TALKED_TO_OAK_IN_KANTO)
CheckBadges:
    readvar(VAR_BADGES)
    ifequal(NUM_BADGES, OpenMtSilver)
    ifequal(NUM_JOHTO_BADGES, Complain)
    goto AhGood;
CheckPokedex:
    writetext(OakLabDexCheckText)
    waitbutton
    special(ProfOaksPCBoot)
    writetext(OakLabGoodbyeText)
    waitbutton
    closetext
    s_end
OpenMtSilver:
    writetext(OakOpenMtSilverText)
    promptbutton
    setevent(EVENT_OPENED_MT_SILVER)
    goto CheckPokedex;
Complain:
    writetext(OakNoKantoBadgesText)
    promptbutton
    goto CheckPokedex;
AhGood:
    writetext(OakYesKantoBadgesText)
    promptbutton
    goto CheckPokedex;
    SCRIPT_END
}
bool OaksAssistant1Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(OaksAssistant1Text)
    SCRIPT_END
}
bool OaksAssistant2Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(OaksAssistant2Text)
    SCRIPT_END
}
bool OaksAssistant3Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(OaksAssistant3Text)
    SCRIPT_END
}
bool OaksLabBookshelf(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(DifficultBookshelfScript)
    SCRIPT_END
}
bool OaksLabPoster1(script_s* s) {
    SCRIPT_BEGIN
    jumptext(OaksLabPoster1Text)
    SCRIPT_END
}
bool OaksLabPoster2(script_s* s) {
    SCRIPT_BEGIN
    jumptext(OaksLabPoster2Text)
    SCRIPT_END
}
bool OaksLabTrashcan(script_s* s) {
    SCRIPT_BEGIN
    jumptext(OaksLabTrashcanText)
    SCRIPT_END
}
bool OaksLabPC(script_s* s) {
    SCRIPT_BEGIN
    jumptext(OaksLabPCText)
    SCRIPT_END
}
const txt_cmd_s OakWelcomeKantoText[] = {
    text_start("OAK: Ah, <PLAY_G>!"
        t_line "It's good of you"
        t_para "to come all this"
        t_line "way to KANTO."
        t_para "What do you think"
        t_line "of the trainers"
        t_para "out here?"
        t_line "Pretty tough, huh?"
        t_done )
};
const txt_cmd_s OakLabDexCheckText[] = {
    text_start("How is your #-"
        t_line "DEX coming?"
        t_para "Let's see…"
        t_done )
};
const txt_cmd_s OakLabGoodbyeText[] = {
    text_start("If you're in the"
        t_line "area, I hope you"
        t_cont "come visit again."
        t_done )
};
const txt_cmd_s OakOpenMtSilverText[] = {
    text_start("OAK: Wow! That's"
        t_line "excellent!"
        t_para "You collected the"
        t_line "BADGES of GYMS in"
        t_cont "KANTO. Well done!"
        t_para "I was right in my"
        t_line "assessment of you."
        t_para "Tell you what,"
        t_line "<PLAY_G>. I'll make"
        t_para "arrangements so"
        t_line "that you can go to"
        t_cont "MT.SILVER."
        t_para "MT.SILVER is a big"
        t_line "mountain that is"
        t_para "home to many wild"
        t_line "#MON."
        t_para "It's too dangerous"
        t_line "for your average"
        t_para "trainer, so it's"
        t_line "off limits. But"
        t_para "we can make an"
        t_line "exception in your"
        t_cont "case, <PLAY_G>."
        t_para "Go up to INDIGO"
        t_line "PLATEAU. You can"
        t_para "reach MT.SILVER"
        t_line "from there."
        t_done )
};
const txt_cmd_s OakNoKantoBadgesText[] = {
    text_start("OAK: Hmm? You're"
        t_line "not collecting"
        t_cont "KANTO GYM BADGES?"
        t_para "The GYM LEADERS in"
        t_line "KANTO are as tough"
        t_para "as any you battled"
        t_line "in JOHTO."
        t_para "I recommend that"
        t_line "you challenge"
        t_cont "them."
        t_done )
};
const txt_cmd_s OakYesKantoBadgesText[] = {
    text_start("OAK: Ah, you're"
        t_line "collecting KANTO"
        t_cont "GYM BADGES."
        t_para "I imagine that"
        t_line "it's hard, but the"
        t_para "experience is sure"
        t_line "to help you."
        t_para "Come see me when"
        t_line "you get them all."
        t_para "I'll have a gift"
        t_line "for you."
        t_para "Keep trying hard,"
        t_line "<PLAY_G>!"
        t_done )
};
const txt_cmd_s OaksAssistant1Text[] = {
    text_start("The PROF's #MON"
        t_line "TALK radio program"
        t_para "isn't aired here"
        t_line "in KANTO."
        t_para "It's a shame--I'd"
        t_line "like to hear it."
        t_done )
};
const txt_cmd_s OaksAssistant2Text[] = {
    text_start("Thanks to your"
        t_line "work on the #-"
        t_cont "DEX, the PROF's"
        t_para "research is coming"
        t_line "along great."
        t_done )
};
const txt_cmd_s OaksAssistant3Text[] = {
    text_start("Don't tell anyone,"
        t_line "but PROF.OAK'S"
        t_para "#MON TALK isn't"
        t_line "a live broadcast."
        t_done )
};
const txt_cmd_s OaksLabPoster1Text[] = {
    text_start("Press START to"
        t_line "open the MENU."
        t_done )
};
const txt_cmd_s OaksLabPoster2Text[] = {
    text_start("The SAVE option is"
        t_line "on the MENU."
        t_para "Use it in a timely"
        t_line "manner."
        t_done )
};
const txt_cmd_s OaksLabTrashcanText[] = {
    text_start("There's nothing in"
        t_line "here…"
        t_done )
};
const txt_cmd_s OaksLabPCText[] = {
    text_start("There's an e-mail"
        t_line "message on the PC."
        t_para "…"
        t_para "PROF.OAK, how is"
        t_line "your research"
        t_cont "coming along?"
        t_para "I'm still plugging"
        t_line "away."
        t_para "I heard rumors"
        t_line "that <PLAY_G> is"
        t_para "getting quite a"
        t_line "reputation."
        t_para "I'm delighted to"
        t_line "hear that."
        t_para "ELM in NEW BARK"
        t_line "TOWN 8-)"
        t_done )
    //db(0, 0) // filler
};
