#include "../constants.h"
#include "../util/scripting.h"
#include "RuinsOfAlphOutside.h"
//// EVENTS
enum {
    RUINSOFALPHOUTSIDE_YOUNGSTER1 = 2,
    RUINSOFALPHOUTSIDE_SCIENTIST,
    RUINSOFALPHOUTSIDE_FISHER,
    RUINSOFALPHOUTSIDE_YOUNGSTER2,
    RUINSOFALPHOUTSIDE_YOUNGSTER3,
};

const Script_fn_t RuinsOfAlphOutside_SceneScripts[] = {
    RuinsOfAlphOutside_MapScripts_DummyScene0 , //  SCENE_RUINSOFALPHOUTSIDE_NOTHING,
    RuinsOfAlphOutside_MapScripts_DummyScene1 , //  SCENE_RUINSOFALPHOUTSIDE_GET_UNOWN_DEX,
};

const struct MapCallback RuinsOfAlphOutside_MapCallbacks[] = {
    map_callback(MAPCALLBACK_OBJECTS, RuinsOfAlphOutside_MapScripts_ScientistCallback),
};

const struct MapScripts RuinsOfAlphOutside_MapScripts = {
    .scene_script_count = lengthof(RuinsOfAlphOutside_SceneScripts),
    .scene_scripts = RuinsOfAlphOutside_SceneScripts,

    .callback_count = lengthof(RuinsOfAlphOutside_MapCallbacks),
    .callbacks = RuinsOfAlphOutside_MapCallbacks,
};

static const struct CoordEvent RuinsOfAlphOutside_CoordEvents[] = {
    coord_event(11, 14, SCENE_RUINSOFALPHOUTSIDE_GET_UNOWN_DEX, &RuinsOfAlphOutsideScientistScene1),
    coord_event(10, 15, SCENE_RUINSOFALPHOUTSIDE_GET_UNOWN_DEX, &RuinsOfAlphOutsideScientistScene2),
};

static const struct BGEvent RuinsOfAlphOutside_BGEvents[] = {
    bg_event(16, 8, BGEVENT_READ, &RuinsOfAlphOutsideMysteryChamberSign),
    bg_event(12, 16, BGEVENT_READ, &RuinsOfAlphSign),
    bg_event(18, 12, BGEVENT_READ, &RuinsOfAlphResearchCenterSign),
};

static const struct WarpEventData RuinsOfAlphOutside_WarpEvents[] = {
    warp_event(2, 17, RUINS_OF_ALPH_HO_OH_CHAMBER, 1),
    warp_event(14, 7, RUINS_OF_ALPH_KABUTO_CHAMBER, 1),
    warp_event(2, 29, RUINS_OF_ALPH_OMANYTE_CHAMBER, 1),
    warp_event(16, 33, RUINS_OF_ALPH_AERODACTYL_CHAMBER, 1),
    warp_event(10, 13, RUINS_OF_ALPH_INNER_CHAMBER, 1),
    warp_event(17, 11, RUINS_OF_ALPH_RESEARCH_CENTER, 1),
    warp_event(6, 19, UNION_CAVE_B1F, 1),
    warp_event(6, 27, UNION_CAVE_B1F, 2),
    warp_event(7, 5, ROUTE_36_RUINS_OF_ALPH_GATE, 3),
    warp_event(13, 20, ROUTE_32_RUINS_OF_ALPH_GATE, 1),
    warp_event(13, 21, ROUTE_32_RUINS_OF_ALPH_GATE, 2),
};

static const struct ObjEvent RuinsOfAlphOutside_ObjectEvents[] = {
    object_event(4, 20, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_TRAINER, 1, &TrainerPsychicNathan, -1),
    object_event(11, 15, SPRITE_SCIENTIST, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &RuinsOfAlphOutsideScientistScript, EVENT_RUINS_OF_ALPH_OUTSIDE_SCIENTIST),
    object_event(13, 17, SPRITE_FISHER, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &RuinsOfAlphOutsideFisherScript, EVENT_RUINS_OF_ALPH_OUTSIDE_TOURIST_FISHER),
    object_event(14, 11, SPRITE_YOUNGSTER, SPRITEMOVEDATA_WANDER, 1, 1, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, &RuinsOfAlphOutsideYoungster1Script, EVENT_RUINS_OF_ALPH_OUTSIDE_TOURIST_YOUNGSTERS),
    object_event(12, 8, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &RuinsOfAlphOutsideYoungster2Script, EVENT_RUINS_OF_ALPH_OUTSIDE_TOURIST_YOUNGSTERS),
};

const struct MapEvents RuinsOfAlphOutside_MapEvents = {
    .warp_event_count = lengthof(RuinsOfAlphOutside_WarpEvents),
    .warp_events = RuinsOfAlphOutside_WarpEvents,

    .coord_event_count = lengthof(RuinsOfAlphOutside_CoordEvents),
    .coord_events = RuinsOfAlphOutside_CoordEvents,

    .bg_event_count = lengthof(RuinsOfAlphOutside_BGEvents),
    .bg_events = RuinsOfAlphOutside_BGEvents,

    .obj_event_count = lengthof(RuinsOfAlphOutside_ObjectEvents),
    .obj_events = RuinsOfAlphOutside_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "RuinsOfAlphOutside.h"

bool RuinsOfAlphOutside_MapScripts_DummyScene0(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool RuinsOfAlphOutside_MapScripts_DummyScene1(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool RuinsOfAlphOutside_MapScripts_ScientistCallback(script_s* s) {
    SCRIPT_BEGIN
    checkflag(ENGINE_UNOWN_DEX)
    iftrue_jump(RuinsOfAlphOutside_MapScripts_NoScientist)
    checkevent(EVENT_MADE_UNOWN_APPEAR_IN_RUINS)
    iftrue_jump(RuinsOfAlphOutside_MapScripts_MaybeScientist)
    sjump(RuinsOfAlphOutside_MapScripts_NoScientist)
    SCRIPT_END
}
bool RuinsOfAlphOutside_MapScripts_MaybeScientist(script_s* s) {
    SCRIPT_BEGIN
    readvar(VAR_UNOWNCOUNT)
    ifgreater_jump(2, RuinsOfAlphOutside_MapScripts_YesScientist)
    sjump(RuinsOfAlphOutside_MapScripts_NoScientist)
    SCRIPT_END
}
bool RuinsOfAlphOutside_MapScripts_YesScientist(script_s* s) {
    SCRIPT_BEGIN
    appear(RUINSOFALPHOUTSIDE_SCIENTIST)
    setscene(SCENE_RUINSOFALPHOUTSIDE_GET_UNOWN_DEX)
    s_endcallback
    SCRIPT_END
}
bool RuinsOfAlphOutside_MapScripts_NoScientist(script_s* s) {
    SCRIPT_BEGIN
    disappear(RUINSOFALPHOUTSIDE_SCIENTIST)
    setscene(SCENE_RUINSOFALPHOUTSIDE_NOTHING)
    s_endcallback
    SCRIPT_END
}
bool RuinsOfAlphOutsideScientistScene1(script_s* s) {
    SCRIPT_BEGIN
    turnobject(RUINSOFALPHOUTSIDE_SCIENTIST, UP)
    turnobject(PLAYER, DOWN)
    sjump(RuinsOfAlphOutsideScientistSceneContinue)
    SCRIPT_END
}
bool RuinsOfAlphOutsideScientistScene2(script_s* s) {
    SCRIPT_BEGIN
    turnobject(RUINSOFALPHOUTSIDE_SCIENTIST, LEFT)
    turnobject(PLAYER, RIGHT)
    sjump(RuinsOfAlphOutsideScientistSceneContinue)
    SCRIPT_END
}
bool RuinsOfAlphOutsideScientistScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    SCRIPT_FALLTHROUGH(RuinsOfAlphOutsideScientistSceneContinue)
}
bool RuinsOfAlphOutsideScientistSceneContinue(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(RuinsOfAlphOutsideScientistText)
    waitbutton
    closetext
    playmusic(MUSIC_SHOW_ME_AROUND)
    follow(RUINSOFALPHOUTSIDE_SCIENTIST, PLAYER)
    applymovement(RUINSOFALPHOUTSIDE_SCIENTIST, RuinsOfAlphOutsideScientistWalkToLabMovement)
    disappear(RUINSOFALPHOUTSIDE_SCIENTIST)
    stopfollow
    applymovement(PLAYER, RuinsOfAlphOutsidePlayerEnterLabMovement)
    setmapscene(RUINS_OF_ALPH_RESEARCH_CENTER, SCENE_RUINSOFALPHRESEARCHCENTER_GET_UNOWN_DEX)
    warpcheck
    s_end
    SCRIPT_END
}
bool RuinsOfAlphOutsideFisherScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_TALKED_TO_RUINS_COWARD)
    iftrue(Next)
    setevent(EVENT_TALKED_TO_RUINS_COWARD)
    writetext(RuinsOfAlphOutsideFisherText1)
    promptbutton
Next:
    writetext(RuinsOfAlphOutsideFisherText2)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool RuinsOfAlphOutsideYoungster1Script(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(RuinsOfAlphOutsideYoungster1Text)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool RuinsOfAlphOutsideYoungster2Script(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(RuinsOfAlphOutsideYoungster2Text)
    waitbutton
    closetext
    turnobject(RUINSOFALPHOUTSIDE_YOUNGSTER3, UP)
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerPsychicNathan = {PSYCHIC_T, NATHAN, EVENT_BEAT_PSYCHIC_NATHAN, PsychicNathanSeenText, PsychicNathanBeatenText, 0, TrainerPsychicNathan_Script};
bool TrainerPsychicNathan_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(PsychicNathanAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSuperNerdStan = {SUPER_NERD, STAN, EVENT_BEAT_SUPER_NERD_STAN, SuperNerdStanSeenText, SuperNerdStanBeatenText, 0, TrainerSuperNerdStan_Script};
bool TrainerSuperNerdStan_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SuperNerdStanAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool RuinsOfAlphOutsideMysteryChamberSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(RuinsOfAlphOutsideMysteryChamberSignText)
    SCRIPT_END
}
bool RuinsOfAlphSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(RuinsOfAlphSignText)
    SCRIPT_END
}
bool RuinsOfAlphResearchCenterSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(RuinsOfAlphResearchCenterSignText)
    SCRIPT_END
}
const uint8_t RuinsOfAlphOutsideScientistWalkToLabMovement[] = {
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    step(UP),
    step(UP),
    step(RIGHT),
    step(RIGHT),
    step(UP),
    step(UP),
    movement_step_end,
};
const uint8_t RuinsOfAlphOutsidePlayerEnterLabMovement[] = {
    step(UP),
    movement_step_end,
};
const txt_cmd_s RuinsOfAlphOutsideScientistText[] = {
    text_start("Hm? That's a #-"
        t_line "DEX, isn't it?"
        t_cont "May I see it?"
        t_para "There are so many"
        t_line "kinds of #MON."
        t_para "Hm? What's this?"
        t_para "What is this"
        t_line "#MON?"
        t_para "It looks like the"
        t_line "strange writing on"
        t_para "the walls of the"
        t_line "RUINS."
        t_para "If those drawings"
        t_line "are really #-"
        t_cont "MON, there should"
        t_cont "be many more."
        t_para "I know! Let me up-"
        t_line "grade your #-"
        t_cont "DEX. Follow me."
        t_done )
};
const txt_cmd_s SuperNerdStanSeenText[] = {
    text_start("What do you want?"
        t_line "I'm studying--"
        t_cont "don't disturb me!"
        t_done )
};
const txt_cmd_s SuperNerdStanBeatenText[] = {
    text_start("Sorry…"
        t_line "I'm frustrated by"
        t_para "our lack of real"
        t_line "understanding…"
        t_done )
};
const txt_cmd_s SuperNerdStanAfterBattleText[] = {
    text_start("The RUINS are from"
        t_line "about 1500 years"
        t_cont "ago."
        t_para "Nobody knows who"
        t_line "built them."
        t_para "It's also not"
        t_line "known if the #-"
        t_cont "MON statues have"
        t_cont "any meaning."
        t_para "It's all one big"
        t_line "mystery…"
        t_done )
};
const txt_cmd_s PsychicNathanSeenText[] = {
    text_start("Hmmm… This is a"
        t_line "strange place."
        t_done )
};
const txt_cmd_s PsychicNathanBeatenText[] = {
    text_start("…"
        t_done )
};
const txt_cmd_s PsychicNathanAfterBattleText[] = {
    text_start("I like thinking"
        t_line "here."
        t_done )
};
const txt_cmd_s RuinsOfAlphOutsideMysteryChamberSignText[] = {
    text_start("MYSTERY STONE"
        t_line "PANEL CHAMBER"
        t_done )
};
const txt_cmd_s RuinsOfAlphSignText[] = {
    text_start("RUINS OF ALPH"
        t_line "VISITORS WELCOME"
        t_done )
};
const txt_cmd_s RuinsOfAlphResearchCenterSignText[] = {
    text_start("RUINS OF ALPH"
        t_line "RESEARCH CENTER"
        t_para "THE AUTHORITY ON"
        t_line "THE RUINS OF ALPH"
        t_done )
};
const txt_cmd_s RuinsOfAlphOutsideFisherText1[] = {
    text_start("While exploring"
        t_line "the RUINS, we"
        t_para "suddenly noticed"
        t_line "an odd presence."
        t_para "We all got scared"
        t_line "and ran away."
        t_para "You should be"
        t_line "careful too."
        t_done )
};
const txt_cmd_s RuinsOfAlphOutsideFisherText2[] = {
    text_start("The RUINS hide a"
        t_line "huge secret!"
        t_para "…I think…"
        t_done )
};
const txt_cmd_s RuinsOfAlphOutsideYoungster1Text[] = {
    text_start("There are many"
        t_line "kinds of UNOWN, so"
        t_para "we use them for"
        t_line "our secret codes."
        t_done )
};
const txt_cmd_s RuinsOfAlphOutsideYoungster2Text[] = {
    text_start("A… H… E… A… D…"
        t_line "Hmm…"
        t_para "What?"
        t_para "I'm decoding this"
        t_line "message!"
        t_done )
    //db(0, 0) // filler
};
