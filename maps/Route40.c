#include "../constants.h"
#include "../util/scripting.h"
#include "Route40.h"
//// EVENTS
enum {
    ROUTE40_OLIVINE_RIVAL1 = 2,
    ROUTE40_OLIVINE_RIVAL2,
    ROUTE40_SWIMMER_GIRL1,
    ROUTE40_SWIMMER_GIRL2,
    ROUTE40_ROCK1,
    ROUTE40_ROCK2,
    ROUTE40_ROCK3,
    ROUTE40_LASS1,
    ROUTE40_MONICA,
    ROUTE40_POKEFAN_M,
    ROUTE40_LASS2,
    ROUTE40_STANDING_YOUNGSTER,
};

const Script_fn_t Route40_SceneScripts[] = {
    0,
};

const struct MapCallback Route40_MapCallbacks[] = {
    map_callback(MAPCALLBACK_OBJECTS, Route40_MapScripts_MonicaCallback),
};

const struct MapScripts Route40_MapScripts = {
    .scene_script_count = 0, // lengthof(Route40_SceneScripts),
    .scene_scripts = Route40_SceneScripts,

    .callback_count = lengthof(Route40_MapCallbacks),
    .callbacks = Route40_MapCallbacks,
};

static const struct CoordEvent Route40_CoordEvents[] = {
    0,
};

static const struct BGEvent Route40_BGEvents[] = {
    bg_event(14, 10, BGEVENT_READ, &Route40Sign),
    bg_event(7, 8, BGEVENT_ITEM, &Route40HiddenHyperPotion),
};

static const struct WarpEventData Route40_WarpEvents[] = {
    warp_event(9, 5, ROUTE_40_BATTLE_TOWER_GATE, 1),
};

static const struct ObjEvent Route40_ObjectEvents[] = {
    object_event(14, 15, SPRITE_OLIVINE_RIVAL, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 4, &TrainerSwimmermSimon, -1),
    object_event(18, 30, SPRITE_OLIVINE_RIVAL, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 5, &TrainerSwimmermRandall, -1),
    object_event(3, 19, SPRITE_SWIMMER_GIRL, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 4, &TrainerSwimmerfElaine, -1),
    object_event(10, 25, SPRITE_SWIMMER_GIRL, SPRITEMOVEDATA_SPINCLOCKWISE, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 3, &TrainerSwimmerfPaula, -1),
    object_event(7, 11, SPRITE_ROCK, SPRITEMOVEDATA_SMASHABLE_ROCK, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Route40Rock, -1),
    object_event(6, 9, SPRITE_ROCK, SPRITEMOVEDATA_SMASHABLE_ROCK, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Route40Rock, -1),
    object_event(7, 8, SPRITE_ROCK, SPRITEMOVEDATA_SMASHABLE_ROCK, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Route40Rock, -1),
    object_event(11, 13, SPRITE_LASS, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Route40Lass1Script, -1),
    object_event(8, 10, SPRITE_BEAUTY, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &MonicaScript, EVENT_ROUTE_40_MONICA_OF_MONDAY),
    object_event(7, 6, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Route40PokefanMScript, -1),
    object_event(13, 4, SPRITE_LASS, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &Route40Lass2Script, -1),
    object_event(16, 9, SPRITE_STANDING_YOUNGSTER, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &Route40StandingYoungsterScript, EVENT_BATTLE_TOWER_OUTSIDE_SAILOR),
};

const struct MapEvents Route40_MapEvents = {
    .warp_event_count = lengthof(Route40_WarpEvents),
    .warp_events = Route40_WarpEvents,

    .coord_event_count = 0, // lengthof(Route40_CoordEvents),
    .coord_events = Route40_CoordEvents,

    .bg_event_count = lengthof(Route40_BGEvents),
    .bg_events = Route40_BGEvents,

    .obj_event_count = lengthof(Route40_ObjectEvents),
    .obj_events = Route40_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "Route40.h"

bool Route40_MapScripts_MonicaCallback(script_s* s) {
    SCRIPT_BEGIN
    clearevent(EVENT_BATTLE_TOWER_OUTSIDE_SAILOR)
    readvar(VAR_WEEKDAY)
    ifequal(MONDAY, MonicaAppears)
    disappear(ROUTE40_MONICA)
    s_endcallback
MonicaAppears:
    appear(ROUTE40_MONICA)
    s_endcallback
    SCRIPT_END
}
const struct TrainerObj TrainerSwimmerfElaine = {SWIMMERF, ELAINE, EVENT_BEAT_SWIMMERF_ELAINE, SwimmerfElaineSeenText, SwimmerfElaineBeatenText, 0, TrainerSwimmerfElaine_Script};
bool TrainerSwimmerfElaine_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SwimmerfElaineAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSwimmerfPaula = {SWIMMERF, PAULA, EVENT_BEAT_SWIMMERF_PAULA, SwimmerfPaulaSeenText, SwimmerfPaulaBeatenText, 0, TrainerSwimmerfPaula_Script};
bool TrainerSwimmerfPaula_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SwimmerfPaulaAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSwimmermSimon = {SWIMMERM, SIMON, EVENT_BEAT_SWIMMERM_SIMON, SwimmermSimonSeenText, SwimmermSimonBeatenText, 0, TrainerSwimmermSimon_Script};
bool TrainerSwimmermSimon_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SwimmermSimonAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSwimmermRandall = {SWIMMERM, RANDALL, EVENT_BEAT_SWIMMERM_RANDALL, SwimmermRandallSeenText, SwimmermRandallBeatenText, 0, TrainerSwimmermRandall_Script};
bool TrainerSwimmermRandall_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SwimmermRandallAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Route40Lass1Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(Route40Lass1Text)
    SCRIPT_END
}
bool Route40PokefanMScript(script_s* s) {
    SCRIPT_BEGIN
    special(Mobile_DummyReturnFalse)
    iftrue(mobile)
    jumptextfaceplayer(Route40PokefanMText)
mobile:
    jumptextfaceplayer(Route40PokefanMText_Mobile)
    SCRIPT_END
}
bool Route40Lass2Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(Route40Lass2Text)
    SCRIPT_END
}
bool Route40StandingYoungsterScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(Route40StandingYoungsterText)
    SCRIPT_END
}
bool MonicaScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_SHARP_BEAK_FROM_MONICA)
    iftrue(Monday)
    readvar(VAR_WEEKDAY)
    ifnotequal(MONDAY, NotMonday)
    checkevent(EVENT_MET_MONICA_OF_MONDAY)
    iftrue(MetMonica)
    writetext(MeetMonicaText)
    promptbutton
    setevent(EVENT_MET_MONICA_OF_MONDAY)
MetMonica:
    writetext(MonicaGivesGiftText)
    promptbutton
    verbosegiveitem(SHARP_BEAK, 1)
    iffalse(done)
    setevent(EVENT_GOT_SHARP_BEAK_FROM_MONICA)
    writetext(MonicaGaveGiftText)
    waitbutton
    closetext
    s_end
Monday:
    writetext(MonicaMondayText)
    waitbutton
done:
    closetext
    s_end
NotMonday:
    writetext(MonicaNotMondayText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Route40Sign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route40SignText)
    SCRIPT_END
}
bool Route40Rock(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(SmashRockScript)
    SCRIPT_END
}
const struct HiddenItem Route40HiddenHyperPotion = {HYPER_POTION, EVENT_ROUTE_40_HIDDEN_HYPER_POTION};
const uint8_t Route40_StepRightUp6Movement[] = {
    step(RIGHT),
    step(UP),
    step(UP),
    step(UP),
    step(UP),
    step(UP),
    step(UP),
    movement_step_end,
};
const uint8_t Route40_StepUp5Movement[] = {
    step(UP),
    step(UP),
    step(UP),
    step(UP),
    step(UP),
    movement_step_end,
};
const uint8_t Route40_StepUp4Movement[] = {
    step(UP),
    step(UP),
    step(UP),
    step(UP),
    movement_step_end,
};
const txt_cmd_s SwimmermSimonSeenText[] = {
    text_start("You have to warm"
        t_line "up before going"
        t_cont "into the water."
        t_para "That's basic."
        t_done )
};
const txt_cmd_s SwimmermSimonBeatenText[] = {
    text_start("OK! Uncle! I give!"
        t_done )
};
const txt_cmd_s SwimmermSimonAfterBattleText[] = {
    text_start("CIANWOOD CITY is"
        t_line "a good distance"
        t_cont "away from here."
        t_done )
};
const txt_cmd_s SwimmermRandallSeenText[] = {
    text_start("Hey, you're young"
        t_line "and fit!"
        t_para "Don't ride your"
        t_line "#MON! Swim!"
        t_done )
};
const txt_cmd_s SwimmermRandallBeatenText[] = {
    text_start("Uh-oh. I lost…"
        t_done )
};
const txt_cmd_s SwimmermRandallAfterBattleText[] = {
    text_start("Swimming exercises"
        t_line "your entire body."
        t_cont "It's healthy."
        t_done )
};
const txt_cmd_s SwimmerfElaineSeenText[] = {
    text_start("Are you going to"
        t_line "CIANWOOD?"
        t_para "How about a quick"
        t_line "battle first?"
        t_done )
};
const txt_cmd_s SwimmerfElaineBeatenText[] = {
    text_start("I lost that one!"
        t_done )
};
const txt_cmd_s SwimmerfElaineAfterBattleText[] = {
    text_start("I'd say I'm a bet-"
        t_line "ter swimmer than"
        t_cont "you. Yeah!"
        t_done )
};
const txt_cmd_s SwimmerfPaulaSeenText[] = {
    text_start("No inner tube for"
        t_line "me."
        t_para "I'm hanging on to"
        t_line "a sea #MON!"
        t_done )
};
const txt_cmd_s SwimmerfPaulaBeatenText[] = {
    text_start("Ooh, I'm feeling"
        t_line "dizzy!"
        t_done )
};
const txt_cmd_s SwimmerfPaulaAfterBattleText[] = {
    text_start("While I float like"
        t_line "this, the waves"
        t_cont "carry me along."
        t_done )
};
const txt_cmd_s Route40Lass1Text[] = {
    text_start("Although you can't"
        t_line "see it from here,"
        t_para "CIANWOOD is across"
        t_line "the sea."
        t_done )
};
const txt_cmd_s Route40PokefanMText[] = {
    text_start("Hm! There's a big"
        t_line "building up ahead!"
        t_para "What is it?"
        t_done )
};
const txt_cmd_s Route40PokefanMText_Mobile[] = {
    text_start("Hm! Look at all"
        t_line "those serious-"
        t_cont "looking trainers"
        t_cont "streaming in."
        t_para "What? What?"
        t_done )
};
const txt_cmd_s Route40Lass2Text[] = {
    text_start("I came to OLIVINE"
        t_line "by ship to see the"
        t_para "sights and soak up"
        t_line "the atmosphere."
        t_para "Being a port, it"
        t_line "feels so different"
        t_cont "from a big city."
        t_done )
};
const txt_cmd_s Route40StandingYoungsterText[] = {
    text_start("Have you gone to"
        t_line "the BATTLE TOWER?"
        t_para "I think a lot of"
        t_line "tough trainers"
        t_para "have gathered"
        t_line "there already."
        t_para "But since you have"
        t_line "so many BADGES,"
        t_para "you shouldn't do"
        t_line "badly at all."
        t_done )
};
const txt_cmd_s MeetMonicaText[] = {
    text_start("MONICA: Glad to"
        t_line "meet you. I'm"
        t_para "MONICA of Monday."
        t_done )
};
const txt_cmd_s MonicaGivesGiftText[] = {
    text_start("As a token of our"
        t_line "friendship, I have"
        t_cont "a gift for you!"
        t_done )
};
const txt_cmd_s MonicaGaveGiftText[] = {
    text_start("MONICA: It's an"
        t_line "item that raises"
        t_para "the power of fly-"
        t_line "ing-type moves."
        t_para "You should equip a"
        t_line "bird #MON with"
        t_cont "that item."
        t_done )
};
const txt_cmd_s MonicaMondayText[] = {
    text_start("MONICA: My broth-"
        t_line "ers and sisters"
        t_para "are all over the"
        t_line "place."
        t_para "See if you could"
        t_line "find them all!"
        t_done )
};
const txt_cmd_s MonicaNotMondayText[] = {
    text_start("MONICA: I don't"
        t_line "think today is"
        t_cont "Monday. How sad…"
        t_done )
};
const txt_cmd_s Route40SignText[] = {
    text_start("ROUTE 40"
        t_para "CIANWOOD CITY -"
        t_line "OLIVINE CITY"
        t_done )
    //db(0, 0) // filler
};
