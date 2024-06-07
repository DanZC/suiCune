#include "../constants.h"
#include "../util/scripting.h"
#include "Route39Barn.h"
//// EVENTS
enum {
    ROUTE39BARN_TWIN1 = 2,
    ROUTE39BARN_TWIN2,
    ROUTE39BARN_MOOMOO,
};

const Script_fn_t Route39Barn_SceneScripts[] = {
    0,
};

const struct MapCallback Route39Barn_MapCallbacks[] = {
    0,
};

const struct MapScripts Route39Barn_MapScripts = {
    .scene_script_count = 0, // lengthof(Route39Barn_SceneScripts),
    .scene_scripts = Route39Barn_SceneScripts,

    .callback_count = 0, // lengthof(Route39Barn_MapCallbacks),
    .callbacks = Route39Barn_MapCallbacks,
};

static const struct CoordEvent Route39Barn_CoordEvents[] = {
    0,
};

static const struct BGEvent Route39Barn_BGEvents[] = {
    0,
};

static const struct WarpEventData Route39Barn_WarpEvents[] = {
    warp_event(3, 7, ROUTE_39, 1),
    warp_event(4, 7, ROUTE_39, 1),
};

static const struct ObjEvent Route39Barn_ObjectEvents[] = {
    object_event(2, 3, SPRITE_TWIN, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Route39BarnTwin1Script, -1),
    object_event(4, 3, SPRITE_TWIN, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &Route39BarnTwin2Script, -1),
    object_event(3, 3, SPRITE_TAUROS, SPRITEMOVEDATA_POKEMON, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &MoomooScript, -1),
};

const struct MapEvents Route39Barn_MapEvents = {
    .warp_event_count = lengthof(Route39Barn_WarpEvents),
    .warp_events = Route39Barn_WarpEvents,

    .coord_event_count = 0, // lengthof(Route39Barn_CoordEvents),
    .coord_events = Route39Barn_CoordEvents,

    .bg_event_count = 0, // lengthof(Route39Barn_BGEvents),
    .bg_events = Route39Barn_BGEvents,

    .obj_event_count = lengthof(Route39Barn_ObjectEvents),
    .obj_events = Route39Barn_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "Route39Barn.h"

bool Route39BarnTwin1Script(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_HEALED_MOOMOO)
    iftrue(FeedingMooMoo)
    writetext(Route39BarnTwinMoomooIsSickText)
    waitbutton
    closetext
    turnobject(ROUTE39BARN_TWIN1, RIGHT)
    s_end
FeedingMooMoo:
    writetext(Route39BarnTwinWereFeedingMoomooText)
    waitbutton
    closetext
    turnobject(ROUTE39BARN_TWIN1, RIGHT)
    s_end
    SCRIPT_END
}
bool Route39BarnTwin2Script(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_HEALED_MOOMOO)
    iftrue(FeedingMooMoo)
    writetext(Route39BarnTwinMoomooIsSickText)
    waitbutton
    closetext
    turnobject(ROUTE39BARN_TWIN2, LEFT)
    s_end
FeedingMooMoo:
    writetext(Route39BarnTwinWereFeedingMoomooText)
    waitbutton
    closetext
    turnobject(ROUTE39BARN_TWIN2, LEFT)
    s_end
    SCRIPT_END
}
bool MoomooScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    checkevent(EVENT_HEALED_MOOMOO)
    iftrue(HappyCow)
    writetext(MoomooWeakMooText)
    setval(MILTANK)
    special(PlaySlowCry)
    promptbutton
    writetext(Route39BarnItsCryIsWeakText)
    checkevent(EVENT_TALKED_TO_FARMER_ABOUT_MOOMOO)
    iftrue(GiveBerry)
    waitbutton
    closetext
    s_end
GiveBerry:
    promptbutton
    writetext(Route39BarnAskGiveBerryText)
    yesorno
    iffalse(Refused)
    checkitem(BERRY)
    iffalse(NoBerriesInBag)
    takeitem(BERRY, 1)
    readmem(wram_ptr(wMooMooBerries))
    addval(1)
    writemem(wram_ptr(wMooMooBerries))
    ifequal(3, ThreeBerries)
    ifequal(5, FiveBerries)
    ifequal(7, SevenBerries)
    writetext(Route39BarnGaveBerryText)
    waitbutton
    closetext
    s_end
ThreeBerries:
    writetext(Route39BarnGaveBerryText)
    promptbutton
    writetext(Route39BarnLittleHealthierText)
    waitbutton
    closetext
    s_end
FiveBerries:
    writetext(Route39BarnGaveBerryText)
    promptbutton
    writetext(Route39BarnQuiteHealthyText)
    waitbutton
    closetext
    s_end
SevenBerries:
    playmusic(MUSIC_HEAL)
    writetext(Route39BarnGaveBerryText)
    pause(60)
    promptbutton
    special(RestartMapMusic)
    writetext(Route39BarnTotallyHealthyText)
    waitbutton
    closetext
    setevent(EVENT_HEALED_MOOMOO)
    s_end
NoBerriesInBag:
    writetext(Route39BarnNoBerriesText)
    waitbutton
    closetext
    s_end
Refused:
    writetext(Route39BarnRefusedBerryText)
    waitbutton
    closetext
    s_end
HappyCow:
    writetext(MoomooHappyMooText)
    playcry(MILTANK)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const txt_cmd_s Route39BarnTwinMoomooIsSickText[] = {
    text_start("MOOMOO is sick…"
        t_para "She needs lots of"
        t_line "BERRIES."
        t_done )
};
const txt_cmd_s Route39BarnTwinWereFeedingMoomooText[] = {
    text_start("We're feeding"
        t_line "MOOMOO!"
        t_done )
};
const txt_cmd_s MoomooWeakMooText[] = {
    text_start("MILTANK: …Moo…"
        t_done )
};
const txt_cmd_s Route39BarnItsCryIsWeakText[] = {
    text_start("Its cry is weak…"
        t_done )
};
const txt_cmd_s MoomooHappyMooText[] = {
    text_start("MILTANK: Mooo!"
        t_done )
};
const txt_cmd_s Route39BarnAskGiveBerryText[] = {
    text_start("Give a BERRY to"
        t_line "MILTANK?"
        t_done )
};
const txt_cmd_s Route39BarnGaveBerryText[] = {
    text_start("<PLAYER> gave a"
        t_line "BERRY to MILTANK."
        t_done )
};
const txt_cmd_s Route39BarnLittleHealthierText[] = {
    text_start("MILTANK became a"
        t_line "little healthier!"
        t_done )
};
const txt_cmd_s Route39BarnQuiteHealthyText[] = {
    text_start("MILTANK became"
        t_line "quite healthy!"
        t_done )
};
const txt_cmd_s Route39BarnTotallyHealthyText[] = {
    text_start("MILTANK became"
        t_line "totally healthy!"
        t_done )
};
const txt_cmd_s Route39BarnNoBerriesText[] = {
    text_start("<PLAYER> has no"
        t_line "BERRIES…"
        t_done )
};
const txt_cmd_s Route39BarnRefusedBerryText[] = {
    text_start("<PLAYER> wouldn't"
        t_line "give a BERRY."
        t_para "MILTANK looks sad."
        t_done )
    //db(0, 0) // filler
};
