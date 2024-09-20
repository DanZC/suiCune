#include "../constants.h"
#include "../util/scripting.h"
#include "CeladonMansion1F.h"
//// EVENTS
enum {
    CELADONMANSION1F_GRANNY = 2,
    CELADONMANSION1F_GROWLITHE1,
    CELADONMANSION1F_CLEFAIRY,
    CELADONMANSION1F_GROWLITHE2,
};

const Script_fn_t CeladonMansion1F_SceneScripts[] = {
    0,
};

const struct MapCallback CeladonMansion1F_MapCallbacks[] = {
    0,
};

const struct MapScripts CeladonMansion1F_MapScripts = {
    .scene_script_count = 0, // lengthof(CeladonMansion1F_SceneScripts),
    .scene_scripts = CeladonMansion1F_SceneScripts,

    .callback_count = 0, // lengthof(CeladonMansion1F_MapCallbacks),
    .callbacks = CeladonMansion1F_MapCallbacks,
};

static const struct CoordEvent CeladonMansion1F_CoordEvents[] = {
    0,
};

static const struct BGEvent CeladonMansion1F_BGEvents[] = {
    bg_event(5, 8, BGEVENT_UP, &CeladonMansionManagersSuiteSign),
    bg_event(0, 3, BGEVENT_READ, &CeladonMansion1FBookshelf),
    bg_event(2, 3, BGEVENT_READ, &CeladonMansion1FBookshelf),
};

static const struct WarpEventData CeladonMansion1F_WarpEvents[] = {
    warp_event(6, 9, CELADON_CITY, 2),
    warp_event(7, 9, CELADON_CITY, 2),
    warp_event(3, 0, CELADON_CITY, 3),
    warp_event(0, 0, CELADON_MANSION_2F, 1),
    warp_event(7, 0, CELADON_MANSION_2F, 4),
};

static const struct ObjEvent CeladonMansion1F_ObjectEvents[] = {
    object_event(1, 5, SPRITE_GRANNY, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &CeladonMansionManager, -1),
    object_event(2, 6, SPRITE_GROWLITHE, SPRITEMOVEDATA_POKEMON, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &CeladonMansion1FMeowth, -1),
    object_event(3, 4, SPRITE_CLEFAIRY, SPRITEMOVEDATA_POKEMON, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &CeladonMansion1FClefairy, -1),
    object_event(4, 4, SPRITE_GROWLITHE, SPRITEMOVEDATA_POKEMON, 2, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &CeladonMansion1FNidoranF, -1),
};

const struct MapEvents CeladonMansion1F_MapEvents = {
    .warp_event_count = lengthof(CeladonMansion1F_WarpEvents),
    .warp_events = CeladonMansion1F_WarpEvents,

    .coord_event_count = 0, // lengthof(CeladonMansion1F_CoordEvents),
    .coord_events = CeladonMansion1F_CoordEvents,

    .bg_event_count = lengthof(CeladonMansion1F_BGEvents),
    .bg_events = CeladonMansion1F_BGEvents,

    .obj_event_count = lengthof(CeladonMansion1F_ObjectEvents),
    .obj_events = CeladonMansion1F_ObjectEvents,
};

//// CODE

bool CeladonMansionManager(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CeladonMansionManagerText)
    SCRIPT_END
}
bool CeladonMansion1FMeowth(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(CeladonMansion1FMeowthText)
    playcry(MEOWTH)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool CeladonMansion1FClefairy(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(CeladonMansion1FClefairyText)
    playcry(CLEFAIRY)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool CeladonMansion1FNidoranF(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(CeladonMansion1FNidoranFText)
    playcry(NIDORAN_F)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool CeladonMansionManagersSuiteSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(CeladonMansionManagersSuiteSignText)
    SCRIPT_END
}
bool CeladonMansion1FBookshelf(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PictureBookshelfScript)
    SCRIPT_END
}
const txt_cmd_s CeladonMansionManagerText[] = {
    text_start("My dear #MON"
        t_line "keep me company,"
        t_para "so I don't ever"
        t_line "feel lonely."
        t_para "MEOWTH even brings"
        t_line "money home."
        t_done )
};
const txt_cmd_s CeladonMansion1FMeowthText[] = {
    text_start("MEOWTH: Meow!"
        t_done )
};
const txt_cmd_s CeladonMansion1FClefairyText[] = {
    text_start("CLEFAIRY: Clef"
        t_line "cleff!"
        t_done )
};
const txt_cmd_s CeladonMansion1FNidoranFText[] = {
    text_start("NIDORAN: Kya"
        t_line "kyaoo!"
        t_done )
};
const txt_cmd_s CeladonMansionManagersSuiteSignText[] = {
    text_start("CELADON MANSION"
        t_line "MANAGER'S SUITE"
        t_done )
    //db(0, 0) // filler
};
