#include "../constants.h"
#include "../util/scripting.h"
#include "Route15.h"
//// EVENTS
enum {
    ROUTE15_YOUNGSTER1 = 2,
    ROUTE15_YOUNGSTER2,
    ROUTE15_YOUNGSTER3,
    ROUTE15_YOUNGSTER4,
    ROUTE15_TEACHER1,
    ROUTE15_TEACHER2,
    ROUTE15_POKE_BALL,
};

const Script_fn_t Route15_SceneScripts[] = {
    0,
};

const struct MapCallback Route15_MapCallbacks[] = {
    0,
};

const struct MapScripts Route15_MapScripts = {
    .scene_script_count = 0, // lengthof(Route15_SceneScripts),
    .scene_scripts = Route15_SceneScripts,

    .callback_count = 0, // lengthof(Route15_MapCallbacks),
    .callbacks = Route15_MapCallbacks,
};

static const struct CoordEvent Route15_CoordEvents[] = {
    0,
};

static const struct BGEvent Route15_BGEvents[] = {
    bg_event(19, 9, BGEVENT_READ, &Route15Sign),
};

static const struct WarpEventData Route15_WarpEvents[] = {
    warp_event(2, 4, ROUTE_15_FUCHSIA_GATE, 3),
    warp_event(2, 5, ROUTE_15_FUCHSIA_GATE, 4),
};

static const struct ObjEvent Route15_ObjectEvents[] = {
    object_event(10, 10, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 4, &TrainerSchoolboyKipp, -1),
    object_event(15, 13, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerSchoolboyTommy, -1),
    object_event(33, 10, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerSchoolboyJohnny, -1),
    object_event(27, 10, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerSchoolboyBilly, -1),
    object_event(30, 12, SPRITE_TEACHER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 4, &TrainerTeacherColette, -1),
    object_event(20, 10, SPRITE_TEACHER, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 3, &TrainerTeacherHillary, -1),
    object_event(12, 5, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &Route15PPUp, EVENT_ROUTE_15_PP_UP),
};

const struct MapEvents Route15_MapEvents = {
    .warp_event_count = lengthof(Route15_WarpEvents),
    .warp_events = Route15_WarpEvents,

    .coord_event_count = 0, // lengthof(Route15_CoordEvents),
    .coord_events = Route15_CoordEvents,

    .bg_event_count = lengthof(Route15_BGEvents),
    .bg_events = Route15_BGEvents,

    .obj_event_count = lengthof(Route15_ObjectEvents),
    .obj_events = Route15_ObjectEvents,
};

//// CODE

const struct TrainerObj TrainerTeacherColette = {TEACHER, COLETTE, EVENT_BEAT_TEACHER_COLETTE, TeacherColetteSeenText, TeacherColetteBeatenText, 0, TrainerTeacherColette_Script};
bool TrainerTeacherColette_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(TeacherColetteAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerTeacherHillary = {TEACHER, HILLARY, EVENT_BEAT_TEACHER_HILLARY, TeacherHillarySeenText, TeacherHillaryBeatenText, 0, TrainerTeacherHillary_Script};
bool TrainerTeacherHillary_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(TeacherHillaryAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSchoolboyKipp = {SCHOOLBOY, KIPP, EVENT_BEAT_SCHOOLBOY_KIP, SchoolboyKippSeenText, SchoolboyKippBeatenText, 0, TrainerSchoolboyKipp_Script};
bool TrainerSchoolboyKipp_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SchoolboyKippAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSchoolboyTommy = {SCHOOLBOY, TOMMY, EVENT_BEAT_SCHOOLBOY_TOMMY, SchoolboyTommySeenText, SchoolboyTommyBeatenText, 0, TrainerSchoolboyTommy_Script};
bool TrainerSchoolboyTommy_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SchoolboyTommyAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSchoolboyJohnny = {SCHOOLBOY, JOHNNY, EVENT_BEAT_SCHOOLBOY_JOHNNY, SchoolboyJohnnySeenText, SchoolboyJohnnyBeatenText, 0, TrainerSchoolboyJohnny_Script};
bool TrainerSchoolboyJohnny_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SchoolboyJohnnyAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSchoolboyBilly = {SCHOOLBOY, BILLY, EVENT_BEAT_SCHOOLBOY_BILLY, SchoolboyBillySeenText, SchoolboyBillyBeatenText, 0, TrainerSchoolboyBilly_Script};
bool TrainerSchoolboyBilly_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SchoolboyBillyAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Route15Sign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route15SignText)
    SCRIPT_END
}
const struct ItemBall Route15PPUp = {PP_UP, 1};
const txt_cmd_s TeacherColetteSeenText[] = {
    text_start("Have you forgotten"
        t_line "anything?"
        t_done )
};
const txt_cmd_s TeacherColetteBeatenText[] = {
    text_start("Kyaaah!"
        t_done )
};
const txt_cmd_s TeacherColetteAfterBattleText[] = {
    text_start("Before I became a"
        t_line "teacher, I used to"
        t_para "forget a lot of"
        t_line "things."
        t_done )
};
const txt_cmd_s TeacherHillarySeenText[] = {
    text_start("On sunny days, I"
        t_line "think that the"
        t_para "kids would rather"
        t_line "be playing in the"
        t_para "schoolyard than"
        t_line "studying in class."
        t_done )
};
const txt_cmd_s TeacherHillaryBeatenText[] = {
    text_start("I didn't want to"
        t_line "lose…"
        t_done )
};
const txt_cmd_s TeacherHillaryAfterBattleText[] = {
    text_start("Studying is impor-"
        t_line "tant, but exercise"
        t_cont "is just as vital."
        t_done )
};
const txt_cmd_s SchoolboyKippSeenText[] = {
    text_start("Hang on. I have to"
        t_line "phone my mom."
        t_done )
};
const txt_cmd_s SchoolboyKippBeatenText[] = {
    text_start("Sorry, Mom!"
        t_line "I was beaten!"
        t_done )
};
const txt_cmd_s SchoolboyKippAfterBattleText[] = {
    text_start("My mom worries so"
        t_line "much about me, I"
        t_para "have to phone her"
        t_line "all the time."
        t_done )
};
const txt_cmd_s SchoolboyTommySeenText[] = {
    text_start("Let's battle."
        t_line "I won't lose!"
        t_done )
};
const txt_cmd_s SchoolboyTommyBeatenText[] = {
    text_start("I forgot to do my"
        t_line "homework!"
        t_done )
};
const txt_cmd_s SchoolboyTommyAfterBattleText[] = {
    text_start("Sayonara! I just"
        t_line "learned that in my"
        t_cont "Japanese class."
        t_done )
};
const txt_cmd_s SchoolboyJohnnySeenText[] = {
    text_start("We're on a field"
        t_line "trip to LAVENDER"
        t_para "RADIO TOWER for"
        t_line "social studies."
        t_done )
};
const txt_cmd_s SchoolboyJohnnyBeatenText[] = {
    text_start("You're wickedly"
        t_line "tough!"
        t_done )
};
const txt_cmd_s SchoolboyJohnnyAfterBattleText[] = {
    text_start("I'm tired of walk-"
        t_line "ing. I need to"
        t_cont "take a break."
        t_done )
};
const txt_cmd_s SchoolboyBillySeenText[] = {
    text_start("My favorite class"
        t_line "is gym!"
        t_done )
};
const txt_cmd_s SchoolboyBillyBeatenText[] = {
    text_start("Oh, no!"
        t_line "How could I lose?"
        t_done )
};
const txt_cmd_s SchoolboyBillyAfterBattleText[] = {
    text_start("If #MON were a"
        t_line "subject at school,"
        t_cont "I'd be the best!"
        t_done )
};
const txt_cmd_s Route15SignText[] = {
    text_start("ROUTE 15"
        t_para "FUCHSIA CITY -"
        t_line "LAVENDER TOWN"
        t_done )
    //db(0, 0) // filler
};
