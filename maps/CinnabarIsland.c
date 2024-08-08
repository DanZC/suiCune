#include "../constants.h"
#include "../util/scripting.h"
#include "CinnabarIsland.h"
//// EVENTS
enum {
    CINNABARISLAND_BLUE = 2,
};

const Script_fn_t CinnabarIsland_SceneScripts[] = {
    0,
};

const struct MapCallback CinnabarIsland_MapCallbacks[] = {
    map_callback(MAPCALLBACK_NEWMAP, CinnabarIsland_MapScripts_FlyPoint),
};

const struct MapScripts CinnabarIsland_MapScripts = {
    .scene_script_count = 0, // lengthof(CinnabarIsland_SceneScripts),
    .scene_scripts = CinnabarIsland_SceneScripts,

    .callback_count = lengthof(CinnabarIsland_MapCallbacks),
    .callbacks = CinnabarIsland_MapCallbacks,
};

static const struct CoordEvent CinnabarIsland_CoordEvents[] = {
    0,
};

static const struct BGEvent CinnabarIsland_BGEvents[] = {
    bg_event(12, 11, BGEVENT_READ, &CinnabarIslandPokecenterSign),
    bg_event(9, 11, BGEVENT_READ, &CinnabarIslandGymSign),
    bg_event(7, 7, BGEVENT_READ, &CinnabarIslandSign),
    bg_event(9, 1, BGEVENT_ITEM, &CinnabarIslandHiddenRareCandy),
};

static const struct WarpEventData CinnabarIsland_WarpEvents[] = {
    warp_event(11, 11, CINNABAR_POKECENTER_1F, 1),
};

static const struct ObjEvent CinnabarIsland_ObjectEvents[] = {
    object_event(9, 6, SPRITE_BLUE, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &CinnabarIslandBlue, EVENT_BLUE_IN_CINNABAR),
};

const struct MapEvents CinnabarIsland_MapEvents = {
    .warp_event_count = lengthof(CinnabarIsland_WarpEvents),
    .warp_events = CinnabarIsland_WarpEvents,

    .coord_event_count = 0, // lengthof(CinnabarIsland_CoordEvents),
    .coord_events = CinnabarIsland_CoordEvents,

    .bg_event_count = lengthof(CinnabarIsland_BGEvents),
    .bg_events = CinnabarIsland_BGEvents,

    .obj_event_count = lengthof(CinnabarIsland_ObjectEvents),
    .obj_events = CinnabarIsland_ObjectEvents,
};

//// CODE

bool CinnabarIsland_MapScripts_FlyPoint(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_FLYPOINT_CINNABAR)
    s_endcallback
    SCRIPT_END
}
bool CinnabarIslandBlue(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(CinnabarIslandBlueText)
    waitbutton
    closetext
    playsound(SFX_WARP_TO)
    applymovement(CINNABARISLAND_BLUE, CinnabarIslandBlueTeleport)
    disappear(CINNABARISLAND_BLUE)
    clearevent(EVENT_VIRIDIAN_GYM_BLUE)
    s_end
    SCRIPT_END
}
bool CinnabarIslandGymSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(CinnabarIslandGymSignText)
    SCRIPT_END
}
bool CinnabarIslandSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(CinnabarIslandSignText)
    SCRIPT_END
}
bool CinnabarIslandPokecenterSign(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PokecenterSignScript)
    SCRIPT_END
}
const struct HiddenItem CinnabarIslandHiddenRareCandy = {RARE_CANDY, EVENT_CINNABAR_ISLAND_HIDDEN_RARE_CANDY};
const uint8_t CinnabarIslandBlueTeleport[] = {
    movement_teleport_from,
    movement_step_end,
};
const txt_cmd_s CinnabarIslandBlueText[] = {
    text_start("Who are you?"
        t_para "Well, it's plain"
        t_line "to see that you're"
        t_cont "a trainer…"
        t_para "My name's BLUE."
        t_para "I was once the"
        t_line "CHAMPION, although"
        t_para "it was for only a"
        t_line "short time…"
        t_para "That meddling RED"
        t_line "did me in…"
        t_para "Anyway, what do"
        t_line "you want? You want"
        t_para "to challenge me or"
        t_line "something?"
        t_para "…I hate to say"
        t_line "it, but I'm not in"
        t_para "the mood for a"
        t_line "battle now."
        t_para "Take a good look"
        t_line "around you…"
        t_para "A volcano erupts,"
        t_line "and just like"
        t_para "that, a whole town"
        t_line "disappears."
        t_para "We can go on win-"
        t_line "ning and losing in"
        t_para "#MON. But if"
        t_line "nature so much as"
        t_para "twitches, we can"
        t_line "lose in a second."
        t_para "…"
        t_para "That's the way it"
        t_line "is…"
        t_para "But, anyway, I'm"
        t_line "still a trainer."
        t_para "If I see a strong"
        t_line "opponent, it makes"
        t_cont "me want to battle."
        t_para "If you want to"
        t_line "battle me, come to"
        t_cont "the VIRIDIAN GYM."
        t_para "I'll take you on"
        t_line "then."
        t_done )
};
const txt_cmd_s CinnabarIslandGymSignText[] = {
    text_start("There's a notice"
        t_line "here…"
        t_para "CINNABAR GYM has"
        t_line "relocated to SEA-"
        t_cont "FOAM ISLANDS."
        t_para "BLAINE"
        t_done )
};
const txt_cmd_s CinnabarIslandSignText[] = {
    text_start("CINNABAR ISLAND"
        t_para "The Fiery Town of"
        t_line "Burning Desire"
        t_done )
    //db(0, 0) // filler
};
