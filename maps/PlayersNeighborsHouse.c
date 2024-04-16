#include "../constants.h"
#include "../util/scripting.h"
#include "PlayersNeighborsHouse.h"
//// EVENTS
enum {
    PLAYERSNEIGHBORSHOUSE_COOLTRAINER_F = 2,
    PLAYERSNEIGHBORSHOUSE_POKEFAN_F,
};

static const Script_fn_t PlayersNeighborsHouse_SceneScripts[] = {
    0,
};

static const struct MapCallback PlayersNeighborsHouse_MapCallbacks[] = {
    0,
};

const struct MapScripts PlayersNeighborsHouse_MapScripts = {
    .scene_script_count = 0, // lengthof(PlayersNeighborsHouse_SceneScripts),
    .scene_scripts = PlayersNeighborsHouse_SceneScripts,

    .callback_count = 0, // lengthof(PlayersNeighborsHouse_MapCallbacks),
    .callbacks = PlayersNeighborsHouse_MapCallbacks,
};

static const struct CoordEvent PlayersNeighborsHouse_CoordEvents[] = {
    0,
};

static const struct BGEvent PlayersNeighborsHouse_BGEvents[] = {
    bg_event(0, 1, BGEVENT_READ, &PlayersNeighborsHouseBookshelfScript),
    bg_event(1, 1, BGEVENT_READ, &PlayersNeighborsHouseBookshelfScript),
    bg_event(7, 1, BGEVENT_READ, &PlayersNeighborsHouseRadioScript),
};

static const struct WarpEventData PlayersNeighborsHouse_WarpEvents[] = {
    warp_event(2, 7, NEW_BARK_TOWN, 3),
    warp_event(3, 7, NEW_BARK_TOWN, 3),
};

static const struct ObjEvent PlayersNeighborsHouse_ObjectEvents[] = {
    object_event(2, 3, SPRITE_COOLTRAINER_F, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &PlayersNeighborsDaughterScript, -1),
    object_event(5, 3, SPRITE_POKEFAN_F, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &PlayersNeighborScript, EVENT_PLAYERS_NEIGHBORS_HOUSE_NEIGHBOR),
};

const struct MapEvents PlayersNeighborsHouse_MapEvents = {
    .warp_event_count = lengthof(PlayersNeighborsHouse_WarpEvents),
    .warp_events = PlayersNeighborsHouse_WarpEvents,

    .coord_event_count = 0, // lengthof(PlayersNeighborsHouse_CoordEvents),
    .coord_events = PlayersNeighborsHouse_CoordEvents,

    .bg_event_count = lengthof(PlayersNeighborsHouse_BGEvents),
    .bg_events = PlayersNeighborsHouse_BGEvents,

    .obj_event_count = lengthof(PlayersNeighborsHouse_ObjectEvents),
    .obj_events = PlayersNeighborsHouse_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "PlayersNeighborsHouse.h"

bool PlayersNeighborsDaughterScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(PlayersNeighborsDaughterText)
    SCRIPT_END
}
bool PlayersNeighborScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(PlayersNeighborText)
    SCRIPT_END
}
bool PlayersNeighborsHouseBookshelfScript(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(MagazineBookshelfScript)
    SCRIPT_END
}
bool PlayersNeighborsHouseRadioScript(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_GOT_A_POKEMON_FROM_ELM)
    iftrue(NormalRadio)
    checkevent(EVENT_LISTENED_TO_INITIAL_RADIO)
    iftrue(AbbreviatedRadio)
    playmusic(MUSIC_POKEMON_TALK)
    opentext
    writetext(PlayerNeighborRadioText1)
    pause(45)
    writetext(PlayerNeighborRadioText2)
    pause(45)
    writetext(PlayerNeighborRadioText3)
    pause(45)
    musicfadeout(MUSIC_NEW_BARK_TOWN, 16)
    writetext(PlayerNeighborRadioText4)
    pause(45)
    closetext
    setevent(EVENT_LISTENED_TO_INITIAL_RADIO)
    s_end
NormalRadio:
    jumpstd(Radio1Script)
AbbreviatedRadio:
    opentext
    writetext(PlayerNeighborRadioText4)
    pause(45)
    closetext
    s_end
    SCRIPT_END
}
const txt_cmd_s PlayersNeighborsDaughterText[] = {
    text_start("PIKACHU is an"
        t_line "evolved #MON."
        t_para "I was amazed by"
        t_line "PROF.ELM's find-"
        t_cont "ings."
        t_para "He's so famous for"
        t_line "his research on"
        t_cont "#MON evolution."
        t_para "…sigh…"
        t_para "I wish I could be"
        t_line "a researcher like"
        t_cont "him…"
        t_done )
};
const txt_cmd_s PlayersNeighborText[] = {
    text_start("My daughter is"
        t_line "adamant about"
        t_para "becoming PROF."
        t_line "ELM's assistant."
        t_para "She really loves"
        t_line "#MON!"
        t_para "But then, so do I!"
        t_done )
};
const txt_cmd_s PlayerNeighborRadioText1[] = {
    text_start("PROF.OAK'S #MON"
        t_line "TALK! Please tune"
        t_cont "in next time!"
        t_done )
};
const txt_cmd_s PlayerNeighborRadioText2[] = {
    text_start("#MON CHANNEL!"
        t_done )
};
const txt_cmd_s PlayerNeighborRadioText3[] = {
    text_start("This is DJ MARY,"
        t_line "your co-host!"
        t_done )
};
const txt_cmd_s PlayerNeighborRadioText4[] = {
    text_start("#MON!"
        t_line "#MON CHANNEL…"
        t_done )
    //db(0, 0) // filler
};
