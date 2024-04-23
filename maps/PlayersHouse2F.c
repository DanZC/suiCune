#include "../constants.h"
#include "../util/scripting.h"
#include "PlayersHouse2F.h"
//// EVENTS
enum {
    PLAYERSHOUSE2F_CONSOLE = 2,
    PLAYERSHOUSE2F_DOLL_1,
    PLAYERSHOUSE2F_DOLL_2,
    PLAYERSHOUSE2F_BIG_DOLL,
};

const Script_fn_t PlayersHouse2F_SceneScripts[] = {
    0,
};

const struct MapCallback PlayersHouse2F_MapCallbacks[] = {
    map_callback(MAPCALLBACK_NEWMAP, PlayersHouse2F_MapScripts_InitializeRoom),
    map_callback(MAPCALLBACK_TILES, PlayersHouse2F_MapScripts_SetUpTileDecorations),
};

const struct MapScripts PlayersHouse2F_MapScripts = {
    .scene_script_count = 0, // lengthof(PlayersHouse2F_SceneScripts),
    .scene_scripts = PlayersHouse2F_SceneScripts,

    .callback_count = lengthof(PlayersHouse2F_MapCallbacks),
    .callbacks = PlayersHouse2F_MapCallbacks,
};

static const struct CoordEvent PlayersHouse2F_CoordEvents[] = {
    0,
};

static const struct BGEvent PlayersHouse2F_BGEvents[] = {
    bg_event(2, 1, BGEVENT_UP, &PlayersHousePCScript),
    bg_event(3, 1, BGEVENT_READ, &PlayersHouseRadioScript),
    bg_event(5, 1, BGEVENT_READ, &PlayersHouseBookshelfScript),
    bg_event(6, 0, BGEVENT_IFSET, &PlayersHousePosterScript),
};

static const struct WarpEventData PlayersHouse2F_WarpEvents[] = {
    warp_event(7, 0, PLAYERS_HOUSE_1F, 3),
};

static const struct ObjEvent PlayersHouse2F_ObjectEvents[] = {
    object_event(4, 2, SPRITE_CONSOLE, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &PlayersHouseGameConsoleScript, EVENT_PLAYERS_HOUSE_2F_CONSOLE),
    object_event(4, 4, SPRITE_DOLL_1, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &PlayersHouseDoll1Script, EVENT_PLAYERS_HOUSE_2F_DOLL_1),
    object_event(5, 4, SPRITE_DOLL_2, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &PlayersHouseDoll2Script, EVENT_PLAYERS_HOUSE_2F_DOLL_2),
    object_event(0, 1, SPRITE_BIG_DOLL, SPRITEMOVEDATA_BIGDOLL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &PlayersHouseBigDollScript, EVENT_PLAYERS_HOUSE_2F_BIG_DOLL),
};

const struct MapEvents PlayersHouse2F_MapEvents = {
    .warp_event_count = lengthof(PlayersHouse2F_WarpEvents),
    .warp_events = PlayersHouse2F_WarpEvents,

    .coord_event_count = 0, // lengthof(PlayersHouse2F_CoordEvents),
    .coord_events = PlayersHouse2F_CoordEvents,

    .bg_event_count = lengthof(PlayersHouse2F_BGEvents),
    .bg_events = PlayersHouse2F_BGEvents,

    .obj_event_count = lengthof(PlayersHouse2F_ObjectEvents),
    .obj_events = PlayersHouse2F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "PlayersHouse2F.h"

bool PlayersHouse2F_MapScripts_DummyScene(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool PlayersHouse2F_MapScripts_InitializeRoom(script_s* s) {
    SCRIPT_BEGIN
    special(ToggleDecorationsVisibility)
    setevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_8)
    checkevent(EVENT_INITIALIZED_EVENTS)
    iftrue_jump(PlayersHouse2F_MapScripts_SkipInitialization)
    jumpstd(InitializeEventsScript)
    s_endcallback
    SCRIPT_END
}
bool PlayersHouse2F_MapScripts_SkipInitialization(script_s* s) {
    SCRIPT_BEGIN
    s_endcallback
    SCRIPT_END
}
bool PlayersHouse2F_MapScripts_SetUpTileDecorations(script_s* s) {
    SCRIPT_BEGIN
    special(ToggleMaptileDecorations)
    s_endcallback
    //db(0, 0, 0) // unused
    SCRIPT_END
}
bool PlayersHouseDoll1Script(script_s* s) {
    SCRIPT_BEGIN
    describedecoration(DECODESC_LEFT_DOLL)
    SCRIPT_END
}
bool PlayersHouseDoll2Script(script_s* s) {
    SCRIPT_BEGIN
    describedecoration(DECODESC_RIGHT_DOLL)
    SCRIPT_END
}
bool PlayersHouseBigDollScript(script_s* s) {
    SCRIPT_BEGIN
    describedecoration(DECODESC_BIG_DOLL)
    SCRIPT_END
}
bool PlayersHouseGameConsoleScript(script_s* s) {
    SCRIPT_BEGIN
    describedecoration(DECODESC_CONSOLE)
    SCRIPT_END
}
const struct ConditionalEvent PlayersHousePosterScript = conditional_event(EVENT_PLAYERS_ROOM_POSTER, PlayersHousePosterScript_Script);
bool PlayersHousePosterScript_Script(script_s* s) {
    SCRIPT_BEGIN
    describedecoration(DECODESC_POSTER)
    SCRIPT_END
}
bool PlayersHouseRadioScript(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_GOT_A_POKEMON_FROM_ELM)
    iftrue(NormalRadio)
    checkevent(EVENT_LISTENED_TO_INITIAL_RADIO)
    iftrue(AbbreviatedRadio)
    playmusic(MUSIC_POKEMON_TALK)
    opentext
    writetext(PlayersRadioText1)
    pause(45)
    writetext(PlayersRadioText2)
    pause(45)
    writetext(PlayersRadioText3)
    pause(45)
    musicfadeout(MUSIC_NEW_BARK_TOWN, 16)
    writetext(PlayersRadioText4)
    pause(45)
    closetext
    setevent(EVENT_LISTENED_TO_INITIAL_RADIO)
    s_end
NormalRadio:
    jumpstd(Radio1Script)
AbbreviatedRadio:
    opentext
    writetext(PlayersRadioText4)
    pause(45)
    closetext
    s_end
    SCRIPT_END
}
bool PlayersHouseBookshelfScript(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PictureBookshelfScript)
    SCRIPT_END
}
bool PlayersHousePCScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    special(PlayersHousePC)
    iftrue(Warp)
    closetext
    s_end
Warp:
    warp(NONE, 0, 0)
    s_end
    SCRIPT_END
}
const txt_cmd_s PlayersRadioText1[] = {
    text_start("PROF.OAK'S #MON"
        t_line "TALK! Please tune"
        t_cont "in next time!"
        t_done )
};
const txt_cmd_s PlayersRadioText2[] = {
    text_start("#MON CHANNEL!"
        t_done )
};
const txt_cmd_s PlayersRadioText3[] = {
    text_start("This is DJ MARY,"
        t_line "your co-host!"
        t_done )
};
const txt_cmd_s PlayersRadioText4[] = {
    text_start("#MON!"
        t_line "#MON CHANNEL…"
        t_done )
    //db(0, 0) // filler
};
