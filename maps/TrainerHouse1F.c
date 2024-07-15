#include "../constants.h"
#include "../util/scripting.h"
#include "TrainerHouse1F.h"
//// EVENTS
enum {
    TRAINERHOUSE1F_RECEPTIONIST = 2,
    TRAINERHOUSE1F_COOLTRAINER_M,
    TRAINERHOUSE1F_COOLTRAINER_F,
    TRAINERHOUSE1F_YOUNGSTER,
    TRAINERHOUSE1F_GENTLEMAN,
};

const Script_fn_t TrainerHouse1F_SceneScripts[] = {
    0,
};

const struct MapCallback TrainerHouse1F_MapCallbacks[] = {
    0,
};

const struct MapScripts TrainerHouse1F_MapScripts = {
    .scene_script_count = 0, // lengthof(TrainerHouse1F_SceneScripts),
    .scene_scripts = TrainerHouse1F_SceneScripts,

    .callback_count = 0, // lengthof(TrainerHouse1F_MapCallbacks),
    .callbacks = TrainerHouse1F_MapCallbacks,
};

static const struct CoordEvent TrainerHouse1F_CoordEvents[] = {
    0,
};

static const struct BGEvent TrainerHouse1F_BGEvents[] = {
    bg_event(5, 0, BGEVENT_READ, &TrainerHouseSign1),
    bg_event(7, 0, BGEVENT_READ, &TrainerHouseSign2),
    bg_event(7, 10, BGEVENT_READ, &TrainerHouseIllegibleBook),
};

static const struct WarpEventData TrainerHouse1F_WarpEvents[] = {
    warp_event(2, 13, VIRIDIAN_CITY, 3),
    warp_event(3, 13, VIRIDIAN_CITY, 3),
    warp_event(8, 2, TRAINER_HOUSE_B1F, 1),
};

static const struct ObjEvent TrainerHouse1F_ObjectEvents[] = {
    object_event(0, 11, SPRITE_RECEPTIONIST, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &TrainerHouse1FReceptionistScript, -1),
    object_event(7, 11, SPRITE_COOLTRAINER_M, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &TrainerHouse1FCooltrainerMScript, -1),
    object_event(6, 2, SPRITE_COOLTRAINER_F, SPRITEMOVEDATA_STANDING_DOWN, 2, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &TrainerHouse1FCooltrainerFScript, -1),
    object_event(4, 8, SPRITE_YOUNGSTER, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 2, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &TrainerHouse1FYoungsterScript, -1),
    object_event(2, 4, SPRITE_GENTLEMAN, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &TrainerHouse1FGentlemanScript, -1),
};

const struct MapEvents TrainerHouse1F_MapEvents = {
    .warp_event_count = lengthof(TrainerHouse1F_WarpEvents),
    .warp_events = TrainerHouse1F_WarpEvents,

    .coord_event_count = 0, // lengthof(TrainerHouse1F_CoordEvents),
    .coord_events = TrainerHouse1F_CoordEvents,

    .bg_event_count = lengthof(TrainerHouse1F_BGEvents),
    .bg_events = TrainerHouse1F_BGEvents,

    .obj_event_count = lengthof(TrainerHouse1F_ObjectEvents),
    .obj_events = TrainerHouse1F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "TrainerHouse1F.h"

bool TrainerHouse1FReceptionistScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(TrainerHouse1FReceptionistText)
    SCRIPT_END
}
bool TrainerHouse1FCooltrainerMScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(TrainerHouse1FCooltrainerMText)
    SCRIPT_END
}
bool TrainerHouse1FCooltrainerFScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(TrainerHouse1FCooltrainerFText)
    SCRIPT_END
}
bool TrainerHouse1FYoungsterScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(TrainerHouse1FYoungsterText)
    SCRIPT_END
}
bool TrainerHouse1FGentlemanScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(TrainerHouse1FGentlemanText)
    SCRIPT_END
}
bool TrainerHouseSign1(script_s* s) {
    SCRIPT_BEGIN
    jumptext(TrainerHouseSign1Text)
    SCRIPT_END
}
bool TrainerHouseSign2(script_s* s) {
    SCRIPT_BEGIN
    jumptext(TrainerHouseSign2Text)
    SCRIPT_END
}
bool TrainerHouseIllegibleBook(script_s* s) {
    SCRIPT_BEGIN
    jumptext(TrainerHouseIllegibleText)
    SCRIPT_END
}
const txt_cmd_s TrainerHouse1FReceptionistText[] = {
    text_start("Welcome to TRAINER"
        t_line "HOUSE, the newest"
        t_para "and most happening"
        t_line "place in VIRIDIAN."
        t_para "We're open to"
        t_line "trainers only."
        t_para "You can battle"
        t_line "against the best"
        t_para "of the best right"
        t_line "downstairs."
        t_done )
};
const txt_cmd_s TrainerHouse1FCooltrainerMText[] = {
    text_start("VIRIDIAN is the"
        t_line "town closest to"
        t_cont "INDIGO PLATEAU."
        t_para "They built this"
        t_line "place because so"
        t_para "many trainers pass"
        t_line "through on their"
        t_para "way up to INDIGO"
        t_line "PLATEAU."
        t_done )
};
const txt_cmd_s TrainerHouse1FCooltrainerFText[] = {
    text_start("They hold practice"
        t_line "battles downstairs"
        t_cont "here."
        t_para "I would love to"
        t_line "see how well a"
        t_para "trainer from JOHTO"
        t_line "battles."
        t_done )
};
const txt_cmd_s TrainerHouse1FYoungsterText[] = {
    text_start("I guess you can't"
        t_line "become the CHAMP"
        t_para "unless you go all"
        t_line "over the place and"
        t_para "battle all kinds"
        t_line "of people."
        t_para "The CHAMPION from"
        t_line "PALLET traveled to"
        t_para "all the cities and"
        t_line "towns in KANTO."
        t_done )
};
const txt_cmd_s TrainerHouse1FGentlemanText[] = {
    text_start("Whew… I'm taking a"
        t_line "rest from #MON"
        t_cont "battles."
        t_done )
};
const txt_cmd_s TrainerHouseSign1Text[] = {
    text_start("Practice battles"
        t_line "are held in the"
        t_para "TRAINING HALL"
        t_line "downstairs."
        t_para "Skilled trainers"
        t_line "are invited to"
        t_cont "participate."
        t_done )
};
const txt_cmd_s TrainerHouseSign2Text[] = {
    text_start("There are no rules"
        t_line "or regulations for"
        t_para "practice matches."
        t_line "Just like in field"
        t_para "battles, anything"
        t_line "goes!"
        t_done )
};
const txt_cmd_s TrainerHouseIllegibleText[] = {
    text_start("…What's this?"
        t_line "A strategy memo?"
        t_para "This writing looks"
        t_line "like ONIX tracks…"
        t_para "It's completely"
        t_line "illegible…"
        t_done )
    //db(0, 0) // filler
};
