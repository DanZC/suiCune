#include "../constants.h"
#include "../util/scripting.h"
#include "Route24.h"
//// EVENTS
enum {
    ROUTE24_ROCKET = 2,
};

const Script_fn_t Route24_SceneScripts[] = {
    0,
};

const struct MapCallback Route24_MapCallbacks[] = {
    0,
};

const struct MapScripts Route24_MapScripts = {
    .scene_script_count = 0, // lengthof(Route24_SceneScripts),
    .scene_scripts = Route24_SceneScripts,

    .callback_count = 0, // lengthof(Route24_MapCallbacks),
    .callbacks = Route24_MapCallbacks,
};

static const struct CoordEvent Route24_CoordEvents[] = {
    0,
};

static const struct BGEvent Route24_BGEvents[] = {
    0,
};

static const struct WarpEventData Route24_WarpEvents[] = {
    0,
};

static const struct ObjEvent Route24_ObjectEvents[] = {
    object_event(8, 7, SPRITE_ROCKET, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Route24RocketScript, EVENT_ROUTE_24_ROCKET),
};

const struct MapEvents Route24_MapEvents = {
    .warp_event_count = 0, // lengthof(Route24_WarpEvents),
    .warp_events = Route24_WarpEvents,

    .coord_event_count = 0, // lengthof(Route24_CoordEvents),
    .coord_events = Route24_CoordEvents,

    .bg_event_count = 0, // lengthof(Route24_BGEvents),
    .bg_events = Route24_BGEvents,

    .obj_event_count = lengthof(Route24_ObjectEvents),
    .obj_events = Route24_ObjectEvents,
};

//// CODE

bool Route24RocketScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    playmusic(MUSIC_ROCKET_ENCOUNTER)
    opentext
    writetext(Route24RocketSeenText)
    waitbutton
    closetext
    winlosstext(Route24RocketBeatenText, NULL)
    loadtrainer(GRUNTM, GRUNTM_31)
    startbattle
    dontrestartmapmusic
    reloadmapafterbattle
    playmusic(MUSIC_ROCKET_ENCOUNTER)
    opentext
    writetext(Route24RocketAfterBattleText)
    promptbutton
    special(FadeOutMusic)
    writetext(Route24RocketDisappearsText)
    waitbutton
    closetext
    special(FadeBlackQuickly)
    special(ReloadSpritesNoPalettes)
    disappear(ROUTE24_ROCKET)
    pause(25)
    special(FadeInQuickly)
    playmapmusic
    s_end
    SCRIPT_END
}
const txt_cmd_s Route24RocketSeenText[] = {
    text_start("Hey, kid! Me am a"
        t_line "TEAM ROCKET member"
        t_cont "kind of guy!"
        t_para "Come from another"
        t_line "country, a trainer"
        t_cont "number one, me!"
        t_para "Think I did, if"
        t_line "stop the energy,"
        t_para "be big panic for"
        t_line "here people!"
        t_para "Secret it is my"
        t_line "mission, so tell"
        t_cont "you I not!"
        t_para "But! If win you do"
        t_line "versus me, a man I"
        t_para "be and mine secret"
        t_line "to you I tell."
        t_para "Hey, kid! Battle"
        t_line "begin we do!"
        t_done )
};
const txt_cmd_s Route24RocketBeatenText[] = {
    text_start("Ayieeeh! No, no,"
        t_line "no, believe it I"
        t_cont "can't!"
        t_para "Strong very much"
        t_line "be you! Match I am"
        t_cont "not to you!"
        t_done )
};
const txt_cmd_s Route24RocketAfterBattleText[] = {
    text_start("OK. Tell you mine"
        t_line "secret will I."
        t_para "MACHINE PART steal"
        t_line "by me, hide it I"
        t_para "did in GYM of the"
        t_line "CERULEAN."
        t_para "Inside water put"
        t_line "it I did. Look for"
        t_para "in water center of"
        t_line "GYM at."
        t_para "But you forget me"
        t_line "not!"
        t_para "Beat you for sure"
        t_line "will TEAM ROCKET."
        t_para "Come from JOHTO"
        t_line "will they, mine"
        t_para "friends, yes. Will"
        t_line "revenge they are."
        t_done )
};
const txt_cmd_s Route24RocketDisappearsText[] = {
    text_start("…"
        t_para "You say what? TEAM"
        t_line "ROCKET bye-bye a"
        t_para "go-go? Broken it"
        t_line "is says you?"
        t_para "Oh, no! Should I"
        t_line "do what now on"
        t_cont "from, me?"
        t_done )
    //db(0, 0) // filler
};
