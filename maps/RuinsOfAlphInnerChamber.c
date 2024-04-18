#include "../constants.h"
#include "../util/scripting.h"
#include "RuinsOfAlphInnerChamber.h"
//// EVENTS
enum {
    RUINSOFALPHINNERCHAMBER_FISHER = 2,
    RUINSOFALPHINNERCHAMBER_TEACHER,
    RUINSOFALPHINNERCHAMBER_GRAMPS,
};

const Script_fn_t RuinsOfAlphInnerChamber_SceneScripts[] = {
    RuinsOfAlphInnerChamber_MapScripts_DummyScene0 , //  SCENE_RUINSOFALPHINNERCHAMBER_NOTHING,
    RuinsOfAlphInnerChamber_MapScripts_UnownAppear , //  SCENE_RUINSOFALPHINNERCHAMBER_STRANGE_PRESENCE,
};

const struct MapCallback RuinsOfAlphInnerChamber_MapCallbacks[] = {
    0,
};

const struct MapScripts RuinsOfAlphInnerChamber_MapScripts = {
    .scene_script_count = lengthof(RuinsOfAlphInnerChamber_SceneScripts),
    .scene_scripts = RuinsOfAlphInnerChamber_SceneScripts,

    .callback_count = 0, // lengthof(RuinsOfAlphInnerChamber_MapCallbacks),
    .callbacks = RuinsOfAlphInnerChamber_MapCallbacks,
};

static const struct CoordEvent RuinsOfAlphInnerChamber_CoordEvents[] = {
    0,
};

static const struct BGEvent RuinsOfAlphInnerChamber_BGEvents[] = {
    bg_event(2, 3, BGEVENT_READ, &RuinsOfAlphInnerChamberStatue),
    bg_event(5, 3, BGEVENT_READ, &RuinsOfAlphInnerChamberStatue),
    bg_event(8, 3, BGEVENT_READ, &RuinsOfAlphInnerChamberStatue),
    bg_event(11, 3, BGEVENT_READ, &RuinsOfAlphInnerChamberStatue),
    bg_event(14, 3, BGEVENT_READ, &RuinsOfAlphInnerChamberStatue),
    bg_event(17, 3, BGEVENT_READ, &RuinsOfAlphInnerChamberStatue),
    bg_event(2, 8, BGEVENT_READ, &RuinsOfAlphInnerChamberStatue),
    bg_event(5, 8, BGEVENT_READ, &RuinsOfAlphInnerChamberStatue),
    bg_event(8, 8, BGEVENT_READ, &RuinsOfAlphInnerChamberStatue),
    bg_event(11, 8, BGEVENT_READ, &RuinsOfAlphInnerChamberStatue),
    bg_event(14, 8, BGEVENT_READ, &RuinsOfAlphInnerChamberStatue),
    bg_event(17, 8, BGEVENT_READ, &RuinsOfAlphInnerChamberStatue),
    bg_event(2, 13, BGEVENT_READ, &RuinsOfAlphInnerChamberStatue),
    bg_event(17, 13, BGEVENT_READ, &RuinsOfAlphInnerChamberStatue),
    bg_event(2, 18, BGEVENT_READ, &RuinsOfAlphInnerChamberStatue),
    bg_event(5, 18, BGEVENT_READ, &RuinsOfAlphInnerChamberStatue),
    bg_event(8, 18, BGEVENT_READ, &RuinsOfAlphInnerChamberStatue),
    bg_event(11, 18, BGEVENT_READ, &RuinsOfAlphInnerChamberStatue),
    bg_event(14, 18, BGEVENT_READ, &RuinsOfAlphInnerChamberStatue),
    bg_event(17, 18, BGEVENT_READ, &RuinsOfAlphInnerChamberStatue),
    bg_event(2, 24, BGEVENT_READ, &RuinsOfAlphInnerChamberStatue),
    bg_event(5, 24, BGEVENT_READ, &RuinsOfAlphInnerChamberStatue),
    bg_event(8, 24, BGEVENT_READ, &RuinsOfAlphInnerChamberStatue),
    bg_event(11, 24, BGEVENT_READ, &RuinsOfAlphInnerChamberStatue),
    bg_event(14, 24, BGEVENT_READ, &RuinsOfAlphInnerChamberStatue),
    bg_event(17, 24, BGEVENT_READ, &RuinsOfAlphInnerChamberStatue),
};

static const struct WarpEventData RuinsOfAlphInnerChamber_WarpEvents[] = {
    warp_event(10, 13, RUINS_OF_ALPH_OUTSIDE, 5),
    warp_event(3, 15, RUINS_OF_ALPH_HO_OH_CHAMBER, 3),
    warp_event(4, 15, RUINS_OF_ALPH_HO_OH_CHAMBER, 4),
    warp_event(15, 3, RUINS_OF_ALPH_KABUTO_CHAMBER, 3),
    warp_event(16, 3, RUINS_OF_ALPH_KABUTO_CHAMBER, 4),
    warp_event(3, 21, RUINS_OF_ALPH_OMANYTE_CHAMBER, 3),
    warp_event(4, 21, RUINS_OF_ALPH_OMANYTE_CHAMBER, 4),
    warp_event(15, 24, RUINS_OF_ALPH_AERODACTYL_CHAMBER, 3),
    warp_event(16, 24, RUINS_OF_ALPH_AERODACTYL_CHAMBER, 4),
};

static const struct ObjEvent RuinsOfAlphInnerChamber_ObjectEvents[] = {
    object_event(3, 7, SPRITE_FISHER, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &RuinsOfAlphInnerChamberFisherScript, EVENT_RUINS_OF_ALPH_INNER_CHAMBER_TOURISTS),
    object_event(14, 13, SPRITE_TEACHER, SPRITEMOVEDATA_WANDER, 1, 1, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &RuinsOfAlphInnerChamberTeacherScript, EVENT_RUINS_OF_ALPH_INNER_CHAMBER_TOURISTS),
    object_event(11, 19, SPRITE_GRAMPS, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, &RuinsOfAlphInnerChamberGrampsScript, EVENT_RUINS_OF_ALPH_INNER_CHAMBER_TOURISTS),
};

const struct MapEvents RuinsOfAlphInnerChamber_MapEvents = {
    .warp_event_count = lengthof(RuinsOfAlphInnerChamber_WarpEvents),
    .warp_events = RuinsOfAlphInnerChamber_WarpEvents,

    .coord_event_count = 0, // lengthof(RuinsOfAlphInnerChamber_CoordEvents),
    .coord_events = RuinsOfAlphInnerChamber_CoordEvents,

    .bg_event_count = lengthof(RuinsOfAlphInnerChamber_BGEvents),
    .bg_events = RuinsOfAlphInnerChamber_BGEvents,

    .obj_event_count = lengthof(RuinsOfAlphInnerChamber_ObjectEvents),
    .obj_events = RuinsOfAlphInnerChamber_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "RuinsOfAlphInnerChamber.h"

bool RuinsOfAlphInnerChamber_MapScripts_DummyScene0(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool RuinsOfAlphInnerChamber_MapScripts_UnownAppear(script_s* s) {
    SCRIPT_BEGIN
    sdefer(RuinsOfAlphInnerChamber_MapScripts_StrangePresenceScript);
    s_end
    SCRIPT_END
}
bool RuinsOfAlphInnerChamber_MapScripts_StrangePresenceScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(RuinsOfAlphStrangePresenceText)
    waitbutton
    closetext
    setscene(SCENE_RUINSOFALPHINNERCHAMBER_NOTHING)
    setevent(EVENT_MADE_UNOWN_APPEAR_IN_RUINS)
    clearevent(EVENT_RUINS_OF_ALPH_OUTSIDE_TOURIST_FISHER)
    s_end
    SCRIPT_END
}
bool RuinsOfAlphInnerChamberFisherScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(RuinsOfAlphInnerChamberFisherText)
    SCRIPT_END
}
bool RuinsOfAlphInnerChamberTeacherScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(RuinsOfAlphInnerChamberTeacherText)
    SCRIPT_END
}
bool RuinsOfAlphInnerChamberGrampsScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(RuinsOfAlphInnerChamberGrampsText)
    SCRIPT_END
}
bool RuinsOfAlphInnerChamberStatue(script_s* s) {
    SCRIPT_BEGIN
    jumptext(RuinsOfAlphInnerChamberStatueText)
    SCRIPT_END
}
const txt_cmd_s RuinsOfAlphStrangePresenceText[] = {
    text_start("There is a strange"
        t_line "presence here…"
        t_done )
};
const txt_cmd_s RuinsOfAlphInnerChamberFisherText[] = {
    text_start("This is a big"
        t_line "room, but there's"
        t_cont "nothing here."
        t_done )
};
const txt_cmd_s RuinsOfAlphInnerChamberTeacherText[] = {
    text_start("This place has a"
        t_line "mystical quality"
        t_cont "to it."
        t_para "It feels sort of"
        t_line "ethereal even."
        t_done )
};
const txt_cmd_s RuinsOfAlphInnerChamberGrampsText[] = {
    text_start("Ancient buildings"
        t_line "are often tombs of"
        t_cont "kings."
        t_para "Like the pyramids,"
        t_line "for instance."
        t_done )
};
const txt_cmd_s RuinsOfAlphInnerChamberStatueText[] = {
    text_start("It's a replica of"
        t_line "an ancient #-"
        t_cont "MON."
        t_done )
    //db(0, 0) // filler
};
