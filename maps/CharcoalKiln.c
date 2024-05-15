#include "../constants.h"
#include "../util/scripting.h"
#include "CharcoalKiln.h"
//// EVENTS
enum {
    CHARCOALKILN_BLACK_BELT = 2,
    CHARCOALKILN_YOUNGSTER,
    CHARCOALKILN_MOLTRES,
};

const Script_fn_t CharcoalKiln_SceneScripts[] = {
    0,
};

const struct MapCallback CharcoalKiln_MapCallbacks[] = {
    0,
};

const struct MapScripts CharcoalKiln_MapScripts = {
    .scene_script_count = 0, // lengthof(CharcoalKiln_SceneScripts),
    .scene_scripts = CharcoalKiln_SceneScripts,

    .callback_count = 0, // lengthof(CharcoalKiln_MapCallbacks),
    .callbacks = CharcoalKiln_MapCallbacks,
};

static const struct CoordEvent CharcoalKiln_CoordEvents[] = {
    0,
};

static const struct BGEvent CharcoalKiln_BGEvents[] = {
    bg_event(0, 1, BGEVENT_READ, &CharcoalKilnBookshelf),
    bg_event(1, 1, BGEVENT_READ, &CharcoalKilnBookshelf),
    bg_event(7, 1, BGEVENT_READ, &CharcoalKilnRadio),
};

static const struct WarpEventData CharcoalKiln_WarpEvents[] = {
    warp_event(2, 7, AZALEA_TOWN, 2),
    warp_event(3, 7, AZALEA_TOWN, 2),
};

static const struct ObjEvent CharcoalKiln_ObjectEvents[] = {
    object_event(2, 3, SPRITE_BLACK_BELT, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &CharcoalKilnBoss, EVENT_CHARCOAL_KILN_BOSS),
    object_event(5, 3, SPRITE_YOUNGSTER, SPRITEMOVEDATA_WANDER, 1, 1, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &CharcoalKilnApprentice, EVENT_CHARCOAL_KILN_APPRENTICE),
    object_event(5, 6, SPRITE_MOLTRES, SPRITEMOVEDATA_POKEMON, 2, 2, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, &CharcoalKilnFarfetchd, EVENT_CHARCOAL_KILN_FARFETCH_D),
};

const struct MapEvents CharcoalKiln_MapEvents = {
    .warp_event_count = lengthof(CharcoalKiln_WarpEvents),
    .warp_events = CharcoalKiln_WarpEvents,

    .coord_event_count = 0, // lengthof(CharcoalKiln_CoordEvents),
    .coord_events = CharcoalKiln_CoordEvents,

    .bg_event_count = lengthof(CharcoalKiln_BGEvents),
    .bg_events = CharcoalKiln_BGEvents,

    .obj_event_count = lengthof(CharcoalKiln_ObjectEvents),
    .obj_events = CharcoalKiln_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "CharcoalKiln.h"

bool CharcoalKilnBoss(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_HM01_CUT)
    iftrue(GotCut)
    checkevent(EVENT_CLEARED_SLOWPOKE_WELL)
    iftrue(SavedSlowpoke)
    writetext(CharcoalKilnBossText1)
    waitbutton
    closetext
    s_end
SavedSlowpoke:
    writetext(CharcoalKilnBossText2)
    waitbutton
    closetext
    s_end
GotCut:
    writetext(CharcoalKilnBossText3)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool CharcoalKilnApprentice(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_CHARCOAL_IN_CHARCOAL_KILN)
    iftrue(YoureTheCoolest)
    checkevent(EVENT_GOT_HM01_CUT)
    iftrue(Thanks)
    writetext(CharcoalKilnApprenticeText1)
    waitbutton
    closetext
    s_end
Thanks:
    writetext(CharcoalKilnApprenticeText2)
    promptbutton
    verbosegiveitem(CHARCOAL, 1)
    iffalse(Done)
    setevent(EVENT_GOT_CHARCOAL_IN_CHARCOAL_KILN)
    closetext
    s_end
YoureTheCoolest:
    writetext(CharcoalKilnApprenticeText3)
    waitbutton
Done:
    closetext
    s_end
    SCRIPT_END
}
bool CharcoalKilnFarfetchd(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(FarfetchdText)
    playcry(FARFETCH_D)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool CharcoalKilnBookshelf(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(MagazineBookshelfScript)
    SCRIPT_END
}
bool CharcoalKilnRadio(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(Radio2Script)
    SCRIPT_END
}
const txt_cmd_s CharcoalKilnBossText1[] = {
    text_start("All the SLOWPOKE"
        t_line "have disappeared"
        t_cont "from the town."
        t_para "The forest's pro-"
        t_line "tector may be"
        t_cont "angry with us…"
        t_para "It may be a bad"
        t_line "omen. We should"
        t_cont "stay in."
        t_done )
};
const txt_cmd_s CharcoalKilnBossText2[] = {
    text_start("The SLOWPOKE have"
        t_line "returned…"
        t_para "But my APPRENTICE"
        t_line "hasn't come back"
        t_cont "from ILEX FOREST."
        t_para "Where in the world"
        t_line "is that lazy guy?"
        t_done )
};
const txt_cmd_s CharcoalKilnBossText3[] = {
    text_start("You chased off"
        t_line "TEAM ROCKET and"
        t_para "went to ILEX"
        t_line "FOREST alone?"
        t_para "That takes guts!"
        t_line "I like that. Come"
        t_cont "train with us."
        t_done )
};
const txt_cmd_s CharcoalKilnApprenticeText1[] = {
    text_start("Where have all the"
        t_line "SLOWPOKE gone?"
        t_para "Are they out play-"
        t_line "ing somewhere?"
        t_done )
};
const txt_cmd_s CharcoalKilnApprenticeText2[] = {
    text_start("I'm sorry--I for-"
        t_line "got to thank you."
        t_para "This is CHARCOAL"
        t_line "that I made."
        t_para "Fire-type #MON"
        t_line "would be happy to"
        t_cont "hold that."
        t_done )
};
const txt_cmd_s CharcoalKilnApprenticeText3[] = {
    text_start("The SLOWPOKE came"
        t_line "back, and you even"
        t_cont "found FARFETCH'D."
        t_para "You're the cool-"
        t_line "est, man!"
        t_done )
};
const txt_cmd_s FarfetchdText[] = {
    text_start("FARFETCH'D: Kwaa!"
        t_done )
    //db(0, 0) // filler
};
