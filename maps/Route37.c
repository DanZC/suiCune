#include "../constants.h"
#include "../util/scripting.h"
#include "Route37.h"
//// EVENTS
enum {
    ROUTE37_WEIRD_TREE1 = 2,
    ROUTE37_WEIRD_TREE2,
    ROUTE37_YOUNGSTER,
    ROUTE37_FRUIT_TREE1,
    ROUTE37_SUNNY,
    ROUTE37_FRUIT_TREE2,
    ROUTE37_FRUIT_TREE3,
};

const Script_fn_t Route37_SceneScripts[] = {
    0,
};

const struct MapCallback Route37_MapCallbacks[] = {
    map_callback(MAPCALLBACK_OBJECTS, Route37_MapScripts_Sunny),
};

const struct MapScripts Route37_MapScripts = {
    .scene_script_count = 0, // lengthof(Route37_SceneScripts),
    .scene_scripts = Route37_SceneScripts,

    .callback_count = lengthof(Route37_MapCallbacks),
    .callbacks = Route37_MapCallbacks,
};

static const struct CoordEvent Route37_CoordEvents[] = {
    0,
};

static const struct BGEvent Route37_BGEvents[] = {
    bg_event(5, 3, BGEVENT_READ, &Route37Sign),
    bg_event(4, 2, BGEVENT_ITEM, &Route37HiddenEther),
};

static const struct WarpEventData Route37_WarpEvents[] = {
    0,
};

static const struct ObjEvent Route37_ObjectEvents[] = {
    object_event(6, 12, SPRITE_WEIRD_TREE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 1, &TrainerTwinsAnnandanne1, -1),
    object_event(7, 12, SPRITE_WEIRD_TREE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 1, &TrainerTwinsAnnandanne2, -1),
    object_event(6, 6, SPRITE_YOUNGSTER, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 1, &TrainerPsychicGreg, -1),
    object_event(13, 5, SPRITE_FRUIT_TREE, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Route37FruitTree1, -1),
    object_event(16, 8, SPRITE_BUG_CATCHER, SPRITEMOVEDATA_WANDER, 1, 1, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &SunnyScript, EVENT_ROUTE_37_SUNNY_OF_SUNDAY),
    object_event(16, 5, SPRITE_FRUIT_TREE, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Route37FruitTree2, -1),
    object_event(15, 7, SPRITE_FRUIT_TREE, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Route37FruitTree3, -1),
};

const struct MapEvents Route37_MapEvents = {
    .warp_event_count = 0, // lengthof(Route37_WarpEvents),
    .warp_events = Route37_WarpEvents,

    .coord_event_count = 0, // lengthof(Route37_CoordEvents),
    .coord_events = Route37_CoordEvents,

    .bg_event_count = lengthof(Route37_BGEvents),
    .bg_events = Route37_BGEvents,

    .obj_event_count = lengthof(Route37_ObjectEvents),
    .obj_events = Route37_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "Route37.h"

bool Route37_MapScripts_Sunny(script_s* s) {
    SCRIPT_BEGIN
    readvar(VAR_WEEKDAY)
    ifequal_jump(SUNDAY, Route37_MapScripts_SunnyAppears)
    disappear(ROUTE37_SUNNY)
    s_endcallback
    SCRIPT_END
}
bool Route37_MapScripts_SunnyAppears(script_s* s) {
    SCRIPT_BEGIN
    appear(ROUTE37_SUNNY)
    s_endcallback
    SCRIPT_END
}
const struct TrainerObj TrainerTwinsAnnandanne1 = {TWINS, ANNANDANNE1, EVENT_BEAT_TWINS_ANN_AND_ANNE, TwinsAnnandanne1SeenText, TwinsAnnandanne1BeatenText, 0, TrainerTwinsAnnandanne1_Script};
bool TrainerTwinsAnnandanne1_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(TwinsAnnandanne1AfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerTwinsAnnandanne2 = {TWINS, ANNANDANNE2, EVENT_BEAT_TWINS_ANN_AND_ANNE, TwinsAnnandanne2SeenText, TwinsAnnandanne2BeatenText, 0, TrainerTwinsAnnandanne2_Script};
bool TrainerTwinsAnnandanne2_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(TwinsAnnandanne2AfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerPsychicGreg = {PSYCHIC_T, GREG, EVENT_BEAT_PSYCHIC_GREG, PsychicGregSeenText, PsychicGregBeatenText, 0, TrainerPsychicGreg_Script};
bool TrainerPsychicGreg_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(PsychicGregAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool SunnyScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_MAGNET_FROM_SUNNY)
    iftrue_jump(SunnySundayScript)
    readvar(VAR_WEEKDAY)
    ifnotequal_jump(SUNDAY, SunnyNotSundayScript)
    checkevent(EVENT_MET_SUNNY_OF_SUNDAY)
    iftrue(MetSunny)
    writetext(MeetSunnyText)
    promptbutton
    setevent(EVENT_MET_SUNNY_OF_SUNDAY)
MetSunny:
    checkflag(ENGINE_PLAYER_IS_FEMALE)
    iftrue(Kris)
    writetext(SunnyGivesGiftText1)
    promptbutton
    goto next;
Kris:
    writetext(SunnyGivesGiftText2)
    promptbutton
next:
    verbosegiveitem(MAGNET, 1)
    iffalse_jump(SunnyDoneScript)
    setevent(EVENT_GOT_MAGNET_FROM_SUNNY)
    writetext(SunnyGaveGiftText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool SunnySundayScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(SunnySundayText)
    waitbutton
    SCRIPT_FALLTHROUGH(SunnyDoneScript)
}
bool SunnyDoneScript(script_s* s) {
    SCRIPT_BEGIN
    closetext
    s_end
    SCRIPT_END
}
bool SunnyNotSundayScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(SunnyNotSundayText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Route37Sign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route37SignText)
    SCRIPT_END
}
bool Route37FruitTree1(script_s* s) {
    SCRIPT_BEGIN
    fruittree(FRUITTREE_ROUTE_37_1)
    SCRIPT_FALLTHROUGH(Route37FruitTree2)
}
bool Route37FruitTree2(script_s* s) {
    SCRIPT_BEGIN
    fruittree(FRUITTREE_ROUTE_37_2)
    SCRIPT_FALLTHROUGH(Route37FruitTree3)
}
bool Route37FruitTree3(script_s* s) {
    SCRIPT_BEGIN
    fruittree(FRUITTREE_ROUTE_37_3)
    SCRIPT_END
}
const struct HiddenItem Route37HiddenEther = {ETHER, EVENT_ROUTE_37_HIDDEN_ETHER};
const txt_cmd_s TwinsAnnandanne1SeenText[] = {
    text_start("ANN: ANNE and I"
        t_line "are in this to-"
        t_cont "gether!"
        t_done )
};
const txt_cmd_s TwinsAnnandanne1BeatenText[] = {
    text_start("ANN & ANNE: Nnn… A"
        t_line "little too strong."
        t_done )
};
const txt_cmd_s TwinsAnnandanne1AfterBattleText[] = {
    text_start("ANN: I can tell"
        t_line "what my sister and"
        t_para "my #MON are"
        t_line "thinking."
        t_done )
};
const txt_cmd_s TwinsAnnandanne2SeenText[] = {
    text_start("ANNE: ANN and I"
        t_line "are in this to-"
        t_cont "gether!"
        t_done )
};
const txt_cmd_s TwinsAnnandanne2BeatenText[] = {
    text_start("ANN & ANNE: Nnn… A"
        t_line "little too strong."
        t_done )
};
const txt_cmd_s TwinsAnnandanne2AfterBattleText[] = {
    text_start("ANNE: We share the"
        t_line "same feelings as"
        t_cont "our #MON."
        t_done )
};
const txt_cmd_s PsychicGregSeenText[] = {
    text_start("#MON can't do a"
        t_line "thing if they are"
        t_cont "asleep."
        t_para "I'll show you how"
        t_line "scary that is!"
        t_done )
};
const txt_cmd_s PsychicGregBeatenText[] = {
    text_start("I lost. That's"
        t_line "pretty sad…"
        t_done )
};
const txt_cmd_s PsychicGregAfterBattleText[] = {
    text_start("Putting #MON to"
        t_line "sleep or paralyz-"
        t_cont "ing them are good"
        t_cont "battle techniques."
        t_done )
};
const txt_cmd_s MeetSunnyText[] = {
    text_start("SUNNY: Hi!"
        t_para "I'm SUNNY of Sun-"
        t_line "day, meaning it's"
        t_cont "Sunday today!"
        t_done )
};
const txt_cmd_s SunnyGivesGiftText1[] = {
    text_start("I was told to give"
        t_line "you this if I saw"
        t_cont "you!"
        t_done )
};
const txt_cmd_s SunnyGivesGiftText2[] = {
    text_start("I was told to give"
        t_line "you this if I saw"
        t_cont "you!"
        t_done )
};
const txt_cmd_s SunnyGaveGiftText[] = {
    text_start("SUNNY: That thing…"
        t_para "Um…"
        t_para "… What was it now…"
        t_para "…"
        t_para "Oh! I remember"
        t_line "now!"
        t_para "A #MON that"
        t_line "knows electric"
        t_para "moves should hold"
        t_line "it."
        t_para "My sis MONICA said"
        t_line "it powers up"
        t_cont "electric moves!"
        t_done )
};
const txt_cmd_s SunnySundayText[] = {
    text_start("SUNNY: My sisters"
        t_line "and brothers are"
        t_cont "MONICA, TUSCANY,"
        t_cont "WESLEY, ARTHUR,"
        t_cont "FRIEDA and SANTOS."
        t_para "They're all older"
        t_line "than me!"
        t_done )
};
const txt_cmd_s SunnyNotSundayText[] = {
    text_start("SUNNY: Isn't today"
        t_line "Sunday?"
        t_cont "Um… I forgot!"
        t_done )
};
const txt_cmd_s Route37SignText[] = {
    text_start("ROUTE 37"
        t_done )
    //db(0, 0) // filler
};
